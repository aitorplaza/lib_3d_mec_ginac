#include <stdlib.h>
#include "unknowns.h"

#define lambda1 0.0000000000000000e+00
#define lambda2 0.0000000000000000e+00
#define lambda3 0.0000000000000000e+00
#define lambda4 0.0000000000000000e+00
#define lambda5 0.0000000000000000e+00
#define lambda6 0.0000000000000000e+00
#define lambda7 0.0000000000000000e+00
#define lambda8 0.0000000000000000e+00
#define lambda9 0.0000000000000000e+00
#define lambda10 0.0000000000000000e+00
#define lambda11 0.0000000000000000e+00
#define lambda12 0.0000000000000000e+00
#define lambda13 0.0000000000000000e+00
#define lambda14 0.0000000000000000e+00
#define lambda15 0.0000000000000000e+00
#define lambda16 0.0000000000000000e+00
#define lambda17 0.0000000000000000e+00
#define lambda18 0.0000000000000000e+00

double * unknowns=NULL; 

void Init_unknowns_values ( void )
{
unknowns[0]=lambda1;
unknowns[1]=lambda2;
unknowns[2]=lambda3;
unknowns[3]=lambda4;
unknowns[4]=lambda5;
unknowns[5]=lambda6;
unknowns[6]=lambda7;
unknowns[7]=lambda8;
unknowns[8]=lambda9;
unknowns[9]=lambda10;
unknowns[10]=lambda11;
unknowns[11]=lambda12;
unknowns[12]=lambda13;
unknowns[13]=lambda14;
unknowns[14]=lambda15;
unknowns[15]=lambda16;
unknowns[16]=lambda17;
unknowns[17]=lambda18;
}

void Init_unknowns ( )
{
  unknowns = malloc ( n_unknowns * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_unknowns ; i++ ) {unknowns[i]=0.0;}
 }
}

void Done_unknowns( ) 
{
if ( unknowns != NULL) 
free ( unknowns ); 
unknowns = NULL; 
}

void Reallocate_unknowns( double * user_unknowns ) 
{
unknowns = user_unknowns; 
}

