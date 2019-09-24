#include "__cf_train_discrete_firction_noOSG.h"
#include <math.h>
#include "train_discrete_firction_noOSG_acc.h"
#include "train_discrete_firction_noOSG_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
static void mdlOutputs ( SimStruct * S , int_T tid ) { ( (
BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) ) -> B_0_0_0 =
( ( Parameters_train_discrete_firction_noOSG * ) ssGetDefaultParam ( S ) ) ->
P_0 ; ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) ) ->
B_0_1_0 = ( ( Parameters_train_discrete_firction_noOSG * ) ssGetDefaultParam
( S ) ) -> P_1 ; ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO
( S ) ) -> B_0_2_0 [ 0 ] = ( ( D_Work_train_discrete_firction_noOSG * )
ssGetRootDWork ( S ) ) -> UnitDelay1_DSTATE [ 0 ] ; ( (
BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) ) -> B_0_2_0 [
1 ] = ( ( D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE [ 1 ] ; ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_2_0 [ 2 ] = ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE [ 2 ] ; ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_2_0 [ 3 ] = ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE [ 3 ] ; ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 = ( (
Parameters_train_discrete_firction_noOSG * ) ssGetDefaultParam ( S ) ) -> P_3
; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) ) -> B_0_2_0 [
0 ] , & ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) )
-> B_0_3_0 , & ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO (
S ) ) -> B_0_4_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) ) -> B_0_2_0 [
1 ] , & ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) )
-> B_0_3_0 , & ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO (
S ) ) -> B_0_5_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) ) -> B_0_2_0 [
2 ] , & ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) )
-> B_0_3_0 , & ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO (
S ) ) -> B_0_6_0 ) ; mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & ( (
BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) ) -> B_0_2_0 [
3 ] , & ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO ( S ) )
-> B_0_3_0 , & ( ( BlockIO_train_discrete_firction_noOSG * ) _ssGetBlockIO (
S ) ) -> B_0_7_0 ) ; ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_8_0 [ 0 ] = ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ 0 ] ; ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_8_0 [ 1 ] = ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ 1 ] ; ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_8_0 [ 2 ] = ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ 2 ] ; ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_8_0 [ 3 ] = ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ 3 ] ; ssCallAccelRunBlock ( S , 0 , 9 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 10 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 11 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 12 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 13 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 14 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 15 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 16 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 17 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 18 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 19 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 20 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 21 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 22 ,
SS_CALL_MDL_OUTPUTS ) ; ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_23_0 = ssGetT ( S ) ; ssCallAccelRunBlock ( S ,
0 , 24 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 25 ,
SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE [ 0 ] = ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_9_3 [ 0 ] ; ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE [ 1 ] = ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_9_3 [ 1 ] ; ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE [ 2 ] = ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_9_3 [ 2 ] ; ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay1_DSTATE [ 3 ] = ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_9_3 [ 3 ] ; ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ 0 ] = ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_9_3 [ 4 ] ; ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ 1 ] = ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_9_3 [ 5 ] ; ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ 2 ] = ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_9_3 [ 6 ] ; ( (
D_Work_train_discrete_firction_noOSG * ) ssGetRootDWork ( S ) ) ->
UnitDelay2_DSTATE [ 3 ] = ( ( BlockIO_train_discrete_firction_noOSG * )
_ssGetBlockIO ( S ) ) -> B_0_9_3 [ 7 ] ; ssCallAccelRunBlock ( S , 0 , 9 ,
SS_CALL_MDL_UPDATE ) ; UNUSED_PARAMETER ( tid ) ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 1268295166U
) ; ssSetChecksumVal ( S , 1 , 3251101985U ) ; ssSetChecksumVal ( S , 2 ,
3384580665U ) ; ssSetChecksumVal ( S , 3 , 1566880625U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "7.8" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( D_Work_train_discrete_firction_noOSG ) ) { ssSetErrorStatus (
S , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( BlockIO_train_discrete_firction_noOSG ) ) { ssSetErrorStatus (
S , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
Parameters_train_discrete_firction_noOSG ) ) { static char msg [ 256 ] ;
sprintf ( msg , "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & train_discrete_firction_noOSG_rtDefaultParameters ) ;
rt_InitInfAndNaN ( sizeof ( real_T ) ) ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
