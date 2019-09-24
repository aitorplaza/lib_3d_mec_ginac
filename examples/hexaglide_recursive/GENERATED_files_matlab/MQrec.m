function MQrec_ = MQrec(q,dq,time,param)

x = q( 1 ); 
y = q( 2 ); 
z = q( 3 ); 
a = q( 4 ); 
b = q( 5 ); 
c = q( 6 ); 
a1 = q( 7 ); 
a2 = q( 8 ); 
a3 = q( 9 ); 
a4 = q( 10 ); 
a5 = q( 11 ); 
a6 = q( 12 ); 
b1 = q( 13 ); 
b2 = q( 14 ); 
b3 = q( 15 ); 
b4 = q( 16 ); 
b5 = q( 17 ); 
b6 = q( 18 ); 
s1 = q( 19 ); 
s2 = q( 20 ); 
s3 = q( 21 ); 
s4 = q( 22 ); 
s5 = q( 23 ); 
s6 = q( 24 ); 

dx = dq( 1 ); 
dy = dq( 2 ); 
dz = dq( 3 ); 
da = dq( 4 ); 
dB = dq( 5 ); 
dc = dq( 6 ); 
da1 = dq( 7 ); 
da2 = dq( 8 ); 
da3 = dq( 9 ); 
da4 = dq( 10 ); 
da5 = dq( 11 ); 
da6 = dq( 12 ); 
dB1 = dq( 13 ); 
dB2 = dq( 14 ); 
dB3 = dq( 15 ); 
dB4 = dq( 16 ); 
dB5 = dq( 17 ); 
dB6 = dq( 18 ); 
ds1 = dq( 19 ); 
ds2 = dq( 20 ); 
ds3 = dq( 21 ); 
ds4 = dq( 22 ); 
ds5 = dq( 23 ); 
ds6 = dq( 24 ); 

t= time ;

g = param( 1 ); 
R = param( 2 ); 
r = param( 3 ); 
L = param( 4 ); 
e = param( 5 ); 
mP = param( 6 ); 
mxP = param( 7 ); 
myP = param( 8 ); 
mzP = param( 9 ); 
IxxP = param( 10 ); 
IxyP = param( 11 ); 
IyyP = param( 12 ); 
IxzP = param( 13 ); 
IzzP = param( 14 ); 
IyzP = param( 15 ); 
m1 = param( 16 ); 
mx1 = param( 17 ); 
my1 = param( 18 ); 
mz1 = param( 19 ); 
Ixx1 = param( 20 ); 
Ixy1 = param( 21 ); 
Iyy1 = param( 22 ); 
Ixz1 = param( 23 ); 
Izz1 = param( 24 ); 
Iyz1 = param( 25 ); 
m2 = param( 26 ); 
mx2 = param( 27 ); 
my2 = param( 28 ); 
mz2 = param( 29 ); 
Ixx2 = param( 30 ); 
Ixy2 = param( 31 ); 
Iyy2 = param( 32 ); 
Ixz2 = param( 33 ); 
Izz2 = param( 34 ); 
Iyz2 = param( 35 ); 
m3 = param( 36 ); 
mx3 = param( 37 ); 
my3 = param( 38 ); 
mz3 = param( 39 ); 
Ixx3 = param( 40 ); 
Ixy3 = param( 41 ); 
Iyy3 = param( 42 ); 
Ixz3 = param( 43 ); 
Izz3 = param( 44 ); 
Iyz3 = param( 45 ); 
m4 = param( 46 ); 
mx4 = param( 47 ); 
my4 = param( 48 ); 
mz4 = param( 49 ); 
Ixx4 = param( 50 ); 
Ixy4 = param( 51 ); 
Iyy4 = param( 52 ); 
Ixz4 = param( 53 ); 
Izz4 = param( 54 ); 
Iyz4 = param( 55 ); 
m5 = param( 56 ); 
mx5 = param( 57 ); 
my5 = param( 58 ); 
mz5 = param( 59 ); 
Ixx5 = param( 60 ); 
Ixy5 = param( 61 ); 
Iyy5 = param( 62 ); 
Ixz5 = param( 63 ); 
Izz5 = param( 64 ); 
Iyz5 = param( 65 ); 
m6 = param( 66 ); 
mx6 = param( 67 ); 
my6 = param( 68 ); 
mz6 = param( 69 ); 
Ixx6 = param( 70 ); 
Ixy6 = param( 71 ); 
Iyy6 = param( 72 ); 
Ixz6 = param( 73 ); 
Izz6 = param( 74 ); 
Iyz6 = param( 75 ); 
Fs1 = param( 76 ); 
Fs2 = param( 77 ); 
Fs3 = param( 78 ); 
Fs4 = param( 79 ); 
Fs5 = param( 80 ); 
Fs6 = param( 81 ); 
FS001 = param( 82 ); 
FSa11 = param( 83 ); 
FSb11 = param( 84 ); 
FSa21 = param( 85 ); 
FSb21 = param( 86 ); 
FS002 = param( 87 ); 
FSa12 = param( 88 ); 
FSb12 = param( 89 ); 
FSa22 = param( 90 ); 
FSb22 = param( 91 ); 
FS003 = param( 92 ); 
FSa13 = param( 93 ); 
FSb13 = param( 94 ); 
FSa23 = param( 95 ); 
FSb23 = param( 96 ); 
FS004 = param( 97 ); 
FSa14 = param( 98 ); 
FSb14 = param( 99 ); 
FSa24 = param( 100 ); 
FSb24 = param( 101 ); 
FS005 = param( 102 ); 
FSa15 = param( 103 ); 
FSb15 = param( 104 ); 
FSa25 = param( 105 ); 
FSb25 = param( 106 ); 
FS006 = param( 107 ); 
FSa16 = param( 108 ); 
FSb16 = param( 109 ); 
FSa26 = param( 110 ); 
FSb26 = param( 111 ); 
gra = param( 112 ); 


