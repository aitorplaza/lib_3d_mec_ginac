/*----------Phi_q.c lib3D_MEC exported-----------*/

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

#include "Phi_q.h"

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
#define alfa param[ 5 ]
#define mP param[ 6 ]
#define mxP param[ 7 ]
#define myP param[ 8 ]
#define mzP param[ 9 ]
#define IxxP param[ 10 ]
#define IxyP param[ 11 ]
#define IyyP param[ 12 ]
#define IxzP param[ 13 ]
#define IzzP param[ 14 ]
#define IyzP param[ 15 ]
#define m1 param[ 16 ]
#define mx1 param[ 17 ]
#define my1 param[ 18 ]
#define mz1 param[ 19 ]
#define Ixx1 param[ 20 ]
#define Ixy1 param[ 21 ]
#define Iyy1 param[ 22 ]
#define Ixz1 param[ 23 ]
#define Izz1 param[ 24 ]
#define Iyz1 param[ 25 ]
#define m2 param[ 26 ]
#define mx2 param[ 27 ]
#define my2 param[ 28 ]
#define mz2 param[ 29 ]
#define Ixx2 param[ 30 ]
#define Ixy2 param[ 31 ]
#define Iyy2 param[ 32 ]
#define Ixz2 param[ 33 ]
#define Izz2 param[ 34 ]
#define Iyz2 param[ 35 ]
#define m3 param[ 36 ]
#define mx3 param[ 37 ]
#define my3 param[ 38 ]
#define mz3 param[ 39 ]
#define Ixx3 param[ 40 ]
#define Ixy3 param[ 41 ]
#define Iyy3 param[ 42 ]
#define Ixz3 param[ 43 ]
#define Izz3 param[ 44 ]
#define Iyz3 param[ 45 ]
#define m4 param[ 46 ]
#define mx4 param[ 47 ]
#define my4 param[ 48 ]
#define mz4 param[ 49 ]
#define Ixx4 param[ 50 ]
#define Ixy4 param[ 51 ]
#define Iyy4 param[ 52 ]
#define Ixz4 param[ 53 ]
#define Izz4 param[ 54 ]
#define Iyz4 param[ 55 ]
#define m5 param[ 56 ]
#define mx5 param[ 57 ]
#define my5 param[ 58 ]
#define mz5 param[ 59 ]
#define Ixx5 param[ 60 ]
#define Ixy5 param[ 61 ]
#define Iyy5 param[ 62 ]
#define Ixz5 param[ 63 ]
#define Izz5 param[ 64 ]
#define Iyz5 param[ 65 ]
#define m6 param[ 66 ]
#define mx6 param[ 67 ]
#define my6 param[ 68 ]
#define mz6 param[ 69 ]
#define Ixx6 param[ 70 ]
#define Ixy6 param[ 71 ]
#define Iyy6 param[ 72 ]
#define Ixz6 param[ 73 ]
#define Izz6 param[ 74 ]
#define Iyz6 param[ 75 ]
#define Fs1 param[ 76 ]
#define Fs2 param[ 77 ]
#define Fs3 param[ 78 ]
#define Fs4 param[ 79 ]
#define Fs5 param[ 80 ]
#define Fs6 param[ 81 ]
#define FS001 param[ 82 ]
#define FSa11 param[ 83 ]
#define FSb11 param[ 84 ]
#define FSa21 param[ 85 ]
#define FSb21 param[ 86 ]
#define FS002 param[ 87 ]
#define FSa12 param[ 88 ]
#define FSb12 param[ 89 ]
#define FSa22 param[ 90 ]
#define FSb22 param[ 91 ]
#define FS003 param[ 92 ]
#define FSa13 param[ 93 ]
#define FSb13 param[ 94 ]
#define FSa23 param[ 95 ]
#define FSb23 param[ 96 ]
#define FS004 param[ 97 ]
#define FSa14 param[ 98 ]
#define FSb14 param[ 99 ]
#define FSa24 param[ 100 ]
#define FSb24 param[ 101 ]
#define FS005 param[ 102 ]
#define FSa15 param[ 103 ]
#define FSb15 param[ 104 ]
#define FSa25 param[ 105 ]
#define FSb25 param[ 106 ]
#define FS006 param[ 107 ]
#define FSa16 param[ 108 ]
#define FSb16 param[ 109 ]
#define FSa26 param[ 110 ]
#define FSb26 param[ 111 ]
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

