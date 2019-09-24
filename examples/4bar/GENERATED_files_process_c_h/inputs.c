#include <stdlib.h>
#include "inputs.h"

#define Fx2 0.0000000000000000e+00
#define Fz2 0.0000000000000000e+00
#define Fx3 0.0000000000000000e+00
#define Fz3 0.0000000000000000e+00
#define My2 0.0000000000000000e+00
#define My3 0.0000000000000000e+00

double * inputs=NULL; 

void Init_inputs_values ( void )
{
inputs[0]=Fx2;
inputs[1]=Fz2;
inputs[2]=Fx3;
inputs[3]=Fz3;
inputs[4]=My2;
inputs[5]=My3;
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

