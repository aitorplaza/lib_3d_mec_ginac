/*----------M.c lib3D_MEC exported-----------*/

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

#include "M.h"

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
double atom152;
double atom81;
double atom847;
double atom153;
double atom36;
double atom35;
double atom2582;
double atom2589;
double atom2832;
double atom2579;
double atom2590;
double atom2831;
double atom1447;
double atom2857;
double atom1049;
double atom1723;
double atom2853;
double atom2854;
double atom3688;
double atom3698;
double atom3687;
double atom1729;
double atom1444;
double atom3693;
double atom133;
double atom3719;
double atom848;
double atom1060;
double atom3249;
double atom95;
double atom130;
double atom3716;
double atom171;
double atom168;
double atom3713;
double atom883;
double atom888;
double atom893;
double atom2929;
double atom521;
double atom526;
double atom531;
double atom2860;
double atom2863;
double atom2876;
double atom2870;
double atom2873;
double atom299;
double atom2576;
double atom2575;
double atom2585;
double atom2588;
double atom3244;
double atom3270;
double atom3267;
double atom3264;
double atom1492;
double atom1487;
double atom1482;
double atom3701;
double atom3704;
double atom3728;
double atom3255;
double atom3722;
double atom3725;
double atom3747;
double atom2865;
double atom3252;
double atom3276;
double atom3273;
double atom3279;
double atom3298;
double atom2932;
double atom2599;
double atom343;
double atom2864;
double atom2885;
double atom2882;
double atom2879;
double atom2902;
double atom565;
double atom933;
double atom1532;
double atom2867;
double atom3258;
double atom3285;
double atom3261;
double atom3282;
double atom3288;
double atom2888;
double atom2866;
double atom2891;
double atom2894;
double atom2935;
double atom3710;
double atom3707;
double atom3737;
double atom3734;
double atom3731;
double atom873;
double atom868;
double atom878;
double atom3311;
double atom2938;
double atom2604;
double atom2910;
double atom552;
double atom918;
double atom3765;
double atom1472;
double atom1467;
double atom1477;
double atom1517;
double atom3324;
double atom2918;
double atom2941;
double atom3783;
double atom516;
double atom3333;
double atom3804;
double atom3807;
double atom2944;
double atom3812;
double atom3817;
double atom3822;
double atom3874;
double atom3875;
double atom3876;
double atom3877;
double atom3878;
double atom3880;
double atom3881;
double atom3882;
double atom3883;
double atom3885;
double atom3886;
double atom3887;
double atom3889;
double atom3839;

double * _M = NULL;
void Init_M ( ) 
{
    _M = malloc ( M_n_rows * M_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < M_n_rows * M_n_cols ; i++ ) {_M[i]=0.0;}
  }
}

void Done_M ( ) 
{
if (_M != NULL) 
free (_M ); 
_M = NULL; 
}


double * M ()
{
if ( _M == NULL )
 {
    _M = malloc ( M_n_rows * M_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < M_n_rows * M_n_cols ; i++ ) {_M[i]=0.0;}
  }
 }

