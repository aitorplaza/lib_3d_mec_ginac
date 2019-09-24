#!/bin/bash
#Compiles main_file.cc and based on its output compiles and executes main_numeric

NEWTON_RAPHSON_TOLERANCE=1.0e-8
NR_TOL=-DNEWTON_RAPHSON_TOLERANCE=$NEWTON_RAPHSON_TOLERANCE

TRAPEZOIDAL_TOLERANCE=1.0e-8
TR_TOL=-DTRAPEZOIDAL_TOLERANCE=$TRAPEZOIDAL_TOLERANCE

EULER=-DEULER
TRAPEZOIDAL=-DTRAPEZOIDAL
Q=-DCOORD_DEP
Z=-DCOORD_IND

COMMON="lin_alg.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c param_vect_def.c param_vect_init.c unknowns_vect_def.c unknowns_vect_init.c inputs_vect_def.c inputs_vect_init.c Phi.c Beta.c write_state_file.c write_state_file_header.c step.c"

COORD_Q="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c Q.c MXdPhi_dqZero.c"

COORD_Z="Phi_z.c Phi_d.c Gamma.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c"


cp ./GENERATED_files_process_c_h/* .
cp ./MAIN_NUMERIC_lin_alg/* .
gcc $NR_TOL $TR_TOL $EULER $Q -O2 -c one_step_euler_q.c -lm 
gcc $NR_TOL $TR_TOL $TRAPEZOIDAL $Q -O2 -c one_step_trapezoidal_q.c -lm 
gcc $NR_TOL $TR_TOL $EULER $Z -O2 -c one_step_euler_z.c -lm 
gcc $NR_TOL $TR_TOL $EULER $TRAPEZOIDAL $Z -O2 -c one_step_trapezoidal_z.c -lm 

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
