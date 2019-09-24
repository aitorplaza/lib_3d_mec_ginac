/* ********************************************************************************************* */
#ifndef COORD_IND
	#define COORD_IND
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
void one_step_i3al_z (double delta_t, double * q, double *dq)
{

for(i = 0; i < n_gen_coord; i++){ qn[i]   =     q[i];	}
for(i = 0; i < n_gen_vel; i++)  {	dqn[i]  = -( dq[i] + 2 *  q[i] / delta_t);	}
for(i = 0; i < n_gen_vel; i++)  {	ddqn[i] = -(ddq[i] + 4 * dq[i] / delta_t + 4 * q[i] / pow(delta_t,2.0));	}

for(i = 0; i < n_gen_coord; i++){ q[i]   =   qn[i] + dq[i]*delta_t + ddq[i]*pow(delta_t,2.0)/2;}
for(i = 0; i < n_gen_vel; i++)  {	dq[i]  =  dqn[i] + 2 * q[i] / delta_t;	}
for(i = 0; i < n_gen_vel; i++)  {	ddq[i] = ddqn[i] + 4 * q[i] / pow(delta_t,2.0);	} 

sum_error_pos = 0.0;
for(i = 0; i < n_gen_coord; i++){	sum_error_pos +=( (q[i] - qn[i]) * (q[i] - qn[i]) ); }
error = pow(sum_error_pos,0.5);
iter=0;

for(i = 0; i < n_coord_indep; i++){ zn[i]   = qn[i]; }
for(i = 0; i < n_vel_indep; i++)  {	dzn[i]  = dqn[i]; }
for(i = 0; i < n_accel_indep; i++){	ddzn[i] = ddqn[i]; }

for(i = 0; i < n_coord_indep; i++){ z[i]   = q[i]; }
for(i = 0; i < n_vel_indep; i++)  {	dz[i]  = dq[i]; }
for(i = 0; i < n_accel_indep; i++){	ddz[i] = ddq[i]; }

/* *********************** */
Phi_d();
Mat_Inv(Phi_d_n_cols, _Phi_d, _Inv_Phi_d);
Mat_Mat_Mult(Phi_d_n_cols, Phi_d_n_cols, Phi_z_n_cols, _Inv_Phi_d, _Phi_z, -1, A);
_Gamma=Gamma();
Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, _Gamma, +1, b);
_Beta=Beta();
Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, _Beta, +1, e);
/* *********************** */
Mzd();
Mat_Mat_Mult(Mzd_n_rows, Mzd_n_cols, Phi_z_n_cols, _Mzd, A, +1, _M_aux);
Mzz();
for(i = 0; i < (Mzz_n_rows * Mzz_n_cols); i++) {_M_aux[i]=_M_aux[i]+_Mzz[i];}
Mat_Vect_Mult(Mzz_n_rows, Mzz_n_cols, _M_aux, ddq, +1, AUX_V_ddz_1);
Mat_Vect_Mult(Mzd_n_rows, Mzd_n_cols, _Mzd, b, +1, AUX_V_ddz_3);

Phi();
for(i = 0; i < n_unknowns; i++) {AUX_V_unk_1[i] = LAMBDA[i] + alfa * _Phi[i];}
Phi_z();
Mat_Trasp(Phi_z_n_rows, Phi_z_n_cols, _Phi_z, Trasp_Phi_z);
Mat_Vect_Mult(n_coord_indep, n_unknowns, Trasp_Phi_z , AUX_V_unk_1, +1, AUX_V_ddz_2);

Qz();
for(i = 0; i < n_accel_indep; i++) {fz[i] = (pow(delta_t,2.0)/4)*(AUX_V_ddz_1[i] + AUX_V_ddz_2[i] + AUX_V_ddz_3[i] - _Qz[i]);}

Qz_dz();
Qz_z();
Mat_Mat_Mult( Phi_z_n_cols, Phi_z_n_rows, Phi_z_n_cols, Trasp_Phi_z, _Phi_z, +1, AUX_M_ddz_1);
for(i = 0; i < n_accel_indep; i++) {
	for(j = 0; j < n_accel_indep; j++) {
		AUX_fz_z[ i + j*n_accel_indep ] = _M_aux[ i + j*n_accel_indep ] - (delta_t/2)*_Qz_dz[ i + j*n_accel_indep ] - (pow(delta_t,2.0)/4)*_Qz_z[ i + j*n_accel_indep ];
		fz_z[ i + j*n_accel_indep ] = AUX_fz_z[ i + j*n_accel_indep ] + (pow(delta_t,2.0)/4)*alfa*AUX_M_ddz_1[ i + j*n_accel_indep ];
	}
}
/* *********************** */
#ifndef TRAPEZOIDAL_TOLERANCE
	#define TRAPEZOIDAL_TOLERANCE 1.0e-8