double atom42;
double atom40;
double atom296;
double atom39;
double atom295;
double atom3654;
double atom3653;
double atom41;
double atom49;
double atom50;
double atom3657;
double atom3656;
double atom44;
double atom43;
double atom47;
double atom62;
double atom59;
double atom1379;
double atom1378;
double atom46;
double atom3659;
double atom3661;
double atom3660;
double atom3662;
double atom45;
double atom56;
double atom53;
double atom3665;
double atom3664;
double atom1376;
double atom1375;
double atom48;
double atom3667;
double atom3669;
double atom3668;
double atom3670;
double atom3673;
double atom3672;
double atom0;
double atom1;
double atom3;
double atom2;
double atom4;
double atom5;
double atom7;
double atom6;
double atom8;
double atom3681;
double atom3682;
double atom3685;
double atom3684;
double atom1403;
double atom1402;
double atom3688;
double atom3687;
double atom3691;
double atom3690;
double atom1400;
double atom1399;
double atom3694;
double atom3693;
double atom3696;
double atom3697;
double atom9;
double atom10;
double atom3699;
double atom3700;
double atom3703;
double atom3702;
double atom1421;
double atom1422;
double atom3706;
double atom3705;
double atom3709;
double atom3708;
double atom1419;
double atom1418;
double atom3712;
double atom3711;
double atom3715;
double atom3714;

double * _Phi_q = NULL;
void Init_Phi_q ( ) 
{
    _Phi_q = malloc ( Phi_q_n_rows * Phi_q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Phi_q_n_rows * Phi_q_n_cols ; i++ ) {_Phi_q[i]=0.0;}
  }
}

void Done_Phi_q ( ) 
{
if (_Phi_q != NULL) 
free (_Phi_q ); 
_Phi_q = NULL; 
}


double * Phi_q ()
{
if ( _Phi_q == NULL )
 {
    _Phi_q = malloc ( Phi_q_n_rows * Phi_q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Phi_q_n_rows * Phi_q_n_cols ; i++ ) {_Phi_q[i]=0.0;}
  }
 }

atom42 = sin(b);
atom40 = sin(c);
atom296 = atom42*atom40;
atom39 = cos(c);
atom295 = -atom42*atom39;
atom3654 = e*atom296;
atom3653 = atom295*r;
atom41 = cos(b);
atom49 = atom39*atom41;
atom50 = -atom40*atom41;
atom3657 = -atom49*e;
atom3656 = atom50*r;
atom44 = sin(a);
atom43 = cos(a);
atom47 = -atom42*atom43;
atom62 = -atom40*atom47+atom39*atom44;
atom59 =  atom39*atom47+atom44*atom40;
atom1379 = atom62*e;
atom1378 = atom59*r;
atom46 = -atom44*atom41;
atom3659 = atom40*atom46;
atom3661 = -atom39*atom46;
atom3660 = e*atom3659;
atom3662 = atom3661*r;
atom45 = atom42*atom44;
atom56 =  atom43*atom39-atom40*atom45;
atom53 =  atom43*atom40+atom39*atom45;
atom3665 = atom56*r;
atom3664 = -e*atom53;
atom1376 = e*atom56;
atom1375 = r*atom53;
atom48 = atom43*atom41;
atom3667 = atom40*atom48;
atom3669 = -atom39*atom48;
atom3668 = e*atom3667;
atom3670 = atom3669*r;
atom3673 = atom62*r;
atom3672 = -atom59*e;
atom0 = 2.0*alfa;
atom1 = sin(atom0);
atom3 = cos(atom0);
atom2 = -e*atom1;
atom4 = atom3*r;
atom5 =  atom2+atom4;
atom7 = r*atom1;
atom6 = atom3*e;
atom8 =  atom7+atom6;
atom3681 = atom5*atom295;
atom3682 = atom296*atom8;
atom3685 = -atom49*atom8;
atom3684 = atom5*atom50;
atom1403 = atom62*atom8;
atom1402 = atom5*atom59;
atom3688 = atom5*atom3661;
atom3687 = atom3659*atom8;
atom3691 = atom5*atom56;
atom3690 = -atom8*atom53;
atom1400 = atom8*atom56;
atom1399 = atom5*atom53;
atom3694 = atom5*atom3669;
atom3693 = atom8*atom3667;
atom3696 = -atom59*atom8;
atom3697 = atom5*atom62;
atom9 = -atom2+atom4;
atom10 =  atom7-atom6;
atom3699 = atom295*atom9;
atom3700 = atom10*atom296;
atom3703 = -atom10*atom49;
atom3702 = atom50*atom9;
atom1421 = atom59*atom9;
atom1422 = atom10*atom62;
atom3706 = atom3661*atom9;
atom3705 = atom10*atom3659;
atom3709 = atom56*atom9;
atom3708 = -atom10*atom53;
atom1419 = atom10*atom56;
atom1418 = atom9*atom53;
atom3712 = atom10*atom3667;
atom3711 = atom3669*atom9;
atom3715 = -atom10*atom59;
atom3714 = atom62*atom9;

