#!/bin/bash
###################################################################################################
OPTION=$1
if [ -z $1 ] ; then 
echo " "
echo "COMPILATION OPTIONS"
echo " "
echo "LAPACK library:"
echo " 1: Lapack library and EULER integrator"
echo " 2: Lapack library and TRAPEZOIDAL integrator"
echo "------------------------------------------------------------------------------------"
echo " "
echo "LIN_ALG library:"
echo " 3: Q EULER with Qgamma and MXdPhi_dqZero matrices with INVERSE"
echo " 4: Q EULER with Qgamma and MXdPhi_dqZero matrices with Cholesky decomposition"
echo " 5: Q EULER with Q and M matrices with INVERSE"
echo " 6: Q EULER with Q and M matrices with Cholesky decomposition"
echo " "
echo " 7: Q TRAPEZOIDAL with Qgamma and MXdPhi_dqZero matrices with INVERSE"
echo " 8: Q TRAPEZOIDAL with Qgamma and MXdPhi_dqZero matrices with Cholesky decomposition"
echo " 9: Q TRAPEZOIDAL with Q and M matrices with INVERSE"
echo "10: Q TRAPEZOIDAL with Q and M matrices with Cholesky decomposition"
echo " "
echo "11: Q index-3 augmented Lagrangian DDL with INVERSE"
echo "12: Q index-3 augmented Lagrangian DDL with LU decomposition"
echo " "
echo "13: Z EULER with INVERSE"
echo "14: Z EULER Cholesky decomposition"
echo " "
echo "15: Z TRAPEZOIDAL with INVERSE"
echo "16: Z TRAPEZOIDAL with Cholesky decomposition"
echo " "
echo "17: Z index-3 augmented Lagrangian DDL with INVERSE"
echo "18: Z index-3 augmented Lagrangian DDL with LU decomposition"
echo "------------------------------------------------------------------------------------"
echo -n "Choose one of the options:  "
read OPTION
if [ -z $OPTION ] ; then exit; fi
fi
###################################################################################################
cp ./GENERATED_files_process_c_h/* .

cp ./common/files_c_h/osg/* .
cp ./common/files_c_h/lapack/* .
cp ./common/files_c_h/lin_alg/* .
cp ./common/files_c_h/common_c/* .

cp ./GENERATED_files_osg/cpp/* .
cp ./GENERATED_files_osg/h/* .

###################################################################################################
## PROYECCION ##
Q=-DCOORD_DEP
Z=-DCOORD_IND
###################################################################################################
 
COMMON="time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c write_data_file.c step.c"
COMMON_o="time.o gen_coord.o gen_vel.o gen_accel.o param.o unknowns.o inputs.o Phi.o Beta.o Gamma.o write_data_file.o step.o"

COORD_Q="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c"
COORD_Q_o="PhiInit.o PhiInit_q.o dPhiInit_dq.o BetaInit.o Phi_q.o dPhi_dq.o"

DYN_DDL="Qgamma.c MXdPhi_dqZero.c"
DYN_DDL_o="Qgamma.o MXdPhi_dqZero.o"

DYN_DDQ="M.c Q.c"
DYN_DDQ_o="M.o Q.o"

COORD_Z="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c"
COORD_Z_o="PhiInit.o PhiInit_q.o dPhiInit_dq.o BetaInit.o Phi_q.o dPhi_dq.o Phi_z.o Phi_d.o Mzz.o Mzd.o Mdd.o Qz.o Qd.o"

L_A="lin_alg.c Initial_position_velocity.c"
L_A_o="lin_alg.o Initial_position_velocity.o"

LA_Q=""
LA_Q_o=""

LA_Z=""
LA_Z_o=""

I3AL_Q="Q_q.c Q_dq.c M.c Q.c"
I3AL_Q_o="Q_q.o Q_dq.o M.o Q.o"

I3AL_Z="Qz_z.c Qz_dz.c"
I3AL_Z_o="Qz_z.o Qz_dz.o"

OSG="solids_homogeneous_matrix.cpp osg_read_file.cpp osg_root.cpp osg_state.cpp"
OSG_o="solids_homogeneous_matrix.o osg_read_file.o osg_root.o osg_state.o"

###################################################################################################
MAIN=main_numeric_osg
echo "";
############
## LAPACK ##
###################################################################################################

if [ "$OPTION" == 1 ];  then
echo "Compiling OpenSceneGraph model with Lapack and EULER integrator";
gcc -DCOORD_DEP -DDDL -O2 -c read_config_file.c newton_raphson_min_norm.c $COMMON $COORD_Q $DYN_DDL
g++ -c $OSG
g++ -DCOORD_DEP -DDDL -DEULER -DLAPACK -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $OSG_o $DYN_DDL_o read_config_file.o newton_raphson_min_norm.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi

if [ "$OPTION" == 2 ];  then
echo "Compiling OpenSceneGraph model with Lapack and TRAPEZOIDAL integrator";
gcc -DCOORD_DEP -DDDL -O2 -c read_config_file.c newton_raphson_min_norm.c $COMMON $COORD_Q $DYN_DDL
g++ -c $OSG
g++ -DCOORD_DEP -DDDL -DTRAPEZOIDAL -DLAPACK -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $OSG_o $DYN_DDL_o read_config_file.o newton_raphson_min_norm.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi

#############
## LIN_ALG ##
#####################################################################################################################################################
NEWTON_RAPHSON_TOLERANCE=1.0e-8
NR_TOL=-DNEWTON_RAPHSON_TOLERANCE=$NEWTON_RAPHSON_TOLERANCE
TRAPEZOIDAL_TOLERANCE=1.0e-8
TR_TOL=-DTRAPEZOIDAL_TOLERANCE=$TRAPEZOIDAL_TOLERANCE
INVERSE_TOLERANCE=1.0e-12
INV_TOL=-DINV_TOL=$INVERSE_TOLERANCE
TOL=" $NR_TOL $TR_TOL $INV_TOL "

ALFA=1.0e+12


if [ "$OPTION" == 3 ];  then 
echo "Q EULER with Qgamma and MXdPhi_dqZero matrices with INVERSE";
gcc -DEULER -DCOORD_DEP -DDDL -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $DYN_DDL one_step_euler_q.c
g++ -c $OSG
gcc  -DEULER -DCOORD_DEP -DDDL -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $LA_Q_o $OSG_o read_config_file.c one_step_euler_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 4 ];  then 
echo "Q EULER with Qgamma and MXdPhi_dqZero matrices with Cholesky decomposition";
gcc -DEULER -DCOORD_DEP -DDDL -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $DYN_DDL one_step_euler_q.c
g++ -c $OSG
gcc  -DEULER -DCOORD_DEP -DDDL -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $LA_Q_o $OSG_o read_config_file.c one_step_euler_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 5 ];  then 
echo "Q EULER with Q and M matrices with INVERSE";
gcc -DEULER -DCOORD_DEP -DDDQ -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $DYN_DDQ one_step_euler_q.c
g++ -c $OSG
gcc  -DEULER -DCOORD_DEP -DDDQ -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $LA_Q_o $OSG_o read_config_file.c one_step_euler_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 6 ];  then 
echo "Q EULER with Q and M matrices with Cholesky decomposition";
gcc -DEULER -DCOORD_DEP -DDDQ -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $DYN_DDQ one_step_euler_q.c
g++ -c $OSG
gcc  -DEULER -DCOORD_DEP -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $LA_Q_o $OSG_o read_config_file.c one_step_euler_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
#####################################################################################################################################################
if [ "$OPTION" == 7 ];  then 
echo "Q TRAPEZOIDAL with Qgamma and MXdPhi_dqZero matrices with INVERSE";
gcc -DTRAPEZOIDAL -DCOORD_DEP -DDDL -DINV $TOL -O2 -funroll-loops -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $DYN_DDL one_step_trapezoidal_q.c
g++ -c -funroll-loops $OSG
gcc  -DTRAPEZOIDAL -DCOORD_DEP -DDDL -DINV $TOL -DLIN_ALG -O2 -funroll-loops -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $LA_Q_o $OSG_o read_config_file.c one_step_trapezoidal_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 8 ];  then 
echo "Q TRAPEZOIDAL with Qgamma and MXdPhi_dqZero matrices with Cholesky decomposition";
gcc -DTRAPEZOIDAL -DCOORD_DEP -DDDL -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $DYN_DDL one_step_trapezoidal_q.c
g++ -c $OSG
gcc  -DTRAPEZOIDAL -DCOORD_DEP -DDDL -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $LA_Q_o $OSG_o read_config_file.c one_step_trapezoidal_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 9 ];  then 
echo "Q TRAPEZOIDAL with Q and M matrices with INVERSE";
gcc -DTRAPEZOIDAL -DCOORD_DEP -DDDQ -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $DYN_DDQ one_step_trapezoidal_q.c
g++ -c $OSG
gcc  -DTRAPEZOIDAL -DCOORD_DEP -DDDQ -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $LA_Q_o $OSG_o read_config_file.c one_step_trapezoidal_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 10 ];  then 
echo "Q TRAPEZOIDAL with Q and M matrices with Cholesky decomposition";
gcc -DTRAPEZOIDAL -DCOORD_DEP -DDDQ -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $DYN_DDQ one_step_trapezoidal_q.c
g++ -c $OSG
gcc  -DTRAPEZOIDAL -DCOORD_DEP -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $LA_Q_o $OSG_o read_config_file.c one_step_trapezoidal_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
#####################################################################################################################################################
if [ "$OPTION" == 11 ];  then 
echo "Q index-3 augmented Lagrangian with Q and M matrices with INVERSE";
gcc  -DI3AL -DCOORD_DEP -DINV $TOL -DALFA -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $I3AL_Q one_step_i3al_q.c
g++ -c $OSG
gcc  -DI3AL -DCOORD_DEP -DINV $TOL -DALFA -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $L_A_o $LA_Q_o $I3AL_Q_o $OSG_o read_config_file.c one_step_i3al_q.o  -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 12 ];  then 
echo "Q index-3 augmented Lagrangian with Q and M matrices with LU";
gcc  -DI3AL -DCOORD_DEP -DTRI $TOL -DALFA -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $LA_Q $I3AL_Q one_step_i3al_q.c
g++ -c $OSG
gcc  -DI3AL -DCOORD_DEP -DTRI $TOL -DALFA -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $L_A_o $LA_Q_o $I3AL_Q_o $OSG_o read_config_file.c one_step_i3al_q.o  -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
#####################################################################################################################################################
if [ "$OPTION" == 13 ];  then 
echo "Z EULER with INVERSE";
gcc -DEULER -DCOORD_IND -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $LA_Z one_step_euler_z.c
g++ -c $OSG
gcc -DEULER -DCOORD_IND -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $LA_Z_o $OSG_o read_config_file.c one_step_euler_z.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 14 ];  then 
echo "Z EULER with Cholesky decomposition ";
gcc -DEULER -DCOORD_IND -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $LA_Z one_step_euler_z.c
g++ -c $OSG
gcc -DEULER -DCOORD_IND -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $LA_Z_o $OSG_o read_config_file.c one_step_euler_z.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
#####################################################################################################################################################
if [ "$OPTION" == 15 ];  then 
echo "Z TRAPEZOIDAL with INVERSE";
gcc -DTRAPEZOIDAL -DCOORD_IND -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $LA_Z one_step_trapezoidal_z.c
g++ -c $OSG
gcc -DTRAPEZOIDAL -DCOORD_IND -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $LA_Z_o $OSG_o read_config_file.c one_step_trapezoidal_z.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 16 ];  then 
echo "Z TRAPEZOIDAL with Cholesky decomposition";
gcc -DTRAPEZOIDAL -DCOORD_IND -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $LA_Z one_step_trapezoidal_z.c
g++ -c $OSG
gcc -DTRAPEZOIDAL -DCOORD_IND -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $LA_Z_o $OSG_o read_config_file.c one_step_trapezoidal_z.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
#####################################################################################################################################################
if [ "$OPTION" == 17 ];  then 
echo "and Z with I3AL integrator with INVERSE";
gcc  -DI3AL -DCOORD_IND -DINV $TOL -DALFA -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $LA_Z $I3AL_Z one_step_i3al_z.c
g++ -c $OSG
gcc  -DI3AL -DCOORD_IND -DINV $TOL -DALFA -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $LA_Z_o $I3AL_Z_o $OSG_o read_config_file.c one_step_i3al_z.o  -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
if [ "$OPTION" == 18 ];  then 
echo "and Z with I3AL integrator with Cholesky decomposition";
gcc  -DI3AL -DCOORD_IND -DTRI $TOL -DALFA -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $LA_Z $I3AL_Z one_step_i3al_z.c
g++ -c $OSG
gcc  -DI3AL -DCOORD_IND -DTRI $TOL -DALFA -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $LA_Z_o $I3AL_Z_o $OSG_o read_config_file.c one_step_i3al_z.o  -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
fi
#####################################################################################################################################################

# Clean and erase
./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash

###################################################################################################
# Organize
cp ./solids/*.* ./GENERATED_OSG_bin/solids/
cp ./common/files_osg/axes.osg ./GENERATED_OSG_bin
cp ./common/files_osg/point.osg ./GENERATED_OSG_bin
cp ./common/files_osg/vector.osg ./GENERATED_OSG_bin
mv $MAIN ./GENERATED_OSG_bin

