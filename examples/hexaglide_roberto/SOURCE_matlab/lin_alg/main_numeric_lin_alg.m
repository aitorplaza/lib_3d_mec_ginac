%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
copyfile('./GENERATED_files_matlab/*.m','.'); % First, copy this folder in working directory.
TIME='ON'
%TIME='OFF'
%% Definicion de parametros, coordenadas, velocidades y fuerzas iniciales.
USER_defines;
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (1)
COORD='COORD_DEP';
INTEG='EULER';
name='matlab_state_euler_q.dat'
Init_variables_parameters;
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (1)
COORD='COORD_IND';
INTEG='EULER';
name='matlab_state_euler_z.dat'
Init_variables_parameters;
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (1)
COORD='COORD_DEP';
INTEG='TRAPEZOIDAL';
name='matlab_state_trapezoidal_q.dat'
Init_variables_parameters;
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (1)
COORD='COORD_IND';
INTEG='TRAPEZOIDAL';
name='matlab_state_trapezoidal_z.dat'
Init_variables_parameters;
Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.
Forward_Dynamics;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (1)
COORD='COORD_DEP';
INTEG='I3AL';
name='matlab_state_i3al_q.dat'
Init_variables_parameters;

Initial_position_velocity; %% POSICION.VELOCIDAD INICIAL. Cinematica directa.

LAMBDA = zeros(n_unknowns,1);
ALFA = alfa * eye(n_coord_dep);
aux = inv(MXdPhi_dqZero(q,dq)) * Qgamma(q,dq);
ddq = aux(1:n_gen_vel);
unknowns = aux((n_gen_vel+1):(n_gen_vel + n_unknowns));

Forward_Dynamics_I3AL;
Results;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
delete_GENERATED_files_matlab;
