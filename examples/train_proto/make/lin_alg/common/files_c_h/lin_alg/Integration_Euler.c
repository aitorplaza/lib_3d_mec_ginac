/* Step forward delta_t */
for(i = 0; i < n_gen_coord; i++){ q[i] = q[i] + ( dq[i] + 0.5 * ddq[i] * delta_t ) * delta_t;	}
for(i = 0; i < n_gen_coord; i++){	dq[i] = dq[i] + ddq[i] * delta_t;	}
