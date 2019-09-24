/*----------Phic.c lib3D_MEC exported-----------*/

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

#include "Phic.h"

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
double atom1814;
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
double atom1847;
double atom1876;
double atom1883;
double atom1916;
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
double atom1276;
double atom1713;
double atom1273;
double atom1231;
double atom1711;
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
double atom1181;
double atom1193;
double atom1180;
double atom1190;
double atom1219;
double atom1237;
double atom1222;
double atom1240;
double atom1255;
double atom1258;
double atom1279;
double atom1282;
double atom1194;
double atom1195;
double atom1225;
double atom1243;
double atom1246;
double atom1228;
double atom1264;
double atom1261;
double atom1285;
double atom1288;
double atom1962;
double atom1968;
double atom1971;
double atom1969;
double atom1972;
double atom1981;
double atom1975;
double atom1977;
double atom1987;
double atom1988;
double atom2061;
double atom2062;
double atom2063;
double atom2065;
double atom2069;
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
double atom2108;
double atom2112;
double atom2105;
double atom2098;
double atom2118;
double atom2123;
double atom2127;
double atom2132;
double atom2134;
double atom2133;
double atom2167;
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
double atom2361;
double atom2367;
double atom2372;
double atom2374;
double atom2379;
double atom2317;
double atom2318;
double atom2319;
double atom2321;
double atom2388;
double atom2389;
double atom2354;
double atom2383;
double atom2390;
double atom2423;
double atom49;
double atom50;
double atom1316;
double atom2212;
double atom2218;
double atom2220;
double atom1319;
double atom2222;
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
double atom1310;
double atom1313;
double atom1325;
double atom1322;
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
double atom2616;
double atom2612;
double atom2623;
double atom2605;
double atom2625;
double atom2630;
double atom2568;
double atom2569;
double atom2570;
double atom2572;
double atom2639;
double atom2634;
double atom2641;
double atom2640;
double atom2674;
double atom2469;
double atom2475;
double atom2478;
double atom2476;
double atom2479;
double atom2482;
double atom2484;
double atom2494;
double atom2495;
double atom2488;
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
double atom2844;
double atom2859;
double atom2861;
double atom2862;
double atom2883;
double atom2863;
double atom2888;
double atom2826;
double atom2827;
double atom2828;
double atom2830;
double atom2892;
double atom2897;
double atom2899;
double atom2898;
double atom2932;
double atom2720;
double atom2726;
double atom1497;
double atom1496;
double atom1019;
double atom1506;
double atom1018;
double atom1527;
double atom1016;
double atom1017;
double atom1509;
double atom497;
double atom1545;
double atom498;
double atom1542;
double atom2729;
double atom1568;
double atom1565;
double atom1524;
double atom2727;
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
double atom1500;
double atom1521;
double atom1503;
double atom1539;
double atom1536;
double atom1562;
double atom1559;
double atom1518;
double atom1512;
double atom1530;
double atom1533;
double atom1515;
double atom1551;
double atom1548;
double atom1571;
double atom1574;
double atom3077;
double atom3078;
double atom3079;
double atom3081;
double atom2988;
double atom2993;
double atom2991;
double atom3003;
double atom3004;
double atom2997;
double atom2978;
double atom2984;
double atom2987;
double atom2985;
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
double atom3095;
double atom3110;
double atom3112;
double atom3113;
double atom3134;
double atom3114;
double atom3139;
double atom3143;
double atom3148;
double atom3149;
double atom3150;
double atom3183;
double atom3229;
double atom3235;
double atom3236;
double atom684;
double atom683;
double atom1607;
double atom1610;
double atom3238;
double atom3240;
double atom3241;
double atom3239;
double atom3246;
double atom3248;
double atom3242;
double atom3245;
double atom3260;
double atom3259;
double atom3249;
double atom3253;
double atom3332;
double atom3333;
double atom3334;
double atom3336;
double atom3341;
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
double atom3378;
double atom3383;
double atom3387;
double atom3369;
double atom3389;
double atom3394;
double atom3403;
double atom3404;
double atom3398;
double atom3405;
double atom3438;
double atom1604;
double atom1601;
double atom1598;
double atom1595;
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
double atom3629;
double atom3634;
double atom3626;
double atom3639;
double atom3644;
double atom3582;
double atom3583;
double atom3584;
double atom3586;
double atom3653;
double atom3654;
double atom3619;
double atom3648;
double atom3655;
double atom3688;
double atom3484;
double atom3490;
double atom3493;
double atom3491;
double atom3494;
double atom3499;
double atom3497;
double atom3509;
double atom3510;
double atom3503;

