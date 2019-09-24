clear all



coord_init
coord_vect_init
vel_init
vel_vect_init
unknowns_init
unknowns_vect_init
param_init
param_vect_init
inputs_init
inputs_vect_init


b_pend = 0.2;
torque = 0.0;

NEWTON_RAPHSON_TOLERANCE = 1.0e-8;
TRAPEZOIDAL_TOLERANCE = 1.0e-8;


%INTEG = 'EULER'
INTEG ='TRAPEZOIDAL'

t_final = 0.1
delta_t = 0.001;

% KALKER
E = 210e9; % MPa
nu = 0.27; %Steel
G = E/(2*(1-nu)); % MPa

error_PhiInit = sqrt(PhiInit(q,dq)' * PhiInit(q,dq));

while error_PhiInit > NEWTON_RAPHSON_TOLERANCE
    delta_q = pinv(PhiInit_q(q,dq)) * PhiInit(q,dq);
    q = q - delta_q;
    error_PhiInit = sqrt(PhiInit(q,dq)' * PhiInit(q,dq));
end

dq = pinv(dPhiInit_dq(q,dq)) * (BetaInit(q,dq));
q(1:6,1)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

t=0

while t < t_final
MXdPhi_dqZero_=MXdPhi_dqZero(q,dq);
Qgamma_=Qgamma(q,dq);
ddqlambda = inv(MXdPhi_dqZero_)*Qgamma_;
ddq=ddqlambda(1:14,1);

lambda=ddqlambda(15:22,1);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if strcmp(INTEG,'EULER')
    q  = q + (dq + 0.5 * ddq * delta_t ) * delta_t;
    dq = dq + ddq * delta_t;
end
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
         
		aux = MXdPhi_dqZero(q,dq) \ Qgamma(q,dq);
        ddq = aux(1:14,1);
        lambda = aux(15:22,1);
        
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

t = t +delta_t;

  error_nr= sqrt(Phi(q,dq)'*Phi(q,dq)); 
  while error_nr > NEWTON_RAPHSON_TOLERANCE
    delta_q = - pinv(dPhi_dq(q,dq)) * Phi(q,dq); 
    q = q + delta_q;
    error_nr= sqrt(Phi(q,dq)'*Phi(q,dq)); 
  end
  delta_dq = (pinv(dPhi_dq(q,dq)) * (Beta(q,dq) - (dPhi_dq(q,dq) * dq))); 
  dq = dq + delta_dq;

  

  
  
  N_L = sqrt(lambda(1)^2+lambda(2)^2+lambda(3)^2); % N dibujar
  N_R = sqrt(lambda(4)^2+lambda(5)^2+lambda(6)^2); % N
  
  Output_=Output(q,dq);
  Ry_wL = Output_(9); % m
  Ry_wR = Output_(10); % m
  Rx_rL = Output_(11); % m 
  Rx_rR = Output_(11); % m 
  
  Ry_rL = inf; % m
  Ry_rR = inf; % m
  Rx_wL = inf; % m  
  Rx_wR = inf; % m 
  
  R_L = [Rx_wL,Rx_rL,Ry_wL,Ry_rL];
  R_R = [Rx_wR,Rx_rR,Ry_wR,Ry_rR];

 
  [aL,bL] = Hertz_ellipse(N_L,R_L,E,nu);
  [aR,bR] = Hertz_ellipse(N_R,R_R,E,nu);
 
  KalkerCoeff_L = kalker_coeff(aL,bL,nu);
  KalkerCoeff_R = kalker_coeff(aR,bR,nu);

  if sqrt(Output_(3)^2 + Output_(3)^2 + Output_(5)^2 ) > 1e-4
    VxL  = Output_(3) / (0.5*Output_(3) + Output_(1));
    VyL  = 0;%Output_(4) / (0.5*Output_(4) + Output_(1));
    PHIL = 0;%Output_(5) / (0.5*Output_(5) + Output_(1));
%     VxL  = (Output_(3) - (Output_(10) * dq(5)) )/ (0.5 * (Output_(3) + Output_(10) * dq(5)) );
%     VyL  = 0;
%     PHIL = 0; 
%     VxL  = Output_(3) / Output_(1);
%     VyL  = Output_(4) / Output_(1);
%     PHIL = Output_(5) / Output_(1);
  else 
    VxL  = 0;
    VyL  = 0;
    PHIL = 0;
  end 
  VcreepL = [VxL;VyL;PHIL]

  if sqrt(Output_(6)^2 + Output_(7)^2 + Output_(8)^2 ) > 1e-4
    VxR  = Output_(6) / (0.5*Output_(6) + Output_(2));
    VyR  = 0;%Output_(7) / (0.5*Output_(7) + Output_(2));
    PHIR = 0;%Output_(8) / (0.5*Output_(8) + Output_(2));
%     VxR  = (Output_(6) - (Output_(11) * dq(5)) )/ (0.5 * (Output_(6) + Output_(11) * dq(5)) );
%     VyR  = 0;
%     PHIR = 0;
%     VxR  = Output_(6) / Output_(2);
%     VyR  = Output_(7) / Output_(2);
%     PHIR = Output_(8) / Output_(2);
  else 
    VxR  = 0;
    VyR  = 0;
    PHIR = 0; 
  end
  VcreepR = [VxR;VyR;PHIR]
pause
  Forces_Vcreep_L = Kalker_linear(VcreepL,KalkerCoeff_L,aL,bL,G)
  Forces_Vcreep_R = Kalker_linear(VcreepR,KalkerCoeff_R,aR,bR,G)
  pause
  
  Fx_L = Forces_Vcreep_L(1)
  Fx_R = Forces_Vcreep_R(1);
  Fy_L = 0.0;% -Forces_Vcreep_L(2); 
  Fy_R = 0.0;% -Forces_Vcreep_R(2);
  Mz_L = 0.0;% -Forces_Vcreep_L(3);
  Mz_R = 0.0;% -Forces_Vcreep_R(3); 

q(1:6,1)
%Output_(12:14)
end

q(1:6,1)










