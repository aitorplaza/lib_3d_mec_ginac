
  /*
  Calculates Kalker's forces
  */

_Output = Output();


#define Kalker_Init 31 
#define E_elastic Kalker_Init + 0
#define nu_poisson Kalker_Init + 1
#define G_elastic Kalker_Init + 2
#define Hertz_a Kalker_Init + 3
#define Hertz_b Kalker_Init + 4
#define C11 Kalker_Init + 5
#define C22 Kalker_Init + 6
#define C23 Kalker_Init + 7
#define C33 Kalker_Init + 8

printf ("RIGTH ============ \n");
//REAR BOGIE, FRONT SIDE, RIGHT WHEEL RFR
  #define output_N_R 0
  #define output_R1x_R output_N_R + 6
  #define output_Vx_R output_N_R + 1

  #define Fx_R 1
  #define Fy_R 2
  #define Mz_R 3

  hertz_ellipse (param, Hertz_a, E_elastic, _Output, output_R1x_R, output_N_R ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11, Hertz_a, nu_poisson );
  #ifndef SIMULINK
  kalker_forces (_Output, output_Vx_R ,param, C11, Hertz_a, G_elastic, inputs, Fx_R );
  #else
    //#define output_fx_L 20
    //kalker_forces (_Output, output_Vx_RFRL ,param, C11, Hertz_a, G_elastic, _Output,  output_fx_L );
  #endif
/***************************************************************************************************************************************/
printf ("LEFT ============ \n");
//REAR BOGIE, FRONT SIDE, LEFT WHEEL RFL
  #define output_N_L 10
  #define output_R1x_L output_N_L + 6
  #define output_Vx_L output_N_L + 1

  #define Fx_L 4
  #define Fy_L 5
  #define Mz_L 6

  hertz_ellipse (param, Hertz_a, E_elastic, _Output, output_R1x_L, output_N_L ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11, Hertz_a, nu_poisson );
  #ifndef SIMULINK
  kalker_forces (_Output, output_Vx_L ,param, C11, Hertz_a, G_elastic, inputs, Fx_L );
  #else
    //#define output_fx_L 20
    //kalker_forces (_Output, output_Vx_RFLL ,param, C11, Hertz_a, G_elastic, _Output,  output_fx_L );
  #endif
/***************************************************************************************************************************************/
