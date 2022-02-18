#include <stdlib.h>
#include "param.h"

#define g 9.8000000000000007e+00
#define d3 4.3180000000000002e-01
#define r3 -1.4909000000000000e-01
#define d4 -2.0320000000000001e-02
#define r4 -4.3180000000000002e-01
#define m1 1.0521000000000001e+01
#define mx1 0.0000000000000000e+00
#define my1 -5.6813000000000002e-01
#define mz1 0.0000000000000000e+00
#define Ixx1 1.6426799999999999e+00
#define Ixy1 0.0000000000000000e+00
#define Ixz1 0.0000000000000000e+00
#define Iyy1 5.0910000000000000e-01
#define Iyz1 0.0000000000000000e+00
#define Izz1 1.6426799999999999e+00
#define m2 1.5781000000000001e+01
#define mx2 2.2061799999999998e+00
#define my2 2.0000000000000001e-01
#define mz2 2.3527900000000002e+00
#define Ixx2 8.4057999999999999e-01
#define Ixy2 2.0000000000000001e-01
#define Ixz2 -3.2891999999999999e-01
#define Iyy2 8.7375000000000007e+00
#define Iyz2 4.0000000000000002e-01
#define Izz2 8.5756200000000007e+00
#define m3 8.7669999999999995e+00
#define mx3 -2.8100000000000000e-03
#define my3 -1.7271000000000001e+00
#define mz3 0.0000000000000000e+00
#define Ixx3 3.7170399999999999e+00
#define Ixy3 -5.5000000000000003e-04
#define Ixz3 2.0000000000000000e-03
#define Iyy3 3.0090000000000000e-01
#define Iyz3 2.0000000000000000e-03
#define Izz3 3.7170399999999999e+00
#define m4 1.0520000000000000e+00
#define mx4 2.9999999999999999e-02
#define my4 5.9999999999999998e-02
#define mz4 -5.9959999999999999e-02
#define Ixx4 1.8442000000000000e-01
#define Ixy4 1.0000000000000000e-04
#define Ixz4 0.0000000000000000e+00
#define Iyy4 1.8442000000000000e-01
#define Iyz4 1.0000000000000000e-04
#define Izz4 1.2730000000000000e-01
#define m5 1.0520000000000000e+00
#define mx5 4.0000000000000001e-03
#define my5 -7.3600000000000002e-03
#define mz5 5.0000000000000001e-03
#define Ixx5 7.3550000000000004e-02
#define Ixy5 1.0000000000000000e-04
#define Ixz5 1.0000000000000000e-04
#define Iyy5 7.3499999999999996e-02
#define Iyz5 1.0000000000000000e-04
#define Izz5 1.2734999999999999e-01
#define m6 3.5099999999999998e-01
#define mx6 1.0000000000000000e-02
#define my6 2.0000000000000000e-02
#define mz6 1.3080000000000000e-02
#define Ixx6 7.5900000000000004e-03
#define Ixy6 2.0000000000000001e-04
#define Ixz6 2.0000000000000001e-04
#define Iyy6 7.5900000000000004e-03
#define Iyz6 2.0000000000000001e-04
#define Izz6 1.4100000000000000e-02
#define Ma1 0.0000000000000000e+00
#define Ma2 0.0000000000000000e+00
#define Ma3 0.0000000000000000e+00
#define Ma4 0.0000000000000000e+00
#define Ma5 0.0000000000000000e+00
#define Ma6 0.0000000000000000e+00
#define FS001 1.4785880999999999e-03
#define FSa11 7.7210384699999995e-02
#define FSb11 -4.2272712800000001e-02
#define FSa21 1.1850621660000001e-01
#define FSb21 2.4908428350000000e-01
#define FSa31 1.6013046000000000e-02
#define FSb31 -6.0350038750000001e-01
#define FSa41 -3.7340693619999998e-01
#define FSb41 1.2973228000000000e-02
#define FS002 4.6548033239999997e-01
#define FSa12 8.8854951999999994e-03
#define FSb12 1.9204071940000000e-01
#define FSa22 -3.8735233130000002e-01
#define FSb22 -1.1052410800000000e-01
#define FSa32 5.1533701860000003e-01
#define FSb32 7.6922184800000001e-02
#define FSa42 3.6251040220000003e-01
#define FSb42 -5.7779867939999996e-01
#define FS003 5.2378177999999997e-01
#define FSa13 -1.5692199590000000e-01
#define FSb13 -1.4068066290000000e-01
#define FSa23 3.3474736810000000e-01
#define FSb23 -8.0427031100000004e-02
#define FSa33 -3.3193958569999998e-01
#define FSb33 2.9227797070000000e-01
#define FSa43 1.7802714840000000e-01
#define FSb43 -1.0640294300000000e-01
#define FS004 -1.3003566590000001e-01
#define FSa14 -1.6971897189999999e-01
#define FSb14 -2.1505564360000001e-01
#define FSa24 -2.0729890999999999e-03
#define FSb24 -4.9444409999999995e-04
#define FSa34 -1.4969756000000000e-03
#define FSb34 6.9502330000000001e-04
#define FSa44 -2.9644600000000001e-05
#define FSb44 6.3173000000000000e-05
#define FS005 1.8753000000000001e-06
#define FSa15 8.7649999999999999e-07
#define FSb15 1.0330000000000001e-07
#define FSa25 2.6831000000000002e-06
#define FSb25 1.5967000000000001e-06
#define FSa35 1.0124000000000000e-06
#define FSb35 1.3374000000000001e-06
#define FSa45 8.8080000000000000e-07
#define FSb45 7.8909999999999999e-07
#define FS006 4.0157999999999997e-06
#define FSa16 1.9404999999999999e-06
#define FSb16 7.0309999999999999e-07
#define FSa26 1.7516000000000001e-06
#define FSb26 1.7049000000000000e-06
#define FSa36 3.0301999999999998e-06
#define FSb36 3.0832000000000000e-06
#define FSa46 1.4203000000000000e-06
#define FSb46 1.7219999999999999e-07

double * param=NULL; 

void Init_param_values ( void )
{
param[0]=g;
param[1]=d3;
param[2]=r3;
param[3]=d4;
param[4]=r4;
param[5]=m1;
param[6]=mx1;
param[7]=my1;
param[8]=mz1;
param[9]=Ixx1;
param[10]=Ixy1;
param[11]=Ixz1;
param[12]=Iyy1;
param[13]=Iyz1;
param[14]=Izz1;
param[15]=m2;
param[16]=mx2;
param[17]=my2;
param[18]=mz2;
param[19]=Ixx2;
param[20]=Ixy2;
param[21]=Ixz2;
param[22]=Iyy2;
param[23]=Iyz2;
param[24]=Izz2;
param[25]=m3;
param[26]=mx3;
param[27]=my3;
param[28]=mz3;
param[29]=Ixx3;
param[30]=Ixy3;
param[31]=Ixz3;
param[32]=Iyy3;
param[33]=Iyz3;
param[34]=Izz3;
param[35]=m4;
param[36]=mx4;
param[37]=my4;
param[38]=mz4;
param[39]=Ixx4;
param[40]=Ixy4;
param[41]=Ixz4;
param[42]=Iyy4;
param[43]=Iyz4;
param[44]=Izz4;
param[45]=m5;
param[46]=mx5;
param[47]=my5;
param[48]=mz5;
param[49]=Ixx5;
param[50]=Ixy5;
param[51]=Ixz5;
param[52]=Iyy5;
param[53]=Iyz5;
param[54]=Izz5;
param[55]=m6;
param[56]=mx6;
param[57]=my6;
param[58]=mz6;
param[59]=Ixx6;
param[60]=Ixy6;
param[61]=Ixz6;
param[62]=Iyy6;
param[63]=Iyz6;
param[64]=Izz6;
param[65]=Ma1;
param[66]=Ma2;
param[67]=Ma3;
param[68]=Ma4;
param[69]=Ma5;
param[70]=Ma6;
param[71]=FS001;
param[72]=FSa11;
param[73]=FSb11;
param[74]=FSa21;
param[75]=FSb21;
param[76]=FSa31;
param[77]=FSb31;
param[78]=FSa41;
param[79]=FSb41;
param[80]=FS002;
param[81]=FSa12;
param[82]=FSb12;
param[83]=FSa22;
param[84]=FSb22;
param[85]=FSa32;
param[86]=FSb32;
param[87]=FSa42;
param[88]=FSb42;
param[89]=FS003;
param[90]=FSa13;
param[91]=FSb13;
param[92]=FSa23;
param[93]=FSb23;
param[94]=FSa33;
param[95]=FSb33;
param[96]=FSa43;
param[97]=FSb43;
param[98]=FS004;
param[99]=FSa14;
param[100]=FSb14;
param[101]=FSa24;
param[102]=FSb24;
param[103]=FSa34;
param[104]=FSb34;
param[105]=FSa44;
param[106]=FSb44;
param[107]=FS005;
param[108]=FSa15;
param[109]=FSb15;
param[110]=FSa25;
param[111]=FSb25;
param[112]=FSa35;
param[113]=FSb35;
param[114]=FSa45;
param[115]=FSb45;
param[116]=FS006;
param[117]=FSa16;
param[118]=FSb16;
param[119]=FSa26;
param[120]=FSb26;
param[121]=FSa36;
param[122]=FSb36;
param[123]=FSa46;
param[124]=FSb46;
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

