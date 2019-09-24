clear all
global delta_t;
m = 1222;
I = 79.6;
r=0.5;
g = 9.81;
alpha = 0.05;
Moment = +0.0;

M = [m,0;0,I];


F_kmax =  I*g*sin(alpha) / ((r^2) *(1+I/(m*r^2))); %Kalker's force max

F_k = 0;
delta = [m*g*sin(alpha)-F_k; Moment + F_k*r];
N= m*g*cos(alpha);

q = [0,0]';% q=[x, theta]
dq = [0.0,0]';dq = [1.01,2.0]';
ddq = [0,0]';
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 
q_buf=[];dq_buf=[];ddq_buf=[];t_buf=[];f_buf=[];Vcreep_buf=[];
t = 0;

%INTEG = 'EULER' % limit delta_t=1.5*1e-4;
INTEG = 'TRAPEZOIDAL' % limit delta_t=1.5*1e-4;
NEWTON_RAPHSON_TOLERANCE = 1.0e-8;
TRAPEZOIDAL_TOLERANCE = 1.0e-8;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% KALKER
E = 210e9; % MPa
nu = 0.27; %Steel
G = E/(2*(1-nu)); % MPa

N= m*g*cos(0.05);

R_w = 0.5;
r_r = 0.1;
Ry_w = R_w; % m
Rx_r = r_r; % m 
Ry_r = inf; % m
Rx_w = inf; % m  

Radii = [Rx_w,Rx_r,Ry_w,Ry_r];

% Initial force
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[a,b] = Hertz_ellipse(N,Radii,E,nu);
[F_k,Vcreep] = KLKR(a,b,dq);
disp('Initial creepage');Vcreep 
disp('----------------');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
q_buf=[q_buf;q'];dq_buf=[dq_buf,dq'];ddq_buf=[ddq_buf,ddq'];t_buf=[t_buf;t];f_buf=[f_buf;F_k];Vcreep_buf=[Vcreep_buf;Vcreep];

t_final = 1.0;
delta_t = 1*1e-4;

while t < t_final

% if t>1.0
%   Moment = +100.0;%dq(2)=0;ddq(2)=0;
% end

delta = [m*g*sin(alpha)-F_k; Moment + F_k*r];
ddq = inv(M)*delta;  

% EULER
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if strcmp(INTEG,'EULER')
    q  = q + (dq + 0.5 * ddq * delta_t ) * delta_t;
    dq = dq + ddq * delta_t;
  end
% TRAPEZOIDAL
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if strcmp(INTEG,'TRAPEZOIDAL')
    qn=q;
	dqn=dq;
    ddqn=ddq;
    
    % Euler mejorado
    q  = qn + (dqn + 0.5 * ddqn * delta_t ) * delta_t;
	dq = dqn + ddqn * delta_t;
    error= sqrt((q-qn)'*(q-qn))+sqrt((dq-dqn)'*(dq-dqn));

    iter=0;

	while error > TRAPEZOIDAL_TOLERANCE
        
        [F_k,Vcreep] = KLKR(a,b,dq);
        delta = [m*g*sin(alpha)-F_k; Moment + F_k*r];
        ddq = inv(M)*delta; 
        
        qn1=q;
        dqn1=dq;
        ddqn1=ddq;

		q= qn +  0.5 * delta_t * ( dqn + dqn1 );
		dq=dqn + 0.5 * delta_t * ( ddqn + ddqn1 );
   		error= sqrt((q-qn1)'*(q-qn1))+sqrt((dq-dqn1)'*(dq-dqn1));
		iter=iter+1;
    end
  end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  F_k = KLKR(a,b,dq);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
% F_k =  I*g*sin(alpha) / ((r^2) *(1+I/(m*r^2))); % max force to roll
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  


  t = t + delta_t;

q_buf=[q_buf;q'];dq_buf=[dq_buf;dq'];ddq_buf=[ddq_buf;ddq'];t_buf=[t_buf;t];f_buf=[f_buf;F_k];Vcreep_buf=[Vcreep_buf;Vcreep];
end
q
%dq
F_k
disp('final creepage');Vcreep
%plot(t_buf,f_buf)

