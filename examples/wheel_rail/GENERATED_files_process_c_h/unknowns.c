#include <stdlib.h>
#include "unknowns.h"

#define lambda1 0.0000000000000000e+00
#define lambda2 0.0000000000000000e+00

double * unknowns=NULL; 

void Init_unknowns_values ( void )
{
unknowns[0]=lambda1;
unknowns[1]=lambda2;
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

