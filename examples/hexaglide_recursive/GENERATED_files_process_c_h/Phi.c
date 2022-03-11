/*----------Phi.c lib3D_MEC exported-----------*/

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

#include "Phi.h"

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
double atom48;
double atom37;
double atom47;
double atom2692;
double atom2691;
double atom79;
double atom41;
double atom40;
double atom42;
double atom43;
double atom54;
double atom51;
double atom2695;
double atom2694;
double atom45;
double atom57;
double atom60;
double atom2697;
double atom2698;
double atom103;
double atom1;
double atom0;
double atom2;
double atom3;
double atom4;
double atom5;
double atom6;
double atom2727;
double atom2728;
double atom127;
double atom131;
double atom2743;
double atom2742;
double atom2730;
double atom2731;
double atom2734;
double atom2733;
double atom8;
double atom7;
double atom2755;
double atom2754;
double atom168;
double atom2770;
double atom2769;
double atom2757;
double atom2758;
double atom2761;
double atom2760;
double atom208;
double atom2791;
double atom2790;
double atom248;
double atom2812;
double atom2811;

double * _Phi = NULL;
void Init_Phi ( ) 
{
    _Phi = malloc ( Phi_n_rows * Phi_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Phi_n_rows * Phi_n_cols ; i++ ) {_Phi[i]=0.0;}
  }
}

void Done_Phi ( ) 
{
if (_Phi != NULL) 
free (_Phi ); 
_Phi = NULL; 
}


double * Phi ()
{
if ( _Phi == NULL )
 {
    _Phi = malloc ( Phi_n_rows * Phi_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Phi_n_rows * Phi_n_cols ; i++ ) {_Phi[i]=0.0;}
  }
 }

atom38 = sin(c);
atom39 = cos(b);
atom48 = -atom38*atom39;
atom37 = cos(c);
atom47 = atom37*atom39;
atom2692 = e*atom48;
atom2691 = atom47*r;
atom79 = cos(b1);
atom41 = cos(a);
atom40 = sin(b);
atom42 = sin(a);
atom43 = atom40*atom42;
atom54 = -atom38*atom43+atom37*atom41;
atom51 =  atom41*atom38+atom37*atom43;
atom2695 = e*atom54;
atom2694 = r*atom51;
atom45 = -atom40*atom41;
atom57 =  atom37*atom45+atom42*atom38;
atom60 = -atom38*atom45+atom37*atom42;
atom2697 = atom57*r;
atom2698 = e*atom60;
atom103 = cos(b2);
atom1 = pow(3.0,(1.0/2.0));
atom0 = -(1.0/2.0)*r;
atom2 = (1.0/2.0)*e*atom1;
atom3 =  atom0+atom2;
atom4 = -(1.0/2.0)*e;
atom5 = -(1.0/2.0)*atom1*r;
atom6 =  atom4+atom5;
atom2727 = atom47*atom3;
atom2728 = atom6*atom48;
atom127 = cos(b3);
atom131 = (1.0/2.0)*atom1;
atom2743 =  e+atom127*sin(a3)*L;
atom2742 =  R-L*sin(b3);
atom2730 = atom3*atom51;
atom2731 = atom6*atom54;
atom2734 = atom60*atom6;
atom2733 = atom57*atom3;
atom8 = -atom4+atom5;
atom7 =  atom0-atom2;
atom2755 = atom8*atom48;
atom2754 = atom47*atom7;
atom168 = cos(b4);
atom2770 = -e+atom168*sin(a4)*L;
atom2769 =  R-L*sin(b4);
atom2757 = atom7*atom51;
atom2758 = atom8*atom54;
atom2761 = atom60*atom8;
atom2760 = atom7*atom57;
atom208 = cos(b5);
atom2791 =  e+atom208*sin(a5)*L;
atom2790 =  R-sin(b5)*L;
atom248 = cos(b6);
atom2812 = -e+sin(a6)*L*atom248;
atom2811 =  R-sin(b6)*L;

_Phi[0] = -R+atom2692+L*sin(b1)+x+atom2691;
_Phi[1] = -e+atom2695+atom2694-atom79*sin(a1)*L+y;
_Phi[2] =  atom2697+atom79*L*cos(a1)+z-s1+atom2698;
_Phi[3] = -R-atom2692+L*sin(b2)+x+atom2691;
_Phi[4] =  e-atom2695+atom2694-atom103*L*sin(a2)+y;
_Phi[5] =  atom103*L*cos(a2)+atom2697-s2+z-atom2698;
_Phi[6] =  atom131*atom2743+atom2727+atom2742/2.0+x+atom2728;
_Phi[7] =  atom2730-atom131*atom2742+atom2743/2.0+y+atom2731;
_Phi[8] = -s3+atom2734+atom127*L*cos(a3)+z+atom2733;
_Phi[9] =  atom2770*atom131+atom2755+atom2769/2.0+atom2754+x;
_Phi[10] =  atom2770/2.0+atom2757+atom2758+y-atom131*atom2769;
_Phi[11] =  atom2761-s4+atom2760+z+atom168*L*cos(a4);
_Phi[12] = -atom2755+atom2790/2.0-atom131*atom2791+atom2754+x;
_Phi[13] =  atom2757+atom2790*atom131-atom2758+atom2791/2.0+y;
_Phi[14] = -atom2761-s5+atom2760+z+atom208*L*cos(a5);
_Phi[15] = -atom2812*atom131+atom2727+atom2811/2.0+x-atom2728;
_Phi[16] =  atom2812/2.0+atom2730+y-atom2731+atom131*atom2811;
_Phi[17] = -s6-atom2734+L*atom248*cos(a6)+z+atom2733;

return _Phi;
}
