 #!/bin/bash
###################################################################################################
FORM=$1
INTEG=$2
MATH=$3
if [ -z $3 ] ; then 
echo "Please, enter an space separated list, with three integer arguments in the following order"
echo "----------------------------------------------"
echo "First Argument corresponds to the Formulation:"
echo "----------------------------------------------"
echo " 1: Simple Formalism"
echo " 2: Udwadia Formalism"
echo " 3: Independent Velocity Formalism"
echo "----------------------------------------------"
echo "Second Argument corresponds to the Integrator:"
echo "----------------------------------------------"
echo " 1: EULER"
echo " 2: TRAPEZOIDAL"
echo " 3: CONTINOUS"
echo "----------------------------------------------"
echo "Third Argument corresponds to the Math Library used for Solving:"
echo "----------------------------------------------"
echo " 1: LIN_ALG"
echo " 2: LAPACK"
echo "----------------------------------------------"
echo " "
echo "Example: 1 1 1"
echo " "
read FORM INTEG MATH
if [ -z $FORM ] ; then exit; fi
fi 
echo "You Chose $FORM, $INTEG, $MATH !"
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

COORD_Z="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c M.c Q.c"
COORD_Z_o="PhiInit.o PhiInit_q.o dPhiInit_dq.o BetaInit.o Phi_q.o dPhi_dq.o M.o Q.o"

L_A="lin_alg.c Initial_position_velocity.c"
L_A_o="lin_alg.o Initial_position_velocity.o"

OSG="solids_homogeneous_matrix.cpp osg_read_file.cpp osg_root.cpp osg_state.cpp"
OSG_o="solids_homogeneous_matrix.o osg_read_file.o osg_root.o osg_state.o"

###################################################################################################
MAIN=main_numeric_osg
echo "";

if [ "$MATH" == 1 ];  then

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

	if [ "$INTEG" == 1 ];  then

		if [ "$FORM" == 1 ];  then 
		echo "Compiling OpenSceneGraph model with Simple Formalism and EULER integrator, solving with LIN_ALG library";
		gcc -DEULER -DCOORD_DEP -DDDL -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A  $DYN_DDL one_step_euler_q.c
		g++ -c $OSG
		gcc  -DEULER -DCOORD_DEP -DDDL -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $OSG_o read_config_file.c one_step_euler_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
		fi

		if [ "$FORM" == 2 ];  then 
		echo "Compiling OpenSceneGraph model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library";
		gcc -DEULER -DCOORD_DEP -DDDQ -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A  $DYN_DDQ one_step_euler_q.c
		g++ -c $OSG
		gcc  -DEULER -DCOORD_DEP -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $OSG_o read_config_file.c one_step_euler_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
		fi

		if [ "$FORM" == 3 ];  then 
		echo "Compiling OpenSceneGraph model with Independent velocity Formalism and EULER integrator, solving with LIN_ALG library";
		gcc -DEULER -DCOORD_IND -DROBUST_SOLVER $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A one_step_euler_z.c
		g++ -c $OSG
		gcc -DEULER -DCOORD_IND -DROBUST_SOLVER $TOL -DLIN_ALG  -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $OSG_o read_config_file.c one_step_euler_z.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
		fi

	fi

	if [ "$INTEG" == 2 ];  then

		if [ "$FORM" == 1 ];  then 
		echo "Compiling OpenSceneGraph model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
		gcc -DTRAPEZOIDAL -DCOORD_DEP -DDDL -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $DYN_DDL one_step_trapezoidal_q.c
		g++ -c $OSG
		gcc  -DTRAPEZOIDAL -DCOORD_DEP -DDDL -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o  $OSG_o read_config_file.c one_step_trapezoidal_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
		fi

		if [ "$FORM" == 2 ];  then 
		echo "Compiling OpenSceneGraph model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
		gcc -DTRAPEZOIDAL -DCOORD_DEP -DDDQ -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $DYN_DDQ one_step_trapezoidal_q.c
		g++ -c $OSG
		gcc  -DTRAPEZOIDAL -DCOORD_DEP -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o  $OSG_o read_config_file.c one_step_trapezoidal_q.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
		fi

		if [ "$FORM" == 3 ];  then 
		echo "Compiling OpenSceneGraph model with Independent velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
		gcc -DTRAPEZOIDAL -DCOORD_IND -DROBUST_SOLVER $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A  one_step_trapezoidal_z.c
		g++ -c $OSG
		gcc -DTRAPEZOIDAL -DCOORD_IND -DROBUST_SOLVER $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o  $OSG_o read_config_file.c one_step_trapezoidal_z.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops                      
		fi

	fi

	if [ "$INTEG" == 3 ];  then

		if [ "$FORM" == 1 ];  then
		echo "Not available - Simple Formalism and CONTINOUS integrator, solving with LIN_ALG library";
		fi

		if [ "$FORM" == 2 ];  then
		echo "Not available - Udwadia Formalism and CONTINOUS integrator, solving with LIN_ALG library";
		fi

		if [ "$FORM" == 3 ];  then
		echo "Not available - Independent velocity Formalism and CONTINOUS integrator, solving with LIN_ALG library";
		fi

	fi

fi

############
## LAPACK ##
###################################################################################################

if [ "$MATH" == 2 ];  then

	if [ "$INTEG" == 1 ];  then

		if [ "$FORM" == 1 ];  then
		echo "Compiling OpenSceneGraph model with Simple Formalism and EULER integrator, solving with LAPACK library";
		gcc -DCOORD_DEP -DDDL -O2 -c read_config_file.c newton_raphson_min_norm.c $COMMON $COORD_Q $DYN_DDL
		g++ -c $OSG
		g++ -DCOORD_DEP -DDDL -DEULER -DLAPACK -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $OSG_o $DYN_DDL_o read_config_file.o newton_raphson_min_norm.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
		fi

		if [ "$FORM" == 2 ];  then
		echo "Not available - Udwadia Formalism and EULER integrator, solving with LAPACK library";
		fi

		if [ "$FORM" == 3 ];  then
		echo "Not available - Independent velocity Formalism and EULER integrator, solving with LAPACK library";
		fi

	fi

	if [ "$INTEG" == 2 ];  then

		if [ "$FORM" == 1 ];  then
		echo "Compiling OpenSceneGraph model with Simple Formalism and TRAPEZOIDAL integrator, solving with LAPACK library";
		gcc -DCOORD_DEP -DDDL -O2 -c read_config_file.c newton_raphson_min_norm.c $COMMON $COORD_Q $DYN_DDL
		g++ -c $OSG
		g++ -DCOORD_DEP -DDDL -DTRAPEZOIDAL -DLAPACK -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $OSG_o $DYN_DDL_o read_config_file.o newton_raphson_min_norm.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
		fi

		if [ "$FORM" == 2 ];  then
		echo "Not available - Udwadia Formalism and TRAPEZOIDAL integrator, solving with LAPACK library";
		fi

		if [ "$FORM" == 3 ];  then
		echo "Not available - Independent velocity Formalism and TRAPEZOIDAL integrator, solving with LAPACK library";
		fi

	fi

	if [ "$INTEG" == 3 ];  then

		if [ "$FORM" == 1 ];  then
		echo "Not available - Simple Formalism and CONTINOUS integrator, solving with LAPACK library";
		fi

		if [ "$FORM" == 2 ];  then
		echo "Not available - Udwadia Formalism and CONTINOUS integrator, solving with LAPACK library";
		fi

		if [ "$FORM" == 3 ];  then
		echo "Not available - Independent velocity Formalism and CONTINOUS integrator, solving with LAPACK library";
		fi

	fi

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
