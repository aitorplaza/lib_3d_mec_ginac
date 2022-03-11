function dPhi_dq_ = dPhi_dq(q,time,param)

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

atom40 = sin(b);
atom38 = sin(c);
atom468 = atom40*atom38;
atom37 = cos(c);
atom466 = -atom40*atom37;
atom2999 = e*atom468;
atom3000 = atom466*r;
atom39 = cos(b);
atom47 = atom37*atom39;
atom48 = -atom38*atom39;
atom3002 = -e*atom47;
atom3003 = r*atom48;
atom79 = cos(b1);
atom42 = sin(a);
atom41 = cos(a);
atom45 = -atom40*atom41;
atom57 = atom37*atom45+atom42*atom38;
atom60 = -atom38*atom45+atom37*atom42;
atom2697 = atom57*r;
atom2698 = e*atom60;
atom44 = -atom42*atom39;
atom502 = -atom37*atom44;
atom498 = atom44*atom38;
atom3007 = r*atom502;
atom3006 = e*atom498;
atom43 = atom40*atom42;
atom54 = -atom38*atom43+atom37*atom41;
atom51 = atom41*atom38+atom37*atom43;
atom3010 = r*atom54;
atom3009 = -e*atom51;
atom81 = cos(a1);
atom80 = sin(b1);
atom82 = sin(a1);
atom2695 = e*atom54;
atom2694 = r*atom51;
atom46 = atom41*atom39;
atom512 = -atom37*atom46;
atom516 = atom38*atom46;
atom3013 = r*atom512;
atom3014 = atom516*e;
atom3016 = atom60*r;
atom3017 = -e*atom57;
atom103 = cos(b2);
atom105 = cos(a2);
atom104 = sin(b2);
atom106 = sin(a2);
atom1 = sqrt(3);
atom0 = -1/2*r;
atom2 = 1/2*e*atom1;
atom3 = atom0+atom2;
atom4 = -1/2*e;
atom5 = -1/2*atom1*r;
atom6 = atom4+atom5;
atom3029 = atom466*atom3;
atom3030 = atom468*atom6;
atom3033 = -atom47*atom6;
atom3032 = atom48*atom3;
atom127 = cos(b3);
atom129 = cos(a3);
atom131 = 1/2*atom1;
atom2741 = -atom127*L*atom129;
atom130 = sin(a3);
atom128 = sin(b3);
atom3036 = -atom130*atom128*L;
atom3038 = -atom127*L;
atom2734 = atom60*atom6;
atom2733 = atom57*atom3;
atom3042 = atom498*atom6;
atom3041 = atom502*atom3;
atom3044 = atom3*atom54;
atom3045 = -atom6*atom51;
atom2730 = atom3*atom51;
atom2731 = atom6*atom54;
atom3052 = atom512*atom3;
atom3051 = atom516*atom6;
atom3055 = atom60*atom3;
atom3054 = -atom57*atom6;
atom7 = atom0-atom2;
atom8 = -atom4+atom5;
atom3059 = atom466*atom7;
atom3058 = atom468*atom8;
atom3062 = atom7*atom48;
atom3061 = -atom47*atom8;
atom168 = cos(b4);
atom170 = cos(a4);
atom2768 = -atom168*atom170*L;
atom3067 = -atom168*L;
atom169 = sin(b4);
atom171 = sin(a4);
atom3065 = -atom169*L*atom171;
atom2761 = atom60*atom8;
atom2760 = atom7*atom57;
atom3071 = atom498*atom8;
atom3070 = atom7*atom502;
atom3073 = atom7*atom54;
atom3074 = -atom8*atom51;
atom2757 = atom7*atom51;
atom2758 = atom8*atom54;
atom3080 = atom516*atom8;
atom3081 = atom7*atom512;
atom3084 = atom60*atom7;
atom3083 = -atom57*atom8;
atom208 = cos(b5);
atom210 = cos(a5);
atom2789 = -atom208*atom210*L;
atom3092 = -atom208*L;
atom209 = sin(b5);
atom211 = sin(a5);
atom3090 = -atom209*atom211*L;
atom250 = cos(a6);
atom248 = cos(b6);
atom2810 = -atom250*L*atom248;
atom249 = sin(b6);
atom251 = sin(a6);
atom3107 = -atom249*atom251*L;
atom3109 = -L*atom248;

dPhi_dq_ = [1.0 , 0.0 , 0.0 , 0.0 , atom2999+atom3000 , atom3002+atom3003 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom79*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , -atom2697-atom2698 , atom3007+atom3006 , atom3010+atom3009 , -atom79*atom81*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom80*L*atom82 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , atom2695+atom2694 , atom3013+atom3014 , atom3016+atom3017 , -atom79*L*atom82 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom80*atom81*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , -atom2999+atom3000 , -atom3002+atom3003 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom103*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , -atom2697+atom2698 , atom3007-atom3006 , atom3010-atom3009 , 0.0 , -atom103*atom105*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom104*L*atom106 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , -atom2695+atom2694 , atom3013-atom3014 , atom3016-atom3017 , 0.0 , -atom103*L*atom106 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom104*atom105*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0 , 0.0 , 0.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , atom3029+atom3030 , atom3033+atom3032 , 0.0 , 0.0 , -atom131*atom2741 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1/2*atom3038+atom131*atom3036 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , -atom2734-atom2733 , atom3042+atom3041 , atom3044+atom3045 , 0.0 , 0.0 , -1/2*atom2741 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom3038*atom131+1/2*atom3036 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , atom2730+atom2731 , atom3052+atom3051 , atom3055+atom3054 , 0.0 , 0.0 , -atom130*atom127*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom128*L*atom129 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0 , 0.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , atom3059+atom3058 , atom3062+atom3061 , 0.0 , 0.0 , 0.0 , -atom131*atom2768 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom131*atom3065+1/2*atom3067 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , -atom2761-atom2760 , atom3071+atom3070 , atom3073+atom3074 , 0.0 , 0.0 , 0.0 , -1/2*atom2768 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom131*atom3067+1/2*atom3065 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , atom2757+atom2758 , atom3080+atom3081 , atom3084+atom3083 , 0.0 , 0.0 , 0.0 , -atom168*L*atom171 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom169*atom170*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , atom3059-atom3058 , atom3062-atom3061 , 0.0 , 0.0 , 0.0 , 0.0 , atom131*atom2789 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1/2*atom3092-atom131*atom3090 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , atom2761-atom2760 , -atom3071+atom3070 , atom3073-atom3074 , 0.0 , 0.0 , 0.0 , 0.0 , -1/2*atom2789 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom3092*atom131+1/2*atom3090 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , atom2757-atom2758 , -atom3080+atom3081 , atom3084-atom3083 , 0.0 , 0.0 , 0.0 , 0.0 , -atom208*atom211*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom209*atom210*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0 , 0.0;
1.0 , 0.0 , 0.0 , 0.0 , atom3029-atom3030 , -atom3033+atom3032 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom131*atom2810 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1/2*atom3109-atom131*atom3107 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 1.0 , 0.0 , atom2734-atom2733 , -atom3042+atom3041 , atom3044-atom3045 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1/2*atom2810 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1/2*atom3107+atom131*atom3109 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 1.0 , atom2730-atom2731 , atom3052-atom3051 , atom3055-atom3054 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom251*L*atom248 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom249*atom250*L , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -1.0];

%endfunction
