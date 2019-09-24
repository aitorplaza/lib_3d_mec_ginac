/*----------dPhic_dq.c lib3D_MEC exported-----------*/

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

#include "dPhic_dq.h"

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

double atom1810;
double atom1811;
double atom1812;
double atom1818;
double atom1831;
double atom1820;
double atom1822;
double atom1834;
double atom1824;
double atom1837;
double atom1826;
double atom1840;
double atom1857;
double atom1860;
double atom1864;
double atom1843;
double atom1867;
double atom1845;
double atom1846;
double atom1872;
double atom1881;
double atom1882;
double atom1876;
double atom1883;
double atom1916;
double atom863;
double atom864;
double atom30;
double atom1702;
double atom868;
double atom1714;
double atom865;
double atom1726;
double atom1725;
double atom31;
double atom1715;
double atom862;
double atom1716;
double atom869;
double atom1729;
double atom1176;
double atom1174;
double atom1180;
double atom1172;
double atom1730;
double atom3771;
double atom867;
double atom866;
double atom1717;
double atom1718;
double atom1721;
double atom1210;
double atom1722;
double atom1724;
double atom1209;
double atom1175;
double atom1736;
double atom1181;
double atom1173;
double atom1733;
double atom0;
double atom3774;
double atom1737;
double atom3782;
double atom3776;
double atom3786;
double atom3792;
double atom3788;
double atom1704;
double atom1710;
double atom3799;
double atom1713;
double atom3778;
double atom1711;
double atom3794;
double atom1918;
double atom1177;
double atom1178;
double atom3735;
double atom1179;
double atom3733;
double atom3738;
double atom3740;
double atom3744;
double atom3746;
double atom3750;
double atom3752;
double atom3756;
double atom3760;
double atom1917;
double atom3811;
double atom3814;
double atom3819;
double atom3826;
double atom3830;
double atom3832;
double atom3836;
double atom3843;
double atom3838;
double atom3822;
double atom1919;
double atom1193;
double atom1190;
double atom3880;
double atom3882;
double atom3884;
double atom3888;
double atom3890;
double atom3894;
double atom3896;
double atom3901;
double atom1184;
double atom1187;
double atom3850;
double atom3870;
double atom3852;
double atom3854;
double atom3860;
double atom3856;
double atom3866;
double atom3862;
double atom1194;
double atom1195;
double atom3913;
double atom3920;
double atom3922;
double atom3928;
double atom3924;
double atom3935;
double atom3930;
double atom3916;
double atom1219;
double atom1237;
double atom1222;
double atom1240;
double atom1255;
double atom1258;
double atom1279;
double atom1282;
double atom1213;
double atom1234;
double atom1216;
double atom1252;
double atom1249;
double atom1276;
double atom1273;
double atom1231;
double atom1228;
double atom3998;
double atom4000;
double atom1225;
double atom4007;
double atom4003;
double atom4009;
double atom4014;
double atom3946;
double atom3953;
double atom3949;
double atom3955;
double atom3959;
double atom3961;
double atom3970;
double atom3973;
double atom3979;
double atom3975;
double atom3981;
double atom3986;
double atom1246;
double atom1264;
double atom1261;
double atom1288;
double atom1285;
double atom4028;
double atom4030;
double atom4033;
double atom4034;
double atom4037;
double atom4038;
double atom4040;
double atom4044;
double atom4068;
double atom4052;
double atom4027;
double atom4074;
double atom4072;
double atom4080;
double atom4076;
double atom4086;
double atom4088;
double atom4097;
double atom4095;
double atom4104;
double atom4099;
double atom1243;
double atom4123;
double atom4121;
double atom4130;
double atom4125;
double atom4139;
double atom4143;
double atom4146;
double atom4152;
double atom4159;
double atom4166;
double atom4169;
double atom4171;
double atom4175;
double atom4163;
double atom4193;
double atom4178;
double atom4185;
double atom2069;
double atom2071;
double atom2073;
double atom2075;
double atom2077;
double atom2082;
double atom2085;
double atom2088;
double atom2091;
double atom2094;
double atom2096;
double atom2097;
double atom2108;
double atom2112;
double atom2105;
double atom2118;
double atom2123;
double atom2127;
double atom2061;
double atom2062;
double atom2063;
double atom2132;
double atom2134;
double atom2133;
double atom2167;
double atom1972;
double atom1975;
double atom1977;
double atom1987;
double atom1984;
double atom1988;
double atom1980;
double atom1981;
double atom1962;
double atom1968;
double atom1969;
double atom1971;
double atom2169;
double atom2168;
double atom2170;
double atom4491;
double atom4494;
double atom4500;
double atom4496;
double atom4488;
double atom4486;
double atom4518;
double atom4508;
double atom4536;
double atom4534;
double atom2326;
double atom2327;
double atom2329;
double atom2331;
double atom2338;
double atom2341;
double atom2344;
double atom2333;
double atom2347;
double atom2350;
double atom2352;
double atom2353;
double atom2361;
double atom2367;
double atom2372;
double atom2374;
double atom2379;
double atom2317;
double atom2318;
double atom2319;
double atom2388;
double atom2389;
double atom2383;
double atom2390;
double atom2423;
double atom49;
double atom2223;
double atom2226;
double atom50;
double atom2224;
double atom2225;
double atom2229;
double atom2230;
double atom2232;
double atom2240;
double atom2244;
double atom2243;
double atom2233;
double atom2236;
double atom2237;
double atom4762;
double atom2212;
double atom2218;
double atom2220;
double atom4768;
double atom2222;
double atom2425;
double atom4785;
double atom4791;
double atom2424;
double atom4809;
double atom4804;
double atom2426;
double atom4854;
double atom4859;
double atom4843;
double atom4837;
double atom4824;
double atom4818;
double atom1310;
double atom1313;
double atom1316;
double atom1319;
double atom4898;
double atom4892;
double atom4879;
double atom4873;
double atom4909;
double atom4914;
double atom1325;
double atom1322;
double atom4933;
double atom4935;
double atom4938;
double atom4939;
double atom4941;
double atom4945;
double atom4930;
double atom4931;
double atom4969;
double atom4958;
double atom4928;
double atom4985;
double atom4987;
double atom5006;
double atom5000;
double atom4981;
double atom4975;
double atom5024;
double atom5019;
double atom5037;
double atom5040;
double atom5043;
double atom5049;
double atom5045;
double atom5067;
double atom5052;
double atom5059;
double atom2568;
double atom2569;
double atom2570;
double atom2577;
double atom2578;
double atom2580;
double atom2582;
double atom2584;
double atom2589;
double atom2592;
double atom2595;
double atom2598;
double atom2601;
double atom2603;
double atom2604;
double atom2616;
double atom2612;
double atom2623;
double atom2625;
double atom2630;
double atom2639;
double atom2634;
double atom2641;
double atom2640;
double atom2674;
double atom2479;
double atom2482;
double atom2484;
double atom2494;
double atom2491;
double atom2495;
double atom2487;
double atom2488;
double atom2469;
double atom2475;
double atom2478;
double atom2476;
double atom2677;
double atom2675;
double atom2676;
double atom5379;
double atom5366;
double atom5369;
double atom5375;
double atom5371;
double atom5364;
double atom5391;
double atom5401;
double atom5413;
double atom5411;
double atom2834;
double atom2836;
double atom2838;
double atom2840;
double atom2842;
double atom2847;
double atom2850;
double atom2853;
double atom2856;
double atom2871;
double atom2870;
double atom2881;
double atom2859;
double atom2861;
double atom2862;
double atom2883;
double atom2888;
double atom2892;
double atom2826;
double atom2827;
double atom2828;
double atom2897;
double atom2899;
double atom2898;
double atom2932;
double atom2720;
double atom2726;
double atom1496;
double atom1497;
double atom5646;
double atom1017;
double atom1019;
double atom5639;
double atom1018;
double atom5642;
double atom1016;
double atom5648;
double atom497;
double atom5652;
double atom498;
double atom2729;
double atom5654;
double atom5658;
double atom5662;
double atom2727;
double atom1020;
double atom2730;
double atom2733;
double atom2734;
double atom2731;
double atom1021;
double atom2732;
double atom2737;
double atom2738;
double atom2740;
double atom2752;
double atom2749;
double atom2753;
double atom1022;
double atom2741;
double atom2742;
double atom1023;
double atom2745;
double atom2746;
double atom2934;
double atom5687;
double atom5681;
double atom5683;
double atom5689;
double atom5693;
double atom5699;
double atom5703;
double atom5695;
double atom2933;
double atom5713;
double atom5715;
double atom5719;
double atom5723;
double atom5729;
double atom5725;
double atom5731;
double atom5736;
double atom2935;
double atom5809;
double atom5815;
double atom5817;
double atom5819;
double atom5823;
double atom5825;
double atom5811;
double atom5830;
double atom5747;
double atom5768;
double atom5750;
double atom5752;
double atom5754;
double atom5758;
double atom5764;
double atom5760;
double atom5781;
double atom5783;
double atom5785;
double atom5791;
double atom5787;
double atom5797;
double atom5801;
double atom5793;
double atom1500;
double atom1521;
double atom1503;
double atom1539;
double atom1536;
double atom1562;
double atom1559;
double atom1518;
double atom1506;
double atom1527;
double atom1509;
double atom1545;
double atom1542;
double atom1568;
double atom1565;
double atom1524;
double atom5844;
double atom5847;
double atom5851;
double atom5853;
double atom5857;
double atom5859;
double atom5871;
double atom5874;
double atom5878;
double atom5880;
double atom5884;
double atom5886;
double atom1515;
double atom5893;
double atom1512;
double atom5895;
double atom5898;
double atom5902;
double atom5904;
double atom5909;
double atom1533;
double atom1551;
double atom1548;
double atom1571;
double atom1574;
double atom5935;
double atom5936;
double atom5930;
double atom5932;
double atom5938;
double atom5942;
double atom5926;
double atom5928;
double atom5961;
double atom5955;
double atom5925;
double atom5970;
double atom5972;
double atom5974;
double atom5978;
double atom5984;
double atom5986;
double atom5997;
double atom5999;
double atom6001;
double atom6005;
double atom1530;
double atom6014;
double atom6016;
double atom6023;
double atom6018;
double atom6041;
double atom6037;
double atom6057;
double atom6050;
double atom6044;
double atom6061;
double atom6064;
double atom6067;
double atom6073;
double atom6069;
double atom6091;
double atom6076;
double atom6083;
double atom3086;
double atom3087;
double atom3098;
double atom3089;
double atom3101;
double atom3091;
double atom3104;
double atom3124;
double atom3121;
double atom3093;
double atom3107;
double atom3131;
double atom3110;
double atom3112;
double atom3113;
double atom3134;
double atom3139;
double atom3143;
double atom3077;
double atom3078;
double atom3079;
double atom3148;
double atom3149;
double atom3150;
double atom3183;
double atom2988;
double atom2993;
double atom2991;
double atom3003;
double atom3000;
double atom3004;
double atom2996;
double atom2997;
double atom2978;
double atom2984;
double atom2985;
double atom2987;
double atom3184;
double atom3185;
double atom3186;
double atom6385;
double atom6375;
double atom6372;
double atom6377;
double atom6381;
double atom6390;
double atom6405;
double atom6395;
double atom6417;
double atom6415;
double atom3341;
double atom3353;
double atom3342;
double atom3344;
double atom3356;
double atom3346;
double atom3359;
double atom3348;
double atom3362;
double atom3365;
double atom3367;
double atom3368;
double atom3378;
double atom3383;
double atom3387;
double atom3389;
double atom3394;
double atom3332;
double atom3333;
double atom3334;
double atom3403;
double atom3404;
double atom3398;
double atom3405;
double atom3438;
double atom683;
double atom3239;
double atom3249;
double atom684;
double atom3240;
double atom3241;
double atom3252;
double atom3253;
double atom3242;
double atom3245;
double atom3246;
double atom3248;
double atom3259;
double atom3256;
double atom3260;
double atom3229;
double atom3235;
double atom3236;
double atom6648;
double atom6653;
double atom3238;
double atom3441;
double atom6688;
double atom6692;
double atom3439;
double atom6674;
double atom6670;
double atom3440;
double atom6722;
double atom6726;
double atom6738;
double atom6742;
double atom6709;
double atom6704;
double atom1598;
double atom1595;
double atom1604;
double atom1601;
double atom6781;
double atom6777;
double atom6793;
double atom6797;
double atom6764;
double atom6759;
double atom6829;
double atom6831;
double atom6815;
double atom6816;
double atom6818;
double atom6820;
double atom6826;
double atom6822;
double atom1607;
double atom1610;
double atom6813;
double atom6853;
double atom6843;
double atom6869;
double atom6871;
double atom6861;
double atom6866;
double atom6889;
double atom6885;
double atom6907;
double atom6903;
double atom6935;
double atom6922;
double atom6925;
double atom6927;
double atom6931;
double atom6937;
double atom6944;
double atom6951;
double atom3591;
double atom3592;
double atom3594;
double atom3596;
double atom3598;
double atom3603;
double atom3606;
double atom3609;
double atom3612;
double atom3615;
double atom3617;
double atom3618;
double atom3629;
double atom3634;
double atom3626;
double atom3639;
double atom3644;
double atom3582;
double atom3583;
double atom3584;
double atom3653;
double atom3654;
double atom3648;
double atom3655;
double atom3688;
double atom3494;
double atom3502;
double atom3503;
double atom3499;
double atom3497;
double atom3506;
double atom3510;
double atom3509;
double atom3484;
double atom3490;
double atom3491;
double atom3493;
double atom3690;
double atom3689;
double atom3691;
double atom7252;
double atom7249;
double atom7254;
double atom7258;
double atom7262;
double atom7285;
double atom7274;
double atom7247;
double atom7294;
double atom7296;

