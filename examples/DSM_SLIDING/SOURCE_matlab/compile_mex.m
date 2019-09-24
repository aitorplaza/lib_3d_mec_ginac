% compilation line for compiling wind_turbine_c_s_func_using_lapack.c in matlab as a mex function, lapack and blas subroutines are not the ones coming with matlab.

copyfile('../GENERATED_files_process_c_h','.')
copyfile('../../common/files_c_h','.')
copyfile('../../common/files_matlab','.')
copyfile('../../common/files_osg/axes.osg','.')

%mex  c_s_func_using_lapack.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c param_vect_def.c param_vect_init.c unknowns_vect_def.c unknowns_vect_init.c inputs_vect_def.c inputs_vect_init.c Phi.c Phi_t.c Phi_q.c Qgamma.c MXPhi_qZero.c newton_raphson_min_norm.c write_state_file.c write_state_file_header.c Output.c -lm -lblas -llapack

%mex  -DNEWTON_RAPHSON_TOLERANCE=1.0e-16 c_s_func_using_lapack_init.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c param_vect_def.c param_vect_init.c unknowns_vect_def.c unknowns_vect_init.c inputs_vect_def.c inputs_vect_init.c Phi.c Phi_t.c Phi_q.c PhiInit.c PhiInit_t.c minus_Phi_t.c minus_PhiInit_t.c PhiInit_q.c Qgamma.c MXPhi_qZero.c newton_raphson_min_norm.c write_state_file.c write_state_file_header.c Output.c print_mat.c Energy.c -lm -lblas -llapack % added print_mat.c Energy_Equations.c

mex  -DNEWTON_RAPHSON_TOLERANCE=1.0e-16 c_s_func_using_lapack_init.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c param_vect_def.c param_vect_init.c unknowns_vect_def.c unknowns_vect_init.c inputs_vect_def.c inputs_vect_init.c Phi.c Phi_q.c Beta.c dPhi_dq.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Qgamma.c MXdPhi_dqZero.c write_state_file.c write_state_file_header.c newton_raphson_min_norm.c Output.c print_mat.c Energy.c -lm -lblas -llapack



%mex  c_s_func_using_lapack_zd_rt.c lin_alg.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c param_vect_def.c param_vect_init.c unknowns_vect_def.c unknowns_vect_init.c inputs_vect_def.c inputs_vect_init.c Phi.c Phi_q.c Phi_z.c Phi_d.c Beta.c Gamma.c M_zz.c M_zd.c M_dd.c Q_z.c Q_d.c write_state_file.c write_state_file_header.c Output.c -lm


copyfile('../GENERATED_files_osg/cpp','.')
copyfile('../GENERATED_files_osg/h','.')

% compilation line for compiling osg model
mex osg_c_s_func.cpp param_vect_init.c param_vect_def.c gen_coord_vect_def.c gen_coord_vect_init.c solids_homogeneous_matrix.cpp osg_root.cpp osg_read_file.cpp osg_state.cpp -lOpenThreads -losg -losgDB -losgUtil -losgViewer -losgGA
%mex osg_c_s_func.cpp param_vect_init.c param_vect_def.c gen_coord_vect_def.c gen_coord_vect_init.c solids_homogeneous_matrix.cpp osg_root.cpp osg_read_file.cpp osg_state.cpp -lOpenThreads -losg -losgDB -losgUtil -losgViewer -losgGA


delete('*.c')
delete('*.h')
delete('*.cpp')
delete('*.cc')
%delete('axes.osg')

%mex  -DNEWTON_RAPHSON_TOLERANCE=1.0e-16 c_s_func_using_lapack.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c param_vect_def.c param_vect_init.c unknowns_vect_def.c unknowns_vect_init.c inputs_vect_def.c inputs_vect_init.c Phi.c Phi_t.c Phi_q.c Qgamma.c MXPhi_qZero.c newton_raphson_min_norm.c write_state_file.c write_state_file_header.c Output.c print_mat.c Energy_Equations.c -lm -lblas -llapack % added print_mat.c Energy_Equations.c






