#include "__cf_wheelset_continuous.h"
#include <math.h>
#include "wheelset_continuous_acc.h"
#include "wheelset_continuous_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
void wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Init (
SimStruct * const S ) { ssCallAccelRunBlock ( S , 0 , 0 ,
SS_CALL_MDL_INITIALIZE_CONDITIONS ) ; } void
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Deriv (
SimStruct * const S ) { ssCallAccelRunBlock ( S , 0 , 0 ,
SS_CALL_MDL_DERIVATIVES ) ; } void
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Projection (
SimStruct * const S ) { ssCallAccelRunBlock ( S , 0 , 0 ,
SS_CALL_MDL_PROJECTION ) ; } void
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( SimStruct *
const S ) { ssCallAccelRunBlock ( S , 1 , 4 , SS_CALL_MDL_OUTPUTS ) ; } void
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Term (
SimStruct * const S ) { { SimStruct * rts = ssGetSFunction ( S , 0 ) ;
sfcnTerminate ( rts ) ; } } static void mdlOutputs ( SimStruct * S , int_T
tid ) { ( ( BlockIO_wheelset_continuous * ) _ssGetBlockIO ( S ) ) -> B_1_0_0
= ssGetT ( S ) ; ssCallAccelRunBlock ( S , 1 , 1 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 2 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { ( ( BlockIO_wheelset_continuous * ) _ssGetBlockIO ( S ) )
-> B_1_3_0 = ( ( Parameters_wheelset_continuous * ) ssGetDefaultParam ( S ) )
-> P_6 ; } wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 (
S ) ; ssCallAccelRunBlock ( S , 1 , 5 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { memcpy ( ( void * ) ( & ( (
BlockIO_wheelset_continuous * ) _ssGetBlockIO ( S ) ) -> B_1_6_0 [ 0 ] ) , (
void * ) ( & ( ( BlockIO_wheelset_continuous * ) _ssGetBlockIO ( S ) ) ->
B_0_0_0 [ 0 ] ) , 28U * sizeof ( real_T ) ) ; ssCallAccelRunBlock ( S , 1 , 7
, SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 1 , 8 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 9 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 1 , 10 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 11 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 12 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 13 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 14 , SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { if ( ssIsSampleHit ( S
, 2 , 0 ) ) { ssCallAccelRunBlock ( S , 1 , 7 , SS_CALL_MDL_UPDATE ) ; }
UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) {
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Deriv ( S ) ;
}
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) {
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Projection (
S ) ; } static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal (
S , 0 , 456534982U ) ; ssSetChecksumVal ( S , 1 , 1404603506U ) ;
ssSetChecksumVal ( S , 2 , 3407318833U ) ; ssSetChecksumVal ( S , 3 ,
3800598216U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat =
mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "7.8" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
D_Work_wheelset_continuous ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( BlockIO_wheelset_continuous ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
Parameters_wheelset_continuous ) ) { static char msg [ 256 ] ; sprintf ( msg
, "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & wheelset_continuous_rtDefaultParameters ) ; rt_InitInfAndNaN (
sizeof ( real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S
) { } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
