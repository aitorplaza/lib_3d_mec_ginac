#include <stdlib.h>
#include "gen_auxvel.h"

#define dthetaW_R 0.0000000000000000e+00
#define duW_R 0.0000000000000000e+00
#define duR_R 0.0000000000000000e+00
#define dsR_R 0.0000000000000000e+00
#define dthetaW_L 0.0000000000000000e+00
#define duW_L 0.0000000000000000e+00
#define duR_L 0.0000000000000000e+00
#define dsR_L 0.0000000000000000e+00

double * dqaux=NULL; 
void Init_dqaux_values ( void )
{
dqaux[0]=dthetaW_R;
dqaux[1]=duW_R;
dqaux[2]=duR_R;
dqaux[3]=dsR_R;
dqaux[4]=dthetaW_L;
dqaux[5]=duW_L;
dqaux[6]=duR_L;
dqaux[7]=dsR_L;
}

void Init_dqaux ( )
{
 dqaux = malloc ( n_gen_auxvel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxvel ; i++ ) {dqaux[i]=0.0;}
 }
}

void Done_dqaux( ) 
{
if ( dqaux != NULL) 
free ( dqaux ); 
dqaux = NULL; 
}

void Reallocate_dqaux( double * user_dqaux ) 
{
dqaux = user_dqaux; 
}

