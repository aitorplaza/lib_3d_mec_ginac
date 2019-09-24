function Energy_ = Energy(q,dq,ddq,time,param)

theta1 = q( 1 ); 
theta2 = q( 2 ); 
theta3 = q( 3 ); 

dtheta1 = dq( 1 ); 
dtheta2 = dq( 2 ); 
dtheta3 = dq( 3 ); 

ddtheta1 = ddq( 1 ); 
ddtheta2 = ddq( 2 ); 
ddtheta3 = ddq( 3 ); 

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


Energy_ = [0];

%endfunction
