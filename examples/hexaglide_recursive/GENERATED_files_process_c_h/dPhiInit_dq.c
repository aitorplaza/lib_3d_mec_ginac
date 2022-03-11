/*----------dPhiInit_dq.c lib3D_MEC exported-----------*/

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

#include "dPhiInit_dq.h"

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

double atom40;
double atom38;
double atom468;
double atom37;
double atom466;
double atom2999;
double atom3000;
double atom39;
double atom47;
double atom48;
double atom3002;
double atom3003;
double atom79;
double atom42;
double atom41;
double atom45;
double atom57;
double atom60;
double atom2697;
double atom2698;
double atom44;
double atom502;
double atom498;
double atom3007;
double atom3006;
double atom43;
double atom54;
double atom51;
double atom3010;
double atom3009;
double atom81;
double atom80;
double atom82;
double atom2695;
double atom2694;
double atom46;
double atom512;
double atom516;
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
double atom127;
double atom129;
double atom131;
double atom2741;
double atom130;
double atom128;
double atom3036;
double atom3038;
double atom2734;
double atom2733;
double atom3042;
double atom3041;
double atom3044;
double atom3045;
double atom2730;
double atom2731;
double atom3052;
double atom3051;
double atom3055;
double atom3054;
double atom7;
double atom8;
double atom3059;
double atom3058;
double atom3062;
double atom3061;
double atom168;
double atom170;
double atom2768;
double atom3067;
double atom169;
double atom171;
double atom3065;
double atom2761;
double atom2760;
double atom3071;
double atom3070;
double atom3073;
double atom3074;
double atom2757;
double atom2758;
double atom3080;
double atom3081;
double atom3084;
double atom3083;
double atom208;
double atom210;
double atom2789;
double atom3092;
double atom209;
double atom211;
double atom3090;
double atom250;
double atom248;
double atom2810;
double atom249;
double atom251;
double atom3107;
double atom3109;

double * _dPhiInit_dq = NULL;
void Init_dPhiInit_dq ( ) 
{
    _dPhiInit_dq = malloc ( dPhiInit_dq_n_rows * dPhiInit_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhiInit_dq_n_rows * dPhiInit_dq_n_cols ; i++ ) {_dPhiInit_dq[i]=0.0;}
  }
}

void Done_dPhiInit_dq ( ) 
{
if (_dPhiInit_dq != NULL) 
free (_dPhiInit_dq ); 
_dPhiInit_dq = NULL; 
}


double * dPhiInit_dq ()
{
if ( _dPhiInit_dq == NULL )
 {
    _dPhiInit_dq = malloc ( dPhiInit_dq_n_rows * dPhiInit_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhiInit_dq_n_rows * dPhiInit_dq_n_cols ; i++ ) {_dPhiInit_dq[i]=0.0;}
  }
 }

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
atom57 =  atom37*atom45+atom42*atom38;
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
atom51 =  atom41*atom38+atom37*atom43;
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
atom1 = pow(3.0,(1.0/2.0));
atom0 = -(1.0/2.0)*r;
atom2 = (1.0/2.0)*e*atom1;
atom3 =  atom0+atom2;
atom4 = -(1.0/2.0)*e;
atom5 = -(1.0/2.0)*atom1*r;
atom6 =  atom4+atom5;
atom3029 = atom466*atom3;
atom3030 = atom468*atom6;
atom3033 = -atom47*atom6;
atom3032 = atom48*atom3;
atom127 = cos(b3);
atom129 = cos(a3);
atom131 = (1.0/2.0)*atom1;
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
atom7 =  atom0-atom2;
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