double * _dPhic_dq = NULL;
void Init_dPhic_dq ( ) 
{
    _dPhic_dq = malloc ( dPhic_dq_n_rows * dPhic_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhic_dq_n_rows * dPhic_dq_n_cols ; i++ ) {_dPhic_dq[i]=0.0;}
  }
}

void Done_dPhic_dq ( ) 
{
if (_dPhic_dq != NULL) 
free (_dPhic_dq ); 
_dPhic_dq = NULL; 
}


double * dPhic_dq ()
{
if ( _dPhic_dq == NULL )
 {
    _dPhic_dq = malloc ( dPhic_dq_n_rows * dPhic_dq_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < dPhic_dq_n_rows * dPhic_dq_n_cols ; i++ ) {_dPhic_dq[i]=0.0;}
  }
 }

atom1810 =  uR_RFR-lR_RFR;
atom1811 = aR_RFR*atom1810;
atom1812 =  atom1811+bR_RFR;
atom1818 = 1.0/( RFRstas-RFRends);
atom1831 = -RFRas*atom1818;
atom1820 = atom1818*( RFRstas-xR_RFR);
atom1822 =  atom1820*RFRas+RFRbs;
atom1834 = -atom1822*atom1818+atom1831*atom1820;
atom1824 =  atom1820*atom1822+RFRcs;
atom1837 = -atom1818*atom1824+atom1820*atom1834;
atom1826 =  RFRds+atom1820*atom1824;
atom1840 =  atom1820*atom1837-atom1818*atom1826;
atom1857 = -atom1834*atom1818;
atom1860 = -atom1818*atom1837;
atom1864 = -atom1818*atom1840;
atom1843 = -atom1818*( atom1820*atom1826+RFRes)+atom1820*atom1840;
atom1867 =  2.0*( atom1860+atom1820*( atom1857-atom1831*atom1820*atom1818))*atom1820+2.0*atom1864;
atom1845 =  (atom1843*atom1843)+1.0;
atom1846 = pow(atom1845,(1.0/2.0));
atom1872 = -1.0/(atom1846*atom1846)*atom1843*atom1867*pow(atom1845,-(1.0/2.0));
atom1881 =  cR_RFR+atom1812*atom1810+atom1810*( atom1812+atom1811);
atom1882 = atom1881*( -5.0000000000000000e-01*atom1872*L_RAIL+atom1843);
atom1876 =  5.0000000000000000e-01*1.0/atom1846*atom1867*L_RAIL+5.0000000000000000e-01*atom1872*atom1843*L_RAIL+1.0;
atom1883 = -atom1876*atom1881;
atom1916 = pow( (atom1876*atom1876)+(atom1882*atom1882)+(atom1883*atom1883),-(1.0/2.0));
atom863 = sin(aRBOG);
atom864 = cos(bRBOG);
atom30 = cos(aRWHSF);
atom1702 = -5.0000000000000000e-01*L_WHS;
atom868 = atom863*atom864;
atom1714 = atom30*atom1702;
atom865 = sin(bRBOG);
atom1726 = atom868*atom1714;
atom1725 = -L_OBOG_OWHS*atom865;
atom31 = sin(aRWHSF);
atom1715 = atom1702*atom31;
atom862 = cos(aRBOG);
atom1716 =  atom1715+zRWHSF;
atom869 = atom862*atom864;
atom1729 =  atom1716*atom869+atom1726+atom1725;
atom1176 = cos(cWAG);
atom1174 = cos(aWAG);
atom1180 = atom1176*atom1174;
atom1172 = cos(bWAG);
atom1730 =  zRBOG+atom1729;
atom3771 = -atom1180*atom1172;
atom867 = atom862*atom865;
atom866 = atom863*atom865;
atom1717 = L_OBOG_OWHS*atom864;
atom1718 = atom866*atom1714;
atom1721 =  atom1717+atom867*atom1716+atom1718;
atom1210 = sin(cRSLD);
atom1722 = atom862*atom1714;
atom1724 = -atom863*atom1716+atom1722;
atom1209 = cos(cRSLD);
atom1175 = sin(aWAG);
atom1736 =  atom1721*atom1210+atom1724*atom1209;
atom1181 = -atom1175*atom1176;
atom1173 = sin(bWAG);
atom1733 = -atom1724*atom1210+atom1721*atom1209;
atom0 = -(1.0/2.0)*L_WAG;
atom3774 = atom1180*atom1173;
atom1737 =  atom1733+atom0;
atom3782 =  atom1181*atom1209-atom3774*atom1210;
atom3776 =  atom1181*atom1210+atom1209*atom3774;
atom3786 =  atom865*atom3776+atom3771*atom864;
atom3792 = -atom3782*atom863+atom862*atom3786;
atom3788 =  atom863*atom3786+atom862*atom3782;
atom1704 =  uW_RFR-lW_RFR;
atom1710 =  ( ( bW_RFR+aW_RFR*atom1704)*atom1704+cW_RFR)*atom1704+dW_RFR;
atom3799 = -atom3788*atom31+atom3792*atom30;
atom1713 = cos(thetaW_RFR)*atom1710;
atom3778 = -atom3771*atom865+atom864*atom3776;
atom1711 = -atom1710*sin(thetaW_RFR);
atom3794 =  atom3792*atom31+atom30*atom3788;
atom1918 = atom1916*atom1883;
atom1177 = sin(cWAG);
atom1178 = -atom1177*atom1174;
atom3735 = atom1173*atom1178;
atom1179 = atom1175*atom1177;
atom3733 = -atom1172*atom1178;
atom3738 =  atom1179*atom1210+atom3735*atom1209;
atom3740 =  atom865*atom3738+atom864*atom3733;
atom3744 = -atom3735*atom1210+atom1209*atom1179;
atom3746 = -atom3744*atom863+atom3740*atom862;
atom3750 =  atom3740*atom863+atom862*atom3744;
atom3752 = -atom3750*atom31+atom3746*atom30;
atom3756 =  atom3750*atom30+atom3746*atom31;
atom3760 =  atom864*atom3738-atom3733*atom865;
atom1917 = atom1882*atom1916;
atom3811 = atom1175*atom1173;
atom3814 = -atom1175*atom1172;
atom3819 =  atom1174*atom1210+atom3811*atom1209;
atom3826 =  atom864*atom3814+atom3819*atom865;
atom3830 = -atom3811*atom1210+atom1209*atom1174;
atom3832 =  atom862*atom3826-atom863*atom3830;
atom3836 =  atom863*atom3826+atom862*atom3830;
atom3843 =  atom3832*atom30-atom3836*atom31;
atom3838 =  atom3836*atom30+atom3832*atom31;
atom3822 =  atom3819*atom864-atom3814*atom865;
atom1919 = atom1876*atom1916;
atom1193 =  atom1177*atom1173+atom1172*atom1181;
atom1190 = -atom1181*atom1173+atom1172*atom1177;
atom3880 = -atom1193*atom1209;
atom3882 = -atom1190*atom865+atom864*atom3880;
atom3884 = atom1193*atom1210;
atom3888 =  atom3880*atom865+atom864*atom1190;
atom3890 =  atom862*atom3884+atom863*atom3888;
atom3894 = -atom863*atom3884+atom862*atom3888;
atom3896 =  atom3894*atom31+atom30*atom3890;
atom3901 = -atom3890*atom31+atom3894*atom30;
atom1184 =  atom1172*atom1176-atom1173*atom1179;
atom1187 =  atom1172*atom1179+atom1176*atom1173;
atom3850 = -atom1187*atom1209;
atom3870 = -atom865*atom1184+atom3850*atom864;
atom3852 =  atom3850*atom865+atom864*atom1184;
atom3854 = atom1187*atom1210;
atom3860 =  atom862*atom3854+atom863*atom3852;
atom3856 = -atom863*atom3854+atom862*atom3852;
atom3866 =  atom3860*atom30+atom3856*atom31;
atom3862 = -atom3860*atom31+atom3856*atom30;
atom1194 = -atom1173*atom1174;
atom1195 = atom1172*atom1174;
atom3913 = -atom1195*atom1209;
atom3920 =  atom3913*atom865+atom864*atom1194;
atom3922 = atom1195*atom1210;
atom3928 =  atom863*atom3920+atom862*atom3922;
atom3924 =  atom862*atom3920-atom863*atom3922;
atom3935 = -atom3928*atom31+atom3924*atom30;
atom3930 =  atom3928*atom30+atom3924*atom31;
atom3916 = -atom1194*atom865+atom3913*atom864;
atom1219 =  atom1180*atom1210+atom1190*atom1209;
atom1237 =  atom864*atom1219-atom1193*atom865;
atom1222 =  atom1180*atom1209-atom1190*atom1210;
atom1240 =  atom1219*atom865+atom1193*atom864;
atom1255 =  atom862*atom1222+atom863*atom1240;
atom1258 = -atom863*atom1222+atom862*atom1240;
atom1279 =  atom1258*atom31+atom1255*atom30;
atom1282 =  atom1258*atom30-atom1255*atom31;
atom1213 =  atom1209*atom1184+atom1178*atom1210;
atom1234 =  atom1213*atom865+atom864*atom1187;
atom1216 = -atom1184*atom1210+atom1209*atom1178;
atom1252 =  atom862*atom1234-atom863*atom1216;
atom1249 =  atom863*atom1234+atom862*atom1216;
atom1276 =  atom1252*atom30-atom1249*atom31;
atom1273 =  atom1252*atom31+atom30*atom1249;
atom1231 =  atom1213*atom864-atom1187*atom865;
atom1228 =  atom1175*atom1209-atom1194*atom1210;
atom3998 = atom1228*atom864;
atom4000 = atom1228*atom865;
atom1225 =  atom1194*atom1209+atom1175*atom1210;
atom4007 =  atom863*atom4000-atom862*atom1225;
atom4003 =  atom862*atom4000+atom863*atom1225;
atom4009 =  atom4003*atom31+atom4007*atom30;
atom4014 = -atom4007*atom31+atom4003*atom30;
atom3946 = atom1216*atom865;
atom3953 = -atom862*atom1213+atom863*atom3946;
atom3949 =  atom863*atom1213+atom862*atom3946;
atom3955 =  atom3949*atom30-atom3953*atom31;
atom3959 =  atom3953*atom30+atom3949*atom31;
atom3961 = atom1216*atom864;
atom3970 = atom1222*atom864;
atom3973 = atom1222*atom865;
atom3979 =  atom863*atom1219+atom862*atom3973;
atom3975 = -atom862*atom1219+atom863*atom3973;
atom3981 =  atom3979*atom31+atom3975*atom30;
atom3986 = -atom3975*atom31+atom3979*atom30;
atom1246 =  atom1195*atom864+atom1225*atom865;
atom1264 =  atom862*atom1246-atom863*atom1228;
atom1261 =  atom862*atom1228+atom863*atom1246;
atom1288 = -atom1261*atom31+atom30*atom1264;
atom1285 =  atom30*atom1261+atom1264*atom31;
atom4028 = atom1714*atom869;
atom4030 =  atom4028-atom868*atom1716;
atom4033 = atom1714*atom867;
atom4034 = -atom866*atom1716+atom4033;
atom4037 = -atom863*atom1714;
atom4038 =  atom4037-atom862*atom1716;
atom4040 =  atom4034*atom1210+atom4038*atom1209;
atom4044 =  atom4034*atom1209-atom4038*atom1210;
atom4068 = -atom1285*atom1713+uW_RFR*atom1288;
atom4052 =  uW_RFR*atom1282-atom1713*atom1279;
atom4027 =  uW_RFR*atom1276-atom1273*atom1713;
atom4074 = atom1231*atom863;
atom4072 = atom1231*atom862;
atom4080 =  atom4072*atom31+atom4074*atom30;
atom4076 = -atom4074*atom31+atom30*atom4072;
atom4086 = atom1729*atom1210;
atom4088 = atom1729*atom1209;
atom4097 = atom862*atom1237;
atom4095 = atom863*atom1237;
atom4104 = -atom4095*atom31+atom30*atom4097;
atom4099 =  atom4095*atom30+atom4097*atom31;
atom1243 =  atom1225*atom864-atom1195*atom865;
atom4123 = atom1243*atom863;
atom4121 = atom862*atom1243;
atom4130 = -atom31*atom4123+atom30*atom4121;
atom4125 =  atom30*atom4123+atom4121*atom31;
atom4139 = -atom863*atom1209+atom867*atom1210;
atom4143 =  atom867*atom1209+atom863*atom1210;
atom4146 =  atom4143*atom1184+atom4139*atom1178+atom1187*atom869;
atom4152 =  atom1193*atom869+atom1180*atom4139+atom4143*atom1190;
atom4159 =  atom4139*atom1175+atom1195*atom869+atom4143*atom1194;
atom4166 = -atom866*atom1715+atom4033;
atom4169 =  atom4037-atom862*atom1715;
atom4171 =  atom4166*atom1210+atom1209*atom4169;
atom4175 = -atom4169*atom1210+atom1209*atom4166;
atom4163 = -atom1715*atom868+atom4028;
atom4193 =  atom1195*atom4163+atom1194*atom4175+atom4171*atom1175;
atom4178 =  atom4163*atom1187+atom4175*atom1184+atom4171*atom1178;
atom4185 =  atom4175*atom1190+atom1180*atom4171+atom1193*atom4163;
atom2069 = 1.0/( RFLstas-RFLends);
atom2071 = atom2069*( RFLstas-xR_RFL);
atom2073 =  atom2071*RFLas+RFLbs;
atom2075 =  RFLcs+atom2071*atom2073;
atom2077 =  atom2071*atom2075+RFLds;
atom2082 = -atom2069*RFLas;
atom2085 =  atom2082*atom2071-atom2073*atom2069;
atom2088 = -atom2069*atom2075+atom2071*atom2085;
atom2091 =  atom2071*atom2088-atom2069*atom2077;
atom2094 =  atom2071*atom2091-atom2069*( atom2071*atom2077+RFLes);
atom2096 =  (atom2094*atom2094)+1.0;
atom2097 = pow(atom2096,(1.0/2.0));
atom2108 = -atom2085*atom2069;
atom2112 = -atom2069*atom2088;
atom2105 = -atom2069*atom2091;
atom2118 =  2.0*atom2105+( 2.0*atom2112+( -2.0000000000000000e+00*atom2082*atom2071*atom2069+2.0*atom2108)*atom2071)*atom2071;
atom2123 = -atom2094*pow(atom2096,-(1.0/2.0))*atom2118/(atom2097*atom2097);
atom2127 =  -5.0000000000000000e-01*atom2094*atom2123*L_RAIL+-5.0000000000000000e-01*atom2118/atom2097*L_RAIL+1.0;
atom2061 =  uR_RFL-lR_RFL;
atom2062 = atom2061*aR_RFL;
atom2063 =  atom2062+bR_RFL;
atom2132 =  atom2063*atom2061+( atom2063+atom2062)*atom2061+cR_RFL;
atom2134 = -atom2127*atom2132;
atom2133 = atom2132*( atom2094+5.0000000000000000e-01*atom2123*L_RAIL);
atom2167 = pow( (atom2127*atom2127)+(atom2133*atom2133)+(atom2134*atom2134),-(1.0/2.0));
atom1972 = -atom1715+zRWHSF;
atom1975 =  atom1972*atom867+atom1717-atom1718;
atom1977 = -atom1722-atom863*atom1972;
atom1987 =  atom1977*atom1209+atom1975*atom1210;
atom1984 = -atom1977*atom1210+atom1975*atom1209;
atom1988 =  atom1984+atom0;
atom1980 =  atom1972*atom869-atom1726+atom1725;
atom1981 =  zRBOG+atom1980;
atom1962 =  uW_RFL-lW_RFL;
atom1968 =  dW_RFL+( cW_RFL+( aW_RFL*atom1962+bW_RFL)*atom1962)*atom1962;
atom1969 = -sin(thetaW_RFL)*atom1968;
atom1971 = atom1968*cos(thetaW_RFL);
atom2169 = atom2167*atom2134;
atom2168 = atom2167*atom2133;
atom2170 = atom2167*atom2127;
atom4491 = -atom866*atom1972-atom4033;
atom4494 = -atom4037-atom862*atom1972;
atom4500 =  atom4491*atom1209-atom4494*atom1210;
atom4496 =  atom1209*atom4494+atom4491*atom1210;
atom4488 = -atom4028-atom868*atom1972;
atom4486 = -atom1285*atom1971+uW_RFL*atom1288;
atom4518 =  uW_RFL*atom1276-atom1273*atom1971;
atom4508 =  uW_RFL*atom1282-atom1971*atom1279;
atom4536 = atom1980*atom1209;
atom4534 = atom1980*atom1210;
atom2326 = 1.0/( RRRstas-RRRends);
atom2327 = atom2326*( RRRstas-xR_RRR);
atom2329 =  atom2327*RRRas+RRRbs;
atom2331 =  RRRcs+atom2327*atom2329;
atom2338 = -atom2326*RRRas;
atom2341 = -atom2329*atom2326+atom2327*atom2338;
atom2344 =  atom2327*atom2341-atom2331*atom2326;
atom2333 =  RRRds+atom2327*atom2331;
atom2347 = -atom2333*atom2326+atom2327*atom2344;
atom2350 = -atom2326*( atom2327*atom2333+RRRes)+atom2327*atom2347;
atom2352 =  (atom2350*atom2350)+1.0;
atom2353 = pow(atom2352,(1.0/2.0));
atom2361 = -atom2326*atom2341;
atom2367 = -atom2344*atom2326;
atom2372 = -atom2347*atom2326;
atom2374 =  2.0*atom2372+atom2327*( 2.0*atom2367+atom2327*( -2.0000000000000000e+00*atom2327*atom2338*atom2326+2.0*atom2361));
atom2379 = -atom2350*pow(atom2352,-(1.0/2.0))*atom2374/(atom2353*atom2353);
atom2317 =  uR_RRR-lR_RRR;
atom2318 = atom2317*aR_RRR;
atom2319 =  atom2318+bR_RRR;
atom2388 =  cR_RRR+atom2317*( atom2318+atom2319)+atom2317*atom2319;
atom2389 = ( -5.0000000000000000e-01*L_RAIL*atom2379+atom2350)*atom2388;
atom2383 =  5.0000000000000000e-01*L_RAIL*atom2374/atom2353+5.0000000000000000e-01*atom2350*L_RAIL*atom2379+1.0;
atom2390 = -atom2383*atom2388;
atom2423 = pow( (atom2390*atom2390)+(atom2389*atom2389)+(atom2383*atom2383),-(1.0/2.0));
atom49 = cos(aRWHSR);
atom2223 = atom49*atom1702;
atom2226 = atom866*atom2223;
atom50 = sin(aRWHSR);
atom2224 = atom50*atom1702;
atom2225 =  atom2224+zRWHSR;
atom2229 = -atom1717+atom2226+atom867*atom2225;
atom2230 = atom862*atom2223;
atom2232 =  atom2230-atom863*atom2225;
atom2240 =  atom1209*atom2229-atom2232*atom1210;
atom2244 =  atom0+atom2240;
atom2243 =  atom2229*atom1210+atom1209*atom2232;
atom2233 = atom868*atom2223;
atom2236 =  atom2233-atom1725+atom2225*atom869;
atom2237 =  zRBOG+atom2236;
atom4762 =  atom49*atom3788+atom3792*atom50;
atom2212 =  uW_RRR-lW_RRR;
atom2218 =  atom2212*( cW_RRR+atom2212*( bW_RRR+atom2212*aW_RRR))+dW_RRR;
atom2220 = -sin(thetaW_RRR)*atom2218;
atom4768 = -atom50*atom3788+atom3792*atom49;
atom2222 = atom2218*cos(thetaW_RRR);
atom2425 = atom2423*atom2390;
atom4785 =  atom3750*atom49+atom50*atom3746;
atom4791 =  atom49*atom3746-atom3750*atom50;
atom2424 = atom2423*atom2389;
atom4809 =  atom3832*atom50+atom49*atom3836;
atom4804 =  atom3832*atom49-atom50*atom3836;
atom2426 = atom2423*atom2383;
atom4854 =  atom3924*atom49-atom3928*atom50;
atom4859 =  atom3924*atom50+atom3928*atom49;
atom4843 =  atom3856*atom49-atom50*atom3860;
atom4837 =  atom49*atom3860+atom3856*atom50;
atom4824 =  atom3894*atom49-atom50*atom3890;
atom4818 =  atom49*atom3890+atom3894*atom50;
atom1310 =  atom49*atom1249+atom50*atom1252;
atom1313 = -atom50*atom1249+atom49*atom1252;
atom1316 =  atom1255*atom49+atom1258*atom50;
atom1319 = -atom1255*atom50+atom1258*atom49;
atom4898 =  atom49*atom3949-atom50*atom3953;
atom4892 =  atom3949*atom50+atom49*atom3953;
atom4879 =  atom3979*atom49-atom3975*atom50;
atom4873 =  atom3975*atom49+atom3979*atom50;
atom4909 =  atom4003*atom49-atom4007*atom50;
atom4914 =  atom4003*atom50+atom49*atom4007;
atom1325 =  atom49*atom1264-atom50*atom1261;
atom1322 =  atom49*atom1261+atom50*atom1264;
atom4933 = atom867*atom2223;
atom4935 =  atom4933-atom866*atom2225;
atom4938 = -atom863*atom2223;
atom4939 =  atom4938-atom862*atom2225;
atom4941 =  atom4939*atom1209+atom4935*atom1210;
atom4945 =  atom4935*atom1209-atom4939*atom1210;
atom4930 = atom2223*atom869;
atom4931 =  atom4930-atom868*atom2225;
atom4969 =  uW_RRR*atom1325-atom2222*atom1322;
atom4958 =  uW_RRR*atom1313-atom2222*atom1310;
atom4928 =  atom1319*uW_RRR-atom1316*atom2222;
atom4985 = atom2236*atom1210;
atom4987 = atom1209*atom2236;
atom5006 =  atom49*atom4072-atom4074*atom50;
atom5000 =  atom4074*atom49+atom50*atom4072;
atom4981 =  atom49*atom4097-atom50*atom4095;
atom4975 =  atom50*atom4097+atom49*atom4095;
atom5024 =  atom49*atom4123+atom50*atom4121;
atom5019 =  atom49*atom4121-atom50*atom4123;
atom5037 =  atom4930-atom2224*atom868;
atom5040 =  atom4933-atom866*atom2224;
atom5043 =  atom4938-atom862*atom2224;
atom5049 = -atom5043*atom1210+atom1209*atom5040;
atom5045 =  atom5040*atom1210+atom1209*atom5043;
atom5067 =  atom5045*atom1175+atom1195*atom5037+atom5049*atom1194;
atom5052 =  atom1193*atom5037+atom5049*atom1190+atom5045*atom1180;
atom5059 =  atom5049*atom1184+atom5045*atom1178+atom1187*atom5037;
atom2568 =  uR_RRL-lR_RRL;
atom2569 = atom2568*aR_RRL;
atom2570 =  bR_RRL+atom2569;
atom2577 = 1.0/( RRLstas-RRLends);
atom2578 = ( RRLstas-xR_RRL)*atom2577;
atom2580 =  atom2578*RRLas+RRLbs;
atom2582 =  RRLcs+atom2578*atom2580;
atom2584 =  atom2578*atom2582+RRLds;
atom2589 = -RRLas*atom2577;
atom2592 =  atom2578*atom2589-atom2580*atom2577;
atom2595 = -atom2582*atom2577+atom2578*atom2592;
atom2598 =  atom2578*atom2595-atom2584*atom2577;
atom2601 =  atom2578*atom2598-( atom2578*atom2584+RRLes)*atom2577;
atom2603 =  (atom2601*atom2601)+1.0;
atom2604 = pow(atom2603,(1.0/2.0));
atom2616 = -atom2592*atom2577;
atom2612 = -atom2595*atom2577;
atom2623 = -atom2598*atom2577;
atom2625 =  2.0*atom2623+-2.0*atom2578*( atom2578*( atom2578*atom2589*atom2577-atom2616)-atom2612);
atom2630 = -pow(atom2603,-(1.0/2.0))*atom2601*atom2625/(atom2604*atom2604);
atom2639 =  atom2570*atom2568+( atom2570+atom2569)*atom2568+cR_RRL;
atom2634 =  -5.0000000000000000e-01*atom2601*atom2630*L_RAIL+-5.0000000000000000e-01*atom2625*L_RAIL/atom2604+1.0;
atom2641 = -atom2639*atom2634;
atom2640 = ( 5.0000000000000000e-01*atom2630*L_RAIL+atom2601)*atom2639;
atom2674 = pow( (atom2634*atom2634)+(atom2641*atom2641)+(atom2640*atom2640),-(1.0/2.0));
atom2479 = -atom2224+zRWHSR;
atom2482 = -atom1717+atom867*atom2479-atom2226;
atom2484 = -atom863*atom2479-atom2230;
atom2494 =  atom1209*atom2484+atom2482*atom1210;
atom2491 = -atom2484*atom1210+atom2482*atom1209;
atom2495 =  atom0+atom2491;
atom2487 = -atom2233+atom2479*atom869-atom1725;
atom2488 =  atom2487+zRBOG;
atom2469 =  uW_RRL-lW_RRL;
atom2475 =  dW_RRL+atom2469*( cW_RRL+atom2469*( atom2469*aW_RRL+bW_RRL));
atom2478 = atom2475*cos(thetaW_RRL);
atom2476 = -sin(thetaW_RRL)*atom2475;
atom2677 = atom2634*atom2674;
atom2675 = atom2674*atom2640;
atom2676 = atom2641*atom2674;
atom5379 = -atom868*atom2479-atom4930;
atom5366 = -atom4933-atom866*atom2479;
atom5369 = -atom862*atom2479-atom4938;
atom5375 =  atom5366*atom1209-atom5369*atom1210;
atom5371 =  atom5366*atom1210+atom1209*atom5369;
atom5364 =  uW_RRL*atom1325-atom2478*atom1322;
atom5391 =  atom1319*uW_RRL-atom1316*atom2478;
atom5401 =  uW_RRL*atom1313-atom2478*atom1310;
atom5413 = atom2487*atom1209;
atom5411 = atom2487*atom1210;
atom2834 = 1.0/( FFRends-FFRstas);
atom2836 = atom2834*( xR_FFR-FFRstas);
atom2838 =  FFRbs+atom2836*FFRas;
atom2840 =  FFRcs+atom2836*atom2838;
atom2842 =  FFRds+atom2836*atom2840;
atom2847 = atom2834*FFRas;
atom2850 =  atom2834*atom2838+atom2836*atom2847;
atom2853 =  atom2834*atom2840+atom2836*atom2850;
atom2856 =  atom2836*atom2853+atom2842*atom2834;
atom2871 = atom2834*atom2850;
atom2870 = atom2834*atom2853;
atom2881 = atom2834*atom2856;
atom2859 =  atom2836*atom2856+atom2834*( FFRes+atom2836*atom2842);
atom2861 =  (atom2859*atom2859)+1.0;
atom2862 = pow(atom2861,(1.0/2.0));
atom2883 =  2.0*atom2881+2.0*atom2836*( atom2870+atom2836*( atom2871+atom2836*atom2834*atom2847));
atom2888 = -1.0/(atom2862*atom2862)*atom2859*pow(atom2861,-(1.0/2.0))*atom2883;
atom2892 =  5.0000000000000000e-01*atom2888*atom2859*L_RAIL+5.0000000000000000e-01*1.0/atom2862*atom2883*L_RAIL+1.0;
atom2826 =  uR_FFR-lR_FFR;
atom2827 = atom2826*aR_FFR;
atom2828 =  bR_FFR+atom2827;
atom2897 =  atom2828*atom2826+cR_FFR+atom2826*( atom2828+atom2827);
atom2899 = -atom2892*atom2897;
atom2898 = atom2897*( atom2859+-5.0000000000000000e-01*atom2888*L_RAIL);
atom2932 = pow( (atom2899*atom2899)+(atom2892*atom2892)+(atom2898*atom2898),-(1.0/2.0));
atom2720 =  uW_FFR-lW_FFR;
atom2726 =  dW_FFR+( cW_FFR+( bW_FFR+aW_FFR*atom2720)*atom2720)*atom2720;
atom1496 = cos(cFSLD);
atom1497 = sin(cFSLD);
atom5646 =  atom1181*atom1496-atom1497*atom3774;
atom1017 = sin(aFBOG);
atom1019 = sin(bFBOG);
atom5639 =  atom1496*atom3774+atom1497*atom1181;
atom1018 = cos(bFBOG);
atom5642 =  atom1018*atom3771+atom1019*atom5639;
atom1016 = cos(aFBOG);
atom5648 = -atom5646*atom1017+atom5642*atom1016;
atom497 = cos(aFWHSF);
atom5652 =  atom5642*atom1017+atom5646*atom1016;
atom498 = sin(aFWHSF);
atom2729 = atom2726*cos(thetaW_FFR);
atom5654 =  atom5648*atom497-atom5652*atom498;
atom5658 =  atom5648*atom498+atom497*atom5652;
atom5662 = -atom1019*atom3771+atom1018*atom5639;
atom2727 = -sin(thetaW_FFR)*atom2726;
atom1020 = atom1019*atom1017;
atom2730 = atom497*atom1702;
atom2733 = atom1018*L_OBOG_OWHS;
atom2734 = atom1020*atom2730;
atom2731 = atom498*atom1702;
atom1021 = atom1019*atom1016;
atom2732 =  atom2731+zFWHSF;
atom2737 =  atom1021*atom2732+atom2733+atom2734;
atom2738 = atom1016*atom2730;
atom2740 = -atom2732*atom1017+atom2738;
atom2752 =  atom1497*atom2737+atom2740*atom1496;
atom2749 = -atom1497*atom2740+atom2737*atom1496;
atom2753 = -atom0+atom2749;
atom1022 = atom1018*atom1017;
atom2741 = -L_OBOG_OWHS*atom1019;
atom2742 = atom2730*atom1022;
atom1023 = atom1018*atom1016;
atom2745 =  atom2741+atom2742+atom1023*atom2732;
atom2746 =  zFBOG+atom2745;
atom2934 = atom2899*atom2932;
atom5687 =  atom1179*atom1496-atom1497*atom3735;
atom5681 =  atom3735*atom1496+atom1497*atom1179;
atom5683 =  atom1019*atom5681+atom1018*atom3733;
atom5689 = -atom5687*atom1017+atom1016*atom5683;
atom5693 =  atom5683*atom1017+atom5687*atom1016;
atom5699 =  atom497*atom5693+atom498*atom5689;
atom5703 =  atom1018*atom5681-atom1019*atom3733;
atom5695 =  atom497*atom5689-atom498*atom5693;
atom2933 = atom2932*atom2898;
atom5713 =  atom3811*atom1496+atom1497*atom1174;
atom5715 =  atom1018*atom5713-atom1019*atom3814;
atom5719 =  atom1019*atom5713+atom1018*atom3814;
atom5723 =  atom1496*atom1174-atom3811*atom1497;
atom5729 =  atom5719*atom1017+atom5723*atom1016;
atom5725 = -atom5723*atom1017+atom1016*atom5719;
atom5731 =  atom497*atom5729+atom498*atom5725;
atom5736 =  atom497*atom5725-atom498*atom5729;
atom2935 = atom2932*atom2892;
atom5809 = -atom1195*atom1496;
atom5815 =  atom1019*atom5809+atom1018*atom1194;
atom5817 = atom1497*atom1195;
atom5819 =  atom5815*atom1016-atom5817*atom1017;
atom5823 =  atom5815*atom1017+atom5817*atom1016;
atom5825 =  atom497*atom5823+atom5819*atom498;
atom5811 =  atom1018*atom5809-atom1019*atom1194;
atom5830 =  atom497*atom5819-atom498*atom5823;
atom5747 = -atom1193*atom1496;
atom5768 =  atom5747*atom1018-atom1019*atom1190;
atom5750 =  atom5747*atom1019+atom1018*atom1190;
atom5752 = atom1497*atom1193;
atom5754 = -atom5752*atom1017+atom5750*atom1016;
atom5758 =  atom5750*atom1017+atom5752*atom1016;
atom5764 =  atom5754*atom498+atom497*atom5758;
atom5760 =  atom497*atom5754-atom498*atom5758;
atom5781 = -atom1187*atom1496;
atom5783 =  atom1018*atom1184+atom1019*atom5781;
atom5785 = atom1497*atom1187;
atom5791 =  atom5785*atom1016+atom5783*atom1017;
atom5787 =  atom5783*atom1016-atom5785*atom1017;
atom5797 =  atom497*atom5791+atom498*atom5787;
atom5801 = -atom1019*atom1184+atom1018*atom5781;
atom5793 =  atom497*atom5787-atom498*atom5791;
atom1500 =  atom1496*atom1184+atom1497*atom1178;
atom1521 =  atom1019*atom1500+atom1018*atom1187;
atom1503 =  atom1496*atom1178-atom1497*atom1184;
atom1539 = -atom1503*atom1017+atom1016*atom1521;
atom1536 =  atom1521*atom1017+atom1503*atom1016;
atom1562 =  atom497*atom1539-atom498*atom1536;
atom1559 =  atom497*atom1536+atom498*atom1539;
atom1518 =  atom1018*atom1500-atom1019*atom1187;
atom1506 =  atom1190*atom1496+atom1497*atom1180;
atom1527 =  atom1019*atom1506+atom1193*atom1018;
atom1509 =  atom1180*atom1496-atom1497*atom1190;
atom1545 =  atom1527*atom1016-atom1017*atom1509;
atom1542 =  atom1016*atom1509+atom1527*atom1017;
atom1568 =  atom497*atom1545-atom498*atom1542;
atom1565 =  atom497*atom1542+atom498*atom1545;
atom1524 = -atom1193*atom1019+atom1018*atom1506;
atom5844 = atom1019*atom1509;
atom5847 =  atom1506*atom1017+atom1016*atom5844;
atom5851 =  atom1017*atom5844-atom1016*atom1506;
atom5853 =  atom497*atom5847-atom5851*atom498;
atom5857 =  atom5851*atom497+atom498*atom5847;
atom5859 = atom1018*atom1509;
atom5871 = atom1503*atom1019;
atom5874 =  atom5871*atom1016+atom1500*atom1017;
atom5878 = -atom1500*atom1016+atom5871*atom1017;
atom5880 =  atom497*atom5874-atom5878*atom498;
atom5884 =  atom498*atom5874+atom5878*atom497;
atom5886 = atom1503*atom1018;
atom1515 =  atom1175*atom1496-atom1497*atom1194;
atom5893 = atom1515*atom1018;
atom1512 =  atom1194*atom1496+atom1497*atom1175;
atom5895 = atom1515*atom1019;
atom5898 =  atom1512*atom1017+atom1016*atom5895;
atom5902 =  atom5895*atom1017-atom1512*atom1016;
atom5904 =  atom497*atom5902+atom498*atom5898;
atom5909 = -atom498*atom5902+atom497*atom5898;
atom1533 =  atom1018*atom1195+atom1019*atom1512;
atom1551 = -atom1515*atom1017+atom1016*atom1533;
atom1548 =  atom1533*atom1017+atom1515*atom1016;
atom1571 =  atom497*atom1548+atom498*atom1551;
atom1574 = -atom498*atom1548+atom497*atom1551;
atom5935 = -atom2730*atom1017;
atom5936 = -atom1016*atom2732+atom5935;
atom5930 = atom1021*atom2730;
atom5932 =  atom5930-atom1020*atom2732;
atom5938 =  atom5936*atom1496+atom1497*atom5932;
atom5942 =  atom5932*atom1496-atom1497*atom5936;
atom5926 = atom1023*atom2730;
atom5928 = -atom2732*atom1022+atom5926;
atom5961 = -atom2729*atom1571+atom1574*uW_FFR;
atom5955 =  atom1562*uW_FFR-atom2729*atom1559;
atom5925 =  uW_FFR*atom1568-atom2729*atom1565;
atom5970 = atom1016*atom1524;
atom5972 = atom1524*atom1017;
atom5974 = -atom5972*atom498+atom5970*atom497;
atom5978 =  atom497*atom5972+atom5970*atom498;
atom5984 = atom1497*atom2745;
atom5986 = atom2745*atom1496;
atom5997 = atom1016*atom1518;
atom5999 = atom1017*atom1518;
atom6001 =  atom5997*atom497-atom5999*atom498;
atom6005 =  atom497*atom5999+atom5997*atom498;
atom1530 = -atom1019*atom1195+atom1018*atom1512;
atom6014 = atom1530*atom1016;
atom6016 = atom1530*atom1017;
atom6023 =  atom6014*atom497-atom6016*atom498;
atom6018 =  atom6016*atom497+atom6014*atom498;
atom6041 =  atom1497*atom1017+atom1021*atom1496;
atom6037 =  atom1497*atom1021-atom1496*atom1017;
atom6057 =  atom1175*atom6037+atom1194*atom6041+atom1023*atom1195;
atom6050 =  atom1023*atom1187+atom6041*atom1184+atom6037*atom1178;
atom6044 =  atom1193*atom1023+atom1190*atom6041+atom1180*atom6037;
atom6061 = -atom2731*atom1022+atom5926;
atom6064 =  atom5930-atom2731*atom1020;
atom6067 =  atom5935-atom2731*atom1016;
atom6073 =  atom6064*atom1496-atom1497*atom6067;
atom6069 =  atom1496*atom6067+atom6064*atom1497;
atom6091 =  atom6061*atom1195+atom1194*atom6073+atom6069*atom1175;
atom6076 =  atom1190*atom6073+atom1180*atom6069+atom1193*atom6061;
atom6083 =  atom6073*atom1184+atom6069*atom1178+atom6061*atom1187;
atom3086 = 1.0/( FFLstas-FFLends);
atom3087 = ( FFLstas-xR_FFL)*atom3086;
atom3098 = -FFLas*atom3086;
atom3089 =  atom3087*FFLas+FFLbs;
atom3101 =  atom3087*atom3098-atom3089*atom3086;
atom3091 =  FFLcs+atom3087*atom3089;
atom3104 =  atom3087*atom3101-atom3091*atom3086;
atom3124 = -atom3086*atom3101;
atom3121 = -atom3104*atom3086;
atom3093 =  FFLds+atom3087*atom3091;
atom3107 =  atom3087*atom3104-atom3093*atom3086;
atom3131 = -atom3107*atom3086;
atom3110 =  atom3087*atom3107-( atom3087*atom3093+FFLes)*atom3086;
atom3112 =  (atom3110*atom3110)+1.0;
atom3113 = pow(atom3112,(1.0/2.0));
atom3134 =  2.0*atom3087*( ( atom3124-atom3087*atom3098*atom3086)*atom3087+atom3121)+2.0*atom3131;
atom3139 = -atom3134/(atom3113*atom3113)*atom3110*pow(atom3112,-(1.0/2.0));
atom3143 =  -5.0000000000000000e-01*atom3139*atom3110*L_RAIL+-5.0000000000000000e-01*atom3134/atom3113*L_RAIL+1.0;
atom3077 =  uR_FFL-lR_FFL;
atom3078 = aR_FFL*atom3077;
atom3079 =  atom3078+bR_FFL;
atom3148 =  cR_FFL+atom3079*atom3077+atom3077*( atom3079+atom3078);
atom3149 = ( atom3110+5.0000000000000000e-01*atom3139*L_RAIL)*atom3148;
atom3150 = -atom3143*atom3148;
atom3183 = pow( (atom3149*atom3149)+(atom3150*atom3150)+(atom3143*atom3143),-(1.0/2.0));
atom2988 = -atom2731+zFWHSF;
atom2993 = -atom1017*atom2988-atom2738;
atom2991 =  atom1021*atom2988+atom2733-atom2734;
atom3003 =  atom1497*atom2991+atom2993*atom1496;
atom3000 =  atom2991*atom1496-atom1497*atom2993;
atom3004 =  atom3000-atom0;
atom2996 =  atom2741+atom1023*atom2988-atom2742;
atom2997 =  zFBOG+atom2996;
atom2978 =  uW_FFL-lW_FFL;
atom2984 =  dW_FFL+atom2978*( atom2978*( atom2978*aW_FFL+bW_FFL)+cW_FFL);
atom2985 = -sin(thetaW_FFL)*atom2984;
atom2987 = cos(thetaW_FFL)*atom2984;
atom3184 = atom3183*atom3149;
atom3185 = atom3150*atom3183;
atom3186 = atom3183*atom3143;
atom6385 = -atom2988*atom1022-atom5926;
atom6375 = -atom1020*atom2988-atom5930;
atom6372 = -atom1016*atom2988-atom5935;
atom6377 =  atom1497*atom6375+atom6372*atom1496;
atom6381 =  atom1496*atom6375-atom1497*atom6372;
atom6390 = -atom2987*atom1571+uW_FFL*atom1574;
atom6405 = -atom2987*atom1565+uW_FFL*atom1568;
atom6395 =  uW_FFL*atom1562-atom2987*atom1559;
atom6417 = atom2996*atom1496;
atom6415 = atom1497*atom2996;
atom3341 = 1.0/( FRRstas-FRRends);
atom3353 = -atom3341*FRRas;
atom3342 = atom3341*( FRRstas-xR_FRR);
atom3344 =  FRRas*atom3342+FRRbs;
atom3356 = -atom3341*atom3344+atom3353*atom3342;
atom3346 =  FRRcs+atom3344*atom3342;
atom3359 =  atom3342*atom3356-atom3341*atom3346;
atom3348 =  FRRds+atom3346*atom3342;
atom3362 =  atom3359*atom3342-atom3341*atom3348;
atom3365 =  atom3362*atom3342-atom3341*( atom3342*atom3348+FRRes);
atom3367 =  (atom3365*atom3365)+1.0;
atom3368 = pow(atom3367,(1.0/2.0));
atom3378 = -atom3341*atom3356;
atom3383 = -atom3341*atom3359;
atom3387 = -atom3341*atom3362;
atom3389 =  2.0*atom3342*( atom3383-( atom3341*atom3353*atom3342-atom3378)*atom3342)+2.0*atom3387;
atom3394 = -1.0/(atom3368*atom3368)*atom3365*atom3389*pow(atom3367,-(1.0/2.0));
atom3332 =  uR_FRR-lR_FRR;
atom3333 = atom3332*aR_FRR;
atom3334 =  atom3333+bR_FRR;
atom3403 =  atom3332*atom3334+cR_FRR+atom3332*( atom3333+atom3334);
atom3404 = ( -5.0000000000000000e-01*L_RAIL*atom3394+atom3365)*atom3403;
atom3398 =  5.0000000000000000e-01*1.0/atom3368*atom3389*L_RAIL+5.0000000000000000e-01*atom3365*L_RAIL*atom3394+1.0;
atom3405 = -atom3398*atom3403;
atom3438 = pow( (atom3405*atom3405)+(atom3404*atom3404)+(atom3398*atom3398),-(1.0/2.0));
atom683 = cos(aFWHSR);
atom3239 = atom683*atom1702;
atom3249 = atom3239*atom1022;
atom684 = sin(aFWHSR);
atom3240 = atom684*atom1702;
atom3241 =  zFWHSR+atom3240;
atom3252 = -atom2741+atom3241*atom1023+atom3249;
atom3253 =  zFBOG+atom3252;
atom3242 = atom3239*atom1020;
atom3245 = -atom2733+atom3241*atom1021+atom3242;
atom3246 = atom3239*atom1016;
atom3248 = -atom3241*atom1017+atom3246;
atom3259 =  atom1497*atom3245+atom3248*atom1496;
atom3256 = -atom1497*atom3248+atom3245*atom1496;
atom3260 = -atom0+atom3256;
atom3229 =  uW_FRR-lW_FRR;
atom3235 =  atom3229*( cW_FRR+atom3229*( bW_FRR+atom3229*aW_FRR))+dW_FRR;
atom3236 = -sin(thetaW_FRR)*atom3235;
atom6648 =  atom684*atom5725+atom683*atom5729;
atom6653 = -atom684*atom5729+atom683*atom5725;
atom3238 = atom3235*cos(thetaW_FRR);
atom3441 = atom3398*atom3438;
atom6688 = -atom684*atom5693+atom683*atom5689;
atom6692 =  atom684*atom5689+atom683*atom5693;
atom3439 = atom3404*atom3438;
atom6674 =  atom683*atom5652+atom5648*atom684;
atom6670 = -atom684*atom5652+atom683*atom5648;
atom3440 = atom3405*atom3438;
atom6722 =  atom683*atom5754-atom684*atom5758;
atom6726 =  atom684*atom5754+atom683*atom5758;
atom6738 = -atom684*atom5791+atom683*atom5787;
atom6742 =  atom684*atom5787+atom683*atom5791;
atom6709 = -atom684*atom5823+atom683*atom5819;
atom6704 =  atom684*atom5819+atom683*atom5823;
atom1598 =  atom683*atom1539-atom684*atom1536;
atom1595 =  atom684*atom1539+atom683*atom1536;
atom1604 =  atom683*atom1545-atom684*atom1542;
atom1601 =  atom683*atom1542+atom684*atom1545;
atom6781 =  atom684*atom5847+atom683*atom5851;
atom6777 = -atom684*atom5851+atom683*atom5847;
atom6793 =  atom683*atom5874-atom5878*atom684;
atom6797 =  atom684*atom5874+atom683*atom5878;
atom6764 = -atom684*atom5902+atom683*atom5898;
atom6759 =  atom683*atom5902+atom684*atom5898;
atom6829 = atom3239*atom1023;
atom6831 = -atom3241*atom1022+atom6829;
atom6815 = -atom3239*atom1017;
atom6816 =  atom6815-atom3241*atom1016;
atom6818 = atom3239*atom1021;
atom6820 =  atom6818-atom3241*atom1020;
atom6826 =  atom6816*atom1496+atom1497*atom6820;
atom6822 =  atom6820*atom1496-atom1497*atom6816;
atom1607 =  atom683*atom1548+atom684*atom1551;
atom1610 = -atom684*atom1548+atom683*atom1551;
atom6813 =  atom1610*uW_FRR-atom1607*atom3238;
atom6853 = -atom3238*atom1595+atom1598*uW_FRR;
atom6843 =  atom1604*uW_FRR-atom1601*atom3238;
atom6869 = atom1496*atom3252;
atom6871 = atom1497*atom3252;
atom6861 =  atom6014*atom684+atom683*atom6016;
atom6866 = -atom6016*atom684+atom6014*atom683;
atom6889 =  atom5970*atom684+atom683*atom5972;
atom6885 = -atom684*atom5972+atom683*atom5970;
atom6907 =  atom683*atom5999+atom684*atom5997;
atom6903 =  atom683*atom5997-atom684*atom5999;
atom6935 = -atom3240*atom1022+atom6829;
atom6922 =  atom6815-atom1016*atom3240;
atom6925 = -atom1020*atom3240+atom6818;
atom6927 =  atom6925*atom1496-atom1497*atom6922;
atom6931 =  atom1497*atom6925+atom6922*atom1496;
atom6937 =  atom6935*atom1195+atom6927*atom1194+atom1175*atom6931;
atom6944 =  atom6927*atom1190+atom1193*atom6935+atom1180*atom6931;
atom6951 =  atom6931*atom1178+atom6935*atom1187+atom6927*atom1184;
atom3591 = 1.0/( FRLstas-FRLends);
atom3592 = atom3591*( FRLstas-xR_FRL);
atom3594 =  FRLbs+atom3592*FRLas;
atom3596 =  FRLcs+atom3592*atom3594;
atom3598 =  FRLds+atom3596*atom3592;
atom3603 = -FRLas*atom3591;
atom3606 = -atom3594*atom3591+atom3603*atom3592;
atom3609 = -atom3596*atom3591+atom3592*atom3606;
atom3612 = -atom3598*atom3591+atom3609*atom3592;
atom3615 = -atom3591*( atom3592*atom3598+FRLes)+atom3612*atom3592;
atom3617 =  (atom3615*atom3615)+1.0;
atom3618 = pow(atom3617,(1.0/2.0));
atom3629 = -atom3606*atom3591;
atom3634 = -atom3609*atom3591;
atom3626 = -atom3612*atom3591;
atom3639 =  2.0*atom3626+2.0*atom3592*( atom3634+atom3592*( atom3629-atom3603*atom3592*atom3591));
atom3644 = -atom3615*pow(atom3617,-(1.0/2.0))*atom3639/(atom3618*atom3618);
atom3582 =  uR_FRL-lR_FRL;
atom3583 = atom3582*aR_FRL;
atom3584 =  atom3583+bR_FRL;
atom3653 =  cR_FRL+atom3582*( atom3584+atom3583)+atom3584*atom3582;
atom3654 = ( atom3615+5.0000000000000000e-01*atom3644*L_RAIL)*atom3653;
atom3648 =  -5.0000000000000000e-01*atom3615*atom3644*L_RAIL+-5.0000000000000000e-01*atom3639*L_RAIL/atom3618+1.0;
atom3655 = -atom3648*atom3653;
atom3688 = pow( (atom3655*atom3655)+(atom3654*atom3654)+(atom3648*atom3648),-(1.0/2.0));
atom3494 =  zFWHSR-atom3240;
atom3502 = -atom2741+atom3494*atom1023-atom3249;
atom3503 =  zFBOG+atom3502;
atom3499 = -atom3494*atom1017-atom3246;
atom3497 =  atom3494*atom1021-atom2733-atom3242;
atom3506 =  atom3497*atom1496-atom1497*atom3499;
atom3510 =  atom3506-atom0;
atom3509 =  atom1497*atom3497+atom3499*atom1496;
atom3484 =  uW_FRL-lW_FRL;
atom3490 =  atom3484*( cW_FRL+( atom3484*aW_FRL+bW_FRL)*atom3484)+dW_FRL;
atom3491 = -sin(thetaW_FRL)*atom3490;
atom3493 = cos(thetaW_FRL)*atom3490;
atom3690 = atom3688*atom3655;
atom3689 = atom3654*atom3688;
atom3691 = atom3688*atom3648;
atom7252 = -atom3494*atom1020-atom6818;
atom7249 = -atom6815-atom3494*atom1016;
atom7254 =  atom7249*atom1496+atom1497*atom7252;
atom7258 =  atom1496*atom7252-atom1497*atom7249;
atom7262 = -atom6829-atom3494*atom1022;
atom7285 =  atom1610*uW_FRL-atom1607*atom3493;
atom7274 = -atom3493*atom1595+atom1598*uW_FRL;
atom7247 =  atom1604*uW_FRL-atom3493*atom1601;
atom7294 = atom1497*atom3502;
atom7296 = atom3502*atom1496;

