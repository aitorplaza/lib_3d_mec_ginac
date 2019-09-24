/* Solving Dynamics Forward */

#ifdef __EXTERNAL
 #include "external_def.h"
#endif


/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP
/* Correction for pos-vel */

#ifdef INV

	/* Correction pos */
	_Phi_q=Phi_q();
	_Phi=Phi();
    double Bufferd[Phi_q_n_cols];
	for (i = 0; i< iterations_NR ; i++){	Solve_N_R(Phi_q_n_rows, Phi_q_n_cols , _Phi, _Phi_q, q, _Inv_Phi_q,Bufferd);}

	/* Correction vel */

	if ( Phi_q_n_rows == dPhi_dq_n_rows ) {
		Mat_Vect_Mult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, dq, +1, AUX_V_dep_1);
	
		_Beta=Beta();
		for (i = 0; i < Phi_q_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}

		Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, _Inv_Phi_q, AUX_V_dep_1, 1, correction_dq);
		for (i = 0; i < Phi_q_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
	}
		else{
			_dPhi_dq =dPhi_dq();
			Mat_Vect_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, dq, +1, AUX_V_dep_1);

			_Beta=Beta();
			for (i = 0; i < dPhi_dq_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}
      double BufferJT[2*dPhi_dq_n_rows*dPhi_dq_n_cols];
      double BufferAUXCols[2*dPhi_dq_n_cols*dPhi_dq_n_cols];
      double BufferAUXRows[2*dPhi_dq_n_rows*dPhi_dq_n_rows];
      double BufferIAUXCols[2*dPhi_dq_n_cols*dPhi_dq_n_cols];
      double BufferIAUXRows[2*dPhi_dq_n_rows*dPhi_dq_n_rows];
			Mat_PInv(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, _Inv_dPhi_dq, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows); /* Avoid this if _Inv_Phi_q = _Inv_dPhi_dq */
			Mat_Vect_Mult(dPhi_dq_n_cols, dPhi_dq_n_rows, _Inv_dPhi_dq, AUX_V_dep_1, 1, correction_dq);
			for (i = 0; i < dPhi_dq_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
		}


#endif

#ifdef TRI

	double AUX_pos[ Phi_q_n_rows * Phi_q_n_rows ];
	double aux_pos[ Phi_q_n_rows ];
	double pinv_aux_pos[ Phi_q_n_cols ];

	double AUX_vel[ dPhi_dq_n_rows * dPhi_dq_n_rows ];
	double aux_vel[ dPhi_dq_n_rows ];
	double pinv_aux_vel[ dPhi_dq_n_cols ];

	/* Correction pos */
	_Phi_q=Phi_q();
	_Phi=Phi();

  double BufferL_LDL[Phi_q_n_rows*Phi_q_n_rows];
  double BufferU_LDL[Phi_q_n_rows*Phi_q_n_rows];
  double Bufferd_LDL[Phi_q_n_rows];
  double Buffery_LDL[Phi_q_n_rows];

