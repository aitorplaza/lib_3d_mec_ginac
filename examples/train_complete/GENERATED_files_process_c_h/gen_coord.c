#include <stdlib.h>
#include "gen_coord.h"

#define xWAG 1.0000000000000000e-03
#define yWAG 0.0000000000000000e+00
#define zWAG 7.3962000000000006e-01
#define aWAG 0.0000000000000000e+00
#define bWAG -2.0000000000000000e-03
#define cWAG 0.0000000000000000e+00
#define cRSLD 0.0000000000000000e+00
#define cFSLD 0.0000000000000000e+00
#define zRBOG -1.2411800000000001e-01
#define aRBOG 0.0000000000000000e+00
#define bRBOG 2.0000000000000000e-03
#define zFBOG -1.3009999999999999e-01
#define aFBOG 0.0000000000000000e+00
#define bFBOG 2.0000000000000000e-03
#define zRWHSF 5.3432300000000002e-02
#define aRWHSF 0.0000000000000000e+00
#define bRWHSF 4.8187000000000001e-02
#define zRWHSR 5.3545900000000000e-02
#define aRWHSR 0.0000000000000000e+00
#define bRWHSR 4.8187000000000001e-02
#define zFWHSF 3.9590000000000000e-02
#define aFWHSF 0.0000000000000000e+00
#define bFWHSF -6.4208000000000001e-02
#define zFWHSR 3.9711000000000003e-02
#define aFWHSR 0.0000000000000000e+00
#define bFWHSR -6.4208000000000001e-02
#define bRAXBFL 0.0000000000000000e+00
#define bRAXBFR 0.0000000000000000e+00
#define bRAXBRL 0.0000000000000000e+00
#define bRAXBRR 0.0000000000000000e+00
#define bFAXBFL 0.0000000000000000e+00
#define bFAXBFR 0.0000000000000000e+00
#define bFAXBRL 0.0000000000000000e+00
#define bFAXBRR 0.0000000000000000e+00
#define xRMOTF 0.0000000000000000e+00
#define yRMOTF 0.0000000000000000e+00
#define zRMOTF -2.2297000000000001e-02
#define bRMOTF 4.4140000000000004e-03
#define xRMOTR 0.0000000000000000e+00
#define yRMOTR 0.0000000000000000e+00
#define zRMOTR -2.2297000000000001e-02
#define bRMOTR -4.4413999999999999e-03
#define bRROTF -2.0479500000000000e-01
#define bRROTR -2.0479500000000000e-01

double * q=NULL; 

void Init_q_values ( void )
{
q[0]=xWAG;
q[1]=yWAG;
q[2]=zWAG;
q[3]=aWAG;
q[4]=bWAG;
q[5]=cWAG;
q[6]=cRSLD;
q[7]=cFSLD;
q[8]=zRBOG;
q[9]=aRBOG;
q[10]=bRBOG;
q[11]=zFBOG;
q[12]=aFBOG;
q[13]=bFBOG;
q[14]=zRWHSF;
q[15]=aRWHSF;
q[16]=bRWHSF;
q[17]=zRWHSR;
q[18]=aRWHSR;
q[19]=bRWHSR;
q[20]=zFWHSF;
q[21]=aFWHSF;
q[22]=bFWHSF;
q[23]=zFWHSR;
q[24]=aFWHSR;
q[25]=bFWHSR;
q[26]=bRAXBFL;
q[27]=bRAXBFR;
q[28]=bRAXBRL;
q[29]=bRAXBRR;
q[30]=bFAXBFL;
q[31]=bFAXBFR;
q[32]=bFAXBRL;
q[33]=bFAXBRR;
q[34]=xRMOTF;
q[35]=yRMOTF;
q[36]=zRMOTF;
q[37]=bRMOTF;
q[38]=xRMOTR;
q[39]=yRMOTR;
q[40]=zRMOTR;
q[41]=bRMOTR;
q[42]=bRROTF;
q[43]=bRROTR;
}

void Init_q ( )
{
 q = malloc ( n_gen_coord * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_coord ; i++ ) {q[i]=0.0;}
 }
}

void Done_q( ) 
{
if ( q != NULL) 
free ( q ); 
q = NULL; 
}

void Reallocate_q( double * user_q ) 
{
q = user_q; 
}

