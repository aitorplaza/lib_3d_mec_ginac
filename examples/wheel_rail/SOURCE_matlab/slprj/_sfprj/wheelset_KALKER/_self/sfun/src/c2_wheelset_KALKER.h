#ifndef __c2_wheelset_KALKER_h__
#define __c2_wheelset_KALKER_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c2_ResolvedFunctionInfo;

typedef struct {
  SimStruct *S;
  int32_T c2_sfEvent;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c2_doneDoubleBufferReInit;
  boolean_T c2_isStable;
  uint8_T c2_is_active_c2_wheelset_KALKER;
  ChartInfoStruct chartInfo;
} SFc2_wheelset_KALKERInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_wheelset_KALKER_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_wheelset_KALKER_get_check_sum(mxArray *plhs[]);
extern void c2_wheelset_KALKER_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
