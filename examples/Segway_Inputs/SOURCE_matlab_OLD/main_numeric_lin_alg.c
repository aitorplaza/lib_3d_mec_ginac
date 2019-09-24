#ifdef __EXTERNAL
 #include "external_def.h"
#endif

/* ********************************************************************************************* */
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"
#include "timestamp.c"
#include "defines.h"
/* ********************************************************************************************* */
#include "one_step.h"
#include "lin_alg.h"
#include "Declare_Variables.h"
/* ********************************************************************************************* */

int main (int argc, char *argv[]) {

#include "arguments.c"
//printf("t = %g, steps %ld ",t,steps);
#include "Init_variables_parameters.c"
#include "Init_functions.c"
/* ********************************************************************************************* */
Initial_position_velocity(q,dq);
#include "Solve_Dynamics.c" /* ddq for t=0 */
/* ********************************************************************************************* */
#ifdef TIME_ON
  start = timestamp();
#endif
#ifndef TIME_ON
  FILE * data_file = fopen(output_file_name, "w");
  write_data_file_header(data_file);
  write_data_file(data_file);
#endif
  
#ifdef MATLAB_MEX_FILE
    #define printf mexPrintf
#endif 
        
/* ********************************************************************************************* */
/* integration */	/* Solving for t > 0 */
for (k=1; k<=steps; k++){

#ifdef COORD_DEP
	#ifdef EULER
		one_step_euler_q(delta_t,q,dq);
	#endif
	#ifdef TRAPEZOIDAL
		one_step_trapezoidal_q(delta_t,q,dq);
	#endif
	#ifdef I3AL
		one_step_i3al_q(delta_t,q,dq);
	#endif
#endif

#ifdef COORD_IND
	#ifdef EULER
		one_step_euler_z(delta_t,q,dq);
	#endif
	#ifdef TRAPEZOIDAL
		one_step_trapezoidal_z(delta_t,q,dq);
	#endif
	#ifdef I3AL
		one_step_i3al_z(delta_t,q,dq);
	#endif
#endif

#ifndef TIME_ON
  t=t+delta_t;
  write_data_file(data_file);
#endif

}
/* ********************************************************************************************* */
#ifdef TIME_ON
  end = timestamp();
  printf("%s calculation time: %.9f secs\n",output_file_name,(end - start) / ((double) n_iterations));
#endif
#ifndef TIME_ON
  fclose(data_file);
  printf("The created file name is: %s\n",output_file_name);
#endif
/* ********************************************************************************************* */
#include "Done_variables_parameters.c"
#include "Done_functions.c"
return 0;
}
