//gcc  -O2 -o main_numeric_zd_rt main_numeric_zd_rt.c lin_alg.c var_def.c var_init.c gen_coord_vect_def.c gen_coord_vect_init.c gen_vel_vect_def.c gen_vel_vect_init.c gen_accel_vect_def.c gen_accel_vect_init.c param_vect_def.c param_vect_init.c unknowns_vect_def.c unknowns_vect_init.c inputs_vect_def.c inputs_vect_init.c Phi.c Phi_q.c Phi_z.c Phi_d.c Beta.c Mzz.c Mzd.c Mdd.c Qz.c Qd.c Phi_q.c Gamma.c dPhi.c write_state_file.c write_state_file_header.c Qgamma.c MXPhi_qZero.c -lm -lblas -llapack
//./main_numeric_zd_rt 1.0 0.001 1e-8

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//************************************************************************************************
#include "var_def.h"
#include "param_vect_def.h"

#include "gen_coord_vect_def.h"
#include "gen_vel_vect_def.h"
#include "gen_accel_vect_def.h"

#include "unknowns_vect_def.h"
#include "inputs_vect_def.h"
//************************************************************************************************
#include	"Phi.h"
//#include	"dPhi.h"

//#include	"Phi_q.h"
#include	"Phi_z.h"
#include	"Phi_d.h"
#include	"Beta.h"

//#include	"Phi_q.h"
#include	"Gamma.h"

#include	"Qz.h"
#include	"Qd.h"

#include	"Mzz.h"
#include	"Mzd.h"
#include	"Mdd.h"
//************************************************************************************************
//#define n_gen_coord 	Phi_q_n_cols
#define n_coord_dep	Phi_d_n_cols
#define n_coord_indep	Phi_z_n_cols
//************************************************************************************************
double	_Inv_Phi_d[Phi_d_n_rows * Phi_d_n_cols];
//************************************************************************************************
// define TIME_ON // solo para calculo tiempo por iteracion
#ifdef TIME_ON

#include <sys/time.h>		/* struct timeval */
#include <unistd.h>			/* gettimeofday() */

static double timestamp()
{
	struct timeval tp;

	if (0 != gettimeofday(&tp, NULL)) {
		return 0.0;
	}
	return ((double) tp.tv_sec) + ((double) tp.tv_usec) / 1000000.0;
}

#endif
//************************************************************************************************
extern double dnrm2(int *n,double *x,int *incx);

int main (int argc, char *argv[]) {

    if (argc!=4){
        printf("Error: The program %s takes three parameters: %s integration_time delta_t newton-raphson-precision\n",argv[0],argv[0]);
        exit(1);
    }

    double integration_time=strtod(argv[1], NULL);
    double delta_t= strtod(argv[2], NULL);
    double tolerance= strtod(argv[3], NULL);
    long int k,steps;
    long int iter;

		steps=ceil(integration_time/delta_t);

		int iterations=1;

int			i, j, l, n_iterations;
double	AUX_V_dep_1[n_coord_dep], AUX_V_dep_2[n_coord_dep];
double	AUX_V_indep_1[n_coord_indep],AUX_V_indep_2[n_coord_indep];
double	AUX_M_indep_dep_1[n_coord_indep * n_coord_dep], AUX_M_indep_dep_2[n_coord_indep * n_coord_dep];
double	AUX_M_indep_indep_1[n_coord_indep * n_coord_indep], AUX_M_indep_indep_2[n_coord_indep * n_coord_indep];
double	INV_AUX_M_indep_indep[n_coord_indep * n_coord_indep];
double	A[n_coord_dep * n_coord_indep], AT[n_coord_indep * n_coord_dep];
double	b[n_coord_dep], c[n_coord_dep];

double	_MZ[n_coord_indep * n_coord_indep],INV_MZ[n_coord_indep * n_coord_indep];;
double	_QZ[n_coord_indep];

double	t_ini = 0.0, t_end = integration_time;

double	start, end;

//************************************************************************************************
//initialize variables anad parameters
    var_init();
    param_vect_init();
//initialize generalized coordinate, velocity and acceleration vectors
    gen_coord_vect_init();
    gen_vel_vect_init();
    gen_accel_vect_init();
//initialize joint force unknowns
    unknowns_vect_init();
    inputs_vect_init();
//************************************************************************************************
Phi();
//dPhi();

Phi_d();
//Phi_q();
Phi_z();
Beta();

Gamma();

Mzz();
Mzd();
Mdd();

Qz();
Qd();

//#define SCREEN_INIT
//************************************************************************************************
#ifdef SCREEN_INIT
Phi();
printf("\n");printf("q\n");Vect_Print(n_gen_coord, q);		// check initial value == Matlab
printf("Phi\n");Vect_Print(n_coord_dep, _Phi);		// check initial value == Matlab
printf("dq\n");Vect_Print(n_gen_coord, dq);printf("\n");		// check initial value == Matlab
#endif
//************************************************************************************************

/* Solving initial position - non lineal system */

Solve_N_R_while(n_coord_dep, &Phi, &Phi_d, &q[n_coord_indep], _Inv_Phi_d);

/* Solving initial velocity - lineal system */

Phi_z();
Mat_Vect_Mult(n_coord_dep, n_coord_indep, _Phi_z, dq, +1, AUX_V_dep_1);

Beta();
for (i = 0; i < n_coord_dep; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}

Mat_Vect_Mult(n_coord_dep, n_coord_dep, _Inv_Phi_d, AUX_V_dep_1, +1, &dq[n_coord_indep]);

//************************************************************************************************
#ifdef SCREEN_INIT
Phi();
printf("\n");printf("q\n");Vect_Print(n_gen_coord, q);		// check initial value == Matlab
printf("Phi\n");Vect_Print(n_coord_dep, _Phi);		// check initial value == Matlab
printf("dq\n");Vect_Print(n_gen_coord, dq);printf("\n");		// check initial value == Matlab
#endif
//************************************************************************************************

//************************************************************************************************
#ifdef TIME_ON
start = timestamp();
#endif
//************************************************************************************************
#ifndef TIME_ON
	FILE * state_file = fopen("state_zd_rt.dat", "w");
	write_state_file_header(state_file);
	printf("t = %g, %ld of %ld\n",t,k,steps);
#endif
//************************************************************************************************

//************************************************************************************************
// integration 
//************************************************************************************************
/* Solving for t > 0 */

for (k=1; k<=steps; k++){

	/* Solving Dynamics Forward */
	Mat_Mat_Mult(n_coord_dep, n_coord_dep, n_coord_indep, _Inv_Phi_d, _Phi_z, -1, A);

	for (j = 0; j < n_coord_indep; j++){
		for(i = 0; i < n_coord_dep; i++){
			AT[j + i * n_coord_indep] = A[i + j * n_coord_dep];
		}
	}

	Gamma();

	Mat_Vect_Mult(n_coord_dep, n_coord_dep, _Inv_Phi_d, _Gamma, +1, b);


	Mzz();
	Mzd();
	Mdd();
	Qz();
	Qd();

	Mat_Mat_Mult(n_coord_indep, n_coord_dep, n_coord_indep, _Mzd, A, +1, AUX_M_indep_indep_1);
	Mat_Mat_Mult(n_coord_indep, n_coord_dep, n_coord_dep, AT, _Mdd, +1, AUX_M_indep_dep_1);
	Mat_Mat_Mult(n_coord_indep, n_coord_dep, n_coord_indep, AUX_M_indep_dep_1, A, +1, AUX_M_indep_indep_2);
	Mat_Vect_Mult(n_coord_indep, n_coord_dep, AT, _Qd, +1, AUX_V_indep_1);	
	
	for (i = 0; i < n_coord_indep; i++){
		for(j = 0; j < n_coord_indep; j++){
			_MZ[i + j * n_coord_indep]=_Mzz[i + j * n_coord_indep] + AUX_M_indep_indep_1[j + i * n_coord_indep] + AUX_M_indep_indep_1[i + j * n_coord_indep] + AUX_M_indep_indep_2[i + j * n_coord_indep];
		}
	}

		for (i = 0; i < n_coord_indep; i++){
		for(j = 0; j < n_coord_dep; j++){
			AUX_M_indep_dep_2[i + j * n_coord_indep] = _Mzd[i + j * n_coord_indep] + AUX_M_indep_dep_1[i + j * n_coord_indep];
		}
	}

	Mat_Vect_Mult(n_coord_indep, n_coord_dep, AUX_M_indep_dep_2, b, +1, AUX_V_indep_2);	

	for (i = 0; i < n_coord_indep; i++){
		_QZ[i] = _Qz[i] + AUX_V_indep_1[i] - AUX_V_indep_2[i];
	}

	Mat_Inv( n_coord_indep, _MZ, INV_MZ);
	Mat_Vect_Mult(n_coord_indep, n_coord_indep, INV_MZ, _QZ, +1, ddq);	

	/* Calculate ddq ===> "ddd = A * ddz + b" */
	Mat_Vect_Mult(n_coord_dep, n_coord_indep, A, ddq, +1, &ddq[n_coord_indep]);	
	for (i = 0; i < n_coord_dep; i++){ ddq[n_coord_indep + i] = ddq[n_coord_indep + i] + b[i]; }

#ifndef TIME_ON
write_state_file(state_file);
t=t+delta_t;
#endif

	/* Step forward delta_t */

	for(i = 0; i < n_gen_coord; i++){ q[i] = q[i] + ( dq[i] + 0.5 * ddq[i] * delta_t ) * delta_t;	}
	for(i = 0; i < n_gen_coord; i++){	dq[i] = dq[i] + ddq[i] * delta_t;	}
	
	/* Correction for pos-vel */

	/* Correction pos */

//	Solve_N_R_while(n_coord_dep, &Phi, &Phi_d, &q[n_coord_indep], _Inv_Phi_d);

	Solve_N_R_for(n_coord_dep, &Phi, &Phi_d, &q[n_coord_indep], iterations, _Inv_Phi_d);

	/* Correction vel */

	Phi_z();
	Mat_Vect_Mult(n_coord_dep, n_coord_indep, _Phi_z, dq, +1, AUX_V_dep_1);

	Beta();
	for (i = 0; i < n_coord_dep; i++){ AUX_V_dep_1[i] = _Beta[i] - AUX_V_dep_1[i];	}

	Mat_Vect_Mult(n_coord_dep, n_coord_dep, _Inv_Phi_d, AUX_V_dep_1, +1, &dq[n_coord_indep]);

}

#ifndef TIME_ON
fclose(state_file);
#endif

#ifdef TIME_ON
end = timestamp();
n_iterations = (t_end - t_ini) / delta_t;

Vect_Print(n_gen_coord, q);		// check initial value == Matlab
Vect_Print(n_gen_coord, dq);		// check initial value == Matlab
Vect_Print(n_coord_indep, ddq);		// check initial value == Matlab

Phi();
Vect_Print	(n_coord_dep, _Phi);	/* CHECKS - Compare to Matlab */
dPhi();
Vect_Print	(n_coord_dep, _dPhi);	/* CHECKS - Compare to Matlab */

printf("calculation time: %f secs\n\n",(end - start) / ((double) n_iterations));
#endif

printf("ieup_rt\n");

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
