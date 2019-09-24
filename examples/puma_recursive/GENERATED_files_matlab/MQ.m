function MQ_ = MQ(q,dq,time,param)

a1 = q( 1 ); 
a2 = q( 2 ); 
a3 = q( 3 ); 
a4 = q( 4 ); 
a5 = q( 5 ); 
a6 = q( 6 ); 

da1 = dq( 1 ); 
da2 = dq( 2 ); 
da3 = dq( 3 ); 
da4 = dq( 4 ); 
da5 = dq( 5 ); 
da6 = dq( 6 ); 

t= time ;

g = param( 1 ); 
d3 = param( 2 ); 
r3 = param( 3 ); 
d4 = param( 4 ); 
r4 = param( 5 ); 
m1 = param( 6 ); 
mx1 = param( 7 ); 
my1 = param( 8 ); 
mz1 = param( 9 ); 
Ixx1 = param( 10 ); 
Ixy1 = param( 11 ); 
Ixz1 = param( 12 ); 
Iyy1 = param( 13 ); 
Iyz1 = param( 14 ); 
Izz1 = param( 15 ); 
m2 = param( 16 ); 
mx2 = param( 17 ); 
my2 = param( 18 ); 
mz2 = param( 19 ); 
Ixx2 = param( 20 ); 
Ixy2 = param( 21 ); 
Ixz2 = param( 22 ); 
Iyy2 = param( 23 ); 
Iyz2 = param( 24 ); 
Izz2 = param( 25 ); 
m3 = param( 26 ); 
mx3 = param( 27 ); 
my3 = param( 28 ); 
mz3 = param( 29 ); 
Ixx3 = param( 30 ); 
Ixy3 = param( 31 ); 
Ixz3 = param( 32 ); 
Iyy3 = param( 33 ); 
Iyz3 = param( 34 ); 
Izz3 = param( 35 ); 
m4 = param( 36 ); 
mx4 = param( 37 ); 
my4 = param( 38 ); 
mz4 = param( 39 ); 
Ixx4 = param( 40 ); 
Ixy4 = param( 41 ); 
Ixz4 = param( 42 ); 
Iyy4 = param( 43 ); 
Iyz4 = param( 44 ); 
Izz4 = param( 45 ); 
m5 = param( 46 ); 
mx5 = param( 47 ); 
my5 = param( 48 ); 
mz5 = param( 49 ); 
Ixx5 = param( 50 ); 
Ixy5 = param( 51 ); 
Ixz5 = param( 52 ); 
Iyy5 = param( 53 ); 
Iyz5 = param( 54 ); 
Izz5 = param( 55 ); 
m6 = param( 56 ); 
mx6 = param( 57 ); 
my6 = param( 58 ); 
mz6 = param( 59 ); 
Ixx6 = param( 60 ); 
Ixy6 = param( 61 ); 
Ixz6 = param( 62 ); 
Iyy6 = param( 63 ); 
Iyz6 = param( 64 ); 
Izz6 = param( 65 ); 
Ma1 = param( 66 ); 
Ma2 = param( 67 ); 
Ma3 = param( 68 ); 
Ma4 = param( 69 ); 
Ma5 = param( 70 ); 
Ma6 = param( 71 ); 
FS001 = param( 72 ); 
FSa11 = param( 73 ); 
FSb11 = param( 74 ); 
FSa21 = param( 75 ); 
FSb21 = param( 76 ); 
FSa31 = param( 77 ); 
FSb31 = param( 78 ); 
FSa41 = param( 79 ); 
FSb41 = param( 80 ); 
FS002 = param( 81 ); 
FSa12 = param( 82 ); 
FSb12 = param( 83 ); 
FSa22 = param( 84 ); 
FSb22 = param( 85 ); 
FSa32 = param( 86 ); 
FSb32 = param( 87 ); 
FSa42 = param( 88 ); 
FSb42 = param( 89 ); 
FS003 = param( 90 ); 
FSa13 = param( 91 ); 
FSb13 = param( 92 ); 
FSa23 = param( 93 ); 
FSb23 = param( 94 ); 
FSa33 = param( 95 ); 
FSb33 = param( 96 ); 
FSa43 = param( 97 ); 
FSb43 = param( 98 ); 
FS004 = param( 99 ); 
FSa14 = param( 100 ); 
FSb14 = param( 101 ); 
FSa24 = param( 102 ); 
FSb24 = param( 103 ); 
FSa34 = param( 104 ); 
FSb34 = param( 105 ); 
FSa44 = param( 106 ); 
FSb44 = param( 107 ); 
FS005 = param( 108 ); 
FSa15 = param( 109 ); 
FSb15 = param( 110 ); 
FSa25 = param( 111 ); 
FSb25 = param( 112 ); 
FSa35 = param( 113 ); 
FSb35 = param( 114 ); 
FSa45 = param( 115 ); 
FSb45 = param( 116 ); 
FS006 = param( 117 ); 
FSa16 = param( 118 ); 
FSb16 = param( 119 ); 
FSa26 = param( 120 ); 
FSb26 = param( 121 ); 
FSa36 = param( 122 ); 
FSb36 = param( 123 ); 
FSa46 = param( 124 ); 
FSb46 = param( 125 ); 
g = param( 126 ); 


