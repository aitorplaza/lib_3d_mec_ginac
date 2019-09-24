#!/bin/bash
#Compiles main_numeric_lapack 

INTEGRATOR=$1
integration=$2
delta_t=$3

if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]; then echo "This program needs 3 parameters: INTEGRATOR (EULER or TRAPEZOIDAL), Integration time and delta_t "; exit ; fi

if [[ $INTEGRATOR != "EULER" ]] && [[ $INTEGRATOR != "TRAPEZOIDAL" ]]; then echo "Chosee integration method: EULER or TRAPEZOIDAL"; exit ; fi

cp ./GENERATED_files_process_c_h/* .
cp ./common/files_c_h/lapack_and_osg/* .
cp ./common/files_c_h/common_c/* .

#./common/files_bash/aux_compile_main.bash
COMMON="time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c write_data_file.c"
COORD_Q="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c"
MAIN=main_numeric_lapack

Q=-DCOORD_DEP

gcc  $Q -D$INTEGRATOR -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q newton_raphson_min_norm.c -lm -lblas -llapack

./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash

echo "Running main_numeric"
./$MAIN $integration $delta_t state.dat
mv $MAIN ./GENERATED_files_bin

sed '1d' state.dat > state_woh.dat
./common/files_bash/aux_graphics.bash
mv state.dat ./GENERATED_files_dat/
mv state_woh.dat ./GENERATED_files_matlab/

./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash
