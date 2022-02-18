/*----------Gamma.c lib3D_MEC exported-----------*/

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

#include "Gamma.h"

#define x q[ 0 ]
#define y q[ 1 ]
#define z q[ 2 ]
#define a q[ 3 ]
#define b q[ 4 ]
#define c q[ 5 ]
#define a1 q[ 6 ]
#define a2 q[ 7 ]
#define a3 q[ 8 ]
#define a4 q[ 9 ]
#define a5 q[ 10 ]
#define a6 q[ 11 ]
#define b1 q[ 12 ]
#define b2 q[ 13 ]
#define b3 q[ 14 ]
#define b4 q[ 15 ]
#define b5 q[ 16 ]
#define b6 q[ 17 ]
#define s1 q[ 18 ]
#define s2 q[ 19 ]
#define s3 q[ 20 ]
#define s4 q[ 21 ]
#define s5 q[ 22 ]
#define s6 q[ 23 ]
#define dx dq[ 0 ]
#define dy dq[ 1 ]
#define dz dq[ 2 ]
#define da dq[ 3 ]
#define dB dq[ 4 ]
#define dc dq[ 5 ]
#define da1 dq[ 6 ]
#define da2 dq[ 7 ]
#define da3 dq[ 8 ]
#define da4 dq[ 9 ]
#define da5 dq[ 10 ]
#define da6 dq[ 11 ]
#define dB1 dq[ 12 ]
#define dB2 dq[ 13 ]
#define dB3 dq[ 14 ]
#define dB4 dq[ 15 ]
#define dB5 dq[ 16 ]
#define dB6 dq[ 17 ]
#define ds1 dq[ 18 ]
#define ds2 dq[ 19 ]
#define ds3 dq[ 20 ]
#define ds4 dq[ 21 ]
#define ds5 dq[ 22 ]
#define ds6 dq[ 23 ]
#define ddx ddq[ 0 ]
#define ddy ddq[ 1 ]
#define ddz ddq[ 2 ]
#define dda ddq[ 3 ]
#define ddB ddq[ 4 ]
#define ddc ddq[ 5 ]
#define dda1 ddq[ 6 ]
#define dda2 ddq[ 7 ]
#define dda3 ddq[ 8 ]
#define dda4 ddq[ 9 ]
#define dda5 ddq[ 10 ]
#define dda6 ddq[ 11 ]
#define ddB1 ddq[ 12 ]
#define ddB2 ddq[ 13 ]
#define ddB3 ddq[ 14 ]
#define ddB4 ddq[ 15 ]
#define ddB5 ddq[ 16 ]
#define ddB6 ddq[ 17 ]
#define dds1 ddq[ 18 ]
#define dds2 ddq[ 19 ]
#define dds3 ddq[ 20 ]
#define dds4 ddq[ 21 ]
#define dds5 ddq[ 22 ]
#define dds6 ddq[ 23 ]
#define g param[ 0 ]
#define R param[ 1 ]
#define r param[ 2 ]
#define L param[ 3 ]
#define e param[ 4 ]
#define mP param[ 5 ]
#define mxP param[ 6 ]
#define myP param[ 7 ]
#define mzP param[ 8 ]
#define IxxP param[ 9 ]
#define IxyP param[ 10 ]
#define IyyP param[ 11 ]
#define IxzP param[ 12 ]
#define IzzP param[ 13 ]
#define IyzP param[ 14 ]
#define m1 param[ 15 ]
#define mx1 param[ 16 ]
#define my1 param[ 17 ]
#define mz1 param[ 18 ]
#define Ixx1 param[ 19 ]
#define Ixy1 param[ 20 ]
#define Iyy1 param[ 21 ]
#define Ixz1 param[ 22 ]
#define Izz1 param[ 23 ]
#define Iyz1 param[ 24 ]
#define m2 param[ 25 ]
#define mx2 param[ 26 ]
#define my2 param[ 27 ]
#define mz2 param[ 28 ]
#define Ixx2 param[ 29 ]
#define Ixy2 param[ 30 ]
#define Iyy2 param[ 31 ]
#define Ixz2 param[ 32 ]
#define Izz2 param[ 33 ]
#define Iyz2 param[ 34 ]
#define m3 param[ 35 ]
#define mx3 param[ 36 ]
#define my3 param[ 37 ]
#define mz3 param[ 38 ]
#define Ixx3 param[ 39 ]
#define Ixy3 param[ 40 ]
#define Iyy3 param[ 41 ]
#define Ixz3 param[ 42 ]
#define Izz3 param[ 43 ]
#define Iyz3 param[ 44 ]
#define m4 param[ 45 ]
#define mx4 param[ 46 ]
#define my4 param[ 47 ]
#define mz4 param[ 48 ]
#define Ixx4 param[ 49 ]
#define Ixy4 param[ 50 ]
#define Iyy4 param[ 51 ]
#define Ixz4 param[ 52 ]
#define Izz4 param[ 53 ]
#define Iyz4 param[ 54 ]
#define m5 param[ 55 ]
#define mx5 param[ 56 ]
#define my5 param[ 57 ]
#define mz5 param[ 58 ]
#define Ixx5 param[ 59 ]
#define Ixy5 param[ 60 ]
#define Iyy5 param[ 61 ]
#define Ixz5 param[ 62 ]
#define Izz5 param[ 63 ]
#define Iyz5 param[ 64 ]
#define m6 param[ 65 ]
#define mx6 param[ 66 ]
#define my6 param[ 67 ]
#define mz6 param[ 68 ]
#define Ixx6 param[ 69 ]
#define Ixy6 param[ 70 ]
#define Iyy6 param[ 71 ]
#define Ixz6 param[ 72 ]
#define Izz6 param[ 73 ]
#define Iyz6 param[ 74 ]
#define Fs1 param[ 75 ]
#define Fs2 param[ 76 ]
#define Fs3 param[ 77 ]
#define Fs4 param[ 78 ]
#define Fs5 param[ 79 ]
#define Fs6 param[ 80 ]
#define FS001 param[ 81 ]
#define FSa11 param[ 82 ]
#define FSb11 param[ 83 ]
#define FSa21 param[ 84 ]
#define FSb21 param[ 85 ]
#define FS002 param[ 86 ]
#define FSa12 param[ 87 ]
#define FSb12 param[ 88 ]
#define FSa22 param[ 89 ]
#define FSb22 param[ 90 ]
#define FS003 param[ 91 ]
#define FSa13 param[ 92 ]
#define FSb13 param[ 93 ]
#define FSa23 param[ 94 ]
#define FSb23 param[ 95 ]
#define FS004 param[ 96 ]
#define FSa14 param[ 97 ]
#define FSb14 param[ 98 ]
#define FSa24 param[ 99 ]
#define FSb24 param[ 100 ]
#define FS005 param[ 101 ]
#define FSa15 param[ 102 ]
#define FSb15 param[ 103 ]
#define FSa25 param[ 104 ]
#define FSb25 param[ 105 ]
#define FS006 param[ 106 ]
#define FSa16 param[ 107 ]
#define FSb16 param[ 108 ]
#define FSa26 param[ 109 ]
#define FSb26 param[ 110 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
#define lambda6 unknowns[ 5 ]
#define lambda7 unknowns[ 6 ]
#define lambda8 unknowns[ 7 ]
#define lambda9 unknowns[ 8 ]
#define lambda10 unknowns[ 9 ]
#define lambda11 unknowns[ 10 ]
#define lambda12 unknowns[ 11 ]
#define lambda13 unknowns[ 12 ]
#define lambda14 unknowns[ 13 ]
#define lambda15 unknowns[ 14 ]
#define lambda16 unknowns[ 15 ]
#define lambda17 unknowns[ 16 ]
#define lambda18 unknowns[ 17 ]

double atom80;
double atom38;
double atom40;
double atom465;
double atom37;
double atom467;
double atom3222;
double atom3221;
double atom3223;
double atom39;
double atom48;
double atom47;
double atom2692;
double atom2691;
double atom2693;
double atom42;
double atom44;
double atom501;
double atom497;
double atom3236;
double atom3237;
double atom3238;
double atom43;
double atom49;
double atom52;
double atom3233;
double atom3232;
double atom41;
double atom46;
double atom488;
double atom479;
double atom3013;
double atom3014;
double atom3015;
double atom81;
double atom3019;
double atom82;
double atom79;
double atom2704;
double atom45;
double atom58;
double atom60;
double atom55;
double atom57;
double atom3016;
double atom3017;
double atom3018;
double atom51;
double atom54;
double atom2694;
double atom2695;
double atom2696;
double atom2705;
double atom3012;
double atom3009;
double atom3010;
double atom3011;
double atom2697;
double atom2698;
double atom2699;
double atom3252;
double atom3251;
double atom3253;
double atom3007;
double atom3006;
double atom3008;
double atom3257;
double atom3256;
double atom104;
double atom3269;
double atom2712;
double atom106;
double atom103;
double atom2719;
double atom105;
double atom3028;
double atom3027;
double atom3281;
double atom2713;
double atom3026;
double atom2720;
double atom3025;
double atom3023;
double atom3295;
double atom2714;
double atom3024;
double atom128;
double atom129;
double atom1;
double atom3057;
double atom131;
double atom3318;
double atom130;
double atom127;
double atom2740;
double atom3316;
double atom2739;
double atom4;
double atom5;
double atom6;
double atom0;
double atom2;
double atom3;
double atom3307;
double atom3308;
double atom3309;
double atom2727;
double atom2728;
double atom2729;
double atom3341;
double atom3343;
double atom3328;
double atom3327;
double atom3329;
double atom3055;
double atom3054;
double atom3056;
double atom2731;
double atom2730;
double atom2732;
double atom3052;
double atom3051;
double atom3053;
double atom3332;
double atom3333;
double atom3045;
double atom3044;
double atom3046;
double atom2734;
double atom2733;
double atom2735;
double atom3353;
double atom3352;
double atom3354;
double atom2741;
double atom3038;
double atom3042;
double atom3041;
double atom3043;
double atom3358;
double atom3357;
double atom169;
double atom170;
double atom3086;
double atom3381;
double atom171;
double atom168;
double atom2767;
double atom3383;
double atom2766;
double atom7;
double atom8;
double atom3374;
double atom3373;
double atom3375;
double atom2754;
double atom2755;
double atom2756;
double atom2758;
double atom2757;
double atom2759;
double atom3084;
double atom3083;
double atom3085;
double atom3393;
double atom3394;
double atom3395;
double atom3080;
double atom3081;
double atom3082;
double atom3406;
double atom3408;
double atom3398;
double atom3397;
double atom3423;
double atom3422;
double atom3424;
double atom3419;
double atom3418;
double atom3071;
double atom3070;
double atom3072;
double atom2768;
double atom3067;
double atom2760;
double atom2761;
double atom2762;
double atom3074;
double atom3073;
double atom3075;
double atom211;
double atom208;
double atom2788;
double atom3446;
double atom209;
double atom210;
double atom3103;
double atom3444;
double atom3438;
double atom2781;
double atom2787;
double atom3455;
double atom2782;
double atom3102;
double atom3467;
double atom3465;
double atom3101;
double atom3090;
double atom2789;
double atom3096;
double atom3479;
double atom2783;
double atom3095;
double atom249;
double atom250;
double atom3120;
double atom3501;
double atom251;
double atom248;
double atom2809;
double atom3499;
double atom2802;
double atom3493;
double atom2808;
double atom2803;
double atom3118;
double atom3119;
double atom3522;
double atom3520;
double atom3511;
double atom3534;
double atom3113;
double atom2804;
double atom3112;
double atom2810;
double atom3109;

