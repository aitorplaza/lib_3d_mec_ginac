#include "__cf_train_discrete_firction_noOSG.h"
#ifndef RTW_HEADER_train_discrete_firction_noOSG_h_
#define RTW_HEADER_train_discrete_firction_noOSG_h_
#ifndef train_discrete_firction_noOSG_COMMON_INCLUDES_
#define train_discrete_firction_noOSG_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "train_discrete_firction_noOSG_types.h"
#define MODEL_NAME train_discrete_firction_noOSG
#define NSAMPLE_TIMES (2) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (11) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (NULL)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)
#endif
typedef struct { real_T mapxmkextn [ 4 ] ; real_T jzaqh5q4hs ; real_T
lm4vg54kgl ; real_T hmgfwvrapw ; real_T bipku3phqn ; real_T ea35mwnxp3 [ 4 ]
; real_T o5g53wpycn [ 90 ] ; real_T ja011sv0ld [ 45 ] ; real_T ehfze2n4rn [
20 ] ; real_T bcfr1o3fhj [ 8 ] ; real_T heaby2xbgq ; } BlockIO ; typedef
struct { real_T mkcbw0czlr [ 4 ] ; real_T kmnd1a0hnp [ 4 ] ; real_T
id4xzvptbk [ 90 ] ; struct { void * LoggedData ; } nxtduwqe0i ; struct { void
* LoggedData ; } kra51p0ula ; struct { void * LoggedData ; } owyk10ibx3 ;
struct { void * LoggedData ; } jdgmm4jsbu ; struct { void * LoggedData ; }
br001kkqdk ; struct { void * LoggedData ; } o0jsobo25z ; struct { void *
LoggedData ; } nbtxt2yzu0 ; struct { void * LoggedData ; } mij1qormyo ;
struct { void * LoggedData ; } kh45rl25om ; struct { void * LoggedData ; }
bxhs1wd3ta ; struct { void * LoggedData ; } ngaphobxq2 ; struct { void *
LoggedData ; } ibsdmxafop ; struct { void * LoggedData ; } dbxa4jk1at ;
struct { void * LoggedData ; } icowkllmtt ; } D_Work ; struct Parameters_ {
real_T FRONTMOTOR_Value ; real_T REARMOTOR_Value ; real_T UnitDelay1_X0 ;
real_T Raincondition_Value ; real_T UnitDelay2_X0 ; real_T Moldel_P1_Size [ 2
] ; real_T Moldel_P1 [ 45 ] ; real_T Moldel_P2_Size [ 2 ] ; real_T Moldel_P2
[ 45 ] ; real_T Moldel_P3_Size [ 2 ] ; real_T Moldel_P3 [ 61 ] ; real_T
Moldel_P4_Size [ 2 ] ; real_T Moldel_P4 ; } ; extern Parameters rtP ; extern
const char * RT_MEMORY_ALLOCATION_ERROR ; extern BlockIO rtB ; extern D_Work
rtDWork ; extern SimStruct * const rtS ; extern const int_T gblNumToFiles ;
extern const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ;
extern rtInportTUtable * gblInportTUtables ; extern const char *
gblInportFileName ; extern const int_T gblNumRootInportBlks ; extern const
int_T gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ;
extern const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [
] ; extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ;
#endif
