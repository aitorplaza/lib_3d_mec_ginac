%------------ Coordinates -------------------
x=0.0;
y=0.0;
z=0.0;
a=0.0;
b=0.0;
c=0.0;
theta_W_R=0.0;
u_W_R=0.0;
theta_W_L=0.0;
u_W_L=0.0;
u_R_R=0.0;
x_R_R=0.0;
u_R_L=0.0;
x_R_L=0.0;
%------------ Velocities -------------------
dx=0.0;
dy=0.0;
dz=0.0;
da=0.0;
db=0.0;
dc=0.0;
dtheta_W_R=0.0;
du_W_R=0.0;
dtheta_W_L=0.0;
du_W_L=0.0;
du_R_R=0.0;
dx_R_R=0.0;
du_R_L=0.0;
dx_R_L=0.0;
%------------ Auxiliar Coordinates -------------------
%------------ Auxiliar Velocities -------------------
%------------ Parameters -------------------
g=9.8000000000000007105;
b_pend=0.10000000000000000555;
L_R=1.0699999999999998401;
L_WHS=1.0660000000000000586;
mWHS=1222.0;
I_WHSx=376.60000000000002274;
I_WHSy=79.599999999999994316;
I_WHSz=376.60000000000002274;
awL=-59.809409171410003125;
bwL=-0.023792495869999999436;
cwL=-0.0089361341199999996115;
dwL=-0.5;
xwL=0.010000000000000000208;
awR=64.56790834618000474;
bwR=-0.023792495869999999436;
cwR=0.0089361341199999996115;
dwR=-0.5;
xwR=0.010000000000000000208;
arL=66.403345669995999856;
brL=1.998816728350000016;
crL=0.0;
drL=0.15900000000000000244;
xrL=0.005000000000000000104;
arR=66.403345669995999856;
brR=-1.998816728350000016;
crR=0.0;
drR=0.15900000000000000244;
xrR=0.005000000000000000104;
E_elastic=2.1E11;
nu_poisson=0.27000000000000001776;
G_elastic=1.4384E11;
Hertz_a_L=0.0;
Hertz_b_L=0.0;
Hertz_a_R=0.0;
Hertz_b_R=0.0;
C11=0.0;
C22=0.0;
C23=0.0;
C33=0.0;
%------------ Joint_Unknowns -------------------
lambda1=0.0;
lambda2=0.0;
lambda3=0.0;
lambda4=0.0;
lambda5=0.0;
lambda6=0.0;
lambda7=0.0;
lambda8=0.0;
lambda9=0.0;
lambda10=0.0;
%------------ Inputs -------------------
torque=0.0;
Fx_R=0.0;
Fy_R=0.0;
Mz_R=0.0;
Fx_L=0.0;
Fy_L=0.0;
Mz_L=0.0;
%------------q,dq,param Vectors -------------------
q=[x;y;z;a;b;c;theta_W_R;u_W_R;theta_W_L;u_W_L;u_R_R;x_R_R;u_R_L;x_R_L;];
dq=[dx;dy;dz;da;db;dc;dtheta_W_R;du_W_R;dtheta_W_L;du_W_L;du_R_R;dx_R_R;du_R_L;dx_R_L;];
qaux=[];
dqaux=[];
param=[g;b_pend;L_R;L_WHS;mWHS;I_WHSx;I_WHSy;I_WHSz;awL;bwL;cwL;dwL;xwL;awR;bwR;cwR;dwR;xwR;arL;brL;crL;drL;xrL;arR;brR;crR;drR;xrR;E_elastic;nu_poisson;G_elastic;Hertz_a_L;Hertz_b_L;Hertz_a_R;Hertz_b_R;C11;C22;C23;C33;];
unkn=[lambda1;lambda2;lambda3;lambda4;lambda5;lambda6;lambda7;lambda8;lambda9;lambda10;];
input=[torque;Fx_R;Fy_R;Mz_R;Fx_L;Fy_L;Mz_L;];
