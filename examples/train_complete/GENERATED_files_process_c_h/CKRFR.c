/*----------CKRFR.c lib3D_MEC exported-----------*/

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

#include "CKRFR.h"

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
#define E_elastic param[ 222 ]
#define nu_poisson param[ 223 ]
#define G_elastic param[ 224 ]
#define aRFR param[ 225 ]
#define bRFR param[ 226 ]
#define C11RFR param[ 227 ]
#define C22RFR param[ 228 ]
#define C23RFR param[ 229 ]
#define C33RFR param[ 230 ]
#define aRFL param[ 231 ]
#define bRFL param[ 232 ]
#define C11RFL param[ 233 ]
#define C22RFL param[ 234 ]
#define C23RFL param[ 235 ]
#define C33RFL param[ 236 ]
#define aRRR param[ 237 ]
#define bRRR param[ 238 ]
#define C11RRR param[ 239 ]
#define C22RRR param[ 240 ]
#define C23RRR param[ 241 ]
#define C33RRR param[ 242 ]
#define aRRL param[ 243 ]
#define bRRL param[ 244 ]
#define C11RRL param[ 245 ]
#define C22RRL param[ 246 ]
#define C23RRL param[ 247 ]
#define C33RRL param[ 248 ]
#define aFFR param[ 249 ]
#define bFFR param[ 250 ]
#define C11FFR param[ 251 ]
#define C22FFR param[ 252 ]
#define C23FFR param[ 253 ]
#define C33FFR param[ 254 ]
#define aFFL param[ 255 ]
#define bFFL param[ 256 ]
#define C11FFL param[ 257 ]
#define C22FFL param[ 258 ]
#define C23FFL param[ 259 ]
#define C33FFL param[ 260 ]
#define aFRR param[ 261 ]
#define bFRR param[ 262 ]
#define C11FRR param[ 263 ]
#define C22FRR param[ 264 ]
#define C23FRR param[ 265 ]
#define C33FRR param[ 266 ]
#define aFRL param[ 267 ]
#define bFRL param[ 268 ]
#define C11FRL param[ 269 ]
#define C22FRL param[ 270 ]
#define C23FRL param[ 271 ]
#define C33FRL param[ 272 ]
#define epsiRFR param[ 273 ]
#define epsiRFL param[ 274 ]
#define epsiRRR param[ 275 ]
#define epsiRRL param[ 276 ]
#define epsiFFR param[ 277 ]
#define epsiFFL param[ 278 ]
#define epsiFRR param[ 279 ]
#define epsiFRL param[ 280 ]
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
double atom1876;
double atom1878;
double atom1914;
double atom1922;
double atom1923;
double atom61001;
double atom1924;
double atom863;
double atom21747;
double atom1210;
double atom864;
double atom862;
double atom865;
double atom867;
double atom1717;
double atom21746;
double atom1209;
double atom0;
double atom21753;
double atom1173;
double atom1174;
double atom21757;
double atom1194;
double atom1175;
double atom21756;
double atom1172;
double atom869;
double atom1725;
double atom21749;
double atom1195;
double atom21750;
double atom21772;
double atom1177;
double atom1702;
double atom31;
double atom1716;
double atom30;
double atom1714;
double atom1721;
double atom1724;
double atom1736;
double atom1737;
double atom868;
double atom1730;
double atom1225;
double atom1704;
double atom1710;
double atom1243;
double atom1711;
double atom1246;
double atom1227;
double atom1228;
double atom1264;
double atom1261;
double atom1285;
double atom1288;
double atom1713;
double atom21778;
double atom51735;
double atom1176;
double atom51866;
double atom60809;
double atom60814;
double atom1179;
double atom1185;
double atom1187;
double atom1184;
double atom1178;
double atom21762;
double atom1213;
double atom1234;
double atom1216;
double atom1252;
double atom1249;
double atom1276;
double atom1273;
double atom1231;
double atom21776;
double atom51875;
double atom60818;
double atom1180;
double atom1181;
double atom1190;
double atom1191;
double atom1193;
double atom21767;
double atom1219;
double atom1237;
double atom1222;
double atom1240;
double atom1255;
double atom1258;
double atom1279;
double atom1282;
double atom21777;
double atom51759;
double atom60825;
double atom60826;
double atom60830;
double atom3814;
double atom60839;
double atom25002;
double atom60833;
double atom24853;
double atom60836;
double atom60845;
double atom7663;
double atom51823;
double atom51819;
double atom51825;
double atom51829;
double atom51832;
double atom22967;
double atom24052;
double atom60847;
double atom60853;
double atom22964;
double atom60856;
double atom60865;
double atom60849;
double atom51834;
double atom60868;
double atom60858;
double atom51898;
double atom60860;
double atom60861;
double atom60871;
double atom22863;
double atom22942;
double atom22861;
double atom60874;
double atom60884;
double atom24911;
double atom24913;
double atom25030;
double atom60877;
double atom24923;
double atom60880;
double atom60890;
double atom4138;
double atom4139;
double atom4143;
double atom4152;
double atom7672;
double atom60893;
double atom24189;
double atom60903;
double atom60894;
double atom24177;
double atom60901;
double atom60905;
double atom60897;
double atom60907;
double atom60911;
double atom60915;
double atom60923;
double atom60917;
double atom60919;
double atom60928;
double atom61002;
double atom1810;
double atom1811;
double atom1812;
double atom1881;
double atom1927;
double atom61003;
double atom1928;
double atom51916;
double atom60935;
double atom61005;
double atom1882;
double atom1883;
double atom1916;
double atom1918;
double atom1917;
double atom61006;
double atom60976;
double atom1919;
double atom60981;
double atom51925;
double atom60942;
double atom60943;
double atom24849;
double atom60950;
double atom60985;
double atom7712;
double atom60990;
double atom51947;
double atom60953;
double atom60957;
double atom61114;
double atom60995;
double atom24917;
double atom60964;
double atom7721;
double atom60967;
double atom60973;
double atom61000;
double atom61007;
double atom61008;
double atom61149;
double atom22860;
double atom22966;
double atom22970;
double atom23999;
double atom23996;
double atom24168;
double atom24180;
double atom59009;
double atom59017;
double atom59021;
double atom59003;
double atom61009;
double atom60744;
double atom21700;
double atom60737;
double atom60747;
double atom60732;
double atom61012;
double atom61015;
double atom61014;
double atom61017;
double atom61191;
double atom22971;
double atom24001;
double atom24003;
double atom24171;
double atom24183;
double atom59040;
double atom59046;
double atom59054;
double atom59058;
double atom61018;
double atom60753;
double atom60758;
double atom61021;
double atom61024;
double atom61241;
double atom59085;
double atom59079;
double atom59089;
double atom59075;
double atom61025;
double atom60769;
double atom60764;
double atom61028;
double atom61031;
double atom61291;
double atom24174;
double atom24186;
double atom59109;
double atom59115;
double atom59119;
double atom59105;
double atom61032;
double atom60780;
double atom60775;
double atom61035;
double atom61038;
double atom61341;
double atom61039;
double atom61040;
double atom61041;
double atom61391;
double atom59136;
double atom59140;
double atom59141;
double atom61042;
double atom59144;
double atom60786;
double atom61044;
double atom61045;
double atom61047;
double atom61048;
double atom61441;
double atom59160;
double atom59156;
double atom59166;
double atom59170;
double atom61049;
double atom60792;
double atom60795;
double atom61052;
double atom61055;
double atom61491;
double atom61056;
double atom61057;
double atom61058;
double atom61541;
double atom61059;
double atom60801;
double atom61061;
double atom61063;
double atom61591;
double atom59195;
double atom61064;
double atom60807;
double atom61067;
double atom61070;
double atom61641;

double * _CKRFR = NULL;
void Init_CKRFR ( ) 
{
    _CKRFR = malloc ( CKRFR_n_rows * CKRFR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKRFR_n_rows * CKRFR_n_cols ; i++ ) {_CKRFR[i]=0.0;}
  }
}

void Done_CKRFR ( ) 
{
if (_CKRFR != NULL) 
free (_CKRFR ); 
_CKRFR = NULL; 
}


