#!/bin/bash
#Compiles main_file.cc and based on its output compiles and executes main_numeric
#####################################################################################################################################################
# define variables
#####################################################################################################################################################
# STANDARD OPTIONS
#####################################################################################################################################################
METHOD=V_P		# ==> MVPhi_qZero.c
ORDER=CMO
MAPLE=MAPLE_ON
SLIP=ROLLING
GRPH=NO_GRAPHVIZ	# do not export to Latex
#####################################################################################################################################################
# ALTERNATIVE OPTIONS: Note: Un-comment the Alternative-option line, Standard option variable becomes over-written. 
#####################################################################################################################################################
#METHOD=LAG				# Remove Comment for ==> MPhi_qTPhi_qZero.c
#ORDER=RMO				# Remove Comment for standard CMO export.
#SLIP=SLIP					# Remove Comment for slipping.
#MAPLE=MAPLE_OFF		# Remove Comment for non mapple files.
#GRPH=GRAPHVIZ			# Remove Comment for GRAPHVIZ function, export to Latex

#INTEGRATOR=EULER
INTEGRATOR=TRAPEZOIDAL

NAME=main_train_proto_7

NEWTON_RAPHSON_TOLERANCE=1.0e-8
NR_TOL=-DNEWTON_RAPHSON_TOLERANCE=$NEWTON_RAPHSON_TOLERANCE

TRAPEZOIDAL_TOLERANCE=1.0e-8
TR_TOL=-DTRAPEZOIDAL_TOLERANCE=$TRAPEZOIDAL_TOLERANCE

INVERSE_TOLERANCE=1.0e-12
INV_TOL=-DINV_TOL=$INVERSE_TOLERANCE

