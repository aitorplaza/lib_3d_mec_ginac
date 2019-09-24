/* ********************************************************************************************* */
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"
#include "one_step.h"
#include "lin_alg.h"
#include "Declare_Variables.h"
#include "timestamp.c"

#include "Phi.h"
#include "Beta.h"
#include "Phi_q.h"
#include "PhiInit_q.h"
#include "Phi_z.h"
#include "Phi_d.h"

#include "Q.h"
#include "Qz.h"
#include "Qd.h"
#include "Qgamma.h"
#include "Gamma.h"

#include "MXdPhi_dqZero.h"
#include "M.h"

#include "Q_q.h"
#include "Q_dq.h"

#include "Qz_z.h"
#include "Qd_d.h"
#include "Qz_dz.h"
#include "Qd_dd.h"

#include "Mzz.h"
#include "Mzd.h"
#include "Mdd.h"
/* ********************************************************************************************* */

int main (int argc, char *argv[]) {

#include "arguments.c"
printf("t = %g, steps %ld ",t,steps);
#include "Init_variables_parameters.c"
#include "Init_functions.c"
//Initial_position_velocity(q,dq);
/* ********************************************************************************************* */
/*
Vect_Print	(n_gen_coord, q);
Vect_Print	(n_gen_vel, dq);
Vect_Print	(n_gen_accel, ddq);
*/
#ifdef COORD_DEP
//	Initial_position_velocity_q(q,dq);
#endif
#ifdef COORD_IND
//	Initial_position_velocity_z(q,dq);
#endif
#ifdef COORD_IND
#include "one_step.h"
//extern double	_Inv_Phi_d[Phi_n_rows * Phi_n_rows] ;
double	AUX_V_dep_1[Phi_d_n_cols];
int i;
printf("hola Z\n");

Phi();
Phi_d();
Solve_N_R_while(Phi_d_n_cols, &Phi, &Phi_d, &q[Phi_z_n_cols], _Inv_Phi_d);


Phi_z();
Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, _Phi_z, dq, +1, AUX_V_dep_1);
Beta();		for (i = 0; i < Phi_d_n_cols; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}
Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, AUX_V_dep_1, +1, &dq[Phi_z_n_cols]);

#endif


#include "Solve_Dynamics.c"
/*
Vect_Print	(n_gen_coord, q);
Vect_Print	(n_gen_vel, dq);
Vect_Print	(n_gen_accel, ddq);

Phi();
printf("Phi\n");
Vect_Print	(Phi_n_rows, _Phi);

Beta();
printf("Beta\n");
Vect_Print	(Beta_n_rows, _Beta);

Phi_q();
printf("Phi_q\n");
Mat_Print	(Phi_q_n_rows, Phi_q_n_cols, _Phi_q);
*/

PhiInit_q();
printf("PhiInit_q\n");
Mat_Print	(PhiInit_q_n_rows, PhiInit_q_n_cols, _PhiInit_q);

/*
Q();
printf("Q\n");
Vect_Print	(Q_n_rows, _Q);

Phi_z();
printf("Phi_z\n");
Mat_Print	(Phi_z_n_rows, Phi_z_n_cols, _Phi_z);
Phi_d();
printf("Phi_d\n");
Mat_Print	(Phi_d_n_rows, Phi_d_n_cols, _Phi_d);
Qz();
printf("Qz\n");
Vect_Print	(Qz_n_rows, _Qz);
Qd();
printf("Qd\n");
Vect_Print	(Qd_n_rows, _Qd);

Qgamma();
printf("Qgamma\n");
Vect_Print	(Qgamma_n_rows, _Qgamma);

MXdPhi_dqZero();
printf("MXdPhi_dqZero\n");
Mat_Print	(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols, _MXdPhi_dqZero);
*/

Q_q();
printf("Q_q\n");
Mat_Print	(Q_q_n_rows, Q_q_n_cols, _Q_q);

/*
Q_dq();
printf("Q_dq\n");
Mat_Print	(Q_dq_n_rows, Q_dq_n_cols, _Q_dq);

Qz_z();
printf("Qz_z\n");
Mat_Print	(Qz_z_n_rows, Qz_z_n_cols, _Qz_z);
Qd_d();
printf("Qd_d\n");
Mat_Print	(Qd_d_n_rows, Qd_d_n_cols, _Qd_d);
Qz_dz();
printf("Qz_dz\n");
Mat_Print	(Qz_dz_n_rows, Qz_dz_n_cols, _Qz_dz);
Qd_dd();
printf("Qd_dd\n");
Mat_Print	(Qd_dd_n_rows, Qd_dd_n_cols, _Qd_dd);
*/
/* ********************************************************************************************* */
#ifdef TIME_ON
  start = timestamp();
#endif
#ifndef TIME_ON
  FILE * data_file = fopen(output_file_name, "w");
  write_data_file_header(data_file);
  write_data_file(data_file);
#endif
/* ********************************************************************************************* */
/* integration */	/* Solving for t > 0 */
/*
for (k=1; k<=steps; k++){

#ifdef COORD_DEP
	#ifdef EULER
		one_step_euler_q(delta_t,q,dq);
	#endif
	#ifdef TRAPEZOIDAL
		one_step_trapezoidal_q(delta_t,q,dq);
	#endif
	#ifdef I3AL
printf("hola1 %.10f\n",TRAPEZOIDAL_TOLERANCE );
		one_step_i3al_q(delta_t,q,dq);
printf("hola3\n");
	#endif
#endif

#ifdef COORD_IND
	#ifdef EULER
		one_step_euler_z(delta_t,q,dq);
	#endif
	#ifdef TRAPEZOIDAL
		one_step_trapezoidal_z(delta_t,q,dq);
	#endif
#endif

#ifndef TIME_ON
  t=t+delta_t;
  write_data_file(data_file);
#endif

}
*/
/* ********************************************************************************************* */
#ifdef TIME_ON
  end = timestamp();
  printf("%s calculation time: %.9f secs\n",output_file_name,(end - start) / ((double) n_iterations));
#endif
#ifndef TIME_ON
  fclose(data_file);
  printf("ieup_%s\n",output_file_name);
#endif
/* ********************************************************************************************* */
#include "Done_variables_parameters.c"
#include "Done_functions.c"
return 0;
}
