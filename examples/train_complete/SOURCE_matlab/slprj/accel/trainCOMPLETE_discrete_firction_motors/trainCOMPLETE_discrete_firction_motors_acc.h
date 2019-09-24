#include "__cf_trainCOMPLETE_discrete_firction_motors.h"
#ifndef RTW_HEADER_trainCOMPLETE_discrete_firction_motors_acc_h_
#define RTW_HEADER_trainCOMPLETE_discrete_firction_motors_acc_h_
#ifndef trainCOMPLETE_discrete_firction_motors_acc_COMMON_INCLUDES_
#define trainCOMPLETE_discrete_firction_motors_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_nonfinite.h"
#endif
#include "trainCOMPLETE_discrete_firction_motors_acc_types.h"
typedef struct { real_T B_0_0_0 ; real_T B_0_1_0 ; real_T B_0_2_0 [ 8 ] ;
real_T B_0_3_0 ; real_T B_0_4_0 ; real_T B_0_5_0 ; real_T B_0_6_0 ; real_T
B_0_7_0 ; real_T B_0_8_0 ; real_T B_0_9_0 ; real_T B_0_10_0 ; real_T B_0_11_0
; real_T B_0_12_0 [ 8 ] ; real_T B_0_13_0 ; real_T B_0_14_0 ; real_T B_0_15_0
; real_T B_0_16_0 ; real_T B_0_17_0 [ 152 ] ; real_T B_0_17_1 [ 76 ] ; real_T
B_0_17_2 [ 40 ] ; real_T B_0_17_3 [ 20 ] ; real_T B_0_21_0 [ 152 ] ; real_T
B_0_37_0 ; real_T B_0_19_0 [ 8 ] ; }
BlockIO_trainCOMPLETE_discrete_firction_motors ; typedef struct { real_T
UnitDelay1_DSTATE [ 8 ] ; real_T UnitDelay2_DSTATE [ 8 ] ; real_T
Moldel_DSTATE [ 152 ] ; struct { void * LoggedData ; } NORMALFORCES_PWORK ;
struct { void * LoggedData ; } Nu_PWORK ; struct { void * LoggedData ; }
Output_PWORK ; struct { void * LoggedData ; } RADIO_PWORK ; struct { void *
LoggedData ; } RADIO_componentes_PWORK ; struct { void * LoggedData ; }
SLIP_PWORK ; void * ToWorkspace_PWORK ; void * ToWorkspace2_PWORK ; void *
ToWorkspace3_PWORK ; void * ToWorkspace4_PWORK ; void * ToWorkspace6_PWORK ;
struct { void * LoggedData ; } Unknowns_PWORK ; struct { void * LoggedData ;
} ddq_PWORK ; struct { void * LoggedData ; } ddxWAG_PWORK ; struct { void *
LoggedData ; } qdq_PWORK ; struct { void * LoggedData ; } xWAG_PWORK ; void *
ToWorkspace1_PWORK ; char pad_ToWorkspace1_PWORK [ 4 ] ; }
D_Work_trainCOMPLETE_discrete_firction_motors ; struct
Parameters_trainCOMPLETE_discrete_firction_motors_ { real_T P_0 ; real_T P_1
; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7
; real_T P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T
P_13 [ 2 ] ; real_T P_14 [ 76 ] ; real_T P_15 [ 2 ] ; real_T P_16 [ 76 ] ;
real_T P_17 [ 2 ] ; real_T P_18 [ 74 ] ; real_T P_19 [ 2 ] ; real_T P_20 ; }
; extern Parameters_trainCOMPLETE_discrete_firction_motors
trainCOMPLETE_discrete_firction_motors_rtDefaultParameters ;
#endif
