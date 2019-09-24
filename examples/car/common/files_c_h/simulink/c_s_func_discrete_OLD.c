/* Model_Based on Example C-file S-function for defining a
/* continuous linear system.
/*
/*      x' = Ax + Bu
/*      y  = Cx + Du
/*
/*      For more details about S-functions, see simulink/src/sfuntmpl_doc.c.
/*
/********************************************************************************************************/
#ifdef __EXTERNAL
#include "external_def.h"
#endif

#ifdef LIN_ALG

#define S_FUNCTION_NAME c_s_func_discrete
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

#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"

#include "step.c"
#include "lin_alg.h"
#include "Declare_Variables.h"

#include "Output.h"
#include "write_data_file.h"

/*#include "Energy.h"*/
extern void one_step_euler_z(double delta_t,double * q,double * dq);
extern void Initial_position_velocity(double * q,double * dq);
double DDelta_t;

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
    if ( mxGetNumberOfElements(ssGetSFcnParam(S,3)) != 1 || !IS_PARAM_DOUBLE(deltat)) {
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
        mexPrintf("* Using EULER explicit method with Dependent Coordinates \n");
        #endif
        #ifdef TRAPEZOIDAL
        mexPrintf("* Using TRAPEZOIDAL implicit method with Dependent Coordinates \n");
        #endif
        #ifdef TRI
        mexPrintf("* and LDL decomposition for solving linear systems \n");
        #endif
      #endif
      #ifdef COORD_IND
        #ifdef EULER
        mexPrintf("* Using EULER explicit method with Independent Velocity Formalism \n");
        #endif
        #ifdef TRAPEZOIDAL
        mexPrintf("* Using TRAPEZOIDAL implicit method with Independent Velocity Formalism \n");
        #endif
        mexPrintf("* and LU Full Pivot decomposition for coordinate partitioning and solving linear systems \n");
      #endif
      #ifdef DDL
      mexPrintf("* with Simple Formalism \n");
      #endif
      #ifdef DDQ
      mexPrintf("* with Udwadia Formalism \n");
      #endif
      #ifdef INV
      mexPrintf("* and Inverse \n");
      #endif
      mexPrintf("***************************************************************************\n");

#endif

    /* FOR CONTINUOUS real_T *x = ssGetContStates(S);*/
    x = ssGetRealDiscStates(S);/*CHANGE FOR DISCRETE*/

    /*initialize generalized coordinate, velocity and acceleration vectors  */
    #include "Init_functions.c"

    /* ALLOCATE MEMORY variables anad parameters */
/*mexPrintf("Hola1---------------------------------------------------------------- \n");*/
    Init_param ( );
    Init_ddq ( );
    Init_unknowns ( );
    Init_inputs ( );
/*mexPrintf("Hola2---------------------------------------------------------------- \n");*/

    /* INITIAL VALUES variables anad parameters */
    Init_param_values ( );
    Init_ddq_values ( ); 
    Init_unknowns_values ( );
    Init_inputs_values ( );

    q=x;
    dq=&x[n_gen_coord];
/*mexPrintf("Hola3---------------------------------------------------------------- \n");*/

    /* Copy the input parameters to the initial positions and velocities. */
    memcpy(q,       mxGetPr(ssGetSFcnParam(S,0)),       n_gen_coord*sizeof(double));
    memcpy(dq,      mxGetPr(ssGetSFcnParam(S,1)),       n_gen_vel*sizeof(double));
    memcpy(param,   mxGetPr(ssGetSFcnParam(S,2)),       n_param*sizeof(double));
/*    memcpy(&DDelta_t,   mxGetPr(ssGetSFcnParam(S,3)),       1*sizeof(double));*/
    
/*mexPrintf("Hola4---------------------------------------------------------------- \n");*/

    Initial_position_velocity(q,dq);
     memcpy(&DDelta_t,   mxGetPr(ssGetSFcnParam(S,3)),       1*sizeof(double));
/*        mexPrintf("2 Delta_t=%f \n",DDelta_t);
   mexPrintf("Hola5---------------------------------------------------------------- \n");*/
 
    #ifdef INPUTS
        for (i=0; i<n_inputs; i++){ inputs[i] = U(i); };
    #endif  
        /* mexPrintf("3 Delta_t=%f \n",DDelta_t);           
            mexPrintf("Hola6---------------------------------------------------------------- \n");*/
    
    #include "Solve_Dynamics.c"
/*                mexPrintf("4 Delta_t=%f \n",DDelta_t);
mexPrintf("Hola7---------------------------------------------------------------- \n");*/

    /* Copy the accel to ddq vector from "gen_accel_vect_def.c" */
    memcpy(ddq,            ddqunknowns,      n_gen_accel*sizeof(double));
/*        mexPrintf("5 Delta_t=%f \n",DDelta_t);*/

    #ifdef WRITE_STATE_FILE
/*            mexPrintf("Hola8---------------------------------------------------------------- \n");*/

    /* Open state file - Write state file header - time is writen so give it a value - Write initial state */
    state_file = fopen("state.dat", "w");
    write_data_file_header(state_file);
    t=ssGetT(S);
    write_data_file(state_file);
    #endif
/*mexPrintf("Hola9---------------------------------------------------------------- \n");
    mexPrintf("Fin Initialize Delta_t=%f \n",DDelta_t);*/
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
   /* mexPrintf("Delta_t en Output %f \n",DDelta_t);*/
    UNUSED_ARG(tid);
   /* mexPrintf("Delta_t en Output %f \n",DDelta_t);*/
    /* Copy the state to the output. In this case the output has been considered to be the state */

    memcpy(yqdq,   x,   ssGetNumDiscStates(S)*sizeof(double));

    /* Resolution of the system to put ddqunknowns in the output*/
/*mexPrintf("Hola10---------------------------------------------------------------- \n");*/


    #ifdef INPUTS
     for (i=0; i<n_inputs; i++){ inputs[i] = U(i); };
    #endif  
  /*           mexPrintf("Hola11---------------------------------------------------------------- \n");
    mexPrintf("ddq antes en Outputs \n");
    Vect_Print(n_gen_coord,ddq);*/
    #include "Solve_Dynamics.c"
/*            mexPrintf("Hola12---------------------------------------------------------------- \n");
    mexPrintf("ddq despues en Outputs \n");
    Vect_Print(n_gen_coord,ddq);*/
    /* copy the dq and ddq vectors to the derivative of the state (dx) vector */
    memcpy(yddq,            ddqunknowns,      n_gen_accel*sizeof(double));
    #ifdef UNKNOWNS
    memcpy(yunknowns,   &ddqunknowns[n_gen_coord],   n_unknowns*sizeof(double));
    #endif
    _Output=Output();
    memcpy(youtput,   _Output,   Output_n_rows*sizeof(double));
/*mexPrintf("Hola13---------------------------------------------------------------- \n");*/

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
/*mexPrintf("Hola14---------------------------------------------------------------- \n");*/

    #ifdef INPUTS
        for (i=0; i<n_inputs; i++){ inputs[i] = U(i); };
    #endif  

/*mexPrintf("Hola15---------------------------------------------------------------- \n");*/

    #ifdef COORD_DEP
			#ifdef EULER
			  one_step_euler_q(DDelta_t,q,dq);
			#endif
			#ifdef TRAPEZOIDAL
			  one_step_trapezoidal_q(DDelta_t,q,dq);
			#endif
    #endif

    #ifdef COORD_IND
			#ifdef EULER
            /*mexPrintf("HolaAE---------------------------------------------------------------- \n");
            %Vect_Print(n_gen_coord,q);
            Vect_Print(n_gen_coord,dq);*/
 /*            mexPrintf("Delta_t entes de llamar a one_step_euler_z %f \n",DDelta_t);*/
			 one_step_euler_z(DDelta_t,q,dq);
            /*mexPrintf("HolaDE---------------------------------------------------------------- \n");
            Vect_Print(n_gen_coord,q);
            Vect_Print(n_gen_coord,dq);*/
			#endif
		  #ifdef TRAPEZOIDAL
			 one_step_trapezoidal_z(DDelta_t,q,dq);
			#endif
    #endif
/*mexPrintf("Hola16---------------------------------------------------------------- \n");*/


    /* Copy the accel to ddq vector from "gen_accel_vect_def.c" */
    memcpy(ddq,            ddqunknowns,      n_gen_accel*sizeof(double));
/*mexPrintf("Hola17---------------------------------------------------------------- \n");*/

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

#endif

#ifdef LAPACK

#define S_FUNCTION_NAME c_s_func_discrete
#define S_FUNCTION_LEVEL 2

#include "mex.h"
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

/*#define DDL*/
/*#define COORD_DEP*/

#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"

#include "Output.h"
#include "write_data_file.h"

//#include "Energy.h"
extern double dnrm2(int *n,double *x,int *incx);
extern double daxpy(int * n_coord, double * dmone, double *qaux, int * ione, double * edq, int * ione2);

/* allocating space for ddqunknowns */
double * ddqunknowns;

real_T            *x; //esto hay que moderlo a variables de C nuestras

double Delta_t;


/* Uncomment to write state file */
#define WRITE_STATE_FILE

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
    ssSetNumContStates(S, 0);//Changed for discrete solver
    ssSetNumDiscStates(S, n_gen_coord+n_gen_vel);//Changed for discrete solver

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
 *    Specifiy that we have a continuous sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    // FOR CONTINUOUS ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    //    ssSetSampleTime(S, 0, 1.0);
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME); //CHANGE FOR DISCRETE Check that this is OK!!! if not try the line above
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
    // FOR CONTINUOUS real_T *x = ssGetContStates(S);
    x = ssGetRealDiscStates(S);//CHANGE FOR DISCRETE

    /* Allocate space for ddqunknowns*/
    ddqunknowns = malloc ( (n_unknowns+n_gen_accel) * sizeof(double) );


    /*initialize generalized coordinate, velocity and acceleration vectors  */

    #include "Init_functions.c"

    /* ALLOCATE MEMORY variables anad parameters */
    Init_t ( ); /* Include initial value t=0.0 */
    Init_param ( );
    //Init_q ( );
    //Init_dq ( );
    Init_ddq ( );
    Init_unknowns ( );
    Init_inputs ( );

    /* INITIAL VALUES variables anad parameters */
    Init_param_values ( );
    //Init_q_values ( ); 
    //Init_dq_values ( ); 
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
    /* Position Correction (obtained q does not have to satisfy geometric constraints)  */
    /* newton_raphson_min_norm (int ma, int na,double * (* A)(),double * (* b)(),double * q);   */

