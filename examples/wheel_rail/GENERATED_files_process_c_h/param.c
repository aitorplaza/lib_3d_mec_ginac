#include <stdlib.h>
#include "param.h"

#define g 9.8000000000000007e+00
#define a_pend 0.0000000000000000e+00
#define b_pend 0.0000000000000000e+00
#define L_R 1.0699999999999998e+00
#define L_WHS 1.0700000000000001e+00
#define a_rail 0.0000000000000000e+00
#define mWHS 1.2220000000000000e+03
#define I_WHSx 3.7660000000000002e+02
#define I_WHSy 7.9599999999999994e+01
#define I_WHSz 3.7660000000000002e+02
#define tor 0.0000000000000000e+00
#define asR 0.0000000000000000e+00
#define bsR 0.0000000000000000e+00
#define csR 0.0000000000000000e+00
#define dsR 0.0000000000000000e+00
#define esR 0.0000000000000000e+00
#define fsR 0.0000000000000000e+00
#define stasR 0.0000000000000000e+00
#define endsR 1.0000000000000000e+01
#define usRz 0.0000000000000000e+00
#define aW_R 0.0000000000000000e+00
#define bW_R 0.0000000000000000e+00
#define cW_R -1.0000000000000001e-01
#define dW_R -5.0000000000000000e-01
#define lW_R 0.0000000000000000e+00
#define aR_R 0.0000000000000000e+00
#define bR_R -2.0000000000000000e+01
#define cR_R 0.0000000000000000e+00
#define dR_R 1.0000000000000001e-01
#define lR_R 0.0000000000000000e+00
#define asL 0.0000000000000000e+00
#define bsL 0.0000000000000000e+00
#define csL 0.0000000000000000e+00
#define dsL 0.0000000000000000e+00
#define esL 0.0000000000000000e+00
#define fsL 0.0000000000000000e+00
#define stasL 0.0000000000000000e+00
#define endsL 1.0000000000000000e+01
#define usLz 0.0000000000000000e+00
#define aW_L 0.0000000000000000e+00
#define bW_L 0.0000000000000000e+00
#define cW_L 1.0000000000000001e-01
#define dW_L -5.0000000000000000e-01
#define lW_L 0.0000000000000000e+00
#define aR_L 0.0000000000000000e+00
#define bR_L -2.0000000000000000e+01
#define cR_L 0.0000000000000000e+00
#define dR_L 1.0000000000000001e-01
#define lR_L 0.0000000000000000e+00
#define E_elastic 2.1000000000000000e+11
#define nu_poisson 2.7000000000000002e-01
#define G_elastic 1.4384000000000000e+11
#define aR 0.0000000000000000e+00
#define bR 0.0000000000000000e+00
#define aL 0.0000000000000000e+00
#define bL 0.0000000000000000e+00
#define C11R 0.0000000000000000e+00
#define C22R 0.0000000000000000e+00
#define C23R 0.0000000000000000e+00
#define C33R 0.0000000000000000e+00
#define C11L 0.0000000000000000e+00
#define C22L 0.0000000000000000e+00
#define C23L 0.0000000000000000e+00
#define C33L 0.0000000000000000e+00
#define y0 0.0000000000000000e+00
#define b0 0.0000000000000000e+00

double * param=NULL; 

void Init_param_values ( void )
{
param[0]=g;
param[1]=a_pend;
param[2]=b_pend;
param[3]=L_R;
param[4]=L_WHS;
param[5]=a_rail;
param[6]=mWHS;
param[7]=I_WHSx;
param[8]=I_WHSy;
param[9]=I_WHSz;
param[10]=tor;
param[11]=asR;
param[12]=bsR;
param[13]=csR;
param[14]=dsR;
param[15]=esR;
param[16]=fsR;
param[17]=stasR;
param[18]=endsR;
param[19]=usRz;
param[20]=aW_R;
param[21]=bW_R;
param[22]=cW_R;
param[23]=dW_R;
param[24]=lW_R;
param[25]=aR_R;
param[26]=bR_R;
param[27]=cR_R;
param[28]=dR_R;
param[29]=lR_R;
param[30]=asL;
param[31]=bsL;
param[32]=csL;
param[33]=dsL;
param[34]=esL;
param[35]=fsL;
param[36]=stasL;
param[37]=endsL;
param[38]=usLz;
param[39]=aW_L;
param[40]=bW_L;
param[41]=cW_L;
param[42]=dW_L;
param[43]=lW_L;
param[44]=aR_L;
param[45]=bR_L;
param[46]=cR_L;
param[47]=dR_L;
param[48]=lR_L;
param[49]=E_elastic;
param[50]=nu_poisson;
param[51]=G_elastic;
param[52]=aR;
param[53]=bR;
param[54]=aL;
param[55]=bL;
param[56]=C11R;
param[57]=C22R;
param[58]=C23R;
param[59]=C33R;
param[60]=C11L;
param[61]=C22L;
param[62]=C23L;
param[63]=C33L;
param[64]=y0;
param[65]=b0;
}

void Init_param ( )
{
 param = malloc ( n_param * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_param ; i++ ) {param[i]=0.0;}
 }
}

void Done_param( ) 
{
if ( param != NULL) 
free ( param ); 
param = NULL; 
}

void Reallocate_param( double * user_param ) 
{
param = user_param; 
}

