//*********************************************************************************

//includes needed in train model

extern "C" {
  #include "Output.h"
  #include "mu_div_mod_vel.h"
  #include "get_spline_coefs.h"
  #include "breaks_rail.h"
  #include "breaks_wheelL.h"
  #include "breaks_wheelR.h"
  #include "coefs_rail.h"
  #include "coefs_wheelL.h"
  #include "coefs_wheelR.h"
  #include "Initial_position_velocity_with_splines.h"
  #include "hertz_ellipse.h" 
  #include "Table_Hertz.h"
  #include "kalker_coeffs.h" 
  #include "Table_Kalker.h"
  #include "kalker_forces.h"   
  
  #ifdef TRAPEZOIDAL  
  #include "one_step_trapezoidal_train.h"
  #endif
}
//*********************************************************************************
