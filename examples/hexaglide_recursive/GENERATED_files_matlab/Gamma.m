function gamma_ = Gamma(q,dq,time,param)

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

atom80 = sin(b1);
atom38 = sin(c);
atom40 = sin(b);
atom465 = atom38*atom40;
atom37 = cos(c);
atom467 = -atom40*atom37;
atom3222 = r*atom465;
atom3221 = -e*atom467;
atom3223 = atom3222+atom3221;
atom39 = cos(b);
atom48 = -atom38*atom39;
atom47 = atom39*atom37;
atom2692 = atom48*e;
atom2691 = r*atom47;
atom2693 = atom2692+atom2691;
atom42 = sin(a);
atom44 = -atom42*atom39;
atom501 = atom38*atom44;
atom497 = -atom37*atom44;
atom3236 = r*atom501;
atom3237 = -atom497*e;
atom3238 = atom3236+atom3237;
atom43 = atom42*atom40;
atom49 = atom43*atom37;
atom52 = -atom38*atom43;
atom3233 = -r*atom49;
atom3232 = -atom52*e;
atom41 = cos(a);
atom46 = atom39*atom41;
atom488 = -atom46*atom37;
atom479 = atom38*atom46;
atom3013 = r*atom488;
atom3014 = atom479*e;
atom3015 = atom3013+atom3014;
atom81 = cos(a1);
atom3019 = atom80*atom81*L;
atom82 = sin(a1);
atom79 = cos(b1);
atom2704 = L*atom82*atom79;
atom45 = -atom40*atom41;
atom58 = -atom38*atom45;
atom60 = atom58+atom42*atom37;
atom55 = atom45*atom37;
atom57 = atom55+atom42*atom38;
atom3016 = r*atom60;
atom3017 = -e*atom57;
atom3018 = atom3016+atom3017;
atom51 = atom38*atom41+atom49;
atom54 = atom37*atom41+atom52;
atom2694 = r*atom51;
atom2695 = atom54*e;
atom2696 = atom2694+atom2695;
atom2705 = -atom81*L*atom79;
atom3012 = -atom80*L*atom82;
atom3009 = r*atom54;
atom3010 = -atom51*e;
atom3011 = atom3009+atom3010;
atom2697 = r*atom57;
atom2698 = e*atom60;
atom2699 = atom2697+atom2698;
atom3252 = -atom488*e;
atom3251 = r*atom479;
atom3253 = atom3252+atom3251;
atom3007 = e*atom501;
atom3006 = r*atom497;
atom3008 = atom3007+atom3006;
atom3257 = -atom58*e;
atom3256 = -r*atom55;
atom104 = sin(b2);
atom3269 = atom3222-atom3221;
atom2712 = -atom2692+atom2691;
atom106 = sin(a2);
atom103 = cos(b2);
atom2719 = L*atom106*atom103;
atom105 = cos(a2);
atom3028 = atom104*atom105*L;
atom3027 = atom3016-atom3017;
atom3281 = atom3236-atom3237;
atom2713 = atom2694-atom2695;
atom3026 = atom3013-atom3014;
atom2720 = -atom105*L*atom103;
atom3025 = -atom104*L*atom106;
atom3023 = -atom3007+atom3006;
atom3295 = -atom3252+atom3251;
atom2714 = atom2697-atom2698;
atom3024 = atom3009-atom3010;
atom128 = sin(b3);
atom129 = cos(a3);
atom1 = sqrt(3);
atom3057 = atom128*L*atom129;
atom131 = 1/2*atom1;
atom3318 = atom3057*atom131;
atom130 = sin(a3);
atom127 = cos(b3);
atom2740 = L*atom130*atom127;
atom3316 = atom2740*atom131;
atom2739 = -atom128*L;
atom4 = -1/2*r*atom1;
atom5 = -1/2*e;
atom6 = atom4+atom5;
atom0 = -1/2*r;
atom2 = 1/2*e*atom1;
atom3 = atom0+atom2;
atom3307 = -atom6*atom467;
atom3308 = atom3*atom465;
atom3309 = atom3307+atom3308;
atom2727 = atom3*atom47;
atom2728 = atom6*atom48;
atom2729 = atom2727+atom2728;
atom3341 = 1/2*atom2740;
atom3343 = 1/2*atom3057;
atom3328 = -atom497*atom6;
atom3327 = atom3*atom501;
atom3329 = atom3328+atom3327;
atom3055 = atom3*atom60;
atom3054 = -atom6*atom57;
atom3056 = atom3055+atom3054;
atom2731 = atom6*atom54;
atom2730 = atom3*atom51;
atom2732 = atom2731+atom2730;
atom3052 = atom488*atom3;
atom3051 = atom479*atom6;
atom3053 = atom3052+atom3051;
atom3332 = -atom49*atom3;
atom3333 = -atom52*atom6;
atom3045 = atom3*atom54;
atom3044 = -atom6*atom51;
atom3046 = atom3045+atom3044;
atom2734 = atom6*atom60;
atom2733 = atom3*atom57;
atom2735 = atom2734+atom2733;
atom3353 = -atom488*atom6;
atom3352 = atom479*atom3;
atom3354 = atom3353+atom3352;
atom2741 = -L*atom129*atom127;
atom3038 = -atom128*L*atom130;
atom3042 = atom497*atom3;
atom3041 = atom6*atom501;
atom3043 = atom3042+atom3041;
atom3358 = -atom6*atom58;
atom3357 = -atom55*atom3;
atom169 = sin(b4);
atom170 = cos(a4);
atom3086 = atom169*atom170*L;
atom3381 = atom131*atom3086;
atom171 = sin(a4);
atom168 = cos(b4);
atom2767 = L*atom171*atom168;
atom3383 = atom2767*atom131;
atom2766 = -atom169*L;
atom7 = atom0-atom2;
atom8 = atom4-atom5;
atom3374 = atom465*atom7;
atom3373 = -atom8*atom467;
atom3375 = atom3374+atom3373;
atom2754 = atom47*atom7;
atom2755 = atom8*atom48;
atom2756 = atom2754+atom2755;
atom2758 = atom8*atom54;
atom2757 = atom51*atom7;
atom2759 = atom2758+atom2757;
atom3084 = -atom8*atom57;
atom3083 = atom60*atom7;
atom3085 = atom3084+atom3083;
atom3393 = atom501*atom7;
atom3394 = -atom8*atom497;
atom3395 = atom3393+atom3394;
atom3080 = atom488*atom7;
atom3081 = atom8*atom479;
atom3082 = atom3080+atom3081;
atom3406 = 1/2*atom3086;
atom3408 = 1/2*atom2767;
atom3398 = -atom8*atom52;
atom3397 = -atom49*atom7;
atom3423 = atom479*atom7;
atom3422 = -atom8*atom488;
atom3424 = atom3423+atom3422;
atom3419 = -atom8*atom58;
atom3418 = -atom55*atom7;
atom3071 = atom497*atom7;
atom3070 = atom8*atom501;
atom3072 = atom3071+atom3070;
atom2768 = -atom170*L*atom168;
atom3067 = -atom169*L*atom171;
atom2760 = atom7*atom57;
atom2761 = atom8*atom60;
atom2762 = atom2760+atom2761;
atom3074 = atom54*atom7;
atom3073 = -atom8*atom51;
atom3075 = atom3074+atom3073;
atom211 = sin(a5);
atom208 = cos(b5);
atom2788 = atom211*L*atom208;
atom3446 = -atom131*atom2788;
atom209 = sin(b5);
atom210 = cos(a5);
atom3103 = L*atom209*atom210;
atom3444 = -atom3103*atom131;
atom3438 = atom3374-atom3373;
atom2781 = atom2754-atom2755;
atom2787 = -L*atom209;
atom3455 = atom3393-atom3394;
atom2782 = -atom2758+atom2757;
atom3102 = -atom3084+atom3083;
atom3467 = 1/2*atom2788;
atom3465 = 1/2*atom3103;
atom3101 = atom3080-atom3081;
atom3090 = -atom211*L*atom209;
atom2789 = -L*atom208*atom210;
atom3096 = atom3074-atom3073;
atom3479 = atom3423-atom3422;
atom2783 = atom2760-atom2761;
atom3095 = atom3071-atom3070;
atom249 = sin(b6);
atom250 = cos(a6);
atom3120 = L*atom249*atom250;
atom3501 = -atom3120*atom131;
atom251 = sin(a6);
atom248 = cos(b6);
atom2809 = atom251*L*atom248;
atom3499 = -atom2809*atom131;
atom2802 = atom2727-atom2728;
atom3493 = -atom3307+atom3308;
atom2808 = -L*atom249;
atom2803 = -atom2731+atom2730;
atom3118 = atom3052-atom3051;
atom3119 = atom3055-atom3054;
atom3522 = 1/2*atom3120;
atom3520 = 1/2*atom2809;
atom3511 = -atom3328+atom3327;
atom3534 = -atom3353+atom3352;
atom3113 = atom3045-atom3044;
atom2804 = -atom2734+atom2733;
atom3112 = atom3042-atom3041;
atom2810 = -L*atom248*atom250;
atom3109 = -atom251*L*atom249;

