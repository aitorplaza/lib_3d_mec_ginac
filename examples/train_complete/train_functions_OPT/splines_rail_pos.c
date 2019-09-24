

#define RFRas 80
#define RFLas 98
#define RRRas 116
#define RRLas 134
#define FFRas 152
#define FFLas 170
#define FRRas 188
#define FRLas 206


#define xR_RFR qaux[3]
#define xR_RFL qaux[7]
#define xR_RRR qaux[11]
#define xR_RRL qaux[15]
#define xR_FFR qaux[19]
#define xR_FFL qaux[23]
#define xR_FRR qaux[27]
#define xR_FRL qaux[31]


#define L 10.0

// Section1
//**********************************************
#define st1 0.0
#define en1 1.0

#define a1 0.0
#define b1 0.0
#define c1 0.0
#define d1 0.0
#define e1 0.0
#define f1 0.0
//**********************************************

// Section2
//**********************************************
#define st2 en1
#define en2 800.0

#define a2 6*L
#define b2 -15*L
#define c2 10*L
#define d2 0.0
#define e2 0.0
#define f2 0.0
//**********************************************

// Section3
//**********************************************
#define st3 en2
#define en3 1000.0

#define a3 0.0
#define b3 0.0
#define c3 0.0
#define d3 0.0
#define e3 0.0
#define f3 L
//**********************************************

  param[RFRas+0] = a1;
  param[RFRas+1] = b1;
  param[RFRas+2] = c1;
  param[RFRas+3] = d1;
  param[RFRas+4] = e1;
  param[RFRas+5] = f1;
  param[RFRas+6] = st1;
  param[RFRas+7] = en1;
  param[RFLas+0] = a1;
  param[RFLas+1] = b1;
  param[RFLas+2] = c1;
  param[RFLas+3] = d1;
  param[RFLas+4] = e1;
  param[RFLas+5] = f1;
  param[RFLas+6] = st1;
  param[RFLas+7] = en1;
  param[RRRas+0] = a1;
  param[RRRas+1] = b1;
  param[RRRas+2] = c1;
  param[RRRas+3] = d1;
  param[RRRas+4] = e1;
  param[RRRas+5] = f1;
  param[RRRas+6] = st1;
  param[RRRas+7] = en1;
  param[RRLas+0] = a1;
  param[RRLas+1] = b1;
  param[RRLas+2] = c1;
  param[RRLas+3] = d1;
  param[RRLas+4] = e1;
  param[RRLas+5] = f1;
  param[RRLas+6] = st1;
  param[RRLas+7] = en1;
  param[FFRas+0] = a1;
  param[FFRas+1] = b1;
  param[FFRas+2] = c1;
  param[FFRas+3] = d1;
  param[FFRas+4] = e1;
  param[FFRas+5] = f1;
  param[FFRas+6] = st1;
  param[FFRas+7] = en1;
  param[FFLas+0] = a1;
  param[FFLas+1] = b1;
  param[FFLas+2] = c1;
  param[FFLas+3] = d1;
  param[FFLas+4] = e1;
  param[FFLas+5] = f1;
  param[FFLas+6] = st1;
  param[FFLas+7] = en1;
  param[FRRas+0] = a1;
  param[FRRas+1] = b1;
  param[FRRas+2] = c1;
  param[FRRas+3] = d1;
  param[FRRas+4] = e1;
  param[FRRas+5] = f1;
  param[FRRas+6] = st1;
  param[FRRas+7] = en1;  
  param[FRLas+0] = a1;
  param[FRLas+1] = b1;
  param[FRLas+2] = c1;
  param[FRLas+3] = d1;
  param[FRLas+4] = e1;
  param[FRLas+5] = f1;
  param[FRLas+6] = st1;
  param[FRLas+7] = en1;






//~ 
//~ 
//~ 
//~ 
//~ 
//if (q[0] > s3){
//  param[10] = 0.0; 
//}
//~ 
//~ //********************************************************************************************
//~ //RFR
//~ if (xR_RFR < en1){
  //~ param[RFRas+0] = a1;
  //~ param[RFRas+1] = b1;
  //~ param[RFRas+2] = c1;
  //~ param[RFRas+3] = d1;
  //~ param[RFRas+4] = e1;
  //~ param[RFRas+5] = f1;
  //~ param[RFRas+6] = st1;
  //~ param[RFRas+7] = en1;
//~ }
//~ 
//~ else if (xR_RFR > st2 && xR_RFR < en2){
  //~ param[RFRas+0] = a2;
  //~ param[RFRas+1] = b2;
  //~ param[RFRas+2] = c2;
  //~ param[RFRas+3] = d2;
  //~ param[RFRas+4] = e2;
  //~ param[RFRas+5] = f2;
  //~ param[RFRas+6] = st2;
  //~ param[RFRas+7] = en2;
