#include "__cf_train_discrete_firction_noOSG.h"
#ifndef RTW_HEADER_train_discrete_firction_noOSG_acc_h_
#define RTW_HEADER_train_discrete_firction_noOSG_acc_h_
#ifndef train_discrete_firction_noOSG_acc_COMMON_INCLUDES_
#define train_discrete_firction_noOSG_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "train_discrete_firction_noOSG_acc_types.h"
typedef struct { real_T B_0_0_0 ; real_T B_0_1_0 ; real_T B_0_2_0 [ 4 ] ;
real_T B_0_3_0 ; real_T B_0_4_0 ; real_T B_0_5_0 ; real_T B_0_6_0 ; real_T
B_0_7_0 ; real_T B_0_8_0 [ 4 ] ; real_T B_0_9_0 [ 90 ] ; real_T B_0_9_1 [ 45
] ; real_T B_0_9_2 [ 20 ] ; real_T B_0_9_3 [ 8 ] ; real_T B_0_23_0 ; }
BlockIO_train_discrete_firction_noOSG ; typedef struct { real_T
UnitDelay1_DSTATE [ 4 ] ; real_T UnitDelay2_DSTATE [ 4 ] ; real_T
Moldel_DSTATE [ 90 ] ; struct { void * LoggedData ; } NORMALFORCES_PWORK ;
struct { void * LoggedData ; } Output_PWORK ; struct { void * LoggedData ; }
SLIP_PWORK ; void * ToWorkspace_PWORK ; void * ToWorkspace2_PWORK ; void *
ToWorkspace3_PWORK ; void * ToWorkspace4_PWORK ; void * ToWorkspace5_PWORK ;
void * ToWorkspace6_PWORK ; struct { void * LoggedData ; } Unknowns_PWORK ;
struct { void * LoggedData ; } ddq_PWORK ; struct { void * LoggedData ; }
qdq_PWORK ; struct { void * LoggedData ; } xBOG_PWORK ; void *
ToWorkspace1_PWORK ; } D_Work_train_discrete_firction_noOSG ; struct
Parameters_train_discrete_firction_noOSG_ { real_T P_0 ; real_T P_1 ; real_T
P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 [ 2 ] ; real_T P_6 [ 45 ] ; real_T
P_7 [ 2 ] ; real_T P_8 [ 45 ] ; real_T P_9 [ 2 ] ; real_T P_10 [ 61 ] ;
real_T P_11 [ 2 ] ; real_T P_12 ; } ; extern
Parameters_train_discrete_firction_noOSG
train_discrete_firction_noOSG_rtDefaultParameters ;
#endif
