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
/* ********************************************************************************************* */
void one_step_euler_z (double delta_t, double * q, double *dq)
{
/* ********************************************************************************************* */
   /* mexPrintf("delta_t dentro de one_step_euler_z %f \n",delta_t);*/
	/* Step forward delta_t */  
/*    mexPrintf("q antes integrar \n");
    Vect_Print(n_gen_coord,q);
     mexPrintf("ddq antes integrar \n");
    Vect_Print(n_gen_coord,ddq);*/
	#include "Integration_Euler.c"
 /*   mexPrintf("q desp integrar \n");
    Vect_Print(n_gen_coord,q);
    mexPrintf("ddq desps integrar \n");
    Vect_Print(n_gen_coord,ddq);*/
/* ********************************************************************************************* */
	/* Position and velocity correction */
	#include "Projection.c"
/* ********************************************************************************************* */
	/* Solving Dynamics Forward */
 /*   mexPrintf("ddq antes \n");
    Vect_Print(n_gen_coord,ddq);*/
	#include "Solve_Dynamics.c"
/*    mexPrintf("ddq despues \n");
    Vect_Print(n_gen_coord,ddq);*/
/* ********************************************************************************************* */

}
