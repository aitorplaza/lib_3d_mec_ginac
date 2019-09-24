 #!/bin/bash
###################################################################################################
FORM=$1
INTEG=$2
MATH=$3
TSTEP=$4
TTIME=$5
if [ -z $5 ] && [ -z $4 ] && [ -z $3 ] && [ -z $2 ] && [ -z $1 ]; then 
echo "Please, enter an space separated list, with 5 arguments in the following order"
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
echo " 1: LIN_ALG with LDL for Dep.Coord and LU for Indep.Coord"
echo " 2: LIN_ALG with LU for both Dep.Coord and for Indep.Coord"
echo " 3: LIN_ALG with INVERSE for Dep.Coord and LU for Indep.Coord"
echo " 4: LAPACK"
echo "----------------------------------------------"
echo "4th and 5th Argument corresponds to time step and Total time:"
echo "----------------------------------------------"
echo " "
echo "Example: Simple Formalism with EULER integrator, and LIN_ALG Math library using LDL, Delta_t=0.001 and integration time 10 seconds"
echo "Corresponds with this sequence: 1 1 1 0.001 10"
echo " "
read FORM INTEG MATH TSTEP TTIME 
if [ -z $FORM ] ; then exit; fi
fi 
###################################################################################################
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

COMMON="Declare_Variables.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Phi.c Beta.c Gamma.c write_data_file.c step.c"
L_A="Initial_position_velocity.c"
COORD_Q="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c"
COORD_Z="PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c  M.c Q.c"

DYN_DDL="Qgamma.c MXdPhi_dqZero.c"
DYN_DDQ="M.c Q.c"

