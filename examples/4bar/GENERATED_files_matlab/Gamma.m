function Gamma_ = Gamma(q,dq,time,param)

theta1 = q( 1 ); 
theta2 = q( 2 ); 
theta3 = q( 3 ); 

dtheta1 = dq( 1 ); 
dtheta2 = dq( 2 ); 
dtheta3 = dq( 3 ); 

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
atom163 = l3*cos(theta3);
atom26 = cos(theta2);
atom167 = atom164*atom27;
atom14 = cos(theta1);
atom186 = -atom163*atom26-atom167;
atom170 = atom164*atom26;
atom183 = atom170-atom163*atom27;
atom15 = sin(theta1);
atom193 = atom14*atom186-atom183*atom15;
atom199 = dtheta3*atom193;
atom165 = l2+atom163;
atom168 = atom167+atom165*atom26;
atom171 = -atom165*atom27+atom170;
atom174 = atom15*atom171;
atom190 = -atom14*atom168-atom174;
atom172 = atom168+l1;
atom200 = atom190*dtheta2;
atom188 = atom14*atom183+atom186*atom15;
atom177 = atom14*atom171;
atom181 = -atom168*atom15+atom177;
atom194 = dtheta3*atom188;
atom195 = dtheta2*atom181;

Gamma_ = [-dtheta3*(dtheta2*atom193+dtheta1*atom193+atom199)-dtheta2*(atom200+atom190*dtheta1+atom199)+dtheta1*(dtheta1*(atom174+atom172*atom14)-atom200-atom199);
dtheta3*(dtheta2*atom188+atom194+dtheta1*atom188)+dtheta1*(atom194-dtheta1*(atom172*atom15-atom177)+atom195)+dtheta2*(atom194+dtheta1*atom181+atom195)];

%endfunction
