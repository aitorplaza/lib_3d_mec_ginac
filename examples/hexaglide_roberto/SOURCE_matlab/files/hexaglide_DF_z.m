%% Problema DINAMICO DIRECTO robot paralelo HEXAGLIDE.
% Se uliliza vector z y d de coord. indep. y dep.
clear all;

%% Definicion de parametros, coordenadas, y valores iniciales.

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

%param_init;     % Se definen 89 valores de parametros (pi, longitudes, masas, Inercias, c, k, ....)
%coord_init;     % Se definen los nombres de todas las coord. Se les asignan valores iniciales.
                % Las coord son 24, 6 indep (Z) y 18 dep (phi, theta y Cartesianas)
%vel_init;       % Se definen los nombres de todas las veloc. Se les asignan valores iniciales.
%epsilon_init;   % Se definen los nombres de todas las fuerzas de enlace. Se les asignan valores iniciales.

%coord_vect_init;    % Se define el vector q(24,1), y que lugar ocupa cada coord. dentro de ese vector.  
%vel_vect_init;      % Se define el vector dq(24,1), y que lugar ocupa cada coord. dentro de ese vector.  
%epsilon_vect_init;  % Se define el vector epsilon(18,1) de las fuerzas de enlace.

%% POSICION.VELOCIDAD INICIAL. Cinematica directa.

% POSICION: RESOLVER SISTEMA NO LINEAL TAMA�O 18 EC 18 INCOG.

