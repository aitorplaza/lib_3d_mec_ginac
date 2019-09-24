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
Beta_=Beta(q,dq);
n_vel_dep = length(Beta_);

n_coord_indep = n_gen_coord - n_coord_dep;
n_vel_indep = n_gen_vel - n_vel_dep;
q_indep = q(1:n_coord_indep);

z = q(1:n_coord_indep);
d = q((n_coord_indep+1):n_gen_coord);
d = fsolve(@(d) Phi_aux(z,d,q,dq),d,optimset('display','off','TolFun',10^-12));
q = [z;d];

dz = dq(1:n_vel_indep);
dd = (pinv(Phi_d(q,dq)) * (Beta(q,dq)-(Phi_z(q,dq)*dz)));
dq = [dz;dd];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
name=strcat('matlab_state_euler_zd_rt.dat');
fi=fopen(name,'w');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
delta_t = 0.001;
for t=0.000: delta_t :0.1;
	A  = -(pinv(Phi_d(q,dq)) * Phi_z(q,dq));
	b  = (pinv(Phi_d(q,dq)) * Gamma(q,dq));
	MZ = M_zz(q,dq)+ A' * M_zd(q,dq)' + M_zd(q,dq) * A + A' * M_dd(q,dq)' * A;
	QZ = (Q_z(q,dq) + A' * Q_d(q,dq)) - (M_zd(q,dq) + A' * M_dd(q,dq)') * b;
    
	ddz = pinv(MZ) * QZ;
	ddd = A*ddz + b;
	ddq = [ddz;ddd];

	fprintf(fi,'%f\t%f\t %f\t%f\t %f\t%f\t %f\t\n',t,q(1),q(2),dq(1),dq(2),ddq(1),ddq(2));

	%% Integrar en el TIEMPO
	z  = z + (dz+0.5*ddz*delta_t)*delta_t;
	d  = d + (dd+0.5*ddd*delta_t)*delta_t;
	q = [z;d];
	dz = dz + ddz*delta_t;
	dd = dd + ddd*delta_t; 
	dq = [dz;dd];

	%% Corregir POSICION y VELOCIDAD en instante t+delta_t
	d = fsolve(@(d) Phi_aux(z,d,q,dq),d,optimset('display','off','TolFun',10^-12));
	q = [z;d];
	delta_dd = (pinv(Phi_d(q,dq)) * (Beta(q,dq) - (Phi_z(q,dq) * dz))); % correction
	dd = dd + delta_dd;
	dq = [dz;dd];	

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fclose('all');

