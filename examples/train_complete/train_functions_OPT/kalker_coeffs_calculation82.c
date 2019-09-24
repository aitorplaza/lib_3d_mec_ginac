
  /*
  Calculates Kalker's forces
  */
  
  //~ _Table_Hertz = Table_Hertz();
  //~ _Table_Kalker = Table_Kalker();
  
//~ struct timeval kalker1,kalker2,kalker3 ;
//~ gettimeofday(&kalker1, NULL);
  //~ _Output = Output();
//~ gettimeofday(&kalker2, NULL);

  
  #define Kalker_Init 238 
  #define E_elastic Kalker_Init + 0
  #define nu_poisson Kalker_Init + 1 
  #define G_elastic Kalker_Init + 2
  
  //REAR BOGIE, FRONT SIDE, RIGHT WHEEL RFR

  #define output_N_RFR 0
  #define output_R1x_RFR 6
  #define Hertz_aRFR 241
  #define C11RFR 243
 
  hertz_ellipse (param, Hertz_aRFR, E_elastic, _Output, output_R1x_RFR, output_N_RFR ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11RFR, Hertz_aRFR, nu_poisson );

/***************************************************************************************************************************************/

//REAR BOGIE, FRONT SIDE, LEFT WHEEL RFL
  #define output_N_RFL 10
  #define output_R1x_RFL 16
  #define Hertz_aRFL 247
  #define C11RFL 249
  
  hertz_ellipse (param, Hertz_aRFL, E_elastic, _Output, output_R1x_RFL, output_N_RFL ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11RFL, Hertz_aRFL, nu_poisson );

/***************************************************************************************************************************************/

//REAR BOGIE, REAR SIDE, RIGHT WHEEL RRR

  #define output_N_RRR 20
  #define output_R1x_RRR 26
  #define Hertz_aRRR 253
  #define C11RRR 255
    
  hertz_ellipse (param, Hertz_aRRR, E_elastic, _Output, output_R1x_RRR, output_N_RRR ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11RRR, Hertz_aRRR, nu_poisson );



/***************************************************************************************************************************************/
//REAR BOGIE, REAR SIDE, LEFT WHEEL RRL
  #define output_N_RRL 30
  #define output_R1x_RRL 36
  #define Hertz_aRRL 259
  #define C11RRL 261
  
  hertz_ellipse (param, Hertz_aRRL, E_elastic, _Output, output_R1x_RRL, output_N_RRL ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11RRL, Hertz_aRRL, nu_poisson );


/***************************************************************************************************************************************/
//FRONT BOGIE, FRONT SIDE, RIGHT WHEEL FFR
  #define output_N_FFR 40
  #define output_R1x_FFR 46
  #define Hertz_aFFR 265
  #define C11FFR 267

  hertz_ellipse (param, Hertz_aFFR, E_elastic, _Output, output_R1x_FFR, output_N_FFR ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11FFR, Hertz_aFFR, nu_poisson );

  
/***************************************************************************************************************************************/
//FRONT BOGIE, FRONT SIDE, LEFT WHEEL FFL
  #define output_N_FFL 50
  #define output_R1x_FFL 56
  #define Hertz_aFFL 271
  #define C11FFL 273
  
  hertz_ellipse (param, Hertz_aFFL, E_elastic, _Output, output_R1x_FFL, output_N_FFL ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11FFL, Hertz_aFFL, nu_poisson );


/***************************************************************************************************************************************/
//FRONT BOGIE, REAR SIDE, RIGHT WHEEL FRR
  #define output_N_FRR 60
  #define output_R1x_FRR 66
  #define Hertz_aFRR 277
  #define C11FRR 279 
  
  hertz_ellipse (param, Hertz_aFRR, E_elastic, _Output, output_R1x_FRR, output_N_FRR ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11FRR, Hertz_aFRR, nu_poisson );


/***************************************************************************************************************************************/
//FRONT BOGIE, REAR SIDE, LEFT WHEEL FRL
  #define output_N_FRL 70
  #define output_R1x_FRL 76
  #define Hertz_aFRL 283
  #define C11FRL 285 
  
  hertz_ellipse (param, Hertz_aFRL, E_elastic, _Output, output_R1x_FRL, output_N_FRL ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11FRL, Hertz_aFRL, nu_poisson );

/***************************************************************************************************************************************/



  
//~ gettimeofday(&kalker3, NULL); 

//~ printf("Evaluar Output  =  %lu\n", (kalker2.tv_usec-kalker1.tv_usec) ); 
//~ printf("Calcular elipse + Kalker=  %lu\n", (kalker3.tv_usec-kalker2.tv_usec) ); 




