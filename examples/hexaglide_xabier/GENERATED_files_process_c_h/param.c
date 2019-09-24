#include <stdlib.h>
#include "param.h"

#define g 9.8000000000000007e+00
#define R 4.8399999999999999e-01
#define r 7.3084999999999997e-02
#define L 1.0000000000000000e+00
#define e 6.8253999999999995e-02
#define alfa 1.0471966666666666e+00
#define mP 6.6970000000000001e+00
#define mxP 7.0000000000000007e-02
#define myP 7.0000000000000007e-02
#define mzP -2.3822568399999999e-01
#define IxxP 2.8319000000000000e-02
#define IxyP 6.9999999999999999e-04
#define IyyP 2.8319000000000000e-02
#define IxzP 2.9999999999999997e-04
#define IzzP 3.8045000000000002e-02
#define IyzP 2.9999999999999997e-04
#define m1 5.8039000000000005e+00
#define mx1 2.9999999999999999e-02
#define my1 2.9999999999999999e-02
#define mz1 -1.4684999999999999e+00
#define Ixx1 1.0435000000000001e+00
#define Ixy1 2.9999999999999997e-04
#define Iyy1 1.0435000000000001e+00
#define Ixz1 1.4000000000000000e-02
#define Izz1 2.2721999999999998e-03
#define Iyz1 1.4000000000000000e-02
#define m2 5.8039000000000005e+00
#define mx2 2.9999999999999999e-02
#define my2 2.9999999999999999e-02
#define mz2 -1.4684999999999999e+00
#define Ixx2 1.0435000000000001e+00
#define Ixy2 2.9999999999999997e-04
#define Iyy2 1.0435000000000001e+00
#define Ixz2 1.4000000000000000e-02
#define Izz2 2.2721999999999998e-03
#define Iyz2 1.4000000000000000e-02
#define m3 5.8039000000000005e+00
#define mx3 2.9999999999999999e-02
#define my3 2.9999999999999999e-02
#define mz3 -1.4684999999999999e+00
#define Ixx3 1.0435000000000001e+00
#define Ixy3 2.9999999999999997e-04
#define Iyy3 1.0435000000000001e+00
#define Ixz3 1.4000000000000000e-02
#define Izz3 2.2721999999999998e-03
#define Iyz3 1.4000000000000000e-02
#define m4 5.8039000000000005e+00
#define mx4 2.9999999999999999e-02
#define my4 2.9999999999999999e-02
#define mz4 -1.4684999999999999e+00
#define Ixx4 1.0435000000000001e+00
#define Ixy4 2.9999999999999997e-04
#define Iyy4 1.0435000000000001e+00
#define Ixz4 1.4000000000000000e-02
#define Izz4 2.2721999999999998e-03
#define Iyz4 1.4000000000000000e-02
#define m5 5.8039000000000005e+00
#define mx5 2.9999999999999999e-02
#define my5 2.9999999999999999e-02
#define mz5 -1.4684999999999999e+00
#define Ixx5 1.0435000000000001e+00
#define Ixy5 2.9999999999999997e-04
#define Iyy5 1.0435000000000001e+00
#define Ixz5 1.4000000000000000e-02
#define Izz5 2.2721999999999998e-03
#define Iyz5 1.4000000000000000e-02
#define m6 5.8039000000000005e+00
#define mx6 2.9999999999999999e-02
#define my6 2.9999999999999999e-02
#define mz6 -1.4684999999999999e+00
#define Ixx6 1.0435000000000001e+00
#define Ixy6 2.9999999999999997e-04
#define Iyy6 1.0435000000000001e+00
#define Ixz6 1.4000000000000000e-02
#define Izz6 2.2721999999999998e-03
#define Iyz6 1.4000000000000000e-02
#define Fs1 0.0000000000000000e+00
#define Fs2 0.0000000000000000e+00
#define Fs3 0.0000000000000000e+00
#define Fs4 0.0000000000000000e+00
#define Fs5 0.0000000000000000e+00
#define Fs6 0.0000000000000000e+00
#define FS001 1.9613765198999999e+00
#define FSa11 -3.3675482200000002e-02
#define FSb11 -4.5098281000000000e-03
#define FSa21 -7.6897540139999998e-01
#define FSb21 -3.6767866080000000e-01
#define FS002 1.9728988349000001e+00
#define FSa12 -7.7602272799999997e-02
#define FSb12 8.7896548500000005e-02
#define FSa22 -8.0477418469999995e-01
#define FSb22 -3.3292410810000000e-01
#define FS003 2.0079006745000001e+00
#define FSa13 1.7356238000000000e-03
#define FSb13 -1.2572387000000001e-02
#define FSa23 -9.3137914669999999e-01
#define FSb23 -8.5410527999999999e-02
#define FS004 1.9590377182000001e+00
#define FSa14 3.2193569999999998e-02
#define FSb14 2.6063488300000000e-02
#define FSa24 -8.8120031899999995e-01
#define FSb24 -8.1068690799999996e-02
#define FS005 2.0517043901999998e+00
#define FSa15 -8.0629011500000000e-02
#define FSb15 2.6959320900000000e-02
#define FSa25 -8.3622348130000002e-01
#define FSb25 -8.8205229499999996e-02
#define FS006 2.0439796765999998e+00
#define FSa16 -7.4300939799999993e-02
#define FSb16 5.6877343800000001e-02
#define FSa26 -8.5970401389999995e-01
#define FSb26 -3.4824260500000002e-02

double * param=NULL; 

void Init_param_values ( void )
{
param[0]=g;
param[1]=R;
param[2]=r;
param[3]=L;
param[4]=e;
param[5]=alfa;
param[6]=mP;
param[7]=mxP;
param[8]=myP;
param[9]=mzP;
param[10]=IxxP;
param[11]=IxyP;
param[12]=IyyP;
param[13]=IxzP;
param[14]=IzzP;
param[15]=IyzP;
param[16]=m1;
param[17]=mx1;
param[18]=my1;
param[19]=mz1;
param[20]=Ixx1;
param[21]=Ixy1;
param[22]=Iyy1;
param[23]=Ixz1;
param[24]=Izz1;
param[25]=Iyz1;
param[26]=m2;
param[27]=mx2;
param[28]=my2;
param[29]=mz2;
param[30]=Ixx2;
param[31]=Ixy2;
param[32]=Iyy2;
param[33]=Ixz2;
param[34]=Izz2;
param[35]=Iyz2;
param[36]=m3;
param[37]=mx3;
param[38]=my3;
param[39]=mz3;
param[40]=Ixx3;
param[41]=Ixy3;
param[42]=Iyy3;
param[43]=Ixz3;
param[44]=Izz3;
param[45]=Iyz3;
param[46]=m4;
param[47]=mx4;
param[48]=my4;
param[49]=mz4;
param[50]=Ixx4;
param[51]=Ixy4;
param[52]=Iyy4;
param[53]=Ixz4;
param[54]=Izz4;
param[55]=Iyz4;
param[56]=m5;
param[57]=mx5;
param[58]=my5;
param[59]=mz5;
param[60]=Ixx5;
param[61]=Ixy5;
param[62]=Iyy5;
param[63]=Ixz5;
param[64]=Izz5;
param[65]=Iyz5;
param[66]=m6;
param[67]=mx6;
param[68]=my6;
param[69]=mz6;
param[70]=Ixx6;
param[71]=Ixy6;
param[72]=Iyy6;
param[73]=Ixz6;
param[74]=Izz6;
param[75]=Iyz6;
param[76]=Fs1;
param[77]=Fs2;
param[78]=Fs3;
param[79]=Fs4;
param[80]=Fs5;
param[81]=Fs6;
param[82]=FS001;
param[83]=FSa11;
param[84]=FSb11;
param[85]=FSa21;
param[86]=FSb21;
param[87]=FS002;
param[88]=FSa12;
param[89]=FSb12;
param[90]=FSa22;
param[91]=FSb22;
param[92]=FS003;
param[93]=FSa13;
param[94]=FSb13;
param[95]=FSa23;
param[96]=FSb23;
param[97]=FS004;
param[98]=FSa14;
param[99]=FSb14;
param[100]=FSa24;
param[101]=FSb24;
param[102]=FS005;
param[103]=FSa15;
param[104]=FSb15;
param[105]=FSa25;
param[106]=FSb25;
param[107]=FS006;
param[108]=FSa16;
param[109]=FSb16;
param[110]=FSa26;
param[111]=FSb26;
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

