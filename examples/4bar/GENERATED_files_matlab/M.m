function M_ = M(q,time,param)

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

atom241 = -cos(theta2)*l1;
atom279 = l2-atom241;
atom240 = sin(theta2)*l1;
atom244 = -m2*atom241*cg2x+m2*atom240*cg2z;
atom0 = cos(theta3);
atom1 = sin(theta3);
atom43 = cg3z*m3;
atom42 = cg3x*m3;
atom295 = (atom1*atom279+atom0*atom240)*atom43+atom42*(atom0*atom279-atom1*atom240);
atom298 = l2*atom0*atom42+l2*atom1*atom43;
atom317 = -atom298-I2yy-I3yy-l2*m3*atom279-atom244-atom295;
atom318 = -I3yy-atom295;
atom320 = -atom298-I3yy;

M_ = [-I2yy-(atom240^2+atom279^2)*m3-I3yy-2*atom244-I1yy-2*atom295-m2*l1^2 , atom317 , atom318;
atom317 , -2*atom298-I2yy-I3yy-l2^2*m3 , atom320;
atom318 , atom320 , -I3yy];

%endfunction
