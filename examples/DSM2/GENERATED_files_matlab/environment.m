%------------ Coordinates -------------------
theta1=1.0500000000000000444;
theta2=0.0;
psi=0.0;
y=2.1768999999999998352;
z=-0.13019000000000000017;
%------------ Velocities -------------------
dtheta1=0.0;
dtheta2=0.0;
dpsi=0.0;
dy=0;
dz=0;
%------------ Acelerations -------------------
ddtheta1=0.0;
ddtheta2=0.0;
ddpsi=0.0;
ddy=0;
ddz=0;
%------------ Auxiliar Coordinates -------------------
%------------ Auxiliar Velocities -------------------
%------------ auxiliar Acelerations -------------------
%------------ Parameters -------------------
g=9.8000000000000007105;
theta1_0=1.5;
psi_0=0.0;
l1=0.5;
l2=1.5;
y0=1.5;
z0=-0.5;
alpha=0.5;
r=0.5;
Cvis=0.2000000000000000111;
mb1=1.0;
I1b1=0.10000000000000000555;
I2b1=0.10000000000000000555;
I3b1=0.10000000000000000555;
mb2=1.0;
I1b2=0.10000000000000000555;
I2b2=0.10000000000000000555;
I3b2=0.10000000000000000555;
mDisc=1.0;
%------------ Joint_Unknowns -------------------
lambda1=0.0;
lambda2=0.0;
lambda3=0.0;
lambda4=0.0;
%------------ Inputs -------------------
Torque=0.0;
%------------q,dq,ddq,param , input, unknowns Vectors -------------------
q=[theta1;theta2;psi;y;z;];
dq=[dtheta1;dtheta2;dpsi;dy;dz;];
ddq=[ddtheta1;ddtheta2;ddpsi;ddy;ddz;];
param=[g;theta1_0;psi_0;l1;l2;y0;z0;alpha;r;Cvis;mb1;I1b1;I2b1;I3b1;mb2;I1b2;I2b2;I3b2;mDisc;];
unkn=[lambda1;lambda2;lambda3;lambda4;];
input=[Torque;];