//    mexPrintf("%e,%e,%e,%e\n",q[0],q[1],dq[0],dq[1]);

    newton_raphson_min_norm(PhiInit_q_n_rows,PhiInit_q_n_cols,&PhiInit_q,&PhiInit,q);

    /* Velocity Correction (obtained dq does not have to satisfy velocity constraints)  */
     _BetaInit=BetaInit();
     _dPhiInit_dq=dPhiInit_dq();

     minimum_norm_correction(dPhiInit_dq_n_rows,dPhiInit_dq_n_cols,_dPhiInit_dq,_BetaInit,dq);

 
    /* Solve accel for initial accel. */
    _Qgamma=Qgamma();
    _MXdPhi_dqZero=MXdPhi_dqZero();

    minimum_norm_solution(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols , _MXdPhi_dqZero, 1, _Qgamma,ddqunknowns);

    /* Copy the accel to ddq vector from "gen_accel_vect_def.c" */
    memcpy(ddq,            ddqunknowns,      n_gen_accel*sizeof(double));
    //memcpy(ddq,            ddqunknowns,      n_gen_coord*sizeof(double));

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
    real_T            *y        = ssGetOutputPortRealSignal(S,0);
    real_T            *yddq     = ssGetOutputPortRealSignal(S,1);
    #ifdef UNKNOWNS
    real_T            *yunknowns= ssGetOutputPortRealSignal(S,2);
    real_T            *youtput  = ssGetOutputPortRealSignal(S,3);
    #else
    real_T            *youtput  = ssGetOutputPortRealSignal(S,2);
    #endif
	int i;
    InputRealPtrsType uPtrs;
	
    /* FOR CONTINUOUS real_T            *x    = ssGetContStates(S);*/
    x    = ssGetRealDiscStates(S);//CHANGE FOR DISCRETE
    uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    UNUSED_ARG(tid);
    /*mexPrintf("ox %e,%e,%e,%e\n",x[0],x[1],x[2],x[3]);*/
    /* Copy the state to the output. In this case the output has been considered to be the state */
    memcpy(y,   x,   ssGetNumDiscStates(S)*sizeof(double));
    /*mexPrintf("oy %e,%e,%e,%e\n",y[0],y[1],y[2],y[3]);*/

    /* Resolution of the system to put ddqunknowns in the output*/

    /* copy the state vector to the q and dq vectors */
    /*memcpy(q,   x,   n_gen_coord*sizeof(double));*/
    /*memcpy(dq,   &x[n_gen_coord],   n_gen_vel*sizeof(double));*/

    #ifdef INPUTS
    memcpy(inputs, &U(0), n_inputs*sizeof(double));
    #endif


    /* Evaluate Qgamma and MXdPhi_dqZero to compute the accelerations and unknowns */
    _Qgamma=Qgamma();
    _MXdPhi_dqZero=MXdPhi_dqZero();

    minimum_norm_solution(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols , _MXdPhi_dqZero, 1, _Qgamma,ddqunknowns);

    /* copy the dq and ddq vectors to the derivative of the state (dx) vector */
    memcpy(yddq,            ddqunknowns,      n_gen_accel*sizeof(double));
    #ifdef UNKNOWNS
    memcpy(yunknowns,   &ddqunknowns[n_gen_coord],   n_unknowns*sizeof(double));
    #endif
    _Output=Output();
    memcpy(youtput,   _Output,   Output_n_rows*sizeof(double));
    /*mexPrintf("Output=["); for (i=0;i<Output_n_rows;i++){ mexPrintf("%e,",_Output[i]); }; mexPrintf("]\n"); */

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
    int i;
      InputRealPtrsType uPtrs;
    x       = ssGetRealDiscStates(S);
	    UNUSED_ARG(tid); /* not used in single tasking mode */
    uPtrs    = ssGetInputPortRealSignalPtrs(S,0);
	    /* copy the state vector to the q and dq vectors */
    /* memcpy(q,   x,   n_gen_coord*sizeof(double));*/
    /* memcpy(dq,   &x[n_gen_coord],   n_gen_coord*sizeof(double));*/

    #ifdef INPUTS
    memcpy(inputs, &U(0), n_inputs*sizeof(double));
    #endif


    /* Evaluate Qgamma and MXdPhi_dqZero to compute the accelerations and unknowns */
    _Qgamma=Qgamma();
    _MXdPhi_dqZero=MXdPhi_dqZero();

    minimum_norm_solution(MXdPhi_dqZero_n_rows, MXdPhi_dqZero_n_cols , _MXdPhi_dqZero, 1, _Qgamma,ddqunknowns);

    for (i=0;i<n_gen_coord;i++){
    q[i]=q[i]+(dq[i]+0.5*ddqunknowns[i]*Delta_t)*Delta_t;
    dq[i]=dq[i]+ddqunknowns[i]*Delta_t;
    }
    /* copy the dq and ddq vectors to the derivative of the state (dx) vector */
    //  memcpy(x,              q,     n_gen_vel*sizeof(double));
    //  memcpy(&x[n_gen_coord],   dq,   n_gen_coord*sizeof(double));

    /* Copy the accel to ddq vector from "gen_accel_vect_def.c" */
    memcpy(ddq,            ddqunknowns,      n_gen_accel*sizeof(double));

    #ifdef WRITE_STATE_FILE
    /*time is writen so give it a value - Write state to write_state_file*/
    t=ssGetT(S);
    write_data_file(state_file);
    #endif

}


