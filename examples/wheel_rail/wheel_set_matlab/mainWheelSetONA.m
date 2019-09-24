clear all

t=0;
environment;

t_final = 10.0;
delta_t = 0.001;


param(11)=50.0; %torque
param(3)=0.00; %pend
param(47)=0.0; %y0

NEWTON_RAPHSON_TOLERANCE = 1.0e-8;
X=[];

q(2) = 0.00;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initial Position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
error_PhiInit = sqrt(PhiInit(q,t,param)' * PhiInit(q,t,param));

while error_PhiInit > NEWTON_RAPHSON_TOLERANCE
    delta_q = pinv(PhiInit_q(q,t,param)) * PhiInit(q,t,param);
    q = q - delta_q;
    error_PhiInit = sqrt(PhiInit(q,t,param)' * PhiInit(q,t,param));
end

dq = pinv(dPhiInit_dq(q,t,param)) * (BetaInit(q,t,param));%
dq(1)=0.648644*1.0;%dx
dq(5)=1.29572*1.0;%db


prm1 =[3,8,1,2,4,5,6,7,9,10];
prm2 =[3,4,1,5,6,7,8,2,9,10];
%prm1 =[1,4,2,3,5,6];
%prm2 =[1,3,4,2,5,6];


Mn = M(q,t,param);
Qn = Q(q,dq,t,param,input);
dPhi_dqn= dPhi_dq(q,t,param);
Gamman = Gamma(q,dq,t,param);

Solve_Dynamics_UK3;

KalkerCoeffUpdate;
 
KalkerR = Kalker_linear([Output_(2)/Output_(6);Output_(3)/Output_(6);Output_(4)/Output_(6)],param( 39:42 ),aR,bR,param(34));
X=[X,[t;q;dq;Output_(2)/Output_(6);KalkerR(1)]];

%X=[X,[t;q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16)]];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Integration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for i=1:t_final/delta_t        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Output_=Output(q,dq,ddq,unkn,t,param,input);
velR=max(Output_(6),0.0001);
velL=max(Output_(16),0.0001);


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
G=D*(CKRq/velR + CKLq/velL);
%G=zeros(n_q_nonaux);
dq_q = dq(1:n_q_nonaux,:);
dq_q_k=dq_q;
dq_q = pinv(eye(n_q_nonaux) + delta_t*G)*(dq_q_k+F*delta_t);
dq(1:n_q_nonaux)=dq_q;

aux2=(Gamma_c-dPhi_dq_cq*pinv(M_qq)*Q2_q);


unkn_q = -aux1*aux2;

unkn_perm= unkn(prm1,:);
unkn_perm(1:n_lambdac)=unkn_q; 
unkn=unkn_perm(prm2,:);


q=q+dq*delta_t;


%Proj   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
error_nr= sqrt(Phi(q,t,param)'*Phi(q,t,param));
Phin = Phi(q,t,param);
Phin_perm = Phin(prm1);
Phi_t = Phin_perm(n_lambdac+1:n_phi,:);
error_nr= sqrt(Phi_t'*Phi_t); 
while error_nr > NEWTON_RAPHSON_TOLERANCE
%for j=1:2
    dPhi_dqn= dPhi_dq(q,t,param);

    dPhi_dq_perm=dPhi_dqn(prm1,:);
    dPhi_dq_ts = dPhi_dq_perm(n_lambdac+1:n_phi,n_q_nonaux+1:n_q);
    Phin = Phi(q,t,param);
    Phin_perm = Phin(prm1);
    Phi_t = Phin_perm(n_lambdac+1:n_phi,:);
    
    dPhi_dq_s = dPhi_dqn(:,n_q_nonaux+1:n_q);
    delta_s = - pinv(dPhi_dq_ts)*Phi_t;
    
    q(n_q_nonaux+1:n_q) = q(n_q_nonaux+1:n_q) + delta_s;
    error_nr= sqrt(Phi(q,t,param)'*Phi(q,t,param)); 
end

Phin = Phi(q,t,param);
Phin_perm = Phin(prm1);
Phi_c = Phin_perm(1:n_lambdac,:);
error_nr= sqrt(Phi_c'*Phi_c); 
%error_nr= sqrt(Phi(q,t,param)'*Phi(q,t,param));

while error_nr > NEWTON_RAPHSON_TOLERANCE
%for j=1:2 

    dPhi_dqn= dPhi_dq(q,t,param);
    
    dPhi_dqq = dPhi_dqn(:,1:n_q_nonaux);
    delta_q = -pinv(dPhi_dqq)*Phi(q,t,param);
    
    q(1:n_q_nonaux) = q(1:n_q_nonaux) + delta_q;
    error_nr= sqrt(Phi(q,t,param)'*Phi(q,t,param)); 
end



dPhi_dqn= dPhi_dq(q,t,param);
dPhi_dq_perm=dPhi_dqn(prm1,:);
dPhi_dq_cq=dPhi_dq_perm(1:n_lambdac,1:n_q_nonaux);

Betan = Beta(q,t,param);
Betan_perm = Betan (prm1);
Beta_c =Betan_perm (1:n_lambdac,:);
delta_dq = pinv(dPhi_dq_cq) * (Beta_c - dPhi_dq_cq * dq(1:n_q_nonaux,:));


dq(1:n_q_nonaux,:) = dq(1:n_q_nonaux,:) + delta_dq;

KalkerCoeffUpdate;

t=t+delta_t;
KalkerR = Kalker_linear([Output_(2)/Output_(6);Output_(3)/Output_(6);Output_(4)/Output_(6)],param( 39:42 ),aR,bR,param(34));
X=[X,[t;q;dq;Output_(2)/Output_(6);KalkerR(1)]];

end



save('new_int2.mat','X')
q


figure
subplot(5,1,1)
plot(X(1,:)',X(2,:)')
subplot(5,1,2)
plot(X(1,:)',X(16,:)')
subplot(5,1,3)
plot(X(1,:)',X(30,:)')
subplot(5,1,4)
plot(X(1,:)',X(31,:)')
subplot(5,1,5)
plot(X(1,:)',X(3,:)')

return 






