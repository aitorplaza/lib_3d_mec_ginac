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

double atom37;
double atom39;
double atom47;
double atom38;
double atom48;
double atom3790;
double atom40;
double atom3784;
double atom3787;
double atom41;
double atom42;
double atom43;
double atom51;
double atom44;
double atom3796;
double atom54;
double atom3793;
double atom3799;
double atom45;
double atom60;
double atom46;
double atom3802;
double atom57;
double atom3805;
double atom3808;
double atom3756;
double atom3843;
double atom3751;
double atom3752;
double atom3753;
double atom3755;
double atom3763;
double atom80;
double atom79;
double atom838;
double atom81;
double atom86;
double atom82;
double atom85;
double atom104;
double atom103;
double atom1132;
double atom106;
double atom105;
double atom109;
double atom110;
double atom128;
double atom127;
double atom1433;
double atom130;
double atom129;
double atom148;
double atom149;
double atom169;
double atom168;
double atom1751;
double atom171;
double atom170;
double atom188;
double atom189;
double atom209;
double atom208;
double atom2067;
double atom211;
double atom210;
double atom229;
double atom228;
double atom248;
double atom249;
double atom2383;
double atom250;
double atom269;
double atom251;
double atom268;
double atom3829;
double atom3814;
double atom3832;
double atom3820;
double atom3835;
double atom3826;
double atom3841;
double atom3765;
double atom839;
double atom4019;
double atom1133;
double atom4119;
double atom1434;
double atom4219;
double atom1752;
double atom4333;
double atom2068;
double atom4447;
double atom2384;
double atom4561;
double atom4013;
double atom4113;
double atom4213;
double atom4327;
double atom4441;
double atom4555;

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

atom37 = cos(c);
atom39 = cos(b);
atom47 = atom37*atom39;
atom38 = sin(c);
atom48 = -atom38*atom39;
atom3790 = -atom47*myP+mxP*atom48;
atom40 = sin(b);
atom3784 = -mzP*atom48+atom40*myP;
atom3787 =  mzP*atom47-atom40*mxP;
atom41 = cos(a);
atom42 = sin(a);
atom43 = atom40*atom42;
atom51 =  atom41*atom38+atom37*atom43;
atom44 = -atom42*atom39;
atom3796 =  mzP*atom51-atom44*mxP;
atom54 = -atom38*atom43+atom37*atom41;
atom3793 = -mzP*atom54+atom44*myP;
atom3799 =  mxP*atom54-myP*atom51;
atom45 = -atom40*atom41;
atom60 = -atom38*atom45+atom37*atom42;
atom46 = atom41*atom39;
atom3802 =  atom46*myP-mzP*atom60;
atom57 =  atom37*atom45+atom42*atom38;
atom3805 = -mxP*atom46+mzP*atom57;
atom3808 =  atom60*mxP-atom57*myP;
atom3756 = atom37*IxzP;
atom3843 = -atom39*( atom38*IyzP-atom3756)+atom40*IzzP;
atom3751 = -atom38*IxyP;
atom3752 =  atom3751+atom37*IxxP;
atom3753 = atom37*IxyP;
atom3755 = -atom38*IyyP+atom3753;
atom3763 = IxzP*atom38;
atom80 = sin(b1);
atom79 = cos(b1);
atom838 = atom80*Izz1;
atom81 = cos(a1);
atom86 = atom79*atom81;
atom82 = sin(a1);
atom85 = -atom80*atom81;
atom104 = sin(b2);
atom103 = cos(b2);
atom1132 = atom104*Izz2;
atom106 = sin(a2);
atom105 = cos(a2);
atom109 = -atom104*atom105;
atom110 = atom103*atom105;
atom128 = sin(b3);
atom127 = cos(b3);
atom1433 = Izz3*atom128;
atom130 = sin(a3);
atom129 = cos(a3);
atom148 = -atom128*atom129;
atom149 = atom127*atom129;
atom169 = sin(b4);
atom168 = cos(b4);
atom1751 = Izz4*atom169;
atom171 = sin(a4);
atom170 = cos(a4);
atom188 = -atom169*atom170;
atom189 = atom168*atom170;
atom209 = sin(b5);
atom208 = cos(b5);
atom2067 = atom209*Izz5;
atom211 = sin(a5);
atom210 = cos(a5);
atom229 = atom208*atom210;
atom228 = -atom209*atom210;
atom248 = cos(b6);
atom249 = sin(b6);
atom2383 = atom249*Izz6;
atom250 = cos(a6);
atom269 = atom250*atom248;
atom251 = sin(a6);
atom268 = -atom249*atom250;
atom3829 = -( atom38*atom3787-atom37*atom3784)*atom39+atom3790*atom40;
atom3814 =  atom38*atom3784+atom37*atom3787;
atom3832 = -( atom38*atom3796-atom37*atom3793)*atom39+atom40*atom3799;
atom3820 =  atom38*atom3793+atom37*atom3796;
atom3835 = -( atom38*atom3805-atom37*atom3802)*atom39+atom40*atom3808;
atom3826 =  atom38*atom3802+atom37*atom3805;
atom3841 =  ( atom3752*atom38+atom37*atom3755)*atom39+atom40*( atom3763+atom37*IzzP);
atom3765 =  atom3763+atom37*IyzP;
atom839 =  atom838+atom79*Ixy1;
atom4019 =  atom80*( mx1*atom82-atom85*my1)+atom79*( atom86*my1-mz1*atom82);
atom1133 =  atom103*Ixy2+atom1132;
atom4119 =  atom104*( mx2*atom106-atom109*my2)+atom103*( atom110*my2-mz2*atom106);
atom1434 =  atom1433+Ixy3*atom127;
atom4219 = -atom127*( atom130*mz3-my3*atom149)+( atom130*mx3-atom148*my3)*atom128;
atom1752 =  atom168*Ixy4+atom1751;
atom4333 =  atom168*( my4*atom189-mz4*atom171)-atom169*( atom188*my4-mx4*atom171);
atom2068 =  atom2067+atom208*Ixy5;
atom4447 = -atom208*( atom211*mz5-atom229*my5)-( atom228*my5-mx5*atom211)*atom209;
atom2384 =  Ixy6*atom248+atom2383;
atom4561 = -( atom251*mz6-atom269*my6)*atom248+( atom251*mx6-atom268*my6)*atom249;
atom4013 = -atom86*mx1+mz1*atom85;
atom4113 =  mz2*atom109-atom110*mx2;
atom4213 =  atom148*mz3-mx3*atom149;
atom4327 = -mx4*atom189+atom188*mz4;
atom4441 = -mx5*atom229+atom228*mz5;
atom4555 = -atom269*mx6+atom268*mz6;

