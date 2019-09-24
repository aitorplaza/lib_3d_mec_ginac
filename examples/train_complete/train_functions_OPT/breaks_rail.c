/* CMO exported from MATLAB*/ 
 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
#include "breaks_rail.h"
 
double * _breaks_rail = NULL;
 
void Init_breaks_rail ( )
 {
 _breaks_rail = malloc (breaks_rail_n_rows * breaks_rail_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < breaks_rail_n_rows * breaks_rail_n_cols; i++ ) {_breaks_rail[i]=0.0;}
  }
 }
 
void Done_breaks_rail ( )
 {
  if ( _breaks_rail != NULL )
  free ( _breaks_rail );
_breaks_rail = NULL;
 }
 
double * breaks_rail ()
{
if ( _breaks_rail == NULL )
 {
  _breaks_rail = malloc ( breaks_rail_n_rows * breaks_rail_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < breaks_rail_n_rows * breaks_rail_n_cols; i++ ) {_breaks_rail[i]=0.0;}
  }
 }
 {
  _breaks_rail[0] = -0.035;
  _breaks_rail[1] = -0.03;
  _breaks_rail[2] = -0.025;
  _breaks_rail[3] = -0.02;
  _breaks_rail[4] = -0.015;
  _breaks_rail[5] = -0.01;
  _breaks_rail[6] = -0.005;
  _breaks_rail[7] = 0;
  _breaks_rail[8] = 0.005;
  _breaks_rail[9] = 0.01;
  _breaks_rail[10] = 0.015;
  _breaks_rail[11] = 0.02;
  _breaks_rail[12] = 0.025;
  _breaks_rail[13] = 0.03;
  _breaks_rail[14] = 0.035;
 }
return _breaks_rail;
}