_Phi_q[0] = 1.0000000000000000e+00;
_Phi_q[1] = 0.0000000000000000e+00;
_Phi_q[2] = 0.0000000000000000e+00;
_Phi_q[3] = 1.0000000000000000e+00;
_Phi_q[4] = 0.0000000000000000e+00;
_Phi_q[5] = 0.0000000000000000e+00;
_Phi_q[6] = 1.0000000000000000e+00;
_Phi_q[7] = 0.0000000000000000e+00;
_Phi_q[8] = 0.0000000000000000e+00;
_Phi_q[9] = 1.0000000000000000e+00;
_Phi_q[10] = 0.0000000000000000e+00;
_Phi_q[11] = 0.0000000000000000e+00;
_Phi_q[12] = 1.0000000000000000e+00;
_Phi_q[13] = 0.0000000000000000e+00;
_Phi_q[14] = 0.0000000000000000e+00;
_Phi_q[15] = 1.0000000000000000e+00;
_Phi_q[16] = 0.0000000000000000e+00;
_Phi_q[17] = 0.0000000000000000e+00;
_Phi_q[18] = 0.0000000000000000e+00;
_Phi_q[19] = 1.0000000000000000e+00;
_Phi_q[20] = 0.0000000000000000e+00;
_Phi_q[21] = 0.0000000000000000e+00;
_Phi_q[22] = 1.0000000000000000e+00;
_Phi_q[23] = 0.0000000000000000e+00;
_Phi_q[24] = 0.0000000000000000e+00;
_Phi_q[25] = 1.0000000000000000e+00;
_Phi_q[26] = 0.0000000000000000e+00;
_Phi_q[27] = 0.0000000000000000e+00;
_Phi_q[28] = 1.0000000000000000e+00;
_Phi_q[29] = 0.0000000000000000e+00;
_Phi_q[30] = 0.0000000000000000e+00;
_Phi_q[31] = 1.0000000000000000e+00;
_Phi_q[32] = 0.0000000000000000e+00;
_Phi_q[33] = 0.0000000000000000e+00;
_Phi_q[34] = 1.0000000000000000e+00;
_Phi_q[35] = 0.0000000000000000e+00;
_Phi_q[36] = 0.0000000000000000e+00;
_Phi_q[37] = 0.0000000000000000e+00;
_Phi_q[38] = 1.0000000000000000e+00;
_Phi_q[39] = 0.0000000000000000e+00;
_Phi_q[40] = 0.0000000000000000e+00;
_Phi_q[41] = 1.0000000000000000e+00;
_Phi_q[42] = 0.0000000000000000e+00;
_Phi_q[43] = 0.0000000000000000e+00;
_Phi_q[44] = 1.0000000000000000e+00;
_Phi_q[45] = 0.0000000000000000e+00;
_Phi_q[46] = 0.0000000000000000e+00;
_Phi_q[47] = 1.0000000000000000e+00;
_Phi_q[48] = 0.0000000000000000e+00;
_Phi_q[49] = 0.0000000000000000e+00;
_Phi_q[50] = 1.0000000000000000e+00;
_Phi_q[51] = 0.0000000000000000e+00;
_Phi_q[52] = 0.0000000000000000e+00;
_Phi_q[53] = 1.0000000000000000e+00;
_Phi_q[54] = 0.0000000000000000e+00;
_Phi_q[55] = -atom1379-atom1378;
_Phi_q[56] =  atom1376+atom1375;
_Phi_q[57] = 0.0000000000000000e+00;
_Phi_q[58] =  atom1379-atom1378;
_Phi_q[59] = -atom1376+atom1375;
_Phi_q[60] = 0.0000000000000000e+00;
_Phi_q[61] = -atom1403-atom1402;
_Phi_q[62] =  atom1400+atom1399;
_Phi_q[63] = 0.0000000000000000e+00;
_Phi_q[64] = -atom1421-atom1422;
_Phi_q[65] =  atom1419+atom1418;
_Phi_q[66] = 0.0000000000000000e+00;
_Phi_q[67] = -atom1421+atom1422;
_Phi_q[68] = -atom1419+atom1418;
_Phi_q[69] = 0.0000000000000000e+00;
_Phi_q[70] =  atom1403-atom1402;
_Phi_q[71] = -atom1400+atom1399;
_Phi_q[72] =  atom3654+atom3653;
_Phi_q[73] =  atom3660+atom3662;
_Phi_q[74] =  atom3668+atom3670;
_Phi_q[75] = -atom3654+atom3653;
_Phi_q[76] = -atom3660+atom3662;
_Phi_q[77] = -atom3668+atom3670;
_Phi_q[78] =  atom3681+atom3682;
_Phi_q[79] =  atom3688+atom3687;
_Phi_q[80] =  atom3694+atom3693;
_Phi_q[81] =  atom3699+atom3700;
_Phi_q[82] =  atom3706+atom3705;
_Phi_q[83] =  atom3712+atom3711;
_Phi_q[84] =  atom3699-atom3700;
_Phi_q[85] =  atom3706-atom3705;
_Phi_q[86] = -atom3712+atom3711;
_Phi_q[87] =  atom3681-atom3682;
_Phi_q[88] =  atom3688-atom3687;
_Phi_q[89] =  atom3694-atom3693;
_Phi_q[90] =  atom3657+atom3656;
_Phi_q[91] =  atom3665+atom3664;
_Phi_q[92] =  atom3673+atom3672;
_Phi_q[93] = -atom3657+atom3656;
_Phi_q[94] =  atom3665-atom3664;
_Phi_q[95] =  atom3673-atom3672;
_Phi_q[96] =  atom3685+atom3684;
_Phi_q[97] =  atom3691+atom3690;
_Phi_q[98] =  atom3696+atom3697;
_Phi_q[99] =  atom3703+atom3702;
_Phi_q[100] =  atom3709+atom3708;
_Phi_q[101] =  atom3715+atom3714;
_Phi_q[102] = -atom3703+atom3702;
_Phi_q[103] =  atom3709-atom3708;
_Phi_q[104] = -atom3715+atom3714;
_Phi_q[105] = -atom3685+atom3684;
_Phi_q[106] =  atom3691-atom3690;
_Phi_q[107] = -atom3696+atom3697;
_Phi_q[108] = 0.0000000000000000e+00;
_Phi_q[109] = 0.0000000000000000e+00;
_Phi_q[110] = 0.0000000000000000e+00;
_Phi_q[111] = 0.0000000000000000e+00;
_Phi_q[112] = 0.0000000000000000e+00;
_Phi_q[113] = 0.0000000000000000e+00;
_Phi_q[114] = 0.0000000000000000e+00;
_Phi_q[115] = 0.0000000000000000e+00;
_Phi_q[116] = 0.0000000000000000e+00;
_Phi_q[117] = 0.0000000000000000e+00;
_Phi_q[118] = 0.0000000000000000e+00;
_Phi_q[119] = 0.0000000000000000e+00;
_Phi_q[120] = 0.0000000000000000e+00;
_Phi_q[121] = 0.0000000000000000e+00;
_Phi_q[122] = 0.0000000000000000e+00;
_Phi_q[123] = 0.0000000000000000e+00;
_Phi_q[124] = 0.0000000000000000e+00;
_Phi_q[125] = 0.0000000000000000e+00;
_Phi_q[126] = 0.0000000000000000e+00;
_Phi_q[127] = 0.0000000000000000e+00;
_Phi_q[128] = 0.0000000000000000e+00;
_Phi_q[129] = 0.0000000000000000e+00;
_Phi_q[130] = 0.0000000000000000e+00;
_Phi_q[131] = 0.0000000000000000e+00;
_Phi_q[132] = 0.0000000000000000e+00;
_Phi_q[133] = 0.0000000000000000e+00;
_Phi_q[134] = 0.0000000000000000e+00;
_Phi_q[135] = 0.0000000000000000e+00;
_Phi_q[136] = 0.0000000000000000e+00;
_Phi_q[137] = 0.0000000000000000e+00;
_Phi_q[138] = 0.0000000000000000e+00;
_Phi_q[139] = 0.0000000000000000e+00;
_Phi_q[140] = 0.0000000000000000e+00;
_Phi_q[141] = 0.0000000000000000e+00;
_Phi_q[142] = 0.0000000000000000e+00;
_Phi_q[143] = 0.0000000000000000e+00;
_Phi_q[144] = 0.0000000000000000e+00;
_Phi_q[145] = 0.0000000000000000e+00;
_Phi_q[146] = 0.0000000000000000e+00;
_Phi_q[147] = 0.0000000000000000e+00;
_Phi_q[148] = 0.0000000000000000e+00;
_Phi_q[149] = 0.0000000000000000e+00;
_Phi_q[150] = 0.0000000000000000e+00;
_Phi_q[151] = 0.0000000000000000e+00;
_Phi_q[152] = 0.0000000000000000e+00;
_Phi_q[153] = 0.0000000000000000e+00;
_Phi_q[154] = 0.0000000000000000e+00;
_Phi_q[155] = 0.0000000000000000e+00;
_Phi_q[156] = 0.0000000000000000e+00;
_Phi_q[157] = 0.0000000000000000e+00;
_Phi_q[158] = 0.0000000000000000e+00;
_Phi_q[159] = 0.0000000000000000e+00;
_Phi_q[160] = 0.0000000000000000e+00;
_Phi_q[161] = 0.0000000000000000e+00;
_Phi_q[162] = 0.0000000000000000e+00;
_Phi_q[163] = 0.0000000000000000e+00;
_Phi_q[164] = 0.0000000000000000e+00;
_Phi_q[165] = 0.0000000000000000e+00;
_Phi_q[166] = 0.0000000000000000e+00;
_Phi_q[167] = 0.0000000000000000e+00;
_Phi_q[168] = 0.0000000000000000e+00;
_Phi_q[169] = 0.0000000000000000e+00;
_Phi_q[170] = 0.0000000000000000e+00;
_Phi_q[171] = 0.0000000000000000e+00;
_Phi_q[172] = 0.0000000000000000e+00;
_Phi_q[173] = 0.0000000000000000e+00;
_Phi_q[174] = 0.0000000000000000e+00;
_Phi_q[175] = 0.0000000000000000e+00;
_Phi_q[176] = 0.0000000000000000e+00;
_Phi_q[177] = 0.0000000000000000e+00;
_Phi_q[178] = 0.0000000000000000e+00;
_Phi_q[179] = 0.0000000000000000e+00;
_Phi_q[180] = 0.0000000000000000e+00;
_Phi_q[181] = 0.0000000000000000e+00;
_Phi_q[182] = 0.0000000000000000e+00;
_Phi_q[183] = 0.0000000000000000e+00;
_Phi_q[184] = 0.0000000000000000e+00;
_Phi_q[185] = 0.0000000000000000e+00;
_Phi_q[186] = 0.0000000000000000e+00;
_Phi_q[187] = 0.0000000000000000e+00;
_Phi_q[188] = 0.0000000000000000e+00;
_Phi_q[189] = 0.0000000000000000e+00;
_Phi_q[190] = 0.0000000000000000e+00;
_Phi_q[191] = 0.0000000000000000e+00;
_Phi_q[192] = 0.0000000000000000e+00;
_Phi_q[193] = 0.0000000000000000e+00;
_Phi_q[194] = 0.0000000000000000e+00;
_Phi_q[195] = 0.0000000000000000e+00;
_Phi_q[196] = 0.0000000000000000e+00;
_Phi_q[197] = 0.0000000000000000e+00;
_Phi_q[198] = 0.0000000000000000e+00;
_Phi_q[199] = 0.0000000000000000e+00;
_Phi_q[200] = 0.0000000000000000e+00;
_Phi_q[201] = 0.0000000000000000e+00;
_Phi_q[202] = 0.0000000000000000e+00;
_Phi_q[203] = 0.0000000000000000e+00;
_Phi_q[204] = 0.0000000000000000e+00;
_Phi_q[205] = 0.0000000000000000e+00;
_Phi_q[206] = 0.0000000000000000e+00;
_Phi_q[207] = 0.0000000000000000e+00;
_Phi_q[208] = 0.0000000000000000e+00;
_Phi_q[209] = 0.0000000000000000e+00;
_Phi_q[210] = 0.0000000000000000e+00;
_Phi_q[211] = 0.0000000000000000e+00;
_Phi_q[212] = 0.0000000000000000e+00;
_Phi_q[213] = 0.0000000000000000e+00;
_Phi_q[214] = 0.0000000000000000e+00;
_Phi_q[215] = 0.0000000000000000e+00;
_Phi_q[216] = 0.0000000000000000e+00;
_Phi_q[217] = 0.0000000000000000e+00;
_Phi_q[218] = 0.0000000000000000e+00;
_Phi_q[219] = 0.0000000000000000e+00;
_Phi_q[220] = 0.0000000000000000e+00;
_Phi_q[221] = 0.0000000000000000e+00;
_Phi_q[222] = 0.0000000000000000e+00;
_Phi_q[223] = 0.0000000000000000e+00;
_Phi_q[224] = 0.0000000000000000e+00;
_Phi_q[225] = 0.0000000000000000e+00;
_Phi_q[226] = 0.0000000000000000e+00;
_Phi_q[227] = 0.0000000000000000e+00;
_Phi_q[228] = 0.0000000000000000e+00;
_Phi_q[229] = 0.0000000000000000e+00;
_Phi_q[230] = 0.0000000000000000e+00;
_Phi_q[231] = 0.0000000000000000e+00;
_Phi_q[232] = 0.0000000000000000e+00;
_Phi_q[233] = 0.0000000000000000e+00;
_Phi_q[234] = 0.0000000000000000e+00;
_Phi_q[235] = 0.0000000000000000e+00;
_Phi_q[236] = 0.0000000000000000e+00;
_Phi_q[237] = 0.0000000000000000e+00;
_Phi_q[238] = 0.0000000000000000e+00;
_Phi_q[239] = 0.0000000000000000e+00;
_Phi_q[240] = 0.0000000000000000e+00;
_Phi_q[241] = 0.0000000000000000e+00;
_Phi_q[242] = 0.0000000000000000e+00;
_Phi_q[243] = 0.0000000000000000e+00;
_Phi_q[244] = 0.0000000000000000e+00;
_Phi_q[245] = 0.0000000000000000e+00;
_Phi_q[246] = 0.0000000000000000e+00;
_Phi_q[247] = 0.0000000000000000e+00;
_Phi_q[248] = 0.0000000000000000e+00;
_Phi_q[249] = 0.0000000000000000e+00;
_Phi_q[250] = 0.0000000000000000e+00;
_Phi_q[251] = 0.0000000000000000e+00;
_Phi_q[252] = 0.0000000000000000e+00;
_Phi_q[253] = 0.0000000000000000e+00;
_Phi_q[254] = 0.0000000000000000e+00;
_Phi_q[255] = 0.0000000000000000e+00;
_Phi_q[256] = 0.0000000000000000e+00;
_Phi_q[257] = 0.0000000000000000e+00;
_Phi_q[258] = 0.0000000000000000e+00;
_Phi_q[259] = 0.0000000000000000e+00;
_Phi_q[260] = 0.0000000000000000e+00;
_Phi_q[261] = 0.0000000000000000e+00;
_Phi_q[262] = 0.0000000000000000e+00;
_Phi_q[263] = 0.0000000000000000e+00;
_Phi_q[264] = 0.0000000000000000e+00;
_Phi_q[265] = 0.0000000000000000e+00;
_Phi_q[266] = 0.0000000000000000e+00;
_Phi_q[267] = 0.0000000000000000e+00;
_Phi_q[268] = 0.0000000000000000e+00;
_Phi_q[269] = 0.0000000000000000e+00;
_Phi_q[270] = 0.0000000000000000e+00;
_Phi_q[271] = 0.0000000000000000e+00;
_Phi_q[272] = 0.0000000000000000e+00;
_Phi_q[273] = 0.0000000000000000e+00;
_Phi_q[274] = 0.0000000000000000e+00;
_Phi_q[275] = 0.0000000000000000e+00;
_Phi_q[276] = 0.0000000000000000e+00;
_Phi_q[277] = 0.0000000000000000e+00;
_Phi_q[278] = 0.0000000000000000e+00;
_Phi_q[279] = 0.0000000000000000e+00;
_Phi_q[280] = 0.0000000000000000e+00;
_Phi_q[281] = 0.0000000000000000e+00;
_Phi_q[282] = 0.0000000000000000e+00;
_Phi_q[283] = 0.0000000000000000e+00;
_Phi_q[284] = 0.0000000000000000e+00;
_Phi_q[285] = 0.0000000000000000e+00;
_Phi_q[286] = 0.0000000000000000e+00;
_Phi_q[287] = 0.0000000000000000e+00;
_Phi_q[288] = 0.0000000000000000e+00;
_Phi_q[289] = 0.0000000000000000e+00;
_Phi_q[290] = 0.0000000000000000e+00;
_Phi_q[291] = 0.0000000000000000e+00;
_Phi_q[292] = 0.0000000000000000e+00;
_Phi_q[293] = 0.0000000000000000e+00;
_Phi_q[294] = 0.0000000000000000e+00;
_Phi_q[295] = 0.0000000000000000e+00;
_Phi_q[296] = 0.0000000000000000e+00;
_Phi_q[297] = 0.0000000000000000e+00;
_Phi_q[298] = 0.0000000000000000e+00;
_Phi_q[299] = 0.0000000000000000e+00;
_Phi_q[300] = 0.0000000000000000e+00;
_Phi_q[301] = 0.0000000000000000e+00;
_Phi_q[302] = 0.0000000000000000e+00;
_Phi_q[303] = 0.0000000000000000e+00;
_Phi_q[304] = 0.0000000000000000e+00;
_Phi_q[305] = 0.0000000000000000e+00;
_Phi_q[306] = 0.0000000000000000e+00;
_Phi_q[307] = 0.0000000000000000e+00;
_Phi_q[308] = 0.0000000000000000e+00;
_Phi_q[309] = 0.0000000000000000e+00;
_Phi_q[310] = 0.0000000000000000e+00;
_Phi_q[311] = 0.0000000000000000e+00;
_Phi_q[312] = 0.0000000000000000e+00;
_Phi_q[313] = 0.0000000000000000e+00;
_Phi_q[314] = 0.0000000000000000e+00;
_Phi_q[315] = 0.0000000000000000e+00;
_Phi_q[316] = 0.0000000000000000e+00;
_Phi_q[317] = 0.0000000000000000e+00;
_Phi_q[318] = 0.0000000000000000e+00;
_Phi_q[319] = 0.0000000000000000e+00;
_Phi_q[320] = 0.0000000000000000e+00;
_Phi_q[321] = 0.0000000000000000e+00;
_Phi_q[322] = 0.0000000000000000e+00;
_Phi_q[323] = 0.0000000000000000e+00;
_Phi_q[324] = 0.0000000000000000e+00;
_Phi_q[325] = 0.0000000000000000e+00;
_Phi_q[326] = -1.0000000000000000e+00;
_Phi_q[327] = 0.0000000000000000e+00;
_Phi_q[328] = 0.0000000000000000e+00;
_Phi_q[329] = 0.0000000000000000e+00;
_Phi_q[330] = 0.0000000000000000e+00;
_Phi_q[331] = 0.0000000000000000e+00;
_Phi_q[332] = 0.0000000000000000e+00;
_Phi_q[333] = 0.0000000000000000e+00;
_Phi_q[334] = 0.0000000000000000e+00;
_Phi_q[335] = 0.0000000000000000e+00;
_Phi_q[336] = 0.0000000000000000e+00;
_Phi_q[337] = 0.0000000000000000e+00;
_Phi_q[338] = 0.0000000000000000e+00;
_Phi_q[339] = 0.0000000000000000e+00;
_Phi_q[340] = 0.0000000000000000e+00;
_Phi_q[341] = 0.0000000000000000e+00;
_Phi_q[342] = 0.0000000000000000e+00;
_Phi_q[343] = 0.0000000000000000e+00;
_Phi_q[344] = 0.0000000000000000e+00;
_Phi_q[345] = 0.0000000000000000e+00;
_Phi_q[346] = 0.0000000000000000e+00;
_Phi_q[347] = -1.0000000000000000e+00;
_Phi_q[348] = 0.0000000000000000e+00;
_Phi_q[349] = 0.0000000000000000e+00;
_Phi_q[350] = 0.0000000000000000e+00;
_Phi_q[351] = 0.0000000000000000e+00;
_Phi_q[352] = 0.0000000000000000e+00;
_Phi_q[353] = 0.0000000000000000e+00;
_Phi_q[354] = 0.0000000000000000e+00;
_Phi_q[355] = 0.0000000000000000e+00;
_Phi_q[356] = 0.0000000000000000e+00;
_Phi_q[357] = 0.0000000000000000e+00;
_Phi_q[358] = 0.0000000000000000e+00;
_Phi_q[359] = 0.0000000000000000e+00;
_Phi_q[360] = 0.0000000000000000e+00;
_Phi_q[361] = 0.0000000000000000e+00;
_Phi_q[362] = 0.0000000000000000e+00;
_Phi_q[363] = 0.0000000000000000e+00;
_Phi_q[364] = 0.0000000000000000e+00;
_Phi_q[365] = 0.0000000000000000e+00;
_Phi_q[366] = 0.0000000000000000e+00;
_Phi_q[367] = 0.0000000000000000e+00;
_Phi_q[368] = -1.0000000000000000e+00;
_Phi_q[369] = 0.0000000000000000e+00;
_Phi_q[370] = 0.0000000000000000e+00;
_Phi_q[371] = 0.0000000000000000e+00;
_Phi_q[372] = 0.0000000000000000e+00;
_Phi_q[373] = 0.0000000000000000e+00;
_Phi_q[374] = 0.0000000000000000e+00;
_Phi_q[375] = 0.0000000000000000e+00;
_Phi_q[376] = 0.0000000000000000e+00;
_Phi_q[377] = 0.0000000000000000e+00;
_Phi_q[378] = 0.0000000000000000e+00;
_Phi_q[379] = 0.0000000000000000e+00;
_Phi_q[380] = 0.0000000000000000e+00;
_Phi_q[381] = 0.0000000000000000e+00;
_Phi_q[382] = 0.0000000000000000e+00;
_Phi_q[383] = 0.0000000000000000e+00;
_Phi_q[384] = 0.0000000000000000e+00;
_Phi_q[385] = 0.0000000000000000e+00;
_Phi_q[386] = 0.0000000000000000e+00;
_Phi_q[387] = 0.0000000000000000e+00;
_Phi_q[388] = 0.0000000000000000e+00;
_Phi_q[389] = -1.0000000000000000e+00;
_Phi_q[390] = 0.0000000000000000e+00;
_Phi_q[391] = 0.0000000000000000e+00;
_Phi_q[392] = 0.0000000000000000e+00;
_Phi_q[393] = 0.0000000000000000e+00;
_Phi_q[394] = 0.0000000000000000e+00;
_Phi_q[395] = 0.0000000000000000e+00;
_Phi_q[396] = 0.0000000000000000e+00;
_Phi_q[397] = 0.0000000000000000e+00;
_Phi_q[398] = 0.0000000000000000e+00;
_Phi_q[399] = 0.0000000000000000e+00;
_Phi_q[400] = 0.0000000000000000e+00;
_Phi_q[401] = 0.0000000000000000e+00;
_Phi_q[402] = 0.0000000000000000e+00;
_Phi_q[403] = 0.0000000000000000e+00;
_Phi_q[404] = 0.0000000000000000e+00;
_Phi_q[405] = 0.0000000000000000e+00;
_Phi_q[406] = 0.0000000000000000e+00;
_Phi_q[407] = 0.0000000000000000e+00;
_Phi_q[408] = 0.0000000000000000e+00;
_Phi_q[409] = 0.0000000000000000e+00;
_Phi_q[410] = -1.0000000000000000e+00;
_Phi_q[411] = 0.0000000000000000e+00;
_Phi_q[412] = 0.0000000000000000e+00;
_Phi_q[413] = 0.0000000000000000e+00;
_Phi_q[414] = 0.0000000000000000e+00;
_Phi_q[415] = 0.0000000000000000e+00;
_Phi_q[416] = 0.0000000000000000e+00;
_Phi_q[417] = 0.0000000000000000e+00;
_Phi_q[418] = 0.0000000000000000e+00;
_Phi_q[419] = 0.0000000000000000e+00;
_Phi_q[420] = 0.0000000000000000e+00;
_Phi_q[421] = 0.0000000000000000e+00;
_Phi_q[422] = 0.0000000000000000e+00;
_Phi_q[423] = 0.0000000000000000e+00;
_Phi_q[424] = 0.0000000000000000e+00;
_Phi_q[425] = 0.0000000000000000e+00;
_Phi_q[426] = 0.0000000000000000e+00;
_Phi_q[427] = 0.0000000000000000e+00;
_Phi_q[428] = 0.0000000000000000e+00;
_Phi_q[429] = 0.0000000000000000e+00;
_Phi_q[430] = 0.0000000000000000e+00;
_Phi_q[431] = -1.0000000000000000e+00;

return _Phi_q;
}
