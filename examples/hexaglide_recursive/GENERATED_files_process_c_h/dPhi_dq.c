/*----------dPhi_dq.c lib3D_MEC exported-----------*/

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

#include "dPhi_dq.h"

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

double atom38;
double atom40;
double atom465;
double atom37;
double atom467;
double atom2999;
double atom3000;
double atom39;
double atom47;
double atom48;
double atom3002;
double atom3003;
double atom79;
double atom41;
double atom45;
double atom42;
double atom57;
double atom60;
double atom2697;
double atom2698;
double atom44;
double atom501;
double atom497;
double atom3007;
double atom3006;
double atom43;
double atom54;
double atom51;
double atom3009;
double atom3010;
double atom81;
double atom80;
double atom82;
double atom2694;
double atom2695;
double atom46;
double atom488;
double atom479;
double atom3013;
double atom3014;
double atom3016;
double atom3017;
double atom103;
double atom105;
double atom104;
double atom106;
double atom1;
double atom0;
double atom2;
double atom3;
double atom4;
double atom5;
double atom6;
double atom3029;
double atom3030;
double atom3033;
double atom3032;
double atom129;
double atom127;
double atom2741;
double atom131;
double atom3036;
double atom128;
double atom130;
double atom3038;
double atom2734;
double atom2733;
double atom3042;
double atom3041;
double atom3045;
double atom3044;
double atom2731;
double atom2730;
double atom3052;
double atom3051;
double atom3055;
double atom3054;
double atom8;
double atom7;
double atom3059;
double atom3058;
double atom3062;
double atom3061;
double atom170;
double atom168;
double atom2768;
double atom169;
double atom171;
double atom3067;
double atom3065;
double atom2760;
double atom2761;
double atom3071;
double atom3070;
double atom3074;
double atom3073;
double atom2758;
double atom2757;
double atom3080;
double atom3081;
double atom3084;
double atom3083;
double atom208;
double atom210;
double atom2789;
double atom3092;
double atom211;
double atom209;
double atom3090;
double atom248;
double atom250;
double atom2810;
double atom3107;
double atom251;
double atom249;
double atom3109;

double * _dPhi_dq = NULL;
void Init_dPhi_dq ( ) 
{
    _dPhi_dq = malloc ( dPhi_dq_n_rows * dPhi_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhi_dq_n_rows * dPhi_dq_n_cols ; i++ ) {_dPhi_dq[i]=0.0;}
  }
}

void Done_dPhi_dq ( ) 
{
if (_dPhi_dq != NULL) 
free (_dPhi_dq ); 
_dPhi_dq = NULL; 
}


double * dPhi_dq ()
{
if ( _dPhi_dq == NULL )
 {
    _dPhi_dq = malloc ( dPhi_dq_n_rows * dPhi_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhi_dq_n_rows * dPhi_dq_n_cols ; i++ ) {_dPhi_dq[i]=0.0;}
  }
 }

