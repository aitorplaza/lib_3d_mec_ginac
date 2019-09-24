#include <stdlib.h>
#include "gen_coord.h"

#define theta1 -1.5707960000000001e+00
#define theta2 1.5707960000000001e+00
#define theta3 1.5707960000000001e+00

double * q=NULL; 

void Init_q_values ( void )
{
q[0]=theta1;
q[1]=theta2;
q[2]=theta3;
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

