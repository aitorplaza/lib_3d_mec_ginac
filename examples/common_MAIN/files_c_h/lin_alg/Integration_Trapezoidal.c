/* Step forward delta_t */

memcpy(tqn,   q,   n_gen_coord*sizeof(double));
memcpy(tdqn,  dq,  n_gen_vel*sizeof(double));
memcpy(tddqn, ddq, n_gen_accel*sizeof(double));

for(i = 0; i < n_gen_coord; i++){
  /* q[i] = tqn[i] + tdqn[i] * delta_t; /* Euler */
  q[i] = tqn[i] + ( tdqn[i] + 0.5 * tddqn[i] * delta_t ) * delta_t; /* Euler Improved */
  delta_q[i] = q[i] - tqn[i];
  sum_error_pos +=(delta_q[i] * delta_q[i]);
}

for(i = 0; i < n_gen_vel; i++){
  dq[i] = tdqn[i] + tddqn[i] * delta_t; /* Euler = Euler Improved */
  delta_dq[i] = dq[i] - tdqn[i];
  sum_error_vel +=(delta_dq[i] * delta_dq[i]);
}

error = pow(sum_error_pos,0.5) + pow(sum_error_vel,0.5);
ti=0;

#ifndef TRAPEZOIDAL_TOLERANCE
  #define TRAPEZOIDAL_TOLERANCE 1.0e-8
#endif

while (error > TRAPEZOIDAL_TOLERANCE){
        
/*
#ifdef COORD_IND
 lufp4(dPhi_dq_n_rows,Phi_q_n_rows, dPhi_dq_n_cols, _dPhi_dq, p_vector, perm_vel);
	for (i = 0; i< n_vel_indep ; i++){
	backward_substitution_LUpq_pq_A(dPhi_dq_n_rows,dPhi_dq_n_rows, _dPhi_dq, p_vector, perm_vel, &_dPhi_dq[perm_vel[i+n_vel_dep] * dPhi_dq_n_rows ], &A[ i * dPhi_dq_n_rows ]);
	}
#endif
*/

  #include "Solve_Dynamics.c"

/*
#ifdef COORD_IND
_dPhi_dq=dPhi_dq();
#endif
*/

  memcpy(tqn1,   q,   n_gen_coord*sizeof(double));
  memcpy(tdqn1,  dq,  n_gen_vel*sizeof(double));
  memcpy(tddqn1, ddq, n_gen_accel*sizeof(double));

  sum_error_pos = 0.0;
  for(i = 0; i < n_gen_coord; i++){
    q[i] = tqn[i] + 0.5 * delta_t * ( tdqn[i]  +  tdqn1[i] );
    delta_q[i] = q[i] - tqn1[i];
    sum_error_pos += (delta_q[i] * delta_q[i]);
  }

  sum_error_vel = 0.0;
  for(i = 0; i < n_gen_vel; i++){
      dq[i] = tdqn[i] + 0.5 * delta_t * ( tddqn[i]  +  tddqn1[i] );
    delta_dq[i] = dq[i] - tdqn1[i];
    sum_error_vel += (delta_dq[i] * delta_dq[i]);
  }
  error = 0.0;
  error = pow(sum_error_pos,0.5) + pow(sum_error_vel,0.5);
  ti++;
}

