%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
copyfile('./lin_alg/*.m','.');
copyfile('./GENERATED_files_matlab/*.m','.');
on=1;off=0;
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDL';
LIN='INV';
INTEG='EULER';
name='matlab_state_euler_q_ddl_inv.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end

if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDL';
LIN='TRI';
INTEG='EULER';
name='matlab_state_euler_q_ddl_tri.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (off)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDQ';
INTEG='EULER';
name='matlab_state_euler_q_ddq.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (off)
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
COORD='COORD_DEP'; SIZE='DDL';LIN='INV';
INTEG='TRAPEZOIDAL';
name='matlab_state_trapezoidal_q_ddl.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDQ';LIN='INV';
INTEG='TRAPEZOIDAL';
name='matlab_state_trapezoidal_q_ddq.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (on)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_IND';LIN='INV';
INTEG='TRAPEZOIDAL';
name='matlab_state_trapezoidal_z.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (off)
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


if (off)
clear all;USER_defines;Init_variables_parameters;
COORD='COORD_DEP'; SIZE='DDL';
INTEG='I3AL';
name='matlab_state_i3al_q_ldl.dat'
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.

LAMBDA = zeros(n_unknowns,1);
ALFA = alfa * eye(n_coord_dep);
LAMBDA = unknowns;
Forward_Dynamics_I3AL_q_ldl;
Results;
end
%}

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (off)
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
