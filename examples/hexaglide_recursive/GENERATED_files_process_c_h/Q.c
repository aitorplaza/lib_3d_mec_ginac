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
double atom3748;
double atom38;
double atom39;
double atom3749;
double atom48;
double atom3870;
double atom3747;
double atom37;
double atom47;
double atom3873;
double atom3876;
double atom288;
double atom42;
double atom41;
double atom45;
double atom60;
double atom57;
double atom46;
double atom417;
double atom75;
double atom44;
double atom43;
double atom54;
double atom51;
double atom70;
double atom418;
double atom289;
double atom295;
double atom292;
double atom65;
double atom3879;
double atom3882;
double atom3885;
double atom3891;
double atom3894;
double atom3888;
double atom76;
double atom77;
double atom2856;
double atom3756;
double atom3938;
double atom3758;
double atom3751;
double atom3752;
double atom3753;
double atom3755;
double atom3937;
double atom3768;
double atom3760;
double atom3762;
double atom3774;
double atom3779;
double atom3763;
double atom3781;
double atom3777;
double atom3765;
double atom3771;
double atom3992;
double atom79;
double atom80;
double atom970;
double atom4004;
double atom976;
double atom82;
double atom81;
double atom104;
double atom103;
double atom1264;
double atom4104;
double atom1270;
double atom106;
double atom105;
double atom127;
double atom128;
double atom1579;
double atom1585;
double atom4204;
double atom130;
double atom131;
double atom133;
double atom129;
double atom132;
double atom154;
double atom166;
double atom135;
double atom134;
double atom159;
double atom165;
double atom169;
double atom168;
double atom1897;
double atom1913;
double atom4318;
double atom171;
double atom173;
double atom170;
double atom172;
double atom194;
double atom206;
double atom175;
double atom174;
double atom199;
double atom205;
double atom209;
double atom211;
double atom208;
double atom213;
double atom210;
double atom212;
double atom234;
double atom246;
double atom215;
double atom214;
double atom239;
double atom245;
double atom2218;
double atom2226;
double atom4432;
double atom249;
double atom251;
double atom248;
double atom255;
double atom250;
double atom254;
double atom279;
double atom285;
double atom252;
double atom253;
double atom274;
double atom286;
double atom2529;
double atom2535;
double atom4546;
double atom89;
double atom113;
double atom4041;
double atom86;
double atom110;
double atom4141;
double atom4255;
double atom149;
double atom1426;
double atom1744;
double atom189;
double atom4369;
double atom229;
double atom4483;
double atom2060;
double atom2376;
double atom269;
double atom4597;

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

