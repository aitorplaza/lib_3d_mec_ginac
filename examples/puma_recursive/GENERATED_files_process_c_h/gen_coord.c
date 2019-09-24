#include <stdlib.h>
#include "gen_coord.h"

#define a1 0.0000000000000000e+00
#define a2 0.0000000000000000e+00
#define a3 0.0000000000000000e+00
#define a4 0.0000000000000000e+00
#define a5 0.0000000000000000e+00
#define a6 0.0000000000000000e+00

double * q=NULL; 

void Init_q_values ( void )
{
q[0]=a1;
q[1]=a2;
q[2]=a3;
q[3]=a4;
q[4]=a5;
q[5]=a6;
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