//~ }
//~ 
//~ else if (xR_RFR > st3){
  //~ param[RFRas+0] = a3;
  //~ param[RFRas+1] = b3;
  //~ param[RFRas+2] = c3;
  //~ param[RFRas+3] = d3;
  //~ param[RFRas+4] = e3;
  //~ param[RFRas+5] = f3;
  //~ param[RFRas+6] = st3;
  //~ param[RFRas+7] = en3;
//~ }
//~ 
//~ //********************************************************************************************
//~ //RFL
//~ if (xR_RFL < en1){
  //~ param[RFLas+0] = a1;
  //~ param[RFLas+1] = b1;
  //~ param[RFLas+2] = c1;
  //~ param[RFLas+3] = d1;
  //~ param[RFLas+4] = e1;
  //~ param[RFLas+5] = f1;
  //~ param[RFLas+6] = st1;
  //~ param[RFLas+7] = en1;
//~ }
//~ 
//~ else if (xR_RFL > st2 && xR_RFL < en2){
  //~ param[RFLas+0] = a2;
  //~ param[RFLas+1] = b2;
  //~ param[RFLas+2] = c2;
  //~ param[RFLas+3] = d2;
  //~ param[RFLas+4] = e2;
  //~ param[RFLas+5] = f2;
  //~ param[RFLas+6] = st2;
  //~ param[RFLas+7] = en2;
//~ }
//~ 
//~ else if (xR_RFL > st3){
  //~ param[RFLas+0] = a3;
  //~ param[RFLas+1] = b3;
  //~ param[RFLas+2] = c3;
  //~ param[RFLas+3] = d3;
  //~ param[RFLas+4] = e3;
  //~ param[RFLas+5] = f3;
  //~ param[RFLas+6] = st3;
  //~ param[RFLas+7] = en3;
//~ }
//~ 
//~ 
//~ //********************************************************************************************
//~ //RRR
//~ if (xR_RRR < en1){
  //~ param[RRRas+0] = a1;
  //~ param[RRRas+1] = b1;
  //~ param[RRRas+2] = c1;
  //~ param[RRRas+3] = d1;
  //~ param[RRRas+4] = e1;
  //~ param[RRRas+5] = f1;
  //~ param[RRRas+6] = st1;
  //~ param[RRRas+7] = en1;
//~ }
//~ 
//~ else if (xR_RRR > st2 && xR_RRR < en2){
  //~ param[RRRas+0] = a2;
  //~ param[RRRas+1] = b2;
  //~ param[RRRas+2] = c2;
  //~ param[RRRas+3] = d2;
  //~ param[RRRas+4] = e2;
  //~ param[RRRas+5] = f2;
  //~ param[RRRas+6] = st2;
  //~ param[RRRas+7] = en2;
//~ }
//~ 
//~ else if (xR_RRR > st3){
  //~ param[RRRas+0] = a3;
  //~ param[RRRas+1] = b3;
  //~ param[RRRas+2] = c3;
  //~ param[RRRas+3] = d3;
  //~ param[RRRas+4] = e3;
  //~ param[RRRas+5] = f3;
  //~ param[RRRas+6] = st3;
  //~ param[RRRas+7] = en3;
//~ }
//~ 
//~ //********************************************************************************************
//~ //RRL
//~ if (xR_RRL < en1){
  //~ param[RRLas+0] = a1;
  //~ param[RRLas+1] = b1;
  //~ param[RRLas+2] = c1;
  //~ param[RRLas+3] = d1;
  //~ param[RRLas+4] = e1;
  //~ param[RRLas+5] = f1;
  //~ param[RRLas+6] = st1;
  //~ param[RRLas+7] = en1;
//~ }
//~ 
//~ else if (xR_RRL > st2 && xR_RRL < en2){
  //~ param[RRLas+0] = a2;
  //~ param[RRLas+1] = b2;
  //~ param[RRLas+2] = c2;
  //~ param[RRLas+3] = d2;
  //~ param[RRLas+4] = e2;
  //~ param[RRLas+5] = f2;
  //~ param[RRLas+6] = st2;
  //~ param[RRLas+7] = en2;
//~ }
//~ 
//~ else if (xR_RRL > st3){
  //~ param[RRLas+0] = a3;
  //~ param[RRLas+1] = b3;
  //~ param[RRLas+2] = c3;
  //~ param[RRLas+3] = d3;
  //~ param[RRLas+4] = e3;
  //~ param[RRLas+5] = f3;
  //~ param[RRLas+6] = st3;
  //~ param[RRLas+7] = en3;
//~ }
//~ 
//~ //********************************************************************************************
//~ //FFR
//~ 
//~ if (xR_FFR < en1){
  //~ param[FFRas+0] = a1;
  //~ param[FFRas+1] = b1;
  //~ param[FFRas+2] = c1;
  //~ param[FFRas+3] = d1;
  //~ param[FFRas+4] = e1;
  //~ param[FFRas+5] = f1;
  //~ param[FFRas+6] = st1;
  //~ param[FFRas+7] = en1;
