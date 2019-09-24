clear all

t=0;
environment;

q=[q;qaux];
dq=[dq;dqaux];
ddq=[ddq;ddqaux];

t_final = 0.00005;
delta_t = 0.00001;


INTEG = 'EULER'
%INTEG ='TRAPEZOIDAL' % Cambiar solver dynimics

param(11)=0.0; %torque
NEWTON_RAPHSON_TOLERANCE = 1.0e-8;
TRAPEZOIDAL_TOLERANCE = 1.0e-8;



weight=[1,1,1,0,0,1,1,1,0,0];
prm1 =[3,8,1,2,4,5,6,7,9,10];
prm2 =[3,4,1,5,6,7,8,2,9,10];
X=[];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initial Position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

error_PhiInit = sqrt(PhiInit(q,qaux,t,param)' * PhiInit(q,qaux,t,param));
dPhi_dqSize=size(dPhi_dq(q,qaux,t,param));
q_size = length(q);
Zeros=zeros(dPhi_dqSize(1));

while error_PhiInit > NEWTON_RAPHSON_TOLERANCE
    delta_q = pinv(PhiInit_q(q(1:6),q(7:14),t,param)) * PhiInit(q(1:6),q(7:14),t,param);
    q = q - delta_q;
    error_PhiInit = sqrt(PhiInit(q(1:6),q(7:14),t,param)' * PhiInit(q(1:6),q(7:14),t,param));
end
q
%dq = pinv(dPhiInit_dq(q,t,param)) * (BetaInit(q,t,param));
dq(1)=0.648644;%dx
dq(5)=1.29572*1.0;%db


Mn = M(q,t,param);
Qn = Q(q,qaux,dq,dqaux,t,param,input);
dPhi_dqn= dPhi_dq(q,qaux,t,param);
Gamman = Gamma(q,qaux,dq,dqaux,t,param);

%~ Solve_Dynamics;
Solve_Dynamics_UK3;




Output_=Output(q,qaux,dq,dqaux,ddq,ddqaux,unkn,t,param,input);

KalkerCoeffUpdate;



input(2:4) = Kalker_linear([Output_(2)/Output_(6);Output_(3)/Output_(6);Output_(4)/Output_(6)],param( 39:42 ),aR,bR,param(34));
input(5:7) = Kalker_linear([Output_(12)/Output_(16);Output_(13)/Output_(16);Output_(14)/Output_(16)],param( 43:46 ),aL,bL,param(34));




X=[X,[t;q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16)]];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Integration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for i=1:t_final/delta_t        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%for i=1:delta_t:t_final

Mn = M(q,t,param);
Qn = Q(q,dq,t,param,input);
dPhi_dqn= dPhi_dq(q,t,param);
Gamman = Gamma(q,dq,t,param);

%~ Solve_Dynamics;

Solve_Dynamics_UK3;


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




%Proj
error_nr= sqrt(Phi(q,t,param)'*Phi(q,t,param)); 
while error_nr > NEWTON_RAPHSON_TOLERANCE
    delta_q = - pinv(dPhi_dq(q,t,param)) * Phi(q,t,param); 
    q = q + delta_q;
    error_nr= sqrt(Phi(q,t,param)'*Phi(q,t,param)); 
end
delta_dq = (pinv(dPhi_dq(q,t,param)) * (Beta(q,t,param) - (dPhi_dq(q,t,param) * dq))); 
dq = dq + delta_dq;


KalkerCoeffUpdate;
Output_=Output(q,dq,ddq,unkn,t,param,input);


input(2:4) = Kalker_linear([Output_(2)/Output_(6);Output_(3)/Output_(6);Output_(4)/Output_(6)],param( 39:42 ),aR,bR,param(34));
input(5:7) = Kalker_linear([Output_(12)/Output_(16);Output_(13)/Output_(16);Output_(14)/Output_(16)],param( 43:46 ),aL,bL,param(34));

t=t+delta_t;


%KalkerR = Kalker_linear([Output_(2)/Output_(6);Output_(3)/Output_(6);Output_(4)/Output_(6)],param( 39:42 ),aR,bR,param(34));



%X=[X,[q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16);KalkerR(1)]];

X=[X,[t;q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16)]];

end
q
save('euler_int.mat','X')
return








