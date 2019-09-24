
ddq_aux=pinv(Mn)*Deltan;
aux1=pinv( dPhic_dqn* pinv(Mn) * dPhic_dqn');

aux2=(Gammacn-dPhic_dqn*ddq_aux);

unk_q = -aux1*aux2;
ddq = ddq_aux+pinv(Mn)*dPhic_dqn'*aux1*aux2;

unkn(1:2,1) = unk_q;