//~ }
//~ 
//~ else if (xR_FFR > st2 && xR_FFR < en2){
  //~ param[FFRas+0] = a2;
  //~ param[FFRas+1] = b2;
  //~ param[FFRas+2] = c2;
  //~ param[FFRas+3] = d2;
  //~ param[FFRas+4] = e2;
  //~ param[FFRas+5] = f2;
  //~ param[FFRas+6] = st2;
  //~ param[FFRas+7] = en2;
//~ }
//~ 
//~ else if (xR_FFR > st3){
  //~ param[FFRas+0] = a3;
  //~ param[FFRas+1] = b3;
  //~ param[FFRas+2] = c3;
  //~ param[FFRas+3] = d3;
  //~ param[FFRas+4] = e3;
  //~ param[FFRas+5] = f3;
  //~ param[FFRas+6] = st3;
  //~ param[FFRas+7] = en3;
//~ }
//~ 
//~ 
//~ //********************************************************************************************
//~ //FFL
//~ 
//~ if (xR_FFL < en1){
  //~ param[FFLas+0] = a1;
  //~ param[FFLas+1] = b1;
  //~ param[FFLas+2] = c1;
  //~ param[FFLas+3] = d1;
  //~ param[FFLas+4] = e1;
  //~ param[FFLas+5] = f1;
  //~ param[FFLas+6] = st1;
  //~ param[FFLas+7] = en1;
//~ }
//~ 
//~ else if (xR_FFL > st2 && xR_FFL < en2){
  //~ param[FFLas+0] = a2;
  //~ param[FFLas+1] = b2;
  //~ param[FFLas+2] = c2;
  //~ param[FFLas+3] = d2;
  //~ param[FFLas+4] = e2;
  //~ param[FFLas+5] = f2;
  //~ param[FFLas+6] = st2;
  //~ param[FFLas+7] = en2;
//~ }
//~ 
//~ else if (xR_FFL > st3){
  //~ param[FFLas+0] = a3;
  //~ param[FFLas+1] = b3;
  //~ param[FFLas+2] = c3;
  //~ param[FFLas+3] = d3;
  //~ param[FFLas+4] = e3;
  //~ param[FFLas+5] = f3;
  //~ param[FFLas+6] = st3;
  //~ param[FFLas+7] = en3;
//~ }
//~ 
//~ //**********************************************
//~ //FRR
//~ if (xR_FRR < en1){
  //~ param[FRRas+0] = a1;
  //~ param[FRRas+1] = b1;
  //~ param[FRRas+2] = c1;
  //~ param[FRRas+3] = d1;
  //~ param[FRRas+4] = e1;
  //~ param[FRRas+5] = f1;
  //~ param[FRRas+6] = st1;
  //~ param[FRRas+7] = en1;
//~ }
//~ 
//~ else if (xR_FRR > st2 && xR_FRR < en2){
  //~ param[FRRas+0] = a2;
  //~ param[FRRas+1] = b2;
  //~ param[FRRas+2] = c2;
  //~ param[FRRas+3] = d2;
  //~ param[FRRas+4] = e2;
  //~ param[FRRas+5] = f2;
  //~ param[FRRas+6] = st2;
  //~ param[FRRas+7] = en2;
//~ }
//~ 
//~ else if (xR_FRR > st3){
  //~ param[FRRas+0] = a3;
  //~ param[FRRas+1] = b3;
  //~ param[FRRas+2] = c3;
  //~ param[FRRas+3] = d3;
  //~ param[FRRas+4] = e3;
  //~ param[FRRas+5] = f3;
  //~ param[FRRas+6] = st3;
  //~ param[FRRas+7] = en3;
//~ }
//~ 
//~ //**********************************************
//~ // FRL
//~ if (xR_FRL < en1){
  //~ param[FRLas+0] = a1;
  //~ param[FRLas+1] = b1;
  //~ param[FRLas+2] = c1;
  //~ param[FRLas+3] = d1;
  //~ param[FRLas+4] = e1;
  //~ param[FRLas+5] = f1;
  //~ param[FRLas+6] = st1;
  //~ param[FRLas+7] = en1;
//~ }
//~ 
//~ else if (xR_FRL > st2 && xR_FRL < en2){
  //~ param[FRLas+0] = a2;
  //~ param[FRLas+1] = b2;
  //~ param[FRLas+2] = c2;
  //~ param[FRLas+3] = d2;
  //~ param[FRLas+4] = e2;
  //~ param[FRLas+5] = f2;
  //~ param[FRLas+6] = st2;
  //~ param[FRLas+7] = en2;
//~ }
//~ 
//~ else if (xR_FRL > st3){
  //~ param[FRLas+0] = a3;
  //~ param[FRLas+1] = b3;
  //~ param[FRLas+2] = c3;
  //~ param[FRLas+3] = d3;
  //~ param[FRLas+4] = e3;
  //~ param[FRLas+5] = f3;
  //~ param[FRLas+6] = st3;
  //~ param[FRLas+7] = en3;
//~ }
