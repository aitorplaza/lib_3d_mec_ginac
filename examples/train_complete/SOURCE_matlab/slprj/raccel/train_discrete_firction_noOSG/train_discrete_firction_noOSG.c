#include "__cf_train_discrete_firction_noOSG.h"
#include <math.h>
#include "train_discrete_firction_noOSG.h"
#include "train_discrete_firction_noOSG_private.h"
#include "train_discrete_firction_noOSG_dt.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
const boolean_T gbl_raccel_isMultitasking = 1 ;
#else
const boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
const boolean_T gbl_raccel_tid01eq = 1 ; const int_T gbl_raccel_NumST = 2 ;
const char_T * gbl_raccel_Version = "8.1 (R2011b) 08-Jul-2011" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#endif
} const char * gblSlvrJacPatternFileName =
 "slprj//raccel//train_discrete_firction_noOSG//train_discrete_firction_noOSG_Jpattern.mat"
; const int_T gblNumRootInportBlks = 0 ; const int_T gblNumModelInputs = 0 ;
extern rtInportTUtable * gblInportTUtables ; extern const char *
gblInportFileName ; const int_T gblInportDataTypeIdx [ ] = { - 1 } ; const
int_T gblInportDims [ ] = { - 1 } ; const int_T gblInportComplex [ ] = { - 1
} ; const int_T gblInportInterpoFlag [ ] = { - 1 } ; const int_T
gblInportContinuous [ ] = { - 1 } ;
#include "simstruc.h"
#include "fixedpoint.h"
BlockIO rtB ; D_Work rtDWork ; static SimStruct model_S ; SimStruct * const
rtS = & model_S ; void MdlInitialize ( void ) { rtDWork . mkcbw0czlr [ 0 ] =
rtP . UnitDelay1_X0 ; rtDWork . mkcbw0czlr [ 1 ] = rtP . UnitDelay1_X0 ;
rtDWork . mkcbw0czlr [ 2 ] = rtP . UnitDelay1_X0 ; rtDWork . mkcbw0czlr [ 3 ]
= rtP . UnitDelay1_X0 ; rtDWork . kmnd1a0hnp [ 0 ] = rtP . UnitDelay2_X0 ;
rtDWork . kmnd1a0hnp [ 1 ] = rtP . UnitDelay2_X0 ; rtDWork . kmnd1a0hnp [ 2 ]
= rtP . UnitDelay2_X0 ; rtDWork . kmnd1a0hnp [ 3 ] = rtP . UnitDelay2_X0 ; {
SimStruct * rts = ssGetSFunction ( rtS , 0 ) ; sfcnInitializeConditions ( rts
) ; if ( ssGetErrorStatus ( rts ) != ( NULL ) ) return ; } } void MdlStart (
void ) { { int_T dimensions [ 1 ] = { 90 } ; rtDWork . jdgmm4jsbu .
LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS )
, ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "state_series"
, SS_DOUBLE , 0 , 0 , 0 , 90 , 1 , dimensions , NO_LOGVALDIMS , ( NULL ) , (
NULL ) , 0 , 1 , 0.002 , 1 ) ; if ( rtDWork . jdgmm4jsbu . LoggedData == (
NULL ) ) return ; } { int_T dimensions [ 1 ] = { 45 } ; rtDWork . br001kkqdk
. LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS
) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "ddq_series"
, SS_DOUBLE , 0 , 0 , 0 , 45 , 1 , dimensions , NO_LOGVALDIMS , ( NULL ) , (
NULL ) , 0 , 1 , 0.002 , 1 ) ; if ( rtDWork . br001kkqdk . LoggedData == (
NULL ) ) return ; } { int_T dimensions [ 1 ] = { 20 } ; rtDWork . o0jsobo25z
. LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS
) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"Unknown_series" , SS_DOUBLE , 0 , 0 , 0 , 20 , 1 , dimensions ,
NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , 0.002 , 1 ) ; if ( rtDWork .
o0jsobo25z . LoggedData == ( NULL ) ) return ; } { int_T dimensions [ 1 ] = {
8 } ; rtDWork . nbtxt2yzu0 . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo (
rtS ) , ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( &
ssGetErrorStatus ( rtS ) ) , "Output_series" , SS_DOUBLE , 0 , 0 , 0 , 8 , 1
, dimensions , NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , 0.002 , 1 ) ; if
( rtDWork . nbtxt2yzu0 . LoggedData == ( NULL ) ) return ; } { int_T
dimensions [ 1 ] = { 4 } ; rtDWork . mij1qormyo . LoggedData =
rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) , ssGetTFinal
( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "N_Forces_series" ,
SS_DOUBLE , 0 , 0 , 0 , 4 , 1 , dimensions , NO_LOGVALDIMS , ( NULL ) , (
NULL ) , 0 , 1 , 0.002 , 1 ) ; if ( rtDWork . mij1qormyo . LoggedData == (
NULL ) ) return ; } { int_T dimensions [ 1 ] = { 4 } ; rtDWork . kh45rl25om .
LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS )
, ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "SLIP_series"
, SS_DOUBLE , 0 , 0 , 0 , 4 , 1 , dimensions , NO_LOGVALDIMS , ( NULL ) , (
NULL ) , 0 , 1 , 0.002 , 1 ) ; if ( rtDWork . kh45rl25om . LoggedData == (
NULL ) ) return ; } { int_T dimensions [ 1 ] = { 1 } ; rtDWork . icowkllmtt .
LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS )
, ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "t_series" ,
SS_DOUBLE , 0 , 0 , 0 , 1 , 1 , dimensions , NO_LOGVALDIMS , ( NULL ) , (
NULL ) , 0 , 1 , 0.002 , 1 ) ; if ( rtDWork . icowkllmtt . LoggedData == (
NULL ) ) return ; } MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { rtB
. mapxmkextn [ 0 ] = rtDWork . mkcbw0czlr [ 0 ] ; rtB . mapxmkextn [ 1 ] =
rtDWork . mkcbw0czlr [ 1 ] ; rtB . mapxmkextn [ 2 ] = rtDWork . mkcbw0czlr [
2 ] ; rtB . mapxmkextn [ 3 ] = rtDWork . mkcbw0czlr [ 3 ] ;
mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & rtB . mapxmkextn [ 0 ] , & rtP
. Raincondition_Value , & rtB . jzaqh5q4hs ) ;
mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & rtB . mapxmkextn [ 1 ] , & rtP
. Raincondition_Value , & rtB . lm4vg54kgl ) ;
mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & rtB . mapxmkextn [ 2 ] , & rtP
. Raincondition_Value , & rtB . hmgfwvrapw ) ;
mu_div_mod_vel_sliding_vel_Outputs_wrapper ( & rtB . mapxmkextn [ 3 ] , & rtP
. Raincondition_Value , & rtB . bipku3phqn ) ; rtB . ea35mwnxp3 [ 0 ] =
rtDWork . kmnd1a0hnp [ 0 ] ; rtB . ea35mwnxp3 [ 1 ] = rtDWork . kmnd1a0hnp [
1 ] ; rtB . ea35mwnxp3 [ 2 ] = rtDWork . kmnd1a0hnp [ 2 ] ; rtB . ea35mwnxp3
[ 3 ] = rtDWork . kmnd1a0hnp [ 3 ] ; { SimStruct * rts = ssGetSFunction ( rtS
, 0 ) ; sfcnOutputs ( rts , 0 ) ; } if ( ssGetLogOutput ( rtS ) ) {
rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDWork . jdgmm4jsbu .
LoggedData ) , rtB . o5g53wpycn , 0 ) ; } if ( ssGetLogOutput ( rtS ) ) {
rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDWork . br001kkqdk .
LoggedData ) , rtB . ja011sv0ld , 0 ) ; } if ( ssGetLogOutput ( rtS ) ) {
rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDWork . o0jsobo25z .
LoggedData ) , rtB . ehfze2n4rn , 0 ) ; } if ( ssGetLogOutput ( rtS ) ) {
rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDWork . nbtxt2yzu0 .
LoggedData ) , rtB . bcfr1o3fhj , 0 ) ; } if ( ssGetLogOutput ( rtS ) ) {
rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDWork . mij1qormyo .
LoggedData ) , & rtB . bcfr1o3fhj [ 4 ] , 0 ) ; } if ( ssGetLogOutput ( rtS )
) { rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDWork . kh45rl25om .
LoggedData ) , rtB . mapxmkextn , 0 ) ; } rtB . heaby2xbgq = ssGetT ( rtS ) ;
if ( ssGetLogOutput ( rtS ) ) { rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) (
rtDWork . icowkllmtt . LoggedData ) , & rtB . heaby2xbgq , 0 ) ; }
UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid ) { rtDWork .
mkcbw0czlr [ 0 ] = rtB . bcfr1o3fhj [ 0 ] ; rtDWork . mkcbw0czlr [ 1 ] = rtB
. bcfr1o3fhj [ 1 ] ; rtDWork . mkcbw0czlr [ 2 ] = rtB . bcfr1o3fhj [ 2 ] ;
rtDWork . mkcbw0czlr [ 3 ] = rtB . bcfr1o3fhj [ 3 ] ; rtDWork . kmnd1a0hnp [
0 ] = rtB . bcfr1o3fhj [ 4 ] ; rtDWork . kmnd1a0hnp [ 1 ] = rtB . bcfr1o3fhj
[ 5 ] ; rtDWork . kmnd1a0hnp [ 2 ] = rtB . bcfr1o3fhj [ 6 ] ; rtDWork .
kmnd1a0hnp [ 3 ] = rtB . bcfr1o3fhj [ 7 ] ; { SimStruct * rts =
ssGetSFunction ( rtS , 0 ) ; sfcnUpdate ( rts , 0 ) ; if ( ssGetErrorStatus (
rts ) != ( NULL ) ) return ; } UNUSED_PARAMETER ( tid ) ; } void MdlTerminate
( void ) { { SimStruct * rts = ssGetSFunction ( rtS , 0 ) ; sfcnTerminate (
rts ) ; } } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 0 )
; ssSetNumY ( rtS , 0 ) ; ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough (
rtS , 0 ) ; ssSetNumSampleTimes ( rtS , 2 ) ; ssSetNumBlocks ( rtS , 26 ) ;
ssSetNumBlockIO ( rtS , 11 ) ; ssSetNumBlockParams ( rtS , 165 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.002 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 0.0 ) ; } void raccel_set_checksum ( SimStruct *
rtS ) { ssSetChecksumVal ( rtS , 0 , 673410750U ) ; ssSetChecksumVal ( rtS ,
1 , 3614289188U ) ; ssSetChecksumVal ( rtS , 2 , 78516600U ) ;
ssSetChecksumVal ( rtS , 3 , 3854323133U ) ; } SimStruct *
raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo ; ( void )
memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void ) memset ( (
char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ; ssSetMdlInfoPtr (
rtS , & mdlInfo ) ; { static time_T mdlPeriod [ NSAMPLE_TIMES ] ; static
time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T mdlTaskTimes [
NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ; static int_T
mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T mdlTNextWasAdjustedPtr [
NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits [ NSAMPLE_TIMES *
NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [ NSAMPLE_TIMES ] ; {
int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) { mdlPeriod [ i ] = 0.0 ;
mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ; mdlTsMap [ i ] = i ;
mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS , & mdlPeriod [ 0 ] )
; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr (
rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , & mdlTaskTimes [ 0 ] ) ;
ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ; ssSetTNextWasAdjustedPtr
( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ; ssSetPerTaskSampleHitsPtr ( rtS ,
& mdlPerTaskSampleHits [ 0 ] ) ; ssSetTimeOfNextSampleHitPtr ( rtS , &
mdlTimeOfNextSampleHit [ 0 ] ) ; } ssSetSolverMode ( rtS ,
SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS , ( ( void * ) & rtB ) ) ;
( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof ( BlockIO ) ) ; }
ssSetDefaultParam ( rtS , ( real_T * ) & rtP ) ; { void * dwork = ( void * )
& rtDWork ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork , 0 ,
sizeof ( D_Work ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 14 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . B = & rtBTransTable ; dtInfo . P = & rtPTransTable ; } ssSetRootSS (
rtS , rtS ) ; ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ;
ssSetModelName ( rtS , "train_discrete_firction_noOSG" ) ; ssSetPath ( rtS ,
"train_discrete_firction_noOSG" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal (
rtS , 10.0 ) ; ssSetStepSize ( rtS , 0.002 ) ; ssSetFixedStepSize ( rtS ,
0.002 ) ; { static RTWLogInfo rt_DataLoggingInfo ; ssSetRTWLogInfo ( rtS , &
rt_DataLoggingInfo ) ; } { { static int_T rt_LoggedStateWidths [ ] = { 4 , 4
, 90 } ; static int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 } ;
static int_T rt_LoggedStateDimensions [ ] = { 4 , 4 , 90 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ;
static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 } ; static const
char_T * rt_LoggedStateLabels [ ] = { "DSTATE" , "DSTATE" , "DSTATE" } ;
static const char_T * rt_LoggedStateBlockNames [ ] = {
"train_discrete_firction_noOSG/Unit Delay1" ,
"train_discrete_firction_noOSG/Unit Delay2" ,
"train_discrete_firction_noOSG/Moldel" } ; static const char_T *
rt_LoggedStateNames [ ] = { "" , "" , "" } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 } ; static RTWLogDataTypeConvert
rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 ,
1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } ,
{ 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 3 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , { rt_LoggedStateLabels } , ( NULL )
, ( NULL ) , ( NULL ) , { rt_LoggedStateBlockNames } , { rt_LoggedStateNames
} , rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 3 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) rtDWork . mkcbw0czlr ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) rtDWork . kmnd1a0hnp ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) rtDWork . id4xzvptbk ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "tmp_raccel_xout" ) ; rtliSetLogXFinal (
ssGetRTWLogInfo ( rtS ) , "xFinal" ) ; rtliSetSigLog ( ssGetRTWLogInfo ( rtS
) , "" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 1000 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo (
rtS ) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
ssSolverInfo slvrInfo ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "FixedStepDiscrete" ) ; ssSetVariableStepSolver ( rtS
, 0 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ; ssSetModelUpdate ( rtS
, MdlUpdate ) ; ssSetTNextTid ( rtS , INT_MIN ) ; ssSetTNext ( rtS ,
rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ; ssSetNumNonsampledZCs ( rtS ,
0 ) ; } ssSetChecksumVal ( rtS , 0 , 673410750U ) ; ssSetChecksumVal ( rtS ,
1 , 3614289188U ) ; ssSetChecksumVal ( rtS , 2 , 78516600U ) ;
ssSetChecksumVal ( rtS , 3 , 3854323133U ) ; { static const sysRanDType
rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo
; static const sysRanDType * systemRan [ 1 ] ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ;
rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } ssSetNumSFunctions ( rtS , 1 ) ; { static SimStruct
childSFunctions [ 1 ] ; static SimStruct * childSFunctionPtrs [ 1 ] ; ( void
) memset ( ( void * ) & childSFunctions [ 0 ] , 0 , sizeof ( childSFunctions
) ) ; ssSetSFunctions ( rtS , & childSFunctionPtrs [ 0 ] ) ; ssSetSFunction (
rtS , 0 , & childSFunctions [ 0 ] ) ; { SimStruct * rts = ssGetSFunction (
rtS , 0 ) ; static time_T sfcnPeriod [ 1 ] ; static time_T sfcnOffset [ 1 ] ;
static int_T sfcnTsMap [ 1 ] ; ( void ) memset ( ( void * ) sfcnPeriod , 0 ,
sizeof ( time_T ) * 1 ) ; ( void ) memset ( ( void * ) sfcnOffset , 0 ,
sizeof ( time_T ) * 1 ) ; ssSetSampleTimePtr ( rts , & sfcnPeriod [ 0 ] ) ;
ssSetOffsetTimePtr ( rts , & sfcnOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr (
rts , sfcnTsMap ) ; ssSetMdlInfoPtr ( rts , ssGetMdlInfoPtr ( rtS ) ) ; {
static struct _ssSFcnModelMethods2 methods2 ; ssSetModelMethods2 ( rts , &
methods2 ) ; } { static struct _ssSFcnModelMethods3 methods3 ;
ssSetModelMethods3 ( rts , & methods3 ) ; } { static struct _ssStatesInfo2
statesInfo2 ; ssSetStatesInfo2 ( rts , & statesInfo2 ) ; } { static struct
_ssPortInputs inputPortInfo [ 1 ] ; _ssSetNumInputPorts ( rts , 1 ) ;
ssSetPortInfoForInputs ( rts , & inputPortInfo [ 0 ] ) ; { static real_T
const * sfcnUPtrs [ 10 ] ; sfcnUPtrs [ 0 ] = & rtP . FRONTMOTOR_Value ;
sfcnUPtrs [ 1 ] = & rtP . REARMOTOR_Value ; sfcnUPtrs [ 2 ] = & rtB .
jzaqh5q4hs ; sfcnUPtrs [ 3 ] = & rtB . lm4vg54kgl ; sfcnUPtrs [ 4 ] = & rtB .
hmgfwvrapw ; sfcnUPtrs [ 5 ] = & rtB . bipku3phqn ; sfcnUPtrs [ 6 ] = & rtB .
ea35mwnxp3 [ 0 ] ; sfcnUPtrs [ 7 ] = & rtB . ea35mwnxp3 [ 1 ] ; sfcnUPtrs [ 8
] = & rtB . ea35mwnxp3 [ 2 ] ; sfcnUPtrs [ 9 ] = & rtB . ea35mwnxp3 [ 3 ] ;
ssSetInputPortSignalPtrs ( rts , 0 , ( InputPtrsType ) & sfcnUPtrs [ 0 ] ) ;
_ssSetInputPortNumDimensions ( rts , 0 , 1 ) ; ssSetInputPortWidth ( rts , 0
, 10 ) ; } } { static struct _ssPortOutputs outputPortInfo [ 4 ] ;
ssSetPortInfoForOutputs ( rts , & outputPortInfo [ 0 ] ) ;
_ssSetNumOutputPorts ( rts , 4 ) ; { _ssSetOutputPortNumDimensions ( rts , 0
, 1 ) ; ssSetOutputPortWidth ( rts , 0 , 90 ) ; ssSetOutputPortSignal ( rts ,
0 , ( ( real_T * ) rtB . o5g53wpycn ) ) ; } { _ssSetOutputPortNumDimensions (
rts , 1 , 1 ) ; ssSetOutputPortWidth ( rts , 1 , 45 ) ; ssSetOutputPortSignal
( rts , 1 , ( ( real_T * ) rtB . ja011sv0ld ) ) ; } {
_ssSetOutputPortNumDimensions ( rts , 2 , 1 ) ; ssSetOutputPortWidth ( rts ,
2 , 20 ) ; ssSetOutputPortSignal ( rts , 2 , ( ( real_T * ) rtB . ehfze2n4rn
) ) ; } { _ssSetOutputPortNumDimensions ( rts , 3 , 1 ) ;
ssSetOutputPortWidth ( rts , 3 , 8 ) ; ssSetOutputPortSignal ( rts , 3 , ( (
real_T * ) rtB . bcfr1o3fhj ) ) ; } } ssSetDiscStates ( rts , ( real_T * ) &
rtDWork . id4xzvptbk [ 0 ] ) ; ssSetModelName ( rts , "Moldel" ) ; ssSetPath
( rts , "train_discrete_firction_noOSG/Moldel" ) ; if ( ssGetRTModel ( rtS )
== ( NULL ) ) { ssSetParentSS ( rts , rtS ) ; ssSetRootSS ( rts , ssGetRootSS
( rtS ) ) ; } else { ssSetRTModel ( rts , ssGetRTModel ( rtS ) ) ;
ssSetParentSS ( rts , ( NULL ) ) ; ssSetRootSS ( rts , rts ) ; } ssSetVersion
( rts , SIMSTRUCT_VERSION_LEVEL2 ) ; { static mxArray * sfcnParams [ 4 ] ;
ssSetSFcnParamsCount ( rts , 4 ) ; ssSetSFcnParamsPtr ( rts , & sfcnParams [
0 ] ) ; ssSetSFcnParam ( rts , 0 , ( mxArray * ) rtP . Moldel_P1_Size ) ;
ssSetSFcnParam ( rts , 1 , ( mxArray * ) rtP . Moldel_P2_Size ) ;
ssSetSFcnParam ( rts , 2 , ( mxArray * ) rtP . Moldel_P3_Size ) ;
ssSetSFcnParam ( rts , 3 , ( mxArray * ) rtP . Moldel_P4_Size ) ; } { static
struct _ssDWorkRecord dWorkRecord [ 1 ] ; static struct _ssDWorkAuxRecord
dWorkAuxRecord [ 1 ] ; ssSetSFcnDWork ( rts , dWorkRecord ) ;
ssSetSFcnDWorkAux ( rts , dWorkAuxRecord ) ; _ssSetNumDWork ( rts , 1 ) ;
ssSetDWorkWidth ( rts , 0 , 90 ) ; ssSetDWorkDataType ( rts , 0 , SS_DOUBLE )
; ssSetDWorkComplexSignal ( rts , 0 , 0 ) ; ssSetDWorkUsedAsDState ( rts , 0
, 1 ) ; ssSetDWork ( rts , 0 , & rtDWork . id4xzvptbk [ 0 ] ) ; }
c_s_func_linalg_discrete ( rts ) ; sfcnInitializeSizes ( rts ) ;
sfcnInitializeSampleTimes ( rts ) ; ssSetSampleTime ( rts , 0 , 0.002 ) ;
ssSetOffsetTime ( rts , 0 , 0.0 ) ; sfcnTsMap [ 0 ] = 1 ;
ssSetNumNonsampledZCs ( rts , 0 ) ; _ssSetInputPortConnected ( rts , 0 , 1 )
; _ssSetOutputPortConnected ( rts , 0 , 1 ) ; _ssSetOutputPortConnected ( rts
, 1 , 1 ) ; _ssSetOutputPortConnected ( rts , 2 , 1 ) ;
_ssSetOutputPortConnected ( rts , 3 , 1 ) ; _ssSetOutputPortBeingMerged ( rts
, 0 , 0 ) ; _ssSetOutputPortBeingMerged ( rts , 1 , 0 ) ;
_ssSetOutputPortBeingMerged ( rts , 2 , 0 ) ; _ssSetOutputPortBeingMerged (
rts , 3 , 0 ) ; ssSetInputPortBufferDstPort ( rts , 0 , - 1 ) ; } } return
rtS ; }
