clear all

t=0;
environment;

t_final = 10.0;
delta_t = 0.001;
alpha=0.001;

param(11)=50.0; %torque
NEWTON_RAPHSON_TOLERANCE = 1.0e-8;
X=[];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initial Position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
error_PhiInit = sqrt(PhiInit(q,t,param)' * PhiInit(q,t,param));

while error_PhiInit > NEWTON_RAPHSON_TOLERANCE
    delta_q = pinv(PhiInit_q(q,t,param)) * PhiInit(q,t,param);
    q = q - delta_q;
    error_PhiInit = sqrt(PhiInit(q,t,param)' * PhiInit(q,t,param));
end

%dq = pinv(dPhiInit_dq(q,t,param)) * (BetaInit(q,t,param));
dq(1)=0.648644;%dx
dq(5)=1.29572*1.0;%db


Solve_Dynamics_UK3;

KalkerCoeffUpdate;


X=[X,[q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16)]];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Integration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for i=1:t_final/delta_t        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

dq_pre=dq;

Solve_Dynamics_Alpha;


dq=(1-alpha)*dq+alpha*(dq_pre+ddq*delta_t);
%dq=dq + alpha*ddq*delta_t;

%dq=(eye(2)-(Mn^-1*(-C_(q,dq,t,param))*delta_t))^-1*(dq+(M_(q,t,param)^-1*delta_(q,dq,t,param))*delta_t);


k=0;


%while norm(dq-dq_pre)>0.0001*delta_t
while norm(dq-dq_pre)>alpha*delta_t
    dq_pre=dq;
    
    Solve_Dynamics_Alpha;

    dq=(1-alpha)*dq+alpha*(dq_pre+ddq*delta_t);
    %k=k+1;
end

%~ if (k>0)
%~ [k,t]
%~ end;



q=q+0.5*(dq_pre+dq)*delta_t;



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
t=t+delta_t;



%KalkerR = Kalker_linear([Output_(2)/Output_(6);Output_(3)/Output_(6);Output_(4)/Output_(6)],param( 39:42 ),aR,bR,param(34));



%X=[X,[q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16);KalkerR(1)]];
X=[X,[q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16)]];



end

figure
subplot(4,1,1)
plot(0:delta_t:t_final,X(1,:)')
subplot(4,1,2)
plot(0:delta_t:t_final,X(15,:)')
subplot(4,1,3)
plot(0:delta_t:t_final,X(29,:)')
subplot(4,1,4)
plot(0:delta_t:t_final,X(30,:)')

%~ subplot(5,1,5)
%~ plot(0:delta_t:t_end,X(5,:)')

return 






