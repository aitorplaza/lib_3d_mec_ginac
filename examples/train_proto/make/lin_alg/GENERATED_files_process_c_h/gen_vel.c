#include <stdlib.h>
#include "gen_vel.h"

#define da1 0.0000000000000000e+00
#define da2 0.0000000000000000e+00
#define da5 0.0000000000000000e+00
#define da6 0.0000000000000000e+00
#define da3 0.0000000000000000e+00
#define da4 0.0000000000000000e+00

double * dq=NULL; 

void Init_dq_values ( void )
{
dq[0]=da1;
dq[1]=da2;
dq[2]=da5;
dq[3]=da6;
dq[4]=da3;
dq[5]=da4;
}

void Init_dq ( )
{
 dq = malloc ( n_gen_vel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_vel ; i++ ) {dq[i]=0.0;}
 }
}

void Done_dq( ) 
{
if ( dq != NULL) 
free ( dq ); 
dq = NULL; 
}

void Reallocate_dq( double * user_dq ) 
{
dq = user_dq; 
}

