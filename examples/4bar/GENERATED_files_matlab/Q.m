function Q_ = Q(q,dq,time,param,inputs)

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

Fx2 = inputs( 1 ); 
Fz2 = inputs( 2 ); 
Fx3 = inputs( 3 ); 
Fz3 = inputs( 4 ); 
My2 = inputs( 5 ); 
My3 = inputs( 6 ); 

atom15 = sin(theta1);
atom14 = cos(theta1);
atom78 = dtheta2+dtheta1;
atom26 = cos(theta2);
atom25 = m2*cg2z;
atom27 = sin(theta2);
atom24 = m2*cg2x;
atom68 = atom14*l1;
atom71 = dtheta1*atom68;
atom69 = -l1*atom15;
atom70 = dtheta1*atom69;
atom30 = -atom15*atom27+atom14*atom26;
atom33 = atom14*atom27+atom26*atom15;
atom36 = atom25*atom33+atom24*atom30;
atom274 = -(atom25*atom30-atom33*atom24)*dtheta1*atom71+dtheta1*atom36*atom70;
atom0 = cos(theta3);
atom284 = atom78+dtheta3;
atom42 = cg3x*m3;
atom339 = -atom0*atom284^2;
atom1 = sin(theta3);
atom340 = -atom284^2*atom1;
atom43 = cg3z*m3;
atom101 = -l2*atom27;
atom100 = l2*atom26;
atom106 = atom101*atom15;
atom124 = -atom14*atom100-atom106;
atom103 = dtheta2*atom100;
atom102 = dtheta2*atom101;
atom118 = -atom14*atom103-atom102*atom15;
atom126 = dtheta1*atom124+atom118;
atom104 = l1+atom100;
atom107 = atom104*atom14+atom106;
atom120 = -atom107*dtheta1+atom118;
atom327 = dtheta2*atom126*m3+atom120*dtheta1*m3;
atom109 = atom101*atom14;
atom122 = -atom100*atom15+atom109;
atom115 = -atom15*atom103+atom102*atom14;
atom128 = -atom115-atom122*dtheta1;
atom110 = -atom104*atom15+atom109;
atom119 = atom110*dtheta1+atom115;
atom330 = dtheta2*m3*atom128-dtheta1*atom119*m3;
atom240 = l1*atom27;
atom241 = -atom26*l1;
atom353 = atom33*atom327-atom42*atom340+atom339*atom43+atom330*atom30;
atom279 = l2-atom241;
atom46 = -atom33*atom1+atom0*atom30;
atom49 = atom0*atom33+atom1*atom30;
atom52 = atom49*atom43+atom42*atom46;
atom351 = -(dtheta2*atom128-dtheta1*atom119)*atom52-(atom42*atom49-atom46*atom43)*(dtheta2*atom126+atom120*dtheta1);
atom40 = atom36*g;
atom57 = -m3*g;
atom56 = atom52*g;
atom11 = -K*(l3x*atom1-atom0*l3z);
atom10 = K*(l2+atom1*l3z-l2x+atom0*l3x);
atom401 = -atom10*atom1-atom11*atom0;
atom398 = atom11*atom1-atom0*atom10;

Q_ = [-Fx3*atom110+Fz2*atom68-atom56-m2*g*atom68-My3-(atom33*atom330-atom42*atom339-atom30*atom327-atom340*atom43)*atom240-atom10*atom240-atom69*Fx2+atom401*(l3x+atom0*atom279-atom1*atom240)-(atom1*atom279+l3z+atom0*atom240)*atom398+atom351+(atom78^2*atom25*atom26+dtheta1*m2*atom15*atom71-atom78^2*atom24*atom27+dtheta1*m2*atom70*atom14)*l1-(m1*cg1z*atom15+m1*atom14*cg1x)*g-atom11*(atom241-l2x)+atom274+atom107*Fz3-My2-atom40-atom353*atom279+atom107*atom57;
atom11*l2x-atom56-My3-Fx3*atom122-Fz3*atom124-l2*atom353-(l2*atom1+l3z)*atom398-atom57*atom124+atom351+atom401*(l3x+l2*atom0)+atom274-My2-atom40;
-atom56-My3+atom401*l3x+atom351-atom398*l3z];

%endfunction
