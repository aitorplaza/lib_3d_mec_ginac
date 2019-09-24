clear all

t=0;
environment;

t_final = 1.0;
delta_t = 0.001;
alpha=0.001;

param(11)=0.0; %torque
param(3)=0.00; %pend
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

dq = pinv(dPhiInit_dq(q,t,param)) * (BetaInit(q,t,param));
dq(1)=0.648644;%dx
dq(5)=1.29572*1.0;%db


prm1 =[3,8,1,2,4,5,6,7,9,10];
prm2 =[3,4,1,5,6,7,8,2,9,10];

Mn = M(q,t,param);
Qn = Q(q,dq,t,param,input);
dPhi_dqn= dPhi_dq(q,t,param);
Gamman = Gamma(q,dq,t,param);

Solve_Dynamics_UK3;

KalkerCoeffUpdate;
 
X=[X,[t;q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16)]];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Integration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for i=1:t_final/delta_t        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Output_=Output(q,dq,ddq,unkn,t,param,input);
velR=max(Output_(6),0.001);
velL=max(Output_(16),0.001);


Mn = M(q,t,param);
Q2n = Q2(q,dq,t,param);
dPhi_dqn= dPhi_dq(q,t,param);
Gamman = Gamma(q,dq,t,param);
CKRn= CKR(q,dq,t,param);
CKLn= CKL(q,dq,t,param);

n_q=length(Qn);
n_q_nonaux = 6;
n_phi=length(Gamman);
n_lambdac = 2;

M_qq=Mn(1:n_q_nonaux,1:n_q_nonaux);
Q2_q=Q2n(1:n_q_nonaux);

dPhi_dq_perm=dPhi_dqn(prm1,:);
dPhi_dq_cq=dPhi_dq_perm(1:n_lambdac,1:n_q_nonaux);

CKRq = CKRn(1:n_q_nonaux,1:n_q_nonaux);
CKLq = CKLn(1:n_q_nonaux,1:n_q_nonaux);

Gamma_perm = Gamman(prm1,:);
Gamma_c=Gamma_perm(1:n_lambdac,:);
Gamma_t=Gamma_perm(n_lambdac+1:n_phi,:);


aux1=pinv( dPhi_dq_cq* pinv(M_qq) * dPhi_dq_cq');
B=pinv(M_qq)*dPhi_dq_cq'*aux1;
D=(pinv(M_qq)-B*dPhi_dq_cq*pinv(M_qq));
F=B*Gamma_c + D*Q2_q;
%G=D*(CKRq/velR + CKLq/velL);
G=zeros(n_q_nonaux);
dq_q = dq(1:n_q_nonaux,:);
dq_q_k=dq_q;
dq_q = pinv(eye(n_q_nonaux) - delta_t*G)*(dq_q_k+F*delta_t);

dPhi_dq_tq=dPhi_dq_perm(n_lambdac+1:n_phi,1:n_q_nonaux);
dPhi_dq_ts=dPhi_dq_perm(n_lambdac+1:n_phi,n_q_nonaux+1:n_q);

H=pinv(dPhi_dq_ts)*Gamma_t;
K=pinv(dPhi_dq_ts)*dPhi_dq_tq;
dq_s_k = dq(n_q_nonaux+1:n_q);
dq_s = dq_s_k + H*delta_t - K*(dq_q -dq_q_k );


dq(1:n_q_nonaux) = dq_q;
dq(n_q_nonaux+1:n_q) = dq_s;


aux2=(Gamma_c-dPhi_dq_cq*pinv(M_qq)*Q2_q);
%aux2=(Gamma_c-dPhi_dq_cq*pinv(M_qq)*(Q2_q +(CKRq/velR + CKLq/velL)*dq_q ));
unkn_q = -aux1*aux2;

unkn_perm= unkn(prm1,:);
unkn_perm(1:n_lambdac)=unkn_q; 
unkn=unkn_perm(prm2,:);


%disp('********************************************************************')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%q=q+0.5*(dq_pre+dq)*delta_t;
q=q+dq*delta_t;

%Proj         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
error_nr= sqrt(Phi(q,t,param)'*Phi(q,t,param)); 
while error_nr > NEWTON_RAPHSON_TOLERANCE
    delta_q = - pinv(dPhi_dq(q,t,param)) * Phi(q,t,param); 
    q = q + delta_q;
    error_nr= sqrt(Phi(q,t,param)'*Phi(q,t,param)); 
end
delta_dq = (pinv(dPhi_dq(q,t,param)) * (Beta(q,t,param) - (dPhi_dq(q,t,param) * dq))) ;
dq = dq + delta_dq;


  
KalkerCoeffUpdate;

t=t+delta_t;

X=[X,[t;q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16)]];
end



save('new_int.mat','X')
q 
return
figure
subplot(4,1,1)
plot(X(1,:)',X(2,:)')
subplot(4,1,2)
plot(X(1,:)',X(16,:)')
subplot(4,1,3)
plot(X(1,:)',X(30,:)')
subplot(4,1,4)
plot(X(1,:)',X(31,:)')

%~ subplot(5,1,5)
%~ plot(0:delta_t:t_end,X(5,:)')

return 






