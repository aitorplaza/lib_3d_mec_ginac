#include <stdlib.h>
#include "gen_auxaccel.h"

#define ddthetaW_RFR 0.0000000000000000e+00
#define dduW_RFR 0.0000000000000000e+00
#define dduR_RFR 0.0000000000000000e+00
#define ddxR_RFR 0.0000000000000000e+00
#define ddthetaW_RFL 0.0000000000000000e+00
#define dduW_RFL 0.0000000000000000e+00
#define dduR_RFL 0.0000000000000000e+00
#define ddxR_RFL 0.0000000000000000e+00
#define ddthetaW_RRR 0.0000000000000000e+00
#define dduW_RRR 0.0000000000000000e+00
#define dduR_RRR 0.0000000000000000e+00
#define ddxR_RRR 0.0000000000000000e+00
#define ddthetaW_RRL 0.0000000000000000e+00
#define dduW_RRL 0.0000000000000000e+00
#define dduR_RRL 0.0000000000000000e+00
#define ddxR_RRL 0.0000000000000000e+00
#define ddthetaW_FFR 0.0000000000000000e+00
#define dduW_FFR 0.0000000000000000e+00
#define dduR_FFR 0.0000000000000000e+00
#define ddxR_FFR 0.0000000000000000e+00
#define ddthetaW_FFL 0.0000000000000000e+00
#define dduW_FFL 0.0000000000000000e+00
#define dduR_FFL 0.0000000000000000e+00
#define ddxR_FFL 0.0000000000000000e+00
#define ddthetaW_FRR 0.0000000000000000e+00
#define dduW_FRR 0.0000000000000000e+00
#define dduR_FRR 0.0000000000000000e+00
#define ddxR_FRR 0.0000000000000000e+00
#define ddthetaW_FRL 0.0000000000000000e+00
#define dduW_FRL 0.0000000000000000e+00
#define dduR_FRL 0.0000000000000000e+00
#define ddxR_FRL 0.0000000000000000e+00

double * ddqaux=NULL; 

void Init_ddqaux_values ( void )
{
ddqaux[0]=ddthetaW_RFR;
ddqaux[1]=dduW_RFR;
ddqaux[2]=dduR_RFR;
ddqaux[3]=ddxR_RFR;
ddqaux[4]=ddthetaW_RFL;
ddqaux[5]=dduW_RFL;
ddqaux[6]=dduR_RFL;
ddqaux[7]=ddxR_RFL;
ddqaux[8]=ddthetaW_RRR;
ddqaux[9]=dduW_RRR;
ddqaux[10]=dduR_RRR;
ddqaux[11]=ddxR_RRR;
ddqaux[12]=ddthetaW_RRL;
ddqaux[13]=dduW_RRL;
ddqaux[14]=dduR_RRL;
ddqaux[15]=ddxR_RRL;
ddqaux[16]=ddthetaW_FFR;
ddqaux[17]=dduW_FFR;
ddqaux[18]=dduR_FFR;
ddqaux[19]=ddxR_FFR;
ddqaux[20]=ddthetaW_FFL;
ddqaux[21]=dduW_FFL;
ddqaux[22]=dduR_FFL;
ddqaux[23]=ddxR_FFL;
ddqaux[24]=ddthetaW_FRR;
ddqaux[25]=dduW_FRR;
ddqaux[26]=dduR_FRR;
ddqaux[27]=ddxR_FRR;
ddqaux[28]=ddthetaW_FRL;
ddqaux[29]=dduW_FRL;
ddqaux[30]=dduR_FRL;
ddqaux[31]=ddxR_FRL;
}

void Init_ddqaux ( )
{
 ddqaux = malloc ( n_gen_auxaccel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxaccel ; i++ ) {ddqaux[i]=0.0;}
 }
}

void Done_ddqaux( ) 
{
if ( ddqaux != NULL) 
free ( ddqaux ); 
ddqaux = NULL; 
}

void Reallocate_ddqaux( double * user_ddqaux ) 
{
ddqaux = user_ddqaux; 
}

