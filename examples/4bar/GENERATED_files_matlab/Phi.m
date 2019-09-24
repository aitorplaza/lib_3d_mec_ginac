function Phi_ = Phi(q,time,param)

theta1 = q( 1 ); 
theta2 = q( 2 ); 
theta3 = q( 3 ); 

t= time ;

g = param( 1 ); 
l1 = param( 2 ); 
l2 = param( 3 ); 
l3 = param( 4 ); 
l4 = param( 5 ); 
m1 = param( 6 ); 
m2 = param( 7 ); 
m3 = param( 8 ); 
cg1x = param( 9 ); 
cg1z = param( 10 ); 
cg2x = param( 11 ); 
cg2z = param( 12 ); 
cg3x = param( 13 ); 
cg3z = param( 14 ); 
I1yy = param( 15 ); 
I2yy = param( 16 ); 
I3yy = param( 17 ); 
K = param( 18 ); 
l2x = param( 19 ); 
l2z = param( 20 ); 
l3x = param( 21 ); 
l3z = param( 22 ); 

atom164 = -sin(theta3)*l3;
atom27 = sin(theta2);
atom165 = l2+l3*cos(theta3);
atom26 = cos(theta2);
atom172 = atom165*atom26+l1+atom164*atom27;
atom14 = cos(theta1);
atom15 = sin(theta1);
atom171 = -atom165*atom27+atom164*atom26;

Phi_ = [atom15*atom171-l4+atom172*atom14;
atom14*atom171-atom172*atom15];

%endfunction