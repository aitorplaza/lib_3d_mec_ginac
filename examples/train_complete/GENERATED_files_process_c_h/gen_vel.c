#include <stdlib.h>
#include "gen_vel.h"

#define dxWAG 0.0000000000000000e+00
#define dyWAG 0.0000000000000000e+00
#define dzWAG 0.0000000000000000e+00
#define daWAG 0.0000000000000000e+00
#define dbWAG 0.0000000000000000e+00
#define dcWAG 0.0000000000000000e+00
#define dcRSLD 0.0000000000000000e+00
#define dcFSLD 0.0000000000000000e+00
#define dzRBOG 0.0000000000000000e+00
#define daRBOG 0.0000000000000000e+00
#define dbRBOG 0.0000000000000000e+00
#define dzFBOG 0.0000000000000000e+00
#define daFBOG 0.0000000000000000e+00
#define dbFBOG 0.0000000000000000e+00
#define dzRWHSF 0.0000000000000000e+00
#define daRWHSF 0.0000000000000000e+00
#define dbRWHSF 0.0000000000000000e+00
#define dzRWHSR 0.0000000000000000e+00
#define daRWHSR 0.0000000000000000e+00
#define dbRWHSR 0.0000000000000000e+00
#define dzFWHSF 0.0000000000000000e+00
#define daFWHSF 0.0000000000000000e+00
#define dbFWHSF 0.0000000000000000e+00
#define dzFWHSR 0.0000000000000000e+00
#define daFWHSR 0.0000000000000000e+00
#define dbFWHSR 0.0000000000000000e+00
#define dbRAXBFL 0.0000000000000000e+00
#define dbRAXBFR 0.0000000000000000e+00
#define dbRAXBRL 0.0000000000000000e+00
#define dbRAXBRR 0.0000000000000000e+00
#define dbFAXBFL 0.0000000000000000e+00
#define dbFAXBFR 0.0000000000000000e+00
#define dbFAXBRL 0.0000000000000000e+00
#define dbFAXBRR 0.0000000000000000e+00
#define dxRMOTF 0.0000000000000000e+00
#define dyRMOTF 0.0000000000000000e+00
#define dzRMOTF 0.0000000000000000e+00
#define dbRMOTF 0.0000000000000000e+00
#define dxRMOTR 0.0000000000000000e+00
#define dyRMOTR 0.0000000000000000e+00
#define dzRMOTR 0.0000000000000000e+00
#define dbRMOTR 0.0000000000000000e+00
#define dbRROTF 0.0000000000000000e+00
#define dbRROTR 0.0000000000000000e+00

double * dq=NULL; 

void Init_dq_values ( void )
{
dq[0]=dxWAG;
dq[1]=dyWAG;
dq[2]=dzWAG;
dq[3]=daWAG;
dq[4]=dbWAG;
dq[5]=dcWAG;
dq[6]=dcRSLD;
dq[7]=dcFSLD;
dq[8]=dzRBOG;
dq[9]=daRBOG;
dq[10]=dbRBOG;
dq[11]=dzFBOG;
dq[12]=daFBOG;
dq[13]=dbFBOG;
dq[14]=dzRWHSF;
dq[15]=daRWHSF;
dq[16]=dbRWHSF;
dq[17]=dzRWHSR;
dq[18]=daRWHSR;
dq[19]=dbRWHSR;
dq[20]=dzFWHSF;
dq[21]=daFWHSF;
dq[22]=dbFWHSF;
dq[23]=dzFWHSR;
dq[24]=daFWHSR;
dq[25]=dbFWHSR;
dq[26]=dbRAXBFL;
dq[27]=dbRAXBFR;
dq[28]=dbRAXBRL;
dq[29]=dbRAXBRR;
dq[30]=dbFAXBFL;
dq[31]=dbFAXBFR;
dq[32]=dbFAXBRL;
dq[33]=dbFAXBRR;
dq[34]=dxRMOTF;
dq[35]=dyRMOTF;
dq[36]=dzRMOTF;
dq[37]=dbRMOTF;
dq[38]=dxRMOTR;
dq[39]=dyRMOTR;
dq[40]=dzRMOTR;
dq[41]=dbRMOTR;
dq[42]=dbRROTF;
dq[43]=dbRROTR;
}

void Init_dq ( )
{
 dq = malloc ( n_gen_vel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_vel ; i++ ) {dq[i]=0.0;}
 }
}

void Done_dq( ) 
{
if ( dq != NULL) 
free ( dq ); 
dq = NULL; 
}

void Reallocate_dq( double * user_dq ) 
{
dq = user_dq; 
}

