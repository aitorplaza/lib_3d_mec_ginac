#!/bin/bash

if [ -z $1 ] ; then echo "This program needs 1 parameters: INTEGRATOR (EULER or TRAPEZOIDAL)"; exit ; fi
if [[ $1 != "EULER" ]] && [[ $1 != "TRAPEZOIDAL" ]]; then echo "Chosee integration method: EULER or TRAPEZOIDAL"; exit ; fi

cp ./GENERATED_files_process_c_h/* .
cp ./common/files_c_h/lapack_and_osg/* .
cp ./common/files_c_h/common_c/* .

cp ./GENERATED_files_osg/cpp/* .
cp ./GENERATED_files_osg/h/* .

#./common/files_bash/aux_compile_main.bash

COMMON="time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c write_data_file.c"
COORD_Q="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c"
MAIN=main_numeric_lapack_osg

Q=-DCOORD_DEP

gcc -O2 -c read_config_file.c newton_raphson_min_norm.c $COMMON $COORD_Q 
g++ -c solids_homogeneous_matrix.cpp osg_read_file.cpp osg_root.cpp osg_state.cpp

g++ $Q -D$1 -o $MAIN $MAIN.cc time.o gen_coord.o gen_vel.o gen_accel.o param.o unknowns.o inputs.o Phi.o Beta.o Gamma.o write_data_file.o PhiInit.o PhiInit_q.o dPhiInit_dq.o BetaInit.o Phi_q.o dPhi_dq.o Qgamma.o MXdPhi_dqZero.o read_config_file.o newton_raphson_min_norm.o solids_homogeneous_matrix.o osg_read_file.o osg_root.o osg_state.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack

./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash

cp ./solids/*.* ./GENERATED_OSG_bin/solids/
cp ./common/files_osg/axes.osg ./GENERATED_OSG_bin
mv $MAIN ./GENERATED_OSG_bin
