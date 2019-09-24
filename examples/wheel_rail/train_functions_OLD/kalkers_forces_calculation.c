
  /*
  Calculates Kalker's forces
  */
  _Table_Hertz = Table_Hertz();
  _Table_Kalker = Table_Kalker();
  _Output = Output();


  #define param_elast 28
  #define param_nu 29 
  #define param_G 30  
  #define param_ellipL 31
  #define param_ellipR 33
  #define param_c11 35
  
  #define output_NL 0 
  #define output_NR 10
  #define output_R1x_L 6
  #define output_R1x_R 16
  #define output_Vx_L 1
  #define output_Vx_R 11
  
  #define input_fx_L 4
  #define input_fx_R 1 


  hertz_ellipse (param, param_ellipL, param_elast, _Output, output_R1x_L, output_NL ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, param_c11, param_ellipL, param_nu );
  #ifndef SIMULINK 
  kalker_forces (_Output, output_Vx_L ,param, param_c11, param_ellipL, param_G, inputs,  input_fx_L );
  #else
  #define output_fx_L 20
  kalker_forces (_Output, output_Vx_L ,param, param_c11, param_ellipL, param_G, _Output,  output_fx_L );
  #endif

  hertz_ellipse (param, param_ellipR, param_elast, _Output, output_R1x_L, output_NR ,_Table_Hertz, Table_Hertz_n_rows);
  kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, param_c11, param_ellipR, param_nu );
  #ifndef SIMULINK 
  kalker_forces (_Output, output_Vx_R ,param, param_c11, param_ellipR, param_G, inputs , input_fx_R);
  #else
  #define output_fx_R 23
  kalker_forces (_Output, output_Vx_R ,param, param_c11, param_ellipR, param_G, _Output,  output_fx_R );
  #endif




