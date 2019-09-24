#include <stdlib.h>
#include "gen_auxvel.h"

#define dthetaW_RFR 0.0000000000000000e+00
#define duW_RFR 0.0000000000000000e+00
#define duR_RFR 0.0000000000000000e+00
#define dxR_RFR 0.0000000000000000e+00
#define dthetaW_RFL 0.0000000000000000e+00
#define duW_RFL 0.0000000000000000e+00
#define duR_RFL 0.0000000000000000e+00
#define dxR_RFL 0.0000000000000000e+00
#define dthetaW_RRR 0.0000000000000000e+00
#define duW_RRR 0.0000000000000000e+00
#define duR_RRR 0.0000000000000000e+00
#define dxR_RRR 0.0000000000000000e+00
#define dthetaW_RRL 0.0000000000000000e+00
#define duW_RRL 0.0000000000000000e+00
#define duR_RRL 0.0000000000000000e+00
#define dxR_RRL 0.0000000000000000e+00
#define dthetaW_FFR 0.0000000000000000e+00
#define duW_FFR 0.0000000000000000e+00
#define duR_FFR 0.0000000000000000e+00
#define dxR_FFR 0.0000000000000000e+00
#define dthetaW_FFL 0.0000000000000000e+00
#define duW_FFL 0.0000000000000000e+00
#define duR_FFL 0.0000000000000000e+00
#define dxR_FFL 0.0000000000000000e+00
#define dthetaW_FRR 0.0000000000000000e+00
#define duW_FRR 0.0000000000000000e+00
#define duR_FRR 0.0000000000000000e+00
#define dxR_FRR 0.0000000000000000e+00
#define dthetaW_FRL 0.0000000000000000e+00
#define duW_FRL 0.0000000000000000e+00
#define duR_FRL 0.0000000000000000e+00
#define dxR_FRL 0.0000000000000000e+00

double * dqaux=NULL; 
void Init_dqaux_values ( void )
{
dqaux[0]=dthetaW_RFR;
dqaux[1]=duW_RFR;
dqaux[2]=duR_RFR;
dqaux[3]=dxR_RFR;
dqaux[4]=dthetaW_RFL;
dqaux[5]=duW_RFL;
dqaux[6]=duR_RFL;
dqaux[7]=dxR_RFL;
dqaux[8]=dthetaW_RRR;
dqaux[9]=duW_RRR;
dqaux[10]=duR_RRR;
dqaux[11]=dxR_RRR;
dqaux[12]=dthetaW_RRL;
dqaux[13]=duW_RRL;
dqaux[14]=duR_RRL;
dqaux[15]=dxR_RRL;
dqaux[16]=dthetaW_FFR;
dqaux[17]=duW_FFR;
dqaux[18]=duR_FFR;
dqaux[19]=dxR_FFR;
dqaux[20]=dthetaW_FFL;
dqaux[21]=duW_FFL;
dqaux[22]=duR_FFL;
dqaux[23]=dxR_FFL;
dqaux[24]=dthetaW_FRR;
dqaux[25]=duW_FRR;
dqaux[26]=duR_FRR;
dqaux[27]=dxR_FRR;
dqaux[28]=dthetaW_FRL;
dqaux[29]=duW_FRL;
dqaux[30]=duR_FRL;
dqaux[31]=dxR_FRL;
}

void Init_dqaux ( )
{
 dqaux = malloc ( n_gen_auxvel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxvel ; i++ ) {dqaux[i]=0.0;}
 }
}

void Done_dqaux( ) 
{
if ( dqaux != NULL) 
free ( dqaux ); 
dqaux = NULL; 
}

void Reallocate_dqaux( double * user_dqaux ) 
{
dqaux = user_dqaux; 
}

