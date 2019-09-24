/* ********************************************************************************************* */
#ifndef COORD_IND
	#define COORD_IND
#endif

#include "Includes_Init_functions.h"
#include "lin_alg.h"
/* ********************************************************************************************* */

void Initial_position_velocity_z (double * q, double *dq)
{

/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND
#include "one_step.h"
double	AUX_V_dep_1[Phi_d_n_cols];
int i;
/* Solving initial position - non lineal system */
Phi();
Phi_d();
Solve_N_R_while(Phi_d_n_cols, &Phi, &Phi_d, &q[Phi_z_n_cols], _Inv_Phi_d);

/* Solving initial velocity - lineal system */
Phi_z();
Mat_Vect_Mult(Phi_d_n_cols, Phi_z_n_cols, _Phi_z, dq, +1, AUX_V_dep_1);
Beta();		for (i = 0; i < Phi_d_n_cols; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}
Mat_Vect_Mult(Phi_d_n_cols, Phi_d_n_cols, _Inv_Phi_d, AUX_V_dep_1, +1, &dq[Phi_z_n_cols]);
#endif
/* ********************************************************************************************* */

}
