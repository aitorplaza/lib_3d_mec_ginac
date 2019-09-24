#include <stdlib.h>
#include "gen_accel.h"

#define ddtheta1 0.0000000000000000e+00
#define ddtheta2 0.0000000000000000e+00
#define ddpsi 0.0000000000000000e+00
#define ddy 0.0
#define ddz 0.0

double * ddq=NULL; 

void Init_ddq_values ( void )
{
ddq[0]=ddtheta1;
ddq[1]=ddtheta2;
ddq[2]=ddpsi;
ddq[3]=ddy;
ddq[4]=ddz;
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

