/* CMO exported from MATLAB*/ 
 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
#include "coefs_wheelR.h"
 
double * _coefs_wheelR = NULL;
 
void Init_coefs_wheelR ( )
 {
 _coefs_wheelR = malloc (coefs_wheelR_n_rows * coefs_wheelR_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < coefs_wheelR_n_rows * coefs_wheelR_n_cols; i++ ) {_coefs_wheelR[i]=0.0;}
  }
 }
 
void Done_coefs_wheelR ( )
 {
  if ( _coefs_wheelR != NULL )
  free ( _coefs_wheelR );
_coefs_wheelR = NULL;
 }
 
double * coefs_wheelR ()
{
if ( _coefs_wheelR == NULL )
 {
  _coefs_wheelR = malloc ( coefs_wheelR_n_rows * coefs_wheelR_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < coefs_wheelR_n_rows * coefs_wheelR_n_cols; i++ ) {_coefs_wheelR[i]=0.0;}
  }
 }
 {
  _coefs_wheelR[0] = -20623.0102;
  _coefs_wheelR[1] = -20623.0102;
  _coefs_wheelR[2] = 4775.4496;
  _coefs_wheelR[3] = -4625.8283;
  _coefs_wheelR[4] = 17011.4637;
  _coefs_wheelR[5] = -18125.5466;
  _coefs_wheelR[6] = -13866.7974;
  _coefs_wheelR[7] = 15452.2562;
  _coefs_wheelR[8] = -40.7972;
  _coefs_wheelR[9] = -0.28555;
  _coefs_wheelR[10] = 59.8094;
  _coefs_wheelR[11] = 64.5679;
  _coefs_wheelR[12] = -14.561;
  _coefs_wheelR[13] = -5.0637;
  _coefs_wheelR[14] = -54.974;
  _coefs_wheelR[15] = 17.7898;
  _coefs_wheelR[16] = -23.995;
  _coefs_wheelR[17] = -23.995;
  _coefs_wheelR[18] = 485.0517;
  _coefs_wheelR[19] = 299.4446;
  _coefs_wheelR[20] = -9.9005;
  _coefs_wheelR[21] = 61.7312;
  _coefs_wheelR[22] = -7.6562;
  _coefs_wheelR[23] = 247.5157;
  _coefs_wheelR[24] = -24.3675;
  _coefs_wheelR[25] = -232.3694;
  _coefs_wheelR[26] = -0.58559;
  _coefs_wheelR[27] = -1.8095;
  _coefs_wheelR[28] = -1.8181;
  _coefs_wheelR[29] = -0.023792;
  _coefs_wheelR[30] = 1.9132;
  _coefs_wheelR[31] = 1.4764;
  _coefs_wheelR[32] = 1.3245;
  _coefs_wheelR[33] = -0.32472;
  _coefs_wheelR[34] = 0.20897;
  _coefs_wheelR[35] = -0.51088;
  _coefs_wheelR[36] = -4.1097;
  _coefs_wheelR[37] = -1.7562;
  _coefs_wheelR[38] = -0.30853;
  _coefs_wheelR[39] = -0.049372;
  _coefs_wheelR[40] = 0.221;
  _coefs_wheelR[41] = 1.4203;
  _coefs_wheelR[42] = 2.536;
  _coefs_wheelR[43] = 1.2524;
  _coefs_wheelR[44] = 0.087582;
  _coefs_wheelR[45] = 0.063631;
  _coefs_wheelR[46] = 0.027355;
  _coefs_wheelR[47] = 0.0089361;
  _coefs_wheelR[48] = 0.027831;
  _coefs_wheelR[49] = 0.061727;
  _coefs_wheelR[50] = 0.089736;
  _coefs_wheelR[51] = 0.099734;
  _coefs_wheelR[52] = 0.098577;
  _coefs_wheelR[53] = 0.095558;
  _coefs_wheelR[54] = -0.5153;
  _coefs_wheelR[55] = -0.52382;
  _coefs_wheelR[56] = -0.52769;
  _coefs_wheelR[57] = -0.52889;
  _coefs_wheelR[58] = -0.52817;
  _coefs_wheelR[59] = -0.52513;
  _coefs_wheelR[60] = -0.5141;
  _coefs_wheelR[61] = -0.50377;
  _coefs_wheelR[62] = -0.50138;
  _coefs_wheelR[63] = -0.50061;
  _coefs_wheelR[64] = -0.50015;
  _coefs_wheelR[65] = -0.5;
  _coefs_wheelR[66] = -0.49985;
  _coefs_wheelR[67] = -0.49939;
  _coefs_wheelR[68] = -0.49863;
  _coefs_wheelR[69] = -0.49766;
  _coefs_wheelR[70] = -0.49668;
  _coefs_wheelR[71] = -0.49569;
 }
return _coefs_wheelR;
}
