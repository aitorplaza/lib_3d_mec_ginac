/* Model_Based on Example C-file S-function for defining a
/* continuous linear system.
/*
/*      x' = Ax + Bu
/*      y  = Cx + Du
/*
/*      For more details about S-functions, see simulink/src/sfuntmpl_doc.c.
/*
/********************************************************************************************************/
/*#define LAPACK*/
/*#define LIN_ALG*/

#define S_FUNCTION_NAME c_s_func_linalg_discrete
#define S_FUNCTION_LEVEL 2

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "simstruc.h"


#define U(element) (*uPtrs[element])  /* Pointer to Input Port0 */

/* Define devoted to chech if a parameters is double or not */
#define IS_PARAM_DOUBLE(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsDouble(pVal))


/*====================*
 * My include files   *
 *====================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h" 

#ifndef MATLAB_MEX_FILE
#include "external_def.h"
#endif

#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"

#include "step.c"
#include "lin_alg.h"
#include "Declare_Variables.h"

#include "Output.h"
#include "write_data_file.h"

/*#include "Energy.h"*/

double Delta_t;


/* state vector */
real_T            *x; /*esto hay que modelo a variables de C nuestras*/

/* Uncomment to write state file */
/*#define WRITE_STATE_FILE*/

#ifdef WRITE_STATE_FILE
    FILE * state_file;
#endif

/********************************************************************************************************/
/****************************           S-function methods        ***************************************/
/********************************************************************************************************/

/* Function: mdlCheckParameters =========================================================================
 * Abstract:
 *    It tests if the parameters are correct
 *    Check to make sure that each first parameter
 *    has appropiate size and type.

 */

#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS)  && defined(MATLAB_MEX_FILE)

static void mdlCheckParameters(SimStruct *S)
{

    const mxArray *pos_init = ssGetSFcnParam(S,0);
    const mxArray *vel_init = ssGetSFcnParam(S,1);
    const mxArray *param_init = ssGetSFcnParam(S,2);
    const mxArray *deltat = ssGetSFcnParam(S,3);

    /* If the number of parameters is different from n_gen_coord */
    if ( mxGetNumberOfElements(ssGetSFcnParam(S,0)) != n_gen_coord || !IS_PARAM_DOUBLE(pos_init)) {
        ssSetErrorStatus(S, "First Parameter Vector must be the initial coordinates values: [q1, q2, ....]");
        return;
    }

    /* If the number of parameters is different from n_gen_coord */
    if ( mxGetNumberOfElements(ssGetSFcnParam(S,1)) != n_gen_vel || !IS_PARAM_DOUBLE(vel_init)) {
        ssSetErrorStatus(S, "Second Parameter Vector must be the initial velocities values: [dq1, dq2, ....]");
        return;
    }

    /* If the number of parameters is different from n_gen_coord */
    if ( mxGetNumberOfElements(ssGetSFcnParam(S,2)) != n_param || !IS_PARAM_DOUBLE(param_init)) {
        ssSetErrorStatus(S, "Third Parameter Vector must be the param values: [param1, param2, ....]");
        return;
    }

    /* If the number of parameters is different from 1 */
    if ( mxGetNumberOfElements(ssGetSFcnParam(S,3)) != 1 || !IS_PARAM_DOUBLE(param_init)) {
        ssSetErrorStatus(S, "Fourth Parameter  must be the fixed Delta_t: [Delta_t]");
        return;
    }

}
#endif



/* Function: mdlInitializeSizes =================================================================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 *    Check the initial settings of the parameters
 */

static void mdlInitializeSizes(SimStruct *S)
{

    ssSetNumSFcnParams(S, 4);  /* Number of expected parameters */

    #if defined(MATLAB_MEX_FILE)
    if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {
        mdlCheckParameters(S);
        if (ssGetErrorStatus(S) != NULL) return;
    } else {
        return;
    }
    #endif

    /* n_gen_coord positions and n_gen_coord velocities*/
    ssSetNumContStates(S, 0);/*Changed for discrete solver*/
    ssSetNumDiscStates(S, n_gen_coord+n_gen_vel);/*Changed for discrete solver*/

    /* Input port*/
    #ifdef INPUTS
    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, n_inputs);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    #endif


    /* Output ports*/

    #ifdef UNKNOWNS
    if (!ssSetNumOutputPorts(S, 4)) return;
    ssSetOutputPortWidth(S, 0, 2*n_gen_coord);
    ssSetOutputPortWidth(S, 1, n_gen_coord);
    ssSetOutputPortWidth(S, 2, n_unknowns);
    ssSetOutputPortWidth(S, 3, Output_n_rows);
    #else
    if (!ssSetNumOutputPorts(S, 3)) return;
    ssSetOutputPortWidth(S, 0, 2*n_gen_coord);
    ssSetOutputPortWidth(S, 1, n_gen_coord);
    ssSetOutputPortWidth(S, 2, Output_n_rows);
    #endif


    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

}