atom57 =  a3+a2;
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
atom2579 =  atom59*atom36+atom58*atom35;
atom2590 = atom2579*d3;
atom2831 =  d4+atom2590;
atom1447 = -atom847*atom153+atom152*atom80;
atom2857 = -atom59*atom2832+atom58*atom2831;
atom1049 = atom114*atom80;
atom1723 = -atom81*atom152-atom153*atom1049;
atom2853 = -atom58*r3;
atom2854 = r3*atom59;
atom3688 = atom115*atom153;
atom3698 =  atom1447*atom2857-atom2854*atom3688+atom1723*atom2853;
atom3687 = -atom115*atom152;
atom1729 =  atom152*atom1049-atom81*atom153;
atom1444 =  atom152*atom847+atom153*atom80;
atom3693 = -atom2854*atom3687+atom2857*atom1444+atom2853*atom1729;
atom133 = -atom115*atom94-atom58*atom114;
atom3719 =  atom3698*mx6-my6*atom3693;
atom848 = -atom81*atom115;
atom1060 = -atom115*atom80;
atom3249 =  atom848*atom2857+atom114*atom2854+atom2853*atom1060;
atom95 = atom81*atom59;
atom130 =  atom114*atom94-atom58*atom115;
atom3716 =  atom3249*mx6+mz6*atom3693;
atom171 =  atom95*atom152-atom130*atom153;
atom168 =  atom130*atom152+atom95*atom153;
atom3713 = -mz6*atom3698-my6*atom3249;
atom883 =  Ixz5*atom95+atom130*Ixx5+atom133*Ixy5;
atom888 =  atom95*Iyz5+atom133*Iyy5+atom130*Ixy5;
atom893 =  Izz5*atom95+atom133*Iyz5+atom130*Ixz5;
atom2929 =  (atom2853*atom2853)+(atom2854*atom2854)+(atom2857*atom2857);
atom521 =  atom95*Ixy4+atom58*Ixz4+atom94*Ixx4;
atom526 =  atom95*Iyy4+atom94*Ixy4+atom58*Iyz4;
atom531 =  Ixz4*atom94+atom95*Iyz4+atom58*Izz4;
atom2860 =  atom81*atom2857+atom2853*atom80;
atom2863 = -atom81*atom2853+atom2857*atom80;
atom2876 = -atom2860*my4+mx4*atom2863;
atom2870 = -mz4*atom2863-atom2854*my4;
atom2873 =  mz4*atom2860+atom2854*mx4;
atom299 = atom35*d3;
atom2576 = r3*atom36;
atom2575 = -atom35*r3;
atom2585 =  atom2579*atom2575-atom2582*atom2576;
atom2588 =  atom2579*atom2576+atom2582*atom2575;
atom3244 =  atom2857*atom847+atom115*atom2854+atom2853*atom1049;
atom3270 =  atom3249*mx5-atom3244*my5;
atom3267 = -mx5*atom2863+mz5*atom3244;
atom3264 = -mz5*atom3249+atom2863*my5;
atom1492 = -atom133*Izz6+atom168*Ixz6+atom171*Iyz6;
atom1487 =  atom168*Ixy6+Iyy6*atom171-atom133*Iyz6;
atom1482 = -atom133*Ixz6+atom168*Ixx6+atom171*Ixy6;
atom3701 = -atom2832*atom1729-atom3687*atom2831;
atom3704 = -atom1723*atom2832-atom3688*atom2831;
atom3728 =  mx6*atom3704-my6*atom3701;
atom3255 =  atom114*atom2831-atom2832*atom1060;
atom3722 = -mz6*atom3704-my6*atom3255;
atom3725 =  atom3255*mx6+mz6*atom3701;
atom3747 = -atom848*atom3719+atom1444*atom3713+atom1447*atom3716;
atom2865 = atom81*atom2832;
atom3252 =  atom115*atom2831-atom2832*atom1049;
atom3276 =  mz5*atom3252-atom2865*mx5;
atom3273 =  atom2865*my5-mz5*atom3255;
atom3279 =  atom3255*mx5-atom3252*my5;
atom3298 =  atom848*atom3267+atom847*atom3264+atom3270*atom80;
atom2932 =  atom2854*atom2831-atom2853*atom2832;
atom2599 = -atom2585*my3+mx3*atom2588;
atom343 = -Ixz3*atom59-atom58*Iyz3;
atom2864 = -atom2832*atom80;
atom2885 = -atom2864*my4+atom2865*mx4;
atom2882 =  mx4*atom2831+mz4*atom2864;
atom2879 = -atom2865*mz4-my4*atom2831;
atom2902 =  atom2873*atom80+atom81*atom2870;
atom565 =  atom81*atom521+atom526*atom80;
atom933 =  atom848*atom888+atom883*atom847+atom893*atom80;
atom1532 =  atom1447*atom1487+atom1444*atom1482-atom848*atom1492;
atom2867 = -atom81*r4;
atom3258 =  atom115*d4+r4*atom1049;
atom3285 =  mz5*atom3258-atom2867*mx5;
atom3261 =  atom1060*r4+atom114*d4;
atom3282 =  atom2867*my5-mz5*atom3261;
atom3288 = -atom3258*my5+mx5*atom3261;
atom2888 = -d4*my4-atom2867*mz4;
atom2866 = r4*atom80;
atom2891 =  mz4*atom2866+d4*mx4;
atom2894 =  atom2867*mx4-atom2866*my4;
atom2935 =  atom2853*r4+atom2854*d4;
atom3710 = -atom3688*d4+atom1723*r4;
atom3707 = -d4*atom3687+r4*atom1729;
atom3737 = -my6*atom3707+mx6*atom3710;
atom3734 =  atom3261*mx6+mz6*atom3707;
atom3731 = -mz6*atom3710-my6*atom3261;
atom873 =  atom80*Iyz5+atom847*Ixy5+atom848*Iyy5;
atom868 =  atom848*Ixy5+atom847*Ixx5+Ixz5*atom80;
atom878 =  Izz5*atom80+atom848*Iyz5+Ixz5*atom847;
atom3311 =  atom848*atom3276+atom3273*atom847+atom3279*atom80;
atom2938 =  (atom2831*atom2831)+(atom2832*atom2832);
atom2604 =  mx3*atom2590-atom2589*my3;
atom2910 =  atom81*atom2879+atom2882*atom80;
atom552 =  ( atom81*Ixy4+Iyy4*atom80)*atom80+atom81*( atom81*Ixx4+atom80*Ixy4);
atom918 =  atom878*atom80+atom848*atom873+atom847*atom868;
atom3765 = -atom848*atom3728+atom3722*atom1444+atom1447*atom3725;
atom1472 = -atom848*Iyz6+atom1444*Ixy6+atom1447*Iyy6;
atom1467 =  atom1447*Ixy6-atom848*Ixz6+atom1444*Ixx6;
atom1477 =  atom1447*Iyz6+Ixz6*atom1444-atom848*Izz6;
atom1517 =  atom1467*atom1444-atom848*atom1477+atom1447*atom1472;
atom3324 =  atom3288*atom80+atom848*atom3285+atom3282*atom847;
atom2918 =  atom80*atom2891+atom81*atom2888;
atom2941 =  d4*atom2831-atom2832*r4;
atom3783 = -atom848*atom3737+atom1444*atom3731+atom1447*atom3734;
atom516 =  Iyz4*atom80+atom81*Ixz4;
atom3333 = -atom115*atom868-atom114*atom873;
atom3804 =  atom3688*atom1472+atom114*atom1477+atom1467*atom3687;
atom3807 =  atom1472*atom152+atom1467*atom153;
atom2944 =  (d4*d4)+(r4*r4);
atom3812 =  atom114*Ixz6+atom3687*Ixx6+atom3688*Ixy6;
atom3817 =  atom114*Iyz6+atom3688*Iyy6+atom3687*Ixy6;
atom3822 =  Ixz6*atom3687+atom3688*Iyz6+atom114*Izz6;
atom3874 = -atom130*atom3273-m4*atom2932-atom1532-atom2599+atom36*Ixz2-atom3298-atom3747-atom95*atom3279+atom58*mz3*atom2589-m5*atom2932-atom58*atom2885-atom2902-atom343-mz3*atom59*atom2590-atom933-atom3725*atom171-atom565-m3*atom2576*d3-m6*atom2932-atom133*atom3276+atom35*Iyz2+atom133*atom3728-atom2882*atom95-atom94*atom2879-atom3722*atom168;
atom3875 = -atom168*atom3731-atom94*atom2888-atom1532-atom95*atom2891-atom3288*atom95-atom2599-m5*atom2935-atom3285*atom133-atom3298-m4*atom2935-atom3747-atom2935*m6-atom58*atom2894-atom2902-atom130*atom3282-atom343-atom933-atom565+atom133*atom3737-atom3734*atom171;
atom3876 =  atom114*atom888-atom3687*atom1482-atom3688*atom1487+atom114*atom3267+atom115*atom883-atom114*atom3719-atom2876-atom531+atom115*atom3264-atom3688*atom3716-atom3687*atom3713-atom114*atom1492;
atom3877 = -atom152*atom3716-atom1487*atom152-atom153*atom3713-atom1482*atom153-atom893-atom3270;
atom3878 = -atom1492-atom3719;
atom3880 = -atom918-atom552-m6*atom2941-atom3324-atom2918-m5*atom2941-atom3783-atom2604-atom1517-atom3765-atom2910-m4*atom2941-atom3311-Izz3;
atom3881 = -atom3722*atom3687-atom114*atom3728+atom114*atom3276-atom2885+atom115*atom3273-atom3333-atom516-atom3688*atom3725-atom3804;
atom3882 = -atom878-atom152*atom3725-atom3279-atom3807-atom3722*atom153;
atom3883 = -atom1477-atom3728;
atom3885 =  atom115*atom3282-atom114*atom3737-atom3333-atom516+atom114*atom3285-atom3688*atom3734-atom2894-atom3687*atom3731-atom3804;
atom3886 = -atom3288-atom152*atom3734-atom878-atom153*atom3731-atom3807;
atom3887 = -atom1477-atom3737;
atom3889 = -atom3817*atom152+atom114*Iyz5+Ixz5*atom115-atom3812*atom153;
atom3839 =  Ixz6*atom153+atom152*Iyz6;

