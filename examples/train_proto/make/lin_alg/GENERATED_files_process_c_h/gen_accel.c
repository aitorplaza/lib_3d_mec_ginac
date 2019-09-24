#include <stdlib.h>
#include "gen_accel.h"

#define dda1 0.0000000000000000e+00
#define dda2 0.0000000000000000e+00
#define dda5 0.0000000000000000e+00
#define dda6 0.0000000000000000e+00
#define dda3 0.0000000000000000e+00
#define dda4 0.0000000000000000e+00

double * ddq=NULL; 

void Init_ddq_values ( void )
{
ddq[0]=dda1;
ddq[1]=dda2;
ddq[2]=dda5;
ddq[3]=dda6;
ddq[4]=dda3;
ddq[5]=dda4;
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

