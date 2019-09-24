/* Model_Based on Example C-file S-function for defining a
 * continuous linear system.
 *
 *      x' = Ax + Bu
 *      y  = Cx + Du
 *
 *      For more details about S-functions, see simulink/src/sfuntmpl_doc.c.
 */


#define S_FUNCTION_NAME c_s_func_lin_alg_z
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"

#define U(element) (*uPtrs[element])  /* Pointer to Input Port0 */

/* Define devoted to chech if a parameters is double or not */
#define IS_PARAM_DOUBLE(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsDouble(pVal))


/*====================*
 * My include files   *
 *====================*/
#define COORD_IND
/*#define COORD_DEP*//* Develop this option with proper includes and compile options */
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"

#include "Output.h"
#include "step.c"
#include "lin_alg.h"
#include "Declare_Variables.c"
#include "mex.h" /* Calling Lapack Blas */

/*ADDED*//************************************************************************************************/

/* Uncomment to write state file */
#define WRITE_DATA_FILE

#ifdef WRITE_DATA_FILE
    FILE * data_file;
#endif

/*====================*
 * S-function methods *
 *====================*/


/* Function: mdlCheckParameters ===============================================
 * Abstract:
 *    It tests if the parameters are correct
 */

#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS)  && defined(MATLAB_MEX_FILE)
/*
 * Check to make sure that each first parameter is 3-d and positive
 * and second parameter is 4-d.
 */
static void mdlCheckParameters(SimStruct *S)
{

    const mxArray *pos_init = ssGetSFcnParam(S,0);
    const mxArray *vel_init = ssGetSFcnParam(S,1);
    const mxArray *param_init = ssGetSFcnParam(S,2);

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
        ssSetErrorStatus(S, "Third Parameter Vector must be the initial param values: [param1, param2, ....]");
        return;
    }

}
#endif



/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{

    /*
     * Check the initial settings of the parameters
     */
    /*1 for the constant parameters, and  1 parameter for the initial conditions*/
    ssSetNumSFcnParams(S, 3);  /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)
    if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {
        mdlCheckParameters(S);
        if (ssGetErrorStatus(S) != NULL) return;
    } else {
        return;
    }
#endif

    /* n_gen_coord positions and n_gen_coord velocities*/
    ssSetNumContStates(S, 2*n_gen_coord);
    ssSetNumDiscStates(S, 0);

    /* 1 Input port for the wind TORQUE in X*/
    if (!ssSetNumInputPorts(S, 1)) return;

    /* The TORQUE input is a scalar*/
    ssSetInputPortWidth(S, 0, n_inputs);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    /* 4 Output ports*/
    if (!ssSetNumOutputPorts(S, 4)) return;
    ssSetOutputPortWidth(S, 0, 2*n_gen_coord);
    ssSetOutputPortWidth(S, 1, n_gen_coord);
    ssSetOutputPortWidth(S, 2, n_unknowns);
    ssSetOutputPortWidth(S, 3, Output_n_rows);

    /*mexPrintf("Output_n_rows=%d\n",Output_n_rows);*/

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



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy that we have a continuous sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
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
    real_T *x0 = ssGetContStates(S);

    #include "Init_variables_parameters.c"
    #include "Init_functions.c"

    /* Copy the input parameters to the initial positions and velocities. */
    memcpy(q,       mxGetPr(ssGetSFcnParam(S,0)),       n_gen_coord*sizeof(double));
    memcpy(dq,      mxGetPr(ssGetSFcnParam(S,1)),       n_gen_coord*sizeof(double));
    memcpy(param,      mxGetPr(ssGetSFcnParam(S,2)),       n_param*sizeof(double));

    Initial_position_velocity_z (q,dq);

    /* Copy the positions and velocities to the state vector. */
    memcpy(x0,              q,      n_gen_coord*sizeof(double));
    memcpy(&x0[n_gen_coord],dq,     n_gen_coord*sizeof(double));

    #include "Solve_Dynamics.c"

