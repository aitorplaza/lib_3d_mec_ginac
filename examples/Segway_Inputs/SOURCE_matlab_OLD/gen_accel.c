#include <stdlib.h>
#include "gen_accel.h"

#define ddrho1 0.0000000000000000e+00
#define ddphi1 0.0000000000000000e+00
#define ddphi2 0.0000000000000000e+00
#define ddphi3 0.0000000000000000e+00
#define ddtheta1 0.0000000000000000e+00
#define ddxp 0.0000000000000000e+00
#define ddyp 0.0000000000000000e+00
#define ddzp 0.0000000000000000e+00
#define ddycdg 0.0000000000000000e+00

double * ddq=NULL; 

void Init_ddq_values ( void )
{
ddq[0]=ddrho1;
ddq[1]=ddphi1;
ddq[2]=ddphi2;
ddq[3]=ddphi3;
ddq[4]=ddtheta1;
ddq[5]=ddxp;
ddq[6]=ddyp;
ddq[7]=ddzp;
ddq[8]=ddycdg;
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