double * _Gamma = NULL;
void Init_Gamma ( ) 
{
    _Gamma = malloc ( Gamma_n_rows * Gamma_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gamma_n_rows * Gamma_n_cols ; i++ ) {_Gamma[i]=0.0;}
  }
}

void Done_Gamma ( ) 
{
if (_Gamma != NULL) 
free (_Gamma ); 
_Gamma = NULL; 
}


double * Gamma ()
{
if ( _Gamma == NULL )
 {
    _Gamma = malloc ( Gamma_n_rows * Gamma_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gamma_n_rows * Gamma_n_cols ; i++ ) {_Gamma[i]=0.0;}
  }
 }

atom80 = sin(b1);
atom38 = sin(c);
atom40 = sin(b);
atom465 = atom38*atom40;
atom37 = cos(c);
atom467 = -atom40*atom37;
atom3222 = r*atom465;
atom3221 = -e*atom467;
atom3223 =  atom3222+atom3221;
atom39 = cos(b);
atom48 = -atom38*atom39;
atom47 = atom39*atom37;
atom2692 = atom48*e;
atom2691 = r*atom47;
atom2693 =  atom2692+atom2691;
atom42 = sin(a);
atom44 = -atom42*atom39;
atom501 = atom38*atom44;
atom497 = -atom37*atom44;
atom3236 = r*atom501;
atom3237 = -atom497*e;
atom3238 =  atom3236+atom3237;
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
atom3015 =  atom3013+atom3014;
atom81 = cos(a1);
atom3019 = atom80*atom81*L;
atom82 = sin(a1);
atom79 = cos(b1);
atom2704 = L*atom82*atom79;
atom45 = -atom40*atom41;
atom58 = -atom38*atom45;
atom60 =  atom58+atom42*atom37;
atom55 = atom45*atom37;
atom57 =  atom55+atom42*atom38;
atom3016 = r*atom60;
atom3017 = -e*atom57;
atom3018 =  atom3016+atom3017;
atom51 =  atom38*atom41+atom49;
atom54 =  atom37*atom41+atom52;
atom2694 = r*atom51;
atom2695 = atom54*e;
atom2696 =  atom2694+atom2695;
atom2705 = -atom81*L*atom79;
atom3012 = -atom80*L*atom82;
atom3009 = r*atom54;
atom3010 = -atom51*e;
atom3011 =  atom3009+atom3010;
atom2697 = r*atom57;
atom2698 = e*atom60;
atom2699 =  atom2697+atom2698;
atom3252 = -atom488*e;
atom3251 = r*atom479;
atom3253 =  atom3252+atom3251;
atom3007 = e*atom501;
atom3006 = r*atom497;
atom3008 =  atom3007+atom3006;
atom3257 = -atom58*e;
atom3256 = -r*atom55;
atom104 = sin(b2);
atom3269 =  atom3222-atom3221;
atom2712 = -atom2692+atom2691;
atom106 = sin(a2);
atom103 = cos(b2);
atom2719 = L*atom106*atom103;
atom105 = cos(a2);
atom3028 = atom104*atom105*L;
atom3027 =  atom3016-atom3017;
atom3281 =  atom3236-atom3237;
atom2713 =  atom2694-atom2695;
atom3026 =  atom3013-atom3014;
atom2720 = -atom105*L*atom103;
atom3025 = -atom104*L*atom106;
atom3023 = -atom3007+atom3006;
atom3295 = -atom3252+atom3251;
atom2714 =  atom2697-atom2698;
atom3024 =  atom3009-atom3010;
atom128 = sin(b3);
atom129 = cos(a3);
atom1 = pow(3.0,(1.0/2.0));
atom3057 = atom128*L*atom129;
atom131 = (1.0/2.0)*atom1;
atom3318 = atom3057*atom131;
atom130 = sin(a3);
atom127 = cos(b3);
atom2740 = L*atom130*atom127;
atom3316 = atom2740*atom131;
atom2739 = -atom128*L;
atom4 = -(1.0/2.0)*r*atom1;
atom5 = -(1.0/2.0)*e;
atom6 =  atom4+atom5;
atom0 = -(1.0/2.0)*r;
atom2 = (1.0/2.0)*e*atom1;
atom3 =  atom0+atom2;
atom3307 = -atom6*atom467;
atom3308 = atom3*atom465;
atom3309 =  atom3307+atom3308;
atom2727 = atom3*atom47;
atom2728 = atom6*atom48;
atom2729 =  atom2727+atom2728;
atom3341 = (1.0/2.0)*atom2740;
atom3343 = (1.0/2.0)*atom3057;
atom3328 = -atom497*atom6;
atom3327 = atom3*atom501;
atom3329 =  atom3328+atom3327;
atom3055 = atom3*atom60;
atom3054 = -atom6*atom57;
atom3056 =  atom3055+atom3054;
atom2731 = atom6*atom54;
atom2730 = atom3*atom51;
atom2732 =  atom2731+atom2730;
atom3052 = atom488*atom3;
atom3051 = atom479*atom6;
atom3053 =  atom3052+atom3051;
atom3332 = -atom49*atom3;
atom3333 = -atom52*atom6;
atom3045 = atom3*atom54;
atom3044 = -atom6*atom51;
atom3046 =  atom3045+atom3044;
atom2734 = atom6*atom60;
atom2733 = atom3*atom57;
atom2735 =  atom2734+atom2733;
atom3353 = -atom488*atom6;
atom3352 = atom479*atom3;
atom3354 =  atom3353+atom3352;
atom2741 = -L*atom129*atom127;
atom3038 = -atom128*L*atom130;
atom3042 = atom497*atom3;
atom3041 = atom6*atom501;
atom3043 =  atom3042+atom3041;
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
atom7 =  atom0-atom2;
atom8 =  atom4-atom5;
atom3374 = atom465*atom7;
atom3373 = -atom8*atom467;
atom3375 =  atom3374+atom3373;
atom2754 = atom47*atom7;
atom2755 = atom8*atom48;
atom2756 =  atom2754+atom2755;
atom2758 = atom8*atom54;
atom2757 = atom51*atom7;
atom2759 =  atom2758+atom2757;
atom3084 = -atom8*atom57;
atom3083 = atom60*atom7;
atom3085 =  atom3084+atom3083;
atom3393 = atom501*atom7;
atom3394 = -atom8*atom497;
atom3395 =  atom3393+atom3394;
atom3080 = atom488*atom7;
atom3081 = atom8*atom479;
atom3082 =  atom3080+atom3081;
atom3406 = (1.0/2.0)*atom3086;
atom3408 = (1.0/2.0)*atom2767;
atom3398 = -atom8*atom52;
atom3397 = -atom49*atom7;
atom3423 = atom479*atom7;
atom3422 = -atom8*atom488;
atom3424 =  atom3423+atom3422;
atom3419 = -atom8*atom58;
atom3418 = -atom55*atom7;
atom3071 = atom497*atom7;
atom3070 = atom8*atom501;
atom3072 =  atom3071+atom3070;
atom2768 = -atom170*L*atom168;
atom3067 = -atom169*L*atom171;
atom2760 = atom7*atom57;
atom2761 = atom8*atom60;
atom2762 =  atom2760+atom2761;
atom3074 = atom54*atom7;
atom3073 = -atom8*atom51;
atom3075 =  atom3074+atom3073;
atom211 = sin(a5);
atom208 = cos(b5);
atom2788 = atom211*L*atom208;
atom3446 = -atom131*atom2788;
atom209 = sin(b5);
atom210 = cos(a5);
atom3103 = L*atom209*atom210;
atom3444 = -atom3103*atom131;
atom3438 =  atom3374-atom3373;
atom2781 =  atom2754-atom2755;
atom2787 = -L*atom209;
atom3455 =  atom3393-atom3394;
atom2782 = -atom2758+atom2757;
atom3102 = -atom3084+atom3083;
atom3467 = (1.0/2.0)*atom2788;
atom3465 = (1.0/2.0)*atom3103;
atom3101 =  atom3080-atom3081;
atom3090 = -atom211*L*atom209;
atom2789 = -L*atom208*atom210;
atom3096 =  atom3074-atom3073;
atom3479 =  atom3423-atom3422;
atom2783 =  atom2760-atom2761;
atom3095 =  atom3071-atom3070;
atom249 = sin(b6);
atom250 = cos(a6);
atom3120 = L*atom249*atom250;
atom3501 = -atom3120*atom131;
atom251 = sin(a6);
atom248 = cos(b6);
atom2809 = atom251*L*atom248;
atom3499 = -atom2809*atom131;
atom2802 =  atom2727-atom2728;
atom3493 = -atom3307+atom3308;
atom2808 = -L*atom249;
atom2803 = -atom2731+atom2730;
atom3118 =  atom3052-atom3051;
atom3119 =  atom3055-atom3054;
atom3522 = (1.0/2.0)*atom3120;
atom3520 = (1.0/2.0)*atom2809;
atom3511 = -atom3328+atom3327;
atom3534 = -atom3353+atom3352;
atom3113 =  atom3045-atom3044;
atom2804 = -atom2734+atom2733;
atom3112 =  atom3042-atom3041;
atom2810 = -L*atom248*atom250;
atom3109 = -atom251*L*atom249;

