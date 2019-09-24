syms phi psi theta e lp lb theta11 phi11 X real
syms mc11 g c11 dz11 Ma11z Klg m11 dphi11 theta11 phi11 mz11 dtheta11 real


%aux1=-( sin(phi)*cos(psi)-sin(psi)*sin(theta)*cos(phi))*e+lp*cos(theta)*cos(phi)-lb+cos(theta11)*l*sin(phi11)+X ;

aux1= -g*m11+1.0/Klg*Ma11z-( ( mz11*sin(theta11)*sin(phi11)/m11*dtheta11-mz11/m11*dphi11*cos(theta11)*cos(phi11))*dphi11+( mz11*sin(theta11)*sin(phi11)/m11*dphi11-mz11/m11*cos(theta11)*dtheta11*cos(phi11))*dtheta11)*m11-dz11*c11-mc11*g ;
%aux2=-e*( sin(phi)*cos(psi)-cos(phi)*sin(psi)*sin(theta))+l*cos(theta11)*sin(phi11)+X-lb+cos(phi)*cos(theta)*lp;

aux2=-m11*g+m11*( dtheta11*( cos(theta11)*mz11/m11*dtheta11*cos(phi11)-dphi11*mz11*sin(phi11)/m11*sin(theta11))+dphi11*( dphi11*cos(theta11)*mz11/m11*cos(phi11)-mz11*sin(phi11)/m11*dtheta11*sin(theta11)))+Ma11z/Klg-dz11*c11-g*mc11 ;

simple(aux1-aux2)
clear all
pi = 3.1415926535897931e+00
lp = 7.3084999999999997e-02
e = 6.8253999999999995e-02
lb = 4.8399999999999999e-01
l = 1.0;
 X =0.0
 phi11 =4.0000000000000002e-01
 theta11 =0.0
 phi =0.0
 theta =0.0
 psi =0.0

#define lp 7.3084999999999997e-02
#define e 6.8253999999999995e-02
#define lb 4.8399999999999999e-01
#define l 1.0

% aux1=-( sin(phi)*cos(psi)-sin(psi)*sin(theta)*cos(phi))*e+lp*cos(theta)*cos(phi)-lb+cos(theta11)*l*sin(phi11)+X 


% aux2=-e*( sin(phi)*cos(psi)-cos(phi)*sin(psi)*sin(theta))+l*cos(theta11)*sin(phi11)+X-lb+cos(phi)*cos(theta)*lp