gamma_ = [-(atom3223*dc-dB*atom2693)*dB+dc*(dc*atom2693-atom3223*dB)+atom80*dB1^2*L;
-dB*(dc*atom3238+(atom3233+atom3232)*dB-atom3015*da)+(atom2696*da+atom3018*dc+atom3015*dB)*da-dB1*(da1*atom3019+dB1*atom2704)-(da1*atom2704+dB1*atom3019)*da1+(atom3018*da+atom2696*dc-dB*atom3238)*dc;
-dB*(atom3253*dc+da*atom3008+(atom3257+atom3256)*dB)+da1*(dB1*atom3012-da1*atom2705)-(dB*atom3008-atom2699*da+dc*atom3011)*da+dB1*(da1*atom3012-dB1*atom2705)+(atom2699*dc-atom3253*dB-da*atom3011)*dc;
atom104*dB2^2*L+(dB*atom2712-dc*atom3269)*dB-dc*(dB*atom3269-dc*atom2712);
(atom3027*da-dB*atom3281+atom2713*dc)*dc-da2*(dB2*atom3028+da2*atom2719)+(atom3026*da-dc*atom3281-(atom3233-atom3232)*dB)*dB+(atom3027*dc+atom3026*dB+atom2713*da)*da-(atom3028*da2+dB2*atom2719)*dB2;
-(atom3024*dc+atom3023*dB-da*atom2714)*da+da2*(dB2*atom3025-da2*atom2720)-(atom3295*dB+atom3024*da-dc*atom2714)*dc+dB2*(da2*atom3025-dB2*atom2720)+dB*(dB*(atom3257-atom3256)-atom3295*dc-atom3023*da);
1/2*dB3*(2*da3*atom3318+dB3*(2*atom3316+atom2739))+dB*(atom2729*dB-atom3309*dc)-dc*(atom3309*dB-atom2729*dc)+da3*(atom3316*da3+dB3*atom3318);
da3*(da3*atom3341+dB3*atom3343)+dB3*(dB3*(atom3341-atom2739*atom131)+atom3343*da3)+da*(atom3056*dc+atom3053*dB+atom2732*da)+dc*(atom2732*dc-dB*atom3329+atom3056*da)-(dB*(atom3332+atom3333)-atom3053*da+dc*atom3329)*dB;
-dB*(dB*(atom3358+atom3357)+atom3354*dc+da*atom3043)+(dc*atom2735-atom3046*da-atom3354*dB)*dc-da*(atom3046*dc+dB*atom3043-da*atom2735)+dB3*(da3*atom3038-dB3*atom2741)+da3*(dB3*atom3038-da3*atom2741);
(atom3383*da4+atom3381*dB4)*da4+dB*(atom2756*dB-atom3375*dc)+1/2*((2*atom3383+atom2766)*dB4+2*da4*atom3381)*dB4-dc*(atom3375*dB-atom2756*dc);
dB*(atom3082*da-dB*(atom3398+atom3397)-atom3395*dc)+(atom3406*dB4+atom3408*da4)*da4+(atom3085*da+dc*atom2759-atom3395*dB)*dc+(atom3082*dB+atom3085*dc+da*atom2759)*da+((atom3408-atom2766*atom131)*dB4+da4*atom3406)*dB4;
-dB*(dB*(atom3419+atom3418)+dc*atom3424+da*atom3072)-(atom2768*da4-atom3067*dB4)*da4-(atom2768*dB4-atom3067*da4)*dB4-da*(dB*atom3072-atom2762*da+dc*atom3075)-dc*(da*atom3075-atom2762*dc+dB*atom3424);
dc*(dc*atom2781-dB*atom3438)+da5*(da5*atom3446+dB5*atom3444)+1/2*(2*da5*atom3444+(atom2787+2*atom3446)*dB5)*dB5+dB*(atom2781*dB-dc*atom3438);
dc*(dc*atom2782+atom3102*da-atom3455*dB)-(atom3455*dc-(atom3398-atom3397)*dB-atom3101*da)*dB+((atom2787*atom131+atom3467)*dB5+atom3465*da5)*dB5+(da*atom2782+atom3101*dB+atom3102*dc)*da+da5*(da5*atom3467+atom3465*dB5);
-da*(atom3096*dc-atom2783*da+atom3095*dB)-(atom2789*da5-atom3090*dB5)*da5+dB*((atom3419-atom3418)*dB-atom3095*da-atom3479*dc)-(atom2789*dB5-da5*atom3090)*dB5-(atom3096*da+atom3479*dB-atom2783*dc)*dc;
-(atom3493*dc-dB*atom2802)*dB+da6*(da6*atom3499+atom3501*dB6)+1/2*(dB6*(atom2808+2*atom3499)+2*da6*atom3501)*dB6+(dc*atom2802-atom3493*dB)*dc;
da6*(da6*atom3520+atom3522*dB6)+(dB*atom3118+dc*atom3119+da*atom2803)*da+dc*(dc*atom2803-dB*atom3511+da*atom3119)-dB*(dc*atom3511+(atom3332-atom3333)*dB-da*atom3118)+((atom2808*atom131+atom3520)*dB6+da6*atom3522)*dB6;
-(dB*atom3534-dc*atom2804+da*atom3113)*dc+dB6*(da6*atom3109-atom2810*dB6)+dB*((atom3358-atom3357)*dB-da*atom3112-dc*atom3534)+da6*(dB6*atom3109-atom2810*da6)-(dc*atom3113+dB*atom3112-da*atom2804)*da];

%endfunction
