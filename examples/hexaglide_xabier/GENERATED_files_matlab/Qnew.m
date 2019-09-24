function Qnew_ = Qnew(q,dq,time,param)

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
atom40 = sin(c);
atom4131 = da*atom41;
atom4135 = dB*atom40+atom39*atom4131;
atom50 = -atom40*atom41;
atom49 = atom39*atom41;
atom4138 = -atom40*atom4131+atom39*dB;
atom4226 = -atom4135*atom50+atom49*atom4138;
atom42 = sin(b);
atom4132 = da*atom42;
atom4139 = dc+atom4132;
atom4223 = -atom49*atom4139+atom4135*atom42;
atom4220 = atom50*atom4139-atom4138*atom42;
atom43 = cos(a);
atom44 = sin(a);
atom45 = atom44*atom42;
atom56 = atom43*atom39-atom40*atom45;
atom53 = atom39*atom45+atom43*atom40;
atom46 = -atom44*atom41;
atom292 = dc*atom42;
atom72 = mxP*atom53+mzP*atom46+myP*atom56;
atom4194 = -atom292*atom43;
atom48 = atom43*atom41;
atom47 = -atom43*atom42;
atom62 = atom39*atom44-atom40*atom47;
atom59 = atom39*atom47+atom44*atom40;
atom77 = mxP*atom59+atom48*mzP+atom62*myP;
atom4193 = atom292*atom44;
atom293 = dc*atom41;
atom1490 = atom43*dB-atom44*atom293;
atom1493 = dB*atom44+atom43*atom293;
atom4235 = -atom4135*atom56+atom4138*atom53;
atom4229 = atom4139*atom56-atom4138*atom46;
atom4232 = -atom4139*atom53+atom4135*atom46;
atom67 = atom49*mxP+mzP*atom42+myP*atom50;
atom4238 = atom62*atom4139-atom4138*atom48;
atom4241 = -atom59*atom4139+atom4135*atom48;
atom4244 = -atom62*atom4135+atom59*atom4138;
atom4292 = dB*atom40*atom4132-dc*atom4135;
atom4289 = -atom39*dB*atom4132+dc*atom4138;
atom4293 = dB*atom4131;
atom4310 = atom4138*IxzP;
atom4309 = -IxyP*atom4139;
atom4348 = IxzP*atom4293-(IyzP*atom4139-IzzP*atom4138)*atom4139+atom4135*(atom4310+atom4309)+IxyP*atom4292+atom4138*(atom4138*IyzP-atom4139*IyyP)+IxxP*atom4289;
atom4321 = -atom4135*IyzP;
atom4349 = -atom4139*(IzzP*atom4135-atom4139*IxzP)+(atom4321-atom4309)*atom4138+atom4135*(IxxP*atom4139-atom4135*IxzP)+atom4289*IxyP+atom4292*IyyP+IyzP*atom4293;
atom4350 = -atom4135*(IxxP*atom4138-IxyP*atom4135)+(atom4135*IyyP-atom4138*IxyP)*atom4138-(atom4310+atom4321)*atom4139+atom4289*IxzP+IzzP*atom4293+atom4292*IyzP;
atom79 = g*atom67;
atom78 = -atom72*g;
atom1497 = atom78*atom42+atom79*atom46;
atom5262 = atom50*atom78+atom79*atom56;
atom5259 = atom79*atom53+atom49*atom78;
atom81 = cos(b1);
atom3157 = da1*atom81;
atom4464 = -Iyz1*atom3157;
atom4453 = Ixz1*dB1;
atom82 = sin(b1);
atom3163 = -da1*atom82;
atom3204 = dB1*atom3157;
atom3164 = dB1*atom3163;
atom4452 = Ixy1*atom3163;
atom84 = sin(a1);
atom85 = atom82*atom84;
atom83 = cos(a1);
atom86 = -atom84*atom81;
atom102 = -(atom86*mz1+atom83*my1+mx1*atom85)*g;
atom91 = atom82*mz1+mx1*atom81;
atom103 = atom91*g;
atom106 = sin(b2);
atom3243 = -atom106*da2;
atom4590 = atom3243*Ixy2;
atom4591 = Ixz2*dB2;
atom105 = cos(b2);
atom3239 = atom105*da2;
atom3284 = dB2*atom3239;
atom3244 = atom3243*dB2;
atom4602 = -Iyz2*atom3239;
atom108 = sin(a2);
atom115 = atom106*mz2+mx2*atom105;
atom110 = -atom108*atom105;
atom127 = atom115*g;
atom109 = atom106*atom108;
atom107 = cos(a2);
atom126 = -(mx2*atom109+atom107*my2+atom110*mz2)*g;
atom0 = 2*alfa;
atom132 = sin(a3);
atom1 = sin(atom0);
atom130 = sin(b3);
atom134 = atom132*atom1;
atom129 = cos(b3);
atom3 = cos(atom0);
atom139 = atom129*atom3-atom130*atom134;
atom131 = cos(a3);
atom133 = -atom131*atom1;
atom142 = atom129*atom134+atom3*atom130;
atom155 = atom133*my3+mx3*atom139+atom142*mz3;
atom136 = -atom3*atom132;
atom167 = atom155*g;
atom145 = -atom130*atom136+atom129*atom1;
atom135 = atom3*atom131;
atom148 = atom129*atom136+atom130*atom1;
atom160 = atom135*my3+atom148*mz3+mx3*atom145;
atom166 = -g*atom160;
atom2589 = atom129*da3;
atom4753 = -Iyz3*atom2589;
atom4742 = Ixz3*dB3;
atom2595 = -atom130*da3;
atom2596 = dB3*atom2595;
atom2646 = dB3*atom2589;
atom4741 = Ixy3*atom2595;
atom169 = cos(b4);
atom2740 = atom169*da4;
atom4904 = -atom2740*Iyz4;
atom4893 = Ixz4*dB4;
atom170 = sin(b4);
atom2748 = -da4*atom170;
atom2799 = dB4*atom2740;
atom2749 = dB4*atom2748;
atom4892 = Ixy4*atom2748;
atom172 = sin(a4);
atom174 = atom172*atom1;
atom176 = -atom3*atom172;
atom185 = -atom176*atom170+atom169*atom1;
atom171 = cos(a4);
atom175 = atom3*atom171;
atom188 = atom169*atom176+atom1*atom170;
atom200 = mx4*atom185+atom175*my4+mz4*atom188;
atom182 = atom169*atom174+atom3*atom170;
atom206 = -atom200*g;
atom173 = -atom171*atom1;
atom179 = atom3*atom169-atom174*atom170;
atom195 = atom182*mz4+atom179*mx4+my4*atom173;
atom207 = atom195*g;
atom210 = sin(b5);
atom2900 = -da5*atom210;
atom2901 = dB5*atom2900;
atom209 = cos(b5);
atom2890 = da5*atom209;
atom2954 = atom2890*dB5;
atom5044 = dB5*Ixz5;
atom5055 = -Iyz5*atom2890;
atom5043 = Ixy5*atom2900;
atom213 = (4.0)*alfa;
atom215 = sin(atom213);
atom214 = cos(atom213);
atom212 = sin(a5);
atom219 = -atom214*atom212;
atom217 = atom212*atom215;
atom222 = -atom217*atom210+atom214*atom209;
atom211 = cos(a5);
atom216 = -atom211*atom215;
atom225 = atom217*atom209+atom214*atom210;
atom238 = atom222*mx5+mz5*atom225+atom216*my5;
atom228 = -atom219*atom210+atom215*atom209;
atom250 = atom238*g;
atom231 = atom219*atom209+atom215*atom210;
atom218 = atom211*atom214;
atom243 = mz5*atom231+atom218*my5+atom228*mx5;
atom249 = -atom243*g;
atom252 = cos(b6);
atom3049 = atom252*da6;
atom3109 = dB6*atom3049;
atom253 = sin(b6);
atom3054 = -atom253*da6;
atom3055 = dB6*atom3054;
atom5194 = Ixy6*atom3054;
atom5195 = dB6*Ixz6;
atom5206 = -Iyz6*atom3049;
atom255 = sin(a6);
atom257 = atom255*atom215;
atom262 = -atom257*atom253+atom214*atom252;
atom254 = cos(a6);
atom256 = -atom215*atom254;
atom265 = atom214*atom253+atom252*atom257;
atom278 = atom262*mx6+atom256*my6+atom265*mz6;
atom259 = -atom214*atom255;
atom290 = atom278*g;
atom271 = atom252*atom259+atom215*atom253;
atom268 = atom215*atom252-atom259*atom253;
atom258 = atom214*atom254;
atom283 = atom268*mx6+mz6*atom271+my6*atom258;
atom289 = -atom283*g;
atom88 = atom83*atom81;
atom4396 = -atom84*atom3163-dB1*atom88;
atom87 = -atom82*atom83;
atom4399 = atom88*atom3157+atom87*atom3163;
atom4402 = atom87*dB1-atom84*atom3157;
atom112 = atom107*atom105;
atom4534 = -dB2*atom112-atom3243*atom108;
atom111 = -atom106*atom107;
atom4537 = atom3243*atom111+atom112*atom3239;
atom4540 = -atom108*atom3239+dB2*atom111;
atom150 = atom129*atom131;
atom4685 = -dB3*atom150-atom132*atom2595;
atom149 = -atom130*atom131;
atom4688 = atom149*atom2595+atom150*atom2589;
atom4691 = dB3*atom149-atom132*atom2589;
atom190 = atom171*atom169;
atom189 = -atom171*atom170;
atom4839 = atom190*atom2740+atom2748*atom189;
atom4836 = -dB4*atom190-atom172*atom2748;
atom4842 = -atom172*atom2740+dB4*atom189;
atom232 = -atom211*atom210;
atom233 = atom211*atom209;
atom4990 = atom232*atom2900+atom2890*atom233;
atom4993 = -atom2890*atom212+dB5*atom232;
atom4987 = -dB5*atom233-atom212*atom2900;
atom273 = atom252*atom254;
atom5138 = -dB6*atom273-atom255*atom3054;
atom272 = -atom253*atom254;
atom5141 = atom272*atom3054+atom273*atom3049;
atom5144 = dB6*atom272-atom255*atom3049;