atom38 = sin(c);
atom39 = cos(b);
atom40 = sin(b);
atom37 = cos(c);
atom47 = atom39*atom37;
atom48 = -atom38*atom39;
atom2480 = atom47*mzP-mxP*atom40;
atom2477 = myP*atom40-atom48*mzP;
atom2483 = mxP*atom48-atom47*myP;
atom4865 = atom38*myP-mxP*atom37;
atom4858 = mzP*atom37;
atom4860 = -atom38*mzP;
atom2467 = da*atom40;
atom3800 = dB*atom2467;
atom2466 = atom39*da;
atom2470 = atom38*dB+atom2466*atom37;
atom2474 = dc+atom2467;
atom4563 = atom3800*atom38-dc*atom2470;
atom3818 = atom2474*atom2470;
atom2473 = dB*atom37-atom2466*atom38;
atom3821 = atom2474*atom2473;
atom4572 = -atom3800*atom37+dc*atom2473;
atom3815 = atom2473^2;
atom3819 = atom2470^2;
atom4586 = -mxP*(atom4563-atom3818)-mzP*(atom3815+atom3819)+myP*(atom3821+atom4572);
atom3817 = atom2473*atom2470;
atom2628 = atom2466*dB;
atom3814 = atom2474^2;
atom4569 = (atom3817-atom2628)*myP+mzP*(atom4563+atom3818)-mxP*(atom3815+atom3814);
atom4578 = (atom3821-atom4572)*mzP-myP*(atom3819+atom3814)+mxP*(atom3817+atom2628);
atom42 = sin(a);
atom44 = -atom42*atom39;
atom41 = cos(a);
atom43 = atom42*atom40;
atom54 = atom41*atom37-atom38*atom43;
atom51 = atom43*atom37+atom41*atom38;
atom46 = atom41*atom39;
atom45 = -atom41*atom40;
atom57 = atom45*atom37+atom42*atom38;
atom60 = -atom38*atom45+atom42*atom37;
atom307 = IyzP*atom48+atom47*IxzP+IzzP*atom40;
atom313 = IyyP*atom37+IxyP*atom38;
atom310 = IxxP*atom38+IxyP*atom37;
atom316 = atom38*IxzP+IyzP*atom37;
atom4603 = atom60*gra;
atom4601 = atom46*gra;
atom2662 = IxyP*atom2470;
atom3893 = atom2474*IyzP+IyyP*atom2473+atom2662;
atom3896 = IyzP*atom2473+atom2470*IxzP+atom2474*IzzP;
atom2527 = atom38*atom2467;
atom2526 = -atom2467*atom37;
atom4608 = (IxxP*atom2526+atom2466*IxzP+atom2527*IxyP)*dB-atom2474*atom3893+(IxxP*atom2473-atom2662)*dc+atom3896*atom2473+atom4601*myP-atom4603*mzP;
atom2664 = -IxyP*atom2473;
atom3890 = -atom2664+atom2474*IxzP+IxxP*atom2470;
atom4610 = atom57*gra;
atom4624 = -atom2473*atom3890+(atom2473*IxzP-IyzP*atom2470)*dc+(atom2526*IxzP+atom2527*IyzP+IzzP*atom2466)*dB-myP*atom4610+mxP*atom4603+atom3893*atom2470;
atom4616 = -(IyyP*atom2470+atom2664)*dc-atom3896*atom2470+atom4610*mzP-mxP*atom4601+atom2474*atom3890+(atom2466*IyzP+atom2527*IyyP+atom2526*IxyP)*dB;
atom79 = cos(b1);
atom80 = sin(b1);
atom82 = sin(a1);
atom81 = cos(a1);
atom85 = -atom80*atom81;
atom86 = atom81*atom79;
atom2697 = da1*atom79;
atom2698 = atom80*da1;
atom2809 = atom2698*Ixz1;
atom4042 = atom2698*Iyz1+Ixy1*atom2697+dB1*Iyy1;
atom4040 = atom2809+dB1*Ixy1+Ixx1*atom2697;
atom4632 = gra*atom82;
atom4640 = atom85*gra;
atom2805 = -Ixz1*atom2697;
atom4630 = gra*atom86;
atom4045 = dB1*Iyz1+atom2698*Izz1-atom2805;
atom104 = sin(b2);
atom103 = cos(b2);
atom106 = sin(a2);
atom105 = cos(a2);
atom110 = atom105*atom103;
atom109 = -atom104*atom105;
atom2843 = da2*atom103;
atom2951 = -Ixz2*atom2843;
atom2844 = atom104*da2;
atom4141 = Izz2*atom2844-atom2951+dB2*Iyz2;
atom4654 = gra*atom110;
atom4138 = Ixy2*atom2843+atom2844*Iyz2+dB2*Iyy2;
atom4648 = gra*atom106;
atom4646 = atom109*gra;
atom2955 = Ixz2*atom2844;
atom4136 = atom2955+dB2*Ixy2+Ixx2*atom2843;
atom127 = cos(b3);
atom128 = sin(b3);
atom130 = sin(a3);
atom129 = cos(a3);
atom148 = -atom128*atom129;
atom149 = atom127*atom129;
atom2989 = atom127*da3;
atom2990 = atom128*da3;
atom4234 = Iyy3*dB3+atom2990*Iyz3+Ixy3*atom2989;
atom3114 = atom2990*Ixz3;
atom4662 = gra*atom148;
atom4232 = Ixx3*atom2989+atom3114+Ixy3*dB3;
atom4664 = gra*atom130;
atom3110 = -Ixz3*atom2989;
atom4237 = atom2990*Izz3-atom3110+Iyz3*dB3;
atom4671 = gra*atom149;
atom168 = cos(b4);
atom169 = sin(b4);
atom171 = sin(a4);
atom170 = cos(a4);
atom189 = atom170*atom168;
atom188 = -atom169*atom170;
atom4679 = gra*atom171;
atom3149 = atom169*da4;
atom3148 = da4*atom168;
atom3273 = Ixz4*atom3149;
atom4328 = Ixx4*atom3148+Ixy4*dB4+atom3273;
atom4330 = Iyz4*atom3149+atom3148*Ixy4+Iyy4*dB4;
atom4681 = gra*atom188;
atom4687 = gra*atom189;
atom3269 = -Ixz4*atom3148;
atom4333 = Izz4*atom3149-atom3269+dB4*Iyz4;
atom208 = cos(b5);
atom209 = sin(b5);
atom211 = sin(a5);
atom210 = cos(a5);
atom228 = -atom209*atom210;
atom229 = atom210*atom208;
atom4695 = atom211*gra;
atom3308 = atom209*da5;
atom3307 = da5*atom208;
atom3432 = atom3308*Ixz5;
atom4424 = Ixx5*atom3307+atom3432+Ixy5*dB5;
atom4702 = gra*atom228;
atom4426 = Iyy5*dB5+atom3307*Ixy5+Iyz5*atom3308;
atom3428 = -Ixz5*atom3307;
atom4429 = atom3308*Izz5-atom3428+Iyz5*dB5;
atom4697 = gra*atom229;
atom249 = sin(b6);
atom248 = cos(b6);
atom250 = cos(a6);
atom269 = atom250*atom248;
atom251 = sin(a6);
atom268 = -atom250*atom249;
atom4713 = atom251*gra;
atom3467 = da6*atom249;
atom3466 = da6*atom248;
atom3591 = atom3467*Ixz6;
atom4520 = atom3591+atom3466*Ixx6+dB6*Ixy6;
atom4522 = atom3467*Iyz6+atom3466*Ixy6+Iyy6*dB6;
atom4711 = atom268*gra;
atom4720 = gra*atom269;
atom3587 = -atom3466*Ixz6;
atom4525 = Iyz6*dB6-atom3587+atom3467*Izz6;
atom3994 = atom2697^2;
atom3990 = atom2698^2;
atom3991 = dB1^2;
atom3993 = atom2698*atom2697;
atom4086 = atom2844^2;
atom4090 = atom2843^2;
atom4089 = atom2844*atom2843;
atom4087 = dB2^2;
atom4186 = atom2989^2;
atom4183 = dB3^2;
atom4185 = atom2990*atom2989;
atom4182 = atom2990^2;
atom4278 = atom3149^2;
atom4282 = atom3148^2;
atom4279 = dB4^2;
atom4281 = atom3148*atom3149;
atom4377 = atom3308*atom3307;
atom4375 = dB5^2;
atom4378 = atom3307^2;
atom4374 = atom3308^2;
atom4470 = atom3467^2;
atom4474 = atom3466^2;
atom4471 = dB6^2;
atom4473 = atom3467*atom3466;
atom2506 = atom47*atom2477+atom2483*atom40+atom48*atom2480;
atom4867 = atom4865*atom40+atom48*atom4860+atom47*atom4858;
atom4872 = -atom2483*atom44-atom54*atom2480-atom51*atom2477;
atom4877 = atom51*atom4858+atom54*atom4860+atom44*atom4865;
atom2492 = mxP*atom54-myP*atom51;
atom4882 = -atom60*atom2480-atom57*atom2477-atom2483*atom46;
atom4887 = atom4865*atom46+atom57*atom4858+atom60*atom4860;
atom2501 = atom60*mxP-atom57*myP;
atom349 = atom47*atom310+atom316*atom40+atom313*atom48;
atom649 = Ixy1*atom79+atom80*Iyz1;
atom2710 = -atom80*(atom85*my1-mx1*atom82)-(atom82*mz1-my1*atom86)*atom79;
atom763 = atom104*Iyz2+Ixy2*atom103;
atom2856 = (my2*atom110-atom106*mz2)*atom103+atom104*(mx2*atom106-atom109*my2);
atom877 = atom127*Ixy3+atom128*Iyz3;
atom3002 = -atom127*(atom130*mz3-my3*atom149)-atom128*(my3*atom148-mx3*atom130);
atom1001 = atom169*Iyz4+Ixy4*atom168;
atom3161 = atom169*(mx4*atom171-my4*atom188)+(atom189*my4-mz4*atom171)*atom168;
atom1125 = Iyz5*atom209+Ixy5*atom208;
atom3320 = -(mz5*atom211-my5*atom229)*atom208+atom209*(atom211*mx5-my5*atom228);
atom1249 = Iyz6*atom249+atom248*Ixy6;
atom3479 = (atom269*my6-mz6*atom251)*atom248+(atom251*mx6-atom268*my6)*atom249;
atom2704 = -mx1*atom86+atom85*mz1;
atom2850 = atom109*mz2-mx2*atom110;
atom2996 = atom148*mz3-mx3*atom149;
atom3155 = mz4*atom188-mx4*atom189;
atom3314 = mz5*atom228-mx5*atom229;
atom3473 = -mx6*atom269+atom268*mz6;

