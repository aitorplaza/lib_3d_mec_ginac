#include "__cf_trainCOMPLETE_discrete_firction_motors.h"
#include <math.h>
#include "trainCOMPLETE_discrete_firction_motors_acc.h"
#include "trainCOMPLETE_discrete_firction_motors_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T currentTime ;
if ( ssIsContinuousTask ( S , tid ) ) { currentTime = ssGetTaskTime ( S , 0 )
; if ( currentTime < ( ( Parameters_trainCOMPLETE_discrete_firction_motors *
) ssGetDefaultParam ( S ) ) -> P_0 ) { ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_0_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_1 ; } else { ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_0_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_2 ; } currentTime = ssGetTaskTime ( S , 0 ) ;
if ( currentTime < ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_3 ) { ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_1_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_4 ; } else { ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_1_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_5 ; } } if ( ssIsSampleHit ( S , 1 , tid ) ) {
memcpy ( ( void * ) ( & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors *
) _ssGetBlockIO ( S ) ) -> B_0_2_0 [ 0 ] ) , ( void * ) ( (
D_Work_trainCOMPLETE_discrete_firction_motors * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE , sizeof ( real_T ) << 3U ) ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_3_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_7 ; mu_div_mod_vel_sliding_vel_Outputs_wrapper
( & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S
) ) -> B_0_2_0 [ 0 ] , & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors *
) _ssGetBlockIO ( S ) ) -> B_0_3_0 , & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_4_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 1 ] , & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 , & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_5_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 2 ] , & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 , & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_6_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 3 ] , & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 , & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_7_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 0 ] , & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 , & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_8_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 1 ] , & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 , & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_9_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 2 ] , & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 , & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_10_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 3 ] , & ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 , & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_11_0 ) ; memcpy ( ( void * ) ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_12_0 [ 0 ] ) , ( void * ) ( (
D_Work_trainCOMPLETE_discrete_firction_motors * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE , sizeof ( real_T ) << 3U ) ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_13_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_9 ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_14_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_10 ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_15_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_11 ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_16_0 = ( ( Parameters_trainCOMPLETE_discrete_firction_motors * )
ssGetDefaultParam ( S ) ) -> P_12 ; } if ( ssIsContinuousTask ( S , tid ) ) {
ssCallAccelRunBlock ( S , 0 , 17 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 1 , tid ) ) { ssCallAccelRunBlock ( S , 0 , 18 ,
SS_CALL_MDL_OUTPUTS ) ; ( ( BlockIO_trainCOMPLETE_discrete_firction_motors *
) _ssGetBlockIO ( S ) ) -> B_0_19_0 [ 0 ] = ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_4_0 * ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_2_0 [ 0 ] ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_19_0 [ 1 ] = ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_5_0 * ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 1 ] ; ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_19_0 [ 2 ] = ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_6_0 * ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_2_0 [ 2 ] ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_19_0 [ 3 ] = ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_7_0 * ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 3 ] ; ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_19_0 [ 4 ] = ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_8_0 * ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_2_0 [ 4 ] ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_19_0 [ 5 ] = ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_9_0 * ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 5 ] ; ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_19_0 [ 6 ] = ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_10_0 * ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_2_0 [ 6 ] ; ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_19_0 [ 7 ] = ( ( BlockIO_trainCOMPLETE_discrete_firction_motors * )
_ssGetBlockIO ( S ) ) -> B_0_11_0 * ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_2_0 [ 7 ] ; ssCallAccelRunBlock ( S , 0 , 20 , SS_CALL_MDL_OUTPUTS ) ; }
if ( ssIsContinuousTask ( S , tid ) && ssIsSpecialSampleHit ( S , 2 , 0 , tid
) ) { memcpy ( ( void * ) ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_21_0 [ 0 ] ) , ( void * ) ( & ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_17_0 [ 0 ] ) , 152U * sizeof ( real_T ) ) ; } if ( ssIsSampleHit ( S , 2
, tid ) ) { ssCallAccelRunBlock ( S , 0 , 22 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 1 , tid ) ) { ssCallAccelRunBlock ( S , 0 , 23 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 24 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 25 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 26 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 27 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 28 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 29 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 30 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 31 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 32 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 33 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 34 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsContinuousTask ( S , tid ) ) { ( (
BlockIO_trainCOMPLETE_discrete_firction_motors * ) _ssGetBlockIO ( S ) ) ->
B_0_35_0 = ssGetT ( S ) ; } if ( ssIsSampleHit ( S , 1 , tid ) ) {
ssCallAccelRunBlock ( S , 0 , 36 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 0 , 37 , SS_CALL_MDL_OUTPUTS ) ; } }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { int32_T i ; if (
ssIsSampleHit ( S , 1 , tid ) ) { for ( i = 0 ; i < 8 ; i ++ ) { ( (
D_Work_trainCOMPLETE_discrete_firction_motors * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE [ i ] = ( ( BlockIO_trainCOMPLETE_discrete_firction_motors
* ) _ssGetBlockIO ( S ) ) -> B_0_17_3 [ i ] ; ( (
D_Work_trainCOMPLETE_discrete_firction_motors * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ i ] = ( ( BlockIO_trainCOMPLETE_discrete_firction_motors
* ) _ssGetBlockIO ( S ) ) -> B_0_17_3 [ i + 8 ] ; } } if ( ssIsContinuousTask
( S , tid ) ) { ssCallAccelRunBlock ( S , 0 , 17 , SS_CALL_MDL_UPDATE ) ; }
if ( ssIsSampleHit ( S , 2 , tid ) ) { ssCallAccelRunBlock ( S , 0 , 22 ,
SS_CALL_MDL_UPDATE ) ; } } static void mdlInitializeSizes ( SimStruct * S ) {
ssSetChecksumVal ( S , 0 , 3499046671U ) ; ssSetChecksumVal ( S , 1 ,
1974664447U ) ; ssSetChecksumVal ( S , 2 , 2651707700U ) ; ssSetChecksumVal (
S , 3 , 2918344686U ) ; { mxArray * slVerStructMat = NULL ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "7.8" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
D_Work_trainCOMPLETE_discrete_firction_motors ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( BlockIO_trainCOMPLETE_discrete_firction_motors ) ) {
ssSetErrorStatus ( S , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
Parameters_trainCOMPLETE_discrete_firction_motors ) ) { static char msg [ 256
] ; sprintf ( msg , "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & trainCOMPLETE_discrete_firction_motors_rtDefaultParameters ) ;
rt_InitInfAndNaN ( sizeof ( real_T ) ) ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
