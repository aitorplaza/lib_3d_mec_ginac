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
#include "Gammat.h"
#include "Betac.h"
#include "Betat.h"
#include "Phic.h"
#include "Phit.h"
#include "dPhic_dq.h"
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
Init_Beta (  ) ;
Init_Phi_q (  );
Init_dPhi_dq (  );
Init_Q (  );
Init_M (  );
Init_MQ (  );
Init_Gamma (  );
Init_Output (  );

Init_Gammac (  );
Init_Gammat (  );
Init_Betac (  ) ;
Init_Betat (  ) ;
Init_Phic (  );
Init_Phit (  );
Init_dPhic_dq (  );
Init_dPhit_ds (  );

Init_Table_Kalker ( );
Init_Table_Kalker ( );

Init_CKL ( );
Init_CKR ( );


#define MAX(a,b) (((a)>(b))?(a):(b))
#define PERM(fi, cj, fi_ini, cj_ini, stride) ((fi+fi_ini)+(cj+cj_ini)*stride)


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




BetaInit();
dPhiInit_dq();

Mat_PInv  (dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, BufferPINV);
//Mat_PInvLU(dPhiInit_dq_n_rows, dPhiInit_dq_n_cols, _dPhiInit_dq, _Inv_dPhiInit_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, p_vector, q_vector, BufferL, BufferU);

Mat_Vect_Mult(dPhiInit_dq_n_cols, dPhiInit_dq_n_rows, _Inv_dPhiInit_dq, AUX_V_Init, 1, correction_dq);

for (i = 0; i < dPhiInit_dq_n_cols; i++){ dqs[i] = dqs[i] + correction_dq[i];	}

for (i = 0; i < dPhic_dq_n_cols; i++){perm_vel[i]=i;}
for (i = 0; i < dPhic_dq_n_rows; i++){p_vector[i]=i;}



dq[0]=0.648644;
dq[2]=1.29572;
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




#define Kalker_Init 31 
#define E_elastic Kalker_Init + 0
#define nu_poisson Kalker_Init + 1
#define G_elastic Kalker_Init + 2

#define output_N_R 0
#define output_R1x_R output_N_R + 6
#define output_Vx_R output_N_R + 1
#define Hertz_aR 34
#define C11R 38




hertz_ellipse (param, Hertz_aR, E_elastic, _Output, output_R1x_R, output_N_R ,_Table_Hertz, Table_Hertz_n_rows);
kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11R, Hertz_aR, nu_poisson );
//~ printf ("aR = %f\n",param [ Hertz_aR + 0 ] );
//~ printf ("bR = %f\n",param [ Hertz_aR + 1 ] );
//~ printf ("C11 = %f\n",param [C11R + 0 ] );
//~ printf ("C22 = %f\n",param [C11R + 1 ] );
//~ printf ("C23 = %f\n",param [C11R+ 2 ] );
//~ printf ("C33 = %f\n",param [C11R + 3 ] );


#define output_N_L 10
#define output_R1x_L output_N_L + 6
#define output_Vx_L output_N_L + 1
#define Hertz_aL 36
#define C11L 42

hertz_ellipse (param, Hertz_aL, E_elastic, _Output, output_R1x_L, output_N_L ,_Table_Hertz, Table_Hertz_n_rows);
kalker_coeffs ( _Table_Kalker ,Table_Kalker_n_rows, param, C11L, Hertz_aL, nu_poisson );

// check kalker coeffs !!!!!!!!!!!!!






/* ********************************************************************************************* */
/* IWrite to file.                                                                               */
/* ********************************************************************************************* */

FILE * data_file = fopen(output_file_name, "w");
write_data_file_header(data_file);
write_data_file(data_file);

/* ********************************************************************************************* */
/* Integration                                                          */
/* ********************************************************************************************* */


long int k_iter;
int i_ini,j_ini;

int n_vel_indep = 4;
int n_vel_dep = 2;

double _Mzz [n_vel_indep*n_vel_indep];
double _Mzd [n_vel_indep*n_vel_dep];
double _Mdd [n_vel_dep*n_vel_dep];

double _dPhic_dz[dPhic_dq_n_rows * n_vel_indep];
double _dPhic_dd[dPhic_dq_n_rows * n_vel_dep];

double bv[n_vel_dep]; //zero
double baAux[(n_vel_indep+ n_vel_dep)*dPhic_dq_n_rows];
double ba[n_vel_dep];

double _Inv_dPhic_dq[dPhic_dq_n_rows * dPhic_dq_n_cols];  
double _Inv_dPhic_dd[dPhic_dq_n_rows * n_vel_dep];
double A[n_vel_dep*n_vel_indep];
double AT[n_vel_dep*n_vel_indep];

double _Mind [n_vel_indep*n_vel_indep];
double _MzdA[n_vel_indep*n_vel_indep];
double _MzdAT[n_vel_indep*n_vel_indep];
//double _MddA[n_vel_dep*n_vel_indep];
double _ATMdd[n_vel_dep*n_vel_indep];

double _ATMddA[n_vel_indep*n_vel_indep];
double _DAux[n_vel_indep*n_vel_dep];
double _D[n_vel_indep];

double _Qz[n_vel_indep];
double _Qd[n_vel_dep];
double ATQd[n_vel_indep];
double _F[n_vel_indep];

double _CK[n_gen_coord*n_gen_coord];
int CK_n_rows = n_gen_coord;
double _CKzz[n_vel_indep*n_vel_indep];
double _CKzd[n_vel_indep*n_vel_dep];
double _CKdz[n_vel_indep*n_vel_dep];
double _CKdd[n_vel_dep*n_vel_dep];


double _ATCKdd[n_vel_indep*n_vel_dep];
double _CKaux1[n_vel_indep*n_vel_dep];
double _CKaux2[n_vel_indep*n_vel_dep];
double _H[n_vel_indep];
double _ATCKdz[n_vel_indep*n_vel_indep];
double _Gaux[n_vel_indep*n_vel_indep];
double _G[n_vel_indep*n_vel_indep];

double _Midz[n_vel_indep];
double Mzaux1[n_vel_indep*n_vel_indep];
double InvMzaux1[n_vel_indep*n_vel_indep];
double Mzaux2[n_vel_indep];
double dz[n_vel_indep];
double dd[n_vel_dep];


for (k_iter=1; k_iter<=steps; k_iter++){

    double v_crit = 0.0001;
    double velR = MAX (_Output[5],v_crit);
    double velL = MAX (_Output[15],v_crit);
    
    Delta();
    M();
    Gammat();
    Gammac();    
    dPhic_dq();
    CKR ();
    CKL ();
    
    lufp4(dPhic_dq_n_rows,dPhic_dq_n_rows, dPhic_dq_n_cols, _dPhic_dq, p_vector, perm_vel);
    
    Vect_Print_Int  (dPhic_dq_n_cols, perm_vel);
    Vect_Print_Int  (dPhic_dq_n_rows, p_vector);

    i_ini=0;
    j_ini=0;
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < n_vel_indep; j++){
            _Mzz[i + j * n_vel_indep] = _M[PERM(i,j,i_ini, j_ini, M_n_rows)];
        }
    }

    i_ini=0;
    j_ini=n_vel_indep;
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < n_vel_dep; j++){
            _Mzd[i + j * n_vel_indep] = _M[PERM(i,j,i_ini, j_ini, M_n_rows)];
        }
    }    

    i_ini=n_vel_indep;
    j_ini=n_vel_indep;
	for (i = 0; i < n_vel_dep; i++){
		for(j = 0; j < n_vel_dep; j++){
            _Mdd[i + j * n_vel_dep] = _M[PERM(i,j,i_ini, j_ini, M_n_rows)];
        }
    } 
    
    
    i_ini=0;
    j_ini=0;
	for (i = 0; i < dPhic_dq_n_rows; i++){
		for(j = 0; j < n_vel_indep; j++){
            _dPhic_dz[i + j * dPhic_dq_n_rows] = _dPhic_dq[PERM(i,j,i_ini, j_ini, dPhic_dq_n_rows)];
        }
    }       

    i_ini=0;
    j_ini=n_vel_indep;
	for (i = 0; i < dPhic_dq_n_rows; i++){
		for(j = 0; j < n_vel_dep; j++){
            _dPhic_dd[i + j * dPhic_dq_n_rows] = _dPhic_dq[PERM(i,j,i_ini, j_ini, dPhic_dq_n_rows)];
        }
    }

   

    Mat_PInv(dPhic_dq_n_rows, n_vel_dep, _dPhic_dd, _Inv_dPhic_dd, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, BufferPINV);
    Mat_Mat_Mult(dPhic_dq_n_rows, n_vel_dep,n_vel_indep , _Inv_dPhic_dd , _dPhic_dz, -1, A );
    
    Mat_PInv(dPhic_dq_n_rows,dPhic_dq_n_cols , _dPhic_dq, _Inv_dPhic_dq, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, BufferPINV);
    Mat_Mat_Mult(n_vel_dep, dPhic_dq_n_rows, n_vel_indep +n_vel_dep , _Inv_dPhic_dd , _dPhic_dq, +1, baAux );
    Mat_Vect_Mult (dPhic_dq_n_rows, n_vel_indep +n_vel_dep ,baAux , q, -1 ,ba);
    
    //_Mind = Mzz + Mzd*A + (Mzd*A)'+ A'*Mdd*A;
    Mat_Mat_Mult(n_vel_indep,n_vel_dep , n_vel_indep , _Mzd , A, +1, _MzdA );
    Mat_Trasp(n_vel_indep,n_vel_indep, _MzdA, _MzdAT);
    
    Mat_Trasp(n_vel_dep,n_vel_indep, A, AT);
    //Mat_Mat_Mult(n_vel_dep,n_vel_dep , n_vel_indep , _Mdd , A, +1, _MddA );
    //Mat_Mat_Mult(n_vel_indep,n_vel_dep , n_vel_indep , AT, _MddA ,  +1, _ATMddA );
    Mat_Mat_Mult(n_vel_indep,n_vel_dep , n_vel_dep , AT, _Mdd ,  +1, _ATMdd );
    Mat_Mat_Mult(n_vel_indep,n_vel_dep , n_vel_indep ,_ATMdd , A ,  +1, _ATMddA );
    
    //~ Mat_Mat_TMult(n_vel_dep, n_vel_indep ,n_vel_indep , A, _MddA, +1,_ATMddA );

	for (i = 0; i < n_vel_indep*n_vel_indep; i++){
        _Mind [i] = _Mzz[i] +_MzdA[i]  + _MzdAT[i] +_ATMddA[i] ;    
    }
    
	for (i = 0; i < n_vel_dep*n_vel_indep; i++){
        _DAux [i] = _Mzd[i]  + _ATMdd[i] ;    
    }    
    Mat_Vect_Mult (n_vel_indep,n_vel_dep ,_DAux , ba, -1 ,_D);

    
    for (i = 0; i < n_vel_indep; i++){
       _Qz[i] = _Delta[i];
    }
	for (i = 0; i < n_vel_dep; i++){
       _Qd[i] = _Delta[n_vel_indep+ i];
    }

    Mat_Vect_Mult (n_vel_indep,n_vel_dep ,AT , _Qd, +1 ,ATQd);

	for (i = 0; i < n_vel_indep; i++){
       _F[i] = _Qz[i] + ATQd[i] + _D[i] ;
    }

	for (i = 0; i < n_vel_indep; i++){
       _F[i] = _Qz[i] + ATQd[i] + _D[i] ;
    }
    
	for (i = 0; i < (n_gen_coord * n_gen_coord); i++){
       _CK[i] = _CKR[i]/velR + _CKL[i]/velL;       
    }    



    i_ini=0;
    j_ini=0;
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < n_vel_indep; j++){
            _CKzz[i + j * n_vel_indep] = _CK[PERM(i,j,i_ini, j_ini, CK_n_rows)];
        }
    }

    i_ini=0;
    j_ini=n_vel_indep;
	for (i = 0; i < n_vel_indep; i++){
		for(j = 0; j < n_vel_dep; j++){
            _CKzd[i + j * n_vel_indep] = _CK[PERM(i,j,i_ini, j_ini, CK_n_rows)];
        }
    }
    
    i_ini=n_vel_indep;
    j_ini=0;
	for (i = 0; i < n_vel_dep; i++){
		for(j = 0; j < n_vel_indep; j++){
            _CKdz[i + j * n_vel_dep] = _CK[PERM(i,j,i_ini, j_ini, CK_n_rows)];
        }
    }        

    i_ini=n_vel_indep;
    j_ini=n_vel_indep;
	for (i = 0; i < n_vel_dep; i++){
		for(j = 0; j < n_vel_dep; j++){
            _CKdd[i + j * n_vel_dep] = _CK[PERM(i,j,i_ini, j_ini, CK_n_rows)];
        }
    } 




    Mat_Mat_Mult(n_vel_indep,n_vel_dep , n_vel_dep , AT, _CKdd ,  +1, _ATCKdd );
    for (i = 0; i < (n_vel_indep*n_vel_dep); i++){
       _CKaux1[i] = _CKdz[i]+ _ATCKdd[i];       
    } 
    //~ Mat_Vect_Mult (n_vel_indep, n_vel_dep ,_CKaux1 , bv, -1 ,_CKaux2); //Zero => bv = [0,0]'
    Mat_Mat_Mult(n_vel_indep,n_vel_dep , n_vel_indep , _CKaux1 , A, +1, _Gaux );

    for (i = 0; i < (n_vel_indep); i++){
       _H[i] = _F[i] ;//+ _CKaux2[i][i];       
    }
    

    Mat_Mat_Mult(n_vel_indep,n_vel_dep, n_vel_indep , AT, _CKdz ,  +1, _ATCKdz );
    

	for (i = 0; i < n_vel_indep*n_vel_indep; i++){
        _G[i] = -(_CKzz[i] +_ATCKdz[i] + _Gaux[i]) ;    
    }

    double dz_k[n_vel_indep];
    double dd_k[n_vel_dep];
    
    for (i = 0; i < (n_vel_indep); i++){
       dz_k[i] = dq[i] ;
    } 
    for (i = 0; i < (n_vel_dep); i++){
       dd_k[i] = dq[n_vel_indep+i] ;
    }     
    
    

    Mat_Vect_Mult (n_vel_indep, n_vel_indep ,_Mind , dz_k, +1 ,_Midz);
    
 	for (i = 0; i < n_vel_indep*n_vel_indep; i++){
        Mzaux1[i] = _Mind[i] - _G[i]*delta_t;    
    }
       
  	for (i = 0; i < n_vel_indep; i++){
        Mzaux2[i] = _Midz[i] + _H[i]*delta_t;    
    } 
    
     
  
    Mat_PInv(n_vel_indep, n_vel_indep, Mzaux1, InvMzaux1, BufferJT, BufferAUXCols, BufferAUXRows, BufferIAUXCols, BufferIAUXRows, BufferPINV);
    //Mat_Mat_Mult(n_vel_indep, n_vel_indep,n_vel_indep , InvMzaux1 ,Mzaux2, +1, dz );
    Mat_Vect_Mult(n_vel_indep, n_vel_indep,InvMzaux1 ,Mzaux2, +1, dz );
    Mat_Vect_Mult (n_vel_dep, n_vel_indep,A , dz, +1 ,dd);//+bv => zero
    //~ Mat_Print(n_vel_indep,1,dz);
    //~ Mat_Print(n_vel_dep,1,dd);
    
    double ddz[n_vel_indep];
    double ddd[n_vel_dep];
    double _Mdz[n_vel_dep*n_vel_indep]; 
    double Dddaux[n_vel_dep];    
    double Ddzaux[n_vel_dep];
    double Daux[n_vel_dep];
    double lambda_c[dPhic_dq_n_rows];    
             
    for (i = 0; i < (n_vel_indep); i++){
       ddz[i] = (dz[i]-dz_k[i])/delta_t;
    } 
    for (i = 0; i < (n_vel_dep); i++){
       ddd[i] = (dd[i]-dd_k[i])/delta_t;
    }
    
    Mat_Vect_Mult (n_vel_dep, n_vel_dep,_Mdd , ddd, +1 ,Dddaux);
    Mat_Trasp(n_vel_indep,n_vel_dep, _Mzd, _Mdz);  
    Mat_Vect_Mult (n_vel_dep, n_vel_indep,_Mdz , ddz, +1 ,Ddzaux);
    /* Qd - Mdd * ddd - Mdz * ddz */
    for (i = 0; i < n_vel_dep; i++){
        Daux[i]= _Qd[i] - Dddaux[i]- Ddzaux[i];
    }

    Mat_Print(dPhic_dq_n_rows,dPhic_dq_n_cols,_dPhic_dq); 
    Mat_Print(dPhic_dq_n_rows,n_vel_dep,_dPhic_dd);
      
    Mat_Vect_Mult (n_vel_dep, dPhic_dq_n_rows,_Inv_dPhic_dd ,Daux, +1 ,lambda_c);

    Vect_Print	(n_vel_dep,lambda_c);

 //~ Mat_Print(n_vel_indep,1,ddz);
 //~ Mat_Print(n_vel_dep,1,ddd);
//~ Mat_Print(n_vel_indep+n_vel_dep,1,_Delta);
//~ Mat_Print(n_vel_indep,1,_Qz);
//~ Mat_Print(n_gen_coord,n_gen_coord,_CK);
//~ Mat_Print(n_vel_indep,n_vel_indep,_CKzz);
//~ Mat_Print(n_vel_indep,n_vel_dep,_CKzd);
//~ Mat_Print(n_vel_dep,n_vel_indep,_CKdz);
//~ Mat_Print(n_vel_dep,n_vel_dep,_CKdd);

}
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
#include "Done_functions.c"

return 0;
}




