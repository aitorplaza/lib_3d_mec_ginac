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

double atom241;
double atom279;
double atom240;
double atom244;
double atom0;
double atom1;
double atom43;
double atom42;
double atom295;
double atom298;
double atom317;
double atom318;
double atom320;

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

atom241 = -cos(theta2)*l1;
atom279 =  l2-atom241;
atom240 = sin(theta2)*l1;
atom244 = -m2*atom241*cg2x+m2*atom240*cg2z;
atom0 = cos(theta3);
atom1 = sin(theta3);
atom43 = cg3z*m3;
atom42 = cg3x*m3;
atom295 =  ( atom1*atom279+atom0*atom240)*atom43+atom42*( atom0*atom279-atom1*atom240);
atom298 =  l2*atom0*atom42+l2*atom1*atom43;
atom317 = -atom298-I2yy-I3yy-l2*m3*atom279-atom244-atom295;
atom318 = -I3yy-atom295;
atom320 = -atom298-I3yy;

_M[0] = -I2yy-( (atom240*atom240)+(atom279*atom279))*m3-I3yy+-2.0*atom244-I1yy+-2.0*atom295-m2*(l1*l1);
_M[1] = atom317;
_M[2] = atom318;
_M[3] = atom317;
_M[4] =  -2.0*atom298-I2yy-I3yy-(l2*l2)*m3;
_M[5] = atom320;
_M[6] = atom318;
_M[7] = atom320;
_M[8] = -I3yy;

return _M;
}
