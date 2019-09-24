#include <stdlib.h>
#include "inputs.h"

#define T_RMOTF 1.0000000000000000e+02
#define T_RMOTR 1.0000000000000000e+02
#define T_FBRKF 0.0000000000000000e+00
#define T_FBRKR 0.0000000000000000e+00
#define T_RBRKF 0.0000000000000000e+00
#define T_RBRKR 0.0000000000000000e+00
#define Fx_RFR 0.0000000000000000e+00
#define Fy_RFR 0.0000000000000000e+00
#define Mz_RFR 0.0000000000000000e+00
#define Fx_RFL 0.0000000000000000e+00
#define Fy_RFL 0.0000000000000000e+00
#define Mz_RFL 0.0000000000000000e+00
#define Fx_RRR 0.0000000000000000e+00
#define Fy_RRR 0.0000000000000000e+00
#define Mz_RRR 0.0000000000000000e+00
#define Fx_RRL 0.0000000000000000e+00
#define Fy_RRL 0.0000000000000000e+00
#define Mz_RRL 0.0000000000000000e+00
#define Fx_FRR 0.0000000000000000e+00
#define Fy_FRR 0.0000000000000000e+00
#define Mz_FRR 0.0000000000000000e+00
#define Fx_FRL 0.0000000000000000e+00
#define Fy_FRL 0.0000000000000000e+00
#define Mz_FRL 0.0000000000000000e+00
#define Fx_FFR 0.0000000000000000e+00
#define Fy_FFR 0.0000000000000000e+00
#define Mz_FFR 0.0000000000000000e+00
#define Fx_FFL 0.0000000000000000e+00
#define Fy_FFL 0.0000000000000000e+00
#define Mz_FFL 0.0000000000000000e+00

double * inputs=NULL; 

void Init_inputs_values ( void )
{
inputs[0]=T_RMOTF;
inputs[1]=T_RMOTR;
inputs[2]=T_FBRKF;
inputs[3]=T_FBRKR;
inputs[4]=T_RBRKF;
inputs[5]=T_RBRKR;
inputs[6]=Fx_RFR;
inputs[7]=Fy_RFR;
inputs[8]=Mz_RFR;
inputs[9]=Fx_RFL;
inputs[10]=Fy_RFL;
inputs[11]=Mz_RFL;
inputs[12]=Fx_RRR;
inputs[13]=Fy_RRR;
inputs[14]=Mz_RRR;
inputs[15]=Fx_RRL;
inputs[16]=Fy_RRL;
inputs[17]=Mz_RRL;
inputs[18]=Fx_FRR;
inputs[19]=Fy_FRR;
inputs[20]=Mz_FRR;
inputs[21]=Fx_FRL;
inputs[22]=Fy_FRL;
inputs[23]=Mz_FRL;
inputs[24]=Fx_FFR;
inputs[25]=Fy_FFR;
inputs[26]=Mz_FFR;
inputs[27]=Fx_FFL;
inputs[28]=Fy_FFL;
inputs[29]=Mz_FFL;
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

