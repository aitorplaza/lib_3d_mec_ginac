/* Solving Dynamics Forward */
#ifdef MATLAB_MEX_FILE
   #define printf mexPrintf
#endif  

#ifdef __EXTERNAL
 #include "external_def.h"
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

    _Q = Q();
    _M = M();
    _Gamma = Gamma();
    _dPhi_dq = dPhi_dq();

    #ifdef INV
    double Buffer[2*MAX(M_n_cols,dPhi_dq_n_rows)*MAX(M_n_cols,dPhi_dq_n_rows)];
    Mat_Inv(M_n_cols ,_M, _INV_M_aux,Buffer); 
    Mat_Vect_Mult(M_n_rows, M_n_cols,_INV_M_aux ,_Q, +1, aux_ddq1 );

    Mat_Trasp(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, Trasp_dPhi_dq); 
    Mat_Mat_Mult(M_n_rows, M_n_cols, dPhi_dq_n_rows, _INV_M_aux , Trasp_dPhi_dq, +1, aux_dPhi_dq_T ); 
    Mat_Vect_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq , aux_ddq1, +1, bb);

    for (i=0; i<n_unknowns; i++){ bb[i]=bb[i]-_Gamma[i]; } 
    Mat_Mat_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, dPhi_dq_n_rows, _dPhi_dq , aux_dPhi_dq_T, +1, AA); 
    Mat_Inv(dPhi_dq_n_rows, AA, INV_AA,Buffer);
    Mat_Vect_Mult(n_unknowns, n_unknowns, INV_AA , bb, +1, unknowns); 
    Mat_Vect_Mult(dPhi_dq_n_cols, dPhi_dq_n_rows, aux_dPhi_dq_T, unknowns, +1, aux_ddq2);
    for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; } 
    #endif

    #if defined TRI_LDL || defined TRI_LU || defined TRI
    ldl(M_n_rows,_M , Buffer3L_LDL,Buffer3d_LDL); /*Forward y backwards con LDL, especifico*/
    Mat_Trasp(M_n_rows, M_n_rows, Buffer3L_LDL,Buffer3U_LDL);
    forward_substitution(M_n_rows, Buffer3L_LDL, _Q, Buffer3y_LDL);
    for (i = 0; i< M_n_rows ; i++){ Buffer3y_LDL[i] = Buffer3y_LDL[i] / Buffer3d_LDL[ i ]; }
    backward_substitution(M_n_rows, Buffer3U_LDL, Buffer3y_LDL, aux_ddq1); /* aux_ddq1 = M^(-1)*Q */

    Mat_Trasp(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, Trasp_dPhi_dq);
    
    for (i = 0; i< dPhi_dq_n_rows ; i++){
        forward_substitution(M_n_rows, Buffer3L_LDL, &Trasp_dPhi_dq[ i * M_n_rows ], &BufferY_LDLM[ i * M_n_rows ]);
        for (j = 0; j< M_n_rows ; j++){ 
            BufferY_LDLM[ j + i * M_n_rows ] = BufferY_LDLM[ j + i * M_n_rows ] / Buffer3d_LDL[ j ];
        }
        backward_substitution(M_n_rows, Buffer3U_LDL, &BufferY_LDLM[ i * M_n_rows ], &aux_dPhi_dq_T[ i * M_n_rows ]);/* aux_dPhi_dq_T=M^(-1)*(dPhi_dq)' */
    }

    Mat_Vect_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq , aux_ddq1, +1, bb); /* bb=(dPhi_dq)*M^(-1)*Q */

    for (i=0; i<n_unknowns; i++){ bb[i]=bb[i]-_Gamma[i]; }/* bb = bb - Gamma = (dPhi_dq)*M^(-1)*Q - Gamma */

    Mat_Mat_Mult_SO(dPhi_dq_n_rows, dPhi_dq_n_cols, dPhi_dq_n_rows, _dPhi_dq , aux_dPhi_dq_T, +1, AA); /* AA = (dPhi_dq)*M^(-1)*(dPhi_dq)'*/

    solve_lin_sys_ldl(n_unknowns, AA , bb, unknowns, Buffer3L_LDL,Buffer3U_LDL,Buffer3d_LDL,Buffer3y_LDL); /*lambda = ((dPhi_dq)*M^(-1)*(dPhi_dq)')^(-1)*((dPhi_dq)*M^(-1)*Q - Gamma)*/
    Mat_Vect_Mult(dPhi_dq_n_cols, dPhi_dq_n_rows, aux_dPhi_dq_T, unknowns, +1, aux_ddq2);/* aux_ddq2 = M^(-1)*(dPhi_dq)'*lambda */
    for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; } /*ddq= aux_ddq1 - aux_ddq2 = M^(-1)*Q - M^(-1)*(dPhi_dq)'*lambda */
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