atom38 = sin(c);
atom40 = sin(b);
atom465 = atom38*atom40;
atom37 = cos(c);
atom467 = -atom40*atom37;
atom2999 = e*atom465;
atom3000 = r*atom467;
atom39 = cos(b);
atom47 = atom39*atom37;
atom48 = -atom38*atom39;
atom3002 = -e*atom47;
atom3003 = r*atom48;
atom79 = cos(b1);
atom41 = cos(a);
atom45 = -atom40*atom41;
atom42 = sin(a);
atom57 =  atom45*atom37+atom42*atom38;
atom60 = -atom38*atom45+atom42*atom37;
atom2697 = r*atom57;
atom2698 = e*atom60;
atom44 = -atom42*atom39;
atom501 = atom38*atom44;
atom497 = -atom37*atom44;
atom3007 = e*atom501;
atom3006 = r*atom497;
atom43 = atom42*atom40;
atom54 =  atom37*atom41-atom38*atom43;
atom51 =  atom38*atom41+atom43*atom37;
atom3009 = r*atom54;
atom3010 = -atom51*e;
atom81 = cos(a1);
atom80 = sin(b1);
atom82 = sin(a1);
atom2694 = r*atom51;
atom2695 = atom54*e;
atom46 = atom39*atom41;
atom488 = -atom46*atom37;
atom479 = atom38*atom46;
atom3013 = r*atom488;
atom3014 = atom479*e;
atom3016 = r*atom60;
atom3017 = -e*atom57;
atom103 = cos(b2);
atom105 = cos(a2);
atom104 = sin(b2);
atom106 = sin(a2);
atom1 = pow(3.0,(1.0/2.0));
atom0 = -(1.0/2.0)*r;
atom2 = (1.0/2.0)*e*atom1;
atom3 =  atom0+atom2;
atom4 = -(1.0/2.0)*r*atom1;
atom5 = -(1.0/2.0)*e;
atom6 =  atom4+atom5;
atom3029 = atom3*atom467;
atom3030 = atom6*atom465;
atom3033 = -atom6*atom47;
atom3032 = atom48*atom3;
atom129 = cos(a3);
atom127 = cos(b3);
atom2741 = -L*atom129*atom127;
atom131 = (1.0/2.0)*atom1;
atom3036 = -L*atom127;
atom128 = sin(b3);
atom130 = sin(a3);
atom3038 = -atom128*L*atom130;
atom2734 = atom6*atom60;
atom2733 = atom3*atom57;
atom3042 = atom497*atom3;
atom3041 = atom6*atom501;
atom3045 = atom3*atom54;
atom3044 = -atom6*atom51;
atom2731 = atom6*atom54;
atom2730 = atom3*atom51;
atom3052 = atom488*atom3;
atom3051 = atom479*atom6;
atom3055 = atom3*atom60;
atom3054 = -atom6*atom57;
atom8 =  atom4-atom5;
atom7 =  atom0-atom2;
atom3059 = atom8*atom465;
atom3058 = atom467*atom7;
atom3062 = -atom8*atom47;
atom3061 = atom48*atom7;
atom170 = cos(a4);
atom168 = cos(b4);
atom2768 = -atom170*L*atom168;
atom169 = sin(b4);
atom171 = sin(a4);
atom3067 = -atom169*L*atom171;
atom3065 = -L*atom168;
atom2760 = atom7*atom57;
atom2761 = atom8*atom60;
atom3071 = atom497*atom7;
atom3070 = atom8*atom501;
atom3074 = atom54*atom7;
atom3073 = -atom8*atom51;
atom2758 = atom8*atom54;
atom2757 = atom51*atom7;
atom3080 = atom488*atom7;
atom3081 = atom8*atom479;
atom3084 = -atom8*atom57;
atom3083 = atom60*atom7;
atom208 = cos(b5);
atom210 = cos(a5);
atom2789 = -L*atom208*atom210;
atom3092 = -L*atom208;
atom211 = sin(a5);
atom209 = sin(b5);
atom3090 = -atom211*L*atom209;
atom248 = cos(b6);
atom250 = cos(a6);
atom2810 = -L*atom248*atom250;
atom3107 = -L*atom248;
atom251 = sin(a6);
atom249 = sin(b6);
atom3109 = -atom251*L*atom249;

