#define Kalker_Init 39
#define E_elastic Kalker_Init + 0
#define nu_poisson Kalker_Init + 1
#define G_elastic Kalker_Init + 2




#define output_N_R 0
#define output_R1x_R output_N_R + 6
#define output_Vx_R output_N_R + 1
#define Hertz_aR 42
#define C11R 46

hertz_ellipse (param, Hertz_aR, E_elastic, _Output, output_R1x_R, output_N_R ,_Table_Hertz, Table_Hertz_n_rows);
kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11R, Hertz_aR, nu_poisson );






#define output_N_L 10
#define output_R1x_L output_N_L + 6
#define output_Vx_L output_N_L + 1
#define Hertz_aL 44
#define C11L 50

hertz_ellipse (param, Hertz_aL, E_elastic, _Output, output_R1x_L, output_N_L ,_Table_Hertz, Table_Hertz_n_rows);
kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11L, Hertz_aL, nu_poisson );