/*_M=M();
_Q=Q();*/
_MQ=MQ();


/*Mat_Print(MQ_n_rows, MQ_n_cols, _MQ);*/


_Gamma=Gamma();
_dPhi_dq = dPhi_dq();

lufp4(dPhi_dq_n_rows,Phi_q_n_rows, dPhi_dq_n_cols, _dPhi_dq, p_vector, perm_vel);/*for coordinate partitioning*/

for (i = 0; i< n_vel_indep ; i++){
  backward_substitution_LUpq_pq_A(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector, perm_vel, &_dPhi_dq[perm_vel[i+n_vel_dep] * dPhi_dq_n_rows ], &A[ i * dPhi_dq_n_rows ]); /* Calculate A with this dedicated backward */
}

/*Calculate b*/
forward_substitution_LUpq_pq_x(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector, perm_vel , _Gamma, yddq);
backward_substitution_LUpq_pq_x(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector, perm_vel , yddq, b);

/*Mzd*A*/
i_ini=n_vel_dep;
j_ini=0;
for (i=0; i<n_vel_indep; i++){
	for (j=0; j< n_vel_indep; j++){
		AUX_M_indep_indep_1[i+j*n_vel_indep] = 0.0;
		for	(k=0; k<dPhi_dq_n_rows; k++){
			/*AUX_M_indep_indep_1[i+j*n_vel_indep] =  _M[PERM(i,k,i_ini, j_ini,M_n_rows, perm_vel)] * A[k+j*dPhi_dq_n_rows] + AUX_M_indep_indep_1[i+j*n_vel_indep];*/
            AUX_M_indep_indep_1[i+j*n_vel_indep] =  _MQ[PERM(i,k,i_ini, j_ini,M_n_rows, perm_vel)] * A[k+j*dPhi_dq_n_rows] + AUX_M_indep_indep_1[i+j*n_vel_indep];
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
  			/*AUX_M_indep_dep_1[i+j*n_vel_indep] =   A[k+i*dPhi_dq_n_rows] * _M[PERM(k,j,i_ini, j_ini,M_n_rows, perm_vel)]  + AUX_M_indep_dep_1[i+j*n_vel_indep];*/
            AUX_M_indep_dep_1[i+j*n_vel_indep] =   A[k+i*dPhi_dq_n_rows] * _MQ[PERM(k,j,i_ini, j_ini,M_n_rows, perm_vel)]  + AUX_M_indep_dep_1[i+j*n_vel_indep];
			}
		}
	}
/*(A'*Mdd)*A=AUX_M_indep_indep_2*/
Mat_Mat_Mult(n_vel_indep, dPhi_dq_n_rows, n_vel_indep, AUX_M_indep_dep_1, A, +1, AUX_M_indep_indep_2);

/*AUX_V_indep_1=A'* Qd*/

for (i=0; i<n_vel_indep; i++){
	AUX_V_indep_1[i] = 0.0;
	for (j=0; j<dPhi_dq_n_rows; j++){
		//AUX_V_indep_1[i] = A[j+i*dPhi_dq_n_rows] * _Q[perm_vel[j]] + AUX_V_indep_1[i];*/
 		AUX_V_indep_1[i] = A[j+i*dPhi_dq_n_rows] * _MQ[MQ_n_rows*n_gen_accel+perm_vel[j]] + AUX_V_indep_1[i];
     	/*printf ("q = %g q2 = %g\n",_Q[perm_vel[j]], _MQ[MQ_n_rows*j_ini+perm_vel[j]]);*/
        }
	}
