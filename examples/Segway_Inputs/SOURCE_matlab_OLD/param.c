#include <stdlib.h>
#include "param.h"

#define g 9.8000000000000007e+00
#define pi 3.1415926535897900e+00
#define zcdg 0.0000000000000000e+00
#define R 2.0000000000000001e-01
#define man 1.2000000000000000e+00
#define r 2.9999999999999999e-01
#define l1 6.8000000000000005e-01
#define l2 5.0000000000000000e-01
#define l3 1.4499999999999999e-01
#define d 5.0000000000000003e-02
#define le 7.5000000000000000e-01
#define cm 1.7999999999999999e-01
#define rm 1.0000000000000000e-02
#define hcdg 1.1799999999999999e+00
#define alpha 2.0943951023931930e+00
#define beta -2.0943951023931930e+00
#define Cvis1 1.0000000000000000e+00
#define Cvis2 1.0000000000000000e+00
#define Cvis3 1.0000000000000000e+00
#define mPlataforma 1.0000000000000000e+00
#define mxPlataforma 0.0000000000000000e+00
#define myPlataforma 0.0000000000000000e+00
#define mzPlataforma 0.0000000000000000e+00
#define IxxPlataforma 1.0000000000000000e+00
#define IxyPlataforma 0.0000000000000000e+00
#define IyyPlataforma 1.0000000000000000e+00
#define IxzPlataforma 0.0000000000000000e+00
#define IzzPlataforma 1.0000000000000000e+00
#define IyzPlataforma 0.0000000000000000e+00
#define mRuedaIzq 1.0000000000000000e+00
#define mxRuedaIzq 0.0000000000000000e+00
#define myRuedaIzq 0.0000000000000000e+00
#define mzRuedaIzq 0.0000000000000000e+00
#define IxxRuedaIzq 1.0000000000000000e+00
#define IxyRuedaIzq 0.0000000000000000e+00
#define IyyRuedaIzq 5.0000000000000000e+00
#define IxzRuedaIzq 0.0000000000000000e+00
#define IzzRuedaIzq 1.0000000000000000e+00
#define IyzRuedaIzq 0.0000000000000000e+00
#define mRuedaDcha 1.0000000000000000e+00
#define mxRuedaDcha 0.0000000000000000e+00
#define myRuedaDcha 0.0000000000000000e+00
#define mzRuedaDcha 0.0000000000000000e+00
#define IxxRuedaDcha 1.0000000000000000e+00
#define IxyRuedaDcha 0.0000000000000000e+00
#define IyyRuedaDcha 1.0000000000000000e+00
#define IxzRuedaDcha 0.0000000000000000e+00
#define IzzRuedaDcha 1.0000000000000000e+00
#define IyzRuedaDcha 0.0000000000000000e+00
#define mEje 1.0000000000000000e+00
#define mxEje 0.0000000000000000e+00
#define myEje 0.0000000000000000e+00
#define mzEje 1.0000000000000000e+00
#define IxxEje 1.0000000000000000e+00
#define IxyEje 0.0000000000000000e+00
#define IyyEje 1.0000000000000000e+00
#define IxzEje 0.0000000000000000e+00
#define IzzEje 1.0000000000000000e+00
#define IyzEje 0.0000000000000000e+00
#define mManillar 1.0000000000000000e+00
#define mxManillar 1.0000000000000000e+00
#define myManillar 1.0000000000000000e+00
#define mzManillar 1.0000000000000000e+00
#define IxxManillar 1.0000000000000000e+00
#define IxyManillar 0.0000000000000000e+00
#define IyyManillar 1.0000000000000000e+00
#define IxzManillar 0.0000000000000000e+00
#define IzzManillar 1.0000000000000000e+00
#define IyzManillar 0.0000000000000000e+00
#define mRider 1.0000000000000000e+00
#define mxRider 1.0000000000000000e+00
#define myRider 1.0000000000000000e+00
#define mzRider 1.0000000000000000e+00
#define IxxRider 1.0000000000000000e+00
#define IxyRider 0.0000000000000000e+00
#define IyyRider 1.0000000000000000e+00
#define IxzRider 0.0000000000000000e+00
#define IzzRider 1.0000000000000000e+00
#define IyzRider 0.0000000000000000e+00
#define xp_0 0.0000000000000000e+00
#define yp_0 0.0000000000000000e+00
#define zp_0 0.0000000000000000e+00
#define KMan 4.0

double * param=NULL; 

void Init_param_values ( void )
{
param[0]=g;
param[1]=pi;
param[2]=zcdg;
param[3]=R;
param[4]=man;
param[5]=r;
param[6]=l1;
param[7]=l2;
param[8]=l3;
param[9]=d;
param[10]=le;
param[11]=cm;
param[12]=rm;
param[13]=hcdg;
param[14]=alpha;
param[15]=beta;
param[16]=Cvis1;
param[17]=Cvis2;
param[18]=Cvis3;
param[19]=mPlataforma;
param[20]=mxPlataforma;
param[21]=myPlataforma;
param[22]=mzPlataforma;
param[23]=IxxPlataforma;
param[24]=IxyPlataforma;
param[25]=IyyPlataforma;
param[26]=IxzPlataforma;
param[27]=IzzPlataforma;
param[28]=IyzPlataforma;
param[29]=mRuedaIzq;
param[30]=mxRuedaIzq;
param[31]=myRuedaIzq;
param[32]=mzRuedaIzq;
param[33]=IxxRuedaIzq;
param[34]=IxyRuedaIzq;
param[35]=IyyRuedaIzq;
param[36]=IxzRuedaIzq;
param[37]=IzzRuedaIzq;
param[38]=IyzRuedaIzq;
param[39]=mRuedaDcha;
param[40]=mxRuedaDcha;
param[41]=myRuedaDcha;
param[42]=mzRuedaDcha;
param[43]=IxxRuedaDcha;
param[44]=IxyRuedaDcha;
param[45]=IyyRuedaDcha;
param[46]=IxzRuedaDcha;
param[47]=IzzRuedaDcha;
param[48]=IyzRuedaDcha;
param[49]=mEje;
param[50]=mxEje;
param[51]=myEje;
param[52]=mzEje;
param[53]=IxxEje;
param[54]=IxyEje;
param[55]=IyyEje;
param[56]=IxzEje;
param[57]=IzzEje;
param[58]=IyzEje;
param[59]=mManillar;
param[60]=mxManillar;
param[61]=myManillar;
param[62]=mzManillar;
param[63]=IxxManillar;
param[64]=IxyManillar;
param[65]=IyyManillar;
param[66]=IxzManillar;
param[67]=IzzManillar;
param[68]=IyzManillar;
param[69]=mRider;
param[70]=mxRider;
param[71]=myRider;
param[72]=mzRider;
param[73]=IxxRider;
param[74]=IxyRider;
param[75]=IyyRider;
param[76]=IxzRider;
param[77]=IzzRider;
param[78]=IyzRider;
param[79]=xp_0;
param[80]=yp_0;
param[81]=zp_0;
param[82]=KMan;
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

