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

#define theta1 q[ 0 ]
#define theta2 q[ 1 ]
#define theta3 q[ 2 ]
#define dtheta1 dq[ 0 ]
#define dtheta2 dq[ 1 ]
#define dtheta3 dq[ 2 ]
#define ddtheta1 ddq[ 0 ]
#define ddtheta2 ddq[ 1 ]
#define ddtheta3 ddq[ 2 ]
#define g param[ 0 ]
#define l1 param[ 1 ]
#define l2 param[ 2 ]
#define l3 param[ 3 ]
#define l4 param[ 4 ]
#define m1 param[ 5 ]
#define m2 param[ 6 ]
#define m3 param[ 7 ]
#define cg1x param[ 8 ]
#define cg1z param[ 9 ]
#define cg2x param[ 10 ]
#define cg2z param[ 11 ]
#define cg3x param[ 12 ]
#define cg3z param[ 13 ]
#define I1yy param[ 14 ]
#define I2yy param[ 15 ]
#define I3yy param[ 16 ]
#define K param[ 17 ]
#define l2x param[ 18 ]
#define l2z param[ 19 ]
#define l3x param[ 20 ]
#define l3z param[ 21 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define Fx2 inputs[ 0 ]
#define Fz2 inputs[ 1 ]
#define Fx3 inputs[ 2 ]
#define Fz3 inputs[ 3 ]
#define My2 inputs[ 4 ]
#define My3 inputs[ 5 ]

double atom164;
double atom27;
double atom165;
double atom26;
double atom172;
double atom14;
double atom15;
double atom171;

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

atom164 = -sin(theta3)*l3;
atom27 = sin(theta2);
atom165 =  l2+l3*cos(theta3);
atom26 = cos(theta2);
atom172 =  atom165*atom26+l1+atom164*atom27;
atom14 = cos(theta1);
atom15 = sin(theta1);
atom171 = -atom165*atom27+atom164*atom26;

_PhiInit[0] =  atom15*atom171-l4+atom172*atom14;
_PhiInit[1] =  atom14*atom171-atom172*atom15;
_PhiInit[2] =  theta1+1.5708000000000000e+00;

return _PhiInit;
}
