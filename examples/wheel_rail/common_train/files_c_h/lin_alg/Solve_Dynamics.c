/* Solving Dynamics Forward */
#ifdef MATLAB_MEX_FILE
   #define printf mexPrintf
#endif  

#ifdef __EXTERNAL
 #include "external_def.h"
#endif

#ifdef TRI
  #ifndef TRI_LU
   #define TRI_LDL
  #endif
#endif

#define PERM(fi, cj, fi_ini, cj_ini, stride, vperm) (vperm[fi+fi_ini]+vperm[cj+cj_ini]*stride)
#define PERM2(fi, cj, fi_ini, cj_ini, stride, p,q) (p[fi+fi_ini]+q[cj+cj_ini]*stride)
/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP

#ifdef DDL
    _Qgamma=Qgamma();
    _MXdPhi_dqZero=MXdPhi_dqZero();
    #ifdef INV
      Mat_Inv(MXdPhi_dqZero_n_cols ,_MXdPhi_dqZero, _INV_MX_aux, Buffer);
      Mat_Vect_Mult(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols,_INV_MX_aux ,_Qgamma, +1,ddqunknowns );
    #endif
    #ifdef TRI_LDL
      solve_lin_sys_ldl(MXdPhi_dqZero_n_rows, _MXdPhi_dqZero, _Qgamma, ddqunknowns, Buffer3L_LDL,Buffer3U_LDL,Buffer3d_LDL,Buffer3y_LDL);
    #endif
    #ifdef TRI_LU
      solve_lin_sys_plu_matrix(MXdPhi_dqZero_n_cols, _MXdPhi_dqZero, _Qgamma,ddqunknowns,Buffery_LU , pv, qv);
    #endif
    for (i=0; i<n_gen_accel; i++){ ddq[i]=ddqunknowns[i]; }
    for (i=0; i<n_unknowns ; i++){ unknowns[i]=ddqunknowns[n_gen_accel+i]; }
#endif

#ifdef DDQ

    _Q=Q();
    _M=M();

    #ifdef INV
    double Buffer[2*MAX(M_n_cols,Phi_q_n_rows)*MAX(M_n_cols,Phi_q_n_rows)];
    Mat_Inv(M_n_cols ,_M, _INV_M_aux,Buffer); 
    Mat_Vect_Mult(M_n_rows, M_n_cols,_INV_M_aux ,_Q, +1, aux_ddq1 );
    Phi_q();
    Mat_Trasp(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, Trasp_Phi_q); 
    Mat_Mat_Mult(M_n_rows, M_n_cols, Phi_q_n_rows, _INV_M_aux , Trasp_Phi_q, +1, aux_Phi_q_T ); 
    Mat_Vect_Mult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q , aux_ddq1, +1, bb);
    Gamma();
    for (i=0; i<n_unknowns; i++){ bb[i]=bb[i]-_Gamma[i]; } 
    Mat_Mat_Mult(Phi_q_n_rows, Phi_q_n_cols, Phi_q_n_rows, _Phi_q , aux_Phi_q_T, +1, AA); 
    Mat_Inv(Phi_q_n_rows, AA, INV_AA,Buffer);
    Mat_Vect_Mult(n_unknowns, n_unknowns, INV_AA , bb, +1, unknowns); 
    Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, aux_Phi_q_T, unknowns, +1, aux_ddq2);
    for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; } 
    #endif

    #ifdef TRI
    ldl(M_n_rows,_M , Buffer3L_LDL,Buffer3d_LDL);
    Mat_Trasp(M_n_rows, M_n_rows, Buffer3L_LDL,Buffer3U_LDL);
    forward_substitution(M_n_rows, Buffer3L_LDL, _Q, Buffer3y_LDL);
    for (i = 0; i< M_n_rows ; i++){ Buffer3y_LDL[i] = Buffer3y_LDL[i] / Buffer3d_LDL[ i ]; }
    backward_substitution(M_n_rows, Buffer3U_LDL, Buffer3y_LDL, aux_ddq1); /* aux_ddq1 = M^(â?»1)*Q */

    Mat_Trasp(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, Trasp_dPhi_dq);
    
    for (i = 0; i< dPhi_dq_n_rows ; i++){
        forward_substitution(M_n_rows, Buffer3L_LDL, &Trasp_dPhi_dq[ i * M_n_rows ], &BufferY_LDLM[ i * M_n_rows ]);
        for (j = 0; j< M_n_rows ; j++){ 
            BufferY_LDLM[ j + i * M_n_rows ] = BufferY_LDLM[ j + i * M_n_rows ] / Buffer3d_LDL[ j ];
        }
        backward_substitution(M_n_rows, Buffer3U_LDL, &BufferY_LDLM[ i * M_n_rows ], &aux_Phi_q_T[ i * M_n_rows ]);/* aux_Phi_q_T=M^(â?»1)*(Phi_q)' */
    }

    Mat_Vect_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq , aux_ddq1, +1, bb); /* bb=(Phi_q)*M^(â?»1)*Q - Gamma*/
    Gamma();
    for (i=0; i<n_unknowns; i++){ bb[i]=bb[i]-_Gamma[i]; }
    Mat_Mat_Mult_SO(dPhi_dq_n_rows, dPhi_dq_n_cols, dPhi_dq_n_rows, _dPhi_dq , aux_Phi_q_T, +1, AA); /* AA=(Phi_q)*M^(â?»1)*(Phi_q)'*/

    solve_lin_sys_ldl(n_unknowns, AA , bb, unknowns, Buffer3L_LDL,Buffer3U_LDL,Buffer3d_LDL,Buffer3y_LDL); /*lambda=((Phi_q)*M^(â?»1)*(Phi_q)')^(-1)*((Phi_q)*M^(â?»1)*Q - Gamma)*/
    Mat_Vect_Mult(dPhi_dq_n_cols, dPhi_dq_n_rows, aux_Phi_q_T, unknowns, +1, aux_ddq2);
    for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; } /*ddq= M^(â?»1)*Q - M^(â?»1)*(Phi_q)'*lambda */
    #endif

    /*Copy ddq and unknowns to ddqunknows*/
    for (i=0; i< n_gen_accel; i++){ ddqunknowns[i]=ddq[i]; } 
    for (i=0; i< n_unknowns; i++){ ddqunknowns[i+n_gen_accel]=unknowns[i]; } 