double * _Phic = NULL;
void Init_Phic ( ) 
{
    _Phic = malloc ( Phic_n_rows * Phic_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Phic_n_rows * Phic_n_cols ; i++ ) {_Phic[i]=0.0;}
  }
}

void Done_Phic ( ) 
{
if (_Phic != NULL) 
free (_Phic ); 
_Phic = NULL; 
}


double * Phic ()
{
if ( _Phic == NULL )
 {
    _Phic = malloc ( Phic_n_rows * Phic_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < Phic_n_rows * Phic_n_cols ; i++ ) {_Phic[i]=0.0;}
  }
 }

atom1810 =  uR_RFR-lR_RFR;
atom1811 = aR_RFR*atom1810;
atom1812 =  atom1811+bR_RFR;
atom1814 =  cR_RFR+atom1812*atom1810;
atom1818 = 1.0/( RFRstas-RFRends);
atom1831 = -RFRas*atom1818;
atom1820 = atom1818*( RFRstas-xR_RFR);
atom1822 =  atom1820*RFRas+RFRbs;
atom1834 = -atom1822*atom1818+atom1831*atom1820;
atom1824 =  atom1820*atom1822+RFRcs;
atom1837 = -atom1818*atom1824+atom1820*atom1834;
atom1826 =  RFRds+atom1820*atom1824;
atom1840 =  atom1820*atom1837-atom1818*atom1826;
atom1828 =  atom1820*atom1826+RFRes;
atom1857 = -atom1834*atom1818;
atom1860 = -atom1818*atom1837;
atom1864 = -atom1818*atom1840;
atom1843 =  atom1820*atom1840-atom1818*atom1828;
atom1867 =  2.0*( atom1860+atom1820*( atom1857-atom1831*atom1820*atom1818))*atom1820+2.0*atom1864;
atom1845 =  (atom1843*atom1843)+1.0;
atom1846 = pow(atom1845,(1.0/2.0));
atom1872 = -1.0/(atom1846*atom1846)*atom1843*atom1867*pow(atom1845,-(1.0/2.0));
atom1881 =  atom1814+atom1810*( atom1812+atom1811);
atom1882 = atom1881*( -5.0000000000000000e-01*atom1872*L_RAIL+atom1843);
atom1847 = 1.0/(atom1846);
atom1876 =  5.0000000000000000e-01*atom1867*L_RAIL*atom1847+5.0000000000000000e-01*atom1872*atom1843*L_RAIL+1.0;
atom1883 = -atom1876*atom1881;
atom1916 = pow( (atom1876*atom1876)+(atom1882*atom1882)+(atom1883*atom1883),-(1.0/2.0));
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
atom1276 =  atom1252*atom30-atom1249*atom31;
atom1713 = cos(thetaW_RFR)*atom1710;
atom1273 =  atom1252*atom31+atom30*atom1249;
atom1231 =  atom1213*atom864-atom1187*atom865;
atom1711 = -atom1710*sin(thetaW_RFR);
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
atom1181 = -atom1175*atom1176;
atom1193 =  atom1177*atom1173+atom1172*atom1181;
atom1180 = atom1176*atom1174;
atom1190 = -atom1181*atom1173+atom1172*atom1177;
atom1219 =  atom1180*atom1210+atom1190*atom1209;
atom1237 =  atom864*atom1219-atom1193*atom865;
atom1222 =  atom1180*atom1209-atom1190*atom1210;
atom1240 =  atom1219*atom865+atom1193*atom864;
atom1255 =  atom862*atom1222+atom863*atom1240;
atom1258 = -atom863*atom1222+atom862*atom1240;
atom1279 =  atom1258*atom31+atom1255*atom30;
atom1282 =  atom1258*atom30-atom1255*atom31;
atom1194 = -atom1173*atom1174;
atom1195 = atom1172*atom1174;
atom1225 =  atom1194*atom1209+atom1175*atom1210;
atom1243 =  atom1225*atom864-atom1195*atom865;
atom1246 =  atom1195*atom864+atom1225*atom865;
atom1228 =  atom1175*atom1209-atom1194*atom1210;
atom1264 =  atom862*atom1246-atom863*atom1228;
atom1261 =  atom862*atom1228+atom863*atom1246;
atom1285 =  atom30*atom1261+atom1264*atom31;
atom1288 = -atom1261*atom31+atom30*atom1264;
atom1962 =  uW_RFL-lW_RFL;
atom1968 =  dW_RFL+( cW_RFL+( aW_RFL*atom1962+bW_RFL)*atom1962)*atom1962;
atom1971 = atom1968*cos(thetaW_RFL);
atom1969 = -sin(thetaW_RFL)*atom1968;
atom1972 = -atom1715+zRWHSF;
atom1981 =  zRBOG+atom1972*atom869-atom1726+atom1725;
atom1975 =  atom1972*atom867+atom1717-atom1718;
atom1977 = -atom1722-atom863*atom1972;
atom1987 =  atom1977*atom1209+atom1975*atom1210;
atom1988 =  atom0-atom1977*atom1210+atom1975*atom1209;
atom2061 =  uR_RFL-lR_RFL;
atom2062 = atom2061*aR_RFL;
atom2063 =  atom2062+bR_RFL;
atom2065 =  atom2063*atom2061+cR_RFL;
atom2069 = 1.0/( RFLstas-RFLends);
atom2071 = atom2069*( RFLstas-xR_RFL);
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
atom2108 = -atom2085*atom2069;
atom2112 = -atom2069*atom2088;
atom2105 = -atom2069*atom2091;
atom2098 = 1.0/(atom2097);
atom2118 =  2.0*atom2105+( 2.0*atom2112+( -2.0000000000000000e+00*atom2082*atom2071*atom2069+2.0*atom2108)*atom2071)*atom2071;
atom2123 = -atom2094*pow(atom2096,-(1.0/2.0))*atom2118/(atom2097*atom2097);
atom2127 =  -5.0000000000000000e-01*atom2094*atom2123*L_RAIL+-5.0000000000000000e-01*atom2098*atom2118*L_RAIL+1.0;
atom2132 =  ( atom2063+atom2062)*atom2061+atom2065;
atom2134 = -atom2127*atom2132;
atom2133 = atom2132*( atom2094+5.0000000000000000e-01*atom2123*L_RAIL);
atom2167 = pow( (atom2127*atom2127)+(atom2133*atom2133)+(atom2134*atom2134),-(1.0/2.0));
atom2326 = 1.0/( RRRstas-RRRends);
atom2327 = atom2326*( RRRstas-xR_RRR);
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
atom2361 = -atom2326*atom2341;
atom2367 = -atom2344*atom2326;
atom2372 = -atom2347*atom2326;
atom2374 =  2.0*atom2372+atom2327*( 2.0*atom2367+atom2327*( -2.0000000000000000e+00*atom2327*atom2338*atom2326+2.0*atom2361));
atom2379 = -atom2350*pow(atom2352,-(1.0/2.0))*atom2374/(atom2353*atom2353);
atom2317 =  uR_RRR-lR_RRR;
atom2318 = atom2317*aR_RRR;
atom2319 =  atom2318+bR_RRR;
atom2321 =  cR_RRR+atom2317*atom2319;
atom2388 =  atom2317*( atom2318+atom2319)+atom2321;
atom2389 = ( -5.0000000000000000e-01*L_RAIL*atom2379+atom2350)*atom2388;
atom2354 = 1.0/(atom2353);
atom2383 =  5.0000000000000000e-01*atom2354*L_RAIL*atom2374+5.0000000000000000e-01*atom2350*L_RAIL*atom2379+1.0;
atom2390 = -atom2383*atom2388;
atom2423 = pow( (atom2390*atom2390)+(atom2389*atom2389)+(atom2383*atom2383),-(1.0/2.0));
atom49 = cos(aRWHSR);
atom50 = sin(aRWHSR);
atom1316 =  atom1255*atom49+atom1258*atom50;
atom2212 =  uW_RRR-lW_RRR;
atom2218 =  atom2212*( cW_RRR+atom2212*( bW_RRR+atom2212*aW_RRR))+dW_RRR;
atom2220 = -sin(thetaW_RRR)*atom2218;
atom1319 = -atom1255*atom50+atom1258*atom49;
atom2222 = atom2218*cos(thetaW_RRR);
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
atom1310 =  atom49*atom1249+atom50*atom1252;
atom1313 = -atom50*atom1249+atom49*atom1252;
atom1325 =  atom49*atom1264-atom50*atom1261;
atom1322 =  atom49*atom1261+atom50*atom1264;
atom2577 = 1.0/( RRLstas-RRLends);
atom2578 = ( RRLstas-xR_RRL)*atom2577;
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
atom2616 = -atom2592*atom2577;
atom2612 = -atom2595*atom2577;
atom2623 = -atom2598*atom2577;
atom2605 = 1.0/(atom2604);
atom2625 =  2.0*atom2623+-2.0*atom2578*( atom2578*( atom2578*atom2589*atom2577-atom2616)-atom2612);
atom2630 = -pow(atom2603,-(1.0/2.0))*atom2601*atom2625/(atom2604*atom2604);
atom2568 =  uR_RRL-lR_RRL;
atom2569 = atom2568*aR_RRL;
atom2570 =  bR_RRL+atom2569;
atom2572 =  atom2570*atom2568+cR_RRL;
atom2639 =  atom2572+( atom2570+atom2569)*atom2568;
atom2634 =  -5.0000000000000000e-01*atom2605*atom2625*L_RAIL+-5.0000000000000000e-01*atom2601*atom2630*L_RAIL+1.0;
atom2641 = -atom2639*atom2634;
atom2640 = ( 5.0000000000000000e-01*atom2630*L_RAIL+atom2601)*atom2639;
atom2674 = pow( (atom2634*atom2634)+(atom2641*atom2641)+(atom2640*atom2640),-(1.0/2.0));
atom2469 =  uW_RRL-lW_RRL;
atom2475 =  dW_RRL+atom2469*( cW_RRL+atom2469*( atom2469*aW_RRL+bW_RRL));
atom2478 = atom2475*cos(thetaW_RRL);
atom2476 = -sin(thetaW_RRL)*atom2475;
atom2479 = -atom2224+zRWHSR;
atom2482 = -atom1717+atom867*atom2479-atom2226;
atom2484 = -atom863*atom2479-atom2230;
atom2494 =  atom1209*atom2484+atom2482*atom1210;
atom2495 = -atom2484*atom1210+atom2482*atom1209+atom0;
atom2488 =  zRBOG-atom2233+atom2479*atom869-atom1725;
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
atom2844 =  FFRes+atom2836*atom2842;
atom2859 =  atom2836*atom2856+atom2834*atom2844;
atom2861 =  (atom2859*atom2859)+1.0;
atom2862 = pow(atom2861,(1.0/2.0));
atom2883 =  2.0*atom2881+2.0*atom2836*( atom2870+atom2836*( atom2871+atom2836*atom2834*atom2847));
atom2863 = 1.0/(atom2862);
atom2888 = -1.0/(atom2862*atom2862)*atom2859*pow(atom2861,-(1.0/2.0))*atom2883;
atom2826 =  uR_FFR-lR_FFR;
atom2827 = atom2826*aR_FFR;
atom2828 =  bR_FFR+atom2827;
atom2830 =  atom2828*atom2826+cR_FFR;
atom2892 =  5.0000000000000000e-01*atom2883*atom2863*L_RAIL+5.0000000000000000e-01*atom2888*atom2859*L_RAIL+1.0;
atom2897 =  atom2830+atom2826*( atom2828+atom2827);
atom2899 = -atom2892*atom2897;
atom2898 = atom2897*( atom2859+-5.0000000000000000e-01*atom2888*L_RAIL);
atom2932 = pow( (atom2899*atom2899)+(atom2892*atom2892)+(atom2898*atom2898),-(1.0/2.0));
atom2720 =  uW_FFR-lW_FFR;
atom2726 =  dW_FFR+( cW_FFR+( bW_FFR+aW_FFR*atom2720)*atom2720)*atom2720;
atom1497 = sin(cFSLD);
atom1496 = cos(cFSLD);
atom1019 = sin(bFBOG);
atom1506 =  atom1190*atom1496+atom1497*atom1180;
atom1018 = cos(bFBOG);
atom1527 =  atom1019*atom1506+atom1193*atom1018;
atom1016 = cos(aFBOG);
atom1017 = sin(aFBOG);
atom1509 =  atom1180*atom1496-atom1497*atom1190;
atom497 = cos(aFWHSF);
atom1545 =  atom1527*atom1016-atom1017*atom1509;
atom498 = sin(aFWHSF);
atom1542 =  atom1016*atom1509+atom1527*atom1017;
atom2729 = atom2726*cos(thetaW_FFR);
atom1568 =  atom497*atom1545-atom498*atom1542;
atom1565 =  atom497*atom1542+atom498*atom1545;
atom1524 = -atom1193*atom1019+atom1018*atom1506;
atom2727 = -sin(thetaW_FFR)*atom2726;
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
atom1500 =  atom1496*atom1184+atom1497*atom1178;
atom1521 =  atom1019*atom1500+atom1018*atom1187;
atom1503 =  atom1496*atom1178-atom1497*atom1184;
atom1539 = -atom1503*atom1017+atom1016*atom1521;
atom1536 =  atom1521*atom1017+atom1503*atom1016;
atom1562 =  atom497*atom1539-atom498*atom1536;
atom1559 =  atom497*atom1536+atom498*atom1539;
atom1518 =  atom1018*atom1500-atom1019*atom1187;
atom1512 =  atom1194*atom1496+atom1497*atom1175;
atom1530 = -atom1019*atom1195+atom1018*atom1512;
atom1533 =  atom1018*atom1195+atom1019*atom1512;
atom1515 =  atom1175*atom1496-atom1497*atom1194;
atom1551 = -atom1515*atom1017+atom1016*atom1533;
atom1548 =  atom1533*atom1017+atom1515*atom1016;
atom1571 =  atom497*atom1548+atom498*atom1551;
atom1574 = -atom498*atom1548+atom497*atom1551;
atom3077 =  uR_FFL-lR_FFL;
atom3078 = aR_FFL*atom3077;
atom3079 =  atom3078+bR_FFL;
atom3081 =  cR_FFL+atom3079*atom3077;
atom2988 = -atom2731+zFWHSF;
atom2993 = -atom1017*atom2988-atom2738;
atom2991 =  atom1021*atom2988+atom2733-atom2734;
atom3003 =  atom1497*atom2991+atom2993*atom1496;
atom3004 =  atom2991*atom1496-atom0-atom1497*atom2993;
atom2997 =  atom2741+zFBOG+atom1023*atom2988-atom2742;
atom2978 =  uW_FFL-lW_FFL;
atom2984 =  dW_FFL+atom2978*( atom2978*( atom2978*aW_FFL+bW_FFL)+cW_FFL);
atom2987 = cos(thetaW_FFL)*atom2984;
atom2985 = -sin(thetaW_FFL)*atom2984;
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
atom3095 =  atom3087*atom3093+FFLes;
atom3110 = -atom3095*atom3086+atom3087*atom3107;
atom3112 =  (atom3110*atom3110)+1.0;
atom3113 = pow(atom3112,(1.0/2.0));
atom3134 =  2.0*atom3087*( ( atom3124-atom3087*atom3098*atom3086)*atom3087+atom3121)+2.0*atom3131;
atom3114 = 1.0/(atom3113);
atom3139 = -atom3134/(atom3113*atom3113)*atom3110*pow(atom3112,-(1.0/2.0));
atom3143 =  -5.0000000000000000e-01*atom3139*atom3110*L_RAIL+-5.0000000000000000e-01*atom3134*atom3114*L_RAIL+1.0;
atom3148 =  atom3081+atom3077*( atom3079+atom3078);
atom3149 = ( atom3110+5.0000000000000000e-01*atom3139*L_RAIL)*atom3148;
atom3150 = -atom3143*atom3148;
atom3183 = pow( (atom3149*atom3149)+(atom3150*atom3150)+(atom3143*atom3143),-(1.0/2.0));
atom3229 =  uW_FRR-lW_FRR;
atom3235 =  atom3229*( cW_FRR+atom3229*( bW_FRR+atom3229*aW_FRR))+dW_FRR;
atom3236 = -sin(thetaW_FRR)*atom3235;
atom684 = sin(aFWHSR);
atom683 = cos(aFWHSR);
atom1607 =  atom683*atom1548+atom684*atom1551;
atom1610 = -atom684*atom1548+atom683*atom1551;
atom3238 = atom3235*cos(thetaW_FRR);
atom3240 = atom684*atom1702;
atom3241 =  zFWHSR+atom3240;
atom3239 = atom683*atom1702;
atom3246 = atom3239*atom1016;
atom3248 = -atom3241*atom1017+atom3246;
atom3242 = atom3239*atom1020;
atom3245 = -atom2733+atom3241*atom1021+atom3242;
atom3260 = -atom1497*atom3248+atom3245*atom1496-atom0;
atom3259 =  atom1497*atom3245+atom3248*atom1496;
atom3249 = atom3239*atom1022;
atom3253 = -atom2741+zFBOG+atom3241*atom1023+atom3249;
atom3332 =  uR_FRR-lR_FRR;
atom3333 = atom3332*aR_FRR;
atom3334 =  atom3333+bR_FRR;
atom3336 =  atom3332*atom3334+cR_FRR;
atom3341 = 1.0/( FRRstas-FRRends);
atom3353 = -atom3341*FRRas;
atom3342 = atom3341*( FRRstas-xR_FRR);
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
atom3378 = -atom3341*atom3356;
atom3383 = -atom3341*atom3359;
atom3387 = -atom3341*atom3362;
atom3369 = 1.0/(atom3368);
atom3389 =  2.0*atom3342*( atom3383-( atom3341*atom3353*atom3342-atom3378)*atom3342)+2.0*atom3387;
atom3394 = -1.0/(atom3368*atom3368)*atom3365*atom3389*pow(atom3367,-(1.0/2.0));
atom3403 =  atom3336+atom3332*( atom3333+atom3334);
atom3404 = ( -5.0000000000000000e-01*L_RAIL*atom3394+atom3365)*atom3403;
atom3398 =  5.0000000000000000e-01*atom3369*atom3389*L_RAIL+5.0000000000000000e-01*atom3365*L_RAIL*atom3394+1.0;
atom3405 = -atom3398*atom3403;
atom3438 = pow( (atom3405*atom3405)+(atom3404*atom3404)+(atom3398*atom3398),-(1.0/2.0));
atom1604 =  atom683*atom1545-atom684*atom1542;
atom1601 =  atom683*atom1542+atom684*atom1545;
atom1598 =  atom683*atom1539-atom684*atom1536;
atom1595 =  atom684*atom1539+atom683*atom1536;
atom3591 = 1.0/( FRLstas-FRLends);
atom3592 = atom3591*( FRLstas-xR_FRL);
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
atom3629 = -atom3606*atom3591;
atom3634 = -atom3609*atom3591;
atom3626 = -atom3612*atom3591;
atom3639 =  2.0*atom3626+2.0*atom3592*( atom3634+atom3592*( atom3629-atom3603*atom3592*atom3591));
atom3644 = -atom3615*pow(atom3617,-(1.0/2.0))*atom3639/(atom3618*atom3618);
atom3582 =  uR_FRL-lR_FRL;
atom3583 = atom3582*aR_FRL;
atom3584 =  atom3583+bR_FRL;
atom3586 =  cR_FRL+atom3584*atom3582;
atom3653 =  atom3582*( atom3584+atom3583)+atom3586;
atom3654 = ( atom3615+5.0000000000000000e-01*atom3644*L_RAIL)*atom3653;
atom3619 = 1.0/(atom3618);
atom3648 =  -5.0000000000000000e-01*atom3619*atom3639*L_RAIL+-5.0000000000000000e-01*atom3615*atom3644*L_RAIL+1.0;
atom3655 = -atom3648*atom3653;
atom3688 = pow( (atom3655*atom3655)+(atom3654*atom3654)+(atom3648*atom3648),-(1.0/2.0));
atom3484 =  uW_FRL-lW_FRL;
atom3490 =  atom3484*( cW_FRL+( atom3484*aW_FRL+bW_FRL)*atom3484)+dW_FRL;
atom3493 = cos(thetaW_FRL)*atom3490;
atom3491 = -sin(thetaW_FRL)*atom3490;
atom3494 =  zFWHSR-atom3240;
atom3499 = -atom3494*atom1017-atom3246;
atom3497 =  atom3494*atom1021-atom2733-atom3242;
atom3509 =  atom1497*atom3497+atom3499*atom1496;
atom3510 =  atom3497*atom1496-atom0-atom1497*atom3499;
atom3503 = -atom2741+zFBOG+atom3494*atom1023-atom3249;