atom40 = sin(b);
atom3748 = atom40*da;
atom38 = sin(c);
atom39 = cos(b);
atom3749 =  atom3748+dc;
atom48 = -atom38*atom39;
atom3870 = -atom40*dB+atom3749*atom48;
atom3747 = atom39*da;
atom37 = cos(c);
atom47 = atom37*atom39;
atom3873 = -atom3749*atom47+atom3747*atom40;
atom3876 =  atom47*dB-atom3747*atom48;
atom288 = atom40*dc;
atom42 = sin(a);
atom41 = cos(a);
atom45 = -atom40*atom41;
atom60 = -atom38*atom45+atom37*atom42;
atom57 =  atom37*atom45+atom42*atom38;
atom46 = atom41*atom39;
atom417 = atom288*atom42;
atom75 =  atom57*mxP+atom60*myP+mzP*atom46;
atom44 = -atom42*atom39;
atom43 = atom40*atom42;
atom54 = -atom38*atom43+atom37*atom41;
atom51 =  atom41*atom38+atom37*atom43;
atom70 =  mzP*atom44+mxP*atom51+myP*atom54;
atom418 = -atom41*atom288;
atom289 = dc*atom39;
atom295 =  atom42*dB+atom289*atom41;
atom292 =  atom41*dB-atom289*atom42;
atom65 =  atom47*mxP+myP*atom48+mzP*atom40;
atom3879 = -atom44*dB+atom3749*atom54;
atom3882 =  atom3747*atom44-atom3749*atom51;
atom3885 = -atom3747*atom54+dB*atom51;
atom3891 =  atom3747*atom46-atom3749*atom57;
atom3894 = -atom3747*atom60+atom57*dB;
atom3888 = -atom46*dB+atom3749*atom60;
atom76 = -atom70*g;
atom77 = atom65*g;
atom2856 =  atom40*atom76+atom44*atom77;
atom3756 = atom37*IxzP;
atom3938 = atom3747*dB;
atom3758 = -atom38*IyzP+atom3756;
atom3751 = -atom38*IxyP;
atom3752 =  atom3751+atom37*IxxP;
atom3753 = atom37*IxyP;
atom3755 = -atom38*IyyP+atom3753;
atom3937 = -atom3748*dB;
atom3768 = -atom3755*atom38+atom37*atom3752;
atom3760 =  IxxP*atom38+atom3753;
atom3762 = -atom3751+atom37*IyyP;
atom3774 = -atom3762*atom38+atom3760*atom37;
atom3779 = -IzzP*atom38+atom3756;
atom3763 = IxzP*atom38;
atom3781 =  atom3763+atom37*IzzP;
atom3777 =  atom37*atom3762+atom3760*atom38;
atom3765 =  atom3763+atom37*IyzP;
atom3771 =  atom3752*atom38+atom37*atom3755;
atom3992 = -atom3749*( dB*atom3758-atom3747*atom3765)-atom3747*( atom3768*dB-atom3747*atom3774)+IzzP*atom3938+atom3937*atom3779+( atom3747*atom3777-atom3771*dB)*dB;
atom79 = cos(b1);
atom80 = sin(b1);
atom970 = atom79*Izz1;
atom4004 = -atom79*( atom80*Ixx1-atom79*Ixz1)-atom80*( Ixz1*atom80-atom970);
atom976 =  atom970-atom80*Ixy1;
atom82 = sin(a1);
atom81 = cos(a1);
atom104 = sin(b2);
atom103 = cos(b2);
atom1264 = atom103*Izz2;
atom4104 = -atom103*( atom104*Ixx2-atom103*Ixz2)+atom104*( atom1264-atom104*Ixz2);
atom1270 = -atom104*Ixy2+atom1264;
atom106 = sin(a2);
atom105 = cos(a2);
atom127 = cos(b3);
atom128 = sin(b3);
atom1579 = Izz3*atom127;
atom1585 =  atom1579-Ixy3*atom128;
atom4204 =  atom128*( atom1579-atom128*Ixz3)+atom127*( atom127*Ixz3-atom128*Ixx3);
atom130 = sin(a3);
atom131 = (1.0/2.0)*pow(3.0,(1.0/2.0));
atom133 = atom130*atom131;
atom129 = cos(a3);
atom132 = -atom131*atom129;
atom154 = -( atom127+2.0*atom128*atom133)*mx3/2.0-mz3*( atom128+-2.0*atom127*atom133)/2.0+my3*atom132;
atom166 = g*atom154;
atom135 = (1.0/2.0)*atom130;
atom134 = -(1.0/2.0)*atom129;
atom159 =  ( atom127*atom135+atom131*atom128)*mz3+( atom131*atom127-atom135*atom128)*mx3+my3*atom134;
atom165 = -atom159*g;
atom169 = sin(b4);
atom168 = cos(b4);
atom1897 = atom168*Izz4;
atom1913 = -Ixy4*atom169+atom1897;
atom4318 = -atom168*( atom169*Ixx4-atom168*Ixz4)-atom169*( atom169*Ixz4-atom1897);
atom171 = sin(a4);
atom173 = atom131*atom171;
atom170 = cos(a4);
atom172 = -atom131*atom170;
atom194 = -mx4*( 2.0*atom173*atom169+atom168)/2.0+my4*atom172-mz4*( atom169+-2.0*atom168*atom173)/2.0;
atom206 = g*atom194;
atom175 = (1.0/2.0)*atom171;
atom174 = -(1.0/2.0)*atom170;
atom199 =  my4*atom174-mx4*( atom175*atom169-atom168*atom131)+( atom131*atom169+atom168*atom175)*mz4;
atom205 = -atom199*g;
atom209 = sin(b5);
atom211 = sin(a5);
atom208 = cos(b5);
atom213 = -atom131*atom211;
atom210 = cos(a5);
atom212 = atom131*atom210;
atom234 = -mx5*( atom208+2.0*atom209*atom213)/2.0+my5*atom212-( atom209+-2.0*atom208*atom213)*mz5/2.0;
atom246 = g*atom234;
atom215 = (1.0/2.0)*atom211;
atom214 = -(1.0/2.0)*atom210;
atom239 = -mx5*( atom208*atom131+atom209*atom215)+atom214*my5-mz5*( atom131*atom209-atom208*atom215);
atom245 = -atom239*g;
atom2218 = atom208*Izz5;
atom2226 =  atom2218-atom209*Ixy5;
atom4432 =  atom208*( atom208*Ixz5-Ixx5*atom209)+( atom2218-atom209*Ixz5)*atom209;
atom249 = sin(b6);
atom251 = sin(a6);
atom248 = cos(b6);
atom255 = (1.0/2.0)*atom251;
atom250 = cos(a6);
atom254 = -(1.0/2.0)*atom250;
atom279 =  my6*atom254-( atom249*atom131-atom248*atom255)*mz6-( atom131*atom248+atom249*atom255)*mx6;
atom285 = -atom279*g;
atom252 = atom131*atom250;
atom253 = -atom131*atom251;
atom274 =  mz6*( 2.0*atom253*atom248-atom249)/2.0+my6*atom252-( 2.0*atom249*atom253+atom248)*mx6/2.0;
atom286 = atom274*g;
atom2529 = Izz6*atom248;
atom2535 = -atom249*Ixy6+atom2529;
atom4546 =  ( Ixz6*atom248-atom249*Ixx6)*atom248-atom249*( atom249*Ixz6-atom2529);
atom89 =  atom79*mx1+mz1*atom80;
atom113 =  atom103*mx2+mz2*atom104;
atom4041 = -da1*atom82-atom80*dB1*atom81;
atom86 = atom79*atom81;
atom110 = atom103*atom105;
atom4141 = -atom104*dB2*atom105-da2*atom106;
atom4255 = -dB3*atom128*atom129-atom130*da3;
atom149 = atom127*atom129;
atom1426 = atom130*dB3;
atom1744 = dB4*atom171;
atom189 = atom168*atom170;
atom4369 = -da4*atom171-dB4*atom169*atom170;
atom229 = atom208*atom210;
atom4483 = -dB5*atom209*atom210-atom211*da5;
atom2060 = dB5*atom211;
atom2376 = dB6*atom251;
atom269 = atom250*atom248;
atom4597 = -atom249*dB6*atom250-atom251*da6;

