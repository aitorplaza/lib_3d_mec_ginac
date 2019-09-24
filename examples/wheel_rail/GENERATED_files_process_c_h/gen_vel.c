#include <stdlib.h>
#include "gen_vel.h"

#define dx 0.0000000000000000e+00
#define dy 0.0000000000000000e+00
#define db 0.0000000000000000e+00
#define dc 0.0000000000000000e+00
#define dz 0.0000000000000000e+00
#define da 0.0000000000000000e+00

double * dq=NULL; 

void Init_dq_values ( void )
{
dq[0]=dx;
dq[1]=dy;
dq[2]=db;
dq[3]=dc;
dq[4]=dz;
dq[5]=da;
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

