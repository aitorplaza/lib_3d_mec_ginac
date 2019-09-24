/* ********************************************************************************************* */
#ifndef COORD_DEP
	#define COORD_DEP
#endif

#ifndef EULER
	#define EULER
#endif

#ifndef INV
	#ifndef TRI
    #define INV
	#endif
#endif

#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "lin_alg.h"
#include "Declare_Variables.c"
/* ********************************************************************************************* */
void one_step_euler_q (double delta_t, double * q, double *dq)
{
/* ********************************************************************************************* */
	/* Step forward delta_t */
	#include "Integration_Euler.c"
/* ********************************************************************************************* */
	/* Position and velocity correction */
	#include "Projection.c"
/* ********************************************************************************************* */
	/* Solving Dynamics Forward */
	#include "Solve_Dynamics.c"
/* ********************************************************************************************* */
}
