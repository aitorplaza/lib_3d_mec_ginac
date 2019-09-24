#include <stdlib.h>
#include "inputs.h"

#define Fx_R 0.0000000000000000e+00
#define Fy_R 0.0000000000000000e+00
#define Mz_R 0.0000000000000000e+00
#define Fx_L 0.0000000000000000e+00
#define Fy_L 0.0000000000000000e+00
#define Mz_L 0.0000000000000000e+00

double * inputs=NULL; 

void Init_inputs_values ( void )
{
inputs[0]=Fx_R;
inputs[1]=Fy_R;
inputs[2]=Mz_R;
inputs[3]=Fx_L;
inputs[4]=Fy_L;
inputs[5]=Mz_L;
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

