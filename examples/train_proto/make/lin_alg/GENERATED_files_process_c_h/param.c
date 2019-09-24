#include <stdlib.h>
#include "param.h"

#define g 9.8000000000000007e+00
#define a1_0 0.0000000000000000e+00
#define da1_0 0.0000000000000000e+00
#define a2_0 0.0000000000000000e+00
#define da2_0 0.0000000000000000e+00
#define a5_0 0.0000000000000000e+00
#define da5_0 0.0000000000000000e+00
#define a6_0 0.0000000000000000e+00
#define da6_0 0.0000000000000000e+00
#define Sp 8.9999999999999997e-02
#define Lp 4.3250000000000000e-01
#define Ln 3.8479999999999998e-01
#define Ww 6.5000000000000002e-01
#define W 3.6499999999999999e-01
#define Hn 6.0999999999999999e-01
#define Hi 2.6260000000000000e-01
#define Hs 2.2939999999999999e-01
#define Hb 4.8249999999999998e-01
#define Rw 7.4999999999999997e-02
#define Rr 7.4999999999999997e-02
#define Rx 1.5500000000000000e-01
#define Bx 5.7000000000000002e-02
#define Mx 2.3180000000000001e-01
#define Si 4.0000000000000002e-01
#define Ss 3.4270000000000000e-01
#define SR 2.0000000000000000e-02
#define VS 1.0000000000000000e+00
#define af1 2.6179938779914919e-01
#define af2 7.8539816339744750e-01
#define W1 7.8539816339744750e-01
#define W2 1.5707963267948950e+00
#define W3 0.0000000000000000e+00
#define W4 3.1415926535897900e+00
#define W5 3.1415926535897900e+00
#define Cvis_a1 1.0000000000000000e+00
#define Cvis_a2 1.0000000000000000e+00
#define Cvis_a3 1.0000000000000000e+00
#define Cvis_a5 1.0000000000000000e+00
#define Cvis_a6 5.0000000000000000e+01
#define Ki 1.6100000000000000e+05
#define Li0 5.0000000000000003e-02
#define Li 4.0000000000000001e-02
#define Ks 1.6100000000000000e+05
#define Ls0 5.0000000000000003e-02
#define Ls 4.0000000000000001e-02
#define Kt 1.6100000000000000e+04
#define L0 5.0000000000000003e-02
#define L 4.9626714303120149e-02
#define Ds 3.2000000000000001e-01
#define Di 1.2237328569687983e-01
#define m1 9.6676570000000002e+00
#define mx1 3.0422360932488798e-03
#define my1 -4.4783209092578401e-03
#define mz1 3.6744390847206498e-01
#define Ixx1 9.8018816536592512e-01
#define Ixy1 4.4206645383572986e-07
#define Ixz1 -2.7381066521478097e-04
#define Iyy1 3.5913885822267944e-01
#define Iyz1 -1.8765169417531233e-09
#define Izz1 1.2621714318161488e+00
#define m2 3.9817383999999997e+01
#define mx2 2.9640487491956478e+00
#define my2 1.2890523297108559e-02
#define mz2 -2.1281833508276321e+01
#define Ixx2 1.4812045412059970e+01
#define Ixy2 3.9575154271222638e-03
#define Ixz2 1.9878803504816100e+00
#define Iyy2 1.8109105205218288e+01
#define Iyz2 5.2398620771679002e-03
#define Izz2 4.6068900395424466e+00
#define m3 5.9558960000000001e+00
#define mx3 -4.7939662052559992e-02
#define my3 5.2397669863016808e-05
#define mz3 -1.7534753413601353e-03
#define Ixx3 1.0137447701649687e-02
#define Ixy3 1.4279088608471107e-05
#define Ixz3 -1.8336256604895276e-05
#define Iyy3 8.4917751853899132e-02
#define Iyz3 1.3199649979843720e-06
#define Izz3 8.4916407074198327e-02
#define m4 3.0096650000000000e+01
#define mx4 8.1595157230594992e+00
#define my4 6.3829643465629993e-01
#define mz4 9.8350976542700019e-01
#define Ixx4 7.8362680833633369e-01
#define Ixy4 -9.7659081867136358e-02
#define Ixz4 -1.5928378541411312e-01
#define Iyy4 4.1898399221187557e+00
#define Iyz4 -8.0676674444343746e-02
#define Izz4 4.1372664487584210e+00
#define m5 5.9935295000000002e+00
#define mx5 -7.2479885899207852e-01
#define my5 -5.0344867442459103e-04
#define mz5 1.8332408681652481e-03
#define Ixx5 1.0233922022417507e-02
#define Ixy5 -1.8407660046722019e-04
#define Ixz5 2.2143604929993708e-04
#define Iyy5 2.6407049838144192e-01
#define Iyz5 1.5074481460462706e-06
#define Izz5 2.6406406993709075e-01
#define m6 1.1543302000000001e+01
#define mx6 4.4614306593158233e+00
#define my6 0.0000000000000000e+00
#define mz6 -4.9468035776464003e-01
#define Ixx6 3.9649403034936037e-01
#define Ixy6 0.0000000000000000e+00
#define Ixz6 3.6224154713213125e-01
#define Iyy6 2.9033917650784469e+00
#define Iyz6 0.0000000000000000e+00
#define Izz6 3.0406016747290865e+00

