/*----------Q.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time_3D_mec.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "Q.h"

#define a1 q[ 0 ]
#define a2 q[ 1 ]
#define a3 q[ 2 ]
#define a4 q[ 3 ]
#define a5 q[ 4 ]
#define a6 q[ 5 ]
#define da1 dq[ 0 ]
#define da2 dq[ 1 ]
#define da3 dq[ 2 ]
#define da4 dq[ 3 ]
#define da5 dq[ 4 ]
#define da6 dq[ 5 ]
#define dda1 ddq[ 0 ]
#define dda2 ddq[ 1 ]
#define dda3 ddq[ 2 ]
#define dda4 ddq[ 3 ]
#define dda5 ddq[ 4 ]
#define dda6 ddq[ 5 ]
#define g param[ 0 ]
#define d3 param[ 1 ]
#define r3 param[ 2 ]
#define d4 param[ 3 ]
#define r4 param[ 4 ]
#define m1 param[ 5 ]
#define mx1 param[ 6 ]
#define my1 param[ 7 ]
#define mz1 param[ 8 ]
#define Ixx1 param[ 9 ]
#define Ixy1 param[ 10 ]
#define Ixz1 param[ 11 ]
#define Iyy1 param[ 12 ]
#define Iyz1 param[ 13 ]
#define Izz1 param[ 14 ]
#define m2 param[ 15 ]
#define mx2 param[ 16 ]
#define my2 param[ 17 ]
#define mz2 param[ 18 ]
#define Ixx2 param[ 19 ]
#define Ixy2 param[ 20 ]
#define Ixz2 param[ 21 ]
#define Iyy2 param[ 22 ]
#define Iyz2 param[ 23 ]
#define Izz2 param[ 24 ]
#define m3 param[ 25 ]
#define mx3 param[ 26 ]
#define my3 param[ 27 ]
#define mz3 param[ 28 ]
#define Ixx3 param[ 29 ]
#define Ixy3 param[ 30 ]
#define Ixz3 param[ 31 ]
#define Iyy3 param[ 32 ]
#define Iyz3 param[ 33 ]
#define Izz3 param[ 34 ]
#define m4 param[ 35 ]
#define mx4 param[ 36 ]
#define my4 param[ 37 ]
#define mz4 param[ 38 ]
#define Ixx4 param[ 39 ]
#define Ixy4 param[ 40 ]
#define Ixz4 param[ 41 ]
#define Iyy4 param[ 42 ]
#define Iyz4 param[ 43 ]
#define Izz4 param[ 44 ]
#define m5 param[ 45 ]
#define mx5 param[ 46 ]
#define my5 param[ 47 ]
#define mz5 param[ 48 ]
#define Ixx5 param[ 49 ]
#define Ixy5 param[ 50 ]
#define Ixz5 param[ 51 ]
#define Iyy5 param[ 52 ]
#define Iyz5 param[ 53 ]
#define Izz5 param[ 54 ]
#define m6 param[ 55 ]
#define mx6 param[ 56 ]
#define my6 param[ 57 ]
#define mz6 param[ 58 ]
#define Ixx6 param[ 59 ]
#define Ixy6 param[ 60 ]
#define Ixz6 param[ 61 ]
#define Iyy6 param[ 62 ]
#define Iyz6 param[ 63 ]
#define Izz6 param[ 64 ]
#define Ma1 param[ 65 ]
#define Ma2 param[ 66 ]
#define Ma3 param[ 67 ]
#define Ma4 param[ 68 ]
#define Ma5 param[ 69 ]
#define Ma6 param[ 70 ]
#define FS001 param[ 71 ]
#define FSa11 param[ 72 ]
#define FSb11 param[ 73 ]
#define FSa21 param[ 74 ]
#define FSb21 param[ 75 ]
#define FSa31 param[ 76 ]
#define FSb31 param[ 77 ]
#define FSa41 param[ 78 ]
#define FSb41 param[ 79 ]
#define FS002 param[ 80 ]
#define FSa12 param[ 81 ]
#define FSb12 param[ 82 ]
#define FSa22 param[ 83 ]
#define FSb22 param[ 84 ]
#define FSa32 param[ 85 ]
#define FSb32 param[ 86 ]
#define FSa42 param[ 87 ]
#define FSb42 param[ 88 ]
#define FS003 param[ 89 ]
#define FSa13 param[ 90 ]
#define FSb13 param[ 91 ]
#define FSa23 param[ 92 ]
#define FSb23 param[ 93 ]
#define FSa33 param[ 94 ]
#define FSb33 param[ 95 ]
#define FSa43 param[ 96 ]
#define FSb43 param[ 97 ]
#define FS004 param[ 98 ]
#define FSa14 param[ 99 ]
#define FSb14 param[ 100 ]
#define FSa24 param[ 101 ]
#define FSb24 param[ 102 ]
#define FSa34 param[ 103 ]
#define FSb34 param[ 104 ]
#define FSa44 param[ 105 ]
#define FSb44 param[ 106 ]
#define FS005 param[ 107 ]
#define FSa15 param[ 108 ]
#define FSb15 param[ 109 ]
#define FSa25 param[ 110 ]
#define FSb25 param[ 111 ]
#define FSa35 param[ 112 ]
#define FSb35 param[ 113 ]
#define FSa45 param[ 114 ]
#define FSb45 param[ 115 ]
#define FS006 param[ 116 ]
#define FSa16 param[ 117 ]
#define FSb16 param[ 118 ]
#define FSa26 param[ 119 ]
#define FSb26 param[ 120 ]
#define FSa36 param[ 121 ]
#define FSb36 param[ 122 ]
#define FSa46 param[ 123 ]
#define FSb46 param[ 124 ]
#define g param[ 125 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
#define lambda6 unknowns[ 5 ]

double atom57;
double atom58;
double atom114;
double atom59;
double atom80;
double atom115;
double atom94;
double atom24;
double atom61;
double atom81;
double atom25;
double atom60;
double atom84;
double atom62;
double atom93;
double atom63;
double atom90;
double atom127;
double atom124;
double atom143;
double atom121;
double atom149;
double atom87;
double atom118;
double atom138;
double atom150;
double atom133;
double atom4337;
double atom130;
double atom4334;
double atom95;
double atom4340;
double atom2574;
double atom2852;
double atom327;
double atom2573;
double atom2848;
double atom3238;
double atom2851;
double atom3389;
double atom2972;
double atom3388;
double atom3576;
double atom3392;
double atom3235;
double atom3583;
double atom2973;
double atom3144;
double atom449;
double atom467;
double atom443;
double atom446;
double atom451;
double atom465;
double atom2995;
double atom35;
double atom299;
double atom452;
double atom458;
double atom36;
double atom300;
double atom453;
double atom450;
double atom301;
double atom456;
double atom459;
double atom2980;
double atom457;
double atom466;
double atom2992;
double atom3109;
double atom2989;
double atom2986;
double atom2983;
double atom3104;
double atom3554;
double atom469;
double atom3110;
double atom148;
double atom3548;
double atom3551;
double atom3239;
double atom3600;
double atom3599;
double atom3641;
double atom3611;
double atom3642;
double atom3643;
double atom2582;
double atom2832;
double atom2579;
double atom2831;
double atom489;
double atom110;
double atom2996;
double atom488;
double atom100;
double atom3005;
double atom2636;
double atom2977;
double atom3037;
double atom2635;
double atom2975;
double atom2997;
double atom105;
double atom3001;
double atom3032;
double atom3063;
double atom3056;
double atom3067;
double atom3057;
double atom3064;
double atom2857;
double atom3011;
double atom3042;
double atom3060;
double atom2853;
double atom3213;
double atom3214;
double atom2854;
double atom2683;
double atom2687;
double atom2694;
double atom2684;
double atom2691;
double atom298;
double atom303;
double atom68;
double atom73;
double atom2669;
double atom76;
double atom302;
double atom305;
double atom2642;
double atom312;
double atom304;
double atom2645;
double atom2663;
double atom37;
double atom2648;
double atom2639;
double atom39;
double atom2666;
double atom2690;
double atom38;
double atom40;
double atom2819;
double atom2449;
double atom2521;
double atom2533;
double atom2450;
double atom2485;
double atom2486;
double atom2522;
double atom2757;
double atom2760;
double atom2732;
double atom2729;
double atom2741;
double atom321;
double atom2738;
double atom2735;
double atom2771;
double atom2770;
double atom2782;
double atom3139;
double atom3119;
double atom3116;
double atom3113;
double atom3172;
double atom3161;
double atom3204;
double atom3160;
double atom3203;
double atom3202;
double atom3494;
double atom3491;
double atom3490;
double atom834;
double atom835;
double atom833;
double atom837;
double atom3399;
double atom3396;
double atom839;
double atom3400;
double atom3404;
double atom3427;
double atom982;
double atom3407;
double atom3403;
double atom3467;
double atom983;
double atom3418;
double atom3460;
double atom3411;
double atom3453;
double atom3658;
double atom1049;
double atom3486;
double atom1060;
double atom3483;
double atom3489;
double atom3657;
double atom847;
double atom3500;
double atom848;
double atom3497;
double atom3503;
double atom153;
double atom152;
double atom3682;
double atom1444;
double atom3686;
double atom4036;
double atom3685;
double atom1447;
double atom4033;
double atom4039;
double atom1421;
double atom1427;
double atom156;
double atom159;
double atom1589;
double atom176;
double atom1581;
double atom1425;
double atom171;
double atom168;
double atom3914;
double atom186;
double atom1422;
double atom1423;
double atom1431;
double atom1434;
double atom3911;
double atom3938;
double atom1428;
double atom3910;
double atom1583;
double atom1592;
double atom1585;
double atom1588;
double atom3917;
double atom3990;
double atom3924;
double atom165;
double atom162;
double atom181;
double atom3907;
double atom3918;
double atom3928;
double atom3921;
double atom3981;
double atom3688;
double atom3687;
double atom4030;
double atom4024;
double atom4027;
double atom3950;
double atom3999;
double atom4203;
double atom1723;
double atom4015;
double atom1729;
double atom4018;
double atom4021;
double atom4202;
double atom4151;
double atom4139;
double atom3900;
double atom4123;
double atom3893;
double atom4114;
double atom4084;
double atom4087;
double atom4090;
double atom4182;
double atom4140;
double atom4181;
double atom4183;
double atom54;
double atom55;
double atom78;
double atom77;
double atom111;
double atom112;
double atom4296;
double atom4299;
double atom4302;
double atom188;
double atom187;
double atom4384;
double atom4381;
double atom4378;
double atom151;
double atom2814;
double atom3212;
double atom3653;
double atom4193;
double atom4271;
double atom113;
double atom4310;
double atom4350;
double atom189;
double atom4394;

double * _Q = NULL;
void Init_Q ( ) 
{
    _Q = malloc ( Q_n_rows * Q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Q_n_rows * Q_n_cols ; i++ ) {_Q[i]=0.0;}
  }
}

void Done_Q ( ) 
{
if (_Q != NULL) 
free (_Q ); 
_Q = NULL; 
}


double * Q ()
{
if ( _Q == NULL )
 {
    _Q = malloc ( Q_n_rows * Q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Q_n_rows * Q_n_cols ; i++ ) {_Q[i]=0.0;}
  }
 }

atom57 =  a3+a2;
atom58 = cos(atom57);
atom114 = cos(a5);
atom59 = sin(atom57);
atom80 = cos(a4);
atom115 = sin(a5);
atom94 = -atom59*atom80;
atom24 = cos(a1);
atom61 = -atom59*atom24;
atom81 = sin(a4);
atom25 = sin(a1);
atom60 = atom58*atom24;
atom84 = -atom81*atom25+atom60*atom80;
atom62 = atom58*atom25;
atom93 = -atom81*atom62+atom24*atom80;
atom63 = -atom59*atom25;
atom90 =  atom80*atom62+atom81*atom24;
atom127 =  atom114*atom63-atom90*atom115;
atom124 =  atom115*atom63+atom114*atom90;
atom143 =  atom127*my5+mx5*atom124+atom93*mz5;
atom121 = -atom84*atom115+atom61*atom114;
atom149 = -g*atom143;
atom87 = -atom81*atom60-atom80*atom25;
atom118 =  atom61*atom115+atom114*atom84;
atom138 =  mz5*atom87+atom121*my5+atom118*mx5;
atom150 = atom138*g;
atom133 = -atom115*atom94-atom58*atom114;
atom4337 =  atom121*atom149+atom150*atom127;
atom130 =  atom114*atom94-atom58*atom115;
atom4334 =  atom150*atom124+atom118*atom149;
atom95 = atom81*atom59;
atom4340 =  atom87*atom149+atom150*atom93;
atom2574 = -atom58*da1;
atom2852 =  da4-atom2574;
atom327 =  da3+da2;
atom2573 = -atom59*da1;
atom2848 =  atom81*atom327+atom2573*atom80;
atom3238 = -atom114*atom2852-atom115*atom2848;
atom2851 =  atom80*atom327-atom81*atom2573;
atom3389 = atom114*atom2851;
atom2972 = atom80*atom2574;
atom3388 = -atom2573*atom115+atom114*atom2972;
atom3576 =  da2*atom3388+da3*atom3388+atom3389*da4+da5*atom3238;
atom3392 = -atom2972*atom115-atom2573*atom114;
atom3235 = -atom2852*atom115+atom114*atom2848;
atom3583 =  da2*atom3392-da4*atom115*atom2851+da3*atom3392-da5*atom3235;
atom2973 = -atom81*atom2574;
atom3144 =  da2*atom2973+da3*atom2973-da4*atom2848;
atom449 =  atom59*d4-atom58*r4;
atom467 = -atom449*da1;
atom443 = -da2+atom327;
atom446 =  atom58*d4+atom59*r4;
atom451 = atom443*atom446;
atom465 = -atom451-atom446*da2;
atom2995 =  atom465*atom25+atom467*atom24;
atom35 = cos(a2);
atom299 = atom35*d3;
atom452 =  atom446+atom299;
atom458 = da1*atom452;
atom36 = sin(a2);
atom300 = -atom36*d3;
atom453 =  atom449-atom300;
atom450 = atom449*atom443;
atom301 = r3*da1;
atom456 = -da2*atom453-atom450;
atom459 = -atom301+atom456;
atom2980 = -atom458*atom25+atom459*atom24;
atom457 =  atom451+da2*atom452;
atom466 = -da1*atom453;
atom2992 = -atom25*atom457+atom24*atom466;
atom3109 =  atom2980*da1+atom2995*da3+da2*atom2992;
atom2989 = -atom467*atom25+atom465*atom24;
atom2986 = -atom25*atom466-atom24*atom457;
atom2983 =  atom459*atom25+atom458*atom24;
atom3104 = -da1*atom2983+da3*atom2989+da2*atom2986;
atom3554 =  atom138*atom3109-atom3104*atom143;
atom469 = -atom449*da2-atom450;
atom3110 = -atom469*da3-atom456*da2;
atom148 =  mz5*atom95+atom133*my5+atom130*mx5;
atom3548 = -atom148*atom3109+atom3110*atom143;
atom3551 = -atom138*atom3110+atom148*atom3104;
atom3239 =  da5+atom2851;
atom3600 = Ixz5*atom3238;
atom3599 = -Ixy5*atom3239;
atom3641 =  ( atom3600+atom3599)*atom3235+atom3548*atom118+atom130*atom3554+atom3551*atom124+Ixx5*atom3576+atom3583*Ixy5-( Iyz5*atom3239-Izz5*atom3238)*atom3239-( Iyy5*atom3239-atom3238*Iyz5)*atom3238+Ixz5*atom3144;
atom3611 = -atom3235*Iyz5;
atom3642 =  atom127*atom3551+( atom3611-atom3599)*atom3238+Ixy5*atom3576+Iyy5*atom3583-( Izz5*atom3235-Ixz5*atom3239)*atom3239+atom133*atom3554+atom3235*( Ixx5*atom3239-Ixz5*atom3235)+atom3548*atom121+atom3144*Iyz5;
atom3643 = -( atom3238*Ixx5-atom3235*Ixy5)*atom3235+atom95*atom3554+Izz5*atom3144+atom3548*atom87+( atom3235*Iyy5-atom3238*Ixy5)*atom3238+Ixz5*atom3576+atom93*atom3551-( atom3611+atom3600)*atom3239+atom3583*Iyz5;
atom2582 = -atom35*atom59+atom58*atom36;
atom2832 =  atom2582*d3-r4;
atom2579 =  atom59*atom36+atom58*atom35;
atom2831 =  atom2579*d3+d4;
atom489 = atom58*da4;
atom110 =  atom94*mx4+atom95*my4+atom58*mz4;
atom2996 = atom489*atom24;
atom488 = atom59*da4;
atom100 =  atom87*my4-atom61*mz4+atom84*mx4;
atom3005 =  atom110*atom2996+atom488*atom100;
atom2636 = atom24*atom327;
atom2977 =  atom488*atom25+atom2636;
atom3037 =  da1*( atom110*atom2977+m4*atom2980)-( atom3005-m4*atom2995)*da3+da2*( m4*atom2992-atom3005);
atom2635 = -atom25*atom327;
atom2975 =  atom488*atom24+atom2635;
atom2997 = atom489*atom25;
atom105 =  atom90*mx4-mz4*atom63+atom93*my4;
atom3001 = -atom110*atom2997-atom488*atom105;
atom3032 = -( m4*atom2983-atom2975*atom110)*da1+( m4*atom2989-atom3001)*da3+da2*( m4*atom2986-atom3001);
atom3063 = -atom2848*atom80+atom81*atom2851;
atom3056 = -atom81*atom2852;
atom3067 = -atom2852*atom3056;
atom3057 = -atom2852*atom80;
atom3064 = atom2852*atom3057;
atom2857 = -atom59*atom2832+atom58*atom2831;
atom3011 = -atom105*atom2996+atom2997*atom100;
atom3042 = -da3*( atom3011+m4*atom469)-( atom3011+atom456*m4)*da2-da1*( atom2977*atom105+atom2975*atom100);
atom3060 =  atom2851*atom80+atom81*atom2848;
atom2853 = -atom58*r3;
atom3213 = -atom59*atom3042+atom3037*atom62+( atom2848*atom3060+atom3067)*my4+mz4*( atom3056*atom2851-atom3057*atom2848)+atom3032*atom60+( atom3064-atom3060*atom2851)*mx4;
atom3214 = -atom58*atom3042+atom3037*atom63+atom61*atom3032+mz4*( (atom2851*atom2851)+(atom2848*atom2848))-atom2852*atom2851*my4-atom2852*atom2848*mx4;
atom2854 = r3*atom59;
atom2683 = atom2582*atom327;
atom2687 = -atom2573*atom2582+atom2579*atom2574;
atom2694 = -atom2683*atom327;
atom2684 = -atom2579*atom327;
atom2691 = atom2684*atom327;
atom298 = da2*d3;
atom303 = -atom298*atom36;
atom68 = -mz3*atom25+atom61*my3+mx3*atom60;
atom73 =  atom63*my3+mx3*atom62+mz3*atom24;
atom2669 = -da1*( atom2635*atom68+atom73*atom2636)-m3*atom303*da2;
atom76 = -atom59*mx3-atom58*my3;
atom302 = da1*atom299;
atom305 = -atom301+atom303;
atom2642 =  atom305*atom25+atom302*atom24;
atom312 = atom300*da1;
atom304 = -atom35*atom298;
atom2645 = -atom312*atom25+atom304*atom24;
atom2663 =  da1*( atom2635*atom76-m3*atom2642)+atom2645*m3*da2;
atom37 = atom35*atom24;
atom2648 =  atom304*atom25+atom312*atom24;
atom2639 = -atom302*atom25+atom305*atom24;
atom39 = atom35*atom25;
atom2666 =  ( atom2636*atom76+m3*atom2639)*da1+m3*da2*atom2648;
atom2690 = -atom2573*atom2579-atom2582*atom2574;
atom38 = -atom36*atom24;
atom40 = -atom36*atom25;
atom2819 =  ( atom2573*atom2690+atom2691)*my3-atom35*atom2669+atom40*atom2666-mz3*( atom2684*atom2574+atom2573*atom2683)-( atom2694+atom2690*atom2574)*mx3+atom38*atom2663;
atom2449 = -atom36*da1;
atom2521 = -da2*Ixy2;
atom2533 = -Iyz2*atom2449;
atom2450 = -atom35*da1;
atom2485 = da2*atom2449;
atom2486 = da2*atom2450;
atom2522 = atom2450*Ixz2;
atom2757 =  da3*atom2574+da2*atom2574;
atom2760 = -atom2573*da2-atom2573*da3;
atom2732 =  atom2639*da1+da2*atom2648;
atom2729 =  atom2645*da2-da1*atom2642;
atom2741 = -atom2729*atom73+atom2732*atom68;
atom321 = -atom303*da2;
atom2738 = -atom321*atom68+atom2729*atom76;
atom2735 = -atom2732*atom76+atom73*atom321;
atom2771 = Ixz3*atom2574;
atom2770 = -Ixy3*atom327;
atom2782 = -atom2573*Iyz3;
atom3139 =  atom2972*da2+atom2972*da3+da4*atom2851;
atom3119 = -atom105*atom3104+atom100*atom3109;
atom3116 = -atom3110*atom100+atom110*atom3104;
atom3113 =  atom3110*atom105-atom110*atom3109;
atom3172 = -atom2848*Iyz4;
atom3161 = Ixz4*atom2851;
atom3204 = -atom61*atom3113-Izz4*atom2760-atom2852*( atom3172+atom3161)+atom3144*Iyz4+( atom2848*Ixy4-Ixx4*atom2851)*atom2848+atom2851*( Iyy4*atom2848-atom2851*Ixy4)+Ixz4*atom3139+atom58*atom3119-atom63*atom3116;
atom3160 = -atom2852*Ixy4;
atom3203 =  atom87*atom3113+atom2852*( Ixz4*atom2852-Izz4*atom2848)+atom3119*atom95-atom2760*Iyz4+atom3139*Ixy4+Iyy4*atom3144+atom2851*( atom3172-atom3160)+atom2848*( atom2852*Ixx4-Ixz4*atom2848)+atom93*atom3116;
atom3202 = -( atom2852*Iyy4-atom2851*Iyz4)*atom2851-atom2852*( atom2852*Iyz4-Izz4*atom2851)+atom3119*atom94+atom84*atom3113-Ixz4*atom2760+atom3144*Ixy4+atom90*atom3116+( atom3161+atom3160)*atom2848+atom3139*Ixx4;
atom3494 = -atom114*atom3235+atom115*atom3238;
atom3491 = -atom115*atom3239;
atom3490 = atom114*atom3239;
atom834 = da5*atom80;
atom835 =  atom834+atom327;
atom833 = -atom81*da5;
atom837 =  atom488+atom58*atom833;
atom3399 =  atom835*atom24+atom837*atom25;
atom3396 =  atom837*atom24-atom835*atom25;
atom839 =  atom489-atom59*atom833;
atom3400 = atom24*atom839;
atom3404 = atom25*atom839;
atom3427 = -atom3400*atom143+atom3404*atom138;
atom982 = -atom58*atom834;
atom3407 =  atom24*atom833+atom982*atom25;
atom3403 = -atom833*atom25+atom24*atom982;
atom3467 = -da3*( atom469*m5+atom3427)-da1*( atom138*atom3396+atom3399*atom143)-( atom456*m5+atom3427)*da2+da4*( atom3403*atom143-atom138*atom3407);
atom983 = atom59*atom834;
atom3418 =  atom837*atom138+atom3400*atom148;
atom3460 =  da1*( atom2980*m5+atom148*atom3399)+da4*( atom138*atom983-atom148*atom3403)+da3*( m5*atom2995-atom3418)-da2*( atom3418-m5*atom2992);
atom3411 = -atom3404*atom148-atom837*atom143;
atom3453 =  da2*( m5*atom2986-atom3411)+da3*( m5*atom2989-atom3411)+da4*( atom148*atom3407-atom983*atom143)-( m5*atom2983-atom3396*atom148)*da1;
atom3658 =  atom61*atom3453+mx5*( atom3491*atom3239-atom3238*atom3494)-atom58*atom3467+atom63*atom3460-mz5*( atom3491*atom3235-atom3238*atom3490)+( atom3235*atom3494-atom3239*atom3490)*my5;
atom1049 = atom114*atom80;
atom3486 = -atom81*atom3235-atom3239*atom1049;
atom1060 = -atom115*atom80;
atom3483 =  atom81*atom3238+atom1060*atom3239;
atom3489 = -atom3235*atom1060+atom3238*atom1049;
atom3657 = -( atom3483*atom3239-atom3235*atom3489)*my5+( atom3483*atom3238-atom3235*atom3486)*mz5-atom59*atom3467-( atom3238*atom3489-atom3486*atom3239)*mx5+atom3460*atom62+atom3453*atom60;
atom847 = atom81*atom114;
atom3500 = -atom847*atom3239+atom3235*atom80;
atom848 = -atom81*atom115;
atom3497 =  atom848*atom3239-atom3238*atom80;
atom3503 = -atom848*atom3235+atom3238*atom847;
atom153 = sin(a6);
atom152 = cos(a6);
atom3682 =  atom153*atom3239+atom3235*atom152;
atom1444 =  atom152*atom847+atom153*atom80;
atom3686 =  da6-atom3238;
atom4036 = -atom1444*atom3686-atom848*atom3682;
atom3685 = -atom3235*atom153+atom152*atom3239;
atom1447 = -atom847*atom153+atom152*atom80;
atom4033 =  atom1447*atom3686+atom3685*atom848;
atom4039 =  atom3685*atom1444-atom3682*atom1447;
atom1421 = da6*atom115;
atom1427 =  atom834+atom81*atom1421;
atom156 =  atom152*atom118+atom87*atom153;
atom159 =  atom87*atom152-atom118*atom153;
atom1589 = atom59*atom1427;
atom176 = -atom121*mz6+atom156*mx6+my6*atom159;
atom1581 = -atom58*atom1427;
atom1425 =  atom1421*atom80+atom833;
atom171 =  atom95*atom152-atom130*atom153;
atom168 =  atom130*atom152+atom95*atom153;
atom3914 =  atom24*atom1581-atom1425*atom25;
atom186 = -atom133*mz6+atom168*mx6+my6*atom171;
atom1422 = atom114*da6;
atom1423 =  atom1422+da4;
atom1431 =  atom58*atom1425+atom59*atom1423;
atom1434 =  atom58*atom1423-atom1425*atom59;
atom3911 = atom1434*atom24;
atom3938 =  atom186*atom3911+atom1431*atom176;
atom1428 =  atom1427+atom327;
atom3910 =  atom1431*atom25+atom24*atom1428;
atom1583 = atom1422*atom80;
atom1592 = -atom59*atom1583-atom58*atom1421;
atom1585 =  atom58*atom1583-atom59*atom1421;
atom1588 = atom81*atom1422;
atom3917 = -atom25*atom1588+atom1585*atom24;
atom3990 = -( atom3938-atom2995*m6)*da3-da4*( atom3914*atom186-atom1589*atom176)+da1*( atom2980*m6+atom186*atom3910)-da2*( atom3938-m6*atom2992)-da5*( atom3917*atom186-atom1592*atom176);
atom3924 =  atom1585*atom25+atom24*atom1588;
atom165 = -atom153*atom124+atom93*atom152;
atom162 =  atom93*atom153+atom152*atom124;
atom181 =  my6*atom165-atom127*mz6+atom162*mx6;
atom3907 =  atom24*atom1431-atom1428*atom25;
atom3918 = atom1434*atom25;
atom3928 = -atom186*atom3918-atom181*atom1431;
atom3921 =  atom1425*atom24+atom1581*atom25;
atom3981 = -da1*( m6*atom2983-atom186*atom3907)+da5*( atom186*atom3924-atom181*atom1592)+da3*( m6*atom2989-atom3928)+da2*( m6*atom2986-atom3928)+da4*( atom3921*atom186-atom181*atom1589);
atom3688 = atom115*atom153;
atom3687 = -atom115*atom152;
atom4030 = -atom3685*atom3687+atom3682*atom3688;
atom4024 = -atom3688*atom3686+atom3685*atom114;
atom4027 =  atom3687*atom3686-atom114*atom3682;
atom3950 = -atom181*atom3911+atom3918*atom176;
atom3999 = -da4*( atom3921*atom176-atom3914*atom181)-da1*( atom181*atom3910+atom3907*atom176)-( atom469*m6+atom3950)*da3-da2*( atom3950+atom456*m6)+( atom3917*atom181-atom3924*atom176)*da5;
atom4203 =  atom61*atom3981+atom63*atom3990+my6*( atom3682*atom4030-atom4024*atom3686)+mz6*( atom3685*atom4024-atom4027*atom3682)-( atom3685*atom4030-atom4027*atom3686)*mx6-atom58*atom3999;
atom1723 = -atom81*atom152-atom153*atom1049;
atom4015 =  atom3685*atom1060+atom1723*atom3686;
atom1729 =  atom152*atom1049-atom81*atom153;
atom4018 = -atom3682*atom1060-atom3686*atom1729;
atom4021 =  atom3685*atom1729-atom3682*atom1723;
atom4202 = -( atom3682*atom4018-atom3685*atom4015)*mz6+atom3990*atom62+my6*( atom3682*atom4021-atom4015*atom3686)-( atom3685*atom4021-atom4018*atom3686)*mx6+atom60*atom3981-atom59*atom3999;
atom4151 = -atom3682*Iyz6;
atom4139 = -atom3686*Ixy6;
atom3900 =  atom152*atom2973-atom3388*atom153;
atom4123 = -( atom3389*atom153+atom152*atom2848)*da4+da2*atom3900-atom3682*da6+da3*atom3900-da5*atom3238*atom153;
atom3893 =  atom152*atom3388+atom2973*atom153;
atom4114 =  da5*atom152*atom3238+da3*atom3893-da4*( atom2848*atom153-atom3389*atom152)+atom3893*da2+atom3685*da6;
atom4084 = -atom186*atom3109+atom3110*atom181;
atom4087 =  atom186*atom3104-atom3110*atom176;
atom4090 =  atom3109*atom176-atom181*atom3104;
atom4182 =  atom4084*atom159-atom3682*( atom3682*Ixz6-atom3686*Ixx6)+atom4123*Iyy6-atom3583*Iyz6+atom4087*atom165-atom3686*( atom3682*Izz6-Ixz6*atom3686)+atom171*atom4090+Ixy6*atom4114+atom3685*( atom4151-atom4139);
atom4140 = atom3685*Ixz6;
atom4181 =  atom4087*atom162+atom168*atom4090+atom3682*( atom4140+atom4139)+atom4084*atom156-Ixz6*atom3583-atom3686*( atom3686*Iyz6-atom3685*Izz6)+atom3685*( atom3685*Iyz6-atom3686*Iyy6)+Ixx6*atom4114+atom4123*Ixy6;
atom4183 =  Ixz6*atom4114-atom3685*( atom3685*Ixy6-atom3682*Iyy6)-Izz6*atom3583+atom4123*Iyz6-atom4084*atom121-atom133*atom4090-( atom4151+atom4140)*atom3686-atom127*atom4087+( atom3682*Ixy6-atom3685*Ixx6)*atom3682;
atom54 = -( atom40*my2+atom24*mz2+atom39*mx2)*g;
atom55 = ( mx2*atom37-atom25*mz2+atom38*my2)*g;
atom78 = g*atom68;
atom77 = -atom73*g;
atom111 = -atom105*g;
atom112 = atom100*g;
atom4296 =  atom90*atom112+atom84*atom111;
atom4299 =  atom93*atom112+atom87*atom111;
atom4302 = -atom63*atom112-atom61*atom111;
atom188 = g*atom176;
atom187 = -atom181*g;
atom4384 = -atom187*atom121-atom188*atom127;
atom4381 =  atom188*atom165+atom187*atom159;
atom4378 =  atom187*atom156+atom188*atom162;
atom151 = -m5*g;
atom2814 =  atom2573*( atom2573*Ixy3-Ixx3*atom2574)+Ixz3*atom2757+( atom2573*Iyy3-Ixy3*atom2574)*atom2574+atom2760*Iyz3-atom2735*atom25-( atom2771+atom2782)*atom327+atom24*atom2738;
atom3212 =  atom3203*atom80+atom81*atom3202;
atom3653 =  atom848*atom3642+atom3641*atom847+atom3643*atom80;
atom4193 =  atom1447*atom4182-atom848*atom4183+atom1444*atom4181;
atom4271 =  atom78*atom24-atom77*atom25;
atom113 = -m4*g;
atom4310 =  atom4299*atom80+atom81*atom4296;
atom4350 =  atom848*atom4337+atom4340*atom80+atom847*atom4334;
atom189 = -m6*g;
atom4394 = -atom848*atom4384+atom1447*atom4381+atom4378*atom1444;

_Q[0] = -atom94*atom4296+atom2853*atom3213+r3*atom36*atom2819+atom35*( ( atom2521-atom2533)*atom2450-Ixy2*atom2486+( Izz2*atom2449-da2*Ixz2)*da2-( Ixx2*da2-Ixz2*atom2449)*atom2449+Iyy2*atom2485)-atom95*atom4340+atom36*( atom39*atom55+atom37*atom54)-atom130*atom4334+atom168*atom4181+atom2854*atom3658+atom58*( atom78*atom63+atom61*atom77)+atom4182*atom171+atom94*atom3202+atom95*atom3643+atom2854*atom4203+atom59*( atom59*atom2741-atom2738*atom62-atom2760*Ixy3-atom2573*( atom2771+atom2770)-Ixx3*atom2757-atom60*atom2735+atom2574*( Iyy3*atom327-Iyz3*atom2574)+( Iyz3*atom327-atom2574*Izz3)*atom327)-atom95*atom4299+atom130*atom3641+atom58*atom3204+( atom24*atom2666-atom2663*atom25-mz3*( (atom2574*atom2574)+(atom2573*atom2573))+my3*atom2574*atom327+atom2573*mx3*atom327)*atom299+atom3203*atom95-( Ixx2*atom2486+( atom2521+atom2522)*atom2449+( Iyz2*atom2450-Iyy2*da2)*atom2450+( atom2450*Izz2-da2*Iyz2)*da2-atom2485*Ixy2)*atom36-atom171*atom4381+atom58*( atom58*atom2741-atom2757*Ixy3-Iyy3*atom2760-atom61*atom2735-( atom2782-atom2770)*atom2574-atom2573*( Ixx3*atom327-Ixz3*atom2573)-atom63*atom2738+( atom2573*Izz3-Ixz3*atom327)*atom327)-( mz5*( atom3235*atom3500-atom3238*atom3497)-atom3460*atom24-( atom3503*atom3235-atom3497*atom3239)*my5+atom3453*atom25+( atom3503*atom3238-atom3500*atom3239)*mx5)*atom2857+atom3214*atom2854-atom58*atom4302-atom168*atom4378+atom35*r3*( mx3*( atom2687*atom2574-atom2691)-atom39*atom2666+atom36*atom2669-( atom2694+atom2573*atom2687)*my3-atom2663*atom37-mz3*( atom2683*atom2574-atom2573*atom2684))+atom35*( atom55*atom40+atom38*atom54)-atom133*atom4183+( atom60*atom77+atom78*atom62)*atom59+atom2857*( atom3037*atom24-( atom3067+atom3063*atom2851)*mx4+( atom3064+atom2848*atom3063)*my4-atom3032*atom25-( atom2848*atom3056+atom3057*atom2851)*mz4)+atom2853*atom3657+atom2853*atom4202-atom133*atom4337-atom2857*( ( atom3685*atom4039-atom4036*atom3686)*mx6-atom24*atom3990+atom25*atom3981-my6*( atom3682*atom4039-atom3686*atom4033)-( atom3685*atom4033-atom3682*atom4036)*mz6)+atom133*atom3642+atom133*atom4384;
_Q[1] =  atom4193+atom3212+atom151*atom452-atom55*atom24+atom189*atom452-( Ixx2*atom2450-Ixy2*atom2449)*atom2449+atom4203*atom2831-atom2450*( Ixy2*atom2450-Iyy2*atom2449)-atom4310-atom4350-atom2832*atom3213+atom2814+atom54*atom25+atom2486*Ixz2-atom4394-atom2832*atom4202-atom2832*atom3657-m3*atom299*g-da2*( atom2533+atom2522)-atom4271-atom2485*Iyz2+atom113*atom452+d3*atom2819+atom3658*atom2831+atom3653+atom3214*atom2831;
_Q[2] =  atom3213*r4+atom4193+atom446*atom113+atom3212+d4*atom4203+d4*atom3658+atom446*atom189+atom446*atom151-atom4310-atom4350+atom2814-atom4394+atom3214*d4-atom4271+atom3653+r4*atom4202+r4*atom3657;
_Q[3] = -atom3688*atom4381+atom114*atom4337-atom114*atom3642-atom114*atom4384-atom115*atom3641+atom114*atom4183+atom3688*atom4182+atom115*atom4334-atom4302-atom4378*atom3687+atom3687*atom4181+atom3204;
_Q[4] = -atom4378*atom153-atom4340+atom3643+atom153*atom4181+atom152*atom4182-atom152*atom4381;
_Q[5] = -atom4384+atom4183;

return _Q;
}