#endif

#endif
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND

/*for (i = 0; i< n_gen_coord ; i++){
perm_M[i]=perm_vel[i];
}*/


/*Calculate b*/
_Gamma=Gamma();
forward_substitution_LUpq_pq_x(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector, perm_vel , _Gamma, y);
backward_substitution_LUpq_pq_x(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector, perm_vel , y, b);

_M=M();

/*Mzd*A*/
i_ini=n_vel_dep;
j_ini=0;
for (i=0; i<n_vel_indep; i++){
	for (j=0; j< n_vel_indep; j++){
		AUX_M_indep_indep_1[i+j*n_vel_indep] = 0.0;
		for	(k=0; k<dPhi_dq_n_rows; k++){
			AUX_M_indep_indep_1[i+j*n_vel_indep] =  _M[PERM(i,k,i_ini, j_ini,M_n_rows, perm_vel)] * A[k+j*dPhi_dq_n_rows] + AUX_M_indep_indep_1[i+j*n_vel_indep];
			}
		}
	}
/*A'*Mdd*/
i_ini=0;
j_ini=0;
for (i=0; i<n_vel_indep; i++){
	for (j=0; j< dPhi_dq_n_rows; j++){
		AUX_M_indep_dep_1[i+j*n_vel_indep] = 0.0;
		for	(k=0; k<dPhi_dq_n_rows; k++){
  			AUX_M_indep_dep_1[i+j*n_vel_indep] =   A[k+i*dPhi_dq_n_rows] * _M[PERM(k,j,i_ini, j_ini,M_n_rows, perm_vel)]  + AUX_M_indep_dep_1[i+j*n_vel_indep];
			}
		}
	}
/*(A'*Mdd)*A=AUX_M_indep_indep_2*/
Mat_Mat_Mult(n_vel_indep, dPhi_dq_n_rows, n_vel_indep, AUX_M_indep_dep_1, A, +1, AUX_M_indep_indep_2);

_Q=Q();
/*AUX_V_indep_1=A'* Qd*/
 for (i=0; i<n_vel_indep; i++){
	AUX_V_indep_1[i] = 0.0;
	for (j=0; j<dPhi_dq_n_rows; j++){
		AUX_V_indep_1[i] = A[j+i*dPhi_dq_n_rows] * _Q[perm_vel[j]] + AUX_V_indep_1[i];
		}
	}
