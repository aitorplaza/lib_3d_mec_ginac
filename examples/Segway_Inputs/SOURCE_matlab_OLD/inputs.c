#include <stdlib.h>
#include "inputs.h"

#define ycdg_input 0.0000000000000000e+00
#define MomRuedaIzq 0.0000000000000000e+00
#define MomRuedaDcha 0.0000000000000000e+00

double * inputs=NULL; 

void Init_inputs_values ( void )
{
inputs[0]=ycdg_input;
inputs[1]=MomRuedaIzq;
inputs[2]=MomRuedaDcha;
}

void Init_inputs ( )
{
 inputs = malloc ( n_inputs * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_inputs ; i++ ) {inputs[i]=0.0;}
 }
}

void Done_inputs( ) 
{
if ( inputs != NULL) 
free ( inputs ); 
inputs = NULL; 
}

void Reallocate_inputs( double * user_inputs ) 
{
inputs = user_inputs; 
}

