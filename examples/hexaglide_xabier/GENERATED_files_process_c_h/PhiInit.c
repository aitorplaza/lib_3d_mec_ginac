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

double atom39;
double atom41;
double atom49;
double atom40;
double atom50;
double atom1372;
double atom1373;
double atom43;
double atom42;
double atom44;
double atom45;
double atom56;
double atom53;
double atom1376;
double atom1375;
double atom47;
double atom62;
double atom59;
double atom1379;
double atom1378;
double atom0;
double atom1;
double atom3;
double atom2;
double atom4;
double atom5;
double atom7;
double atom6;
double atom8;
double atom1396;
double atom1397;
double atom1408;
double atom1410;
double atom1400;
double atom1399;
double atom1403;
double atom1402;
double atom9;
double atom10;
double atom1415;
double atom1416;
double atom1419;
double atom1418;
double atom1421;
double atom1422;
double atom213;
double atom214;
double atom215;
double atom1438;
double atom1439;
double atom1441;
double atom1442;

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

atom39 = cos(c);
atom41 = cos(b);
atom49 = atom39*atom41;
atom40 = sin(c);
atom50 = -atom40*atom41;
atom1372 = atom49*r;
atom1373 = e*atom50;
atom43 = cos(a);
atom42 = sin(b);
atom44 = sin(a);
atom45 = atom42*atom44;
atom56 =  atom43*atom39-atom40*atom45;
atom53 =  atom43*atom40+atom39*atom45;
atom1376 = e*atom56;
atom1375 = r*atom53;
atom47 = -atom42*atom43;
atom62 = -atom40*atom47+atom39*atom44;
atom59 =  atom39*atom47+atom44*atom40;
atom1379 = atom62*e;
atom1378 = atom59*r;
atom0 = 2.0*alfa;
atom1 = sin(atom0);
atom3 = cos(atom0);
atom2 = -e*atom1;
atom4 = atom3*r;
atom5 =  atom2+atom4;
atom7 = r*atom1;
atom6 = atom3*e;
atom8 =  atom7+atom6;
atom1396 = atom5*atom49;
atom1397 = atom8*atom50;
atom1408 = atom3*R;
atom1410 = R*atom1;
atom1400 = atom8*atom56;
atom1399 = atom5*atom53;
atom1403 = atom62*atom8;
atom1402 = atom5*atom59;
atom9 = -atom2+atom4;
atom10 =  atom7-atom6;
atom1415 = atom49*atom9;
atom1416 = atom10*atom50;
atom1419 = atom10*atom56;
atom1418 = atom9*atom53;
atom1421 = atom59*atom9;
atom1422 = atom10*atom62;
atom213 = 4.0000000000000000e+00*alfa;
atom214 = cos(atom213);
atom215 = sin(atom213);
atom1438 = atom214*R;
atom1439 = -e*atom215;
atom1441 = atom215*R;
atom1442 = atom214*e;

_PhiInit[0] =  atom1372+x-R+atom1373;
_PhiInit[1] =  y-e+atom1376+atom1375;
_PhiInit[2] = -s1+z+atom1379+atom1378;
_PhiInit[3] =  atom1372+x-R-atom1373;
_PhiInit[4] =  y+e-atom1376+atom1375;
_PhiInit[5] =  z-atom1379+atom1378-s2;
_PhiInit[6] =  atom1396-atom2-atom1408+x+atom1397;
_PhiInit[7] =  y-atom1410+atom1400-atom6+atom1399;
_PhiInit[8] =  atom1403+z+atom1402-s3;
_PhiInit[9] =  atom2+atom1415-atom1408+x+atom1416;
_PhiInit[10] =  atom1419+y-atom1410+atom6+atom1418;
_PhiInit[11] =  z+atom1421-s4+atom1422;
_PhiInit[12] =  atom1415+x-atom1438-atom1416-atom1439;
_PhiInit[13] = -atom1419+y-atom1441+atom1418-atom1442;
_PhiInit[14] =  z+atom1421-s5-atom1422;
_PhiInit[15] =  atom1396+x-atom1438-atom1397+atom1439;
_PhiInit[16] =  y-atom1441-atom1400+atom1442+atom1399;
_PhiInit[17] = -atom1403+z+atom1402-s6;

return _PhiInit;
}
