/* ********************************************************************************************* */
#ifndef COORD_IND
	#define COORD_IND
#endif

#ifndef TRAPEZOIDAL
	#define TRAPEZOIDAL
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
void one_step_trapezoidal_z (double delta_t, double * q, double *dq)
{
/* ********************************************************************************************* */
	/* Step forward delta_t */
	#include "Integration_Trapezoidal.c"
/* ********************************************************************************************* */
	/* Position and velocity correction */
	#include "Projection.c"
/* ********************************************************************************************* */
	/* Solving Dynamics Forward */
	#include "Solve_Dynamics.c"
/* ********************************************************************************************* */
}
