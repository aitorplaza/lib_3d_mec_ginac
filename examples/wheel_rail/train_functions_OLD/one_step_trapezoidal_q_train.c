/* ********************************************************************************************* */
#ifdef __EXTERNAL
 #include "external_def.h"
#endif

#include "defines.h"
#include "Includes_variables_parameters.h"
#include "Includes_Init_functions.h"
#include "Includes_functions.h"
#include "lin_alg.h"
#include "Declare_Variables.c"

#include "hertz_ellipse.h" 
#include "Table_Hertz.h"
#include "kalker_coeffs.h" 
#include "Table_Kalker.h"
#include "kalker_forces.h" 
#include "Output.h"
/* ********************************************************************************************* */
void one_step_trapezoidal_q_train (double delta_t, double * q, double *dq)
{
/* ********************************************************************************************* */
	/* Step forward delta_t */
	#include "Integration_Trapezoidal_train.c"
/* ********************************************************************************************* */
	/* Position and velocity correction */
	#include "Projection.c"
/* ********************************************************************************************* */
	/* Solving Dynamics Forward */
	#include "Solve_Dynamics.c"
/* ********************************************************************************************* */
}
