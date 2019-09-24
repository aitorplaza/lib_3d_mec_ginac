/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP
/* Correction for pos-vel */

/* Correction pos */
_Phi_q=Phi_q();
_Phi=Phi();
for (i = 0; i< iterations_NR ; i++){	Solve_N_R(Phi_q_n_rows, Phi_q_n_cols , _Phi, _Phi_q, q, _Inv_Phi_q);}

/* Correction vel */
_dPhi_dq =dPhi_dq();
Mat_Vect_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, dq, +1, AUX_V_dep_1);

_Beta=Beta();
for (i = 0; i < dPhi_dq_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}

if ( Phi_q_n_rows == dPhi_dq_n_rows ) {
		Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, _Inv_Phi_q, AUX_V_dep_1, 1, correction_dq);
		for (i = 0; i < Phi_q_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
}
	else{
		Mat_PInv(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, _Inv_dPhi_dq); /* Avoid this if _Inv_Phi_q = _Inv_dPhi_dq */
		Mat_Vect_Mult(dPhi_dq_n_cols, dPhi_dq_n_rows, _Inv_dPhi_dq, AUX_V_dep_1, 1, correction_dq);
		for (i = 0; i < dPhi_dq_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	}
	}
#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND
/* Correction for pos-vel */

/* Correction pos */
_Phi_d=Phi_d();
_Phi=Phi();
for (i = 0; i< iterations_NR ; i++){	Solve_N_R(Phi_d_n_rows, Phi_d_n_cols , _Phi, _Phi_d, &q[Phi_z_n_cols], _Inv_Phi_d);}
//Solve_N_R_for(Phi_d_n_rows, &Phi, &Phi_d, &q[Phi_z_n_cols], iterations_NR, _Inv_Phi_d);

/* Correction vel */
_Phi_z=Phi_z();
Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, _Phi_z, dq, +1, AUX_V_dep_1);

_Beta=Beta();
for (i = 0; i < Phi_d_n_cols; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}

Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, AUX_V_dep_1, +1, &dq[Phi_z_n_cols]);
#endif
/* ********************************************************************************************* */