#ifdef WRITE_DATA_FILE
    /* Open state file - Write state file header - time is writen so give it a value - Write initial state */
    data_file = fopen("state_cs_func_lin_alg_z.dat", "w");
    write_data_file_header(data_file);
    t=ssGetT(S);
    write_data_file(data_file);
#endif

}



/* Function: mdlOutputs =======================================================
 * Abstract:
 *      y = Cx + Du
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T            *y        = ssGetOutputPortRealSignal(S,0);
    real_T            *yddq     = ssGetOutputPortRealSignal(S,1);
    real_T            *yunknowns= ssGetOutputPortRealSignal(S,2);
    real_T            *youtput  = ssGetOutputPortRealSignal(S,3);

    real_T            *x    = ssGetContStates(S);
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);

    int i;

    UNUSED_ARG(tid);

    /* Copy the state to the output. In this case the output has been considered to be the state */
    memcpy(y,   x,   ssGetNumContStates(S)*sizeof(double));

    /* Resolution of the system to put ddq in the output*/

    /* copy the state vector to the q and dq vectors */
    memcpy(q,   x,   n_gen_coord*sizeof(double));
    memcpy(dq,   &x[n_gen_coord],   n_gen_coord*sizeof(double));
    memcpy(inputs, &U(0), n_inputs*sizeof(double));

    #include "Solve_Dynamics.c"

    /* copy the dq and ddq vectors to the derivative of the state (dx) vector */
    memcpy(yddq,            ddq,      n_gen_coord*sizeof(double));
    /*memcpy(yunknowns,   &ddqunknowns[n_gen_coord],   n_unknowns*sizeof(double));*/

    _Output=Output();
    memcpy(youtput,   _Output,   Output_n_rows*sizeof(double));
    /*mexPrintf("Output=["); for (i=0;i<Output_n_rows;i++){ mexPrintf("%e,",_Output[i]); }; mexPrintf("]\n"); */

}



#define MDL_DERIVATIVES
/* Function: mdlDerivatives =================================================
 * Abstract:
 *      xdot = Ax + Bu
 */
static void mdlDerivatives(SimStruct *S)
{
    real_T            *dx   = ssGetdX(S);
    real_T            *x    = ssGetContStates(S);
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);


    /* copy the state vector to the q and dq vectors */
    memcpy(q,   x,   n_gen_coord*sizeof(double));
    memcpy(dq,   &x[n_gen_coord],   n_gen_coord*sizeof(double));
    memcpy(inputs, &U(0), n_inputs*sizeof(double));

    #include "Solve_Dynamics.c"


    /* copy the dq and ddq vectors to the derivative of the state (dx) vector */
    memcpy(dx,              dq,     n_gen_coord*sizeof(double));
    memcpy(&dx[n_gen_coord],ddq,   n_gen_coord*sizeof(double));

    #ifdef WRITE_DATA_FILE
    /*time is writen so give it a value - Write state to write_data_file*/
    t=ssGetT(S);
    write_data_file(data_file);
    #endif

}



/* Function: mdlProjection =====================================================
 * Abstract:
 *    Projection function added to the original example
 */

/* Un-comment the next DEFINE to make the projection */
#define MDL_PROJECTION

void mdlProjection(SimStruct *S)
{

    real_T            *x    = ssGetContStates(S);

/*  q and dq update */
    memcpy(q,       x,          n_gen_coord*sizeof(double));
    memcpy(dq,      &x[n_gen_coord],    n_gen_coord*sizeof(double));

    #include "Projection.c"

/*  x update    */
    memcpy(x,           q,      n_gen_coord*sizeof(double));
    memcpy(&x[n_gen_coord], dq,     n_gen_coord*sizeof(double));
}

/* Function: mdlTerminate =====================================================
 * Abstract:
 *    No termination needed, but we are required to have this routine.
 */
static void mdlTerminate(SimStruct *S)
{

    #ifdef WRITE_DATA_FILE
    fclose(data_file);
    #endif

    #include "Done_variables_parameters.c"
    #include "Done_functions.c"

    UNUSED_ARG(S); /* unused input argument */
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif




