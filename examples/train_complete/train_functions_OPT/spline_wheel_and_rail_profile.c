#define thetaW_RFR q[ 44 ]
#define uW_RFR q[ 45 ]
#define uR_RFR q[ 46 ]
#define xR_RFR q[ 47 ]
#define thetaW_RFL q[ 48 ]
#define uW_RFL q[ 49 ]
#define uR_RFL q[ 50 ]
#define xR_RFL q[ 51 ]
#define thetaW_RRR q[ 52 ]
#define uW_RRR q[ 53 ]
#define uR_RRR q[ 54 ]
#define xR_RRR q[ 55 ]
#define thetaW_RRL q[ 56 ]
#define uW_RRL q[ 57 ]
#define uR_RRL q[ 58 ]
#define xR_RRL q[ 59 ]
#define thetaW_FFR q[ 60 ]
#define uW_FFR q[ 61 ]
#define uR_FFR q[ 62 ]
#define xR_FFR q[ 63 ]
#define thetaW_FFL q[ 64 ]
#define uW_FFL q[ 65 ]
#define uR_FFL q[ 66 ]
#define xR_FFL q[ 67 ]
#define thetaW_FRR q[ 68 ]
#define uW_FRR q[ 69 ]
#define uR_FRR q[ 70 ]
#define xR_FRR q[ 71 ]
#define thetaW_FRL q[ 72 ]
#define uW_FRL q[ 73 ]
#define uR_FRL q[ 74 ]
#define xR_FRL q[ 75 ]


_coefs_rail = coefs_rail();
_breaks_rail = breaks_rail();
_coefs_wheelL = coefs_wheelL();
_breaks_wheelL = breaks_wheelL();
_coefs_wheelR = coefs_wheelR();
_breaks_wheelR = breaks_wheelR();

// REAR BOGIE, FRONT SIDE, RIGHT WHEEL RFR
get_spline_coefs (param, aW_RFR, _coefs_wheelR, _breaks_wheelR, uW_RFR, breaks_wheelR_n_cols, coefs_wheelR_n_rows);
get_spline_coefs (param, aR_RFR, _coefs_rail  , _breaks_rail  , uR_RFR, breaks_rail_n_cols, coefs_rail_n_rows);

//REAR BOGIE, FRONT SIDE, LEFT WHEEL RFL
get_spline_coefs (param, aW_RFL, _coefs_wheelL, _breaks_wheelL, uW_RFL, breaks_wheelL_n_cols, coefs_wheelL_n_rows);
get_spline_coefs (param, aR_RFL, _coefs_rail  , _breaks_rail  , uR_RFL, breaks_rail_n_cols, coefs_rail_n_rows);

//REAR BOGIE, REAR SIDE, RIGHT WHEEL RRR
get_spline_coefs (param, aW_RRR, _coefs_wheelR, _breaks_wheelR, uW_RRR, breaks_wheelR_n_cols, coefs_wheelR_n_rows);
get_spline_coefs (param, aR_RRR, _coefs_rail  , _breaks_rail  , uR_RRR, breaks_rail_n_cols, coefs_rail_n_rows);

//REAR BOGIE, REAR SIDE, LEFT WHEEL RRL
get_spline_coefs (param, aW_RRL, _coefs_wheelL, _breaks_wheelL, uW_RRL, breaks_wheelL_n_cols, coefs_wheelL_n_rows);
get_spline_coefs (param, aR_RRL, _coefs_rail  , _breaks_rail  , uR_RRL, breaks_rail_n_cols, coefs_rail_n_rows);

// FRONT BOGIE, FRONT SIDE, RIGHT WHEEL FFR
get_spline_coefs (param, aW_FFR, _coefs_wheelR, _breaks_wheelR, uW_FFR, breaks_wheelR_n_cols, coefs_wheelR_n_rows);
get_spline_coefs (param, aR_FFR, _coefs_rail  , _breaks_rail  , uR_FFR, breaks_rail_n_cols, coefs_rail_n_rows);

// FRONT BOGIE, FRONT SIDE, LEFT WHEEL FFL
get_spline_coefs (param, aW_FFL, _coefs_wheelL, _breaks_wheelL, uW_FFL, breaks_wheelL_n_cols, coefs_wheelL_n_rows);
get_spline_coefs (param, aR_FFL, _coefs_rail  , _breaks_rail  , uR_FFL, breaks_rail_n_cols, coefs_rail_n_rows);

// FRONT BOGIE, REAR SIDE, RIGHT WHEEL FRR
get_spline_coefs (param, aW_FRR, _coefs_wheelR, _breaks_wheelR, uW_FRR, breaks_wheelR_n_cols, coefs_wheelR_n_rows);
get_spline_coefs (param, aR_FRR, _coefs_rail  , _breaks_rail  , uR_FRR, breaks_rail_n_cols, coefs_rail_n_rows);

// FRONT BOGIE, REAR SIDE, LEFT WHEEL FRL
get_spline_coefs (param, aW_FRL, _coefs_wheelL, _breaks_wheelL, uW_FRL, breaks_wheelL_n_cols, coefs_wheelL_n_rows);
get_spline_coefs (param, aR_FRL, _coefs_rail  , _breaks_rail  , uR_FRL, breaks_rail_n_cols, coefs_rail_n_rows);



