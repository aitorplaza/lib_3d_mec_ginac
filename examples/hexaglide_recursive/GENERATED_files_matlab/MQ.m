function MQ_ = MQ(q,dq,time,param)

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


atom38 = sin(c);
atom39 = cos(b);
atom40 = sin(b);
atom37 = cos(c);
atom47 = atom39*atom37;
atom48 = -atom38*atom39;
atom2480 = atom47*mzP-mxP*atom40;
atom2477 = myP*atom40-atom48*mzP;
atom2483 = mxP*atom48-atom47*myP;
atom2466 = atom39*da;
atom2470 = atom38*dB+atom2466*atom37;
atom2467 = da*atom40;
atom2474 = dc+atom2467;
atom2558 = atom2470*atom40-atom47*atom2474;
atom2473 = dB*atom37-atom2466*atom38;
atom2555 = -atom2473*atom40+atom2474*atom48;
atom2561 = atom47*atom2473-atom48*atom2470;
atom41 = cos(a);
atom288 = dc*atom40;
atom42 = sin(a);
atom44 = -atom42*atom39;
atom43 = atom42*atom40;
atom54 = atom41*atom37-atom38*atom43;
atom51 = atom43*atom37+atom41*atom38;
atom2529 = -atom41*atom288;
atom70 = mxP*atom51+atom44*mzP+myP*atom54;
atom46 = atom41*atom39;
atom45 = -atom41*atom40;
atom60 = -atom38*atom45+atom42*atom37;
atom57 = atom45*atom37+atom42*atom38;
atom2528 = atom288*atom42;
atom75 = mxP*atom57+atom60*myP+atom46*mzP;
atom289 = dc*atom39;
atom1532 = atom41*dB-atom42*atom289;
atom1535 = atom42*dB+atom41*atom289;
atom2492 = mxP*atom54-myP*atom51;
atom2489 = -mxP*atom44+mzP*atom51;
atom2486 = -atom54*mzP+atom44*myP;
atom2567 = -atom2474*atom51+atom44*atom2470;
atom2564 = atom2474*atom54-atom44*atom2473;
atom2570 = -atom54*atom2470+atom2473*atom51;
atom65 = mzP*atom40+atom47*mxP+myP*atom48;
atom2498 = atom57*mzP-mxP*atom46;
atom2495 = myP*atom46-atom60*mzP;
atom2501 = atom60*mxP-atom57*myP;
atom2579 = atom57*atom2473-atom60*atom2470;
atom2576 = atom46*atom2470-atom57*atom2474;
atom2573 = -atom46*atom2473+atom60*atom2474;
atom307 = IyzP*atom48+atom47*IxzP+IzzP*atom40;
atom302 = atom48*IyyP+IyzP*atom40+atom47*IxyP;
atom297 = IxyP*atom48+IxxP*atom47+atom40*IxzP;
atom77 = g*atom65;
atom76 = -atom70*g;
atom1539 = atom44*atom77+atom76*atom40;
atom3645 = atom77*atom54+atom48*atom76;
atom3642 = atom47*atom76+atom77*atom51;
atom2656 = -IyzP*atom2470;
atom2645 = atom2473*IxzP;
atom2624 = dc*atom2473-dB*atom2467*atom37;
atom2627 = -dc*atom2470+atom38*dB*atom2467;
atom2628 = atom2466*dB;
atom2685 = atom2473*(IyyP*atom2470-IxyP*atom2473)+atom2624*IxzP+IzzP*atom2628-(IxxP*atom2473-IxyP*atom2470)*atom2470+IyzP*atom2627-atom2474*(atom2656+atom2645);
atom2644 = -atom2474*IxyP;
atom2684 = IyyP*atom2627-(atom2644-atom2656)*atom2473+IxyP*atom2624+atom2474*(atom2474*IxzP-IzzP*atom2470)+atom2628*IyzP-(atom2470*IxzP-IxxP*atom2474)*atom2470;
atom2683 = atom2628*IxzP+(atom2644+atom2645)*atom2470-(atom2474*IyyP-IyzP*atom2473)*atom2473+IxxP*atom2624+IxyP*atom2627+atom2474*(IzzP*atom2473-atom2474*IyzP);
atom79 = cos(b1);
atom80 = sin(b1);
atom82 = sin(a1);
atom81 = cos(a1);
atom85 = -atom80*atom81;
atom86 = atom81*atom79;
atom2697 = da1*atom79;
atom2796 = Ixz1*dB1;
atom2807 = -atom2697*Iyz1;
atom2698 = atom80*da1;
atom2785 = dB1*atom2697;
atom2784 = -atom2698*dB1;
atom2795 = -atom2698*Ixy1;
atom83 = atom80*atom82;
atom84 = -atom82*atom79;
atom100 = -g*(atom84*mz1+atom81*my1+mx1*atom83);
atom89 = mx1*atom79+atom80*mz1;
atom101 = g*atom89;
atom104 = sin(b2);
atom103 = cos(b2);
atom106 = sin(a2);
atom105 = cos(a2);
atom110 = atom105*atom103;
atom109 = -atom104*atom105;
atom113 = atom104*mz2+mx2*atom103;
atom125 = g*atom113;
atom107 = atom104*atom106;
atom108 = -atom106*atom103;
atom124 = -(atom105*my2+atom108*mz2+mx2*atom107)*g;
atom2843 = da2*atom103;
atom2931 = dB2*atom2843;
atom2844 = atom104*da2;
atom2930 = -dB2*atom2844;
atom2953 = -Iyz2*atom2843;
atom2942 = dB2*Ixz2;
atom2941 = -Ixy2*atom2844;
atom127 = cos(b3);
atom128 = sin(b3);
atom130 = sin(a3);
atom129 = cos(a3);
atom148 = -atom128*atom129;
atom149 = atom127*atom129;
atom2989 = atom127*da3;
atom3112 = -atom2989*Iyz3;
atom3101 = Ixz3*dB3;
atom2990 = atom128*da3;
atom3090 = atom2989*dB3;
atom3089 = -atom2990*dB3;
atom3100 = -atom2990*Ixy3;
atom131 = 1/2*sqrt(3);
atom133 = atom131*atom130;
atom135 = 1/2*atom130;
atom144 = atom131*atom127-atom135*atom128;
atom134 = -1/2*atom129;
atom147 = atom127*atom135+atom131*atom128;
atom159 = my3*atom134+atom144*mx3+atom147*mz3;
atom141 = -1/2*atom128+atom127*atom133;
atom165 = -atom159*g;
atom138 = -1/2*atom127-atom128*atom133;
atom132 = -atom131*atom129;
atom154 = atom138*mx3+atom132*my3+atom141*mz3;
atom166 = g*atom154;
atom168 = cos(b4);
atom169 = sin(b4);
atom171 = sin(a4);
atom170 = cos(a4);
atom189 = atom170*atom168;
atom188 = -atom169*atom170;
atom175 = 1/2*atom171;
atom173 = atom131*atom171;
atom181 = -1/2*atom169+atom173*atom168;
atom172 = -atom131*atom170;
atom178 = -atom173*atom169-1/2*atom168;
atom194 = atom172*my4+mz4*atom181+atom178*mx4;
atom187 = atom131*atom169+atom175*atom168;
atom206 = g*atom194;
atom184 = -atom175*atom169+atom131*atom168;
atom174 = -1/2*atom170;
atom199 = mx4*atom184+mz4*atom187+atom174*my4;
atom205 = -atom199*g;
atom3148 = da4*atom168;
atom3260 = Ixz4*dB4;
atom3271 = -atom3148*Iyz4;
atom3149 = atom169*da4;
atom3249 = atom3148*dB4;
atom3248 = -dB4*atom3149;
atom3259 = -Ixy4*atom3149;
atom208 = cos(b5);
atom209 = sin(b5);
atom211 = sin(a5);
atom210 = cos(a5);
atom228 = -atom209*atom210;
atom229 = atom210*atom208;
atom213 = -atom131*atom211;
atom215 = 1/2*atom211;
atom224 = -atom209*atom215-atom131*atom208;
atom214 = -1/2*atom210;
atom227 = atom215*atom208-atom131*atom209;
atom239 = mz5*atom227+atom224*mx5+my5*atom214;
atom221 = -1/2*atom209+atom213*atom208;
atom245 = -atom239*g;
atom212 = atom131*atom210;
atom218 = -atom209*atom213-1/2*atom208;
atom234 = mx5*atom218+mz5*atom221+atom212*my5;
atom246 = g*atom234;
atom3308 = atom209*da5;
atom3419 = Ixz5*dB5;
atom3418 = -atom3308*Ixy5;
atom3307 = da5*atom208;
atom3408 = atom3307*dB5;
atom3407 = -atom3308*dB5;
atom3430 = -Iyz5*atom3307;
atom249 = sin(b6);
atom248 = cos(b6);
atom250 = cos(a6);
atom269 = atom250*atom248;
atom251 = sin(a6);
atom268 = -atom250*atom249;
atom3467 = da6*atom249;
atom3566 = -atom3467*dB6;
atom3466 = da6*atom248;
atom3567 = atom3466*dB6;
atom3578 = Ixz6*dB6;
atom3577 = -atom3467*Ixy6;
atom3589 = -Iyz6*atom3466;
atom255 = 1/2*atom251;
atom267 = atom248*atom255-atom131*atom249;
atom254 = -1/2*atom250;
atom264 = -atom255*atom249-atom131*atom248;
atom279 = atom254*my6+atom264*mx6+mz6*atom267;
atom253 = -atom131*atom251;
atom285 = -atom279*g;
atom261 = atom253*atom248-1/2*atom249;
atom258 = -atom253*atom249-1/2*atom248;
atom252 = atom131*atom250;
atom274 = atom261*mz6+atom252*my6+mx6*atom258;
atom286 = atom274*g;
atom2735 = atom2698*atom82-dB1*atom86;
atom2738 = -atom2698*atom85+atom2697*atom86;
atom2741 = atom85*dB1-atom2697*atom82;
atom2881 = atom2844*atom106-dB2*atom110;
atom2884 = -atom109*atom2844+atom110*atom2843;
atom2887 = atom109*dB2-atom106*atom2843;
atom3043 = -atom2990*atom148+atom2989*atom149;
atom3046 = atom148*dB3-atom2989*atom130;
atom3040 = atom2990*atom130-atom149*dB3;
atom3202 = atom3148*atom189-atom188*atom3149;
atom3205 = atom188*dB4-atom3148*atom171;
atom3199 = atom171*atom3149-atom189*dB4;
atom3358 = -dB5*atom229+atom211*atom3308;
atom3361 = -atom3308*atom228+atom3307*atom229;
atom3364 = dB5*atom228-atom211*atom3307;
atom3523 = atom268*dB6-atom3466*atom251;
atom3517 = -dB6*atom269+atom3467*atom251;
atom3520 = -atom268*atom3467+atom3466*atom269;
atom2506 = atom47*atom2477+atom2483*atom40+atom48*atom2480;
atom2509 = atom2480*atom37+atom38*atom2477;
atom2514 = atom48*atom2489+atom2486*atom47+atom2492*atom40;
atom2517 = atom2489*atom37+atom2486*atom38;
atom2522 = atom2501*atom40+atom48*atom2498+atom47*atom2495;
atom2525 = atom2498*atom37+atom38*atom2495;
atom339 = atom38*atom297+atom302*atom37;
atom316 = atom38*IxzP+IyzP*atom37;
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

