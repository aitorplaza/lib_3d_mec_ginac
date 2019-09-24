

#define as 11

#define L 10.0

#define s1 0.0
#define e1 3.0
#define s2 3.0
#define e2 80.0
#define s3 80.0
#define e3 1000.0

if (q[0] > s3){
  param[10] =0.0; 
}

if (qaux[3] < s1){
  param[as+0] = 0;
  param[as+1] = 0;
  param[as+2] = 0;
  param[as+3] = 0;
  param[as+4] = 0;
  param[as+5] = 0;
  param[as+6] = s1;
  param[as+7] = e1;
}

else if (qaux[3] > s2 && qaux[3] < e2){
  param[as+0] = 6*L;
  param[as+1] = -15*L;
  param[as+2] = 10*L;
  param[as+3] = 0;
  param[as+4] = 0;
  param[as+5] = 0;  
  param[as+6] = s2;
  param[as+7] = e2;
}

else if (qaux[3] > s3){
  param[as+0] = 0;
  param[as+1] = 0;
  param[as+2] = 0;
  param[as+3] = 0;
  param[as+4] = 0;
  param[as+5] = L;  
  param[as+6] = s3;
  param[as+7] = e3;
}




if (qaux[7] < s1){
  param[as+0] = 0;
  param[as+1] = 0;
  param[as+2] = 0;
  param[as+3] = 0;
  param[as+4] = 0;
  param[as+5] = 0;  
  param[as+6] = s1;
  param[as+7] = e1;
}

else if (qaux[7] > s2 && qaux[7] < e2){
  param[as+0] = 6*L;
  param[as+1] = -15*L;
  param[as+2] = 10*L;
  param[as+3] = 0;
  param[as+4] = 0;
  param[as+5] = 0;  
  param[as+6] = s2;
  param[as+7] = e2;
}

else if (qaux[7] > s3){
  param[as+0] = 0;
  param[as+1] = 0;
  param[as+2] = 0;
  param[as+3] = 0;
  param[as+4] = 0;
  param[as+5] = L; 
  param[as+6] = s3;
  param[as+7] = e3;    
}
