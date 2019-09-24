/* Solving Dynamics Forward */

#ifdef __EXTERNAL
 #include "external_def.h"
#endif

/* ********************************************************************************************* */
/*Common for coord q and z */

_Phi=Phi();
_Phi_q=Phi_q();
_dPhi_dq=dPhi_dq();

/* Coord q */
#ifdef COORD_DEP
/* Correction for pos-vel */
#ifdef INV
  /* Correction pos */

  for (i = 0; i< iterations_NR ; i++){	
  Solve_N_R(Phi_q_n_rows, Phi_q_n_cols , _Phi, _Phi_q, q, _Inv_Phi_q, Bufferd, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, p_vector, q_vector, BufferL, BufferPINV); /* q = q - Pinv(Phi_q)*Phi */
  }

  /* Correction vel */

  if ( Phi_q_n_rows == dPhi_dq_n_rows ) {
    Mat_Vect_Mult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, dq, +1, AUX_V_dep_1);
    _Beta=Beta();
    for (i = 0; i < Phi_q_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	} 
    Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, _Inv_Phi_q, AUX_V_dep_1, 1, correction_dq);
    for (i = 0; i < Phi_q_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	} 
  }
  else {
    Mat_Vect_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, dq, +1, AUX_V_dep_1);
    _Beta=Beta();
    for (i = 0; i < dPhi_dq_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	} /* AUX_V_dep_1 = Beta - dPhi_dq*dq */
    Mat_PInv(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, _Inv_dPhi_dq, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows,Buffer); 
    Mat_Vect_Mult(dPhi_dq_n_cols, dPhi_dq_n_rows, _Inv_dPhi_dq, AUX_V_dep_1, 1, correction_dq);
    for (i = 0; i < dPhi_dq_n_cols; i++){ dq[i] = dq[i] + correction_dq[i];	} /* dq = dq + Pinv(dPhi_dq)*(Beta - dPhi_dq*dq) */
  }


#endif

//#ifdef TRI
 #if defined TRI_LDL || defined TRI_LU || defined TRI

  /* Correction pos */

  for (i = 0; i< iterations_NR ; i++){
    Mat_Self_MultT_SO(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, +1, AUX_pos);
    solve_lin_sys_ldl(Phi_q_n_rows, AUX_pos, _Phi, aux_pos, BufferL_LDL,BufferU_LDL,Bufferd_LDL,Buffery_LDL);
    Mat_Vect_TMult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, aux_pos, +1, pinv_aux_pos);
    for (i = 0; i < n_gen_coord; i++){ q[i] = q[i] - pinv_aux_pos[i];	}
  }

  /* Correction vel */

  if ( Phi_q_n_rows == dPhi_dq_n_rows ) { 
    Mat_Vect_Mult(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, dq, +1, AUX_V_dep_1);
    _Beta=Beta();
    for (i = 0; i < Phi_q_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}
    solve_lin_sys_ldl(Phi_q_n_rows, AUX_pos, AUX_V_dep_1, aux_pos, BufferL_LDL,BufferU_LDL,Bufferd_LDL,Buffery_LDL);
    Mat_Vect_Mult(Phi_q_n_cols, Phi_q_n_rows, Trasp_Phi_q, aux_pos, +1, pinv_aux_pos);
    for (i = 0; i < n_gen_coord; i++){ dq[i] = dq[i] + pinv_aux_pos[i];	}
  }
  else{
    Mat_Vect_Mult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, dq, +1, AUX_V_dep_1);
    _Beta=Beta();
    for (i = 0; i < dPhi_dq_n_rows; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}
    Mat_Self_MultT_SO(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, +1, AUX_vel);
    solve_lin_sys_ldl(dPhi_dq_n_rows, AUX_vel, AUX_V_dep_1, aux_vel, BufferL_LDL,BufferU_LDL,Bufferd_LDL,Buffery_LDL);
    Mat_Vect_TMult(dPhi_dq_n_rows, dPhi_dq_n_cols, _dPhi_dq, aux_vel, +1, pinv_aux_vel);
    for (i = 0; i < n_gen_coord; i++){ dq[i] = dq[i] + pinv_aux_vel[i];	}
  }

#endif

#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND
  lufp4(dPhi_dq_n_rows,Phi_q_n_rows, dPhi_dq_n_cols, _dPhi_dq, p_vector, perm_vel);/*for coordinate partitioning*/

  /* Correction pos -> C.2 Equation DSM*/
  for (i = 0; i< iterations_NR ; i++){
    forward_substitution_LUpq_pq_x(dPhi_dq_n_rows,Phi_q_n_rows, _dPhi_dq, p_vector, perm_vel, _Phi, y);
    backward_substitution_LUpq_pq_x(dPhi_dq_n_rows,Phi_q_n_rows, _dPhi_dq, p_vector, perm_vel, y, aux_dq_dep);
  for (i = 0; i < Phi_n_rows; i++){ q[perm_vel[i]] = q[perm_vel[i]] - aux_dq_dep[i];	}	
  }

  /* Correction vel -> C.3 Equation DSM*/
  for (i = 0; i< n_vel_indep ; i++){
    backward_substitution_LUpq_pq_A(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector, perm_vel, &_dPhi_dq[perm_vel[i+n_vel_dep] * dPhi_dq_n_rows ], &A[ i * dPhi_dq_n_rows ]); /* Calculate A with this dedicated backward */
  }
  _Beta=Beta();
  forward_substitution_LUpq_pq_x(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector,perm_vel, _Beta , y);
  backward_substitution_LUpq_pq_x(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector,perm_vel, y, AUX_V_dep_1 );
  for (i=0; i< dPhi_dq_n_rows; i++){
    AUX_V_dep_2[i] = 0.0;
    for (j=0; j<n_vel_indep; j++){
      AUX_V_dep_2[i] =  AUX_V_dep_2[i] + A[i+j*dPhi_dq_n_rows] * dq[perm_vel[j+n_vel_dep]];
    }
  }

  for (i = 0; i < dPhi_dq_n_rows; i++){ dq[perm_vel[i]]= AUX_V_dep_2[i] - AUX_V_dep_1[i] ;	}

#endif
/* ********************************************************************************************* */
