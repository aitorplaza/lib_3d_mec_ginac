function M_ = M(q,time,param)

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

t= time ;

g = param( 1 ); 
R = param( 2 ); 
r = param( 3 ); 
L = param( 4 ); 
e = param( 5 ); 
alfa = param( 6 ); 
mP = param( 7 ); 
mxP = param( 8 ); 
myP = param( 9 ); 
mzP = param( 10 ); 
IxxP = param( 11 ); 
IxyP = param( 12 ); 
IyyP = param( 13 ); 
IxzP = param( 14 ); 
IzzP = param( 15 ); 
IyzP = param( 16 ); 
m1 = param( 17 ); 
mx1 = param( 18 ); 
my1 = param( 19 ); 
mz1 = param( 20 ); 
Ixx1 = param( 21 ); 
Ixy1 = param( 22 ); 
Iyy1 = param( 23 ); 
Ixz1 = param( 24 ); 
Izz1 = param( 25 ); 
Iyz1 = param( 26 ); 
m2 = param( 27 ); 
mx2 = param( 28 ); 
my2 = param( 29 ); 
mz2 = param( 30 ); 
Ixx2 = param( 31 ); 
Ixy2 = param( 32 ); 
Iyy2 = param( 33 ); 
Ixz2 = param( 34 ); 
Izz2 = param( 35 ); 
Iyz2 = param( 36 ); 
m3 = param( 37 ); 
mx3 = param( 38 ); 
my3 = param( 39 ); 
mz3 = param( 40 ); 
Ixx3 = param( 41 ); 
Ixy3 = param( 42 ); 
Iyy3 = param( 43 ); 
Ixz3 = param( 44 ); 
Izz3 = param( 45 ); 
Iyz3 = param( 46 ); 
m4 = param( 47 ); 
mx4 = param( 48 ); 
my4 = param( 49 ); 
mz4 = param( 50 ); 
Ixx4 = param( 51 ); 
Ixy4 = param( 52 ); 
Iyy4 = param( 53 ); 
Ixz4 = param( 54 ); 
Izz4 = param( 55 ); 
Iyz4 = param( 56 ); 
m5 = param( 57 ); 
mx5 = param( 58 ); 
my5 = param( 59 ); 
mz5 = param( 60 ); 
Ixx5 = param( 61 ); 
Ixy5 = param( 62 ); 
Iyy5 = param( 63 ); 
Ixz5 = param( 64 ); 
Izz5 = param( 65 ); 
Iyz5 = param( 66 ); 
m6 = param( 67 ); 
mx6 = param( 68 ); 
my6 = param( 69 ); 
mz6 = param( 70 ); 
Ixx6 = param( 71 ); 
Ixy6 = param( 72 ); 
Iyy6 = param( 73 ); 
Ixz6 = param( 74 ); 
Izz6 = param( 75 ); 
Iyz6 = param( 76 ); 
Fs1 = param( 77 ); 
Fs2 = param( 78 ); 
Fs3 = param( 79 ); 
Fs4 = param( 80 ); 
Fs5 = param( 81 ); 
Fs6 = param( 82 ); 
FS001 = param( 83 ); 
FSa11 = param( 84 ); 
FSb11 = param( 85 ); 
FSa21 = param( 86 ); 
FSb21 = param( 87 ); 
FS002 = param( 88 ); 
FSa12 = param( 89 ); 
FSb12 = param( 90 ); 
FSa22 = param( 91 ); 
FSb22 = param( 92 ); 
FS003 = param( 93 ); 
FSa13 = param( 94 ); 
FSb13 = param( 95 ); 
FSa23 = param( 96 ); 
FSb23 = param( 97 ); 
FS004 = param( 98 ); 
FSa14 = param( 99 ); 
FSb14 = param( 100 ); 
FSa24 = param( 101 ); 
FSb24 = param( 102 ); 
FS005 = param( 103 ); 
FSa15 = param( 104 ); 
FSb15 = param( 105 ); 
FSa25 = param( 106 ); 
FSb25 = param( 107 ); 
FS006 = param( 108 ); 
FSa16 = param( 109 ); 
FSb16 = param( 110 ); 
FSa26 = param( 111 ); 
FSb26 = param( 112 ); 

atom39 = cos(c);
atom41 = cos(b);
atom49 = atom39*atom41;
atom40 = sin(c);
atom50 = -atom40*atom41;
atom42 = sin(b);
atom4148 = -atom49*myP+mxP*atom50;
atom4145 = -atom42*mxP+atom49*mzP;
atom4142 = -atom50*mzP+atom42*myP;
atom43 = cos(a);
atom44 = sin(a);
atom45 = atom42*atom44;
atom56 = atom43*atom39-atom40*atom45;
atom53 = atom43*atom40+atom39*atom45;
atom4157 = -myP*atom53+mxP*atom56;
atom46 = -atom44*atom41;
atom4154 = -mxP*atom46+mzP*atom53;
atom4151 = -atom56*mzP+myP*atom46;
atom48 = atom43*atom41;
atom47 = -atom42*atom43;
atom62 = -atom40*atom47+atom39*atom44;
atom4160 = myP*atom48-atom62*mzP;
atom59 = atom39*atom47+atom44*atom40;
atom4163 = atom59*mzP-mxP*atom48;
atom4166 = atom62*mxP-atom59*myP;
atom301 = IxxP*atom49+IxyP*atom50+atom42*IxzP;
atom306 = atom49*IxyP+atom50*IyyP+atom42*IyzP;
atom311 = atom42*IzzP+IyzP*atom50+IxzP*atom49;
atom82 = sin(b1);
atom81 = cos(b1);
atom84 = sin(a1);
atom83 = cos(a1);
atom87 = -atom82*atom83;
atom88 = atom81*atom83;
atom106 = sin(b2);
atom105 = cos(b2);
atom107 = cos(a2);
atom112 = atom105*atom107;
atom108 = sin(a2);
atom111 = -atom106*atom107;
atom130 = sin(b3);
atom129 = cos(b3);
atom132 = sin(a3);
atom131 = cos(a3);
atom149 = -atom130*atom131;
atom150 = atom129*atom131;
atom170 = sin(b4);
atom169 = cos(b4);
atom172 = sin(a4);
atom171 = cos(a4);
atom189 = -atom170*atom171;
atom190 = atom171*atom169;
atom210 = sin(b5);
atom209 = cos(b5);
atom212 = sin(a5);
atom211 = cos(a5);
atom232 = -atom210*atom211;
atom233 = atom209*atom211;
atom253 = sin(b6);
atom252 = cos(b6);
atom255 = sin(a6);
atom254 = cos(a6);
atom272 = -atom254*atom253;
atom273 = atom254*atom252;
atom4171 = atom49*atom4142+atom42*atom4148+atom4145*atom50;
atom4174 = atom39*atom4145+atom40*atom4142;
atom4179 = atom4154*atom50+atom4151*atom49+atom42*atom4157;
atom4182 = atom4154*atom39+atom4151*atom40;
atom4187 = atom42*atom4166+atom50*atom4163+atom49*atom4160;
atom4190 = atom39*atom4163+atom40*atom4160;
atom343 = atom306*atom39+atom301*atom40;
atom320 = IxzP*atom40+atom39*IyzP;
atom653 = atom82*Iyz1+atom81*Ixy1;
atom4373 = -atom81*(atom84*mz1-atom88*my1)-atom82*(atom87*my1-mx1*atom84);
atom767 = atom106*Iyz2+atom105*Ixy2;
atom4511 = -atom105*(mz2*atom108-atom112*my2)+atom106*(mx2*atom108-atom111*my2);
atom881 = Iyz3*atom130+atom129*Ixy3;
atom4649 = atom130*(mx3*atom132-atom149*my3)-(mz3*atom132-atom150*my3)*atom129;
atom1005 = Ixy4*atom169+Iyz4*atom170;
atom4800 = atom169*(my4*atom190-mz4*atom172)-atom170*(atom189*my4-mx4*atom172);
atom1129 = atom209*Ixy5+atom210*Iyz5;
atom4951 = atom210*(atom212*mx5-my5*atom232)+atom209*(my5*atom233-mz5*atom212);
atom1253 = Iyz6*atom253+Ixy6*atom252;
atom5102 = atom253*(atom255*mx6-my6*atom272)+(my6*atom273-mz6*atom255)*atom252;
atom4367 = -atom88*mx1+atom87*mz1;
atom4505 = -atom112*mx2+mz2*atom111;
atom4643 = -mx3*atom150+mz3*atom149;
atom4794 = -mx4*atom190+atom189*mz4;
atom4945 = atom232*mz5-mx5*atom233;
atom5096 = -mx6*atom273+mz6*atom272;

M_ = [-mP , 0 , 0 , -atom4171 , -atom4174 , -atom4148 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0;
0 , -mP , 0 , -atom4179 , -atom4182 , -atom4157 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0;
0 , 0 , -mP , -atom4187 , -atom4190 , -atom4166 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0;
-atom4171 , -atom4179 , -atom4187 , -atom306*atom50-atom42*atom311-atom301*atom49 , -atom343 , -atom311 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0;
-atom4174 , -atom4182 , -atom4190 , -atom343 , -atom39*(atom39*IyyP+IxyP*atom40)-(IxxP*atom40+atom39*IxyP)*atom40 , -atom320 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0;
-atom4148 , -atom4157 , -atom4166 , -atom311 , -atom320 , -IzzP , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , -atom81*(atom81*Ixx1+Ixz1*atom82)-atom82*(atom82*Izz1+atom81*Ixz1) , 0 , 0 , 0 , 0 , 0 , -atom653 , 0 , 0 , 0 , 0 , 0 , -atom4373 , 0 , 0 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom106*(atom105*Ixz2+atom106*Izz2)-atom105*(atom105*Ixx2+atom106*Ixz2) , 0 , 0 , 0 , 0 , 0 , -atom767 , 0 , 0 , 0 , 0 , 0 , -atom4511 , 0 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom129*(atom129*Ixx3+Ixz3*atom130)-atom130*(atom129*Ixz3+atom130*Izz3) , 0 , 0 , 0 , 0 , 0 , -atom881 , 0 , 0 , 0 , 0 , 0 , -atom4649 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom169*(Ixx4*atom169+atom170*Ixz4)-atom170*(atom170*Izz4+Ixz4*atom169) , 0 , 0 , 0 , 0 , 0 , -atom1005 , 0 , 0 , 0 , 0 , 0 , -atom4800 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom209*(atom209*Ixx5+atom210*Ixz5)-atom210*(atom210*Izz5+atom209*Ixz5) , 0 , 0 , 0 , 0 , 0 , -atom1129 , 0 , 0 , 0 , 0 , 0 , -atom4951 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -(atom253*Izz6+atom252*Ixz6)*atom253-atom252*(atom252*Ixx6+Ixz6*atom253) , 0 , 0 , 0 , 0 , 0 , -atom1253 , 0 , 0 , 0 , 0 , 0 , -atom5102;
0 , 0 , 0 , 0 , 0 , 0 , -atom653 , 0 , 0 , 0 , 0 , 0 , -Iyy1 , 0 , 0 , 0 , 0 , 0 , -atom4367 , 0 , 0 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom767 , 0 , 0 , 0 , 0 , 0 , -Iyy2 , 0 , 0 , 0 , 0 , 0 , -atom4505 , 0 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom881 , 0 , 0 , 0 , 0 , 0 , -Iyy3 , 0 , 0 , 0 , 0 , 0 , -atom4643 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom1005 , 0 , 0 , 0 , 0 , 0 , -Iyy4 , 0 , 0 , 0 , 0 , 0 , -atom4794 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom1129 , 0 , 0 , 0 , 0 , 0 , -Iyy5 , 0 , 0 , 0 , 0 , 0 , -atom4945 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom1253 , 0 , 0 , 0 , 0 , 0 , -Iyy6 , 0 , 0 , 0 , 0 , 0 , -atom5096;
0 , 0 , 0 , 0 , 0 , 0 , -atom4373 , 0 , 0 , 0 , 0 , 0 , -atom4367 , 0 , 0 , 0 , 0 , 0 , -m1 , 0 , 0 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom4511 , 0 , 0 , 0 , 0 , 0 , -atom4505 , 0 , 0 , 0 , 0 , 0 , -m2 , 0 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom4649 , 0 , 0 , 0 , 0 , 0 , -atom4643 , 0 , 0 , 0 , 0 , 0 , -m3 , 0 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom4800 , 0 , 0 , 0 , 0 , 0 , -atom4794 , 0 , 0 , 0 , 0 , 0 , -m4 , 0 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom4951 , 0 , 0 , 0 , 0 , 0 , -atom4945 , 0 , 0 , 0 , 0 , 0 , -m5 , 0;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom5102 , 0 , 0 , 0 , 0 , 0 , -atom5096 , 0 , 0 , 0 , 0 , 0 , -m6];

%endfunction
