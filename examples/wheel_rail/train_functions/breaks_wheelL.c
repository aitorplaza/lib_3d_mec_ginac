/* CMO exported from MATLAB*/ 
 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
#include "breaks_wheelL.h"
 
double * _breaks_wheelL = NULL;
 
void Init_breaks_wheelL ( )
 {
 _breaks_wheelL = malloc (breaks_wheelL_n_rows * breaks_wheelL_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < breaks_wheelL_n_rows * breaks_wheelL_n_cols; i++ ) {_breaks_wheelL[i]=0.0;}
  }
 }
 
void Done_breaks_wheelL ( )
 {
  if ( _breaks_wheelL != NULL )
  free ( _breaks_wheelL );
_breaks_wheelL = NULL;
 }
 
double * breaks_wheelL ()
{
if ( _breaks_wheelL == NULL )
 {
  _breaks_wheelL = malloc ( breaks_wheelL_n_rows * breaks_wheelL_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < breaks_wheelL_n_rows * breaks_wheelL_n_cols; i++ ) {_breaks_wheelL[i]=0.0;}
  }
 }
 {
  _breaks_wheelL[0] = -0.062;
  _breaks_wheelL[1] = -0.06;
  _breaks_wheelL[2] = -0.05;
  _breaks_wheelL[3] = -0.04;
  _breaks_wheelL[4] = -0.03;
  _breaks_wheelL[5] = -0.02;
  _breaks_wheelL[6] = -0.01;
  _breaks_wheelL[7] = 0;
  _breaks_wheelL[8] = 0.01;
  _breaks_wheelL[9] = 0.02;
  _breaks_wheelL[10] = 0.03;
  _breaks_wheelL[11] = 0.035;
  _breaks_wheelL[12] = 0.04;
  _breaks_wheelL[13] = 0.045;
  _breaks_wheelL[14] = 0.05;
  _breaks_wheelL[15] = 0.055;
  _breaks_wheelL[16] = 0.06;
  _breaks_wheelL[17] = 0.065;
  _breaks_wheelL[18] = 0.068;
 }
return _breaks_wheelL;
}
