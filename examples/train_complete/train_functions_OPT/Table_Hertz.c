/* CMO exported from MATLAB*/ 
 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
#include "Table_Hertz.h"
 
double * _Table_Hertz = NULL;
 
void Init_Table_Hertz ( )
 {
 _Table_Hertz = malloc (Table_Hertz_n_rows * Table_Hertz_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < Table_Hertz_n_rows * Table_Hertz_n_cols; i++ ) {_Table_Hertz[i]=0.0;}
  }
 }
 
void Done_Table_Hertz ( )
 {
  if ( _Table_Hertz != NULL )
  free ( _Table_Hertz );
_Table_Hertz = NULL;
 }
 
double * Table_Hertz ()
{
if ( _Table_Hertz == NULL )
 {
  _Table_Hertz = malloc ( Table_Hertz_n_rows * Table_Hertz_n_cols * sizeof(double) );
  {
  int i;
  for (i = 0 ; i < Table_Hertz_n_rows * Table_Hertz_n_cols; i++ ) {_Table_Hertz[i]=0.0;}
  }
 }
 {
  _Table_Hertz[0] = 0.5;
  _Table_Hertz[1] = 1;
  _Table_Hertz[2] = 1.5;
  _Table_Hertz[3] = 2;
  _Table_Hertz[4] = 2.5;
  _Table_Hertz[5] = 3;
  _Table_Hertz[6] = 3.5;
  _Table_Hertz[7] = 4;
  _Table_Hertz[8] = 4.5;
  _Table_Hertz[9] = 5;
  _Table_Hertz[10] = 5.5;
  _Table_Hertz[11] = 6;
  _Table_Hertz[12] = 6.5;
  _Table_Hertz[13] = 7;
  _Table_Hertz[14] = 7.5;
  _Table_Hertz[15] = 8;
  _Table_Hertz[16] = 8.5;
  _Table_Hertz[17] = 9;
  _Table_Hertz[18] = 9.5;
  _Table_Hertz[19] = 10;
  _Table_Hertz[20] = 10.5;
  _Table_Hertz[21] = 11;
  _Table_Hertz[22] = 11.5;
  _Table_Hertz[23] = 12;
  _Table_Hertz[24] = 12.5;
  _Table_Hertz[25] = 13;
  _Table_Hertz[26] = 13.5;
  _Table_Hertz[27] = 14;
  _Table_Hertz[28] = 14.5;
  _Table_Hertz[29] = 15;
  _Table_Hertz[30] = 15.5;
  _Table_Hertz[31] = 16;
  _Table_Hertz[32] = 16.5;
  _Table_Hertz[33] = 17;
  _Table_Hertz[34] = 17.5;
  _Table_Hertz[35] = 18;
  _Table_Hertz[36] = 18.5;
  _Table_Hertz[37] = 19;
  _Table_Hertz[38] = 19.5;
  _Table_Hertz[39] = 20;
  _Table_Hertz[40] = 20.5;
  _Table_Hertz[41] = 21;
  _Table_Hertz[42] = 21.5;
  _Table_Hertz[43] = 22;
  _Table_Hertz[44] = 22.5;
  _Table_Hertz[45] = 23;
  _Table_Hertz[46] = 23.5;
  _Table_Hertz[47] = 24;
  _Table_Hertz[48] = 24.5;
  _Table_Hertz[49] = 25;
  _Table_Hertz[50] = 25.5;
  _Table_Hertz[51] = 26;
  _Table_Hertz[52] = 26.5;
  _Table_Hertz[53] = 27;
  _Table_Hertz[54] = 27.5;
  _Table_Hertz[55] = 28;
  _Table_Hertz[56] = 28.5;
  _Table_Hertz[57] = 29;
  _Table_Hertz[58] = 29.5;
  _Table_Hertz[59] = 30;
  _Table_Hertz[60] = 30.5;
  _Table_Hertz[61] = 31;
  _Table_Hertz[62] = 31.5;
  _Table_Hertz[63] = 32;
  _Table_Hertz[64] = 32.5;
  _Table_Hertz[65] = 33;
  _Table_Hertz[66] = 33.5;
  _Table_Hertz[67] = 34;
  _Table_Hertz[68] = 34.5;
  _Table_Hertz[69] = 35;
  _Table_Hertz[70] = 35.5;
  _Table_Hertz[71] = 36;
  _Table_Hertz[72] = 36.5;
  _Table_Hertz[73] = 37;
  _Table_Hertz[74] = 37.5;
  _Table_Hertz[75] = 38;
  _Table_Hertz[76] = 38.5;
  _Table_Hertz[77] = 39;
  _Table_Hertz[78] = 39.5;
  _Table_Hertz[79] = 40;
  _Table_Hertz[80] = 40.5;
  _Table_Hertz[81] = 41;
  _Table_Hertz[82] = 41.5;
  _Table_Hertz[83] = 42;
  _Table_Hertz[84] = 42.5;
  _Table_Hertz[85] = 43;
  _Table_Hertz[86] = 43.5;
  _Table_Hertz[87] = 44;
  _Table_Hertz[88] = 44.5;
  _Table_Hertz[89] = 45;
  _Table_Hertz[90] = 45.5;
  _Table_Hertz[91] = 46;
  _Table_Hertz[92] = 46.5;
  _Table_Hertz[93] = 47;
  _Table_Hertz[94] = 47.5;
  _Table_Hertz[95] = 48;
  _Table_Hertz[96] = 48.5;
  _Table_Hertz[97] = 49;
  _Table_Hertz[98] = 49.5;
  _Table_Hertz[99] = 50;
  _Table_Hertz[100] = 50.5;
  _Table_Hertz[101] = 51;
  _Table_Hertz[102] = 51.5;
  _Table_Hertz[103] = 52;
  _Table_Hertz[104] = 52.5;
  _Table_Hertz[105] = 53;
  _Table_Hertz[106] = 53.5;
  _Table_Hertz[107] = 54;
  _Table_Hertz[108] = 54.5;
  _Table_Hertz[109] = 55;
  _Table_Hertz[110] = 55.5;
  _Table_Hertz[111] = 56;
  _Table_Hertz[112] = 56.5;
  _Table_Hertz[113] = 57;
  _Table_Hertz[114] = 57.5;
  _Table_Hertz[115] = 58;
  _Table_Hertz[116] = 58.5;
  _Table_Hertz[117] = 59;
  _Table_Hertz[118] = 59.5;
  _Table_Hertz[119] = 60;
  _Table_Hertz[120] = 60.5;
  _Table_Hertz[121] = 61;
  _Table_Hertz[122] = 61.5;
  _Table_Hertz[123] = 62;
  _Table_Hertz[124] = 62.5;
  _Table_Hertz[125] = 63;
  _Table_Hertz[126] = 63.5;
  _Table_Hertz[127] = 64;
  _Table_Hertz[128] = 64.5;
  _Table_Hertz[129] = 65;
  _Table_Hertz[130] = 65.5;
  _Table_Hertz[131] = 66;
  _Table_Hertz[132] = 66.5;
  _Table_Hertz[133] = 67;
  _Table_Hertz[134] = 67.5;
  _Table_Hertz[135] = 68;
  _Table_Hertz[136] = 68.5;
  _Table_Hertz[137] = 69;
  _Table_Hertz[138] = 69.5;
  _Table_Hertz[139] = 70;
  _Table_Hertz[140] = 70.5;
  _Table_Hertz[141] = 71;
  _Table_Hertz[142] = 71.5;
  _Table_Hertz[143] = 72;
  _Table_Hertz[144] = 72.5;
  _Table_Hertz[145] = 73;
  _Table_Hertz[146] = 73.5;
  _Table_Hertz[147] = 74;
  _Table_Hertz[148] = 74.5;
  _Table_Hertz[149] = 75;
  _Table_Hertz[150] = 75.5;
  _Table_Hertz[151] = 76;
  _Table_Hertz[152] = 76.5;
  _Table_Hertz[153] = 77;
  _Table_Hertz[154] = 77.5;
  _Table_Hertz[155] = 78;
  _Table_Hertz[156] = 78.5;
  _Table_Hertz[157] = 79;
  _Table_Hertz[158] = 79.5;
  _Table_Hertz[159] = 80;
  _Table_Hertz[160] = 80.5;
  _Table_Hertz[161] = 81;
  _Table_Hertz[162] = 81.5;
  _Table_Hertz[163] = 82;
  _Table_Hertz[164] = 82.5;
  _Table_Hertz[165] = 83;
  _Table_Hertz[166] = 83.5;
  _Table_Hertz[167] = 84;
  _Table_Hertz[168] = 84.5;
  _Table_Hertz[169] = 85;
  _Table_Hertz[170] = 85.5;
  _Table_Hertz[171] = 86;
  _Table_Hertz[172] = 86.5;
  _Table_Hertz[173] = 87;
  _Table_Hertz[174] = 87.5;
  _Table_Hertz[175] = 88;
  _Table_Hertz[176] = 88.5;
  _Table_Hertz[177] = 89;
  _Table_Hertz[178] = 89.5;
  _Table_Hertz[179] = 90;
  _Table_Hertz[180] = 90.5;
  _Table_Hertz[181] = 91;
  _Table_Hertz[182] = 91.5;
  _Table_Hertz[183] = 92;
  _Table_Hertz[184] = 92.5;
  _Table_Hertz[185] = 93;
  _Table_Hertz[186] = 93.5;
  _Table_Hertz[187] = 94;
  _Table_Hertz[188] = 94.5;
  _Table_Hertz[189] = 95;
  _Table_Hertz[190] = 95.5;
  _Table_Hertz[191] = 96;
  _Table_Hertz[192] = 96.5;
  _Table_Hertz[193] = 97;
  _Table_Hertz[194] = 97.5;
  _Table_Hertz[195] = 98;
  _Table_Hertz[196] = 98.5;
  _Table_Hertz[197] = 99;
  _Table_Hertz[198] = 99.5;
  _Table_Hertz[199] = 100;
  _Table_Hertz[200] = 100.5;
  _Table_Hertz[201] = 101;
  _Table_Hertz[202] = 101.5;
  _Table_Hertz[203] = 102;
  _Table_Hertz[204] = 102.5;
  _Table_Hertz[205] = 103;
  _Table_Hertz[206] = 103.5;
  _Table_Hertz[207] = 104;
  _Table_Hertz[208] = 104.5;
  _Table_Hertz[209] = 105;
  _Table_Hertz[210] = 105.5;
  _Table_Hertz[211] = 106;
  _Table_Hertz[212] = 106.5;
  _Table_Hertz[213] = 107;
  _Table_Hertz[214] = 107.5;
  _Table_Hertz[215] = 108;
  _Table_Hertz[216] = 108.5;
  _Table_Hertz[217] = 109;
  _Table_Hertz[218] = 109.5;
  _Table_Hertz[219] = 110;
  _Table_Hertz[220] = 110.5;
  _Table_Hertz[221] = 111;
  _Table_Hertz[222] = 111.5;
  _Table_Hertz[223] = 112;
  _Table_Hertz[224] = 112.5;
  _Table_Hertz[225] = 113;
  _Table_Hertz[226] = 113.5;
  _Table_Hertz[227] = 114;
  _Table_Hertz[228] = 114.5;
  _Table_Hertz[229] = 115;
  _Table_Hertz[230] = 115.5;
  _Table_Hertz[231] = 116;
  _Table_Hertz[232] = 116.5;
  _Table_Hertz[233] = 117;
  _Table_Hertz[234] = 117.5;
  _Table_Hertz[235] = 118;
  _Table_Hertz[236] = 118.5;
  _Table_Hertz[237] = 119;
  _Table_Hertz[238] = 119.5;
  _Table_Hertz[239] = 120;
  _Table_Hertz[240] = 120.5;
  _Table_Hertz[241] = 121;
  _Table_Hertz[242] = 121.5;
  _Table_Hertz[243] = 122;
  _Table_Hertz[244] = 122.5;
  _Table_Hertz[245] = 123;
  _Table_Hertz[246] = 123.5;
  _Table_Hertz[247] = 124;
  _Table_Hertz[248] = 124.5;
  _Table_Hertz[249] = 125;
  _Table_Hertz[250] = 125.5;
  _Table_Hertz[251] = 126;
  _Table_Hertz[252] = 126.5;
  _Table_Hertz[253] = 127;
  _Table_Hertz[254] = 127.5;
  _Table_Hertz[255] = 128;
  _Table_Hertz[256] = 128.5;
  _Table_Hertz[257] = 129;
  _Table_Hertz[258] = 129.5;
  _Table_Hertz[259] = 130;
  _Table_Hertz[260] = 130.5;
  _Table_Hertz[261] = 131;
  _Table_Hertz[262] = 131.5;
  _Table_Hertz[263] = 132;
  _Table_Hertz[264] = 132.5;
  _Table_Hertz[265] = 133;
  _Table_Hertz[266] = 133.5;
  _Table_Hertz[267] = 134;
  _Table_Hertz[268] = 134.5;
  _Table_Hertz[269] = 135;
  _Table_Hertz[270] = 135.5;
  _Table_Hertz[271] = 136;
  _Table_Hertz[272] = 136.5;
  _Table_Hertz[273] = 137;
  _Table_Hertz[274] = 137.5;
  _Table_Hertz[275] = 138;
  _Table_Hertz[276] = 138.5;
  _Table_Hertz[277] = 139;
  _Table_Hertz[278] = 139.5;
  _Table_Hertz[279] = 140;
  _Table_Hertz[280] = 140.5;
  _Table_Hertz[281] = 141;
  _Table_Hertz[282] = 141.5;
  _Table_Hertz[283] = 142;
  _Table_Hertz[284] = 142.5;
  _Table_Hertz[285] = 143;
  _Table_Hertz[286] = 143.5;
  _Table_Hertz[287] = 144;
  _Table_Hertz[288] = 144.5;
  _Table_Hertz[289] = 145;
  _Table_Hertz[290] = 145.5;
  _Table_Hertz[291] = 146;
  _Table_Hertz[292] = 146.5;
  _Table_Hertz[293] = 147;
  _Table_Hertz[294] = 147.5;
  _Table_Hertz[295] = 148;
  _Table_Hertz[296] = 148.5;
  _Table_Hertz[297] = 149;
  _Table_Hertz[298] = 149.5;
  _Table_Hertz[299] = 150;
  _Table_Hertz[300] = 150.5;
  _Table_Hertz[301] = 151;
  _Table_Hertz[302] = 151.5;
  _Table_Hertz[303] = 152;
  _Table_Hertz[304] = 152.5;
  _Table_Hertz[305] = 153;
  _Table_Hertz[306] = 153.5;
  _Table_Hertz[307] = 154;
  _Table_Hertz[308] = 154.5;
  _Table_Hertz[309] = 155;
  _Table_Hertz[310] = 155.5;
  _Table_Hertz[311] = 156;
  _Table_Hertz[312] = 156.5;
  _Table_Hertz[313] = 157;
  _Table_Hertz[314] = 157.5;
  _Table_Hertz[315] = 158;
  _Table_Hertz[316] = 158.5;
  _Table_Hertz[317] = 159;
  _Table_Hertz[318] = 159.5;
  _Table_Hertz[319] = 160;
  _Table_Hertz[320] = 160.5;
  _Table_Hertz[321] = 161;
  _Table_Hertz[322] = 161.5;
  _Table_Hertz[323] = 162;
  _Table_Hertz[324] = 162.5;
  _Table_Hertz[325] = 163;
  _Table_Hertz[326] = 163.5;
  _Table_Hertz[327] = 164;
  _Table_Hertz[328] = 164.5;
  _Table_Hertz[329] = 165;
  _Table_Hertz[330] = 165.5;
  _Table_Hertz[331] = 166;
  _Table_Hertz[332] = 166.5;
  _Table_Hertz[333] = 167;
  _Table_Hertz[334] = 167.5;
  _Table_Hertz[335] = 168;
  _Table_Hertz[336] = 168.5;
  _Table_Hertz[337] = 169;
  _Table_Hertz[338] = 169.5;
  _Table_Hertz[339] = 170;
  _Table_Hertz[340] = 170.5;
  _Table_Hertz[341] = 171;
  _Table_Hertz[342] = 171.5;
  _Table_Hertz[343] = 172;
  _Table_Hertz[344] = 172.5;
  _Table_Hertz[345] = 173;
  _Table_Hertz[346] = 173.5;
  _Table_Hertz[347] = 174;
  _Table_Hertz[348] = 174.5;
  _Table_Hertz[349] = 175;
  _Table_Hertz[350] = 175.5;
  _Table_Hertz[351] = 176;
  _Table_Hertz[352] = 176.5;
  _Table_Hertz[353] = 177;
  _Table_Hertz[354] = 177.5;
  _Table_Hertz[355] = 178;
  _Table_Hertz[356] = 178.5;
  _Table_Hertz[357] = 179;
  _Table_Hertz[358] = 179.5;
  _Table_Hertz[359] = 61.4;
  _Table_Hertz[360] = 36.89;
  _Table_Hertz[361] = 27.48;
  _Table_Hertz[362] = 22.26;
  _Table_Hertz[363] = 19.38;
  _Table_Hertz[364] = 16.5;
  _Table_Hertz[365] = 14.905;
  _Table_Hertz[366] = 13.31;
  _Table_Hertz[367] = 12.43;
  _Table_Hertz[368] = 11.55;
  _Table_Hertz[369] = 10.67;
  _Table_Hertz[370] = 9.79;
  _Table_Hertz[371] = 9.3075;
  _Table_Hertz[372] = 8.825;
  _Table_Hertz[373] = 8.3425;
  _Table_Hertz[374] = 7.86;
  _Table_Hertz[375] = 7.546;
  _Table_Hertz[376] = 7.232;
  _Table_Hertz[377] = 6.918;
  _Table_Hertz[378] = 6.604;
  _Table_Hertz[379] = 6.4645;
  _Table_Hertz[380] = 6.3249;
  _Table_Hertz[381] = 6.1853;
  _Table_Hertz[382] = 6.0458;
  _Table_Hertz[383] = 5.9062;
  _Table_Hertz[384] = 5.7667;
  _Table_Hertz[385] = 5.6272;
  _Table_Hertz[386] = 5.4876;
  _Table_Hertz[387] = 5.3481;
  _Table_Hertz[388] = 5.2085;
  _Table_Hertz[389] = 5.069;
  _Table_Hertz[390] = 4.9294;
  _Table_Hertz[391] = 4.7899;
  _Table_Hertz[392] = 4.6503;
  _Table_Hertz[393] = 4.5107;
  _Table_Hertz[394] = 4.3712;
  _Table_Hertz[395] = 4.2317;
  _Table_Hertz[396] = 4.0921;
  _Table_Hertz[397] = 3.9526;
  _Table_Hertz[398] = 3.813;
  _Table_Hertz[399] = 3.7589;
  _Table_Hertz[400] = 3.7048;
  _Table_Hertz[401] = 3.6507;
  _Table_Hertz[402] = 3.5966;
  _Table_Hertz[403] = 3.5425;
  _Table_Hertz[404] = 3.4884;
  _Table_Hertz[405] = 3.4343;
  _Table_Hertz[406] = 3.3802;
  _Table_Hertz[407] = 3.3261;
  _Table_Hertz[408] = 3.272;
  _Table_Hertz[409] = 3.2179;
  _Table_Hertz[410] = 3.1638;
  _Table_Hertz[411] = 3.1097;
  _Table_Hertz[412] = 3.0556;
  _Table_Hertz[413] = 3.0015;
  _Table_Hertz[414] = 2.9474;
  _Table_Hertz[415] = 2.8933;
  _Table_Hertz[416] = 2.8392;
  _Table_Hertz[417] = 2.7851;
  _Table_Hertz[418] = 2.731;
  _Table_Hertz[419] = 2.6976;
  _Table_Hertz[420] = 2.6642;
  _Table_Hertz[421] = 2.6308;
  _Table_Hertz[422] = 2.5974;
  _Table_Hertz[423] = 2.564;
  _Table_Hertz[424] = 2.5306;
  _Table_Hertz[425] = 2.4972;
  _Table_Hertz[426] = 2.4638;
  _Table_Hertz[427] = 2.4304;
  _Table_Hertz[428] = 2.397;
  _Table_Hertz[429] = 2.3709;
  _Table_Hertz[430] = 2.3448;
  _Table_Hertz[431] = 2.3187;
  _Table_Hertz[432] = 2.2926;
  _Table_Hertz[433] = 2.2665;
  _Table_Hertz[434] = 2.2404;
  _Table_Hertz[435] = 2.2143;
  _Table_Hertz[436] = 2.1882;
  _Table_Hertz[437] = 2.1621;
  _Table_Hertz[438] = 2.136;
  _Table_Hertz[439] = 2.115;
  _Table_Hertz[440] = 2.094;
  _Table_Hertz[441] = 2.073;
  _Table_Hertz[442] = 2.052;
  _Table_Hertz[443] = 2.031;
  _Table_Hertz[444] = 2.01;
  _Table_Hertz[445] = 1.989;
  _Table_Hertz[446] = 1.968;
  _Table_Hertz[447] = 1.947;
  _Table_Hertz[448] = 1.926;
  _Table_Hertz[449] = 1.9088;
  _Table_Hertz[450] = 1.8916;
  _Table_Hertz[451] = 1.8744;
  _Table_Hertz[452] = 1.8572;
  _Table_Hertz[453] = 1.84;
  _Table_Hertz[454] = 1.8228;
  _Table_Hertz[455] = 1.8056;
  _Table_Hertz[456] = 1.7884;
  _Table_Hertz[457] = 1.7712;
  _Table_Hertz[458] = 1.754;
  _Table_Hertz[459] = 1.7397;
  _Table_Hertz[460] = 1.7254;
  _Table_Hertz[461] = 1.7111;
  _Table_Hertz[462] = 1.6968;
  _Table_Hertz[463] = 1.6825;
  _Table_Hertz[464] = 1.6682;
  _Table_Hertz[465] = 1.6539;
  _Table_Hertz[466] = 1.6396;
  _Table_Hertz[467] = 1.6253;
  _Table_Hertz[468] = 1.611;
  _Table_Hertz[469] = 1.5985;
  _Table_Hertz[470] = 1.586;
  _Table_Hertz[471] = 1.5735;
  _Table_Hertz[472] = 1.561;
  _Table_Hertz[473] = 1.5485;
  _Table_Hertz[474] = 1.536;
  _Table_Hertz[475] = 1.5235;
  _Table_Hertz[476] = 1.511;
  _Table_Hertz[477] = 1.4985;
  _Table_Hertz[478] = 1.486;
  _Table_Hertz[479] = 1.4752;
  _Table_Hertz[480] = 1.4644;
  _Table_Hertz[481] = 1.4536;
  _Table_Hertz[482] = 1.4428;
  _Table_Hertz[483] = 1.432;
  _Table_Hertz[484] = 1.4212;
  _Table_Hertz[485] = 1.4104;
  _Table_Hertz[486] = 1.3996;
  _Table_Hertz[487] = 1.3888;
  _Table_Hertz[488] = 1.378;
  _Table_Hertz[489] = 1.3686;
  _Table_Hertz[490] = 1.3592;
  _Table_Hertz[491] = 1.3498;
  _Table_Hertz[492] = 1.3404;
  _Table_Hertz[493] = 1.331;
  _Table_Hertz[494] = 1.3216;
  _Table_Hertz[495] = 1.3122;
  _Table_Hertz[496] = 1.3028;
  _Table_Hertz[497] = 1.2934;
  _Table_Hertz[498] = 1.284;
  _Table_Hertz[499] = 1.2758;
  _Table_Hertz[500] = 1.2676;
  _Table_Hertz[501] = 1.2594;
  _Table_Hertz[502] = 1.2512;
  _Table_Hertz[503] = 1.243;
  _Table_Hertz[504] = 1.2348;
  _Table_Hertz[505] = 1.2266;
  _Table_Hertz[506] = 1.2184;
  _Table_Hertz[507] = 1.2102;
  _Table_Hertz[508] = 1.202;
  _Table_Hertz[509] = 1.1946;
  _Table_Hertz[510] = 1.1872;
  _Table_Hertz[511] = 1.1798;
  _Table_Hertz[512] = 1.1724;
  _Table_Hertz[513] = 1.165;
  _Table_Hertz[514] = 1.1576;
  _Table_Hertz[515] = 1.1502;
  _Table_Hertz[516] = 1.1428;
  _Table_Hertz[517] = 1.1354;
  _Table_Hertz[518] = 1.128;
  _Table_Hertz[519] = 1.1213;
  _Table_Hertz[520] = 1.1146;
  _Table_Hertz[521] = 1.1079;
  _Table_Hertz[522] = 1.1012;
  _Table_Hertz[523] = 1.0945;
  _Table_Hertz[524] = 1.0878;
  _Table_Hertz[525] = 1.0811;
  _Table_Hertz[526] = 1.0744;
  _Table_Hertz[527] = 1.0677;
  _Table_Hertz[528] = 1.061;
  _Table_Hertz[529] = 1.0549;
  _Table_Hertz[530] = 1.0488;
  _Table_Hertz[531] = 1.0427;
  _Table_Hertz[532] = 1.0366;
  _Table_Hertz[533] = 1.0305;
  _Table_Hertz[534] = 1.0244;
  _Table_Hertz[535] = 1.0183;
  _Table_Hertz[536] = 1.0122;
  _Table_Hertz[537] = 1.0061;
  _Table_Hertz[538] = 1;
  _Table_Hertz[539] = 0.9944;
  _Table_Hertz[540] = 0.9888;
  _Table_Hertz[541] = 0.9832;
  _Table_Hertz[542] = 0.9776;
  _Table_Hertz[543] = 0.972;
  _Table_Hertz[544] = 0.9664;
  _Table_Hertz[545] = 0.9608;
  _Table_Hertz[546] = 0.9552;
  _Table_Hertz[547] = 0.9496;
  _Table_Hertz[548] = 0.944;
  _Table_Hertz[549] = 0.9389;
  _Table_Hertz[550] = 0.9338;
  _Table_Hertz[551] = 0.9287;
  _Table_Hertz[552] = 0.9236;
  _Table_Hertz[553] = 0.9185;
  _Table_Hertz[554] = 0.9134;
  _Table_Hertz[555] = 0.9083;
  _Table_Hertz[556] = 0.9032;
  _Table_Hertz[557] = 0.8981;
  _Table_Hertz[558] = 0.893;
  _Table_Hertz[559] = 0.8883;
  _Table_Hertz[560] = 0.8836;
  _Table_Hertz[561] = 0.8789;
  _Table_Hertz[562] = 0.8742;
  _Table_Hertz[563] = 0.8695;
  _Table_Hertz[564] = 0.8648;
  _Table_Hertz[565] = 0.8601;
  _Table_Hertz[566] = 0.8554;
  _Table_Hertz[567] = 0.8507;
  _Table_Hertz[568] = 0.846;
  _Table_Hertz[569] = 0.8416;
  _Table_Hertz[570] = 0.8372;
  _Table_Hertz[571] = 0.8328;
  _Table_Hertz[572] = 0.8284;
  _Table_Hertz[573] = 0.824;
  _Table_Hertz[574] = 0.8196;
  _Table_Hertz[575] = 0.8152;
  _Table_Hertz[576] = 0.8108;
  _Table_Hertz[577] = 0.8064;
  _Table_Hertz[578] = 0.802;
  _Table_Hertz[579] = 0.7977;
  _Table_Hertz[580] = 0.7934;
  _Table_Hertz[581] = 0.7891;
  _Table_Hertz[582] = 0.7848;
  _Table_Hertz[583] = 0.7805;
  _Table_Hertz[584] = 0.7762;
  _Table_Hertz[585] = 0.7719;
  _Table_Hertz[586] = 0.7676;
  _Table_Hertz[587] = 0.7633;
  _Table_Hertz[588] = 0.759;
  _Table_Hertz[589] = 0.7548;
  _Table_Hertz[590] = 0.7506;
  _Table_Hertz[591] = 0.7464;
  _Table_Hertz[592] = 0.7422;
  _Table_Hertz[593] = 0.738;
  _Table_Hertz[594] = 0.7338;
  _Table_Hertz[595] = 0.7296;
  _Table_Hertz[596] = 0.7254;
  _Table_Hertz[597] = 0.7212;
  _Table_Hertz[598] = 0.717;
  _Table_Hertz[599] = 0.7131;
  _Table_Hertz[600] = 0.7092;
  _Table_Hertz[601] = 0.7053;
  _Table_Hertz[602] = 0.7014;
  _Table_Hertz[603] = 0.6975;
  _Table_Hertz[604] = 0.6936;
  _Table_Hertz[605] = 0.6897;
  _Table_Hertz[606] = 0.6858;
  _Table_Hertz[607] = 0.6819;
  _Table_Hertz[608] = 0.678;
  _Table_Hertz[609] = 0.6743;
  _Table_Hertz[610] = 0.6706;
  _Table_Hertz[611] = 0.6669;
  _Table_Hertz[612] = 0.6632;
  _Table_Hertz[613] = 0.6595;
  _Table_Hertz[614] = 0.6558;
  _Table_Hertz[615] = 0.6521;
  _Table_Hertz[616] = 0.6484;
  _Table_Hertz[617] = 0.6447;
  _Table_Hertz[618] = 0.641;
  _Table_Hertz[619] = 0.6373;
  _Table_Hertz[620] = 0.6336;
  _Table_Hertz[621] = 0.6299;
  _Table_Hertz[622] = 0.6262;
  _Table_Hertz[623] = 0.6225;
  _Table_Hertz[624] = 0.6188;
  _Table_Hertz[625] = 0.6151;
  _Table_Hertz[626] = 0.6114;
  _Table_Hertz[627] = 0.6077;
  _Table_Hertz[628] = 0.604;
  _Table_Hertz[629] = 0.6003;
  _Table_Hertz[630] = 0.5966;
  _Table_Hertz[631] = 0.5929;
  _Table_Hertz[632] = 0.5892;
  _Table_Hertz[633] = 0.5855;
  _Table_Hertz[634] = 0.5818;
  _Table_Hertz[635] = 0.5781;
  _Table_Hertz[636] = 0.5744;
  _Table_Hertz[637] = 0.5707;
  _Table_Hertz[638] = 0.567;
  _Table_Hertz[639] = 0.5633;
  _Table_Hertz[640] = 0.5596;
  _Table_Hertz[641] = 0.5559;
  _Table_Hertz[642] = 0.5522;
  _Table_Hertz[643] = 0.5485;
  _Table_Hertz[644] = 0.5448;
  _Table_Hertz[645] = 0.5411;
  _Table_Hertz[646] = 0.5374;
  _Table_Hertz[647] = 0.5337;
  _Table_Hertz[648] = 0.53;
  _Table_Hertz[649] = 0.5263;
  _Table_Hertz[650] = 0.5226;
  _Table_Hertz[651] = 0.5189;
  _Table_Hertz[652] = 0.5152;
  _Table_Hertz[653] = 0.5115;
  _Table_Hertz[654] = 0.5078;
  _Table_Hertz[655] = 0.5041;
  _Table_Hertz[656] = 0.5004;
  _Table_Hertz[657] = 0.4967;
  _Table_Hertz[658] = 0.493;
  _Table_Hertz[659] = 0.48896;
  _Table_Hertz[660] = 0.48493;
  _Table_Hertz[661] = 0.4809;
  _Table_Hertz[662] = 0.47686;
  _Table_Hertz[663] = 0.47282;
  _Table_Hertz[664] = 0.46879;
  _Table_Hertz[665] = 0.46475;
  _Table_Hertz[666] = 0.46072;
  _Table_Hertz[667] = 0.45669;
  _Table_Hertz[668] = 0.45265;
  _Table_Hertz[669] = 0.44861;
  _Table_Hertz[670] = 0.44458;
  _Table_Hertz[671] = 0.44055;
  _Table_Hertz[672] = 0.43651;
  _Table_Hertz[673] = 0.43247;
  _Table_Hertz[674] = 0.42844;
  _Table_Hertz[675] = 0.42441;
  _Table_Hertz[676] = 0.42037;
  _Table_Hertz[677] = 0.41634;
  _Table_Hertz[678] = 0.4123;
  _Table_Hertz[679] = 0.40725;
  _Table_Hertz[680] = 0.40219;
  _Table_Hertz[681] = 0.39714;
  _Table_Hertz[682] = 0.39208;
  _Table_Hertz[683] = 0.38703;
  _Table_Hertz[684] = 0.38197;
  _Table_Hertz[685] = 0.37692;
  _Table_Hertz[686] = 0.37186;
  _Table_Hertz[687] = 0.3668;
  _Table_Hertz[688] = 0.36175;
  _Table_Hertz[689] = 0.35669;
  _Table_Hertz[690] = 0.35164;
  _Table_Hertz[691] = 0.34658;
  _Table_Hertz[692] = 0.34153;
  _Table_Hertz[693] = 0.33647;
  _Table_Hertz[694] = 0.33142;
  _Table_Hertz[695] = 0.32637;
  _Table_Hertz[696] = 0.32131;
  _Table_Hertz[697] = 0.31625;
  _Table_Hertz[698] = 0.3112;
  _Table_Hertz[699] = 0.30465;
  _Table_Hertz[700] = 0.2981;
  _Table_Hertz[701] = 0.29155;
  _Table_Hertz[702] = 0.285;
  _Table_Hertz[703] = 0.27755;
  _Table_Hertz[704] = 0.2701;
  _Table_Hertz[705] = 0.26265;
  _Table_Hertz[706] = 0.2552;
  _Table_Hertz[707] = 0.2461;
  _Table_Hertz[708] = 0.237;
  _Table_Hertz[709] = 0.2279;
  _Table_Hertz[710] = 0.2188;
  _Table_Hertz[711] = 0.2076;
  _Table_Hertz[712] = 0.1964;
  _Table_Hertz[713] = 0.18275;
  _Table_Hertz[714] = 0.1691;
  _Table_Hertz[715] = 0.1522;
  _Table_Hertz[716] = 0.1314;
  _Table_Hertz[717] = 0.1018;
  _Table_Hertz[718] = 0.1018;
  _Table_Hertz[719] = 0.1314;
  _Table_Hertz[720] = 0.1522;
  _Table_Hertz[721] = 0.1691;
  _Table_Hertz[722] = 0.18275;
  _Table_Hertz[723] = 0.1964;
  _Table_Hertz[724] = 0.2076;
  _Table_Hertz[725] = 0.2188;
  _Table_Hertz[726] = 0.2279;
  _Table_Hertz[727] = 0.237;
  _Table_Hertz[728] = 0.2461;
  _Table_Hertz[729] = 0.2552;
  _Table_Hertz[730] = 0.26265;
  _Table_Hertz[731] = 0.2701;
  _Table_Hertz[732] = 0.27755;
  _Table_Hertz[733] = 0.285;
  _Table_Hertz[734] = 0.29155;
  _Table_Hertz[735] = 0.2981;
  _Table_Hertz[736] = 0.30465;
  _Table_Hertz[737] = 0.3112;
  _Table_Hertz[738] = 0.31625;
  _Table_Hertz[739] = 0.32131;
  _Table_Hertz[740] = 0.32636;
  _Table_Hertz[741] = 0.33142;
  _Table_Hertz[742] = 0.33647;
  _Table_Hertz[743] = 0.34153;
  _Table_Hertz[744] = 0.34658;
  _Table_Hertz[745] = 0.35164;
  _Table_Hertz[746] = 0.35669;
  _Table_Hertz[747] = 0.36175;
  _Table_Hertz[748] = 0.3668;
  _Table_Hertz[749] = 0.37186;
  _Table_Hertz[750] = 0.37692;
  _Table_Hertz[751] = 0.38197;
  _Table_Hertz[752] = 0.38703;
  _Table_Hertz[753] = 0.39208;
  _Table_Hertz[754] = 0.39714;
  _Table_Hertz[755] = 0.40219;
  _Table_Hertz[756] = 0.40724;
  _Table_Hertz[757] = 0.4123;
  _Table_Hertz[758] = 0.41634;
  _Table_Hertz[759] = 0.42037;
  _Table_Hertz[760] = 0.4244;
  _Table_Hertz[761] = 0.42844;
  _Table_Hertz[762] = 0.43247;
  _Table_Hertz[763] = 0.43651;
  _Table_Hertz[764] = 0.44055;
  _Table_Hertz[765] = 0.44458;
  _Table_Hertz[766] = 0.44861;
  _Table_Hertz[767] = 0.45265;
  _Table_Hertz[768] = 0.45669;
  _Table_Hertz[769] = 0.46072;
  _Table_Hertz[770] = 0.46475;
  _Table_Hertz[771] = 0.46879;
  _Table_Hertz[772] = 0.47282;
  _Table_Hertz[773] = 0.47686;
  _Table_Hertz[774] = 0.48089;
  _Table_Hertz[775] = 0.48493;
  _Table_Hertz[776] = 0.48896;
  _Table_Hertz[777] = 0.493;
  _Table_Hertz[778] = 0.4967;
  _Table_Hertz[779] = 0.5004;
  _Table_Hertz[780] = 0.5041;
  _Table_Hertz[781] = 0.5078;
  _Table_Hertz[782] = 0.5115;
  _Table_Hertz[783] = 0.5152;
  _Table_Hertz[784] = 0.5189;
  _Table_Hertz[785] = 0.5226;
  _Table_Hertz[786] = 0.5263;
  _Table_Hertz[787] = 0.53;
  _Table_Hertz[788] = 0.5337;
  _Table_Hertz[789] = 0.5374;
  _Table_Hertz[790] = 0.5411;
  _Table_Hertz[791] = 0.5448;
  _Table_Hertz[792] = 0.5485;
  _Table_Hertz[793] = 0.5522;
  _Table_Hertz[794] = 0.5559;
  _Table_Hertz[795] = 0.5596;
  _Table_Hertz[796] = 0.5633;
  _Table_Hertz[797] = 0.567;
  _Table_Hertz[798] = 0.5707;
  _Table_Hertz[799] = 0.5744;
  _Table_Hertz[800] = 0.5781;
  _Table_Hertz[801] = 0.5818;
  _Table_Hertz[802] = 0.5855;
  _Table_Hertz[803] = 0.5892;
  _Table_Hertz[804] = 0.5929;
  _Table_Hertz[805] = 0.5966;
  _Table_Hertz[806] = 0.6003;
  _Table_Hertz[807] = 0.604;
  _Table_Hertz[808] = 0.6077;
  _Table_Hertz[809] = 0.6114;
  _Table_Hertz[810] = 0.6151;
  _Table_Hertz[811] = 0.6188;
  _Table_Hertz[812] = 0.6225;
  _Table_Hertz[813] = 0.6262;
  _Table_Hertz[814] = 0.6299;
  _Table_Hertz[815] = 0.6336;
  _Table_Hertz[816] = 0.6373;
  _Table_Hertz[817] = 0.641;
  _Table_Hertz[818] = 0.6447;
  _Table_Hertz[819] = 0.6484;
  _Table_Hertz[820] = 0.6521;
  _Table_Hertz[821] = 0.6558;
  _Table_Hertz[822] = 0.6595;
  _Table_Hertz[823] = 0.6632;
  _Table_Hertz[824] = 0.6669;
  _Table_Hertz[825] = 0.6706;
  _Table_Hertz[826] = 0.6743;
  _Table_Hertz[827] = 0.678;
  _Table_Hertz[828] = 0.6819;
  _Table_Hertz[829] = 0.6858;
  _Table_Hertz[830] = 0.6897;
  _Table_Hertz[831] = 0.6936;
  _Table_Hertz[832] = 0.6975;
  _Table_Hertz[833] = 0.7014;
  _Table_Hertz[834] = 0.7053;
  _Table_Hertz[835] = 0.7092;
  _Table_Hertz[836] = 0.7131;
  _Table_Hertz[837] = 0.717;
  _Table_Hertz[838] = 0.7212;
  _Table_Hertz[839] = 0.7254;
  _Table_Hertz[840] = 0.7296;
  _Table_Hertz[841] = 0.7338;
  _Table_Hertz[842] = 0.738;
  _Table_Hertz[843] = 0.7422;
  _Table_Hertz[844] = 0.7464;
  _Table_Hertz[845] = 0.7506;
  _Table_Hertz[846] = 0.7548;
  _Table_Hertz[847] = 0.759;
  _Table_Hertz[848] = 0.7633;
  _Table_Hertz[849] = 0.7676;
  _Table_Hertz[850] = 0.7719;
  _Table_Hertz[851] = 0.7762;
  _Table_Hertz[852] = 0.7805;
  _Table_Hertz[853] = 0.7848;
  _Table_Hertz[854] = 0.7891;
  _Table_Hertz[855] = 0.7934;
  _Table_Hertz[856] = 0.7977;
  _Table_Hertz[857] = 0.802;
  _Table_Hertz[858] = 0.8064;
  _Table_Hertz[859] = 0.8108;
  _Table_Hertz[860] = 0.8152;
  _Table_Hertz[861] = 0.8196;
  _Table_Hertz[862] = 0.824;
  _Table_Hertz[863] = 0.8284;
  _Table_Hertz[864] = 0.8328;
  _Table_Hertz[865] = 0.8372;
  _Table_Hertz[866] = 0.8416;
  _Table_Hertz[867] = 0.846;
  _Table_Hertz[868] = 0.8507;
  _Table_Hertz[869] = 0.8554;
  _Table_Hertz[870] = 0.8601;
  _Table_Hertz[871] = 0.8648;
  _Table_Hertz[872] = 0.8695;
  _Table_Hertz[873] = 0.8742;
  _Table_Hertz[874] = 0.8789;
  _Table_Hertz[875] = 0.8836;
  _Table_Hertz[876] = 0.8883;
  _Table_Hertz[877] = 0.893;
  _Table_Hertz[878] = 0.8981;
  _Table_Hertz[879] = 0.9032;
  _Table_Hertz[880] = 0.9083;
  _Table_Hertz[881] = 0.9134;
  _Table_Hertz[882] = 0.9185;
  _Table_Hertz[883] = 0.9236;
  _Table_Hertz[884] = 0.9287;
  _Table_Hertz[885] = 0.9338;
  _Table_Hertz[886] = 0.9389;
  _Table_Hertz[887] = 0.944;
  _Table_Hertz[888] = 0.9496;
  _Table_Hertz[889] = 0.9552;
  _Table_Hertz[890] = 0.9608;
  _Table_Hertz[891] = 0.9664;
  _Table_Hertz[892] = 0.972;
  _Table_Hertz[893] = 0.9776;
  _Table_Hertz[894] = 0.9832;
  _Table_Hertz[895] = 0.9888;
  _Table_Hertz[896] = 0.9944;
  _Table_Hertz[897] = 1;
  _Table_Hertz[898] = 1.0061;
  _Table_Hertz[899] = 1.0122;
  _Table_Hertz[900] = 1.0183;
  _Table_Hertz[901] = 1.0244;
  _Table_Hertz[902] = 1.0305;
  _Table_Hertz[903] = 1.0366;
  _Table_Hertz[904] = 1.0427;
  _Table_Hertz[905] = 1.0488;
  _Table_Hertz[906] = 1.0549;
  _Table_Hertz[907] = 1.061;
  _Table_Hertz[908] = 1.0677;
  _Table_Hertz[909] = 1.0744;
  _Table_Hertz[910] = 1.0811;
  _Table_Hertz[911] = 1.0878;
  _Table_Hertz[912] = 1.0945;
  _Table_Hertz[913] = 1.1012;
  _Table_Hertz[914] = 1.1079;
  _Table_Hertz[915] = 1.1146;
  _Table_Hertz[916] = 1.1213;
  _Table_Hertz[917] = 1.128;
  _Table_Hertz[918] = 1.1354;
  _Table_Hertz[919] = 1.1428;
  _Table_Hertz[920] = 1.1502;
  _Table_Hertz[921] = 1.1576;
  _Table_Hertz[922] = 1.165;
  _Table_Hertz[923] = 1.1724;
  _Table_Hertz[924] = 1.1798;
  _Table_Hertz[925] = 1.1872;
  _Table_Hertz[926] = 1.1946;
  _Table_Hertz[927] = 1.202;
  _Table_Hertz[928] = 1.2102;
  _Table_Hertz[929] = 1.2184;
  _Table_Hertz[930] = 1.2266;
  _Table_Hertz[931] = 1.2348;
  _Table_Hertz[932] = 1.243;
  _Table_Hertz[933] = 1.2512;
  _Table_Hertz[934] = 1.2594;
  _Table_Hertz[935] = 1.2676;
  _Table_Hertz[936] = 1.2758;
  _Table_Hertz[937] = 1.284;
  _Table_Hertz[938] = 1.2934;
  _Table_Hertz[939] = 1.3028;
  _Table_Hertz[940] = 1.3122;
  _Table_Hertz[941] = 1.3216;
  _Table_Hertz[942] = 1.331;
  _Table_Hertz[943] = 1.3404;
  _Table_Hertz[944] = 1.3498;
  _Table_Hertz[945] = 1.3592;
  _Table_Hertz[946] = 1.3686;
  _Table_Hertz[947] = 1.378;
  _Table_Hertz[948] = 1.3888;
  _Table_Hertz[949] = 1.3996;
  _Table_Hertz[950] = 1.4104;
  _Table_Hertz[951] = 1.4212;
  _Table_Hertz[952] = 1.432;
  _Table_Hertz[953] = 1.4428;
  _Table_Hertz[954] = 1.4536;
  _Table_Hertz[955] = 1.4644;
  _Table_Hertz[956] = 1.4752;
  _Table_Hertz[957] = 1.486;
  _Table_Hertz[958] = 1.4985;
  _Table_Hertz[959] = 1.511;
  _Table_Hertz[960] = 1.5235;
  _Table_Hertz[961] = 1.536;
  _Table_Hertz[962] = 1.5485;
  _Table_Hertz[963] = 1.561;
  _Table_Hertz[964] = 1.5735;
  _Table_Hertz[965] = 1.586;
  _Table_Hertz[966] = 1.5985;
  _Table_Hertz[967] = 1.611;
  _Table_Hertz[968] = 1.6253;
  _Table_Hertz[969] = 1.6396;
  _Table_Hertz[970] = 1.6539;
  _Table_Hertz[971] = 1.6682;
  _Table_Hertz[972] = 1.6825;
  _Table_Hertz[973] = 1.6968;
  _Table_Hertz[974] = 1.7111;
  _Table_Hertz[975] = 1.7254;
  _Table_Hertz[976] = 1.7397;
  _Table_Hertz[977] = 1.754;
  _Table_Hertz[978] = 1.7712;
  _Table_Hertz[979] = 1.7884;
  _Table_Hertz[980] = 1.8056;
  _Table_Hertz[981] = 1.8228;
  _Table_Hertz[982] = 1.84;
  _Table_Hertz[983] = 1.8572;
  _Table_Hertz[984] = 1.8744;
  _Table_Hertz[985] = 1.8916;
  _Table_Hertz[986] = 1.9088;
  _Table_Hertz[987] = 1.926;
  _Table_Hertz[988] = 1.947;
  _Table_Hertz[989] = 1.968;
  _Table_Hertz[990] = 1.989;
  _Table_Hertz[991] = 2.01;
  _Table_Hertz[992] = 2.031;
  _Table_Hertz[993] = 2.052;
  _Table_Hertz[994] = 2.073;
  _Table_Hertz[995] = 2.094;
  _Table_Hertz[996] = 2.115;
  _Table_Hertz[997] = 2.136;
  _Table_Hertz[998] = 2.1621;
  _Table_Hertz[999] = 2.1882;
  _Table_Hertz[1000] = 2.2143;
  _Table_Hertz[1001] = 2.2404;
  _Table_Hertz[1002] = 2.2665;
  _Table_Hertz[1003] = 2.2926;
  _Table_Hertz[1004] = 2.3187;
  _Table_Hertz[1005] = 2.3448;
  _Table_Hertz[1006] = 2.3709;
  _Table_Hertz[1007] = 2.397;
  _Table_Hertz[1008] = 2.4304;
  _Table_Hertz[1009] = 2.4638;
  _Table_Hertz[1010] = 2.4972;
  _Table_Hertz[1011] = 2.5306;
  _Table_Hertz[1012] = 2.564;
  _Table_Hertz[1013] = 2.5974;
  _Table_Hertz[1014] = 2.6308;
  _Table_Hertz[1015] = 2.6642;
  _Table_Hertz[1016] = 2.6976;
  _Table_Hertz[1017] = 2.731;
  _Table_Hertz[1018] = 2.7851;
  _Table_Hertz[1019] = 2.8392;
  _Table_Hertz[1020] = 2.8933;
  _Table_Hertz[1021] = 2.9474;
  _Table_Hertz[1022] = 3.0015;
  _Table_Hertz[1023] = 3.0556;
  _Table_Hertz[1024] = 3.1097;
  _Table_Hertz[1025] = 3.1638;
  _Table_Hertz[1026] = 3.2179;
  _Table_Hertz[1027] = 3.272;
  _Table_Hertz[1028] = 3.3261;
  _Table_Hertz[1029] = 3.3802;
  _Table_Hertz[1030] = 3.4343;
  _Table_Hertz[1031] = 3.4884;
  _Table_Hertz[1032] = 3.5425;
  _Table_Hertz[1033] = 3.5966;
  _Table_Hertz[1034] = 3.6507;
  _Table_Hertz[1035] = 3.7048;
  _Table_Hertz[1036] = 3.7589;
  _Table_Hertz[1037] = 3.813;
  _Table_Hertz[1038] = 3.9526;
  _Table_Hertz[1039] = 4.0921;
  _Table_Hertz[1040] = 4.2317;
  _Table_Hertz[1041] = 4.3712;
  _Table_Hertz[1042] = 4.5107;
  _Table_Hertz[1043] = 4.6503;
  _Table_Hertz[1044] = 4.7899;
  _Table_Hertz[1045] = 4.9294;
  _Table_Hertz[1046] = 5.069;
  _Table_Hertz[1047] = 5.2085;
  _Table_Hertz[1048] = 5.3481;
  _Table_Hertz[1049] = 5.4876;
  _Table_Hertz[1050] = 5.6272;
  _Table_Hertz[1051] = 5.7667;
  _Table_Hertz[1052] = 5.9062;
  _Table_Hertz[1053] = 6.0458;
  _Table_Hertz[1054] = 6.1853;
  _Table_Hertz[1055] = 6.3249;
  _Table_Hertz[1056] = 6.4644;
  _Table_Hertz[1057] = 6.604;
  _Table_Hertz[1058] = 6.918;
  _Table_Hertz[1059] = 7.232;
  _Table_Hertz[1060] = 7.546;
  _Table_Hertz[1061] = 7.86;
  _Table_Hertz[1062] = 8.3425;
  _Table_Hertz[1063] = 8.825;
  _Table_Hertz[1064] = 9.3075;
  _Table_Hertz[1065] = 9.79;
  _Table_Hertz[1066] = 10.67;
  _Table_Hertz[1067] = 11.55;
  _Table_Hertz[1068] = 12.43;
  _Table_Hertz[1069] = 13.31;
  _Table_Hertz[1070] = 14.905;
  _Table_Hertz[1071] = 16.5;
  _Table_Hertz[1072] = 19.38;
  _Table_Hertz[1073] = 22.26;
  _Table_Hertz[1074] = 27.48;
  _Table_Hertz[1075] = 36.89;
  _Table_Hertz[1076] = 61.4;
 }
return _Table_Hertz;
}
