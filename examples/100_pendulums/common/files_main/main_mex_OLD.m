function main_mex

OSGWINPATH='C:\Program Files\OpenSceneGraph-2.8.5';
disp('------------------------------------------------------------------------------------')
disp('------------------------------------------------------------------------------------')
disp('FOR EXTERNAL MODES, OPEN THE MODEL BEFORE RUNNING THIS UTILITY')
disp('------------------------------------------------------------------------------------')
disp(' 0: EXTERNAL')
disp(' 1: NORMAL')
disp('------------------------------------------------------------------------------------')
extchoice=input('Choose one of the following options (0 for External, 1 For Normal) [1]:');
if (isempty(extchoice)|ischar(extchoice)|isnan(extchoice));
    extchoice= 1;
end
if((extchoice~=0)&&(extchoice~=1))
disp(' ')
disp('Wrong option')
disp('Option 1 (Normal) assigned')
disp('Press <enter> to continue...')
disp(' ')
pause
end

disp(' ')
disp('------------------------------------------------------------------------------------')
disp(' COMPILATION OPTIONS')
disp('------------------------------------------------------------------------------------')
disp(' DISCRETE OPTIONS')
disp('------------------------------------------------------------------------------------')
disp(' 1: Simple Formalism and EULER integrator, solving with LAPACK library')
disp('------------------------------------------------------------------------------------')
disp(' 2: Simple Formalism and EULER integrator, solving with LIN_ALG library')
disp(' 3: Udwadia Formalism and EULER integrator, solving with LIN_ALG library')
disp(' 4: Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library')
disp(' 5: Udwadia Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library')
disp(' 6: Independent Velocity Formalism and EULER integrator, solving with LIN_ALG library')
disp(' 7: Independent Velocity Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library')
disp(' 8: Simple Formalism and TRAPEZOIDAL integrator, solving with LIN_ALG library and INVERSE')
disp('------------------------------------------------------------------------------------')
disp('------------------------------------------------------------------------------------')
disp(' CONTINOUS OPTIONS')
disp('------------------------------------------------------------------------------------')
disp(' 9: Simple Formalism and MATLAB integrator, solving with LAPACK library')
disp('------------------------------------------------------------------------------------')
disp(' 10: Simple Formalism and MATLAB integrator, solving with LIN_ALG library')
disp(' 11: Udwadia Formalism and MATLAB integrator, solving with LIN_ALG library')
disp(' 12: Independent Velocity Formalism and MATLAB integrator, solving with LIN_ALG library')
disp('------------------------------------------------------------------------------------')   
disp(' ')
disp(' ')
disp(' ')
if (extchoice == 0)
disp('------------------------------------------------------------------------------------')   
disp(' EXTERNAL MODE IS CHOSEN')
disp('------------------------------------------------------------------------------------')
end

if (extchoice == 1)
disp('------------------------------------------------------------------------------------')
disp(' NORMAL MODE IS CHOSEN')
disp('------------------------------------------------------------------------------------')
end
disp(' ')
choice=input(' Choose one of the options: ');
disp(' ')

if ((choice == 0)|(choice > 9))
if (choice<12)
disp(' OPTION NOT YET IMPLEMENTED ')
else
disp(' WRONG OPTION NUMBER ')
end
else

if (isunix)
delete('*.mex*')
end

if (ispc)
    if (strcmp(computer,'PCWIN'))
        delete('*.mexw32')
    end   
    if (strcmp(computer,'PCWIN64'))
        delete('*.mexw64')
    end 
end

copyfile('../GENERATED_files_process_c_h/*','.')
copyfile('../common/files_c_h/common_c/*','.')
copyfile('../common/files_c_h/simulink/*','.')
copyfile('../common/files_c_h/lin_alg/*','.')
copyfile('../common/files_c_h/osg/*','.')
copyfile('../common/files_c_h/lapack/*','.')

copyfile('../common/files_osg/axes.osg','.')
copyfile('../common/files_osg/point.osg','.')
copyfile('../common/files_osg/vector.osg','.')

copyfile('../solids/*.*','./solids')

% if (extchoice == 0)
% set_param('main_hexaglide_discrete', 'SimUserIncludeDirs', '../GENERATED_files_process_c_h ../common/files_c_h/common_c ../common/files_c_h/simulink ../common/files_c_h/lin_alg ../common/files_c_h/osg ../common/files_c_h/lapack ../GENERATED_files_osg/cpp ../GENERATED_files_osg/h')
% end

if (choice == 1)
  disp('LAPACK Discrete')
