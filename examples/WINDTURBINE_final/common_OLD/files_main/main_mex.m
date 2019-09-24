function main_mex

OSGWINPATH='C:\Archivos de programa\OpenSceneGraph-3.0.1-VS10.0.30319-x86-release-12741';
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
disp('COMPILATION OPTIONS')
disp('------------------------------------------------------------------------------------')
disp(' 0: LAPACK Continous')
disp('------------------------------------------------------------------------------------')
disp(' 1: Q EULER with Qgamma and MXdPhi_dqZero matrices with INVERSE')
disp(' 2: Q EULER with Qgamma and MXdPhi_dqZero matrices with Cholesky decomposition')
disp(' 3: Q EULER with Q and M matrices with INVERSE')
disp(' 4: Q EULER with Q and M matrices with Cholesky decomposition')
disp(' ')
disp(' 5: Q TRAPEZOIDAL with Qgamma and MXdPhi_dqZero matrices with INVERSE')
disp(' 6: Q TRAPEZOIDAL with Qgamma and MXdPhi_dqZero matrices with Cholesky decomposition')
disp(' 7: Q TRAPEZOIDAL with Q and M matrices with INVERSE')
disp(' 8: Q TRAPEZOIDAL with Q and M matrices with Cholesky decomposition')
disp(' ')
disp(' 9: Q index-3 augmented Lagrangian with INVERSE')
disp('10: Q index-3 augmented Lagrangian with LU decomposition')
disp('------------------------------------------------------------------------------------')
disp('11: Z EULER with INVERSE')
disp('12: Z EULER Cholesky decomposition')
disp(' ')
disp('13: Z TRAPEZOIDAL with INVERSE')
disp('14: Z TRAPEZOIDAL with Cholesky decomposition')
disp(' ')
disp('15: Z index-3 augmented Lagrangian with INVERSE')
disp('16: Z index-3 augmented Lagrangian with LU decomposition')
disp('------------------------------------------------------------------------------------')
if (extchoice == 0)
disp('------------------------------------------------------------------------------------')   
disp('EXTERNAL MODE IS CHOSEN')
disp('------------------------------------------------------------------------------------')
end

if (extchoice == 1)
disp('------------------------------------------------------------------------------------')
disp('NORMAL MODE IS CHOSEN')
disp('------------------------------------------------------------------------------------')
end
disp('------------------------------------------------------------------------------------')
disp(' ')
choice=input('Choose one of the following options: ');
disp(' ')

if (isunix)
delete('*.mex*')
end

if (ispc)
    if (computer=='PCWIN')
        delete('*.mexw32')
    else
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

if (extchoice == 0)
set_param('main_hexaglide_discrete', 'SimUserIncludeDirs', '../GENERATED_files_process_c_h ../common/files_c_h/common_c ../common/files_c_h/simulink ../common/files_c_h/lin_alg ../common/files_c_h/osg ../common/files_c_h/lapack ../GENERATED_files_osg/cpp ../GENERATED_files_osg/h')
end

if (choice == 0)
  disp('LAPACK continuos')
mex  -v c_s_func_lapack.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c newton_raphson_min_norm.c -lm -lblas -llapack
end

if (choice == 1)
  disp('Q EULER DDL with INVERSE')
  if (isunix)
   mex -v -DCOORD_DEP -DEULER -DDDL -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c  Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c -lm
  end
  if (ispc)
   mex -v -DCOORD_DEP -DEULER -DDDL -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c  Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c 
  end
 if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define EULER\n');
  fprintf(fid,'#define DDL\n');
  fprintf(fid,'#define INV\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c  Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c')
 end
end

