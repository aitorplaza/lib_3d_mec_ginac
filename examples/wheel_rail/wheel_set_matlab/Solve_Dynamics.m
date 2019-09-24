

MX=[Mn,dPhi_dqn';dPhi_dqn,Zeros];
QG=[Deltan;Gamman];

ddqlambda=inv(MX)*QG;

ddq=ddqlambda(1:q_size);
unkn=ddqlambda(q_size+1:length(ddqlambda));




