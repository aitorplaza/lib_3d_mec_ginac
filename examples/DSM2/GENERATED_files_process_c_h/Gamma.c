/*----------Gamma.c lib3D_MEC exported-----------*/

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

#include "Gamma.h"

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

double * _Gamma = NULL;
void Init_Gamma ( ) 
{
    _Gamma = malloc ( Gamma_n_rows * Gamma_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gamma_n_rows * Gamma_n_cols ; i++ ) {_Gamma[i]=0.0;}
  }
}

void Done_Gamma ( ) 
{
if (_Gamma != NULL) 
free (_Gamma ); 
_Gamma = NULL; 
}


double * Gamma ()
{
if ( _Gamma == NULL )
 {
    _Gamma = malloc ( Gamma_n_rows * Gamma_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Gamma_n_rows * Gamma_n_cols ; i++ ) {_Gamma[i]=0.0;}
  }
 }

_Gamma[0]=-2.0*(dtheta2*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta1*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))+dz)*dz+2.0*(dtheta2*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))-dtheta1*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1))-dy)*dy+2.0*dtheta1*(dtheta2*((sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1))-(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)-z-z0)-(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1)-y-y0)+((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1)))-(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1))*dy+((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*dz-dtheta1*(pow(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1),2.0)-(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1))*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)-z-z0)+pow((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1),2.0)-((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1)-y-y0)))-2.0*dtheta2*((cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*dz-dtheta1*((sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1))-(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)-z-z0)-(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1)-y-y0)+((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1)))-(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*dy+dtheta2*(pow(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1),2.0)-(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)-z-z0)-(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1)-y-y0)+pow(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1),2.0)));
_Gamma[1]=0.0;
_Gamma[2]=2.0*dtheta2*(dtheta1*((cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*cos(alpha)+(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*sin(alpha))-dtheta2*((cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*cos(alpha)+(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*sin(alpha)))+2.0*dtheta1*(dtheta2*((cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*cos(alpha)+(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*sin(alpha))-dtheta1*((sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1))*sin(alpha)+((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*cos(alpha)));
_Gamma[3]=dtheta1*(sin(alpha)*((sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1))*dpsi-dtheta2*sin(-theta2)*l2*cos(theta1)-dtheta2*cos(-theta2)*l2*sin(theta1)+dtheta1*(sin(-theta2)*l2*cos(theta1)+(l1+cos(-theta2)*l2)*sin(theta1)))+cos(alpha)*(((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))*dpsi+dtheta1*((l1+cos(-theta2)*l2)*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1)))-dtheta2*(((sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))*dpsi+dtheta1*(sin(-theta2)*l2*cos(theta1)+cos(-theta2)*l2*sin(theta1))-dtheta2*sin(-theta2)*l2*cos(theta1)-dtheta2*cos(-theta2)*l2*sin(theta1))*sin(alpha)+cos(alpha)*((cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))*dpsi+dtheta1*(cos(-theta2)*l2*cos(theta1)-sin(-theta2)*l2*sin(theta1))-dtheta2*cos(-theta2)*l2*cos(theta1)+dtheta2*sin(-theta2)*l2*sin(theta1)))+sin(alpha)*dy*dpsi-cos(alpha)*dz*dpsi;
return _Gamma;
}
