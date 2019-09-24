#ifndef NR_ITER
  #define NR_ITER 1
#endif

#include "Declare_Variables.h"

int iterations_NR=NR_ITER;
int i, j, iter;

double	ddqunknowns[n_unknowns+n_gen_accel];

/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP

	#ifdef DDL
		double _INV_MX_aux[MXdPhi_dqZero_n_rows * MXdPhi_dqZero_n_cols];
	#endif

	#ifdef DDQ
		double _INV_M_aux[M_n_rows * M_n_cols];
		double aux_ddq1[n_gen_accel], aux_ddq2[n_gen_accel];
		double aux_Phi_q_T[ M_n_rows * Phi_q_n_rows ];
		double bb[ Phi_q_n_rows ];
		double AA[ Phi_q_n_rows * Phi_q_n_rows ], INV_AA[ Phi_q_n_rows * Phi_q_n_rows ];
		double Trasp_Phi_q[ Phi_q_n_rows * Phi_q_n_cols ];
	#endif

	double	AUX_V_dep_1[dPhi_dq_n_rows];
	double	correction_dq[dPhi_dq_n_cols];
	double _Inv_Phi_q[Phi_q_n_rows * Phi_q_n_cols];
	double _Inv_dPhi_dq[dPhi_dq_n_rows * dPhi_dq_n_cols];

	#ifdef I3AL
		double qn[n_gen_coord], delta_q[n_gen_coord] ;
		double dqn[n_gen_vel];
		double ddqn[n_gen_accel];
		double AUX_V_unk_1[n_unknowns];
		double AUX_V_dq_1[n_gen_vel], AUX_V_dq_2[n_gen_vel], project_dq[n_gen_vel];
		double AUX_V_ddq_1[n_gen_accel], AUX_V_ddq_2[n_gen_accel], project_ddq[n_gen_accel];
		double AUX_M_ddq_1[ n_gen_accel * n_gen_accel ];
		double fq[n_gen_accel];
		double AUX_fq_q[ n_gen_accel * n_gen_accel ], fq_q[ n_gen_accel * n_gen_accel ], INV_fq_q[ n_gen_accel * n_gen_accel ];
		double Trasp_Phi_q[ Phi_q_n_rows * Phi_q_n_cols ];
		double LAMBDA[n_unknowns];
		double alfa=ALFA;
		double sum_error_pos ;
		double error         ;
	#endif
#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND
double	_Inv_Phi_d[Phi_d_n_rows * Phi_d_n_cols] ;
double	AUX_V_dep_1[Phi_d_n_cols], AUX_V_dep_2[Phi_d_n_cols];
double	AUX_V_indep_1[Phi_z_n_cols],AUX_V_indep_2[Phi_z_n_cols];
double	AUX_M_indep_dep_1[Phi_z_n_cols * Phi_d_n_cols], AUX_M_indep_dep_2[Phi_z_n_cols * Phi_d_n_cols];
double	AUX_M_indep_indep_1[Phi_z_n_cols * Phi_z_n_cols], AUX_M_indep_indep_2[Phi_z_n_cols * Phi_z_n_cols];
double	INV_AUX_M_indep_indep[Phi_z_n_cols * Phi_z_n_cols];
double	A[Phi_d_n_cols * Phi_z_n_cols], AT[Phi_z_n_cols * Phi_d_n_cols];
double	b[Phi_d_n_cols], c[Phi_d_n_cols];
double	_MZ[Phi_z_n_cols * Phi_z_n_cols],INV_MZ[Phi_z_n_cols * Phi_z_n_cols];;
double	_QZ[Phi_z_n_cols];

	#ifdef I3AL
		double qn[n_gen_coord], delta_q[n_gen_coord], z[n_coord_indep], zn[n_coord_indep], delta_z[n_coord_indep];
		double dqn[n_gen_vel], dz[n_vel_indep], dzn[n_vel_indep];
		double ddqn[n_gen_accel], ddz[n_accel_indep], ddzn[n_accel_indep];
		double e[Phi_d_n_cols];
		double _M_aux[n_coord_indep * n_coord_indep];
//		double AUX_V_dz_1[n_vel_indep], AUX_V_dz_2[n_vel_indep], project_dz[n_vel_indep];
		double AUX_V_dd_1[n_vel_dep];
		double AUX_V_ddd_1[n_accel_dep];
		double AUX_V_ddz_1[n_accel_indep], AUX_V_ddz_2[n_accel_indep], AUX_V_ddz_3[n_accel_indep];
		double AUX_V_unk_1[n_unknowns];
		double AUX_M_ddz_1[ n_accel_indep * n_accel_indep ];
		double fz[n_accel_indep];
		double AUX_fz_z[ n_accel_indep * n_accel_indep ], fz_z[ n_accel_indep * n_accel_indep ], INV_fz_z[ n_accel_indep * n_accel_indep ];
		double Trasp_Phi_z[ Phi_z_n_rows * Phi_z_n_cols ];
		double LAMBDA[n_unknowns];
		double alfa=ALFA;
		double sum_error_pos ;
		double error         ;
	#endif

#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
#ifdef TRAPEZOIDAL
double qn[n_gen_coord], qn1[n_gen_coord],delta_q[n_gen_coord] ;
double dqn[n_gen_vel], dqn1[n_gen_vel], delta_dq[n_gen_vel];
double ddqn[n_gen_accel], ddqn1[n_gen_accel];
double sum_error_pos ;
double sum_error_vel ;
double error         ;
#endif
/* ********************************************************************************************* */

