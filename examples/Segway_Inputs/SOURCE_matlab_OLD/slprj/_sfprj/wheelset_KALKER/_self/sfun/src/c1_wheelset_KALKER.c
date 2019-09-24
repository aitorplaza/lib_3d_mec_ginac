/* Include files */

#include "blascompat32.h"
#include "wheelset_KALKER_sfun.h"
#include "c1_wheelset_KALKER.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "wheelset_KALKER_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[28] = { "N", "Vxslip", "Vyslip",
  "OMzslip", "Omega", "Vo", "R", "r", "E", "nu", "G", "Ry_w", "Rx_r", "Ry_r",
  "Rx_w", "Radii", "a", "b", "Vx", "Vy", "Phi", "Vcreep", "mu", "Delta_t",
  "nargin", "nargout", "input_vector", "kalker_forces" };

/* Function Declarations */
static void initialize_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance);
static void initialize_params_c1_wheelset_KALKER
  (SFc1_wheelset_KALKERInstanceStruct *chartInstance);
static void enable_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance);
static void disable_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_wheelset_KALKER
  (SFc1_wheelset_KALKERInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_wheelset_KALKER
  (SFc1_wheelset_KALKERInstanceStruct *chartInstance);
static void set_sim_state_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct *
  chartInstance, const mxArray *c1_st);
static void finalize_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance);
static void sf_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance);
static void c1_chartstep_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance);
static void initSimStructsc1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_b_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[4]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[16]);
static real_T c1_mpower(SFc1_wheelset_KALKERInstanceStruct *chartInstance,
  real_T c1_a);
static void c1_eml_error(SFc1_wheelset_KALKERInstanceStruct *chartInstance);
static void c1_c_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_mtimes, const char_T *c1_identifier, real_T
  c1_y[3]);
static void c1_d_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3]);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_e_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_f_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_wheelset_KALKER, const char_T
  *c1_identifier);
static uint8_T c1_g_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_wheelset_KALKER = 0U;
}

static void initialize_params_c1_wheelset_KALKER
  (SFc1_wheelset_KALKERInstanceStruct *chartInstance)
{
}

static void enable_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_wheelset_KALKER
  (SFc1_wheelset_KALKERInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c1_wheelset_KALKER
  (SFc1_wheelset_KALKERInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  real_T c1_u[3];
  const mxArray *c1_b_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T (*c1_kalker_forces)[3];
  c1_kalker_forces = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2), FALSE);
  for (c1_i0 = 0; c1_i0 < 3; c1_i0++) {
    c1_u[c1_i0] = (*c1_kalker_forces)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = chartInstance->c1_is_active_c1_wheelset_KALKER;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct *
  chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[3];
  int32_T c1_i1;
  real_T (*c1_kalker_forces)[3];
  c1_kalker_forces = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                        "kalker_forces", c1_dv0);
  for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
    (*c1_kalker_forces)[c1_i1] = c1_dv0[c1_i1];
  }

  chartInstance->c1_is_active_c1_wheelset_KALKER = c1_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
     "is_active_c1_wheelset_KALKER");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_wheelset_KALKER(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance)
{
}

