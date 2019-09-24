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

double atom38;
double atom39;
double atom40;
double atom37;
double atom47;
double atom48;
double atom2480;
double atom2477;
double atom2483;
double atom41;
double atom42;
double atom43;
double atom54;
double atom51;
double atom2492;
double atom44;
double atom2489;
double atom2486;
double atom45;
double atom57;
double atom46;
double atom2498;
double atom60;
double atom2495;
double atom2501;
double atom307;
double atom302;
double atom297;
double atom79;
double atom80;
double atom82;
double atom81;
double atom85;
double atom86;
double atom104;
double atom103;
double atom106;
double atom105;
double atom110;
double atom109;
double atom127;
double atom128;
double atom130;
double atom129;
double atom148;
double atom149;
double atom168;
double atom169;
double atom171;
double atom170;
double atom189;
double atom188;
double atom208;
double atom209;
double atom211;
double atom210;
double atom228;
double atom229;
double atom249;
double atom248;
double atom250;
double atom269;
double atom251;
double atom268;
double atom2506;
double atom2509;
double atom2514;
double atom2517;
double atom2522;
double atom2525;
double atom339;
double atom316;
double atom649;
double atom2710;
double atom763;
double atom2856;
double atom877;
double atom3002;
double atom1001;
double atom3161;
double atom1125;
double atom3320;
double atom1249;
double atom3479;
double atom2704;
double atom2850;
double atom2996;
double atom3155;
double atom3314;
double atom3473;

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

atom38 = sin(c);
atom39 = cos(b);
atom40 = sin(b);
atom37 = cos(c);
atom47 = atom39*atom37;
atom48 = -atom38*atom39;
atom2480 =  atom47*mzP-mxP*atom40;
atom2477 =  myP*atom40-atom48*mzP;
atom2483 =  mxP*atom48-atom47*myP;
atom41 = cos(a);
atom42 = sin(a);
atom43 = atom42*atom40;
atom54 =  atom41*atom37-atom38*atom43;
atom51 =  atom43*atom37+atom41*atom38;
atom2492 =  mxP*atom54-myP*atom51;
atom44 = -atom42*atom39;
atom2489 = -mxP*atom44+mzP*atom51;
atom2486 = -atom54*mzP+atom44*myP;
atom45 = -atom41*atom40;
atom57 =  atom45*atom37+atom42*atom38;
atom46 = atom41*atom39;
atom2498 =  atom57*mzP-mxP*atom46;
atom60 = -atom38*atom45+atom42*atom37;
atom2495 =  myP*atom46-atom60*mzP;
atom2501 =  atom60*mxP-atom57*myP;
atom307 =  IyzP*atom48+atom47*IxzP+IzzP*atom40;
atom302 =  atom48*IyyP+IyzP*atom40+atom47*IxyP;
atom297 =  IxyP*atom48+IxxP*atom47+atom40*IxzP;
atom79 = cos(b1);
atom80 = sin(b1);
atom82 = sin(a1);
atom81 = cos(a1);
atom85 = -atom80*atom81;
atom86 = atom81*atom79;
atom104 = sin(b2);
atom103 = cos(b2);
atom106 = sin(a2);
atom105 = cos(a2);
atom110 = atom105*atom103;
atom109 = -atom104*atom105;
atom127 = cos(b3);
atom128 = sin(b3);
atom130 = sin(a3);
atom129 = cos(a3);
atom148 = -atom128*atom129;
atom149 = atom127*atom129;
atom168 = cos(b4);
atom169 = sin(b4);
atom171 = sin(a4);
atom170 = cos(a4);
atom189 = atom170*atom168;
atom188 = -atom169*atom170;
atom208 = cos(b5);
atom209 = sin(b5);
atom211 = sin(a5);
atom210 = cos(a5);
atom228 = -atom209*atom210;
atom229 = atom210*atom208;
atom249 = sin(b6);
atom248 = cos(b6);
atom250 = cos(a6);
atom269 = atom250*atom248;
atom251 = sin(a6);
atom268 = -atom250*atom249;
atom2506 =  atom47*atom2477+atom2483*atom40+atom48*atom2480;
atom2509 =  atom2480*atom37+atom38*atom2477;
atom2514 =  atom48*atom2489+atom2486*atom47+atom2492*atom40;
atom2517 =  atom2489*atom37+atom2486*atom38;
atom2522 =  atom2501*atom40+atom48*atom2498+atom47*atom2495;
atom2525 =  atom2498*atom37+atom38*atom2495;
atom339 =  atom38*atom297+atom302*atom37;
atom316 =  atom38*IxzP+IyzP*atom37;
atom649 =  Ixy1*atom79+atom80*Iyz1;
atom2710 = -atom80*( atom85*my1-mx1*atom82)-( atom82*mz1-my1*atom86)*atom79;
atom763 =  atom104*Iyz2+Ixy2*atom103;
atom2856 =  ( my2*atom110-atom106*mz2)*atom103+atom104*( mx2*atom106-atom109*my2);
atom877 =  atom127*Ixy3+atom128*Iyz3;
atom3002 = -atom127*( atom130*mz3-my3*atom149)-atom128*( my3*atom148-mx3*atom130);
atom1001 =  atom169*Iyz4+Ixy4*atom168;
atom3161 =  atom169*( mx4*atom171-my4*atom188)+( atom189*my4-mz4*atom171)*atom168;
atom1125 =  Iyz5*atom209+Ixy5*atom208;
atom3320 = -( mz5*atom211-my5*atom229)*atom208+atom209*( atom211*mx5-my5*atom228);
atom1249 =  Iyz6*atom249+atom248*Ixy6;
atom3479 =  ( atom269*my6-mz6*atom251)*atom248+( atom251*mx6-atom268*my6)*atom249;
atom2704 = -mx1*atom86+atom85*mz1;
atom2850 =  atom109*mz2-mx2*atom110;
atom2996 =  atom148*mz3-mx3*atom149;
atom3155 =  mz4*atom188-mx4*atom189;
atom3314 =  mz5*atom228-mx5*atom229;
atom3473 = -mx6*atom269+atom268*mz6;

