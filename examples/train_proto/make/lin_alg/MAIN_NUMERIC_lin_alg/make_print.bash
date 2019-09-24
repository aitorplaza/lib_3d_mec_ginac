#!/bin/bash
#Compiles main_file.cc and based on its output compiles and executes main_numeric

NEWTON_RAPHSON_TOLERANCE=1.0e-8
NR_TOL=-DNEWTON_RAPHSON_TOLERANCE=$NEWTON_RAPHSON_TOLERANCE

TRAPEZOIDAL_TOLERANCE=1.0e-8
TR_TOL=-DTRAPEZOIDAL_TOLERANCE=$TRAPEZOIDAL_TOLERANCE

ALFA=1.0e+12
AUX_ALFA=-DALFA=$ALFA

COMMON="lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c write_data_file.c step.c"
COORD_Q="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c"
DYN_DDL="Qgamma.c MXdPhi_dqZero.c"
DYN_DDQ="M.c Q.c Gamma.c"
I3AL_Q="M.c Q.c Q_q.c Q_dq.c"
COORD_Z="Phi_z.c Phi_d.c Gamma.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c"
MAIN=main_numeric_lin_alg_print

cp ./GENERATED_files_process_c_h/* .
cp ./MAIN_NUMERIC_lin_alg/* .

## INTEGRADOR ##
EULER=-DEULER
TRAPEZOIDAL=-DTRAPEZOIDAL
I3AL=-DI3AL

## PROYECCION ##
Q=-DCOORD_DEP
Z=-DCOORD_IND

## ECUACIONES DINAMICAS - INCOGNITAS ##
DDL=-DDDL # FULL unknowns vector ===> ddq+lambda in 1 vector
DDQ=-DDDQ # SPLIT unknowns vector ===> lambda in 1 vector and ddq in another vector
DDZ=-DDDZ # Dinamics eq only for indep. accel.

## METODO DE RESOLUCION DE LOS SISTEMAS LINEALES DE ECUACIONES ##
INV=-DINV #Uses Gauss-Jordan (Forward elimination Backward substitution with column pivoting) to compute all the inverse 
TRI=-DTRI #Uses Choleski for symmetric definite positive and LDL for symmetric semi definite positive 

TIME=TIME_ON
#AUX_TIME=-D$TIME

NR_ITER=1
AUX_NR_ITER=-DNR_ITER=$NR_ITER

integration=0.001
delta_t=0.001

echo "";
name="state_lin_alg_euler_q_ddl_inv_print.dat"
#gcc  $EULER $Z $INV $NR_TOL $TR_TOL $AUX_NR_ITER $AUX_TIME -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z one_step_euler_z.c -lm
gcc  $EULER $Z $INV $NR_TOL $TR_TOL $AUX_NR_ITER $AUX_TIME -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z $DYN_DDL $I3AL_Q Phi_q.c PhiInit_q.c Qz_z.c Qd_d.c Qz_dz.c Qd_dd.c one_step_euler_z.c -lm
#gcc  $EULER $Q $INV $NR_TOL $TR_TOL $AUX_NR_ITER $AUX_TIME -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL $I3AL_Q Qz_z.c Qd_d.c Qz_dz.c Qd_dd.c one_step_euler_q.c -lm

./$MAIN $integration $delta_t $name

rm -f -r $MAIN 

rm -f -r *_def.* *_init.* *_file.c *_header.c
rm -f -r gen_*.* time*.* param.* unknowns.* inputs.* data*.*

rm -f -r Phi.* Beta.* Phi_q.* dPhi_dq.* Qgamma.* MXdPhi_dqZero.*
rm -f -r Phi.* Beta.* Phi_z.* Phi_d.* Gamma.* Qz*.* Qd*.* Mzz*.* Mzd*.* Mdd*.*
rm -f -r PhiInit.* PhiInit_q.* BetaInit.* dPhiInit_dq.*

rm -f -r Q*.* M.* Gamma.*
rm -f -r defines.h Energy.* Output.* dPhi*.* 
rm -f -r *_maple_include.c

./aux_clear_common.bash


date

