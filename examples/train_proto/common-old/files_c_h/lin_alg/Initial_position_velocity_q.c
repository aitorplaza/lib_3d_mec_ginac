/* ********************************************************************************************* */
#ifndef COORD_DEP
	#define COORD_DEP
#endif

#include "Includes_Init_functions.h"
#include "lin_alg.h"
/* ********************************************************************************************* */

void Initial_position_velocity_q (double * q, double *dq)
{

/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP

double	_Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];
double	_Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];
/* Solving initial position - non lineal system */
PhiInit();
PhiInit_q();
Solve_N_R_while(PhiInit_n_rows,&PhiInit, &PhiInit_q, q, _Inv_PhiInit_q);

/* Solving initial velocity - lineal system */
dPhiInit_dq();
Mat_Inv(dPhiInit_dq_n_rows, _dPhiInit_dq, _Inv_dPhiInit_dq);
BetaInit();
Mat_Vect_Mult(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _Inv_dPhiInit_dq, _BetaInit , 1, dq);
#endif
/* ********************************************************************************************* */

}