###################################################################################################
cp ./common/files_c_h/lapack/* .
cp ./common/files_c_h/lin_alg/* .
cp ./common/files_c_h/common_c/* .
cp ./GENERATED_files_process_c_h/* .
echo "";

if [ "$MATH" == 1 ];  then

######################
##   LIN_ALG LDL    ##
#####################################################################################################################################################

  if [ "$INTEG" == 1 ];  then
    if [ "$FORM" == 1 ];  then 
      echo "Compiling Model with Simple Formalism and EULER integrator, solving with LIN_ALG library";
      name="state_lin_alg_Euler_Simple_form_LDL.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $EULER $Q $DDL $TRI_LDL $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDL one_step_euler.c -lm
      ./$MAIN $TTIME $TSTEP $name;
    fi
    if [ "$FORM" == 2 ];  then 
      echo "Compiling Model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library";
      name="state_lin_alg_Euler_Udwadia_form_LDL.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $EULER $Q $DDQ $TRI_LDL $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDQ one_step_euler.c -lm
      ./$MAIN $TTIME $TSTEP $name;
    fi
    if [ "$FORM" == 3 ];  then 
      echo "Compiling Model with Independent Velocity Formalism and EULER integrator, solving with LIN_ALG library";
      name="state_lin_alg_Euler_Indep_Vel_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $EULER $Z $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Z one_step_euler.c -lm
      ./$MAIN $TTIME $TSTEP $name;		
    fi
  fi

  if [ "$INTEG" == 2 ];  then
    if [ "$FORM" == 1 ];  then 
      echo "Compiling Model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
      name="state_lin_alg_Trapezoidal_Simple_form_LDL.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $TRAPEZOIDAL $Q $DDL $TRI_LDL $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDL one_step_trapezoidal.c -lm
      ./$MAIN $TTIME $TSTEP $name;
    fi
    if [ "$FORM" == 2 ];  then 
      echo "Compiling Model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
      name="state_lin_alg_Trapezoidal_Udwadia_form_LDL.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $TRAPEZOIDAL $Q $DDQ $TRI_LDL $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDQ one_step_trapezoidal.c -lm
      ./$MAIN $TTIME $TSTEP $name;
    fi
    if [ "$FORM" == 3 ];  then 
      echo "Compiling Model with Independent Velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
      name="state_lin_alg_Trapezoidal_Indep_Vel_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $TRAPEZOIDAL $Z $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Z one_step_trapezoidal.c -lm
      ./$MAIN $TTIME $TSTEP $name;		
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

if [ "$MATH" == 2 ];  then

#############
## LIN_ALG LU ##
#####################################################################################################################################################

  if [ "$INTEG" == 1 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling Model with Simple Formalism and EULER integrator, solving with LIN_ALG library";
      name="state_lin_alg_Euler_Simple_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $EULER $Q $DDL $TRI_LU $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDL one_step_euler.c -lm
      ./$MAIN $TTIME $TSTEP $name;
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling Model with Udwadia Formalism and EULER integrator, solving with LIN_ALG library";
      name="state_lin_alg_Euler_Udwadia_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $EULER $Q $DDQ $TRI_LU $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDQ one_step_euler.c -lm
      ./$MAIN $TTIME $TSTEP $name;
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling Model with Independent Velocity Formalism and EULER integrator, solving with LIN_ALG library";
      name="state_lin_alg_Euler_Indep_Vel_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $EULER $Z $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Z one_step_euler.c -lm
      ./$MAIN $TTIME $TSTEP $name;		
    fi

  fi

  if [ "$INTEG" == 2 ];  then

    if [ "$FORM" == 1 ];  then 
      echo "Compiling Model with Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
      name="state_lin_alg_Trapezoidal_Simple_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $TRAPEZOIDAL $Q $DDL $TRI_LU $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDL one_step_trapezoidal.c -lm
      ./$MAIN $TTIME $TSTEP $name;
    fi

    if [ "$FORM" == 2 ];  then 
      echo "Compiling Model with Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
      name="state_lin_alg_Trapezoidal_Udwadia_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $TRAPEZOIDAL $Q $DDQ $TRI_LU $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDQ one_step_trapezoidal.c -lm
      ./$MAIN $TTIME $TSTEP $name;
    fi

    if [ "$FORM" == 3 ];  then 
      echo "Compiling Model with Independent Velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library";
      name="state_lin_alg_Trapezoidal_Indep_Vel_form_LU.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc -DLIN_ALG -DTIME_OFF $INIT $TRAPEZOIDAL $Z $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Z one_step_trapezoidal.c -lm
      ./$MAIN $TTIME $TSTEP $name;		
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

if [ "$MATH" == 3 ];  then

###################################################################################################
##   OPTIONS WITH LIN_ALG AND INVERSE   #########
###################################################################################################

  if [ "$FORM" == 1 ] && [ "$INTEG" == 1 ];  then 
    echo "Compiling Model with Simple Formalism and EULER integrator, solving with INVERSE and LIN_ALG library";
    name="state_lin_alg_Euler_Simple_form_INVERSE.dat"; rm -f -r ./GENERATED_files_dat/$name
    gcc -DLIN_ALG -DTIME_OFF $EULER $Q $DDL $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDL one_step_euler.c -lm
    ./$MAIN $TTIME $TSTEP $name;
  fi
  if [ "$FORM" == 1 ] && [ "$INTEG" == 2 ];  then 
    echo "Compiling Model with Simple Formalism and TRAPEZOIDAL integrator, solving with INVERSE and LIN_ALG library";
    name="state_lin_alg_Trapezoidal_Simple_form_INVERSE.dat"; rm -f -r ./GENERATED_files_dat/$name
    gcc -DLIN_ALG -DTIME_OFF $TRAPEZOIDAL $Q $DDL $INV $TOL $AUX -O2 -o $MAIN $MAIN.c $COMMON $L_A $COORD_Q $DYN_DDL one_step_trapezoidal.c -lm
    ./$MAIN $TTIME $TSTEP $name;
  fi
  if [ "$FORM" != 1 ] || [ "$INTEG" == 3 ];  then 
      echo "Option not valid for INVERSE"
  fi
fi

############
## LAPACK ##
###################################################################################################

if [ "$MATH" == 4 ];  then

  if [ "$INTEG" == 1 ];  then
    if [ "$FORM" == 1 ];  then
      echo "Compiling Model with Simple Formalism and EULER integrator, solving with LAPACK library";
      name="state_Lapack_Euler_Simple_form.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc  -DLAPACK -DTIME_OFF $EULER $Q $DDL -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL newton_raphson_min_norm.c -lm -lblas -llapack
      ./$MAIN $TTIME $TSTEP $name;
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
      echo "Compiling Model with Simple Formalism and TRAPEZOIDAL integrator, solving with LAPACK library";
      name="state_Lapack_Trapezoidal_Simple_form.dat"; rm -f -r ./GENERATED_files_dat/$name
      gcc  -DLAPACK -DTIME_OFF $TRAPEZOIDAL $Q $DDL -O2 -o $MAIN $MAIN.c $COMMON $COORD_Q $DYN_DDL newton_raphson_min_norm.c -lm -lblas -llapack
      ./$MAIN $TTIME $TSTEP $name;
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
mv $MAIN ./GENERATED_files_bin
./common/files_bash/aux_clear_common.bash
./common/files_bash/aux_move.bash
