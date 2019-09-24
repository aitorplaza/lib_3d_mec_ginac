/* Solving Dynamics Forward */

#ifdef __EXTERNAL
 #include "external_def.h"
#endif

/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP

#ifndef DDL
	#ifndef DDQ
		#define DDQ
	#endif
#endif

 #ifdef MATLAB_MEX_FILE
   #define printf mexPrintf
#endif     
        
#ifdef DDL
_Qgamma=Qgamma();
_MXdPhi_dqZero=MXdPhi_dqZero();

	#ifdef INV
    double Buffer[2*MXdPhi_dqZero_n_cols*MXdPhi_dqZero_n_cols];
		Mat_Inv(MXdPhi_dqZero_n_cols ,_MXdPhi_dqZero, _INV_MX_aux, Buffer);
		Mat_Vect_Mult(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols,_INV_MX_aux ,_Qgamma, +1,ddqunknowns );
	#endif

	#ifdef TRI
    double Buffer3L_LDL[MXdPhi_dqZero_n_rows*MXdPhi_dqZero_n_rows];
    double Buffer3U_LDL[MXdPhi_dqZero_n_rows*MXdPhi_dqZero_n_rows];
    double Buffer3d_LDL[MXdPhi_dqZero_n_rows];
    double Buffer3y_LDL[MXdPhi_dqZero_n_rows];
		solve_lin_sys_ldl(MXdPhi_dqZero_n_rows,_MXdPhi_dqZero , _Qgamma, ddqunknowns, Buffer3L_LDL,Buffer3U_LDL,Buffer3d_LDL,Buffer3y_LDL);
	#endif

for (i=0; i<n_gen_accel; i++){ ddq[i]=ddqunknowns[i]; }
for (i=0; i<n_unknowns ; i++){ unknowns[i]=ddqunknowns[n_gen_accel+i]; }
#endif

#ifdef DDQ
_Q=Q();
_M=M();

	#ifdef INV
    double Buffer[2*MAX(M_n_cols,Phi_q_n_rows) * MAX(M_n_cols,Phi_q_n_rows)];
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
    double Buffer3L_LDL[M_n_rows*M_n_rows];
    double Buffer3U_LDL[M_n_rows*M_n_rows];
    double Buffer3d_LDL[M_n_rows];
    double Buffer3y_LDL[M_n_rows];
		solve_lin_sys_ldl(M_n_rows,_M , _Q, aux_ddq1, Buffer3L_LDL,Buffer3U_LDL,Buffer3d_LDL,Buffer3y_LDL);
		Phi_q();
		Mat_Trasp(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, Trasp_Phi_q);
    double BufferY_LDLM[M_n_rows*Phi_q_n_rows];
		solve_lin_sys_ldl_matrix(M_n_rows, _M , Phi_q_n_rows, Trasp_Phi_q, aux_Phi_q_T, Buffer3L_LDL,Buffer3U_LDL,Buffer3d_LDL,BufferY_LDLM);
		Mat_Vect_Mult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q , aux_ddq1, +1, bb);
		Gamma();
		for (i=0; i<n_unknowns; i++){ bb[i]=bb[i]-_Gamma[i]; }
		Mat_Mat_Mult(Phi_q_n_rows, Phi_q_n_cols, Phi_q_n_rows, _Phi_q , aux_Phi_q_T, +1, AA);
		solve_lin_sys_ldl(n_unknowns, AA , bb, unknowns, Buffer3L_LDL,Buffer3U_LDL,Buffer3d_LDL,Buffer3y_LDL);
		Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, aux_Phi_q_T, unknowns, +1, aux_ddq2);
		for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; }
	#endif

#endif

