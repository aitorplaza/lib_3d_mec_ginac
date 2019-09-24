
#define u_W_R q[7]
#define u_R_R q[8]
#define u_W_L q[11]
#define u_R_L q[12]


#define first_spline_param 10
#define aW_R first_spline_param + 0
#define aR_R first_spline_param + 5
#define aW_L first_spline_param + 10
#define aR_L first_spline_param + 15


//~ _coefs_rail = coefs_rail();
//~ _breaks_rail = breaks_rail();
//~ _coefs_wheelL = coefs_wheelL();
//~ _breaks_wheelL = breaks_wheelL();
//~ _coefs_wheelR = coefs_wheelR();
//~ _breaks_wheelR = breaks_wheelR();

// REAR BOGIE, FRONT SIDE, RIGHT WHEEL RFR
get_spline_coefs (param, aW_R, _coefs_wheelR, _breaks_wheelR, u_W_R, breaks_wheelR_n_cols, coefs_wheelR_n_rows);
get_spline_coefs (param, aR_R, _coefs_rail  , _breaks_rail  , u_R_R, breaks_rail_n_cols, coefs_rail_n_rows);

//REAR BOGIE, FRONT SIDE, LEFT WHEEL RFL
get_spline_coefs (param, aW_L, _coefs_wheelL, _breaks_wheelL, u_W_L, breaks_wheelL_n_cols, coefs_wheelL_n_rows);
get_spline_coefs (param, aR_L, _coefs_rail  , _breaks_rail  , u_R_L, breaks_rail_n_cols, coefs_rail_n_rows);
