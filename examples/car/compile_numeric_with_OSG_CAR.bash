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

cp ./car_functions/* .
###################################################################################################
## PROYECCION ##
Q=-DCOORD_DEP
Z=-DCOORD_IND

##INIT SOLVER
INIT=" "
# INIT="-DROBUST_INIT_SOLVER"


###################################################################################################
 
COMMON="Declare_Variables.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c write_data_file.c step.c"
COMMON_o=" Declare_Variables.o time.o gen_coord.o gen_vel.o gen_accel.o param.o unknowns.o inputs.o Phi.o Beta.o Gamma.o write_data_file.o step.o"

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

# XABIER
CAR="Geom_Kin_Model_plane.c  Kinematics_Wheels.c  TyreModel.c ContactPointVelocity.c"
CAR_o="Geom_Kin_Model_plane.o  Kinematics_Wheels.o  TyreModel.o ContactPointVelocity.o"

###################################################################################################
# XABIER
MAIN=main_numeric_osg_car
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
      gcc -DEULER -DCOORD_DEP $INIT -DDDL  -DTRI_LDL $TOL -DLIN_ALG -O2 -c read_config_file.c $COMMON $COORD_Q $L_A  $DYN_DDL $CAR one_step_euler.c
      g++ -c $OSG
      gcc  -DEULER -DCOORD_DEP $INIT -DDDL  -DTRI_LDL $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $OSG_o $CAR_o  read_config_file.c one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library and LDL";
      gcc -DEULER -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -c read_config_file.c $COMMON $COORD_Q $L_A  $DYN_DDQ $CAR one_step_euler.c
      g++ -c $OSG
      gcc  -DEULER -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $OSG_o $CAR_o  read_config_file.c one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling OpenSceneGraph model with Independent velocity Formalism and EULER integrator, solving with LIN_ALG library and LU";
      gcc -DEULER -DCOORD_IND $INIT $TOL -DLIN_ALG -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $CAR one_step_euler.c
      g++ -c $OSG
      gcc -DEULER -DCOORD_IND $INIT $TOL -DLIN_ALG  -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $OSG_o $CAR_o  read_config_file.c one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

  fi

  if [ "$INTEG" == 2 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LDL";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DTRI_LDL $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $DYN_DDL $CAR one_step_trapezoidal.c
      g++ -c $OSG
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DTRI_LDL $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o  $OSG_o $CAR_o  read_config_file.c one_step_trapezoidal.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LDL";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $DYN_DDQ $CAR one_step_trapezoidal.c
      g++ -c $OSG
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o  $OSG_o $CAR_o  read_config_file.c one_step_trapezoidal.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling OpenSceneGraph model with Independent velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LU";
      gcc -DTRAPEZOIDAL -DCOORD_IND $INIT $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $CAR  one_step_trapezoidal.c
      g++ -c $OSG
      gcc -DTRAPEZOIDAL -DCOORD_IND $INIT $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o  $OSG_o $CAR_o  read_config_file.c one_step_trapezoidal.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops                      
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
      gcc -DEULER -DCOORD_DEP $INIT -DDDL -DTRI_LU $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A  $DYN_DDL $CAR one_step_euler.c
      g++ -c $OSG
      gcc  -DEULER -DCOORD_DEP $INIT -DDDL -DTRI_LU $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $OSG_o $CAR_o  read_config_file.c one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library and LU";
      gcc -DEULER -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A  $DYN_DDQ $CAR one_step_euler.c
      g++ -c $OSG
      gcc  -DEULER -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $OSG_o $CAR_o  read_config_file.c one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling OpenSceneGraph model with Independent velocity Formalism and EULER integrator, solving with LIN_ALG library and LU";
      gcc -DEULER -DCOORD_IND $INIT $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $CAR one_step_euler.c
      g++ -c $OSG
      gcc -DEULER -DCOORD_IND $INIT $TOL -DLIN_ALG  -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o $OSG_o $CAR_o  read_config_file.c one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

  fi

  if [ "$INTEG" == 2 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LU";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DTRI_LU $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $DYN_DDL $CAR one_step_trapezoidal.c
      g++ -c $OSG
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DTRI_LU $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o  $OSG_o $CAR_o  read_config_file.c one_step_trapezoidal.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LU";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $DYN_DDQ $CAR one_step_trapezoidal.c
      g++ -c $OSG
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DTRI $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o  $OSG_o $CAR_o  read_config_file.c one_step_trapezoidal.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling OpenSceneGraph model with Independent velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and LU";
      gcc -DTRAPEZOIDAL -DCOORD_IND $INIT $TOL -O2 -c read_config_file.c $COMMON $COORD_Z $L_A $CAR  one_step_trapezoidal.c
      g++ -c $OSG
      gcc -DTRAPEZOIDAL -DCOORD_IND $INIT $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Z_o $L_A_o  $OSG_o $CAR_o  read_config_file.c one_step_trapezoidal.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops                      
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
      gcc -DEULER -DCOORD_DEP $INIT -DDDL -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A  $DYN_DDL $CAR one_step_euler.c
      g++ -c $OSG
      gcc  -DEULER -DCOORD_DEP $INIT -DDDL -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o $OSG_o $CAR_o  read_config_file.c one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library and INVERSE";
      gcc -DEULER -DCOORD_DEP $INIT -DDDQ -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A  $DYN_DDQ $CAR one_step_euler.c
      g++ -c $OSG
      gcc  -DEULER -DCOORD_DEP $INIT -DDDQ -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o $OSG_o $CAR_o  read_config_file.c one_step_euler.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Not available - Independent velocity Formalism and EULER integrator, solving with LIN_ALG library and INVERSE";
    fi

  fi

  if [ "$INTEG" == 2 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling OpenSceneGraph model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and INVERSE";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $DYN_DDL $CAR one_step_trapezoidal.c
      g++ -c $OSG
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDL -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDL_o $L_A_o  $OSG_o $CAR_o  read_config_file.c one_step_trapezoidal.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling OpenSceneGraph model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and INVERSE";
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DINV $TOL -O2 -c read_config_file.c $COMMON $COORD_Q $L_A $DYN_DDQ $CAR one_step_trapezoidal.c
      g++ -c $OSG
      gcc -DTRAPEZOIDAL -DCOORD_DEP $INIT -DDDQ -DINV $TOL -DLIN_ALG -O2 -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $DYN_DDQ_o $L_A_o  $OSG_o $CAR_o  read_config_file.c one_step_trapezoidal.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack -ansi -funroll-loops
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
      gcc -DCOORD_DEP -DDDL -O2 -c read_config_file.c newton_raphson_min_norm.c $COMMON $COORD_Q $DYN_DDL
      g++ -c $OSG
      g++ -DCOORD_DEP -DDDL -DEULER -DLAPACK -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $OSG_o $CAR_o  $DYN_DDL_o read_config_file.o newton_raphson_min_norm.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
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
      g++ -DCOORD_DEP -DDDL -DTRAPEZOIDAL -DLAPACK -o $MAIN $MAIN.cc $COMMON_o $COORD_Q_o $OSG_o $CAR_o  $DYN_DDL_o read_config_file.o newton_raphson_min_norm.o -lOpenThreads -losg -losgDB -losgGA -losgUtil -losgViewer -losgText -lm -lblas -llapack
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


rm -f Geom_Kin_Model_plane.c
rm -f Kinematics_Wheels.c
rm -f Kinematics_Wheels.h
rm -f TyreModel.c
rm -f TyreModel.h
rm -f direct_dynamics_lin_alg_car.c 
rm -f main_numeric_osg_car.cc
rm -f ContactPointVelocity.c
rm -f ContactPointVelocity.h



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