z = q(1:6);     % posicion inicial coord indep. Real
d = q(7:24);    % posicion inicial coord dep. Estimada.
d = fsolve(@(d) Phi_aux(z,d),d,optimset('display','off','TolFun',10^-12));
%d = fsolve(@(d) Phi(q,dq),d,optimset('display','off','TolFun',10^-12));
q = [z;d]      % asignar al vector de coord. totales los valores de las coord, indep. y dep.
% ATENCION: Definida funcion Phi_aux(z,d)
% COORD. DEP. posicion inicial CALCULADAS (las indep no varian).
% comprobacion_pos_ini = sqrt(Phi_aux(z,d)' * Phi_aux(z,d))                                                 % COMPROBAR = 0

% VELOCIDAD: RESOLVER SISTEMA LINEAL TAMA�O 18 EC 18 INCOG.

dz = dq(1:6);    % velocidad inicial coord indep. Real.
dd = -(Phi_d(q,dq)^-1 * (Phi_z(q,dq)*dz));                                                                % INVERTIR 24 X 24
dq = [dz;dd]     % asignar al vector de veloc. totales los valores de las veloc. indep. y dep.
% VELOC. inicial CALCULADAS (las indep no varian).
% comprobacion_vel_ini_dPhi = sqrt((dPhi(q,dq))' * dPhi(q,dq))                                        % COMPROBAR = 0
% comprobacion_vel_ini_Phi_q_x_dq = sqrt((Phi_d(q,dq)*dd + Phi_z(q,dq)*dz)' * (Phi_d(q,dq)*dd + Phi_z(q,dq)*dz))  % COMPROBAR = 0

%% Definicion vector tiempo antes de iteracion.
t_ini   = 0.00;     t_fin   = 0.001;     delta_t = 0.001;
t=t_ini:delta_t:t_fin;
i = 0;
tic;

%% Resolucion problema DINAMICO DIRECTO para instante t. + Integracion a t+delta_t y correccion
for t=t_ini:delta_t:t_fin;    % Define numero de iteraciones.
    %% Problema DINAMICO DIRECTO.

    i = i + 1;
    
    % RESOLVER SISTEMA LINEAL TAMA�O 6 EC 6 INCOG.
    %omega = pi; c = cos(omega*t); s = sin(omega*t); cc = cos(omega*t+(pi/4));
    %tau=1*[c;c;c;c;c;c]; % Se definen los valores iniciales de TAU.
    %tau=100*[1;1;1;1;1;1]; % Se definen los valores iniciales de TAU.
    TAU(:,i) = inputs;
    time(i) = t;
    
    Inv_Phi_d = Phi_d(q,dq)^-1;                                                         % INVERTIR 18 X 18
    A  = -(Inv_Phi_d * Phi_z(q,dq));
    IA = [eye(6);A];
    B  = -(Inv_Phi_d * (dPhi_q(q,dq)*dq));
    OB = [zeros(6,1);B];
    ddz = (IA'*M(q,dq)*IA)^-1 * (IA'*(Q(q,dq) - M(q,dq)*OB));     % INVERTIR 6 X 6
    ddd = A*ddz + B;
    ddq = [ddz;ddd];
    % comprobacion_acel = sqrt((Phi_q(q,dq)*ddq + dPhi_q(q,dq)*dq)' * (Phi_q(q,dq)*ddq + dPhi_q(q,dq)*dq))

    ZZ11(i) = q(1);     ZZ12(i) = q(2);
    XX(i) = q(19);      YY(i) = q(20);      ZZ(i) = q(21);
    AA(i) = q(22);      BB(i) = q(23);      CC(i) = q(24);
    
    %% Integrar en el TIEMPO
    
    z  = z + (dz+0.5*ddz*delta_t)*delta_t;
    d  = d + (dd+0.5*ddd*delta_t)*delta_t;
    dz = dz + ddz*delta_t;
    
    %% Corregir POSICION y VELOCIDAD en instante t+delta_t
    %
    % Hace correccion con numero variable de ITERACIONES ������
    
    % POSICION: RESOLVER SISTEMA NO LINEAL TAMA�O 18 EC 18 INCOG.

    d = fsolve(@(d) Phi_aux(z,d),d,optimset('display','off','TolFun',10^-12));
    q = [z;d];      % asignar al vector de coord. totales los valores de las coord, indep. y dep.

    % ATENCION: Definida funcion Phi_aux(z,d)
    % COORD. instante t+delta_t CALCULADAS (las indep no varian).
    % comprobacion_pos = sqrt(Phi_aux(z,d)' * Phi_aux(z,d))                                                 % COMPROBAR = 0

    % VELOCIDAD: RESOLVER SISTEMA LINEAL TAMA�O 18 EC 18 INCOG.

    dd = -(Phi_d(q,dq)^-1 * (Phi_z(q,dq)*dz));                                                            % INVERTIR 18 X 18
    dq = [dz;dd];     % asignar al vector de veloc. totales los valores de las veloc. indep. y dep.
    % VELOC. instante t+delta_t CALCULADAS (las indep no varian).
    % comprobacion_vel_dPhi = sqrt((dPhi(q,dq))' * dPhi(q,dq))                                        % COMPROBAR = 0
    % comprobacion_vel_Phi_q_x_dq = sqrt((Phi_d(q,dq)*dd + Phi_z(q,dq)*dz)' *(Phi_d(q,dq)*dd + Phi_z(q,dq)*dz))   % COMPROBAR = 0
    
end
%% RESULTADOS
toc;    % esta linea va en pareja con la setencia tic
iter = t_fin / delta_t
tiempo_ciclo = toc / iter
z'
dz'
ddz'
comprobacion_acel = sqrt((Phi_q(q,dq)*ddq + dPhi_q(q,dq)*dq)' * (Phi_q(q,dq)*ddq + dPhi_q(q,dq)*dq))
comprobacion_pos = sqrt(Phi_aux(z,d)' * Phi_aux(z,d))                                                 % COMPROBAR = 0
comprobacion_vel_dPhi = sqrt((dPhi(q,dq))' * dPhi(q,dq))                                        % COMPROBAR = 0
comprobacion_vel_Phi_q_x_dq = sqrt((Phi_d(q,dq)*dd + Phi_z(q,dq)*dz)' * (Phi_d(q,dq)*dd + Phi_z(q,dq)*dz))  % COMPROBAR = 0

figure(1)
%TAU_1=TAU(1,:);
subplot(2,2,1),plot(time, TAU(1,:),'b',time, TAU(2,:),'r')
title('TAU');grid on;legend('TAU11','TAU12');
subplot(2,2,2),plot(time, ZZ11,'b',time, ZZ12,'r')
title('Glide position');grid on;legend('Z11','Z12');
subplot(2,2,3),plot(time, XX,'b',time, YY,'r',time, ZZ,'c')
title('Platform XYZ position');grid on;legend('X','Y','Z');
subplot(2,2,4),plot(time, AA,'b',time, BB,'r',time, CC,'c')
title('Platform ABC angles');grid on;legend('A','B','C');
