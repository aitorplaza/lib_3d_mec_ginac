/* Step forward delta_t */

memcpy(qn,   q,   n_gen_coord*sizeof(double));
memcpy(dqn,  dq,  n_gen_vel*sizeof(double));
memcpy(ddqn, ddq, n_gen_accel*sizeof(double));

for(i = 0; i < n_gen_coord; i++){
	/* q[i] = qn[i] + dqn[i] * delta_t; /* Euler */
	q[i] = qn[i] + ( dqn[i] + 0.5 * ddqn[i] * delta_t ) * delta_t; /* Euler Mejorado */
	delta_q[i] = q[i] - qn[i];
	sum_error_pos +=(delta_q[i] * delta_q[i]);
}

for(i = 0; i < n_gen_vel; i++){
	dq[i] = dqn[i] + ddqn[i] * delta_t; /* Euler = Euler Mejorado */
	delta_dq[i] = dq[i] - dqn[i];
	sum_error_vel +=(delta_dq[i] * delta_dq[i]);
}

error = pow(sum_error_pos,0.5) + pow(sum_error_vel,0.5);
iter=0;

#ifndef TRAPEZOIDAL_TOLERANCE
	#define TRAPEZOIDAL_TOLERANCE 1.0e-8
#endif

while (error > TRAPEZOIDAL_TOLERANCE){

	#include "Solve_Dynamics.c"

	memcpy(qn1,   q,   n_gen_coord*sizeof(double));
	memcpy(dqn1,  dq,  n_gen_vel*sizeof(double));
	memcpy(ddqn1, ddq, n_gen_accel*sizeof(double));

	sum_error_pos = 0.0;
	for(i = 0; i < n_gen_coord; i++){
		q[i] = qn[i] + 0.5 * delta_t * ( dqn[i]  +  dqn1[i] );
		delta_q[i] = q[i] - qn1[i];
		sum_error_pos += (delta_q[i] * delta_q[i]);
		}

	sum_error_vel = 0.0;
	for(i = 0; i < n_gen_vel; i++){
		dq[i] = dqn[i] + 0.5 * delta_t * ( ddqn[i]  +  ddqn1[i] );
		delta_dq[i] = dq[i] - dqn1[i];
		sum_error_vel += (delta_dq[i] * delta_dq[i]);
	}

	error = 0.0;
	error = pow(sum_error_pos,0.5) + pow(sum_error_vel,0.5);
	iter++;

}

