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

_Q[0]=((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*g*mDisc+0.500000*l1*mb1*g*cos(theta1)+0.500000*l1*pow(dtheta1,2.0)*l2*mb2*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1))*cos(theta1)-Torque+l1*mb2*g*cos(theta1)-0.500000*l1*sin(-theta2)*l2*mb2*pow(dtheta2-dtheta1,2.0)+(l1*cos(-theta2)+l2)*((dtheta1*mDisc*(dtheta1*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))-dtheta2*(dtheta1*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))*mDisc)*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1))-((dtheta2*sin(-theta2)*l2*cos(theta1)+dtheta2*cos(-theta2)*l2*sin(theta1)-dtheta1*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)))*dtheta1*mDisc+dtheta2*mDisc*(dtheta1*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))-dtheta2*sin(-theta2)*l2*cos(theta1)-dtheta2*cos(-theta2)*l2*sin(theta1)))*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1)))-0.500000*l2*mb2*g*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))+dtheta1*Cvis+l1*sin(-theta2)*((dtheta1*mDisc*(dtheta1*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))-dtheta2*(dtheta1*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))*mDisc)*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))+((dtheta2*sin(-theta2)*l2*cos(theta1)+dtheta2*cos(-theta2)*l2*sin(theta1)-dtheta1*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)))*dtheta1*mDisc+dtheta2*mDisc*(dtheta1*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))-dtheta2*sin(-theta2)*l2*cos(theta1)-dtheta2*cos(-theta2)*l2*sin(theta1)))*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1)))+0.500000*l1*pow(dtheta1,2.0)*l2*mb2*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))*sin(theta1);
_Q[1]=-0.500000*l1*pow(dtheta1,2.0)*l2*mb2*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1))*cos(theta1)-l2*((dtheta1*mDisc*(dtheta1*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))-dtheta2*(dtheta1*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1))*mDisc)*(sin(-theta2)*cos(theta1)+cos(-theta2)*sin(theta1))-((dtheta2*sin(-theta2)*l2*cos(theta1)+dtheta2*cos(-theta2)*l2*sin(theta1)-dtheta1*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)))*dtheta1*mDisc+dtheta2*mDisc*(dtheta1*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))-dtheta2*sin(-theta2)*l2*cos(theta1)-dtheta2*cos(-theta2)*l2*sin(theta1)))*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1)))+0.500000*l2*mb2*g*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))-0.500000*l1*pow(dtheta1,2.0)*l2*mb2*(sin(-theta2)*sin(theta1)-cos(-theta2)*cos(theta1))*sin(theta1)-(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*g*mDisc;
_Q[2]=0.0;
_Q[3]=0.0;
_Q[4]=0.0;
return _Q;
}
