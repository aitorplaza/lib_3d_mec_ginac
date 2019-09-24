#include <stdlib.h>
#include "gen_auxaccel.h"

#define ddthetaW_R 0.0000000000000000e+00
#define dduW_R 0.0000000000000000e+00
#define dduR_R 0.0000000000000000e+00
#define ddsR_R 0.0000000000000000e+00
#define ddthetaW_L 0.0000000000000000e+00
#define dduW_L 0.0000000000000000e+00
#define dduR_L 0.0000000000000000e+00
#define ddsR_L 0.0000000000000000e+00

double * ddqaux=NULL; 

void Init_ddqaux_values ( void )
{
ddqaux[0]=ddthetaW_R;
ddqaux[1]=dduW_R;
ddqaux[2]=dduR_R;
ddqaux[3]=ddsR_R;
ddqaux[4]=ddthetaW_L;
ddqaux[5]=dduW_L;
ddqaux[6]=dduR_L;
ddqaux[7]=ddsR_L;
}

void Init_ddqaux ( )
{
 ddqaux = malloc ( n_gen_auxaccel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxaccel ; i++ ) {ddqaux[i]=0.0;}
 }
}

void Done_ddqaux( ) 
{
if ( ddqaux != NULL) 
free ( ddqaux ); 
ddqaux = NULL; 
}

void Reallocate_ddqaux( double * user_ddqaux ) 
{
ddqaux = user_ddqaux; 
}