Qnew_ = [-dB*(atom72*atom4194-atom77*atom4193)-mzP*(atom4135*atom4223-atom4138*atom4220)-da*(atom72*atom1490+atom77*atom1493)-mxP*(atom4138*atom4226-atom4139*atom4223)-myP*(atom4139*atom4220-atom4226*atom4135);
-dB*(atom77*atom293-atom4194*atom67)+(atom4135*atom4235-atom4229*atom4139)*myP+mzP*(atom4229*atom4138-atom4135*atom4232)-mxP*(atom4138*atom4235-atom4232*atom4139)+atom1490*da*atom67;
-(atom4241*atom4135-atom4238*atom4138)*mzP+mxP*(atom4241*atom4139-atom4244*atom4138)+(atom4244*atom4135-atom4238*atom4139)*myP+mP*g+da*atom1493*atom67+dB*(atom72*atom293-atom4193*atom67);
-atom49*atom5259+atom4350*atom42+atom50*atom4349-atom1497*atom42-atom50*atom5262+atom49*atom4348;
-atom39*atom5262-atom5259*atom40+atom39*atom4349+atom40*atom4348;
-atom1497+atom4350;
(Ixx1*atom3164+Ixz1*atom3204+(atom4452+atom4453)*atom3157+dB1*(dB1*Iyz1+Iyy1*atom3163)-(Iyz1*atom3163+Izz1*dB1)*atom3163)*atom81+atom82*((Ixy1*atom3157-Ixx1*dB1)*atom3157+(atom4464+atom4453)*atom3163+Ixz1*atom3164+(Iyy1*atom3157-Ixy1*dB1)*dB1+atom3204*Izz1)-(atom103*atom85+atom102*atom81)*atom81-atom82*(atom86*atom103+atom82*atom102);
atom106*(atom3244*Ixz2+atom3239*(Ixy2*atom3239-Ixx2*dB2)+atom3243*(atom4602+atom4591)+Izz2*atom3284-(Ixy2*dB2-Iyy2*atom3239)*dB2)-atom106*(atom110*atom127+atom106*atom126)-(atom126*atom105+atom127*atom109)*atom105+(atom3244*Ixx2-atom3243*(Izz2*dB2+atom3243*Iyz2)+(atom4590+atom4591)*atom3239+Ixz2*atom3284+(atom3243*Iyy2+dB2*Iyz2)*dB2)*atom105;
atom129*(Ixz3*atom2646+Ixx3*atom2596+(atom4741+atom4742)*atom2589-(Iyz3*atom2595+dB3*Izz3)*atom2595+(dB3*Iyz3+atom2595*Iyy3)*dB3)-atom129*(atom166*atom139+atom167*atom145)+atom130*((Ixy3*atom2589-Ixx3*dB3)*atom2589+(Iyy3*atom2589-dB3*Ixy3)*dB3+Ixz3*atom2596+(atom4753+atom4742)*atom2595+Izz3*atom2646)-(atom166*atom142+atom148*atom167)*atom130;
(Ixy4*atom2740^2+Ixz4*atom2749+dB4*(atom2740*Iyy4-dB4*Ixy4)+atom2799*Izz4+(atom4904+atom4893)*atom2748)*atom170-atom169*(atom179*atom206+atom207*atom185)-((dB4*Izz4+atom2748*Iyz4)*atom2748-(atom4892+atom4893)*atom2740-dB4*(dB4*Iyz4+atom2748*Iyy4)-atom2799*Ixz4)*atom169-(atom182*atom206+atom188*atom207)*atom170;
-(atom228*atom250+atom222*atom249)*atom209+atom210*(Ixz5*atom2901+dB5*(Iyy5*atom2890-dB5*Ixy5)+(atom5044+atom5055)*atom2900+(atom2890*Ixy5-dB5*Ixx5)*atom2890+atom2954*Izz5)-(atom231*atom250+atom249*atom225)*atom210+(dB5*(Iyy5*atom2900+Iyz5*dB5)+Ixx5*atom2901-(dB5*Izz5+Iyz5*atom2900)*atom2900+(atom5044+atom5043)*atom2890+Ixz5*atom2954)*atom209;
atom253*(atom3109*Izz6+(atom5195+atom5206)*atom3054-dB6*(dB6*Ixy6-Iyy6*atom3049)+(Ixy6*atom3049-dB6*Ixx6)*atom3049+Ixz6*atom3055)+((Iyz6*dB6+Iyy6*atom3054)*dB6+Ixx6*atom3055+atom3109*Ixz6-(dB6*Izz6+Iyz6*atom3054)*atom3054+(atom5194+atom5195)*atom3049)*atom252-atom252*(atom262*atom289+atom268*atom290)-(atom290*atom271+atom265*atom289)*atom253;
atom3204*Iyz1-(atom4452-atom4464)*dB1+atom3164*Ixy1-atom83*atom103-(Ixx1*atom3163+Ixz1*atom3157)*atom3157+(Izz1*atom3157+Ixz1*atom3163)*atom3163;
atom3284*Iyz2+atom3243*(Ixz2*atom3243+Izz2*atom3239)+atom3244*Ixy2-atom107*atom127-dB2*(atom4590-atom4602)-(Ixz2*atom3239+atom3243*Ixx2)*atom3239;
-(Ixz3*atom2589+Ixx3*atom2595)*atom2589+Ixy3*atom2596-atom135*atom167+Iyz3*atom2646+atom2595*(Ixz3*atom2595+Izz3*atom2589)-dB3*(atom4741-atom4753)-atom133*atom166;
(Ixz4*atom2748+Izz4*atom2740)*atom2748-(atom4892-atom4904)*dB4+atom2799*Iyz4-atom175*atom207-atom206*atom173+atom2749*Ixy4-Ixz4*atom2740^2;
-atom218*atom250-dB5*(atom5043-atom5055)-atom2890*(atom2890*Ixz5+Ixx5*atom2900)+Iyz5*atom2954-atom249*atom216+(Ixz5*atom2900+atom2890*Izz5)*atom2900+Ixy5*atom2901;
Iyz6*atom3109-atom289*atom256-dB6*(atom5194-atom5206)-atom290*atom258+atom3055*Ixy6+(Ixz6*atom3054+Izz6*atom3049)*atom3054-(Ixz6*atom3049+Ixx6*atom3054)*atom3049;
-(atom4399*atom3157-atom4396*dB1)*mz1+da1*atom84*dB1*atom91+my1*(atom4402*atom3157+atom4396*atom3163)-Fs1-mx1*(atom4399*atom3163+atom4402*dB1)+g*m1;
dB2*atom108*atom115*da2-Fs2+my2*(atom3243*atom4534+atom4540*atom3239)-(atom4540*dB2+atom3243*atom4537)*mx2+g*m2-(atom4537*atom3239-dB2*atom4534)*mz2;
-Fs3-(atom155*dB3*atom136-dB3*atom134*atom160)*da3-mx3*(atom2595*atom4688+atom4691*dB3)+m3*g+(atom4691*atom2589+atom4685*atom2595)*my3-(atom4688*atom2589-atom4685*dB3)*mz3;
m4*g+(atom2748*atom4836+atom4842*atom2740)*my4-Fs4-(dB4*atom195*atom176-atom200*dB4*atom174)*da4-mx4*(dB4*atom4842+atom4839*atom2748)+mz4*(dB4*atom4836-atom4839*atom2740);
-Fs5+m5*g-mz5*(atom2890*atom4990-atom4987*dB5)+(atom2890*atom4993+atom4987*atom2900)*my5-(atom238*dB5*atom219-atom243*dB5*atom217)*da5-mx5*(atom4990*atom2900+dB5*atom4993);
-da6*(dB6*atom259*atom278-dB6*atom257*atom283)-(atom5141*atom3054+dB6*atom5144)*mx6-Fs6-(atom5141*atom3049-dB6*atom5138)*mz6+(atom5144*atom3049+atom5138*atom3054)*my6+m6*g];

%endfunction