/*----------Kinematics_Wheels.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "gen_auxcoord.h"
#include "gen_auxvel.h"
#include "gen_auxaccel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "Kinematics_Wheels.h"

#define x q[ 0 ]
#define y q[ 1 ]
#define z q[ 2 ]
#define a q[ 3 ]
#define b q[ 4 ]
#define c q[ 5 ]
#define r q[ 6 ]
#define t1 q[ 7 ]
#define t2 q[ 8 ]
#define t3 q[ 9 ]
#define dx dq[ 0 ]
#define dy dq[ 1 ]
#define dz dq[ 2 ]
#define da dq[ 3 ]
#define db dq[ 4 ]
#define dc dq[ 5 ]
#define dr dq[ 6 ]
#define dt1 dq[ 7 ]
#define dt2 dq[ 8 ]
#define dt3 dq[ 9 ]
#define ddx ddq[ 0 ]
#define ddy ddq[ 1 ]
#define ddz ddq[ 2 ]
#define dda ddq[ 3 ]
#define ddb ddq[ 4 ]
#define ddc ddq[ 5 ]
#define ddr ddq[ 6 ]
#define ddt1 ddq[ 7 ]
#define ddt2 ddq[ 8 ]
#define ddt3 ddq[ 9 ]
#define g param[ 0 ]
#define W param[ 1 ]
#define L param[ 2 ]
#define Lx param[ 3 ]
#define Lz param[ 4 ]
#define R param[ 5 ]
#define kz param[ 6 ]
#define cz param[ 7 ]
#define kx param[ 8 ]
#define ky param[ 9 ]
#define mChassi param[ 10 ]
#define IxxChassi param[ 11 ]
#define IxyChassi param[ 12 ]
#define IyyChassi param[ 13 ]
#define IxzChassi param[ 14 ]
#define IzzChassi param[ 15 ]
#define IyzChassi param[ 16 ]
#define mWheel1 param[ 17 ]
#define IxxWheel1 param[ 18 ]
#define IxyWheel1 param[ 19 ]
#define IyyWheel1 param[ 20 ]
#define IxzWheel1 param[ 21 ]
#define IzzWheel1 param[ 22 ]
#define IyzWheel1 param[ 23 ]
#define mWheel2 param[ 24 ]
#define IxxWheel2 param[ 25 ]
#define IxyWheel2 param[ 26 ]
#define IyyWheel2 param[ 27 ]
#define IxzWheel2 param[ 28 ]
#define IzzWheel2 param[ 29 ]
#define IyzWheel2 param[ 30 ]
#define mWheel3 param[ 31 ]
#define IxxWheel3 param[ 32 ]
#define IxyWheel3 param[ 33 ]
#define IyyWheel3 param[ 34 ]
#define IxzWheel3 param[ 35 ]
#define IzzWheel3 param[ 36 ]
#define IyzWheel3 param[ 37 ]
#define x1 param[ 38 ]
#define y1 param[ 39 ]
#define z1 param[ 40 ]
#define x2 param[ 41 ]
#define y2 param[ 42 ]
#define z2 param[ 43 ]
#define x3 param[ 44 ]
#define y3 param[ 45 ]
#define z3 param[ 46 ]
#define F1x inputs[ 0 ]
#define F1y inputs[ 1 ]
#define F1z inputs[ 2 ]
#define F2x inputs[ 3 ]
#define F2y inputs[ 4 ]
#define F2z inputs[ 5 ]
#define F3x inputs[ 6 ]
#define F3y inputs[ 7 ]
#define F3z inputs[ 8 ]
#define M1x inputs[ 9 ]
#define M1y inputs[ 10 ]
#define M1z inputs[ 11 ]
#define M2x inputs[ 12 ]
#define M2y inputs[ 13 ]
#define M2z inputs[ 14 ]
#define M3x inputs[ 15 ]
#define M3y inputs[ 16 ]
#define M3z inputs[ 17 ]

double * _Kinematics_Wheels = NULL;
void Init_Kinematics_Wheels ( ) 
{
    _Kinematics_Wheels = malloc ( Kinematics_Wheels_n_rows * Kinematics_Wheels_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Kinematics_Wheels_n_rows * Kinematics_Wheels_n_cols ; i++ ) {_Kinematics_Wheels[i]=0.0;}
  }
}

void Done_Kinematics_Wheels ( ) 
{
if (_Kinematics_Wheels != NULL) 
free (_Kinematics_Wheels ); 
_Kinematics_Wheels = NULL; 
}


double * Kinematics_Wheels ()
{
if ( _Kinematics_Wheels == NULL )
 {
    _Kinematics_Wheels = malloc ( Kinematics_Wheels_n_rows * Kinematics_Wheels_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Kinematics_Wheels_n_rows * Kinematics_Wheels_n_cols ; i++ ) {_Kinematics_Wheels[i]=0.0;}
  }
 }
_Kinematics_Wheels[0]=x+cos(b)*cos(c)*L;
_Kinematics_Wheels[1]=cos(b)*L*sin(c)+y;
_Kinematics_Wheels[2]=-sin(b)*L+z;
_Kinematics_Wheels[3]=-cos(r)*cos(a)*sin(c)-(cos(b)*sin(r)-cos(r)*sin(b)*sin(a))*cos(c);
_Kinematics_Wheels[4]=cos(r)*cos(c)*cos(a)-(cos(b)*sin(r)-cos(r)*sin(b)*sin(a))*sin(c);
_Kinematics_Wheels[5]=cos(r)*cos(b)*sin(a)+sin(r)*sin(b);
_Kinematics_Wheels[6]=-sin(b)*cos(c)*L*db+dx-dc*cos(b)*L*sin(c);
_Kinematics_Wheels[7]=-sin(b)*L*db*sin(c)+dy+dc*cos(b)*cos(c)*L;
_Kinematics_Wheels[8]=dz-cos(b)*L*db;
_Kinematics_Wheels[9]=(cos(b)*(da-dt1*sin(r))+(dr*cos(a)+dt1*cos(r)*sin(a))*sin(b))*cos(c)-(db+dt1*cos(r)*cos(a)-dr*sin(a))*sin(c);
_Kinematics_Wheels[10]=(cos(b)*(da-dt1*sin(r))+(dr*cos(a)+dt1*cos(r)*sin(a))*sin(b))*sin(c)+(db+dt1*cos(r)*cos(a)-dr*sin(a))*cos(c);
_Kinematics_Wheels[11]=dc+cos(b)*(dr*cos(a)+dt1*cos(r)*sin(a))-sin(b)*(da-dt1*sin(r));
_Kinematics_Wheels[12]=x-0.5*(sin(b)*cos(c)*sin(a)-cos(a)*sin(c))*W;
_Kinematics_Wheels[13]=-0.5*W*(cos(c)*cos(a)+sin(b)*sin(c)*sin(a))+y;
_Kinematics_Wheels[14]=-0.5*cos(b)*W*sin(a)+z;
_Kinematics_Wheels[15]=sin(b)*cos(c)*sin(a)-cos(a)*sin(c);
_Kinematics_Wheels[16]=cos(c)*cos(a)+sin(b)*sin(c)*sin(a);
_Kinematics_Wheels[17]=cos(b)*sin(a);
_Kinematics_Wheels[18]=dx+0.5*dc*W*(cos(c)*cos(a)+sin(b)*sin(c)*sin(a))-0.5*cos(b)*W*cos(c)*db*sin(a)-0.5*W*(sin(b)*cos(c)*cos(a)+sin(c)*sin(a))*da;
_Kinematics_Wheels[19]=-0.5*dc*(sin(b)*cos(c)*sin(a)-cos(a)*sin(c))*W-0.5*cos(b)*W*db*sin(c)*sin(a)+dy+0.5*(cos(c)*sin(a)-sin(b)*cos(a)*sin(c))*W*da;
_Kinematics_Wheels[20]=-0.5*cos(b)*W*cos(a)*da+dz+0.5*W*sin(b)*db*sin(a);
_Kinematics_Wheels[21]=cos(c)*(cos(b)*da+sin(b)*sin(a)*dt2)-sin(c)*(cos(a)*dt2+db);
_Kinematics_Wheels[22]=cos(c)*(cos(a)*dt2+db)+sin(c)*(cos(b)*da+sin(b)*sin(a)*dt2);
_Kinematics_Wheels[23]=dc+cos(b)*sin(a)*dt2-sin(b)*da;
_Kinematics_Wheels[24]=x+0.5*(sin(b)*cos(c)*sin(a)-cos(a)*sin(c))*W;
_Kinematics_Wheels[25]=0.5*W*(cos(c)*cos(a)+sin(b)*sin(c)*sin(a))+y;
_Kinematics_Wheels[26]=0.5*cos(b)*W*sin(a)+z;
_Kinematics_Wheels[27]=sin(b)*cos(c)*sin(a)-cos(a)*sin(c);
_Kinematics_Wheels[28]=cos(c)*cos(a)+sin(b)*sin(c)*sin(a);
_Kinematics_Wheels[29]=cos(b)*sin(a);
_Kinematics_Wheels[30]=dx-0.5*dc*W*(cos(c)*cos(a)+sin(b)*sin(c)*sin(a))+0.5*cos(b)*W*cos(c)*db*sin(a)+0.5*W*(sin(b)*cos(c)*cos(a)+sin(c)*sin(a))*da;
_Kinematics_Wheels[31]=0.5*dc*(sin(b)*cos(c)*sin(a)-cos(a)*sin(c))*W+0.5*cos(b)*W*db*sin(c)*sin(a)+dy-0.5*(cos(c)*sin(a)-sin(b)*cos(a)*sin(c))*W*da;
_Kinematics_Wheels[32]=0.5*cos(b)*W*cos(a)*da+dz-0.5*W*sin(b)*db*sin(a);
_Kinematics_Wheels[33]=(cos(b)*da+dt3*sin(b)*sin(a))*cos(c)-(db+dt3*cos(a))*sin(c);
_Kinematics_Wheels[34]=(cos(b)*da+dt3*sin(b)*sin(a))*sin(c)+cos(c)*(db+dt3*cos(a));
_Kinematics_Wheels[35]=cos(b)*dt3*sin(a)+dc-sin(b)*da;
return _Kinematics_Wheels;
}
