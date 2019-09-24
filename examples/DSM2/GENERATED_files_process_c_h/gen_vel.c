#include <stdlib.h>
#include "gen_vel.h"

#define dtheta1 0.0000000000000000e+00
#define dtheta2 0.0000000000000000e+00
#define dpsi 0.0000000000000000e+00
#define dy 0.0
#define dz 0.0

double * dq=NULL; 

void Init_dq_values ( void )
{
dq[0]=dtheta1;
dq[1]=dtheta2;
dq[2]=dpsi;
dq[3]=dy;
dq[4]=dz;
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

