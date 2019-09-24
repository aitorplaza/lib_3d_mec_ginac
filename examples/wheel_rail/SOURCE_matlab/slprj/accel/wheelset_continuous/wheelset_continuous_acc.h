#include "__cf_wheelset_continuous.h"
#ifndef RTW_HEADER_wheelset_continuous_acc_h_
#define RTW_HEADER_wheelset_continuous_acc_h_
#ifndef wheelset_continuous_acc_COMMON_INCLUDES_
#define wheelset_continuous_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "wheelset_continuous_acc_types.h"
typedef struct { real_T B_1_3_0 ; real_T B_1_6_0 [ 28 ] ; real_T B_0_0_0 [ 28
] ; real_T B_0_0_1 [ 14 ] ; real_T B_0_0_2 [ 10 ] ; real_T B_0_0_3 [ 26 ] ;
real_T B_1_0_0 ; } BlockIO_wheelset_continuous ; typedef struct { void *
ToWorkspace1_PWORK ; void *
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_AlgLoopData ; struct { void *
LoggedData ; } LAMBDA_PWORK ; struct { void * LoggedData ; } Output_PWORK ;
void * ToWorkspace_PWORK ; void * ToWorkspace2_PWORK ; void *
ToWorkspace3_PWORK ; void * ToWorkspace4_PWORK ; struct { void * LoggedData ;
} ddq_PWORK ; struct { void * LoggedData ; } qdq_PWORK ; }
D_Work_wheelset_continuous ; typedef struct { real_T Moldel_CSTATE [ 28 ] ; }
ContinuousStates_wheelset_continuous ; typedef struct { real_T Moldel_CSTATE
[ 28 ] ; } StateDerivatives_wheelset_continuous ; typedef struct { boolean_T
Moldel_CSTATE [ 28 ] ; } StateDisabled_wheelset_continuous ; struct
Parameters_wheelset_continuous_ { real_T P_0 [ 2 ] ; real_T P_1 [ 14 ] ;
real_T P_2 [ 2 ] ; real_T P_3 [ 14 ] ; real_T P_4 [ 2 ] ; real_T P_5 [ 39 ] ;
real_T P_6 ; } ; extern Parameters_wheelset_continuous
wheelset_continuous_rtDefaultParameters ;
#endif
