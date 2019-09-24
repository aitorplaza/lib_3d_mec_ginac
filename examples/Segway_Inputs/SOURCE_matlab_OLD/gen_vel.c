#include <stdlib.h>
#include "gen_vel.h"

#define drho1 0.0000000000000000e+00
#define dphi1 0.0000000000000000e+00
#define dphi2 0.0000000000000000e+00
#define dphi3 0.0000000000000000e+00
#define dtheta1 0.0000000000000000e+00
#define dxp 0.0000000000000000e+00
#define dyp 0.0000000000000000e+00
#define dzp 0.0000000000000000e+00
#define dycdg 0.0000000000000000e+00

double * dq=NULL; 

void Init_dq_values ( void )
{
dq[0]=drho1;
dq[1]=dphi1;
dq[2]=dphi2;
dq[3]=dphi3;
dq[4]=dtheta1;
dq[5]=dxp;
dq[6]=dyp;
dq[7]=dzp;
dq[8]=dycdg;
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

