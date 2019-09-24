% compilation line for compiling wind_turbine_c_s_func_using_lapack.c in matlab as a mex function, lapack and blas subroutines are not the ones coming with matlab.

delete('*.mexglx')
delete('model.mdl')
delete('static.mdl')

copyfile('../GENERATED_files_process_c_h/*','.')
copyfile('../common/files_c_h/common_c/*','.')
copyfile('../common/files_c_h/simulink/*','.')
copyfile('../common/files_c_h/lin_alg/*','.')


copyfile('../common/files_c_h/lapack_and_osg/newton_raphson_min_norm.*','.')

copyfile('../common/files_matlab/model.mdl','.')
copyfile('../common/files_matlab/static.mdl','.')
copyfile('../common/files_osg/axes.osg','.')

copyfile('../solids/*.*','./solids')


mex  c_s_func_lapack.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Phi.c Beta.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c newton_raphson_min_norm.c -lm -lblas -llapack
mex  c_s_func_lapack_discrete.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Phi.c Beta.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c newton_raphson_min_norm.c -lm -lblas -llapack
%mex  c_s_func_lin_alg_z.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Initial_position_velocity_z.c Phi.c Phi_q.c Phi_z.c Phi_d.c Beta.c Gamma.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c write_data_file.c Output.c -lm


copyfile('../GENERATED_files_osg/cpp','.')
copyfile('../GENERATED_files_osg/h','.')

% compilation line for compiling osg model
mex osg_c_s_func.cpp gen_coord.c param.c solids_homogeneous_matrix.cpp osg_root.cpp osg_read_file.cpp osg_state.cpp -lOpenThreads -losg -losgDB -losgUtil -losgViewer -losgGA

delete('*.c')
delete('*.h')
delete('*.cpp')
delete('*.cc')
delete('*.*~')
%delete('axes.osg')

copyfile('../GENERATED_files_matlab/environment.m','.')





