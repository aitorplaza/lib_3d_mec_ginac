
aux1=pinv( (diag(weight)*dPhi_dqn) * pinv(Mn) * (diag(weight)*dPhi_dqn)');

ddq_aux=pinv(Mn)*Qn;

aux2=(Gamman-dPhi_dqn*ddq_aux);

unkn = -aux1*aux2;
ddq = ddq_aux+pinv(Mn)*dPhi_dqn'*aux1*aux2;