for (i = 0; i< iterations_NR ; i++){

	Mat_Trasp(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, Trasp_Phi_q);
	Mat_Mat_Mult(Phi_q_n_rows, Phi_q_n_cols, Phi_q_n_rows, _Phi_q, Trasp_Phi_q, +1, AUX_pos);

	solve_lin_sys_ldl(Phi_q_n_rows, AUX_pos, _Phi, aux_pos, BufferL_LDL,BufferU_LDL,Bufferd_LDL,Buffery_LDL);

	Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, Trasp_Phi_q, aux_pos, +1, pinv_aux_pos);
	for (i = 0; i < n_gen_coord; i++){ q[i] = q[i] - pinv_aux_pos[i];	}
}

	/* Correction vel */


	if ( Phi_q_n_rows == dPhi_dq_n_rows ) {
		Mat_Vect_Mult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, dq, +1, AUX_V_dep_1);
		_Beta=Beta();

    double Buffer1L_LDL[Phi_q_n_rows*Phi_q_n_rows];
    double Buffer1U_LDL[Phi_q_n_rows*Phi_q_n_rows];
    double Buffer1d_LDL[Phi_q_n_rows];
    double Buffer1y_LDL[Phi_q_n_rows];

		for (i = 0; i < Phi_q_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}

		solve_lin_sys_ldl(Phi_q_n_rows, AUX_pos, AUX_V_dep_1, aux_pos, Buffer1L_LDL,Buffer1U_LDL,Buffer1d_LDL,Buffer1y_LDL);
		Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, Trasp_Phi_q, aux_pos, +1, pinv_aux_pos);
		for (i = 0; i < n_gen_coord; i++){ dq[i] = dq[i] + pinv_aux_pos[i];	}

	}
		else{

			_dPhi_dq =dPhi_dq();
			Mat_Vect_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, dq, +1, AUX_V_dep_1);
			_Beta=Beta();
      double Buffer2L_LDL[dPhi_dq_n_rows*dPhi_dq_n_rows];
      double Buffer2U_LDL[dPhi_dq_n_rows*dPhi_dq_n_rows];
      double Buffer2d_LDL[dPhi_dq_n_rows];
      double Buffer2y_LDL[dPhi_dq_n_rows];

			for (i = 0; i < dPhi_dq_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}

			solve_lin_sys_ldl(dPhi_dq_n_rows, AUX_vel, AUX_V_dep_1, aux_vel, Buffer2L_LDL,Buffer2U_LDL,Buffer2d_LDL,Buffer2y_LDL);

			double Trasp_dPhi_dq[ dPhi_dq_n_rows * dPhi_dq_n_cols ];
			Mat_Trasp(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, Trasp_dPhi_dq);
			Mat_Vect_Mult(dPhi_dq_n_cols, dPhi_dq_n_rows, Trasp_dPhi_dq, aux_vel, +1, pinv_aux_vel);
			for (i = 0; i < n_gen_coord; i++){ dq[i] = dq[i] + pinv_aux_vel[i];	}

		}

#endif

#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND

	_Phi_d=Phi_d();
	_Phi=Phi();

/* Correction pos */
#ifdef INV
double Bufferd[Phi_d_n_cols];
	for (i = 0; i< iterations_NR ; i++){	Solve_N_R(Phi_d_n_rows, Phi_d_n_cols , _Phi, _Phi_d, &q[Phi_z_n_cols], _Inv_Phi_d,Bufferd);}
	/*Solve_N_R_for(Phi_d_n_rows, &Phi, &Phi_d, &q[Phi_z_n_cols], iterations_NR, _Inv_Phi_d);*/
#endif

#ifdef TRI
	double aux_d[ Phi_d_n_cols ];
	for (i = 0; i< iterations_NR ; i++){
		/*	solve_lin_sys_lu(Phi_d_n_cols, _Phi_d, _Phi, aux_d);*/
		forward_substitution_piv(Phi_d_n_cols, LU, o, _Phi, y);
		backward_substitution_piv(Phi_d_n_cols, LU, o, y, aux_d);
		for (i = 0; i < Phi_d_n_cols; i++){ q[Phi_z_n_cols + i] = q[Phi_z_n_cols + i] - aux_d[i];	}
	}
#endif

/* Correction vel */
_Phi_z=Phi_z();
Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, _Phi_z, dq, +1, AUX_V_dep_1);

_Beta=Beta();
for (i = 0; i < Phi_d_n_cols; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}

#ifdef INV
	Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, AUX_V_dep_1, +1, &dq[Phi_z_n_cols]);
#endif

#ifdef TRI
	forward_substitution_piv(Phi_d_n_cols, LU, o, AUX_V_dep_1, y);
	backward_substitution_piv(Phi_d_n_cols, LU, o, y, &dq[Phi_z_n_cols]);
#endif



#endif
/* ********************************************************************************************* */