#define MDL_PROJECTION
/* Function: mdlProjection ===============================================================================================
 * Abstract:
 *    Projection function added to the original example
 */

/* Un-comment the next DEFINE to make the projection */


void mdlProjection(SimStruct *S)
{
/* FOR DISCRETE it is possible to put this correction within Function: mdlUpdate*/
    x    = ssGetContStates(S);

/*  q and dq update */
//    memcpy(q,       x,          n_gen_coord*sizeof(double));
//    memcpy(dq,      &x[n_gen_coord],    n_gen_coord*sizeof(double));

/*  Full Newton-Raphson Position Correction */

    #ifdef UNKNOWNS
    newton_raphson_min_norm(Phi_q_n_rows,Phi_q_n_cols,&Phi_q,&Phi,q);

/*  Velocity Correction */
    _dPhi_dq=dPhi_dq();
    _Beta=Beta();

    minimum_norm_correction(dPhi_dq_n_rows,dPhi_dq_n_cols,_dPhi_dq,_Beta,dq);

    #endif



/*  x update    */
//    memcpy(x,           q,      n_gen_coord*sizeof(double));
//    memcpy(&x[n_gen_coord], dq,     n_gen_coord*sizeof(double));
}

/* Function: mdlTerminate ========================================================================================================
 * Abstract:
 *    No termination needed, but we are required to have this routine.
 */
static void mdlTerminate(SimStruct *S)
{

    #ifdef WRITE_STATE_FILE
    fclose(state_file);
    #endif

//    free(q);
//    free(dq);
    free(ddq);

    /* freeing space for ddqunknowns */ 
    #ifdef UNKNOWNS
    free(ddqunknowns);
    #endif

    UNUSED_ARG(S); /* unused input argument */
}

#endif



#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif




