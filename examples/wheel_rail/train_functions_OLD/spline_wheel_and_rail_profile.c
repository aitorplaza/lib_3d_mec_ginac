/*

#define theta_W_R q[ 6 ]
#define u_W_R q[ 7 ]
#define theta_W_L q[ 8 ]
#define u_W_L q[ 9 ]
#define u_R_R q[ 10 ]
#define x_R_R q[ 11 ]
#define u_R_L q[ 12 ]
#define x_R_L q[ 13 ]


#define awL param[ 8 ]
#define bwL param[ 9 ]
#define cwL param[ 10 ]
#define dwL param[ 11 ]
#define xwL param[ 12 ]
#define awR param[ 13 ]
#define bwR param[ 14 ]
#define cwR param[ 15 ]
#define dwR param[ 16 ]
#define xwR param[ 17 ]
#define arL param[ 18 ]
#define brL param[ 19 ]
#define crL param[ 20 ]
#define drL param[ 21 ]
#define xrL param[ 22 ]
#define arR param[ 23 ]
#define brR param[ 24 ]
#define crR param[ 25 ]
#define drR param[ 26 ]
#define xrR param[ 27 ]

*/
#define param_wheelL 8
#define param_wheelR 13
#define param_railL 18
#define param_railR 23

_coefs_rail = coefs_rail();
_breaks_rail = breaks_rail();
_coefs_wheelL = coefs_wheelL();
_breaks_wheelL = breaks_wheelL();
_coefs_wheelR = coefs_wheelR();
_breaks_wheelR = breaks_wheelR();

get_spline_coefs (param, param_wheelL, _coefs_wheelL, _breaks_wheelL, q[ 9 ], breaks_wheelL_n_cols, coefs_wheelL_n_rows);
get_spline_coefs (param, param_wheelR, _coefs_wheelR, _breaks_wheelR, q[ 7 ], breaks_wheelR_n_cols, coefs_wheelR_n_rows);
get_spline_coefs (param, param_railL, _coefs_rail, _breaks_rail, q[ 12 ], breaks_rail_n_cols, coefs_rail_n_rows);
get_spline_coefs (param, param_railR, _coefs_rail, _breaks_rail, q[ 10 ], breaks_rail_n_cols, coefs_rail_n_rows);
  
