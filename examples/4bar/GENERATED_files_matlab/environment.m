%------------ Coordinates -------------------
theta1=-1.5707960000000000811;
theta2=1.5707960000000000811;
theta3=1.5707960000000000811;
%------------ Velocities -------------------
dtheta1=0.0;
dtheta2=0.0;
dtheta3=0.0;
%------------ Acelerations -------------------
ddtheta1=0.0;
ddtheta2=0.0;
ddtheta3=0.0;
%------------ Auxiliar Coordinates -------------------
%------------ Auxiliar Velocities -------------------
%------------ auxiliar Acelerations -------------------
%------------ Parameters -------------------
g=9.8000000000000007105;
l1=0.4000000000000000222;
l2=2.0;
l3=1.1999999999999999556;
l4=1.6000000000000000888;
m1=1.0;
m2=1.0;
m3=1.0;
cg1x=0.2000000000000000111;
cg1z=0.10000000000000000555;
cg2x=1.0;
cg2z=0.10000000000000000555;
cg3x=0.5999999999999999778;
cg3z=0.10000000000000000555;
I1yy=1.0;
I2yy=1.0;
I3yy=1.0;
K=50.0;
l2x=1.0;
l2z=0.10000000000000000555;
l3x=0.5;
l3z=0.10000000000000000555;
%------------ Joint_Unknowns -------------------
lambda1=0.0;
lambda2=0.0;
%------------ Inputs -------------------
Fx2=0.0;
Fz2=0.0;
Fx3=0.0;
Fz3=0.0;
My2=0.0;
My3=0.0;
%------------q,dq,ddq,param , input, unknowns Vectors -------------------
q=[theta1;theta2;theta3;];
dq=[dtheta1;dtheta2;dtheta3;];
ddq=[ddtheta1;ddtheta2;ddtheta3;];
param=[g;l1;l2;l3;l4;m1;m2;m3;cg1x;cg1z;cg2x;cg2z;cg3x;cg3z;I1yy;I2yy;I3yy;K;l2x;l2z;l3x;l3z;];
unkn=[lambda1;lambda2;];
input=[Fx2;Fz2;Fx3;Fz3;My2;My3;];
