% Se uliliza vector completo q de coordenadas.
clear all;
%% Definicion de parametros, coordenadas, velocidades y fuerzas iniciales.

global q;
global dq;
global param;
global unknowns;
global inputs;

param_init;     % Se definen valores de parametros (pi, longitudes, masas, Inercias, c, k, ....)
coord_init;     % Se definen los nombres de todas las coord. Se les asignan valores iniciales.
vel_init;       % Se definen los nombres de todas las veloc. Se les asignan valores iniciales.
unknowns_init;  % Se definen los nombres de todas las fuerzas de enlace. Se les asignan valores iniciales.
inputs_init;  	% Se definen los nombres de todas los inputs. Se les asignan valores iniciales.

param_vect_init; 		% Se define el vector param(n_param,1), y que lugar ocupa cada param dentro de ese vector. 
coord_vect_init;    % Se define el vector q(n_gen_coord,1), y que lugar ocupa cada coord. dentro de ese vector.  
vel_vect_init;      % Se define el vector dq(n_gen_vel,1), y que lugar ocupa cada coord. dentro de ese vector.  
unknowns_vect_init; % Se define el vector unknowns(n_unknowns,1) de las fuerzas de enlace.
inputs_vect_init; 	% Se define el vector inputs(n_inputs,1) de los inputs.

%% POSICION.VELOCIDAD INICIAL. Cinematica directa.
n_param = length(param);
n_gen_coord = length(q);
n_gen_vel = length(dq);
n_unknowns = length(unknowns);
n_inputs = length(inputs);

Phi_=Phi(q,dq);
n_coord_dep = length(Phi_);
n_coord_indep = n_coord_dep - n_gen_coord;
q_indep = q(1:n_coord_indep);

q = fsolve(@(q) PhiInit(q,dq),q,optimset('display','off','TolFun',10^-12));
dq = (pinv(dPhiInit_dq(q,dq)) * (BetaInit(q,dq)));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
name=strcat('matlab_state_euler_q_rt.dat');
fi=fopen(name,'w');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
delta_t = 0.001;
for t=0.000: delta_t :0.1;
	aux = pinv(MXdPhi_dqZero(q,dq)) * Qgamma(q,dq);
	ddq = aux(1:n_gen_vel);
	unknowns = aux((n_gen_vel+1):(n_gen_vel + n_unknowns));

	fprintf(fi,'%f\t%f\t %f\t%f\t %f\t%f\t %f\t\n',t,q(1),q(2),dq(1),dq(2),ddq(1),ddq(2));

	%% Integrar en el TIEMPO
	q  = q + (dq + 0.5 * ddq * delta_t ) * delta_t;
	dq = dq + ddq * delta_t;

	%% Corregir POSICION y VELOCIDAD en instante t+delta_t
	q = q - (pinv(Phi_q(q,dq)) * Phi(q,dq));
	delta_dq = (pinv(dPhi_dq(q,dq)) * (Beta(q,dq) - (dPhi_dq(q,dq) * dq))); % correction
	dq = dq + delta_dq;



end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fclose('all');


