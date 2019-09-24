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
  echo "Third Argument corresponds to the Math Library, and Options used for Solving:"
  echo "----------------------------------------------"
  echo " 1: LIN_ALG with LDL for Dep.Coord (Simple formalism & Udwadia Formalism) and LU for Indep.Coord"
  echo " 2: LIN_ALG with LU for both Dep.Coord (Simple formalism) and for Indep.Coord"
  echo " 3: LIN_ALG with INVERSE for Dep.Coord and LU for Indep.Coord"
  echo " 4: LAPACK"
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

cp ./train_functions/* .


###################################################################################################
## PROYECCION ##
Q=-DCOORD_DEP
Z=-DCOORD_IND

##INIT SOLVER
INIT=" "
# INIT="-DROBUST_INIT_SOLVER"


###################################################################################################
 
COMMON="Declare_Variables.c time_3D_mec.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c Output.c write_data_file.c step.c read_config_file.c"
COMMON_o=" Declare_Variables.o time_3D_mec.o gen_coord.o gen_vel.o gen_accel.o param.o unknowns.o inputs.o Phi.o Beta.o Gamma.o Output.o write_data_file.o step.o read_config_file.o"

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


TRAIN="mu_div_mod_vel.c get_spline_coefs.c breaks_rail.c breaks_wheelL.c breaks_wheelR.c coefs_rail.c coefs_wheelL.c coefs_wheelR.c Initial_position_velocity_with_splines.c hertz_ellipse.c Table_Hertz.c Table_Kalker.c kalker_coeffs.c kalker_forces.c"
TRAIN_o="mu_div_mod_vel.o get_spline_coefs.o breaks_rail.o breaks_wheelL.o breaks_wheelR.o coefs_rail.o coefs_wheelL.o coefs_wheelR.o Initial_position_velocity_with_splines.o hertz_ellipse.o Table_Hertz.o Table_Kalker.o kalker_coeffs.o kalker_forces.o"



###################################################################################################
#MAIN=main_numeric_osg
MAIN=main_numeric_osg_train
echo "";

if [ "$MATH" != 4 ] ;  then

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

fi

if [ "$MATH" == 1 ];  then

#added -DTRI_LDL to use LDL descomposition in dynamics

  if [ "$INTEG" == 1 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and EULER integrator, solving with LIN_ALG library and LDL";
      gcc -DEULER -DCOORD_DEP $INIT -DDDL  -DTRI_LDL $TOL -DLIN_ALG -O2 -c  $COMMON $COORD_Q $L_A  $DYN_DDL $TRAIN one_step_euler.c
      g++ -c $OSG
      g++  -DEULER -DCOORD_DEP $INIT -DDDL  -DTRI_LDL $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $OSG_o $TRAIN_o  one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library and LDL";
      gcc -DEULER -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -c  $COMMON $COORD_Q $L_A  $DYN_DDQ one_step_euler.c
      g++ -c $OSG
      g++  -DEULER -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $OSG_o  one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling OpenSceneGraph model with Independent velocity Formalism and EULER integrator, solving with LIN_ALG library and LU";
      gcc -DEULER -DCOORD_IND $INIT $TOL -DLIN_ALG -m64 -O2 -c  $COMMON $COORD_Z $L_A $TRAIN one_step_euler.c
      g++ -c $OSG
      g++ -DEULER -DCOORD_IND $INIT $TOL -DLIN_ALG -m64 -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $OSG_o $TRAIN_o  one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

  fi

  if [ "$INTEG" == 2 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LDL";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DTRI_LDL $TOL -O2 -c  $COMMON $COORD_Q $L_A $DYN_DDL  $TRAIN one_step_trapezoidal_train.c
      g++ -c $OSG
      g++ -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DTRI_LDL $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o  $OSG_o  $TRAIN_o  one_step_trapezoidal_train.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LDL";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -O2 -c  $COMMON $COORD_Q $L_A $DYN_DDQ one_step_trapezoidal_train.c
      g++ -c $OSG
      g++ -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o  $OSG_o  one_step_trapezoidal_train.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling OpenSceneGraph model with Independent velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LU";
      gcc -DTRAPEZOIDAL -DCOORD_IND $INIT $TOL -O2 -c  $COMMON $COORD_Z $L_A $TRAIN one_step_trapezoidal_train.c
      g++ -c $OSG
      g++ -DTRAPEZOIDAL -DCOORD_IND $INIT $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $TRAIN_o $OSG_o  one_step_trapezoidal_train.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops                      
    fi

  fi

  if [ "$INTEG" == 3 ];  then

    if [ "$FORM" == 1 ];  then
      echo "Not available - Simple Formalism and CONTINOUS integrator, solving with LIN_ALG library and LDL";
    fi

    if [ "$FORM" == 2 ];  then
      echo "Not available - Udwadia Formalism and CONTINOUS integrator, solving with LIN_ALG library and LDL";
    fi

    if [ "$FORM" == 3 ];  then
      echo "Not available - Independent velocity Formalism and CONTINOUS integrator, solving with LIN_ALG library";
    fi

  fi

fi

if [ "$MATH" == 2 ];  then

#added -DTRI_LU to use LU descomposition in dynamics

  if [ "$INTEG" == 1 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and EULER integrator, solving with LIN_ALG library and LU";
      gcc -DEULER -DCOORD_DEP $INIT -DDDL -DTRI_LU $TOL -DLIN_ALG -O2 -c  $COMMON $COORD_Q $L_A  $DYN_DDL $TRAIN one_step_euler.c
      g++ -c $OSG
      g++  -DEULER -DCOORD_DEP $INIT -DDDL -DTRI_LU $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $OSG_o $TRAIN_o  one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library and LU";
      gcc -DEULER -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -O2 -c  $COMMON $COORD_Q $L_A  $DYN_DDQ one_step_euler.c
      g++ -c $OSG
      g++  -DEULER -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $OSG_o  one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling OpenSceneGraph model with Independent velocity Formalism and EULER integrator, solving with LIN_ALG library and LU";
      gcc -DEULER -DCOORD_IND $INIT $TOL -O2 -c  $COMMON $COORD_Z $L_A $TRAIN one_step_euler.c
      g++ -c $OSG
      g++ -DEULER -DCOORD_IND $INIT $TOL -DLIN_ALG  -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $OSG_o $TRAIN_o  one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

  fi

  if [ "$INTEG" == 2 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LU";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DTRI_LU $TOL -O2 -c  $COMMON $COORD_Q $L_A $DYN_DDL $TRAIN one_step_trapezoidal_train.c
      g++ -c $OSG
      g++ -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DTRI_LU $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o  $OSG_o $TRAIN_o  one_step_trapezoidal_train.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LU";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -c  $COMMON $COORD_Q $L_A $DYN_DDQ one_step_trapezoidal_train.c
      g++ -c $OSG
      g++ -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o  $OSG_o  one_step_trapezoidal_train.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling OpenSceneGraph model with Independent velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LU";
      gcc -DTRAPEZOIDAL -DCOORD_IND $INIT $TOL -O2 -c  $COMMON $COORD_Z $L_A $TRAIN  one_step_trapezoidal_train.c
      g++ -c $OSG
      g++ -DTRAPEZOIDAL -DCOORD_IND $INIT $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o  $OSG_o $TRAIN_o   one_step_trapezoidal_train.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops                      
    fi

  fi

  if [ "$INTEG" == 3 ];  then

    if [ "$FORM" == 1 ];  then
      echo "Not available - Simple Formalism and CONTINOUS integrator, solving with LIN_ALG library and LU";
    fi

    if [ "$FORM" == 2 ];  then
      echo "Not available - Udwadia Formalism and CONTINOUS integrator, solving with LIN_ALG library and LU";
    fi

    if [ "$FORM" == 3 ];  then
      echo "Not available - Independent velocity Formalism and CONTINOUS integrator, solving with LIN_ALG library and LU";
    fi

  fi

fi

if [ "$MATH" == 3 ];  then

  if [ "$INTEG" == 1 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and EULER integrator, solving with LIN_ALG library and INVERSE";
      gcc -DEULER -DCOORD_DEP $INIT -DDDL -DINV $TOL -O2 -c  $COMMON $COORD_Q $L_A  $DYN_DDL one_step_euler.c
      g++ -c $OSG
      g++  -DEULER -DCOORD_DEP $INIT -DDDL -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $OSG_o  one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library and INVERSE";
      gcc -DEULER -DCOORD_DEP $INIT -DDDQ -DINV $TOL -O2 -c  $COMMON $COORD_Q $L_A  $DYN_DDQ one_step_euler.c
      g++ -c $OSG
      g++  -DEULER -DCOORD_DEP $INIT -DDDQ -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $OSG_o  one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Not available - Independent velocity Formalism and EULER integrator, solving with LIN_ALG library and INVERSE";
    fi

  fi

  if [ "$INTEG" == 2 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and INVERSE";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DINV $TOL -O2 -c  $COMMON $COORD_Q $L_A $DYN_DDL $TRAIN one_step_trapezoidal_train.c
      g++ -c $OSG
      g++ -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $OSG_o $TRAIN_o  one_step_trapezoidal_train.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and INVERSE";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DINV $TOL -O2 -c  $COMMON $COORD_Q $L_A $DYN_DDQ one_step_trapezoidal_train.c
      g++ -c $OSG
      g++ -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o  $OSG_o  one_step_trapezoidal_train.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Not available - Independent velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and INVERSE";
    fi

  fi

  if [ "$INTEG" == 3 ];  then

    if [ "$FORM" == 1 ];  then
      echo "Not available - Simple Formalism and CONTINOUS integrator, solving with LIN_ALG library and INVERSE";
    fi

    if [ "$FORM" == 2 ];  then
      echo "Not available - Udwadia Formalism and CONTINOUS integrator, solving with LIN_ALG library and INVERSE";
    fi

    if [ "$FORM" == 3 ];  then
      echo "Not available - Independent velocity Formalism and CONTINOUS integrator, solving with LIN_ALG library and INVERSE";
    fi

  fi

fi


############
## LAPACK ##
###################################################################################################

if [ "$MATH" == 4 ];  then

  if [ "$INTEG" == 1 ];  then

    if [ "$FORM" == 1 ];  then
      echo "Compiling OpenSceneGraph model with Simple Formalism and EULER integrator, solving with LAPACK library";
      gcc -DCOORD_DEP -DDDL -O2 -c  newton_raphson_min_norm.c $COMMON $COORD_Q $DYN_DDL
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
      gcc -DCOORD_DEP -DDDL -O2 -c  newton_raphson_min_norm.c $COMMON $COORD_Q $DYN_DDL
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

rm -f *.*~


./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash


###################################################################################################
# Organize
cp ./solids/*.* ./GENERATED_OSG_bin/solids/
cp ./common/files_osg/axes.osg ./GENERATED_OSG_bin
cp ./common/files_osg/point.osg ./GENERATED_OSG_bin
cp ./common/files_osg/vector.osg ./GENERATED_OSG_bin
mv $MAIN ./GENERATED_OSG_bin
