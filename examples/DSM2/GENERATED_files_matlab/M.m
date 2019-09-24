function M_ = M(q,dq,ddq)

global t;
global g;
global theta1_0;
global psi_0;
global l1;
global l2;
global y0;
global z0;
global alpha;
global r;
global Cvis;
global mb1;
global I1b1;
global I2b1;
global I3b1;
global mb2;
global I1b2;
global I2b2;
global I3b2;
global mDisc;
global theta1;
global theta2;
global psi;
global y;
global z;
global dtheta1;
global dtheta2;
global dpsi;
global dy;
global dz;
if nargin == 3
global ddtheta1;
global ddtheta2;
global ddpsi;
global ddy;
global ddz;
end
global lambda1;
global lambda2;
global lambda3;
global lambda4;
global Torque;

theta1 = q( 1); 
theta2 = q( 2); 
psi = q( 3); 
y = q( 4); 
z = q( 5); 
dtheta1 = dq( 1); 
dtheta2 = dq( 2); 
dpsi = dq( 3); 
dy = dq( 4); 
dz = dq( 5); 
if nargin == 3
ddtheta1 = ddq( 1); 
ddtheta2 = ddq( 2); 
ddpsi = ddq( 3); 
ddy = ddq( 4); 
ddz = ddq( 5); 
end

M_ = [-mDisc*((l1*cos(-theta2)+l2)^2+l1^2*sin(-theta2)^2)-l1^2*mb2-I1b1-l1*cos(-theta2)*l2*mb2-I1b2 , l2*(l1*cos(-theta2)+l2)*mDisc+(0.5)*l1*cos(-theta2)*l2*mb2+I1b2 , 0 , 0 , 0;
l2*(l1*cos(-theta2)+l2)*mDisc+(0.5)*l1*cos(-theta2)*l2*mb2+I1b2 , -l2^2*mDisc-I1b2 , 0 , 0 , 0;
0 , 0 , -(0.5)*r^2*mDisc , 0 , 0;
0 , 0 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0];

%endfunction