_M[0] =  -2.0*atom168*atom3713-atom130*atom883+-2.0*atom58*atom2876+atom133*atom1492+-2.0*atom59*( mz3*atom2588-atom299*my3)-atom36*( atom36*Ixx2+atom35*Ixy2)+-2.0*atom94*atom2870-atom35*( atom35*Iyy2+atom36*Ixy2)-m6*atom2929-atom58*( atom58*Iyy3+atom59*Ixy3)+2.0*atom133*atom3719+-2.0*atom95*atom2873-m5*atom2929+-2.0*atom133*atom3267-atom59*( atom59*Ixx3+atom58*Ixy3)-Izz1-atom521*atom94+-2.0*atom3716*atom171-atom58*atom531+-2.0*atom95*atom3270-atom1487*atom171-atom95*atom893-atom526*atom95-m4*atom2929+-2.0*atom130*atom3264-atom168*atom1482-m3*( (atom299*atom299)+(atom2575*atom2575)+(atom2576*atom2576))-atom133*atom888+-2.0*( mx3*atom299-mz3*atom2585)*atom58;
_M[1] = atom3874;
_M[2] = atom3875;
_M[3] = atom3876;
_M[4] = atom3877;
_M[5] = atom3878;
_M[6] = atom3874;
_M[7] = -m4*atom2938-atom918-atom552-m5*atom2938-m3*(d3*d3)+-2.0*atom2604-atom1517+-2.0*atom3765-m6*atom2938+-2.0*atom2910-Izz2+-2.0*atom3311-Izz3;
_M[8] = atom3880;
_M[9] = atom3881;
_M[10] = atom3882;
_M[11] = atom3883;
_M[12] = atom3875;
_M[13] = atom3880;
_M[14] = -atom918-atom552+-2.0*atom3324-atom2944*m4+-2.0*atom2918+-2.0*atom3783-atom2944*m5-atom1517-atom2944*m6-Izz3;
_M[15] = atom3885;
_M[16] = atom3886;
_M[17] = atom3887;
_M[18] = atom3876;
_M[19] = atom3881;
_M[20] = atom3885;
_M[21] = -Izz4+atom115*(-atom114*Ixy5-atom115*Ixx5)-atom114*atom3822-atom3812*atom3687-atom3817*atom3688+atom114*(-atom115*Ixy5-atom114*Iyy5);
_M[22] = atom3889;
_M[23] = -atom3822;
_M[24] = atom3877;
_M[25] = atom3882;
_M[26] = atom3886;
_M[27] = atom3889;
_M[28] = -Izz5-( atom153*Ixx6+atom152*Ixy6)*atom153-( atom152*Iyy6+atom153*Ixy6)*atom152;
_M[29] = -atom3839;
_M[30] = atom3878;
_M[31] = atom3883;
_M[32] = atom3887;
_M[33] = -atom3822;
_M[34] = -atom3839;
_M[35] = -Izz6;

return _M;
}
