#include <stdlib.h>
#include "gen_auxcoord.h"

#define thetaW_RFR 0.0000000000000000e+00
#define uW_RFR 0.0000000000000000e+00
#define uR_RFR 0.0000000000000000e+00
#define xR_RFR -3.6559499999999998e+00
#define thetaW_RFL 0.0000000000000000e+00
#define uW_RFL 0.0000000000000000e+00
#define uR_RFL 0.0000000000000000e+00
#define xR_RFL -3.6559499999999998e+00
#define thetaW_RRR 0.0000000000000000e+00
#define uW_RRR 0.0000000000000000e+00
#define uR_RRR 0.0000000000000000e+00
#define xR_RRR -5.8409500000000003e+00
#define thetaW_RRL 0.0000000000000000e+00
#define uW_RRL 0.0000000000000000e+00
#define uR_RRL 0.0000000000000000e+00
#define xR_RRL -5.8409500000000003e+00
#define thetaW_FFR 0.0000000000000000e+00
#define uW_FFR 0.0000000000000000e+00
#define uR_FFR 0.0000000000000000e+00
#define xR_FFR 5.8440399999999997e+00
#define thetaW_FFL 0.0000000000000000e+00
#define uW_FFL 0.0000000000000000e+00
#define uR_FFL 0.0000000000000000e+00
#define xR_FFL 5.8440399999999997e+00
#define thetaW_FRR 0.0000000000000000e+00
#define uW_FRR 0.0000000000000000e+00
#define uR_FRR 0.0000000000000000e+00
#define xR_FRR 3.6590400000000001e+00
#define thetaW_FRL 0.0000000000000000e+00
#define uW_FRL 0.0000000000000000e+00
#define uR_FRL 0.0000000000000000e+00
#define xR_FRL 3.6590400000000001e+00

double * qaux=NULL; 

void Init_qaux_values ( void )
{
qaux[0]=thetaW_RFR;
qaux[1]=uW_RFR;
qaux[2]=uR_RFR;
qaux[3]=xR_RFR;
qaux[4]=thetaW_RFL;
qaux[5]=uW_RFL;
qaux[6]=uR_RFL;
qaux[7]=xR_RFL;
qaux[8]=thetaW_RRR;
qaux[9]=uW_RRR;
qaux[10]=uR_RRR;
qaux[11]=xR_RRR;
qaux[12]=thetaW_RRL;
qaux[13]=uW_RRL;
qaux[14]=uR_RRL;
qaux[15]=xR_RRL;
qaux[16]=thetaW_FFR;
qaux[17]=uW_FFR;
qaux[18]=uR_FFR;
qaux[19]=xR_FFR;
qaux[20]=thetaW_FFL;
qaux[21]=uW_FFL;
qaux[22]=uR_FFL;
qaux[23]=xR_FFL;
qaux[24]=thetaW_FRR;
qaux[25]=uW_FRR;
qaux[26]=uR_FRR;
qaux[27]=xR_FRR;
qaux[28]=thetaW_FRL;
qaux[29]=uW_FRL;
qaux[30]=uR_FRL;
qaux[31]=xR_FRL;
}

void Init_qaux ( )
{
 qaux = malloc ( n_gen_auxcoord * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxcoord ; i++ ) {qaux[i]=0.0;}
 }
}

void Done_qaux( ) 
{
if ( qaux != NULL) 
free ( qaux ); 
qaux = NULL; 
}

void Reallocate_qaux( double * user_qaux ) 
{
qaux = user_qaux; 
}

