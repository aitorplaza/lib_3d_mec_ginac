#include <stdlib.h>
#include "param.h"

#define g 9.8000000000000007e+00
#define l1 4.0000000000000002e-01
#define l2 2.0000000000000000e+00
#define l3 1.2000000000000000e+00
#define l4 1.6000000000000001e+00
#define m1 1.0000000000000000e+00
#define m2 1.0000000000000000e+00
#define m3 1.0000000000000000e+00
#define cg1x 2.0000000000000001e-01
#define cg1z 1.0000000000000001e-01
#define cg2x 1.0000000000000000e+00
#define cg2z 1.0000000000000001e-01
#define cg3x 5.9999999999999998e-01
#define cg3z 1.0000000000000001e-01
#define I1yy 1.0000000000000000e+00
#define I2yy 1.0000000000000000e+00
#define I3yy 1.0000000000000000e+00
#define K 5.0000000000000000e+01
#define l2x 1.0000000000000000e+00
#define l2z 1.0000000000000001e-01
#define l3x 5.0000000000000000e-01
#define l3z 1.0000000000000001e-01

double * param=NULL; 

void Init_param_values ( void )
{
param[0]=g;
param[1]=l1;
param[2]=l2;
param[3]=l3;
param[4]=l4;
param[5]=m1;
param[6]=m2;
param[7]=m3;
param[8]=cg1x;
param[9]=cg1z;
param[10]=cg2x;
param[11]=cg2z;
param[12]=cg3x;
param[13]=cg3z;
param[14]=I1yy;
param[15]=I2yy;
param[16]=I3yy;
param[17]=K;
param[18]=l2x;
param[19]=l2z;
param[20]=l3x;
param[21]=l3z;
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

