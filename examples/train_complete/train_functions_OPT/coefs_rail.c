/* CMO exported from MATLAB*/ 
 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
#include "coefs_rail.h"
 
double * _coefs_rail = NULL;
 
void Init_coefs_rail ( )
 {
 _coefs_rail = malloc (coefs_rail_n_rows * coefs_rail_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < coefs_rail_n_rows * coefs_rail_n_cols; i++ ) {_coefs_rail[i]=0.0;}
  }
 }
 
void Done_coefs_rail ( )
 {
  if ( _coefs_rail != NULL )
  free ( _coefs_rail );
_coefs_rail = NULL;
 }
 
double * coefs_rail ()
{
if ( _coefs_rail == NULL )
 {
  _coefs_rail = malloc ( coefs_rail_n_rows * coefs_rail_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < coefs_rail_n_rows * coefs_rail_n_cols; i++ ) {_coefs_rail[i]=0.0;}
  }
 }
 {
  _coefs_rail[0] = 9248.1504;
  _coefs_rail[1] = 9248.1504;
  _coefs_rail[2] = -109.4719;
  _coefs_rail[3] = -2.3428;
  _coefs_rail[4] = 188.2032;
  _coefs_rail[5] = 199.37;
  _coefs_rail[6] = -66.4033;
  _coefs_rail[7] = 66.4033;
  _coefs_rail[8] = -199.37;
  _coefs_rail[9] = -188.2032;
  _coefs_rail[10] = 2.3428;
  _coefs_rail[11] = 109.4719;
  _coefs_rail[12] = -9248.1504;
  _coefs_rail[13] = -9248.1504;
  _coefs_rail[14] = -282.5837;
  _coefs_rail[15] = -143.8614;
  _coefs_rail[16] = -5.1391;
  _coefs_rail[17] = -6.7812;
  _coefs_rail[18] = -6.8164;
  _coefs_rail[19] = -3.9933;
  _coefs_rail[20] = -1.0028;
  _coefs_rail[21] = -1.9988;
  _coefs_rail[22] = -1.0028;
  _coefs_rail[23] = -3.9933;
  _coefs_rail[24] = -6.8164;
  _coefs_rail[25] = -6.7812;
  _coefs_rail[26] = -5.1391;
  _coefs_rail[27] = -143.8614;
  _coefs_rail[28] = 3.0989;
  _coefs_rail[29] = 0.96663;
  _coefs_rail[30] = 0.22163;
  _coefs_rail[31] = 0.16202;
  _coefs_rail[32] = 0.094037;
  _coefs_rail[33] = 0.039988;
  _coefs_rail[34] = 0.015008;
  _coefs_rail[35] = 0;
  _coefs_rail[36] = -0.015008;
  _coefs_rail[37] = -0.039988;
  _coefs_rail[38] = -0.094037;
  _coefs_rail[39] = -0.16202;
  _coefs_rail[40] = -0.22163;
  _coefs_rail[41] = -0.96663;
  _coefs_rail[42] = 0.14493;
  _coefs_rail[43] = 0.15451;
  _coefs_rail[44] = 0.1569;
  _coefs_rail[45] = 0.15787;
  _coefs_rail[46] = 0.15851;
  _coefs_rail[47] = 0.15883;
  _coefs_rail[48] = 0.15896;
  _coefs_rail[49] = 0.159;
  _coefs_rail[50] = 0.15896;
  _coefs_rail[51] = 0.15883;
  _coefs_rail[52] = 0.15851;
  _coefs_rail[53] = 0.15787;
  _coefs_rail[54] = 0.1569;
  _coefs_rail[55] = 0.15451;
 }
return _coefs_rail;
}
