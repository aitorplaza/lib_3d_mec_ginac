#include <stdlib.h>
#include "gen_coord.h"

#define theta1 1.0500000000000000e+00
#define theta2 0.0000000000000000e+00
#define psi 0.0000000000000000e+00
#define y 2.1768999999999998e+00
#define z -1.3019000000000000e-01

double * q=NULL; 

void Init_q_values ( void )
{
q[0]=theta1;
q[1]=theta2;
q[2]=psi;
q[3]=y;
q[4]=z;
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

