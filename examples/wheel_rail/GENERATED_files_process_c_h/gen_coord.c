#include <stdlib.h>
#include "gen_coord.h"

#define x 0.0000000000000000e+00
#define y 0.0000000000000000e+00
#define b 0.0000000000000000e+00
#define c 0.0000000000000000e+00
#define z 5.0000000000000000e-01
#define a 0.0000000000000000e+00

double * q=NULL; 

void Init_q_values ( void )
{
q[0]=x;
q[1]=y;
q[2]=b;
q[3]=c;
q[4]=z;
q[5]=a;
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

