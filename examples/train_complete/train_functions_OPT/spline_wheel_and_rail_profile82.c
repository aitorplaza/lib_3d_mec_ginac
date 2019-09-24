#define uW_RFR qaux[ 1 ]
#define uR_RFR qaux[ 2 ]
#define uW_RFL qaux[ 5 ]
#define uR_RFL qaux[ 6 ]
#define uW_RRR qaux[ 9 ]
#define uR_RRR qaux[ 10 ]
#define uW_RRL qaux[ 13 ]
#define uR_RRL qaux[ 14 ]
#define uW_FFR qaux[ 17 ]
#define uR_FFR qaux[ 18 ]
#define uW_FFL qaux[ 21 ]
#define uR_FFL qaux[ 22 ]
#define uW_FRR qaux[ 25 ]
#define uR_FRR qaux[ 26 ]
#define uW_FRL qaux[ 29 ]
#define uR_FRL qaux[ 30 ]

#define aW_RFR 70
#define aR_RFR 75
#define aW_RFL 91
#define aR_RFL 96
#define aW_RRR 112
#define aR_RRR 117
#define aW_RRL 133
#define aR_RRL 138
#define aW_FFR 154 
#define aR_FFR 159
#define aW_FFL 175
#define aR_FFL 180
#define aW_FRR 196
#define aR_FRR 201
#define aW_FRL 217
#define aR_FRL 222

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