double * CKRFR ()
{
if ( _CKRFR == NULL )
 {
    _CKRFR = malloc ( CKRFR_n_rows * CKRFR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKRFR_n_rows * CKRFR_n_cols ; i++ ) {_CKRFR[i]=0.0;}
  }
 }

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
atom1876 =  5.0000000000000000e-01*1.0/atom1846*atom1867*L_RAIL+5.0000000000000000e-01*atom1872*atom1843*L_RAIL+1.0;
atom1878 =  -5.0000000000000000e-01*atom1872*L_RAIL+atom1843;
atom1914 = (atom1876*atom1876);
atom1922 = pow( atom1914+(atom1878*atom1878),-(1.0/2.0));
atom1923 = atom1922*atom1876;
atom61001 = -C11RFR*G_elastic*epsiRFR*aRFR*atom1923*bRFR;
atom1924 = atom1922*atom1878;
atom863 = sin(aRBOG);
atom21747 = -atom863*zRWHSF;
atom1210 = sin(cRSLD);
atom864 = cos(bRBOG);
atom862 = cos(aRBOG);
atom865 = sin(bRBOG);
atom867 = atom862*atom865;
atom1717 = L_OBOG_OWHS*atom864;
atom21746 =  atom1717+atom867*zRWHSF;
atom1209 = cos(cRSLD);
atom0 = -(1.0/2.0)*L_WAG;
atom21753 =  atom21746*atom1209-atom21747*atom1210;
atom1173 = sin(bWAG);
atom1174 = cos(aWAG);
atom21757 =  atom0+atom21753;
atom1194 = -atom1173*atom1174;
atom1175 = sin(aWAG);
atom21756 =  atom21746*atom1210+atom1209*atom21747;
atom1172 = cos(bWAG);
atom869 = atom862*atom864;
atom1725 = -L_OBOG_OWHS*atom865;
atom21749 =  atom1725+zRWHSF*atom869;
atom1195 = atom1172*atom1174;
atom21750 =  atom21749+zRBOG;
atom21772 =  atom1195*atom21750+atom1175*atom21756+atom21757*atom1194;
atom1177 = sin(cWAG);
atom1702 = -5.0000000000000000e-01*L_WHS;
atom31 = sin(aRWHSF);
atom1716 =  atom1702*atom31+zRWHSF;
atom30 = cos(aRWHSF);
atom1714 = atom30*atom1702;
atom1721 =  atom1717+atom863*atom1714*atom865+atom867*atom1716;
atom1724 =  atom862*atom1714-atom863*atom1716;
atom1736 =  atom1721*atom1210+atom1724*atom1209;
atom1737 =  atom0-atom1724*atom1210+atom1721*atom1209;
atom868 = atom863*atom864;
atom1730 =  atom868*atom1714+atom1716*atom869+zRBOG+atom1725;
atom1225 =  atom1194*atom1209+atom1175*atom1210;
atom1704 =  uW_RFR-lW_RFR;
atom1710 =  ( ( bW_RFR+aW_RFR*atom1704)*atom1704+cW_RFR)*atom1704+dW_RFR;
atom1243 =  atom1225*atom864-atom1195*atom865;
atom1711 = -atom1710*sin(thetaW_RFR);
atom1246 =  atom1195*atom864+atom1225*atom865;
atom1227 = atom1175*atom1209;
atom1228 =  atom1227-atom1194*atom1210;
atom1264 =  atom862*atom1246-atom863*atom1228;
atom1261 =  atom862*atom1228+atom863*atom1246;
atom1285 =  atom30*atom1261+atom1264*atom31;
atom1288 = -atom1261*atom31+atom30*atom1264;
atom1713 = cos(thetaW_RFR)*atom1710;
atom21778 = -atom21772+atom1243*atom1711+atom1730*atom1195+uW_RFR*atom1285+atom1288*atom1713+atom1175*atom1736+atom1194*atom1737;
atom51735 = atom21772*atom1177;
atom1176 = cos(cWAG);
atom51866 = -atom21772*atom1176;
atom60809 =  atom51866-atom1176*atom21778;
atom60814 =  ( atom51735+atom1177*atom21778)*atom1923+atom1924*atom60809;
atom1179 = atom1175*atom1177;
atom1185 = atom1176*atom1173;
atom1187 =  atom1172*atom1179+atom1185;
atom1184 =  atom1172*atom1176-atom1173*atom1179;
atom1178 = -atom1177*atom1174;
atom21762 =  atom1187*atom21750+atom21757*atom1184+atom21756*atom1178;
atom1213 =  atom1209*atom1184+atom1178*atom1210;
atom1234 =  atom1213*atom865+atom864*atom1187;
atom1216 = -atom1184*atom1210+atom1209*atom1178;
atom1252 =  atom862*atom1234-atom863*atom1216;
atom1249 =  atom863*atom1234+atom862*atom1216;
atom1276 =  atom1252*atom30-atom1249*atom31;
atom1273 =  atom1252*atom31+atom30*atom1249;
atom1231 =  atom1213*atom864-atom1187*atom865;
atom21776 =  atom1184*atom1737+atom1276*atom1713-atom21762+uW_RFR*atom1273+atom1730*atom1187+atom1231*atom1711+atom1736*atom1178;
atom51875 = -atom21772*atom1178+atom1175*atom21762;
atom60818 =  atom1175*atom21776-atom21778*atom1178+atom51875;
atom1180 = atom1176*atom1174;
atom1181 = -atom1175*atom1176;
atom1190 = -atom1181*atom1173+atom1172*atom1177;
atom1191 = atom1177*atom1173;
atom1193 =  atom1191+atom1172*atom1181;
atom21767 =  atom21757*atom1190+atom1193*atom21750+atom1180*atom21756;
atom1219 =  atom1180*atom1210+atom1190*atom1209;
atom1237 =  atom864*atom1219-atom1193*atom865;
atom1222 =  atom1180*atom1209-atom1190*atom1210;
atom1240 =  atom1219*atom865+atom1193*atom864;
atom1255 =  atom862*atom1222+atom863*atom1240;
atom1258 = -atom863*atom1222+atom862*atom1240;
atom1279 =  atom1258*atom31+atom1255*atom30;
atom1282 =  atom1258*atom30-atom1255*atom31;
atom21777 =  atom1180*atom1736+uW_RFR*atom1279+atom1711*atom1237-atom21767+atom1190*atom1737+atom1282*atom1713+atom1730*atom1193;
atom51759 = -atom1175*atom21767+atom21772*atom1180;
atom60825 =  ( atom1180*atom21778+atom51759-atom1175*atom21777)*atom1923+atom1924*atom60818;
atom60826 =  atom21776+atom21762;
atom60830 =  atom60826*atom1924-( atom21767+atom21777)*atom1923;
atom3814 = -atom1175*atom1172;
atom60839 =  atom1191+atom1176*atom3814;
atom25002 = -atom21756*atom1184+atom1178*atom21753;
atom60833 = -atom3814*atom1177+atom1185;
atom24853 =  atom1180*atom21753-atom21756*atom1190;
atom60836 =  atom24853-atom21778*atom60833+atom21776*atom1195;
atom60845 = -( atom1195*atom21777-atom25002-atom60839*atom21778)*atom1923+atom1924*atom60836;
atom7663 =  atom1193*atom1924+atom1187*atom1923;
atom51823 = -atom21749*atom864-atom21746*atom865;
atom51819 = -atom21747*atom865;
atom51825 = -atom1209*atom51819-atom51823*atom1210;
atom51829 =  atom51823*atom1209-atom1210*atom51819;
atom51832 = atom864*atom21747;
atom22967 = atom864*atom1210;
atom24052 = atom864*atom1209;
atom60847 = -atom1172*atom865-atom1173*atom24052;
atom60853 = -atom1175*atom60847+atom22967*atom1174;
atom22964 = -atom1173*atom865;
atom60856 =  atom1172*atom24052+atom22964;
atom60865 =  atom1176*atom60853+atom60856*atom1177;
atom60849 =  atom60847*atom1174+atom1175*atom22967;
atom51834 =  atom51832*atom1187+atom51829*atom1178+atom51825*atom1184;
atom60868 = -atom21777*atom60849+atom60865*atom21778;
atom60858 =  atom1176*atom60856-atom60853*atom1177;
atom51898 =  atom1193*atom51832+atom1180*atom51829+atom51825*atom1190;
atom60860 = -atom60858*atom21778+atom21776*atom60849;
atom60861 =  atom51898+atom60860;
atom60871 =  atom60861*atom1924+( atom51834+atom60868)*atom1923;
atom22863 = atom1173*atom1210;
atom22942 =  atom22863*atom1174+atom1227;
atom22861 = -atom1172*atom1210;
atom60874 =  atom1209*atom1174-atom1175*atom22863;
atom60884 =  atom22861*atom1177+atom60874*atom1176;
atom24911 = atom21749*atom1209;
atom24913 = atom21749*atom1210;
atom25030 =  atom24913*atom1178-atom21746*atom1187+atom24911*atom1184;
atom60877 =  atom22861*atom1176-atom60874*atom1177;
atom24923 =  atom1180*atom24913+atom24911*atom1190-atom1193*atom21746;
atom60880 =  atom24923-atom60877*atom21778+atom22942*atom21776;
atom60890 =  atom1924*atom60880+atom1923*( atom60884*atom21778-atom22942*atom21777+atom25030);
atom4138 = -atom863*atom1209;
atom4139 =  atom4138+atom867*atom1210;
atom4143 =  atom867*atom1209+atom863*atom1210;
atom4152 =  atom1193*atom869+atom1180*atom4139+atom4143*atom1190;
atom7672 =  ( atom4143*atom1184+atom4139*atom1178+atom1187*atom869)*atom1923+atom4152*atom1924;
atom60893 =  atom60868*atom1923+atom1924*atom60860;
atom24189 = -atom863*atom30-atom862*atom31;
atom60903 = -atom864*atom24189;
atom60894 = -atom24189*atom865;
atom24177 =  atom862*atom30-atom863*atom31;
atom60901 = -atom24177*atom1210+atom60894*atom1209;
atom60905 =  atom1172*atom60903-atom60901*atom1173;
atom60897 =  atom24177*atom1209+atom60894*atom1210;
atom60907 =  atom60897*atom1175+atom60905*atom1174;
atom60911 = -atom1175*atom60905+atom60897*atom1174;
atom60915 =  atom1172*atom60901+atom60903*atom1173;
atom60923 =  atom1177*atom60915+atom60911*atom1176;
atom60917 =  atom1176*atom60915-atom60911*atom1177;
atom60919 = -atom21778*atom60917+atom21776*atom60907;
atom60928 = -atom1923*( atom21777*atom60907-atom60923*atom21778)+atom60919*atom1924;
atom61002 = -C11RFR*atom1924*G_elastic*epsiRFR*aRFR*bRFR;
atom1810 =  uR_RFR-lR_RFR;
atom1811 = aR_RFR*atom1810;
atom1812 =  atom1811+bR_RFR;
atom1881 =  cR_RFR+atom1812*atom1810+atom1810*( atom1812+atom1811);
atom1927 = pow( (atom1881*atom1881)+1.0,-(1.0/2.0));
atom61003 = -G_elastic*epsiRFR*C22RFR*aRFR*atom1927*bRFR;
atom1928 = atom1881*atom1927;
atom51916 =  atom1176*atom21767-atom21762*atom1177;
atom60935 =  atom1928*( atom1176*atom21777-atom21776*atom1177+atom51916)+atom60809*atom1927;
atom61005 = pow(aRFR*bRFR,(1.0/2.0));
atom1882 = atom1881*atom1878;
atom1883 = -atom1876*atom1881;
atom1916 = pow( atom1914+(atom1882*atom1882)+(atom1883*atom1883),-(1.0/2.0));
atom1918 = atom1916*atom1883;
atom1917 = atom1882*atom1916;
atom61006 = -G_elastic*epsiRFR*aRFR*atom1927*atom61005*C23RFR*bRFR;
atom60976 =  atom1917*atom1176+atom1177*atom1918;
atom1919 = atom1876*atom1916;
atom60981 =  atom1917*atom1178+atom1180*atom1918+atom1175*atom1919;
atom51925 =  atom21767*atom1178-atom1180*atom21762;
atom60942 =  atom1928*( atom21777*atom1178-atom1180*atom21776+atom51925)+atom60818*atom1927;
atom60943 = atom60826*atom1927;
atom24849 =  atom1175*atom21753-atom21756*atom1194;
atom60950 =  atom1928*( atom21777*atom60833-atom21776*atom60839+atom24849)+atom1927*atom60836;
atom60985 =  atom1919*atom1195+atom1917*atom60833+atom60839*atom1918;
atom7712 =  atom1928*atom1195+atom1193*atom1927;
atom60990 =  atom1919*atom60849+atom1917*atom60858+atom60865*atom1918;
atom51947 =  atom1195*atom51832+atom51829*atom1175+atom51825*atom1194;
atom60953 = -atom21776*atom60865+atom60858*atom21777;
atom60957 =  ( atom51947+atom60953)*atom1928+atom60861*atom1927;
atom61114 = atom60990*atom61006;
atom60995 =  atom22942*atom1919+atom1917*atom60877+atom60884*atom1918;
atom24917 =  atom1194*atom24911-atom21746*atom1195+atom1175*atom24913;
atom60964 =  atom60880*atom1927-atom1928*( atom60884*atom21776-atom60877*atom21777-atom24917);
atom7721 =  ( atom4139*atom1175+atom1195*atom869+atom4143*atom1194)*atom1928+atom4152*atom1927;
atom60967 =  atom1927*atom60860+atom1928*atom60953;
atom60973 =  atom60919*atom1927-atom1928*( atom60923*atom21776-atom21777*atom60917);
atom61000 =  atom1917*atom60917+atom1919*atom60907+atom60923*atom1918;
atom61007 = -atom1928*G_elastic*epsiRFR*C22RFR*aRFR*bRFR;
atom61008 = -atom1928*G_elastic*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61149 = atom61008*atom60990;
atom22860 = atom1172*atom1209;
atom22966 =  atom864*atom22860+atom22964;
atom22970 =  atom864*atom1173+atom22860*atom865;
atom23999 =  atom862*atom22970-atom22861*atom863;
atom23996 =  atom862*atom22861+atom22970*atom863;
atom24168 =  atom23996*atom30+atom23999*atom31;
atom24180 =  atom23999*atom30-atom23996*atom31;
atom59009 =  atom22966*atom1243+atom24168*atom1285+atom24180*atom1288;
atom59017 =  atom24168*atom1273+atom1231*atom22966+atom24180*atom1276;
atom59021 =  atom51866-atom59017*atom21778+atom21776*atom59009;
atom59003 =  atom24180*atom1282+atom22966*atom1237+atom24168*atom1279;
atom61009 = -( ( atom51735-atom21777*atom59009+atom21778*atom59003)*atom1923+atom1924*atom59021)*C11RFR*G_elastic*epsiRFR*aRFR*bRFR;
atom60744 =  atom1918*atom1237+atom1243*atom1919+atom1231*atom1917;
atom21700 =  atom1918*atom1279+atom1919*atom1285+atom1917*atom1273;
atom60737 =  atom1918*atom1282+atom1919*atom1288+atom1917*atom1276;
atom60747 =  atom24168*atom21700+atom60737*atom24180+atom22966*atom60744;
atom60732 =  ( atom51916+atom59017*atom21777-atom21776*atom59003)*atom1928+atom59021*atom1927;
atom61012 = -G_elastic*atom60732*epsiRFR*C22RFR*aRFR*bRFR+G_elastic*epsiRFR*aRFR*atom61005*atom60747*C23RFR*bRFR;
atom61015 = (bRFR*bRFR);
atom61014 = (aRFR*aRFR);
atom61017 = -G_elastic*atom60732*epsiRFR*aRFR*atom61005*C23RFR*bRFR-atom61015*C33RFR*G_elastic*atom61014*epsiRFR*atom60747;
atom61191 = atom60990*atom61017;
atom22971 = atom865*atom1210;
atom24001 =  atom862*atom1209+atom863*atom22971;
atom24003 =  atom4138+atom862*atom22971;
atom24171 =  atom24001*atom30+atom24003*atom31;
atom24183 =  atom24003*atom30-atom24001*atom31;
atom59040 =  atom22967*atom1237+atom24171*atom1279+atom24183*atom1282;
atom59046 =  atom1243*atom22967+atom24171*atom1285+atom24183*atom1288;
atom59054 =  atom1231*atom22967+atom1276*atom24183+atom24171*atom1273;
atom59058 =  atom59046*atom21776-atom59054*atom21778+atom51875;
atom61018 = -( atom1924*atom59058-( atom59046*atom21777-atom51759-atom59040*atom21778)*atom1923)*C11RFR*G_elastic*epsiRFR*aRFR*bRFR;
atom60753 = -atom1928*( atom59040*atom21776-atom59054*atom21777-atom51925)+atom59058*atom1927;
atom60758 =  atom60737*atom24183+atom24171*atom21700+atom60744*atom22967;
atom61021 = -atom60753*G_elastic*epsiRFR*C22RFR*aRFR*bRFR+atom60758*G_elastic*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61024 = -atom61015*atom60758*C33RFR*G_elastic*atom61014*epsiRFR-atom60753*G_elastic*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61241 = atom60990*atom61024;
atom59085 =  atom1273*atom1285+atom1231*atom1243+atom1276*atom1288;
atom59079 =  (atom1288*atom1288)+(atom1285*atom1285)+(atom1243*atom1243);
atom59089 = -atom59085*atom21778+atom21762+atom59079*atom21776;
atom59075 =  atom1285*atom1279+atom1243*atom1237+atom1288*atom1282;
atom61025 = -( ( atom21778*atom59075-atom21767-atom59079*atom21777)*atom1923+atom59089*atom1924)*C11RFR*G_elastic*epsiRFR*aRFR*bRFR;
atom60769 =  atom21700*atom1285+atom60737*atom1288+atom1243*atom60744;
atom60764 =  atom1928*( atom59085*atom21777-atom21776*atom59075)+atom59089*atom1927;
atom61028 = -atom60764*G_elastic*epsiRFR*C22RFR*aRFR*bRFR+atom60769*G_elastic*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61031 = -atom60764*G_elastic*epsiRFR*aRFR*atom61005*C23RFR*bRFR-atom61015*atom60769*C33RFR*G_elastic*atom61014*epsiRFR;
atom61291 = atom60990*atom61031;
atom24174 =  atom868*atom30+atom869*atom31;
atom24186 =  atom30*atom869-atom868*atom31;
atom59109 = -atom1243*atom865+atom24186*atom1288+atom1285*atom24174;
atom59115 =  atom1276*atom24186-atom1231*atom865+atom1273*atom24174;
atom59119 = -atom59115*atom21778+atom24853+atom21776*atom59109;
atom59105 = -atom865*atom1237+atom24174*atom1279+atom24186*atom1282;
atom61032 = C11RFR*G_elastic*epsiRFR*( ( atom21777*atom59109-atom25002-atom59105*atom21778)*atom1923-atom1924*atom59119)*aRFR*bRFR;
atom60780 =  atom60737*atom24186+atom21700*atom24174-atom60744*atom865;
atom60775 = -atom1928*( atom21776*atom59105-atom59115*atom21777-atom24849)+atom59119*atom1927;
atom61035 =  G_elastic*atom60780*epsiRFR*aRFR*atom61005*C23RFR*bRFR-atom60775*G_elastic*epsiRFR*C22RFR*aRFR*bRFR;
atom61038 = -atom61015*C33RFR*G_elastic*atom60780*atom61014*epsiRFR-atom60775*G_elastic*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61341 = atom60990*atom61038;
atom61039 = -C11RFR*G_elastic*epsiRFR*atom7663*aRFR*bRFR;
atom61040 = -G_elastic*atom7712*epsiRFR*C22RFR*aRFR*bRFR;
atom61041 = -G_elastic*atom7712*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61391 = atom60990*atom61041;
atom59136 =  atom21778*atom1237-atom1243*atom21777;
atom59140 = -atom1231*atom21778+atom21776*atom1243;
atom59141 =  atom59140+atom51898;
atom61042 = -( atom1924*atom59141+( atom51834+atom59136)*atom1923)*C11RFR*G_elastic*epsiRFR*aRFR*bRFR;
atom59144 =  atom1231*atom21777-atom21776*atom1237;
atom60786 =  atom1928*( atom51947+atom59144)+atom1927*atom59141;
atom61044 = G_elastic*atom60744*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61045 = -atom60786*G_elastic*epsiRFR*C22RFR*aRFR*bRFR+atom61044;
atom61047 = -atom61015*C33RFR*G_elastic*atom60744*atom61014*epsiRFR;
atom61048 =  atom61047-atom60786*G_elastic*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61441 = atom60990*atom61048;
atom59160 =  atom24189*atom1288+atom24177*atom1285;
atom59156 =  atom24177*atom1279+atom24189*atom1282;
atom59166 =  atom1276*atom24189+atom24177*atom1273;
atom59170 = -atom21778*atom59166+atom24923+atom21776*atom59160;
atom61049 = C11RFR*G_elastic*( ( atom59160*atom21777-atom59156*atom21778-atom25030)*atom1923-atom1924*atom59170)*epsiRFR*aRFR*bRFR;
atom60792 =  ( atom21777*atom59166-atom59156*atom21776+atom24917)*atom1928+atom59170*atom1927;
atom60795 =  atom60737*atom24189+atom21700*atom24177;
atom61052 = -G_elastic*epsiRFR*C22RFR*aRFR*atom60792*bRFR+G_elastic*atom60795*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61055 = -atom61015*C33RFR*G_elastic*atom60795*atom61014*epsiRFR-G_elastic*epsiRFR*aRFR*atom60792*atom61005*C23RFR*bRFR;
atom61491 = atom60990*atom61055;
atom61056 = -C11RFR*G_elastic*epsiRFR*atom7672*aRFR*bRFR;
atom61057 = -G_elastic*epsiRFR*atom7721*C22RFR*aRFR*bRFR;
atom61058 = -G_elastic*epsiRFR*atom7721*aRFR*atom61005*C23RFR*bRFR;
atom61541 = atom61058*atom60990;
atom61059 = -( atom1924*atom59140+atom59136*atom1923)*C11RFR*G_elastic*epsiRFR*aRFR*bRFR;
atom60801 =  atom59140*atom1927+atom1928*atom59144;
atom61061 = -G_elastic*atom60801*epsiRFR*C22RFR*aRFR*bRFR+atom61044;
atom61063 =  atom61047-G_elastic*atom60801*epsiRFR*aRFR*atom61005*C23RFR*bRFR;
atom61591 = atom60990*atom61063;
atom59195 = -atom1273*atom21778+atom21776*atom1285;
atom61064 = C11RFR*G_elastic*epsiRFR*aRFR*( atom1923*( atom21777*atom1285-atom21778*atom1279)-atom1924*atom59195)*bRFR;
atom60807 = -( atom21776*atom1279-atom21777*atom1273)*atom1928+atom59195*atom1927;
atom61067 =  G_elastic*epsiRFR*atom21700*aRFR*atom61005*C23RFR*bRFR-G_elastic*epsiRFR*C22RFR*aRFR*atom60807*bRFR;
atom61070 = -atom61015*C33RFR*G_elastic*atom61014*epsiRFR*atom21700-G_elastic*epsiRFR*aRFR*atom61005*C23RFR*atom60807*bRFR;
atom61641 = atom60990*atom61070;

