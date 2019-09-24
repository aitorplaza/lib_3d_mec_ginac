/*----------Energy.c lib3D_MEC exported-----------*/

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

#include "Energy.h"

#define theta1 q[ 0 ]
#define theta2 q[ 1 ]
#define psi q[ 2 ]
#define y q[ 3 ]
#define z q[ 4 ]
#define dtheta1 dq[ 0 ]
#define dtheta2 dq[ 1 ]
#define dpsi dq[ 2 ]
#define dy dq[ 3 ]
#define dz dq[ 4 ]
#define ddtheta1 ddq[ 0 ]
#define ddtheta2 ddq[ 1 ]
#define ddpsi ddq[ 2 ]
#define ddy ddq[ 3 ]
#define ddz ddq[ 4 ]
#define g param[ 0 ]
#define theta1_0 param[ 1 ]
#define psi_0 param[ 2 ]
#define l1 param[ 3 ]
#define l2 param[ 4 ]
#define y0 param[ 5 ]
#define z0 param[ 6 ]
#define alpha param[ 7 ]
#define r param[ 8 ]
#define Cvis param[ 9 ]
#define mb1 param[ 10 ]
#define I1b1 param[ 11 ]
#define I2b1 param[ 12 ]
#define I3b1 param[ 13 ]
#define mb2 param[ 14 ]
#define I1b2 param[ 15 ]
#define I2b2 param[ 16 ]
#define I3b2 param[ 17 ]
#define mDisc param[ 18 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define Torque inputs[ 0 ]

double * _Energy = NULL;
void Init_Energy ( ) 
{
    _Energy = malloc ( Energy_n_rows * Energy_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Energy_n_rows * Energy_n_cols ; i++ ) {_Energy[i]=0.0;}
  }
}

void Done_Energy ( ) 
{
if (_Energy != NULL) 
free (_Energy ); 
_Energy = NULL; 
}


double * Energy ()
{
if ( _Energy == NULL )
 {
    _Energy = malloc ( Energy_n_rows * Energy_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Energy_n_rows * Energy_n_cols ; i++ ) {_Energy[i]=0.0;}
  }
 }

_Energy[0]=0.0;
return _Energy;
}
