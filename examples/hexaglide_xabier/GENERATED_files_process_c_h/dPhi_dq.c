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

_dPhi_dq[0] = 1.0000000000000000e+00;
_dPhi_dq[1] = 0.0000000000000000e+00;
_dPhi_dq[2] = 0.0000000000000000e+00;
_dPhi_dq[3] = 1.0000000000000000e+00;
_dPhi_dq[4] = 0.0000000000000000e+00;
_dPhi_dq[5] = 0.0000000000000000e+00;
_dPhi_dq[6] = 1.0000000000000000e+00;
_dPhi_dq[7] = 0.0000000000000000e+00;
_dPhi_dq[8] = 0.0000000000000000e+00;
_dPhi_dq[9] = 1.0000000000000000e+00;
_dPhi_dq[10] = 0.0000000000000000e+00;
_dPhi_dq[11] = 0.0000000000000000e+00;
_dPhi_dq[12] = 1.0000000000000000e+00;
_dPhi_dq[13] = 0.0000000000000000e+00;
_dPhi_dq[14] = 0.0000000000000000e+00;
_dPhi_dq[15] = 1.0000000000000000e+00;
_dPhi_dq[16] = 0.0000000000000000e+00;
_dPhi_dq[17] = 0.0000000000000000e+00;
_dPhi_dq[18] = 0.0000000000000000e+00;
_dPhi_dq[19] = 1.0000000000000000e+00;
_dPhi_dq[20] = 0.0000000000000000e+00;
_dPhi_dq[21] = 0.0000000000000000e+00;
_dPhi_dq[22] = 1.0000000000000000e+00;
_dPhi_dq[23] = 0.0000000000000000e+00;
_dPhi_dq[24] = 0.0000000000000000e+00;
_dPhi_dq[25] = 1.0000000000000000e+00;
_dPhi_dq[26] = 0.0000000000000000e+00;
_dPhi_dq[27] = 0.0000000000000000e+00;
_dPhi_dq[28] = 1.0000000000000000e+00;
_dPhi_dq[29] = 0.0000000000000000e+00;
_dPhi_dq[30] = 0.0000000000000000e+00;
_dPhi_dq[31] = 1.0000000000000000e+00;
_dPhi_dq[32] = 0.0000000000000000e+00;
_dPhi_dq[33] = 0.0000000000000000e+00;
_dPhi_dq[34] = 1.0000000000000000e+00;
_dPhi_dq[35] = 0.0000000000000000e+00;
_dPhi_dq[36] = 0.0000000000000000e+00;
_dPhi_dq[37] = 0.0000000000000000e+00;
_dPhi_dq[38] = 1.0000000000000000e+00;
_dPhi_dq[39] = 0.0000000000000000e+00;
_dPhi_dq[40] = 0.0000000000000000e+00;
_dPhi_dq[41] = 1.0000000000000000e+00;
_dPhi_dq[42] = 0.0000000000000000e+00;
_dPhi_dq[43] = 0.0000000000000000e+00;
_dPhi_dq[44] = 1.0000000000000000e+00;
_dPhi_dq[45] = 0.0000000000000000e+00;
_dPhi_dq[46] = 0.0000000000000000e+00;
_dPhi_dq[47] = 1.0000000000000000e+00;
_dPhi_dq[48] = 0.0000000000000000e+00;
_dPhi_dq[49] = 0.0000000000000000e+00;
_dPhi_dq[50] = 1.0000000000000000e+00;
_dPhi_dq[51] = 0.0000000000000000e+00;
_dPhi_dq[52] = 0.0000000000000000e+00;
_dPhi_dq[53] = 1.0000000000000000e+00;
_dPhi_dq[54] = 0.0000000000000000e+00;
_dPhi_dq[55] = -atom1379-atom1378;
_dPhi_dq[56] =  atom1376+atom1375;
_dPhi_dq[57] = 0.0000000000000000e+00;
_dPhi_dq[58] =  atom1379-atom1378;
_dPhi_dq[59] = -atom1376+atom1375;
_dPhi_dq[60] = 0.0000000000000000e+00;
_dPhi_dq[61] = -atom1403-atom1402;
_dPhi_dq[62] =  atom1400+atom1399;
_dPhi_dq[63] = 0.0000000000000000e+00;
_dPhi_dq[64] = -atom1421-atom1422;
_dPhi_dq[65] =  atom1419+atom1418;
_dPhi_dq[66] = 0.0000000000000000e+00;
_dPhi_dq[67] = -atom1421+atom1422;
_dPhi_dq[68] = -atom1419+atom1418;
_dPhi_dq[69] = 0.0000000000000000e+00;
_dPhi_dq[70] =  atom1403-atom1402;
_dPhi_dq[71] = -atom1400+atom1399;
_dPhi_dq[72] =  atom3654+atom3653;
_dPhi_dq[73] =  atom3660+atom3662;
_dPhi_dq[74] =  atom3668+atom3670;
_dPhi_dq[75] = -atom3654+atom3653;
_dPhi_dq[76] = -atom3660+atom3662;
_dPhi_dq[77] = -atom3668+atom3670;
_dPhi_dq[78] =  atom3681+atom3682;
_dPhi_dq[79] =  atom3688+atom3687;
_dPhi_dq[80] =  atom3694+atom3693;
_dPhi_dq[81] =  atom3699+atom3700;
_dPhi_dq[82] =  atom3706+atom3705;
_dPhi_dq[83] =  atom3712+atom3711;
_dPhi_dq[84] =  atom3699-atom3700;
_dPhi_dq[85] =  atom3706-atom3705;
_dPhi_dq[86] = -atom3712+atom3711;
_dPhi_dq[87] =  atom3681-atom3682;
_dPhi_dq[88] =  atom3688-atom3687;
_dPhi_dq[89] =  atom3694-atom3693;
_dPhi_dq[90] =  atom3657+atom3656;
_dPhi_dq[91] =  atom3665+atom3664;
_dPhi_dq[92] =  atom3673+atom3672;
_dPhi_dq[93] = -atom3657+atom3656;
_dPhi_dq[94] =  atom3665-atom3664;
_dPhi_dq[95] =  atom3673-atom3672;
_dPhi_dq[96] =  atom3685+atom3684;
_dPhi_dq[97] =  atom3691+atom3690;
_dPhi_dq[98] =  atom3696+atom3697;
_dPhi_dq[99] =  atom3703+atom3702;
_dPhi_dq[100] =  atom3709+atom3708;
_dPhi_dq[101] =  atom3715+atom3714;
_dPhi_dq[102] = -atom3703+atom3702;
_dPhi_dq[103] =  atom3709-atom3708;
_dPhi_dq[104] = -atom3715+atom3714;
_dPhi_dq[105] = -atom3685+atom3684;
_dPhi_dq[106] =  atom3691-atom3690;
_dPhi_dq[107] = -atom3696+atom3697;
_dPhi_dq[108] = 0.0000000000000000e+00;
_dPhi_dq[109] = 0.0000000000000000e+00;
_dPhi_dq[110] = 0.0000000000000000e+00;
_dPhi_dq[111] = 0.0000000000000000e+00;
_dPhi_dq[112] = 0.0000000000000000e+00;
_dPhi_dq[113] = 0.0000000000000000e+00;
_dPhi_dq[114] = 0.0000000000000000e+00;
_dPhi_dq[115] = 0.0000000000000000e+00;
_dPhi_dq[116] = 0.0000000000000000e+00;
_dPhi_dq[117] = 0.0000000000000000e+00;
_dPhi_dq[118] = 0.0000000000000000e+00;
_dPhi_dq[119] = 0.0000000000000000e+00;
_dPhi_dq[120] = 0.0000000000000000e+00;
_dPhi_dq[121] = 0.0000000000000000e+00;
_dPhi_dq[122] = 0.0000000000000000e+00;
_dPhi_dq[123] = 0.0000000000000000e+00;
_dPhi_dq[124] = 0.0000000000000000e+00;
_dPhi_dq[125] = 0.0000000000000000e+00;
_dPhi_dq[126] = 0.0000000000000000e+00;
_dPhi_dq[127] = 0.0000000000000000e+00;
_dPhi_dq[128] = 0.0000000000000000e+00;
_dPhi_dq[129] = 0.0000000000000000e+00;
_dPhi_dq[130] = 0.0000000000000000e+00;
_dPhi_dq[131] = 0.0000000000000000e+00;
_dPhi_dq[132] = 0.0000000000000000e+00;
_dPhi_dq[133] = 0.0000000000000000e+00;
_dPhi_dq[134] = 0.0000000000000000e+00;
_dPhi_dq[135] = 0.0000000000000000e+00;
_dPhi_dq[136] = 0.0000000000000000e+00;
_dPhi_dq[137] = 0.0000000000000000e+00;
_dPhi_dq[138] = 0.0000000000000000e+00;
_dPhi_dq[139] = 0.0000000000000000e+00;
_dPhi_dq[140] = 0.0000000000000000e+00;
_dPhi_dq[141] = 0.0000000000000000e+00;
_dPhi_dq[142] = 0.0000000000000000e+00;
_dPhi_dq[143] = 0.0000000000000000e+00;
_dPhi_dq[144] = 0.0000000000000000e+00;
_dPhi_dq[145] = 0.0000000000000000e+00;
_dPhi_dq[146] = 0.0000000000000000e+00;
_dPhi_dq[147] = 0.0000000000000000e+00;
_dPhi_dq[148] = 0.0000000000000000e+00;
_dPhi_dq[149] = 0.0000000000000000e+00;
_dPhi_dq[150] = 0.0000000000000000e+00;
_dPhi_dq[151] = 0.0000000000000000e+00;
_dPhi_dq[152] = 0.0000000000000000e+00;
_dPhi_dq[153] = 0.0000000000000000e+00;
_dPhi_dq[154] = 0.0000000000000000e+00;
_dPhi_dq[155] = 0.0000000000000000e+00;
_dPhi_dq[156] = 0.0000000000000000e+00;
_dPhi_dq[157] = 0.0000000000000000e+00;
_dPhi_dq[158] = 0.0000000000000000e+00;
_dPhi_dq[159] = 0.0000000000000000e+00;
_dPhi_dq[160] = 0.0000000000000000e+00;
_dPhi_dq[161] = 0.0000000000000000e+00;
_dPhi_dq[162] = 0.0000000000000000e+00;
_dPhi_dq[163] = 0.0000000000000000e+00;
_dPhi_dq[164] = 0.0000000000000000e+00;
_dPhi_dq[165] = 0.0000000000000000e+00;
_dPhi_dq[166] = 0.0000000000000000e+00;
_dPhi_dq[167] = 0.0000000000000000e+00;
_dPhi_dq[168] = 0.0000000000000000e+00;
_dPhi_dq[169] = 0.0000000000000000e+00;
_dPhi_dq[170] = 0.0000000000000000e+00;
_dPhi_dq[171] = 0.0000000000000000e+00;
_dPhi_dq[172] = 0.0000000000000000e+00;
_dPhi_dq[173] = 0.0000000000000000e+00;
_dPhi_dq[174] = 0.0000000000000000e+00;
_dPhi_dq[175] = 0.0000000000000000e+00;
_dPhi_dq[176] = 0.0000000000000000e+00;
_dPhi_dq[177] = 0.0000000000000000e+00;
_dPhi_dq[178] = 0.0000000000000000e+00;
_dPhi_dq[179] = 0.0000000000000000e+00;
_dPhi_dq[180] = 0.0000000000000000e+00;
_dPhi_dq[181] = 0.0000000000000000e+00;
_dPhi_dq[182] = 0.0000000000000000e+00;
_dPhi_dq[183] = 0.0000000000000000e+00;
_dPhi_dq[184] = 0.0000000000000000e+00;
_dPhi_dq[185] = 0.0000000000000000e+00;
_dPhi_dq[186] = 0.0000000000000000e+00;
_dPhi_dq[187] = 0.0000000000000000e+00;
_dPhi_dq[188] = 0.0000000000000000e+00;
_dPhi_dq[189] = 0.0000000000000000e+00;
_dPhi_dq[190] = 0.0000000000000000e+00;
_dPhi_dq[191] = 0.0000000000000000e+00;
_dPhi_dq[192] = 0.0000000000000000e+00;
_dPhi_dq[193] = 0.0000000000000000e+00;
_dPhi_dq[194] = 0.0000000000000000e+00;
_dPhi_dq[195] = 0.0000000000000000e+00;
_dPhi_dq[196] = 0.0000000000000000e+00;
_dPhi_dq[197] = 0.0000000000000000e+00;
_dPhi_dq[198] = 0.0000000000000000e+00;
_dPhi_dq[199] = 0.0000000000000000e+00;
_dPhi_dq[200] = 0.0000000000000000e+00;
_dPhi_dq[201] = 0.0000000000000000e+00;
_dPhi_dq[202] = 0.0000000000000000e+00;
_dPhi_dq[203] = 0.0000000000000000e+00;
_dPhi_dq[204] = 0.0000000000000000e+00;
_dPhi_dq[205] = 0.0000000000000000e+00;
_dPhi_dq[206] = 0.0000000000000000e+00;
_dPhi_dq[207] = 0.0000000000000000e+00;
_dPhi_dq[208] = 0.0000000000000000e+00;
_dPhi_dq[209] = 0.0000000000000000e+00;
_dPhi_dq[210] = 0.0000000000000000e+00;
_dPhi_dq[211] = 0.0000000000000000e+00;
_dPhi_dq[212] = 0.0000000000000000e+00;
_dPhi_dq[213] = 0.0000000000000000e+00;
_dPhi_dq[214] = 0.0000000000000000e+00;
_dPhi_dq[215] = 0.0000000000000000e+00;
_dPhi_dq[216] = 0.0000000000000000e+00;
_dPhi_dq[217] = 0.0000000000000000e+00;
_dPhi_dq[218] = 0.0000000000000000e+00;
_dPhi_dq[219] = 0.0000000000000000e+00;
_dPhi_dq[220] = 0.0000000000000000e+00;
_dPhi_dq[221] = 0.0000000000000000e+00;
_dPhi_dq[222] = 0.0000000000000000e+00;
_dPhi_dq[223] = 0.0000000000000000e+00;
_dPhi_dq[224] = 0.0000000000000000e+00;
_dPhi_dq[225] = 0.0000000000000000e+00;
_dPhi_dq[226] = 0.0000000000000000e+00;
_dPhi_dq[227] = 0.0000000000000000e+00;
_dPhi_dq[228] = 0.0000000000000000e+00;
_dPhi_dq[229] = 0.0000000000000000e+00;
_dPhi_dq[230] = 0.0000000000000000e+00;
_dPhi_dq[231] = 0.0000000000000000e+00;
_dPhi_dq[232] = 0.0000000000000000e+00;
_dPhi_dq[233] = 0.0000000000000000e+00;
_dPhi_dq[234] = 0.0000000000000000e+00;
_dPhi_dq[235] = 0.0000000000000000e+00;
_dPhi_dq[236] = 0.0000000000000000e+00;
_dPhi_dq[237] = 0.0000000000000000e+00;
_dPhi_dq[238] = 0.0000000000000000e+00;
_dPhi_dq[239] = 0.0000000000000000e+00;
_dPhi_dq[240] = 0.0000000000000000e+00;
_dPhi_dq[241] = 0.0000000000000000e+00;
_dPhi_dq[242] = 0.0000000000000000e+00;
_dPhi_dq[243] = 0.0000000000000000e+00;
_dPhi_dq[244] = 0.0000000000000000e+00;
_dPhi_dq[245] = 0.0000000000000000e+00;
_dPhi_dq[246] = 0.0000000000000000e+00;
_dPhi_dq[247] = 0.0000000000000000e+00;
_dPhi_dq[248] = 0.0000000000000000e+00;
_dPhi_dq[249] = 0.0000000000000000e+00;
_dPhi_dq[250] = 0.0000000000000000e+00;
_dPhi_dq[251] = 0.0000000000000000e+00;
_dPhi_dq[252] = 0.0000000000000000e+00;
_dPhi_dq[253] = 0.0000000000000000e+00;
_dPhi_dq[254] = 0.0000000000000000e+00;
_dPhi_dq[255] = 0.0000000000000000e+00;
_dPhi_dq[256] = 0.0000000000000000e+00;
_dPhi_dq[257] = 0.0000000000000000e+00;
_dPhi_dq[258] = 0.0000000000000000e+00;
_dPhi_dq[259] = 0.0000000000000000e+00;
_dPhi_dq[260] = 0.0000000000000000e+00;
_dPhi_dq[261] = 0.0000000000000000e+00;
_dPhi_dq[262] = 0.0000000000000000e+00;
_dPhi_dq[263] = 0.0000000000000000e+00;
_dPhi_dq[264] = 0.0000000000000000e+00;
_dPhi_dq[265] = 0.0000000000000000e+00;
_dPhi_dq[266] = 0.0000000000000000e+00;
_dPhi_dq[267] = 0.0000000000000000e+00;
_dPhi_dq[268] = 0.0000000000000000e+00;
_dPhi_dq[269] = 0.0000000000000000e+00;
_dPhi_dq[270] = 0.0000000000000000e+00;
_dPhi_dq[271] = 0.0000000000000000e+00;
_dPhi_dq[272] = 0.0000000000000000e+00;
_dPhi_dq[273] = 0.0000000000000000e+00;
_dPhi_dq[274] = 0.0000000000000000e+00;
_dPhi_dq[275] = 0.0000000000000000e+00;
_dPhi_dq[276] = 0.0000000000000000e+00;
_dPhi_dq[277] = 0.0000000000000000e+00;
_dPhi_dq[278] = 0.0000000000000000e+00;
_dPhi_dq[279] = 0.0000000000000000e+00;
_dPhi_dq[280] = 0.0000000000000000e+00;
_dPhi_dq[281] = 0.0000000000000000e+00;
_dPhi_dq[282] = 0.0000000000000000e+00;
_dPhi_dq[283] = 0.0000000000000000e+00;
_dPhi_dq[284] = 0.0000000000000000e+00;
_dPhi_dq[285] = 0.0000000000000000e+00;
_dPhi_dq[286] = 0.0000000000000000e+00;
_dPhi_dq[287] = 0.0000000000000000e+00;
_dPhi_dq[288] = 0.0000000000000000e+00;
_dPhi_dq[289] = 0.0000000000000000e+00;
_dPhi_dq[290] = 0.0000000000000000e+00;
_dPhi_dq[291] = 0.0000000000000000e+00;
_dPhi_dq[292] = 0.0000000000000000e+00;
_dPhi_dq[293] = 0.0000000000000000e+00;
_dPhi_dq[294] = 0.0000000000000000e+00;
_dPhi_dq[295] = 0.0000000000000000e+00;
_dPhi_dq[296] = 0.0000000000000000e+00;
_dPhi_dq[297] = 0.0000000000000000e+00;
_dPhi_dq[298] = 0.0000000000000000e+00;
_dPhi_dq[299] = 0.0000000000000000e+00;
_dPhi_dq[300] = 0.0000000000000000e+00;
_dPhi_dq[301] = 0.0000000000000000e+00;
_dPhi_dq[302] = 0.0000000000000000e+00;
_dPhi_dq[303] = 0.0000000000000000e+00;
_dPhi_dq[304] = 0.0000000000000000e+00;
_dPhi_dq[305] = 0.0000000000000000e+00;
_dPhi_dq[306] = 0.0000000000000000e+00;
_dPhi_dq[307] = 0.0000000000000000e+00;
_dPhi_dq[308] = 0.0000000000000000e+00;
_dPhi_dq[309] = 0.0000000000000000e+00;
_dPhi_dq[310] = 0.0000000000000000e+00;
_dPhi_dq[311] = 0.0000000000000000e+00;
_dPhi_dq[312] = 0.0000000000000000e+00;
_dPhi_dq[313] = 0.0000000000000000e+00;
_dPhi_dq[314] = 0.0000000000000000e+00;
_dPhi_dq[315] = 0.0000000000000000e+00;
_dPhi_dq[316] = 0.0000000000000000e+00;
_dPhi_dq[317] = 0.0000000000000000e+00;
_dPhi_dq[318] = 0.0000000000000000e+00;
_dPhi_dq[319] = 0.0000000000000000e+00;
_dPhi_dq[320] = 0.0000000000000000e+00;
_dPhi_dq[321] = 0.0000000000000000e+00;
_dPhi_dq[322] = 0.0000000000000000e+00;
_dPhi_dq[323] = 0.0000000000000000e+00;
_dPhi_dq[324] = 0.0000000000000000e+00;
_dPhi_dq[325] = 0.0000000000000000e+00;
_dPhi_dq[326] = -1.0000000000000000e+00;
_dPhi_dq[327] = 0.0000000000000000e+00;
_dPhi_dq[328] = 0.0000000000000000e+00;
_dPhi_dq[329] = 0.0000000000000000e+00;
_dPhi_dq[330] = 0.0000000000000000e+00;
_dPhi_dq[331] = 0.0000000000000000e+00;
_dPhi_dq[332] = 0.0000000000000000e+00;
_dPhi_dq[333] = 0.0000000000000000e+00;
_dPhi_dq[334] = 0.0000000000000000e+00;
_dPhi_dq[335] = 0.0000000000000000e+00;
_dPhi_dq[336] = 0.0000000000000000e+00;
_dPhi_dq[337] = 0.0000000000000000e+00;
_dPhi_dq[338] = 0.0000000000000000e+00;
_dPhi_dq[339] = 0.0000000000000000e+00;
_dPhi_dq[340] = 0.0000000000000000e+00;
_dPhi_dq[341] = 0.0000000000000000e+00;
_dPhi_dq[342] = 0.0000000000000000e+00;
_dPhi_dq[343] = 0.0000000000000000e+00;
_dPhi_dq[344] = 0.0000000000000000e+00;
_dPhi_dq[345] = 0.0000000000000000e+00;
_dPhi_dq[346] = 0.0000000000000000e+00;
_dPhi_dq[347] = -1.0000000000000000e+00;
_dPhi_dq[348] = 0.0000000000000000e+00;
_dPhi_dq[349] = 0.0000000000000000e+00;
_dPhi_dq[350] = 0.0000000000000000e+00;
_dPhi_dq[351] = 0.0000000000000000e+00;
_dPhi_dq[352] = 0.0000000000000000e+00;
_dPhi_dq[353] = 0.0000000000000000e+00;
_dPhi_dq[354] = 0.0000000000000000e+00;
_dPhi_dq[355] = 0.0000000000000000e+00;
_dPhi_dq[356] = 0.0000000000000000e+00;
_dPhi_dq[357] = 0.0000000000000000e+00;
_dPhi_dq[358] = 0.0000000000000000e+00;
_dPhi_dq[359] = 0.0000000000000000e+00;
_dPhi_dq[360] = 0.0000000000000000e+00;
_dPhi_dq[361] = 0.0000000000000000e+00;
_dPhi_dq[362] = 0.0000000000000000e+00;
_dPhi_dq[363] = 0.0000000000000000e+00;
_dPhi_dq[364] = 0.0000000000000000e+00;
_dPhi_dq[365] = 0.0000000000000000e+00;
_dPhi_dq[366] = 0.0000000000000000e+00;
_dPhi_dq[367] = 0.0000000000000000e+00;
_dPhi_dq[368] = -1.0000000000000000e+00;
_dPhi_dq[369] = 0.0000000000000000e+00;
_dPhi_dq[370] = 0.0000000000000000e+00;
_dPhi_dq[371] = 0.0000000000000000e+00;
_dPhi_dq[372] = 0.0000000000000000e+00;
_dPhi_dq[373] = 0.0000000000000000e+00;
_dPhi_dq[374] = 0.0000000000000000e+00;
_dPhi_dq[375] = 0.0000000000000000e+00;
_dPhi_dq[376] = 0.0000000000000000e+00;
_dPhi_dq[377] = 0.0000000000000000e+00;
_dPhi_dq[378] = 0.0000000000000000e+00;
_dPhi_dq[379] = 0.0000000000000000e+00;
_dPhi_dq[380] = 0.0000000000000000e+00;
_dPhi_dq[381] = 0.0000000000000000e+00;
_dPhi_dq[382] = 0.0000000000000000e+00;
_dPhi_dq[383] = 0.0000000000000000e+00;
_dPhi_dq[384] = 0.0000000000000000e+00;
_dPhi_dq[385] = 0.0000000000000000e+00;
_dPhi_dq[386] = 0.0000000000000000e+00;
_dPhi_dq[387] = 0.0000000000000000e+00;
_dPhi_dq[388] = 0.0000000000000000e+00;
_dPhi_dq[389] = -1.0000000000000000e+00;
_dPhi_dq[390] = 0.0000000000000000e+00;
_dPhi_dq[391] = 0.0000000000000000e+00;
_dPhi_dq[392] = 0.0000000000000000e+00;
_dPhi_dq[393] = 0.0000000000000000e+00;
_dPhi_dq[394] = 0.0000000000000000e+00;
_dPhi_dq[395] = 0.0000000000000000e+00;
_dPhi_dq[396] = 0.0000000000000000e+00;
_dPhi_dq[397] = 0.0000000000000000e+00;
_dPhi_dq[398] = 0.0000000000000000e+00;
_dPhi_dq[399] = 0.0000000000000000e+00;
_dPhi_dq[400] = 0.0000000000000000e+00;
_dPhi_dq[401] = 0.0000000000000000e+00;
_dPhi_dq[402] = 0.0000000000000000e+00;
_dPhi_dq[403] = 0.0000000000000000e+00;
_dPhi_dq[404] = 0.0000000000000000e+00;
_dPhi_dq[405] = 0.0000000000000000e+00;
_dPhi_dq[406] = 0.0000000000000000e+00;
_dPhi_dq[407] = 0.0000000000000000e+00;
_dPhi_dq[408] = 0.0000000000000000e+00;
_dPhi_dq[409] = 0.0000000000000000e+00;
_dPhi_dq[410] = -1.0000000000000000e+00;
_dPhi_dq[411] = 0.0000000000000000e+00;
_dPhi_dq[412] = 0.0000000000000000e+00;
_dPhi_dq[413] = 0.0000000000000000e+00;
_dPhi_dq[414] = 0.0000000000000000e+00;
_dPhi_dq[415] = 0.0000000000000000e+00;
_dPhi_dq[416] = 0.0000000000000000e+00;
_dPhi_dq[417] = 0.0000000000000000e+00;
_dPhi_dq[418] = 0.0000000000000000e+00;
_dPhi_dq[419] = 0.0000000000000000e+00;
_dPhi_dq[420] = 0.0000000000000000e+00;
_dPhi_dq[421] = 0.0000000000000000e+00;
_dPhi_dq[422] = 0.0000000000000000e+00;
_dPhi_dq[423] = 0.0000000000000000e+00;
_dPhi_dq[424] = 0.0000000000000000e+00;
_dPhi_dq[425] = 0.0000000000000000e+00;
_dPhi_dq[426] = 0.0000000000000000e+00;
_dPhi_dq[427] = 0.0000000000000000e+00;
_dPhi_dq[428] = 0.0000000000000000e+00;
_dPhi_dq[429] = 0.0000000000000000e+00;
_dPhi_dq[430] = 0.0000000000000000e+00;
_dPhi_dq[431] = -1.0000000000000000e+00;

return _dPhi_dq;
}