double * param=NULL; 

void Init_param_values ( void )
{
param[0]=g;
param[1]=a1_0;
param[2]=da1_0;
param[3]=a2_0;
param[4]=da2_0;
param[5]=a5_0;
param[6]=da5_0;
param[7]=a6_0;
param[8]=da6_0;
param[9]=Sp;
param[10]=Lp;
param[11]=Ln;
param[12]=Ww;
param[13]=W;
param[14]=Hn;
param[15]=Hi;
param[16]=Hs;
param[17]=Hb;
param[18]=Rw;
param[19]=Rr;
param[20]=Rx;
param[21]=Bx;
param[22]=Mx;
param[23]=Si;
param[24]=Ss;
param[25]=SR;
param[26]=VS;
param[27]=af1;
param[28]=af2;
param[29]=W1;
param[30]=W2;
param[31]=W3;
param[32]=W4;
param[33]=W5;
param[34]=Cvis_a1;
param[35]=Cvis_a2;
param[36]=Cvis_a3;
param[37]=Cvis_a5;
param[38]=Cvis_a6;
param[39]=Ki;
param[40]=Li0;
param[41]=Li;
param[42]=Ks;
param[43]=Ls0;
param[44]=Ls;
param[45]=Kt;
param[46]=L0;
param[47]=L;
param[48]=Ds;
param[49]=Di;
param[50]=m1;
param[51]=mx1;
param[52]=my1;
param[53]=mz1;
param[54]=Ixx1;
param[55]=Ixy1;
param[56]=Ixz1;
param[57]=Iyy1;
param[58]=Iyz1;
param[59]=Izz1;
param[60]=m2;
param[61]=mx2;
param[62]=my2;
param[63]=mz2;
param[64]=Ixx2;
param[65]=Ixy2;
param[66]=Ixz2;
param[67]=Iyy2;
param[68]=Iyz2;
param[69]=Izz2;
param[70]=m3;
param[71]=mx3;
param[72]=my3;
param[73]=mz3;
param[74]=Ixx3;
param[75]=Ixy3;
param[76]=Ixz3;
param[77]=Iyy3;
param[78]=Iyz3;
param[79]=Izz3;
param[80]=m4;
param[81]=mx4;
param[82]=my4;
param[83]=mz4;
param[84]=Ixx4;
param[85]=Ixy4;
param[86]=Ixz4;
param[87]=Iyy4;
param[88]=Iyz4;
param[89]=Izz4;
param[90]=m5;
param[91]=mx5;
param[92]=my5;
param[93]=mz5;
param[94]=Ixx5;
param[95]=Ixy5;
param[96]=Ixz5;
param[97]=Iyy5;
param[98]=Iyz5;
param[99]=Izz5;
param[100]=m6;
param[101]=mx6;
param[102]=my6;
param[103]=mz6;
param[104]=Ixx6;
param[105]=Ixy6;
param[106]=Ixz6;
param[107]=Iyy6;
param[108]=Iyz6;
param[109]=Izz6;
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