MQrec_ = [mP , 0.0 , 0.0 , -atom2506 , atom4867 , atom2483 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4578*atom48+atom40*atom4586+atom47*atom4569;
0.0 , mP , 0.0 , atom4872 , atom4877 , atom2492 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4569*atom51+atom4578*atom54-atom42*atom39*atom4586;
0.0 , 0.0 , mP , atom4882 , atom4887 , atom2501 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom46*atom4586+atom60*atom4578+atom57*atom4569+gra*mP;
-atom2506 , atom4872 , atom4882 , atom48*(atom48*IyyP+IyzP*atom40+atom47*IxyP)+atom307*atom40+atom47*(IxyP*atom48+IxxP*atom47+atom40*IxzP) , atom349 , atom307 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4616*atom48+atom47*atom4608+atom4624*atom40;
atom4867 , atom4877 , atom4887 , atom349 , atom313*atom37+atom38*atom310 , atom316 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom38*atom4608+atom4616*atom37;
atom2483 , atom2492 , atom2501 , atom307 , atom316 , IzzP , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4624;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom79*(Ixz1*atom80+Ixx1*atom79)+atom80*(atom80*Izz1+Ixz1*atom79) , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom649 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2710 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom79*(dB1*atom4045-atom2698*atom4042+my1*atom4630-dB1*(atom2698*Ixx1+atom2805)-atom4632*mz1)+(atom4632*mx1-(atom2809-Izz1*atom2697)*dB1+atom4042*atom2697-atom4640*my1-dB1*atom4040)*atom80;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom104*(Ixz2*atom103+atom104*Izz2)+(Ixx2*atom103+atom104*Ixz2)*atom103 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom763 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2856 , 0.0 , 0.0 , 0.0 , 0.0 , -(dB2*(Ixx2*atom2844+atom2951)-atom4654*my2+atom4138*atom2844+mz2*atom4648-dB2*atom4141)*atom103-(dB2*(atom2955-Izz2*atom2843)+atom4136*dB2-mx2*atom4648+my2*atom4646-atom4138*atom2843)*atom104;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom127*(Ixz3*atom128+atom127*Ixx3)+(atom128*Izz3+atom127*Ixz3)*atom128 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom877 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3002 , 0.0 , 0.0 , 0.0 , -atom127*((atom2990*Ixx3+atom3110)*dB3-atom4671*my3+atom2990*atom4234-dB3*atom4237+atom4664*mz3)-atom128*(my3*atom4662-(Izz3*atom2989-atom3114)*dB3-atom2989*atom4234-atom4664*mx3+atom4232*dB3);
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , (Ixx4*atom168+atom169*Ixz4)*atom168+atom169*(atom169*Izz4+Ixz4*atom168) , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom1001 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3161 , 0.0 , 0.0 , -atom169*(atom4328*dB4+atom4681*my4-mx4*atom4679-atom3148*atom4330+(atom3273-atom3148*Izz4)*dB4)-((Ixx4*atom3149+atom3269)*dB4-atom4333*dB4+atom4330*atom3149-atom4687*my4+mz4*atom4679)*atom168;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom209*(atom209*Izz5+Ixz5*atom208)+(Ixx5*atom208+atom209*Ixz5)*atom208 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom1125 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3320 , 0.0 , (atom4695*mx5+dB5*(Izz5*atom3307-atom3432)+atom4426*atom3307-atom4424*dB5-my5*atom4702)*atom209+atom208*(atom4429*dB5-(atom3308*Ixx5+atom3428)*dB5-atom3308*atom4426+atom4697*my5-mz5*atom4695);
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , (Ixz6*atom248+Izz6*atom249)*atom249+atom248*(Ixz6*atom249+Ixx6*atom248) , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom1249 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3479 , -(atom4711*my6+atom4520*dB6+(atom3591-atom3466*Izz6)*dB6-atom3466*atom4522-atom4713*mx6)*atom249+atom248*(atom4720*my6-(atom3467*Ixx6+atom3587)*dB6-atom3467*atom4522+atom4525*dB6-mz6*atom4713);
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom649 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , Iyy1 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2704 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4640*mz1-dB1*(atom2698*Ixy1-atom2697*Iyz1)-atom2697*atom4045+atom2698*atom4040-mx1*atom4630;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom763 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , Iyy2 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2850 , 0.0 , 0.0 , 0.0 , 0.0 , atom4646*mz2-atom4141*atom2843+atom4136*atom2844-atom4654*mx2-dB2*(Ixy2*atom2844-Iyz2*atom2843);
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom877 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , Iyy3 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2996 , 0.0 , 0.0 , 0.0 , -atom2989*atom4237+atom2990*atom4232+atom4662*mz3+(atom2989*Iyz3-atom2990*Ixy3)*dB3-atom4671*mx3;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom1001 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , Iyy4 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3155 , 0.0 , 0.0 , atom4328*atom3149-mx4*atom4687-atom3148*atom4333+mz4*atom4681+(atom3148*Iyz4-Ixy4*atom3149)*dB4;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom1125 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , Iyy5 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3314 , 0.0 , mz5*atom4702-atom4429*atom3307+atom3308*atom4424-atom4697*mx5+dB5*(Iyz5*atom3307-atom3308*Ixy5);
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom1249 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , Iyy6 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3473 , (Iyz6*atom3466-atom3467*Ixy6)*dB6-atom4525*atom3466-mx6*atom4720+mz6*atom4711+atom3467*atom4520;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2710 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2704 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , m1 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , (mx1*atom3993-(atom3994+atom3991)*mz1)*atom86+gra*m1+(2*dB1*mx1*atom2697-(atom3994+atom3990)*my1+2*atom2698*dB1*mz1)*atom82-atom85*(mx1*(atom3991+atom3990)-atom3993*mz1);
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2856 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2850 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , m2 , 0.0 , 0.0 , 0.0 , 0.0 , (2*dB2*mx2*atom2843+2*dB2*atom2844*mz2-(atom4086+atom4090)*my2)*atom106+(atom4089*mx2-(atom4090+atom4087)*mz2)*atom110+atom109*(atom4089*mz2-(atom4086+atom4087)*mx2)+gra*m2;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3002 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom2996 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , m3 , 0.0 , 0.0 , 0.0 , m3*gra-atom149*((atom4186+atom4183)*mz3-mx3*atom4185)+(atom4185*mz3-mx3*(atom4183+atom4182))*atom148-((atom4186+atom4182)*my3-2*atom2990*dB3*mz3-2*mx3*atom2989*dB3)*atom130;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3161 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3155 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , m4 , 0.0 , 0.0 , -((atom4278+atom4282)*my4-2*atom3148*mx4*dB4-2*mz4*dB4*atom3149)*atom171+(atom4281*mx4-mz4*(atom4282+atom4279))*atom189+(mz4*atom4281-(atom4278+atom4279)*mx4)*atom188+m4*gra;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3320 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3314 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , m5 , 0.0 , -(mx5*(atom4374+atom4375)-atom4377*mz5)*atom228+(2*mz5*atom3308*dB5+2*mx5*atom3307*dB5-my5*(atom4374+atom4378))*atom211+m5*gra-(mz5*(atom4375+atom4378)-atom4377*mx5)*atom229;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3479 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3473 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , m6 , m6*gra-atom268*((atom4470+atom4471)*mx6-atom4473*mz6)+(atom4473*mx6-mz6*(atom4474+atom4471))*atom269+atom251*(2*atom3466*mx6*dB6+2*atom3467*mz6*dB6-(atom4470+atom4474)*my6)];

%endfunction