/*MZ =  Mzz + Mzd*A +(Mzd*A )' + (A'*Mdd)*A*/
i_ini=n_vel_dep;
j_ini=n_vel_dep;
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < n_vel_indep; j++){	
		/*_MZ[i + j * n_vel_indep]= _M[PERM(i,j,i_ini, j_ini, M_n_rows, perm_vel)] + AUX_M_indep_indep_1[j + i * n_vel_indep] + AUX_M_indep_indep_1[i + j * n_vel_indep] + AUX_M_indep_indep_2[i + j * n_vel_indep]; */
		_MZ[i + j * n_vel_indep]= _MQ[PERM(i,j,i_ini, j_ini, M_n_rows, perm_vel)] + AUX_M_indep_indep_1[j + i * n_vel_indep] + AUX_M_indep_indep_1[i + j * n_vel_indep] + AUX_M_indep_indep_2[i + j * n_vel_indep]; 

		}
	}
/*Mzd+(A'*Mdd)*/
i_ini=n_vel_dep;
j_ini=0; 
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < dPhi_dq_n_rows; j++){
		/*AUX_M_indep_dep_2[i + j * n_vel_indep] = _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] + AUX_M_indep_dep_1[i + j * n_vel_indep];*/
		AUX_M_indep_dep_2[i + j * n_vel_indep] = _MQ[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] + AUX_M_indep_dep_1[i + j * n_vel_indep];        
		}
	}
/* (Mzd+(A'*Mdd) )* b */   
Mat_Vect_Mult(n_vel_indep, dPhi_dq_n_rows, AUX_M_indep_dep_2, b, +1, AUX_V_indep_2);	

/*_QZ = Qz + A'* Qd - (Mzd+(A'*Mdd))*b*/
	for (i = 0; i < n_vel_indep; i++){
		/*_QZ[i] = _Q[perm_vel[i+n_vel_dep]] + AUX_V_indep_1[i] - AUX_V_indep_2[i];*/
        _QZ[i] = _MQ[MQ_n_rows*n_gen_accel+perm_vel[i+n_vel_dep]] + AUX_V_indep_1[i] - AUX_V_indep_2[i];
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
		/*AUX_L_dep[i] = AUX_L_dep[i] + _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * ddq[perm_vel[j]] ;*/
        AUX_L_dep[i] = AUX_L_dep[i] + _MQ[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * ddq[perm_vel[j]] ;
		}
	}
/* Mdz · ddz */
i_ini=0;
j_ini=n_vel_dep;
for (i=0; i<n_vel_dep; i++){
	AUX_L_indep[i] = 0.0;
	for (j=0; j<n_vel_indep; j++){
		/*AUX_L_indep[i] = AUX_L_indep[i] + _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * ddq[perm_vel[j+n_vel_dep]] ;*/
 		AUX_L_indep[i] = AUX_L_indep[i] + _MQ[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * ddq[perm_vel[j+n_vel_dep]] ;       
		}
	}
/* Qd - Mdd * ddd - Mdz * ddz */
for (i = 0; i < n_vel_dep; i++){
	/*b_aux[i] = _Q[perm_vel[i]] - AUX_L_dep[i] - AUX_L_indep[i];*/
    b_aux[i] = _MQ[MQ_n_rows*n_gen_accel+perm_vel[i]] - AUX_L_dep[i] - AUX_L_indep[i];
}

forward_substitution_LUpq_T_pq_q (n_vel_dep,n_vel_dep, _dPhi_dq, p_vector, perm_vel, b_aux, yL);
backward_substitution_LUpq_T_pq_q(n_vel_dep,n_vel_dep, _dPhi_dq, p_vector, perm_vel, yL, unknowns);

/*Copy ddq and unknowns to ddqunknows*/
for (i=0; i< n_gen_accel; i++){ ddqunknowns[i]=ddq[i]; } 
for (i=0; i< n_unknowns; i++){ ddqunknowns[i+n_gen_accel]=unknowns[i]; } 
//printf("ddq= \n");Vect_Print    (n_gen_accel, ddq);
#endif
/* ********************************************************************************************* */
//~ printf("ddq= \n");Vect_Print    (n_gen_accel, ddq);




