#include <stdlib.h>
#include "param.h"

#define g 9.8000000000000007e+00
#define theta1_0 1.5000000000000000e+00
#define psi_0 0.0000000000000000e+00
#define l1 5.0000000000000000e-01
#define l2 1.5000000000000000e+00
#define y0 1.5000000000000000e+00
#define z0 -5.0000000000000000e-01
#define alpha 5.0000000000000000e-01
#define r 5.0000000000000000e-01
#define Cvis 2.0000000000000001e-01
#define mb1 1.0000000000000000e+00
#define I1b1 1.0000000000000001e-01
#define I2b1 1.0000000000000001e-01
#define I3b1 1.0000000000000001e-01
#define mb2 1.0000000000000000e+00
#define I1b2 1.0000000000000001e-01
#define I2b2 1.0000000000000001e-01
#define I3b2 1.0000000000000001e-01
#define mDisc 1.0000000000000000e+00

double * param=NULL; 

void Init_param_values ( void )
{
param[0]=g;
param[1]=theta1_0;
param[2]=psi_0;
param[3]=l1;
param[4]=l2;
param[5]=y0;
param[6]=z0;
param[7]=alpha;
param[8]=r;
param[9]=Cvis;
param[10]=mb1;
param[11]=I1b1;
param[12]=I2b1;
param[13]=I3b1;
param[14]=mb2;
param[15]=I1b2;
param[16]=I2b2;
param[17]=I3b2;
param[18]=mDisc;
}

void Init_param ( )
{
 param = malloc ( n_param * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_param ; i++ ) {param[i]=0.0;}
 }
}

void Done_param( ) 
{
if ( param != NULL) 
free ( param ); 
param = NULL; 
}

void Reallocate_param( double * user_param ) 
{
param = user_param; 
}

