//  Fast, change -march to suit your needs (more /proc/cpuinfo)
// gcc -O3  -o main  main.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c unknowns_vect_def.c unknowns_vect_init.c Q.c M.c  write_state_file.c write_state_file_header.c qr_nm.c newton_raphson_qr.c printing.c  -lgsl -lgslcblas -lm  -march=i686 -fomit-frame-pointer

//  Probably as fast as above and less error prone, change -march to suit your needs (more /proc/cpuinfo)
// gcc -O2  -o main  main.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c unknowns_vect_def.c unknowns_vect_init.c Q.c M.c  write_state_file.c write_state_file_header.c qr_nm.c newton_raphson_qr.c printing.c  -lgsl -lgslcblas -lm  -march=i686 -fomit-frame-pointer

//  Debbuging
// gcc -g   -o main3-i686  main.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c unknowns_vect_def.c unknowns_vect_init.c Q.c M.c  write_state_file.c write_state_file_header.c qr_nm.c newton_raphson_qr.c printing.c  -lgsl -lgslcblas -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include <gsl/gsl_linalg.h>
//#include <gsl/gsl_blas.h>

#include "defines.h"

#include "var_def.h"
#include "param_vect_def.h"
#include "gen_coord_vect_def.h"
#include "gen_vel_vect_def.h"
#include "gen_accel_vect_def.h"
#include "unknowns_vect_def.h"
#include "inputs_vect_def.h"

#include "Phi.h"
#include "Phi_q.h"
#include "Beta.h"
#include "dPhi_dq.h"

#include "PhiInit.h"
#include "PhiInit_q.h"
#include "dPhiInit_dq.h"
#include "BetaInit.h"

#include "Qgamma.h"
#include "MXdPhi_dqZero.h"
#include "write_state_file_header.h"
#include "write_state_file.h"

//#include "lin_alg.h"

#include "print_mat.h"

//#include "printing.h"

#include "atom_def.c"
#include "step.c"

#include "newton_raphson_min_norm.h"
#include "Energy.h"
//#include "bq.h"
//#include "bdq.h"
//#include "AqX.h"


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

extern double dnrm2(int *n,double *x,int *incx);

int main (int argc, char *argv[]) {

//#define EULER
//#define TRAPEZOIDAL

    if (argc!=4){
        printf("Error: The program %s takes three parameters: %s integration_time delta_t newton-raphson-precision\n",argv[0],argv[0]);
        exit(1);
    }

    double integration_time=strtod(argv[1], NULL);
    double delta_t= strtod(argv[2], NULL);
    double tolerance= strtod(argv[3], NULL);
    long int k,steps;

//initialize variables
    var_init();

//initialize generalized coordinate, velocity and acceleration vectors
    gen_coord_vect_init();
    gen_vel_vect_init();
    gen_accel_vect_init();

    param_vect_init();

//initialize joint force unknowns
    unknowns_vect_init();
    inputs_vect_init();


//Choose integrator
#ifdef EULER
#include "direct_dynamics_lagrange_with_multipliers_and_qr_proyection_euler_improved_init.c"
#endif

#ifdef TRAPEZOIDAL
#include "direct_dynamics_lagrange_with_multipliers_trapezoidal_init.c"
#endif

/*#include "direct_dynamics_lagrange_with_multipliers_and_qr_proyection_rk4.c"*/

    free(q);
    free(dq);
    free(ddq);


    if(unknowns!=NULL)
        free(unknowns);
    if(inputs!=NULL)
        free(inputs);
    if(param!=NULL)
        free(param);

    return 0;
}

