/* CMO exported from MATLAB*/ 
 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
#include "Table_Kalker.h"
 
double * _Table_Kalker = NULL;
 
void Init_Table_Kalker ( )
 {
 _Table_Kalker = malloc (Table_Kalker_n_rows * Table_Kalker_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < Table_Kalker_n_rows * Table_Kalker_n_cols; i++ ) {_Table_Kalker[i]=0.0;}
  }
 }
 
void Done_Table_Kalker ( )
 {
  if ( _Table_Kalker != NULL )
  free ( _Table_Kalker );
_Table_Kalker = NULL;
 }
 
double * Table_Kalker ()
{
if ( _Table_Kalker == NULL )
 {
  _Table_Kalker = malloc ( Table_Kalker_n_rows * Table_Kalker_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < Table_Kalker_n_rows * Table_Kalker_n_cols; i++ ) {_Table_Kalker[i]=0.0;}
  }
 }
 {
  _Table_Kalker[0] = 2.51;
  _Table_Kalker[1] = 2.59;
  _Table_Kalker[2] = 2.68;
  _Table_Kalker[3] = 2.78;
  _Table_Kalker[4] = 2.88;
  _Table_Kalker[5] = 2.98;
  _Table_Kalker[6] = 3.09;
  _Table_Kalker[7] = 3.19;
  _Table_Kalker[8] = 3.29;
  _Table_Kalker[9] = 3.4;
  _Table_Kalker[10] = 3.51;
  _Table_Kalker[11] = 3.65;
  _Table_Kalker[12] = 3.82;
  _Table_Kalker[13] = 4.06;
  _Table_Kalker[14] = 4.37;
  _Table_Kalker[15] = 4.84;
  _Table_Kalker[16] = 5.57;
  _Table_Kalker[17] = 6.96;
  _Table_Kalker[18] = 10.7;
  _Table_Kalker[19] = 3.31;
  _Table_Kalker[20] = 3.37;
  _Table_Kalker[21] = 3.44;
  _Table_Kalker[22] = 3.53;
  _Table_Kalker[23] = 3.62;
  _Table_Kalker[24] = 3.72;
  _Table_Kalker[25] = 3.81;
  _Table_Kalker[26] = 3.91;
  _Table_Kalker[27] = 4.01;
  _Table_Kalker[28] = 4.12;
  _Table_Kalker[29] = 4.22;
  _Table_Kalker[30] = 4.36;
  _Table_Kalker[31] = 4.54;
  _Table_Kalker[32] = 4.78;
  _Table_Kalker[33] = 5.1;
  _Table_Kalker[34] = 5.57;
  _Table_Kalker[35] = 6.34;
  _Table_Kalker[36] = 7.78;
  _Table_Kalker[37] = 11.7;
  _Table_Kalker[38] = 4.85;
  _Table_Kalker[39] = 4.81;
  _Table_Kalker[40] = 4.8;
  _Table_Kalker[41] = 4.82;
  _Table_Kalker[42] = 4.83;
  _Table_Kalker[43] = 4.91;
  _Table_Kalker[44] = 4.97;
  _Table_Kalker[45] = 5.05;
  _Table_Kalker[46] = 5.12;
  _Table_Kalker[47] = 5.2;
  _Table_Kalker[48] = 5.3;
  _Table_Kalker[49] = 5.42;
  _Table_Kalker[50] = 5.58;
  _Table_Kalker[51] = 5.8;
  _Table_Kalker[52] = 6.11;
  _Table_Kalker[53] = 6.57;
  _Table_Kalker[54] = 7.34;
  _Table_Kalker[55] = 8.82;
  _Table_Kalker[56] = 12.9;
  _Table_Kalker[57] = 2.51;
  _Table_Kalker[58] = 2.59;
  _Table_Kalker[59] = 2.68;
  _Table_Kalker[60] = 2.78;
  _Table_Kalker[61] = 2.88;
  _Table_Kalker[62] = 2.98;
  _Table_Kalker[63] = 3.09;
  _Table_Kalker[64] = 3.19;
  _Table_Kalker[65] = 3.29;
  _Table_Kalker[66] = 3.4;
  _Table_Kalker[67] = 3.51;
  _Table_Kalker[68] = 3.65;
  _Table_Kalker[69] = 3.82;
  _Table_Kalker[70] = 4.06;
  _Table_Kalker[71] = 4.37;
  _Table_Kalker[72] = 4.84;
  _Table_Kalker[73] = 5.57;
  _Table_Kalker[74] = 6.96;
  _Table_Kalker[75] = 10.7;
  _Table_Kalker[76] = 2.52;
  _Table_Kalker[77] = 2.63;
  _Table_Kalker[78] = 2.75;
  _Table_Kalker[79] = 2.88;
  _Table_Kalker[80] = 3.01;
  _Table_Kalker[81] = 3.14;
  _Table_Kalker[82] = 3.28;
  _Table_Kalker[83] = 3.41;
  _Table_Kalker[84] = 3.54;
  _Table_Kalker[85] = 3.67;
  _Table_Kalker[86] = 3.81;
  _Table_Kalker[87] = 3.99;
  _Table_Kalker[88] = 4.21;
  _Table_Kalker[89] = 4.5;
  _Table_Kalker[90] = 4.9;
  _Table_Kalker[91] = 5.48;
  _Table_Kalker[92] = 6.4;
  _Table_Kalker[93] = 8.14;
  _Table_Kalker[94] = 12.8;
  _Table_Kalker[95] = 2.53;
  _Table_Kalker[96] = 2.66;
  _Table_Kalker[97] = 2.81;
  _Table_Kalker[98] = 2.98;
  _Table_Kalker[99] = 3.14;
  _Table_Kalker[100] = 3.31;
  _Table_Kalker[101] = 3.48;
  _Table_Kalker[102] = 3.65;
  _Table_Kalker[103] = 3.82;
  _Table_Kalker[104] = 3.98;
  _Table_Kalker[105] = 4.16;
  _Table_Kalker[106] = 4.39;
  _Table_Kalker[107] = 4.67;
  _Table_Kalker[108] = 5.04;
  _Table_Kalker[109] = 5.56;
  _Table_Kalker[110] = 6.31;
  _Table_Kalker[111] = 7.51;
  _Table_Kalker[112] = 9.79;
  _Table_Kalker[113] = 16;
  _Table_Kalker[114] = 0.334;
  _Table_Kalker[115] = 0.483;
  _Table_Kalker[116] = 0.607;
  _Table_Kalker[117] = 0.72;
  _Table_Kalker[118] = 0.827;
  _Table_Kalker[119] = 0.93;
  _Table_Kalker[120] = 1.03;
  _Table_Kalker[121] = 1.13;
  _Table_Kalker[122] = 1.23;
  _Table_Kalker[123] = 1.33;
  _Table_Kalker[124] = 1.44;
  _Table_Kalker[125] = 1.58;
  _Table_Kalker[126] = 1.76;
  _Table_Kalker[127] = 2.01;
  _Table_Kalker[128] = 2.35;
  _Table_Kalker[129] = 2.88;
  _Table_Kalker[130] = 3.79;
  _Table_Kalker[131] = 5.72;
  _Table_Kalker[132] = 12.2;
  _Table_Kalker[133] = 0.473;
  _Table_Kalker[134] = 0.603;
  _Table_Kalker[135] = 0.715;
  _Table_Kalker[136] = 0.823;
  _Table_Kalker[137] = 0.929;
  _Table_Kalker[138] = 1.03;
  _Table_Kalker[139] = 1.14;
  _Table_Kalker[140] = 1.25;
  _Table_Kalker[141] = 1.36;
  _Table_Kalker[142] = 1.47;
  _Table_Kalker[143] = 1.59;
  _Table_Kalker[144] = 1.75;
  _Table_Kalker[145] = 1.95;
  _Table_Kalker[146] = 2.23;
  _Table_Kalker[147] = 2.62;
  _Table_Kalker[148] = 3.24;
  _Table_Kalker[149] = 4.32;
  _Table_Kalker[150] = 6.63;
  _Table_Kalker[151] = 14.6;
  _Table_Kalker[152] = 0.731;
  _Table_Kalker[153] = 0.809;
  _Table_Kalker[154] = 0.889;
  _Table_Kalker[155] = 0.977;
  _Table_Kalker[156] = 1.07;
  _Table_Kalker[157] = 1.18;
  _Table_Kalker[158] = 1.29;
  _Table_Kalker[159] = 1.4;
  _Table_Kalker[160] = 1.51;
  _Table_Kalker[161] = 1.63;
  _Table_Kalker[162] = 1.77;
  _Table_Kalker[163] = 1.94;
  _Table_Kalker[164] = 2.18;
  _Table_Kalker[165] = 2.5;
  _Table_Kalker[166] = 2.96;
  _Table_Kalker[167] = 3.7;
  _Table_Kalker[168] = 5.01;
  _Table_Kalker[169] = 7.89;
  _Table_Kalker[170] = 18;
  _Table_Kalker[171] = 6.42;
  _Table_Kalker[172] = 3.46;
  _Table_Kalker[173] = 2.49;
  _Table_Kalker[174] = 2.02;
  _Table_Kalker[175] = 1.74;
  _Table_Kalker[176] = 1.56;
  _Table_Kalker[177] = 1.43;
  _Table_Kalker[178] = 1.34;
  _Table_Kalker[179] = 1.27;
  _Table_Kalker[180] = 1.21;
  _Table_Kalker[181] = 1.16;
  _Table_Kalker[182] = 1.1;
  _Table_Kalker[183] = 1.05;
  _Table_Kalker[184] = 1.01;
  _Table_Kalker[185] = 0.958;
  _Table_Kalker[186] = 0.912;
  _Table_Kalker[187] = 0.868;
  _Table_Kalker[188] = 0.828;
  _Table_Kalker[189] = 0.795;
  _Table_Kalker[190] = 8.28;
  _Table_Kalker[191] = 4.27;
  _Table_Kalker[192] = 2.96;
  _Table_Kalker[193] = 2.32;
  _Table_Kalker[194] = 1.93;
  _Table_Kalker[195] = 1.68;
  _Table_Kalker[196] = 1.5;
  _Table_Kalker[197] = 1.37;
  _Table_Kalker[198] = 1.27;
  _Table_Kalker[199] = 1.19;
  _Table_Kalker[200] = 1.11;
  _Table_Kalker[201] = 1.04;
  _Table_Kalker[202] = 0.965;
  _Table_Kalker[203] = 0.892;
  _Table_Kalker[204] = 0.819;
  _Table_Kalker[205] = 0.747;
  _Table_Kalker[206] = 0.674;
  _Table_Kalker[207] = 0.601;
  _Table_Kalker[208] = 0.526;
  _Table_Kalker[209] = 11.7;
  _Table_Kalker[210] = 5.66;
  _Table_Kalker[211] = 3.72;
  _Table_Kalker[212] = 2.77;
  _Table_Kalker[213] = 2.22;
  _Table_Kalker[214] = 1.86;
  _Table_Kalker[215] = 1.6;
  _Table_Kalker[216] = 1.42;
  _Table_Kalker[217] = 1.27;
  _Table_Kalker[218] = 1.16;
  _Table_Kalker[219] = 1.06;
  _Table_Kalker[220] = 0.954;
  _Table_Kalker[221] = 0.852;
  _Table_Kalker[222] = 0.751;
  _Table_Kalker[223] = 0.65;
  _Table_Kalker[224] = 0.549;
  _Table_Kalker[225] = 0.446;
  _Table_Kalker[226] = 0.341;
  _Table_Kalker[227] = 0.228;
 }
return _Table_Kalker;
}