_M[0] = -mP;
_M[1] = 0.0;
_M[2] = 0.0;
_M[3] = -atom2506;
_M[4] = -atom2509;
_M[5] = -atom2483;
_M[6] = 0.0;
_M[7] = 0.0;
_M[8] = 0.0;
_M[9] = 0.0;
_M[10] = 0.0;
_M[11] = 0.0;
_M[12] = 0.0;
_M[13] = 0.0;
_M[14] = 0.0;
_M[15] = 0.0;
_M[16] = 0.0;
_M[17] = 0.0;
_M[18] = 0.0;
_M[19] = 0.0;
_M[20] = 0.0;
_M[21] = 0.0;
_M[22] = 0.0;
_M[23] = 0.0;
_M[24] = 0.0;
_M[25] = -mP;
_M[26] = 0.0;
_M[27] = -atom2514;
_M[28] = -atom2517;
_M[29] = -atom2492;
_M[30] = 0.0;
_M[31] = 0.0;
_M[32] = 0.0;
_M[33] = 0.0;
_M[34] = 0.0;
_M[35] = 0.0;
_M[36] = 0.0;
_M[37] = 0.0;
_M[38] = 0.0;
_M[39] = 0.0;
_M[40] = 0.0;
_M[41] = 0.0;
_M[42] = 0.0;
_M[43] = 0.0;
_M[44] = 0.0;
_M[45] = 0.0;
_M[46] = 0.0;
_M[47] = 0.0;
_M[48] = 0.0;
_M[49] = 0.0;
_M[50] = -mP;
_M[51] = -atom2522;
_M[52] = -atom2525;
_M[53] = -atom2501;
_M[54] = 0.0;
_M[55] = 0.0;
_M[56] = 0.0;
_M[57] = 0.0;
_M[58] = 0.0;
_M[59] = 0.0;
_M[60] = 0.0;
_M[61] = 0.0;
_M[62] = 0.0;
_M[63] = 0.0;
_M[64] = 0.0;
_M[65] = 0.0;
_M[66] = 0.0;
_M[67] = 0.0;
_M[68] = 0.0;
_M[69] = 0.0;
_M[70] = 0.0;
_M[71] = 0.0;
_M[72] = -atom2506;
_M[73] = -atom2514;
_M[74] = -atom2522;
_M[75] = -atom307*atom40-atom47*atom297-atom302*atom48;
_M[76] = -atom339;
_M[77] = -atom307;
_M[78] = 0.0;
_M[79] = 0.0;
_M[80] = 0.0;
_M[81] = 0.0;
_M[82] = 0.0;
_M[83] = 0.0;
_M[84] = 0.0;
_M[85] = 0.0;
_M[86] = 0.0;
_M[87] = 0.0;
_M[88] = 0.0;
_M[89] = 0.0;
_M[90] = 0.0;
_M[91] = 0.0;
_M[92] = 0.0;
_M[93] = 0.0;
_M[94] = 0.0;
_M[95] = 0.0;
_M[96] = -atom2509;
_M[97] = -atom2517;
_M[98] = -atom2525;
_M[99] = -atom339;
_M[100] = -( IyyP*atom37+IxyP*atom38)*atom37-( IxxP*atom38+IxyP*atom37)*atom38;
_M[101] = -atom316;
_M[102] = 0.0;
_M[103] = 0.0;
_M[104] = 0.0;
_M[105] = 0.0;
_M[106] = 0.0;
_M[107] = 0.0;
_M[108] = 0.0;
_M[109] = 0.0;
_M[110] = 0.0;
_M[111] = 0.0;
_M[112] = 0.0;
_M[113] = 0.0;
_M[114] = 0.0;
_M[115] = 0.0;
_M[116] = 0.0;
_M[117] = 0.0;
_M[118] = 0.0;
_M[119] = 0.0;
_M[120] = -atom2483;
_M[121] = -atom2492;
_M[122] = -atom2501;
_M[123] = -atom307;
_M[124] = -atom316;
_M[125] = -IzzP;
_M[126] = 0.0;
_M[127] = 0.0;
_M[128] = 0.0;
_M[129] = 0.0;
_M[130] = 0.0;
_M[131] = 0.0;
_M[132] = 0.0;
_M[133] = 0.0;
_M[134] = 0.0;
_M[135] = 0.0;
_M[136] = 0.0;
_M[137] = 0.0;
_M[138] = 0.0;
_M[139] = 0.0;
_M[140] = 0.0;
_M[141] = 0.0;
_M[142] = 0.0;
_M[143] = 0.0;
_M[144] = 0.0;
_M[145] = 0.0;
_M[146] = 0.0;
_M[147] = 0.0;
_M[148] = 0.0;
_M[149] = 0.0;
_M[150] = -atom79*( Ixz1*atom80+Ixx1*atom79)-atom80*( atom80*Izz1+Ixz1*atom79);
_M[151] = 0.0;
_M[152] = 0.0;
_M[153] = 0.0;
_M[154] = 0.0;
_M[155] = 0.0;
_M[156] = -atom649;
_M[157] = 0.0;
_M[158] = 0.0;
_M[159] = 0.0;
_M[160] = 0.0;
_M[161] = 0.0;
_M[162] = -atom2710;
_M[163] = 0.0;
_M[164] = 0.0;
_M[165] = 0.0;
_M[166] = 0.0;
_M[167] = 0.0;
_M[168] = 0.0;
_M[169] = 0.0;
_M[170] = 0.0;
_M[171] = 0.0;
_M[172] = 0.0;
_M[173] = 0.0;
_M[174] = 0.0;
_M[175] = -atom104*( Ixz2*atom103+atom104*Izz2)-( Ixx2*atom103+atom104*Ixz2)*atom103;
_M[176] = 0.0;
_M[177] = 0.0;
_M[178] = 0.0;
_M[179] = 0.0;
_M[180] = 0.0;
_M[181] = -atom763;
_M[182] = 0.0;
_M[183] = 0.0;
_M[184] = 0.0;
_M[185] = 0.0;
_M[186] = 0.0;
_M[187] = -atom2856;
_M[188] = 0.0;
_M[189] = 0.0;
_M[190] = 0.0;
_M[191] = 0.0;
_M[192] = 0.0;
_M[193] = 0.0;
_M[194] = 0.0;
_M[195] = 0.0;
_M[196] = 0.0;
_M[197] = 0.0;
_M[198] = 0.0;
_M[199] = 0.0;
_M[200] = -atom127*( Ixz3*atom128+atom127*Ixx3)-( atom128*Izz3+atom127*Ixz3)*atom128;
_M[201] = 0.0;
_M[202] = 0.0;
_M[203] = 0.0;
_M[204] = 0.0;
_M[205] = 0.0;
_M[206] = -atom877;
_M[207] = 0.0;
_M[208] = 0.0;
_M[209] = 0.0;
_M[210] = 0.0;
_M[211] = 0.0;
_M[212] = -atom3002;
_M[213] = 0.0;
_M[214] = 0.0;
_M[215] = 0.0;
_M[216] = 0.0;
_M[217] = 0.0;
_M[218] = 0.0;
_M[219] = 0.0;
_M[220] = 0.0;
_M[221] = 0.0;
_M[222] = 0.0;
_M[223] = 0.0;
_M[224] = 0.0;
_M[225] = -( Ixx4*atom168+atom169*Ixz4)*atom168-atom169*( atom169*Izz4+Ixz4*atom168);
_M[226] = 0.0;
_M[227] = 0.0;
_M[228] = 0.0;
_M[229] = 0.0;
_M[230] = 0.0;
_M[231] = -atom1001;
_M[232] = 0.0;
_M[233] = 0.0;
_M[234] = 0.0;
_M[235] = 0.0;
_M[236] = 0.0;
_M[237] = -atom3161;
_M[238] = 0.0;
_M[239] = 0.0;
_M[240] = 0.0;
_M[241] = 0.0;
_M[242] = 0.0;
_M[243] = 0.0;
_M[244] = 0.0;
_M[245] = 0.0;
_M[246] = 0.0;
_M[247] = 0.0;
_M[248] = 0.0;
_M[249] = 0.0;
_M[250] = -atom209*( atom209*Izz5+Ixz5*atom208)-( Ixx5*atom208+atom209*Ixz5)*atom208;
_M[251] = 0.0;
_M[252] = 0.0;
_M[253] = 0.0;
_M[254] = 0.0;
_M[255] = 0.0;
_M[256] = -atom1125;
_M[257] = 0.0;
_M[258] = 0.0;
_M[259] = 0.0;
_M[260] = 0.0;
_M[261] = 0.0;
_M[262] = -atom3320;
_M[263] = 0.0;
_M[264] = 0.0;
_M[265] = 0.0;
_M[266] = 0.0;
_M[267] = 0.0;
_M[268] = 0.0;
_M[269] = 0.0;
_M[270] = 0.0;
_M[271] = 0.0;
_M[272] = 0.0;
_M[273] = 0.0;
_M[274] = 0.0;
_M[275] = -( Ixz6*atom248+Izz6*atom249)*atom249-atom248*( Ixz6*atom249+Ixx6*atom248);
_M[276] = 0.0;
_M[277] = 0.0;
_M[278] = 0.0;
_M[279] = 0.0;
_M[280] = 0.0;
_M[281] = -atom1249;
_M[282] = 0.0;
_M[283] = 0.0;
_M[284] = 0.0;
_M[285] = 0.0;
_M[286] = 0.0;
_M[287] = -atom3479;
_M[288] = 0.0;
_M[289] = 0.0;
_M[290] = 0.0;
_M[291] = 0.0;
_M[292] = 0.0;
_M[293] = 0.0;
_M[294] = -atom649;
_M[295] = 0.0;
_M[296] = 0.0;
_M[297] = 0.0;
_M[298] = 0.0;
_M[299] = 0.0;
_M[300] = -Iyy1;
_M[301] = 0.0;
_M[302] = 0.0;
_M[303] = 0.0;
_M[304] = 0.0;
_M[305] = 0.0;
_M[306] = -atom2704;
_M[307] = 0.0;
_M[308] = 0.0;
_M[309] = 0.0;
_M[310] = 0.0;
_M[311] = 0.0;
_M[312] = 0.0;
_M[313] = 0.0;
_M[314] = 0.0;
_M[315] = 0.0;
_M[316] = 0.0;
_M[317] = 0.0;
_M[318] = 0.0;
_M[319] = -atom763;
_M[320] = 0.0;
_M[321] = 0.0;
_M[322] = 0.0;
_M[323] = 0.0;
_M[324] = 0.0;
_M[325] = -Iyy2;
_M[326] = 0.0;
_M[327] = 0.0;
_M[328] = 0.0;
_M[329] = 0.0;
_M[330] = 0.0;
_M[331] = -atom2850;
_M[332] = 0.0;
_M[333] = 0.0;
_M[334] = 0.0;
_M[335] = 0.0;
_M[336] = 0.0;
_M[337] = 0.0;
_M[338] = 0.0;
_M[339] = 0.0;
_M[340] = 0.0;
_M[341] = 0.0;
_M[342] = 0.0;
_M[343] = 0.0;
_M[344] = -atom877;
_M[345] = 0.0;
_M[346] = 0.0;
_M[347] = 0.0;
_M[348] = 0.0;
_M[349] = 0.0;
_M[350] = -Iyy3;
_M[351] = 0.0;
_M[352] = 0.0;
_M[353] = 0.0;
_M[354] = 0.0;
_M[355] = 0.0;
_M[356] = -atom2996;
_M[357] = 0.0;
_M[358] = 0.0;
_M[359] = 0.0;
_M[360] = 0.0;
_M[361] = 0.0;
_M[362] = 0.0;
_M[363] = 0.0;
_M[364] = 0.0;
_M[365] = 0.0;
_M[366] = 0.0;
_M[367] = 0.0;
_M[368] = 0.0;
_M[369] = -atom1001;
_M[370] = 0.0;
_M[371] = 0.0;
_M[372] = 0.0;
_M[373] = 0.0;
_M[374] = 0.0;
_M[375] = -Iyy4;
_M[376] = 0.0;
_M[377] = 0.0;
_M[378] = 0.0;
_M[379] = 0.0;
_M[380] = 0.0;
_M[381] = -atom3155;
_M[382] = 0.0;
_M[383] = 0.0;
_M[384] = 0.0;
_M[385] = 0.0;
_M[386] = 0.0;
_M[387] = 0.0;
_M[388] = 0.0;
_M[389] = 0.0;
_M[390] = 0.0;
_M[391] = 0.0;
_M[392] = 0.0;
_M[393] = 0.0;
_M[394] = -atom1125;
_M[395] = 0.0;
_M[396] = 0.0;
_M[397] = 0.0;
_M[398] = 0.0;
_M[399] = 0.0;
_M[400] = -Iyy5;
_M[401] = 0.0;
_M[402] = 0.0;
_M[403] = 0.0;
_M[404] = 0.0;
_M[405] = 0.0;
_M[406] = -atom3314;
_M[407] = 0.0;
_M[408] = 0.0;
_M[409] = 0.0;
_M[410] = 0.0;
_M[411] = 0.0;
_M[412] = 0.0;
_M[413] = 0.0;
_M[414] = 0.0;
_M[415] = 0.0;
_M[416] = 0.0;
_M[417] = 0.0;
_M[418] = 0.0;
_M[419] = -atom1249;
_M[420] = 0.0;
_M[421] = 0.0;
_M[422] = 0.0;
_M[423] = 0.0;
_M[424] = 0.0;
_M[425] = -Iyy6;
_M[426] = 0.0;
_M[427] = 0.0;
_M[428] = 0.0;
_M[429] = 0.0;
_M[430] = 0.0;
_M[431] = -atom3473;
_M[432] = 0.0;
_M[433] = 0.0;
_M[434] = 0.0;
_M[435] = 0.0;
_M[436] = 0.0;
_M[437] = 0.0;
_M[438] = -atom2710;
_M[439] = 0.0;
_M[440] = 0.0;
_M[441] = 0.0;
_M[442] = 0.0;
_M[443] = 0.0;
_M[444] = -atom2704;
_M[445] = 0.0;
_M[446] = 0.0;
_M[447] = 0.0;
_M[448] = 0.0;
_M[449] = 0.0;
_M[450] = -m1;
_M[451] = 0.0;
_M[452] = 0.0;
_M[453] = 0.0;
_M[454] = 0.0;
_M[455] = 0.0;
_M[456] = 0.0;
_M[457] = 0.0;
_M[458] = 0.0;
_M[459] = 0.0;
_M[460] = 0.0;
_M[461] = 0.0;
_M[462] = 0.0;
_M[463] = -atom2856;
_M[464] = 0.0;
_M[465] = 0.0;
_M[466] = 0.0;
_M[467] = 0.0;
_M[468] = 0.0;
_M[469] = -atom2850;
_M[470] = 0.0;
_M[471] = 0.0;
_M[472] = 0.0;
_M[473] = 0.0;
_M[474] = 0.0;
_M[475] = -m2;
_M[476] = 0.0;
_M[477] = 0.0;
_M[478] = 0.0;
_M[479] = 0.0;
_M[480] = 0.0;
_M[481] = 0.0;
_M[482] = 0.0;
_M[483] = 0.0;
_M[484] = 0.0;
_M[485] = 0.0;
_M[486] = 0.0;
_M[487] = 0.0;
_M[488] = -atom3002;
_M[489] = 0.0;
_M[490] = 0.0;
_M[491] = 0.0;
_M[492] = 0.0;
_M[493] = 0.0;
_M[494] = -atom2996;
_M[495] = 0.0;
_M[496] = 0.0;
_M[497] = 0.0;
_M[498] = 0.0;
_M[499] = 0.0;
_M[500] = -m3;
_M[501] = 0.0;
_M[502] = 0.0;
_M[503] = 0.0;
_M[504] = 0.0;
_M[505] = 0.0;
_M[506] = 0.0;
_M[507] = 0.0;
_M[508] = 0.0;
_M[509] = 0.0;
_M[510] = 0.0;
_M[511] = 0.0;
_M[512] = 0.0;
_M[513] = -atom3161;
_M[514] = 0.0;
_M[515] = 0.0;
_M[516] = 0.0;
_M[517] = 0.0;
_M[518] = 0.0;
_M[519] = -atom3155;
_M[520] = 0.0;
_M[521] = 0.0;
_M[522] = 0.0;
_M[523] = 0.0;
_M[524] = 0.0;
_M[525] = -m4;
_M[526] = 0.0;
_M[527] = 0.0;
_M[528] = 0.0;
_M[529] = 0.0;
_M[530] = 0.0;
_M[531] = 0.0;
_M[532] = 0.0;
_M[533] = 0.0;
_M[534] = 0.0;
_M[535] = 0.0;
_M[536] = 0.0;
_M[537] = 0.0;
_M[538] = -atom3320;
_M[539] = 0.0;
_M[540] = 0.0;
_M[541] = 0.0;
_M[542] = 0.0;
_M[543] = 0.0;
_M[544] = -atom3314;
_M[545] = 0.0;
_M[546] = 0.0;
_M[547] = 0.0;
_M[548] = 0.0;
_M[549] = 0.0;
_M[550] = -m5;
_M[551] = 0.0;
_M[552] = 0.0;
_M[553] = 0.0;
_M[554] = 0.0;
_M[555] = 0.0;
_M[556] = 0.0;
_M[557] = 0.0;
_M[558] = 0.0;
_M[559] = 0.0;
_M[560] = 0.0;
_M[561] = 0.0;
_M[562] = 0.0;
_M[563] = -atom3479;
_M[564] = 0.0;
_M[565] = 0.0;
_M[566] = 0.0;
_M[567] = 0.0;
_M[568] = 0.0;
_M[569] = -atom3473;
_M[570] = 0.0;
_M[571] = 0.0;
_M[572] = 0.0;
_M[573] = 0.0;
_M[574] = 0.0;
_M[575] = -m6;

return _M;
}
