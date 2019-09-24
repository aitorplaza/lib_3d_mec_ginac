#include <stdlib.h>
#include "gen_coord.h"

#define x 0.0000000000000000e+00
#define y 0.0000000000000000e+00
#define z 5.0000000000000000e+00
#define a 0.0000000000000000e+00
#define b 0.0000000000000000e+00
#define c 0.0000000000000000e+00
#define a1 0.0000000000000000e+00
#define a2 0.0000000000000000e+00
#define a3 0.0000000000000000e+00
#define a4 0.0000000000000000e+00
#define a5 0.0000000000000000e+00
#define a6 0.0000000000000000e+00
#define b1 4.8099999999999998e-01
#define b2 4.8099999999999998e-01
#define b3 4.8099999999999998e-01
#define b4 4.8099999999999998e-01
#define b5 4.8099999999999998e-01
#define b6 4.8099999999999998e-01
#define s1 1.0000000000000000e+00
#define s2 1.0000000000000000e+00
#define s3 1.0000000000000000e+00
#define s4 1.0000000000000000e+00
#define s5 1.0000000000000000e+00
#define s6 1.0000000000000000e+00

double * q=NULL; 

void Init_q_values ( void )
{
q[0]=x;
q[1]=y;
q[2]=z;
q[3]=a;
q[4]=b;
q[5]=c;
q[6]=a1;
q[7]=a2;
q[8]=a3;
q[9]=a4;
q[10]=a5;
q[11]=a6;
q[12]=b1;
q[13]=b2;
q[14]=b3;
q[15]=b4;
q[16]=b5;
q[17]=b6;
q[18]=s1;
q[19]=s2;
q[20]=s3;
q[21]=s4;
q[22]=s5;
q[23]=s6;
}

void Init_q ( )
{
 q = malloc ( n_gen_coord * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_coord ; i++ ) {q[i]=0.0;}
 }
}

void Done_q( ) 
{
if ( q != NULL) 
free ( q ); 
q = NULL; 
}

void Reallocate_q( double * user_q ) 
{
q = user_q; 
}

