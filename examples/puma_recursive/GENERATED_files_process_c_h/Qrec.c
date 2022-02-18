/*----------Qrec.c lib3D_MEC exported-----------*/

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

#include "Qrec.h"

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

double atom35;
double atom57;
double atom59;
double atom58;
double atom36;
double atom3537;
double atom3610;
double atom3538;
double atom3607;
double atom5508;
double atom80;
double atom888;
double atom81;
double atom5512;
double atom5660;
double atom115;
double atom5511;
double atom114;
double atom5664;
double atom5789;
double atom5663;
double atom152;
double atom5790;
double atom5786;
double atom153;
double atom5904;
double atom5903;
double atom5416;
double atom5417;
double atom6124;
double atom6130;
double atom6161;
double atom6165;
double atom6158;
double atom5923;
double atom6168;
double atom5900;
double atom6197;
double atom5919;
double atom5921;
double atom5916;
double atom5423;
double atom5528;
double atom6125;
double atom5531;
double atom6131;
double atom6120;
double atom6134;
double atom5436;
double atom6139;
double atom5435;
double atom6136;
double atom5527;
double atom5524;
double atom5525;
double atom5526;
double atom6141;
double atom6144;
double atom6146;
double atom5529;
double atom5530;
double atom6152;
double atom6153;
double atom6192;
double atom6207;
double atom6228;
double atom6230;
double atom6210;
double atom5917;
double atom5920;
double atom6174;
double atom6218;
double atom5806;
double atom5805;
double atom5802;
double atom5803;
double atom6233;
double atom6155;
double atom5809;
double atom5807;
double atom6188;
double atom5680;
double atom5677;
double atom5676;
double atom5679;
double atom6244;
double atom5683;
double atom5681;
double atom6266;
double atom6268;
double atom6445;
double atom6446;
double atom6426;
double atom6434;
double atom5465;
double atom5475;
double atom5753;
double atom5743;
double atom5971;
double atom5981;
double atom6322;
double atom5976;
double atom6311;
double atom5857;
double atom5862;
double atom6386;
double atom6387;
double atom5748;
double atom5867;
double atom6279;
double atom6290;
double atom6325;
double atom6361;
double atom5591;
double atom5622;
double atom5595;
double atom5600;
double atom6398;
double atom5587;
double atom5627;
double atom5590;
double atom6338;
double atom6346;
double atom6455;
double atom5470;
double atom5633;
double atom6483;

double * _Qrec = NULL;
void Init_Qrec ( ) 
{
    _Qrec = malloc ( Qrec_n_rows * Qrec_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Qrec_n_rows * Qrec_n_cols ; i++ ) {_Qrec[i]=0.0;}
  }
}

void Done_Qrec ( ) 
{
if (_Qrec != NULL) 
free (_Qrec ); 
_Qrec = NULL; 
}


double * Qrec ()
{
if ( _Qrec == NULL )
 {
    _Qrec = malloc ( Qrec_n_rows * Qrec_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Qrec_n_rows * Qrec_n_cols ; i++ ) {_Qrec[i]=0.0;}
  }
 }