_M[0] = -mP;
_M[3] = -atom3829;
_M[4] = -atom3814;
_M[5] = -atom3790;
_M[25] = -mP;
_M[27] = -atom3832;
_M[28] = -atom3820;
_M[29] = -atom3799;
_M[50] = -mP;
_M[51] = -atom3835;
_M[52] = -atom3826;
_M[53] = -atom3808;
_M[72] = -atom3829;
_M[73] = -atom3832;
_M[74] = -atom3835;
_M[75] =  ( atom40*( IzzP*atom38-atom3756)+( atom3755*atom38-atom37*atom3752)*atom39)*atom39-atom40*atom3843;
_M[76] = -atom3841;
_M[77] = -atom3843;
_M[96] = -atom3814;
_M[97] = -atom3820;
_M[98] = -atom3826;
_M[99] = -atom3841;
_M[100] =  atom37*( atom3751-atom37*IyyP)-atom38*( IxxP*atom38+atom3753);
_M[101] = -atom3765;
_M[120] = -atom3790;
_M[121] = -atom3799;
_M[122] = -atom3808;
_M[123] = -atom3843;
_M[124] = -atom3765;
_M[125] = -IzzP;
_M[150] = -atom79*( Ixz1*atom80+atom79*Ixx1)-atom80*( atom838+atom79*Ixz1);
_M[156] = -atom839;
_M[162] = -atom4019;
_M[175] = -atom103*( atom103*Ixx2+atom104*Ixz2)-( atom103*Ixz2+atom1132)*atom104;
_M[181] = -atom1133;
_M[187] = -atom4119;
_M[200] = -( atom128*Ixz3+atom127*Ixx3)*atom127-atom128*( atom1433+atom127*Ixz3);
_M[206] = -atom1434;
_M[212] = -atom4219;
_M[225] = -atom169*( atom1751+atom168*Ixz4)-atom168*( atom168*Ixx4+atom169*Ixz4);
_M[231] = -atom1752;
_M[237] = -atom4333;
_M[250] = -atom209*( atom2067+atom208*Ixz5)-atom208*( atom209*Ixz5+atom208*Ixx5);
_M[256] = -atom2068;
_M[262] = -atom4447;
_M[275] = -( atom249*Ixz6+atom248*Ixx6)*atom248-atom249*( Ixz6*atom248+atom2383);
_M[281] = -atom2384;
_M[287] = -atom4561;
_M[294] = -atom839;
_M[300] = -Iyy1;
_M[306] = -atom4013;
_M[319] = -atom1133;
_M[325] = -Iyy2;
_M[331] = -atom4113;
_M[344] = -atom1434;
_M[350] = -Iyy3;
_M[356] = -atom4213;
_M[369] = -atom1752;
_M[375] = -Iyy4;
_M[381] = -atom4327;
_M[394] = -atom2068;
_M[400] = -Iyy5;
_M[406] = -atom4441;
_M[419] = -atom2384;
_M[425] = -Iyy6;
_M[431] = -atom4555;
_M[438] = -atom4019;
_M[444] = -atom4013;
_M[450] = -m1;
_M[463] = -atom4119;
_M[469] = -atom4113;
_M[475] = -m2;
_M[488] = -atom4219;
_M[494] = -atom4213;
_M[500] = -m3;
_M[513] = -atom4333;
_M[519] = -atom4327;
_M[525] = -m4;
_M[538] = -atom4447;
_M[544] = -atom4441;
_M[550] = -m5;
_M[563] = -atom4561;
_M[569] = -atom4555;
_M[575] = -m6;

return _M;
}
