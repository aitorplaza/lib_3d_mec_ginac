clear all

t=0;
environment;

t_final = 0.3;
delta_t = 0.001;


param(11)=50.0; %torque
param(3)=0.00; %pend
param(47)=0.0; %y0

NEWTON_RAPHSON_TOLERANCE = 1.0e-8;
X=[];

q(2) = 0.00;

n_q = 6;
n_s = 8;

s = qaux;
ds = dqaux;
dds = ddqaux;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initial Position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
error_PhiInit = sqrt(PhiInit(q,s,t,param)' * PhiInit(q,s,t,param));
dPhic_dqn= dPhic_dq(q,s,t,param);

PhiInit(q,s,t,param);
PhiInit_q(q,s,t,param);
pinv(PhiInit_q(q,s,t,param));
while error_PhiInit > NEWTON_RAPHSON_TOLERANCE
    delta_q = pinv(PhiInit_q(q,s,t,param)) * PhiInit(q,s,t,param);
    
    q = q - delta_q(1:n_q);
    s = s - delta_q(n_q+1:n_q+n_s);
    error_PhiInit = sqrt(PhiInit(q,s,t,param)' * PhiInit(q,s,t,param));
end



dq = pinv(dPhiInit_dq(q,s,t,param)) * (BetaInit(q,s,t,param));


dq = dq(1:n_q);
dq(1)=0.648644*1.0;%dx
dq(3)=1.29572*1.0;%db


n_ind = 4;
n_dep = 2;


Mn = M(q,t,param);
%Qn = Q(q,s,dq,ds,t,param,input);
Deltan = Delta(q,dq,t,param);
dPhic_dqn= dPhic_dq(q,s,t,param);
Gammacn = Gammac(q,s,dq,ds,t,param);

Solve_Dynamics_UK;

Outputn=Output(q,s,dq,ds,ddq,dds,unkn,t,param,input);
KalkerCoeffUpdate;

KalkerR = Kalker_linear([Outputn(2)/Outputn(6);Outputn(3)/Outputn(6);Outputn(4)/Outputn(6)],param( 39:42 ),aR,bR,param(34));

X=[X,[t;q;s;dq;ds;Outputn(2)/Outputn(6);KalkerR(1)]];

%X=[X,[t;q;dq;Output_(2)/Output_(6);Output_(12)/Output_(16)]];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Integration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for i=1:t_final/delta_t        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ddq_k=ddq;

%Output_=Output(q,dq,ddq,unkn,t,param,input);
velR=max(Outputn(6),0.0001);
velL=max(Outputn(16),0.0001);


Mn = M(q,t,param);
Deltan = Delta(q,dq,t,param);
dPhic_dqn= dPhic_dq(q,s,t,param);

perm = [];

CKRn= CKR(q,s,dq,t,param);
CKLn= CKL(q,s,dq,t,param);

Gammacn=Gammac(q,s,dq,ds,t,param);
Gammatn=Gammat(q,s,dq,ds,t,param);

Mzz = Mn (1:n_ind,1:n_ind);
Mzd = Mn (1:n_ind,n_ind+1:n_dep+n_ind);
Mdd = Mn (n_ind+1:n_dep+n_ind,n_ind+1:n_dep+n_ind);

dPhi_dq_cz = dPhic_dqn(:,1:n_ind);
dPhi_dq_cd = dPhic_dqn(:,n_ind+1:n_dep+n_ind);



A = -pinv(dPhi_dq_cd)*dPhi_dq_cz;
bv=zeros(n_dep,1);% Phi_t cero en este problema 
ba = -pinv(dPhi_dq_cd)*dPhic_dqn*q;% Phi_t cero en este problema 
Mind = Mzz + Mzd*A + (Mzd*A)'+ A'*Mdd*A;
D = -(Mzd +  A'*Mdd)*ba;

Q_z = Deltan(1:n_ind);
Q_d = Deltan(n_ind+1:n_dep+n_ind);
F=Q_z + A'*Q_d + D;


CK=(CKRn/velR + CKLn/velL);

CKzz = CK(1:n_ind,1:n_ind);
CKzd = CK(1:n_ind,n_ind+1:n_dep+n_ind);
CKdz = CK(n_ind+1:n_dep+n_ind,1:n_ind );
CKdd = CK(n_ind+1:n_dep+n_ind,n_ind+1:n_dep+n_ind);


H = F - (CKzd + A'*CKdd)*bv;
G = -(CKzz + A' * CKdz + (CKzd + A'*CKdd)*A);
dq_k= dq;
dz_k =dq_k(1:n_ind);
dd_k = dq_k(n_ind+1:n_dep+n_ind);

dz = pinv(Mind - G*delta_t)*(Mind*dz_k+H*delta_t);
dd = A * dz + bv;

dq = [dz;dd];


ddq = (dq-dq_k)/delta_t
ddq_aux=pinv(Mn)*Deltan;
aux1=pinv( dPhic_dqn* pinv(Mn) * dPhic_dqn');
aux2=(Gammacn-dPhic_dqn*ddq_aux);

unk_q = -aux1*aux2;
unkn(1:2,1) = unk_q;


q=q+dq*delta_t;


%Proj   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Phitn = Phit(q,s,t,param);
error_nr= sqrt(Phitn'*Phitn); 

while error_nr > NEWTON_RAPHSON_TOLERANCE
    dPhit_dsn= dPhit_ds(q,s,t,param);
    delta_s = - pinv(dPhit_dsn)*Phit(q,s,t,param);

    s = s + delta_s;
    
    Phitn = Phit(q,s,t,param);
    error_nr= sqrt(Phitn'*Phitn); 

end


Phicn = Phic(q,s,t,param);
error_nr= sqrt(Phicn'*Phicn);
while error_nr > NEWTON_RAPHSON_TOLERANCE
    dPhic_dqn= dPhic_dq(q,s,t,param);
    delta_q = - pinv(dPhic_dqn)*Phic(q,s,t,param);
    
    q = q + delta_q;
    
    Phicn = Phic(q,s,t,param);
    error_nr= sqrt(Phicn'*Phicn);
end


dPhic_dqn= dPhic_dq(q,s,t,param);
Betacn =Betac(q,s,t,param);
delta_dq = pinv(dPhic_dqn) * (Betacn - dPhic_dqn * dq);


dq = dq + delta_dq;

Outputn=Output(q,s,dq,ds,ddq,dds,unkn,t,param,input);
KalkerCoeffUpdate;

t=t+delta_t;

%return
KalkerR = Kalker_linear([Outputn(2)/Outputn(6);Outputn(3)/Outputn(6);Outputn(4)/Outputn(6)],param( 39:42 ),aR,bR,param(34));

X=[X,[t;q;s;dq;ds;Outputn(2)/Outputn(6);KalkerR(1)]];
end



save('new_int2.mat','X')
[q;s]


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






