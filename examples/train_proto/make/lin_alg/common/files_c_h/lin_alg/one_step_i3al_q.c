/* ********************************************************************************************* */
#ifndef COORD_DEP
	#define COORD_DEP
#endif

#ifndef I3AL
	#define I3AL
#endif

#ifndef INV
	#ifndef TRI
    #define INV
	#endif
#endif

#ifndef ALFA
	#define ALFA 1.0e+12
#endif

#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "lin_alg.h"
#include "Declare_Variables.c"
/* ********************************************************************************************* */
void one_step_i3al_q (double delta_t, double * q, double *dq)
{

for(i = 0; i < n_gen_coord; i++){ qn[i]   =     q[i];	}
for(i = 0; i < n_gen_vel; i++)  {	dqn[i]  = -( dq[i] + 2.0 *  q[i] / delta_t);	}
for(i = 0; i < n_gen_vel; i++)  {	ddqn[i] = -(ddq[i] + 4.0 * dq[i] / delta_t + 4.0 * q[i] / pow(delta_t,2.0));	}

for(i = 0; i < n_gen_coord; i++){ q[i]   =   qn[i] + dq[i]*delta_t + ddq[i]*pow(delta_t,2.0)/2.0;}
for(i = 0; i < n_gen_vel; i++)  {	dq[i]  =  dqn[i] + 2.0 * q[i] / delta_t;	}
for(i = 0; i < n_gen_vel; i++)  {	ddq[i] = ddqn[i] + 4.0 * q[i] / pow(delta_t,2.0);	} 

sum_error_pos = 0.0;
for(i = 0; i < n_gen_coord; i++){	sum_error_pos +=( (q[i] - qn[i]) * (q[i] - qn[i]) ); }
error = pow(sum_error_pos,0.5);
iter=0;
/* *********************** */
M();
Mat_Vect_Mult(n_gen_accel, n_gen_accel, _M, ddq, +1.0, AUX_V_ddq_1);
Phi();
for(i = 0; i < n_unknowns; i++) {AUX_V_unk_1[i] = LAMBDA[i] + alfa * _Phi[i];}
Phi_q();
Mat_Trasp(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, Trasp_Phi_q);
Mat_Vect_Mult(n_gen_coord, n_unknowns, Trasp_Phi_q , AUX_V_unk_1, +1.0, AUX_V_ddq_2);
Q();
for(i = 0; i < n_gen_accel; i++) {fq[i] = (pow(delta_t,2.0)/4.0)*(AUX_V_ddq_1[i] + AUX_V_ddq_2[i] - _Q[i]);}

Q_dq();
Q_q();
Mat_Mat_Mult( Phi_q_n_cols, Phi_q_n_rows, Phi_q_n_cols, Trasp_Phi_q, _Phi_q, +1.0, AUX_M_ddq_1);
for(i = 0; i < n_gen_accel; i++) {
	for(j = 0; j < n_gen_accel; j++) {
		AUX_fq_q[ i + j*n_gen_accel ] = _M[ i + j*n_gen_accel ] - (delta_t/2.0)*_Q_dq[ i + j*n_gen_accel ] - (pow(delta_t,2.0)/4.0)*_Q_q[ i + j*n_gen_accel ];
		fq_q[ i + j*n_gen_accel ] = AUX_fq_q[ i + j*n_gen_accel ] + (pow(delta_t,2.0)/4.0)*alfa*AUX_M_ddq_1[ i + j*n_gen_accel ];
	}
}


/* *********************** */
#ifndef TRAPEZOIDAL_TOLERANCE
	#define TRAPEZOIDAL_TOLERANCE 1.0e-8
#endif
while (error > TRAPEZOIDAL_TOLERANCE){
/* *********************** */

	#ifdef INV
		Mat_Inv( n_gen_coord, fq_q, INV_fq_q);
		Mat_Vect_Mult(n_gen_coord, n_gen_coord, INV_fq_q, fq, -1.0, delta_q);
	#endif

	#ifdef TRI
		solve_lin_sys_ldl(n_gen_coord, fq_q, fq, delta_q);
		for(i = 0; i < n_gen_coord; i++) {delta_q[i]=-delta_q[i];}
	#endif



	for(i = 0; i < n_gen_coord; i++){ q[i]   =    q[i] + delta_q[i];}
	for(i = 0; i < n_gen_vel; i++)  {	dq[i]  =  dqn[i] + (2.0 * q[i] / delta_t);	}
	for(i = 0; i < n_gen_vel; i++)  {	ddq[i] = ddqn[i] + (4.0 * q[i] / (pow(delta_t,2.0)));	} 
	Phi();
	for(i = 0; i < n_unknowns; i++) {	LAMBDA[i] = LAMBDA[i] + alfa * _Phi[i];	} 

	sum_error_pos = 0.0;
	for(i = 0; i < n_gen_coord; i++){ sum_error_pos += (delta_q[i] * delta_q[i]); }
	error = 0.0;	error = pow(sum_error_pos,0.5);
	iter++;
/* *********************** */
	M();
	Mat_Vect_Mult(n_gen_accel, n_gen_accel, _M, ddq, +1.0, AUX_V_ddq_1);
	Phi();
	for(i = 0; i < n_unknowns; i++) {	AUX_V_unk_1[i] = LAMBDA[i] + alfa * _Phi[i];	}
	Phi_q();
	Mat_Trasp(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, Trasp_Phi_q);
	Mat_Vect_Mult(n_gen_coord, n_unknowns, Trasp_Phi_q , AUX_V_unk_1, +1.0, AUX_V_ddq_2);
	Q();
	for(i = 0; i < n_gen_accel; i++) {fq[i] = (pow(delta_t,2.0)/4.0)*(AUX_V_ddq_1[i] + AUX_V_ddq_2[i] - _Q[i]);} 
	Q_dq();
	Q_q();
	Mat_Mat_Mult( Phi_q_n_cols, Phi_q_n_rows, Phi_q_n_cols, Trasp_Phi_q, _Phi_q, +1.0, AUX_M_ddq_1);
	for(i = 0; i < n_gen_accel; i++) {
		for(j = 0; j < n_gen_accel; j++) {
			AUX_fq_q[ i + j*n_gen_accel ] = _M[ i + j*n_gen_accel ] - (delta_t/2.0)*_Q_dq[ i + j*n_gen_accel ] - (pow(delta_t,2.0)/4.0)*_Q_q[ i + j*n_gen_accel ];
			fq_q[ i + j*n_gen_accel ] = AUX_fq_q[ i + j*n_gen_accel ] + (pow(delta_t,2.0)/4.0)*alfa*AUX_M_ddq_1[ i + j*n_gen_accel ];
		}
	}
}

/* *********************** */
/* Correction for vel-accel */
Mat_Vect_Mult(n_gen_vel, n_gen_vel, AUX_fq_q, dq, +1.0, AUX_V_dq_1);
Beta();
Phi_q();
Mat_Trasp(Phi_q_n_rows, Phi_q_n_cols, _Phi_q, Trasp_Phi_q);
Mat_Vect_Mult(n_gen_coord, n_unknowns, Trasp_Phi_q , _Beta, +1.0, AUX_V_dq_2);
for(i = 0; i < n_gen_vel; i++) {	project_dq[i] = (AUX_V_dq_1[i] + (pow(delta_t,2.0)/4.0)*alfa*AUX_V_dq_2[i]);	} 

Mat_Vect_Mult(n_gen_accel, n_gen_accel, AUX_fq_q, ddq, +1.0, AUX_V_ddq_1);
Gamma();
Mat_Vect_Mult(n_gen_coord, n_unknowns, Trasp_Phi_q , _Gamma, +1.0, AUX_V_ddq_2);
for(i = 0; i < n_gen_accel; i++) {	project_ddq[i] = (AUX_V_ddq_1[i] + (pow(delta_t,2.0)/4.0)*alfa*AUX_V_ddq_2[i]);	} 

#ifdef INV
	Mat_Inv( n_gen_coord, fq_q, INV_fq_q);
	Mat_Vect_Mult(n_gen_vel, n_gen_vel, INV_fq_q, project_dq, +1.0, dq);
	Mat_Vect_Mult(n_gen_accel, n_gen_accel, INV_fq_q, project_ddq, +1.0, ddq);
#endif

#ifdef TRI
	solve_lin_sys_ldl(n_gen_vel, fq_q, project_dq, dq);
	solve_lin_sys_ldl(n_gen_accel, fq_q, project_ddq, ddq);
#endif

}