_dPhiInit_dq[0] = 1.0000000000000000e+00;
_dPhiInit_dq[3] = 1.0000000000000000e+00;
_dPhiInit_dq[6] = 1.0000000000000000e+00;
_dPhiInit_dq[9] = 1.0000000000000000e+00;
_dPhiInit_dq[12] = 1.0000000000000000e+00;
_dPhiInit_dq[15] = 1.0000000000000000e+00;
_dPhiInit_dq[19] = 1.0000000000000000e+00;
_dPhiInit_dq[22] = 1.0000000000000000e+00;
_dPhiInit_dq[25] = 1.0000000000000000e+00;
_dPhiInit_dq[28] = 1.0000000000000000e+00;
_dPhiInit_dq[31] = 1.0000000000000000e+00;
_dPhiInit_dq[34] = 1.0000000000000000e+00;
_dPhiInit_dq[38] = 1.0000000000000000e+00;
_dPhiInit_dq[41] = 1.0000000000000000e+00;
_dPhiInit_dq[44] = 1.0000000000000000e+00;
_dPhiInit_dq[47] = 1.0000000000000000e+00;
_dPhiInit_dq[50] = 1.0000000000000000e+00;
_dPhiInit_dq[53] = 1.0000000000000000e+00;
_dPhiInit_dq[55] = -atom2697-atom2698;
_dPhiInit_dq[56] =  atom2695+atom2694;
_dPhiInit_dq[58] = -atom2697+atom2698;
_dPhiInit_dq[59] = -atom2695+atom2694;
_dPhiInit_dq[61] = -atom2734-atom2733;
_dPhiInit_dq[62] =  atom2730+atom2731;
_dPhiInit_dq[64] = -atom2761-atom2760;
_dPhiInit_dq[65] =  atom2757+atom2758;
_dPhiInit_dq[67] =  atom2761-atom2760;
_dPhiInit_dq[68] =  atom2757-atom2758;
_dPhiInit_dq[70] =  atom2734-atom2733;
_dPhiInit_dq[71] =  atom2730-atom2731;
_dPhiInit_dq[72] =  atom2999+atom3000;
_dPhiInit_dq[73] =  atom3007+atom3006;
_dPhiInit_dq[74] =  atom3013+atom3014;
_dPhiInit_dq[75] = -atom2999+atom3000;
_dPhiInit_dq[76] =  atom3007-atom3006;
_dPhiInit_dq[77] =  atom3013-atom3014;
_dPhiInit_dq[78] =  atom3029+atom3030;
_dPhiInit_dq[79] =  atom3042+atom3041;
_dPhiInit_dq[80] =  atom3052+atom3051;
_dPhiInit_dq[81] =  atom3059+atom3058;
_dPhiInit_dq[82] =  atom3071+atom3070;
_dPhiInit_dq[83] =  atom3080+atom3081;
_dPhiInit_dq[84] =  atom3059-atom3058;
_dPhiInit_dq[85] = -atom3071+atom3070;
_dPhiInit_dq[86] = -atom3080+atom3081;
_dPhiInit_dq[87] =  atom3029-atom3030;
_dPhiInit_dq[88] = -atom3042+atom3041;
_dPhiInit_dq[89] =  atom3052-atom3051;
_dPhiInit_dq[90] =  atom3002+atom3003;
_dPhiInit_dq[91] =  atom3010+atom3009;
_dPhiInit_dq[92] =  atom3016+atom3017;
_dPhiInit_dq[93] = -atom3002+atom3003;
_dPhiInit_dq[94] =  atom3010-atom3009;
_dPhiInit_dq[95] =  atom3016-atom3017;
_dPhiInit_dq[96] =  atom3033+atom3032;
_dPhiInit_dq[97] =  atom3044+atom3045;
_dPhiInit_dq[98] =  atom3055+atom3054;
_dPhiInit_dq[99] =  atom3062+atom3061;
_dPhiInit_dq[100] =  atom3073+atom3074;
_dPhiInit_dq[101] =  atom3084+atom3083;
_dPhiInit_dq[102] =  atom3062-atom3061;
_dPhiInit_dq[103] =  atom3073-atom3074;
_dPhiInit_dq[104] =  atom3084-atom3083;
_dPhiInit_dq[105] = -atom3033+atom3032;
_dPhiInit_dq[106] =  atom3044-atom3045;
_dPhiInit_dq[107] =  atom3055-atom3054;
_dPhiInit_dq[109] = -atom79*atom81*L;
_dPhiInit_dq[110] = -atom79*L*atom82;
_dPhiInit_dq[130] = -atom103*atom105*L;
_dPhiInit_dq[131] = -atom103*L*atom106;
_dPhiInit_dq[150] = -atom131*atom2741;
_dPhiInit_dq[151] = -(1.0/2.0)*atom2741;
_dPhiInit_dq[152] = -atom130*atom127*L;
_dPhiInit_dq[171] = -atom131*atom2768;
_dPhiInit_dq[172] = -(1.0/2.0)*atom2768;
_dPhiInit_dq[173] = -atom168*L*atom171;
_dPhiInit_dq[192] = atom131*atom2789;
_dPhiInit_dq[193] = -(1.0/2.0)*atom2789;
_dPhiInit_dq[194] = -atom208*atom211*L;
_dPhiInit_dq[213] = atom131*atom2810;
_dPhiInit_dq[214] = -(1.0/2.0)*atom2810;
_dPhiInit_dq[215] = -atom251*L*atom248;
_dPhiInit_dq[216] = atom79*L;
_dPhiInit_dq[217] = atom80*L*atom82;
_dPhiInit_dq[218] = -atom80*atom81*L;
_dPhiInit_dq[237] = atom103*L;
_dPhiInit_dq[238] = atom104*L*atom106;
_dPhiInit_dq[239] = -atom104*atom105*L;
_dPhiInit_dq[258] =  atom3038/2.0+atom131*atom3036;
_dPhiInit_dq[259] = -atom3038*atom131+atom3036/2.0;
_dPhiInit_dq[260] = -atom128*L*atom129;
_dPhiInit_dq[279] =  atom131*atom3065+atom3067/2.0;
_dPhiInit_dq[280] = -atom131*atom3067+atom3065/2.0;
_dPhiInit_dq[281] = -atom169*atom170*L;
_dPhiInit_dq[300] =  atom3092/2.0-atom131*atom3090;
_dPhiInit_dq[301] =  atom3092*atom131+atom3090/2.0;
_dPhiInit_dq[302] = -atom209*atom210*L;
_dPhiInit_dq[321] =  atom3109/2.0-atom131*atom3107;
_dPhiInit_dq[322] =  atom3107/2.0+atom131*atom3109;
_dPhiInit_dq[323] = -atom249*atom250*L;
_dPhiInit_dq[326] = -1.0000000000000000e+00;
_dPhiInit_dq[347] = -1.0000000000000000e+00;
_dPhiInit_dq[368] = -1.0000000000000000e+00;
_dPhiInit_dq[389] = -1.0000000000000000e+00;
_dPhiInit_dq[410] = -1.0000000000000000e+00;
_dPhiInit_dq[431] = -1.0000000000000000e+00;

return _dPhiInit_dq;
}
