%% Problema DINAMICO DIRECTO robot paralelo HEXAGLIDE.
% Se uliliza vector completo q de coordenadas.
clear all;

%% Definicion de parametros, coordenadas, velocidades y fuerzas iniciales.

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


%tau=[100,100,100,100,100,100]'; % Se definen los valores iniciales de TAU.

%% POSICION.VELOCIDAD INICIAL. Cinematica directa.

% POSICION: RESOLVER SISTEMA NO LINEAL TAMA�O 24 EC 24 INCOG.

q_indep_0 = q(1:6);     % posicion inicial coord indep. Real
% q_dep_0 = q(7:24);
q = fsolve(@(q) PhiInit(q,q_indep_0),q,optimset('display','off','TolFun',10^-12));


% COORD. posicion inicial CALCULADAS (las indep no varian).
comprobacion_pos_ini = sqrt(Phi(q,dq)' * Phi(q,dq))                                       % COMPROBAR = 0

% VELOCIDAD: RESOLVER SISTEMA LINEAL TAMA�O 24 EC 24 INCOG.

dq_indep_0 = dq(1:6);   % velocidad inicial coord indep. Real.
dq = -(PhiInit_q(q,dq)^-1 * (PhiInit_t(q,dq_indep_0)));                                % INVERTIR 24 X 24

% VELOC. inicial CALCULADAS (las indep no varian).
comprobacion_vel_ini_dPhi = sqrt((dPhi(q,dq))' * dPhi(q,dq))                        % COMPROBAR = 0
comprobacion_vel_ini_Phi_q_x_dq = sqrt((Phi_q(q,dq)*dq)' * Phi_q(q,dq)*dq)                % COMPROBAR = 0

%% Definicion vector tiempo antes de iteracion.
t_ini   = 0.00;     t_fin   = 0.10;     delta_t = 0.01;
tic;

%% Resolucion problema DINAMICO DIRECTO para instante t. + Integracion a t+delta_t y correccion
for t=t_ini:delta_t:t_fin;    % Define numero de iteraciones.
    %% Problema DINAMICO DIRECTO.

    % RESOLVER SISTEMA LINEAL TAMA�O 42 EC 42 INCOG.
    
    aux=MVPhi_qZero(q,dq)^-1 * QddPhi(q,dq);                                       % INVERTIR 42 X 42
    ddq=aux(1:24);
    epsilon=aux(25:42);
    
    
    
    % comprobacion_acel = sqrt((Phi_q(q,dq)*ddq + dPhi_q(q,dq)*dq)' * (Phi_q(q,dq)*ddq + dPhi_q(q,dq)*dq))
    % A = -Phi_d(q,dq)^-1 * Phi_z(q,dq);    MVPhi_qZero_ = MVPhi_qZero(q,dq);  V =MVPhi_qZero_(1:24,25:42);
    % comprobacion_w_f_enlace = ([eye(6);A]'*V*epsilon)' * ([eye(6);A]'*V*epsilon)
    
    %% Integrar en el TIEMPO
    
    q  = q+(dq+0.5*ddq*delta_t)*delta_t;
    
    dq = dq+ddq*delta_t;
    
    %% Corregir POSICION y VELOCIDAD en instante t+delta_t
    %
    % Hace correccion con numero variable de ITERACIONES ������
    
    % POSICION: RESOLVER SISTEMA NO LINEAL TAMA�O 24 EC 24 INCOG.
    
    q_indep_0 = q(1:6); % posicion coord indep. instanste t+delta_t. Real
    q = fsolve(@(q) PhiInit(q,q_indep_0),q,optimset('display','off','TolFun',10^-12));
    
    
    % COORD. instante t+delta_t CALCULADAS (las indep no varian).
    % comprobacion_pos = sqrt(Phi(q,dq)' * Phi(q,dq))                                         % COMPROBAR = 0
    
    % VELOCIDAD: RESOLVER SISTEMA LINEAL TAMA�O 24 EC 24 INCOG.

    dq_indep_0 = dq(1:6);   % velocidad coord indep. instanste t+delta_t. Real
    dq = -(PhiInit_q(q,dq)^-1 * (PhiInit_t(q,dq_indep_0)));                                % INVERTIR 24 X 24
    % VELOC. instante t+delta_t CALCULADAS (las indep no varian).
    % comprobacion_vel_dPhi = sqrt((dPhi(q,dq))' * dPhi(q,dq))                            % COMPROBAR = 0
    % comprobacion_vel_Phi_q_x_dq = sqrt((Phi_q(q,dq) * dq)'*Phi_q(q,dq)*dq)                    % COMPROBAR = 0

end
%% RESULTADOS
toc;    % esta linea va en pareja con la setencia tic
iter = t_fin / delta_t
tiempo_ciclo = toc / iter
z = q(1:6); z'
dz = dq(1:6); dz'
ddz = ddq(1:6); ddz'
comprobacion_acel = sqrt((Phi_q(q,dq)*ddq + dPhi_q(q,dq)*dq)' * (Phi_q(q,dq)*ddq + dPhi_q(q,dq)*dq))
comprobacion_pos = sqrt(Phi(q,dq)' * Phi(q,dq))                                           % COMPROBAR = 0
comprobacion_vel_dPhi = sqrt((dPhi(q,dq))' * dPhi(q,dq))                            % COMPROBAR = 0
comprobacion_vel_Phi_q_x_dq = sqrt((Phi_q(q,dq) * dq)'*Phi_q(q,dq)*dq)                    % COMPROBAR = 0
