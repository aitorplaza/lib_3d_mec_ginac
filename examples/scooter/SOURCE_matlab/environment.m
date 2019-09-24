%------------ Coordinates -------------------
x=0.0;
theta=1.5707960000000000811;
%------------ Velocities -------------------
dx=0.0;
dtheta=0.0;
%------------ Auxiliar Coordinates -------------------
%------------ Auxiliar Velocities -------------------
%------------ Parameters -------------------
g=9.8000000000000007105;
d=0.5;
h=0.5;
kk=0.014999999999999999445;
Pi=0.0;
Cvis=0.8000000000000000444;
K=1.0;
mBlock=1.0;
mxBlock=0.0;
myBlock=0.0;
mzBlock=0.0;
IxxBlock=1.0;
IxyBlock=0.0;
IyyBlock=1.0;
IxzBlock=0.0;
IzzBlock=1.0;
IyzBlock=0.0;
mPendulum=1.0;
mxPendulum=0.0;
myPendulum=0.0;
mzPendulum=-1.0;
IxxPendulum=0.0;
IxyPendulum=0.0;
IyyPendulum=5.0;
IxzPendulum=0.0;
IzzPendulum=0.0;
IyzPendulum=0.0;
theta_0=2.0;
%------------ Joint_Unknowns -------------------
%------------ Inputs -------------------
FBlockx=0.0;
MPendulumy=0.0;
%------------q,dq,param Vectors -------------------
q=[x;theta;];
dq=[dx;dtheta;];
qaux=[];
dqaux=[];
param=[g;d;h;kk;Pi;Cvis;K;mBlock;mxBlock;myBlock;mzBlock;IxxBlock;IxyBlock;IyyBlock;IxzBlock;IzzBlock;IyzBlock;mPendulum;mxPendulum;myPendulum;mzPendulum;IxxPendulum;IxyPendulum;IyyPendulum;IxzPendulum;IzzPendulum;IyzPendulum;theta_0;];
unkn=[];
input=[FBlockx;MPendulumy;];