_dPhic_dq[0] = atom1917;
_dPhic_dq[1] = atom2168;
_dPhic_dq[2] = atom2424;
_dPhic_dq[3] = atom2675;
_dPhic_dq[4] = atom2933;
_dPhic_dq[5] = atom3184;
_dPhic_dq[6] = atom3439;
_dPhic_dq[7] = atom3689;
_dPhic_dq[8] = atom1918;
_dPhic_dq[9] = atom2169;
_dPhic_dq[10] = atom2425;
_dPhic_dq[11] = atom2676;
_dPhic_dq[12] = atom2934;
_dPhic_dq[13] = atom3185;
_dPhic_dq[14] = atom3440;
_dPhic_dq[15] = atom3690;
_dPhic_dq[16] = atom1919;
_dPhic_dq[17] = atom2170;
_dPhic_dq[18] = atom2426;
_dPhic_dq[19] = atom2677;
_dPhic_dq[20] = atom2935;
_dPhic_dq[21] = atom3186;
_dPhic_dq[22] = atom3441;
_dPhic_dq[23] = atom3691;
_dPhic_dq[24] =  ( atom3843*atom1713+atom3811*atom1737+atom1730*atom3814+uW_RFR*atom3838+atom3822*atom1711+atom1736*atom1174)*atom1919+( atom1736*atom1181+atom1730*atom3771+atom3778*atom1711+uW_RFR*atom3794+atom3799*atom1713+atom3774*atom1737)*atom1918+( uW_RFR*atom3756+atom3735*atom1737+atom3752*atom1713+atom3760*atom1711+atom1730*atom3733+atom1736*atom1179)*atom1917;
_dPhic_dq[25] =  ( atom1988*atom3774+atom3794*uW_RFL+atom3778*atom1969+atom1987*atom1181+atom3799*atom1971+atom1981*atom3771)*atom2169+( atom1987*atom1174+atom3843*atom1971+atom1981*atom3814+atom3822*atom1969+atom3811*atom1988+uW_RFL*atom3838)*atom2170+( atom1987*atom1179+atom3756*uW_RFL+atom1988*atom3735+atom1981*atom3733+atom3752*atom1971+atom3760*atom1969)*atom2168;
_dPhic_dq[26] =  ( atom4804*atom2222+atom3811*atom2244+atom4809*uW_RRR+atom2243*atom1174+atom3822*atom2220+atom2237*atom3814)*atom2426+atom2425*( atom3778*atom2220+atom4762*uW_RRR+atom3771*atom2237+atom2244*atom3774+atom2243*atom1181+atom4768*atom2222)+atom2424*( atom3735*atom2244+atom2243*atom1179+atom4785*uW_RRR+atom2237*atom3733+atom2222*atom4791+atom3760*atom2220);
_dPhic_dq[27] =  atom2675*( atom3735*atom2495+atom2478*atom4791+atom2488*atom3733+atom4785*uW_RRL+atom2476*atom3760+atom2494*atom1179)+atom2676*( uW_RRL*atom4762+atom2494*atom1181+atom3771*atom2488+atom4768*atom2478+atom3774*atom2495+atom2476*atom3778)+atom2677*( atom2476*atom3822+atom2488*atom3814+atom4809*uW_RRL+atom4804*atom2478+atom3811*atom2495+atom2494*atom1174);
_dPhic_dq[28] =  ( atom5703*atom2727+atom2746*atom3733+atom2752*atom1179+atom2753*atom3735+atom5699*uW_FFR+atom2729*atom5695)*atom2933+atom2934*( atom2746*atom3771+atom2729*atom5654+atom2752*atom1181+atom2753*atom3774+atom5658*uW_FFR+atom5662*atom2727)+( atom5715*atom2727+atom2729*atom5736+uW_FFR*atom5731+atom2746*atom3814+atom2752*atom1174+atom3811*atom2753)*atom2935;
_dPhic_dq[29] =  atom3186*( atom5715*atom2985+uW_FFL*atom5731+atom2997*atom3814+atom3811*atom3004+atom3003*atom1174+atom5736*atom2987)+atom3185*( atom1181*atom3003+atom3004*atom3774+atom5662*atom2985+uW_FFL*atom5658+atom2997*atom3771+atom2987*atom5654)+( atom3735*atom3004+atom5695*atom2987+atom2997*atom3733+atom5703*atom2985+uW_FFL*atom5699+atom3003*atom1179)*atom3184;
_dPhic_dq[30] =  atom3439*( atom3735*atom3260+atom3253*atom3733+atom3236*atom5703+atom3259*atom1179+atom6688*atom3238+uW_FRR*atom6692)+atom3440*( atom3260*atom3774+atom3259*atom1181+atom3236*atom5662+atom6674*uW_FRR+atom3238*atom6670+atom3253*atom3771)+( atom3811*atom3260+atom6648*uW_FRR+atom3253*atom3814+atom3236*atom5715+atom3259*atom1174+atom6653*atom3238)*atom3441;
_dPhic_dq[31] =  ( atom1179*atom3509+atom3735*atom3510+atom3493*atom6688+uW_FRL*atom6692+atom3733*atom3503+atom5703*atom3491)*atom3689+( atom3510*atom3774+atom3493*atom6670+atom1181*atom3509+atom6674*uW_FRL+atom3771*atom3503+atom3491*atom5662)*atom3690+( atom5715*atom3491+atom3811*atom3510+atom6648*uW_FRL+atom3509*atom1174+atom6653*atom3493+atom3814*atom3503)*atom3691;
_dPhic_dq[32] = -atom1918*( atom1193*atom1737-atom1730*atom1190-uW_RFR*atom3896-atom3901*atom1713-atom3882*atom1711)+atom1917*( atom3862*atom1713+atom1730*atom1184+uW_RFR*atom3866-atom1187*atom1737+atom3870*atom1711)+( atom3935*atom1713+atom3916*atom1711+uW_RFR*atom3930-atom1195*atom1737+atom1730*atom1194)*atom1919;
_dPhic_dq[33] = -( atom1988*atom1195-atom3916*atom1969-atom3935*atom1971-atom1981*atom1194-atom3930*uW_RFL)*atom2170+atom2169*( atom3896*uW_RFL+atom1981*atom1190+atom3901*atom1971-atom1988*atom1193+atom3882*atom1969)+atom2168*( atom3862*atom1971+atom3866*uW_RFL+atom1981*atom1184-atom1988*atom1187+atom3870*atom1969);
_dPhic_dq[34] =  atom2425*( atom4818*uW_RRR-atom1193*atom2244+atom3882*atom2220+atom2222*atom4824+atom2237*atom1190)+( atom3916*atom2220+atom4854*atom2222+atom4859*uW_RRR-atom1195*atom2244+atom2237*atom1194)*atom2426+atom2424*( atom4837*uW_RRR+atom2222*atom4843+atom2237*atom1184+atom2220*atom3870-atom1187*atom2244);
_dPhic_dq[35] =  atom2676*( atom2478*atom4824+uW_RRL*atom4818-atom1193*atom2495+atom2488*atom1190+atom2476*atom3882)+atom2675*( atom4837*uW_RRL+atom2478*atom4843-atom1187*atom2495+atom2476*atom3870+atom2488*atom1184)+atom2677*( atom2488*atom1194+atom2476*atom3916-atom1195*atom2495+atom4859*uW_RRL+atom2478*atom4854);
_dPhic_dq[36] = -atom2933*( atom2753*atom1187-atom2746*atom1184-atom5797*uW_FFR-atom2729*atom5793-atom5801*atom2727)+atom2934*( atom5768*atom2727+atom2729*atom5760+atom2746*atom1190+atom5764*uW_FFR-atom1193*atom2753)+atom2935*( uW_FFR*atom5825+atom2746*atom1194-atom2753*atom1195+atom5811*atom2727+atom2729*atom5830);
_dPhic_dq[37] = -( atom3004*atom1187-atom5793*atom2987-atom2997*atom1184-atom5801*atom2985-uW_FFL*atom5797)*atom3184+atom3186*( atom2997*atom1194+uW_FFL*atom5825+atom2987*atom5830+atom5811*atom2985-atom3004*atom1195)+atom3185*( atom5768*atom2985-atom1193*atom3004+atom2997*atom1190+uW_FFL*atom5764+atom5760*atom2987);
_dPhic_dq[38] =  atom3439*( atom6742*uW_FRR+atom3253*atom1184-atom1187*atom3260+atom3238*atom6738+atom3236*atom5801)-atom3440*( atom1193*atom3260-atom3253*atom1190-atom3236*atom5768-uW_FRR*atom6726-atom6722*atom3238)+atom3441*( atom6709*atom3238+atom3253*atom1194+atom6704*uW_FRR+atom3236*atom5811-atom1195*atom3260);
_dPhic_dq[39] =  atom3689*( atom1184*atom3503+atom3493*atom6738-atom3510*atom1187+atom6742*uW_FRL+atom5801*atom3491)+atom3690*( atom5768*atom3491-atom1193*atom3510+atom3493*atom6722+uW_FRL*atom6726+atom1190*atom3503)-atom3691*( atom3510*atom1195-atom6704*uW_FRL-atom6709*atom3493-atom5811*atom3491-atom1194*atom3503);
_dPhic_dq[40] = -atom1917*( atom1180*atom1736+uW_RFR*atom1279+atom1711*atom1237+atom1190*atom1737+atom1282*atom1713+atom1730*atom1193)+( atom1184*atom1737+atom1276*atom1713+uW_RFR*atom1273+atom1730*atom1187+atom1231*atom1711+atom1736*atom1178)*atom1918;
_dPhic_dq[41] = -( atom1969*atom1237+uW_RFL*atom1279+atom1193*atom1981+atom1988*atom1190+atom1282*atom1971+atom1180*atom1987)*atom2168+( atom1276*atom1971+atom1981*atom1187+atom1987*atom1178+atom1988*atom1184+atom1231*atom1969+uW_RFL*atom1273)*atom2169;
_dPhic_dq[42] =  atom2425*( uW_RRR*atom1310+atom2244*atom1184+atom2222*atom1313+atom2243*atom1178+atom1231*atom2220+atom2237*atom1187)-atom2424*( atom1180*atom2243+atom1316*uW_RRR+atom1190*atom2244+atom1319*atom2222+atom1193*atom2237+atom2220*atom1237);
_dPhic_dq[43] = -atom2675*( atom1180*atom2494+atom2476*atom1237+atom1316*uW_RRL+atom1193*atom2488+atom1190*atom2495+atom1319*atom2478)+( atom1184*atom2495+uW_RRL*atom1310+atom2488*atom1187+atom2476*atom1231+atom2478*atom1313+atom2494*atom1178)*atom2676;
_dPhic_dq[44] = -( atom2753*atom1190+atom1180*atom2752+uW_FFR*atom1565+atom1524*atom2727+atom2729*atom1568+atom2746*atom1193)*atom2933+( atom2752*atom1178+atom2746*atom1187+atom1559*uW_FFR+atom2753*atom1184+atom2727*atom1518+atom2729*atom1562)*atom2934;
_dPhic_dq[45] = -( atom3004*atom1190+atom2987*atom1568+uW_FFL*atom1565+atom1193*atom2997+atom1180*atom3003+atom2985*atom1524)*atom3184+atom3185*( atom2987*atom1562+uW_FFL*atom1559+atom2997*atom1187+atom2985*atom1518+atom3003*atom1178+atom3004*atom1184);
_dPhic_dq[46] = -( atom1193*atom3253+atom3236*atom1524+atom1604*atom3238+atom1180*atom3259+atom1190*atom3260+uW_FRR*atom1601)*atom3439+atom3440*( atom3260*atom1184+atom3253*atom1187+atom3236*atom1518+uW_FRR*atom1595+atom3259*atom1178+atom1598*atom3238);
_dPhic_dq[47] = -( atom1604*atom3493+atom1193*atom3503+atom1180*atom3509+atom3510*atom1190+uW_FRL*atom1601+atom3491*atom1524)*atom3689+( uW_FRL*atom1595+atom3509*atom1178+atom3510*atom1184+atom1187*atom3503+atom1598*atom3493+atom3491*atom1518)*atom3690;
_dPhic_dq[48] =  atom1919*( atom4014*atom1713+atom3998*atom1711+uW_RFR*atom4009-atom1736*atom1194+atom1733*atom1175)+( atom3986*atom1713+atom3970*atom1711-atom1736*atom1190+atom1733*atom1180+uW_RFR*atom3981)*atom1918+atom1917*( uW_RFR*atom3959+atom3955*atom1713+atom1733*atom1178+atom3961*atom1711-atom1736*atom1184);
_dPhic_dq[49] =  atom2169*( atom3986*atom1971+atom3970*atom1969+atom1180*atom1984-atom1987*atom1190+atom3981*uW_RFL)+( atom4014*atom1971+uW_RFL*atom4009+atom3998*atom1969+atom1984*atom1175-atom1987*atom1194)*atom2170-( atom1987*atom1184-atom3955*atom1971-atom3959*uW_RFL-atom3961*atom1969-atom1984*atom1178)*atom2168;
_dPhic_dq[50] =  atom2425*( atom4873*uW_RRR+atom1180*atom2240+atom2220*atom3970+atom2222*atom4879-atom2243*atom1190)-atom2424*( atom2243*atom1184-atom2220*atom3961-atom2222*atom4898-atom4892*uW_RRR-atom2240*atom1178)+( atom4914*uW_RRR+atom2220*atom3998+atom2222*atom4909+atom1175*atom2240-atom2243*atom1194)*atom2426;
_dPhic_dq[51] =  atom2675*( atom2491*atom1178+atom4892*uW_RRL-atom2494*atom1184+atom2476*atom3961+atom2478*atom4898)+( atom4873*uW_RRL+atom2476*atom3970+atom1180*atom2491+atom2478*atom4879-atom2494*atom1190)*atom2676+atom2677*( atom4914*uW_RRL+atom2478*atom4909-atom2494*atom1194+atom2476*atom3998+atom1175*atom2491);
_dPhic_dq[52] = 0.0000000000000000e+00;
_dPhic_dq[53] = 0.0000000000000000e+00;
_dPhic_dq[54] = 0.0000000000000000e+00;
_dPhic_dq[55] = 0.0000000000000000e+00;
_dPhic_dq[56] = 0.0000000000000000e+00;
_dPhic_dq[57] = 0.0000000000000000e+00;
_dPhic_dq[58] = 0.0000000000000000e+00;
_dPhic_dq[59] = 0.0000000000000000e+00;
_dPhic_dq[60] = -( atom2752*atom1190-atom1180*atom2749-atom5857*uW_FFR-atom2729*atom5853-atom2727*atom5859)*atom2934-atom2935*( atom2752*atom1194-atom5904*uW_FFR-atom5893*atom2727-atom1175*atom2749-atom2729*atom5909)+( atom2729*atom5880+atom5884*uW_FFR+atom2749*atom1178+atom5886*atom2727-atom2752*atom1184)*atom2933;
_dPhic_dq[61] =  ( atom3000*atom1178+atom5884*uW_FFL+atom2987*atom5880-atom3003*atom1184+atom5886*atom2985)*atom3184+atom3186*( atom5909*atom2987+atom2985*atom5893+atom5904*uW_FFL-atom1194*atom3003+atom3000*atom1175)+atom3185*( atom2987*atom5853-atom1190*atom3003+atom2985*atom5859+uW_FFL*atom5857+atom3000*atom1180);
_dPhic_dq[62] =  ( uW_FRR*atom6759-atom3259*atom1194+atom1175*atom3256+atom3236*atom5893+atom6764*atom3238)*atom3441+( atom3256*atom1178+atom3238*atom6793-atom3259*atom1184+atom3236*atom5886+atom6797*uW_FRR)*atom3439-atom3440*( atom3259*atom1190-uW_FRR*atom6781-atom3236*atom5859-atom6777*atom3238-atom1180*atom3256);
_dPhic_dq[63] =  ( uW_FRL*atom6781+atom1180*atom3506-atom1190*atom3509+atom3491*atom5859+atom6777*atom3493)*atom3690+( uW_FRL*atom6759+atom3491*atom5893+atom3506*atom1175-atom1194*atom3509+atom3493*atom6764)*atom3691-( atom3509*atom1184-atom6797*uW_FRL-atom5886*atom3491-atom3506*atom1178-atom3493*atom6793)*atom3689;
_dPhic_dq[64] =  atom1919*atom1195+atom1193*atom1918+atom1917*atom1187;
_dPhic_dq[65] =  atom1193*atom2169+atom1195*atom2170+atom1187*atom2168;
_dPhic_dq[66] =  atom2424*atom1187+atom1193*atom2425+atom1195*atom2426;
_dPhic_dq[67] =  atom2677*atom1195+atom2675*atom1187+atom1193*atom2676;
_dPhic_dq[68] = 0.0000000000000000e+00;
_dPhic_dq[69] = 0.0000000000000000e+00;
_dPhic_dq[70] = 0.0000000000000000e+00;
_dPhic_dq[71] = 0.0000000000000000e+00;
_dPhic_dq[72] =  atom1919*( atom4040*atom1175+atom4068+atom4044*atom1194+atom1195*atom4030)+( atom4044*atom1184+atom4027+atom4040*atom1178+atom1187*atom4030)*atom1917+( atom4052+atom1193*atom4030+atom1180*atom4040+atom4044*atom1190)*atom1918;
_dPhic_dq[73] =  atom2168*( atom4518+atom4488*atom1187+atom4500*atom1184+atom4496*atom1178)+( atom4486+atom4500*atom1194+atom1195*atom4488+atom1175*atom4496)*atom2170+atom2169*( atom1180*atom4496+atom4500*atom1190+atom4508+atom1193*atom4488);
_dPhic_dq[74] =  ( atom4945*atom1184+atom4941*atom1178+atom4958+atom1187*atom4931)*atom2424+( atom1175*atom4941+atom1195*atom4931+atom4969+atom4945*atom1194)*atom2426+atom2425*( atom1193*atom4931+atom1180*atom4941+atom4945*atom1190+atom4928);
_dPhic_dq[75] =  atom2677*( atom1194*atom5375+atom5364+atom5379*atom1195+atom1175*atom5371)+atom2675*( atom5379*atom1187+atom5375*atom1184+atom5401+atom5371*atom1178)+( atom1193*atom5379+atom1180*atom5371+atom1190*atom5375+atom5391)*atom2676;
_dPhic_dq[76] = 0.0000000000000000e+00;
_dPhic_dq[77] = 0.0000000000000000e+00;
_dPhic_dq[78] = 0.0000000000000000e+00;
_dPhic_dq[79] = 0.0000000000000000e+00;
_dPhic_dq[80] = -( atom1711*atom1246+atom1195*atom1721-atom4088*atom1194-atom1175*atom4086-atom4125*uW_RFR-atom4130*atom1713)*atom1919+( uW_RFR*atom4080-atom1234*atom1711+atom4088*atom1184+atom4086*atom1178-atom1721*atom1187+atom4076*atom1713)*atom1917+atom1918*( uW_RFR*atom4099+atom1180*atom4086-atom1240*atom1711+atom4088*atom1190+atom4104*atom1713-atom1193*atom1721);
_dPhic_dq[81] =  ( atom4536*atom1184+atom4080*uW_RFL-atom1234*atom1969-atom1975*atom1187+atom4534*atom1178+atom4076*atom1971)*atom2168+atom2169*( atom1180*atom4534-atom1240*atom1969+uW_RFL*atom4099-atom1193*atom1975+atom4104*atom1971+atom4536*atom1190)-( atom1969*atom1246-atom1175*atom4534-atom4125*uW_RFL+atom1975*atom1195-atom4130*atom1971-atom4536*atom1194)*atom2170;
_dPhic_dq[82] = -atom2425*( atom2220*atom1240-atom2222*atom4981+atom1193*atom2229-atom4987*atom1190-atom4975*uW_RRR-atom1180*atom4985)+( atom1194*atom4987+atom5019*atom2222+atom1175*atom4985-atom1195*atom2229-atom2220*atom1246+atom5024*uW_RRR)*atom2426+( uW_RRR*atom5000+atom4985*atom1178-atom1187*atom2229+atom5006*atom2222+atom4987*atom1184-atom2220*atom1234)*atom2424;
_dPhic_dq[83] = -atom2677*( atom2476*atom1246-atom2478*atom5019-atom5413*atom1194+atom2482*atom1195-atom5024*uW_RRL-atom5411*atom1175)+atom2675*( atom2478*atom5006+uW_RRL*atom5000-atom2476*atom1234+atom5413*atom1184-atom2482*atom1187+atom5411*atom1178)-( atom1193*atom2482-atom2478*atom4981-atom5413*atom1190-atom5411*atom1180-atom4975*uW_RRL+atom2476*atom1240)*atom2676;
_dPhic_dq[84] = 0.0000000000000000e+00;
_dPhic_dq[85] = 0.0000000000000000e+00;
_dPhic_dq[86] = 0.0000000000000000e+00;
_dPhic_dq[87] = 0.0000000000000000e+00;
_dPhic_dq[88] = 0.0000000000000000e+00;
_dPhic_dq[89] = 0.0000000000000000e+00;
_dPhic_dq[90] = 0.0000000000000000e+00;
_dPhic_dq[91] = 0.0000000000000000e+00;
_dPhic_dq[92] =  atom1193*atom2934+atom2935*atom1195+atom1187*atom2933;
_dPhic_dq[93] =  atom1193*atom3185+atom3186*atom1195+atom1187*atom3184;
_dPhic_dq[94] =  atom1195*atom3441+atom3439*atom1187+atom3440*atom1193;
_dPhic_dq[95] =  atom1193*atom3690+atom1195*atom3691+atom1187*atom3689;
_dPhic_dq[96] = 0.0000000000000000e+00;
_dPhic_dq[97] = 0.0000000000000000e+00;
_dPhic_dq[98] = 0.0000000000000000e+00;
_dPhic_dq[99] = 0.0000000000000000e+00;
_dPhic_dq[100] =  atom2933*( atom5942*atom1184+atom5955+atom5928*atom1187+atom5938*atom1178)+atom2934*( atom5925+atom1193*atom5928+atom1180*atom5938+atom5942*atom1190)+atom2935*( atom5961+atom1175*atom5938+atom5942*atom1194+atom5928*atom1195);
_dPhic_dq[101] =  atom3185*( atom6381*atom1190+atom1180*atom6377+atom1193*atom6385+atom6405)+atom3186*( atom6390+atom1175*atom6377+atom6381*atom1194+atom6385*atom1195)+( atom6395+atom6385*atom1187+atom6381*atom1184+atom6377*atom1178)*atom3184;
_dPhic_dq[102] =  atom3441*( atom6831*atom1195+atom1175*atom6826+atom6822*atom1194+atom6813)+atom3440*( atom1180*atom6826+atom6831*atom1193+atom6822*atom1190+atom6843)+( atom6822*atom1184+atom6826*atom1178+atom6853+atom6831*atom1187)*atom3439;
_dPhic_dq[103] =  ( atom7262*atom1195+atom7285+atom1175*atom7254+atom1194*atom7258)*atom3691+( atom7254*atom1178+atom7258*atom1184+atom7262*atom1187+atom7274)*atom3689+atom3690*( atom1193*atom7262+atom1190*atom7258+atom7247+atom1180*atom7254);
_dPhic_dq[104] = 0.0000000000000000e+00;
_dPhic_dq[105] = 0.0000000000000000e+00;
_dPhic_dq[106] = 0.0000000000000000e+00;
_dPhic_dq[107] = 0.0000000000000000e+00;
_dPhic_dq[108] =  ( atom5978*uW_FFR+atom1180*atom5984-atom1193*atom2737-atom1527*atom2727+atom1190*atom5986+atom2729*atom5974)*atom2934-atom2935*( atom2737*atom1195+atom1533*atom2727-atom1175*atom5984-atom2729*atom6023-atom6018*uW_FFR-atom1194*atom5986)+atom2933*( atom1184*atom5986-atom1521*atom2727-atom2737*atom1187+atom5984*atom1178+atom2729*atom6001+atom6005*uW_FFR);
_dPhic_dq[109] =  ( uW_FFL*atom5978+atom2987*atom5974+atom1180*atom6415-atom1193*atom2991+atom6417*atom1190-atom1527*atom2985)*atom3185+( atom6415*atom1178+atom6417*atom1184+atom2987*atom6001+uW_FFL*atom6005-atom2985*atom1521-atom1187*atom2991)*atom3184+atom3186*( atom2987*atom6023+atom6417*atom1194+atom1175*atom6415+atom6018*uW_FFL-atom2985*atom1533-atom1195*atom2991);
_dPhic_dq[110] = -( atom3245*atom1195+atom3236*atom1533-atom6866*atom3238-atom6871*atom1175-atom6861*uW_FRR-atom1194*atom6869)*atom3441+atom3440*( atom6889*uW_FRR+atom6885*atom3238-atom1193*atom3245-atom3236*atom1527+atom1190*atom6869+atom1180*atom6871)+atom3439*( atom1184*atom6869-atom3236*atom1521+atom6871*atom1178-atom3245*atom1187+atom3238*atom6903+atom6907*uW_FRR);
_dPhic_dq[111] =  ( atom6866*atom3493+atom1194*atom7296+atom1175*atom7294-atom3491*atom1533+atom6861*uW_FRL-atom1195*atom3497)*atom3691+( atom7294*atom1178+atom3493*atom6903-atom3491*atom1521+atom7296*atom1184-atom1187*atom3497+atom6907*uW_FRL)*atom3689+atom3690*( atom6889*uW_FRL+atom6885*atom3493-atom1193*atom3497+atom7296*atom1190-atom1527*atom3491+atom1180*atom7294);
_dPhic_dq[112] =  atom4146*atom1917+atom4159*atom1919+atom4152*atom1918;
_dPhic_dq[113] =  atom4146*atom2168+atom4159*atom2170+atom4152*atom2169;
_dPhic_dq[114] = 0.0000000000000000e+00;
_dPhic_dq[115] = 0.0000000000000000e+00;
_dPhic_dq[116] = 0.0000000000000000e+00;
_dPhic_dq[117] = 0.0000000000000000e+00;
_dPhic_dq[118] = 0.0000000000000000e+00;
_dPhic_dq[119] = 0.0000000000000000e+00;
_dPhic_dq[120] =  atom1917*( atom4178+atom4027)+( atom4193+atom4068)*atom1919+( atom4185+atom4052)*atom1918;
_dPhic_dq[121] = -( atom4185-atom4508)*atom2169-( atom4178-atom4518)*atom2168+( atom4486-atom4193)*atom2170;
_dPhic_dq[122] = 0.0000000000000000e+00;
_dPhic_dq[123] = 0.0000000000000000e+00;
_dPhic_dq[124] = 0.0000000000000000e+00;
_dPhic_dq[125] = 0.0000000000000000e+00;
_dPhic_dq[126] = 0.0000000000000000e+00;
_dPhic_dq[127] = 0.0000000000000000e+00;
_dPhic_dq[128] = 0.0000000000000000e+00;
_dPhic_dq[129] = 0.0000000000000000e+00;
_dPhic_dq[130] = 0.0000000000000000e+00;
_dPhic_dq[131] = 0.0000000000000000e+00;
_dPhic_dq[132] = 0.0000000000000000e+00;
_dPhic_dq[133] = 0.0000000000000000e+00;
_dPhic_dq[134] = 0.0000000000000000e+00;
_dPhic_dq[135] = 0.0000000000000000e+00;
_dPhic_dq[136] = 0.0000000000000000e+00;
_dPhic_dq[137] = 0.0000000000000000e+00;
_dPhic_dq[138] =  atom4152*atom2425+atom4146*atom2424+atom4159*atom2426;
_dPhic_dq[139] =  atom2677*atom4159+atom4152*atom2676+atom4146*atom2675;
_dPhic_dq[140] = 0.0000000000000000e+00;
_dPhic_dq[141] = 0.0000000000000000e+00;
_dPhic_dq[142] = 0.0000000000000000e+00;
_dPhic_dq[143] = 0.0000000000000000e+00;
_dPhic_dq[144] = 0.0000000000000000e+00;
_dPhic_dq[145] = 0.0000000000000000e+00;
_dPhic_dq[146] =  atom2426*( atom5067+atom4969)+( atom5059+atom4958)*atom2424+( atom5052+atom4928)*atom2425;
_dPhic_dq[147] = -atom2675*( atom5059-atom5401)+atom2676*( atom5391-atom5052)-atom2677*( atom5067-atom5364);
_dPhic_dq[148] = 0.0000000000000000e+00;
_dPhic_dq[149] = 0.0000000000000000e+00;
_dPhic_dq[150] = 0.0000000000000000e+00;
_dPhic_dq[151] = 0.0000000000000000e+00;
_dPhic_dq[152] = 0.0000000000000000e+00;
_dPhic_dq[153] = 0.0000000000000000e+00;
_dPhic_dq[154] = 0.0000000000000000e+00;
_dPhic_dq[155] = 0.0000000000000000e+00;
_dPhic_dq[156] = 0.0000000000000000e+00;
_dPhic_dq[157] = 0.0000000000000000e+00;
_dPhic_dq[158] = 0.0000000000000000e+00;
_dPhic_dq[159] = 0.0000000000000000e+00;
_dPhic_dq[160] = 0.0000000000000000e+00;
_dPhic_dq[161] = 0.0000000000000000e+00;
_dPhic_dq[162] = 0.0000000000000000e+00;
_dPhic_dq[163] = 0.0000000000000000e+00;
_dPhic_dq[164] =  atom6050*atom2933+atom6044*atom2934+atom2935*atom6057;
_dPhic_dq[165] =  atom6044*atom3185+atom3186*atom6057+atom6050*atom3184;
_dPhic_dq[166] = 0.0000000000000000e+00;
_dPhic_dq[167] = 0.0000000000000000e+00;
_dPhic_dq[168] = 0.0000000000000000e+00;
_dPhic_dq[169] = 0.0000000000000000e+00;
_dPhic_dq[170] = 0.0000000000000000e+00;
_dPhic_dq[171] = 0.0000000000000000e+00;
_dPhic_dq[172] =  ( atom5925+atom6076)*atom2934+atom2935*( atom5961+atom6091)+( atom6083+atom5955)*atom2933;
_dPhic_dq[173] = -atom3185*( atom6076-atom6405)+atom3186*( atom6390-atom6091)+( atom6395-atom6083)*atom3184;
_dPhic_dq[174] = 0.0000000000000000e+00;
_dPhic_dq[175] = 0.0000000000000000e+00;
_dPhic_dq[176] = 0.0000000000000000e+00;
_dPhic_dq[177] = 0.0000000000000000e+00;
_dPhic_dq[178] = 0.0000000000000000e+00;
_dPhic_dq[179] = 0.0000000000000000e+00;
_dPhic_dq[180] = 0.0000000000000000e+00;
_dPhic_dq[181] = 0.0000000000000000e+00;
_dPhic_dq[182] = 0.0000000000000000e+00;
_dPhic_dq[183] = 0.0000000000000000e+00;
_dPhic_dq[184] = 0.0000000000000000e+00;
_dPhic_dq[185] = 0.0000000000000000e+00;
_dPhic_dq[186] = 0.0000000000000000e+00;
_dPhic_dq[187] = 0.0000000000000000e+00;
_dPhic_dq[188] = 0.0000000000000000e+00;
_dPhic_dq[189] = 0.0000000000000000e+00;
_dPhic_dq[190] =  atom3439*atom6050+atom6057*atom3441+atom3440*atom6044;
_dPhic_dq[191] =  atom6050*atom3689+atom6044*atom3690+atom6057*atom3691;
_dPhic_dq[192] = 0.0000000000000000e+00;
_dPhic_dq[193] = 0.0000000000000000e+00;
_dPhic_dq[194] = 0.0000000000000000e+00;
_dPhic_dq[195] = 0.0000000000000000e+00;
_dPhic_dq[196] = 0.0000000000000000e+00;
_dPhic_dq[197] = 0.0000000000000000e+00;
_dPhic_dq[198] =  atom3440*( atom6944+atom6843)+( atom6853+atom6951)*atom3439+( atom6937+atom6813)*atom3441;
_dPhic_dq[199] =  ( atom7274-atom6951)*atom3689-( atom6937-atom7285)*atom3691-atom3690*( atom6944-atom7247);
_dPhic_dq[200] = 0.0000000000000000e+00;
_dPhic_dq[201] = 0.0000000000000000e+00;
_dPhic_dq[202] = 0.0000000000000000e+00;
_dPhic_dq[203] = 0.0000000000000000e+00;
_dPhic_dq[204] = 0.0000000000000000e+00;
_dPhic_dq[205] = 0.0000000000000000e+00;
_dPhic_dq[206] = 0.0000000000000000e+00;
_dPhic_dq[207] = 0.0000000000000000e+00;
_dPhic_dq[208] = 0.0000000000000000e+00;
_dPhic_dq[209] = 0.0000000000000000e+00;
_dPhic_dq[210] = 0.0000000000000000e+00;
_dPhic_dq[211] = 0.0000000000000000e+00;
_dPhic_dq[212] = 0.0000000000000000e+00;
_dPhic_dq[213] = 0.0000000000000000e+00;
_dPhic_dq[214] = 0.0000000000000000e+00;
_dPhic_dq[215] = 0.0000000000000000e+00;
_dPhic_dq[216] = 0.0000000000000000e+00;
_dPhic_dq[217] = 0.0000000000000000e+00;
_dPhic_dq[218] = 0.0000000000000000e+00;
_dPhic_dq[219] = 0.0000000000000000e+00;
_dPhic_dq[220] = 0.0000000000000000e+00;
_dPhic_dq[221] = 0.0000000000000000e+00;
_dPhic_dq[222] = 0.0000000000000000e+00;
_dPhic_dq[223] = 0.0000000000000000e+00;
_dPhic_dq[224] = 0.0000000000000000e+00;
_dPhic_dq[225] = 0.0000000000000000e+00;
_dPhic_dq[226] = 0.0000000000000000e+00;
_dPhic_dq[227] = 0.0000000000000000e+00;
_dPhic_dq[228] = 0.0000000000000000e+00;
_dPhic_dq[229] = 0.0000000000000000e+00;
_dPhic_dq[230] = 0.0000000000000000e+00;
_dPhic_dq[231] = 0.0000000000000000e+00;
_dPhic_dq[232] = 0.0000000000000000e+00;
_dPhic_dq[233] = 0.0000000000000000e+00;
_dPhic_dq[234] = 0.0000000000000000e+00;
_dPhic_dq[235] = 0.0000000000000000e+00;
_dPhic_dq[236] = 0.0000000000000000e+00;
_dPhic_dq[237] = 0.0000000000000000e+00;
_dPhic_dq[238] = 0.0000000000000000e+00;
_dPhic_dq[239] = 0.0000000000000000e+00;
_dPhic_dq[240] = 0.0000000000000000e+00;
_dPhic_dq[241] = 0.0000000000000000e+00;
_dPhic_dq[242] = 0.0000000000000000e+00;
_dPhic_dq[243] = 0.0000000000000000e+00;
_dPhic_dq[244] = 0.0000000000000000e+00;
_dPhic_dq[245] = 0.0000000000000000e+00;
_dPhic_dq[246] = 0.0000000000000000e+00;
_dPhic_dq[247] = 0.0000000000000000e+00;
_dPhic_dq[248] = 0.0000000000000000e+00;
_dPhic_dq[249] = 0.0000000000000000e+00;
_dPhic_dq[250] = 0.0000000000000000e+00;
_dPhic_dq[251] = 0.0000000000000000e+00;
_dPhic_dq[252] = 0.0000000000000000e+00;
_dPhic_dq[253] = 0.0000000000000000e+00;
_dPhic_dq[254] = 0.0000000000000000e+00;
_dPhic_dq[255] = 0.0000000000000000e+00;
_dPhic_dq[256] = 0.0000000000000000e+00;
_dPhic_dq[257] = 0.0000000000000000e+00;
_dPhic_dq[258] = 0.0000000000000000e+00;
_dPhic_dq[259] = 0.0000000000000000e+00;
_dPhic_dq[260] = 0.0000000000000000e+00;
_dPhic_dq[261] = 0.0000000000000000e+00;
_dPhic_dq[262] = 0.0000000000000000e+00;
_dPhic_dq[263] = 0.0000000000000000e+00;
_dPhic_dq[264] = 0.0000000000000000e+00;
_dPhic_dq[265] = 0.0000000000000000e+00;
_dPhic_dq[266] = 0.0000000000000000e+00;
_dPhic_dq[267] = 0.0000000000000000e+00;
_dPhic_dq[268] = 0.0000000000000000e+00;
_dPhic_dq[269] = 0.0000000000000000e+00;
_dPhic_dq[270] = 0.0000000000000000e+00;
_dPhic_dq[271] = 0.0000000000000000e+00;
_dPhic_dq[272] = 0.0000000000000000e+00;
_dPhic_dq[273] = 0.0000000000000000e+00;
_dPhic_dq[274] = 0.0000000000000000e+00;
_dPhic_dq[275] = 0.0000000000000000e+00;
_dPhic_dq[276] = 0.0000000000000000e+00;
_dPhic_dq[277] = 0.0000000000000000e+00;
_dPhic_dq[278] = 0.0000000000000000e+00;
_dPhic_dq[279] = 0.0000000000000000e+00;
_dPhic_dq[280] = 0.0000000000000000e+00;
_dPhic_dq[281] = 0.0000000000000000e+00;
_dPhic_dq[282] = 0.0000000000000000e+00;
_dPhic_dq[283] = 0.0000000000000000e+00;
_dPhic_dq[284] = 0.0000000000000000e+00;
_dPhic_dq[285] = 0.0000000000000000e+00;
_dPhic_dq[286] = 0.0000000000000000e+00;
_dPhic_dq[287] = 0.0000000000000000e+00;
_dPhic_dq[288] = 0.0000000000000000e+00;
_dPhic_dq[289] = 0.0000000000000000e+00;
_dPhic_dq[290] = 0.0000000000000000e+00;
_dPhic_dq[291] = 0.0000000000000000e+00;
_dPhic_dq[292] = 0.0000000000000000e+00;
_dPhic_dq[293] = 0.0000000000000000e+00;
_dPhic_dq[294] = 0.0000000000000000e+00;
_dPhic_dq[295] = 0.0000000000000000e+00;
_dPhic_dq[296] = 0.0000000000000000e+00;
_dPhic_dq[297] = 0.0000000000000000e+00;
_dPhic_dq[298] = 0.0000000000000000e+00;
_dPhic_dq[299] = 0.0000000000000000e+00;
_dPhic_dq[300] = 0.0000000000000000e+00;
_dPhic_dq[301] = 0.0000000000000000e+00;
_dPhic_dq[302] = 0.0000000000000000e+00;
_dPhic_dq[303] = 0.0000000000000000e+00;
_dPhic_dq[304] = 0.0000000000000000e+00;
_dPhic_dq[305] = 0.0000000000000000e+00;
_dPhic_dq[306] = 0.0000000000000000e+00;
_dPhic_dq[307] = 0.0000000000000000e+00;
_dPhic_dq[308] = 0.0000000000000000e+00;
_dPhic_dq[309] = 0.0000000000000000e+00;
_dPhic_dq[310] = 0.0000000000000000e+00;
_dPhic_dq[311] = 0.0000000000000000e+00;
_dPhic_dq[312] = 0.0000000000000000e+00;
_dPhic_dq[313] = 0.0000000000000000e+00;
_dPhic_dq[314] = 0.0000000000000000e+00;
_dPhic_dq[315] = 0.0000000000000000e+00;
_dPhic_dq[316] = 0.0000000000000000e+00;
_dPhic_dq[317] = 0.0000000000000000e+00;
_dPhic_dq[318] = 0.0000000000000000e+00;
_dPhic_dq[319] = 0.0000000000000000e+00;
_dPhic_dq[320] = 0.0000000000000000e+00;
_dPhic_dq[321] = 0.0000000000000000e+00;
_dPhic_dq[322] = 0.0000000000000000e+00;
_dPhic_dq[323] = 0.0000000000000000e+00;
_dPhic_dq[324] = 0.0000000000000000e+00;
_dPhic_dq[325] = 0.0000000000000000e+00;
_dPhic_dq[326] = 0.0000000000000000e+00;
_dPhic_dq[327] = 0.0000000000000000e+00;
_dPhic_dq[328] = 0.0000000000000000e+00;
_dPhic_dq[329] = 0.0000000000000000e+00;
_dPhic_dq[330] = 0.0000000000000000e+00;
_dPhic_dq[331] = 0.0000000000000000e+00;
_dPhic_dq[332] = 0.0000000000000000e+00;
_dPhic_dq[333] = 0.0000000000000000e+00;
_dPhic_dq[334] = 0.0000000000000000e+00;
_dPhic_dq[335] = 0.0000000000000000e+00;
_dPhic_dq[336] = 0.0000000000000000e+00;
_dPhic_dq[337] = 0.0000000000000000e+00;
_dPhic_dq[338] = 0.0000000000000000e+00;
_dPhic_dq[339] = 0.0000000000000000e+00;
_dPhic_dq[340] = 0.0000000000000000e+00;
_dPhic_dq[341] = 0.0000000000000000e+00;
_dPhic_dq[342] = 0.0000000000000000e+00;
_dPhic_dq[343] = 0.0000000000000000e+00;
_dPhic_dq[344] = 0.0000000000000000e+00;
_dPhic_dq[345] = 0.0000000000000000e+00;
_dPhic_dq[346] = 0.0000000000000000e+00;
_dPhic_dq[347] = 0.0000000000000000e+00;
_dPhic_dq[348] = 0.0000000000000000e+00;
_dPhic_dq[349] = 0.0000000000000000e+00;
_dPhic_dq[350] = 0.0000000000000000e+00;
_dPhic_dq[351] = 0.0000000000000000e+00;

return _dPhic_dq;
}