static void sf_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance)
{
  int32_T c1_i2;
  int32_T c1_i3;
  real_T (*c1_kalker_forces)[3];
  real_T (*c1_input_vector)[8];
  c1_kalker_forces = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_input_vector = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i2 = 0; c1_i2 < 8; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*c1_input_vector)[c1_i2], 0U);
  }

  for (c1_i3 = 0; c1_i3 < 3; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*c1_kalker_forces)[c1_i3], 1U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_wheelset_KALKER(chartInstance);
  sf_debug_check_for_state_inconsistency(_wheelset_KALKERMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance)
{
  int32_T c1_i4;
  real_T c1_input_vector[8];
  uint32_T c1_debug_family_var_map[28];
  real_T c1_N;
  real_T c1_Vxslip;
  real_T c1_Vyslip;
  real_T c1_OMzslip;
  real_T c1_Omega;
  real_T c1_Vo;
  real_T c1_R;
  real_T c1_r;
  real_T c1_E;
  real_T c1_nu;
  real_T c1_G;
  real_T c1_Ry_w;
  real_T c1_Rx_r;
  real_T c1_Ry_r;
  real_T c1_Rx_w;
  real_T c1_Radii[4];
  const mxArray *c1_a = NULL;
  const mxArray *c1_b = NULL;
  real_T c1_Vx;
  real_T c1_Vy;
  real_T c1_Phi;
  real_T c1_Vcreep[3];
  real_T c1_mu;
  real_T c1_Delta_t;
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  real_T c1_kalker_forces[3];
  real_T c1_u;
  const mxArray *c1_y = NULL;
  int32_T c1_i5;
  real_T c1_b_u[4];
  const mxArray *c1_b_y = NULL;
  real_T c1_c_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_d_u;
  const mxArray *c1_d_y = NULL;
  const mxArray *c1_m0 = NULL;
  const mxArray *c1_m1 = NULL;
  const mxArray *c1_b_a = NULL;
  const mxArray *c1_b_b = NULL;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_c_a;
  real_T c1_c_b;
  real_T c1_e_y;
  real_T c1_d_a;
  real_T c1_d_b;
  real_T c1_f_y;
  real_T c1_e_b;
  real_T c1_g_y;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_h_y;
  real_T c1_A;
  real_T c1_B;
  real_T c1_e_x;
  real_T c1_i_y;
  real_T c1_f_x;
  real_T c1_j_y;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_k_y;
  real_T c1_i_x;
  real_T c1_j_x;
  real_T c1_e_a;
  int32_T c1_i6;
  real_T c1_f_b;
  real_T c1_l_y;
  real_T c1_b_A;
  real_T c1_k_x;
  real_T c1_l_x;
  real_T c1_m_y;
  real_T c1_f_a;
  real_T c1_g_b;
  real_T c1_n_y;
  int32_T c1_i7;
  real_T c1_e_u[3];
  const mxArray *c1_o_y = NULL;
  real_T c1_f_u;
  const mxArray *c1_p_y = NULL;
  int32_T c1_i8;
  real_T c1_g_u[3];
  const mxArray *c1_q_y = NULL;
  real_T c1_h_u;
  const mxArray *c1_r_y = NULL;
  real_T c1_i_u;
  const mxArray *c1_s_y = NULL;
  real_T c1_dv1[3];
  int32_T c1_i9;
  real_T c1_m_x;
  real_T c1_n_x;
  real_T c1_t_y;
  real_T c1_o_x;
  real_T c1_p_x;
  real_T c1_h_b;
  real_T c1_u_y;
  real_T c1_g_a;
  real_T c1_i_b;
  real_T c1_v_y;
  int32_T c1_i10;
  real_T (*c1_b_kalker_forces)[3];
  real_T (*c1_b_input_vector)[8];
  boolean_T guard1 = FALSE;
  c1_b_kalker_forces = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_input_vector = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i4 = 0; c1_i4 < 8; c1_i4++) {
    c1_input_vector[c1_i4] = (*c1_b_input_vector)[c1_i4];
  }

  sf_debug_symbol_scope_push_eml(0U, 28U, 28U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_N, 0U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Vxslip, 1U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Vyslip, 2U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_OMzslip, 3U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Omega, 4U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Vo, 5U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_R, 6U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_r, 7U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_E, 8U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_nu, 9U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_G, 10U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Ry_w, 11U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Rx_r, 12U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Ry_r, 13U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Rx_w, 14U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_Radii, 15U, c1_e_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_a, 16U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_b, 17U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_Vx, 18U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Vy, 19U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Phi, 20U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_Vcreep, 21U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_mu, 22U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_Delta_t, 23U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 24U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 25U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c1_input_vector, 26U, c1_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c1_kalker_forces, 27U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  c1_N = c1_input_vector[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  c1_Vxslip = c1_input_vector[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  c1_Vyslip = c1_input_vector[2];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  c1_OMzslip = c1_input_vector[3];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_Omega = c1_input_vector[4];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  c1_Vo = c1_input_vector[5];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_R = c1_input_vector[6];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_r = c1_input_vector[7];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  c1_E = 2.1E+11;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
  c1_nu = 0.27;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
  c1_G = 1.4383561643835617E+11;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
  if (CV_EML_IF(0, 1, 0, c1_R == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
    c1_R = 0.5;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
  if (CV_EML_IF(0, 1, 1, c1_r == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
    c1_r = 0.1;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 28);
  c1_Ry_w = c1_R;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 29);
  c1_Rx_r = c1_r;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 30);
  c1_Ry_r = rtInf;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 31);
  c1_Rx_w = rtInf;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  c1_Radii[0] = c1_Rx_w;
  c1_Radii[1] = c1_Rx_r;
  c1_Radii[2] = c1_Ry_w;
  c1_Radii[3] = c1_Ry_r;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 35);
  c1_u = c1_N;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  for (c1_i5 = 0; c1_i5 < 4; c1_i5++) {
    c1_b_u[c1_i5] = c1_Radii[c1_i5];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  c1_c_u = c1_E;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  c1_d_u = c1_nu;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_call_debug("Hertz_ellipse", 2U, 4U, 14, c1_y, 14, c1_b_y, 14, c1_c_y,
                    14, c1_d_y, &c1_m1, &c1_m0);
  sf_mex_assign(&c1_b_a, sf_mex_dup(c1_m1), FALSE);
  sf_mex_assign(&c1_b_b, sf_mex_dup(c1_m0), FALSE);
  sf_mex_assign(&c1_a, sf_mex_dup(c1_b_a), FALSE);
  sf_mex_assign(&c1_b, sf_mex_dup(c1_b_b), FALSE);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
  c1_x = (c1_mpower(chartInstance, c1_Vxslip) + c1_mpower(chartInstance,
           c1_Vyslip)) + c1_mpower(chartInstance, c1_OMzslip);
  c1_b_x = c1_x;
  if (c1_b_x < 0.0) {
    c1_eml_error(chartInstance);
  }

  c1_b_x = muDoubleScalarSqrt(c1_b_x);
  if (CV_EML_IF(0, 1, 2, c1_b_x > 1.0E-8)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 40);
    c1_c_a = c1_R;
    c1_c_b = c1_Omega;
    c1_e_y = c1_c_a * c1_c_b;
    c1_d_a = c1_R;
    c1_d_b = c1_Omega;
    c1_f_y = c1_d_a * c1_d_b;
    c1_e_b = c1_Vo + c1_f_y;
    c1_g_y = 0.5 * c1_e_b;
    c1_c_x = c1_g_y;
    c1_d_x = c1_c_x;
    c1_h_y = muDoubleScalarAbs(c1_d_x);
    c1_A = c1_Vo - c1_e_y;
    c1_B = c1_h_y;
    c1_e_x = c1_A;
    c1_i_y = c1_B;
    c1_f_x = c1_e_x;
    c1_j_y = c1_i_y;
    c1_Vx = c1_f_x / c1_j_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 43);
    c1_g_x = c1_Vx;
    c1_h_x = c1_g_x;
    c1_k_y = muDoubleScalarAbs(c1_h_x);
    if (CV_EML_IF(0, 1, 3, c1_k_y >= 0.04)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 44);
      c1_i_x = c1_Vx;
      c1_j_x = c1_i_x;
      if (c1_j_x > 0.0) {
        c1_j_x = 1.0;
      } else if (c1_j_x < 0.0) {
        c1_j_x = -1.0;
      } else {
        if (c1_j_x == 0.0) {
          c1_j_x = 0.0;
        }
      }

      c1_e_a = c1_j_x;
      c1_Vx = c1_e_a * 0.04;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 46);
    c1_Vy = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 47);
    c1_Phi = 0.0;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 49);
    c1_Vx = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 50);
    c1_Vy = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 51);
    c1_Phi = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 53);
  c1_Vcreep[0] = c1_Vx;
  c1_Vcreep[1] = c1_Vy;
  c1_Vcreep[2] = c1_Phi;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 55);
  c1_mu = 0.4;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 56);
  c1_Delta_t = 0.001;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 58);
  for (c1_i6 = 0; c1_i6 < 3; c1_i6++) {
    c1_kalker_forces[c1_i6] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 59);
  guard1 = FALSE;
  if (CV_EML_COND(0, 1, 0, c1_Vxslip < 0.0098000000000000014)) {
    if (CV_EML_COND(0, 1, 1, c1_Vo < 0.1)) {
      CV_EML_MCDC(0, 1, 0, TRUE);
      CV_EML_IF(0, 1, 4, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 60);
      c1_f_b = c1_N;
      c1_l_y = 0.4 * c1_f_b;
      c1_b_A = c1_l_y;
      c1_k_x = c1_b_A;
      c1_l_x = c1_k_x;
      c1_m_y = c1_l_x / 0.0098000000000000014;
      c1_f_a = -c1_m_y;
      c1_g_b = c1_Vxslip;
      c1_n_y = c1_f_a * c1_g_b;
      c1_kalker_forces[0] = c1_n_y;
      sf_mex_printf("%s =\\n", "kalker_forces");
      for (c1_i7 = 0; c1_i7 < 3; c1_i7++) {
        c1_e_u[c1_i7] = c1_kalker_forces[c1_i7];
      }

      c1_o_y = NULL;
      sf_mex_assign(&c1_o_y, sf_mex_create("y", c1_e_u, 0, 0U, 1U, 0U, 1, 3),
                    FALSE);
      sf_mex_call_debug("disp", 0U, 1U, 14, c1_o_y);
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 0, FALSE);
    CV_EML_IF(0, 1, 4, FALSE);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 62);
    c1_f_u = 1.0;
    c1_p_y = NULL;
    sf_mex_assign(&c1_p_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), FALSE);
    for (c1_i8 = 0; c1_i8 < 3; c1_i8++) {
      c1_g_u[c1_i8] = c1_Vcreep[c1_i8];
    }

    c1_q_y = NULL;
    sf_mex_assign(&c1_q_y, sf_mex_create("y", c1_g_u, 0, 0U, 1U, 0U, 1, 3),
                  FALSE);
    c1_h_u = c1_G;
    c1_r_y = NULL;
    sf_mex_assign(&c1_r_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), FALSE);
    c1_i_u = c1_nu;
    c1_s_y = NULL;
    sf_mex_assign(&c1_s_y, sf_mex_create("y", &c1_i_u, 0, 0U, 0U, 0U, 0), FALSE);
    c1_c_emlrt_marshallIn(chartInstance, sf_mex_call_debug("mtimes", 1U, 2U, 14,
      c1_p_y, 14, sf_mex_call_debug("Kalker_linear", 1U, 5U, 14, c1_q_y, 14,
      sf_mex_dup(c1_a), 14, sf_mex_dup(c1_b), 14, c1_r_y, 14, c1_s_y)), "mtimes",
                          c1_dv1);
    for (c1_i9 = 0; c1_i9 < 3; c1_i9++) {
      c1_kalker_forces[c1_i9] = c1_dv1[c1_i9];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 66);
  c1_m_x = c1_kalker_forces[0];
  c1_n_x = c1_m_x;
  c1_t_y = muDoubleScalarAbs(c1_n_x);
  if (CV_EML_IF(0, 1, 5, c1_t_y >= c1_N)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 67);
    c1_o_x = c1_kalker_forces[0];
    c1_p_x = c1_o_x;
    if (c1_p_x > 0.0) {
      c1_p_x = 1.0;
    } else if (c1_p_x < 0.0) {
      c1_p_x = -1.0;
    } else {
      if (c1_p_x == 0.0) {
        c1_p_x = 0.0;
      }
    }

    c1_h_b = c1_p_x;
    c1_u_y = 0.4 * c1_h_b;
    c1_g_a = c1_u_y;
    c1_i_b = c1_N;
    c1_v_y = c1_g_a * c1_i_b;
    c1_kalker_forces[0] = c1_v_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -67);
  sf_debug_symbol_scope_pop();
  sf_mex_destroy(&c1_a);
  sf_mex_destroy(&c1_b);
  sf_mex_destroy(&c1_b_a);
  sf_mex_destroy(&c1_b_b);
  sf_mex_destroy(&c1_m0);
  sf_mex_destroy(&c1_m1);
  for (c1_i10 = 0; c1_i10 < 3; c1_i10++) {
    (*c1_b_kalker_forces)[c1_i10] = c1_kalker_forces[c1_i10];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_wheelset_KALKER(SFc1_wheelset_KALKERInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i11;
  real_T c1_b_inData[3];
  int32_T c1_i12;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i11 = 0; c1_i11 < 3; c1_i11++) {
    c1_b_inData[c1_i11] = (*(real_T (*)[3])c1_inData)[c1_i11];
  }

  for (c1_i12 = 0; c1_i12 < 3; c1_i12++) {
    c1_u[c1_i12] = c1_b_inData[c1_i12];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_mtimes;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i13;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_mtimes = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_mtimes), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_mtimes);
  for (c1_i13 = 0; c1_i13 < 3; c1_i13++) {
    (*(real_T (*)[3])c1_outData)[c1_i13] = c1_y[c1_i13];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i14;
  real_T c1_b_inData[8];
  int32_T c1_i15;
  real_T c1_u[8];
  const mxArray *c1_y = NULL;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i14 = 0; c1_i14 < 8; c1_i14++) {
    c1_b_inData[c1_i14] = (*(real_T (*)[8])c1_inData)[c1_i14];
  }

  for (c1_i15 = 0; c1_i15 < 8; c1_i15++) {
    c1_u[c1_i15] = c1_b_inData[c1_i15];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 8), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  const mxArray *c1_u;
  const mxArray *c1_y = NULL;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = sf_mex_dup(*(const mxArray **)c1_inData);
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), FALSE);
  sf_mex_destroy(&c1_u);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i16;
  real_T c1_b_inData[4];
  int32_T c1_i17;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i16 = 0; c1_i16 < 4; c1_i16++) {
    c1_b_inData[c1_i16] = (*(real_T (*)[4])c1_inData)[c1_i16];
  }

  for (c1_i17 = 0; c1_i17 < 4; c1_i17++) {
    c1_u[c1_i17] = c1_b_inData[c1_i17];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_b_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[4])
{
  real_T c1_dv2[4];
  int32_T c1_i18;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv2, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c1_i18 = 0; c1_i18 < 4; c1_i18++) {
    c1_y[c1_i18] = c1_dv2[c1_i18];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_Radii;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4];
  int32_T c1_i19;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_Radii = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Radii), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Radii);
  for (c1_i19 = 0; c1_i19 < 4; c1_i19++) {
    (*(real_T (*)[4])c1_outData)[c1_i19] = c1_y[c1_i19];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_wheelset_KALKER_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[16];
  const mxArray *c1_m2 = NULL;
  int32_T c1_i20;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m2, sf_mex_createstruct("nameCaptureInfo", 1, 16), FALSE);
  for (c1_i20 = 0; c1_i20 < 16; c1_i20++) {
    c1_r0 = &c1_info[c1_i20];
    sf_mex_addfield(c1_m2, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i20);
    sf_mex_addfield(c1_m2, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i20);
    sf_mex_addfield(c1_m2, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i20);
    sf_mex_addfield(c1_m2, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i20);
    sf_mex_addfield(c1_m2, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i20);
    sf_mex_addfield(c1_m2, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i20);
    sf_mex_addfield(c1_m2, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i20);
    sf_mex_addfield(c1_m2, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i20);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m2, FALSE);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[16])
{
  c1_info[0].context = "";
  c1_info[0].name = "mtimes";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[0].fileTimeLo = 1289519692U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context = "";
  c1_info[1].name = "mrdivide";
  c1_info[1].dominantType = "double";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[1].fileTimeLo = 1310137456U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 1289519692U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[2].name = "rdivide";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[2].fileTimeLo = 1286818844U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[3].name = "eml_div";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[3].fileTimeLo = 1305318000U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context = "";
  c1_info[4].name = "mpower";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[4].fileTimeLo = 1286818842U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[5].name = "power";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[5].fileTimeLo = 1294067944U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[6].name = "eml_scalar_eg";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[6].fileTimeLo = 1286818796U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[7].name = "eml_scalexp_alloc";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[7].fileTimeLo = 1286818796U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[8].name = "eml_scalar_floor";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[8].fileTimeLo = 1286818726U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context = "";
  c1_info[9].name = "sqrt";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[9].fileTimeLo = 1286818752U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[10].name = "eml_error";
  c1_info[10].dominantType = "char";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[10].fileTimeLo = 1305318000U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[11].name = "eml_scalar_sqrt";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c1_info[11].fileTimeLo = 1286818738U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context = "";
  c1_info[12].name = "abs";
  c1_info[12].dominantType = "double";
  c1_info[12].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[12].fileTimeLo = 1286818694U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[13].name = "eml_scalar_abs";
  c1_info[13].dominantType = "double";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[13].fileTimeLo = 1286818712U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context = "";
  c1_info[14].name = "sign";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[14].fileTimeLo = 1286818750U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[15].name = "eml_scalar_sign";
  c1_info[15].dominantType = "double";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sign.m";
  c1_info[15].fileTimeLo = 1286818736U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
}

