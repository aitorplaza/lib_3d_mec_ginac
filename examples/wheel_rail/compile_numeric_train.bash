 #!/bin/bash
###################################################################################################
FORM=1
INTEG=2
MATH=3


###################################################################################################
#Compiles main_file.cc and based on its output compiles and executes main_numeric

#MAIN=main_numeric_train
MAIN=main_numeric_trainLU
###################################################################################################
NEWTON_RAPHSON_TOLERANCE=1.0e-8
NR_TOL=-DNEWTON_RAPHSON_TOLERANCE=$NEWTON_RAPHSON_TOLERANCE

TRAPEZOIDAL_TOLERANCE=1.0e-8
TR_TOL=-DTRAPEZOIDAL_TOLERANCE=$TRAPEZOIDAL_TOLERANCE

INVERSE_TOLERANCE=1.0e-12
INV_TOL=-DINV_TOL=$INVERSE_TOLERANCE

TOL=" $NR_TOL $TR_TOL $INV_TOL "
###################################################################################################

NR_ITER=1
AUX_NR_ITER=-DNR_ITER=$NR_ITER

ALFA=1.0e+12
AUX_ALFA=-DALFA=$ALFA

AUX=" $AUX_NR_ITER $AUX_ALFA "
###################################################################################################
## INTEGRADOR ##
EULER=-DEULER # Explicit Euler
TRAPEZOIDAL=-DTRAPEZOIDAL # Implicit Trapezoidal

## PROYECCION ##
Q=-DCOORD_DEP
Z=-DCOORD_IND

## ECUACIONES DINAMICAS - INCOGNITAS ##
DDL=-DDDL # Simple formalism.
DDQ=-DDDQ # Udwadia formalism.
DDZ=-DDDZ # Independent velocity formalism.

## METODO DE RESOLUCION DE LOS SISTEMAS LINEALES DE ECUACIONES ##
INV=-DINV #Uses Gauss-Jordan (Forward elimination Backward substitution with column pivoting) to compute all the inverse 
TRI_LDL=-DTRI_LDL #Uses LDL (For symmetric definite positive)
TRI_LU=-DTRI_LU #Uses LU (For thers)

## INIT SOLVER
INIT=" " # Solves the initial position using pseudo-inverse
# INIT="-DROBUST_INIT_SOLVER" # Solves the initial position using pseudo-inverse LU based


###################################################################################################
#~ COMMON="Declare_Variables.c time_3D_mec.c gen_coord.c gen_vel.c gen_accel.c gen_auxcoord.c gen_auxvel.c gen_auxaccel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c Output.c write_data_file.c step.c"

COMMON="time_3D_mec.c gen_coord.c gen_vel.c gen_accel.c gen_auxcoord.c gen_auxvel.c gen_auxaccel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c Output.c write_data_file.c step.c"

L_A="lin_alg.c Initial_position_velocity_with_splines.c"

COORD_Z="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c M.c Q.c MQ.c"

TRAIN="several_functions.c mu_div_mod_vel.c get_spline_coefs.c breaks_rail.c breaks_wheelL.c breaks_wheelR.c coefs_rail.c coefs_wheelL.c coefs_wheelR.c hertz_ellipse.c Table_Hertz.c Table_Kalker.c kalker_coeffs.c kalker_forces.c"
KALKER="CKL.c CKR.c Delta.c"
CONTACT="Gammac.c Gammat.c Betac.c Betat.c Phic.c Phit.c dPhic_dq.c dPhit_ds.c" 


###################################################################################################
cp ./GENERATED_files_process_c_h/* .
cp ./common/files_c_h/lapack/* .
cp ./common/files_c_h/lin_alg/* .
cp ./common/files_c_h/common_c/* .


cp ./train_functions/* .

TSTEP=0.001
TTIME=300.000

echo "";
name="state_lin_alg_Euler_Indep_Vel_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
gcc -DLIN_ALG -DTIME_OFF $INIT $EULER $Z $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $TRAIN $CONTACT $KALKER $L_A $COORD_Z  -lm
start=$SECONDS
time ./$MAIN $TTIME $TSTEP $name;		
      
      
      



#####################################################################################################################################################
# Clean and erase
mv $MAIN ./GENERATED_files_bin

rm -f Output.*
rm -f mu_div_mod_vel.*
rm -f get_spline_coefs.*
rm -f breaks_rail.*
rm -f breaks_wheelL.*
rm -f breaks_wheelR.*
rm -f coefs_rail.*
rm -f coefs_wheelL.*
rm -f coefs_wheelR.*
rm -f Initial_position_velocity_with_splines.*
rm -f hertz_ellipse.* 
rm -f Table_Hertz.*
rm -f kalker_coeffs.* 
rm -f Table_Kalker.*
rm -f kalker_forces.*   

rm -f one_step_trapezoidal_q_train.*
rm -f c_s_func_continuous_train.c
rm -f c_s_func_discrete_train.c
rm -f direct_dynamics_lin_alg_train.c
rm -f Includes_train.c
rm -f Integration_Trapezoidal_train.c
rm -f kalkers_forces_calculation.c
rm -f main_numeric_train.c
rm -f mu_div_mod_vel_sliding_vel.c
rm -f one_step_trapezoidal_q_train.c
rm -f one_step_trapezoidal_q_train.h
rm -f spline_tables.c
rm -f spline_tables_functions.c
rm -f spline_wheel_and_rail_profile.c

rm -f Declare_Variables_Train.c
rm -f Declare_Variables_Train.h

rm -f *.*~

#read -p "Press [Enter] key to continue..."
./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash
