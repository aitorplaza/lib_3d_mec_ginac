/*----------PhiInit_q.c lib3D_MEC exported-----------*/

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

#include "PhiInit_q.h"

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

double * _PhiInit_q = NULL;
void Init_PhiInit_q ( ) 
{
    _PhiInit_q = malloc ( PhiInit_q_n_rows * PhiInit_q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < PhiInit_q_n_rows * PhiInit_q_n_cols ; i++ ) {_PhiInit_q[i]=0.0;}
  }
}

void Done_PhiInit_q ( ) 
{
if (_PhiInit_q != NULL) 
free (_PhiInit_q ); 
_PhiInit_q = NULL; 
}


double * PhiInit_q ()
{
if ( _PhiInit_q == NULL )
 {
    _PhiInit_q = malloc ( PhiInit_q_n_rows * PhiInit_q_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < PhiInit_q_n_rows * PhiInit_q_n_cols ; i++ ) {_PhiInit_q[i]=0.0;}
  }
 }

_PhiInit_q[0]=2.0*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)-z-z0)-2.0*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1))*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1)-y-y0);
_PhiInit_q[1]=0.0;
_PhiInit_q[2]=-2.0*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*sin(alpha)+2.0*cos(alpha)*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1));
_PhiInit_q[3]=1.0;
_PhiInit_q[4]=0.0;
_PhiInit_q[5]=-2.0*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)-z-z0)+2.0*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1)-y-y0);
_PhiInit_q[6]=0.0;
_PhiInit_q[7]=2.0*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*sin(alpha)-2.0*cos(alpha)*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1));
_PhiInit_q[8]=0.0;
_PhiInit_q[9]=0.0;
_PhiInit_q[10]=0.0;
_PhiInit_q[11]=0.0;
_PhiInit_q[12]=0.0;
_PhiInit_q[13]=0.0;
_PhiInit_q[14]=1.0;
_PhiInit_q[15]=-2.0*(l1+cos(-theta2)*l2)*cos(theta1)+2.0*sin(-theta2)*l2*sin(theta1)+2.0*y+2.0*y0;
_PhiInit_q[16]=-sin(alpha);
_PhiInit_q[17]=2.0*cos(alpha);
_PhiInit_q[18]=0.0;
_PhiInit_q[19]=0.0;
_PhiInit_q[20]=-2.0*sin(-theta2)*l2*cos(theta1)-2.0*(l1+cos(-theta2)*l2)*sin(theta1)+2.0*z+2.0*z0;
_PhiInit_q[21]=cos(alpha);
_PhiInit_q[22]=2.0*sin(alpha);
_PhiInit_q[23]=0.0;
_PhiInit_q[24]=0.0;
return _PhiInit_q;
}