atom35 = cos(a2);
atom57 =  a3+a2;
atom59 = sin(atom57);
atom58 = cos(atom57);
atom36 = sin(a2);
atom3537 = -atom35*da1;
atom3610 =  atom58*atom36-atom35*atom59;
atom3538 = atom36*da1;
atom3607 =  atom59*atom36+atom58*atom35;
atom5508 = -atom3537*atom3610-atom3538*atom3607;
atom80 = cos(a4);
atom888 = da3;
atom81 = sin(a4);
atom5512 =  atom888+da2;
atom5660 =  atom5508*atom80+atom81*atom5512;
atom115 = sin(a5);
atom5511 =  atom3607*atom3537-atom3538*atom3610;
atom114 = cos(a5);
atom5664 =  da4-atom5511;
atom5789 = -atom114*atom5664-atom5660*atom115;
atom5663 =  atom5512*atom80-atom81*atom5508;
atom152 = cos(a6);
atom5790 =  da5+atom5663;
atom5786 = -atom115*atom5664+atom114*atom5660;
atom153 = sin(a6);
atom5904 = -atom5789+da6;
atom5903 =  atom152*atom5790-atom5786*atom153;
atom5416 = da2*atom3537;
atom5417 = da2*atom3538;
atom6124 =  atom5417*atom3607-atom888*atom5508+atom3610*atom5416;
atom6130 =  atom3607*atom5416-atom5417*atom3610+atom888*atom5511;
atom6161 =  da4*atom5663+atom80*atom6130;
atom6165 =  atom114*atom6161+atom5789*da5+atom115*atom6124;
atom6158 = -atom81*atom6130-atom5660*da4;
atom5923 = atom5904*atom5903;
atom6168 =  atom6158*atom153+da6*atom5903+atom152*atom6165;
atom5900 =  atom152*atom5786+atom5790*atom153;
atom6197 = -atom6161*atom115-da5*atom5786+atom114*atom6124;
atom5919 = atom5900*atom5903;
atom5921 = (atom5900*atom5900);
atom5916 = (atom5904*atom5904);
atom5423 = (atom3537*atom3537);
atom5528 = atom5512*atom5508;
atom6125 = -atom6124+atom5528;
atom5531 = atom5512*atom5511;
atom6131 =  atom5531+atom6130;
atom6120 = -r3*( atom5423+(atom3538*atom3538))+-2.0*atom5417*d3;
atom6134 =  atom6125*d4-atom6131*r4+atom6120;
atom5436 = atom35*g;
atom6139 = -atom3538*atom3537*d3+atom5436;
atom5435 = atom36*g;
atom6136 = -( atom5423+(da2*da2))*d3+atom5435;
atom5527 = atom5511*atom5508;
atom5524 = (atom5512*atom5512);
atom5525 = (atom5511*atom5511);
atom5526 = -atom5524-atom5525;
atom6141 =  atom6136*atom3607-atom6139*atom3610;
atom6144 =  atom5526*d4-atom5527*r4+atom6141;
atom6146 =  atom6144*atom80+atom81*atom6134;
atom5529 = (atom5508*atom5508);
atom5530 = -atom5529-atom5524;
atom6152 =  atom6136*atom3610+atom6139*atom3607;
atom6153 =  atom6152-atom5530*r4+atom5527*d4;
atom6192 =  atom114*atom6146+atom115*atom6153;
atom6207 =  atom6134*atom80-atom81*atom6144;
atom6228 = -atom6192*atom153+atom152*atom6207;
atom6230 = -my6*( atom5921+atom5916)+m6*atom6228+( atom5923-atom6168)*mz6-( atom6197-atom5919)*mx6;
atom6210 =  atom6192*atom152+atom153*atom6207;
atom5917 = (atom5903*atom5903);
atom5920 = atom5900*atom5904;
atom6174 = -atom6165*atom153-atom5900*da6+atom6158*atom152;
atom6218 =  m6*atom6210+my6*( atom6197+atom5919)-mx6*( atom5917+atom5916)+mz6*( atom5920+atom6174);
atom5806 = atom5786*atom5790;
atom5805 = atom5789*atom5786;
atom5802 = (atom5790*atom5790);
atom5803 = (atom5789*atom5789);
atom6233 = -( atom6158-atom5805)*my5+atom6192*m5-atom153*atom6230+mz5*( atom6197+atom5806)-( atom5802+atom5803)*mx5+atom152*atom6218;
atom6155 = -atom6146*atom115+atom114*atom6153;
atom5809 = atom5789*atom5790;
atom5807 = (atom5786*atom5786);
atom6188 =  ( atom5809-atom6165)*mz5+( atom5921+atom5917)*mz6+atom6155*m5+atom6155*m6-( atom5920-atom6174)*mx6-my6*( atom5923+atom6168)-( atom5807+atom5802)*my5+mx5*( atom6158+atom5805);
atom5680 = atom5660*atom5664;
atom5677 = (atom5663*atom5663);
atom5676 = (atom5664*atom5664);
atom5679 = atom5660*atom5663;
atom6244 = -atom115*atom6188+atom114*atom6233-( atom5677+atom5676)*mx4+atom6146*m4+mz4*( atom5680+atom6158)+my4*( atom6124+atom5679);
atom5683 = atom5664*atom5663;
atom5681 = (atom5660*atom5660);
atom6266 =  m4*atom6207-my4*( atom5676+atom5681)-mz5*( atom5807+atom5803)+( atom5809+atom6165)*my5+atom153*atom6218-( atom6124-atom5679)*mx4+m5*atom6207+mz4*( atom5683-atom6161)-( atom6197-atom5806)*mx5+atom152*atom6230;
atom6268 =  atom81*atom6244+atom6266*atom80;
atom6445 =  atom6244*atom80-atom81*atom6266;
atom6446 =  mz3*( atom6124+atom5528)+atom5526*mx3+m3*atom6141+my3*atom5527+atom6445;
atom6426 = -atom114*atom6188-atom115*atom6233-mz4*( atom5677+atom5681)-m4*atom6153+( atom5680-atom6158)*mx4+( atom5683+atom6161)*my4;
atom6434 =  atom6152*m3+atom5527*mx3+( atom5531-atom6130)*mz3-atom6426+my3*atom5530;
atom5465 = -atom3538*Ixx2+Ixz2*da2+atom3537*Ixy2;
atom5475 =  Izz2*da2-Ixz2*atom3538+Izz2*atom3537;
atom5753 =  Izz4*atom5664+Izz4*atom5663+atom5660*Ixz4;
atom5743 =  Ixy4*atom5663+atom5660*Ixx4+Ixz4*atom5664;
atom5971 =  Ixz6*atom5904+Ixy6*atom5903+atom5900*Ixx6;
atom5981 =  Izz6*atom5903+Izz6*atom5904+atom5900*Ixz6;
atom6322 = -atom6197*Iyz6+Ixy6*atom6168+Iyy6*atom6174+mz6*atom6210-atom5900*atom5981+atom6155*mx6+atom5971*atom5904;
atom5976 =  Iyy6*atom5903+Ixy6*atom5900+atom5904*Iyz6;
atom6311 = -mz6*atom6228+atom5981*atom5903-Ixz6*atom6197+Ixx6*atom6168-my6*atom6155-atom5904*atom5976+Ixy6*atom6174;
atom5857 =  Ixz5*atom5790+atom5789*Ixy5+Ixx5*atom5786;
atom5862 =  atom5790*Iyz5+atom5786*Ixy5+atom5789*Iyy5;
atom6386 = -atom5789*atom5857-atom6192*my5+atom6155*mx5+atom6311*atom153+atom152*atom6322+atom5862*atom5786+Ixz5*atom6165+Izz5*atom6197+Izz5*atom6158;
atom6387 =  Ixy4*atom6161-atom6124*Iyz4+atom6146*mz4-atom5660*atom5753+atom6158*Iyy4+atom6153*mx4+atom6386+atom5664*atom5743;
atom5748 =  Ixy4*atom5660+atom5664*Iyz4+Iyy4*atom5663;
atom5867 =  Ixz5*atom5786+Izz5*atom5790+atom5789*Izz5;
atom6279 =  Ixz6*atom6168-Izz6*atom6197-atom5971*atom5903-my6*atom6210+atom5900*atom5976+Izz6*atom6174+atom6228*mx6;
atom6290 =  mz5*atom6192-atom5867*atom5786+atom5857*atom5790-atom6279+atom6165*Ixy5+atom6197*Iyy5+atom6158*Iyz5-mx5*atom6207;
atom6325 =  atom6207*my5+atom5789*atom5867+atom6197*Ixy5+atom6165*Ixx5-atom5862*atom5790+Ixz5*atom6158+atom6311*atom152-atom6155*mz5-atom6322*atom153;
atom6361 =  atom114*atom6325-Ixz4*atom6124-my4*atom6153+Ixy4*atom6158+atom5753*atom5663-atom115*atom6290-atom5748*atom5664+atom6161*Ixx4-mz4*atom6207;
atom5591 = atom5508*Ixy3;
atom5622 = -atom5591+atom5511*Ixx3;
atom5595 =  atom5512*Iyz3+atom5591+atom5511*Iyy3;
atom5600 =  Ixz3*atom5508+atom5512*Izz3+Izz3*atom5511;
atom6398 = -atom5512*atom5595-atom6152*mz3+my3*atom6120+atom5511*atom5600+atom6361*atom80+da3*atom5622-atom6268*r4-atom81*atom6387+atom5622*da2;
atom5587 = atom5511*Ixy3;
atom5627 = -atom5508*Iyy3+atom5587;
atom5590 =  atom5512*Ixz3+atom5508*Ixx3+atom5587;
atom6338 = -atom5663*atom5743+Izz4*atom6158-atom115*atom6325+atom5660*atom5748+mx4*atom6207+Ixz4*atom6161-atom114*atom6290-my4*atom6146-Izz4*atom6124;
atom6346 =  mz3*atom6141-atom6268*d4-atom6120*mx3-atom6338+da2*atom5627-atom5508*atom5600+atom5512*atom5590+da3*atom5627;
atom6455 = -atom6446*atom3610+atom6434*atom3607;
atom5470 =  Iyy2*atom3537-atom3538*Ixy2+da2*Iyz2;
atom5633 =  Ixz3*atom5511-Izz3*atom5508;
atom6483 =  da2*atom5633-my3*atom6141+atom81*atom6361+da3*atom5633+atom5508*atom5595+atom6152*mx3-atom5590*atom5511+r4*atom6445-d4*atom6426+atom6387*atom80;

_Qrec[0] = -atom36*( Ixx2*atom5416+atom5475*atom3537+atom5417*Ixy2-r3*atom6455+atom3610*atom6346-mz2*atom5436-atom5470*da2+atom3607*atom6398)-atom35*( atom5465*da2+atom5475*atom3538+atom3607*atom6346+atom5416*Ixy2+Iyy2*atom5417+mz2*atom5435+r3*( atom6446*atom3607+atom6434*atom3610)-atom6398*atom3610-( atom6268+atom6125*mx3-mz3*( atom5529+atom5525)+my3*atom6131+atom6120*m3)*d3);
_Qrec[1] =  d3*atom6455-atom5470*atom3538+atom6483-atom5465*atom3537+Ixz2*atom5416-my2*atom5435+atom5436*mx2+Izz2*atom5417;
_Qrec[2] = atom6483;
_Qrec[3] = atom6338;
_Qrec[4] = atom6386;
_Qrec[5] = atom6279;

return _Qrec;
}
