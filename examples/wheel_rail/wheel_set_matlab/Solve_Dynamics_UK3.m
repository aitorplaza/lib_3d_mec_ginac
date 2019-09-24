n_q=length(Qn);
n_q_nonaux = 6;
n_phi=length(Gamman);
n_lambdac = 2;
n_lambdaq = 6;
M_qq=Mn(1:n_q_nonaux,1:n_q_nonaux);
Q_q=Qn(1:n_q_nonaux);

dPhi_dq_perm=dPhi_dqn(prm1,:);
dPhi_dq_cq=dPhi_dq_perm(1:n_lambdac,1:n_q_nonaux);

Gamma_perm = Gamman(prm1,:);
Gamma_c=Gamma_perm(1:n_lambdac,:);
Gamma_t=Gamma_perm(n_lambdac+1:n_phi,:);


ddq_aux=pinv(M_qq)*Q_q;
aux1=pinv( dPhi_dq_cq* pinv(M_qq) * dPhi_dq_cq');

aux2=(Gamma_c-dPhi_dq_cq*ddq_aux);

unkn_q = -aux1*aux2;
ddq_q = ddq_aux+pinv(M_qq)*dPhi_dq_cq'*aux1*aux2;



dPhi_dq_tq=dPhi_dq_perm(n_lambdac+1:n_phi,1:n_q_nonaux);
dPhi_dq_ts=dPhi_dq_perm(n_lambdac+1:n_phi,n_q_nonaux+1:n_q);

ddq_s=pinv(dPhi_dq_ts)*(Gamma_t-dPhi_dq_tq*ddq_q);
%ddq_s=pinv(dPhi_dq_ts)*(-dPhi_dq_tq*ddq_q);


ddq(1:n_q_nonaux)=ddq_q;
ddq(n_q_nonaux+1:n_q)=ddq_s;

unkn_perm= unkn(prm1,:);
unkn_perm(1:n_lambdac)=unkn_q; 
unkn=unkn_perm(prm2,:);