#endif
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND

	#ifdef INV
	/* Calculate A and b */
	Mat_Mat_Mult(Phi_d_n_cols, Phi_d_n_cols, Phi_z_n_cols, _Inv_Phi_d, _Phi_z, -1, A);
	_Gamma=Gamma();
	Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, _Gamma, +1, b);
	#endif

	#ifdef TRI
  Phi_d();/*new - moved to InitialPositionvelocity*/
  Phi_z();/*new - moved to InitialPositionvelocity*/

	/* Calculate A and b */

	/*
	solve_lin_sys_lu_matrix(Phi_d_n_cols, _Phi_d, Phi_z_n_cols, _Phi_z, A);
	for (i=0; i< Phi_d_n_cols*Phi_z_n_cols ; i++){ A[i]=-A[i]; }
	_Gamma=Gamma();
	solve_lin_sys_lu(Phi_d_n_cols, _Phi_d, _Gamma, b);
	*/
  double BufferLU[Phi_d_n_cols];
	lu(Phi_d_n_cols, _Phi_d, LU,o, BufferLU, niter);

	for (i = 0; i< Phi_z_n_cols ; i++){
		forward_substitution_piv(Phi_d_n_cols, LU, o, &_Phi_z[ i * Phi_d_n_cols ], &Y[ i * Phi_d_n_cols ]);
		backward_substitution_piv(Phi_d_n_cols, LU, o, &Y[ i * Phi_d_n_cols ], &A[ i * Phi_d_n_cols ]);
	}
	for (i=0; i< Phi_d_n_cols*Phi_z_n_cols ; i++){ A[i]=-A[i]; }
	_Gamma=Gamma();
	forward_substitution_piv(Phi_d_n_cols, LU, o, _Gamma, y);
	backward_substitution_piv(Phi_d_n_cols, LU, o, y, b);
	#endif


	/* Calculate MZ */
	Mzd();
	Mat_Mat_Mult(Phi_z_n_cols, Phi_d_n_cols, Phi_z_n_cols, _Mzd, A, +1, AUX_M_indep_indep_1);
	Mdd();
	for (j = 0; j < Phi_z_n_cols; j++){
		for(i = 0; i < Phi_d_n_cols; i++){AT[j + i * Phi_z_n_cols] = A[i + j * Phi_d_n_cols];}
	}
	Mat_Mat_Mult(Phi_z_n_cols, Phi_d_n_cols, Phi_d_n_cols, AT, _Mdd, +1, AUX_M_indep_dep_1);
	Mat_Mat_Mult(Phi_z_n_cols, Phi_d_n_cols, Phi_z_n_cols, AUX_M_indep_dep_1, A, +1, AUX_M_indep_indep_2);
	Qd();
	Mat_Vect_Mult(Phi_z_n_cols, Phi_d_n_cols, AT, _Qd, +1, AUX_V_indep_1);	
	Mzz();
	for (i = 0; i < Phi_z_n_cols; i++){
		for(j = 0; j < Phi_z_n_cols; j++){
			_MZ[i + j * Phi_z_n_cols]=_Mzz[i + j * Phi_z_n_cols] + AUX_M_indep_indep_1[j + i * Phi_z_n_cols] + AUX_M_indep_indep_1[i + j * Phi_z_n_cols] + AUX_M_indep_indep_2[i + j * Phi_z_n_cols];
		}
	}

		for (i = 0; i < Phi_z_n_cols; i++){
		for(j = 0; j < Phi_d_n_cols; j++){
			AUX_M_indep_dep_2[i + j * Phi_z_n_cols] = _Mzd[i + j * Phi_z_n_cols] + AUX_M_indep_dep_1[i + j * Phi_z_n_cols];
		}
	}

	/* Calculate QZ */
	Mat_Vect_Mult(Phi_z_n_cols, Phi_d_n_cols, AUX_M_indep_dep_2, b, +1, AUX_V_indep_2);	
	Qz();
	for (i = 0; i < Phi_z_n_cols; i++){
		_QZ[i] = _Qz[i] + AUX_V_indep_1[i] - AUX_V_indep_2[i];
	}

	/* Solve MZ * ddz = QZ */
	
	#ifdef INV
    double Buffer[2*Phi_z_n_cols*Phi_z_n_cols];
		Mat_Inv( Phi_z_n_cols, _MZ, INV_MZ, Buffer);
		Mat_Vect_Mult(Phi_z_n_cols, Phi_z_n_cols, INV_MZ, _QZ, +1, ddq);
	#endif

	#ifdef TRI
  double Buffer3L_LDL[Phi_z_n_cols*Phi_z_n_cols];
  double Buffer3U_LDL[Phi_z_n_cols*Phi_z_n_cols];
  double Buffer3d_LDL[Phi_z_n_cols];
  double Buffer3y_LDL[Phi_z_n_cols];
  solve_lin_sys_ldl(Phi_z_n_cols,_MZ , _QZ, ddq, Buffer3L_LDL,Buffer3U_LDL,Buffer3d_LDL,Buffer3y_LDL);
	#endif

	#ifndef INV
		#ifndef TRI
			printf("Please select Solver for Linear System\n");
		#endif
	#endif

	/* Calculate ddq ===> "ddd = A * ddz + b" */
	Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, A, ddq, +1, &ddq[Phi_z_n_cols]);	
	for (i = 0; i < Phi_d_n_cols; i++){ ddq[Phi_z_n_cols + i] = ddq[Phi_z_n_cols + i] + b[i]; }
#endif
/* ********************************************************************************************* */
#ifdef I3AL

	for(i = 0; i < n_unknowns; i++) {LAMBDA[i]=unknowns[i];}
#endif