_CKRFR[0] = atom61001*atom1923;
_CKRFR[1] = atom61002*atom1923;
_CKRFR[2] = 0.0;
_CKRFR[3] = atom61009*atom1923;
_CKRFR[4] = atom61018*atom1923;
_CKRFR[5] = atom61025*atom1923;
_CKRFR[6] = atom61032*atom1923;
_CKRFR[7] = 0.0;
_CKRFR[8] = atom61039*atom1923;
_CKRFR[9] = atom61042*atom1923;
_CKRFR[10] = atom61049*atom1923;
_CKRFR[11] = 0.0;
_CKRFR[12] = 0.0;
_CKRFR[13] = 0.0;
_CKRFR[14] = atom61056*atom1923;
_CKRFR[15] = atom1923*atom61059;
_CKRFR[16] = atom61064*atom1923;
_CKRFR[17] = 0.0;
_CKRFR[18] = 0.0;
_CKRFR[19] = 0.0;
_CKRFR[20] = 0.0;
_CKRFR[21] = 0.0;
_CKRFR[22] = 0.0;
_CKRFR[23] = 0.0;
_CKRFR[24] = 0.0;
_CKRFR[25] = 0.0;
_CKRFR[26] = 0.0;
_CKRFR[27] = 0.0;
_CKRFR[28] = 0.0;
_CKRFR[29] = 0.0;
_CKRFR[30] = 0.0;
_CKRFR[31] = 0.0;
_CKRFR[32] = 0.0;
_CKRFR[33] = 0.0;
_CKRFR[34] = 0.0;
_CKRFR[35] = 0.0;
_CKRFR[36] = 0.0;
_CKRFR[37] = 0.0;
_CKRFR[38] = 0.0;
_CKRFR[39] = 0.0;
_CKRFR[40] = 0.0;
_CKRFR[41] = 0.0;
_CKRFR[42] = 0.0;
_CKRFR[43] = 0.0;
_CKRFR[44] = atom61001*atom1924;
_CKRFR[45] =  atom61003*atom1927+atom1924*atom61002;
_CKRFR[46] = atom1927*atom61007;
_CKRFR[47] =  atom1924*atom61009+atom61012*atom1927;
_CKRFR[48] =  atom1924*atom61018+atom61021*atom1927;
_CKRFR[49] =  atom61028*atom1927+atom1924*atom61025;
_CKRFR[50] =  atom61035*atom1927+atom1924*atom61032;
_CKRFR[51] = 0.0;
_CKRFR[52] =  atom61040*atom1927+atom61039*atom1924;
_CKRFR[53] =  atom61045*atom1927+atom1924*atom61042;
_CKRFR[54] =  atom61052*atom1927+atom61049*atom1924;
_CKRFR[55] = 0.0;
_CKRFR[56] = 0.0;
_CKRFR[57] = 0.0;
_CKRFR[58] =  atom61056*atom1924+atom61057*atom1927;
_CKRFR[59] =  atom1924*atom61059+atom61061*atom1927;
_CKRFR[60] =  atom61064*atom1924+atom1927*atom61067;
_CKRFR[61] = 0.0;
_CKRFR[62] = 0.0;
_CKRFR[63] = 0.0;
_CKRFR[64] = 0.0;
_CKRFR[65] = 0.0;
_CKRFR[66] = 0.0;
_CKRFR[67] = 0.0;
_CKRFR[68] = 0.0;
_CKRFR[69] = 0.0;
_CKRFR[70] = 0.0;
_CKRFR[71] = 0.0;
_CKRFR[72] = 0.0;
_CKRFR[73] = 0.0;
_CKRFR[74] = 0.0;
_CKRFR[75] = 0.0;
_CKRFR[76] = 0.0;
_CKRFR[77] = 0.0;
_CKRFR[78] = 0.0;
_CKRFR[79] = 0.0;
_CKRFR[80] = 0.0;
_CKRFR[81] = 0.0;
_CKRFR[82] = 0.0;
_CKRFR[83] = 0.0;
_CKRFR[84] = 0.0;
_CKRFR[85] = 0.0;
_CKRFR[86] = 0.0;
_CKRFR[87] = 0.0;
_CKRFR[88] = 0.0;
_CKRFR[89] = atom1928*atom61003;
_CKRFR[90] = atom1928*atom61007;
_CKRFR[91] = atom1928*atom61012;
_CKRFR[92] = atom1928*atom61021;
_CKRFR[93] = atom1928*atom61028;
_CKRFR[94] = atom1928*atom61035;
_CKRFR[95] = 0.0;
_CKRFR[96] = atom1928*atom61040;
_CKRFR[97] = atom61045*atom1928;
_CKRFR[98] = atom1928*atom61052;
_CKRFR[99] = 0.0;
_CKRFR[100] = 0.0;
_CKRFR[101] = 0.0;
_CKRFR[102] = atom61057*atom1928;
_CKRFR[103] = atom61061*atom1928;
_CKRFR[104] = atom1928*atom61067;
_CKRFR[105] = 0.0;
_CKRFR[106] = 0.0;
_CKRFR[107] = 0.0;
_CKRFR[108] = 0.0;
_CKRFR[109] = 0.0;
_CKRFR[110] = 0.0;
_CKRFR[111] = 0.0;
_CKRFR[112] = 0.0;
_CKRFR[113] = 0.0;
_CKRFR[114] = 0.0;
_CKRFR[115] = 0.0;
_CKRFR[116] = 0.0;
_CKRFR[117] = 0.0;
_CKRFR[118] = 0.0;
_CKRFR[119] = 0.0;
_CKRFR[120] = 0.0;
_CKRFR[121] = 0.0;
_CKRFR[122] = 0.0;
_CKRFR[123] = 0.0;
_CKRFR[124] = 0.0;
_CKRFR[125] = 0.0;
_CKRFR[126] = 0.0;
_CKRFR[127] = 0.0;
_CKRFR[128] = 0.0;
_CKRFR[129] = 0.0;
_CKRFR[130] = 0.0;
_CKRFR[131] = 0.0;
_CKRFR[132] = atom61001*atom60814;
_CKRFR[133] =  atom61002*atom60814+atom60935*atom61003+atom61006*atom60976;
_CKRFR[134] =  atom61008*atom60976+atom60935*atom61007;
_CKRFR[135] =  atom60976*atom61017+atom61009*atom60814+atom60935*atom61012;
_CKRFR[136] =  atom60976*atom61024+atom60935*atom61021+atom61018*atom60814;
_CKRFR[137] =  atom61025*atom60814+atom60935*atom61028+atom61031*atom60976;
_CKRFR[138] =  atom61032*atom60814+atom61038*atom60976+atom60935*atom61035;
_CKRFR[139] = 0.0;
_CKRFR[140] =  atom61041*atom60976+atom60935*atom61040+atom61039*atom60814;
_CKRFR[141] =  atom61042*atom60814+atom61048*atom60976+atom61045*atom60935;
_CKRFR[142] =  atom60935*atom61052+atom61055*atom60976+atom61049*atom60814;
_CKRFR[143] = 0.0;
_CKRFR[144] = 0.0;
_CKRFR[145] = 0.0;
_CKRFR[146] =  atom61056*atom60814+atom61057*atom60935+atom61058*atom60976;
_CKRFR[147] =  atom61063*atom60976+atom60814*atom61059+atom61061*atom60935;
_CKRFR[148] =  atom61064*atom60814+atom61070*atom60976+atom60935*atom61067;
_CKRFR[149] = 0.0;
_CKRFR[150] = 0.0;
_CKRFR[151] = 0.0;
_CKRFR[152] = 0.0;
_CKRFR[153] = 0.0;
_CKRFR[154] = 0.0;
_CKRFR[155] = 0.0;
_CKRFR[156] = 0.0;
_CKRFR[157] = 0.0;
_CKRFR[158] = 0.0;
_CKRFR[159] = 0.0;
_CKRFR[160] = 0.0;
_CKRFR[161] = 0.0;
_CKRFR[162] = 0.0;
_CKRFR[163] = 0.0;
_CKRFR[164] = 0.0;
_CKRFR[165] = 0.0;
_CKRFR[166] = 0.0;
_CKRFR[167] = 0.0;
_CKRFR[168] = 0.0;
_CKRFR[169] = 0.0;
_CKRFR[170] = 0.0;
_CKRFR[171] = 0.0;
_CKRFR[172] = 0.0;
_CKRFR[173] = 0.0;
_CKRFR[174] = 0.0;
_CKRFR[175] = 0.0;
_CKRFR[176] = atom61001*atom60825;
_CKRFR[177] =  atom61002*atom60825+atom60981*atom61006+atom61003*atom60942;
_CKRFR[178] =  atom61007*atom60942+atom61008*atom60981;
_CKRFR[179] =  atom61012*atom60942+atom60981*atom61017+atom61009*atom60825;
_CKRFR[180] =  atom61018*atom60825+atom61021*atom60942+atom60981*atom61024;
_CKRFR[181] =  atom61028*atom60942+atom60981*atom61031+atom61025*atom60825;
_CKRFR[182] =  atom60981*atom61038+atom61032*atom60825+atom61035*atom60942;
_CKRFR[183] = 0.0;
_CKRFR[184] =  atom61040*atom60942+atom61039*atom60825+atom60981*atom61041;
_CKRFR[185] =  atom60981*atom61048+atom61045*atom60942+atom61042*atom60825;
_CKRFR[186] =  atom61049*atom60825+atom60981*atom61055+atom61052*atom60942;
_CKRFR[187] = 0.0;
_CKRFR[188] = 0.0;
_CKRFR[189] = 0.0;
_CKRFR[190] =  atom60981*atom61058+atom61057*atom60942+atom61056*atom60825;
_CKRFR[191] =  atom61061*atom60942+atom60981*atom61063+atom60825*atom61059;
_CKRFR[192] =  atom61067*atom60942+atom60981*atom61070+atom61064*atom60825;
_CKRFR[193] = 0.0;
_CKRFR[194] = 0.0;
_CKRFR[195] = 0.0;
_CKRFR[196] = 0.0;
_CKRFR[197] = 0.0;
_CKRFR[198] = 0.0;
_CKRFR[199] = 0.0;
_CKRFR[200] = 0.0;
_CKRFR[201] = 0.0;
_CKRFR[202] = 0.0;
_CKRFR[203] = 0.0;
_CKRFR[204] = 0.0;
_CKRFR[205] = 0.0;
_CKRFR[206] = 0.0;
_CKRFR[207] = 0.0;
_CKRFR[208] = 0.0;
_CKRFR[209] = 0.0;
_CKRFR[210] = 0.0;
_CKRFR[211] = 0.0;
_CKRFR[212] = 0.0;
_CKRFR[213] = 0.0;
_CKRFR[214] = 0.0;
_CKRFR[215] = 0.0;
_CKRFR[216] = 0.0;
_CKRFR[217] = 0.0;
_CKRFR[218] = 0.0;
_CKRFR[219] = 0.0;
_CKRFR[220] = atom61001*atom60830;
_CKRFR[221] =  atom1919*atom61006+atom61002*atom60830+atom60943*atom61003;
_CKRFR[222] =  atom61008*atom1919+atom60943*atom61007;
_CKRFR[223] =  atom60943*atom61012+atom1919*atom61017+atom61009*atom60830;
_CKRFR[224] =  atom1919*atom61024+atom60943*atom61021+atom61018*atom60830;
_CKRFR[225] =  atom60943*atom61028+atom61025*atom60830+atom1919*atom61031;
_CKRFR[226] =  atom61032*atom60830+atom1919*atom61038+atom60943*atom61035;
_CKRFR[227] = 0.0;
_CKRFR[228] =  atom1919*atom61041+atom61040*atom60943+atom61039*atom60830;
_CKRFR[229] =  atom61045*atom60943+atom61042*atom60830+atom1919*atom61048;
_CKRFR[230] =  atom60943*atom61052+atom1919*atom61055+atom61049*atom60830;
_CKRFR[231] = 0.0;
_CKRFR[232] = 0.0;
_CKRFR[233] = 0.0;
_CKRFR[234] =  atom61056*atom60830+atom61058*atom1919+atom61057*atom60943;
_CKRFR[235] =  atom61059*atom60830+atom61061*atom60943+atom1919*atom61063;
_CKRFR[236] =  atom61064*atom60830+atom60943*atom61067+atom1919*atom61070;
_CKRFR[237] = 0.0;
_CKRFR[238] = 0.0;
_CKRFR[239] = 0.0;
_CKRFR[240] = 0.0;
_CKRFR[241] = 0.0;
_CKRFR[242] = 0.0;
_CKRFR[243] = 0.0;
_CKRFR[244] = 0.0;
_CKRFR[245] = 0.0;
_CKRFR[246] = 0.0;
_CKRFR[247] = 0.0;
_CKRFR[248] = 0.0;
_CKRFR[249] = 0.0;
_CKRFR[250] = 0.0;
_CKRFR[251] = 0.0;
_CKRFR[252] = 0.0;
_CKRFR[253] = 0.0;
_CKRFR[254] = 0.0;
_CKRFR[255] = 0.0;
_CKRFR[256] = 0.0;
_CKRFR[257] = 0.0;
_CKRFR[258] = 0.0;
_CKRFR[259] = 0.0;
_CKRFR[260] = 0.0;
_CKRFR[261] = 0.0;
_CKRFR[262] = 0.0;
_CKRFR[263] = 0.0;
_CKRFR[264] = atom61001*atom60845;
_CKRFR[265] =  atom60985*atom61006+atom61003*atom60950+atom61002*atom60845;
_CKRFR[266] =  atom61008*atom60985+atom60950*atom61007;
_CKRFR[267] =  atom60985*atom61017+atom61012*atom60950+atom61009*atom60845;
_CKRFR[268] =  atom60985*atom61024+atom61018*atom60845+atom60950*atom61021;
_CKRFR[269] =  atom60985*atom61031+atom61025*atom60845+atom61028*atom60950;
_CKRFR[270] =  atom61035*atom60950+atom60985*atom61038+atom61032*atom60845;
_CKRFR[271] = 0.0;
_CKRFR[272] =  atom60985*atom61041+atom61039*atom60845+atom61040*atom60950;
_CKRFR[273] =  atom60985*atom61048+atom60845*atom61042+atom61045*atom60950;
_CKRFR[274] =  atom61049*atom60845+atom60950*atom61052+atom60985*atom61055;
_CKRFR[275] = 0.0;
_CKRFR[276] = 0.0;
_CKRFR[277] = 0.0;
_CKRFR[278] =  atom61057*atom60950+atom61056*atom60845+atom61058*atom60985;
_CKRFR[279] =  atom60845*atom61059+atom60985*atom61063+atom61061*atom60950;
_CKRFR[280] =  atom60950*atom61067+atom61064*atom60845+atom60985*atom61070;
_CKRFR[281] = 0.0;
_CKRFR[282] = 0.0;
_CKRFR[283] = 0.0;
_CKRFR[284] = 0.0;
_CKRFR[285] = 0.0;
_CKRFR[286] = 0.0;
_CKRFR[287] = 0.0;
_CKRFR[288] = 0.0;
_CKRFR[289] = 0.0;
_CKRFR[290] = 0.0;
_CKRFR[291] = 0.0;
_CKRFR[292] = 0.0;
_CKRFR[293] = 0.0;
_CKRFR[294] = 0.0;
_CKRFR[295] = 0.0;
_CKRFR[296] = 0.0;
_CKRFR[297] = 0.0;
_CKRFR[298] = 0.0;
_CKRFR[299] = 0.0;
_CKRFR[300] = 0.0;
_CKRFR[301] = 0.0;
_CKRFR[302] = 0.0;
_CKRFR[303] = 0.0;
_CKRFR[304] = 0.0;
_CKRFR[305] = 0.0;
_CKRFR[306] = 0.0;
_CKRFR[307] = 0.0;
_CKRFR[308] = 0.0;
_CKRFR[309] = 0.0;
_CKRFR[310] = 0.0;
_CKRFR[311] = 0.0;
_CKRFR[312] = 0.0;
_CKRFR[313] = 0.0;
_CKRFR[314] = 0.0;
_CKRFR[315] = 0.0;
_CKRFR[316] = 0.0;
_CKRFR[317] = 0.0;
_CKRFR[318] = 0.0;
_CKRFR[319] = 0.0;
_CKRFR[320] = 0.0;
_CKRFR[321] = 0.0;
_CKRFR[322] = 0.0;
_CKRFR[323] = 0.0;
_CKRFR[324] = 0.0;
_CKRFR[325] = 0.0;
_CKRFR[326] = 0.0;
_CKRFR[327] = 0.0;
_CKRFR[328] = 0.0;
_CKRFR[329] = 0.0;
_CKRFR[330] = 0.0;
_CKRFR[331] = 0.0;
_CKRFR[332] = 0.0;
_CKRFR[333] = 0.0;
_CKRFR[334] = 0.0;
_CKRFR[335] = 0.0;
_CKRFR[336] = 0.0;
_CKRFR[337] = 0.0;
_CKRFR[338] = 0.0;
_CKRFR[339] = 0.0;
_CKRFR[340] = 0.0;
_CKRFR[341] = 0.0;
_CKRFR[342] = 0.0;
_CKRFR[343] = 0.0;
_CKRFR[344] = 0.0;
_CKRFR[345] = 0.0;
_CKRFR[346] = 0.0;
_CKRFR[347] = 0.0;
_CKRFR[348] = 0.0;
_CKRFR[349] = 0.0;
_CKRFR[350] = 0.0;
_CKRFR[351] = 0.0;
_CKRFR[352] = atom61001*atom7663;
_CKRFR[353] =  atom7712*atom61003+atom61002*atom7663;
_CKRFR[354] = atom7712*atom61007;
_CKRFR[355] =  atom7712*atom61012+atom61009*atom7663;
_CKRFR[356] =  atom61018*atom7663+atom7712*atom61021;
_CKRFR[357] =  atom7712*atom61028+atom61025*atom7663;
_CKRFR[358] =  atom7712*atom61035+atom61032*atom7663;
_CKRFR[359] = 0.0;
_CKRFR[360] =  atom61039*atom7663+atom61040*atom7712;
_CKRFR[361] =  atom61045*atom7712+atom7663*atom61042;
_CKRFR[362] =  atom61049*atom7663+atom7712*atom61052;
_CKRFR[363] = 0.0;
_CKRFR[364] = 0.0;
_CKRFR[365] = 0.0;
_CKRFR[366] =  atom61056*atom7663+atom61057*atom7712;
_CKRFR[367] =  atom7663*atom61059+atom61061*atom7712;
_CKRFR[368] =  atom7712*atom61067+atom61064*atom7663;
_CKRFR[369] = 0.0;
_CKRFR[370] = 0.0;
_CKRFR[371] = 0.0;
_CKRFR[372] = 0.0;
_CKRFR[373] = 0.0;
_CKRFR[374] = 0.0;
_CKRFR[375] = 0.0;
_CKRFR[376] = 0.0;
_CKRFR[377] = 0.0;
_CKRFR[378] = 0.0;
_CKRFR[379] = 0.0;
_CKRFR[380] = 0.0;
_CKRFR[381] = 0.0;
_CKRFR[382] = 0.0;
_CKRFR[383] = 0.0;
_CKRFR[384] = 0.0;
_CKRFR[385] = 0.0;
_CKRFR[386] = 0.0;
_CKRFR[387] = 0.0;
_CKRFR[388] = 0.0;
_CKRFR[389] = 0.0;
_CKRFR[390] = 0.0;
_CKRFR[391] = 0.0;
_CKRFR[392] = 0.0;
_CKRFR[393] = 0.0;
_CKRFR[394] = 0.0;
_CKRFR[395] = 0.0;
_CKRFR[396] = atom61001*atom60871;
_CKRFR[397] =  atom61114+atom60957*atom61003+atom61002*atom60871;
_CKRFR[398] =  atom60957*atom61007+atom61149;
_CKRFR[399] =  atom61191+atom60957*atom61012+atom60871*atom61009;
_CKRFR[400] =  atom60871*atom61018+atom61241+atom60957*atom61021;
_CKRFR[401] =  atom60957*atom61028+atom61291+atom60871*atom61025;
_CKRFR[402] =  atom60871*atom61032+atom60957*atom61035+atom61341;
_CKRFR[403] = 0.0;
_CKRFR[404] =  atom61391+atom60957*atom61040+atom61039*atom60871;
_CKRFR[405] =  atom61441+atom60957*atom61045+atom60871*atom61042;
_CKRFR[406] =  atom61491+atom60957*atom61052+atom61049*atom60871;
_CKRFR[407] = 0.0;
_CKRFR[408] = 0.0;
_CKRFR[409] = 0.0;
_CKRFR[410] =  atom61056*atom60871+atom61541+atom60957*atom61057;
_CKRFR[411] =  atom60871*atom61059+atom61591+atom60957*atom61061;
_CKRFR[412] =  atom61064*atom60871+atom60957*atom61067+atom61641;
_CKRFR[413] = 0.0;
_CKRFR[414] = 0.0;
_CKRFR[415] = 0.0;
_CKRFR[416] = 0.0;
_CKRFR[417] = 0.0;
_CKRFR[418] = 0.0;
_CKRFR[419] = 0.0;
_CKRFR[420] = 0.0;
_CKRFR[421] = 0.0;
_CKRFR[422] = 0.0;
_CKRFR[423] = 0.0;
_CKRFR[424] = 0.0;
_CKRFR[425] = 0.0;
_CKRFR[426] = 0.0;
_CKRFR[427] = 0.0;
_CKRFR[428] = 0.0;
_CKRFR[429] = 0.0;
_CKRFR[430] = 0.0;
_CKRFR[431] = 0.0;
_CKRFR[432] = 0.0;
_CKRFR[433] = 0.0;
_CKRFR[434] = 0.0;
_CKRFR[435] = 0.0;
_CKRFR[436] = 0.0;
_CKRFR[437] = 0.0;
_CKRFR[438] = 0.0;
_CKRFR[439] = 0.0;
_CKRFR[440] = atom61001*atom60890;
_CKRFR[441] =  atom60890*atom61002+atom61003*atom60964+atom61006*atom60995;
_CKRFR[442] =  atom61008*atom60995+atom60964*atom61007;
_CKRFR[443] =  atom60995*atom61017+atom60890*atom61009+atom61012*atom60964;
_CKRFR[444] =  atom60964*atom61021+atom60995*atom61024+atom60890*atom61018;
_CKRFR[445] =  atom60995*atom61031+atom60890*atom61025+atom61028*atom60964;
_CKRFR[446] =  atom60890*atom61032+atom61035*atom60964+atom61038*atom60995;
_CKRFR[447] = 0.0;
_CKRFR[448] =  atom61041*atom60995+atom61039*atom60890+atom61040*atom60964;
_CKRFR[449] =  atom61045*atom60964+atom61048*atom60995+atom60890*atom61042;
_CKRFR[450] =  atom60964*atom61052+atom61049*atom60890+atom61055*atom60995;
_CKRFR[451] = 0.0;
_CKRFR[452] = 0.0;
_CKRFR[453] = 0.0;
_CKRFR[454] =  atom61056*atom60890+atom61057*atom60964+atom61058*atom60995;
_CKRFR[455] =  atom61063*atom60995+atom60890*atom61059+atom61061*atom60964;
_CKRFR[456] =  atom60890*atom61064+atom61070*atom60995+atom60964*atom61067;
_CKRFR[457] = 0.0;
_CKRFR[458] = 0.0;
_CKRFR[459] = 0.0;
_CKRFR[460] = 0.0;
_CKRFR[461] = 0.0;
_CKRFR[462] = 0.0;
_CKRFR[463] = 0.0;
_CKRFR[464] = 0.0;
_CKRFR[465] = 0.0;
_CKRFR[466] = 0.0;
_CKRFR[467] = 0.0;
_CKRFR[468] = 0.0;
_CKRFR[469] = 0.0;
_CKRFR[470] = 0.0;
_CKRFR[471] = 0.0;
_CKRFR[472] = 0.0;
_CKRFR[473] = 0.0;
_CKRFR[474] = 0.0;
_CKRFR[475] = 0.0;
_CKRFR[476] = 0.0;
_CKRFR[477] = 0.0;
_CKRFR[478] = 0.0;
_CKRFR[479] = 0.0;
_CKRFR[480] = 0.0;
_CKRFR[481] = 0.0;
_CKRFR[482] = 0.0;
_CKRFR[483] = 0.0;
_CKRFR[484] = 0.0;
_CKRFR[485] = 0.0;
_CKRFR[486] = 0.0;
_CKRFR[487] = 0.0;
_CKRFR[488] = 0.0;
_CKRFR[489] = 0.0;
_CKRFR[490] = 0.0;
_CKRFR[491] = 0.0;
_CKRFR[492] = 0.0;
_CKRFR[493] = 0.0;
_CKRFR[494] = 0.0;
_CKRFR[495] = 0.0;
_CKRFR[496] = 0.0;
_CKRFR[497] = 0.0;
_CKRFR[498] = 0.0;
_CKRFR[499] = 0.0;
_CKRFR[500] = 0.0;
_CKRFR[501] = 0.0;
_CKRFR[502] = 0.0;
_CKRFR[503] = 0.0;
_CKRFR[504] = 0.0;
_CKRFR[505] = 0.0;
_CKRFR[506] = 0.0;
_CKRFR[507] = 0.0;
_CKRFR[508] = 0.0;
_CKRFR[509] = 0.0;
_CKRFR[510] = 0.0;
_CKRFR[511] = 0.0;
_CKRFR[512] = 0.0;
_CKRFR[513] = 0.0;
_CKRFR[514] = 0.0;
_CKRFR[515] = 0.0;
_CKRFR[516] = 0.0;
_CKRFR[517] = 0.0;
_CKRFR[518] = 0.0;
_CKRFR[519] = 0.0;
_CKRFR[520] = 0.0;
_CKRFR[521] = 0.0;
_CKRFR[522] = 0.0;
_CKRFR[523] = 0.0;
_CKRFR[524] = 0.0;
_CKRFR[525] = 0.0;
_CKRFR[526] = 0.0;
_CKRFR[527] = 0.0;
_CKRFR[528] = 0.0;
_CKRFR[529] = 0.0;
_CKRFR[530] = 0.0;
_CKRFR[531] = 0.0;
_CKRFR[532] = 0.0;
_CKRFR[533] = 0.0;
_CKRFR[534] = 0.0;
_CKRFR[535] = 0.0;
_CKRFR[536] = 0.0;
_CKRFR[537] = 0.0;
_CKRFR[538] = 0.0;
_CKRFR[539] = 0.0;
_CKRFR[540] = 0.0;
_CKRFR[541] = 0.0;
_CKRFR[542] = 0.0;
_CKRFR[543] = 0.0;
_CKRFR[544] = 0.0;
_CKRFR[545] = 0.0;
_CKRFR[546] = 0.0;
_CKRFR[547] = 0.0;
_CKRFR[548] = 0.0;
_CKRFR[549] = 0.0;
_CKRFR[550] = 0.0;
_CKRFR[551] = 0.0;
_CKRFR[552] = 0.0;
_CKRFR[553] = 0.0;
_CKRFR[554] = 0.0;
_CKRFR[555] = 0.0;
_CKRFR[556] = 0.0;
_CKRFR[557] = 0.0;
_CKRFR[558] = 0.0;
_CKRFR[559] = 0.0;
_CKRFR[560] = 0.0;
_CKRFR[561] = 0.0;
_CKRFR[562] = 0.0;
_CKRFR[563] = 0.0;
_CKRFR[564] = 0.0;
_CKRFR[565] = 0.0;
_CKRFR[566] = 0.0;
_CKRFR[567] = 0.0;
_CKRFR[568] = 0.0;
_CKRFR[569] = 0.0;
_CKRFR[570] = 0.0;
_CKRFR[571] = 0.0;
_CKRFR[572] = 0.0;
_CKRFR[573] = 0.0;
_CKRFR[574] = 0.0;
_CKRFR[575] = 0.0;
_CKRFR[576] = 0.0;
_CKRFR[577] = 0.0;
_CKRFR[578] = 0.0;
_CKRFR[579] = 0.0;
_CKRFR[580] = 0.0;
_CKRFR[581] = 0.0;
_CKRFR[582] = 0.0;
_CKRFR[583] = 0.0;
_CKRFR[584] = 0.0;
_CKRFR[585] = 0.0;
_CKRFR[586] = 0.0;
_CKRFR[587] = 0.0;
_CKRFR[588] = 0.0;
_CKRFR[589] = 0.0;
_CKRFR[590] = 0.0;
_CKRFR[591] = 0.0;
_CKRFR[592] = 0.0;
_CKRFR[593] = 0.0;
_CKRFR[594] = 0.0;
_CKRFR[595] = 0.0;
_CKRFR[596] = 0.0;
_CKRFR[597] = 0.0;
_CKRFR[598] = 0.0;
_CKRFR[599] = 0.0;
_CKRFR[600] = 0.0;
_CKRFR[601] = 0.0;
_CKRFR[602] = 0.0;
_CKRFR[603] = 0.0;
_CKRFR[604] = 0.0;
_CKRFR[605] = 0.0;
_CKRFR[606] = 0.0;
_CKRFR[607] = 0.0;
_CKRFR[608] = 0.0;
_CKRFR[609] = 0.0;
_CKRFR[610] = 0.0;
_CKRFR[611] = 0.0;
_CKRFR[612] = 0.0;
_CKRFR[613] = 0.0;
_CKRFR[614] = 0.0;
_CKRFR[615] = 0.0;
_CKRFR[616] = atom61001*atom7672;
_CKRFR[617] =  atom61003*atom7721+atom61002*atom7672;
_CKRFR[618] = atom7721*atom61007;
_CKRFR[619] =  atom7721*atom61012+atom61009*atom7672;
_CKRFR[620] =  atom61018*atom7672+atom7721*atom61021;
_CKRFR[621] =  atom7721*atom61028+atom61025*atom7672;
_CKRFR[622] =  atom61035*atom7721+atom61032*atom7672;
_CKRFR[623] = 0.0;
_CKRFR[624] =  atom61039*atom7672+atom61040*atom7721;
_CKRFR[625] =  atom61042*atom7672+atom61045*atom7721;
_CKRFR[626] =  atom61049*atom7672+atom7721*atom61052;
_CKRFR[627] = 0.0;
_CKRFR[628] = 0.0;
_CKRFR[629] = 0.0;
_CKRFR[630] =  atom61057*atom7721+atom61056*atom7672;
_CKRFR[631] =  atom7672*atom61059+atom61061*atom7721;
_CKRFR[632] =  atom7721*atom61067+atom61064*atom7672;
_CKRFR[633] = 0.0;
_CKRFR[634] = 0.0;
_CKRFR[635] = 0.0;
_CKRFR[636] = 0.0;
_CKRFR[637] = 0.0;
_CKRFR[638] = 0.0;
_CKRFR[639] = 0.0;
_CKRFR[640] = 0.0;
_CKRFR[641] = 0.0;
_CKRFR[642] = 0.0;
_CKRFR[643] = 0.0;
_CKRFR[644] = 0.0;
_CKRFR[645] = 0.0;
_CKRFR[646] = 0.0;
_CKRFR[647] = 0.0;
_CKRFR[648] = 0.0;
_CKRFR[649] = 0.0;
_CKRFR[650] = 0.0;
_CKRFR[651] = 0.0;
_CKRFR[652] = 0.0;
_CKRFR[653] = 0.0;
_CKRFR[654] = 0.0;
_CKRFR[655] = 0.0;
_CKRFR[656] = 0.0;
_CKRFR[657] = 0.0;
_CKRFR[658] = 0.0;
_CKRFR[659] = 0.0;
_CKRFR[660] = atom61001*atom60893;
_CKRFR[661] =  atom61114+atom61002*atom60893+atom60967*atom61003;
_CKRFR[662] =  atom60967*atom61007+atom61149;
_CKRFR[663] =  atom61009*atom60893+atom61191+atom60967*atom61012;
_CKRFR[664] =  atom61241+atom61018*atom60893+atom60967*atom61021;
_CKRFR[665] =  atom61025*atom60893+atom61291+atom60967*atom61028;
_CKRFR[666] =  atom60967*atom61035+atom61032*atom60893+atom61341;
_CKRFR[667] = 0.0;
_CKRFR[668] =  atom61391+atom61040*atom60967+atom61039*atom60893;
_CKRFR[669] =  atom61042*atom60893+atom61441+atom61045*atom60967;
_CKRFR[670] =  atom61491+atom61049*atom60893+atom60967*atom61052;
_CKRFR[671] = 0.0;
_CKRFR[672] = 0.0;
_CKRFR[673] = 0.0;
_CKRFR[674] =  atom61541+atom61056*atom60893+atom61057*atom60967;
_CKRFR[675] =  atom61061*atom60967+atom61059*atom60893+atom61591;
_CKRFR[676] =  atom60967*atom61067+atom61064*atom60893+atom61641;
_CKRFR[677] = 0.0;
_CKRFR[678] = 0.0;
_CKRFR[679] = 0.0;
_CKRFR[680] = 0.0;
_CKRFR[681] = 0.0;
_CKRFR[682] = 0.0;
_CKRFR[683] = 0.0;
_CKRFR[684] = 0.0;
_CKRFR[685] = 0.0;
_CKRFR[686] = 0.0;
_CKRFR[687] = 0.0;
_CKRFR[688] = 0.0;
_CKRFR[689] = 0.0;
_CKRFR[690] = 0.0;
_CKRFR[691] = 0.0;
_CKRFR[692] = 0.0;
_CKRFR[693] = 0.0;
_CKRFR[694] = 0.0;
_CKRFR[695] = 0.0;
_CKRFR[696] = 0.0;
_CKRFR[697] = 0.0;
_CKRFR[698] = 0.0;
_CKRFR[699] = 0.0;
_CKRFR[700] = 0.0;
_CKRFR[701] = 0.0;
_CKRFR[702] = 0.0;
_CKRFR[703] = 0.0;
_CKRFR[704] = atom61001*atom60928;
_CKRFR[705] =  atom61002*atom60928+atom61003*atom60973+atom61006*atom61000;
_CKRFR[706] =  atom61008*atom61000+atom61007*atom60973;
_CKRFR[707] =  atom61009*atom60928+atom61012*atom60973+atom61000*atom61017;
_CKRFR[708] =  atom61000*atom61024+atom61021*atom60973+atom61018*atom60928;
_CKRFR[709] =  atom61025*atom60928+atom61028*atom60973+atom61000*atom61031;
_CKRFR[710] =  atom61000*atom61038+atom61032*atom60928+atom61035*atom60973;
_CKRFR[711] = 0.0;
_CKRFR[712] =  atom61040*atom60973+atom61039*atom60928+atom61041*atom61000;
_CKRFR[713] =  atom61000*atom61048+atom61045*atom60973+atom61042*atom60928;
_CKRFR[714] =  atom61000*atom61055+atom61052*atom60973+atom61049*atom60928;
_CKRFR[715] = 0.0;
_CKRFR[716] = 0.0;
_CKRFR[717] = 0.0;
_CKRFR[718] =  atom61056*atom60928+atom61058*atom61000+atom61057*atom60973;
_CKRFR[719] =  atom60928*atom61059+atom61061*atom60973+atom61000*atom61063;
_CKRFR[720] =  atom61064*atom60928+atom61000*atom61070+atom61067*atom60973;
_CKRFR[721] = 0.0;
_CKRFR[722] = 0.0;
_CKRFR[723] = 0.0;
_CKRFR[724] = 0.0;
_CKRFR[725] = 0.0;
_CKRFR[726] = 0.0;
_CKRFR[727] = 0.0;
_CKRFR[728] = 0.0;
_CKRFR[729] = 0.0;
_CKRFR[730] = 0.0;
_CKRFR[731] = 0.0;
_CKRFR[732] = 0.0;
_CKRFR[733] = 0.0;
_CKRFR[734] = 0.0;
_CKRFR[735] = 0.0;
_CKRFR[736] = 0.0;
_CKRFR[737] = 0.0;
_CKRFR[738] = 0.0;
_CKRFR[739] = 0.0;
_CKRFR[740] = 0.0;
_CKRFR[741] = 0.0;
_CKRFR[742] = 0.0;
_CKRFR[743] = 0.0;
_CKRFR[744] = 0.0;
_CKRFR[745] = 0.0;
_CKRFR[746] = 0.0;
_CKRFR[747] = 0.0;
_CKRFR[748] = 0.0;
_CKRFR[749] = 0.0;
_CKRFR[750] = 0.0;
_CKRFR[751] = 0.0;
_CKRFR[752] = 0.0;
_CKRFR[753] = 0.0;
_CKRFR[754] = 0.0;
_CKRFR[755] = 0.0;
_CKRFR[756] = 0.0;
_CKRFR[757] = 0.0;
_CKRFR[758] = 0.0;
_CKRFR[759] = 0.0;
_CKRFR[760] = 0.0;
_CKRFR[761] = 0.0;
_CKRFR[762] = 0.0;
_CKRFR[763] = 0.0;
_CKRFR[764] = 0.0;
_CKRFR[765] = 0.0;
_CKRFR[766] = 0.0;
_CKRFR[767] = 0.0;
_CKRFR[768] = 0.0;
_CKRFR[769] = 0.0;
_CKRFR[770] = 0.0;
_CKRFR[771] = 0.0;
_CKRFR[772] = 0.0;
_CKRFR[773] = 0.0;
_CKRFR[774] = 0.0;
_CKRFR[775] = 0.0;
_CKRFR[776] = 0.0;
_CKRFR[777] = 0.0;
_CKRFR[778] = 0.0;
_CKRFR[779] = 0.0;
_CKRFR[780] = 0.0;
_CKRFR[781] = 0.0;
_CKRFR[782] = 0.0;
_CKRFR[783] = 0.0;
_CKRFR[784] = 0.0;
_CKRFR[785] = 0.0;
_CKRFR[786] = 0.0;
_CKRFR[787] = 0.0;
_CKRFR[788] = 0.0;
_CKRFR[789] = 0.0;
_CKRFR[790] = 0.0;
_CKRFR[791] = 0.0;
_CKRFR[792] = 0.0;
_CKRFR[793] = 0.0;
_CKRFR[794] = 0.0;
_CKRFR[795] = 0.0;
_CKRFR[796] = 0.0;
_CKRFR[797] = 0.0;
_CKRFR[798] = 0.0;
_CKRFR[799] = 0.0;
_CKRFR[800] = 0.0;
_CKRFR[801] = 0.0;
_CKRFR[802] = 0.0;
_CKRFR[803] = 0.0;
_CKRFR[804] = 0.0;
_CKRFR[805] = 0.0;
_CKRFR[806] = 0.0;
_CKRFR[807] = 0.0;
_CKRFR[808] = 0.0;
_CKRFR[809] = 0.0;
_CKRFR[810] = 0.0;
_CKRFR[811] = 0.0;
_CKRFR[812] = 0.0;
_CKRFR[813] = 0.0;
_CKRFR[814] = 0.0;
_CKRFR[815] = 0.0;
_CKRFR[816] = 0.0;
_CKRFR[817] = 0.0;
_CKRFR[818] = 0.0;
_CKRFR[819] = 0.0;
_CKRFR[820] = 0.0;
_CKRFR[821] = 0.0;
_CKRFR[822] = 0.0;
_CKRFR[823] = 0.0;
_CKRFR[824] = 0.0;
_CKRFR[825] = 0.0;
_CKRFR[826] = 0.0;
_CKRFR[827] = 0.0;
_CKRFR[828] = 0.0;
_CKRFR[829] = 0.0;
_CKRFR[830] = 0.0;
_CKRFR[831] = 0.0;
_CKRFR[832] = 0.0;
_CKRFR[833] = 0.0;
_CKRFR[834] = 0.0;
_CKRFR[835] = 0.0;
_CKRFR[836] = 0.0;
_CKRFR[837] = 0.0;
_CKRFR[838] = 0.0;
_CKRFR[839] = 0.0;
_CKRFR[840] = 0.0;
_CKRFR[841] = 0.0;
_CKRFR[842] = 0.0;
_CKRFR[843] = 0.0;
_CKRFR[844] = 0.0;
_CKRFR[845] = 0.0;
_CKRFR[846] = 0.0;
_CKRFR[847] = 0.0;
_CKRFR[848] = 0.0;
_CKRFR[849] = 0.0;
_CKRFR[850] = 0.0;
_CKRFR[851] = 0.0;
_CKRFR[852] = 0.0;
_CKRFR[853] = 0.0;
_CKRFR[854] = 0.0;
_CKRFR[855] = 0.0;
_CKRFR[856] = 0.0;
_CKRFR[857] = 0.0;
_CKRFR[858] = 0.0;
_CKRFR[859] = 0.0;
_CKRFR[860] = 0.0;
_CKRFR[861] = 0.0;
_CKRFR[862] = 0.0;
_CKRFR[863] = 0.0;
_CKRFR[864] = 0.0;
_CKRFR[865] = 0.0;
_CKRFR[866] = 0.0;
_CKRFR[867] = 0.0;
_CKRFR[868] = 0.0;
_CKRFR[869] = 0.0;
_CKRFR[870] = 0.0;
_CKRFR[871] = 0.0;
_CKRFR[872] = 0.0;
_CKRFR[873] = 0.0;
_CKRFR[874] = 0.0;
_CKRFR[875] = 0.0;
_CKRFR[876] = 0.0;
_CKRFR[877] = 0.0;
_CKRFR[878] = 0.0;
_CKRFR[879] = 0.0;
_CKRFR[880] = 0.0;
_CKRFR[881] = 0.0;
_CKRFR[882] = 0.0;
_CKRFR[883] = 0.0;
_CKRFR[884] = 0.0;
_CKRFR[885] = 0.0;
_CKRFR[886] = 0.0;
_CKRFR[887] = 0.0;
_CKRFR[888] = 0.0;
_CKRFR[889] = 0.0;
_CKRFR[890] = 0.0;
_CKRFR[891] = 0.0;
_CKRFR[892] = 0.0;
_CKRFR[893] = 0.0;
_CKRFR[894] = 0.0;
_CKRFR[895] = 0.0;
_CKRFR[896] = 0.0;
_CKRFR[897] = 0.0;
_CKRFR[898] = 0.0;
_CKRFR[899] = 0.0;
_CKRFR[900] = 0.0;
_CKRFR[901] = 0.0;
_CKRFR[902] = 0.0;
_CKRFR[903] = 0.0;
_CKRFR[904] = 0.0;
_CKRFR[905] = 0.0;
_CKRFR[906] = 0.0;
_CKRFR[907] = 0.0;
_CKRFR[908] = 0.0;
_CKRFR[909] = 0.0;
_CKRFR[910] = 0.0;
_CKRFR[911] = 0.0;
_CKRFR[912] = 0.0;
_CKRFR[913] = 0.0;
_CKRFR[914] = 0.0;
_CKRFR[915] = 0.0;
_CKRFR[916] = 0.0;
_CKRFR[917] = 0.0;
_CKRFR[918] = 0.0;
_CKRFR[919] = 0.0;
_CKRFR[920] = 0.0;
_CKRFR[921] = 0.0;
_CKRFR[922] = 0.0;
_CKRFR[923] = 0.0;
_CKRFR[924] = 0.0;
_CKRFR[925] = 0.0;
_CKRFR[926] = 0.0;
_CKRFR[927] = 0.0;
_CKRFR[928] = 0.0;
_CKRFR[929] = 0.0;
_CKRFR[930] = 0.0;
_CKRFR[931] = 0.0;
_CKRFR[932] = 0.0;
_CKRFR[933] = 0.0;
_CKRFR[934] = 0.0;
_CKRFR[935] = 0.0;
_CKRFR[936] = 0.0;
_CKRFR[937] = 0.0;
_CKRFR[938] = 0.0;
_CKRFR[939] = 0.0;
_CKRFR[940] = 0.0;
_CKRFR[941] = 0.0;
_CKRFR[942] = 0.0;
_CKRFR[943] = 0.0;
_CKRFR[944] = 0.0;
_CKRFR[945] = 0.0;
_CKRFR[946] = 0.0;
_CKRFR[947] = 0.0;
_CKRFR[948] = 0.0;
_CKRFR[949] = 0.0;
_CKRFR[950] = 0.0;
_CKRFR[951] = 0.0;
_CKRFR[952] = 0.0;
_CKRFR[953] = 0.0;
_CKRFR[954] = 0.0;
_CKRFR[955] = 0.0;
_CKRFR[956] = 0.0;
_CKRFR[957] = 0.0;
_CKRFR[958] = 0.0;
_CKRFR[959] = 0.0;
_CKRFR[960] = 0.0;
_CKRFR[961] = 0.0;
_CKRFR[962] = 0.0;
_CKRFR[963] = 0.0;
_CKRFR[964] = 0.0;
_CKRFR[965] = 0.0;
_CKRFR[966] = 0.0;
_CKRFR[967] = 0.0;
_CKRFR[968] = 0.0;
_CKRFR[969] = 0.0;
_CKRFR[970] = 0.0;
_CKRFR[971] = 0.0;
_CKRFR[972] = 0.0;
_CKRFR[973] = 0.0;
_CKRFR[974] = 0.0;
_CKRFR[975] = 0.0;
_CKRFR[976] = 0.0;
_CKRFR[977] = 0.0;
_CKRFR[978] = 0.0;
_CKRFR[979] = 0.0;
_CKRFR[980] = 0.0;
_CKRFR[981] = 0.0;
_CKRFR[982] = 0.0;
_CKRFR[983] = 0.0;
_CKRFR[984] = 0.0;
_CKRFR[985] = 0.0;
_CKRFR[986] = 0.0;
_CKRFR[987] = 0.0;
_CKRFR[988] = 0.0;
_CKRFR[989] = 0.0;
_CKRFR[990] = 0.0;
_CKRFR[991] = 0.0;
_CKRFR[992] = 0.0;
_CKRFR[993] = 0.0;
_CKRFR[994] = 0.0;
_CKRFR[995] = 0.0;
_CKRFR[996] = 0.0;
_CKRFR[997] = 0.0;
_CKRFR[998] = 0.0;
_CKRFR[999] = 0.0;
_CKRFR[1000] = 0.0;
_CKRFR[1001] = 0.0;
_CKRFR[1002] = 0.0;
_CKRFR[1003] = 0.0;
_CKRFR[1004] = 0.0;
_CKRFR[1005] = 0.0;
_CKRFR[1006] = 0.0;
_CKRFR[1007] = 0.0;
_CKRFR[1008] = 0.0;
_CKRFR[1009] = 0.0;
_CKRFR[1010] = 0.0;
_CKRFR[1011] = 0.0;
_CKRFR[1012] = 0.0;
_CKRFR[1013] = 0.0;
_CKRFR[1014] = 0.0;
_CKRFR[1015] = 0.0;
_CKRFR[1016] = 0.0;
_CKRFR[1017] = 0.0;
_CKRFR[1018] = 0.0;
_CKRFR[1019] = 0.0;
_CKRFR[1020] = 0.0;
_CKRFR[1021] = 0.0;
_CKRFR[1022] = 0.0;
_CKRFR[1023] = 0.0;
_CKRFR[1024] = 0.0;
_CKRFR[1025] = 0.0;
_CKRFR[1026] = 0.0;
_CKRFR[1027] = 0.0;
_CKRFR[1028] = 0.0;
_CKRFR[1029] = 0.0;
_CKRFR[1030] = 0.0;
_CKRFR[1031] = 0.0;
_CKRFR[1032] = 0.0;
_CKRFR[1033] = 0.0;
_CKRFR[1034] = 0.0;
_CKRFR[1035] = 0.0;
_CKRFR[1036] = 0.0;
_CKRFR[1037] = 0.0;
_CKRFR[1038] = 0.0;
_CKRFR[1039] = 0.0;
_CKRFR[1040] = 0.0;
_CKRFR[1041] = 0.0;
_CKRFR[1042] = 0.0;
_CKRFR[1043] = 0.0;
_CKRFR[1044] = 0.0;
_CKRFR[1045] = 0.0;
_CKRFR[1046] = 0.0;
_CKRFR[1047] = 0.0;
_CKRFR[1048] = 0.0;
_CKRFR[1049] = 0.0;
_CKRFR[1050] = 0.0;
_CKRFR[1051] = 0.0;
_CKRFR[1052] = 0.0;
_CKRFR[1053] = 0.0;
_CKRFR[1054] = 0.0;
_CKRFR[1055] = 0.0;
_CKRFR[1056] = 0.0;
_CKRFR[1057] = 0.0;
_CKRFR[1058] = 0.0;
_CKRFR[1059] = 0.0;
_CKRFR[1060] = 0.0;
_CKRFR[1061] = 0.0;
_CKRFR[1062] = 0.0;
_CKRFR[1063] = 0.0;
_CKRFR[1064] = 0.0;
_CKRFR[1065] = 0.0;
_CKRFR[1066] = 0.0;
_CKRFR[1067] = 0.0;
_CKRFR[1068] = 0.0;
_CKRFR[1069] = 0.0;
_CKRFR[1070] = 0.0;
_CKRFR[1071] = 0.0;
_CKRFR[1072] = 0.0;
_CKRFR[1073] = 0.0;
_CKRFR[1074] = 0.0;
_CKRFR[1075] = 0.0;
_CKRFR[1076] = 0.0;
_CKRFR[1077] = 0.0;
_CKRFR[1078] = 0.0;
_CKRFR[1079] = 0.0;
_CKRFR[1080] = 0.0;
_CKRFR[1081] = 0.0;
_CKRFR[1082] = 0.0;
_CKRFR[1083] = 0.0;
_CKRFR[1084] = 0.0;
_CKRFR[1085] = 0.0;
_CKRFR[1086] = 0.0;
_CKRFR[1087] = 0.0;
_CKRFR[1088] = 0.0;
_CKRFR[1089] = 0.0;
_CKRFR[1090] = 0.0;
_CKRFR[1091] = 0.0;
_CKRFR[1092] = 0.0;
_CKRFR[1093] = 0.0;
_CKRFR[1094] = 0.0;
_CKRFR[1095] = 0.0;
_CKRFR[1096] = 0.0;
_CKRFR[1097] = 0.0;
_CKRFR[1098] = 0.0;
_CKRFR[1099] = 0.0;
_CKRFR[1100] = 0.0;
_CKRFR[1101] = 0.0;
_CKRFR[1102] = 0.0;
_CKRFR[1103] = 0.0;
_CKRFR[1104] = 0.0;
_CKRFR[1105] = 0.0;
_CKRFR[1106] = 0.0;
_CKRFR[1107] = 0.0;
_CKRFR[1108] = 0.0;
_CKRFR[1109] = 0.0;
_CKRFR[1110] = 0.0;
_CKRFR[1111] = 0.0;
_CKRFR[1112] = 0.0;
_CKRFR[1113] = 0.0;
_CKRFR[1114] = 0.0;
_CKRFR[1115] = 0.0;
_CKRFR[1116] = 0.0;
_CKRFR[1117] = 0.0;
_CKRFR[1118] = 0.0;
_CKRFR[1119] = 0.0;
_CKRFR[1120] = 0.0;
_CKRFR[1121] = 0.0;
_CKRFR[1122] = 0.0;
_CKRFR[1123] = 0.0;
_CKRFR[1124] = 0.0;
_CKRFR[1125] = 0.0;
_CKRFR[1126] = 0.0;
_CKRFR[1127] = 0.0;
_CKRFR[1128] = 0.0;
_CKRFR[1129] = 0.0;
_CKRFR[1130] = 0.0;
_CKRFR[1131] = 0.0;
_CKRFR[1132] = 0.0;
_CKRFR[1133] = 0.0;
_CKRFR[1134] = 0.0;
_CKRFR[1135] = 0.0;
_CKRFR[1136] = 0.0;
_CKRFR[1137] = 0.0;
_CKRFR[1138] = 0.0;
_CKRFR[1139] = 0.0;
_CKRFR[1140] = 0.0;
_CKRFR[1141] = 0.0;
_CKRFR[1142] = 0.0;
_CKRFR[1143] = 0.0;
_CKRFR[1144] = 0.0;
_CKRFR[1145] = 0.0;
_CKRFR[1146] = 0.0;
_CKRFR[1147] = 0.0;
_CKRFR[1148] = 0.0;
_CKRFR[1149] = 0.0;
_CKRFR[1150] = 0.0;
_CKRFR[1151] = 0.0;
_CKRFR[1152] = 0.0;
_CKRFR[1153] = 0.0;
_CKRFR[1154] = 0.0;
_CKRFR[1155] = 0.0;
_CKRFR[1156] = 0.0;
_CKRFR[1157] = 0.0;
_CKRFR[1158] = 0.0;
_CKRFR[1159] = 0.0;
_CKRFR[1160] = 0.0;
_CKRFR[1161] = 0.0;
_CKRFR[1162] = 0.0;
_CKRFR[1163] = 0.0;
_CKRFR[1164] = 0.0;
_CKRFR[1165] = 0.0;
_CKRFR[1166] = 0.0;
_CKRFR[1167] = 0.0;
_CKRFR[1168] = 0.0;
_CKRFR[1169] = 0.0;
_CKRFR[1170] = 0.0;
_CKRFR[1171] = 0.0;
_CKRFR[1172] = 0.0;
_CKRFR[1173] = 0.0;
_CKRFR[1174] = 0.0;
_CKRFR[1175] = 0.0;
_CKRFR[1176] = 0.0;
_CKRFR[1177] = 0.0;
_CKRFR[1178] = 0.0;
_CKRFR[1179] = 0.0;
_CKRFR[1180] = 0.0;
_CKRFR[1181] = 0.0;
_CKRFR[1182] = 0.0;
_CKRFR[1183] = 0.0;
_CKRFR[1184] = 0.0;
_CKRFR[1185] = 0.0;
_CKRFR[1186] = 0.0;
_CKRFR[1187] = 0.0;
_CKRFR[1188] = 0.0;
_CKRFR[1189] = 0.0;
_CKRFR[1190] = 0.0;
_CKRFR[1191] = 0.0;
_CKRFR[1192] = 0.0;
_CKRFR[1193] = 0.0;
_CKRFR[1194] = 0.0;
_CKRFR[1195] = 0.0;
_CKRFR[1196] = 0.0;
_CKRFR[1197] = 0.0;
_CKRFR[1198] = 0.0;
_CKRFR[1199] = 0.0;
_CKRFR[1200] = 0.0;
_CKRFR[1201] = 0.0;
_CKRFR[1202] = 0.0;
_CKRFR[1203] = 0.0;
_CKRFR[1204] = 0.0;
_CKRFR[1205] = 0.0;
_CKRFR[1206] = 0.0;
_CKRFR[1207] = 0.0;
_CKRFR[1208] = 0.0;
_CKRFR[1209] = 0.0;
_CKRFR[1210] = 0.0;
_CKRFR[1211] = 0.0;
_CKRFR[1212] = 0.0;
_CKRFR[1213] = 0.0;
_CKRFR[1214] = 0.0;
_CKRFR[1215] = 0.0;
_CKRFR[1216] = 0.0;
_CKRFR[1217] = 0.0;
_CKRFR[1218] = 0.0;
_CKRFR[1219] = 0.0;
_CKRFR[1220] = 0.0;
_CKRFR[1221] = 0.0;
_CKRFR[1222] = 0.0;
_CKRFR[1223] = 0.0;
_CKRFR[1224] = 0.0;
_CKRFR[1225] = 0.0;
_CKRFR[1226] = 0.0;
_CKRFR[1227] = 0.0;
_CKRFR[1228] = 0.0;
_CKRFR[1229] = 0.0;
_CKRFR[1230] = 0.0;
_CKRFR[1231] = 0.0;
_CKRFR[1232] = 0.0;
_CKRFR[1233] = 0.0;
_CKRFR[1234] = 0.0;
_CKRFR[1235] = 0.0;
_CKRFR[1236] = 0.0;
_CKRFR[1237] = 0.0;
_CKRFR[1238] = 0.0;
_CKRFR[1239] = 0.0;
_CKRFR[1240] = 0.0;
_CKRFR[1241] = 0.0;
_CKRFR[1242] = 0.0;
_CKRFR[1243] = 0.0;
_CKRFR[1244] = 0.0;
_CKRFR[1245] = 0.0;
_CKRFR[1246] = 0.0;
_CKRFR[1247] = 0.0;
_CKRFR[1248] = 0.0;
_CKRFR[1249] = 0.0;
_CKRFR[1250] = 0.0;
_CKRFR[1251] = 0.0;
_CKRFR[1252] = 0.0;
_CKRFR[1253] = 0.0;
_CKRFR[1254] = 0.0;
_CKRFR[1255] = 0.0;
_CKRFR[1256] = 0.0;
_CKRFR[1257] = 0.0;
_CKRFR[1258] = 0.0;
_CKRFR[1259] = 0.0;
_CKRFR[1260] = 0.0;
_CKRFR[1261] = 0.0;
_CKRFR[1262] = 0.0;
_CKRFR[1263] = 0.0;
_CKRFR[1264] = 0.0;
_CKRFR[1265] = 0.0;
_CKRFR[1266] = 0.0;
_CKRFR[1267] = 0.0;
_CKRFR[1268] = 0.0;
_CKRFR[1269] = 0.0;
_CKRFR[1270] = 0.0;
_CKRFR[1271] = 0.0;
_CKRFR[1272] = 0.0;
_CKRFR[1273] = 0.0;
_CKRFR[1274] = 0.0;
_CKRFR[1275] = 0.0;
_CKRFR[1276] = 0.0;
_CKRFR[1277] = 0.0;
_CKRFR[1278] = 0.0;
_CKRFR[1279] = 0.0;
_CKRFR[1280] = 0.0;
_CKRFR[1281] = 0.0;
_CKRFR[1282] = 0.0;
_CKRFR[1283] = 0.0;
_CKRFR[1284] = 0.0;
_CKRFR[1285] = 0.0;
_CKRFR[1286] = 0.0;
_CKRFR[1287] = 0.0;
_CKRFR[1288] = 0.0;
_CKRFR[1289] = 0.0;
_CKRFR[1290] = 0.0;
_CKRFR[1291] = 0.0;
_CKRFR[1292] = 0.0;
_CKRFR[1293] = 0.0;
_CKRFR[1294] = 0.0;
_CKRFR[1295] = 0.0;
_CKRFR[1296] = 0.0;
_CKRFR[1297] = 0.0;
_CKRFR[1298] = 0.0;
_CKRFR[1299] = 0.0;
_CKRFR[1300] = 0.0;
_CKRFR[1301] = 0.0;
_CKRFR[1302] = 0.0;
_CKRFR[1303] = 0.0;
_CKRFR[1304] = 0.0;
_CKRFR[1305] = 0.0;
_CKRFR[1306] = 0.0;
_CKRFR[1307] = 0.0;
_CKRFR[1308] = 0.0;
_CKRFR[1309] = 0.0;
_CKRFR[1310] = 0.0;
_CKRFR[1311] = 0.0;
_CKRFR[1312] = 0.0;
_CKRFR[1313] = 0.0;
_CKRFR[1314] = 0.0;
_CKRFR[1315] = 0.0;
_CKRFR[1316] = 0.0;
_CKRFR[1317] = 0.0;
_CKRFR[1318] = 0.0;
_CKRFR[1319] = 0.0;
_CKRFR[1320] = 0.0;
_CKRFR[1321] = 0.0;
_CKRFR[1322] = 0.0;
_CKRFR[1323] = 0.0;
_CKRFR[1324] = 0.0;
_CKRFR[1325] = 0.0;
_CKRFR[1326] = 0.0;
_CKRFR[1327] = 0.0;
_CKRFR[1328] = 0.0;
_CKRFR[1329] = 0.0;
_CKRFR[1330] = 0.0;
_CKRFR[1331] = 0.0;
_CKRFR[1332] = 0.0;
_CKRFR[1333] = 0.0;
_CKRFR[1334] = 0.0;
_CKRFR[1335] = 0.0;
_CKRFR[1336] = 0.0;
_CKRFR[1337] = 0.0;
_CKRFR[1338] = 0.0;
_CKRFR[1339] = 0.0;
_CKRFR[1340] = 0.0;
_CKRFR[1341] = 0.0;
_CKRFR[1342] = 0.0;
_CKRFR[1343] = 0.0;
_CKRFR[1344] = 0.0;
_CKRFR[1345] = 0.0;
_CKRFR[1346] = 0.0;
_CKRFR[1347] = 0.0;
_CKRFR[1348] = 0.0;
_CKRFR[1349] = 0.0;
_CKRFR[1350] = 0.0;
_CKRFR[1351] = 0.0;
_CKRFR[1352] = 0.0;
_CKRFR[1353] = 0.0;
_CKRFR[1354] = 0.0;
_CKRFR[1355] = 0.0;
_CKRFR[1356] = 0.0;
_CKRFR[1357] = 0.0;
_CKRFR[1358] = 0.0;
_CKRFR[1359] = 0.0;
_CKRFR[1360] = 0.0;
_CKRFR[1361] = 0.0;
_CKRFR[1362] = 0.0;
_CKRFR[1363] = 0.0;
_CKRFR[1364] = 0.0;
_CKRFR[1365] = 0.0;
_CKRFR[1366] = 0.0;
_CKRFR[1367] = 0.0;
_CKRFR[1368] = 0.0;
_CKRFR[1369] = 0.0;
_CKRFR[1370] = 0.0;
_CKRFR[1371] = 0.0;
_CKRFR[1372] = 0.0;
_CKRFR[1373] = 0.0;
_CKRFR[1374] = 0.0;
_CKRFR[1375] = 0.0;
_CKRFR[1376] = 0.0;
_CKRFR[1377] = 0.0;
_CKRFR[1378] = 0.0;
_CKRFR[1379] = 0.0;
_CKRFR[1380] = 0.0;
_CKRFR[1381] = 0.0;
_CKRFR[1382] = 0.0;
_CKRFR[1383] = 0.0;
_CKRFR[1384] = 0.0;
_CKRFR[1385] = 0.0;
_CKRFR[1386] = 0.0;
_CKRFR[1387] = 0.0;
_CKRFR[1388] = 0.0;
_CKRFR[1389] = 0.0;
_CKRFR[1390] = 0.0;
_CKRFR[1391] = 0.0;
_CKRFR[1392] = 0.0;
_CKRFR[1393] = 0.0;
_CKRFR[1394] = 0.0;
_CKRFR[1395] = 0.0;
_CKRFR[1396] = 0.0;
_CKRFR[1397] = 0.0;
_CKRFR[1398] = 0.0;
_CKRFR[1399] = 0.0;
_CKRFR[1400] = 0.0;
_CKRFR[1401] = 0.0;
_CKRFR[1402] = 0.0;
_CKRFR[1403] = 0.0;
_CKRFR[1404] = 0.0;
_CKRFR[1405] = 0.0;
_CKRFR[1406] = 0.0;
_CKRFR[1407] = 0.0;
_CKRFR[1408] = 0.0;
_CKRFR[1409] = 0.0;
_CKRFR[1410] = 0.0;
_CKRFR[1411] = 0.0;
_CKRFR[1412] = 0.0;
_CKRFR[1413] = 0.0;
_CKRFR[1414] = 0.0;
_CKRFR[1415] = 0.0;
_CKRFR[1416] = 0.0;
_CKRFR[1417] = 0.0;
_CKRFR[1418] = 0.0;
_CKRFR[1419] = 0.0;
_CKRFR[1420] = 0.0;
_CKRFR[1421] = 0.0;
_CKRFR[1422] = 0.0;
_CKRFR[1423] = 0.0;
_CKRFR[1424] = 0.0;
_CKRFR[1425] = 0.0;
_CKRFR[1426] = 0.0;
_CKRFR[1427] = 0.0;
_CKRFR[1428] = 0.0;
_CKRFR[1429] = 0.0;
_CKRFR[1430] = 0.0;
_CKRFR[1431] = 0.0;
_CKRFR[1432] = 0.0;
_CKRFR[1433] = 0.0;
_CKRFR[1434] = 0.0;
_CKRFR[1435] = 0.0;
_CKRFR[1436] = 0.0;
_CKRFR[1437] = 0.0;
_CKRFR[1438] = 0.0;
_CKRFR[1439] = 0.0;
_CKRFR[1440] = 0.0;
_CKRFR[1441] = 0.0;
_CKRFR[1442] = 0.0;
_CKRFR[1443] = 0.0;
_CKRFR[1444] = 0.0;
_CKRFR[1445] = 0.0;
_CKRFR[1446] = 0.0;
_CKRFR[1447] = 0.0;
_CKRFR[1448] = 0.0;
_CKRFR[1449] = 0.0;
_CKRFR[1450] = 0.0;
_CKRFR[1451] = 0.0;
_CKRFR[1452] = 0.0;
_CKRFR[1453] = 0.0;
_CKRFR[1454] = 0.0;
_CKRFR[1455] = 0.0;
_CKRFR[1456] = 0.0;
_CKRFR[1457] = 0.0;
_CKRFR[1458] = 0.0;
_CKRFR[1459] = 0.0;
_CKRFR[1460] = 0.0;
_CKRFR[1461] = 0.0;
_CKRFR[1462] = 0.0;
_CKRFR[1463] = 0.0;
_CKRFR[1464] = 0.0;
_CKRFR[1465] = 0.0;
_CKRFR[1466] = 0.0;
_CKRFR[1467] = 0.0;
_CKRFR[1468] = 0.0;
_CKRFR[1469] = 0.0;
_CKRFR[1470] = 0.0;
_CKRFR[1471] = 0.0;
_CKRFR[1472] = 0.0;
_CKRFR[1473] = 0.0;
_CKRFR[1474] = 0.0;
_CKRFR[1475] = 0.0;
_CKRFR[1476] = 0.0;
_CKRFR[1477] = 0.0;
_CKRFR[1478] = 0.0;
_CKRFR[1479] = 0.0;
_CKRFR[1480] = 0.0;
_CKRFR[1481] = 0.0;
_CKRFR[1482] = 0.0;
_CKRFR[1483] = 0.0;
_CKRFR[1484] = 0.0;
_CKRFR[1485] = 0.0;
_CKRFR[1486] = 0.0;
_CKRFR[1487] = 0.0;
_CKRFR[1488] = 0.0;
_CKRFR[1489] = 0.0;
_CKRFR[1490] = 0.0;
_CKRFR[1491] = 0.0;
_CKRFR[1492] = 0.0;
_CKRFR[1493] = 0.0;
_CKRFR[1494] = 0.0;
_CKRFR[1495] = 0.0;
_CKRFR[1496] = 0.0;
_CKRFR[1497] = 0.0;
_CKRFR[1498] = 0.0;
_CKRFR[1499] = 0.0;
_CKRFR[1500] = 0.0;
_CKRFR[1501] = 0.0;
_CKRFR[1502] = 0.0;
_CKRFR[1503] = 0.0;
_CKRFR[1504] = 0.0;
_CKRFR[1505] = 0.0;
_CKRFR[1506] = 0.0;
_CKRFR[1507] = 0.0;
_CKRFR[1508] = 0.0;
_CKRFR[1509] = 0.0;
_CKRFR[1510] = 0.0;
_CKRFR[1511] = 0.0;
_CKRFR[1512] = 0.0;
_CKRFR[1513] = 0.0;
_CKRFR[1514] = 0.0;
_CKRFR[1515] = 0.0;
_CKRFR[1516] = 0.0;
_CKRFR[1517] = 0.0;
_CKRFR[1518] = 0.0;
_CKRFR[1519] = 0.0;
_CKRFR[1520] = 0.0;
_CKRFR[1521] = 0.0;
_CKRFR[1522] = 0.0;
_CKRFR[1523] = 0.0;
_CKRFR[1524] = 0.0;
_CKRFR[1525] = 0.0;
_CKRFR[1526] = 0.0;
_CKRFR[1527] = 0.0;
_CKRFR[1528] = 0.0;
_CKRFR[1529] = 0.0;
_CKRFR[1530] = 0.0;
_CKRFR[1531] = 0.0;
_CKRFR[1532] = 0.0;
_CKRFR[1533] = 0.0;
_CKRFR[1534] = 0.0;
_CKRFR[1535] = 0.0;
_CKRFR[1536] = 0.0;
_CKRFR[1537] = 0.0;
_CKRFR[1538] = 0.0;
_CKRFR[1539] = 0.0;
_CKRFR[1540] = 0.0;
_CKRFR[1541] = 0.0;
_CKRFR[1542] = 0.0;
_CKRFR[1543] = 0.0;
_CKRFR[1544] = 0.0;
_CKRFR[1545] = 0.0;
_CKRFR[1546] = 0.0;
_CKRFR[1547] = 0.0;
_CKRFR[1548] = 0.0;
_CKRFR[1549] = 0.0;
_CKRFR[1550] = 0.0;
_CKRFR[1551] = 0.0;
_CKRFR[1552] = 0.0;
_CKRFR[1553] = 0.0;
_CKRFR[1554] = 0.0;
_CKRFR[1555] = 0.0;
_CKRFR[1556] = 0.0;
_CKRFR[1557] = 0.0;
_CKRFR[1558] = 0.0;
_CKRFR[1559] = 0.0;
_CKRFR[1560] = 0.0;
_CKRFR[1561] = 0.0;
_CKRFR[1562] = 0.0;
_CKRFR[1563] = 0.0;
_CKRFR[1564] = 0.0;
_CKRFR[1565] = 0.0;
_CKRFR[1566] = 0.0;
_CKRFR[1567] = 0.0;
_CKRFR[1568] = 0.0;
_CKRFR[1569] = 0.0;
_CKRFR[1570] = 0.0;
_CKRFR[1571] = 0.0;
_CKRFR[1572] = 0.0;
_CKRFR[1573] = 0.0;
_CKRFR[1574] = 0.0;
_CKRFR[1575] = 0.0;
_CKRFR[1576] = 0.0;
_CKRFR[1577] = 0.0;
_CKRFR[1578] = 0.0;
_CKRFR[1579] = 0.0;
_CKRFR[1580] = 0.0;
_CKRFR[1581] = 0.0;
_CKRFR[1582] = 0.0;
_CKRFR[1583] = 0.0;
_CKRFR[1584] = 0.0;
_CKRFR[1585] = 0.0;
_CKRFR[1586] = 0.0;
_CKRFR[1587] = 0.0;
_CKRFR[1588] = 0.0;
_CKRFR[1589] = 0.0;
_CKRFR[1590] = 0.0;
_CKRFR[1591] = 0.0;
_CKRFR[1592] = 0.0;
_CKRFR[1593] = 0.0;
_CKRFR[1594] = 0.0;
_CKRFR[1595] = 0.0;
_CKRFR[1596] = 0.0;
_CKRFR[1597] = 0.0;
_CKRFR[1598] = 0.0;
_CKRFR[1599] = 0.0;
_CKRFR[1600] = 0.0;
_CKRFR[1601] = 0.0;
_CKRFR[1602] = 0.0;
_CKRFR[1603] = 0.0;
_CKRFR[1604] = 0.0;
_CKRFR[1605] = 0.0;
_CKRFR[1606] = 0.0;
_CKRFR[1607] = 0.0;
_CKRFR[1608] = 0.0;
_CKRFR[1609] = 0.0;
_CKRFR[1610] = 0.0;
_CKRFR[1611] = 0.0;
_CKRFR[1612] = 0.0;
_CKRFR[1613] = 0.0;
_CKRFR[1614] = 0.0;
_CKRFR[1615] = 0.0;
_CKRFR[1616] = 0.0;
_CKRFR[1617] = 0.0;
_CKRFR[1618] = 0.0;
_CKRFR[1619] = 0.0;
_CKRFR[1620] = 0.0;
_CKRFR[1621] = 0.0;
_CKRFR[1622] = 0.0;
_CKRFR[1623] = 0.0;
_CKRFR[1624] = 0.0;
_CKRFR[1625] = 0.0;
_CKRFR[1626] = 0.0;
_CKRFR[1627] = 0.0;
_CKRFR[1628] = 0.0;
_CKRFR[1629] = 0.0;
_CKRFR[1630] = 0.0;
_CKRFR[1631] = 0.0;
_CKRFR[1632] = 0.0;
_CKRFR[1633] = 0.0;
_CKRFR[1634] = 0.0;
_CKRFR[1635] = 0.0;
_CKRFR[1636] = 0.0;
_CKRFR[1637] = 0.0;
_CKRFR[1638] = 0.0;
_CKRFR[1639] = 0.0;
_CKRFR[1640] = 0.0;
_CKRFR[1641] = 0.0;
_CKRFR[1642] = 0.0;
_CKRFR[1643] = 0.0;
_CKRFR[1644] = 0.0;
_CKRFR[1645] = 0.0;
_CKRFR[1646] = 0.0;
_CKRFR[1647] = 0.0;
_CKRFR[1648] = 0.0;
_CKRFR[1649] = 0.0;
_CKRFR[1650] = 0.0;
_CKRFR[1651] = 0.0;
_CKRFR[1652] = 0.0;
_CKRFR[1653] = 0.0;
_CKRFR[1654] = 0.0;
_CKRFR[1655] = 0.0;
_CKRFR[1656] = 0.0;
_CKRFR[1657] = 0.0;
_CKRFR[1658] = 0.0;
_CKRFR[1659] = 0.0;
_CKRFR[1660] = 0.0;
_CKRFR[1661] = 0.0;
_CKRFR[1662] = 0.0;
_CKRFR[1663] = 0.0;
_CKRFR[1664] = 0.0;
_CKRFR[1665] = 0.0;
_CKRFR[1666] = 0.0;
_CKRFR[1667] = 0.0;
_CKRFR[1668] = 0.0;
_CKRFR[1669] = 0.0;
_CKRFR[1670] = 0.0;
_CKRFR[1671] = 0.0;
_CKRFR[1672] = 0.0;
_CKRFR[1673] = 0.0;
_CKRFR[1674] = 0.0;
_CKRFR[1675] = 0.0;
_CKRFR[1676] = 0.0;
_CKRFR[1677] = 0.0;
_CKRFR[1678] = 0.0;
_CKRFR[1679] = 0.0;
_CKRFR[1680] = 0.0;
_CKRFR[1681] = 0.0;
_CKRFR[1682] = 0.0;
_CKRFR[1683] = 0.0;
_CKRFR[1684] = 0.0;
_CKRFR[1685] = 0.0;
_CKRFR[1686] = 0.0;
_CKRFR[1687] = 0.0;
_CKRFR[1688] = 0.0;
_CKRFR[1689] = 0.0;
_CKRFR[1690] = 0.0;
_CKRFR[1691] = 0.0;
_CKRFR[1692] = 0.0;
_CKRFR[1693] = 0.0;
_CKRFR[1694] = 0.0;
_CKRFR[1695] = 0.0;
_CKRFR[1696] = 0.0;
_CKRFR[1697] = 0.0;
_CKRFR[1698] = 0.0;
_CKRFR[1699] = 0.0;
_CKRFR[1700] = 0.0;
_CKRFR[1701] = 0.0;
_CKRFR[1702] = 0.0;
_CKRFR[1703] = 0.0;
_CKRFR[1704] = 0.0;
_CKRFR[1705] = 0.0;
_CKRFR[1706] = 0.0;
_CKRFR[1707] = 0.0;
_CKRFR[1708] = 0.0;
_CKRFR[1709] = 0.0;
_CKRFR[1710] = 0.0;
_CKRFR[1711] = 0.0;
_CKRFR[1712] = 0.0;
_CKRFR[1713] = 0.0;
_CKRFR[1714] = 0.0;
_CKRFR[1715] = 0.0;
_CKRFR[1716] = 0.0;
_CKRFR[1717] = 0.0;
_CKRFR[1718] = 0.0;
_CKRFR[1719] = 0.0;
_CKRFR[1720] = 0.0;
_CKRFR[1721] = 0.0;
_CKRFR[1722] = 0.0;
_CKRFR[1723] = 0.0;
_CKRFR[1724] = 0.0;
_CKRFR[1725] = 0.0;
_CKRFR[1726] = 0.0;
_CKRFR[1727] = 0.0;
_CKRFR[1728] = 0.0;
_CKRFR[1729] = 0.0;
_CKRFR[1730] = 0.0;
_CKRFR[1731] = 0.0;
_CKRFR[1732] = 0.0;
_CKRFR[1733] = 0.0;
_CKRFR[1734] = 0.0;
_CKRFR[1735] = 0.0;
_CKRFR[1736] = 0.0;
_CKRFR[1737] = 0.0;
_CKRFR[1738] = 0.0;
_CKRFR[1739] = 0.0;
_CKRFR[1740] = 0.0;
_CKRFR[1741] = 0.0;
_CKRFR[1742] = 0.0;
_CKRFR[1743] = 0.0;
_CKRFR[1744] = 0.0;
_CKRFR[1745] = 0.0;
_CKRFR[1746] = 0.0;
_CKRFR[1747] = 0.0;
_CKRFR[1748] = 0.0;
_CKRFR[1749] = 0.0;
_CKRFR[1750] = 0.0;
_CKRFR[1751] = 0.0;
_CKRFR[1752] = 0.0;
_CKRFR[1753] = 0.0;
_CKRFR[1754] = 0.0;
_CKRFR[1755] = 0.0;
_CKRFR[1756] = 0.0;
_CKRFR[1757] = 0.0;
_CKRFR[1758] = 0.0;
_CKRFR[1759] = 0.0;
_CKRFR[1760] = 0.0;
_CKRFR[1761] = 0.0;
_CKRFR[1762] = 0.0;
_CKRFR[1763] = 0.0;
_CKRFR[1764] = 0.0;
_CKRFR[1765] = 0.0;
_CKRFR[1766] = 0.0;
_CKRFR[1767] = 0.0;
_CKRFR[1768] = 0.0;
_CKRFR[1769] = 0.0;
_CKRFR[1770] = 0.0;
_CKRFR[1771] = 0.0;
_CKRFR[1772] = 0.0;
_CKRFR[1773] = 0.0;
_CKRFR[1774] = 0.0;
_CKRFR[1775] = 0.0;
_CKRFR[1776] = 0.0;
_CKRFR[1777] = 0.0;
_CKRFR[1778] = 0.0;
_CKRFR[1779] = 0.0;
_CKRFR[1780] = 0.0;
_CKRFR[1781] = 0.0;
_CKRFR[1782] = 0.0;
_CKRFR[1783] = 0.0;
_CKRFR[1784] = 0.0;
_CKRFR[1785] = 0.0;
_CKRFR[1786] = 0.0;
_CKRFR[1787] = 0.0;
_CKRFR[1788] = 0.0;
_CKRFR[1789] = 0.0;
_CKRFR[1790] = 0.0;
_CKRFR[1791] = 0.0;
_CKRFR[1792] = 0.0;
_CKRFR[1793] = 0.0;
_CKRFR[1794] = 0.0;
_CKRFR[1795] = 0.0;
_CKRFR[1796] = 0.0;
_CKRFR[1797] = 0.0;
_CKRFR[1798] = 0.0;
_CKRFR[1799] = 0.0;
_CKRFR[1800] = 0.0;
_CKRFR[1801] = 0.0;
_CKRFR[1802] = 0.0;
_CKRFR[1803] = 0.0;
_CKRFR[1804] = 0.0;
_CKRFR[1805] = 0.0;
_CKRFR[1806] = 0.0;
_CKRFR[1807] = 0.0;
_CKRFR[1808] = 0.0;
_CKRFR[1809] = 0.0;
_CKRFR[1810] = 0.0;
_CKRFR[1811] = 0.0;
_CKRFR[1812] = 0.0;
_CKRFR[1813] = 0.0;
_CKRFR[1814] = 0.0;
_CKRFR[1815] = 0.0;
_CKRFR[1816] = 0.0;
_CKRFR[1817] = 0.0;
_CKRFR[1818] = 0.0;
_CKRFR[1819] = 0.0;
_CKRFR[1820] = 0.0;
_CKRFR[1821] = 0.0;
_CKRFR[1822] = 0.0;
_CKRFR[1823] = 0.0;
_CKRFR[1824] = 0.0;
_CKRFR[1825] = 0.0;
_CKRFR[1826] = 0.0;
_CKRFR[1827] = 0.0;
_CKRFR[1828] = 0.0;
_CKRFR[1829] = 0.0;
_CKRFR[1830] = 0.0;
_CKRFR[1831] = 0.0;
_CKRFR[1832] = 0.0;
_CKRFR[1833] = 0.0;
_CKRFR[1834] = 0.0;
_CKRFR[1835] = 0.0;
_CKRFR[1836] = 0.0;
_CKRFR[1837] = 0.0;
_CKRFR[1838] = 0.0;
_CKRFR[1839] = 0.0;
_CKRFR[1840] = 0.0;
_CKRFR[1841] = 0.0;
_CKRFR[1842] = 0.0;
_CKRFR[1843] = 0.0;
_CKRFR[1844] = 0.0;
_CKRFR[1845] = 0.0;
_CKRFR[1846] = 0.0;
_CKRFR[1847] = 0.0;
_CKRFR[1848] = 0.0;
_CKRFR[1849] = 0.0;
_CKRFR[1850] = 0.0;
_CKRFR[1851] = 0.0;
_CKRFR[1852] = 0.0;
_CKRFR[1853] = 0.0;
_CKRFR[1854] = 0.0;
_CKRFR[1855] = 0.0;
_CKRFR[1856] = 0.0;
_CKRFR[1857] = 0.0;
_CKRFR[1858] = 0.0;
_CKRFR[1859] = 0.0;
_CKRFR[1860] = 0.0;
_CKRFR[1861] = 0.0;
_CKRFR[1862] = 0.0;
_CKRFR[1863] = 0.0;
_CKRFR[1864] = 0.0;
_CKRFR[1865] = 0.0;
_CKRFR[1866] = 0.0;
_CKRFR[1867] = 0.0;
_CKRFR[1868] = 0.0;
_CKRFR[1869] = 0.0;
_CKRFR[1870] = 0.0;
_CKRFR[1871] = 0.0;
_CKRFR[1872] = 0.0;
_CKRFR[1873] = 0.0;
_CKRFR[1874] = 0.0;
_CKRFR[1875] = 0.0;
_CKRFR[1876] = 0.0;
_CKRFR[1877] = 0.0;
_CKRFR[1878] = 0.0;
_CKRFR[1879] = 0.0;
_CKRFR[1880] = 0.0;
_CKRFR[1881] = 0.0;
_CKRFR[1882] = 0.0;
_CKRFR[1883] = 0.0;
_CKRFR[1884] = 0.0;
_CKRFR[1885] = 0.0;
_CKRFR[1886] = 0.0;
_CKRFR[1887] = 0.0;
_CKRFR[1888] = 0.0;
_CKRFR[1889] = 0.0;
_CKRFR[1890] = 0.0;
_CKRFR[1891] = 0.0;
_CKRFR[1892] = 0.0;
_CKRFR[1893] = 0.0;
_CKRFR[1894] = 0.0;
_CKRFR[1895] = 0.0;
_CKRFR[1896] = 0.0;
_CKRFR[1897] = 0.0;
_CKRFR[1898] = 0.0;
_CKRFR[1899] = 0.0;
_CKRFR[1900] = 0.0;
_CKRFR[1901] = 0.0;
_CKRFR[1902] = 0.0;
_CKRFR[1903] = 0.0;
_CKRFR[1904] = 0.0;
_CKRFR[1905] = 0.0;
_CKRFR[1906] = 0.0;
_CKRFR[1907] = 0.0;
_CKRFR[1908] = 0.0;
_CKRFR[1909] = 0.0;
_CKRFR[1910] = 0.0;
_CKRFR[1911] = 0.0;
_CKRFR[1912] = 0.0;
_CKRFR[1913] = 0.0;
_CKRFR[1914] = 0.0;
_CKRFR[1915] = 0.0;
_CKRFR[1916] = 0.0;
_CKRFR[1917] = 0.0;
_CKRFR[1918] = 0.0;
_CKRFR[1919] = 0.0;
_CKRFR[1920] = 0.0;
_CKRFR[1921] = 0.0;
_CKRFR[1922] = 0.0;
_CKRFR[1923] = 0.0;
_CKRFR[1924] = 0.0;
_CKRFR[1925] = 0.0;
_CKRFR[1926] = 0.0;
_CKRFR[1927] = 0.0;
_CKRFR[1928] = 0.0;
_CKRFR[1929] = 0.0;
_CKRFR[1930] = 0.0;
_CKRFR[1931] = 0.0;
_CKRFR[1932] = 0.0;
_CKRFR[1933] = 0.0;
_CKRFR[1934] = 0.0;
_CKRFR[1935] = 0.0;

return _CKRFR;
}
