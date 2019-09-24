#include <stdlib.h>
#include "gen_accel.h"

#define ddx 0.0000000000000000e+00
#define ddy 0.0000000000000000e+00
#define ddb 0.0000000000000000e+00
#define ddc 0.0000000000000000e+00
#define ddz 0.0000000000000000e+00
#define dda 0.0000000000000000e+00

double * ddq=NULL; 

void Init_ddq_values ( void )
{
ddq[0]=ddx;
ddq[1]=ddy;
ddq[2]=ddb;
ddq[3]=ddc;
ddq[4]=ddz;
ddq[5]=dda;
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

