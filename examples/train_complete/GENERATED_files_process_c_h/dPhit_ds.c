/*----------dPhit_ds.c lib3D_MEC exported-----------*/

/* CMO exported */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "time_3D_mec.h"
#include "gen_coord.h"
#include "gen_vel.h"
#include "gen_accel.h"
#include "gen_auxcoord.h"
#include "gen_auxvel.h"
#include "gen_auxaccel.h"
#include "param.h"
#include "unknowns.h"
#include "inputs.h"

#include "step.h"

#include "dPhit_ds.h"

#define xWAG q[ 0 ]
#define yWAG q[ 1 ]
#define zWAG q[ 2 ]
#define aWAG q[ 3 ]
#define bWAG q[ 4 ]
#define cWAG q[ 5 ]
#define cRSLD q[ 6 ]
#define cFSLD q[ 7 ]
#define zRBOG q[ 8 ]
#define aRBOG q[ 9 ]
#define bRBOG q[ 10 ]
#define zFBOG q[ 11 ]
#define aFBOG q[ 12 ]
#define bFBOG q[ 13 ]
#define zRWHSF q[ 14 ]
#define aRWHSF q[ 15 ]
#define bRWHSF q[ 16 ]
#define zRWHSR q[ 17 ]
#define aRWHSR q[ 18 ]
#define bRWHSR q[ 19 ]
#define zFWHSF q[ 20 ]
#define aFWHSF q[ 21 ]
#define bFWHSF q[ 22 ]
#define zFWHSR q[ 23 ]
#define aFWHSR q[ 24 ]
#define bFWHSR q[ 25 ]
#define bRAXBFL q[ 26 ]
#define bRAXBFR q[ 27 ]
#define bRAXBRL q[ 28 ]
#define bRAXBRR q[ 29 ]
#define bFAXBFL q[ 30 ]
#define bFAXBFR q[ 31 ]
#define bFAXBRL q[ 32 ]
#define bFAXBRR q[ 33 ]
#define xRMOTF q[ 34 ]
#define yRMOTF q[ 35 ]
#define zRMOTF q[ 36 ]
#define bRMOTF q[ 37 ]
#define xRMOTR q[ 38 ]
#define yRMOTR q[ 39 ]
#define zRMOTR q[ 40 ]
#define bRMOTR q[ 41 ]
#define bRROTF q[ 42 ]
#define bRROTR q[ 43 ]
#define dxWAG dq[ 0 ]
#define dyWAG dq[ 1 ]
#define dzWAG dq[ 2 ]
#define daWAG dq[ 3 ]
#define dbWAG dq[ 4 ]
#define dcWAG dq[ 5 ]
#define dcRSLD dq[ 6 ]
#define dcFSLD dq[ 7 ]
#define dzRBOG dq[ 8 ]
#define daRBOG dq[ 9 ]
#define dbRBOG dq[ 10 ]
#define dzFBOG dq[ 11 ]
#define daFBOG dq[ 12 ]
#define dbFBOG dq[ 13 ]
#define dzRWHSF dq[ 14 ]
#define daRWHSF dq[ 15 ]
#define dbRWHSF dq[ 16 ]
#define dzRWHSR dq[ 17 ]
#define daRWHSR dq[ 18 ]
#define dbRWHSR dq[ 19 ]
#define dzFWHSF dq[ 20 ]
#define daFWHSF dq[ 21 ]
#define dbFWHSF dq[ 22 ]
#define dzFWHSR dq[ 23 ]
#define daFWHSR dq[ 24 ]
#define dbFWHSR dq[ 25 ]
#define dbRAXBFL dq[ 26 ]
#define dbRAXBFR dq[ 27 ]
#define dbRAXBRL dq[ 28 ]
#define dbRAXBRR dq[ 29 ]
#define dbFAXBFL dq[ 30 ]
#define dbFAXBFR dq[ 31 ]
#define dbFAXBRL dq[ 32 ]
#define dbFAXBRR dq[ 33 ]
#define dxRMOTF dq[ 34 ]
#define dyRMOTF dq[ 35 ]
#define dzRMOTF dq[ 36 ]
#define dbRMOTF dq[ 37 ]
#define dxRMOTR dq[ 38 ]
#define dyRMOTR dq[ 39 ]
#define dzRMOTR dq[ 40 ]
#define dbRMOTR dq[ 41 ]
#define dbRROTF dq[ 42 ]
#define dbRROTR dq[ 43 ]
#define ddxWAG ddq[ 0 ]
#define ddyWAG ddq[ 1 ]
#define ddzWAG ddq[ 2 ]
#define ddaWAG ddq[ 3 ]
#define ddbWAG ddq[ 4 ]
#define ddcWAG ddq[ 5 ]
#define ddcRSLD ddq[ 6 ]
#define ddcFSLD ddq[ 7 ]
#define ddzRBOG ddq[ 8 ]
#define ddaRBOG ddq[ 9 ]
#define ddbRBOG ddq[ 10 ]
#define ddzFBOG ddq[ 11 ]
#define ddaFBOG ddq[ 12 ]
#define ddbFBOG ddq[ 13 ]
#define ddzRWHSF ddq[ 14 ]
#define ddaRWHSF ddq[ 15 ]
#define ddbRWHSF ddq[ 16 ]
#define ddzRWHSR ddq[ 17 ]
#define ddaRWHSR ddq[ 18 ]
#define ddbRWHSR ddq[ 19 ]
#define ddzFWHSF ddq[ 20 ]
#define ddaFWHSF ddq[ 21 ]
#define ddbFWHSF ddq[ 22 ]
#define ddzFWHSR ddq[ 23 ]
#define ddaFWHSR ddq[ 24 ]
#define ddbFWHSR ddq[ 25 ]
#define ddbRAXBFL ddq[ 26 ]
#define ddbRAXBFR ddq[ 27 ]
#define ddbRAXBRL ddq[ 28 ]
#define ddbRAXBRR ddq[ 29 ]
#define ddbFAXBFL ddq[ 30 ]
#define ddbFAXBFR ddq[ 31 ]
#define ddbFAXBRL ddq[ 32 ]
#define ddbFAXBRR ddq[ 33 ]
#define ddxRMOTF ddq[ 34 ]
#define ddyRMOTF ddq[ 35 ]
#define ddzRMOTF ddq[ 36 ]
#define ddbRMOTF ddq[ 37 ]
#define ddxRMOTR ddq[ 38 ]
#define ddyRMOTR ddq[ 39 ]
#define ddzRMOTR ddq[ 40 ]
#define ddbRMOTR ddq[ 41 ]
#define ddbRROTF ddq[ 42 ]
#define ddbRROTR ddq[ 43 ]
#define thetaW_RFR qaux[ 0 ]
#define uW_RFR qaux[ 1 ]
#define uR_RFR qaux[ 2 ]
#define xR_RFR qaux[ 3 ]
#define thetaW_RFL qaux[ 4 ]
#define uW_RFL qaux[ 5 ]
#define uR_RFL qaux[ 6 ]
#define xR_RFL qaux[ 7 ]
#define thetaW_RRR qaux[ 8 ]
#define uW_RRR qaux[ 9 ]
#define uR_RRR qaux[ 10 ]
#define xR_RRR qaux[ 11 ]
#define thetaW_RRL qaux[ 12 ]
#define uW_RRL qaux[ 13 ]
#define uR_RRL qaux[ 14 ]
#define xR_RRL qaux[ 15 ]
#define thetaW_FFR qaux[ 16 ]
#define uW_FFR qaux[ 17 ]
#define uR_FFR qaux[ 18 ]
#define xR_FFR qaux[ 19 ]
#define thetaW_FFL qaux[ 20 ]
#define uW_FFL qaux[ 21 ]
#define uR_FFL qaux[ 22 ]
#define xR_FFL qaux[ 23 ]
#define thetaW_FRR qaux[ 24 ]
#define uW_FRR qaux[ 25 ]
#define uR_FRR qaux[ 26 ]
#define xR_FRR qaux[ 27 ]
#define thetaW_FRL qaux[ 28 ]
#define uW_FRL qaux[ 29 ]
#define uR_FRL qaux[ 30 ]
#define xR_FRL qaux[ 31 ]
#define dthetaW_RFR dqaux[ 0 ]
#define duW_RFR dqaux[ 1 ]
#define duR_RFR dqaux[ 2 ]
#define dxR_RFR dqaux[ 3 ]
#define dthetaW_RFL dqaux[ 4 ]
#define duW_RFL dqaux[ 5 ]
#define duR_RFL dqaux[ 6 ]
#define dxR_RFL dqaux[ 7 ]
#define dthetaW_RRR dqaux[ 8 ]
#define duW_RRR dqaux[ 9 ]
#define duR_RRR dqaux[ 10 ]
#define dxR_RRR dqaux[ 11 ]
#define dthetaW_RRL dqaux[ 12 ]
#define duW_RRL dqaux[ 13 ]
#define duR_RRL dqaux[ 14 ]
#define dxR_RRL dqaux[ 15 ]
#define dthetaW_FFR dqaux[ 16 ]
#define duW_FFR dqaux[ 17 ]
#define duR_FFR dqaux[ 18 ]
#define dxR_FFR dqaux[ 19 ]
#define dthetaW_FFL dqaux[ 20 ]
#define duW_FFL dqaux[ 21 ]
#define duR_FFL dqaux[ 22 ]
#define dxR_FFL dqaux[ 23 ]
#define dthetaW_FRR dqaux[ 24 ]
#define duW_FRR dqaux[ 25 ]
#define duR_FRR dqaux[ 26 ]
#define dxR_FRR dqaux[ 27 ]
#define dthetaW_FRL dqaux[ 28 ]
#define duW_FRL dqaux[ 29 ]
#define duR_FRL dqaux[ 30 ]
#define dxR_FRL dqaux[ 31 ]
#define ddthetaW_RFR ddqaux[ 0 ]
#define dduW_RFR ddqaux[ 1 ]
#define dduR_RFR ddqaux[ 2 ]
#define ddxR_RFR ddqaux[ 3 ]
#define ddthetaW_RFL ddqaux[ 4 ]
#define dduW_RFL ddqaux[ 5 ]
#define dduR_RFL ddqaux[ 6 ]
#define ddxR_RFL ddqaux[ 7 ]
#define ddthetaW_RRR ddqaux[ 8 ]
#define dduW_RRR ddqaux[ 9 ]
#define dduR_RRR ddqaux[ 10 ]
#define ddxR_RRR ddqaux[ 11 ]
#define ddthetaW_RRL ddqaux[ 12 ]
#define dduW_RRL ddqaux[ 13 ]
#define dduR_RRL ddqaux[ 14 ]
#define ddxR_RRL ddqaux[ 15 ]
#define ddthetaW_FFR ddqaux[ 16 ]
#define dduW_FFR ddqaux[ 17 ]
#define dduR_FFR ddqaux[ 18 ]
#define ddxR_FFR ddqaux[ 19 ]
#define ddthetaW_FFL ddqaux[ 20 ]
#define dduW_FFL ddqaux[ 21 ]
#define dduR_FFL ddqaux[ 22 ]
#define ddxR_FFL ddqaux[ 23 ]
#define ddthetaW_FRR ddqaux[ 24 ]
#define dduW_FRR ddqaux[ 25 ]
#define dduR_FRR ddqaux[ 26 ]
#define ddxR_FRR ddqaux[ 27 ]
#define ddthetaW_FRL ddqaux[ 28 ]
#define dduW_FRL ddqaux[ 29 ]
#define dduR_FRL ddqaux[ 30 ]
#define ddxR_FRL ddqaux[ 31 ]
#define g param[ 0 ]
#define L_OBOG_OAXBy param[ 1 ]
#define L_OBOG_OAXBz param[ 2 ]
#define L_OBOG_OSUSPy param[ 3 ]
#define L_OBOG_OSUSPx param[ 4 ]
#define L_OBOG_OSUSPz param[ 5 ]
#define L_OBOG_OWHS param[ 6 ]
#define L_OBOG_P1BOG param[ 7 ]
#define L_MOT param[ 8 ]
#define L_GEAR param[ 9 ]
#define L_AXB1 param[ 10 ]
#define L_AXB2 param[ 11 ]
#define L_SUSP param[ 12 ]
#define L_WHS param[ 13 ]
#define L_RAIL param[ 14 ]
#define L_WAG param[ 15 ]
#define L_SUSPBEAM1 param[ 16 ]
#define L_SUSPBEAM2 param[ 17 ]
#define L_SLDx param[ 18 ]
#define L_SLDy param[ 19 ]
#define b_pend param[ 20 ]
#define a_pend param[ 21 ]
#define L0_1 param[ 22 ]
#define L0_2 param[ 23 ]
#define m_WAG param[ 24 ]
#define I_WAGx param[ 25 ]
#define I_WAGy param[ 26 ]
#define I_WAGz param[ 27 ]
#define xCGWAG param[ 28 ]
#define yCGWAG param[ 29 ]
#define zCGWAG param[ 30 ]
#define G_BOGz param[ 31 ]
#define m_BOG param[ 32 ]
#define I_BOGx param[ 33 ]
#define I_BOGy param[ 34 ]
#define I_BOGz param[ 35 ]
#define m_MOT param[ 36 ]
#define I_MOTx param[ 37 ]
#define I_MOTy param[ 38 ]
#define I_MOTz param[ 39 ]
#define m_ROT param[ 40 ]
#define I_ROTx param[ 41 ]
#define I_ROTy param[ 42 ]
#define I_ROTz param[ 43 ]
#define m_WHS param[ 44 ]
#define I_WHSx param[ 45 ]
#define I_WHSy param[ 46 ]
#define I_WHSz param[ 47 ]
#define I_CORy param[ 48 ]
#define m_AXB param[ 49 ]
#define I_AXBx param[ 50 ]
#define I_AXBy param[ 51 ]
#define I_AXBz param[ 52 ]
#define m_SLD param[ 53 ]
#define I_SLDx param[ 54 ]
#define I_SLDy param[ 55 ]
#define I_SLDz param[ 56 ]
#define K_SSl param[ 57 ]
#define C_SSl param[ 58 ]
#define C_SSr param[ 59 ]
#define K_SSr param[ 60 ]
#define Kgear param[ 61 ]
#define Cgear param[ 62 ]
#define alpha_gear param[ 63 ]
#define zROT param[ 64 ]
#define zWHS param[ 65 ]
#define K_S1 param[ 66 ]
#define C_S1 param[ 67 ]
#define K_S2 param[ 68 ]
#define C_S2 param[ 69 ]
#define aW_RFR param[ 70 ]
#define bW_RFR param[ 71 ]
#define cW_RFR param[ 72 ]
#define dW_RFR param[ 73 ]
#define lW_RFR param[ 74 ]
#define aR_RFR param[ 75 ]
#define bR_RFR param[ 76 ]
#define cR_RFR param[ 77 ]
#define dR_RFR param[ 78 ]
#define lR_RFR param[ 79 ]
#define RFRas param[ 80 ]
#define RFRbs param[ 81 ]
#define RFRcs param[ 82 ]
#define RFRds param[ 83 ]
#define RFRes param[ 84 ]
#define RFRfs param[ 85 ]
#define RFRstas param[ 86 ]
#define RFRends param[ 87 ]
#define irrRFRz param[ 88 ]
#define aW_RFL param[ 89 ]
#define bW_RFL param[ 90 ]
#define cW_RFL param[ 91 ]
#define dW_RFL param[ 92 ]
#define lW_RFL param[ 93 ]
#define aR_RFL param[ 94 ]
#define bR_RFL param[ 95 ]
#define cR_RFL param[ 96 ]
#define dR_RFL param[ 97 ]
#define lR_RFL param[ 98 ]
#define RFLas param[ 99 ]
#define RFLbs param[ 100 ]
#define RFLcs param[ 101 ]
#define RFLds param[ 102 ]
#define RFLes param[ 103 ]
#define RFLfs param[ 104 ]
#define RFLstas param[ 105 ]
#define RFLends param[ 106 ]
#define irrRFLz param[ 107 ]
#define aW_RRR param[ 108 ]
#define bW_RRR param[ 109 ]
#define cW_RRR param[ 110 ]
#define dW_RRR param[ 111 ]
#define lW_RRR param[ 112 ]
#define aR_RRR param[ 113 ]
#define bR_RRR param[ 114 ]
#define cR_RRR param[ 115 ]
#define dR_RRR param[ 116 ]
#define lR_RRR param[ 117 ]
#define RRRas param[ 118 ]
#define RRRbs param[ 119 ]
#define RRRcs param[ 120 ]
#define RRRds param[ 121 ]
#define RRRes param[ 122 ]
#define RRRfs param[ 123 ]
#define RRRstas param[ 124 ]
#define RRRends param[ 125 ]
#define irrRRRz param[ 126 ]
#define aW_RRL param[ 127 ]
#define bW_RRL param[ 128 ]
#define cW_RRL param[ 129 ]
#define dW_RRL param[ 130 ]
#define lW_RRL param[ 131 ]
#define aR_RRL param[ 132 ]
#define bR_RRL param[ 133 ]
#define cR_RRL param[ 134 ]
#define dR_RRL param[ 135 ]
#define lR_RRL param[ 136 ]
#define RRLas param[ 137 ]
#define RRLbs param[ 138 ]
#define RRLcs param[ 139 ]
#define RRLds param[ 140 ]
#define RRLes param[ 141 ]
#define RRLfs param[ 142 ]
#define RRLstas param[ 143 ]
#define RRLends param[ 144 ]
#define irrRRLz param[ 145 ]
#define aW_FFR param[ 146 ]
#define bW_FFR param[ 147 ]
#define cW_FFR param[ 148 ]
#define dW_FFR param[ 149 ]
#define lW_FFR param[ 150 ]
#define aR_FFR param[ 151 ]
#define bR_FFR param[ 152 ]
#define cR_FFR param[ 153 ]
#define dR_FFR param[ 154 ]
#define lR_FFR param[ 155 ]
#define FFRas param[ 156 ]
#define FFRbs param[ 157 ]
#define FFRcs param[ 158 ]
#define FFRds param[ 159 ]
#define FFRes param[ 160 ]
#define FFRfs param[ 161 ]
#define FFRstas param[ 162 ]
#define FFRends param[ 163 ]
#define irrFFRz param[ 164 ]
#define aW_FFL param[ 165 ]
#define bW_FFL param[ 166 ]
#define cW_FFL param[ 167 ]
#define dW_FFL param[ 168 ]
#define lW_FFL param[ 169 ]
#define aR_FFL param[ 170 ]
#define bR_FFL param[ 171 ]
#define cR_FFL param[ 172 ]
#define dR_FFL param[ 173 ]
#define lR_FFL param[ 174 ]
#define FFLas param[ 175 ]
#define FFLbs param[ 176 ]
#define FFLcs param[ 177 ]
#define FFLds param[ 178 ]
#define FFLes param[ 179 ]
#define FFLfs param[ 180 ]
#define FFLstas param[ 181 ]
#define FFLends param[ 182 ]
#define irrFFLz param[ 183 ]
#define aW_FRR param[ 184 ]
#define bW_FRR param[ 185 ]
#define cW_FRR param[ 186 ]
#define dW_FRR param[ 187 ]
#define lW_FRR param[ 188 ]
#define aR_FRR param[ 189 ]
#define bR_FRR param[ 190 ]
#define cR_FRR param[ 191 ]
#define dR_FRR param[ 192 ]
#define lR_FRR param[ 193 ]
#define FRRas param[ 194 ]
#define FRRbs param[ 195 ]
#define FRRcs param[ 196 ]
#define FRRds param[ 197 ]
#define FRRes param[ 198 ]
#define FRRfs param[ 199 ]
#define FRRstas param[ 200 ]
#define FRRends param[ 201 ]
#define irrFRRz param[ 202 ]
#define aW_FRL param[ 203 ]
#define bW_FRL param[ 204 ]
#define cW_FRL param[ 205 ]
#define dW_FRL param[ 206 ]
#define lW_FRL param[ 207 ]
#define aR_FRL param[ 208 ]
#define bR_FRL param[ 209 ]
#define cR_FRL param[ 210 ]
#define dR_FRL param[ 211 ]
#define lR_FRL param[ 212 ]
#define FRLas param[ 213 ]
#define FRLbs param[ 214 ]
#define FRLcs param[ 215 ]
#define FRLds param[ 216 ]
#define FRLes param[ 217 ]
#define FRLfs param[ 218 ]
#define FRLstas param[ 219 ]
#define FRLends param[ 220 ]
#define irrFRLz param[ 221 ]
#define lambda1 unknowns[ 0 ]
#define lambda2 unknowns[ 1 ]
#define lambda3 unknowns[ 2 ]
#define lambda4 unknowns[ 3 ]
#define lambda5 unknowns[ 4 ]
#define lambda6 unknowns[ 5 ]
#define lambda7 unknowns[ 6 ]
#define lambda8 unknowns[ 7 ]
#define T_RMOTF inputs[ 0 ]
#define T_RMOTR inputs[ 1 ]
#define T_FBRKF inputs[ 2 ]
#define T_FBRKR inputs[ 3 ]
#define T_RBRKF inputs[ 4 ]
#define T_RBRKR inputs[ 5 ]
#define Fx_RFR inputs[ 6 ]
#define Fy_RFR inputs[ 7 ]
#define Mz_RFR inputs[ 8 ]
#define Fx_RFL inputs[ 9 ]
#define Fy_RFL inputs[ 10 ]
#define Mz_RFL inputs[ 11 ]
#define Fx_RRR inputs[ 12 ]
#define Fy_RRR inputs[ 13 ]
#define Mz_RRR inputs[ 14 ]
#define Fx_RRL inputs[ 15 ]
#define Fy_RRL inputs[ 16 ]
#define Mz_RRL inputs[ 17 ]
#define Fx_FRR inputs[ 18 ]
#define Fy_FRR inputs[ 19 ]
#define Mz_FRR inputs[ 20 ]
#define Fx_FRL inputs[ 21 ]
#define Fy_FRL inputs[ 22 ]
#define Mz_FRL inputs[ 23 ]
#define Fx_FFR inputs[ 24 ]
#define Fy_FFR inputs[ 25 ]
#define Mz_FFR inputs[ 26 ]
#define Fx_FFL inputs[ 27 ]
#define Fy_FFL inputs[ 28 ]
#define Mz_FFL inputs[ 29 ]