static real_T c1_mpower(SFc1_wheelset_KALKERInstanceStruct *chartInstance,
  real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_ak;
  c1_b_a = c1_a;
  c1_ak = c1_b_a;
  return muDoubleScalarPower(c1_ak, 2.0);
}

static void c1_eml_error(SFc1_wheelset_KALKERInstanceStruct *chartInstance)
{
  int32_T c1_i21;
  static char_T c1_varargin_1[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o',
    'o', 'l', 'b', 'o', 'x', ':', 's', 'q', 'r', 't', '_', 'd', 'o', 'm', 'a',
    'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c1_u[30];
  const mxArray *c1_y = NULL;
  for (c1_i21 = 0; c1_i21 < 30; c1_i21++) {
    c1_u[c1_i21] = c1_varargin_1[c1_i21];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c1_y));
}

static void c1_c_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_mtimes, const char_T *c1_identifier, real_T
  c1_y[3])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_mtimes), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_mtimes);
}

static void c1_d_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3])
{
  real_T c1_dv3[3];
  int32_T c1_i22;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i22 = 0; c1_i22 < 3; c1_i22++) {
    c1_y[c1_i22] = c1_dv3[c1_i22];
  }

  sf_mex_destroy(&c1_u);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_e_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i23;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i23, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i23;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_wheelset_KALKER, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_wheelset_KALKER), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_wheelset_KALKER);
  return c1_y;
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_wheelset_KALKERInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_wheelset_KALKER_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(874285679U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1407534007U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3999201080U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1785607183U);
}

