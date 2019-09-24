#include <stdlib.h>
#include "gen_accel.h"

#define ddtheta1 0.0000000000000000e+00
#define ddtheta2 0.0000000000000000e+00
#define ddtheta3 0.0000000000000000e+00

double * ddq=NULL; 

void Init_ddq_values ( void )
{
ddq[0]=ddtheta1;
ddq[1]=ddtheta2;
ddq[2]=ddtheta3;
}

void Init_ddq ( )
{
 ddq = malloc ( n_gen_accel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_accel ; i++ ) {ddq[i]=0.0;}
 }
}

void Done_ddq( ) 
{
if ( ddq != NULL) 
free ( ddq ); 
ddq = NULL; 
}

void Reallocate_ddq( double * user_ddq ) 
{
ddq = user_ddq; 
}

