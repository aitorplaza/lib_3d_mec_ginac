clear all


global q;
global dq;
global epsilon;

param_init;

coord_init;
coord_vect_init;

vel_init;
vel_vect_init;

joint_unknowns_vect_init;
joint_unknowns_init;

inputs_init;
inputs_vect_init;

%z = q(1:6);     
%d = q(7:24);    % posicion inicial coord dep. Estimada.
q = fsolve(@(q) PhiInit(q,dq),q,optimset('display','off','TolFun',10^-12));
%d = fsolve(@(d) Phi_aux(z,d,q,dq),d,optimset('display','off','TolFun',10^-12));
%[q,p,r]=qr_n_m(Phi_q(q,dq),q,zeros(18));

q

%q = [z;d]      % asignar al vector de coord. totales los valores de las coord, indep. y dep.

% ATENCION: Definida funcion Phi_aux(z,d)
% COORD. DEP. posicion inicial CALCULADAS (las indep no varian).
% comprobacion_pos_ini = sqrt(Phi_aux(z,d)' * Phi_aux(z,d))                                                 % COMPROBAR = 0

% VELOCIDAD: RESOLVER SISTEMA LINEAL TAMA�O 18 EC 18 INCOG.

%dz = dq(1:6);    % velocidad inicial coord indep. Real.
%dq = -(PhiInit_d(q,dq)^-1 * (Phi_z(q,dq)*dz));                                                                % INVERTIR 24 X 24
%dq = [dz;dd]     % asignar al vector de veloc. totales los valores de las veloc. indep. y dep.
