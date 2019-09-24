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
#include "Q.h"
#include "M.h"
#include "MQ.h"
#include "Output.h"

#include "Gammac.h"
//#include "Gammat.h"
#include "Betac.h"
//#include "Betat.h"
#include "Phic.h"
#include "Phit.h"
#include "dPhic_dq.h"
#include "dPhit_ds.h"


//~ #include "Declare_Variables_Train.h"
/* ********************************************************************************************* */
#include "write_data_file.h"
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
  
  #include "CKL.h"
  #include "CKR.h"
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
//Init_Beta (  ) ;
//Init_Phi_q (  );
//Init_dPhi_dq (  );
Init_Q (  );
Init_M (  );
Init_MQ (  );
//Init_Gamma (  );
Init_Output (  );

Init_Gammac (  );
//Init_Gammat (  );
Init_Betac (  ) ;
//Init_Betat (  ) ;
Init_Phic (  );
Init_Phit (  );
Init_dPhic_dq (  );
Init_dPhit_ds (  );

Init_Table_Kalker ( );
Init_Table_Kalker ( );

Init_CKL ( );
Init_CKR ( );


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
double	correction_dq[dPhiInit_dq_n_cols];
double AUX_V_Init[PhiInit_q_n_rows];
double BufferL[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
double BufferU[2*dPhiInit_dq_n_rows*dPhiInit_dq_n_rows];
int p_vector[dPhic_dq_n_rows], q_vector[dPhic_dq_n_cols],  perm_vel[dPhic_dq_n_cols];
double	deltaqs[PhiInit_q_n_cols];

double qs[n_gen_coord + n_gen_auxcoord];
double dqs[n_gen_vel + n_gen_auxvel];
//Vect_Print  (n_gen_coord, q);
for (i = 0; i < n_gen_coord; i++){qs[i]=q[i];}
for (i = 0; i < n_gen_auxcoord; i++){qs[n_gen_coord + i]=qaux[i];}



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



//~ Vect_Print  (n_gen_coord, q);
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



//~ dq[0]=0.648644;
//~ dq[2]=1.29572;
param[10]= 10.0;
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
#define n_unk_c dPhic_dq_n_rows
double unks_c[n_unk_c];



Mat_Inv(M_n_cols ,_M, _INV_M_aux,Buffer);
Mat_Vect_Mult(M_n_rows, M_n_cols,_INV_M_aux ,_Delta, +1, aux_ddq1 );
Mat_Trasp(dPhic_dq_n_rows, dPhic_dq_n_cols, _dPhic_dq, Trasp_dPhic_dq); 
Mat_Mat_Mult(M_n_rows, M_n_cols, dPhic_dq_n_rows, _INV_M_aux , Trasp_dPhic_dq, +1, aux_dPhic_dq_T );
Mat_Vect_Mult(dPhic_dq_n_rows, dPhic_dq_n_cols, _dPhic_dq , aux_ddq1, +1, bb);
for (i=0; i<n_unk_c; i++){ bb[i]=bb[i]-_Gammac[i]; } 
Mat_Mat_Mult(dPhic_dq_n_rows, dPhic_dq_n_cols, dPhic_dq_n_rows, _dPhic_dq , aux_dPhic_dq_T, +1, AA);
Mat_Inv(dPhic_dq_n_rows, AA, INV_AA,Buffer);
Mat_Vect_Mult(n_unk_c, n_unk_c, INV_AA , bb, +1, unks_c); 
Mat_Vect_Mult(dPhic_dq_n_cols, dPhic_dq_n_rows, aux_dPhic_dq_T, unks_c, +1, aux_ddq2);


for (i=0; i<n_gen_accel; i++){ ddq[i]=aux_ddq1[i]-aux_ddq2[i]; } 
for (i=0; i<n_unk_c; i++){ unknowns[i]=unks_c[i]; }


/* ********************************************************************************************* */
/* Calculate KALKER's coeffs                                                                     */
/* ********************************************************************************************* */
Output();
Table_Hertz();
Table_Kalker();
Vect_Print  (n_gen_coord, q);
#include "kalker_coeffs_calculation.c"


// check kalker coeffs !!!!!!!!!!!!!


Vect_Print  (n_gen_coord, q);


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

double v_crit = 0.0001;
double velR = MAX (_Output[5],v_crit);
double velL = MAX (_Output[15],v_crit);
    
//Dynamics    
double b[dPhic_dq_n_rows];
double yddq[n_vel_dep];
double AUX_M_indep_indep_1[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)],AUX_M_indep_indep_2[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)];
//double AUX_M_indep_dep_1[MAX(n_vel_indep,n_vel_indep)*MAX(Phi_n_rows,n_vel_dep)] , AUX_M_indep_dep_2[MAX(n_vel_indep,n_vel_indep)*MAX(Phic_n_rows,dPhic_dq_n_rows)];
double AUX_M_indep_dep_1[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_dep,n_vel_dep)] , AUX_M_indep_dep_2[MAX(n_vel_indep,n_vel_indep)*MAX(Phic_n_rows,dPhic_dq_n_rows)];
double _MZ[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)];
double _QZ[MAX(n_vel_indep,n_vel_indep)];
double AUX_V_indep_1[MAX(n_vel_indep,n_vel_indep)],AUX_V_indep_2[MAX(n_vel_indep,n_vel_indep)];

// Kalker
double _CK[n_gen_coord*n_gen_coord];
int CK_n_rows = n_gen_coord;
double AUX_CK_indep_indep_1[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)],AUX_CK_indep_indep_2[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)],AUX_CK_indep_indep_3[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)];
double AUX_CK_indep_dep_1[MAX(n_vel_indep,n_vel_indep)*MAX(Phic_n_rows,n_vel_dep)] , AUX_CK_indep_dep_2[MAX(n_vel_indep,n_vel_indep)*MAX(Phic_n_rows,dPhic_dq_n_rows)];
double _CKZ[MAX(n_vel_indep,n_vel_indep)*MAX(n_vel_indep,n_vel_indep)];


// Z partition
double _Midz[n_vel_indep];
double Mzaux1[n_vel_indep*n_vel_indep];
double Mzaux2[n_vel_indep];


double dz[n_vel_indep];
double dd[n_vel_dep];
double dz_k[n_vel_indep];
double dd_k[n_vel_dep];
double dq_k[n_gen_coord];
double dq_k1[n_gen_coord];
double aux_dq[n_gen_coord];

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
for (i = 0; i < dPhit_ds_n_cols; i++){perm_s[i]=i;}
for (i = 0; i < dPhit_ds_n_rows; i++){p_vecs[i]=i;}




for (k_iter=1; k_iter<=steps; k_iter++){
    Output();
    #include "kalker_coeffs_calculation.c"
    #include "splines_rail_pos.c" // Posiblemente sea mejor antes de la correccion
    
    
    velR = MAX (_Output[5],v_crit);
    velL = MAX (_Output[15],v_crit);
    
    Delta();
    M();
    Gammac();    
    dPhic_dq();


    /*for coordinate partitioning*/
    lufp4(dPhic_dq_n_rows,dPhic_dq_n_rows, dPhic_dq_n_cols, _dPhic_dq, p_vector, perm_vel);
    //Vect_Print_Int  (dPhic_dq_n_cols, perm_vel);
    /* Calculate A with this dedicated backward */
    for (i = 0; i< n_vel_indep ; i++){
        backward_substitution_LUpq_pq_A(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel, &_dPhic_dq[perm_vel[i+n_vel_dep] * dPhic_dq_n_rows ], &A[ i * dPhic_dq_n_rows ]); /* Calculate A with this dedicated backward */
    }
    

    /*Calculate b*/
    forward_substitution_LUpq_pq_x(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel , _Gammac, yddq);
    backward_substitution_LUpq_pq_x(dPhic_dq_n_rows,dPhic_dq_n_rows, _dPhic_dq, p_vector, perm_vel , yddq, b);


    /*Mzd*A*/
    i_ini=n_vel_dep;
    j_ini=0;
    for (i=0; i<n_vel_indep; i++){
	    for (j=0; j< n_vel_indep; j++){
		    AUX_M_indep_indep_1[i+j*n_vel_indep] = 0.0;
		    for	(k=0; k<dPhic_dq_n_rows; k++){
			    AUX_M_indep_indep_1[i+j*n_vel_indep] =  _M[PERM(i,k,i_ini, j_ini,M_n_rows, perm_vel)] * A[k+j*dPhic_dq_n_rows] + AUX_M_indep_indep_1[i+j*n_vel_indep];
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
  				AUX_M_indep_dep_1[i+j*n_vel_indep] =   A[k+i*dPhic_dq_n_rows] * _M[PERM(k,j,i_ini, j_ini,M_n_rows, perm_vel)]  + AUX_M_indep_dep_1[i+j*n_vel_indep];
			}
		}
	}    
    
	/*(A'*Mdd)*A=AUX_M_indep_indep_2*/
	Mat_Mat_Mult(n_vel_indep, dPhic_dq_n_rows, n_vel_indep, AUX_M_indep_dep_1, A, +1, AUX_M_indep_indep_2);

	/*Mzz =  Mzz + Mzd*A +(Mzd*A )' + (A'*Mdd)*A*/
	i_ini=n_vel_dep;
	j_ini=n_vel_dep;
		for (i = 0; i < n_vel_indep; i++){
			for(j = 0; j < n_vel_indep; j++){	
			_MZ[i + j * n_vel_indep]= _M[PERM(i,j,i_ini, j_ini, M_n_rows, perm_vel)] + AUX_M_indep_indep_1[j + i * n_vel_indep] + AUX_M_indep_indep_1[i + j * n_vel_indep] + AUX_M_indep_indep_2[i + j * n_vel_indep]; 
		}
	}
    //Mat_Print     (n_vel_indep, n_vel_indep, _MZ);

    /*AUX_V_indep_1=A'* Qd*/
    for (i=0; i<n_vel_indep; i++){
	    AUX_V_indep_1[i] = 0.0;
	    for (j=0; j<dPhic_dq_n_rows; j++){
		    AUX_V_indep_1[i] = A[j+i*dPhic_dq_n_rows] * _Delta[perm_vel[j]] + AUX_V_indep_1[i];
        }
	}
    /*Mzd+(A'*Mdd)*/
    i_ini=n_vel_dep;
    j_ini=0; 
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < dPhic_dq_n_rows; j++){
		AUX_M_indep_dep_2[i + j * n_vel_indep] = _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] + AUX_M_indep_dep_1[i + j * n_vel_indep];
		}
	}
    /* (Mzd+(A'*Mdd) )* b */   
    Mat_Vect_Mult(n_vel_indep, dPhic_dq_n_rows, AUX_M_indep_dep_2, b, +1, AUX_V_indep_2);	
    
    /*_QZ = Qz + A'* Qd - (Mzd+(A'*Mdd))*b*/
	for (i = 0; i < n_vel_indep; i++){
		_QZ[i] = _Delta[perm_vel[i+n_vel_dep]] + AUX_V_indep_1[i] - AUX_V_indep_2[i];
	}   
    //Mat_Print     (n_vel_indep, 1, _QZ);
    
    
    CKR ();
    CKL ();   
    for (i = 0; i < (n_gen_coord * n_gen_coord); i++){
       _CK[i] = _CKR[i]/velR + _CKL[i]/velL;       
    }
    //~ Mat_Print     (n_gen_coord, n_gen_coord, _CK);

    
    /*CKzd*A*/
    i_ini=n_vel_dep;
    j_ini=0;
    for (i=0; i<n_vel_indep; i++){
	    for (j=0; j< n_vel_indep; j++){
		    AUX_CK_indep_indep_1[i+j*n_vel_indep] = 0.0;
		    for	(k=0; k<dPhic_dq_n_rows; k++){
			    AUX_CK_indep_indep_1[i+j*n_vel_indep] =  _CK[PERM(i,k,i_ini, j_ini,CK_n_rows, perm_vel)] * A[k+j*dPhic_dq_n_rows] + AUX_CK_indep_indep_1[i+j*n_vel_indep];
			}
		}
	}
    /*A'*CKdz*/
    i_ini=0;
    j_ini=n_vel_dep;
    for (j=0; j< n_vel_indep; j++){
       for (i=0; i<n_vel_indep; i++){         
		    AUX_CK_indep_indep_3[i+j*n_vel_indep] = 0.0;
		    for	(k=0; k<dPhic_dq_n_rows; k++){
  			    AUX_CK_indep_indep_3[j+i*n_vel_indep] =   _CK[PERM(k,i,i_ini, j_ini,CK_n_rows, perm_vel)] * A[k+j*dPhic_dq_n_rows]  + AUX_CK_indep_indep_3[j+i*n_vel_indep];
    		}
		}
	}  
    /*A'*CKdd*/
    i_ini=0;
    j_ini=0;
    for (i=0; i<n_vel_indep; i++){
	    for (j=0; j< dPhic_dq_n_rows; j++){
		    AUX_CK_indep_dep_1[i+j*n_vel_indep] = 0.0;
		    for	(k=0; k<dPhic_dq_n_rows; k++){
  			    AUX_CK_indep_dep_1[i+j*n_vel_indep] =   A[k+i*dPhic_dq_n_rows] * _CK[PERM(k,j,i_ini, j_ini,CK_n_rows, perm_vel)]  + AUX_CK_indep_dep_1[i+j*n_vel_indep];
			}
		}
	}
    /*(A'*CKdd)*A=AUX_M_indep_indep_2*/
    Mat_Mat_Mult(n_vel_indep, dPhic_dq_n_rows, n_vel_indep, AUX_CK_indep_dep_1, A, +1, AUX_CK_indep_indep_2);

    /*CKZ =   - (CKzz + CKzd*A +(CKzd*A )' + (A'*CKdd)*A)*/
    i_ini=n_vel_dep;
    j_ini=n_vel_dep;
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < n_vel_indep; j++){	
		    _CKZ[i + j * n_vel_indep]= +(_CK[PERM(i,j,i_ini, j_ini, CK_n_rows, perm_vel)] + AUX_CK_indep_indep_3[i + j * n_vel_indep] + AUX_CK_indep_indep_1[i + j * n_vel_indep] + AUX_CK_indep_indep_2[i + j * n_vel_indep]); 
		}
	}

    //Mat_Print     (n_vel_indep, n_vel_indep, _CKZ);
    //~ /*CKzd+(A'*CKdd)*/
    //~ i_ini=n_vel_dep;
    //~ j_ini=0; 
	//~ for (i = 0; i < n_vel_indep; i++){
		//~ for(j = 0; j < dPhic_dq_n_rows; j++){
		//~ AUX_CK_indep_dep_2[i + j * n_vel_indep] = _CK[PERM(i,j,i_ini, j_ini,CK_n_rows, perm_vel)] + AUX_CK_indep_dep_1[i + j * n_vel_indep];
		//~ }
	//~ }
    //~ /* (Mzd+(A'*Mdd) )* b = Zero*/   
    //~ Mat_Vect_Mult(n_vel_indep, dPhic_dq_n_rows, AUX_CK_indep_dep_2, bv, +1, _H);
    
    

    for (i = 0; i < n_gen_coord; i++){ dq_k[i] = dq[perm_vel[i]]; }
    //for (i = 0; i < n_vel_dep; i++){ dd_k[i] = dq_k[i];}
    for (i = 0; i < n_vel_indep; i++){dz_k[i] = dq_k[n_vel_dep+i];}     
   

    Mat_Vect_Mult (n_vel_indep, n_vel_indep ,_MZ , dz_k, +1 ,_Midz);
    
 	for (i = 0; i < n_vel_indep*n_vel_indep; i++){
        Mzaux1[i] = _MZ[i] - _CKZ[i]*delta_t;
        //Mzaux1[i] = _MZ[i] + _CKZ[i]*delta_t;    
    }
       
  	for (i = 0; i < n_vel_indep; i++){
        Mzaux2[i] = _Midz[i] + _QZ[i]*delta_t;    
    } 
    /* Solve Mzaux1 * ddz = Mzaux2 */

    solve_lin_sys_ldl(n_vel_indep,Mzaux1 , Mzaux2, dz, AUX_M_indep_indep_1, AUX_M_indep_indep_2 , AUX_V_indep_1 , AUX_V_indep_2);
    Mat_Vect_Mult (n_vel_dep, n_vel_indep,A , dz, +1 ,dd);//+bv => zero
    
    
   
    for (i = 0; i < n_vel_dep; i++){dq_k1[i]=dd[i];}
    for (i = 0; i < n_vel_indep; i++){dq_k1[i+n_vel_dep] = dz[i];}

    //Vect_Print    (n_gen_coord, aux_dq);
    //Vect_Print    (n_gen_coord, dq_k);
    //Vect_Print    (n_gen_coord, dq);
    
    
    /* ========================================================================================================================================= */
    /* Calculate unknowns */
    /* Phi_d_T * lambda = Qd - Mdd * ddd - Mdz * ddz */
    /* ========================================================================================================================================= */
    //double ddq[n_gen_coord];

    for (i = 0; i < n_gen_coord; i++){
       ddq[i] = (dq_k1[i]-dq_k[i])/delta_t;
    } 
    //Vect_Print    (n_gen_coord, ddq);
    
    /* Mdd · ddd */
    i_ini=0;
    j_ini=0;
    for (i=0; i<n_vel_dep; i++){
	    AUX_L_dep[i] = 0.0;
	    for (j=0; j<n_vel_dep; j++){
		    AUX_L_dep[i] = AUX_L_dep[i] + _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * ddq[j];
		}
	}
    /* Mdz · ddz */
    i_ini=0;
    j_ini=n_vel_dep;
    for (i=0; i<n_vel_dep; i++){
	    AUX_L_indep[i] = 0.0;
	    for (j=0; j<n_vel_indep; j++){
		    AUX_L_indep[i] = AUX_L_indep[i] + _M[PERM(i,j,i_ini, j_ini,M_n_rows, perm_vel)] * ddq[j+n_vel_dep] ;            
		}
	}

    /* Qd  + _CKZ*dq - Mdd * ddd - Mdz * ddz ???????????????*/
    //~ Mat_Vect_Mult (n_gen_coord, n_gen_coord,A , dz, +1 ,dd);
    for (i = 0; i < n_vel_dep; i++){
	    b_aux[i] = _Delta[perm_vel[i]] - AUX_L_dep[i] - AUX_L_indep[i];
    }
    /* dPhic_dq *lambda_c =  Deltad - Mdd * ddd - Mdz * ddz */
    forward_substitution_LUpq_T_pq_q (n_vel_dep,n_vel_dep, _dPhic_dq, p_vector, perm_vel, b_aux, yL);
    backward_substitution_LUpq_T_pq_q(n_vel_dep,n_vel_dep, _dPhic_dq, p_vector, perm_vel, yL, lambda_c); 
    //Vect_Print    (n_vel_dep, lambda_c);
    //for(i = 0; i < n_vel_dep; i++){unknowns[i] =lambda_c[i];}
    for(i = 0; i < n_vel_dep; i++){unknowns[perm_vel[i]] =lambda_c[i];}
    

    /* ========================================================================================================================================= */
    /* Integration
    /* ========================================================================================================================================= */
      //double q_k1[n_gen_coord];

      //~ Vect_Print    (n_gen_coord, dq);
      //for (i = 0; i < n_gen_coord; i++){dq[i] = dq_k1[perm_vel[i]] ;}
      for (i = 0; i < n_gen_coord; i++){dq[perm_vel[i]] = dq_k1[i] ;}
      //~ Vect_Print    (n_gen_coord, dq);
      //~ Vect_Print    (n_gen_coord, q);
      for(i = 0; i < n_gen_coord; i++){q[i] = q[i] + dq[i] * delta_t;}

      
    /* ========================================================================================================================================= */
    /* Projection
    /* ========================================================================================================================================= */
    dPhit_ds();
    Phit();
    dPhic_dq();
    Phic();    
    Betac();

 
 
    lufp4(dPhit_ds_n_rows,dPhit_ds_n_rows, dPhit_ds_n_cols, _dPhit_ds, p_vecs, perm_s);

    for (i = 0; i < iterations_NR ; i++){
        Phit();
        forward_substitution_LUpq_pq_x (dPhit_ds_n_rows,dPhit_ds_n_rows, _dPhit_ds, p_vecs, perm_s, _Phit, ys);
        backward_substitution_LUpq_pq_x(dPhit_ds_n_rows,dPhit_ds_n_rows, _dPhit_ds, p_vecs, perm_s, ys, delta_s);
        for (j = 0; j < n_gen_auxcoord; j++){    
            //qaux[j] = qaux[j] - delta_s[perm_s[j]];
            qaux[perm_s[j]] = qaux[perm_s[j]] - delta_s[j];
        }	
    }
    

    
    //dPhic_dq();
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

    /* ========================================================================================================================================= */
    
    t=t+delta_t;
    write_data_file(data_file);
    
}

Vect_Print  (n_gen_coord, q);

/* ********************************************************************************************* */
#ifdef TIME_ON
  //~ printf("%s One step calculation time: %.9f secs\n",output_file_name,(end - start) / ((double) n_iterations));
#endif
#ifndef TIME_ON
  //~ printf("The created file name is: %s\n",output_file_name);
#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
#include "Done_variables_parameters.c"
//#include "Done_functions.c"
Done_PhiInit (  );
Done_PhiInit_q (  );
Done_BetaInit (  ) ;
Done_dPhiInit_dq (  );


Done_Phi (  );
Done_Q (  );
Done_M (  );
Done_MQ (  );

return 0;
}