#endif
while (error > TRAPEZOIDAL_TOLERANCE){

	#ifdef INV
		Mat_Inv( n_accel_indep, fz_z, INV_fz_z);
		Mat_Vect_Mult(n_coord_indep, n_coord_indep, INV_fz_z, fz, -1, delta_z);
	#endif

	#ifdef TRI
		solve_lin_sys_ldl(n_coord_indep, fz_z, fz, delta_z);
		for(i = 0; i < n_coord_indep; i++) {delta_z[i]=-delta_z[i];}
	#endif

	for(i = 0; i < n_coord_indep; i++){ z[i]   =   z[i] + delta_z[i];	q[i]=z[i];}

	for(i = 0; i < n_vel_indep; i++)  {	dq[i]  =  dzn[i] + 2 * z[i] / delta_t;	}

	Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, A, dq, +1, AUX_V_dd_1);
	for(i = 0; i < n_vel_dep; i++)  {	dq[n_vel_indep + i] = AUX_V_dd_1[i] + e[i];	} 
	for(i = 0; i < n_accel_indep; i++)  {	ddq[i] = ddzn[i] + (4.0 * z[i] / (pow(delta_t,2.0)));	}

	Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, A, ddq, +1, AUX_V_ddd_1);
	for(i = 0; i < n_accel_dep; i++)  {	ddq[n_accel_indep + i] = AUX_V_ddd_1[i] + b[i];	} 
	for(i = 0; i < n_unknowns; i++) {	LAMBDA[i] = LAMBDA[i] + alfa * _Phi[i];	} 

	sum_error_pos = 0.0;
	for(i = 0; i < n_coord_indep; i++){ sum_error_pos += (delta_z[i] * delta_z[i]); }
	error = 0.0;	error = pow(sum_error_pos,0.5);
	iter++;

	/* *********************** */
	Phi_d();
	Mat_Inv(Phi_d_n_cols, _Phi_d, _Inv_Phi_d);
	Mat_Mat_Mult(Phi_d_n_cols, Phi_d_n_cols, Phi_z_n_cols, _Inv_Phi_d, _Phi_z, -1, A);
	_Gamma=Gamma();
	Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, _Gamma, +1, b);
	_Beta=Beta();
	Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, _Beta, +1, e);
	/* *********************** */
	Mzd();
	Mat_Mat_Mult(Mzd_n_rows, Mzd_n_cols, Phi_z_n_cols, _Mzd, A, +1, _M_aux);
	Mzz();
	for(i = 0; i < (Mzz_n_rows * Mzz_n_cols); i++) {_M_aux[i]=_M_aux[i]+_Mzz[i];}
	Mat_Vect_Mult(Mzz_n_rows, Mzz_n_cols, _M_aux, ddq, +1, AUX_V_ddz_1);
	Mat_Vect_Mult(Mzd_n_rows, Mzd_n_cols, _Mzd, b, +1, AUX_V_ddz_3);

	Phi();
	for(i = 0; i < n_unknowns; i++) {AUX_V_unk_1[i] = LAMBDA[i] + alfa * _Phi[i];}
	Phi_z();
	Mat_Trasp(Phi_z_n_rows, Phi_z_n_cols, _Phi_z, Trasp_Phi_z);
	Mat_Vect_Mult(n_coord_indep, n_unknowns, Trasp_Phi_z , AUX_V_unk_1, +1, AUX_V_ddz_2);

	Qz();
	for(i = 0; i < n_accel_indep; i++) {fz[i] = (pow(delta_t,2.0)/4)*(AUX_V_ddz_1[i] + AUX_V_ddz_2[i] + AUX_V_ddz_3[i] - _Qz[i]);}

	Qz_dz();
	Qz_z();
	Mat_Mat_Mult( Phi_z_n_cols, Phi_z_n_rows, Phi_z_n_cols, Trasp_Phi_z, _Phi_z, +1, AUX_M_ddz_1);
	for(i = 0; i < n_accel_indep; i++) {
		for(j = 0; j < n_accel_indep; j++) {
			AUX_fz_z[ i + j*n_accel_indep ] = _M_aux[ i + j*n_accel_indep ] - (delta_t/2)*_Qz_dz[ i + j*n_accel_indep ] - (pow(delta_t,2.0)/4)*_Qz_z[ i + j*n_accel_indep ];
			fz_z[ i + j*n_accel_indep ] = AUX_fz_z[ i + j*n_accel_indep ] + (pow(delta_t,2.0)/4)*alfa*AUX_M_ddz_1[ i + j*n_accel_indep ];
		}
	}
}
/* *********************** */
/* Correction for vel-accel */
Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, A, dq, +1, AUX_V_dd_1);
for(i = 0; i < n_vel_dep; i++)  {	dq[n_vel_indep + i] = AUX_V_dd_1[i] + e[i];	} 

Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, A, ddq, +1, AUX_V_ddd_1);
for(i = 0; i < n_accel_dep; i++)  {	ddq[n_accel_indep + i] = AUX_V_ddd_1[i] + b[i];	} 

}
