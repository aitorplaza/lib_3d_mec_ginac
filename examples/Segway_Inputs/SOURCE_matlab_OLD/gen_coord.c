#include <stdlib.h>
#include "gen_coord.h"

#define rho1 0.0000000000000000e+00
#define phi1 0.0000000000000000e+00
#define phi2 0.0000000000000000e+00
#define phi3 0.0000000000000000e+00
#define theta1 5.0000000000000000e-01
#define xp 0.0000000000000000e+00
#define yp 0.0000000000000000e+00
#define zp 0.0000000000000000e+00
#define ycdg -1.2050000000000001e+00

double * q=NULL; 

void Init_q_values ( void )
{
q[0]=rho1;
q[1]=phi1;
q[2]=phi2;
q[3]=phi3;
q[4]=theta1;
q[5]=xp;
q[6]=yp;
q[7]=zp;
q[8]=ycdg;
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

