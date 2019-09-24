/* CMO exported from MATLAB*/ 
 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
#include "breaks_wheelR.h"
 
double * _breaks_wheelR = NULL;
 
void Init_breaks_wheelR ( )
 {
 _breaks_wheelR = malloc (breaks_wheelR_n_rows * breaks_wheelR_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < breaks_wheelR_n_rows * breaks_wheelR_n_cols; i++ ) {_breaks_wheelR[i]=0.0;}
  }
 }
 
void Done_breaks_wheelR ( )
 {
  if ( _breaks_wheelR != NULL )
  free ( _breaks_wheelR );
_breaks_wheelR = NULL;
 }
 
double * breaks_wheelR ()
{
if ( _breaks_wheelR == NULL )
 {
  _breaks_wheelR = malloc ( breaks_wheelR_n_rows * breaks_wheelR_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < breaks_wheelR_n_rows * breaks_wheelR_n_cols; i++ ) {_breaks_wheelR[i]=0.0;}
  }
 }
 {
  _breaks_wheelR[0] = -0.068;
  _breaks_wheelR[1] = -0.065;
  _breaks_wheelR[2] = -0.06;
  _breaks_wheelR[3] = -0.055;
  _breaks_wheelR[4] = -0.05;
  _breaks_wheelR[5] = -0.045;
  _breaks_wheelR[6] = -0.04;
  _breaks_wheelR[7] = -0.035;
  _breaks_wheelR[8] = -0.03;
  _breaks_wheelR[9] = -0.02;
  _breaks_wheelR[10] = -0.01;
  _breaks_wheelR[11] = 0;
  _breaks_wheelR[12] = 0.01;
  _breaks_wheelR[13] = 0.02;
  _breaks_wheelR[14] = 0.03;
  _breaks_wheelR[15] = 0.04;
  _breaks_wheelR[16] = 0.05;
  _breaks_wheelR[17] = 0.06;
  _breaks_wheelR[18] = 0.062;
 }
return _breaks_wheelR;
}