mex  -v -DLAPACK  -DCOORD_DEP -DEULER -DDDL c_s_func_discrete.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c newton_raphson_min_norm.c -lm -lblas -llapack
end

if (choice == 2)
  disp('Q EULER DDL with LDL decomposition')
  if (isunix)
   mex -v -DLIN_ALG -DCOORD_DEP -DEULER -DDDL -DTRI  c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c -lm
  end
  if (ispc)
   mex -v -DLIN_ALG -DCOORD_DEP -DEULER -DDDL  -DTRI c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c  Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define LAPACK\n');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define EULER\n');
  fprintf(fid,'#define DDL\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
 set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c')
 end
end

if (choice == 3)
  disp('Q EULER DDQ with LDL decomposition')
  if (isunix)
   mex -v -DLIN_ALG -DCOORD_DEP -DEULER -DDDQ  -DTRI c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c -lm
  end
  if (ispc)
   mex -v -DLIN_ALG -DCOORD_DEP -DEULER -DDDQ -DTRI c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define LIN_ALG\n');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define EULER\n');
  fprintf(fid,'#define DDQ\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c')
  end
 end

if (choice == 4)
  disp('Q TRAPEZOIDAL DDL with LDL decomposition')
  if (isunix)
   mex -v -DLIN_ALG -DCOORD_DEP -DTRAPEZOIDAL -DDDL  -DTRI c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c -lm
  end
   if (ispc)
  mex -v -DLIN_ALG -DCOORD_DEP -DTRAPEZOIDAL -DDDL  -DTRI c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c
   end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define LIN_ALG\n');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fprintf(fid,'#define DDL\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c  Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c')
  end
 end

if (choice == 5)
  disp('Q TRAPEZOIDAL DDQ with LDL decomposition')
  if (isunix)
   mex -v -DLIN_ALG -DCOORD_DEP -DTRAPEZOIDAL -DDDQ  -DTRI c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c -lm
  end
  if (ispc)
   mex -v -DLIN_ALG -DCOORD_DEP -DTRAPEZOIDAL -DDDQ -DTRI c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define LIN_ALG\n');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fprintf(fid,'#define DDQ\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c')
  end
 end

if (choice == 6)
  disp('Z EULER with LU full pivot decomposition')
 if (isunix)
  mex  -v -DLIN_ALG -DCOORD_IND -DEULER c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c  M.c Q.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_euler_z.c -lm
 end
 if (ispc)
  mex -v -DLIN_ALG -DCOORD_IND -DEULER c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c  M.c Q.c  PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_euler_z.c 
 end
 if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define LIN_ALG\n');
  fprintf(fid,'#define COORD_IND\n');
  fprintf(fid,'#define EULER\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c  M.c Q.c  PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_euler_z.c')
 end
end



if (choice == 7)
  disp('Z TRAPEZOIDAL with LU full pivot decomposition')
 if (isunix)
  mex -v -DLIN_ALG -DCOORD_IND -DTRAPEZOIDAL c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c  M.c Q.c  PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c -lm
 end  
 if (ispc)
  mex -v -DLIN_ALG -DCOORD_IND -DTRAPEZOIDAL c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c  M.c Q.c  PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c
 end
 if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define LIN_ALG\n');
  fprintf(fid,'#define COORD_IND\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c  M.c Q.c  PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c')
 end
end

if (choice == 9)
  disp('LAPACK continous')
mex  -v -DLAPACK c_s_func_continous.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c newton_raphson_min_norm.c -lm -lblas -llapack
end

copyfile('../GENERATED_files_osg/cpp','.')
copyfile('../GENERATED_files_osg/h','.')

if (isunix)
mex -v osg_c_s_func.cpp gen_coord.c gen_vel.c param.c unknowns.c inputs.c solids_homogeneous_matrix.cpp osg_root.cpp osg_read_file.cpp osg_state.cpp -lOpenThreads -losg -losgDB -losgUtil -losgViewer -losgGA
end

if (ispc)
INCLUDESPATH = strcat('-I', OSGWINPATH, '\include')
LIBSPATH = strcat('-L', OSGWINPATH, '\lib')
mex  -v osg_c_s_func.cpp gen_coord.c gen_vel.c param.c unknowns.c inputs.c solids_homogeneous_matrix.cpp osg_root.cpp osg_read_file.cpp osg_state.cpp -I'C:\OpenSceneGraph\include' -L'C:\OpenSceneGraph\lib'  -lOpenThreads -losg -losgDB -losgUtil -losgViewer -losgGA  
end


delete('*.c')
delete('*.h')
delete('*.cpp')
delete('*.cc')
delete('*.*~')


copyfile('../GENERATED_files_matlab/environment.m','.')

end
