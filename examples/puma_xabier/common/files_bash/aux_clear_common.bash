#!/bin/bash

# delete files comming from common.
# all files loaded from common, MUST be removed after being used.

rm -f *.tex

rm -f gen_coord_vect_def.c
rm -f gen_vel_vect_def.c
rm -f gen_accel_vect_def.c
rm -f param_vect_def.c
rm -f unknowns_vect_def.c
rm -f inputs_vect_def.c
rm -f newton_raphson_min_norm.c
rm -f print_mat.c
rm -f main_numeric_lapack.c
rm -f main_numeric_lin_alg.c
rm -f atom_def.c
rm -f direct_dynamics_lagrange_with_multipliers_and_qr_proyection_euler_improved_init.c
rm -f direct_dynamics_lagrange_with_multipliers_trapezoidal_init.c
rm -f read_config_file.c

rm -f step.c
rm -f lin_alg.c
rm -f timestamp.c
rm -f write_data_file.h

rm -f write_state_file.h
rm -f write_state_file_header.h
rm -f newton_raphson_min_norm.h
rm -f print_mat.h
rm -f atom_def.h
rm -f read_config_file.h

rm -f step.h
rm -f lin_alg.h


rm -f main_numeric_lapack_osg.cc
rm -f main_numeric_osg.cc
rm -f main_model_osg.cc
rm -f modelo_osg.cc
rm -f joystick.cc
rm -f KeyboardEventHandler.c
rm -f Includes_osg.h


rm -f axes.osg
rm -f ground.stl
rm -f Includes_functions.h
rm -f Includes_Init_functions.h
rm -f Includes_variables_parameters.h
rm -f one_step.h
rm -f Declare_Variables.h
rm -f arguments.c
rm -f Declare_Variables.c
rm -f Done_functions.c
rm -f Done_variables_parameters.c
rm -f Init_functions.c
rm -f Initial_position_velocity.c
rm -f Initial_position_velocity_q.c
rm -f Initial_position_velocity_z.c
rm -f Init_variables_parameters.c
rm -f Integration_Euler.c
rm -f Integration_Trapezoidal.c
rm -f main_numeric_lin_alg.c
rm -f main_numeric.c
rm -f direct_dynamics_lin_alg.c
rm -f one_step_euler_q.c
rm -f one_step_euler_z.c
rm -f one_step_euler.c
rm -f one_step_trapezoidal_q.c
rm -f one_step_trapezoidal_z.c
rm -f one_step_trapezoidal.c
rm -f one_step_i3al_q.c
rm -f one_step_i3al_z.c
rm -f Projection.c
rm -f Solve_Dynamics.c
rm -f information_text.c
rm -f *.*~