_Q[0] = -( atom70*atom418-atom417*atom75)*dB+mzP*( atom3870*dB-atom3873*atom3747)-( atom3876*dB-atom3873*atom3749)*mxP+myP*( atom3747*atom3876-atom3870*atom3749)-( atom292*atom70+atom75*atom295)*da;
_Q[1] = -mzP*( atom3747*atom3882-atom3879*dB)-( atom3879*atom3749-atom3747*atom3885)*myP-mxP*( atom3885*dB-atom3749*atom3882)+atom65*atom292*da+( atom65*atom418-atom289*atom75)*dB;
_Q[2] = -( atom3749*atom3888-atom3747*atom3894)*myP+atom65*atom295*da-mzP*( atom3747*atom3891-dB*atom3888)+( atom289*atom70-atom417*atom65)*dB+mP*g+( atom3749*atom3891-atom3894*dB)*mxP;
_Q[3] = -atom39*( atom39*atom76+atom77*atom43)+atom40*atom3992-( ( atom3749*atom3765-IzzP*dB)*atom3749-atom3747*( atom3779*dB-atom3749*atom3774)-atom3937*atom3768-atom3938*atom3758+( atom3749*atom3777-atom3781*dB)*dB)*atom39-atom2856*atom40;
_Q[4] =  atom3937*atom3774-( atom3747*atom3781-atom3749*atom3771)*dB+atom3749*( atom3749*atom3758-atom3747*IzzP)+atom3747*( atom3749*atom3768-atom3747*atom3779)+atom3765*atom3938-atom41*atom77;
_Q[5] = -atom2856+atom3992;
_Q[6] =  (dB1*dB1)*atom976+( atom81*my1+atom80*mx1*atom82-mz1*atom79*atom82)*g+atom4004*dB1*da1;
_Q[7] =  (dB2*dB2)*atom1270-( atom103*mz2*atom106-atom105*my2-atom104*mx2*atom106)*g+atom4104*dB2*da2;
_Q[8] = -atom131*atom166+(dB3*dB3)*atom1585+atom165/2.0+dB3*da3*atom4204;
_Q[9] =  atom4318*dB4*da4+atom1913*(dB4*dB4)+atom205/2.0-atom131*atom206;
_Q[10] =  atom4432*dB5*da5+atom131*atom246+atom245/2.0+(dB5*dB5)*atom2226;
_Q[11] =  dB6*atom4546*da6+atom285/2.0+(dB6*dB6)*atom2535+atom286*atom131;
_Q[12] = -dB1*atom976*da1-atom4004*(da1*da1)-g*atom81*atom89;
_Q[13] = -atom4104*(da2*da2)-dB2*da2*atom1270-g*atom105*atom113;
_Q[14] = -atom166*atom134-(da3*da3)*atom4204-atom165*atom132-dB3*atom1585*da3;
_Q[15] = -atom4318*(da4*da4)-atom1913*dB4*da4-atom206*atom174-atom172*atom205;
_Q[16] = -dB5*atom2226*da5-atom4432*(da5*da5)-atom212*atom245-atom214*atom246;
_Q[17] = -atom285*atom252-atom4546*(da6*da6)-dB6*da6*atom2535-atom286*atom254;
_Q[18] =  m1*g+dB1*da1*atom82*atom89+atom4041*da1*my1-mz1*( atom86*(da1*da1)+atom86*(dB1*dB1))-atom4041*mx1*dB1;
_Q[19] =  atom4141*da2*my2-dB2*atom4141*mx2+dB2*da2*atom113*atom106-mz2*( atom110*(dB2*dB2)+atom110*(da2*da2))+m2*g;
_Q[20] = -atom4255*dB3*mx3+my3*atom4255*da3+g*m3-( (dB3*dB3)*atom149+(da3*da3)*atom149)*mz3-( atom1426*atom154+-2.0*atom131*atom1426*atom159)*da3/2.0;
_Q[21] = -( atom1744*atom194+-2.0*atom131*atom199*atom1744)*da4/2.0+my4*atom4369*da4+g*m4-( (dB4*dB4)*atom189+(da4*da4)*atom189)*mz4-mx4*dB4*atom4369;
_Q[22] = -( atom229*(da5*da5)+atom229*(dB5*dB5))*mz5+g*m5-( 2.0*atom131*atom239*atom2060+atom2060*atom234)*da5/2.0-mx5*dB5*atom4483+atom4483*my5*da5;
_Q[23] = -dB6*atom4597*mx6-mz6*( atom269*(da6*da6)+atom269*(dB6*dB6))+my6*atom4597*da6-( atom274*atom2376+2.0*atom279*atom131*atom2376)*da6/2.0+g*m6;

return _Q;
}