atom57 = a3+a2;
atom58 = cos(atom57);
atom114 = cos(a5);
atom59 = sin(atom57);
atom80 = cos(a4);
atom115 = sin(a5);
atom94 = -atom59*atom80;
atom152 = cos(a6);
atom81 = sin(a4);
atom847 = atom81*atom114;
atom153 = sin(a6);
atom36 = sin(a2);
atom35 = cos(a2);
atom2582 = -atom35*atom59+atom58*atom36;
atom2589 = -atom2582*d3;
atom2832 = -atom2589-r4;
atom2579 = atom59*atom36+atom58*atom35;
atom2590 = atom2579*d3;
atom2831 = d4+atom2590;
atom1447 = -atom847*atom153+atom152*atom80;
atom2857 = -atom59*atom2832+atom58*atom2831;
atom1049 = atom114*atom80;
atom1723 = -atom81*atom152-atom153*atom1049;
atom2853 = -atom58*r3;
atom2854 = r3*atom59;
atom3688 = atom115*atom153;
atom3698 = atom1447*atom2857-atom2854*atom3688+atom1723*atom2853;
atom3687 = -atom115*atom152;
atom1729 = atom152*atom1049-atom81*atom153;
atom1444 = atom152*atom847+atom153*atom80;
atom3693 = -atom2854*atom3687+atom2857*atom1444+atom2853*atom1729;
atom133 = -atom115*atom94-atom58*atom114;
atom3719 = atom3698*mx6-my6*atom3693;
atom848 = -atom81*atom115;
atom1060 = -atom115*atom80;
atom3249 = atom848*atom2857+atom114*atom2854+atom2853*atom1060;
atom95 = atom81*atom59;
atom130 = atom114*atom94-atom58*atom115;
atom3716 = atom3249*mx6+mz6*atom3693;
atom171 = atom95*atom152-atom130*atom153;
atom168 = atom130*atom152+atom95*atom153;
atom3713 = -mz6*atom3698-my6*atom3249;
atom883 = Ixz5*atom95+atom130*Ixx5+atom133*Ixy5;
atom888 = atom95*Iyz5+atom133*Iyy5+atom130*Ixy5;
atom893 = Izz5*atom95+atom133*Iyz5+atom130*Ixz5;
atom2929 = atom2853^2+atom2854^2+atom2857^2;
atom521 = atom95*Ixy4+atom58*Ixz4+atom94*Ixx4;
atom526 = atom95*Iyy4+atom94*Ixy4+atom58*Iyz4;
atom531 = Ixz4*atom94+atom95*Iyz4+atom58*Izz4;
atom2860 = atom81*atom2857+atom2853*atom80;
atom2863 = -atom81*atom2853+atom2857*atom80;
atom2876 = -atom2860*my4+mx4*atom2863;
atom2870 = -mz4*atom2863-atom2854*my4;
atom2873 = mz4*atom2860+atom2854*mx4;
atom299 = atom35*d3;
atom2576 = r3*atom36;
atom2575 = -atom35*r3;
atom2585 = atom2579*atom2575-atom2582*atom2576;
atom2588 = atom2579*atom2576+atom2582*atom2575;
atom3244 = atom2857*atom847+atom115*atom2854+atom2853*atom1049;
atom3270 = atom3249*mx5-atom3244*my5;
atom3267 = -mx5*atom2863+mz5*atom3244;
atom3264 = -mz5*atom3249+atom2863*my5;
atom1492 = -atom133*Izz6+atom168*Ixz6+atom171*Iyz6;
atom1487 = atom168*Ixy6+Iyy6*atom171-atom133*Iyz6;
atom1482 = -atom133*Ixz6+atom168*Ixx6+atom171*Ixy6;
atom3701 = -atom2832*atom1729-atom3687*atom2831;
atom3704 = -atom1723*atom2832-atom3688*atom2831;
atom3728 = mx6*atom3704-my6*atom3701;
atom3255 = atom114*atom2831-atom2832*atom1060;
atom3722 = -mz6*atom3704-my6*atom3255;
atom3725 = atom3255*mx6+mz6*atom3701;
atom3747 = -atom848*atom3719+atom1444*atom3713+atom1447*atom3716;
atom2865 = atom81*atom2832;
atom3252 = atom115*atom2831-atom2832*atom1049;
atom3276 = mz5*atom3252-atom2865*mx5;
atom3273 = atom2865*my5-mz5*atom3255;
atom3279 = atom3255*mx5-atom3252*my5;
atom3298 = atom848*atom3267+atom847*atom3264+atom3270*atom80;
atom2932 = atom2854*atom2831-atom2853*atom2832;
atom2599 = -atom2585*my3+mx3*atom2588;
atom343 = -Ixz3*atom59-atom58*Iyz3;
atom2864 = -atom2832*atom80;
atom2885 = -atom2864*my4+atom2865*mx4;
atom2882 = mx4*atom2831+mz4*atom2864;
atom2879 = -atom2865*mz4-my4*atom2831;
atom2902 = atom2873*atom80+atom81*atom2870;
atom565 = atom81*atom521+atom526*atom80;
atom933 = atom848*atom888+atom883*atom847+atom893*atom80;
atom1532 = atom1447*atom1487+atom1444*atom1482-atom848*atom1492;
atom2867 = -atom81*r4;
atom3258 = atom115*d4+r4*atom1049;
atom3285 = mz5*atom3258-atom2867*mx5;
atom3261 = atom1060*r4+atom114*d4;
atom3282 = atom2867*my5-mz5*atom3261;
atom3288 = -atom3258*my5+mx5*atom3261;
atom2888 = -d4*my4-atom2867*mz4;
atom2866 = r4*atom80;
atom2891 = mz4*atom2866+d4*mx4;
atom2894 = atom2867*mx4-atom2866*my4;
atom2935 = atom2853*r4+atom2854*d4;
atom3710 = -atom3688*d4+atom1723*r4;
atom3707 = -d4*atom3687+r4*atom1729;
atom3737 = -my6*atom3707+mx6*atom3710;
atom3734 = atom3261*mx6+mz6*atom3707;
atom3731 = -mz6*atom3710-my6*atom3261;
atom24 = cos(a1);
atom61 = -atom59*atom24;
atom25 = sin(a1);
atom60 = atom58*atom24;
atom84 = -atom81*atom25+atom60*atom80;
atom62 = atom58*atom25;
atom93 = -atom81*atom62+atom24*atom80;
atom63 = -atom59*atom25;
atom90 = atom80*atom62+atom81*atom24;
atom127 = atom114*atom63-atom90*atom115;
atom124 = atom115*atom63+atom114*atom90;
atom143 = atom127*my5+mx5*atom124+atom93*mz5;
atom121 = -atom84*atom115+atom61*atom114;
atom149 = -g*atom143;
atom87 = -atom81*atom60-atom80*atom25;
atom118 = atom61*atom115+atom114*atom84;
atom138 = mz5*atom87+atom121*my5+atom118*mx5;
atom150 = atom138*g;
atom4337 = atom121*atom149+atom150*atom127;
atom4334 = atom150*atom124+atom118*atom149;
atom4340 = atom87*atom149+atom150*atom93;
atom2574 = -atom58*da1;
atom2852 = da4-atom2574;
atom327 = da3+da2;
atom2573 = -atom59*da1;
atom2848 = atom81*atom327+atom2573*atom80;
atom3238 = -atom114*atom2852-atom115*atom2848;
atom2851 = atom80*atom327-atom81*atom2573;
atom3389 = atom114*atom2851;
atom2972 = atom80*atom2574;
atom3388 = -atom2573*atom115+atom114*atom2972;
atom3576 = da2*atom3388+da3*atom3388+atom3389*da4+da5*atom3238;
atom3392 = -atom2972*atom115-atom2573*atom114;
atom3235 = -atom2852*atom115+atom114*atom2848;
atom3583 = da2*atom3392-da4*atom115*atom2851+da3*atom3392-da5*atom3235;
atom2973 = -atom81*atom2574;
atom3144 = da2*atom2973+da3*atom2973-da4*atom2848;
atom449 = atom59*d4-atom58*r4;
atom467 = -atom449*da1;
atom443 = -da2+atom327;
atom446 = atom58*d4+atom59*r4;
atom451 = atom443*atom446;
atom465 = -atom451-atom446*da2;
atom2995 = atom465*atom25+atom467*atom24;
atom452 = atom446+atom299;
atom458 = da1*atom452;
atom300 = -atom36*d3;
atom453 = atom449-atom300;
atom450 = atom449*atom443;
atom301 = r3*da1;
atom456 = -da2*atom453-atom450;
atom459 = -atom301+atom456;
atom2980 = -atom458*atom25+atom459*atom24;
atom457 = atom451+da2*atom452;
atom466 = -da1*atom453;
atom2992 = -atom25*atom457+atom24*atom466;
atom3109 = atom2980*da1+atom2995*da3+da2*atom2992;
atom2989 = -atom467*atom25+atom465*atom24;
atom2986 = -atom25*atom466-atom24*atom457;
atom2983 = atom459*atom25+atom458*atom24;
atom3104 = -da1*atom2983+da3*atom2989+da2*atom2986;
atom3554 = atom138*atom3109-atom3104*atom143;
atom469 = -atom449*da2-atom450;
atom3110 = -atom469*da3-atom456*da2;
atom148 = mz5*atom95+atom133*my5+atom130*mx5;
atom3548 = -atom148*atom3109+atom3110*atom143;
atom3551 = -atom138*atom3110+atom148*atom3104;
atom3239 = da5+atom2851;
atom3600 = Ixz5*atom3238;
atom3599 = -Ixy5*atom3239;
atom3641 = (atom3600+atom3599)*atom3235+atom3548*atom118+atom130*atom3554+atom3551*atom124+Ixx5*atom3576+atom3583*Ixy5-(Iyz5*atom3239-Izz5*atom3238)*atom3239-(Iyy5*atom3239-atom3238*Iyz5)*atom3238+Ixz5*atom3144;
atom3611 = -atom3235*Iyz5;
atom3642 = atom127*atom3551+(atom3611-atom3599)*atom3238+Ixy5*atom3576+Iyy5*atom3583-(Izz5*atom3235-Ixz5*atom3239)*atom3239+atom133*atom3554+atom3235*(Ixx5*atom3239-Ixz5*atom3235)+atom3548*atom121+atom3144*Iyz5;
atom3643 = -(atom3238*Ixx5-atom3235*Ixy5)*atom3235+atom95*atom3554+Izz5*atom3144+atom3548*atom87+(atom3235*Iyy5-atom3238*Ixy5)*atom3238+Ixz5*atom3576+atom93*atom3551-(atom3611+atom3600)*atom3239+atom3583*Iyz5;
atom489 = atom58*da4;
atom110 = atom94*mx4+atom95*my4+atom58*mz4;
atom2996 = atom489*atom24;
atom488 = atom59*da4;
atom100 = atom87*my4-atom61*mz4+atom84*mx4;
atom3005 = atom110*atom2996+atom488*atom100;
atom2636 = atom24*atom327;
atom2977 = atom488*atom25+atom2636;
atom3037 = da1*(atom110*atom2977+m4*atom2980)-(atom3005-m4*atom2995)*da3+da2*(m4*atom2992-atom3005);
atom2635 = -atom25*atom327;
atom2975 = atom488*atom24+atom2635;
atom2997 = atom489*atom25;
atom105 = atom90*mx4-mz4*atom63+atom93*my4;
atom3001 = -atom110*atom2997-atom488*atom105;
atom3032 = -(m4*atom2983-atom2975*atom110)*da1+(m4*atom2989-atom3001)*da3+da2*(m4*atom2986-atom3001);
atom3063 = -atom2848*atom80+atom81*atom2851;
atom3056 = -atom81*atom2852;
atom3067 = -atom2852*atom3056;
atom3057 = -atom2852*atom80;
atom3064 = atom2852*atom3057;
atom3011 = -atom105*atom2996+atom2997*atom100;
atom3042 = -da3*(atom3011+m4*atom469)-(atom3011+atom456*m4)*da2-da1*(atom2977*atom105+atom2975*atom100);
atom3060 = atom2851*atom80+atom81*atom2848;
atom3213 = -atom59*atom3042+atom3037*atom62+(atom2848*atom3060+atom3067)*my4+mz4*(atom3056*atom2851-atom3057*atom2848)+atom3032*atom60+(atom3064-atom3060*atom2851)*mx4;
atom3214 = -atom58*atom3042+atom3037*atom63+atom61*atom3032+mz4*(atom2851^2+atom2848^2)-atom2852*atom2851*my4-atom2852*atom2848*mx4;
atom2683 = atom2582*atom327;
atom2687 = -atom2573*atom2582+atom2579*atom2574;
atom2694 = -atom2683*atom327;
atom2684 = -atom2579*atom327;
atom2691 = atom2684*atom327;
atom298 = da2*d3;
atom303 = -atom298*atom36;
atom68 = -mz3*atom25+atom61*my3+mx3*atom60;
atom73 = atom63*my3+mx3*atom62+mz3*atom24;
atom2669 = -da1*(atom2635*atom68+atom73*atom2636)-m3*atom303*da2;
atom76 = -atom59*mx3-atom58*my3;
atom302 = da1*atom299;
atom305 = -atom301+atom303;
atom2642 = atom305*atom25+atom302*atom24;
atom312 = atom300*da1;
atom304 = -atom35*atom298;
atom2645 = -atom312*atom25+atom304*atom24;
atom2663 = da1*(atom2635*atom76-m3*atom2642)+atom2645*m3*da2;
atom37 = atom35*atom24;
atom2648 = atom304*atom25+atom312*atom24;
atom2639 = -atom302*atom25+atom305*atom24;
atom39 = atom35*atom25;
atom2666 = (atom2636*atom76+m3*atom2639)*da1+m3*da2*atom2648;
atom2690 = -atom2573*atom2579-atom2582*atom2574;
atom38 = -atom36*atom24;
atom40 = -atom36*atom25;
atom2819 = (atom2573*atom2690+atom2691)*my3-atom35*atom2669+atom40*atom2666-mz3*(atom2684*atom2574+atom2573*atom2683)-(atom2694+atom2690*atom2574)*mx3+atom38*atom2663;
atom2449 = -atom36*da1;
atom2521 = -da2*Ixy2;
atom2533 = -Iyz2*atom2449;
atom2450 = -atom35*da1;
atom2485 = da2*atom2449;
atom2486 = da2*atom2450;
atom2522 = atom2450*Ixz2;
atom2757 = da3*atom2574+da2*atom2574;
atom2760 = -atom2573*da2-atom2573*da3;
atom2732 = atom2639*da1+da2*atom2648;
atom2729 = atom2645*da2-da1*atom2642;
atom2741 = -atom2729*atom73+atom2732*atom68;
atom321 = -atom303*da2;
atom2738 = -atom321*atom68+atom2729*atom76;
atom2735 = -atom2732*atom76+atom73*atom321;
atom2771 = Ixz3*atom2574;
atom2770 = -Ixy3*atom327;
atom2782 = -atom2573*Iyz3;
atom3139 = atom2972*da2+atom2972*da3+da4*atom2851;
atom3119 = -atom105*atom3104+atom100*atom3109;
atom3116 = -atom3110*atom100+atom110*atom3104;
atom3113 = atom3110*atom105-atom110*atom3109;
atom3172 = -atom2848*Iyz4;
atom3161 = Ixz4*atom2851;
atom3204 = -atom61*atom3113-Izz4*atom2760-atom2852*(atom3172+atom3161)+atom3144*Iyz4+(atom2848*Ixy4-Ixx4*atom2851)*atom2848+atom2851*(Iyy4*atom2848-atom2851*Ixy4)+Ixz4*atom3139+atom58*atom3119-atom63*atom3116;
atom3160 = -atom2852*Ixy4;
atom3203 = atom87*atom3113+atom2852*(Ixz4*atom2852-Izz4*atom2848)+atom3119*atom95-atom2760*Iyz4+atom3139*Ixy4+Iyy4*atom3144+atom2851*(atom3172-atom3160)+atom2848*(atom2852*Ixx4-Ixz4*atom2848)+atom93*atom3116;
atom3202 = -(atom2852*Iyy4-atom2851*Iyz4)*atom2851-atom2852*(atom2852*Iyz4-Izz4*atom2851)+atom3119*atom94+atom84*atom3113-Ixz4*atom2760+atom3144*Ixy4+atom90*atom3116+(atom3161+atom3160)*atom2848+atom3139*Ixx4;
atom3494 = -atom114*atom3235+atom115*atom3238;
atom3491 = -atom115*atom3239;
atom3490 = atom114*atom3239;
atom834 = da5*atom80;
atom835 = atom834+atom327;
atom833 = -atom81*da5;
atom837 = atom488+atom58*atom833;
atom3399 = atom835*atom24+atom837*atom25;
atom3396 = atom837*atom24-atom835*atom25;
atom839 = atom489-atom59*atom833;
atom3400 = atom24*atom839;
atom3404 = atom25*atom839;
atom3427 = -atom3400*atom143+atom3404*atom138;
atom982 = -atom58*atom834;
atom3407 = atom24*atom833+atom982*atom25;
atom3403 = -atom833*atom25+atom24*atom982;
atom3467 = -da3*(atom469*m5+atom3427)-da1*(atom138*atom3396+atom3399*atom143)-(atom456*m5+atom3427)*da2+da4*(atom3403*atom143-atom138*atom3407);
atom983 = atom59*atom834;
atom3418 = atom837*atom138+atom3400*atom148;
atom3460 = da1*(atom2980*m5+atom148*atom3399)+da4*(atom138*atom983-atom148*atom3403)+da3*(m5*atom2995-atom3418)-da2*(atom3418-m5*atom2992);
atom3411 = -atom3404*atom148-atom837*atom143;
atom3453 = da2*(m5*atom2986-atom3411)+da3*(m5*atom2989-atom3411)+da4*(atom148*atom3407-atom983*atom143)-(m5*atom2983-atom3396*atom148)*da1;
atom3658 = atom61*atom3453+mx5*(atom3491*atom3239-atom3238*atom3494)-atom58*atom3467+atom63*atom3460-mz5*(atom3491*atom3235-atom3238*atom3490)+(atom3235*atom3494-atom3239*atom3490)*my5;
atom3486 = -atom81*atom3235-atom3239*atom1049;
atom3483 = atom81*atom3238+atom1060*atom3239;
atom3489 = -atom3235*atom1060+atom3238*atom1049;
atom3657 = -(atom3483*atom3239-atom3235*atom3489)*my5+(atom3483*atom3238-atom3235*atom3486)*mz5-atom59*atom3467-(atom3238*atom3489-atom3486*atom3239)*mx5+atom3460*atom62+atom3453*atom60;
atom3500 = -atom847*atom3239+atom3235*atom80;
atom3497 = atom848*atom3239-atom3238*atom80;
atom3503 = -atom848*atom3235+atom3238*atom847;
atom3682 = atom153*atom3239+atom3235*atom152;
atom3686 = da6-atom3238;
atom4036 = -atom1444*atom3686-atom848*atom3682;
atom3685 = -atom3235*atom153+atom152*atom3239;
atom4033 = atom1447*atom3686+atom3685*atom848;
atom4039 = atom3685*atom1444-atom3682*atom1447;
atom1421 = da6*atom115;
atom1427 = atom834+atom81*atom1421;
atom156 = atom152*atom118+atom87*atom153;
atom159 = atom87*atom152-atom118*atom153;
atom1589 = atom59*atom1427;
atom176 = -atom121*mz6+atom156*mx6+my6*atom159;
atom1581 = -atom58*atom1427;
atom1425 = atom1421*atom80+atom833;
atom3914 = atom24*atom1581-atom1425*atom25;
atom186 = -atom133*mz6+atom168*mx6+my6*atom171;
atom1422 = atom114*da6;
atom1423 = atom1422+da4;
atom1431 = atom58*atom1425+atom59*atom1423;
atom1434 = atom58*atom1423-atom1425*atom59;
atom3911 = atom1434*atom24;
atom3938 = atom186*atom3911+atom1431*atom176;
atom1428 = atom1427+atom327;
atom3910 = atom1431*atom25+atom24*atom1428;
atom1583 = atom1422*atom80;
atom1592 = -atom59*atom1583-atom58*atom1421;
atom1585 = atom58*atom1583-atom59*atom1421;
atom1588 = atom81*atom1422;
atom3917 = -atom25*atom1588+atom1585*atom24;
atom3990 = -(atom3938-atom2995*m6)*da3-da4*(atom3914*atom186-atom1589*atom176)+da1*(atom2980*m6+atom186*atom3910)-da2*(atom3938-m6*atom2992)-da5*(atom3917*atom186-atom1592*atom176);
atom3924 = atom1585*atom25+atom24*atom1588;
atom165 = -atom153*atom124+atom93*atom152;
atom162 = atom93*atom153+atom152*atom124;
atom181 = my6*atom165-atom127*mz6+atom162*mx6;
atom3907 = atom24*atom1431-atom1428*atom25;
atom3918 = atom1434*atom25;
atom3928 = -atom186*atom3918-atom181*atom1431;
atom3921 = atom1425*atom24+atom1581*atom25;
atom3981 = -da1*(m6*atom2983-atom186*atom3907)+da5*(atom186*atom3924-atom181*atom1592)+da3*(m6*atom2989-atom3928)+da2*(m6*atom2986-atom3928)+da4*(atom3921*atom186-atom181*atom1589);
atom4030 = -atom3685*atom3687+atom3682*atom3688;
atom4024 = -atom3688*atom3686+atom3685*atom114;
atom4027 = atom3687*atom3686-atom114*atom3682;
atom3950 = -atom181*atom3911+atom3918*atom176;
atom3999 = -da4*(atom3921*atom176-atom3914*atom181)-da1*(atom181*atom3910+atom3907*atom176)-(atom469*m6+atom3950)*da3-da2*(atom3950+atom456*m6)+(atom3917*atom181-atom3924*atom176)*da5;
atom4203 = atom61*atom3981+atom63*atom3990+my6*(atom3682*atom4030-atom4024*atom3686)+mz6*(atom3685*atom4024-atom4027*atom3682)-(atom3685*atom4030-atom4027*atom3686)*mx6-atom58*atom3999;
atom4015 = atom3685*atom1060+atom1723*atom3686;
atom4018 = -atom3682*atom1060-atom3686*atom1729;
atom4021 = atom3685*atom1729-atom3682*atom1723;
atom4202 = -(atom3682*atom4018-atom3685*atom4015)*mz6+atom3990*atom62+my6*(atom3682*atom4021-atom4015*atom3686)-(atom3685*atom4021-atom4018*atom3686)*mx6+atom60*atom3981-atom59*atom3999;
atom4151 = -atom3682*Iyz6;
atom4139 = -atom3686*Ixy6;
atom3900 = atom152*atom2973-atom3388*atom153;
atom4123 = -(atom3389*atom153+atom152*atom2848)*da4+da2*atom3900-atom3682*da6+da3*atom3900-da5*atom3238*atom153;
atom3893 = atom152*atom3388+atom2973*atom153;
atom4114 = da5*atom152*atom3238+da3*atom3893-da4*(atom2848*atom153-atom3389*atom152)+atom3893*da2+atom3685*da6;
atom4084 = -atom186*atom3109+atom3110*atom181;
atom4087 = atom186*atom3104-atom3110*atom176;
atom4090 = atom3109*atom176-atom181*atom3104;
atom4182 = atom4084*atom159-atom3682*(atom3682*Ixz6-atom3686*Ixx6)+atom4123*Iyy6-atom3583*Iyz6+atom4087*atom165-atom3686*(atom3682*Izz6-Ixz6*atom3686)+atom171*atom4090+Ixy6*atom4114+atom3685*(atom4151-atom4139);
atom4140 = atom3685*Ixz6;
atom4181 = atom4087*atom162+atom168*atom4090+atom3682*(atom4140+atom4139)+atom4084*atom156-Ixz6*atom3583-atom3686*(atom3686*Iyz6-atom3685*Izz6)+atom3685*(atom3685*Iyz6-atom3686*Iyy6)+Ixx6*atom4114+atom4123*Ixy6;
atom4183 = Ixz6*atom4114-atom3685*(atom3685*Ixy6-atom3682*Iyy6)-Izz6*atom3583+atom4123*Iyz6-atom4084*atom121-atom133*atom4090-(atom4151+atom4140)*atom3686-atom127*atom4087+(atom3682*Ixy6-atom3685*Ixx6)*atom3682;
atom54 = -(atom40*my2+atom24*mz2+atom39*mx2)*g;
atom55 = (mx2*atom37-atom25*mz2+atom38*my2)*g;
atom78 = g*atom68;
atom77 = -atom73*g;
atom111 = -atom105*g;
atom112 = atom100*g;
atom4296 = atom90*atom112+atom84*atom111;
atom4299 = atom93*atom112+atom87*atom111;
atom4302 = -atom63*atom112-atom61*atom111;
atom188 = g*atom176;
atom187 = -atom181*g;
atom4384 = -atom187*atom121-atom188*atom127;
atom4381 = atom188*atom165+atom187*atom159;
atom4378 = atom187*atom156+atom188*atom162;
atom873 = atom80*Iyz5+atom847*Ixy5+atom848*Iyy5;
atom868 = atom848*Ixy5+atom847*Ixx5+Ixz5*atom80;
atom878 = Izz5*atom80+atom848*Iyz5+Ixz5*atom847;
atom3311 = atom848*atom3276+atom3273*atom847+atom3279*atom80;
atom2938 = atom2831^2+atom2832^2;
atom2604 = mx3*atom2590-atom2589*my3;
atom2910 = atom81*atom2879+atom2882*atom80;
atom552 = (atom81*Ixy4+Iyy4*atom80)*atom80+atom81*(atom81*Ixx4+atom80*Ixy4);
atom918 = atom878*atom80+atom848*atom873+atom847*atom868;
atom3765 = -atom848*atom3728+atom3722*atom1444+atom1447*atom3725;
atom1472 = -atom848*Iyz6+atom1444*Ixy6+atom1447*Iyy6;
atom1467 = atom1447*Ixy6-atom848*Ixz6+atom1444*Ixx6;
atom1477 = atom1447*Iyz6+Ixz6*atom1444-atom848*Izz6;
atom1517 = atom1467*atom1444-atom848*atom1477+atom1447*atom1472;
atom3324 = atom3288*atom80+atom848*atom3285+atom3282*atom847;
atom2918 = atom80*atom2891+atom81*atom2888;
atom2941 = d4*atom2831-atom2832*r4;
atom3783 = -atom848*atom3737+atom1444*atom3731+atom1447*atom3734;
atom516 = Iyz4*atom80+atom81*Ixz4;
atom3333 = -atom115*atom868-atom114*atom873;
atom3804 = atom3688*atom1472+atom114*atom1477+atom1467*atom3687;
atom3807 = atom1472*atom152+atom1467*atom153;
atom151 = -m5*g;
atom2814 = atom2573*(atom2573*Ixy3-Ixx3*atom2574)+Ixz3*atom2757+(atom2573*Iyy3-Ixy3*atom2574)*atom2574+atom2760*Iyz3-atom2735*atom25-(atom2771+atom2782)*atom327+atom24*atom2738;
atom3212 = atom3203*atom80+atom81*atom3202;
atom3653 = atom848*atom3642+atom3641*atom847+atom3643*atom80;
atom4193 = atom1447*atom4182-atom848*atom4183+atom1444*atom4181;
atom4271 = atom78*atom24-atom77*atom25;
atom113 = -m4*g;
atom4310 = atom4299*atom80+atom81*atom4296;
atom4350 = atom848*atom4337+atom4340*atom80+atom847*atom4334;
atom189 = -m6*g;
atom4394 = -atom848*atom4384+atom1447*atom4381+atom4378*atom1444;
atom2944 = d4^2+r4^2;
atom3812 = atom114*Ixz6+atom3687*Ixx6+atom3688*Ixy6;
atom3817 = atom114*Iyz6+atom3688*Iyy6+atom3687*Ixy6;
atom3822 = Ixz6*atom3687+atom3688*Iyz6+atom114*Izz6;
atom3874 = -atom130*atom3273-m4*atom2932-atom1532-atom2599+atom36*Ixz2-atom3298-atom3747-atom95*atom3279+atom58*mz3*atom2589-m5*atom2932-atom58*atom2885-atom2902-atom343-mz3*atom59*atom2590-atom933-atom3725*atom171-atom565-m3*atom2576*d3-m6*atom2932-atom133*atom3276+atom35*Iyz2+atom133*atom3728-atom2882*atom95-atom94*atom2879-atom3722*atom168;
atom3875 = -atom168*atom3731-atom94*atom2888-atom1532-atom95*atom2891-atom3288*atom95-atom2599-m5*atom2935-atom3285*atom133-atom3298-m4*atom2935-atom3747-atom2935*m6-atom58*atom2894-atom2902-atom130*atom3282-atom343-atom933-atom565+atom133*atom3737-atom3734*atom171;
atom3876 = atom114*atom888-atom3687*atom1482-atom3688*atom1487+atom114*atom3267+atom115*atom883-atom114*atom3719-atom2876-atom531+atom115*atom3264-atom3688*atom3716-atom3687*atom3713-atom114*atom1492;
atom3877 = -atom152*atom3716-atom1487*atom152-atom153*atom3713-atom1482*atom153-atom893-atom3270;
atom3878 = -atom1492-atom3719;
atom3880 = -atom918-atom552-m6*atom2941-atom3324-atom2918-m5*atom2941-atom3783-atom2604-atom1517-atom3765-atom2910-m4*atom2941-atom3311-Izz3;
atom3881 = -atom3722*atom3687-atom114*atom3728+atom114*atom3276-atom2885+atom115*atom3273-atom3333-atom516-atom3688*atom3725-atom3804;
atom3882 = -atom878-atom152*atom3725-atom3279-atom3807-atom3722*atom153;
atom3883 = -atom1477-atom3728;
atom3885 = atom115*atom3282-atom114*atom3737-atom3333-atom516+atom114*atom3285-atom3688*atom3734-atom2894-atom3687*atom3731-atom3804;
atom3886 = -atom3288-atom152*atom3734-atom878-atom153*atom3731-atom3807;
atom3887 = -atom1477-atom3737;
atom3889 = -atom3817*atom152+atom114*Iyz5+Ixz5*atom115-atom3812*atom153;
atom3839 = Ixz6*atom153+atom152*Iyz6;