if (choice == 2)
  disp('Q EULER DDL with Cholesky decomposition')
  if (isunix)
   mex -v -DCOORD_DEP -DEULER -DDDL -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c -lm
  end
  if (ispc)
   mex -v -DCOORD_DEP -DEULER -DDDL -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c  Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define EULER\n');
  fprintf(fid,'#define DDL\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
 set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_euler_q.c')
 end
end
if (choice == 3)
  disp('Q EULER DDQ with INVERSE')
  if (isunix)
  mex -v -DCOORD_DEP -DEULER -DDDQ -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c -lm
  end
  if (ispc)
  mex -v -DCOORD_DEP -DEULER -DDDQ -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define EULER\n');
  fprintf(fid,'#define DDQ\n');
  fprintf(fid,'#define INV\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c')
  end
 end
if (choice == 4)
  disp('Q EULER DDQ with Cholesky decomposition')
  disp('Q EULER DDQ with INVERSE')
  if (isunix)
   mex -v -DCOORD_DEP -DEULER -DDDQ -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c -lm
  end
  if (ispc)
   mex -v -DCOORD_DEP -DEULER -DDDQ -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define EULER\n');
  fprintf(fid,'#define DDQ\n');
  fprintf(fid,'#define INV\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_euler_q.c')
  end
 end
if (choice == 5)
  disp('Q TRAPEZOIDAL DDL with INVERSE')
  if (isunix)
   mex -v -DCOORD_DEP -DTRAPEZOIDAL -DDDL -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c  Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c -lm
  end
  if (ispc)
   mex -v -DCOORD_DEP -DTRAPEZOIDAL -DDDL -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fprintf(fid,'#define DDL\n');
  fprintf(fid,'#define INV\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c  Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c')
  end
 end
if (choice == 6)
  disp('Q TRAPEZOIDAL DDL with Cholesky decomposition')
  if (isunix)
   mex -v -DCOORD_DEP -DTRAPEZOIDAL -DDDL -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c -lm
  end
   if (ispc)
  mex -v -DCOORD_DEP -DTRAPEZOIDAL -DDDL -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c
   end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fprintf(fid,'#define DDL\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c  Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Qgamma.c MXdPhi_dqZero.c one_step_trapezoidal_q.c')
  end
 end
if (choice == 7)
  disp('Q TRAPEZOIDAL DDQ with INVERSE')
  if (isunix)
   mex -v -DCOORD_DEP -DTRAPEZOIDAL -DDDQ -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c -lm
  end
  if (ispc)
   mex -v -DCOORD_DEP -DTRAPEZOIDAL -DDDQ -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fprintf(fid,'#define DDQ\n');
  fprintf(fid,'#define INV\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c')
  end
 end
if (choice == 8)
  disp('Q TRAPEZOIDAL DDQ with Cholesky decomposition')
  if (isunix)
   mex -v -DCOORD_DEP -DTRAPEZOIDAL -DDDQ -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c -lm
  end
  if (ispc)
   mex -v -DCOORD_DEP -DTRAPEZOIDAL -DDDQ -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_DEP\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fprintf(fid,'#define DDQ\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c Q.c M.c one_step_trapezoidal_q.c')
  end
 end
if (choice == 9)
  disp('This integrator is not fully checked. Option not available now')
end
if (choice == 10)
  disp('This integrator is not fully checked. Option not available now')
end
if (choice == 11)
  disp('Z EULER with INVERSE')
if (isunix)
  mex -v -DCOORD_IND -DEULER -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c  one_step_euler_z.c -lm
 end
 if (ispc)
  mex -v -DCOORD_IND -DEULER -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_euler_z.c.c
 end
 if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_IND\n');
  fprintf(fid,'#define EULER\n');
  fprintf(fid,'#define INV\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c  one_step_euler_z.c')
 end
end
if (choice == 12)
  disp('Z EULER with Cholesky decomposition')
 if (isunix)
  mex  -v -DCOORD_IND -DEULER -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_euler_z.c -lm
 end
 if (ispc)
  mex -v -DCOORD_IND -DEULER -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c  one_step_euler_z.c.c
 end
 if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_IND\n');
  fprintf(fid,'#define EULER\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c  one_step_euler_z.c')
 end
end

if (choice == 13)
  disp('Z TRAPEZOIDAL with INVERSE')
  if (isunix)
  mex -v -DCOORD_IND -DTRAPEZOIDAL -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c -lm
  end
  if (ispc)
  mex -v -DCOORD_IND -DTRAPEZOIDAL -DINV c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c.c
  end
  if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_IND\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fprintf(fid,'#define INV\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c')
  end
 end

if (choice == 14)
  disp('Z TRAPEZOIDAL with Cholesky decomposition')
 if (isunix)
  mex -v -DCOORD_IND -DTRAPEZOIDAL -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c -lm
 end  
 if (ispc)
  mex -v -DCOORD_IND -DTRAPEZOIDAL -DTRI c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c.c
 end
 if (extchoice == 0)
  fid = fopen('../GENERATED_files_process_c_h/external_def.h','w');
  fprintf(fid,'#define COORD_IND\n');
  fprintf(fid,'#define TRAPEZOIDAL\n');
  fprintf(fid,'#define TRI\n');
  fclose(fid);
  set_param('main_hexaglide_discrete', 'SimUserSources', 'c_s_func_linalg_discrete.c lin_alg.c time.c gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c Output.c Initial_position_velocity.c Phi.c Beta.c Gamma.c write_data_file.c Phi_z.c Phi_d.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c PhiInit.c PhiInit_q.c dPhiInit_dq.c BetaInit.c Phi_q.c dPhi_dq.c one_step_trapezoidal_z.c')
 end
 end


if (choice == 15)
  disp('This integrator is not fully checked. Option not available now')
end
if (choice == 16)
  disp('This integrator is not fully checked. Option not available now')
end

copyfile('../GENERATED_files_osg/cpp','.')
copyfile('../GENERATED_files_osg/h','.')

if ((choice~=9)&&(choice~=10)&&(choice~=15)&&(choice~=16))

    if (isunix)
    mex -v osg_c_s_func.cpp gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c solids_homogeneous_matrix.cpp osg_root.cpp osg_read_file.cpp osg_state.cpp -lOpenThreads -losg -losgDB -losgUtil -losgViewer -losgGA
    end

    if (ispc)
    INCLUDESPATH = strcat('-I', OSGWINPATH, '\include')
    LIBSPATH = strcat('-L', OSGWINPATH, '\lib')
    mex  -v osg_c_s_func.cpp gen_coord.c gen_vel.c gen_accel.c param.c unknowns.c inputs.c solids_homogeneous_matrix.cpp osg_root.cpp osg_read_file.cpp osg_state.cpp '-IC:\Archivos de programa\OpenSceneGraph-3.0.1-VS10.0.30319-x86-release-12741\include' '-LC:\Archivos de programa\OpenSceneGraph-3.0.1-VS10.0.30319-x86-release-12741\lib' -losg -losgDB -losgViewer -losgUtil -losgGA -lOpenThreads
    end

end

delete('*.c')
delete('*.h')
delete('*.cpp')
delete('*.cc')
delete('*.*~')

copyfile('../GENERATED_files_matlab/environment.m','.')

