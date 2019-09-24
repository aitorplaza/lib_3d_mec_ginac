n_q_nonaux = 6;
n_lambda = 10;

M_qq=Mn(1:n_q_nonaux,1:n_q_nonaux);
Q_q=Qn(1:n_q_nonaux);
dPhi_dq_q=dPhi_dqn(:,1:n_q_nonaux);

Gamma_q=Gamman;

aux1=inv( dPhi_dq_q* inv(M_qq) * dPhi_dq_q');
ddq_aux=inv(M_qq)*Q_q;
aux2=(Gamma_q-dPhi_dq_q*ddq_aux);

unkn_q = -aux1*aux2;
ddq_q = inv(M_qq)*dPhi_dq_q'*aux1*aux2 + ddq_aux;

%ddq(1:n_q_nonaux)=ddq_q;
%unkn = unkn_q ;

ddq_q