MQ_ = [-2*atom168*atom3713-atom130*atom883-2*atom58*atom2876+atom133*atom1492-2*atom59*(mz3*atom2588-atom299*my3)-atom36*(atom36*Ixx2+atom35*Ixy2)-2*atom94*atom2870-atom35*(atom35*Iyy2+atom36*Ixy2)-m6*atom2929-atom58*(atom58*Iyy3+atom59*Ixy3)+2*atom133*atom3719-2*atom95*atom2873-m5*atom2929-2*atom133*atom3267-atom59*(atom59*Ixx3+atom58*Ixy3)-Izz1-atom521*atom94-2*atom3716*atom171-atom58*atom531-2*atom95*atom3270-atom1487*atom171-atom95*atom893-atom526*atom95-m4*atom2929-2*atom130*atom3264-atom168*atom1482-m3*(atom299^2+atom2575^2+atom2576^2)-atom133*atom888-2*(mx3*atom299-mz3*atom2585)*atom58 , atom3874 , atom3875 , atom3876 , atom3877 , atom3878 , atom2576*atom2819-atom94*atom4296+atom2853*atom3213+atom35*((atom2521-atom2533)*atom2450-Ixy2*atom2486+(Izz2*atom2449-da2*Ixz2)*da2-(Ixx2*da2-Ixz2*atom2449)*atom2449+Iyy2*atom2485)-atom95*atom4340+atom36*(atom39*atom55+atom37*atom54)-atom130*atom4334+atom168*atom4181+atom2854*atom3658+atom58*(atom78*atom63+atom61*atom77)+atom4182*atom171-(mx3*(atom2687*atom2574-atom2691)-atom39*atom2666+atom36*atom2669-(atom2694+atom2573*atom2687)*my3-atom2663*atom37-mz3*(atom2683*atom2574-atom2573*atom2684))*atom2575+atom94*atom3202+atom95*atom3643+atom2854*atom4203+atom59*(atom59*atom2741-atom2738*atom62-atom2760*Ixy3-atom2573*(atom2771+atom2770)-Ixx3*atom2757-atom60*atom2735+atom2574*(Iyy3*atom327-Iyz3*atom2574)+(Iyz3*atom327-atom2574*Izz3)*atom327)-atom95*atom4299+atom130*atom3641+atom58*atom3204+(atom24*atom2666-atom2663*atom25-mz3*(atom2574^2+atom2573^2)+my3*atom2574*atom327+atom2573*mx3*atom327)*atom299+atom3203*atom95-(Ixx2*atom2486+(atom2521+atom2522)*atom2449+(Iyz2*atom2450-Iyy2*da2)*atom2450+(atom2450*Izz2-da2*Iyz2)*da2-atom2485*Ixy2)*atom36-atom171*atom4381+atom58*(atom58*atom2741-atom2757*Ixy3-Iyy3*atom2760-atom61*atom2735-(atom2782-atom2770)*atom2574-atom2573*(Ixx3*atom327-Ixz3*atom2573)-atom63*atom2738+(atom2573*Izz3-Ixz3*atom327)*atom327)-(mz5*(atom3235*atom3500-atom3238*atom3497)-atom3460*atom24-(atom3503*atom3235-atom3497*atom3239)*my5+atom3453*atom25+(atom3503*atom3238-atom3500*atom3239)*mx5)*atom2857+atom3214*atom2854-atom58*atom4302-atom168*atom4378+atom35*(atom55*atom40+atom38*atom54)-atom133*atom4183+(atom60*atom77+atom78*atom62)*atom59+atom2857*(atom3037*atom24-(atom3067+atom3063*atom2851)*mx4+(atom3064+atom2848*atom3063)*my4-atom3032*atom25-(atom2848*atom3056+atom3057*atom2851)*mz4)+atom2853*atom3657+atom2853*atom4202-atom133*atom4337-atom2857*((atom3685*atom4039-atom4036*atom3686)*mx6-atom24*atom3990+atom25*atom3981-my6*(atom3682*atom4039-atom3686*atom4033)-(atom3685*atom4033-atom3682*atom4036)*mz6)+atom133*atom3642+atom133*atom4384;
atom3874 , -m4*atom2938-atom918-atom552-m5*atom2938-m3*d3^2-2*atom2604-atom1517-2*atom3765-m6*atom2938-2*atom2910-Izz2-2*atom3311-Izz3 , atom3880 , atom3881 , atom3882 , atom3883 , atom4193+atom3212+atom151*atom452-atom55*atom24+atom189*atom452-(Ixx2*atom2450-Ixy2*atom2449)*atom2449+atom4203*atom2831-atom2450*(Ixy2*atom2450-Iyy2*atom2449)-atom4310-atom4350-atom2832*atom3213+atom2814+atom54*atom25+atom2486*Ixz2-atom4394-atom2832*atom4202-atom2832*atom3657-m3*atom299*g-da2*(atom2533+atom2522)-atom4271-atom2485*Iyz2+atom113*atom452+d3*atom2819+atom3658*atom2831+atom3653+atom3214*atom2831;
atom3875 , atom3880 , -atom918-atom552-2*atom3324-atom2944*m4-2*atom2918-2*atom3783-atom2944*m5-atom1517-atom2944*m6-Izz3 , atom3885 , atom3886 , atom3887 , atom3213*r4+atom4193+atom446*atom113+atom3212+d4*atom4203+d4*atom3658+atom446*atom189+atom446*atom151-atom4310-atom4350+atom2814-atom4394+atom3214*d4-atom4271+atom3653+r4*atom4202+r4*atom3657;
atom3876 , atom3881 , atom3885 , -Izz4+atom115*(-atom114*Ixy5-atom115*Ixx5)-atom114*atom3822-atom3812*atom3687-atom3817*atom3688+atom114*(-atom115*Ixy5-atom114*Iyy5) , atom3889 , -atom3822 , -atom3688*atom4381+atom114*atom4337-atom114*atom3642-atom114*atom4384-atom115*atom3641+atom114*atom4183+atom3688*atom4182+atom115*atom4334-atom4302-atom4378*atom3687+atom3687*atom4181+atom3204;
atom3877 , atom3882 , atom3886 , atom3889 , -Izz5-(atom153*Ixx6+atom152*Ixy6)*atom153-(atom152*Iyy6+atom153*Ixy6)*atom152 , -atom3839 , -atom4378*atom153-atom4340+atom3643+atom153*atom4181+atom152*atom4182-atom152*atom4381;
atom3878 , atom3883 , atom3887 , -atom3822 , -atom3839 , -Izz6 , -atom4384+atom4183];

%endfunction
