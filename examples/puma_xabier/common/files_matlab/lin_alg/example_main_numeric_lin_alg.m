%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
addpath('./common/files_matlab/lin_alg/');
addpath('./GENERATED_files_matlab/');
on=1;off=0;
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDL';
INTEG='EULER';
name='matlab_state_euler_q_ddl.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDQ';
INTEG='EULER';
name='matlab_state_euler_q_ddq.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_IND';
INTEG='EULER';
name='matlab_state_euler_z.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDL';
INTEG='TRAPEZOIDAL';
name='matlab_state_trapezoidal_q_ddl.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDQ';
INTEG='TRAPEZOIDAL';
name='matlab_state_trapezoidal_q_ddq.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_IND';
INTEG='TRAPEZOIDAL';
name='matlab_state_trapezoidal_z.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDL';
INTEG='I3AL';
name='matlab_state_i3al_q.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.

LAMBDA = zeros(n_unknowns,1);
ALFA = alfa * eye(n_coord_dep);
LAMBDA = unknowns;
Forward_Dynamics_I3AL_q;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_IND';
INTEG='I3AL';
name='matlab_state_i3al_z.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.

LAMBDA = zeros(n_unknowns,1);
ALFA = alfa * eye(n_coord_dep);
LAMBDA = unknowns;
Forward_Dynamics_I3AL_z;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%UNDER DEVELOPMENT
%UNDER DEVELOPMENT
%UNDER DEVELOPMENT

%{
if (off)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDL';
INTEG='I3AL';
name='matlab_state_i3al_q_emb.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.

LAMBDA = zeros(n_unknowns,1);
ALFA = alfa * eye(n_coord_dep);
LAMBDA = unknowns;
Forward_Dynamics_I3AL_q_emb;
Results;
end
%}

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
delete_GENERATED_files_matlab;
delete *.m~;