_dPhi_dq[0] = 1.0000000000000000e+00;
_dPhi_dq[3] = 1.0000000000000000e+00;
_dPhi_dq[6] = 1.0000000000000000e+00;
_dPhi_dq[9] = 1.0000000000000000e+00;
_dPhi_dq[12] = 1.0000000000000000e+00;
_dPhi_dq[15] = 1.0000000000000000e+00;
_dPhi_dq[19] = 1.0000000000000000e+00;
_dPhi_dq[22] = 1.0000000000000000e+00;
_dPhi_dq[25] = 1.0000000000000000e+00;
_dPhi_dq[28] = 1.0000000000000000e+00;
_dPhi_dq[31] = 1.0000000000000000e+00;
_dPhi_dq[34] = 1.0000000000000000e+00;
_dPhi_dq[38] = 1.0000000000000000e+00;
_dPhi_dq[41] = 1.0000000000000000e+00;
_dPhi_dq[44] = 1.0000000000000000e+00;
_dPhi_dq[47] = 1.0000000000000000e+00;
_dPhi_dq[50] = 1.0000000000000000e+00;
_dPhi_dq[53] = 1.0000000000000000e+00;
_dPhi_dq[55] = -atom2697-atom2698;
_dPhi_dq[56] =  atom2694+atom2695;
_dPhi_dq[58] = -atom2697+atom2698;
_dPhi_dq[59] =  atom2694-atom2695;
_dPhi_dq[61] = -atom2734-atom2733;
_dPhi_dq[62] =  atom2731+atom2730;
_dPhi_dq[64] = -atom2760-atom2761;
_dPhi_dq[65] =  atom2758+atom2757;
_dPhi_dq[67] = -atom2760+atom2761;
_dPhi_dq[68] = -atom2758+atom2757;
_dPhi_dq[70] =  atom2734-atom2733;
_dPhi_dq[71] = -atom2731+atom2730;
_dPhi_dq[72] =  atom2999+atom3000;
_dPhi_dq[73] =  atom3007+atom3006;
_dPhi_dq[74] =  atom3013+atom3014;
_dPhi_dq[75] = -atom2999+atom3000;
_dPhi_dq[76] = -atom3007+atom3006;
_dPhi_dq[77] =  atom3013-atom3014;
_dPhi_dq[78] =  atom3029+atom3030;
_dPhi_dq[79] =  atom3042+atom3041;
_dPhi_dq[80] =  atom3052+atom3051;
_dPhi_dq[81] =  atom3059+atom3058;
_dPhi_dq[82] =  atom3071+atom3070;
_dPhi_dq[83] =  atom3080+atom3081;
_dPhi_dq[84] = -atom3059+atom3058;
_dPhi_dq[85] =  atom3071-atom3070;
_dPhi_dq[86] =  atom3080-atom3081;
_dPhi_dq[87] =  atom3029-atom3030;
_dPhi_dq[88] =  atom3042-atom3041;
_dPhi_dq[89] =  atom3052-atom3051;
_dPhi_dq[90] =  atom3002+atom3003;
_dPhi_dq[91] =  atom3009+atom3010;
_dPhi_dq[92] =  atom3016+atom3017;
_dPhi_dq[93] = -atom3002+atom3003;
_dPhi_dq[94] =  atom3009-atom3010;
_dPhi_dq[95] =  atom3016-atom3017;
_dPhi_dq[96] =  atom3033+atom3032;
_dPhi_dq[97] =  atom3045+atom3044;
_dPhi_dq[98] =  atom3055+atom3054;
_dPhi_dq[99] =  atom3062+atom3061;
_dPhi_dq[100] =  atom3074+atom3073;
_dPhi_dq[101] =  atom3084+atom3083;
_dPhi_dq[102] = -atom3062+atom3061;
_dPhi_dq[103] =  atom3074-atom3073;
_dPhi_dq[104] = -atom3084+atom3083;
_dPhi_dq[105] = -atom3033+atom3032;
_dPhi_dq[106] =  atom3045-atom3044;
_dPhi_dq[107] =  atom3055-atom3054;
_dPhi_dq[109] = -atom81*L*atom79;
_dPhi_dq[110] = -L*atom82*atom79;
_dPhi_dq[130] = -atom105*L*atom103;
_dPhi_dq[131] = -L*atom106*atom103;
_dPhi_dq[150] = -atom2741*atom131;
_dPhi_dq[151] = -(1.0/2.0)*atom2741;
_dPhi_dq[152] = -L*atom130*atom127;
_dPhi_dq[171] = -atom2768*atom131;
_dPhi_dq[172] = -(1.0/2.0)*atom2768;
_dPhi_dq[173] = -L*atom171*atom168;
_dPhi_dq[192] = atom2789*atom131;
_dPhi_dq[193] = -(1.0/2.0)*atom2789;
_dPhi_dq[194] = -atom211*L*atom208;
_dPhi_dq[213] = atom2810*atom131;
_dPhi_dq[214] = -(1.0/2.0)*atom2810;
_dPhi_dq[215] = -atom251*L*atom248;
_dPhi_dq[216] = L*atom79;
_dPhi_dq[217] = atom80*L*atom82;
_dPhi_dq[218] = -atom80*atom81*L;
_dPhi_dq[237] = L*atom103;
_dPhi_dq[238] = atom104*L*atom106;
_dPhi_dq[239] = -atom104*atom105*L;
_dPhi_dq[258] =  atom3038*atom131+atom3036/2.0;
_dPhi_dq[259] =  atom3038/2.0-atom3036*atom131;
_dPhi_dq[260] = -atom128*L*atom129;
_dPhi_dq[279] =  atom3067*atom131+atom3065/2.0;
_dPhi_dq[280] = -atom3065*atom131+atom3067/2.0;
_dPhi_dq[281] = -atom169*atom170*L;
_dPhi_dq[300] =  atom3092/2.0-atom3090*atom131;
_dPhi_dq[301] =  atom3090/2.0+atom3092*atom131;
_dPhi_dq[302] = -L*atom209*atom210;
_dPhi_dq[321] =  atom3107/2.0-atom131*atom3109;
_dPhi_dq[322] =  atom3107*atom131+atom3109/2.0;
_dPhi_dq[323] = -L*atom249*atom250;
_dPhi_dq[326] = -1.0000000000000000e+00;
_dPhi_dq[347] = -1.0000000000000000e+00;
_dPhi_dq[368] = -1.0000000000000000e+00;
_dPhi_dq[389] = -1.0000000000000000e+00;
_dPhi_dq[410] = -1.0000000000000000e+00;
_dPhi_dq[431] = -1.0000000000000000e+00;

return _dPhi_dq;
}
