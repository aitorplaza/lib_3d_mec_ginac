// ================================================================
// RAIL data splies:
// ================================================================

double breaks_rail[1][15] = {-0.0350, -0.0300, -0.0250, -0.0200, -0.0150, -0.0100, -0.0050, 0, 0.0050, 0.0100, 0.0150, 0.0200, 0.0250, 0.0300, 0.0350};

double coefs_rail[14][4] ={
 {  9.248150377498375e+03,  -0.282583655662476e+03,   0.003098854518875e+03,   0.000144925400000e+03},
 {  9.248150377498403e+03,  -0.143861400000000e+03,   0.000966629240563e+03,   0.000154511100000e+03},
 { -0.109471887491193e+03,  -0.005139144337524e+03,   0.000221626518875e+03,   0.000156903730000e+03},
 { -0.002342827534757e+03,  -0.006781222649892e+03,   0.000162024683938e+03,   0.000157869700000e+03},
 {  0.188203197631013e+03,  -0.006816365062914e+03,   0.000094036745374e+03,   0.000158510000000e+03},
 {  0.199370037009904e+03,  -0.003993317098448e+03,   0.000039988334567e+03,   0.000158833300000e+03},
 { -0.066403345669996e+03,  -0.001002766543300e+03,   0.000015007916358e+03,   0.000158958330000e+03},
 {  0.066403345669996e+03,  -0.001998816728350e+03,   0.000000000000000e+03,   0.000159000000000e+03},
 { -0.199370037009904e+03,  -0.001002766543300e+03,  -0.000015007916358e+03,   0.000158958330000e+03},
 { -0.188203197631013e+03,  -0.003993317098448e+03,  -0.000039988334567e+03,   0.000158833300000e+03},
 {  0.002342827534756e+03,  -0.006816365062914e+03,  -0.000094036745374e+03,   0.000158510000000e+03},
 {  0.109471887491188e+03,  -0.006781222649892e+03,  -0.000162024683938e+03,   0.000157869700000e+03},
 { -9.248150377498403e+03,  -0.005139144337524e+03,  -0.000221626518875e+03,   0.000156903730000e+03},
 { -9.248150377498403e+03,  -0.143861400000000e+03,  -0.000966629240563e+03,   0.000154511100000e+03},
};

// ================================================================
// WHEEL data splies:
// ================================================================

// LEFT WHEEL
double breaks_wheelL[1][19] = { -0.062, -0.06, -0.05, -0.04, -0.03, -0.02, -0.01, 0.0, 0.01, 0.02, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.065, 0.068};

double coefs_wheelL[18][4] = {
   { 0.002399502684842e+04, -0.000065484704254e+04, -0.000009322628602e+04, -0.000049550448000e+04 },
   { 0.002399502684842e+04, -0.000051087688145e+04, -0.000009555773387e+04, -0.000049569336000e+04 },
   {-0.001778975795144e+04,  0.000020897392400e+04, -0.000009857676344e+04, -0.000049667603000e+04 },
   { 0.005497400495744e+04, -0.000032471881454e+04, -0.000009973421235e+04, -0.000049765869000e+04 },
   { 0.000506373812161e+04,  0.000132450133418e+04, -0.000008973638715e+04, -0.000049863353000e+04 },
   { 0.001456104255614e+04,  0.000147641347783e+04, -0.000006172723903e+04, -0.000049939338000e+04 },
   {-0.006456790834618e+04,  0.000191324475451e+04, -0.000002783065671e+04, -0.000049984845000e+04 },
   {-0.005980940917141e+04, -0.000002379249587e+04, -0.000000893613412e+04, -0.000050000000000e+04 },
   { 0.000028554503181e+04, -0.000181807477102e+04, -0.000002735480679e+04, -0.000050015155000e+04 },
   { 0.004079722904418e+04, -0.000180950842006e+04, -0.000006363063870e+04, -0.000050060662000e+04 },
   {-1.545225615458162e+04, -0.000058559154874e+04, -0.000008758163839e+04, -0.000050138308000e+04 },
   { 1.386679739240303e+04, -0.023236943386746e+04, -0.000125235676547e+04, -0.000050376716000e+04 },
   { 1.812554658496822e+04, -0.002436747298142e+04, -0.000253604129972e+04, -0.000051410483000e+04 },
   {-1.701146373227364e+04,  0.024751572579311e+04, -0.000142030003566e+04, -0.000052512853000e+04 },
   { 0.462582834412374e+04, -0.000765623019100e+04, -0.000022100255765e+04, -0.000052816857000e+04 },
   {-0.477544964421909e+04,  0.006173119497086e+04,  0.000004937226625e+04, -0.000052888676000e+04 },
   { 2.062301023275084e+04, -0.000990054969243e+04,  0.000030852549264e+04, -0.000052769355000e+04 },
   { 2.062301023275067e+04,  0.029944460379884e+04,  0.000175624576318e+04, -0.000052382056000e+04 },
};