_Phic[0] =  atom1882*( atom1184*atom1737+atom1276*atom1713-xR_RFR+uW_RFR*atom1273+atom1730*atom1187+atom1231*atom1711+-5.0000000000000000e-01*atom1843*L_RAIL*atom1847+xWAG+atom1736*atom1178)*atom1916+atom1876*( atom1243*atom1711+atom1730*atom1195-dR_RFR+uW_RFR*atom1285+atom1288*atom1713-atom1810*atom1814+atom1175*atom1736-irrRFRz+zWAG+atom1194*atom1737)*atom1916-( atom1820*atom1828-atom1180*atom1736-uW_RFR*atom1279-atom1711*atom1237+-5.0000000000000000e-01*L_RAIL*atom1847+uR_RFR-atom1190*atom1737-atom1282*atom1713-yWAG-atom1730*atom1193+RFRfs)*atom1916*atom1883;
_Phic[1] =  atom2167*( atom1243*atom1969+uW_RFL*atom1285-atom2061*atom2065+atom1175*atom1987+atom1288*atom1971+atom1988*atom1194-dR_RFL-irrRFLz+atom1981*atom1195+zWAG)*atom2127+atom2167*atom2133*( 5.0000000000000000e-01*atom2094*atom2098*L_RAIL+atom1276*atom1971+atom1981*atom1187+atom1987*atom1178+atom1988*atom1184+atom1231*atom1969-xR_RFL+xWAG+uW_RFL*atom1273)+atom2167*( atom1969*atom1237-RFLfs+uW_RFL*atom1279-atom2071*atom2079+atom1193*atom1981+atom1988*atom1190+-5.0000000000000000e-01*atom2098*L_RAIL-uR_RFL+atom1282*atom1971+atom1180*atom1987+yWAG)*atom2134;
_Phic[2] = -atom2423*atom2390*( RRRfs+atom2327*atom2335-atom1180*atom2243-atom1316*uW_RRR-atom1190*atom2244-atom1319*atom2222+uR_RRR-atom1193*atom2237-yWAG-atom2220*atom1237+-5.0000000000000000e-01*atom2354*L_RAIL)+atom2423*atom2389*( -5.0000000000000000e-01*atom2350*atom2354*L_RAIL+uW_RRR*atom1310+atom2244*atom1184+atom2222*atom1313+atom2243*atom1178-xR_RRR+atom1231*atom2220+xWAG+atom2237*atom1187)+( atom2222*atom1325+uW_RRR*atom1322+atom1243*atom2220+atom1195*atom2237-dR_RRR-irrRRRz+atom1194*atom2244+zWAG+atom1175*atom2243-atom2317*atom2321)*atom2423*atom2383;
_Phic[3] = -atom2641*( uR_RRL-atom1180*atom2494-atom2476*atom1237+RRLfs-atom1316*uW_RRL+5.0000000000000000e-01*atom2605*L_RAIL+atom2578*atom2586-atom1193*atom2488-atom1190*atom2495-yWAG-atom1319*atom2478)*atom2674+( 5.0000000000000000e-01*atom2605*atom2601*L_RAIL+atom1184*atom2495+uW_RRL*atom1310+atom2488*atom1187+atom2476*atom1231+atom2478*atom1313+xWAG-xR_RRL+atom2494*atom1178)*atom2674*atom2640+( atom1195*atom2488+uW_RRL*atom1322+atom2476*atom1243+atom2478*atom1325+atom1175*atom2494-atom2572*atom2568+zWAG-dR_RRL-irrRRLz+atom1194*atom2495)*atom2634*atom2674;
_Phic[4] = -atom2932*atom2898*( xR_FFR+5.0000000000000000e-01*atom2859*atom2863*L_RAIL-atom2752*atom1178-atom2746*atom1187-atom1559*uW_FFR-atom2753*atom1184-xWAG-atom2727*atom1518-atom2729*atom1562)+atom2899*atom2932*( atom2753*atom1190-uR_FFR+atom1180*atom2752+uW_FFR*atom1565+atom1524*atom2727-FFRfs+atom2729*atom1568+5.0000000000000000e-01*atom2863*L_RAIL+yWAG-atom2836*atom2844+atom2746*atom1193)+atom2932*atom2892*( atom2753*atom1194+atom2746*atom1195+atom1571*uW_FFR+atom2729*atom1574-irrFFRz-atom2830*atom2826+atom1175*atom2752+zWAG+atom1530*atom2727-dR_FFR);
_Phic[5] =  atom3183*( uW_FFL*atom1571+atom3004*atom1194+atom1175*atom3003-dR_FFL-irrFFLz-atom3081*atom3077+atom2987*atom1574+zWAG+atom1530*atom2985+atom2997*atom1195)*atom3143+( atom3004*atom1190+atom2987*atom1568+uW_FFL*atom1565-atom3087*atom3095-uR_FFL+atom1193*atom2997+atom1180*atom3003+yWAG+-5.0000000000000000e-01*atom3114*L_RAIL-FFLfs+atom2985*atom1524)*atom3150*atom3183+atom3183*( 5.0000000000000000e-01*atom3110*atom3114*L_RAIL+atom2987*atom1562+uW_FFL*atom1559+atom2997*atom1187-xR_FFL+atom2985*atom1518+atom3003*atom1178+atom3004*atom1184+xWAG)*atom3149;
_Phic[6] =  atom3404*( atom3260*atom1184+atom3253*atom1187+atom3236*atom1518+uW_FRR*atom1595+atom3259*atom1178-xR_FRR+atom1598*atom3238+-5.0000000000000000e-01*atom3369*atom3365*L_RAIL+xWAG)*atom3438+( atom1193*atom3253+atom3236*atom1524+atom1604*atom3238+5.0000000000000000e-01*atom3369*L_RAIL-atom3342*atom3350+atom1180*atom3259+atom1190*atom3260+uW_FRR*atom1601-uR_FRR+yWAG-FRRfs)*atom3405*atom3438+( atom1175*atom3259+atom1610*atom3238-atom3332*atom3336+atom1194*atom3260-dR_FRR+atom1607*uW_FRR-irrFRRz+zWAG+atom3253*atom1195+atom3236*atom1530)*atom3398*atom3438;
_Phic[7] =  ( uW_FRL*atom1595+atom3509*atom1178+atom3510*atom1184-xR_FRL+atom1187*atom3503+atom1598*atom3493+atom3491*atom1518+5.0000000000000000e-01*atom3615*atom3619*L_RAIL+xWAG)*atom3654*atom3688+atom3688*atom3655*( atom1604*atom3493+atom1193*atom3503+atom1180*atom3509-atom3592*atom3600+atom3510*atom1190-uR_FRL+uW_FRL*atom1601+-5.0000000000000000e-01*atom3619*L_RAIL+atom3491*atom1524+yWAG-FRLfs)-atom3688*atom3648*( atom3582*atom3586-atom1610*atom3493+dR_FRL+irrFRLz-atom1195*atom3503-atom3510*atom1194-atom1607*uW_FRL-atom1530*atom3491-atom1175*atom3509-zWAG);

return _Phic;
}