double atom1175;
double atom1177;
double atom1172;
double atom1179;
double atom1176;
double atom1173;
double atom864;
double atom1187;
double atom1209;
double atom1184;
double atom1174;
double atom1178;
double atom1210;
double atom1213;
double atom865;
double atom862;
double atom1234;
double atom863;
double atom1216;
double atom1252;
double atom30;
double atom1249;
double atom31;
double atom1704;
double atom1710;
double atom1703;
double atom1276;
double atom1711;
double atom1712;
double atom1231;
double atom1713;
double atom1817;
double atom1819;
double atom1818;
double atom1831;
double atom1820;
double atom1822;
double atom1834;
double atom1824;
double atom1837;
double atom1826;
double atom1840;
double atom1828;
double atom1855;
double atom1857;
double atom1859;
double atom1860;
double atom1863;
double atom1864;
double atom1843;
double atom1867;
double atom1845;
double atom1868;
double atom1869;
double atom1846;
double atom1870;
double atom1871;
double atom1872;
double atom1847;
double atom1873;
double atom1876;
double atom1878;
double atom1914;
double atom1922;
double atom1776;
double atom1923;
double atom1181;
double atom1193;
double atom1180;
double atom1190;
double atom1219;
double atom1237;
double atom1240;
double atom1222;
double atom1258;
double atom1255;
double atom1282;
double atom1924;
double atom1779;
double atom1784;
double atom1786;
double atom1787;
double atom1789;
double atom1273;
double atom1792;
double atom1279;
double atom1796;
double atom4203;
double atom4205;
double atom4207;
double atom4213;
double atom4215;
double atom4217;
double atom4221;
double atom4218;
double atom4247;
double atom4222;
double atom4223;
double atom4224;
double atom4230;
double atom4232;
double atom4237;
double atom4235;
double atom4225;
double atom4239;
double atom4248;
double atom4240;
double atom4297;
double atom4324;
double atom4301;
double atom4302;
double atom4298;
double atom4328;
double atom4303;
double atom4336;
double atom4331;
double atom4338;
double atom7686;
double atom4304;
double atom4277;
double atom4276;
double atom4275;
double atom4287;
double atom4312;
double atom4314;
double atom1761;
double atom1764;
double atom1702;
double atom868;
double atom1714;
double atom1726;
double atom1725;
double atom1715;
double atom1716;
double atom869;
double atom1730;
double atom867;
double atom866;
double atom1717;
double atom1718;
double atom1721;
double atom1722;
double atom1724;
double atom1736;
double atom0;
double atom1737;
double atom1930;
double atom4362;
double atom4356;
double atom1756;
double atom1759;
double atom1810;
double atom1811;
double atom1812;
double atom1879;
double atom1813;
double atom1814;
double atom1881;
double atom1927;
double atom1195;
double atom1194;
double atom1225;
double atom1246;
double atom1228;
double atom1264;
double atom1261;
double atom1288;
double atom1243;
double atom1928;
double atom1782;
double atom1285;
double atom1800;
double atom4244;
double atom4245;
double atom4254;
double atom7733;
double atom1766;
double atom1769;
double atom4200;
double atom1882;
double atom1883;
double atom1916;
double atom1919;
double atom1917;
double atom1918;
double atom4252;
double atom4258;
double atom4266;
double atom4261;
double atom4270;
double atom4340;
double atom4360;
double atom4343;
double atom4369;
double atom7928;
double atom7931;
double atom7929;
double atom2068;
double atom2069;
double atom2070;
double atom2071;
double atom2073;
double atom2075;
double atom2077;
double atom2079;
double atom2082;
double atom2085;
double atom2088;
double atom2091;
double atom2094;
double atom2096;
double atom2097;
double atom2107;
double atom2108;
double atom2111;
double atom2112;
double atom2115;
double atom2105;
double atom2098;
double atom2118;
double atom2119;
double atom2120;
double atom2121;
double atom2122;
double atom2123;
double atom2125;
double atom2127;
double atom2129;
double atom2165;
double atom2173;
double atom1962;
double atom1966;
double atom1968;
double atom1970;
double atom1971;
double atom1961;
double atom1969;
double atom2174;
double atom2027;
double atom2030;
double atom2175;
double atom2035;
double atom2037;
double atom2041;
double atom2038;
double atom2047;
double atom2043;
double atom4589;
double atom4600;
double atom4679;
double atom4682;
double atom4683;
double atom4601;
double atom4602;
double atom4603;
double atom4684;
double atom4616;
double atom4700;
double atom4703;
double atom4702;
double atom4701;
double atom4713;
double atom4728;
double atom4732;
double atom4614;
double atom4604;
double atom4677;
double atom4618;
double atom4695;
double atom4628;
double atom4691;
double atom4629;
double atom4619;
double atom7992;
double atom2007;
double atom2010;
double atom1972;
double atom1981;
double atom1975;
double atom1977;
double atom1987;
double atom1988;
double atom4742;
double atom4750;
double atom2012;
double atom2015;
double atom2181;
double atom2061;
double atom2062;
double atom2063;
double atom2130;
double atom2065;
double atom2132;
double atom2178;
double atom2033;
double atom2179;
double atom2051;
double atom4624;
double atom4634;
double atom8039;
double atom4646;
double atom2017;
double atom2020;
double atom2134;
double atom2133;
double atom2167;
double atom2170;
double atom2168;
double atom2169;
double atom4625;
double atom4632;
double atom4638;
double atom4639;
double atom4656;
double atom4650;
double atom4699;
double atom4735;
double atom4754;
double atom4740;
double atom8234;
double atom8235;
double atom8237;
double atom2325;
double atom2324;
double atom2326;
double atom2327;
double atom2329;
double atom2331;
double atom2338;
double atom2341;
double atom2344;
double atom2333;
double atom2347;
double atom2335;
double atom2350;
double atom2352;
double atom2353;
double atom2363;
double atom2361;
double atom2366;
double atom2367;
double atom2370;
double atom2372;
double atom2374;
double atom2376;
double atom2375;
double atom2378;
double atom2377;
double atom2379;
double atom2385;
double atom2354;
double atom2380;
double atom2383;
double atom2421;
double atom2429;
double atom49;
double atom50;
double atom2212;
double atom2219;
double atom2218;
double atom1319;
double atom2220;
double atom2221;
double atom2222;
double atom2431;
double atom2286;
double atom1313;
double atom2283;
double atom2430;
double atom2291;
double atom2293;
double atom2297;
double atom2294;
double atom1310;
double atom2299;
double atom1316;
double atom2303;
double atom5080;
double atom5159;
double atom5162;
double atom5173;
double atom5085;
double atom5096;
double atom5174;
double atom5097;
double atom5190;
double atom5228;
double atom5193;
double atom5192;
double atom5191;
double atom5203;
double atom5218;
double atom5236;
double atom5098;
double atom5099;
double atom5107;
double atom5115;
double atom5110;
double atom5118;
double atom5112;
double atom5119;
double atom5113;
double atom5171;
double atom5185;
double atom5178;
double atom5187;
double atom8298;
double atom2268;
double atom2271;
double atom2224;
double atom2225;
double atom2223;
double atom2233;
double atom2237;
double atom2226;
double atom2229;
double atom2230;
double atom2232;
double atom2243;
double atom2244;
double atom2437;
double atom2263;
double atom2266;
double atom5222;
double atom1325;
double atom2317;
double atom2318;
double atom2319;
double atom2386;
double atom2321;
double atom2388;
double atom2434;
double atom2289;
double atom2435;
double atom1322;
double atom2307;
double atom2273;
double atom2276;
double atom5132;
double atom5075;
double atom5124;
double atom8345;
double atom2389;
double atom2390;
double atom2423;
double atom2425;
double atom2424;
double atom2426;
double atom5076;
double atom5122;
double atom5128;
double atom5136;
double atom5142;
double atom5145;
double atom5189;
double atom5247;
double atom5240;
double atom5226;
double atom8540;
double atom8541;
double atom8543;
double atom2469;
double atom2475;
double atom2477;
double atom2478;
double atom2468;
double atom2476;
double atom2575;
double atom2577;
double atom2578;
double atom2580;
double atom2582;
double atom2584;
double atom2589;
double atom2592;
double atom2595;
double atom2598;
double atom2586;
double atom2601;
double atom2603;
double atom2604;
double atom2614;
double atom2616;
double atom2618;
double atom2612;
double atom2621;
double atom2623;
double atom2605;
double atom2625;
double atom2626;
double atom2627;
double atom2629;
double atom2628;
double atom2630;
double atom2631;
double atom2634;
double atom2636;
double atom2672;
double atom2680;
double atom2537;
double atom2682;
double atom2681;
double atom2534;
double atom2542;
double atom2544;
double atom2545;
double atom2548;
double atom2554;
double atom2550;
double atom5467;
double atom5478;
double atom5489;
double atom5490;
double atom5488;
double atom5491;
double atom5503;
double atom5505;
double atom5494;
double atom5506;
double atom5495;
double atom5593;
double atom5550;
double atom5549;
double atom5546;
double atom5551;
double atom5600;
double atom5606;
double atom5602;
double atom8604;
double atom5555;
double atom5554;
double atom5553;
double atom5565;
double atom5552;
double atom5580;
double atom5584;
double atom2479;
double atom2482;
double atom2484;
double atom2495;
double atom2494;
double atom2488;
double atom2514;
double atom2517;
double atom5624;
double atom2519;
double atom2522;
double atom2688;
double atom5619;
double atom2568;
double atom2569;
double atom2570;
double atom2571;
double atom2637;
double atom2572;
double atom2639;
double atom2685;
double atom2686;
double atom2540;
double atom2558;
double atom5499;
double atom5500;
double atom5511;
double atom8651;
double atom5523;
double atom2524;
double atom2527;
double atom2641;
double atom2640;
double atom2674;
double atom2675;
double atom2676;
double atom2677;
double atom5509;
double atom5515;
double atom5516;
double atom5527;
double atom5533;
double atom5609;
double atom5612;
double atom5617;
double atom5628;
double atom8846;
double atom8849;
double atom8847;
double atom2720;
double atom2726;
double atom2728;
double atom1497;
double atom1496;
double atom1018;
double atom1506;
double atom1019;
double atom2729;
double atom1524;
double atom2719;
double atom1527;
double atom1016;
double atom1017;
double atom1509;
double atom497;
double atom1545;
double atom498;
double atom1542;
double atom2727;
double atom1568;
double atom2835;
double atom2834;
double atom2836;
double atom2838;
double atom2840;
double atom2842;
double atom2847;
double atom2850;
double atom2853;
double atom2856;
double atom2844;
double atom2859;
double atom2861;
double atom2862;
double atom2873;
double atom2871;
double atom2876;
double atom2870;
double atom2879;
double atom2881;
double atom2883;
double atom2884;
double atom2885;
double atom2887;
double atom2886;
double atom2888;
double atom2863;
double atom2889;
double atom2892;
double atom2894;
double atom2930;
double atom2938;
double atom2795;
double atom2940;
double atom1500;
double atom1518;
double atom1521;
double atom1503;
double atom1539;
double atom1536;
double atom1562;
double atom2792;
double atom2939;
double atom2800;
double atom2802;
double atom2805;
double atom1559;
double atom2803;
double atom2808;
double atom1565;
double atom2812;
double atom2777;
double atom2780;
double atom2730;
double atom1022;
double atom2741;
double atom2742;
double atom2731;
double atom1023;
double atom2732;
double atom2746;
double atom1020;
double atom2733;
double atom2734;
double atom1021;
double atom2737;
double atom2738;
double atom2740;
double atom2752;
double atom2753;
double atom6132;
double atom6135;
double atom6131;
double atom6136;
double atom6137;
double atom6208;
double atom6219;
double atom6138;
double atom6147;
double atom6221;
double atom6141;
double atom6143;
double atom6229;
double atom6144;
double atom6148;
double atom8910;
double atom6175;
double atom6174;
double atom6173;
double atom6185;
double atom6186;
double atom6201;
double atom6245;
double atom2946;
double atom6237;
double atom2772;
double atom2775;
double atom6205;
double atom1512;
double atom1533;
double atom1515;
double atom1551;
double atom1548;
double atom1574;
double atom1530;
double atom2826;
double atom2827;
double atom2828;
double atom2895;
double atom2829;
double atom2830;
double atom2897;
double atom2943;
double atom2798;
double atom2944;
double atom1571;
double atom2816;
double atom6098;
double atom6103;
double atom6105;
double atom8957;
double atom2782;
double atom2785;
double atom2899;
double atom2898;
double atom2932;
double atom2933;
double atom2934;
double atom2935;
double atom6151;
double atom6155;
double atom6156;
double atom6159;
double atom6165;
double atom6168;
double atom6232;
double atom6249;
double atom6235;
double atom6256;
double atom9152;
double atom9155;
double atom9153;
double atom2978;
double atom2977;
double atom2984;
double atom2985;
double atom2986;
double atom2987;
double atom3084;
double atom3086;
double atom3087;
double atom3089;
double atom3091;
double atom3093;
double atom3098;
double atom3101;
double atom3104;
double atom3107;
double atom3095;
double atom3110;
double atom3112;
double atom3123;
double atom3124;
double atom3127;
double atom3121;
double atom3130;
double atom3131;
double atom3134;
double atom3136;
double atom3135;
double atom3113;
double atom3137;
double atom3138;
double atom3139;
double atom3114;
double atom3141;
double atom3143;
double atom3145;
double atom3181;
double atom3189;
double atom3046;
double atom3191;
double atom3190;
double atom3043;
double atom3051;
double atom3053;
double atom3054;
double atom3057;
double atom3059;
double atom3063;
double atom6503;
double atom6500;
double atom6567;
double atom6568;
double atom6564;
double atom6504;
double atom6569;
double atom6598;
double atom6639;
double atom6586;
double atom6585;
double atom6593;
double atom6597;
double atom6613;
double atom6626;
double atom6562;
double atom6505;
double atom6499;
double atom6506;
double atom6507;
double atom6511;
double atom6515;
double atom6581;
double atom6576;
double atom6516;
double atom6512;
double atom9216;
double atom3028;
double atom3031;
double atom2988;
double atom2993;
double atom2991;
double atom3004;
double atom3003;
double atom2997;
double atom3197;
double atom6617;
double atom3023;
double atom3026;
double atom3077;
double atom3078;
double atom3079;
double atom3080;
double atom3146;
double atom3081;
double atom3148;
double atom3194;
double atom3049;
double atom3195;
double atom3067;
double atom6473;
double atom6469;
double atom9263;
double atom3033;
double atom3036;
double atom6532;
double atom3149;
double atom3150;
double atom3183;
double atom3184;
double atom3185;
double atom3186;
double atom6519;
double atom6523;
double atom6524;
double atom6536;
double atom6541;
double atom6525;
double atom6584;
double atom6620;
double atom6637;
double atom6630;
double atom9458;
double atom9459;
double atom9461;
double atom3340;
double atom3341;
double atom3339;
double atom3353;
double atom3342;
double atom3344;
double atom3356;
double atom3346;
double atom3359;
double atom3348;
double atom3362;
double atom3350;
double atom3365;
double atom3367;
double atom3368;
double atom3377;
double atom3378;
double atom3381;
double atom3383;
double atom3385;
double atom3387;
double atom3369;
double atom3389;
double atom3391;
double atom3390;
double atom3393;
double atom3392;
double atom3394;
double atom3395;
double atom3398;
double atom3400;
double atom3436;
double atom3444;
double atom3229;
double atom3230;
double atom3231;
double atom3233;
double atom3237;
double atom3235;
double atom3238;
double atom3228;
double atom684;
double atom683;
double atom3236;
double atom1604;
double atom3446;
double atom3302;
double atom1598;
double atom3299;
double atom3445;
double atom3306;
double atom3308;
double atom3311;
double atom1595;
double atom3309;
double atom3314;
double atom1601;
double atom3318;
double atom6969;
double atom6959;
double atom6971;
double atom7036;
double atom6983;
double atom7041;
double atom6972;
double atom7045;
double atom6965;
double atom6974;
double atom7046;
double atom7034;
double atom7039;
double atom6964;
double atom6975;
double atom7047;
double atom6976;
double atom7048;
double atom7050;
double atom7053;
double atom7049;
double atom7061;
double atom7076;
double atom7123;
double atom6977;
double atom6989;
double atom6978;
double atom6991;
double atom6993;
double atom7002;
double atom6994;
double atom7003;
double atom7094;
double atom6984;
double atom7089;
double atom7102;
double atom9522;
double atom3239;
double atom3249;
double atom3240;
double atom3241;
double atom3253;
double atom3246;
double atom3248;
double atom3242;
double atom3245;
double atom3260;
double atom3259;
double atom3284;
double atom3287;
double atom3452;
double atom7115;
double atom3279;
double atom3282;
double atom7080;
double atom3332;
double atom3333;
double atom3334;
double atom3401;
double atom3335;
double atom3336;
double atom3403;
double atom3449;
double atom1610;
double atom3450;
double atom3305;
double atom1607;
double atom3322;
double atom3289;
double atom3292;
double atom6998;
double atom6999;
double atom7008;
double atom9569;
double atom7020;
double atom3404;
double atom3405;
double atom3438;
double atom3440;
double atom3439;
double atom3441;
double atom7006;
double atom7012;
double atom7013;
double atom7030;
double atom7024;
double atom7105;
double atom7108;
double atom7113;
double atom7127;
double atom9764;
double atom9765;
double atom9767;
double atom3484;
double atom3485;
double atom3486;
double atom3488;
double atom3492;
double atom3490;
double atom3493;
double atom3483;
double atom3491;
double atom3590;
double atom3589;
double atom3591;
double atom3592;
double atom3594;
double atom3596;
double atom3598;
double atom3600;
double atom3603;
double atom3606;
double atom3609;
double atom3612;
double atom3615;
double atom3617;
double atom3618;
double atom3628;
double atom3629;
double atom3632;
double atom3634;
double atom3636;
double atom3626;
double atom3639;
double atom3640;
double atom3641;
double atom3643;
double atom3642;
double atom3644;
double atom3650;
double atom3619;
double atom3645;
double atom3648;
double atom3686;
double atom3694;
double atom3552;
double atom3696;
double atom3549;
double atom3695;
double atom3556;
double atom3558;
double atom3561;
double atom3559;
double atom3564;
double atom3568;
double atom3494;
double atom3499;
double atom3497;
double atom3510;
double atom3509;
double atom3503;
double atom3529;
double atom3532;
double atom7367;
double atom7364;
double atom7368;
double atom7358;
double atom7351;
double atom7361;
double atom7363;
double atom7369;
double atom7379;
double atom7380;
double atom7383;
double atom7385;
double atom7389;
double atom7386;
double atom7390;
double atom7373;
double atom7421;
double atom7431;
double atom7437;
double atom7436;
double atom7438;
double atom7374;
double atom7433;
double atom7449;
double atom7444;
double atom9828;
double atom7456;
double atom7455;
double atom7454;
double atom7466;
double atom7453;
double atom7481;
double atom7485;
double atom7491;
double atom3534;
double atom3537;
double atom7499;
double atom3702;
double atom3582;
double atom3583;
double atom3584;
double atom3651;
double atom3585;
double atom3586;
double atom3653;
double atom3699;
double atom3700;
double atom3555;
double atom3572;
double atom7402;
double atom7345;
double atom7347;
double atom9875;
double atom3539;
double atom3542;
double atom3654;
double atom3655;
double atom3688;
double atom3690;
double atom3689;
double atom3691;
double atom7393;
double atom7397;
double atom7398;
double atom7406;
double atom7412;
double atom7415;
double atom7452;
double atom7489;
double atom7503;
double atom7510;
double atom10070;
double atom10071;
double atom10073;
double atom7832;
double atom8138;
double atom8444;
double atom8750;
double atom9056;
double atom9362;
double atom9668;
double atom9974;

double * _dPhit_ds = NULL;
void Init_dPhit_ds ( ) 
{
    _dPhit_ds = malloc ( dPhit_ds_n_rows * dPhit_ds_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhit_ds_n_rows * dPhit_ds_n_cols ; i++ ) {_dPhit_ds[i]=0.0;}
  }
}

void Done_dPhit_ds ( ) 
{
if (_dPhit_ds != NULL) 
free (_dPhit_ds ); 
_dPhit_ds = NULL; 
}


double * dPhit_ds ()
{
if ( _dPhit_ds == NULL )
 {
    _dPhit_ds = malloc ( dPhit_ds_n_rows * dPhit_ds_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhit_ds_n_rows * dPhit_ds_n_cols ; i++ ) {_dPhit_ds[i]=0.0;}
  }
 }