/*MZ =  Mzz + Mzd*A +(Mzd*A )' + (A'*Mdd)*A*/
i_ini=n_vel_dep;
j_ini=n_vel_dep;
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < n_vel_indep; j++){	
		_MZ[i + j * n_vel_indep]= _M[PERM(i,j,i_ini, j_ini, M_n_rows, perm_vel)] + AUX_M_indep_indep_1[j + i * n_vel_indep] + AUX_M_indep_indep_1[i + j * n_vel_indep] + AUX_M_indep_indep_2[i + j * n_vel_indep]; 
		}
	}
/*Mzd+(A'*Mdd)*/
i_ini=n_vel_dep;
j_ini=0; 
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < dPhi_dq_n_rows; j++){
		AUX_M_indep_dep_2[i + j * n_vel_indep] = _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] + AUX_M_indep_dep_1[i + j * n_vel_indep];
		}
	}
Mat_Vect_Mult(n_vel_indep, dPhi_dq_n_rows, AUX_M_indep_dep_2, b, +1, AUX_V_indep_2);	
/*_QZ = Qz + A'* Qd - (Mzd+(A'*Mdd))*b*/
	for (i = 0; i < n_vel_indep; i++){
		_QZ[i] = _Q[perm_vel[i+n_vel_dep]] + AUX_V_indep_1[i] - AUX_V_indep_2[i];
	}
/* Solve MZ * ddz = QZ */

solve_lin_sys_ldl(n_vel_indep,_MZ , _QZ, &aux_ddq[n_vel_dep], AUX_M_indep_indep_1, AUX_M_indep_indep_2 , AUX_V_indep_1 , AUX_V_indep_2);

/* Calculate  ddd = A * ddz + b -> C.4 Equation DSM*/
Mat_Vect_Mult(dPhi_dq_n_rows, n_vel_indep, A, &aux_ddq[n_vel_dep], +1, aux_ddq);
for (i = 0; i < dPhi_dq_n_rows; i++){ aux_ddq[i] = aux_ddq[ i] + b[i]; }
for (i = 0; i < dPhi_dq_n_cols; i++){ ddq[perm_vel[i]]=aux_ddq[i]; }

/* ========================================================================================================================================= */
/* Calculate unknowns */
/* Phi_d_T * lambda = Qd - Mdd * ddd - Mdz * ddz */
/* ========================================================================================================================================= */
/* Mdd · ddd */
i_ini=0;
j_ini=0;
for (i=0; i<n_vel_dep; i++){
	AUX_L_dep[i] = 0.0;
	for (j=0; j<n_vel_dep; j++){
		AUX_L_dep[i] = AUX_L_dep[i] + _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * ddq[perm_vel[j]] ;
		}
	}
/* Mdz · ddz */
i_ini=0;
j_ini=n_vel_dep;
for (i=0; i<n_vel_dep; i++){
	AUX_L_indep[i] = 0.0;
	for (j=0; j<n_vel_indep; j++){
		AUX_L_indep[i] = AUX_L_indep[i] + _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * ddq[perm_vel[j+n_vel_dep]] ;
		}
	}
/* Qd - Mdd * ddd - Mdz * ddz */
for (i = 0; i < n_vel_dep; i++){
	b_aux[i] = _Q[perm_vel[i]] - AUX_L_dep[i] - AUX_L_indep[i];
}

forward_substitution_LUpq_T_pq_q (n_vel_dep,n_vel_dep, _dPhi_dq, p_vector, perm_vel, b_aux, yL);
backward_substitution_LUpq_T_pq_q(n_vel_dep,n_vel_dep, _dPhi_dq, p_vector, perm_vel, yL, unknowns);

/*Copy ddq and unknowns to ddqunknows*/
for (i=0; i< n_gen_accel; i++){ ddqunknowns[i]=ddq[i]; } 
for (i=0; i< n_unknowns; i++){ ddqunknowns[i+n_gen_accel]=unknowns[i]; } 
//printf("ddq= \n");Vect_Print    (n_gen_accel, ddq);
#endif
/* ********************************************************************************************* */





