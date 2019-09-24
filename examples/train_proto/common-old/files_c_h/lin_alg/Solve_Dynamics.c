/* Solving Dynamics Forward */

#ifndef INV
	#ifndef TRI
    #define INV
	#endif
#endif

/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP

#ifndef DDL
	#ifndef DDQ
		#define DDQ
	#endif
#endif

#ifdef DDL
_Qgamma=Qgamma();
_MXdPhi_dqZero=MXdPhi_dqZero();

	#ifdef INV
		Mat_Inv(MXdPhi_dqZero_n_cols ,_MXdPhi_dqZero, _INV_MX_aux);
		Mat_Vect_Mult(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols,_INV_MX_aux ,_Qgamma, +1,ddqunknowns );
	#endif

	#ifdef TRI
		solve_lin_sys_ldl(MXdPhi_dqZero_n_rows,_MXdPhi_dqZero , _Qgamma, ddqunknowns);
	#endif

for (i=0; i<n_gen_accel; i++){ ddq[i]=ddqunknowns[i]; }
for (i=0; i<n_unknowns ; i++){ unknowns[i]=ddqunknowns[n_gen_accel+i]; }
#endif

#ifdef DDQ
_Q=Q();
_M=M();

	#ifdef INV
		Mat_Inv(M_n_cols ,_M, _INV_M_aux);
		Mat_Vect_Mult(M_n_rows, M_n_cols,_INV_M_aux ,_Q, +1, aux_ddq1 );
		Phi_q();
		Mat_Trasp(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, Trasp_Phi_q);
		Mat_Mat_Mult(M_n_rows, M_n_cols, Phi_q_n_rows, _INV_M_aux , Trasp_Phi_q, +1, aux_Phi_q_T );
		Mat_Vect_Mult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q , aux_ddq1, +1, bb);
		Gamma();
		for (i=0; i<n_unknowns; i++){ bb[i]=bb[i]-_Gamma[i]; }
		Mat_Mat_Mult(Phi_q_n_rows, Phi_q_n_cols, Phi_q_n_rows, _Phi_q , aux_Phi_q_T, +1, AA);
		Mat_Inv(Phi_q_n_rows, AA, INV_AA);
		Mat_Vect_Mult(n_unknowns, n_unknowns, INV_AA , bb, +1, unknowns);
		Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, aux_Phi_q_T, unknowns, +1, aux_ddq2);
		for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; }
	#endif

	#ifdef TRI
		solve_lin_sys_ldl(M_n_rows,_M , _Q, aux_ddq1);
		Phi_q();
		Mat_Trasp(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, Trasp_Phi_q);
		solve_lin_sys_ldl_matrix(M_n_rows, _M , Phi_q_n_rows, Trasp_Phi_q, aux_Phi_q_T);
		Mat_Vect_Mult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q , aux_ddq1, +1, bb);
		Gamma();
		for (i=0; i<n_unknowns; i++){ bb[i]=bb[i]-_Gamma[i]; }
		Mat_Mat_Mult(Phi_q_n_rows, Phi_q_n_cols, Phi_q_n_rows, _Phi_q , aux_Phi_q_T, +1, AA);
		solve_lin_sys_ldl(n_unknowns, AA , bb, unknowns);
		Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, aux_Phi_q_T, unknowns, +1, aux_ddq2);
		for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; }
	#endif

#endif

#endif
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND
	/* Calculate A and b */
	Mat_Mat_Mult(Phi_d_n_cols, Phi_d_n_cols, Phi_z_n_cols, _Inv_Phi_d, _Phi_z, -1, A);
	for (j = 0; j < Phi_z_n_cols; j++){
		for(i = 0; i < Phi_d_n_cols; i++){AT[j + i * Phi_z_n_cols] = A[i + j * Phi_d_n_cols];}
	}
	_Gamma=Gamma();
	Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, _Gamma, +1, b);

	/* Calculate MZ */
	Mzd();
	Mat_Mat_Mult(Phi_z_n_cols, Phi_d_n_cols, Phi_z_n_cols, _Mzd, A, +1, AUX_M_indep_indep_1);
	Mdd();
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
		Mat_Inv( Phi_z_n_cols, _MZ, INV_MZ);
		Mat_Vect_Mult(Phi_z_n_cols, Phi_z_n_cols, INV_MZ, _QZ, +1, ddq);
	#endif

	#ifdef TRI
		solve_lin_sys_ldl(Phi_z_n_cols,_MZ , _QZ, ddq);
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

