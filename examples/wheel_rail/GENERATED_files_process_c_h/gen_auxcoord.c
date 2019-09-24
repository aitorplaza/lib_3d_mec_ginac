#include <stdlib.h>
#include "gen_auxcoord.h"

#define thetaW_R 0.0000000000000000e+00
#define uW_R 0.0000000000000000e+00
#define uR_R 0.0000000000000000e+00
#define sR_R 0.0000000000000000e+00
#define thetaW_L 0.0000000000000000e+00
#define uW_L 0.0000000000000000e+00
#define uR_L 0.0000000000000000e+00
#define sR_L 0.0000000000000000e+00

double * qaux=NULL; 

void Init_qaux_values ( void )
{
qaux[0]=thetaW_R;
qaux[1]=uW_R;
qaux[2]=uR_R;
qaux[3]=sR_R;
qaux[4]=thetaW_L;
qaux[5]=uW_L;
qaux[6]=uR_L;
qaux[7]=sR_L;
}

void Init_qaux ( )
{
 qaux = malloc ( n_gen_auxcoord * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxcoord ; i++ ) {qaux[i]=0.0;}
 }
}

void Done_qaux( ) 
{
if ( qaux != NULL) 
free ( qaux ); 
qaux = NULL; 
}

void Reallocate_qaux( double * user_qaux ) 
{
qaux = user_qaux; 
}