/* Function: mdlInitializeSampleTimes ==================================================================================
 * Abstract:
 *    Specifiy that we have a discrete sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{

    /*    ssSetSampleTime(S, 0, 1.0);*/
  
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME); /*CHANGE FOR DISCRETE Check that this is OK!!! if not try the line above*/
    /*ssSetSampleTime(S, 0, Delta_t); /*CHECK THIS (Aitor)*/

    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);

}

#define MDL_INITIALIZE_CONDITIONS
/* Function: mdlInitializeConditions ========================================
 * Abstract:
 *    - Get initial states from the input parameters
 *    - Copy to the q and dq vectors
 *    - Update q with the Newton-Raphson method
 *    - Update dq solving for the solution nearer to the proposed on input
 *    - Assign the corrected initial values to the state vector x
 */
static void mdlInitializeConditions(SimStruct *S)
{

InputRealPtrsType uPtrs;
 
uPtrs    = ssGetInputPortRealSignalPtrs(S,0);

#ifdef MATLAB_MEX_FILE

/* Information messages */

        mexPrintf("\n");
        mexPrintf("**************************************************************************\n");
        mexPrintf("* Using LIN_ALG library \n");
        #ifdef COORD_DEP
	  #ifdef EULER
	   mexPrintf("* Using EULER with Dependent Coordinates  \n"); 
	  #endif
	  #ifdef TRAPEZOIDAL
	    mexPrintf("* Using TRAPEZOIDAL with Dependent Coordinates \n");
	  #endif
	  #ifdef I3AL
	    mexPrintf("* Using index-3 augmented Lagrangian with Dependent Coordinates \n");
	  #endif
        #endif
        #ifdef COORD_IND
	  #ifdef EULER
	   mexPrintf("* Using EULER with Independent Coordinates  \n"); 
	  #endif
	  #ifdef TRAPEZOIDAL
	    mexPrintf("* Using TRAPEZOIDAL with Independent Coordinates \n");
	  #endif
	  #ifdef I3AL
	    mexPrintf("* Using index-3 augmented Lagrangian with Independent Coordinates \n");
	  #endif
        #endif
        #ifdef DDL
          mexPrintf("* with Qgamma and MXdPhi_dqZero matrices \n");
        #endif
        #ifdef DDQ
          mexPrintf("* with Q and M matrices \n");
        #endif
        #ifdef TRI
          mexPrintf("* and Cholesky decomposition. \n");
        #endif
        #ifdef INV
          mexPrintf("* and Inverse. \n");
        #endif
        mexPrintf("**************************************************************************\n");
        mexPrintf("\n");

#endif

    /* FOR CONTINUOUS real_T *x = ssGetContStates(S);*/
    x = ssGetRealDiscStates(S);/*CHANGE FOR DISCRETE*/

    /*initialize generalized coordinate, velocity and acceleration vectors  */
    #include "Init_functions.c"

    /* ALLOCATE MEMORY variables anad parameters */

    Init_param ( );
    Init_ddq ( );
    Init_unknowns ( );
    Init_inputs ( );

    /* INITIAL VALUES variables anad parameters */
    Init_param_values ( );
    Init_ddq_values ( ); 
    Init_unknowns_values ( );
    Init_inputs_values ( );

    q=x;
    dq=&x[n_gen_coord];

    /* Copy the input parameters to the initial positions and velocities. */
    memcpy(q,       mxGetPr(ssGetSFcnParam(S,0)),       n_gen_coord*sizeof(double));
    memcpy(dq,      mxGetPr(ssGetSFcnParam(S,1)),       n_gen_vel*sizeof(double));
    memcpy(param,   mxGetPr(ssGetSFcnParam(S,2)),       n_param*sizeof(double));
    memcpy(&Delta_t,   mxGetPr(ssGetSFcnParam(S,3)),       1*sizeof(double));
    

    Initial_position_velocity(q,dq);

    #ifdef INPUTS
        for (i=0; i<n_inputs; i++){ inputs[i] = U(i); };
    #endif  


    #include "Solve_Dynamics.c"


    /* Copy the accel to ddq vector from "gen_accel_vect_def.c" */
    memcpy(ddq,            ddqunknowns,      n_gen_accel*sizeof(double));

    #ifdef WRITE_STATE_FILE
    /* Open state file - Write state file header - time is writen so give it a value - Write initial state */
    state_file = fopen("state.dat", "w");
    write_data_file_header(state_file);
    t=ssGetT(S);
    write_data_file(state_file);
    #endif

}