mxArray *sf_c1_wheelset_KALKER_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("BUUGA7lTzLIycLjz34lpVB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c1_wheelset_KALKER(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"kalker_forces\",},{M[8],M[0],T\"is_active_c1_wheelset_KALKER\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_wheelset_KALKER_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_wheelset_KALKERInstanceStruct *chartInstance;
    chartInstance = (SFc1_wheelset_KALKERInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_wheelset_KALKERMachineNumber_,
           1,
           1,
           1,
           2,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_wheelset_KALKERMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_wheelset_KALKERMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_wheelset_KALKERMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"input_vector");
          _SFD_SET_DATA_PROPS(1,2,0,1,"kalker_forces");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,6,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1651);
        _SFD_CV_INIT_EML_IF(0,1,0,373,382,-1,400);
        _SFD_CV_INIT_EML_IF(0,1,1,401,410,-1,428);
        _SFD_CV_INIT_EML_IF(0,1,2,601,649,1027,1075);
        _SFD_CV_INIT_EML_IF(0,1,3,872,888,-1,916);
        _SFD_CV_INIT_EML_IF(0,1,4,1152,1187,1252,1318);
        _SFD_CV_INIT_EML_IF(0,1,5,1321,1348,-1,1403);

        {
          static int condStart[] = { 1155, 1179 };

          static int condEnd[] = { 1175, 1187 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,1155,1187,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          real_T (*c1_input_vector)[8];
          real_T (*c1_kalker_forces)[3];
          c1_kalker_forces = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c1_input_vector = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S,
            0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_input_vector);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_kalker_forces);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_wheelset_KALKERMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c1_wheelset_KALKER(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_wheelset_KALKERInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*)
    chartInstanceVar);
  initialize_c1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_wheelset_KALKER(void *chartInstanceVar)
{
  enable_c1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_wheelset_KALKER(void *chartInstanceVar)
{
  disable_c1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_wheelset_KALKER(void *chartInstanceVar)
{
  sf_c1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_wheelset_KALKER(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_wheelset_KALKER
    ((SFc1_wheelset_KALKERInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_wheelset_KALKER();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_wheelset_KALKER(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_wheelset_KALKER();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_wheelset_KALKER(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_wheelset_KALKER(S);
}

static void sf_opaque_set_sim_state_c1_wheelset_KALKER(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c1_wheelset_KALKER(S, st);
}

static void sf_opaque_terminate_c1_wheelset_KALKER(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_wheelset_KALKERInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_wheelset_KALKER_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_wheelset_KALKER(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_wheelset_KALKER((SFc1_wheelset_KALKERInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_wheelset_KALKER(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_wheelset_KALKER_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,infoStruct,1,1);
      sf_mark_chart_reusable_outputs(S,infoStruct,1,1);
    }

    sf_set_rtw_dwork_info(S,infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3071329623U));
  ssSetChecksum1(S,(608470297U));
  ssSetChecksum2(S,(52378598U));
  ssSetChecksum3(S,(2032325070U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_wheelset_KALKER(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_wheelset_KALKER(SimStruct *S)
{
  SFc1_wheelset_KALKERInstanceStruct *chartInstance;
  chartInstance = (SFc1_wheelset_KALKERInstanceStruct *)malloc(sizeof
    (SFc1_wheelset_KALKERInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_wheelset_KALKERInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_wheelset_KALKER;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_wheelset_KALKER;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_wheelset_KALKER;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_wheelset_KALKER;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_wheelset_KALKER;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_wheelset_KALKER;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_wheelset_KALKER;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_wheelset_KALKER;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_wheelset_KALKER;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_wheelset_KALKER;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_wheelset_KALKER;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_wheelset_KALKER_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_wheelset_KALKER(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_wheelset_KALKER(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_wheelset_KALKER(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_wheelset_KALKER_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}