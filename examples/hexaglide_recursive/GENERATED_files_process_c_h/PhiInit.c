/*----------PhiInit.c lib3D_MEC exported-----------*/

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

#include "PhiInit.h"

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

double atom39;
double atom37;
double atom47;
double atom38;
double atom48;
double atom1368;
double atom1369;
double atom79;
double atom41;
double atom42;
double atom40;
double atom43;
double atom54;
double atom51;
double atom1372;
double atom1371;
double atom45;
double atom60;
double atom57;
double atom1375;
double atom1374;
double atom103;
double atom1;
double atom0;
double atom2;
double atom3;
double atom4;
double atom5;
double atom6;
double atom1404;
double atom1405;
double atom1419;
double atom127;
double atom131;
double atom1420;
double atom1408;
double atom1407;
double atom1411;
double atom1410;
double atom1446;
double atom168;
double atom1447;
double atom8;
double atom7;
double atom1432;
double atom1431;
double atom1435;
double atom1434;
double atom1437;
double atom1438;
double atom1467;
double atom208;
double atom1468;
double atom248;
double atom1489;
double atom1488;

double * _PhiInit = NULL;
void Init_PhiInit ( ) 
{
    _PhiInit = malloc ( PhiInit_n_rows * PhiInit_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < PhiInit_n_rows * PhiInit_n_cols ; i++ ) {_PhiInit[i]=0.0;}
  }
}

void Done_PhiInit ( ) 
{
if (_PhiInit != NULL) 
free (_PhiInit ); 
_PhiInit = NULL; 
}


double * PhiInit ()
{
if ( _PhiInit == NULL )
 {
    _PhiInit = malloc ( PhiInit_n_rows * PhiInit_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < PhiInit_n_rows * PhiInit_n_cols ; i++ ) {_PhiInit[i]=0.0;}
  }
 }

atom39 = cos(b);
atom37 = cos(c);
atom47 = atom39*atom37;
atom38 = sin(c);
atom48 = -atom38*atom39;
atom1368 = atom47*r;
atom1369 = atom48*e;
atom79 = cos(b1);
atom41 = cos(a);
atom42 = sin(a);
atom40 = sin(b);
atom43 = atom42*atom40;
atom54 =  atom41*atom37-atom38*atom43;
atom51 =  atom43*atom37+atom41*atom38;
atom1372 = atom54*e;
atom1371 = r*atom51;
atom45 = -atom41*atom40;
atom60 = -atom38*atom45+atom42*atom37;
atom57 =  atom45*atom37+atom42*atom38;
atom1375 = atom60*e;
atom1374 = atom57*r;
atom103 = cos(b2);
atom1 = pow(3.0,(1.0/2.0));
atom0 = -(1.0/2.0)*r;
atom2 = (1.0/2.0)*e*atom1;
atom3 =  atom0+atom2;
atom4 = -(1.0/2.0)*r*atom1;
atom5 = -(1.0/2.0)*e;
atom6 =  atom4+atom5;
atom1404 = atom47*atom3;
atom1405 = atom6*atom48;
atom1419 = -sin(b3)*L+R;
atom127 = cos(b3);
atom131 = (1.0/2.0)*atom1;
atom1420 =  e+atom127*L*sin(a3);
atom1408 = atom6*atom54;
atom1407 = atom3*atom51;
atom1411 = atom60*atom6;
atom1410 = atom57*atom3;
atom1446 =  R-sin(b4)*L;
atom168 = cos(b4);
atom1447 =  L*atom168*sin(a4)-e;
atom8 =  atom4-atom5;
atom7 =  atom0-atom2;
atom1432 = atom8*atom48;
atom1431 = atom47*atom7;
atom1435 = atom8*atom54;
atom1434 = atom7*atom51;
atom1437 = atom7*atom57;
atom1438 = atom60*atom8;
atom1467 = -sin(b5)*L+R;
atom208 = cos(b5);
atom1468 =  sin(a5)*L*atom208+e;
atom248 = cos(b6);
atom1489 =  sin(a6)*L*atom248-e;
atom1488 = -L*sin(b6)+R;

_PhiInit[0] =  atom1368+atom1369+sin(b1)*L+x-R;
_PhiInit[1] =  atom1372-L*sin(a1)*atom79+y+atom1371-e;
_PhiInit[2] =  atom1375+atom1374-s1+z+L*cos(a1)*atom79;
_PhiInit[3] =  atom1368+sin(b2)*L-atom1369+x-R;
_PhiInit[4] = -L*sin(a2)*atom103-atom1372+y+atom1371+e;
_PhiInit[5] = -atom1375-s2+atom1374+z+L*cos(a2)*atom103;
_PhiInit[6] =  atom1404+atom1419/2.0+atom131*atom1420+x+atom1405;
_PhiInit[7] =  atom1408+y+atom1407+atom1420/2.0-atom131*atom1419;
_PhiInit[8] =  atom127*L*cos(a3)-s3+atom1411+z+atom1410;
_PhiInit[9] =  atom1446/2.0+x+atom1432+atom131*atom1447+atom1431;
_PhiInit[10] =  atom1435+y-atom131*atom1446+atom1434+atom1447/2.0;
_PhiInit[11] = -s4+L*cos(a4)*atom168+atom1437+z+atom1438;
_PhiInit[12] =  atom1467/2.0+x-atom131*atom1468-atom1432+atom1431;
_PhiInit[13] = -atom1435+atom131*atom1467+y+atom1434+atom1468/2.0;
_PhiInit[14] = -s5+atom1437+z+cos(a5)*L*atom208-atom1438;
_PhiInit[15] = -atom131*atom1489+atom1404+atom1488/2.0+x-atom1405;
_PhiInit[16] =  atom1489/2.0-atom1408+y+atom131*atom1488+atom1407;
_PhiInit[17] = -atom1411+z+cos(a6)*L*atom248+atom1410-s6;

return _PhiInit;
}
