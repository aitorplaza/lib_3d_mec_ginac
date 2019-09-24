#include <stdlib.h>
#include "gen_vel.h"

#define dx 0.0000000000000000e+00
#define dy 0.0000000000000000e+00
#define dz 0.0000000000000000e+00
#define da 0.0000000000000000e+00
#define dB 0.0000000000000000e+00
#define dc 0.0000000000000000e+00
#define da1 0.0000000000000000e+00
#define da2 0.0000000000000000e+00
#define da3 0.0000000000000000e+00
#define da4 0.0000000000000000e+00
#define da5 0.0000000000000000e+00
#define da6 0.0000000000000000e+00
#define dB1 0.0000000000000000e+00
#define dB2 0.0000000000000000e+00
#define dB3 0.0000000000000000e+00
#define dB4 0.0000000000000000e+00
#define dB5 0.0000000000000000e+00
#define dB6 0.0000000000000000e+00
#define ds1 0.0000000000000000e+00
#define ds2 0.0000000000000000e+00
#define ds3 0.0000000000000000e+00
#define ds4 0.0000000000000000e+00
#define ds5 0.0000000000000000e+00
#define ds6 0.0000000000000000e+00

double * dq=NULL; 

void Init_dq_values ( void )
{
dq[0]=dx;
dq[1]=dy;
dq[2]=dz;
dq[3]=da;
dq[4]=dB;
dq[5]=dc;
dq[6]=da1;
dq[7]=da2;
dq[8]=da3;
dq[9]=da4;
dq[10]=da5;
dq[11]=da6;
dq[12]=dB1;
dq[13]=dB2;
dq[14]=dB3;
dq[15]=dB4;
dq[16]=dB5;
dq[17]=dB6;
dq[18]=ds1;
dq[19]=ds2;
dq[20]=ds3;
dq[21]=ds4;
dq[22]=ds5;
dq[23]=ds6;
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

