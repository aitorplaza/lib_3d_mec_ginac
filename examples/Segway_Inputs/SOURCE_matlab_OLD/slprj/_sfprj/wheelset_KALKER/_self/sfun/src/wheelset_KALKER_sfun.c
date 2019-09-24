/* Include files */

#include "wheelset_KALKER_sfun.h"
#include "c1_wheelset_KALKER.h"
#include "c2_wheelset_KALKER.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _wheelset_KALKERMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void wheelset_KALKER_initializer(void)
{
}

void wheelset_KALKER_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_wheelset_KALKER_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_wheelset_KALKER_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_wheelset_KALKER_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_wheelset_KALKER_process_check_sum_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1635634723U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3971800750U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(300491474U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2609842789U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3086588830U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1763259256U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2658708780U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2387466167U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_wheelset_KALKER_get_check_sum(mxArray *plhs[]);
          sf_c1_wheelset_KALKER_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_wheelset_KALKER_get_check_sum(mxArray *plhs[]);
          sf_c2_wheelset_KALKER_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3564696471U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(678668628U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1090454852U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3896867807U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3450866467U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1289620004U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3381613629U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3582129054U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_wheelset_KALKER_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "BUUGA7lTzLIycLjz34lpVB") == 0) {
          extern mxArray *sf_c1_wheelset_KALKER_get_autoinheritance_info(void);
          plhs[0] = sf_c1_wheelset_KALKER_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "BUUGA7lTzLIycLjz34lpVB") == 0) {
          extern mxArray *sf_c2_wheelset_KALKER_get_autoinheritance_info(void);
          plhs[0] = sf_c2_wheelset_KALKER_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_wheelset_KALKER_get_eml_resolved_functions_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray
          *sf_c1_wheelset_KALKER_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_wheelset_KALKER_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_wheelset_KALKER_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_wheelset_KALKER_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

void wheelset_KALKER_debug_initialize(void)
{
  _wheelset_KALKERMachineNumber_ = sf_debug_initialize_machine("wheelset_KALKER",
    "sfun",0,2,0,0,0);
  sf_debug_set_machine_event_thresholds(_wheelset_KALKERMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_wheelset_KALKERMachineNumber_,0);
}

void wheelset_KALKER_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_wheelset_KALKER_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("wheelset_KALKER",
      "wheelset_KALKER");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_wheelset_KALKER_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
