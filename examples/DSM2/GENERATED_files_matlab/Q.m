function Q_ = Q(q,dq,ddq)

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

Q_ = [((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*g*mDisc+(0.5)*l1*mb1*g*cos(theta1)+(0.5)*l1*dtheta1^2*l2*mb2*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1))*cos(theta1)-Torque+l1*mb2*g*cos(theta1)-(0.5)*l1*sin(-theta2)*l2*mb2*(dtheta2-dtheta1)^2+(l1*cos(-theta2)+l2)*((dtheta1*mDisc*(dtheta1*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))-dtheta2*(dtheta1*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))*mDisc)*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1))-((dtheta2*sin(-theta2)*l2*cos(theta1)+dtheta2*cos(-theta2)*l2*sin(theta1)-dtheta1*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)))*dtheta1*mDisc+dtheta2*mDisc*(dtheta1*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))-dtheta2*sin(-theta2)*l2*cos(theta1)-dtheta2*cos(-theta2)*l2*sin(theta1)))*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1)))-(0.5)*l2*mb2*g*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))+dtheta1*Cvis+l1*sin(-theta2)*((dtheta1*mDisc*(dtheta1*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))-dtheta2*(dtheta1*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))*mDisc)*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))+((dtheta2*sin(-theta2)*l2*cos(theta1)+dtheta2*cos(-theta2)*l2*sin(theta1)-dtheta1*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)))*dtheta1*mDisc+dtheta2*mDisc*(dtheta1*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))-dtheta2*sin(-theta2)*l2*cos(theta1)-dtheta2*cos(-theta2)*l2*sin(theta1)))*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1)))+(0.5)*l1*dtheta1^2*l2*mb2*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))*sin(theta1);
-(0.5)*l1*dtheta1^2*l2*mb2*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1))*cos(theta1)-l2*((dtheta1*mDisc*(dtheta1*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))-dtheta2*(dtheta1*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))*mDisc)*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1))-((dtheta2*sin(-theta2)*l2*cos(theta1)+dtheta2*cos(-theta2)*l2*sin(theta1)-dtheta1*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)))*dtheta1*mDisc+dtheta2*mDisc*(dtheta1*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))-dtheta2*sin(-theta2)*l2*cos(theta1)-dtheta2*cos(-theta2)*l2*sin(theta1)))*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1)))+(0.5)*l2*mb2*g*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))-(0.5)*l1*dtheta1^2*l2*mb2*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))*sin(theta1)-(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*g*mDisc;
0;
0;
0];

%endfunction
