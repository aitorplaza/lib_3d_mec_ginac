#include <stdlib.h>
#include "gen_accel.h"

#define ddx 0.0000000000000000e+00
#define ddy 0.0000000000000000e+00
#define ddz 0.0000000000000000e+00
#define dda 0.0000000000000000e+00
#define ddB 0.0000000000000000e+00
#define ddc 0.0000000000000000e+00
#define dda1 0.0000000000000000e+00
#define dda2 0.0000000000000000e+00
#define dda3 0.0000000000000000e+00
#define dda4 0.0000000000000000e+00
#define dda5 0.0000000000000000e+00
#define dda6 0.0000000000000000e+00
#define ddB1 0.0000000000000000e+00
#define ddB2 0.0000000000000000e+00
#define ddB3 0.0000000000000000e+00
#define ddB4 0.0000000000000000e+00
#define ddB5 0.0000000000000000e+00
#define ddB6 0.0000000000000000e+00
#define dds1 0.0000000000000000e+00
#define dds2 0.0000000000000000e+00
#define dds3 0.0000000000000000e+00
#define dds4 0.0000000000000000e+00
#define dds5 0.0000000000000000e+00
#define dds6 0.0000000000000000e+00

double * ddq=NULL; 

void Init_ddq_values ( void )
{
ddq[0]=ddx;
ddq[1]=ddy;
ddq[2]=ddz;
ddq[3]=dda;
ddq[4]=ddB;
ddq[5]=ddc;
ddq[6]=dda1;
ddq[7]=dda2;
ddq[8]=dda3;
ddq[9]=dda4;
ddq[10]=dda5;
ddq[11]=dda6;
ddq[12]=ddB1;
ddq[13]=ddB2;
ddq[14]=ddB3;
ddq[15]=ddB4;
ddq[16]=ddB5;
ddq[17]=ddB6;
ddq[18]=dds1;
ddq[19]=dds2;
ddq[20]=dds3;
ddq[21]=dds4;
ddq[22]=dds5;
ddq[23]=dds6;
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