atom1175 = sin(aWAG);
atom1177 = sin(cWAG);
atom1172 = cos(bWAG);
atom1179 = atom1175*atom1177;
atom1176 = cos(cWAG);
atom1173 = sin(bWAG);
atom864 = cos(bRBOG);
atom1187 =  atom1172*atom1179+atom1176*atom1173;
atom1209 = cos(cRSLD);
atom1184 =  atom1172*atom1176-atom1173*atom1179;
atom1174 = cos(aWAG);
atom1178 = -atom1177*atom1174;
atom1210 = sin(cRSLD);
atom1213 =  atom1209*atom1184+atom1178*atom1210;
atom865 = sin(bRBOG);
atom862 = cos(aRBOG);
atom1234 =  atom1213*atom865+atom864*atom1187;
atom863 = sin(aRBOG);
atom1216 = -atom1184*atom1210+atom1209*atom1178;
atom1252 =  atom862*atom1234-atom863*atom1216;
atom30 = cos(aRWHSF);
atom1249 =  atom863*atom1234+atom862*atom1216;
atom31 = sin(aRWHSF);
atom1704 =  uW_RFR-lW_RFR;
atom1710 =  ( ( bW_RFR+aW_RFR*atom1704)*atom1704+cW_RFR)*atom1704+dW_RFR;
atom1703 = sin(thetaW_RFR);
atom1276 =  atom1252*atom30-atom1249*atom31;
atom1711 = -atom1710*atom1703;
atom1712 = cos(thetaW_RFR);
atom1231 =  atom1213*atom864-atom1187*atom865;
atom1713 = atom1710*atom1712;
atom1817 =  RFRstas-RFRends;
atom1819 =  RFRstas-xR_RFR;
atom1818 = 1.0/(atom1817);
atom1831 = -RFRas*atom1818;
atom1820 = atom1819*atom1818;
atom1822 =  atom1820*RFRas+RFRbs;
atom1834 = -atom1822*atom1818+atom1831*atom1820;
atom1824 =  atom1820*atom1822+RFRcs;
atom1837 = -atom1818*atom1824+atom1820*atom1834;
atom1826 =  RFRds+atom1820*atom1824;
atom1840 =  atom1820*atom1837-atom1818*atom1826;
atom1828 =  atom1820*atom1826+RFRes;
atom1855 = -2.0*atom1831*atom1818;
atom1857 = -atom1834*atom1818;
atom1859 =  2.0*atom1857+atom1820*atom1855;
atom1860 = -atom1818*atom1837;
atom1863 =  2.0*atom1860+atom1820*atom1859;
atom1864 = -atom1818*atom1840;
atom1843 =  atom1820*atom1840-atom1818*atom1828;
atom1867 =  2.0*atom1864+atom1863*atom1820;
atom1845 =  (atom1843*atom1843)+1.0;
atom1868 = 2.0*atom1843*atom1867;
atom1869 = pow(atom1845,-(1.0/2.0));
atom1846 = pow(atom1845,(1.0/2.0));
atom1870 = (1.0/2.0)*atom1868*atom1869;
atom1871 = 1.0/(atom1846*atom1846);
atom1872 = -atom1870*atom1871;
atom1847 = 1.0/(atom1846);
atom1873 = 5.0000000000000000e-01*atom1867*L_RAIL*atom1847;
atom1876 =  5.0000000000000000e-01*atom1872*atom1843*L_RAIL+atom1873+1.0;
atom1878 =  -5.0000000000000000e-01*atom1872*L_RAIL+atom1843;
atom1914 = (atom1876*atom1876);
atom1922 = pow( atom1914+(atom1878*atom1878),-(1.0/2.0));
atom1776 =  atom1276*atom1711-atom1231*atom1713;
atom1923 = atom1922*atom1876;
atom1181 = -atom1175*atom1176;
atom1193 =  atom1177*atom1173+atom1172*atom1181;
atom1180 = atom1176*atom1174;
atom1190 = -atom1181*atom1173+atom1172*atom1177;
atom1219 =  atom1180*atom1210+atom1190*atom1209;
atom1237 =  atom864*atom1219-atom1193*atom865;
atom1240 =  atom1219*atom865+atom1193*atom864;
atom1222 =  atom1180*atom1209-atom1190*atom1210;
atom1258 = -atom863*atom1222+atom862*atom1240;
atom1255 =  atom862*atom1222+atom863*atom1240;
atom1282 =  atom1258*atom30-atom1255*atom31;
atom1924 = atom1922*atom1878;
atom1779 =  atom1711*atom1282-atom1237*atom1713;
atom1784 =  bW_RFR+2.0*aW_RFR*atom1704;
atom1786 =  ( bW_RFR+aW_RFR*atom1704)*atom1704+atom1784*atom1704+cW_RFR;
atom1787 = atom1786*atom1712;
atom1789 = -atom1786*atom1703;
atom1273 =  atom1252*atom31+atom30*atom1249;
atom1792 =  atom1276*atom1787+atom1789*atom1231+atom1273;
atom1279 =  atom1258*atom31+atom1255*atom30;
atom1796 =  atom1789*atom1237+atom1282*atom1787+atom1279;
atom4203 =  atom1819*RFRas*atom1818+RFRbs;
atom4205 =  RFRcs+atom4203*atom1819*atom1818;
atom4207 =  RFRds+atom1819*atom4205*atom1818;
atom4213 = -atom1819*RFRas/(atom1817*atom1817)-atom4203*atom1818;
atom4215 = -atom4205*atom1818+atom1819*atom4213*atom1818;
atom4217 =  atom1819*atom1818*atom4215-atom1818*atom4207;
atom4221 = -atom1818*( atom1819*atom1818*atom4207+RFRes);
atom4218 = atom1819*atom4217*atom1818;
atom4247 =  -5.0000000000000000e-01*( atom4221+atom4218)*pow( pow( atom4221+atom4218,2.0)+1.0,-(3.0/2.0))*( ( 2.0*(-( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+( 2.0*(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)+-2.0000000000000000e+00*RFRas/pow( RFRstas-RFRends,3.0)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR)+2.0*(-( ( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRds)/( RFRstas-RFRends)+(-( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends))*L_RAIL+atom4221+atom4218;
atom4222 =  atom4221+atom4218;
atom4223 = (atom4222*atom4222);
atom4224 =  atom4223+1.0;
atom4230 =  -2.0000000000000000e+00*atom1819*RFRas/(atom1817*atom1817*atom1817)+2.0*atom4213*atom1818;
atom4232 =  2.0*atom1818*atom4215+atom1819*atom4230*atom1818;
atom4237 = pow(atom4224,-(1.0/2.0));
atom4235 =  2.0*atom4217*atom1818+atom4232*atom1819*atom1818;
atom4225 = pow(atom4224,-(3.0/2.0));
atom4239 =  -5.0000000000000000e-01*atom4237*atom4235*L_RAIL+5.0000000000000000e-01*atom4235*atom4225*atom4223*L_RAIL+1.0;
atom4248 = (atom4247*atom4247);
atom4240 = (atom4239*atom4239);
atom4297 =  atom1819*atom1818*( (-atom1818*( atom1819*RFRas*atom1818+RFRbs)-atom1819*RFRas*(atom1818*atom1818))*atom1818-( atom1818*( atom1819*RFRas*atom1818+RFRbs)+atom1819*RFRas*(atom1818*atom1818))*atom1818+-2.0000000000000000e+00*atom1819*RFRas*(atom1818*atom1818*atom1818))+atom1818*atom4215-( ( ( RFRas*atom1818*( RFRstas-xR_RFR)+RFRbs)*atom1818+RFRas*(atom1818*atom1818)*( RFRstas-xR_RFR))*atom1818*( RFRstas-xR_RFR)+( RFRcs+( RFRas*atom1818*( RFRstas-xR_RFR)+RFRbs)*atom1818*( RFRstas-xR_RFR))*atom1818)*atom1818;
atom4324 =  atom1819*( atom4230*atom1818+-6.0000000000000000e+00*atom1819*RFRas/((atom1817*atom1817)*(atom1817*atom1817))+2.0*atom1818*( -2.0000000000000000e+00*RFRas*(atom1818*atom1818*atom1818)*( RFRstas-xR_RFR)+(-( RFRas*atom1818*( RFRstas-xR_RFR)+RFRbs)*atom1818-RFRas*(atom1818*atom1818)*( RFRstas-xR_RFR))*atom1818-( ( RFRas*atom1818*( RFRstas-xR_RFR)+RFRbs)*atom1818+RFRas*(atom1818*atom1818)*( RFRstas-xR_RFR))*atom1818))*atom1818+atom4232*atom1818+2.0*atom4297*atom1818;
atom4301 = -( atom1818*( ( RFRcs+( RFRas*atom1818*( RFRstas-xR_RFR)+RFRbs)*atom1818*( RFRstas-xR_RFR))*atom1818*( RFRstas-xR_RFR)+RFRds)+( ( ( RFRas*atom1818*( RFRstas-xR_RFR)+RFRbs)*atom1818+RFRas*(atom1818*atom1818)*( RFRstas-xR_RFR))*atom1818*( RFRstas-xR_RFR)+( RFRcs+( RFRas*atom1818*( RFRstas-xR_RFR)+RFRbs)*atom1818*( RFRstas-xR_RFR))*atom1818)*atom1818*( RFRstas-xR_RFR))*atom1818;
atom4302 = atom4217*atom1818;
atom4298 = atom4297*atom1819*atom1818;
atom4328 = pow(atom4224,-(5.0/2.0));
atom4303 =  atom4301+atom4302+atom4298;
atom4336 =  5.0000000000000000e-01*atom4222*atom4225*L_RAIL*atom4324-atom4301+-1.5000000000000000e+00*atom4328*atom4303*atom4235*atom4223*L_RAIL+5.0000000000000000e-01*pow( pow( (-( ( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRds)/( RFRstas-RFRends)+(-( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR)-( RFRes+( ( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRds)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends),2.0)+1.0,-(3.0/2.0))*( atom4301+( (-( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+1.0/( RFRstas-RFRends)*( RFRstas-xR_RFR)*( (-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)-( RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)+-2.0000000000000000e+00*RFRas/pow( RFRstas-RFRends,3.0)*( RFRstas-xR_RFR))-1.0/( RFRstas-RFRends)*( ( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+( RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)*( RFRstas-xR_RFR)))/( RFRstas-RFRends)*( RFRstas-xR_RFR)+(-( ( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRds)/( RFRstas-RFRends)+(-( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends))*( ( 2.0*(-( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+( 2.0*(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)+-2.0000000000000000e+00*RFRas/pow( RFRstas-RFRends,3.0)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR)+2.0*(-( ( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRds)/( RFRstas-RFRends)+(-( RFRcs+( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)+(-RFRas/pow( RFRstas-RFRends,2.0)*( RFRstas-xR_RFR)-( RFRas/( RFRstas-RFRends)*( RFRstas-xR_RFR)+RFRbs)/( RFRstas-RFRends))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends)*( RFRstas-xR_RFR))/( RFRstas-RFRends))*L_RAIL-atom4302-atom4298;
atom4331 =  -1.5000000000000000e+00*atom4222*atom4303*atom4235*atom4225*L_RAIL+1.5000000000000000e+00*atom4328*(atom4222*atom4222*atom4222)*atom4303*atom4235*L_RAIL+-5.0000000000000000e-01*atom4225*atom4223*L_RAIL*atom4324+5.0000000000000000e-01*atom4237*L_RAIL*atom4324;
atom4338 = atom4239*atom4331;
atom7686 = -( atom4247*atom4336+atom4338)*pow( atom4248+atom4240,-(3.0/2.0));
atom4304 = atom4222*atom4303*atom4225;
atom4277 = -atom1818*atom1855;
atom4276 = -atom1818*atom1859;
atom4275 = -atom1863*atom1818;
atom4287 =  3.0*atom1820*( atom4276+atom1820*atom4277)+3.0*atom4275;
atom4312 = -atom1871*( ( 2.0*atom1843*atom4287+2.0*(atom1867*atom1867))*atom1869+atom1868*atom4304)/2.0+-2.0*atom4222/(atom4224*atom4224)*atom4303*atom1870;
atom4314 =  atom1867+-5.0000000000000000e-01*atom4312*L_RAIL;
atom1761 = atom1711*atom1237;
atom1764 = atom1282*atom1713;
atom1702 = -5.0000000000000000e-01*L_WHS;
atom868 = atom863*atom864;
atom1714 = atom30*atom1702;
atom1726 = atom868*atom1714;
atom1725 = -L_OBOG_OWHS*atom865;
atom1715 = atom1702*atom31;
atom1716 =  atom1715+zRWHSF;
atom869 = atom862*atom864;
atom1730 =  atom1716*atom869+zRBOG+atom1726+atom1725;
atom867 = atom862*atom865;
atom866 = atom863*atom865;
atom1717 = L_OBOG_OWHS*atom864;
atom1718 = atom866*atom1714;
atom1721 =  atom1717+atom867*atom1716+atom1718;
atom1722 = atom862*atom1714;
atom1724 = -atom863*atom1716+atom1722;
atom1736 =  atom1721*atom1210+atom1724*atom1209;
atom0 = -(1.0/2.0)*L_WAG;
atom1737 =  atom0-atom1724*atom1210+atom1721*atom1209;
atom1930 = -atom1820*atom1828+atom1180*atom1736+uW_RFR*atom1279+5.0000000000000000e-01*L_RAIL*atom1847+atom1761-uR_RFR+atom1190*atom1737+yWAG+atom1730*atom1193+atom1764-RFRfs;
atom4362 =  atom1843+-5.0000000000000000e-01*atom4304*L_RAIL;
atom4356 =  5.0000000000000000e-01*atom4304*atom1867*L_RAIL+5.0000000000000000e-01*atom1843*atom4312*L_RAIL+5.0000000000000000e-01*atom1872*atom1867*L_RAIL+5.0000000000000000e-01*atom4287*L_RAIL*atom1847;
atom1756 = atom1231*atom1711;
atom1759 = atom1276*atom1713;
atom1810 =  uR_RFR-lR_RFR;
atom1811 = aR_RFR*atom1810;
atom1812 =  atom1811+bR_RFR;
atom1879 =  atom1812+atom1811;
atom1813 = atom1812*atom1810;
atom1814 =  atom1813+cR_RFR;
atom1881 =  atom1879*atom1810+atom1814;
atom1927 = pow( (atom1881*atom1881)+1.0,-(1.0/2.0));
atom1195 = atom1172*atom1174;
atom1194 = -atom1173*atom1174;
atom1225 =  atom1194*atom1209+atom1175*atom1210;
atom1246 =  atom1195*atom864+atom1225*atom865;
atom1228 =  atom1175*atom1209-atom1194*atom1210;
atom1264 =  atom862*atom1246-atom863*atom1228;
atom1261 =  atom862*atom1228+atom863*atom1246;
atom1288 = -atom1261*atom31+atom30*atom1264;
atom1243 =  atom1225*atom864-atom1195*atom865;
atom1928 = atom1881*atom1927;
atom1782 = -atom1243*atom1713+atom1288*atom1711;
atom1285 =  atom30*atom1261+atom1264*atom31;
atom1800 =  atom1789*atom1243+atom1288*atom1787+atom1285;
atom4244 =  atom1813+atom1810*( 2.0*aR_RFR*atom1810+bR_RFR)+cR_RFR;
atom4245 = (atom4244*atom4244);
atom4254 =  3.0*aR_RFR*atom1810+bR_RFR;
atom7733 = -2.0*atom4254*pow( atom4245+1.0,-(3.0/2.0))*atom4244;
atom1766 = atom1243*atom1711;
atom1769 = atom1288*atom1713;
atom4200 =  2.0*aR_RFR*atom1810+2.0*atom1879;
atom1882 = atom1881*atom1878;
atom1883 = -atom1876*atom1881;
atom1916 = pow( atom1914+(atom1882*atom1882)+(atom1883*atom1883),-(1.0/2.0));
atom1919 = atom1876*atom1916;
atom1917 = atom1882*atom1916;
atom1918 = atom1916*atom1883;
atom4252 = pow( pow( cR_RFR+( aR_RFR*( uR_RFR-lR_RFR)+bR_RFR)*( uR_RFR-lR_RFR)+( uR_RFR-lR_RFR)*( 2.0*aR_RFR*( uR_RFR-lR_RFR)+bR_RFR),2.0)*atom4240+atom4248*atom4245+atom4240,-(3.0/2.0));
atom4258 = -2.0*atom4252*( atom4248*atom4254*atom4244+atom4254*atom4240*atom4244);
atom4266 = -atom4200*atom1876*atom1916+atom4258*atom1883;
atom4261 =  atom1882*atom4258+atom4200*atom1916*atom1878;
atom4270 = atom4258*atom1876;
atom4340 = -atom4252*( atom4247*atom4336*atom4245+atom4245*atom4239*atom4331+atom4338);
atom4360 =  atom4340*atom1883-atom4356*atom1881*atom1916;
atom4343 =  atom1882*atom4340+atom4314*atom1881*atom1916;
atom4369 =  atom4340*atom1876+atom4356*atom1916;
atom7928 =  2.0*atom1784+2.0000000000000000e+00*aW_RFR*atom1704;
atom7931 = atom7928*atom1712;
atom7929 = -atom7928*atom1703;
atom2068 =  RFLstas-RFLends;
atom2069 = 1.0/(atom2068);
atom2070 =  RFLstas-xR_RFL;
atom2071 = atom2069*atom2070;
atom2073 =  atom2071*RFLas+RFLbs;
atom2075 =  RFLcs+atom2071*atom2073;
atom2077 =  atom2071*atom2075+RFLds;
atom2079 =  atom2071*atom2077+RFLes;
atom2082 = -atom2069*RFLas;
atom2085 =  atom2082*atom2071-atom2073*atom2069;
atom2088 = -atom2069*atom2075+atom2071*atom2085;
atom2091 =  atom2071*atom2088-atom2069*atom2077;
atom2094 =  atom2071*atom2091-atom2069*atom2079;
atom2096 =  (atom2094*atom2094)+1.0;
atom2097 = pow(atom2096,(1.0/2.0));
atom2107 = -2.0000000000000000e+00*atom2082*atom2069;
atom2108 = -atom2085*atom2069;
atom2111 =  2.0*atom2108+atom2071*atom2107;
atom2112 = -atom2069*atom2088;
atom2115 =  2.0*atom2112+atom2071*atom2111;
atom2105 = -atom2069*atom2091;
atom2098 = 1.0/(atom2097);
atom2118 =  2.0*atom2105+atom2071*atom2115;
atom2119 = 2.0*atom2094*atom2118;
atom2120 = pow(atom2096,-(1.0/2.0));
atom2121 = (1.0/2.0)*atom2119*atom2120;
atom2122 = 1.0/(atom2097*atom2097);
atom2123 = -atom2121*atom2122;
atom2125 = -5.0000000000000000e-01*atom2098*atom2118*L_RAIL;
atom2127 =  atom2125+-5.0000000000000000e-01*atom2094*atom2123*L_RAIL+1.0;
atom2129 =  atom2094+5.0000000000000000e-01*atom2123*L_RAIL;
atom2165 = (atom2127*atom2127);
atom2173 = pow( (atom2129*atom2129)+atom2165,-(1.0/2.0));
atom1962 =  uW_RFL-lW_RFL;
atom1966 =  cW_RFL+( aW_RFL*atom1962+bW_RFL)*atom1962;
atom1968 =  dW_RFL+atom1966*atom1962;
atom1970 = cos(thetaW_RFL);
atom1971 = atom1968*atom1970;
atom1961 = sin(thetaW_RFL);
atom1969 = -atom1968*atom1961;
atom2174 = atom2127*atom2173;
atom2027 =  atom1276*atom1969-atom1231*atom1971;
atom2030 =  atom1969*atom1282-atom1237*atom1971;
atom2175 = atom2129*atom2173;
atom2035 =  2.0*aW_RFL*atom1962+bW_RFL;
atom2037 =  atom1966+atom2035*atom1962;
atom2041 = atom1970*atom2037;
atom2038 = -atom2037*atom1961;
atom2047 =  atom2038*atom1237+atom2041*atom1282+atom1279;
atom2043 =  atom1273+atom1231*atom2038+atom2041*atom1276;
atom4589 = -atom2069*( ( ( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069*( RFLstas-xR_RFL)+RFLds)*atom2069*( RFLstas-xR_RFL)+RFLes);
atom4600 = ( atom2069*atom2070*( (-( atom2069*RFLas*atom2070+RFLbs)*atom2069-(atom2069*atom2069)*RFLas*atom2070)*atom2069*atom2070-( RFLcs+( atom2069*RFLas*atom2070+RFLbs)*atom2069*atom2070)*atom2069)-( ( RFLcs+( atom2069*RFLas*atom2070+RFLbs)*atom2069*atom2070)*atom2069*atom2070+RFLds)*atom2069)*atom2069*atom2070;
atom4679 = atom2069*(-( ( ( atom2069*RFLas*atom2070+RFLbs)*atom2069+(atom2069*atom2069)*RFLas*atom2070)*atom2069*atom2070+( RFLcs+( atom2069*RFLas*atom2070+RFLbs)*atom2069*atom2070)*atom2069)*atom2069+atom2069*( (-( atom2069*RFLas*atom2070+RFLbs)*atom2069-(atom2069*atom2069)*RFLas*atom2070)*atom2069*atom2070-( RFLcs+( atom2069*RFLas*atom2070+RFLbs)*atom2069*atom2070)*atom2069)+( -2.0000000000000000e+00*(atom2069*atom2069*atom2069)*RFLas*atom2070+(-( atom2069*RFLas*atom2070+RFLbs)*atom2069-(atom2069*atom2069)*RFLas*atom2070)*atom2069-( ( atom2069*RFLas*atom2070+RFLbs)*atom2069+(atom2069*atom2069)*RFLas*atom2070)*atom2069)*atom2069*atom2070)*atom2070;
atom4682 = -( ( ( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069*( RFLstas-xR_RFL)+RFLds)*atom2069+( ( (atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))*atom2069*( RFLstas-xR_RFL)+( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069)*atom2069*( RFLstas-xR_RFL))*atom2069;
atom4683 = atom2069*(-( ( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069*( RFLstas-xR_RFL)+RFLds)*atom2069+(-( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069+atom2069*(-(atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))*atom2069*( RFLstas-xR_RFL));
atom4601 =  atom4589+atom4600;
atom4602 = (atom4601*atom4601);
atom4603 =  atom4602+1.0;
atom4684 =  atom4679+atom4682+atom4683;
atom4616 = pow(atom4603,-(3.0/2.0));
atom4700 = atom4601*atom4684*atom4616;
atom4703 = -atom2069*atom2107;
atom4702 = -atom2069*atom2111;
atom4701 = -atom2115*atom2069;
atom4713 =  3.0*atom2071*( atom4702+atom4703*atom2071)+3.0*atom4701;
atom4728 = -( atom2119*atom4700+( 2.0*atom2094*atom4713+2.0*(atom2118*atom2118))*atom2120)*atom2122/2.0+-2.0*atom4601/(atom4603*atom4603)*atom4684*atom2121;
atom4732 =  -5.0000000000000000e-01*atom4700*atom2118*L_RAIL+-5.0000000000000000e-01*atom2123*atom2118*L_RAIL+-5.0000000000000000e-01*atom2098*L_RAIL*atom4713+-5.0000000000000000e-01*atom2094*atom4728*L_RAIL;
atom4614 =  2.0000000000000000e+00*atom2069*(-( ( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069*( RFLstas-xR_RFL)+RFLds)*atom2069+(-( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069+atom2069*(-(atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))*atom2069*( RFLstas-xR_RFL))+( atom2069*( -2.0000000000000000e+00*(atom2069*atom2069*atom2069)*RFLas*atom2070+2.0*(-( atom2069*RFLas*atom2070+RFLbs)*atom2069-(atom2069*atom2069)*RFLas*atom2070)*atom2069)*atom2070+2.0*atom2069*( (-( atom2069*RFLas*atom2070+RFLbs)*atom2069-(atom2069*atom2069)*RFLas*atom2070)*atom2069*atom2070-( RFLcs+( atom2069*RFLas*atom2070+RFLbs)*atom2069*atom2070)*atom2069))*atom2069*atom2070;
atom4604 = pow(atom4603,-(1.0/2.0));
atom4677 =  ( 2.0*(-( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069+atom2069*(-(atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))*atom2069+atom2069*( RFLstas-xR_RFL)*( -2.0000000000000000e+00*(atom2069*atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas+2.0*atom2069*(-(atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))))*atom2069+2.0000000000000000e+00*( (-( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069+atom2069*(-(atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))*atom2069+( -2.0000000000000000e+00*(atom2069*atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-( (atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))*atom2069+atom2069*(-(atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)))*atom2069*( RFLstas-xR_RFL)-( ( (atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))*atom2069*( RFLstas-xR_RFL)+( RFLcs+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)*( RFLstas-xR_RFL))*atom2069)*atom2069)*atom2069+atom2069*( 2.0*( -2.0000000000000000e+00*1.0/(atom2068*atom2068*atom2068)*RFLas*atom2070-( (atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas+atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs))*atom2069+atom2069*(-(atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)))*atom2069+atom2069*( -2.0000000000000000e+00*(atom2069*atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas+2.0*atom2069*(-(atom2069*atom2069)*( RFLstas-xR_RFL)*RFLas-atom2069*( atom2069*( RFLstas-xR_RFL)*RFLas+RFLbs)))+-6.0000000000000000e+00*1.0/((atom2068*atom2068)*(atom2068*atom2068))*RFLas*atom2070)*atom2070;
atom4618 =  5.0000000000000000e-01*atom4614*atom4604*L_RAIL+-5.0000000000000000e-01*atom4616*atom4614*atom4602*L_RAIL+1.0;
atom4695 =  atom4679+atom4682+5.0000000000000000e-01*( atom4679+atom4682+atom4683)*( 1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( 2.0*1.0/( RFLstas-RFLends)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))+-2.0000000000000000e+00*1.0/pow( RFLstas-RFLends,3.0)*( RFLstas-xR_RFL)*RFLas)*( RFLstas-xR_RFL)+2.0*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))-1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))/( RFLstas-RFLends))*( RFLstas-xR_RFL)+2.0000000000000000e+00*atom4683)*L_RAIL*pow( pow(-1.0/( RFLstas-RFLends)*( ( RFLds+1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))/( RFLstas-RFLends)*( RFLstas-xR_RFL)+RFLes)+( RFLstas-xR_RFL)*atom4683,2.0)+1.0,-(3.0/2.0))+atom4683+5.0000000000000000e-01*(-1.0/( RFLstas-RFLends)*( ( RFLds+1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))/( RFLstas-RFLends)*( RFLstas-xR_RFL)+RFLes)+( RFLstas-xR_RFL)*atom4683)*( ( 2.0*( 1.0/( RFLstas-RFLends)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))+-2.0000000000000000e+00*1.0/pow( RFLstas-RFLends,3.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas+1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))/( RFLstas-RFLends)+-6.0000000000000000e+00*1.0/pow( RFLstas-RFLends,4.0)*( RFLstas-xR_RFL)*RFLas+1.0/( RFLstas-RFLends)*( 2.0*1.0/( RFLstas-RFLends)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))+-2.0000000000000000e+00*1.0/pow( RFLstas-RFLends,3.0)*( RFLstas-xR_RFL)*RFLas))/( RFLstas-RFLends)*( RFLstas-xR_RFL)+1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( 2.0*1.0/( RFLstas-RFLends)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))+-2.0000000000000000e+00*1.0/pow( RFLstas-RFLends,3.0)*( RFLstas-xR_RFL)*RFLas)*( RFLstas-xR_RFL)+2.0*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))-1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))/( RFLstas-RFLends))+2.0000000000000000e+00*1.0/( RFLstas-RFLends)*( ( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))-1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))/( RFLstas-RFLends)+( 1.0/( RFLstas-RFLends)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))+-2.0000000000000000e+00*1.0/pow( RFLstas-RFLends,3.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas+1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))/( RFLstas-RFLends)*( RFLstas-xR_RFL)-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas+1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))+1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))))*L_RAIL*pow( pow(-1.0/( RFLstas-RFLends)*( ( RFLds+1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))/( RFLstas-RFLends)*( RFLstas-xR_RFL)+RFLes)+( RFLstas-xR_RFL)*atom4683,2.0)+1.0,-(3.0/2.0))+-1.5000000000000000e+00*pow(-1.0/( RFLstas-RFLends)*( ( RFLds+1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))/( RFLstas-RFLends)*( RFLstas-xR_RFL)+RFLes)+( RFLstas-xR_RFL)*atom4683,2.0)*( atom4679+atom4682+atom4683)*( 1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( 2.0*1.0/( RFLstas-RFLends)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))+-2.0000000000000000e+00*1.0/pow( RFLstas-RFLends,3.0)*( RFLstas-xR_RFL)*RFLas)*( RFLstas-xR_RFL)+2.0*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))-1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))/( RFLstas-RFLends))*( RFLstas-xR_RFL)+2.0000000000000000e+00*atom4683)*L_RAIL*pow( pow(-1.0/( RFLstas-RFLends)*( ( RFLds+1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))/( RFLstas-RFLends)*( RFLstas-xR_RFL)+RFLes)+( RFLstas-xR_RFL)*atom4683,2.0)+1.0,-(5.0/2.0));
atom4628 =  atom4589+5.0000000000000000e-01*pow( pow( atom4589+atom4600,2.0)+1.0,-(3.0/2.0))*( 1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( 2.0*1.0/( RFLstas-RFLends)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))+-2.0000000000000000e+00*1.0/pow( RFLstas-RFLends,3.0)*( RFLstas-xR_RFL)*RFLas)*( RFLstas-xR_RFL)+2.0*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))-1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))/( RFLstas-RFLends))*( RFLstas-xR_RFL)+2.0000000000000000e+00*1.0/( RFLstas-RFLends)*(-( RFLds+1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))*( RFLstas-xR_RFL))/( RFLstas-RFLends)+( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*(-1.0/pow( RFLstas-RFLends,2.0)*( RFLstas-xR_RFL)*RFLas-1.0/( RFLstas-RFLends)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs))-1.0/( RFLstas-RFLends)*( RFLcs+1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*( 1.0/( RFLstas-RFLends)*( RFLstas-xR_RFL)*RFLas+RFLbs)))/( RFLstas-RFLends)*( RFLstas-xR_RFL)))*L_RAIL*( atom4589+atom4600)+atom4600;
atom4691 = atom4618*( 5.0000000000000000e-01*atom4616*atom4602*atom4677*L_RAIL+-1.5000000000000000e+00*(atom4601*atom4601*atom4601)*pow(atom4603,-(5.0/2.0))*atom4684*atom4614*L_RAIL+-5.0000000000000000e-01*atom4604*atom4677*L_RAIL+1.5000000000000000e+00*atom4601*atom4684*atom4616*atom4614*L_RAIL);
atom4629 = (atom4628*atom4628);
atom4619 = (atom4618*atom4618);
atom7992 = -pow( atom4629+atom4619,-(3.0/2.0))*( atom4691-atom4695*atom4628);
atom2007 = atom1231*atom1969;
atom2010 = atom1276*atom1971;
atom1972 = -atom1715+zRWHSF;
atom1981 =  zRBOG+atom1972*atom869-atom1726+atom1725;
atom1975 =  atom1972*atom867+atom1717-atom1718;
atom1977 = -atom1722-atom863*atom1972;
atom1987 =  atom1977*atom1209+atom1975*atom1210;
atom1988 =  atom0-atom1977*atom1210+atom1975*atom1209;
atom4742 =  atom2094+5.0000000000000000e-01*atom4700*L_RAIL;
atom4750 =  5.0000000000000000e-01*atom4728*L_RAIL+atom2118;
atom2012 = atom1969*atom1237;
atom2015 = atom1282*atom1971;
atom2181 = -RFLfs+uW_RFL*atom1279-atom2071*atom2079+atom1193*atom1981+atom1988*atom1190+atom2015+-5.0000000000000000e-01*atom2098*L_RAIL-uR_RFL+atom1180*atom1987+yWAG+atom2012;
atom2061 =  uR_RFL-lR_RFL;
atom2062 = atom2061*aR_RFL;
atom2063 =  atom2062+bR_RFL;
atom2130 =  atom2063+atom2062;
atom2065 =  atom2063*atom2061+cR_RFL;
atom2132 =  atom2065+atom2061*atom2130;
atom2178 = pow( (atom2132*atom2132)+1.0,-(1.0/2.0));
atom2033 = -atom1243*atom1971+atom1288*atom1969;
atom2179 = atom2178*atom2132;
atom2051 =  atom1243*atom2038+atom1285+atom2041*atom1288;
atom4624 =  atom2061*( atom2061*aR_RFL+bR_RFL)+cR_RFL+atom2061*( 2.0*atom2061*aR_RFL+bR_RFL);
atom4634 =  3.0*atom2061*aR_RFL+bR_RFL;
atom8039 = -2.0*atom4624*pow( (atom4624*atom4624)+1.0,-(3.0/2.0))*atom4634;
atom4646 =  2.0*atom2130+2.0*atom2061*aR_RFL;
atom2017 = atom1243*atom1969;
atom2020 = atom1288*atom1971;
atom2134 = -atom2127*atom2132;
atom2133 = atom2129*atom2132;
atom2167 = pow( atom2165+(atom2133*atom2133)+(atom2134*atom2134),-(1.0/2.0));
atom2170 = atom2167*atom2127;
atom2168 = atom2167*atom2133;
atom2169 = atom2167*atom2134;
atom4625 = (atom4624*atom4624);
atom4632 = pow( pow( ( 2.0*( uR_RFL-lR_RFL)*aR_RFL+bR_RFL)*( uR_RFL-lR_RFL)+( uR_RFL-lR_RFL)*( ( uR_RFL-lR_RFL)*aR_RFL+bR_RFL)+cR_RFL,2.0)*atom4619+atom4625*atom4629+atom4619,-(3.0/2.0));
atom4638 = -2.0*( atom4624*atom4629*atom4634+atom4624*atom4634*atom4619)*atom4632;
atom4639 = atom2127*atom4638;
atom4656 =  atom2129*atom2167*atom4646+atom2133*atom4638;
atom4650 = -atom2167*atom2127*atom4646+atom4638*atom2134;
atom4699 = -( atom4691+atom4691*pow( ( 2.0*( uR_RFL-lR_RFL)*aR_RFL+bR_RFL)*( uR_RFL-lR_RFL)+( uR_RFL-lR_RFL)*( ( uR_RFL-lR_RFL)*aR_RFL+bR_RFL)+cR_RFL,2.0)-atom4625*atom4695*atom4628)*atom4632;
atom4735 =  atom2167*atom4732+atom4699*atom2127;
atom4754 =  atom4699*atom2133+atom2167*atom2132*atom4750;
atom4740 =  atom4699*atom2134-atom2167*atom4732*atom2132;
atom8234 =  2.0000000000000000e+00*aW_RFL*atom1962+2.0*atom2035;
atom8235 = atom1970*atom8234;
atom8237 = -atom1961*atom8234;
atom2325 =  RRRstas-RRRends;
atom2324 =  RRRstas-xR_RRR;
atom2326 = 1.0/(atom2325);
atom2327 = atom2324*atom2326;
atom2329 =  atom2327*RRRas+RRRbs;
atom2331 =  RRRcs+atom2327*atom2329;
atom2338 = -atom2326*RRRas;
atom2341 = -atom2329*atom2326+atom2327*atom2338;
atom2344 =  atom2327*atom2341-atom2331*atom2326;
atom2333 =  RRRds+atom2327*atom2331;
atom2347 = -atom2333*atom2326+atom2327*atom2344;
atom2335 =  atom2327*atom2333+RRRes;
atom2350 = -atom2335*atom2326+atom2327*atom2347;
atom2352 =  (atom2350*atom2350)+1.0;
atom2353 = pow(atom2352,(1.0/2.0));
atom2363 = -2.0000000000000000e+00*atom2338*atom2326;
atom2361 = -atom2326*atom2341;
atom2366 =  2.0*atom2361+atom2327*atom2363;
atom2367 = -atom2344*atom2326;
atom2370 =  2.0*atom2367+atom2327*atom2366;
atom2372 = -atom2347*atom2326;
atom2374 =  2.0*atom2372+atom2327*atom2370;
atom2376 = pow(atom2352,-(1.0/2.0));
atom2375 = 2.0*atom2350*atom2374;
atom2378 = 1.0/(atom2353*atom2353);
atom2377 = (1.0/2.0)*atom2376*atom2375;
atom2379 = -atom2378*atom2377;
atom2385 =  -5.0000000000000000e-01*L_RAIL*atom2379+atom2350;
atom2354 = 1.0/(atom2353);
atom2380 = 5.0000000000000000e-01*atom2354*L_RAIL*atom2374;
atom2383 =  atom2380+5.0000000000000000e-01*atom2350*L_RAIL*atom2379+1.0;
atom2421 = (atom2383*atom2383);
atom2429 = pow( (atom2385*atom2385)+atom2421,-(1.0/2.0));
atom49 = cos(aRWHSR);
atom50 = sin(aRWHSR);
atom2212 =  uW_RRR-lW_RRR;
atom2219 = sin(thetaW_RRR);
atom2218 =  atom2212*( cW_RRR+atom2212*( bW_RRR+atom2212*aW_RRR))+dW_RRR;
atom1319 = -atom1255*atom50+atom1258*atom49;
atom2220 = -atom2219*atom2218;
atom2221 = cos(thetaW_RRR);
atom2222 = atom2221*atom2218;
atom2431 = atom2385*atom2429;
atom2286 = -atom2222*atom1237+atom1319*atom2220;
atom1313 = -atom50*atom1249+atom49*atom1252;
atom2283 = -atom1231*atom2222+atom2220*atom1313;
atom2430 = atom2429*atom2383;
atom2291 =  bW_RRR+2.0*atom2212*aW_RRR;
atom2293 =  atom2212*atom2291+cW_RRR+atom2212*( bW_RRR+atom2212*aW_RRR);
atom2297 = atom2221*atom2293;
atom2294 = -atom2219*atom2293;
atom1310 =  atom49*atom1249+atom50*atom1252;
atom2299 =  atom2297*atom1313+atom1231*atom2294+atom1310;
atom1316 =  atom1255*atom49+atom1258*atom50;
atom2303 =  atom1316+atom1319*atom2297+atom2294*atom1237;
atom5080 =  RRRcs+( atom2324*atom2326*RRRas+RRRbs)*atom2324*atom2326;
atom5159 = atom2324*atom2326*( atom2326*( atom2326*( RRRcs+( atom2324*atom2326*RRRas+RRRbs)*atom2324*atom2326)+atom2324*atom2326*( ( atom2324*atom2326*RRRas+RRRbs)*atom2326+atom2324*(atom2326*atom2326)*RRRas))-(-atom2326*( RRRcs+( atom2324*atom2326*RRRas+RRRbs)*atom2324*atom2326)+atom2324*atom2326*(-( atom2324*atom2326*RRRas+RRRbs)*atom2326-atom2324*(atom2326*atom2326)*RRRas))*atom2326+atom2324*atom2326*( 2.0000000000000000e+00*atom2324*(atom2326*atom2326*atom2326)*RRRas-atom2326*(-( atom2324*atom2326*RRRas+RRRbs)*atom2326-atom2324*(atom2326*atom2326)*RRRas)+atom2326*( ( atom2324*atom2326*RRRas+RRRbs)*atom2326+atom2324*(atom2326*atom2326)*RRRas)));
atom5162 = atom2326*( atom2326*( atom2324*atom5080*atom2326+RRRds)+atom2324*atom2326*( atom2326*( RRRcs+( atom2324*atom2326*RRRas+RRRbs)*atom2324*atom2326)+atom2324*atom2326*( ( atom2324*atom2326*RRRas+RRRbs)*atom2326+atom2324*(atom2326*atom2326)*RRRas)));
atom5173 = -(-( RRRds+( RRRcs+( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326*( RRRstas-xR_RRR))*atom2326*( RRRstas-xR_RRR))*atom2326+(-( RRRcs+( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326*( RRRstas-xR_RRR))*atom2326+atom2326*( RRRstas-xR_RRR)*(-( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326-(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas))*atom2326*( RRRstas-xR_RRR))*atom2326;
atom5085 = -atom2326*( atom2324*atom2326*( RRRds+atom2324*atom2326*( RRRcs+( atom2324*atom2326*RRRas+RRRbs)*atom2324*atom2326))+RRRes);
atom5096 = atom2324*( (-atom2326*( RRRcs+( atom2324*atom2326*RRRas+RRRbs)*atom2324*atom2326)+atom2324*atom2326*(-( atom2324*atom2326*RRRas+RRRbs)*atom2326-atom2324*(atom2326*atom2326)*RRRas))*atom2324*atom2326-atom2326*( RRRds+atom2324*atom2326*( RRRcs+( atom2324*atom2326*RRRas+RRRbs)*atom2324*atom2326)))*atom2326;
atom5174 =  atom5159+atom5162+atom5173;
atom5097 =  atom5085+atom5096;
atom5190 = -atom5174*pow( (atom5097*atom5097)+1.0,-(3.0/2.0))*atom5097;
atom5228 =  -5.0000000000000000e-01*atom5190*L_RAIL+atom2350;
atom5193 = -atom2363*atom2326;
atom5192 = -atom2326*atom2366;
atom5191 = -atom2370*atom2326;
atom5203 =  3.0*atom5191+3.0*atom2327*( atom5192+atom2327*atom5193);
atom5218 =  2.0*atom5174/pow( (atom5097*atom5097)+1.0,2.0)*atom2377*atom5097-atom2378*( atom2375*atom5190+atom2376*( 2.0*atom2350*atom5203+2.0*(atom2374*atom2374)))/2.0;
atom5236 =  atom2374+-5.0000000000000000e-01*atom5218*L_RAIL;
atom5098 = (atom5097*atom5097);
atom5099 =  atom5098+1.0;
atom5107 = -atom2324*( 2.0000000000000000e+00*atom2324*(atom2326*atom2326*atom2326)*RRRas+-2.0000000000000000e+00*atom2326*(-( atom2324*atom2326*RRRas+RRRbs)*atom2326-atom2324*(atom2326*atom2326)*RRRas))*atom2326+2.0*(-atom5080*atom2326+atom2324*atom2326*(-( atom2324*atom2326*RRRas+RRRbs)*atom2326-atom2324*(atom2326*atom2326)*RRRas))*atom2326;
atom5115 = pow(atom5099,-(1.0/2.0));
atom5110 =  atom2324*atom5107*atom2326+2.0*(-( RRRds+( RRRcs+( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326*( RRRstas-xR_RRR))*atom2326*( RRRstas-xR_RRR))*atom2326+(-( RRRcs+( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326*( RRRstas-xR_RRR))*atom2326+atom2326*( RRRstas-xR_RRR)*(-( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326-(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas))*atom2326*( RRRstas-xR_RRR))*atom2326;
atom5118 =  -5.0000000000000000e-01*atom5115*atom5110*L_RAIL+5.0000000000000000e-01*atom5098*atom5110*L_RAIL*pow( atom5098+1.0,-(3.0/2.0))+1.0;
atom5112 =  atom5085+atom5096+-5.0000000000000000e-01*atom5110*pow( (atom5097*atom5097)+1.0,-(3.0/2.0))*L_RAIL*atom5097;
atom5119 = (atom5118*atom5118);
atom5113 = (atom5112*atom5112);
atom5171 =  atom2324*atom2326*( atom2326*( 2.0000000000000000e+00*(atom2326*atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas+-2.0000000000000000e+00*atom2326*(-( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326-(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas))+6.0000000000000000e+00*atom2324/((atom2325*atom2325)*(atom2325*atom2325))*RRRas+2.0*atom2326*( atom2326*( ( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326+(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas)+2.0000000000000000e+00*atom2324/(atom2325*atom2325*atom2325)*RRRas-atom2326*(-( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326-(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas)))-atom5107*atom2326+2.0*atom2326*( ( atom2326*( RRRstas-xR_RRR)*( ( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326+(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas)+( RRRcs+( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326*( RRRstas-xR_RRR))*atom2326)*atom2326-(-( RRRcs+( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326*( RRRstas-xR_RRR))*atom2326+atom2326*( RRRstas-xR_RRR)*(-( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326-(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas))*atom2326+( atom2326*( ( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326+(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas)+2.0000000000000000e+00*(atom2326*atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas-atom2326*(-( atom2326*( RRRstas-xR_RRR)*RRRas+RRRbs)*atom2326-(atom2326*atom2326)*( RRRstas-xR_RRR)*RRRas))*atom2326*( RRRstas-xR_RRR));
atom5185 =  1.5000000000000000e+00*atom5110*atom5174*pow( (atom5097*atom5097)+1.0,-(3.0/2.0))*L_RAIL*atom5097+5.0000000000000000e-01*atom5098*L_RAIL*atom5171*pow( atom5098+1.0,-(3.0/2.0))+-1.5000000000000000e+00*pow(atom5099,-(5.0/2.0))*atom5110*atom5174*L_RAIL*(atom5097*atom5097*atom5097)+-5.0000000000000000e-01*atom5115*L_RAIL*atom5171;
atom5178 =  -5.0000000000000000e-01*pow( (atom5097*atom5097)+1.0,-(3.0/2.0))*L_RAIL*atom5171*atom5097+atom5159+1.5000000000000000e+00*pow(-( ( RRRstas-xR_RRR)*( RRRds+( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)*( RRRstas-xR_RRR)/( RRRstas-RRRends))/( RRRstas-RRRends)+RRRes)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRds+( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)*( RRRstas-xR_RRR)/( RRRstas-RRRends))/( RRRstas-RRRends)+(-( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends)))*( RRRstas-xR_RRR)/( RRRstas-RRRends)),2.0)*( atom5159+atom5162+atom5173)*pow( pow(-( ( RRRstas-xR_RRR)*( RRRds+( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)*( RRRstas-xR_RRR)/( RRRstas-RRRends))/( RRRstas-RRRends)+RRRes)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRds+( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)*( RRRstas-xR_RRR)/( RRRstas-RRRends))/( RRRstas-RRRends)+(-( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends)))*( RRRstas-xR_RRR)/( RRRstas-RRRends)),2.0)+1.0,-(5.0/2.0))*L_RAIL*( ( 2.0*(-( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends)))/( RRRstas-RRRends)-( RRRstas-xR_RRR)/( RRRstas-RRRends)*( -2.0000000000000000e+00*1.0/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends))+2.0000000000000000e+00*( RRRstas-xR_RRR)/pow( RRRstas-RRRends,3.0)*RRRas))*( RRRstas-xR_RRR)/( RRRstas-RRRends)+2.0*1.0/( RRRstas-RRRends)*(-( RRRds+( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)*( RRRstas-xR_RRR)/( RRRstas-RRRends))/( RRRstas-RRRends)+(-( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends)))*( RRRstas-xR_RRR)/( RRRstas-RRRends)))+-5.0000000000000000e-01*( atom5159+atom5162+atom5173)*pow( pow(-( ( RRRstas-xR_RRR)*( RRRds+( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)*( RRRstas-xR_RRR)/( RRRstas-RRRends))/( RRRstas-RRRends)+RRRes)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRds+( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)*( RRRstas-xR_RRR)/( RRRstas-RRRends))/( RRRstas-RRRends)+(-( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends)))*( RRRstas-xR_RRR)/( RRRstas-RRRends)),2.0)+1.0,-(3.0/2.0))*L_RAIL*( ( 2.0*(-( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends)))/( RRRstas-RRRends)-( RRRstas-xR_RRR)/( RRRstas-RRRends)*( -2.0000000000000000e+00*1.0/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends))+2.0000000000000000e+00*( RRRstas-xR_RRR)/pow( RRRstas-RRRends,3.0)*RRRas))*( RRRstas-xR_RRR)/( RRRstas-RRRends)+2.0*1.0/( RRRstas-RRRends)*(-( RRRds+( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)*( RRRstas-xR_RRR)/( RRRstas-RRRends))/( RRRstas-RRRends)+(-( ( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)*( RRRstas-xR_RRR)/( RRRstas-RRRends)+RRRcs)/( RRRstas-RRRends)+( RRRstas-xR_RRR)/( RRRstas-RRRends)*(-( RRRstas-xR_RRR)/pow( RRRstas-RRRends,2.0)*RRRas-( ( RRRstas-xR_RRR)/( RRRstas-RRRends)*RRRas+RRRbs)/( RRRstas-RRRends)))*( RRRstas-xR_RRR)/( RRRstas-RRRends)))+atom5162+atom5173;
atom5187 = atom5185*atom5118;
atom8298 = -( atom5187+atom5112*atom5178)*pow( atom5119+atom5113,-(3.0/2.0));
atom2268 = atom2220*atom1237;
atom2271 = atom1319*atom2222;
atom2224 = atom50*atom1702;
atom2225 =  atom2224+zRWHSR;
atom2223 = atom49*atom1702;
atom2233 = atom868*atom2223;
atom2237 =  zRBOG+atom2233-atom1725+atom2225*atom869;
atom2226 = atom866*atom2223;
atom2229 = -atom1717+atom2226+atom867*atom2225;
atom2230 = atom862*atom2223;
atom2232 =  atom2230-atom863*atom2225;
atom2243 =  atom2229*atom1210+atom1209*atom2232;
atom2244 =  atom0+atom1209*atom2229-atom2232*atom1210;
atom2437 = -RRRfs-atom2327*atom2335+atom1180*atom2243+atom1316*uW_RRR+atom1190*atom2244+atom2271-uR_RRR+atom1193*atom2237+yWAG+5.0000000000000000e-01*atom2354*L_RAIL+atom2268;
atom2263 = atom1231*atom2220;
atom2266 = atom2222*atom1313;
atom5222 =  5.0000000000000000e-01*atom2354*atom5203*L_RAIL+5.0000000000000000e-01*atom5218*atom2350*L_RAIL+5.0000000000000000e-01*L_RAIL*atom2379*atom2374+5.0000000000000000e-01*atom5190*L_RAIL*atom2374;
atom1325 =  atom49*atom1264-atom50*atom1261;
atom2317 =  uR_RRR-lR_RRR;
atom2318 = atom2317*aR_RRR;
atom2319 =  atom2318+bR_RRR;
atom2386 =  atom2318+atom2319;
atom2321 =  cR_RRR+atom2317*atom2319;
atom2388 =  atom2317*atom2386+atom2321;
atom2434 = pow( (atom2388*atom2388)+1.0,-(1.0/2.0));
atom2289 =  atom2220*atom1325-atom1243*atom2222;
atom2435 = atom2434*atom2388;
atom1322 =  atom49*atom1261+atom50*atom1264;
atom2307 =  atom1243*atom2294+atom2297*atom1325+atom1322;
atom2273 = atom1243*atom2220;
atom2276 = atom2222*atom1325;
atom5132 =  2.0*atom2317*aR_RRR+2.0*atom2386;
atom5075 =  cR_RRR+atom2317*( 2.0*atom2317*aR_RRR+bR_RRR)+atom2317*( atom2317*aR_RRR+bR_RRR);
atom5124 =  3.0*atom2317*aR_RRR+bR_RRR;
atom8345 = -2.0*pow( (atom5075*atom5075)+1.0,-(3.0/2.0))*atom5075*atom5124;
atom2389 = atom2385*atom2388;
atom2390 = -atom2383*atom2388;
atom2423 = pow( (atom2390*atom2390)+(atom2389*atom2389)+atom2421,-(1.0/2.0));
atom2425 = atom2423*atom2390;
atom2424 = atom2423*atom2389;
atom2426 = atom2423*atom2383;
atom5076 = (atom5075*atom5075);
atom5122 = pow( atom5076*atom5119+atom5119+atom5076*atom5113,-(3.0/2.0));
atom5128 = -2.0*atom5122*( atom5119*atom5075*atom5124+atom5075*atom5124*atom5113);
atom5136 = -atom2423*atom5132*atom2383+atom2390*atom5128;
atom5142 =  atom2385*atom2423*atom5132+atom2389*atom5128;
atom5145 = atom2383*atom5128;
atom5189 = -atom5122*( atom5187+atom5112*atom5076*atom5178+atom5185*atom5076*atom5118);
atom5247 =  atom2383*atom5189+atom2423*atom5222;
atom5240 =  atom2423*atom2388*atom5236+atom2389*atom5189;
atom5226 =  atom2390*atom5189-atom2423*atom5222*atom2388;
atom8540 =  2.0*atom2291+2.0000000000000000e+00*atom2212*aW_RRR;
atom8541 = atom2221*atom8540;
atom8543 = -atom2219*atom8540;
atom2469 =  uW_RRL-lW_RRL;
atom2475 =  dW_RRL+atom2469*( cW_RRL+atom2469*( atom2469*aW_RRL+bW_RRL));
atom2477 = cos(thetaW_RRL);
atom2478 = atom2475*atom2477;
atom2468 = sin(thetaW_RRL);
atom2476 = -atom2475*atom2468;
atom2575 =  RRLstas-xR_RRL;
atom2577 = 1.0/( RRLstas-RRLends);
atom2578 = atom2575*atom2577;
atom2580 =  atom2578*RRLas+RRLbs;
atom2582 =  RRLcs+atom2578*atom2580;
atom2584 =  atom2578*atom2582+RRLds;
atom2589 = -RRLas*atom2577;
atom2592 =  atom2578*atom2589-atom2580*atom2577;
atom2595 = -atom2582*atom2577+atom2578*atom2592;
atom2598 =  atom2578*atom2595-atom2584*atom2577;
atom2586 =  atom2578*atom2584+RRLes;
atom2601 =  atom2578*atom2598-atom2586*atom2577;
atom2603 =  (atom2601*atom2601)+1.0;
atom2604 = pow(atom2603,(1.0/2.0));
atom2614 = -2.0*atom2589*atom2577;
atom2616 = -atom2592*atom2577;
atom2618 =  atom2578*atom2614+2.0*atom2616;
atom2612 = -atom2595*atom2577;
atom2621 =  2.0*atom2612+atom2618*atom2578;
atom2623 = -atom2598*atom2577;
atom2605 = 1.0/(atom2604);
atom2625 =  atom2578*atom2621+2.0*atom2623;
atom2626 = 2.0*atom2601*atom2625;
atom2627 = pow(atom2603,-(1.0/2.0));
atom2629 = 1.0/(atom2604*atom2604);
atom2628 = (1.0/2.0)*atom2626*atom2627;
atom2630 = -atom2629*atom2628;
atom2631 = -5.0000000000000000e-01*atom2605*atom2625*L_RAIL;
atom2634 =  atom2631+-5.0000000000000000e-01*atom2601*atom2630*L_RAIL+1.0;
atom2636 =  5.0000000000000000e-01*atom2630*L_RAIL+atom2601;
atom2672 = (atom2634*atom2634);
atom2680 = pow( atom2672+(atom2636*atom2636),-(1.0/2.0));
atom2537 =  atom1319*atom2476-atom2478*atom1237;
atom2682 = atom2680*atom2636;
atom2681 = atom2634*atom2680;
atom2534 =  atom2476*atom1313-atom1231*atom2478;
atom2542 =  2.0*atom2469*aW_RRL+bW_RRL;
atom2544 =  cW_RRL+atom2542*atom2469+atom2469*( atom2469*aW_RRL+bW_RRL);
atom2545 = -atom2544*atom2468;
atom2548 = atom2544*atom2477;
atom2554 =  atom1316+atom1319*atom2548+atom1237*atom2545;
atom2550 =  atom2548*atom1313+atom1310+atom1231*atom2545;
atom5467 = -( ( RRLds+( ( atom2575*RRLas*atom2577+RRLbs)*atom2575*atom2577+RRLcs)*atom2575*atom2577)*atom2575*atom2577+RRLes)*atom2577;
atom5478 = atom2575*atom2577*(-( RRLds+( ( atom2575*RRLas*atom2577+RRLbs)*atom2575*atom2577+RRLcs)*atom2575*atom2577)*atom2577+( (-( atom2575*RRLas*atom2577+RRLbs)*atom2577-atom2575*RRLas*(atom2577*atom2577))*atom2575*atom2577-( ( atom2575*RRLas*atom2577+RRLbs)*atom2575*atom2577+RRLcs)*atom2577)*atom2575*atom2577);
atom5489 =  atom5467+atom5478;
atom5490 = (atom5489*atom5489);
atom5488 =  2.0*( ( RRLstas-xR_RRL)*(-( RRLcs+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577+( RRLstas-xR_RRL)*atom2577*(-( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577)-( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577))*atom2577-( RRLds+( RRLstas-xR_RRL)*( RRLcs+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577)*atom2577)*atom2577+atom2575*atom2577*( ( 2.0*(-( atom2575*RRLas*atom2577+RRLbs)*atom2577-atom2575*RRLas*(atom2577*atom2577))*atom2577+-2.0000000000000000e+00*atom2575*RRLas*(atom2577*atom2577*atom2577))*atom2575*atom2577+2.0000000000000000e+00*( (-( atom2575*RRLas*atom2577+RRLbs)*atom2577-atom2575*RRLas*(atom2577*atom2577))*atom2575*atom2577-( ( atom2575*RRLas*atom2577+RRLbs)*atom2575*atom2577+RRLcs)*atom2577)*atom2577);
atom5491 =  atom5490+1.0;
atom5503 = pow(atom5491,-(1.0/2.0));
atom5505 =  -5.0000000000000000e-01*pow( atom5490+1.0,-(3.0/2.0))*atom5488*atom5490*L_RAIL+5.0000000000000000e-01*atom5503*atom5488*L_RAIL+1.0;
atom5494 =  5.0000000000000000e-01*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( 2.0*1.0/( RRLstas-RRLends)*(-( RRLstas-xR_RRL)/pow( RRLstas-RRLends,2.0)*RRLas-1.0/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs))+-2.0000000000000000e+00*( RRLstas-xR_RRL)/pow( RRLstas-RRLends,3.0)*RRLas)+2.0000000000000000e+00*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*(-( RRLstas-xR_RRL)/pow( RRLstas-RRLends,2.0)*RRLas-1.0/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs))-( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs)+RRLcs)/( RRLstas-RRLends))/( RRLstas-RRLends))+2.0*1.0/( RRLstas-RRLends)*(-1.0/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs)+RRLcs)/( RRLstas-RRLends)+RRLds)+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*(-( RRLstas-xR_RRL)/pow( RRLstas-RRLends,2.0)*RRLas-1.0/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs))-( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs)+RRLcs)/( RRLstas-RRLends))/( RRLstas-RRLends)))*( atom5467+atom5478)*pow( pow( atom5467+atom5478,2.0)+1.0,-(3.0/2.0))*L_RAIL+atom5467+atom5478;
atom5506 = (atom5505*atom5505);
atom5495 = (atom5494*atom5494);
atom5593 =  2.0*(-( ( RRLcs+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577)+( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577)*atom2577+( RRLstas-xR_RRL)*atom2577*( atom2577*(-( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577)-( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)+-2.0000000000000000e+00*( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577*atom2577)-( ( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577)+( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577)+(-( RRLcs+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577+( RRLstas-xR_RRL)*atom2577*(-( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577)-( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577))*atom2577)*atom2577+( -6.0000000000000000e+00*atom2575*RRLas*((atom2577*atom2577)*(atom2577*atom2577))+( 2.0*(-( atom2575*RRLas*atom2577+RRLbs)*atom2577-atom2575*RRLas*(atom2577*atom2577))*atom2577+-2.0000000000000000e+00*atom2575*RRLas*(atom2577*atom2577*atom2577))*atom2577+2.0000000000000000e+00*(-( ( atom2575*RRLas*atom2577+RRLbs)*atom2577+atom2575*RRLas*(atom2577*atom2577))*atom2577+(-( atom2575*RRLas*atom2577+RRLbs)*atom2577-atom2575*RRLas*(atom2577*atom2577))*atom2577+-2.0000000000000000e+00*atom2575*RRLas*(atom2577*atom2577*atom2577))*atom2577)*atom2575*atom2577+( ( RRLstas-xR_RRL)*( 2.0*atom2577*(-( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577)-( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)+-2.0000000000000000e+00*( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577*atom2577))*atom2577+2.0000000000000000e+00*(-( RRLcs+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577+( RRLstas-xR_RRL)*atom2577*(-( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577)-( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577))*atom2577)*atom2577;
atom5550 = ( ( RRLstas-xR_RRL)*(-( RRLcs+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577+( RRLstas-xR_RRL)*atom2577*(-( RRLstas-xR_RRL)*RRLas*(atom2577*atom2577)-( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577))*atom2577-( RRLds+( RRLstas-xR_RRL)*( RRLcs+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577)*atom2577)*atom2577;
atom5549 = -( ( RRLds+( RRLstas-xR_RRL)*( RRLcs+( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)*RRLas*atom2577+RRLbs)*atom2577)*atom2577)*atom2577+atom2575*atom2577*( ( ( atom2575*RRLas*atom2577+RRLbs)*atom2577+atom2575*RRLas*(atom2577*atom2577))*atom2575*atom2577+( ( atom2575*RRLas*atom2577+RRLbs)*atom2575*atom2577+RRLcs)*atom2577))*atom2577;
atom5546 = atom2575*(-atom2577*( ( ( atom2575*RRLas*atom2577+RRLbs)*atom2577+atom2575*RRLas*(atom2577*atom2577))*atom2575*atom2577+( ( atom2575*RRLas*atom2577+RRLbs)*atom2575*atom2577+RRLcs)*atom2577)+atom2575*(-( ( atom2575*RRLas*atom2577+RRLbs)*atom2577+atom2575*RRLas*(atom2577*atom2577))*atom2577+(-( atom2575*RRLas*atom2577+RRLbs)*atom2577-atom2575*RRLas*(atom2577*atom2577))*atom2577+-2.0000000000000000e+00*atom2575*RRLas*(atom2577*atom2577*atom2577))*atom2577+( (-( atom2575*RRLas*atom2577+RRLbs)*atom2577-atom2575*RRLas*(atom2577*atom2577))*atom2575*atom2577-( ( atom2575*RRLas*atom2577+RRLbs)*atom2575*atom2577+RRLcs)*atom2577)*atom2577)*atom2577;
atom5551 =  atom5550+atom5549+atom5546;
atom5600 =  -5.0000000000000000e-01*atom5503*L_RAIL*atom5593+-1.5000000000000000e+00*(atom5489*atom5489*atom5489)*atom5488*L_RAIL*atom5551*pow(atom5491,-(5.0/2.0))+1.5000000000000000e+00*atom5489*pow( (atom5489*atom5489)+1.0,-(3.0/2.0))*atom5488*L_RAIL*atom5551+5.0000000000000000e-01*pow( atom5490+1.0,-(3.0/2.0))*atom5490*L_RAIL*atom5593;
atom5606 =  5.0000000000000000e-01*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( 2.0*1.0/( RRLstas-RRLends)*(-( RRLstas-xR_RRL)/pow( RRLstas-RRLends,2.0)*RRLas-1.0/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs))+-2.0000000000000000e+00*( RRLstas-xR_RRL)/pow( RRLstas-RRLends,3.0)*RRLas)+2.0000000000000000e+00*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*(-( RRLstas-xR_RRL)/pow( RRLstas-RRLends,2.0)*RRLas-1.0/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs))-( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs)+RRLcs)/( RRLstas-RRLends))/( RRLstas-RRLends))+2.0*atom5550)*( atom5550+atom5549+atom5546)*L_RAIL*pow( pow( ( RRLstas-xR_RRL)*atom5550-( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs)+RRLcs)/( RRLstas-RRLends)+RRLds)+RRLes)/( RRLstas-RRLends),2.0)+1.0,-(3.0/2.0))+atom5550+atom5549+atom5546+5.0000000000000000e-01*atom5489*pow( (atom5489*atom5489)+1.0,-(3.0/2.0))*L_RAIL*atom5593+-1.5000000000000000e+00*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( 2.0*1.0/( RRLstas-RRLends)*(-( RRLstas-xR_RRL)/pow( RRLstas-RRLends,2.0)*RRLas-1.0/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs))+-2.0000000000000000e+00*( RRLstas-xR_RRL)/pow( RRLstas-RRLends,3.0)*RRLas)+2.0000000000000000e+00*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*(-( RRLstas-xR_RRL)/pow( RRLstas-RRLends,2.0)*RRLas-1.0/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs))-( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs)+RRLcs)/( RRLstas-RRLends))/( RRLstas-RRLends))+2.0*atom5550)*( atom5550+atom5549+atom5546)*L_RAIL*pow( pow( ( RRLstas-xR_RRL)*atom5550-( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs)+RRLcs)/( RRLstas-RRLends)+RRLds)+RRLes)/( RRLstas-RRLends),2.0)+1.0,-(5.0/2.0))*pow( ( RRLstas-xR_RRL)*atom5550-( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*( ( RRLstas-xR_RRL)/( RRLstas-RRLends)*RRLas+RRLbs)+RRLcs)/( RRLstas-RRLends)+RRLds)+RRLes)/( RRLstas-RRLends),2.0);
atom5602 = atom5505*atom5600;
atom8604 = -( atom5602-atom5494*atom5606)*pow( atom5506+atom5495,-(3.0/2.0));
atom5555 = -atom2614*atom2577;
atom5554 = -atom2618*atom2577;
atom5553 = -atom2577*atom2621;
atom5565 =  3.0*atom5553+3.0*atom2578*( atom5554+atom2578*atom5555);
atom5552 = atom5489*pow( (atom5489*atom5489)+1.0,-(3.0/2.0))*atom5551;
atom5580 = -atom2629*( ( 2.0*atom2601*atom5565+2.0*(atom2625*atom2625))*atom2627+atom2626*atom5552)/2.0+-2.0*atom5489*atom2628/pow( (atom5489*atom5489)+1.0,2.0)*atom5551;
atom5584 =  -5.0000000000000000e-01*atom2625*atom2630*L_RAIL+-5.0000000000000000e-01*atom2625*atom5552*L_RAIL+-5.0000000000000000e-01*atom2605*atom5565*L_RAIL+-5.0000000000000000e-01*atom2601*L_RAIL*atom5580;
atom2479 = -atom2224+zRWHSR;
atom2482 = -atom1717+atom867*atom2479-atom2226;
atom2484 = -atom863*atom2479-atom2230;
atom2495 = -atom2484*atom1210+atom2482*atom1209+atom0;
atom2494 =  atom1209*atom2484+atom2482*atom1210;
atom2488 =  zRBOG-atom2233+atom2479*atom869-atom1725;
atom2514 = atom2476*atom1231;
atom2517 = atom2478*atom1313;
atom5624 =  5.0000000000000000e-01*L_RAIL*atom5580+atom2625;
atom2519 = atom2476*atom1237;
atom2522 = atom1319*atom2478;
atom2688 = -uR_RRL+atom2519+atom1180*atom2494-RRLfs+atom1316*uW_RRL+-5.0000000000000000e-01*atom2605*L_RAIL-atom2578*atom2586+atom1193*atom2488+atom2522+atom1190*atom2495+yWAG;
atom5619 =  atom2601+5.0000000000000000e-01*atom5552*L_RAIL;
atom2568 =  uR_RRL-lR_RRL;
atom2569 = atom2568*aR_RRL;
atom2570 =  bR_RRL+atom2569;
atom2571 = atom2570*atom2568;
atom2637 =  atom2570+atom2569;
atom2572 =  cR_RRL+atom2571;
atom2639 =  atom2572+atom2568*atom2637;
atom2685 = pow( (atom2639*atom2639)+1.0,-(1.0/2.0));
atom2686 = atom2639*atom2685;
atom2540 =  atom2476*atom1325-atom2478*atom1243;
atom2558 =  atom1243*atom2545+atom2548*atom1325+atom1322;
atom5499 =  atom2568*( 2.0*atom2568*aR_RRL+bR_RRL)+cR_RRL+atom2571;
atom5500 = (atom5499*atom5499);
atom5511 =  3.0*atom2568*aR_RRL+bR_RRL;
atom8651 = -2.0*atom5511*pow( atom5500+1.0,-(3.0/2.0))*atom5499;
atom5523 =  2.0*atom2568*aR_RRL+2.0*atom2637;
atom2524 = atom2476*atom1243;
atom2527 = atom2478*atom1325;
atom2641 = -atom2639*atom2634;
atom2640 = atom2639*atom2636;
atom2674 = pow( atom2672+(atom2641*atom2641)+(atom2640*atom2640),-(1.0/2.0));
atom2675 = atom2674*atom2640;
atom2676 = atom2641*atom2674;
atom2677 = atom2634*atom2674;
atom5509 = pow( atom5506+atom5506*atom5500+atom5495*atom5500,-(3.0/2.0));
atom5515 = -2.0*atom5509*( atom5506*atom5511*atom5499+atom5495*atom5511*atom5499);
atom5516 = atom5515*atom2634;
atom5527 = -atom5523*atom2634*atom2674+atom5515*atom2641;
atom5533 =  atom5523*atom2674*atom2636+atom5515*atom2640;
atom5609 = atom5509*( atom5494*atom5606*atom5500-atom5602-atom5505*atom5600*atom5500);
atom5612 =  atom2634*atom5609+atom5584*atom2674;
atom5617 = -atom2639*atom5584*atom2674+atom2641*atom5609;
atom5628 =  atom5609*atom2640+atom2639*atom5624*atom2674;
atom8846 =  2.0*atom2542+2.0000000000000000e+00*atom2469*aW_RRL;
atom8849 = atom8846*atom2477;
atom8847 = -atom8846*atom2468;
atom2720 =  uW_FFR-lW_FFR;
atom2726 =  dW_FFR+( cW_FFR+( bW_FFR+aW_FFR*atom2720)*atom2720)*atom2720;
atom2728 = cos(thetaW_FFR);
atom1497 = sin(cFSLD);
atom1496 = cos(cFSLD);
atom1018 = cos(bFBOG);
atom1506 =  atom1190*atom1496+atom1497*atom1180;
atom1019 = sin(bFBOG);
atom2729 = atom2726*atom2728;
atom1524 = -atom1193*atom1019+atom1018*atom1506;
atom2719 = sin(thetaW_FFR);
atom1527 =  atom1019*atom1506+atom1193*atom1018;
atom1016 = cos(aFBOG);
atom1017 = sin(aFBOG);
atom1509 =  atom1180*atom1496-atom1497*atom1190;
atom497 = cos(aFWHSF);
atom1545 =  atom1527*atom1016-atom1017*atom1509;
atom498 = sin(aFWHSF);
atom1542 =  atom1016*atom1509+atom1527*atom1017;
atom2727 = -atom2726*atom2719;
atom1568 =  atom497*atom1545-atom498*atom1542;
atom2835 =  xR_FFR-FFRstas;
atom2834 = 1.0/( FFRends-FFRstas);
atom2836 = atom2835*atom2834;
atom2838 =  FFRbs+atom2836*FFRas;
atom2840 =  FFRcs+atom2836*atom2838;
atom2842 =  FFRds+atom2836*atom2840;
atom2847 = atom2834*FFRas;
atom2850 =  atom2834*atom2838+atom2836*atom2847;
atom2853 =  atom2834*atom2840+atom2836*atom2850;
atom2856 =  atom2836*atom2853+atom2842*atom2834;
atom2844 =  FFRes+atom2836*atom2842;
atom2859 =  atom2836*atom2856+atom2834*atom2844;
atom2861 =  (atom2859*atom2859)+1.0;
atom2862 = pow(atom2861,(1.0/2.0));
atom2873 = 2.0*atom2834*atom2847;
atom2871 = atom2834*atom2850;
atom2876 =  2.0*atom2871+atom2836*atom2873;
atom2870 = atom2834*atom2853;
atom2879 =  2.0*atom2870+atom2876*atom2836;
atom2881 = atom2834*atom2856;
atom2883 =  2.0*atom2881+atom2836*atom2879;
atom2884 = 2.0*atom2859*atom2883;
atom2885 = pow(atom2861,-(1.0/2.0));
atom2887 = 1.0/(atom2862*atom2862);
atom2886 = (1.0/2.0)*atom2884*atom2885;
atom2888 = -atom2887*atom2886;
atom2863 = 1.0/(atom2862);
atom2889 = 5.0000000000000000e-01*atom2883*atom2863*L_RAIL;
atom2892 =  atom2889+5.0000000000000000e-01*atom2888*atom2859*L_RAIL+1.0;
atom2894 =  atom2859+-5.0000000000000000e-01*atom2888*L_RAIL;
atom2930 = (atom2892*atom2892);
atom2938 = pow( (atom2894*atom2894)+atom2930,-(1.0/2.0));
atom2795 =  atom2727*atom1568-atom2729*atom1524;
atom2940 = atom2894*atom2938;
atom1500 =  atom1496*atom1184+atom1497*atom1178;
atom1518 =  atom1018*atom1500-atom1019*atom1187;
atom1521 =  atom1019*atom1500+atom1018*atom1187;
atom1503 =  atom1496*atom1178-atom1497*atom1184;
atom1539 = -atom1503*atom1017+atom1016*atom1521;
atom1536 =  atom1521*atom1017+atom1503*atom1016;
atom1562 =  atom497*atom1539-atom498*atom1536;
atom2792 =  atom1562*atom2727-atom2729*atom1518;
atom2939 = atom2892*atom2938;
atom2800 =  bW_FFR+2.0*aW_FFR*atom2720;
atom2802 =  cW_FFR+atom2800*atom2720+( bW_FFR+aW_FFR*atom2720)*atom2720;
atom2805 = -atom2802*atom2719;
atom1559 =  atom497*atom1536+atom498*atom1539;
atom2803 = atom2802*atom2728;
atom2808 =  atom1562*atom2803+atom1559+atom2805*atom1518;
atom1565 =  atom497*atom1542+atom498*atom1545;
atom2812 =  atom2805*atom1524+atom1565+atom2803*atom1568;
atom2777 = atom1524*atom2727;
atom2780 = atom2729*atom1568;
atom2730 = atom497*atom1702;
atom1022 = atom1018*atom1017;
atom2741 = -L_OBOG_OWHS*atom1019;
atom2742 = atom2730*atom1022;
atom2731 = atom498*atom1702;
atom1023 = atom1018*atom1016;
atom2732 =  atom2731+zFWHSF;
atom2746 =  atom2741+zFBOG+atom2742+atom1023*atom2732;
atom1020 = atom1019*atom1017;
atom2733 = atom1018*L_OBOG_OWHS;
atom2734 = atom1020*atom2730;
atom1021 = atom1019*atom1016;
atom2737 =  atom1021*atom2732+atom2733+atom2734;
atom2738 = atom1016*atom2730;
atom2740 = -atom2732*atom1017+atom2738;
atom2752 =  atom1497*atom2737+atom2740*atom1496;
atom2753 = -atom1497*atom2740-atom0+atom2737*atom1496;
atom6132 = atom2835*atom2834*( atom2835*atom2834*( atom2834*( FFRcs+atom2835*atom2834*( FFRbs+atom2835*atom2834*FFRas))+atom2835*( atom2834*( FFRbs+atom2835*atom2834*FFRas)+atom2835*(atom2834*atom2834)*FFRas)*atom2834)+atom2834*( atom2835*atom2834*( FFRcs+atom2835*atom2834*( FFRbs+atom2835*atom2834*FFRas))+FFRds));
atom6135 = ( atom2834*( xR_FFR-FFRstas)*( atom2834*( xR_FFR-FFRstas)*( FFRcs+( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+FFRds)+FFRes)*atom2834;
atom6131 =  atom2835*atom2834*( atom2834*( atom2834*( FFRcs+atom2835*atom2834*( FFRbs+atom2835*atom2834*FFRas))+atom2835*( atom2834*( FFRbs+atom2835*atom2834*FFRas)+atom2835*(atom2834*atom2834)*FFRas)*atom2834)+atom2835*atom2834*( atom2835*(atom2834*atom2834*atom2834)*FFRas+( atom2834*( FFRbs+atom2835*atom2834*FFRas)+atom2835*(atom2834*atom2834)*FFRas)*atom2834))+atom2834*( atom2834*( xR_FFR-FFRstas)*( atom2834*( FFRcs+( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+( ( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834+(atom2834*atom2834)*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+atom2834*( atom2834*( xR_FFR-FFRstas)*( FFRcs+( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+FFRds));
atom6136 =  atom6132+atom6135;
atom6137 = (atom6136*atom6136);
atom6208 = (atom6131*atom6131);
atom6219 =  atom2835*atom2834*( atom2834*( atom2835*(atom2834*atom2834*atom2834)*FFRas+( atom2834*( FFRbs+atom2835*atom2834*FFRas)+atom2835*(atom2834*atom2834)*FFRas)*atom2834)+atom2835*((atom2834*atom2834)*(atom2834*atom2834))*FFRas)+atom2834*( atom2834*( atom2834*( FFRcs+( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+( ( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834+(atom2834*atom2834)*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+atom2834*( xR_FFR-FFRstas)*( (atom2834*atom2834*atom2834)*( xR_FFR-FFRstas)*FFRas+( ( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834+(atom2834*atom2834)*( xR_FFR-FFRstas)*FFRas)*atom2834));
atom6138 =  atom6137+1.0;
atom6147 =  atom6132+atom6135+atom6131*L_RAIL*pow( (atom6136*atom6136)+1.0,-(3.0/2.0))*atom6136;
atom6221 =  2.0*atom2835*atom2834*( atom2834*( atom2834*( FFRcs+atom2835*atom2834*( FFRbs+atom2835*atom2834*FFRas))+atom2835*( atom2834*( FFRbs+atom2835*atom2834*FFRas)+atom2835*(atom2834*atom2834)*FFRas)*atom2834)+atom2835*atom2834*( atom2835*(atom2834*atom2834*atom2834)*FFRas+( atom2834*( FFRbs+atom2835*atom2834*FFRas)+atom2835*(atom2834*atom2834)*FFRas)*atom2834))+3.0*atom6219*L_RAIL*pow( (atom6136*atom6136)+1.0,-(3.0/2.0))*atom6136+-6.0*pow( atom6137+1.0,-(5.0/2.0))*atom6137*L_RAIL*atom6208+2.0*atom2834*( atom2834*( xR_FFR-FFRstas)*( atom2834*( FFRcs+( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+( ( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834+(atom2834*atom2834)*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+atom2834*( atom2834*( xR_FFR-FFRstas)*( FFRcs+( FFRbs+atom2834*( xR_FFR-FFRstas)*FFRas)*atom2834*( xR_FFR-FFRstas))+FFRds))+2.0*pow(atom6138,-(3.0/2.0))*L_RAIL*atom6208;
atom6141 = pow(atom6138,-(1.0/2.0));
atom6143 = -pow( atom6137+1.0,-(3.0/2.0))*atom6137*atom6131*L_RAIL+atom6141*atom6131*L_RAIL+1.0;
atom6229 = ( 6.0000000000000000e+00*pow(atom6138,-(5.0/2.0))*L_RAIL*atom6208*(atom6136*atom6136*atom6136)+-6.0000000000000000e+00*L_RAIL*pow( (atom6136*atom6136)+1.0,-(3.0/2.0))*atom6208*atom6136+-3.0000000000000000e+00*pow( atom6137+1.0,-(3.0/2.0))*atom6219*atom6137*L_RAIL+3.0*atom6219*atom6141*L_RAIL)*atom6143;
atom6144 = (atom6143*atom6143);
atom6148 = (atom6147*atom6147);
atom8910 = -pow( atom6144+atom6148,-(3.0/2.0))*( atom6147*atom6221+atom6229);
atom6175 = atom2834*atom2873;
atom6174 = atom2876*atom2834;
atom6173 = atom2834*atom2879;
atom6185 =  3.0*atom6173+3.0*atom2836*( atom2836*atom6175+atom6174);
atom6186 = -2.0*atom6131*pow( (atom6136*atom6136)+1.0,-(3.0/2.0))*atom6136;
atom6201 =  4.0*atom6131/pow( (atom6136*atom6136)+1.0,2.0)*atom2886*atom6136-( atom2884*atom6186+atom2885*( 2.0*(atom2883*atom2883)+2.0*atom2859*atom6185))*atom2887/2.0;
atom6245 =  -5.0000000000000000e-01*atom6201*L_RAIL+atom2883;
atom2946 =  atom2753*atom1190-uR_FFR+atom1180*atom2752+atom2780+uW_FFR*atom1565+atom2777-FFRfs+5.0000000000000000e-01*atom2863*L_RAIL+yWAG-atom2836*atom2844+atom2746*atom1193;
atom6237 =  atom2859+-5.0000000000000000e-01*atom6186*L_RAIL;
atom2772 = atom2727*atom1518;
atom2775 = atom2729*atom1562;
atom6205 =  5.0000000000000000e-01*atom6201*atom2859*L_RAIL+5.0000000000000000e-01*atom6185*atom2863*L_RAIL+5.0000000000000000e-01*atom6186*atom2883*L_RAIL+5.0000000000000000e-01*atom2888*atom2883*L_RAIL;
atom1512 =  atom1194*atom1496+atom1497*atom1175;
atom1533 =  atom1018*atom1195+atom1019*atom1512;
atom1515 =  atom1175*atom1496-atom1497*atom1194;
atom1551 = -atom1515*atom1017+atom1016*atom1533;
atom1548 =  atom1533*atom1017+atom1515*atom1016;
atom1574 = -atom498*atom1548+atom497*atom1551;
atom1530 = -atom1019*atom1195+atom1018*atom1512;
atom2826 =  uR_FFR-lR_FFR;
atom2827 = atom2826*aR_FFR;
atom2828 =  bR_FFR+atom2827;
atom2895 =  atom2828+atom2827;
atom2829 = atom2828*atom2826;
atom2830 =  cR_FFR+atom2829;
atom2897 =  atom2826*atom2895+atom2830;
atom2943 = pow( (atom2897*atom2897)+1.0,-(1.0/2.0));
atom2798 = -atom1530*atom2729+atom1574*atom2727;
atom2944 = atom2943*atom2897;
atom1571 =  atom497*atom1548+atom498*atom1551;
atom2816 =  atom2803*atom1574+atom1571+atom1530*atom2805;
atom6098 =  2.0*atom2895+2.0*atom2826*aR_FFR;
atom6103 =  cR_FFR+atom2829+atom2826*( bR_FFR+2.0*atom2826*aR_FFR);
atom6105 =  bR_FFR+3.0*atom2826*aR_FFR;
atom8957 = -2.0*pow( (atom6103*atom6103)+1.0,-(3.0/2.0))*atom6105*atom6103;
atom2782 = atom1530*atom2727;
atom2785 = atom2729*atom1574;
atom2899 = -atom2892*atom2897;
atom2898 = atom2894*atom2897;
atom2932 = pow( (atom2899*atom2899)+atom2930+(atom2898*atom2898),-(1.0/2.0));
atom2933 = atom2932*atom2898;
atom2934 = atom2899*atom2932;
atom2935 = atom2932*atom2892;
atom6151 = (atom6103*atom6103);
atom6155 = pow( atom6148*atom6151+atom6144+atom6144*atom6151,-(3.0/2.0));
atom6156 = -2.0*atom6155*( atom6105*atom6144*atom6103+atom6105*atom6148*atom6103);
atom6159 =  atom2899*atom6156-atom2932*atom6098*atom2892;
atom6165 =  atom6156*atom2898+atom2894*atom2932*atom6098;
atom6168 = atom6156*atom2892;
atom6232 = -atom6155*( atom6229+pow( ( bR_FFR+aR_FFR*( uR_FFR-lR_FFR))*( uR_FFR-lR_FFR)+cR_FFR+( bR_FFR+2.0*aR_FFR*( uR_FFR-lR_FFR))*( uR_FFR-lR_FFR),2.0)*atom6229+atom6147*atom6151*atom6221);
atom6249 =  atom2898*atom6232+atom2932*atom6245*atom2897;
atom6235 =  atom2899*atom6232-atom2932*atom6205*atom2897;
atom6256 =  atom2932*atom6205+atom2892*atom6232;
atom9152 =  2.0*atom2800+2.0000000000000000e+00*aW_FFR*atom2720;
atom9155 = -atom9152*atom2719;
atom9153 = atom9152*atom2728;
atom2978 =  uW_FFL-lW_FFL;
atom2977 = sin(thetaW_FFL);
atom2984 =  dW_FFL+atom2978*( atom2978*( atom2978*aW_FFL+bW_FFL)+cW_FFL);
atom2985 = -atom2977*atom2984;
atom2986 = cos(thetaW_FFL);
atom2987 = atom2986*atom2984;
atom3084 =  FFLstas-xR_FFL;
atom3086 = 1.0/( FFLstas-FFLends);
atom3087 = atom3084*atom3086;
atom3089 =  atom3087*FFLas+FFLbs;
atom3091 =  FFLcs+atom3087*atom3089;
atom3093 =  FFLds+atom3087*atom3091;
atom3098 = -FFLas*atom3086;
atom3101 =  atom3087*atom3098-atom3089*atom3086;
atom3104 =  atom3087*atom3101-atom3091*atom3086;
atom3107 =  atom3087*atom3104-atom3093*atom3086;
atom3095 =  atom3087*atom3093+FFLes;
atom3110 = -atom3095*atom3086+atom3087*atom3107;
atom3112 =  (atom3110*atom3110)+1.0;
atom3123 = -2.0*atom3098*atom3086;
atom3124 = -atom3086*atom3101;
atom3127 =  2.0*atom3124+atom3087*atom3123;
atom3121 = -atom3104*atom3086;
atom3130 =  2.0*atom3121+atom3087*atom3127;
atom3131 = -atom3107*atom3086;
atom3134 =  atom3087*atom3130+2.0*atom3131;
atom3136 = pow(atom3112,-(1.0/2.0));
atom3135 = 2.0*atom3134*atom3110;
atom3113 = pow(atom3112,(1.0/2.0));
atom3137 = (1.0/2.0)*atom3136*atom3135;
atom3138 = 1.0/(atom3113*atom3113);
atom3139 = -atom3137*atom3138;
atom3114 = 1.0/(atom3113);
atom3141 = -5.0000000000000000e-01*atom3134*atom3114*L_RAIL;
atom3143 =  atom3141+-5.0000000000000000e-01*atom3139*atom3110*L_RAIL+1.0;
atom3145 =  atom3110+5.0000000000000000e-01*atom3139*L_RAIL;
atom3181 = (atom3143*atom3143);
atom3189 = pow( atom3181+(atom3145*atom3145),-(1.0/2.0));
atom3046 = -atom2987*atom1524+atom2985*atom1568;
atom3191 = atom3145*atom3189;
atom3190 = atom3189*atom3143;
atom3043 = -atom2987*atom1518+atom1562*atom2985;
atom3051 =  2.0*atom2978*aW_FFL+bW_FFL;
atom3053 =  atom2978*( atom2978*aW_FFL+bW_FFL)+cW_FFL+atom2978*atom3051;
atom3054 = -atom3053*atom2977;
atom3057 = atom2986*atom3053;
atom3059 =  atom1559+atom3054*atom1518+atom1562*atom3057;
atom3063 =  atom3057*atom1568+atom3054*atom1524+atom1565;
atom6503 = -( atom3084*( atom3084*atom3086*( FFLcs+( FFLbs+atom3084*FFLas*atom3086)*atom3084*atom3086)+FFLds)*atom3086+FFLes)*atom3086;
atom6500 = atom3084*( atom3084*(-atom3086*( FFLcs+( FFLbs+atom3084*FFLas*atom3086)*atom3084*atom3086)+atom3084*atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086)))*atom3086-( atom3084*atom3086*( FFLcs+( FFLbs+atom3084*FFLas*atom3086)*atom3084*atom3086)+FFLds)*atom3086)*atom3086;
atom6567 = -( ( FFLstas-xR_FFL)*( ( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086+( FFLstas-xR_FFL)*atom3086*( ( FFLstas-xR_FFL)*FFLas*(atom3086*atom3086)+( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086))*atom3086+atom3086*( FFLds+( FFLstas-xR_FFL)*( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086))*atom3086;
atom6568 = ( ( FFLstas-xR_FFL)*(-( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086+( FFLstas-xR_FFL)*(-( FFLstas-xR_FFL)*FFLas*(atom3086*atom3086)-( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086)*atom3086-atom3086*( FFLds+( FFLstas-xR_FFL)*( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086))*atom3086;
atom6564 = atom3084*atom3086*( (-atom3086*( FFLcs+( FFLbs+atom3084*FFLas*atom3086)*atom3084*atom3086)+atom3084*atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086)))*atom3086+( atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086))-atom3086*( ( FFLbs+atom3084*FFLas*atom3086)*atom3086+atom3084*FFLas*(atom3086*atom3086))+-2.0000000000000000e+00*atom3084*FFLas*(atom3086*atom3086*atom3086))*atom3084*atom3086-atom3086*( atom3084*atom3086*( ( FFLbs+atom3084*FFLas*atom3086)*atom3086+atom3084*FFLas*(atom3086*atom3086))+atom3086*( FFLcs+( FFLbs+atom3084*FFLas*atom3086)*atom3084*atom3086)));
atom6504 =  atom6503+atom6500;
atom6569 =  atom6567+atom6568+atom6564;
atom6598 = pow( (atom6504*atom6504)+1.0,-(3.0/2.0))*atom6504*atom6569;
atom6639 =  atom3110+5.0000000000000000e-01*atom6598*L_RAIL;
atom6586 = -atom3123*atom3086;
atom6585 = -atom3086*atom3127;
atom6593 = -atom3130*atom3086;
atom6597 =  3.0*atom6593+3.0*atom3087*( atom3087*atom6586+atom6585);
atom6613 = -( atom3135*atom6598+( 2.0*(atom3134*atom3134)+2.0*atom6597*atom3110)*atom3136)*atom3138/2.0+-2.0*atom3137/pow( (atom6504*atom6504)+1.0,2.0)*atom6504*atom6569;
atom6626 =  atom3134+5.0000000000000000e-01*atom6613*L_RAIL;
atom6562 =  atom3084*atom3086*( 6.0000000000000000e+00*atom3084*FFLas*((atom3086*atom3086)*(atom3086*atom3086))+-2.0000000000000000e+00*( atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086))-atom3086*( ( FFLbs+atom3084*FFLas*atom3086)*atom3086+atom3084*FFLas*(atom3086*atom3086))+-2.0000000000000000e+00*atom3084*FFLas*(atom3086*atom3086*atom3086))*atom3086-( 2.0*atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086))+-2.0000000000000000e+00*atom3084*FFLas*(atom3086*atom3086*atom3086))*atom3086)+-2.0*( (-( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086+( FFLstas-xR_FFL)*(-( FFLstas-xR_FFL)*FFLas*(atom3086*atom3086)-( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086)*atom3086-atom3086*( atom3084*atom3086*( ( FFLbs+atom3084*FFLas*atom3086)*atom3086+atom3084*FFLas*(atom3086*atom3086))+( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086)+( atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086))-atom3086*( ( FFLbs+atom3084*FFLas*atom3086)*atom3086+atom3084*FFLas*(atom3086*atom3086))+-2.0000000000000000e+00*atom3084*FFLas*(atom3086*atom3086*atom3086))*atom3084*atom3086)*atom3086-atom3086*( 2.0000000000000000e+00*(-( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086+( FFLstas-xR_FFL)*(-( FFLstas-xR_FFL)*FFLas*(atom3086*atom3086)-( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086)*atom3086+( 2.0*atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086))+-2.0000000000000000e+00*atom3084*FFLas*(atom3086*atom3086*atom3086))*atom3084*atom3086);
atom6505 = (atom6504*atom6504);
atom6499 =  atom3084*atom3086*( 2.0000000000000000e+00*(-atom3086*( FFLcs+( FFLbs+atom3084*FFLas*atom3086)*atom3084*atom3086)+atom3084*atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086)))*atom3086+( 2.0*atom3086*(-( FFLbs+atom3084*FFLas*atom3086)*atom3086-atom3084*FFLas*(atom3086*atom3086))+-2.0000000000000000e+00*atom3084*FFLas*(atom3086*atom3086*atom3086))*atom3084*atom3086)+2.0*( ( FFLstas-xR_FFL)*(-( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086+( FFLstas-xR_FFL)*(-( FFLstas-xR_FFL)*FFLas*(atom3086*atom3086)-( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086)*atom3086-atom3086*( FFLds+( FFLstas-xR_FFL)*( FFLcs+( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*FFLas*atom3086+FFLbs)*atom3086)*atom3086))*atom3086;
atom6506 =  atom6505+1.0;
atom6507 = pow(atom6506,-(1.0/2.0));
atom6511 =  -5.0000000000000000e-01*atom6499*L_RAIL*pow( atom6505+1.0,-(3.0/2.0))*atom6505+5.0000000000000000e-01*atom6507*atom6499*L_RAIL+1.0;
atom6515 =  5.0000000000000000e-01*atom6499*pow( (atom6504*atom6504)+1.0,-(3.0/2.0))*atom6504*L_RAIL+atom6503+atom6500;
atom6581 =  atom6567+-1.5000000000000000e+00*pow(-( FFLes+( FFLstas-xR_FFL)/( FFLstas-FFLends)*( FFLds+( FFLstas-xR_FFL)/( FFLstas-FFLends)*( FFLcs+( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)*( FFLstas-xR_FFL)/( FFLstas-FFLends))))/( FFLstas-FFLends)+( FFLstas-xR_FFL)*atom6568,2.0)*L_RAIL*( atom6567+atom6568+atom6564)*pow( pow(-( FFLes+( FFLstas-xR_FFL)/( FFLstas-FFLends)*( FFLds+( FFLstas-xR_FFL)/( FFLstas-FFLends)*( FFLcs+( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)*( FFLstas-xR_FFL)/( FFLstas-FFLends))))/( FFLstas-FFLends)+( FFLstas-xR_FFL)*atom6568,2.0)+1.0,-(5.0/2.0))*( ( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*( 2.0*(-( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)/( FFLstas-FFLends)-( FFLstas-xR_FFL)*FFLas/pow( FFLstas-FFLends,2.0))/( FFLstas-FFLends)+-2.0000000000000000e+00*( FFLstas-xR_FFL)*FFLas/pow( FFLstas-FFLends,3.0))/( FFLstas-FFLends)+2.0000000000000000e+00*1.0/( FFLstas-FFLends)*( ( FFLstas-xR_FFL)*(-( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)/( FFLstas-FFLends)-( FFLstas-xR_FFL)*FFLas/pow( FFLstas-FFLends,2.0))/( FFLstas-FFLends)-1.0/( FFLstas-FFLends)*( FFLcs+( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)*( FFLstas-xR_FFL)/( FFLstas-FFLends))))/( FFLstas-FFLends)+2.0*atom6568)+5.0000000000000000e-01*L_RAIL*( atom6567+atom6568+atom6564)*pow( pow(-( FFLes+( FFLstas-xR_FFL)/( FFLstas-FFLends)*( FFLds+( FFLstas-xR_FFL)/( FFLstas-FFLends)*( FFLcs+( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)*( FFLstas-xR_FFL)/( FFLstas-FFLends))))/( FFLstas-FFLends)+( FFLstas-xR_FFL)*atom6568,2.0)+1.0,-(3.0/2.0))*( ( FFLstas-xR_FFL)*( ( FFLstas-xR_FFL)*( 2.0*(-( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)/( FFLstas-FFLends)-( FFLstas-xR_FFL)*FFLas/pow( FFLstas-FFLends,2.0))/( FFLstas-FFLends)+-2.0000000000000000e+00*( FFLstas-xR_FFL)*FFLas/pow( FFLstas-FFLends,3.0))/( FFLstas-FFLends)+2.0000000000000000e+00*1.0/( FFLstas-FFLends)*( ( FFLstas-xR_FFL)*(-( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)/( FFLstas-FFLends)-( FFLstas-xR_FFL)*FFLas/pow( FFLstas-FFLends,2.0))/( FFLstas-FFLends)-1.0/( FFLstas-FFLends)*( FFLcs+( ( FFLstas-xR_FFL)*FFLas/( FFLstas-FFLends)+FFLbs)*( FFLstas-xR_FFL)/( FFLstas-FFLends))))/( FFLstas-FFLends)+2.0*atom6568)+atom6568+atom6564+-5.0000000000000000e-01*pow( (atom6504*atom6504)+1.0,-(3.0/2.0))*atom6504*atom6562*L_RAIL;
atom6576 = ( 5.0000000000000000e-01*atom6507*atom6562*L_RAIL+1.5000000000000000e+00*atom6499*pow( (atom6504*atom6504)+1.0,-(3.0/2.0))*atom6504*atom6569*L_RAIL+-5.0000000000000000e-01*atom6562*L_RAIL*pow( atom6505+1.0,-(3.0/2.0))*atom6505+-1.5000000000000000e+00*atom6499*(atom6504*atom6504*atom6504)*pow(atom6506,-(5.0/2.0))*atom6569*L_RAIL)*atom6511;
atom6516 = (atom6515*atom6515);
atom6512 = (atom6511*atom6511);
atom9216 = -pow( atom6516+atom6512,-(3.0/2.0))*( atom6576-atom6515*atom6581);
atom3028 = atom2985*atom1524;
atom3031 = atom2987*atom1568;
atom2988 = -atom2731+zFWHSF;
atom2993 = -atom1017*atom2988-atom2738;
atom2991 =  atom1021*atom2988+atom2733-atom2734;
atom3004 =  atom2991*atom1496-atom0-atom1497*atom2993;
atom3003 =  atom1497*atom2991+atom2993*atom1496;
atom2997 =  atom2741+zFBOG+atom1023*atom2988-atom2742;
atom3197 =  atom3004*atom1190+uW_FFL*atom1565-atom3087*atom3095-uR_FFL+atom1193*atom2997+atom1180*atom3003+atom3031+yWAG+-5.0000000000000000e-01*atom3114*L_RAIL-FFLfs+atom3028;
atom6617 =  -5.0000000000000000e-01*atom6597*atom3114*L_RAIL+-5.0000000000000000e-01*atom3134*atom6598*L_RAIL+-5.0000000000000000e-01*atom3134*atom3139*L_RAIL+-5.0000000000000000e-01*atom6613*atom3110*L_RAIL;
atom3023 = atom2985*atom1518;
atom3026 = atom2987*atom1562;
atom3077 =  uR_FFL-lR_FFL;
atom3078 = aR_FFL*atom3077;
atom3079 =  atom3078+bR_FFL;
atom3080 = atom3079*atom3077;
atom3146 =  atom3079+atom3078;
atom3081 =  cR_FFL+atom3080;
atom3148 =  atom3081+atom3077*atom3146;
atom3194 = pow( (atom3148*atom3148)+1.0,-(1.0/2.0));
atom3049 =  atom2985*atom1574-atom1530*atom2987;
atom3195 = atom3194*atom3148;
atom3067 =  atom1530*atom3054+atom3057*atom1574+atom1571;
atom6473 =  cR_FFL+( bR_FFL+2.0*aR_FFL*atom3077)*atom3077+atom3080;
atom6469 =  bR_FFL+3.0*aR_FFL*atom3077;
atom9263 = -2.0*pow( (atom6473*atom6473)+1.0,-(3.0/2.0))*atom6469*atom6473;
atom3033 = atom1530*atom2985;
atom3036 = atom2987*atom1574;
atom6532 =  2.0*aR_FFL*atom3077+2.0*atom3146;
atom3149 = atom3145*atom3148;
atom3150 = -atom3143*atom3148;
atom3183 = pow( atom3181+(atom3149*atom3149)+(atom3150*atom3150),-(1.0/2.0));
atom3184 = atom3183*atom3149;
atom3185 = atom3150*atom3183;
atom3186 = atom3183*atom3143;
atom6519 = (atom6473*atom6473);
atom6523 = pow( atom6512+atom6519*atom6516+pow( cR_FFL+( bR_FFL+2.0*aR_FFL*( uR_FFL-lR_FFL))*( uR_FFL-lR_FFL)+( bR_FFL+aR_FFL*( uR_FFL-lR_FFL))*( uR_FFL-lR_FFL),2.0)*atom6512,-(3.0/2.0));
atom6524 = -2.0*( atom6469*atom6512*atom6473+atom6516*atom6469*atom6473)*atom6523;
atom6536 =  atom3183*atom3145*atom6532+atom6524*atom3149;
atom6541 =  atom3150*atom6524-atom3183*atom6532*atom3143;
atom6525 = atom6524*atom3143;
atom6584 = ( atom6519*atom6515*atom6581-atom6576-atom6576*pow( cR_FFL+( bR_FFL+2.0*aR_FFL*( uR_FFL-lR_FFL))*( uR_FFL-lR_FFL)+( bR_FFL+aR_FFL*( uR_FFL-lR_FFL))*( uR_FFL-lR_FFL),2.0))*atom6523;
atom6620 =  atom3183*atom6617+atom3143*atom6584;
atom6637 = -atom3183*atom6617*atom3148+atom3150*atom6584;
atom6630 =  atom3149*atom6584+atom3183*atom6626*atom3148;
atom9458 =  2.0*atom3051+2.0000000000000000e+00*atom2978*aW_FFL;
atom9459 = atom2986*atom9458;
atom9461 = -atom9458*atom2977;
atom3340 =  FRRstas-FRRends;
atom3341 = 1.0/(atom3340);
atom3339 =  FRRstas-xR_FRR;
atom3353 = -atom3341*FRRas;
atom3342 = atom3341*atom3339;
atom3344 =  FRRas*atom3342+FRRbs;
atom3356 = -atom3341*atom3344+atom3353*atom3342;
atom3346 =  FRRcs+atom3344*atom3342;
atom3359 =  atom3342*atom3356-atom3341*atom3346;
atom3348 =  FRRds+atom3346*atom3342;
atom3362 =  atom3359*atom3342-atom3341*atom3348;
atom3350 =  atom3342*atom3348+FRRes;
atom3365 =  atom3362*atom3342-atom3341*atom3350;
atom3367 =  (atom3365*atom3365)+1.0;
atom3368 = pow(atom3367,(1.0/2.0));
atom3377 = -2.0*atom3341*atom3353;
atom3378 = -atom3341*atom3356;
atom3381 =  2.0*atom3378+atom3342*atom3377;
atom3383 = -atom3341*atom3359;
atom3385 =  atom3381*atom3342+2.0*atom3383;
atom3387 = -atom3341*atom3362;
atom3369 = 1.0/(atom3368);
atom3389 =  atom3342*atom3385+2.0*atom3387;
atom3391 = pow(atom3367,-(1.0/2.0));
atom3390 = 2.0*atom3365*atom3389;
atom3393 = 1.0/(atom3368*atom3368);
atom3392 = (1.0/2.0)*atom3391*atom3390;
atom3394 = -atom3393*atom3392;
atom3395 = 5.0000000000000000e-01*atom3369*atom3389*L_RAIL;
atom3398 =  atom3395+5.0000000000000000e-01*atom3365*L_RAIL*atom3394+1.0;
atom3400 =  -5.0000000000000000e-01*L_RAIL*atom3394+atom3365;
atom3436 = (atom3398*atom3398);
atom3444 = pow( (atom3400*atom3400)+atom3436,-(1.0/2.0));
atom3229 =  uW_FRR-lW_FRR;
atom3230 = atom3229*aW_FRR;
atom3231 =  atom3230+bW_FRR;
atom3233 =  atom3231*atom3229+cW_FRR;
atom3237 = cos(thetaW_FRR);
atom3235 =  dW_FRR+atom3229*atom3233;
atom3238 = atom3237*atom3235;
atom3228 = sin(thetaW_FRR);
atom684 = sin(aFWHSR);
atom683 = cos(aFWHSR);
atom3236 = -atom3228*atom3235;
atom1604 =  atom683*atom1545-atom684*atom1542;
atom3446 = atom3444*atom3400;
atom3302 =  atom3236*atom1604-atom3238*atom1524;
atom1598 =  atom683*atom1539-atom684*atom1536;
atom3299 =  atom3236*atom1598-atom3238*atom1518;
atom3445 = atom3444*atom3398;
atom3306 =  atom3231+atom3230;
atom3308 =  atom3229*atom3306+atom3233;
atom3311 = -atom3228*atom3308;
atom1595 =  atom684*atom1539+atom683*atom1536;
atom3309 = atom3237*atom3308;
atom3314 =  atom3311*atom1518+atom1598*atom3309+atom1595;
atom1601 =  atom683*atom1542+atom684*atom1545;
atom3318 =  atom3311*atom1524+atom3309*atom1604+atom1601;
atom6969 = -FRRas*atom3339/(atom3340*atom3340)-atom3341*( atom3341*FRRas*atom3339+FRRbs);
atom6959 =  FRRcs+atom3341*( atom3341*FRRas*atom3339+FRRbs)*atom3339;
atom6971 = -atom3341*atom6959;
atom7036 = -atom3341*atom6969*atom3339-atom6971;
atom6983 = -2.0000000000000000e+00*FRRas*atom3339/(atom3340*atom3340*atom3340);
atom7041 =  2.0*atom3341*atom6969+atom6983;
atom6972 =  atom3341*(-(atom3341*atom3341)*FRRas*atom3339-atom3341*( atom3341*FRRas*atom3339+FRRbs))*atom3339+atom6971;
atom7045 =  atom3341*atom6972+atom3341*atom7041*atom3339-atom3341*atom7036;
atom6965 = -atom3341*( FRRds+atom3341*atom6959*atom3339);
atom6974 =  atom3341*atom3339*atom6972+atom6965;
atom7046 = atom3341*atom7045*atom3339;
atom7034 = atom3341*atom6974;
atom7039 = -atom3341*( atom3341*atom7036*atom3339-atom6965);
atom6964 = -atom3341*( atom3341*( atom3341*( FRRcs+atom3341*( atom3341*FRRas*atom3339+FRRbs)*atom3339)*atom3339+FRRds)*atom3339+FRRes);
atom6975 = atom3341*atom6974*atom3339;
atom7047 =  atom7046+atom7034+atom7039;
atom6976 =  atom6964+atom6975;
atom7048 = atom7047*atom6976*pow( (atom6976*atom6976)+1.0,-(3.0/2.0));
atom7050 = -atom3341*atom3377;
atom7053 = -atom3341*atom3381;
atom7049 = -atom3341*atom3385;
atom7061 =  3.0*atom7049+3.0*( atom3342*atom7050+atom7053)*atom3342;
atom7076 =  -2.0*atom7047*atom6976/pow( (atom6976*atom6976)+1.0,2.0)*atom3392-atom3393*( atom3391*( 2.0*atom7061*atom3365+2.0*(atom3389*atom3389))+atom3390*atom7048)/2.0;
atom7123 =  atom3389+-5.0000000000000000e-01*atom7076*L_RAIL;
atom6977 = (atom6976*atom6976);
atom6989 =  atom3341*atom3339*( 2.0*atom3341*( atom3341*(-(atom3341*atom3341)*FRRas*atom3339-atom3341*( atom3341*FRRas*atom3339+FRRbs))*atom3339-atom3341*( FRRcs+atom3341*( atom3341*FRRas*atom3339+FRRbs)*atom3339))+atom3341*atom3339*( 2.0*atom3341*(-(atom3341*atom3341)*FRRas*atom3339-atom3341*( atom3341*FRRas*atom3339+FRRbs))+-2.0000000000000000e+00*(atom3341*atom3341*atom3341)*FRRas*atom3339))+2.0*atom3341*atom6974;
atom6978 =  atom6977+1.0;
atom6991 = pow(atom6978,-(1.0/2.0));
atom6993 =  -5.0000000000000000e-01*atom6991*L_RAIL*atom6989+5.0000000000000000e-01*atom6977*pow( atom6977+1.0,-(3.0/2.0))*L_RAIL*atom6989+1.0;
atom7002 =  atom6964+atom6975+-5.0000000000000000e-01*( 2.0*(-( FRRds+( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))*( FRRstas-xR_FRR)/( FRRstas-FRRends))/( FRRstas-FRRends)+( ( FRRstas-xR_FRR)*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)-( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))/( FRRstas-FRRends))*( FRRstas-xR_FRR)/( FRRstas-FRRends))/( FRRstas-FRRends)+( FRRstas-xR_FRR)*( ( 2.0*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)+-2.0000000000000000e+00*FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,3.0))*( FRRstas-xR_FRR)/( FRRstas-FRRends)+2.0*( ( FRRstas-xR_FRR)*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)-( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends))*L_RAIL*pow( pow( atom6964+atom6975,2.0)+1.0,-(3.0/2.0))*( atom6964+atom6975);
atom6994 = (atom6993*atom6993);
atom7003 = (atom7002*atom7002);
atom7094 =  1.5000000000000000e+00*pow( pow(-( ( FRRstas-xR_FRR)*( FRRds+( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))*( FRRstas-xR_FRR)/( FRRstas-FRRends))/( FRRstas-FRRends)+FRRes)/( FRRstas-FRRends)+( FRRstas-xR_FRR)*atom7034,2.0)+1.0,-(5.0/2.0))*pow(-( ( FRRstas-xR_FRR)*( FRRds+( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))*( FRRstas-xR_FRR)/( FRRstas-FRRends))/( FRRstas-FRRends)+FRRes)/( FRRstas-FRRends)+( FRRstas-xR_FRR)*atom7034,2.0)*( ( FRRstas-xR_FRR)*( ( 2.0*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)+-2.0000000000000000e+00*FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,3.0))*( FRRstas-xR_FRR)/( FRRstas-FRRends)+2.0*( ( FRRstas-xR_FRR)*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)-( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends)+2.0*atom7034)*L_RAIL*( atom7046+atom7034+atom7039)+5.0000000000000000e-01*( ( 6.0000000000000000e+00*FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,4.0)+-2.0*( (-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)-( ( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)+FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)+-2.0000000000000000e+00*FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,3.0))/( FRRstas-FRRends)-( 2.0*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)+-2.0000000000000000e+00*FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,3.0))/( FRRstas-FRRends))*( FRRstas-xR_FRR)/( FRRstas-FRRends)-( ( 2.0*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)+-2.0000000000000000e+00*FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,3.0))*( FRRstas-xR_FRR)/( FRRstas-FRRends)+2.0*( ( FRRstas-xR_FRR)*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)-( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends)+-2.0*( ( (-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)-( ( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)+FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)+-2.0000000000000000e+00*FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,3.0))*( FRRstas-xR_FRR)/( FRRstas-FRRends)-( ( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))/( FRRstas-FRRends)+( ( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)+FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))*( FRRstas-xR_FRR)/( FRRstas-FRRends))/( FRRstas-FRRends)+( ( FRRstas-xR_FRR)*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)-( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends))*pow( pow(-( ( FRRstas-xR_FRR)*( FRRds+( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))*( FRRstas-xR_FRR)/( FRRstas-FRRends))/( FRRstas-FRRends)+FRRes)/( FRRstas-FRRends)+( FRRstas-xR_FRR)*atom7034,2.0)+1.0,-(3.0/2.0))*(-( ( FRRstas-xR_FRR)*( FRRds+( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))*( FRRstas-xR_FRR)/( FRRstas-FRRends))/( FRRstas-FRRends)+FRRes)/( FRRstas-FRRends)+( FRRstas-xR_FRR)*atom7034)*L_RAIL+atom7046+-5.0000000000000000e-01*pow( pow(-( ( FRRstas-xR_FRR)*( FRRds+( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))*( FRRstas-xR_FRR)/( FRRstas-FRRends))/( FRRstas-FRRends)+FRRes)/( FRRstas-FRRends)+( FRRstas-xR_FRR)*atom7034,2.0)+1.0,-(3.0/2.0))*( ( FRRstas-xR_FRR)*( ( 2.0*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)+-2.0000000000000000e+00*FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,3.0))*( FRRstas-xR_FRR)/( FRRstas-FRRends)+2.0*( ( FRRstas-xR_FRR)*(-( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends)-FRRas*( FRRstas-xR_FRR)/pow( FRRstas-FRRends,2.0))/( FRRstas-FRRends)-( FRRcs+( FRRstas-xR_FRR)*( FRRas*( FRRstas-xR_FRR)/( FRRstas-FRRends)+FRRbs)/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends))/( FRRstas-FRRends)+2.0*atom7034)*L_RAIL*( atom7046+atom7034+atom7039)+atom7034+atom7039;
atom6984 =  2.0*atom3341*atom6969+atom6983;
atom7089 =  -2.0*atom3341*atom7045-atom3341*( 2.0*atom3341*atom7041+-6.0000000000000000e+00*FRRas*atom3339/((atom3340*atom3340)*(atom3340*atom3340))+atom3341*atom6984)*atom3339-atom3341*( 2.0*atom3341*atom6972+atom3341*atom6984*atom3339);
atom7102 = -atom6993*( -1.5000000000000000e+00*atom7047*atom6976*pow( (atom6976*atom6976)+1.0,-(3.0/2.0))*L_RAIL*atom6989+5.0000000000000000e-01*atom6977*atom7089*pow( atom6977+1.0,-(3.0/2.0))*L_RAIL+-5.0000000000000000e-01*atom6991*atom7089*L_RAIL+1.5000000000000000e+00*atom7047*pow(atom6978,-(5.0/2.0))*(atom6976*atom6976*atom6976)*L_RAIL*atom6989);
atom9522 = ( atom7094*atom7002+atom7102)*pow( atom6994+atom7003,-(3.0/2.0));
atom3239 = atom683*atom1702;
atom3249 = atom3239*atom1022;
atom3240 = atom684*atom1702;
atom3241 =  zFWHSR+atom3240;
atom3253 = -atom2741+zFBOG+atom3241*atom1023+atom3249;
atom3246 = atom3239*atom1016;
atom3248 = -atom3241*atom1017+atom3246;
atom3242 = atom3239*atom1020;
atom3245 = -atom2733+atom3241*atom1021+atom3242;
atom3260 = -atom1497*atom3248+atom3245*atom1496-atom0;
atom3259 =  atom1497*atom3245+atom3248*atom1496;
atom3284 = atom3236*atom1524;
atom3287 = atom1604*atom3238;
atom3452 =  atom1193*atom3253+atom3287+atom3284+5.0000000000000000e-01*atom3369*L_RAIL-atom3342*atom3350+atom1180*atom3259+atom1190*atom3260+uW_FRR*atom1601-uR_FRR+yWAG-FRRfs;
atom7115 =  -5.0000000000000000e-01*atom7048*L_RAIL+atom3365;
atom3279 = atom3236*atom1518;
atom3282 = atom1598*atom3238;
atom7080 =  5.0000000000000000e-01*atom3389*L_RAIL*atom3394+5.0000000000000000e-01*atom7061*atom3369*L_RAIL+5.0000000000000000e-01*atom7076*atom3365*L_RAIL+5.0000000000000000e-01*atom7048*atom3389*L_RAIL;
atom3332 =  uR_FRR-lR_FRR;
atom3333 = atom3332*aR_FRR;
atom3334 =  atom3333+bR_FRR;
atom3401 =  atom3333+atom3334;
atom3335 = atom3332*atom3334;
atom3336 =  cR_FRR+atom3335;
atom3403 =  atom3336+atom3332*atom3401;
atom3449 = pow( (atom3403*atom3403)+1.0,-(1.0/2.0));
atom1610 = -atom684*atom1548+atom683*atom1551;
atom3450 = atom3403*atom3449;
atom3305 = -atom1530*atom3238+atom3236*atom1610;
atom1607 =  atom683*atom1548+atom684*atom1551;
atom3322 =  atom1607+atom1610*atom3309+atom1530*atom3311;
atom3289 = atom3236*atom1530;
atom3292 = atom1610*atom3238;
atom6998 =  cR_FRR+atom3332*( 2.0*atom3332*aR_FRR+bR_FRR)+atom3335;
atom6999 = (atom6998*atom6998);
atom7008 =  3.0*atom3332*aR_FRR+bR_FRR;
atom9569 = -2.0*atom6998*atom7008*pow( atom6999+1.0,-(3.0/2.0));
atom7020 =  2.0*atom3401+2.0*atom3332*aR_FRR;
atom3404 = atom3400*atom3403;
atom3405 = -atom3398*atom3403;
atom3438 = pow( (atom3405*atom3405)+(atom3404*atom3404)+atom3436,-(1.0/2.0));
atom3440 = atom3405*atom3438;
atom3439 = atom3404*atom3438;
atom3441 = atom3398*atom3438;
atom7006 = pow( atom6994+atom6994*atom6999+atom7003*atom6999,-(3.0/2.0));
atom7012 = -2.0*atom7006*( atom6998*atom7003*atom7008+atom6994*atom6998*atom7008);
atom7013 = atom7012*atom3398;
atom7030 =  atom7012*atom3404+atom3400*atom7020*atom3438;
atom7024 =  atom7012*atom3405-atom7020*atom3398*atom3438;
atom7105 = atom7006*( atom7094*atom7002*atom6999+pow( ( uR_FRR-lR_FRR)*( 2.0*( uR_FRR-lR_FRR)*aR_FRR+bR_FRR)+cR_FRR+( ( uR_FRR-lR_FRR)*aR_FRR+bR_FRR)*( uR_FRR-lR_FRR),2.0)*atom7102+atom7102);
atom7108 =  atom3398*atom7105+atom7080*atom3438;
atom7113 = -atom3403*atom7080*atom3438+atom3405*atom7105;
atom7127 =  atom7123*atom3403*atom3438+atom3404*atom7105;
atom9764 =  2.0*atom3306+2.0*atom3229*aW_FRR;
atom9765 = -atom3228*atom9764;
atom9767 = atom3237*atom9764;
atom3484 =  uW_FRL-lW_FRL;
atom3485 = atom3484*aW_FRL;
atom3486 =  atom3485+bW_FRL;
atom3488 =  cW_FRL+atom3484*atom3486;
atom3492 = cos(thetaW_FRL);
atom3490 =  dW_FRL+atom3488*atom3484;
atom3493 = atom3492*atom3490;
atom3483 = sin(thetaW_FRL);
atom3491 = -atom3483*atom3490;
atom3590 =  FRLstas-FRLends;
atom3589 =  FRLstas-xR_FRL;
atom3591 = 1.0/(atom3590);
atom3592 = atom3589*atom3591;
atom3594 =  FRLbs+atom3592*FRLas;
atom3596 =  FRLcs+atom3592*atom3594;
atom3598 =  FRLds+atom3596*atom3592;
atom3600 =  atom3592*atom3598+FRLes;
atom3603 = -FRLas*atom3591;
atom3606 = -atom3594*atom3591+atom3603*atom3592;
atom3609 = -atom3596*atom3591+atom3592*atom3606;
atom3612 = -atom3598*atom3591+atom3609*atom3592;
atom3615 = -atom3600*atom3591+atom3612*atom3592;
atom3617 =  (atom3615*atom3615)+1.0;
atom3618 = pow(atom3617,(1.0/2.0));
atom3628 = -2.0*atom3603*atom3591;
atom3629 = -atom3606*atom3591;
atom3632 =  2.0*atom3629+atom3592*atom3628;
atom3634 = -atom3609*atom3591;
atom3636 =  2.0*atom3634+atom3592*atom3632;
atom3626 = -atom3612*atom3591;
atom3639 =  2.0*atom3626+atom3592*atom3636;
atom3640 = 2.0*atom3615*atom3639;
atom3641 = pow(atom3617,-(1.0/2.0));
atom3643 = 1.0/(atom3618*atom3618);
atom3642 = (1.0/2.0)*atom3640*atom3641;
atom3644 = -atom3643*atom3642;
atom3650 =  atom3615+5.0000000000000000e-01*atom3644*L_RAIL;
atom3619 = 1.0/(atom3618);
atom3645 = -5.0000000000000000e-01*atom3619*atom3639*L_RAIL;
atom3648 =  atom3645+-5.0000000000000000e-01*atom3615*atom3644*L_RAIL+1.0;
atom3686 = (atom3648*atom3648);
atom3694 = pow( (atom3650*atom3650)+atom3686,-(1.0/2.0));
atom3552 = -atom3493*atom1524+atom1604*atom3491;
atom3696 = atom3650*atom3694;
atom3549 =  atom1598*atom3491-atom3493*atom1518;
atom3695 = atom3694*atom3648;
atom3556 =  atom3485+atom3486;
atom3558 =  atom3488+atom3484*atom3556;
atom3561 = -atom3483*atom3558;
atom3559 = atom3492*atom3558;
atom3564 =  atom1598*atom3559+atom3561*atom1518+atom1595;
atom3568 =  atom3559*atom1604+atom1601+atom3561*atom1524;
atom3494 =  zFWHSR-atom3240;
atom3499 = -atom3494*atom1017-atom3246;
atom3497 =  atom3494*atom1021-atom2733-atom3242;
atom3510 =  atom3497*atom1496-atom0-atom1497*atom3499;
atom3509 =  atom1497*atom3497+atom3499*atom1496;
atom3503 = -atom2741+zFBOG+atom3494*atom1023-atom3249;
atom3529 = atom3491*atom1518;
atom3532 = atom1598*atom3493;
atom7367 = -( atom3589*( atom3589*( FRLcs+atom3589*( FRLbs+atom3589*FRLas*atom3591)*atom3591)*atom3591+FRLds)*atom3591+FRLes)*atom3591;
atom7364 = atom3589*atom3591*( atom3589*(-( FRLcs+atom3589*( FRLbs+atom3589*FRLas*atom3591)*atom3591)*atom3591+atom3589*(-atom3589*FRLas*(atom3591*atom3591)-( FRLbs+atom3589*FRLas*atom3591)*atom3591)*atom3591)*atom3591-( atom3589*( FRLcs+atom3589*( FRLbs+atom3589*FRLas*atom3591)*atom3591)*atom3591+FRLds)*atom3591);
atom7368 =  atom7367+atom7364;
atom7358 = -atom3589*FRLas/(atom3590*atom3590)-( FRLbs+atom3589*FRLas*atom3591)*atom3591;
atom7351 =  FRLcs+atom3589*( FRLbs+atom3589*FRLas*atom3591)*atom3591;
atom7361 = -atom7351*atom3591+atom3589*atom7358*atom3591;
atom7363 =  atom3589*atom3591*atom7361-atom3591*( FRLds+atom3589*atom7351*atom3591);
atom7369 = (atom7368*atom7368);
atom7379 =  -2.0000000000000000e+00*atom7363*atom3591-atom3589*atom3591*( atom3589*( 2.0*(-atom3589*FRLas*(atom3591*atom3591)-( FRLbs+atom3589*FRLas*atom3591)*atom3591)*atom3591+-2.0000000000000000e+00*atom3589*FRLas*(atom3591*atom3591*atom3591))*atom3591+2.0*(-( FRLcs+atom3589*( FRLbs+atom3589*FRLas*atom3591)*atom3591)*atom3591+atom3589*(-atom3589*FRLas*(atom3591*atom3591)-( FRLbs+atom3589*FRLas*atom3591)*atom3591)*atom3591)*atom3591);
atom7380 =  atom7369+1.0;
atom7383 = pow(atom7380,-(1.0/2.0));
atom7385 =  5.0000000000000000e-01*pow( atom7369+1.0,-(3.0/2.0))*L_RAIL*atom7369*atom7379+-5.0000000000000000e-01*atom7383*L_RAIL*atom7379+1.0;
atom7389 =  atom7367+atom7364+-5.0000000000000000e-01*pow( pow( atom7367+atom7364,2.0)+1.0,-(3.0/2.0))*( -2.0000000000000000e+00*(-( FRLds+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends))/( FRLstas-FRLends)+( (-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends))/( FRLstas-FRLends)-( FRLstas-xR_FRL)*( ( 2.0*(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+-2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+2.0*( (-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))*( atom7367+atom7364)*L_RAIL;
atom7386 = (atom7385*atom7385);
atom7390 = (atom7389*atom7389);
atom7373 = -2.0000000000000000e+00*atom3589*FRLas/(atom3590*atom3590*atom3590);
atom7421 = -atom7373+-2.0*atom7358*atom3591;
atom7431 =  atom3589*atom7421*atom3591+-2.0*atom3591*atom7361;
atom7437 = -atom3589*atom7431*atom3591;
atom7436 = atom7363*atom3591;
atom7438 =  atom7437+2.0*atom7436;
atom7374 =  atom7373+2.0*atom7358*atom3591;
atom7433 = -atom3591*( 2.0*atom3591*atom7361+atom3589*atom3591*atom7374)-atom3589*atom3591*( atom3591*atom7374+-6.0000000000000000e+00*atom3589*FRLas/((atom3590*atom3590)*(atom3590*atom3590))+-2.0*atom7421*atom3591)+2.0000000000000000e+00*atom7431*atom3591;
atom7449 =  atom7437+5.0000000000000000e-01*( ( ( ( ( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)+FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)-(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+( ( ( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)+FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends)-( (-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+-2.0*atom7436)*pow( pow(-( ( FRLstas-xR_FRL)*( FRLds+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends))/( FRLstas-FRLends)+FRLes)/( FRLstas-FRLends)+atom7436*( FRLstas-xR_FRL),2.0)+1.0,-(3.0/2.0))*L_RAIL*( -2.0000000000000000e+00*atom7436-( FRLstas-xR_FRL)*( ( 2.0*(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+-2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+2.0*( (-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))+-5.0000000000000000e-01*(-( ( FRLstas-xR_FRL)*( FRLds+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends))/( FRLstas-FRLends)+FRLes)/( FRLstas-FRLends)+atom7436*( FRLstas-xR_FRL))*pow( pow(-( ( FRLstas-xR_FRL)*( FRLds+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends))/( FRLstas-FRLends)+FRLes)/( FRLstas-FRLends)+atom7436*( FRLstas-xR_FRL),2.0)+1.0,-(3.0/2.0))*L_RAIL*( ( 2.0*( ( ( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)+FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)-(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))/( FRLstas-FRLends)-( 2.0*(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+-2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))/( FRLstas-FRLends)+6.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,4.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( ( 2.0*(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+-2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+2.0*( (-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends)+2.0000000000000000e+00*( ( ( ( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)+FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)-(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+( ( ( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)+FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends)-( (-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))+2.0*atom7436+-1.5000000000000000e+00*( ( ( ( ( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)+FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)-(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+( ( ( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)+FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends)-( (-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+-2.0*atom7436)*pow(-( ( FRLstas-xR_FRL)*( FRLds+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends))/( FRLstas-FRLends)+FRLes)/( FRLstas-FRLends)+atom7436*( FRLstas-xR_FRL),2.0)*pow( pow(-( ( FRLstas-xR_FRL)*( FRLds+( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))*( FRLstas-xR_FRL)/( FRLstas-FRLends))/( FRLstas-FRLends)+FRLes)/( FRLstas-FRLends)+atom7436*( FRLstas-xR_FRL),2.0)+1.0,-(5.0/2.0))*L_RAIL*( -2.0000000000000000e+00*atom7436-( FRLstas-xR_FRL)*( ( 2.0*(-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))/( FRLstas-FRLends)+-2.0000000000000000e+00*FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,3.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)+2.0*( (-( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends)-FRLas*( FRLstas-xR_FRL)/pow( FRLstas-FRLends,2.0))*( FRLstas-xR_FRL)/( FRLstas-FRLends)-( FRLcs+( FRLstas-xR_FRL)*( FRLas*( FRLstas-xR_FRL)/( FRLstas-FRLends)+FRLbs)/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends))/( FRLstas-FRLends));
atom7444 = ( -5.0000000000000000e-01*atom7433*pow( atom7369+1.0,-(3.0/2.0))*L_RAIL*atom7369+1.5000000000000000e+00*(atom7368*atom7368*atom7368)*atom7438*pow(atom7380,-(5.0/2.0))*L_RAIL*atom7379+-1.5000000000000000e+00*pow( (atom7368*atom7368)+1.0,-(3.0/2.0))*atom7368*atom7438*L_RAIL*atom7379+5.0000000000000000e-01*atom7433*atom7383*L_RAIL)*atom7385;
atom9828 = pow( atom7386+atom7390,-(3.0/2.0))*( atom7449*atom7389-atom7444);
atom7456 = -atom3591*atom3628;
atom7455 = -atom3632*atom3591;
atom7454 = -atom3591*atom3636;
atom7466 =  3.0*atom3592*( atom7456*atom3592+atom7455)+3.0*atom7454;
atom7453 = pow( (atom7368*atom7368)+1.0,-(3.0/2.0))*atom7368*atom7438;
atom7481 =  -2.0*1.0/pow( (atom7368*atom7368)+1.0,2.0)*atom7368*atom7438*atom3642-( atom3640*atom7453+( 2.0*(atom3639*atom3639)+2.0*atom7466*atom3615)*atom3641)*atom3643/2.0;
atom7485 =  -5.0000000000000000e-01*atom3615*atom7481*L_RAIL+-5.0000000000000000e-01*atom3639*L_RAIL*atom7453+-5.0000000000000000e-01*atom3639*atom3644*L_RAIL+-5.0000000000000000e-01*atom7466*atom3619*L_RAIL;
atom7491 =  atom3615+5.0000000000000000e-01*L_RAIL*atom7453;
atom3534 = atom3491*atom1524;
atom3537 = atom1604*atom3493;
atom7499 =  5.0000000000000000e-01*atom7481*L_RAIL+atom3639;
atom3702 =  atom1193*atom3503+atom1180*atom3509+atom3537-atom3592*atom3600+atom3510*atom1190-uR_FRL+uW_FRL*atom1601+-5.0000000000000000e-01*atom3619*L_RAIL+atom3534+yWAG-FRLfs;
atom3582 =  uR_FRL-lR_FRL;
atom3583 = atom3582*aR_FRL;
atom3584 =  atom3583+bR_FRL;
atom3651 =  atom3584+atom3583;
atom3585 = atom3584*atom3582;
atom3586 =  cR_FRL+atom3585;
atom3653 =  atom3582*atom3651+atom3586;
atom3699 = pow( (atom3653*atom3653)+1.0,-(1.0/2.0));
atom3700 = atom3699*atom3653;
atom3555 = -atom1530*atom3493+atom1610*atom3491;
atom3572 =  atom1607+atom1610*atom3559+atom1530*atom3561;
atom7402 =  2.0*atom3582*aR_FRL+2.0*atom3651;
atom7345 =  cR_FRL+( 2.0*atom3582*aR_FRL+bR_FRL)*atom3582+atom3585;
atom7347 =  3.0*atom3582*aR_FRL+bR_FRL;
atom9875 = -2.0*pow( (atom7345*atom7345)+1.0,-(3.0/2.0))*atom7347*atom7345;
atom3539 = atom1530*atom3491;
atom3542 = atom1610*atom3493;
atom3654 = atom3650*atom3653;
atom3655 = -atom3648*atom3653;
atom3688 = pow( (atom3655*atom3655)+(atom3654*atom3654)+atom3686,-(1.0/2.0));
atom3690 = atom3688*atom3655;
atom3689 = atom3654*atom3688;
atom3691 = atom3688*atom3648;
atom7393 = (atom7345*atom7345);
atom7397 = pow( atom7393*atom7390+pow( cR_FRL+( aR_FRL*( uR_FRL-lR_FRL)+bR_FRL)*( uR_FRL-lR_FRL)+( 2.0*aR_FRL*( uR_FRL-lR_FRL)+bR_FRL)*( uR_FRL-lR_FRL),2.0)*atom7386+atom7386,-(3.0/2.0));
atom7398 = -2.0*atom7397*( atom7347*atom7390*atom7345+atom7347*atom7386*atom7345);
atom7406 = -atom7402*atom3688*atom3648+atom3655*atom7398;
atom7412 =  atom3650*atom7402*atom3688+atom3654*atom7398;
atom7415 = atom3648*atom7398;
atom7452 = -atom7397*( pow( cR_FRL+( aR_FRL*( uR_FRL-lR_FRL)+bR_FRL)*( uR_FRL-lR_FRL)+( 2.0*aR_FRL*( uR_FRL-lR_FRL)+bR_FRL)*( uR_FRL-lR_FRL),2.0)*atom7444-atom7449*atom7389*atom7393+atom7444);
atom7489 = -atom3688*atom3653*atom7485+atom7452*atom3655;
atom7503 =  atom7452*atom3654+atom3688*atom7499*atom3653;
atom7510 =  atom7452*atom3648+atom3688*atom7485;
atom10070 =  2.0*atom3556+2.0*atom3484*aW_FRL;
atom10071 = -atom3483*atom10070;
atom10073 = atom3492*atom10070;
atom7832 = -atom1919*( atom1243*atom1787-atom1789*atom1288)+atom1917*( atom1789*atom1276-atom1231*atom1787)+( atom1789*atom1282-atom1237*atom1787)*atom1918;
atom8138 = -( atom1231*atom2041-atom2038*atom1276)*atom2168+( atom2038*atom1288-atom1243*atom2041)*atom2170+atom2169*( atom2038*atom1282-atom2041*atom1237);
atom8444 = -( atom1243*atom2297-atom2294*atom1325)*atom2426+atom2425*( atom1319*atom2294-atom2297*atom1237)-( atom1231*atom2297-atom2294*atom1313)*atom2424;
atom8750 = -atom2675*( atom1231*atom2548-atom1313*atom2545)+atom2676*( atom1319*atom2545-atom2548*atom1237)+( atom1325*atom2545-atom1243*atom2548)*atom2677;
atom9056 =  ( atom2805*atom1568-atom2803*atom1524)*atom2934+( atom1562*atom2805-atom2803*atom1518)*atom2933+atom2935*( atom2805*atom1574-atom1530*atom2803);
atom9362 = -atom3186*( atom1530*atom3057-atom3054*atom1574)-( atom3057*atom1518-atom1562*atom3054)*atom3184-atom3185*( atom3057*atom1524-atom3054*atom1568);
atom9668 =  atom3439*( atom1598*atom3311-atom3309*atom1518)-( atom1530*atom3309-atom1610*atom3311)*atom3441+atom3440*( atom3311*atom1604-atom3309*atom1524);
atom9974 = -( atom3559*atom1518-atom1598*atom3561)*atom3689-atom3690*( atom3559*atom1524-atom1604*atom3561)-( atom1530*atom3559-atom1610*atom3561)*atom3691;

_dPhit_ds[0] =  atom1776*atom1923+atom1924*atom1779;
_dPhit_ds[1] =  atom1928*atom1782+atom1927*atom1779;
_dPhit_ds[2] = -atom1918*( atom1761+atom1764)-atom1919*( atom1766+atom1769)-atom1917*( atom1759+atom1756);
_dPhit_ds[3] = atom7832;
_dPhit_ds[4] = 0.0000000000000000e+00;
_dPhit_ds[5] = 0.0000000000000000e+00;
_dPhit_ds[6] = 0.0000000000000000e+00;
_dPhit_ds[7] = 0.0000000000000000e+00;
_dPhit_ds[8] = 0.0000000000000000e+00;
_dPhit_ds[9] = 0.0000000000000000e+00;
_dPhit_ds[10] = 0.0000000000000000e+00;
_dPhit_ds[11] = 0.0000000000000000e+00;
_dPhit_ds[12] = 0.0000000000000000e+00;
_dPhit_ds[13] = 0.0000000000000000e+00;
_dPhit_ds[14] = 0.0000000000000000e+00;
_dPhit_ds[15] = 0.0000000000000000e+00;
_dPhit_ds[16] = 0.0000000000000000e+00;
_dPhit_ds[17] = 0.0000000000000000e+00;
_dPhit_ds[18] = 0.0000000000000000e+00;
_dPhit_ds[19] = 0.0000000000000000e+00;
_dPhit_ds[20] = 0.0000000000000000e+00;
_dPhit_ds[21] = 0.0000000000000000e+00;
_dPhit_ds[22] = 0.0000000000000000e+00;
_dPhit_ds[23] = 0.0000000000000000e+00;
_dPhit_ds[24] = 0.0000000000000000e+00;
_dPhit_ds[25] = 0.0000000000000000e+00;
_dPhit_ds[26] = 0.0000000000000000e+00;
_dPhit_ds[27] = 0.0000000000000000e+00;
_dPhit_ds[28] = 0.0000000000000000e+00;
_dPhit_ds[29] = 0.0000000000000000e+00;
_dPhit_ds[30] = 0.0000000000000000e+00;
_dPhit_ds[31] = 0.0000000000000000e+00;
_dPhit_ds[32] =  atom1924*atom1796+atom1792*atom1923;
_dPhit_ds[33] =  atom1796*atom1927+atom1928*atom1800;
_dPhit_ds[34] = atom7832;
_dPhit_ds[35] =  atom1917*( atom1231*atom7929+atom1276*atom7931)+( atom7929*atom1237+atom7931*atom1282)*atom1918+atom1919*( atom1243*atom7929+atom1288*atom7931);
_dPhit_ds[36] = 0.0000000000000000e+00;
_dPhit_ds[37] = 0.0000000000000000e+00;
_dPhit_ds[38] = 0.0000000000000000e+00;
_dPhit_ds[39] = 0.0000000000000000e+00;
_dPhit_ds[40] = 0.0000000000000000e+00;
_dPhit_ds[41] = 0.0000000000000000e+00;
_dPhit_ds[42] = 0.0000000000000000e+00;
_dPhit_ds[43] = 0.0000000000000000e+00;
_dPhit_ds[44] = 0.0000000000000000e+00;
_dPhit_ds[45] = 0.0000000000000000e+00;
_dPhit_ds[46] = 0.0000000000000000e+00;
_dPhit_ds[47] = 0.0000000000000000e+00;
_dPhit_ds[48] = 0.0000000000000000e+00;
_dPhit_ds[49] = 0.0000000000000000e+00;
_dPhit_ds[50] = 0.0000000000000000e+00;
_dPhit_ds[51] = 0.0000000000000000e+00;
_dPhit_ds[52] = 0.0000000000000000e+00;
_dPhit_ds[53] = 0.0000000000000000e+00;
_dPhit_ds[54] = 0.0000000000000000e+00;
_dPhit_ds[55] = 0.0000000000000000e+00;
_dPhit_ds[56] = 0.0000000000000000e+00;
_dPhit_ds[57] = 0.0000000000000000e+00;
_dPhit_ds[58] = 0.0000000000000000e+00;
_dPhit_ds[59] = 0.0000000000000000e+00;
_dPhit_ds[60] = 0.0000000000000000e+00;
_dPhit_ds[61] = 0.0000000000000000e+00;
_dPhit_ds[62] = 0.0000000000000000e+00;
_dPhit_ds[63] = 0.0000000000000000e+00;
_dPhit_ds[64] = -atom1924;
_dPhit_ds[65] =  atom7733*atom1930-atom1928*atom1881-atom1927+( atom1881*atom7733+atom4200*atom1927)*( atom1730*atom1195+atom1766-dR_RFR+uW_RFR*atom1285-atom1810*atom1814+atom1175*atom1736-irrRFRz+zWAG+atom1769+atom1194*atom1737);
_dPhit_ds[66] =  atom4261*atom1776+atom4266*atom1779+atom4270*atom1782;
_dPhit_ds[67] =  atom1792*atom4261+atom4270*atom1800+atom4266*atom1796;
_dPhit_ds[68] = 0.0000000000000000e+00;
_dPhit_ds[69] = 0.0000000000000000e+00;
_dPhit_ds[70] = 0.0000000000000000e+00;
_dPhit_ds[71] = 0.0000000000000000e+00;
_dPhit_ds[72] = 0.0000000000000000e+00;
_dPhit_ds[73] = 0.0000000000000000e+00;
_dPhit_ds[74] = 0.0000000000000000e+00;
_dPhit_ds[75] = 0.0000000000000000e+00;
_dPhit_ds[76] = 0.0000000000000000e+00;
_dPhit_ds[77] = 0.0000000000000000e+00;
_dPhit_ds[78] = 0.0000000000000000e+00;
_dPhit_ds[79] = 0.0000000000000000e+00;
_dPhit_ds[80] = 0.0000000000000000e+00;
_dPhit_ds[81] = 0.0000000000000000e+00;
_dPhit_ds[82] = 0.0000000000000000e+00;
_dPhit_ds[83] = 0.0000000000000000e+00;
_dPhit_ds[84] = 0.0000000000000000e+00;
_dPhit_ds[85] = 0.0000000000000000e+00;
_dPhit_ds[86] = 0.0000000000000000e+00;
_dPhit_ds[87] = 0.0000000000000000e+00;
_dPhit_ds[88] = 0.0000000000000000e+00;
_dPhit_ds[89] = 0.0000000000000000e+00;
_dPhit_ds[90] = 0.0000000000000000e+00;
_dPhit_ds[91] = 0.0000000000000000e+00;
_dPhit_ds[92] = 0.0000000000000000e+00;
_dPhit_ds[93] = 0.0000000000000000e+00;
_dPhit_ds[94] = 0.0000000000000000e+00;
_dPhit_ds[95] = 0.0000000000000000e+00;
_dPhit_ds[96] =  ( atom7686*atom1876+atom4356*atom1922)*( atom1184*atom1737+atom1759-xR_RFR+atom1756+uW_RFR*atom1273+atom1730*atom1187+-5.0000000000000000e-01*atom1843*L_RAIL*atom1847+xWAG+atom1736*atom1178)+( atom7686*atom1878+atom4314*atom1922)*atom1930-atom1924*atom4362-( 5.0000000000000000e-01*atom4304*atom1843*L_RAIL+atom1873+1.0000000000000000e+00)*atom1923;
_dPhit_ds[97] = -atom4362*atom1927;
_dPhit_ds[98] =  atom4343*atom1776+atom4369*atom1782+atom4360*atom1779;
_dPhit_ds[99] =  atom4360*atom1796+atom4369*atom1800+atom1792*atom4343;
_dPhit_ds[100] = 0.0000000000000000e+00;
_dPhit_ds[101] = 0.0000000000000000e+00;
_dPhit_ds[102] = 0.0000000000000000e+00;
_dPhit_ds[103] = 0.0000000000000000e+00;
_dPhit_ds[104] = 0.0000000000000000e+00;
_dPhit_ds[105] = 0.0000000000000000e+00;
_dPhit_ds[106] = 0.0000000000000000e+00;
_dPhit_ds[107] = 0.0000000000000000e+00;
_dPhit_ds[108] = 0.0000000000000000e+00;
_dPhit_ds[109] = 0.0000000000000000e+00;
_dPhit_ds[110] = 0.0000000000000000e+00;
_dPhit_ds[111] = 0.0000000000000000e+00;
_dPhit_ds[112] = 0.0000000000000000e+00;
_dPhit_ds[113] = 0.0000000000000000e+00;
_dPhit_ds[114] = 0.0000000000000000e+00;
_dPhit_ds[115] = 0.0000000000000000e+00;
_dPhit_ds[116] = 0.0000000000000000e+00;
_dPhit_ds[117] = 0.0000000000000000e+00;
_dPhit_ds[118] = 0.0000000000000000e+00;
_dPhit_ds[119] = 0.0000000000000000e+00;
_dPhit_ds[120] = 0.0000000000000000e+00;
_dPhit_ds[121] = 0.0000000000000000e+00;
_dPhit_ds[122] = 0.0000000000000000e+00;
_dPhit_ds[123] = 0.0000000000000000e+00;
_dPhit_ds[124] = 0.0000000000000000e+00;
_dPhit_ds[125] = 0.0000000000000000e+00;
_dPhit_ds[126] = 0.0000000000000000e+00;
_dPhit_ds[127] = 0.0000000000000000e+00;
_dPhit_ds[128] = 0.0000000000000000e+00;
_dPhit_ds[129] = 0.0000000000000000e+00;
_dPhit_ds[130] = 0.0000000000000000e+00;
_dPhit_ds[131] = 0.0000000000000000e+00;
_dPhit_ds[132] =  atom2030*atom2175+atom2174*atom2027;
_dPhit_ds[133] =  atom2033*atom2179+atom2178*atom2030;
_dPhit_ds[134] = -( atom2007+atom2010)*atom2168-( atom2020+atom2017)*atom2170-atom2169*( atom2015+atom2012);
_dPhit_ds[135] = atom8138;
_dPhit_ds[136] = 0.0000000000000000e+00;
_dPhit_ds[137] = 0.0000000000000000e+00;
_dPhit_ds[138] = 0.0000000000000000e+00;
_dPhit_ds[139] = 0.0000000000000000e+00;
_dPhit_ds[140] = 0.0000000000000000e+00;
_dPhit_ds[141] = 0.0000000000000000e+00;
_dPhit_ds[142] = 0.0000000000000000e+00;
_dPhit_ds[143] = 0.0000000000000000e+00;
_dPhit_ds[144] = 0.0000000000000000e+00;
_dPhit_ds[145] = 0.0000000000000000e+00;
_dPhit_ds[146] = 0.0000000000000000e+00;
_dPhit_ds[147] = 0.0000000000000000e+00;
_dPhit_ds[148] = 0.0000000000000000e+00;
_dPhit_ds[149] = 0.0000000000000000e+00;
_dPhit_ds[150] = 0.0000000000000000e+00;
_dPhit_ds[151] = 0.0000000000000000e+00;
_dPhit_ds[152] = 0.0000000000000000e+00;
_dPhit_ds[153] = 0.0000000000000000e+00;
_dPhit_ds[154] = 0.0000000000000000e+00;
_dPhit_ds[155] = 0.0000000000000000e+00;
_dPhit_ds[156] = 0.0000000000000000e+00;
_dPhit_ds[157] = 0.0000000000000000e+00;
_dPhit_ds[158] = 0.0000000000000000e+00;
_dPhit_ds[159] = 0.0000000000000000e+00;
_dPhit_ds[160] = 0.0000000000000000e+00;
_dPhit_ds[161] = 0.0000000000000000e+00;
_dPhit_ds[162] = 0.0000000000000000e+00;
_dPhit_ds[163] = 0.0000000000000000e+00;
_dPhit_ds[164] =  atom2047*atom2175+atom2174*atom2043;
_dPhit_ds[165] =  atom2178*atom2047+atom2179*atom2051;
_dPhit_ds[166] = atom8138;
_dPhit_ds[167] =  atom2169*( atom8237*atom1237+atom8235*atom1282)+atom2168*( atom1231*atom8237+atom1276*atom8235)+( atom1243*atom8237+atom1288*atom8235)*atom2170;
_dPhit_ds[168] = 0.0000000000000000e+00;
_dPhit_ds[169] = 0.0000000000000000e+00;
_dPhit_ds[170] = 0.0000000000000000e+00;
_dPhit_ds[171] = 0.0000000000000000e+00;
_dPhit_ds[172] = 0.0000000000000000e+00;
_dPhit_ds[173] = 0.0000000000000000e+00;
_dPhit_ds[174] = 0.0000000000000000e+00;
_dPhit_ds[175] = 0.0000000000000000e+00;
_dPhit_ds[176] = 0.0000000000000000e+00;
_dPhit_ds[177] = 0.0000000000000000e+00;
_dPhit_ds[178] = 0.0000000000000000e+00;
_dPhit_ds[179] = 0.0000000000000000e+00;
_dPhit_ds[180] = 0.0000000000000000e+00;
_dPhit_ds[181] = 0.0000000000000000e+00;
_dPhit_ds[182] = 0.0000000000000000e+00;
_dPhit_ds[183] = 0.0000000000000000e+00;
_dPhit_ds[184] = 0.0000000000000000e+00;
_dPhit_ds[185] = 0.0000000000000000e+00;
_dPhit_ds[186] = 0.0000000000000000e+00;
_dPhit_ds[187] = 0.0000000000000000e+00;
_dPhit_ds[188] = 0.0000000000000000e+00;
_dPhit_ds[189] = 0.0000000000000000e+00;
_dPhit_ds[190] = 0.0000000000000000e+00;
_dPhit_ds[191] = 0.0000000000000000e+00;
_dPhit_ds[192] = 0.0000000000000000e+00;
_dPhit_ds[193] = 0.0000000000000000e+00;
_dPhit_ds[194] = 0.0000000000000000e+00;
_dPhit_ds[195] = 0.0000000000000000e+00;
_dPhit_ds[196] = -atom2175;
_dPhit_ds[197] =  ( atom8039*atom2132+atom2178*atom4646)*( uW_RFL*atom1285-atom2061*atom2065+atom1175*atom1987+atom2020+atom1988*atom1194-dR_RFL-irrRFLz+atom1981*atom1195+zWAG+atom2017)-atom2178-atom2132*atom2179+atom8039*atom2181;
_dPhit_ds[198] =  atom4650*atom2030+atom4639*atom2033+atom4656*atom2027;
_dPhit_ds[199] =  atom4656*atom2043+atom4639*atom2051+atom4650*atom2047;
_dPhit_ds[200] = 0.0000000000000000e+00;
_dPhit_ds[201] = 0.0000000000000000e+00;
_dPhit_ds[202] = 0.0000000000000000e+00;
_dPhit_ds[203] = 0.0000000000000000e+00;
_dPhit_ds[204] = 0.0000000000000000e+00;
_dPhit_ds[205] = 0.0000000000000000e+00;
_dPhit_ds[206] = 0.0000000000000000e+00;
_dPhit_ds[207] = 0.0000000000000000e+00;
_dPhit_ds[208] = 0.0000000000000000e+00;
_dPhit_ds[209] = 0.0000000000000000e+00;
_dPhit_ds[210] = 0.0000000000000000e+00;
_dPhit_ds[211] = 0.0000000000000000e+00;
_dPhit_ds[212] = 0.0000000000000000e+00;
_dPhit_ds[213] = 0.0000000000000000e+00;
_dPhit_ds[214] = 0.0000000000000000e+00;
_dPhit_ds[215] = 0.0000000000000000e+00;
_dPhit_ds[216] = 0.0000000000000000e+00;
_dPhit_ds[217] = 0.0000000000000000e+00;
_dPhit_ds[218] = 0.0000000000000000e+00;
_dPhit_ds[219] = 0.0000000000000000e+00;
_dPhit_ds[220] = 0.0000000000000000e+00;
_dPhit_ds[221] = 0.0000000000000000e+00;
_dPhit_ds[222] = 0.0000000000000000e+00;
_dPhit_ds[223] = 0.0000000000000000e+00;
_dPhit_ds[224] = 0.0000000000000000e+00;
_dPhit_ds[225] = 0.0000000000000000e+00;
_dPhit_ds[226] = 0.0000000000000000e+00;
_dPhit_ds[227] = 0.0000000000000000e+00;
_dPhit_ds[228] =  ( 5.0000000000000000e-01*atom2094*atom2098*L_RAIL+atom1981*atom1187+atom1987*atom1178+atom1988*atom1184+atom2007-xR_RFL+atom2010+xWAG+uW_RFL*atom1273)*( atom4732*atom2173+atom2127*atom7992)-atom4742*atom2175-atom2174*( atom2125+-5.0000000000000000e-01*atom2094*atom4700*L_RAIL+1.0000000000000000e+00)+atom2181*( atom2129*atom7992+atom2173*atom4750);
_dPhit_ds[229] = -atom4742*atom2178;
_dPhit_ds[230] =  atom4740*atom2030+atom4735*atom2033+atom2027*atom4754;
_dPhit_ds[231] =  atom2043*atom4754+atom4740*atom2047+atom4735*atom2051;
_dPhit_ds[232] = 0.0000000000000000e+00;
_dPhit_ds[233] = 0.0000000000000000e+00;
_dPhit_ds[234] = 0.0000000000000000e+00;
_dPhit_ds[235] = 0.0000000000000000e+00;
_dPhit_ds[236] = 0.0000000000000000e+00;
_dPhit_ds[237] = 0.0000000000000000e+00;
_dPhit_ds[238] = 0.0000000000000000e+00;
_dPhit_ds[239] = 0.0000000000000000e+00;
_dPhit_ds[240] = 0.0000000000000000e+00;
_dPhit_ds[241] = 0.0000000000000000e+00;
_dPhit_ds[242] = 0.0000000000000000e+00;
_dPhit_ds[243] = 0.0000000000000000e+00;
_dPhit_ds[244] = 0.0000000000000000e+00;
_dPhit_ds[245] = 0.0000000000000000e+00;
_dPhit_ds[246] = 0.0000000000000000e+00;
_dPhit_ds[247] = 0.0000000000000000e+00;
_dPhit_ds[248] = 0.0000000000000000e+00;
_dPhit_ds[249] = 0.0000000000000000e+00;
_dPhit_ds[250] = 0.0000000000000000e+00;
_dPhit_ds[251] = 0.0000000000000000e+00;
_dPhit_ds[252] = 0.0000000000000000e+00;
_dPhit_ds[253] = 0.0000000000000000e+00;
_dPhit_ds[254] = 0.0000000000000000e+00;
_dPhit_ds[255] = 0.0000000000000000e+00;
_dPhit_ds[256] = 0.0000000000000000e+00;
_dPhit_ds[257] = 0.0000000000000000e+00;
_dPhit_ds[258] = 0.0000000000000000e+00;
_dPhit_ds[259] = 0.0000000000000000e+00;
_dPhit_ds[260] = 0.0000000000000000e+00;
_dPhit_ds[261] = 0.0000000000000000e+00;
_dPhit_ds[262] = 0.0000000000000000e+00;
_dPhit_ds[263] = 0.0000000000000000e+00;
_dPhit_ds[264] =  atom2431*atom2286+atom2283*atom2430;
_dPhit_ds[265] =  atom2434*atom2286+atom2289*atom2435;
_dPhit_ds[266] = -atom2425*( atom2271+atom2268)-( atom2276+atom2273)*atom2426-( atom2266+atom2263)*atom2424;
_dPhit_ds[267] = atom8444;
_dPhit_ds[268] = 0.0000000000000000e+00;
_dPhit_ds[269] = 0.0000000000000000e+00;
_dPhit_ds[270] = 0.0000000000000000e+00;
_dPhit_ds[271] = 0.0000000000000000e+00;
_dPhit_ds[272] = 0.0000000000000000e+00;
_dPhit_ds[273] = 0.0000000000000000e+00;
_dPhit_ds[274] = 0.0000000000000000e+00;
_dPhit_ds[275] = 0.0000000000000000e+00;
_dPhit_ds[276] = 0.0000000000000000e+00;
_dPhit_ds[277] = 0.0000000000000000e+00;
_dPhit_ds[278] = 0.0000000000000000e+00;
_dPhit_ds[279] = 0.0000000000000000e+00;
_dPhit_ds[280] = 0.0000000000000000e+00;
_dPhit_ds[281] = 0.0000000000000000e+00;
_dPhit_ds[282] = 0.0000000000000000e+00;
_dPhit_ds[283] = 0.0000000000000000e+00;
_dPhit_ds[284] = 0.0000000000000000e+00;
_dPhit_ds[285] = 0.0000000000000000e+00;
_dPhit_ds[286] = 0.0000000000000000e+00;
_dPhit_ds[287] = 0.0000000000000000e+00;
_dPhit_ds[288] = 0.0000000000000000e+00;
_dPhit_ds[289] = 0.0000000000000000e+00;
_dPhit_ds[290] = 0.0000000000000000e+00;
_dPhit_ds[291] = 0.0000000000000000e+00;
_dPhit_ds[292] = 0.0000000000000000e+00;
_dPhit_ds[293] = 0.0000000000000000e+00;
_dPhit_ds[294] = 0.0000000000000000e+00;
_dPhit_ds[295] = 0.0000000000000000e+00;
_dPhit_ds[296] =  atom2299*atom2430+atom2303*atom2431;
_dPhit_ds[297] =  atom2434*atom2303+atom2307*atom2435;
_dPhit_ds[298] = atom8444;
_dPhit_ds[299] =  atom2426*( atom8541*atom1325+atom8543*atom1243)+atom2425*( atom1319*atom8541+atom8543*atom1237)+atom2424*( atom8541*atom1313+atom1231*atom8543);
_dPhit_ds[300] = 0.0000000000000000e+00;
_dPhit_ds[301] = 0.0000000000000000e+00;
_dPhit_ds[302] = 0.0000000000000000e+00;
_dPhit_ds[303] = 0.0000000000000000e+00;
_dPhit_ds[304] = 0.0000000000000000e+00;
_dPhit_ds[305] = 0.0000000000000000e+00;
_dPhit_ds[306] = 0.0000000000000000e+00;
_dPhit_ds[307] = 0.0000000000000000e+00;
_dPhit_ds[308] = 0.0000000000000000e+00;
_dPhit_ds[309] = 0.0000000000000000e+00;
_dPhit_ds[310] = 0.0000000000000000e+00;
_dPhit_ds[311] = 0.0000000000000000e+00;
_dPhit_ds[312] = 0.0000000000000000e+00;
_dPhit_ds[313] = 0.0000000000000000e+00;
_dPhit_ds[314] = 0.0000000000000000e+00;
_dPhit_ds[315] = 0.0000000000000000e+00;
_dPhit_ds[316] = 0.0000000000000000e+00;
_dPhit_ds[317] = 0.0000000000000000e+00;
_dPhit_ds[318] = 0.0000000000000000e+00;
_dPhit_ds[319] = 0.0000000000000000e+00;
_dPhit_ds[320] = 0.0000000000000000e+00;
_dPhit_ds[321] = 0.0000000000000000e+00;
_dPhit_ds[322] = 0.0000000000000000e+00;
_dPhit_ds[323] = 0.0000000000000000e+00;
_dPhit_ds[324] = 0.0000000000000000e+00;
_dPhit_ds[325] = 0.0000000000000000e+00;
_dPhit_ds[326] = 0.0000000000000000e+00;
_dPhit_ds[327] = 0.0000000000000000e+00;
_dPhit_ds[328] = -atom2431;
_dPhit_ds[329] = -atom2434+( atom2276+uW_RRR*atom1322+atom2273+atom1195*atom2237-dR_RRR-irrRRRz+atom1194*atom2244+zWAG+atom1175*atom2243-atom2317*atom2321)*( atom8345*atom2388+atom5132*atom2434)+atom2437*atom8345-atom2388*atom2435;
_dPhit_ds[330] =  atom5142*atom2283+atom2289*atom5145+atom5136*atom2286;
_dPhit_ds[331] =  atom2307*atom5145+atom5136*atom2303+atom2299*atom5142;
_dPhit_ds[332] = 0.0000000000000000e+00;
_dPhit_ds[333] = 0.0000000000000000e+00;
_dPhit_ds[334] = 0.0000000000000000e+00;
_dPhit_ds[335] = 0.0000000000000000e+00;
_dPhit_ds[336] = 0.0000000000000000e+00;
_dPhit_ds[337] = 0.0000000000000000e+00;
_dPhit_ds[338] = 0.0000000000000000e+00;
_dPhit_ds[339] = 0.0000000000000000e+00;
_dPhit_ds[340] = 0.0000000000000000e+00;
_dPhit_ds[341] = 0.0000000000000000e+00;
_dPhit_ds[342] = 0.0000000000000000e+00;
_dPhit_ds[343] = 0.0000000000000000e+00;
_dPhit_ds[344] = 0.0000000000000000e+00;
_dPhit_ds[345] = 0.0000000000000000e+00;
_dPhit_ds[346] = 0.0000000000000000e+00;
_dPhit_ds[347] = 0.0000000000000000e+00;
_dPhit_ds[348] = 0.0000000000000000e+00;
_dPhit_ds[349] = 0.0000000000000000e+00;
_dPhit_ds[350] = 0.0000000000000000e+00;
_dPhit_ds[351] = 0.0000000000000000e+00;
_dPhit_ds[352] = 0.0000000000000000e+00;
_dPhit_ds[353] = 0.0000000000000000e+00;
_dPhit_ds[354] = 0.0000000000000000e+00;
_dPhit_ds[355] = 0.0000000000000000e+00;
_dPhit_ds[356] = 0.0000000000000000e+00;
_dPhit_ds[357] = 0.0000000000000000e+00;
_dPhit_ds[358] = 0.0000000000000000e+00;
_dPhit_ds[359] = 0.0000000000000000e+00;
_dPhit_ds[360] = -atom5228*atom2431+atom2437*( atom2385*atom8298+atom2429*atom5236)-( atom2380+5.0000000000000000e-01*atom2350*atom5190*L_RAIL+1.0000000000000000e+00)*atom2430+( -5.0000000000000000e-01*atom2350*atom2354*L_RAIL+uW_RRR*atom1310+atom2244*atom1184+atom2243*atom1178+atom2266-xR_RRR+xWAG+atom2237*atom1187+atom2263)*( atom2383*atom8298+atom2429*atom5222);
_dPhit_ds[361] = -atom5228*atom2434;
_dPhit_ds[362] =  atom5240*atom2283+atom5247*atom2289+atom5226*atom2286;
_dPhit_ds[363] =  atom5247*atom2307+atom5240*atom2299+atom2303*atom5226;
_dPhit_ds[364] = 0.0000000000000000e+00;
_dPhit_ds[365] = 0.0000000000000000e+00;
_dPhit_ds[366] = 0.0000000000000000e+00;
_dPhit_ds[367] = 0.0000000000000000e+00;
_dPhit_ds[368] = 0.0000000000000000e+00;
_dPhit_ds[369] = 0.0000000000000000e+00;
_dPhit_ds[370] = 0.0000000000000000e+00;
_dPhit_ds[371] = 0.0000000000000000e+00;
_dPhit_ds[372] = 0.0000000000000000e+00;
_dPhit_ds[373] = 0.0000000000000000e+00;
_dPhit_ds[374] = 0.0000000000000000e+00;
_dPhit_ds[375] = 0.0000000000000000e+00;
_dPhit_ds[376] = 0.0000000000000000e+00;
_dPhit_ds[377] = 0.0000000000000000e+00;
_dPhit_ds[378] = 0.0000000000000000e+00;
_dPhit_ds[379] = 0.0000000000000000e+00;
_dPhit_ds[380] = 0.0000000000000000e+00;
_dPhit_ds[381] = 0.0000000000000000e+00;
_dPhit_ds[382] = 0.0000000000000000e+00;
_dPhit_ds[383] = 0.0000000000000000e+00;
_dPhit_ds[384] = 0.0000000000000000e+00;
_dPhit_ds[385] = 0.0000000000000000e+00;
_dPhit_ds[386] = 0.0000000000000000e+00;
_dPhit_ds[387] = 0.0000000000000000e+00;
_dPhit_ds[388] = 0.0000000000000000e+00;
_dPhit_ds[389] = 0.0000000000000000e+00;
_dPhit_ds[390] = 0.0000000000000000e+00;
_dPhit_ds[391] = 0.0000000000000000e+00;
_dPhit_ds[392] = 0.0000000000000000e+00;
_dPhit_ds[393] = 0.0000000000000000e+00;
_dPhit_ds[394] = 0.0000000000000000e+00;
_dPhit_ds[395] = 0.0000000000000000e+00;
_dPhit_ds[396] =  atom2537*atom2682+atom2681*atom2534;
_dPhit_ds[397] =  atom2537*atom2685+atom2686*atom2540;
_dPhit_ds[398] = -( atom2519+atom2522)*atom2676-atom2675*( atom2514+atom2517)-( atom2527+atom2524)*atom2677;
_dPhit_ds[399] = atom8750;
_dPhit_ds[400] = 0.0000000000000000e+00;
_dPhit_ds[401] = 0.0000000000000000e+00;
_dPhit_ds[402] = 0.0000000000000000e+00;
_dPhit_ds[403] = 0.0000000000000000e+00;
_dPhit_ds[404] = 0.0000000000000000e+00;
_dPhit_ds[405] = 0.0000000000000000e+00;
_dPhit_ds[406] = 0.0000000000000000e+00;
_dPhit_ds[407] = 0.0000000000000000e+00;
_dPhit_ds[408] = 0.0000000000000000e+00;
_dPhit_ds[409] = 0.0000000000000000e+00;
_dPhit_ds[410] = 0.0000000000000000e+00;
_dPhit_ds[411] = 0.0000000000000000e+00;
_dPhit_ds[412] = 0.0000000000000000e+00;
_dPhit_ds[413] = 0.0000000000000000e+00;
_dPhit_ds[414] = 0.0000000000000000e+00;
_dPhit_ds[415] = 0.0000000000000000e+00;
_dPhit_ds[416] = 0.0000000000000000e+00;
_dPhit_ds[417] = 0.0000000000000000e+00;
_dPhit_ds[418] = 0.0000000000000000e+00;
_dPhit_ds[419] = 0.0000000000000000e+00;
_dPhit_ds[420] = 0.0000000000000000e+00;
_dPhit_ds[421] = 0.0000000000000000e+00;
_dPhit_ds[422] = 0.0000000000000000e+00;
_dPhit_ds[423] = 0.0000000000000000e+00;
_dPhit_ds[424] = 0.0000000000000000e+00;
_dPhit_ds[425] = 0.0000000000000000e+00;
_dPhit_ds[426] = 0.0000000000000000e+00;
_dPhit_ds[427] = 0.0000000000000000e+00;
_dPhit_ds[428] =  atom2681*atom2550+atom2554*atom2682;
_dPhit_ds[429] =  atom2554*atom2685+atom2686*atom2558;
_dPhit_ds[430] = atom8750;
_dPhit_ds[431] =  ( atom1231*atom8847+atom8849*atom1313)*atom2675+atom2677*( atom8849*atom1325+atom1243*atom8847)+( atom8847*atom1237+atom1319*atom8849)*atom2676;
_dPhit_ds[432] = 0.0000000000000000e+00;
_dPhit_ds[433] = 0.0000000000000000e+00;
_dPhit_ds[434] = 0.0000000000000000e+00;
_dPhit_ds[435] = 0.0000000000000000e+00;
_dPhit_ds[436] = 0.0000000000000000e+00;
_dPhit_ds[437] = 0.0000000000000000e+00;
_dPhit_ds[438] = 0.0000000000000000e+00;
_dPhit_ds[439] = 0.0000000000000000e+00;
_dPhit_ds[440] = 0.0000000000000000e+00;
_dPhit_ds[441] = 0.0000000000000000e+00;
_dPhit_ds[442] = 0.0000000000000000e+00;
_dPhit_ds[443] = 0.0000000000000000e+00;
_dPhit_ds[444] = 0.0000000000000000e+00;
_dPhit_ds[445] = 0.0000000000000000e+00;
_dPhit_ds[446] = 0.0000000000000000e+00;
_dPhit_ds[447] = 0.0000000000000000e+00;
_dPhit_ds[448] = 0.0000000000000000e+00;
_dPhit_ds[449] = 0.0000000000000000e+00;
_dPhit_ds[450] = 0.0000000000000000e+00;
_dPhit_ds[451] = 0.0000000000000000e+00;
_dPhit_ds[452] = 0.0000000000000000e+00;
_dPhit_ds[453] = 0.0000000000000000e+00;
_dPhit_ds[454] = 0.0000000000000000e+00;
_dPhit_ds[455] = 0.0000000000000000e+00;
_dPhit_ds[456] = 0.0000000000000000e+00;
_dPhit_ds[457] = 0.0000000000000000e+00;
_dPhit_ds[458] = 0.0000000000000000e+00;
_dPhit_ds[459] = 0.0000000000000000e+00;
_dPhit_ds[460] = -atom2682;
_dPhit_ds[461] = -atom2686*atom2639+atom8651*atom2688+( atom8651*atom2639+atom5523*atom2685)*( atom1195*atom2488+uW_RRL*atom1322+atom2527+atom1175*atom2494-atom2572*atom2568+atom2524+zWAG-dR_RRL-irrRRLz+atom1194*atom2495)-atom2685;
_dPhit_ds[462] =  atom2537*atom5527+atom2540*atom5516+atom2534*atom5533;
_dPhit_ds[463] =  atom2554*atom5527+atom5533*atom2550+atom2558*atom5516;
_dPhit_ds[464] = 0.0000000000000000e+00;
_dPhit_ds[465] = 0.0000000000000000e+00;
_dPhit_ds[466] = 0.0000000000000000e+00;
_dPhit_ds[467] = 0.0000000000000000e+00;
_dPhit_ds[468] = 0.0000000000000000e+00;
_dPhit_ds[469] = 0.0000000000000000e+00;
_dPhit_ds[470] = 0.0000000000000000e+00;
_dPhit_ds[471] = 0.0000000000000000e+00;
_dPhit_ds[472] = 0.0000000000000000e+00;
_dPhit_ds[473] = 0.0000000000000000e+00;
_dPhit_ds[474] = 0.0000000000000000e+00;
_dPhit_ds[475] = 0.0000000000000000e+00;
_dPhit_ds[476] = 0.0000000000000000e+00;
_dPhit_ds[477] = 0.0000000000000000e+00;
_dPhit_ds[478] = 0.0000000000000000e+00;
_dPhit_ds[479] = 0.0000000000000000e+00;
_dPhit_ds[480] = 0.0000000000000000e+00;
_dPhit_ds[481] = 0.0000000000000000e+00;
_dPhit_ds[482] = 0.0000000000000000e+00;
_dPhit_ds[483] = 0.0000000000000000e+00;
_dPhit_ds[484] = 0.0000000000000000e+00;
_dPhit_ds[485] = 0.0000000000000000e+00;
_dPhit_ds[486] = 0.0000000000000000e+00;
_dPhit_ds[487] = 0.0000000000000000e+00;
_dPhit_ds[488] = 0.0000000000000000e+00;
_dPhit_ds[489] = 0.0000000000000000e+00;
_dPhit_ds[490] = 0.0000000000000000e+00;
_dPhit_ds[491] = 0.0000000000000000e+00;
_dPhit_ds[492] = -atom2682*atom5619+( 5.0000000000000000e-01*atom2605*atom2601*L_RAIL+atom1184*atom2495+atom2514+uW_RRL*atom1310+atom2488*atom1187+xWAG+atom2517-xR_RRL+atom2494*atom1178)*( atom2634*atom8604+atom5584*atom2680)-( atom2631+-5.0000000000000000e-01*atom2601*atom5552*L_RAIL+1.0000000000000000e+00)*atom2681+( atom8604*atom2636+atom5624*atom2680)*atom2688;
_dPhit_ds[493] = -atom2685*atom5619;
_dPhit_ds[494] =  atom2537*atom5617+atom2534*atom5628+atom2540*atom5612;
_dPhit_ds[495] =  atom2554*atom5617+atom2558*atom5612+atom5628*atom2550;
_dPhit_ds[496] = 0.0000000000000000e+00;
_dPhit_ds[497] = 0.0000000000000000e+00;
_dPhit_ds[498] = 0.0000000000000000e+00;
_dPhit_ds[499] = 0.0000000000000000e+00;
_dPhit_ds[500] = 0.0000000000000000e+00;
_dPhit_ds[501] = 0.0000000000000000e+00;
_dPhit_ds[502] = 0.0000000000000000e+00;
_dPhit_ds[503] = 0.0000000000000000e+00;
_dPhit_ds[504] = 0.0000000000000000e+00;
_dPhit_ds[505] = 0.0000000000000000e+00;
_dPhit_ds[506] = 0.0000000000000000e+00;
_dPhit_ds[507] = 0.0000000000000000e+00;
_dPhit_ds[508] = 0.0000000000000000e+00;
_dPhit_ds[509] = 0.0000000000000000e+00;
_dPhit_ds[510] = 0.0000000000000000e+00;
_dPhit_ds[511] = 0.0000000000000000e+00;
_dPhit_ds[512] = 0.0000000000000000e+00;
_dPhit_ds[513] = 0.0000000000000000e+00;
_dPhit_ds[514] = 0.0000000000000000e+00;
_dPhit_ds[515] = 0.0000000000000000e+00;
_dPhit_ds[516] = 0.0000000000000000e+00;
_dPhit_ds[517] = 0.0000000000000000e+00;
_dPhit_ds[518] = 0.0000000000000000e+00;
_dPhit_ds[519] = 0.0000000000000000e+00;
_dPhit_ds[520] = 0.0000000000000000e+00;
_dPhit_ds[521] = 0.0000000000000000e+00;
_dPhit_ds[522] = 0.0000000000000000e+00;
_dPhit_ds[523] = 0.0000000000000000e+00;
_dPhit_ds[524] = 0.0000000000000000e+00;
_dPhit_ds[525] = 0.0000000000000000e+00;
_dPhit_ds[526] = 0.0000000000000000e+00;
_dPhit_ds[527] = 0.0000000000000000e+00;
_dPhit_ds[528] =  atom2795*atom2940+atom2792*atom2939;
_dPhit_ds[529] =  atom2795*atom2943+atom2798*atom2944;
_dPhit_ds[530] = -atom2934*( atom2780+atom2777)-( atom2782+atom2785)*atom2935-( atom2775+atom2772)*atom2933;
_dPhit_ds[531] = atom9056;
_dPhit_ds[532] = 0.0000000000000000e+00;
_dPhit_ds[533] = 0.0000000000000000e+00;
_dPhit_ds[534] = 0.0000000000000000e+00;
_dPhit_ds[535] = 0.0000000000000000e+00;
_dPhit_ds[536] = 0.0000000000000000e+00;
_dPhit_ds[537] = 0.0000000000000000e+00;
_dPhit_ds[538] = 0.0000000000000000e+00;
_dPhit_ds[539] = 0.0000000000000000e+00;
_dPhit_ds[540] = 0.0000000000000000e+00;
_dPhit_ds[541] = 0.0000000000000000e+00;
_dPhit_ds[542] = 0.0000000000000000e+00;
_dPhit_ds[543] = 0.0000000000000000e+00;
_dPhit_ds[544] = 0.0000000000000000e+00;
_dPhit_ds[545] = 0.0000000000000000e+00;
_dPhit_ds[546] = 0.0000000000000000e+00;
_dPhit_ds[547] = 0.0000000000000000e+00;
_dPhit_ds[548] = 0.0000000000000000e+00;
_dPhit_ds[549] = 0.0000000000000000e+00;
_dPhit_ds[550] = 0.0000000000000000e+00;
_dPhit_ds[551] = 0.0000000000000000e+00;
_dPhit_ds[552] = 0.0000000000000000e+00;
_dPhit_ds[553] = 0.0000000000000000e+00;
_dPhit_ds[554] = 0.0000000000000000e+00;
_dPhit_ds[555] = 0.0000000000000000e+00;
_dPhit_ds[556] = 0.0000000000000000e+00;
_dPhit_ds[557] = 0.0000000000000000e+00;
_dPhit_ds[558] = 0.0000000000000000e+00;
_dPhit_ds[559] = 0.0000000000000000e+00;
_dPhit_ds[560] =  atom2939*atom2808+atom2812*atom2940;
_dPhit_ds[561] =  atom2816*atom2944+atom2943*atom2812;
_dPhit_ds[562] = atom9056;
_dPhit_ds[563] =  atom2934*( atom9155*atom1524+atom9153*atom1568)+( atom9155*atom1518+atom9153*atom1562)*atom2933+atom2935*( atom9153*atom1574+atom1530*atom9155);
_dPhit_ds[564] = 0.0000000000000000e+00;
_dPhit_ds[565] = 0.0000000000000000e+00;
_dPhit_ds[566] = 0.0000000000000000e+00;
_dPhit_ds[567] = 0.0000000000000000e+00;
_dPhit_ds[568] = 0.0000000000000000e+00;
_dPhit_ds[569] = 0.0000000000000000e+00;
_dPhit_ds[570] = 0.0000000000000000e+00;
_dPhit_ds[571] = 0.0000000000000000e+00;
_dPhit_ds[572] = 0.0000000000000000e+00;
_dPhit_ds[573] = 0.0000000000000000e+00;
_dPhit_ds[574] = 0.0000000000000000e+00;
_dPhit_ds[575] = 0.0000000000000000e+00;
_dPhit_ds[576] = 0.0000000000000000e+00;
_dPhit_ds[577] = 0.0000000000000000e+00;
_dPhit_ds[578] = 0.0000000000000000e+00;
_dPhit_ds[579] = 0.0000000000000000e+00;
_dPhit_ds[580] = 0.0000000000000000e+00;
_dPhit_ds[581] = 0.0000000000000000e+00;
_dPhit_ds[582] = 0.0000000000000000e+00;
_dPhit_ds[583] = 0.0000000000000000e+00;
_dPhit_ds[584] = 0.0000000000000000e+00;
_dPhit_ds[585] = 0.0000000000000000e+00;
_dPhit_ds[586] = 0.0000000000000000e+00;
_dPhit_ds[587] = 0.0000000000000000e+00;
_dPhit_ds[588] = 0.0000000000000000e+00;
_dPhit_ds[589] = 0.0000000000000000e+00;
_dPhit_ds[590] = 0.0000000000000000e+00;
_dPhit_ds[591] = 0.0000000000000000e+00;
_dPhit_ds[592] = -atom2940;
_dPhit_ds[593] = -atom2944*atom2897+atom2946*atom8957-atom2943+( atom2753*atom1194+atom2746*atom1195+atom1571*uW_FFR+atom2782-irrFFRz-atom2830*atom2826+atom1175*atom2752+zWAG+atom2785-dR_FFR)*( atom8957*atom2897+atom2943*atom6098);
_dPhit_ds[594] =  atom6168*atom2798+atom2795*atom6159+atom2792*atom6165;
_dPhit_ds[595] =  atom2816*atom6168+atom6165*atom2808+atom6159*atom2812;
_dPhit_ds[596] = 0.0000000000000000e+00;
_dPhit_ds[597] = 0.0000000000000000e+00;
_dPhit_ds[598] = 0.0000000000000000e+00;
_dPhit_ds[599] = 0.0000000000000000e+00;
_dPhit_ds[600] = 0.0000000000000000e+00;
_dPhit_ds[601] = 0.0000000000000000e+00;
_dPhit_ds[602] = 0.0000000000000000e+00;
_dPhit_ds[603] = 0.0000000000000000e+00;
_dPhit_ds[604] = 0.0000000000000000e+00;
_dPhit_ds[605] = 0.0000000000000000e+00;
_dPhit_ds[606] = 0.0000000000000000e+00;
_dPhit_ds[607] = 0.0000000000000000e+00;
_dPhit_ds[608] = 0.0000000000000000e+00;
_dPhit_ds[609] = 0.0000000000000000e+00;
_dPhit_ds[610] = 0.0000000000000000e+00;
_dPhit_ds[611] = 0.0000000000000000e+00;
_dPhit_ds[612] = 0.0000000000000000e+00;
_dPhit_ds[613] = 0.0000000000000000e+00;
_dPhit_ds[614] = 0.0000000000000000e+00;
_dPhit_ds[615] = 0.0000000000000000e+00;
_dPhit_ds[616] = 0.0000000000000000e+00;
_dPhit_ds[617] = 0.0000000000000000e+00;
_dPhit_ds[618] = 0.0000000000000000e+00;
_dPhit_ds[619] = 0.0000000000000000e+00;
_dPhit_ds[620] = 0.0000000000000000e+00;
_dPhit_ds[621] = 0.0000000000000000e+00;
_dPhit_ds[622] = 0.0000000000000000e+00;
_dPhit_ds[623] = 0.0000000000000000e+00;
_dPhit_ds[624] =  ( atom2894*atom8910+atom6245*atom2938)*atom2946-( xR_FFR+5.0000000000000000e-01*atom2859*atom2863*L_RAIL-atom2775-atom2752*atom1178-atom2746*atom1187-atom1559*uW_FFR-atom2772-atom2753*atom1184-xWAG)*( atom8910*atom2892+atom6205*atom2938)-atom6237*atom2940-( atom2889+5.0000000000000000e-01*atom6186*atom2859*L_RAIL+1.0000000000000000e+00)*atom2939;
_dPhit_ds[625] = -atom2943*atom6237;
_dPhit_ds[626] =  atom2795*atom6235+atom6256*atom2798+atom2792*atom6249;
_dPhit_ds[627] =  atom2808*atom6249+atom6235*atom2812+atom6256*atom2816;
_dPhit_ds[628] = 0.0000000000000000e+00;
_dPhit_ds[629] = 0.0000000000000000e+00;
_dPhit_ds[630] = 0.0000000000000000e+00;
_dPhit_ds[631] = 0.0000000000000000e+00;
_dPhit_ds[632] = 0.0000000000000000e+00;
_dPhit_ds[633] = 0.0000000000000000e+00;
_dPhit_ds[634] = 0.0000000000000000e+00;
_dPhit_ds[635] = 0.0000000000000000e+00;
_dPhit_ds[636] = 0.0000000000000000e+00;
_dPhit_ds[637] = 0.0000000000000000e+00;
_dPhit_ds[638] = 0.0000000000000000e+00;
_dPhit_ds[639] = 0.0000000000000000e+00;
_dPhit_ds[640] = 0.0000000000000000e+00;
_dPhit_ds[641] = 0.0000000000000000e+00;
_dPhit_ds[642] = 0.0000000000000000e+00;
_dPhit_ds[643] = 0.0000000000000000e+00;
_dPhit_ds[644] = 0.0000000000000000e+00;
_dPhit_ds[645] = 0.0000000000000000e+00;
_dPhit_ds[646] = 0.0000000000000000e+00;
_dPhit_ds[647] = 0.0000000000000000e+00;
_dPhit_ds[648] = 0.0000000000000000e+00;
_dPhit_ds[649] = 0.0000000000000000e+00;
_dPhit_ds[650] = 0.0000000000000000e+00;
_dPhit_ds[651] = 0.0000000000000000e+00;
_dPhit_ds[652] = 0.0000000000000000e+00;
_dPhit_ds[653] = 0.0000000000000000e+00;
_dPhit_ds[654] = 0.0000000000000000e+00;
_dPhit_ds[655] = 0.0000000000000000e+00;
_dPhit_ds[656] = 0.0000000000000000e+00;
_dPhit_ds[657] = 0.0000000000000000e+00;
_dPhit_ds[658] = 0.0000000000000000e+00;
_dPhit_ds[659] = 0.0000000000000000e+00;
_dPhit_ds[660] =  atom3190*atom3043+atom3046*atom3191;
_dPhit_ds[661] =  atom3049*atom3195+atom3194*atom3046;
_dPhit_ds[662] = -( atom3023+atom3026)*atom3184-atom3185*( atom3031+atom3028)-atom3186*( atom3036+atom3033);
_dPhit_ds[663] = atom9362;
_dPhit_ds[664] = 0.0000000000000000e+00;
_dPhit_ds[665] = 0.0000000000000000e+00;
_dPhit_ds[666] = 0.0000000000000000e+00;
_dPhit_ds[667] = 0.0000000000000000e+00;
_dPhit_ds[668] = 0.0000000000000000e+00;
_dPhit_ds[669] = 0.0000000000000000e+00;
_dPhit_ds[670] = 0.0000000000000000e+00;
_dPhit_ds[671] = 0.0000000000000000e+00;
_dPhit_ds[672] = 0.0000000000000000e+00;
_dPhit_ds[673] = 0.0000000000000000e+00;
_dPhit_ds[674] = 0.0000000000000000e+00;
_dPhit_ds[675] = 0.0000000000000000e+00;
_dPhit_ds[676] = 0.0000000000000000e+00;
_dPhit_ds[677] = 0.0000000000000000e+00;
_dPhit_ds[678] = 0.0000000000000000e+00;
_dPhit_ds[679] = 0.0000000000000000e+00;
_dPhit_ds[680] = 0.0000000000000000e+00;
_dPhit_ds[681] = 0.0000000000000000e+00;
_dPhit_ds[682] = 0.0000000000000000e+00;
_dPhit_ds[683] = 0.0000000000000000e+00;
_dPhit_ds[684] = 0.0000000000000000e+00;
_dPhit_ds[685] = 0.0000000000000000e+00;
_dPhit_ds[686] = 0.0000000000000000e+00;
_dPhit_ds[687] = 0.0000000000000000e+00;
_dPhit_ds[688] = 0.0000000000000000e+00;
_dPhit_ds[689] = 0.0000000000000000e+00;
_dPhit_ds[690] = 0.0000000000000000e+00;
_dPhit_ds[691] = 0.0000000000000000e+00;
_dPhit_ds[692] =  atom3190*atom3059+atom3063*atom3191;
_dPhit_ds[693] =  atom3067*atom3195+atom3194*atom3063;
_dPhit_ds[694] = atom9362;
_dPhit_ds[695] =  ( atom9459*atom1568+atom9461*atom1524)*atom3185+( atom9459*atom1562+atom9461*atom1518)*atom3184+atom3186*( atom9459*atom1574+atom1530*atom9461);
_dPhit_ds[696] = 0.0000000000000000e+00;
_dPhit_ds[697] = 0.0000000000000000e+00;
_dPhit_ds[698] = 0.0000000000000000e+00;
_dPhit_ds[699] = 0.0000000000000000e+00;
_dPhit_ds[700] = 0.0000000000000000e+00;
_dPhit_ds[701] = 0.0000000000000000e+00;
_dPhit_ds[702] = 0.0000000000000000e+00;
_dPhit_ds[703] = 0.0000000000000000e+00;
_dPhit_ds[704] = 0.0000000000000000e+00;
_dPhit_ds[705] = 0.0000000000000000e+00;
_dPhit_ds[706] = 0.0000000000000000e+00;
_dPhit_ds[707] = 0.0000000000000000e+00;
_dPhit_ds[708] = 0.0000000000000000e+00;
_dPhit_ds[709] = 0.0000000000000000e+00;
_dPhit_ds[710] = 0.0000000000000000e+00;
_dPhit_ds[711] = 0.0000000000000000e+00;
_dPhit_ds[712] = 0.0000000000000000e+00;
_dPhit_ds[713] = 0.0000000000000000e+00;
_dPhit_ds[714] = 0.0000000000000000e+00;
_dPhit_ds[715] = 0.0000000000000000e+00;
_dPhit_ds[716] = 0.0000000000000000e+00;
_dPhit_ds[717] = 0.0000000000000000e+00;
_dPhit_ds[718] = 0.0000000000000000e+00;
_dPhit_ds[719] = 0.0000000000000000e+00;
_dPhit_ds[720] = 0.0000000000000000e+00;
_dPhit_ds[721] = 0.0000000000000000e+00;
_dPhit_ds[722] = 0.0000000000000000e+00;
_dPhit_ds[723] = 0.0000000000000000e+00;
_dPhit_ds[724] = -atom3191;
_dPhit_ds[725] =  ( atom3194*atom6532+atom9263*atom3148)*( uW_FFL*atom1571+atom3004*atom1194+atom1175*atom3003+atom3036-dR_FFL-irrFFLz-atom3081*atom3077+zWAG+atom3033+atom2997*atom1195)-atom3194-atom3195*atom3148+atom9263*atom3197;
_dPhit_ds[726] =  atom6536*atom3043+atom3049*atom6525+atom6541*atom3046;
_dPhit_ds[727] =  atom6536*atom3059+atom3067*atom6525+atom6541*atom3063;
_dPhit_ds[728] = 0.0000000000000000e+00;
_dPhit_ds[729] = 0.0000000000000000e+00;
_dPhit_ds[730] = 0.0000000000000000e+00;
_dPhit_ds[731] = 0.0000000000000000e+00;
_dPhit_ds[732] = 0.0000000000000000e+00;
_dPhit_ds[733] = 0.0000000000000000e+00;
_dPhit_ds[734] = 0.0000000000000000e+00;
_dPhit_ds[735] = 0.0000000000000000e+00;
_dPhit_ds[736] = 0.0000000000000000e+00;
_dPhit_ds[737] = 0.0000000000000000e+00;
_dPhit_ds[738] = 0.0000000000000000e+00;
_dPhit_ds[739] = 0.0000000000000000e+00;
_dPhit_ds[740] = 0.0000000000000000e+00;
_dPhit_ds[741] = 0.0000000000000000e+00;
_dPhit_ds[742] = 0.0000000000000000e+00;
_dPhit_ds[743] = 0.0000000000000000e+00;
_dPhit_ds[744] = 0.0000000000000000e+00;
_dPhit_ds[745] = 0.0000000000000000e+00;
_dPhit_ds[746] = 0.0000000000000000e+00;
_dPhit_ds[747] = 0.0000000000000000e+00;
_dPhit_ds[748] = 0.0000000000000000e+00;
_dPhit_ds[749] = 0.0000000000000000e+00;
_dPhit_ds[750] = 0.0000000000000000e+00;
_dPhit_ds[751] = 0.0000000000000000e+00;
_dPhit_ds[752] = 0.0000000000000000e+00;
_dPhit_ds[753] = 0.0000000000000000e+00;
_dPhit_ds[754] = 0.0000000000000000e+00;
_dPhit_ds[755] = 0.0000000000000000e+00;
_dPhit_ds[756] = -atom3190*( atom3141+-5.0000000000000000e-01*atom3110*atom6598*L_RAIL+1.0000000000000000e+00)+( atom9216*atom3143+atom3189*atom6617)*( 5.0000000000000000e-01*atom3110*atom3114*L_RAIL+atom3023+uW_FFL*atom1559+atom2997*atom1187-xR_FFL+atom3003*atom1178+atom3004*atom1184+atom3026+xWAG)+( atom3189*atom6626+atom9216*atom3145)*atom3197-atom3191*atom6639;
_dPhit_ds[757] = -atom3194*atom6639;
_dPhit_ds[758] =  atom3043*atom6630+atom3046*atom6637+atom3049*atom6620;
_dPhit_ds[759] =  atom6637*atom3063+atom3059*atom6630+atom3067*atom6620;
_dPhit_ds[760] = 0.0000000000000000e+00;
_dPhit_ds[761] = 0.0000000000000000e+00;
_dPhit_ds[762] = 0.0000000000000000e+00;
_dPhit_ds[763] = 0.0000000000000000e+00;
_dPhit_ds[764] = 0.0000000000000000e+00;
_dPhit_ds[765] = 0.0000000000000000e+00;
_dPhit_ds[766] = 0.0000000000000000e+00;
_dPhit_ds[767] = 0.0000000000000000e+00;
_dPhit_ds[768] = 0.0000000000000000e+00;
_dPhit_ds[769] = 0.0000000000000000e+00;
_dPhit_ds[770] = 0.0000000000000000e+00;
_dPhit_ds[771] = 0.0000000000000000e+00;
_dPhit_ds[772] = 0.0000000000000000e+00;
_dPhit_ds[773] = 0.0000000000000000e+00;
_dPhit_ds[774] = 0.0000000000000000e+00;
_dPhit_ds[775] = 0.0000000000000000e+00;
_dPhit_ds[776] = 0.0000000000000000e+00;
_dPhit_ds[777] = 0.0000000000000000e+00;
_dPhit_ds[778] = 0.0000000000000000e+00;
_dPhit_ds[779] = 0.0000000000000000e+00;
_dPhit_ds[780] = 0.0000000000000000e+00;
_dPhit_ds[781] = 0.0000000000000000e+00;
_dPhit_ds[782] = 0.0000000000000000e+00;
_dPhit_ds[783] = 0.0000000000000000e+00;
_dPhit_ds[784] = 0.0000000000000000e+00;
_dPhit_ds[785] = 0.0000000000000000e+00;
_dPhit_ds[786] = 0.0000000000000000e+00;
_dPhit_ds[787] = 0.0000000000000000e+00;
_dPhit_ds[788] = 0.0000000000000000e+00;
_dPhit_ds[789] = 0.0000000000000000e+00;
_dPhit_ds[790] = 0.0000000000000000e+00;
_dPhit_ds[791] = 0.0000000000000000e+00;
_dPhit_ds[792] =  atom3299*atom3445+atom3446*atom3302;
_dPhit_ds[793] =  atom3450*atom3305+atom3302*atom3449;
_dPhit_ds[794] = -( atom3289+atom3292)*atom3441-( atom3282+atom3279)*atom3439-atom3440*( atom3287+atom3284);
_dPhit_ds[795] = atom9668;
_dPhit_ds[796] = 0.0000000000000000e+00;
_dPhit_ds[797] = 0.0000000000000000e+00;
_dPhit_ds[798] = 0.0000000000000000e+00;
_dPhit_ds[799] = 0.0000000000000000e+00;
_dPhit_ds[800] = 0.0000000000000000e+00;
_dPhit_ds[801] = 0.0000000000000000e+00;
_dPhit_ds[802] = 0.0000000000000000e+00;
_dPhit_ds[803] = 0.0000000000000000e+00;
_dPhit_ds[804] = 0.0000000000000000e+00;
_dPhit_ds[805] = 0.0000000000000000e+00;
_dPhit_ds[806] = 0.0000000000000000e+00;
_dPhit_ds[807] = 0.0000000000000000e+00;
_dPhit_ds[808] = 0.0000000000000000e+00;
_dPhit_ds[809] = 0.0000000000000000e+00;
_dPhit_ds[810] = 0.0000000000000000e+00;
_dPhit_ds[811] = 0.0000000000000000e+00;
_dPhit_ds[812] = 0.0000000000000000e+00;
_dPhit_ds[813] = 0.0000000000000000e+00;
_dPhit_ds[814] = 0.0000000000000000e+00;
_dPhit_ds[815] = 0.0000000000000000e+00;
_dPhit_ds[816] = 0.0000000000000000e+00;
_dPhit_ds[817] = 0.0000000000000000e+00;
_dPhit_ds[818] = 0.0000000000000000e+00;
_dPhit_ds[819] = 0.0000000000000000e+00;
_dPhit_ds[820] = 0.0000000000000000e+00;
_dPhit_ds[821] = 0.0000000000000000e+00;
_dPhit_ds[822] = 0.0000000000000000e+00;
_dPhit_ds[823] = 0.0000000000000000e+00;
_dPhit_ds[824] =  atom3446*atom3318+atom3314*atom3445;
_dPhit_ds[825] =  atom3318*atom3449+atom3450*atom3322;
_dPhit_ds[826] = atom9668;
_dPhit_ds[827] =  atom3440*( atom1604*atom9767+atom9765*atom1524)+( atom1610*atom9767+atom1530*atom9765)*atom3441+( atom9765*atom1518+atom1598*atom9767)*atom3439;
_dPhit_ds[828] = 0.0000000000000000e+00;
_dPhit_ds[829] = 0.0000000000000000e+00;
_dPhit_ds[830] = 0.0000000000000000e+00;
_dPhit_ds[831] = 0.0000000000000000e+00;
_dPhit_ds[832] = 0.0000000000000000e+00;
_dPhit_ds[833] = 0.0000000000000000e+00;
_dPhit_ds[834] = 0.0000000000000000e+00;
_dPhit_ds[835] = 0.0000000000000000e+00;
_dPhit_ds[836] = 0.0000000000000000e+00;
_dPhit_ds[837] = 0.0000000000000000e+00;
_dPhit_ds[838] = 0.0000000000000000e+00;
_dPhit_ds[839] = 0.0000000000000000e+00;
_dPhit_ds[840] = 0.0000000000000000e+00;
_dPhit_ds[841] = 0.0000000000000000e+00;
_dPhit_ds[842] = 0.0000000000000000e+00;
_dPhit_ds[843] = 0.0000000000000000e+00;
_dPhit_ds[844] = 0.0000000000000000e+00;
_dPhit_ds[845] = 0.0000000000000000e+00;
_dPhit_ds[846] = 0.0000000000000000e+00;
_dPhit_ds[847] = 0.0000000000000000e+00;
_dPhit_ds[848] = 0.0000000000000000e+00;
_dPhit_ds[849] = 0.0000000000000000e+00;
_dPhit_ds[850] = 0.0000000000000000e+00;
_dPhit_ds[851] = 0.0000000000000000e+00;
_dPhit_ds[852] = 0.0000000000000000e+00;
_dPhit_ds[853] = 0.0000000000000000e+00;
_dPhit_ds[854] = 0.0000000000000000e+00;
_dPhit_ds[855] = 0.0000000000000000e+00;
_dPhit_ds[856] = -atom3446;
_dPhit_ds[857] = -atom3450*atom3403+( atom7020*atom3449+atom9569*atom3403)*( atom1175*atom3259+atom3289-atom3332*atom3336+atom1194*atom3260-dR_FRR+atom1607*uW_FRR-irrFRRz+zWAG+atom3292+atom3253*atom1195)+atom3452*atom9569-atom3449;
_dPhit_ds[858] =  atom3305*atom7013+atom7024*atom3302+atom3299*atom7030;
_dPhit_ds[859] =  atom3314*atom7030+atom3318*atom7024+atom3322*atom7013;
_dPhit_ds[860] = 0.0000000000000000e+00;
_dPhit_ds[861] = 0.0000000000000000e+00;
_dPhit_ds[862] = 0.0000000000000000e+00;
_dPhit_ds[863] = 0.0000000000000000e+00;
_dPhit_ds[864] = 0.0000000000000000e+00;
_dPhit_ds[865] = 0.0000000000000000e+00;
_dPhit_ds[866] = 0.0000000000000000e+00;
_dPhit_ds[867] = 0.0000000000000000e+00;
_dPhit_ds[868] = 0.0000000000000000e+00;
_dPhit_ds[869] = 0.0000000000000000e+00;
_dPhit_ds[870] = 0.0000000000000000e+00;
_dPhit_ds[871] = 0.0000000000000000e+00;
_dPhit_ds[872] = 0.0000000000000000e+00;
_dPhit_ds[873] = 0.0000000000000000e+00;
_dPhit_ds[874] = 0.0000000000000000e+00;
_dPhit_ds[875] = 0.0000000000000000e+00;
_dPhit_ds[876] = 0.0000000000000000e+00;
_dPhit_ds[877] = 0.0000000000000000e+00;
_dPhit_ds[878] = 0.0000000000000000e+00;
_dPhit_ds[879] = 0.0000000000000000e+00;
_dPhit_ds[880] = 0.0000000000000000e+00;
_dPhit_ds[881] = 0.0000000000000000e+00;
_dPhit_ds[882] = 0.0000000000000000e+00;
_dPhit_ds[883] = 0.0000000000000000e+00;
_dPhit_ds[884] = 0.0000000000000000e+00;
_dPhit_ds[885] = 0.0000000000000000e+00;
_dPhit_ds[886] = 0.0000000000000000e+00;
_dPhit_ds[887] = 0.0000000000000000e+00;
_dPhit_ds[888] = -atom3446*atom7115-atom3445*( 5.0000000000000000e-01*atom7048*atom3365*L_RAIL+atom3395+1.0000000000000000e+00)+( atom3444*atom7123+atom3400*atom9522)*atom3452+( atom3260*atom1184+atom3253*atom1187+uW_FRR*atom1595+atom3282+atom3279+atom3259*atom1178-xR_FRR+-5.0000000000000000e-01*atom3369*atom3365*L_RAIL+xWAG)*( atom3444*atom7080+atom9522*atom3398);
_dPhit_ds[889] = -atom3449*atom7115;
_dPhit_ds[890] =  atom7113*atom3302+atom7108*atom3305+atom3299*atom7127;
_dPhit_ds[891] =  atom7113*atom3318+atom3314*atom7127+atom7108*atom3322;
_dPhit_ds[892] = 0.0000000000000000e+00;
_dPhit_ds[893] = 0.0000000000000000e+00;
_dPhit_ds[894] = 0.0000000000000000e+00;
_dPhit_ds[895] = 0.0000000000000000e+00;
_dPhit_ds[896] = 0.0000000000000000e+00;
_dPhit_ds[897] = 0.0000000000000000e+00;
_dPhit_ds[898] = 0.0000000000000000e+00;
_dPhit_ds[899] = 0.0000000000000000e+00;
_dPhit_ds[900] = 0.0000000000000000e+00;
_dPhit_ds[901] = 0.0000000000000000e+00;
_dPhit_ds[902] = 0.0000000000000000e+00;
_dPhit_ds[903] = 0.0000000000000000e+00;
_dPhit_ds[904] = 0.0000000000000000e+00;
_dPhit_ds[905] = 0.0000000000000000e+00;
_dPhit_ds[906] = 0.0000000000000000e+00;
_dPhit_ds[907] = 0.0000000000000000e+00;
_dPhit_ds[908] = 0.0000000000000000e+00;
_dPhit_ds[909] = 0.0000000000000000e+00;
_dPhit_ds[910] = 0.0000000000000000e+00;
_dPhit_ds[911] = 0.0000000000000000e+00;
_dPhit_ds[912] = 0.0000000000000000e+00;
_dPhit_ds[913] = 0.0000000000000000e+00;
_dPhit_ds[914] = 0.0000000000000000e+00;
_dPhit_ds[915] = 0.0000000000000000e+00;
_dPhit_ds[916] = 0.0000000000000000e+00;
_dPhit_ds[917] = 0.0000000000000000e+00;
_dPhit_ds[918] = 0.0000000000000000e+00;
_dPhit_ds[919] = 0.0000000000000000e+00;
_dPhit_ds[920] = 0.0000000000000000e+00;
_dPhit_ds[921] = 0.0000000000000000e+00;
_dPhit_ds[922] = 0.0000000000000000e+00;
_dPhit_ds[923] = 0.0000000000000000e+00;
_dPhit_ds[924] =  atom3549*atom3695+atom3552*atom3696;
_dPhit_ds[925] =  atom3700*atom3555+atom3552*atom3699;
_dPhit_ds[926] = -atom3690*( atom3537+atom3534)-( atom3532+atom3529)*atom3689-atom3691*( atom3539+atom3542);
_dPhit_ds[927] = atom9974;
_dPhit_ds[928] = 0.0000000000000000e+00;
_dPhit_ds[929] = 0.0000000000000000e+00;
_dPhit_ds[930] = 0.0000000000000000e+00;
_dPhit_ds[931] = 0.0000000000000000e+00;
_dPhit_ds[932] = 0.0000000000000000e+00;
_dPhit_ds[933] = 0.0000000000000000e+00;
_dPhit_ds[934] = 0.0000000000000000e+00;
_dPhit_ds[935] = 0.0000000000000000e+00;
_dPhit_ds[936] = 0.0000000000000000e+00;
_dPhit_ds[937] = 0.0000000000000000e+00;
_dPhit_ds[938] = 0.0000000000000000e+00;
_dPhit_ds[939] = 0.0000000000000000e+00;
_dPhit_ds[940] = 0.0000000000000000e+00;
_dPhit_ds[941] = 0.0000000000000000e+00;
_dPhit_ds[942] = 0.0000000000000000e+00;
_dPhit_ds[943] = 0.0000000000000000e+00;
_dPhit_ds[944] = 0.0000000000000000e+00;
_dPhit_ds[945] = 0.0000000000000000e+00;
_dPhit_ds[946] = 0.0000000000000000e+00;
_dPhit_ds[947] = 0.0000000000000000e+00;
_dPhit_ds[948] = 0.0000000000000000e+00;
_dPhit_ds[949] = 0.0000000000000000e+00;
_dPhit_ds[950] = 0.0000000000000000e+00;
_dPhit_ds[951] = 0.0000000000000000e+00;
_dPhit_ds[952] = 0.0000000000000000e+00;
_dPhit_ds[953] = 0.0000000000000000e+00;
_dPhit_ds[954] = 0.0000000000000000e+00;
_dPhit_ds[955] = 0.0000000000000000e+00;
_dPhit_ds[956] =  atom3568*atom3696+atom3564*atom3695;
_dPhit_ds[957] =  atom3699*atom3568+atom3572*atom3700;
_dPhit_ds[958] = atom9974;
_dPhit_ds[959] =  ( atom1610*atom10073+atom1530*atom10071)*atom3691+( atom10071*atom1518+atom1598*atom10073)*atom3689+atom3690*( atom10071*atom1524+atom1604*atom10073);
_dPhit_ds[960] = 0.0000000000000000e+00;
_dPhit_ds[961] = 0.0000000000000000e+00;
_dPhit_ds[962] = 0.0000000000000000e+00;
_dPhit_ds[963] = 0.0000000000000000e+00;
_dPhit_ds[964] = 0.0000000000000000e+00;
_dPhit_ds[965] = 0.0000000000000000e+00;
_dPhit_ds[966] = 0.0000000000000000e+00;
_dPhit_ds[967] = 0.0000000000000000e+00;
_dPhit_ds[968] = 0.0000000000000000e+00;
_dPhit_ds[969] = 0.0000000000000000e+00;
_dPhit_ds[970] = 0.0000000000000000e+00;
_dPhit_ds[971] = 0.0000000000000000e+00;
_dPhit_ds[972] = 0.0000000000000000e+00;
_dPhit_ds[973] = 0.0000000000000000e+00;
_dPhit_ds[974] = 0.0000000000000000e+00;
_dPhit_ds[975] = 0.0000000000000000e+00;
_dPhit_ds[976] = 0.0000000000000000e+00;
_dPhit_ds[977] = 0.0000000000000000e+00;
_dPhit_ds[978] = 0.0000000000000000e+00;
_dPhit_ds[979] = 0.0000000000000000e+00;
_dPhit_ds[980] = 0.0000000000000000e+00;
_dPhit_ds[981] = 0.0000000000000000e+00;
_dPhit_ds[982] = 0.0000000000000000e+00;
_dPhit_ds[983] = 0.0000000000000000e+00;
_dPhit_ds[984] = 0.0000000000000000e+00;
_dPhit_ds[985] = 0.0000000000000000e+00;
_dPhit_ds[986] = 0.0000000000000000e+00;
_dPhit_ds[987] = 0.0000000000000000e+00;
_dPhit_ds[988] = -atom3696;
_dPhit_ds[989] = -atom3699+atom3702*atom9875-atom3653*atom3700-( atom3582*atom3586-atom3539+dR_FRL+irrFRLz-atom1195*atom3503-atom3510*atom1194-atom1607*uW_FRL-atom1175*atom3509-zWAG-atom3542)*( atom3653*atom9875+atom3699*atom7402);
_dPhit_ds[990] =  atom3549*atom7412+atom3552*atom7406+atom3555*atom7415;
_dPhit_ds[991] =  atom3568*atom7406+atom3572*atom7415+atom3564*atom7412;
_dPhit_ds[992] = 0.0000000000000000e+00;
_dPhit_ds[993] = 0.0000000000000000e+00;
_dPhit_ds[994] = 0.0000000000000000e+00;
_dPhit_ds[995] = 0.0000000000000000e+00;
_dPhit_ds[996] = 0.0000000000000000e+00;
_dPhit_ds[997] = 0.0000000000000000e+00;
_dPhit_ds[998] = 0.0000000000000000e+00;
_dPhit_ds[999] = 0.0000000000000000e+00;
_dPhit_ds[1000] = 0.0000000000000000e+00;
_dPhit_ds[1001] = 0.0000000000000000e+00;
_dPhit_ds[1002] = 0.0000000000000000e+00;
_dPhit_ds[1003] = 0.0000000000000000e+00;
_dPhit_ds[1004] = 0.0000000000000000e+00;
_dPhit_ds[1005] = 0.0000000000000000e+00;
_dPhit_ds[1006] = 0.0000000000000000e+00;
_dPhit_ds[1007] = 0.0000000000000000e+00;
_dPhit_ds[1008] = 0.0000000000000000e+00;
_dPhit_ds[1009] = 0.0000000000000000e+00;
_dPhit_ds[1010] = 0.0000000000000000e+00;
_dPhit_ds[1011] = 0.0000000000000000e+00;
_dPhit_ds[1012] = 0.0000000000000000e+00;
_dPhit_ds[1013] = 0.0000000000000000e+00;
_dPhit_ds[1014] = 0.0000000000000000e+00;
_dPhit_ds[1015] = 0.0000000000000000e+00;
_dPhit_ds[1016] = 0.0000000000000000e+00;
_dPhit_ds[1017] = 0.0000000000000000e+00;
_dPhit_ds[1018] = 0.0000000000000000e+00;
_dPhit_ds[1019] = 0.0000000000000000e+00;
_dPhit_ds[1020] =  atom3702*( atom3694*atom7499+atom3650*atom9828)-( -5.0000000000000000e-01*atom3615*L_RAIL*atom7453+atom3645+1.0000000000000000e+00)*atom3695-atom3696*atom7491+( atom3694*atom7485+atom9828*atom3648)*( uW_FRL*atom1595+atom3509*atom1178+atom3510*atom1184-xR_FRL+atom1187*atom3503+atom3532+5.0000000000000000e-01*atom3615*atom3619*L_RAIL+atom3529+xWAG);
_dPhit_ds[1021] = -atom3699*atom7491;
_dPhit_ds[1022] =  atom3552*atom7489+atom3549*atom7503+atom3555*atom7510;
_dPhit_ds[1023] =  atom3564*atom7503+atom3568*atom7489+atom3572*atom7510;

return _dPhit_ds;
}