_Gamma[0] = -( atom3223*dc-dB*atom2693)*dB+dc*( dc*atom2693-atom3223*dB)+atom80*(dB1*dB1)*L;
_Gamma[1] = -dB*( dc*atom3238+( atom3233+atom3232)*dB-atom3015*da)+( atom2696*da+atom3018*dc+atom3015*dB)*da-dB1*( da1*atom3019+dB1*atom2704)-( da1*atom2704+dB1*atom3019)*da1+( atom3018*da+atom2696*dc-dB*atom3238)*dc;
_Gamma[2] = -dB*( atom3253*dc+da*atom3008+( atom3257+atom3256)*dB)+da1*( dB1*atom3012-da1*atom2705)-( dB*atom3008-atom2699*da+dc*atom3011)*da+dB1*( da1*atom3012-dB1*atom2705)+( atom2699*dc-atom3253*dB-da*atom3011)*dc;
_Gamma[3] =  atom104*(dB2*dB2)*L+( dB*atom2712-dc*atom3269)*dB-dc*( dB*atom3269-dc*atom2712);
_Gamma[4] =  ( atom3027*da-dB*atom3281+atom2713*dc)*dc-da2*( dB2*atom3028+da2*atom2719)+( atom3026*da-dc*atom3281-( atom3233-atom3232)*dB)*dB+( atom3027*dc+atom3026*dB+atom2713*da)*da-( atom3028*da2+dB2*atom2719)*dB2;
_Gamma[5] = -( atom3024*dc+atom3023*dB-da*atom2714)*da+da2*( dB2*atom3025-da2*atom2720)-( atom3295*dB+atom3024*da-dc*atom2714)*dc+dB2*( da2*atom3025-dB2*atom2720)+dB*( dB*( atom3257-atom3256)-atom3295*dc-atom3023*da);
_Gamma[6] =  dB3*( 2.0*da3*atom3318+dB3*( 2.0*atom3316+atom2739))/2.0+dB*( atom2729*dB-atom3309*dc)-dc*( atom3309*dB-atom2729*dc)+da3*( atom3316*da3+dB3*atom3318);
_Gamma[7] =  da3*( da3*atom3341+dB3*atom3343)+dB3*( dB3*( atom3341-atom2739*atom131)+atom3343*da3)+da*( atom3056*dc+atom3053*dB+atom2732*da)+dc*( atom2732*dc-dB*atom3329+atom3056*da)-( dB*( atom3332+atom3333)-atom3053*da+dc*atom3329)*dB;
_Gamma[8] = -dB*( dB*( atom3358+atom3357)+atom3354*dc+da*atom3043)+( dc*atom2735-atom3046*da-atom3354*dB)*dc-da*( atom3046*dc+dB*atom3043-da*atom2735)+dB3*( da3*atom3038-dB3*atom2741)+da3*( dB3*atom3038-da3*atom2741);
_Gamma[9] =  ( atom3383*da4+atom3381*dB4)*da4+dB*( atom2756*dB-atom3375*dc)+( ( 2.0*atom3383+atom2766)*dB4+2.0*da4*atom3381)*dB4/2.0-dc*( atom3375*dB-atom2756*dc);
_Gamma[10] =  dB*( atom3082*da-dB*( atom3398+atom3397)-atom3395*dc)+( atom3406*dB4+atom3408*da4)*da4+( atom3085*da+dc*atom2759-atom3395*dB)*dc+( atom3082*dB+atom3085*dc+da*atom2759)*da+( ( atom3408-atom2766*atom131)*dB4+da4*atom3406)*dB4;
_Gamma[11] = -dB*( dB*( atom3419+atom3418)+dc*atom3424+da*atom3072)-( atom2768*da4-atom3067*dB4)*da4-( atom2768*dB4-atom3067*da4)*dB4-da*( dB*atom3072-atom2762*da+dc*atom3075)-dc*( da*atom3075-atom2762*dc+dB*atom3424);
_Gamma[12] =  dc*( dc*atom2781-dB*atom3438)+da5*( da5*atom3446+dB5*atom3444)+( 2.0*da5*atom3444+( atom2787+2.0*atom3446)*dB5)*dB5/2.0+dB*( atom2781*dB-dc*atom3438);
_Gamma[13] =  dc*( dc*atom2782+atom3102*da-atom3455*dB)-( atom3455*dc-( atom3398-atom3397)*dB-atom3101*da)*dB+( ( atom2787*atom131+atom3467)*dB5+atom3465*da5)*dB5+( da*atom2782+atom3101*dB+atom3102*dc)*da+da5*( da5*atom3467+atom3465*dB5);
_Gamma[14] = -da*( atom3096*dc-atom2783*da+atom3095*dB)-( atom2789*da5-atom3090*dB5)*da5+dB*( ( atom3419-atom3418)*dB-atom3095*da-atom3479*dc)-( atom2789*dB5-da5*atom3090)*dB5-( atom3096*da+atom3479*dB-atom2783*dc)*dc;
_Gamma[15] = -( atom3493*dc-dB*atom2802)*dB+da6*( da6*atom3499+atom3501*dB6)+( dB6*( atom2808+2.0*atom3499)+2.0*da6*atom3501)*dB6/2.0+( dc*atom2802-atom3493*dB)*dc;
_Gamma[16] =  da6*( da6*atom3520+atom3522*dB6)+( dB*atom3118+dc*atom3119+da*atom2803)*da+dc*( dc*atom2803-dB*atom3511+da*atom3119)-dB*( dc*atom3511+( atom3332-atom3333)*dB-da*atom3118)+( ( atom2808*atom131+atom3520)*dB6+da6*atom3522)*dB6;
_Gamma[17] = -( dB*atom3534-dc*atom2804+da*atom3113)*dc+dB6*( da6*atom3109-atom2810*dB6)+dB*( ( atom3358-atom3357)*dB-da*atom3112-dc*atom3534)+da6*( dB6*atom3109-atom2810*da6)-( dc*atom3113+dB*atom3112-da*atom2804)*da;

return _Gamma;
}
