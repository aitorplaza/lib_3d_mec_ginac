#!/bin/bash
#Compiles main_file.cc and based on its output compiles and executes main_numeric
MAIN=main_numeric
###################################################################################################
NEWTON_RAPHSON_TOLERANCE=1.0e-8
NR_TOL=-DNEWTON_RAPHSON_TOLERANCE=$NEWTON_RAPHSON_TOLERANCE

TRAPEZOIDAL_TOLERANCE=1.0e-8
TR_TOL=-DTRAPEZOIDAL_TOLERANCE=$TRAPEZOIDAL_TOLERANCE

INVERSE_TOLERANCE=1.0e-12
INV_TOL=-DINV_TOL=$INVERSE_TOLERANCE

TOL=" $NR_TOL $TR_TOL $INV_TOL "
###################################################################################################
TIME=TIME_ON
AUX_TIME=-D$TIME

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
COMMON="lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c write_data_file.c step.c"

COORD_Q="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c"
COORD_Z="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c"

L_A_Q="Initial_position_velocity.c"
L_A_Z="Initial_position_velocity.c"

DYN_DDL="Qgamma.c MXdPhi_dqZero.c"
DYN_DDQ="M.c Q.c"

I3AL_Q="Q_q.c Q_dq.c M.c Q.c"
I3AL_Z="Qz_z.c Qz_dz.c"
###################################################################################################
#cp ./common/files_c_h/osg/* .
cp ./common/files_c_h/lapack/* .
cp ./common/files_c_h/lin_alg/* .
cp ./common/files_c_h/common_c/* .
cp ./GENERATED_files_process_c_h/* .

echo "";
integration=1.0
delta_t=0.0005

#####################################################################################################################################################
name="state_lapack_euler.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ];  then 
	gcc  -DLAPACK $EULER $Q $DDL -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL newton_raphson_min_norm.c -lm -lblas -llapack
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lapack_trapezoidal.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ];  then 
	gcc  -DLAPACK $TRAPEZOIDAL $Q $DDL -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL newton_raphson_min_norm.c -lm -lblas -llapack
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_q_ddl_inv.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ];  then 
	gcc  -DLIN_ALG $EULER $Q $DDL $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL $L_A_Q one_step_euler_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_q_ddl_tri.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ];  then 
	gcc  -DLIN_ALG $EULER $Q $DDL $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL $L_A_Q one_step_euler_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_q_ddq_inv.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ];  then 
	gcc  -DLIN_ALG $EULER $Q $DDQ $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDQ $L_A_Q one_step_euler_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_q_ddq_tri.dat"; rm -f -r ./GENERATED_files_dat/$name
if [ ];  then 
	gcc -DLIN_ALG  $EULER $Q $DDQ $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDQ $L_A_Q one_step_euler_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_z_inv.dat"; rm -f -r ./GENERATED_files_dat/$name
if [ ]; then 
	gcc -DLIN_ALG $EULER $Z $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z $L_A_Z one_step_euler_z.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_euler_z_tri.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ]; then 
	gcc -DLIN_ALG $EULER $Z $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z $L_A_Z one_step_euler_z.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_q_ddl_inv.dat"; rm -f -r ./GENERATED_files_dat/$name
if [ ON ];  then 
	gcc -funroll-loops -DLIN_ALG $TRAPEZOIDAL $Q $DDL $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL $L_A_Q one_step_trapezoidal_q.c -lm
        echo "Compilation finished"
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_q_ddl_tri.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ];  then 
	gcc -DLIN_ALG $TRAPEZOIDAL $Q $DDL $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL $L_A_Q one_step_trapezoidal_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_q_ddq_inv.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ];  then 
	gcc -DLIN_ALG $TRAPEZOIDAL $Q $DDQ $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDQ $L_A_Q one_step_trapezoidal_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_q_ddq_tri.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ];  then 
	gcc -DLIN_ALG $TRAPEZOIDAL $Q $DDQ $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDQ $L_A_Q one_step_trapezoidal_q.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_z_inv.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ]; then 
	gcc -DLIN_ALG $TRAPEZOIDAL $Z $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z $L_A_Z one_step_trapezoidal_z.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################
name="state_lin_alg_trapezoidal_z_tri.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ]; then 
	gcc -DLIN_ALG $TRAPEZOIDAL $Z $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z $L_A_Z one_step_trapezoidal_z.c -lm
	./$MAIN $integration $delta_t $name;fi
#####################################################################################################################################################

#####################################################################################################################################################
name="state_lin_alg_i3al_q_inv.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ]; then 
	gcc -DLIN_ALG $I3AL $Q $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $I3AL_Q $L_A_Q one_step_i3al_q.c -lm
	./$MAIN $integration $delta_t $name;
fi
#####################################################################################################################################################
name="state_lin_alg_i3al_q_tri.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ]; then 
	gcc  -DLIN_ALG $I3AL $Q $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $I3AL_Q $L_A_Q one_step_i3al_q.c -lm
	./$MAIN $integration $delta_t $name;
fi
#####################################################################################################################################################
name="state_lin_alg_i3al_z_inv.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ]; then 
	gcc -DLIN_ALG $I3AL $Z $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z $I3AL_Z $L_A_Z one_step_i3al_z.c -lm
	./$MAIN $integration $delta_t $name;
fi
#####################################################################################################################################################
name="state_lin_alg_i3al_z_tri.dat"; rm -f -r ./GENERATED_files_dat/$name
if [  ]; then 
	gcc  -DLIN_ALG $I3AL $Z $TRI $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $COORD_Z $I3AL_Z $L_A_Z one_step_i3al_z.c -lm
	./$MAIN $integration $delta_t $name;
fi
#####################################################################################################################################################

mv $MAIN ./GENERATED_files_bin
./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash


