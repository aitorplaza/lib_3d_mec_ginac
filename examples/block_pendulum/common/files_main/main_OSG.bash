#!/bin/bash

cp ./GENERATED_files_process_c_h/* .
cp ./common/files_c_h/osg/* .
cp ./common/files_c_h/common_c/* .
cp ./GENERATED_files_osg/cpp/* .
cp ./GENERATED_files_osg/h/* .



COMMON="gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c "
COMMON_o="gen_coord.o gen_vel.o gen_accel.o param.o unknowns.o inputs.o "

OSG="solids_homogeneous_matrix.cpp osg_read_file.cpp osg_root.cpp osg_state.cpp"
OSG_o="solids_homogeneous_matrix.o osg_read_file.o osg_root.o osg_state.o"

###################################################################################################
MAIN=main_model_osg
echo "";
echo "Compiling OpenSceneGraph model without integrator";

gcc -DCOORD_DEP -DDDL -O2 -c read_config_file.c $COMMON 
g++ -c $OSG
g++ -DCOORD_DEP -DDDL -DTRAPEZOIDAL -DLAPACK -o $MAIN $MAIN.cc $COMMON_o  $OSG_o read_config_file.o  -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText



# Clean and erase
./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash

###################################################################################################
# Organize
cp ./solids/*.* ./GENERATED_OSG_bin/solids/
cp ./common/files_osg/axes.osg ./GENERATED_OSG_bin
mv $MAIN ./GENERATED_OSG_bin

