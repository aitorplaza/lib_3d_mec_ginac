/* CMO exported from MATLAB*/ 
 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
#include "coefs_wheelL.h"
 
double * _coefs_wheelL = NULL;
 
void Init_coefs_wheelL ( )
 {
 _coefs_wheelL = malloc (coefs_wheelL_n_rows * coefs_wheelL_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < coefs_wheelL_n_rows * coefs_wheelL_n_cols; i++ ) {_coefs_wheelL[i]=0.0;}
  }
 }
 
void Done_coefs_wheelL ( )
 {
  if ( _coefs_wheelL != NULL )
  free ( _coefs_wheelL );
_coefs_wheelL = NULL;
 }
 
double * coefs_wheelL ()
{
if ( _coefs_wheelL == NULL )
 {
  _coefs_wheelL = malloc ( coefs_wheelL_n_rows * coefs_wheelL_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < coefs_wheelL_n_rows * coefs_wheelL_n_cols; i++ ) {_coefs_wheelL[i]=0.0;}
  }
 }
 {
  _coefs_wheelL[0] = 23.995;
  _coefs_wheelL[1] = 23.995;
  _coefs_wheelL[2] = -17.7898;
  _coefs_wheelL[3] = 54.974;
  _coefs_wheelL[4] = 5.0637;
  _coefs_wheelL[5] = 14.561;
  _coefs_wheelL[6] = -64.5679;
  _coefs_wheelL[7] = -59.8094;
  _coefs_wheelL[8] = 0.28555;
  _coefs_wheelL[9] = 40.7972;
  _coefs_wheelL[10] = -15452.2562;
  _coefs_wheelL[11] = 13866.7974;
  _coefs_wheelL[12] = 18125.5466;
  _coefs_wheelL[13] = -17011.4637;
  _coefs_wheelL[14] = 4625.8283;
  _coefs_wheelL[15] = -4775.4496;
  _coefs_wheelL[16] = 20623.0102;
  _coefs_wheelL[17] = 20623.0102;
  _coefs_wheelL[18] = -0.65485;
  _coefs_wheelL[19] = -0.51088;
  _coefs_wheelL[20] = 0.20897;
  _coefs_wheelL[21] = -0.32472;
  _coefs_wheelL[22] = 1.3245;
  _coefs_wheelL[23] = 1.4764;
  _coefs_wheelL[24] = 1.9132;
  _coefs_wheelL[25] = -0.023792;
  _coefs_wheelL[26] = -1.8181;
  _coefs_wheelL[27] = -1.8095;
  _coefs_wheelL[28] = -0.58559;
  _coefs_wheelL[29] = -232.3694;
  _coefs_wheelL[30] = -24.3675;
  _coefs_wheelL[31] = 247.5157;
  _coefs_wheelL[32] = -7.6562;
  _coefs_wheelL[33] = 61.7312;
  _coefs_wheelL[34] = -9.9005;
  _coefs_wheelL[35] = 299.4446;
  _coefs_wheelL[36] = -0.093226;
  _coefs_wheelL[37] = -0.095558;
  _coefs_wheelL[38] = -0.098577;
  _coefs_wheelL[39] = -0.099734;
  _coefs_wheelL[40] = -0.089736;
  _coefs_wheelL[41] = -0.061727;
  _coefs_wheelL[42] = -0.027831;
  _coefs_wheelL[43] = -0.0089361;
  _coefs_wheelL[44] = -0.027355;
  _coefs_wheelL[45] = -0.063631;
  _coefs_wheelL[46] = -0.087582;
  _coefs_wheelL[47] = -1.2524;
  _coefs_wheelL[48] = -2.536;
  _coefs_wheelL[49] = -1.4203;
  _coefs_wheelL[50] = -0.221;
  _coefs_wheelL[51] = 0.049372;
  _coefs_wheelL[52] = 0.30853;
  _coefs_wheelL[53] = 1.7562;
  _coefs_wheelL[54] = -0.4955;
  _coefs_wheelL[55] = -0.49569;
  _coefs_wheelL[56] = -0.49668;
  _coefs_wheelL[57] = -0.49766;
  _coefs_wheelL[58] = -0.49863;
  _coefs_wheelL[59] = -0.49939;
  _coefs_wheelL[60] = -0.49985;
  _coefs_wheelL[61] = -0.5;
  _coefs_wheelL[62] = -0.50015;
  _coefs_wheelL[63] = -0.50061;
  _coefs_wheelL[64] = -0.50138;
  _coefs_wheelL[65] = -0.50377;
  _coefs_wheelL[66] = -0.5141;
  _coefs_wheelL[67] = -0.52513;
  _coefs_wheelL[68] = -0.52817;
  _coefs_wheelL[69] = -0.52889;
  _coefs_wheelL[70] = -0.52769;
  _coefs_wheelL[71] = -0.52382;
 }
return _coefs_wheelL;
}
