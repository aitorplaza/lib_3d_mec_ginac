clear all;

environment;
t=0;

dPhi_dq_= dPhi_dq(q,t,param);
dPhi_dd_= dPhi_dq_(:,1:18);
dPhi_dz_= dPhi_dq_(:,19:24);


A=-pinv(dPhi_dd_)*dPhi_dz_;

M_=Mnew(q,t,param);

 
Mdd = M_(1:18,1:18);
Mdz = M_(1:18,19:24);
Mzz = M_(19:24,19:24);
Mzd = M_(19:24,1:18);

Mindep= (Mzz + Mzd * A + (Mzd * A)' + (A' *Mdd)*A);
printf ("Rank = %d\n", rank(Mindep));
printf ("SVD = %e\n", svd(Mindep)');

