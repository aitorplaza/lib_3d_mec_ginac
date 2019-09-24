/* ********************************************************************************************* */
/*
/* This program integrates the multibody problem with different integrators 
/* Aitor Plaza & Roberto Yoldi
/* 
/* ********************************************************************************************* */

#define NEWTON_RAPHSON_TOLERANCE 1.0e-8 
#define UNKNOWNS
#define INPUTS
#define PHI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


 
#include "time_3D_mec.h"
#include "param.h"

#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "gen_auxcoord.h"
#include "gen_auxvel.h"
#include "gen_auxaccel.h"

#include "unknowns.h"
#include "inputs.h"

#include "PhiInit.h"
#include "PhiInit_q.h"
#include "BetaInit.h"
#include "dPhiInit_dq.h"

#include "Phi.h"
#include "Beta.h"
#include "Phi_q.h"
#include "dPhi_dq.h"
#include "Gamma.h"
#include "Q.h"
#include "M.h"
#include "MQ.h"
#include "Gamma.h"
#include "Output.h"

#include "Gammac.h"
#include "Betac.h"
#include "Phic.h"
#include "Phit.h"
#include "dPhic_dq.h"
#include "dPhit_dq.h"
#include "dPhit_ds.h"

//~ #include "Declare_Variables_Train.h"
/* ********************************************************************************************* */
//~ #include "write_data_file.h"
/* ********************************************************************************************* */

//#include "one_step.h"
/* ********************************************************************************************* */
#include <sys/time.h>

/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* If LIN_ALG library is used                                                                    */
/* ********************************************************************************************* */
#include "lin_alg.h"
#include "timestamp.c"


extern void Initial_position_velocity_with_splines (double * q, double * s,  double *dq, double * ds, double * param);
 


//*********************************************************************************
//includes needed in train model
  //~ #include "Output.h"
  #include "mu_div_mod_vel.h"
  #include "get_spline_coefs.h"
  #include "breaks_rail.h"
  #include "breaks_wheelL.h"
  #include "breaks_wheelR.h"
  #include "coefs_rail.h"
  #include "coefs_wheelL.h"
  #include "coefs_wheelR.h"
  #include "Initial_position_velocity_with_splines.h"
  #include "several_functions.h"  
  #include "hertz_ellipse.h" 
  #include "Table_Hertz.h"
  #include "kalker_coeffs.h" 
  #include "Table_Kalker.h"
  #include "kalker_forces.h"   
  
  #include "CKRFR.h"
  #include "CKRFL.h"
  #include "CKRRR.h"
  #include "CKRRL.h" 
  #include "CKFFR.h"
  #include "CKFFL.h"  
  #include "CKFRR.h"
  #include "CKFRL.h" 
  
  #include "Delta.h"


/* ********************************************************************************************* */
/*#include "Energy.h"*/

int main (int argc, char *argv[]) {

#include "arguments.c"


Init_t ( ); 
Init_param ( );
Init_q ( );
Init_dq ( );
Init_ddq ( );
Init_qaux ( );
Init_dqaux ( );
Init_ddqaux ( );
Init_unknowns ( );
Init_inputs ( );


Init_param_values ( );
Init_q_values ( ); 
Init_dq_values ( ); 
Init_ddq_values ( );
Init_qaux_values ( ); 
Init_dqaux_values ( ); 
Init_ddqaux_values ( );
Init_unknowns_values ( );
Init_inputs_values ( );

Init_PhiInit (  );
Init_PhiInit_q (  );
Init_BetaInit (  ) ;
Init_dPhiInit_dq (  );

Init_Phi (  );
Init_Beta (  ) ;
Init_Phi_q (  );
Init_dPhi_dq (  );
Init_Q (  );
Init_M (  );
Init_MQ (  );
Init_Gamma (  );
Init_Output (  );

Init_Gammac (  );
Init_Betac (  ) ;
Init_Phic (  );
Init_Phit (  );
Init_dPhic_dq (  );
Init_dPhit_dq (  );
Init_dPhit_ds (  );

Init_Table_Kalker ( );
Init_Table_Kalker ( );

Init_CKRFR ( );
Init_CKRFL ( );
Init_CKRRR ( );
Init_CKRRL ( );
Init_CKFFR ( );
Init_CKFFL ( );
Init_CKFRR ( );
Init_CKFRL ( );


#define MAX(a,b) (((a)>(b))?(a):(b))
#define PERM1(fi, cj, fi_ini, cj_ini, stride) ((fi+fi_ini)+(cj+cj_ini)*stride)
#define PERM(fi, cj, fi_ini, cj_ini, stride, vperm) (vperm[fi+fi_ini]+vperm[cj+cj_ini]*stride)
int  iterations_NR  = 1; 
/* ********************************************************************************************* */
/* Initial Position and Velocity                                                                 */
/* ********************************************************************************************* */

int i,j;
double BufferJT[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_cols];
double BufferAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
double BufferAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferIAUXCols[2*dPhiInit_dq_n_cols*dPhiInit_dq_n_cols];
double BufferIAUXRows[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferPINV[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];    
double _Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];
double _Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];
double	correction_dq[dPhi_dq_n_cols];
double AUX_V_Init[PhiInit_q_n_rows];
double BufferL[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferU[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
int p_vector[dPhic_dq_n_rows], q_vector[dPhic_dq_n_cols],  perm_vel[dPhic_dq_n_cols];
double	deltaqs[PhiInit_q_n_cols];

double qs[n_gen_coord + n_gen_auxcoord];
double dqs[n_gen_vel + n_gen_auxvel];

for (i = 0; i < n_gen_coord; i++){qs[i]=q[i];}
for (i = 0; i < n_gen_auxcoord; i++){qs[n_gen_coord + i]=qaux[i];}


#include "spline_wheel_and_rail_profile82.c"

PhiInit();
PhiInit_q();
double conv_err = 0.0;
conv_err =  module(PhiInit_n_rows,_PhiInit);

while (conv_err > 1.0e-12){

    Mat_PInv( PhiInit_q_n_rows,PhiInit_q_n_cols, _PhiInit_q, _Inv_PhiInit_q, BufferJT,BufferAUXCols,BufferAUXRows,BufferIAUXCols,BufferIAUXRows,BufferPINV);
    Mat_Vect_Mult(PhiInit_q_n_cols,PhiInit_q_n_rows , _Inv_PhiInit_q,_PhiInit , +1, deltaqs);

    for (i=0; i<PhiInit_q_n_cols; i++){
      qs[i] -= deltaqs[i];             
    }
    for (i = 0; i < n_gen_coord; i++){q[i]=qs[i];}
    for (i = 0; i < n_gen_auxcoord; i++){qaux[i] = qs[n_gen_coord + i];}
    
    PhiInit();
    PhiInit_q();
    
    conv_err =  module(PhiInit_n_rows,_PhiInit);

}

for (i = 0; i < n_gen_coord; i++){q[i]=qs[i];}
for (i = 0; i < n_gen_auxcoord; i++){qaux[i] = qs[n_gen_coord + i];}
#include "spline_wheel_and_rail_profile82.c"

BetaInit();
dPhiInit_dq();

Mat_PInv  (dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, BufferPINV);
//Mat_PInvLU(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, p_vector, q_vector, BufferL, BufferU);

Mat_Vect_Mult(dPhiInit_dq_n_cols, dPhiInit_dq_n_rows, _Inv_dPhiInit_dq, AUX_V_Init, 1, correction_dq);

for (i = 0; i < dPhiInit_dq_n_cols; i++){ dqs[i] = dqs[i] + correction_dq[i];	}

for (i = 0; i < dPhic_dq_n_cols; i++){perm_vel[i]=i;}
for (i = 0; i < dPhic_dq_n_rows; i++){p_vector[i]=i;}

//~ Vect_Print_Int  (dPhic_dq_n_rows, p_vector);
//~ Vect_Print_Int  (dPhic_dq_n_cols, perm_vel);

//~ Vect_Print  (n_gen_coord+n_gen_auxcoord, qs);

inputs[0]=0.0;
inputs[1]=0.0;

double vs=50.0;
dq[0] = 0.2374*vs;//dx
dq[16]= 0.4746*vs;//db
dq[19]= 0.4746*vs;//db
dq[22]= 0.4746*vs;//db
dq[25]= 0.4746*vs;//db
dq[42]= +2.0171*vs;//dmot
dq[43]= +2.0171*vs;//dmot

/* ********************************************************************************************* */
/* Solve_Dynamics Train UK                                                                       */
/* ********************************************************************************************* */
double _INV_M_aux[M_n_rows * M_n_cols];
double aux_ddq1[n_gen_accel], aux_ddq2[n_gen_accel];
double aux_dPhic_dq_T[ M_n_rows * dPhic_dq_n_rows ];
double bb[ dPhic_dq_n_rows ];
double AA[ dPhic_dq_n_rows * dPhic_dq_n_rows ], INV_AA[ dPhic_dq_n_rows * dPhic_dq_n_rows ];
double Buffer[2*MAX(M_n_cols,dPhic_dq_n_rows)*MAX(M_n_cols,dPhic_dq_n_rows)];
double Trasp_dPhic_dq[ dPhic_dq_n_rows * dPhic_dq_n_cols ]; 


Delta();
M();
Gammac();
dPhic_dq();
//Vect_Print  (n_unknowns, unknowns);

Mat_Inv(M_n_cols ,_M, _INV_M_aux,Buffer);
Mat_Vect_Mult(M_n_rows, M_n_cols,_INV_M_aux ,_Delta, +1, aux_ddq1 );
Mat_Trasp(dPhic_dq_n_rows, dPhic_dq_n_cols, _dPhic_dq, Trasp_dPhic_dq); 
Mat_Mat_Mult(M_n_rows, M_n_cols, dPhic_dq_n_rows, _INV_M_aux , Trasp_dPhic_dq, +1, aux_dPhic_dq_T );
Mat_Vect_Mult(dPhic_dq_n_rows, dPhic_dq_n_cols, _dPhic_dq , aux_ddq1, +1, bb);
for (i=0; i<n_unknowns; i++){ bb[i]=bb[i]-_Gammac[i]; } 
Mat_Mat_Mult(dPhic_dq_n_rows, dPhic_dq_n_cols, dPhic_dq_n_rows, _dPhic_dq , aux_dPhic_dq_T, +1, AA);
Mat_Inv(dPhic_dq_n_rows, AA, INV_AA,Buffer);
Mat_Vect_Mult(n_unknowns, n_unknowns, INV_AA , bb, +1, unknowns); 
Mat_Vect_Mult(dPhic_dq_n_cols, dPhic_dq_n_rows, aux_dPhic_dq_T, unknowns, +1, aux_ddq2);


for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; } 
//Vect_Print  (n_unknowns, unknowns);
/* ********************************************************************************************* */
/* Calculate KALKER's coeffs                                                                     */
/* ********************************************************************************************* */
Output();
Table_Hertz();
Table_Kalker();

//Vect_Print  (n_unknowns, unknowns);
#include "kalker_coeffs_calculation82.c"
//Vect_Print  (n_unknowns, unknowns);


// check kalker coeffs !!!!!!!!!!!!!

 

/* ********************************************************************************************* */
/* IWrite to file.                                                                               */
/* ********************************************************************************************* */

FILE * data_file = fopen(output_file_name, "w");
//write_data_file_header(data_file);
write_data_file(data_file);

/* ********************************************************************************************* */
/* Integration                                                          */
/* ********************************************************************************************* */


long int k_iter;
int i_ini,j_ini;

int n_vel_dep = Phic_n_rows;
int n_vel_indep = n_gen_coord -n_vel_dep;


double A[n_vel_dep*n_vel_indep];

double v_crit = 0.001;
double velRFR = MAX (_Output[5],v_crit);
double velRFL = MAX (_Output[15],v_crit);
double velRRR = MAX (_Output[25],v_crit);
double velRRL = MAX (_Output[35],v_crit);   
double velFFR = MAX (_Output[45],v_crit);
double velFFL = MAX (_Output[55],v_crit);    
double velFRR = MAX (_Output[65],v_crit);
double velFRL = MAX (_Output[75],v_crit);
    
//Dynamics    
double b[dPhic_dq_n_rows];
double yddq[n_vel_dep];
double AUX_M_indep_indep_1[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)],AUX_M_indep_indep_2[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)];
double AUX_M_indep_dep_1[MAX(n_vel_indep,n_vel_indep)*MAX(Phi_n_rows,n_vel_dep)] , AUX_M_indep_dep_2[MAX(n_vel_indep,n_vel_indep)*MAX(Phic_n_rows,dPhic_dq_n_rows)];
double _MZ[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)];
double _QZ[MAX(n_vel_indep,n_vel_indep)];
double AUX_V_indep_1[MAX(n_vel_indep,n_vel_indep)],AUX_V_indep_2[MAX(n_vel_indep,n_vel_indep)];
double aux_dq[n_gen_vel],aux_ddq[n_gen_accel];
double _IMZ[n_vel_indep*n_vel_indep], JAug[2*n_vel_indep*n_vel_indep];


// Kalker
double _CK[n_gen_coord*n_gen_coord];
int CK_n_rows = n_gen_coord;
double AUX_CK_indep_indep_1[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)],AUX_CK_indep_indep_2[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)],AUX_CK_indep_indep_3[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)];
double AUX_CK_indep_dep_1[MAX(n_vel_indep,n_vel_indep)*MAX(Phic_n_rows,n_vel_dep)] , AUX_CK_indep_dep_2[MAX(n_vel_indep,n_vel_indep)*MAX(Phic_n_rows,dPhic_dq_n_rows)];
double _CKZ[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)];

// Kalker2
double _Mdt[n_gen_coord*n_gen_coord];
double _MdtC[n_gen_coord*n_gen_coord];
double _Mdtdq[n_gen_coord];
double _Delta_Mdtdq[n_gen_coord];
double _dPhidqdq[n_vel_dep];
double _Gammadt_dPhidqdq[n_vel_dep];

// Z partition
int perm_M[n_vel_indep];
int M_vecs[n_vel_indep];
double QLaux[n_vel_indep];


for (i = 0; i < n_vel_indep; i++){perm_M[i]=i;}
for (i = 0; i < n_vel_indep; i++){M_vecs[i]=i;}

double _Midz[n_vel_indep];
double Mzaux1[n_vel_indep*n_vel_indep];
double Mzaux2[n_vel_indep];


double dz[n_vel_indep];
double dd[n_vel_dep];
double dz_k[n_vel_indep];
double dd_k[n_vel_dep];
double dq_k[n_gen_coord];
double dq_k1[n_gen_coord];


//unkowns
double lambda_c[dPhic_dq_n_rows];  
double AUX_L_dep[1*n_vel_dep],AUX_L_indep[1*n_vel_dep],b_aux[n_vel_dep*1], yL[n_vel_dep*1];


//projection
int perm_s[dPhit_ds_n_cols];
int p_vecs[dPhit_ds_n_rows];
double delta_s[n_gen_auxcoord];
double ys[n_gen_auxcoord];   
double yq[n_vel_dep],ydq[n_vel_dep];
double aux_dq_dep[n_vel_dep];
double	AUX_V_dep_1[dPhic_dq_n_rows],AUX_V_dep_2[MAX(Phic_n_rows,dPhic_dq_n_rows)];
double _dPhit_dqdq[dPhit_dq_n_rows*n_gen_vel];


for (i = 0; i < dPhit_ds_n_cols; i++){perm_s[i]=i;}
for (i = 0; i < dPhit_ds_n_rows; i++){p_vecs[i]=i;}


#include "kalker_coeffs_calculation82.c"

//Vect_Print    (n_param, param);
//Vect_Print    (n_gen_coord, q);
//Vect_Print    (n_gen_coord, dq);
//Vect_Print    (n_unknowns, unknowns);        


//Vect_Print    (n_gen_coord, q);
//Vect_Print    (n_gen_auxcoord, qaux);

Vect_Print    (n_gen_coord, dq);
Vect_Print    (n_unknowns, unknowns);


for (k_iter=1; k_iter<=steps; k_iter++){
    
    struct timeval integration1,integration2 ;
    gettimeofday(&integration1, NULL);
    struct timeval Outputstart,Outputstop;
    //~ gettimeofday(&Outputstart, NULL);
    //~ Output();
    //~ gettimeofday(&Outputstop, NULL);
    
    struct timeval Kalkerstart1,Kalkerstop1,Kalkerstart2,Kalkerstop2;
 
    //gettimeofday(&Kalkerstart1, NULL);
    //#include "kalker_coeffs_calculation.c"
    //gettimeofday(&Kalkerstop1, NULL);
 
    //~ velRFR = MAX (_Output[5], v_crit);
    //~ velRFL = MAX (_Output[15],v_crit);
    //~ velRRR = MAX (_Output[25],v_crit);
    //~ velRRL = MAX (_Output[35],v_crit);   
    //~ velFFR = MAX (_Output[45],v_crit);
    //~ velFFL = MAX (_Output[55],v_crit);    
    //~ velFRR = MAX (_Output[65],v_crit);
    //~ velFRL = MAX (_Output[75],v_crit);    

    struct timeval functions1start,functions1stop ;
    gettimeofday(&functions1start, NULL);
    Delta();
    M();
    Gammac();    
    dPhic_dq();
    gettimeofday(&functions1stop, NULL);
    
    
    //~ struct timeval splinesstart,splinesstop ;
    //~ gettimeofday(&splinesstart, NULL); 
    //~ #include "spline_wheel_and_rail_profile82.c"
    //~ gettimeofday(&splinesstop, NULL);
    
    gettimeofday(&Kalkerstart1, NULL);
    Output();
    #include "kalker_coeffs_calculation82.c"
	CKRFR ( ); 	CKRFL ( );
	CKRRR ( );	CKRRL ( );
	CKFFR ( );	CKFFL ( );
	CKFRR ( );	CKFRL ( );
    
    velRFR = MAX (_Output[5], v_crit);
    velRFL = MAX (_Output[15],v_crit);
    velRRR = MAX (_Output[25],v_crit);
    velRRL = MAX (_Output[35],v_crit);   
    velFFR = MAX (_Output[45],v_crit);
    velFFL = MAX (_Output[55],v_crit);    
    velFRR = MAX (_Output[65],v_crit);
    velFRL = MAX (_Output[75],v_crit);  
      
    gettimeofday(&Kalkerstop1, NULL);
    //~ for (i = 0; i < (n_gen_coord * n_gen_coord); i++){   
        //~ _Mdt[i] = _M[i] / delta_t;      
    //~ }
//~ 
    //~ for (i = 0; i < (n_gen_coord * n_gen_coord); i++){
        //~ _MdtC[i] =   _Mdt[i] + 
                    //~ ( _CKRFR[i]/velRFR + _CKRFL[i]/velRFL + _CKRRR[i]/velRRR + _CKRRL[i]/velRRL +
                      //~ _CKFFR[i]/velFFR + _CKFFL[i]/velFFL + _CKFRR[i]/velFRR + _CKFRL[i]/velFRL );  
    //~ }
    struct timeval Dynstart,Dynstop ;
    gettimeofday(&Dynstart, NULL);
    for (i = 0; i < (n_gen_coord * n_gen_coord); i++){
        _Mdt[i] = _M[i] / delta_t;
        _MdtC[i] =   _Mdt[i] + 
                    ( _CKRFR[i]/velRFR + _CKRFL[i]/velRFL + _CKRRR[i]/velRRR + _CKRRL[i]/velRRL +
                      _CKFFR[i]/velFFR + _CKFFL[i]/velFFL + _CKFRR[i]/velFRR + _CKFRL[i]/velFRL );  
    }   
    
    Mat_Vect_Mult(n_gen_coord, n_gen_coord, _Mdt, dq, +1, _Mdtdq);
  
    //printf("_MdtC\n"); Mat_Print(n_gen_coord , n_gen_coord, _MdtC);
    for (i = 0; i < (n_gen_coord ); i++){
        _Delta_Mdtdq[i] = _Delta[i] + _Mdtdq[i]; 
    }

    Mat_Vect_Mult(n_vel_dep, n_gen_coord, _dPhic_dq, dq, +1, _dPhidqdq);
    
    for (i = 0; i < (n_vel_dep); i++){
        _Gammadt_dPhidqdq[i] = _Gammac[i]*delta_t + _dPhidqdq[i]; 
    }    



  
    
    /*for coordinate partitioning*/
    lufp4(dPhic_dq_n_rows,dPhic_dq_n_rows, dPhic_dq_n_cols, _dPhic_dq, p_vector, perm_vel);/*for coordinate partitioning*/

    /* Calculate A with this dedicated backward */
    for (i = 0; i< n_vel_indep ; i++){
        backward_substitution_LUpq_pq_A(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel, &_dPhic_dq[perm_vel[i+n_vel_dep] * dPhic_dq_n_rows ], &A[ i * dPhic_dq_n_rows ]);    
    }
    
    /*Calculate b*/
    forward_substitution_LUpq_pq_x (dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel , _Gammadt_dPhidqdq, yddq);
    backward_substitution_LUpq_pq_x(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel , yddq, b);
    
    /*Mzd*A*/
    i_ini=n_vel_dep;
    j_ini=0;
    for (i=0; i<n_vel_indep; i++){
	    for (j=0; j< n_vel_indep; j++){
		    AUX_M_indep_indep_1[i+j*n_vel_indep] = 0.0;
		    for	(k=0; k<dPhic_dq_n_rows; k++){
			    AUX_M_indep_indep_1[i+j*n_vel_indep] =  _MdtC[PERM(i,k,i_ini, j_ini,M_n_rows, perm_vel)] * A[k+j*dPhic_dq_n_rows] + AUX_M_indep_indep_1[i+j*n_vel_indep];
			}
		}
	}
    
	/*A'*Mdd*/
	i_ini=0;
	j_ini=0;
	for (i=0; i<n_vel_indep; i++){
		for (j=0; j< dPhic_dq_n_rows; j++){
			AUX_M_indep_dep_1[i+j*n_vel_indep] = 0.0;
			for	(k=0; k<dPhic_dq_n_rows; k++){
  				AUX_M_indep_dep_1[i+j*n_vel_indep] =   A[k+i*dPhic_dq_n_rows] * _MdtC[PERM(k,j,i_ini, j_ini,M_n_rows, perm_vel)]  + AUX_M_indep_dep_1[i+j*n_vel_indep];
			}
		}
	}
       
    /*(A'*Mdd)*A=AUX_M_indep_indep_2*/
    Mat_Mat_Mult(n_vel_indep, dPhic_dq_n_rows, n_vel_indep, AUX_M_indep_dep_1, A, +1, AUX_M_indep_indep_2);
    
    
    /*AUX_V_indep_1=A'* Qd*/
    for (i=0; i<n_vel_indep; i++){
	    AUX_V_indep_1[i] = 0.0;
	    for (j=0; j<dPhic_dq_n_rows; j++){
		    AUX_V_indep_1[i] = A[j+i*dPhic_dq_n_rows] * _Delta_Mdtdq[perm_vel[j]] + AUX_V_indep_1[i];
		}
	}

	/*MZ =  Mzz + Mzd*A +(Mzd*A )' + (A'*Mdd)*A*/
	i_ini=n_vel_dep;
	j_ini=n_vel_dep;
	for (i = 0; i < n_vel_indep; i++){
        for(j = 0; j < n_vel_indep; j++){	
			_MZ[i + j * n_vel_indep]= _MdtC[PERM(i,j,i_ini, j_ini, M_n_rows, perm_vel)] + AUX_M_indep_indep_1[j + i * n_vel_indep] + AUX_M_indep_indep_1[i + j * n_vel_indep] + AUX_M_indep_indep_2[i + j * n_vel_indep]; 
		}
	}
    
    //Mat_Print(n_vel_indep, n_vel_indep, _MZ);


	/*Mzd+(A'*Mdd)*/
	i_ini=n_vel_dep;
	j_ini=0; 
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < dPhic_dq_n_rows; j++){
		AUX_M_indep_dep_2[i + j * n_vel_indep] = _MdtC[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] + AUX_M_indep_dep_1[i + j * n_vel_indep];
		}
	}
    
    /* (Mzd+(A'*Mdd) )* b */   
    Mat_Vect_Mult(n_vel_indep, dPhic_dq_n_rows, AUX_M_indep_dep_2, b, +1, AUX_V_indep_2);	

    
    /*_QZ = Qz + A'* Qd - (Mzd+(A'*Mdd))*b*/
	for (i = 0; i < n_vel_indep; i++){
		_QZ[i] = _Delta_Mdtdq[perm_vel[i+n_vel_dep]] + AUX_V_indep_1[i] - AUX_V_indep_2[i];
	}   

    //for (i = 0; i < n_gen_coord; i++){dq_k[i] = dq[perm_vel[i]]; }
    //for (i = 0; i < n_vel_indep; i++){dz_k[i] = dq_k[n_vel_dep+i];}     
   

    //Mat_Vect_Mult (n_vel_indep, n_vel_indep ,_MZ , dz_k, +1 ,_Midz);
    
    /* Solve MZ * ddz = QZ */
    //solve_lin_sys_ldl(n_vel_indep,_MZ , _QZ, &aux_dq[n_vel_dep], AUX_M_indep_indep_1, AUX_M_indep_indep_2 , AUX_V_indep_1 , AUX_V_indep_2);    
    //Mat_Inv(n_vel_indep, _MZ, _IMZ, JAug);
    //Mat_Vect_Mult(n_vel_indep, n_vel_indep,_IMZ ,_QZ, +1,dz );
    
    lufp4(n_vel_indep,n_vel_indep, n_vel_indep, _MZ, M_vecs, perm_M);
    forward_substitution_LUpq_T_pq_q (n_vel_indep,n_vel_indep, _MZ, M_vecs, perm_M, _QZ  , QLaux);
    backward_substitution_LUpq_T_pq_q(n_vel_indep,n_vel_indep, _MZ, M_vecs, perm_M, QLaux, dz); 


    for (i = 0; i < n_vel_indep; i++){aux_dq[i+n_vel_dep] = dz[i];}

    //printf("------------------------------------------------------\n");
    //Mat_Print(n_vel_indep, n_vel_indep, _MZ);
    //Mat_Print(n_vel_indep, n_vel_indep, _IMZ);
    //Vect_Print    (, dz);
   
    
    /* Calculate  ddd = A * ddz + b -> C.4 Equation DSM*/
    Mat_Vect_Mult(dPhic_dq_n_rows, n_vel_indep, A, &aux_dq[n_vel_dep], +1, aux_dq);
    for (i = 0; i < dPhic_dq_n_rows; i++){ aux_dq[i] = aux_dq[i] + b[i]; }
    
    //~ for (i = 0; i < n_gen_vel; i++){dq_k[i] = dq[i]; }
    
    for (i = 0; i < dPhic_dq_n_cols; i++){ dq[perm_vel[i]]=aux_dq[i]; } // dq_{k+ dt}
    
    //for (i = 0; i < n_vel_dep; i++){dq_k1[i]=dd[i];}
    //for (i = 0; i < n_vel_indep; i++){dq_k1[i+n_vel_dep] = dz[i];}

    //Vect_Print    (n_gen_coord, aux_dq);
    //Vect_Print    (n_gen_coord, dq_k);
    //Vect_Print    (n_gen_coord, dq);

    /* ========================================================================================================================================= */
    /* Calculate unknowns */
    /* Phi_d_T * lambda = Qd - Mdd * ddd - Mdz * ddz */
    /* ========================================================================================================================================= */
    //double ddq[n_gen_coord];

    //~ for (i = 0; i < n_gen_coord; i++){
       //~ ddq[i] = (dq[i]-dq_k[i])/delta_t;
    //~ } 

    /* Mdd · dd */
    i_ini=0;
    j_ini=0;
    for (i=0; i<n_vel_dep; i++){
	AUX_L_dep[i] = 0.0;
	    for (j=0; j<n_vel_dep; j++){
		    AUX_L_dep[i] = AUX_L_dep[i] + _MdtC[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * dq[perm_vel[j]] ;
		}
	}
	/* Mdz · dz */
	i_ini=0;
	j_ini=n_vel_dep;
	for (i=0; i<n_vel_dep; i++){
	AUX_L_indep[i] = 0.0;
		for (j=0; j<n_vel_indep; j++){
			AUX_L_indep[i] = AUX_L_indep[i] + _MdtC[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * dq[perm_vel[j+n_vel_dep]] ;
		}
	}

	/* Qd - Mdd * dd - Mdz * dz */
	for (i = 0; i < n_vel_dep; i++){
		b_aux[i] = _Delta_Mdtdq[perm_vel[i]] - AUX_L_dep[i] - AUX_L_indep[i];
	}
    
    /* dPhic_dd_T *lambda_c =  Deltad - Mdd * ddd - Mdz * ddz */
    forward_substitution_LUpq_T_pq_q (n_vel_dep,n_vel_dep, _dPhic_dq, p_vector, perm_vel, b_aux, yL);
    backward_substitution_LUpq_T_pq_q(n_vel_dep,n_vel_dep, _dPhic_dq, p_vector, perm_vel, yL, unknowns); 
    
 
    
    
    
    
    //Vect_Print    (n_vel_dep, lambda_c);
    //for(i = 0; i < n_vel_dep; i++){unknowns[i] =lambda_c[i];}
    //for(i = 0; i < n_vel_dep; i++){unknowns[perm_vel[i]] =lambda_c[i];}
    //for (i=0; i< n_gen_accel; i++){ ddqunknowns[i]=ddq[i]; } 
    //for (i=0; i< n_unknowns; i++){ ddqunknowns[i+n_gen_accel]=unknowns[i]; } 

    //return 0;
    gettimeofday(&Dynstop, NULL);
    /* ========================================================================================================================================= */
    /* Integration
    /* ========================================================================================================================================= */

      //double q_k1[n_gen_coord];

      //~ Vect_Print    (n_gen_coord, dq);
      //for (i = 0; i < n_gen_coord; i++){dq[i] = dq_k1[perm_vel[i]] ;}
      //for (i = 0; i < n_gen_coord; i++){dq[perm_vel[i]] = dq_k1[i] ;}
      //~ Vect_Print    (n_gen_coord, dq);
      //~ Vect_Print    (n_gen_coord, q);
      struct timeval Intstart,Intstop ;
      gettimeofday(&Intstart, NULL);
      for(i = 0; i < n_gen_coord; i++){q[i] = q[i] + dq[i] * delta_t;}
      gettimeofday(&Intstop, NULL);
      
      //Vect_Print    (n_gen_coord, q);
      
    /* ========================================================================================================================================= */
    /* Projection
    /* ========================================================================================================================================= */
    struct timeval Projstart,Projstop ; 

    
    struct timeval functions2start,functions2stop ;
    gettimeofday(&functions2start, NULL);
    
    dPhit_ds();
    Phit();
    dPhic_dq();
    Phic();    
    Betac();
    dPhit_dq();
    gettimeofday(&functions2stop, NULL);
 

    gettimeofday(&Projstart, NULL);
    lufp4(dPhit_ds_n_rows,dPhit_ds_n_rows, dPhit_ds_n_cols, _dPhit_ds, p_vecs, perm_s);

    for (i = 0; i < 1 ; i++){
        Phit();
        forward_substitution_LUpq_pq_x (dPhit_ds_n_rows,dPhit_ds_n_rows, _dPhit_ds, p_vecs, perm_s, _Phit, ys);
        backward_substitution_LUpq_pq_x(dPhit_ds_n_rows,dPhit_ds_n_rows, _dPhit_ds, p_vecs, perm_s, ys, delta_s);
        for (j = 0; j < n_gen_auxcoord; j++){    
            //qaux[j] = qaux[j] - delta_s[perm_s[j]];
            qaux[perm_s[j]] = qaux[perm_s[j]] - delta_s[j];
        }	
    }
   
    
    lufp4(dPhic_dq_n_rows,dPhic_dq_n_rows, dPhic_dq_n_cols, _dPhic_dq, p_vector, perm_vel);
    /* Correction pos -> C.2 Equation DSM*/
    for (i = 0; i < iterations_NR ; i++){
        Phic();
        forward_substitution_LUpq_pq_x (dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel, _Phic, yq);
        backward_substitution_LUpq_pq_x(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel, yq, aux_dq_dep);
        //for (i = 0; i < Phi_n_rows; i++){
        for (j = 0; j < n_vel_dep; j++){    
            q[perm_vel[j]] = q[perm_vel[j]] - aux_dq_dep[j];
        }	
    }
    
    struct timeval splinesstart,splinesstop ;
    gettimeofday(&splinesstart, NULL); 
    #include "spline_wheel_and_rail_profile82.c"
    gettimeofday(&splinesstop, NULL);
    
    
    /* Correction vel -> C.3 Equation DSM*/
    for (i = 0; i< n_vel_indep ; i++){
        backward_substitution_LUpq_pq_A(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel, &_dPhic_dq[perm_vel[i+n_vel_dep] * dPhic_dq_n_rows ], &A[ i * dPhic_dq_n_rows ]); /* Calculate A with this dedicated backward */
    }
    
   
    forward_substitution_LUpq_pq_x(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel , _Betac, ydq);
    backward_substitution_LUpq_pq_x(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel , ydq, AUX_V_dep_1 );  

    for (i=0; i< n_vel_dep; i++){        
        AUX_V_dep_2[i] = 0.0;
        for (j=0; j<n_vel_indep; j++){
            AUX_V_dep_2[i] =  AUX_V_dep_2[i] + A[i+j*n_vel_dep] * dq[perm_vel[j+n_vel_dep]];
        }
    }

    for (i=0; i< n_vel_dep; i++){    
        dq[perm_vel[i]] = AUX_V_dep_2[i] - AUX_V_dep_1[i] ;
    }
    

    //~ dPhit_dq();
    Mat_Vect_Mult(dPhit_dq_n_rows, n_gen_vel, _dPhit_dq, _dPhit_dqdq, -1, dq);
    forward_substitution_LUpq_pq_x (dPhit_ds_n_rows,dPhit_ds_n_rows, _dPhit_ds, p_vecs, perm_s, _dPhit_dqdq, ys);
    backward_substitution_LUpq_pq_x(dPhit_ds_n_rows,dPhit_ds_n_rows, _dPhit_ds, p_vecs, perm_s, ys, delta_s);   
    for (j = 0; j < n_gen_auxcoord; j++){    
        dqaux[perm_s[j]] = delta_s[j];
    }
    
    gettimeofday(&Projstop, NULL);
    /* ========================================================================================================================================= */
    
    t=t+delta_t;

    write_data_file(data_file);
    //printf("unknowns \n"); Vect_Print  (n_unknowns, unknowns);
    //printf("dq \n"); Vect_Print    (n_gen_coord, dq);
    //printf("q \n"); Vect_Print    (n_gen_coord, q);
    //printf("qaux \n"); Vect_Print    (n_gen_auxcoord, qaux);     
    
    gettimeofday(&integration2, NULL);

    printf("Integration  TOTAL=  %lu\n", (integration2.tv_usec-integration1.tv_usec ));
    printf("M Delta dPhic_dq Gammac=  %lu\n", (functions1stop.tv_usec-functions1start.tv_usec ));
    printf("dPhit_ds() Phit() dPhic_dq() Phic() Betac() =  %lu\n", (functions2stop.tv_usec-functions2start.tv_usec ));
    printf("Splines  =  %lu\n", (splinesstop.tv_usec-splinesstart.tv_usec ));    
    printf("Integration =  %lu\n", (Intstop.tv_usec-Intstart.tv_usec )); 
    printf("Kalker=  %lu\n", (Kalkerstop1.tv_usec-Kalkerstart1.tv_usec) ); 
    printf("Dynamics=  %lu\n", (Dynstop.tv_usec-Dynstart.tv_usec ));
    printf("Projection=  %lu\n", (Projstop.tv_usec-Projstart.tv_usec ));    
    printf("*********************************************************************************************\n"); 
}
printf("q \n"); Vect_Print    (n_gen_coord, q);
/* ********************************************************************************************* */

/* ********************************************************************************************* */
/* ********************************************************************************************* */
//#include "Done_variables_parameters.c"
//#include "Done_functions.c"

return 0;
}




