%------------ Coordinates -------------------
theta1=1.0500000000000000444;
psi=0.0;
theta2=0.0;
y=2.1768999999999998352;
z=-0.13019000000000000017;
%------------ Velocities -------------------
dtheta1=0.0;
dpsi=0.0;
dtheta2=0.0;
dy=0;
dz=0;
%------------ Auxiliar Coordinates -------------------
%------------ Auxiliar Velocities -------------------
%------------ Parameters -------------------
g=9.8000000000000007105;
theta1_0=1.5;
psi_0=0.0;
l1=0.5;
l2=1.5;
y0=1.5;
z0=-0.5;
alpha=0.5;
b=0.5;
a=0.6999999999999999556;
Cvis=0.2000000000000000111;
mb1=1.0;
I1b1=0.10000000000000000555;
mb2=1.0;
I1b2=0.10000000000000000555;
mEllipse=1.0;
%------------ Joint_Unknowns -------------------
lambda1=0.0;
lambda2=0.0;
lambda3=0.0;
lambda4=0.0;
%------------ Inputs -------------------
Torque=0.0;
%------------q,dq,param Vectors -------------------
q=[theta1;psi;theta2;y;z;];
dq=[dtheta1;dpsi;dtheta2;dy;dz;];
qaux=[];
dqaux=[];
param=[g;theta1_0;psi_0;l1;l2;y0;z0;alpha;b;a;Cvis;mb1;I1b1;mb2;I1b2;mEllipse;];
unkn=[lambda1;lambda2;lambda3;lambda4;];
input=[Torque;];