// RIGHT  WHEEL
double breaks_wheelR[1][19] = {-0.068, -0.065, -0.06, -0.055, -0.05, -0.045, -0.04, -0.035, -0.03, -0.02, -0.01, -0.0,+0.01,+0.02,+0.03,+0.04,+0.05,+0.06,+0.062};

double coefs_wheelR[18][4] = {
  {-2.062301023275065e+04,   0.048505169589359e+04,  -0.000410973466225e+04,  -0.000051530000000e+04 },
  {-2.062301023275083e+04,   0.029944460379884e+04,  -0.000175624576318e+04,  -0.000052382056000e+04 },
  { 0.477544964421908e+04,  -0.000990054969243e+04,  -0.000030852549264e+04,  -0.000052769355000e+04 },
  {-0.462582834412374e+04,   0.006173119497086e+04,  -0.000004937226625e+04,  -0.000052888676000e+04 },
  { 1.701146373227364e+04,  -0.000765623019100e+04,   0.000022100255765e+04,  -0.000052816857000e+04 },
  {-1.812554658496823e+04,   0.024751572579311e+04,   0.000142030003566e+04,  -0.000052512853000e+04 },
  {-1.386679739240303e+04,  -0.002436747298142e+04,   0.000253604129972e+04,  -0.000051410483000e+04 },
  { 1.545225615458162e+04,  -0.023236943386746e+04,   0.000125235676547e+04,  -0.000050376716000e+04 },
  {-0.004079722904418e+04,  -0.000058559154874e+04,   0.000008758163839e+04,  -0.000050138308000e+04 },
  {-0.000028554503181e+04,  -0.000180950842006e+04,   0.000006363063870e+04,  -0.000050060662000e+04 },
  { 0.005980940917141e+04,  -0.000181807477102e+04,   0.000002735480679e+04,  -0.000050015155000e+04 },
  { 0.006456790834618e+04,  -0.000002379249587e+04,   0.000000893613412e+04,  -0.000050000000000e+04 },
  {-0.001456104255614e+04,   0.000191324475451e+04,   0.000002783065671e+04,  -0.000049984845000e+04 },
  {-0.000506373812161e+04,   0.000147641347783e+04,   0.000006172723903e+04,  -0.000049939338000e+04 },
  {-0.005497400495744e+04,   0.000132450133418e+04,   0.000008973638715e+04,  -0.000049863353000e+04 },
  { 0.001778975795144e+04,  -0.000032471881454e+04,   0.000009973421235e+04,  -0.000049765869000e+04 },
  {-0.002399502684842e+04,   0.000020897392400e+04,   0.000009857676344e+04,  -0.000049667603000e+04 },
  {-0.002399502684842e+04,  -0.000051087688145e+04,   0.000009555773387e+04,  -0.000049569336000e+04 },
};