TOL=" $NR_TOL $TR_TOL $INV_TOL "
#####################################################################################################################################################
if [[ $METHOD != "V_P" ]] && [[ $METHOD != "LAG" ]]; then echo "select METHOD"; exit ; fi
if [[ $ORDER != "CMO" ]] && [[ $ORDER != "RMO" ]]; then echo "select ORDER"; exit ; fi
if [[ $SLIP != "ROLLING" ]] && [[ $SLIP != "SLIP" ]]; then echo "select SLIP"; exit ; fi
if [[ $MAPLE != "MAPLE_ON" ]] && [[ $MAPLE != "MAPLE_OFF" ]]; then echo "select MAPLE"; exit ; fi
if [[ $INTEGRATOR != "EULER" ]] && [[ $INTEGRATOR != "TRAPEZOIDAL" ]]; then echo "Chosee integration method: EULER or TRAPEZOIDAL RULE"; exit ; fi
#####################################################################################################################################################
#####################################################################################################################################################
#TYPE=Q
#TYPE="Z"
#TYPE="I3AL_Q"
#TYPE="I3AL_Z"
TYPE="ALL"
PROBLEM_TYPE=$TYPE
AUX_PROBLEM_TYPE=-D$PROBLEM_TYPE
#####################################################################################################################################################
rm -f -r ./GENERATED_files_*
cp ../common/files_bash/* .
./aux_tree.bash

export PKG_CONFIG_PATH=`pwd`/../../../lib/pkgconfig
export LD_LIBRARY_PATH=`pwd`/../../../lib
RELEASE=RELEASE_1
g++ -D$METHOD -DORDER=$ORDER -DMAPLE=$MAPLE $AUX_PROBLEM_TYPE -D$SLIP -D$GRPH -D$RELEASE -o $NAME $NAME.cc `pkg-config --cflags --libs lib_3d_mec_ginac-1.1 ginac`
#-DPROBLEM_TYPE=$PROBLEM_TYPE
cp ../common/files_tex/* .
./$NAME DOWN NO

cp ../common/files_c_h/common_c/* .

#####################################################################################################################################################

#####################################################################################################################################################
#####################################################################################################################################################
cp ../common/files_c_h/common_release_1/* .
./aux_compile_main.bash
COMMON_RELEASE_1="var_def.o var_init.o gen_coord_vect_def.o gen_coord_vect_init.o gen_vel_vect_def.o gen_vel_vect_init.o gen_accel_vect_def.o gen_accel_vect_init.o param_vect_def.o param_vect_init.o unknowns_vect_def.o unknowns_vect_init.o inputs_vect_def.o inputs_vect_init.o Phi.o Beta.o write_state_file.o write_state_file_header.o newton_raphson_min_norm.o print_mat.o Output.o Energy.o"
COORD_Q1="PhiInit.o PhiInit_q.o dPhiInit_dq.o BetaInit.o Phi_q.o dPhi_dq.o Qgamma.o MXdPhi_dqZero.o"
# comprobar con AITOR sin print_mat Ouput y Energy son becesarias en la compilacion....... (quitar las referencias en los main....)
gcc $NR_TOL $TR_TOL -D$INTEGRATOR -O2 -o main_numeric  main_numeric.c $COMMON_RELEASE_1 $COORD_Q1 -lm -lblas -llapack
#####################################################################################################################################################
#Compilar OSG model y main_numeric_osg
g++ -c solids_homogeneous_matrix.cpp osg_read_file.cpp osg_root.cpp osg_state.cpp 
g++ -D$INTEGRATOR -o main_numeric_osg main_numeric_osg.cc $COMMON_RELEASE_1 $COORD_Q1 read_config_file.o solids_homogeneous_matrix.o osg_read_file.o osg_root.o osg_state.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
#####################################################################################################################################################

integration=0.01
delta_t=0.001

error=1e-8
if [[ $ORDER == "CMO" ]] # cuidado, main_numeric pensado para recibir matrices CMO
	then
    echo "main_numeric"
#    ./main_numeric $integration $delta_t $error
#    cp state.dat state_main.dat
#    sed '1d' state_main.dat > state.dat; ./aux_graphics.bash
fi
#####################################################################################################################################################
#####################################################################################################################################################
cp ../common/files_c_h/lin_alg/* .

COMMON="lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c write_data_file.c step.c Initial_position_velocity.c"

COORD_Q="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Initial_position_velocity_q.c"
COORD_Z="Phi_z.c Phi_d.c Gamma.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c Initial_position_velocity_z.c"

DYN_DDL="Qgamma.c MXdPhi_dqZero.c"
DYN_DDQ="M.c Q.c Gamma.c"

I3AL_Q="Q_q.c Q_dq.c"
I3AL_Z="Qz_z.c Qz_dz.c"

MAIN=main_numeric_lin_alg

TIME=TIME_ON
#AUX_TIME=-D$TIME

NR_ITER=1
AUX_NR_ITER=-DNR_ITER=$NR_ITER

ALFA=1.0e+12
AUX_ALFA=-DALFA=$ALFA

AUX=" $AUX_NR_ITER $AUX_TIME $AUX_ALFA "

###################################################################################################
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
###################################################################################################

#####################################################################################################################################################
name="state_lin_alg_euler_q_ddl_inv.dat"
if [ ON ];  then 
	gcc  $EULER $Q $DDL $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL one_step_euler_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_q_ddl_tri.dat"
if [ ON ];  then 
	gcc  $EULER $Q $DDL $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL one_step_euler_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_q_ddq_inv.dat"
if [ ON ];  then 
	gcc  $EULER $Q $DDQ $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDQ one_step_euler_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_q_ddq_tri.dat"
if [ ON ];  then 
	gcc  $EULER $Q $DDQ $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDQ one_step_euler_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_z_inv.dat"
if [ ON ]; then 
	gcc  $EULER $Z $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z one_step_euler_z.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_z_tri.dat"
if [ ON ]; then 
	gcc  $EULER $Z $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z one_step_euler_z.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_q_ddl_inv.dat"
if [ ON ];  then 
	gcc  $TRAPEZOIDAL $Q $DDL $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL one_step_trapezoidal_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_q_ddl_tri.dat"
if [ ON ];  then 
	gcc  $TRAPEZOIDAL $Q $DDL $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL one_step_trapezoidal_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_q_ddq_inv.dat"
if [ ON ];  then 
	gcc  $TRAPEZOIDAL $Q $DDQ $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDQ one_step_trapezoidal_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_q_ddq_tri.dat"
if [ ON ];  then 
	gcc  $TRAPEZOIDAL $Q $DDQ $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDQ one_step_trapezoidal_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_z_inv.dat"
if [ ON ]; then 
	gcc  $TRAPEZOIDAL $Z $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z one_step_trapezoidal_z.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_z_tri.dat"
if [ ON ]; then 
	gcc  $TRAPEZOIDAL $Z $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z one_step_trapezoidal_z.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
# sed '1d' $name_euler_q > state.dat; ./aux_graphics_lin_alg.bash
#./main_numeric_osg 0.01 1e-8

./aux_clear_common.bash
./aux_move.bash $GRPH $MAPLE

mv *.gnuplot GENERATED_files_graphics/
cp GENERATED_files_matlab/environment.m SOURCE_matlab/
rm -f -r *.*~
mv $NAME GENERATED_files_bin/

date

