#include <stdlib.h>
#include "gen_accel.h"

#define ddxWAG 0.0000000000000000e+00
#define ddyWAG 0.0000000000000000e+00
#define ddzWAG 0.0000000000000000e+00
#define ddaWAG 0.0000000000000000e+00
#define ddbWAG 0.0000000000000000e+00
#define ddcWAG 0.0000000000000000e+00
#define ddcRSLD 0.0000000000000000e+00
#define ddcFSLD 0.0000000000000000e+00
#define ddzRBOG 0.0000000000000000e+00
#define ddaRBOG 0.0000000000000000e+00
#define ddbRBOG 0.0000000000000000e+00
#define ddzFBOG 0.0000000000000000e+00
#define ddaFBOG 0.0000000000000000e+00
#define ddbFBOG 0.0000000000000000e+00
#define ddzRWHSF 0.0000000000000000e+00
#define ddaRWHSF 0.0000000000000000e+00
#define ddbRWHSF 0.0000000000000000e+00
#define ddzRWHSR 0.0000000000000000e+00
#define ddaRWHSR 0.0000000000000000e+00
#define ddbRWHSR 0.0000000000000000e+00
#define ddzFWHSF 0.0000000000000000e+00
#define ddaFWHSF 0.0000000000000000e+00
#define ddbFWHSF 0.0000000000000000e+00
#define ddzFWHSR 0.0000000000000000e+00
#define ddaFWHSR 0.0000000000000000e+00
#define ddbFWHSR 0.0000000000000000e+00
#define ddbRAXBFL 0.0000000000000000e+00
#define ddbRAXBFR 0.0000000000000000e+00
#define ddbRAXBRL 0.0000000000000000e+00
#define ddbRAXBRR 0.0000000000000000e+00
#define ddbFAXBFL 0.0000000000000000e+00
#define ddbFAXBFR 0.0000000000000000e+00
#define ddbFAXBRL 0.0000000000000000e+00
#define ddbFAXBRR 0.0000000000000000e+00
#define ddxRMOTF 0.0000000000000000e+00
#define ddyRMOTF 0.0000000000000000e+00
#define ddzRMOTF 0.0000000000000000e+00
#define ddbRMOTF 0.0000000000000000e+00
#define ddxRMOTR 0.0000000000000000e+00
#define ddyRMOTR 0.0000000000000000e+00
#define ddzRMOTR 0.0000000000000000e+00
#define ddbRMOTR 0.0000000000000000e+00
#define ddbRROTF 0.0000000000000000e+00
#define ddbRROTR 0.0000000000000000e+00

double * ddq=NULL; 

void Init_ddq_values ( void )
{
ddq[0]=ddxWAG;
ddq[1]=ddyWAG;
ddq[2]=ddzWAG;
ddq[3]=ddaWAG;
ddq[4]=ddbWAG;
ddq[5]=ddcWAG;
ddq[6]=ddcRSLD;
ddq[7]=ddcFSLD;
ddq[8]=ddzRBOG;
ddq[9]=ddaRBOG;
ddq[10]=ddbRBOG;
ddq[11]=ddzFBOG;
ddq[12]=ddaFBOG;
ddq[13]=ddbFBOG;
ddq[14]=ddzRWHSF;
ddq[15]=ddaRWHSF;
ddq[16]=ddbRWHSF;
ddq[17]=ddzRWHSR;
ddq[18]=ddaRWHSR;
ddq[19]=ddbRWHSR;
ddq[20]=ddzFWHSF;
ddq[21]=ddaFWHSF;
ddq[22]=ddbFWHSF;
ddq[23]=ddzFWHSR;
ddq[24]=ddaFWHSR;
ddq[25]=ddbFWHSR;
ddq[26]=ddbRAXBFL;
ddq[27]=ddbRAXBFR;
ddq[28]=ddbRAXBRL;
ddq[29]=ddbRAXBRR;
ddq[30]=ddbFAXBFL;
ddq[31]=ddbFAXBFR;
ddq[32]=ddbFAXBRL;
ddq[33]=ddbFAXBRR;
ddq[34]=ddxRMOTF;
ddq[35]=ddyRMOTF;
ddq[36]=ddzRMOTF;
ddq[37]=ddbRMOTF;
ddq[38]=ddxRMOTR;
ddq[39]=ddyRMOTR;
ddq[40]=ddzRMOTR;
ddq[41]=ddbRMOTR;
ddq[42]=ddbRROTF;
ddq[43]=ddbRROTR;
}

void Init_ddq ( )
{
 ddq = malloc ( n_gen_accel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_accel ; i++ ) {ddq[i]=0.0;}
 }
}

void Done_ddq( ) 
{
if ( ddq != NULL) 
free ( ddq ); 
ddq = NULL; 
}

void Reallocate_ddq( double * user_ddq ) 
{
ddq = user_ddq; 
}