/* Function: mdlOutputs =================================================================================================
 * Abstract:
 *      y = Cx + Du
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T            *yqdq        = ssGetOutputPortRealSignal(S,0);
    real_T            *yddq     = ssGetOutputPortRealSignal(S,1);
    #ifdef UNKNOWNS
    real_T            *yunknowns= ssGetOutputPortRealSignal(S,2);
    real_T            *youtput  = ssGetOutputPortRealSignal(S,3);
    #else
    real_T            *youtput  = ssGetOutputPortRealSignal(S,2);
    #endif
    InputRealPtrsType uPtrs;

    /* FOR CONTINUOUS real_T            *x    = ssGetContStates(S);*/
    x    = ssGetRealDiscStates(S);/*CHANGE FOR DISCRETE*/
    uPtrs = ssGetInputPortRealSignalPtrs(S,0);

    UNUSED_ARG(tid);

    /* Copy the state to the output. In this case the output has been considered to be the state */

    memcpy(yqdq,   x,   ssGetNumDiscStates(S)*sizeof(double));


    /* Resolution of the system to put ddqunknowns in the output*/

    #ifdef INPUTS
     for (i=0; i<n_inputs; i++){ inputs[i] = U(i); };
    #endif  

    #include "Solve_Dynamics.c"

    /* copy the dq and ddq vectors to the derivative of the state (dx) vector */
    memcpy(yddq,            ddqunknowns,      n_gen_accel*sizeof(double));
    #ifdef UNKNOWNS
    memcpy(yunknowns,   &ddqunknowns[n_gen_coord],   n_unknowns*sizeof(double));
    #endif
    _Output=Output();
    memcpy(youtput,   _Output,   Output_n_rows*sizeof(double));

}

/* FOR DISCRETE 
Function mdlDerivatives is REMOVED and changed by the following Function mdlUpdate */

#define MDL_UPDATE
/* Function: mdlUpdate ================================================================================================
 * Abstract:
 *      xdot = Ax + Bu
 */
static void mdlUpdate(SimStruct *S, int_T tid)
{
    InputRealPtrsType uPtrs;
    x       = ssGetRealDiscStates(S);
    uPtrs    = ssGetInputPortRealSignalPtrs(S,0);
    
    UNUSED_ARG(tid); /* not used in single tasking mode */

    #ifdef INPUTS
        for (i=0; i<n_inputs; i++){ inputs[i] = U(i); };
    #endif  


    #ifdef COORD_DEP
	  #ifdef EULER
	    one_step_euler_q(Delta_t,q,dq);
	  #endif
	  #ifdef TRAPEZOIDAL
	    one_step_trapezoidal_q(Delta_t,q,dq);
	  #endif
	  #ifdef I3AL
	    one_step_i3al_q(Delta_t,q,dq);
	  #endif
    #endif

    #ifdef COORD_IND
	  #ifdef EULER
	   one_step_euler_z(Delta_t,q,dq);
	  #endif
          #ifdef TRAPEZOIDAL
	   one_step_trapezoidal_z(Delta_t,q,dq);
	  #endif
	  #ifdef I3AL
	   one_step_i3al_z(Delta_t,q,dq);
	  #endif
    #endif


    /* Copy the accel to ddq vector from "gen_accel_vect_def.c" */
    memcpy(ddq,            ddqunknowns,      n_gen_accel*sizeof(double));

    #ifdef WRITE_STATE_FILE
    /*time is writen so give it a value - Write state to write_state_file*/
    t=ssGetT(S);
    write_data_file(state_file);
    #endif

}



/* Function: mdlProjection ===============================================================================================
 * Abstract:
 *    Projection function added to the original example
 *    In DISCRETE no projection needed, is done in mdlUpdate function.
 */

/* Function: mdlTerminate ========================================================================================================
 * Abstract:
 *    No termination needed, but we are required to have this routine.
 */
static void mdlTerminate(SimStruct *S)
{

    #ifdef WRITE_STATE_FILE
    fclose(state_file);
    #endif

   Done_ddq (  );
   Done_inputs (  );
   Done_param (  );
   #ifdef UNKNOWNS
    Done_unknowns (  );
   #endif

   #include "Done_functions.c"

   UNUSED_ARG(S); /* unused input argument */
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif




