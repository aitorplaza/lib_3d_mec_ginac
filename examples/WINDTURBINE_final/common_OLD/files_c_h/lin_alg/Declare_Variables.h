#ifdef __EXTERNAL
 #include "external_def.h"
#endif

#define n_coord_indep (n_gen_coord-Phi_n_rows)
#define n_vel_dep Beta_n_rows
#define n_vel_indep (n_gen_vel-n_vel_dep)
#define n_accel_dep Gamma_n_rows
#define n_accel_indep (n_gen_accel-n_accel_dep)

extern int iterations_NR;
extern int i, j, iter, niter;

extern double	ddqunknowns[n_unknowns+n_gen_accel];

extern double	* q;
extern double	* dq;
/* ********************************************************************************************* */
/* Coord q */
#ifdef COORD_DEP

	#ifndef DDL
		#ifndef DDQ
			#define DDQ
		#endif
	#endif

	#ifdef DDL
		extern double _INV_MX_aux[MXdPhi_dqZero_n_rows * MXdPhi_dqZero_n_cols];
	#endif

	#ifdef DDQ
		extern double _INV_M_aux[M_n_rows * M_n_cols];
		extern double aux_ddq1[n_gen_accel], aux_ddq2[n_gen_accel];
		extern double aux_Phi_q_T[ M_n_rows * Phi_q_n_rows ];
		extern double bb[ Phi_q_n_rows ];
		extern double AA[ Phi_q_n_rows * Phi_q_n_rows ], INV_AA[ Phi_q_n_rows * Phi_q_n_rows ];
	#endif

	extern double	AUX_V_dep_1[dPhi_dq_n_rows];
	extern double	correction_dq[dPhi_dq_n_cols];
  extern double _Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];/*new*/
	extern double _Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];/*new*/
	extern double _Inv_Phi_q[Phi_q_n_rows * Phi_q_n_cols];
	extern double _Inv_dPhi_dq[dPhi_dq_n_rows * dPhi_dq_n_cols];
	extern double Trasp_Phi_q[ Phi_q_n_rows * Phi_q_n_cols ];
	extern double Trasp_dPhi_dq[ dPhi_dq_n_rows * dPhi_dq_n_cols ];

	#ifdef I3AL
		extern double qn[n_gen_coord], delta_q[n_gen_coord] ;
		extern double dqn[n_gen_vel];
		extern double ddqn[n_gen_accel];
		extern double AUX_V_unk_1[n_unknowns];
		extern double AUX_V_dq_1[n_gen_vel], AUX_V_dq_2[n_gen_vel], project_dq[n_gen_vel];
		extern double AUX_V_ddq_1[n_gen_accel], AUX_V_ddq_2[n_gen_accel], project_ddq[n_gen_accel];
		extern double AUX_M_ddq_1[ n_gen_accel * n_gen_accel ];
		extern double fq[n_gen_accel];
		extern double AUX_fq_q[ n_gen_accel * n_gen_accel ], fq_q[ n_gen_accel * n_gen_accel ], INV_fq_q[ n_gen_accel * n_gen_accel ];
		extern double LAMBDA[n_unknowns];
		extern double alfa;
		extern double sum_error_pos ;
		extern double error         ;
	#endif
#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
/* Coord z */
#ifdef COORD_IND
extern double	correction_dq[dPhi_dq_n_cols];/*new*/
extern double _Inv_PhiInit_q[PhiInit_q_n_rows * PhiInit_q_n_cols];/*new*/
extern double _Inv_dPhiInit_dq[dPhiInit_dq_n_rows * dPhiInit_dq_n_cols];/*new*/
extern double _Inv_Phi_q[Phi_q_n_rows * Phi_q_n_cols];/*new*/
extern double _Inv_dPhi_dq[dPhi_dq_n_rows * dPhi_dq_n_cols];/*new*/
extern double	_Inv_Phi_d[Phi_d_n_rows * Phi_d_n_cols] ;
extern double	AUX_V_dep_1[Phi_d_n_cols], AUX_V_dep_2[Phi_d_n_cols];
extern double	AUX_V_indep_1[Phi_z_n_cols],AUX_V_indep_2[Phi_z_n_cols];
extern double	AUX_M_indep_dep_1[Phi_z_n_cols * Phi_d_n_cols], AUX_M_indep_dep_2[Phi_z_n_cols * Phi_d_n_cols];
extern double	AUX_M_indep_indep_1[Phi_z_n_cols * Phi_z_n_cols], AUX_M_indep_indep_2[Phi_z_n_cols * Phi_z_n_cols];
extern double	INV_AUX_M_indep_indep[Phi_z_n_cols * Phi_z_n_cols];
extern double	A[Phi_d_n_cols * Phi_z_n_cols], AT[Phi_z_n_cols * Phi_d_n_cols];
extern double	b[Phi_d_n_cols], c[Phi_d_n_cols];
extern double	_MZ[Phi_z_n_cols * Phi_z_n_cols],INV_MZ[Phi_z_n_cols * Phi_z_n_cols];;
extern double	_QZ[Phi_z_n_cols];
extern double LU[ Phi_d_n_cols * Phi_d_n_cols ], Y[ Phi_d_n_cols * Phi_z_n_cols ], y[Phi_d_n_cols];
extern int i, o[Phi_d_n_rows], p_vector[Phi_d_n_rows], q_vector[Phi_d_n_cols];
	#ifdef I3AL
		extern double qn[n_gen_coord], delta_q[n_gen_coord], z[n_coord_indep], zn[n_coord_indep], delta_z[n_coord_indep];
		extern double dqn[n_gen_vel], dz[n_vel_indep], dzn[n_vel_indep];
		extern double ddqn[n_gen_accel], ddz[n_accel_indep], ddzn[n_accel_indep];
		extern double e[Phi_d_n_cols];
		extern double _M_aux[n_coord_indep * n_coord_indep];
//		extern double AUX_V_dz_1[n_vel_indep], AUX_V_dz_2[n_vel_indep], project_dz[n_vel_indep];
		extern double AUX_V_dd_1[n_vel_dep];
		extern double AUX_V_ddd_1[n_accel_dep];
		extern double AUX_V_ddz_1[n_accel_indep], AUX_V_ddz_2[n_accel_indep], AUX_V_ddz_3[n_accel_indep];
		extern double AUX_V_unk_1[n_unknowns];
		extern double AUX_M_ddz_1[ n_accel_indep * n_accel_indep ];
		extern double fz[n_accel_indep];
		extern double AUX_fz_z[ n_accel_indep * n_accel_indep ], fz_z[ n_accel_indep * n_accel_indep ], INV_fz_z[ n_accel_indep * n_accel_indep ];
		extern double Trasp_Phi_z[ Phi_z_n_rows * Phi_z_n_cols ];
		extern double LAMBDA[n_unknowns];
		extern double alfa;
		extern double sum_error_pos ;
		extern double error         ;
	#endif

#endif
/* ********************************************************************************************* */
/* ********************************************************************************************* */
#ifdef TRAPEZOIDAL
extern double qn[n_gen_coord], qn1[n_gen_coord],delta_q[n_gen_coord] ;
extern double dqn[n_gen_vel], dqn1[n_gen_vel], delta_dq[n_gen_vel];
extern double ddqn[n_gen_accel], ddqn1[n_gen_accel];
extern double sum_error_pos ;
extern double sum_error_vel ;
extern double error         ;
#endif
/* ********************************************************************************************* */

