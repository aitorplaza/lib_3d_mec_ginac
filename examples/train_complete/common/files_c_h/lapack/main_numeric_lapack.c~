#include "Includes_variables_parameters.h"
#define DDL
#include "Includes_functions.h"
#include "Includes_Init_functions.h"
/* ********************************************************************************************* */
#include "defines.h"

#if !defined(_WIN32)
//#define dgelsd dgelsd_
//#define dgemv dgemv_
#define daxpy daxpy_
#define dnrm2 dnrm2_
#endif

#if defined(__MINGW32__)
#define dgelsd dgelsd_
#define dgemv dgemv_
#define daxpy daxpy_
#define dnrm2 dnrm2_
#endif

#include "write_data_file.h"

#include "newton_raphson_min_norm.h"

#include "Energy.h"


extern double dnrm2(int *n,double *x,int *incx);

int main (int argc, char *argv[]) {

#include "arguments.c"

#include "Init_variables_parameters.c"
#include "Init_functions.c"

//Choose integrator
#ifdef EULER
#include "direct_dynamics_lagrange_with_multipliers_and_qr_proyection_euler_improved_init.c"
#endif

#ifdef TRAPEZOIDAL
#include "direct_dynamics_lagrange_with_multipliers_trapezoidal_init.c"
#endif

#include "Done_variables_parameters.c"
#include "Done_functions.c"



    return 0;
}