MQ_ = [-mP , 0 , 0 , -atom2506 , -atom2509 , -atom2483 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -dB*(atom2529*atom70-atom2528*atom75)+mzP*(atom2555*atom2473-atom2558*atom2470)-(atom70*atom1532+atom1535*atom75)*da+mxP*(atom2474*atom2558-atom2473*atom2561)+myP*(atom2561*atom2470-atom2474*atom2555);
0 , -mP , 0 , -atom2514 , -atom2517 , -atom2492 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , dB*(atom2529*atom65-atom289*atom75)-(atom2470*atom2567-atom2564*atom2473)*mzP-mxP*(atom2473*atom2570-atom2474*atom2567)-(atom2474*atom2564-atom2470*atom2570)*myP+da*atom1532*atom65;
0 , 0 , -mP , -atom2522 , -atom2525 , -atom2501 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , myP*(atom2579*atom2470-atom2474*atom2573)+(atom70*atom289-atom2528*atom65)*dB-mxP*(atom2579*atom2473-atom2474*atom2576)+atom1535*da*atom65+g*mP-(atom2576*atom2470-atom2573*atom2473)*mzP;
-atom2506 , -atom2514 , -atom2522 , -atom307*atom40-atom47*atom297-atom302*atom48 , -atom339 , -atom307 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom47*atom3642-atom40*atom1539+atom47*atom2683+atom40*atom2685+atom2684*atom48-atom48*atom3645;
-atom2509 , -atom2517 , -atom2525 , -atom339 , -(IyyP*atom37+IxyP*atom38)*atom37-(IxxP*atom38+IxyP*atom37)*atom38 , -atom316 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , atom2684*atom37-atom37*atom3645+atom38*atom2683-atom38*atom3642;
-atom2483 , -atom2492 , -atom2501 , -atom307 , -atom316 , -IzzP , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , atom2685-atom1539;
0 , 0 , 0 , 0 , 0 , 0 , -atom79*(Ixz1*atom80+Ixx1*atom79)-atom80*(atom80*Izz1+Ixz1*atom79) , 0 , 0 , 0 , 0 , 0 , -atom649 , 0 , 0 , 0 , 0 , 0 , -atom2710 , 0 , 0 , 0 , 0 , 0 , -(atom101*atom83+atom100*atom79)*atom79+atom80*(dB1*(atom2697*Iyy1-dB1*Ixy1)+Ixz1*atom2784+(Ixy1*atom2697-dB1*Ixx1)*atom2697-atom2698*(atom2796+atom2807)+atom2785*Izz1)-atom80*(atom80*atom100+atom84*atom101)-(atom2698*(atom2698*Iyz1-dB1*Izz1)-atom2785*Ixz1-Ixx1*atom2784-(atom2796+atom2795)*atom2697+dB1*(atom2698*Iyy1-dB1*Iyz1))*atom79;
0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom104*(Ixz2*atom103+atom104*Izz2)-(Ixx2*atom103+atom104*Ixz2)*atom103 , 0 , 0 , 0 , 0 , 0 , -atom763 , 0 , 0 , 0 , 0 , 0 , -atom2856 , 0 , 0 , 0 , 0 , atom104*(Ixz2*atom2930-(atom2953+atom2942)*atom2844-(dB2*Ixx2-Ixy2*atom2843)*atom2843+atom2931*Izz2-dB2*(dB2*Ixy2-Iyy2*atom2843))+(Ixx2*atom2930+(dB2*Izz2-atom2844*Iyz2)*atom2844+Ixz2*atom2931+(atom2942+atom2941)*atom2843+dB2*(dB2*Iyz2-atom2844*Iyy2))*atom103-(atom125*atom107+atom124*atom103)*atom103-atom104*(atom108*atom125+atom104*atom124);
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom127*(Ixz3*atom128+atom127*Ixx3)-(atom128*Izz3+atom127*Ixz3)*atom128 , 0 , 0 , 0 , 0 , 0 , -atom877 , 0 , 0 , 0 , 0 , 0 , -atom3002 , 0 , 0 , 0 , -atom127*(atom138*atom165+atom144*atom166)+atom128*(atom3090*Izz3+Ixz3*atom3089+atom2989*(Ixy3*atom2989-Ixx3*dB3)-(atom3112+atom3101)*atom2990+(atom2989*Iyy3-Ixy3*dB3)*dB3)+atom127*(atom3090*Ixz3+Ixx3*atom3089-(atom2990*Iyy3-Iyz3*dB3)*dB3+atom2989*(atom3101+atom3100)-atom2990*(atom2990*Iyz3-Izz3*dB3))-atom128*(atom147*atom166+atom141*atom165);
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -(Ixx4*atom168+atom169*Ixz4)*atom168-atom169*(atom169*Izz4+Ixz4*atom168) , 0 , 0 , 0 , 0 , 0 , -atom1001 , 0 , 0 , 0 , 0 , 0 , -atom3161 , 0 , 0 , atom169*(atom3249*Izz4+atom3248*Ixz4-atom3148*(Ixx4*dB4-atom3148*Ixy4)-(Ixy4*dB4-Iyy4*atom3148)*dB4-(atom3260+atom3271)*atom3149)-atom169*(atom205*atom181+atom187*atom206)+(atom3148*(atom3259+atom3260)+atom3248*Ixx4-(Iyy4*atom3149-dB4*Iyz4)*dB4-(Iyz4*atom3149-Izz4*dB4)*atom3149+atom3249*Ixz4)*atom168-(atom178*atom205+atom206*atom184)*atom168;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom209*(atom209*Izz5+Ixz5*atom208)-(Ixx5*atom208+atom209*Ixz5)*atom208 , 0 , 0 , 0 , 0 , 0 , -atom1125 , 0 , 0 , 0 , 0 , 0 , -atom3320 , 0 , -atom209*(atom227*atom246+atom221*atom245)+atom209*(atom3407*Ixz5+atom3408*Izz5-(Ixx5*dB5-atom3307*Ixy5)*atom3307+(Iyy5*atom3307-Ixy5*dB5)*dB5-(atom3430+atom3419)*atom3308)-(atom218*atom245+atom224*atom246)*atom208+atom208*(atom3407*Ixx5+(atom3419+atom3418)*atom3307+atom3408*Ixz5+atom3308*(Izz5*dB5-Iyz5*atom3308)-(Iyy5*atom3308-Iyz5*dB5)*dB5);
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -(Ixz6*atom248+Izz6*atom249)*atom249-atom248*(Ixz6*atom249+Ixx6*atom248) , 0 , 0 , 0 , 0 , 0 , -atom1249 , 0 , 0 , 0 , 0 , 0 , -atom3479 , -(atom285*atom258+atom264*atom286)*atom248+(dB6*(Iyy6*atom3466-dB6*Ixy6)+Ixz6*atom3566-atom3466*(Ixx6*dB6-atom3466*Ixy6)+atom3567*Izz6-atom3467*(atom3578+atom3589))*atom249-(atom285*atom261+atom267*atom286)*atom249+(Ixz6*atom3567-atom3467*(atom3467*Iyz6-dB6*Izz6)+(Iyz6*dB6-atom3467*Iyy6)*dB6+atom3466*(atom3578+atom3577)+Ixx6*atom3566)*atom248;
0 , 0 , 0 , 0 , 0 , 0 , -atom649 , 0 , 0 , 0 , 0 , 0 , -Iyy1 , 0 , 0 , 0 , 0 , 0 , -atom2704 , 0 , 0 , 0 , 0 , 0 , atom2697*(atom2698*Ixx1-Ixz1*atom2697)+atom2785*Iyz1+atom2784*Ixy1-atom101*atom81+atom2698*(atom2698*Ixz1-Izz1*atom2697)+dB1*(atom2807-atom2795);
0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom763 , 0 , 0 , 0 , 0 , 0 , -Iyy2 , 0 , 0 , 0 , 0 , 0 , -atom2850 , 0 , 0 , 0 , 0 , -(Izz2*atom2843-Ixz2*atom2844)*atom2844-(Ixz2*atom2843-Ixx2*atom2844)*atom2843+dB2*(atom2953-atom2941)+atom2930*Ixy2+atom2931*Iyz2-atom105*atom125;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom877 , 0 , 0 , 0 , 0 , 0 , -Iyy3 , 0 , 0 , 0 , 0 , 0 , -atom2996 , 0 , 0 , 0 , -atom2990*(Izz3*atom2989-atom2990*Ixz3)-atom166*atom134+(atom3112-atom3100)*dB3+atom2989*(atom2990*Ixx3-Ixz3*atom2989)-atom165*atom132+Ixy3*atom3089+atom3090*Iyz3;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom1001 , 0 , 0 , 0 , 0 , 0 , -Iyy4 , 0 , 0 , 0 , 0 , 0 , -atom3155 , 0 , 0 , -(atom3148*Izz4-Ixz4*atom3149)*atom3149+(Ixx4*atom3149-Ixz4*atom3148)*atom3148+atom3248*Ixy4-atom172*atom205+atom3249*Iyz4-dB4*(atom3259-atom3271)-atom206*atom174;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom1125 , 0 , 0 , 0 , 0 , 0 , -Iyy5 , 0 , 0 , 0 , 0 , 0 , -atom3314 , 0 , -atom212*atom245+atom3407*Ixy5-atom3307*(Ixz5*atom3307-atom3308*Ixx5)-atom246*atom214+(atom3430-atom3418)*dB5-atom3308*(Izz5*atom3307-atom3308*Ixz5)+Iyz5*atom3408;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom1249 , 0 , 0 , 0 , 0 , 0 , -Iyy6 , 0 , 0 , 0 , 0 , 0 , -atom3473 , -atom285*atom252+Ixy6*atom3566-atom254*atom286+dB6*(atom3589-atom3577)+atom3466*(atom3467*Ixx6-atom3466*Ixz6)+atom3467*(atom3467*Ixz6-atom3466*Izz6)+Iyz6*atom3567;
0 , 0 , 0 , 0 , 0 , 0 , -atom2710 , 0 , 0 , 0 , 0 , 0 , -atom2704 , 0 , 0 , 0 , 0 , 0 , -m1 , 0 , 0 , 0 , 0 , 0 , (atom2698*atom2738-dB1*atom2741)*mx1-(atom2698*atom2735-atom2697*atom2741)*my1+dB1*da1*atom82*atom89+mz1*(dB1*atom2735-atom2697*atom2738)+g*m1;
0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom2856 , 0 , 0 , 0 , 0 , 0 , -atom2850 , 0 , 0 , 0 , 0 , 0 , -m2 , 0 , 0 , 0 , 0 , (dB2*atom2881-atom2884*atom2843)*mz2+my2*(atom2887*atom2843-atom2881*atom2844)+mx2*(atom2884*atom2844-dB2*atom2887)+g*m2+dB2*da2*atom113*atom106;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom3002 , 0 , 0 , 0 , 0 , 0 , -atom2996 , 0 , 0 , 0 , 0 , 0 , -m3 , 0 , 0 , 0 , da3*(atom159*atom133*dB3-atom135*atom154*dB3)+mx3*(atom2990*atom3043-atom3046*dB3)+(atom3040*dB3-atom3043*atom2989)*mz3+(atom3046*atom2989-atom2990*atom3040)*my3+m3*g;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom3161 , 0 , 0 , 0 , 0 , 0 , -atom3155 , 0 , 0 , 0 , 0 , 0 , -m4 , 0 , 0 , -mx4*(atom3205*dB4-atom3202*atom3149)+mz4*(atom3199*dB4-atom3202*atom3148)-(atom3199*atom3149-atom3205*atom3148)*my4+m4*g+da4*(atom199*atom173*dB4-atom175*atom194*dB4);
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom3320 , 0 , 0 , 0 , 0 , 0 , -atom3314 , 0 , 0 , 0 , 0 , 0 , -m5 , 0 , (atom3361*atom3308-dB5*atom3364)*mx5+m5*g-mz5*(atom3361*atom3307-atom3358*dB5)+da5*(atom213*atom239*dB5-atom215*atom234*dB5)-(atom3358*atom3308-atom3307*atom3364)*my5;
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -atom3479 , 0 , 0 , 0 , 0 , 0 , -atom3473 , 0 , 0 , 0 , 0 , 0 , -m6 , da6*(atom279*atom253*dB6-atom274*atom255*dB6)-(atom3467*atom3517-atom3466*atom3523)*my6-(atom3520*atom3466-atom3517*dB6)*mz6-(dB6*atom3523-atom3467*atom3520)*mx6+m6*g];

%endfunction
