/*----------CKFRR.c lib3D_MEC exported-----------*/

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

#include "CKFRR.h"

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
double atom3398;
double atom3400;
double atom3436;
double atom3444;
double atom3445;
double atom66382;
double atom3446;
double atom1017;
double atom1497;
double atom22450;
double atom1018;
double atom1019;
double atom1016;
double atom1021;
double atom2733;
double atom22449;
double atom1496;
double atom22456;
double atom0;
double atom1173;
double atom1174;
double atom22460;
double atom1194;
double atom1175;
double atom22459;
double atom1023;
double atom2741;
double atom22452;
double atom1172;
double atom22453;
double atom1195;
double atom22475;
double atom1176;
double atom3229;
double atom3235;
double atom1512;
double atom3236;
double atom1530;
double atom1533;
double atom1514;
double atom1515;
double atom684;
double atom1551;
double atom683;
double atom1548;
double atom1607;
double atom1610;
double atom3238;
double atom1702;
double atom3241;
double atom3239;
double atom3248;
double atom3245;
double atom3260;
double atom3259;
double atom1022;
double atom3253;
double atom22481;
double atom58407;
double atom66220;
double atom1177;
double atom58406;
double atom66222;
double atom1178;
double atom1179;
double atom1185;
double atom1187;
double atom1184;
double atom1500;
double atom1521;
double atom1503;
double atom1539;
double atom1536;
double atom1598;
double atom1595;
double atom1518;
double atom22465;
double atom22479;
double atom58417;
double atom66231;
double atom1181;
double atom1191;
double atom1193;
double atom1180;
double atom1190;
double atom22470;
double atom1506;
double atom1527;
double atom1509;
double atom1542;
double atom1545;
double atom1604;
double atom1601;
double atom1524;
double atom22480;
double atom58414;
double atom66233;
double atom66236;
double atom66238;
double atom3814;
double atom60839;
double atom44188;
double atom60833;
double atom44063;
double atom66247;
double atom66249;
double atom9499;
double atom58423;
double atom58429;
double atom58427;
double atom58435;
double atom58431;
double atom41956;
double atom40896;
double atom64448;
double atom40899;
double atom64442;
double atom64445;
double atom64461;
double atom64453;
double atom58438;
double atom66252;
double atom64450;
double atom66257;
double atom58443;
double atom66258;
double atom66260;
double atom40804;
double atom40806;
double atom64468;
double atom64480;
double atom40875;
double atom44126;
double atom44128;
double atom44216;
double atom64471;
double atom44131;
double atom66269;
double atom66271;
double atom6041;
double atom6036;
double atom6037;
double atom6044;
double atom9508;
double atom66274;
double atom43497;
double atom66275;
double atom66278;
double atom43485;
double atom66280;
double atom66282;
double atom66286;
double atom66288;
double atom66292;
double atom66296;
double atom66298;
double atom66305;
double atom66307;
double atom66309;
double atom66383;
double atom3332;
double atom3333;
double atom3334;
double atom3403;
double atom3449;
double atom66384;
double atom3450;
double atom58410;
double atom66316;
double atom3404;
double atom3405;
double atom3438;
double atom3439;
double atom3440;
double atom66386;
double atom66357;
double atom66387;
double atom58420;
double atom66323;
double atom3441;
double atom66362;
double atom66324;
double atom66366;
double atom44067;
double atom66331;
double atom9548;
double atom66371;
double atom58448;
double atom66334;
double atom66338;
double atom66495;
double atom66376;
double atom44137;
double atom66345;
double atom9557;
double atom66348;
double atom66354;
double atom66381;
double atom66388;
double atom66389;
double atom66530;
double atom40803;
double atom40902;
double atom41903;
double atom41900;
double atom43488;
double atom40898;
double atom43476;
double atom60330;
double atom60325;
double atom60337;
double atom60341;
double atom66390;
double atom66140;
double atom22397;
double atom66146;
double atom66153;
double atom66155;
double atom66393;
double atom66395;
double atom66396;
double atom66398;
double atom66572;
double atom40903;
double atom41907;
double atom41905;
double atom43491;
double atom43479;
double atom60359;
double atom60364;
double atom60371;
double atom60375;
double atom66399;
double atom66161;
double atom66166;
double atom66402;
double atom66405;
double atom66622;
double atom60392;
double atom60396;
double atom60402;
double atom60406;
double atom66406;
double atom66177;
double atom66172;
double atom66409;
double atom66412;
double atom66672;
double atom43482;
double atom43494;
double atom60426;
double atom60422;
double atom60432;
double atom60436;
double atom66413;
double atom66183;
double atom66188;
double atom66416;
double atom66419;
double atom66722;
double atom66420;
double atom66421;
double atom66422;
double atom66772;
double atom60457;
double atom60458;
double atom60453;
double atom66423;
double atom60461;
double atom66194;
double atom66425;
double atom66426;
double atom66428;
double atom66429;
double atom66822;
double atom60473;
double atom60483;
double atom60487;
double atom60477;
double atom66430;
double atom66200;
double atom66203;
double atom66433;
double atom66436;
double atom66872;
double atom66437;
double atom66438;
double atom66439;
double atom66922;
double atom66440;
double atom66209;
double atom66442;
double atom66444;
double atom66972;
double atom60512;
double atom66445;
double atom66215;
double atom66448;
double atom66451;
double atom67022;

double * _CKFRR = NULL;
void Init_CKFRR ( ) 
{
    _CKFRR = malloc ( CKFRR_n_rows * CKFRR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKFRR_n_rows * CKFRR_n_cols ; i++ ) {_CKFRR[i]=0.0;}
  }
}

void Done_CKFRR ( ) 
{
if (_CKFRR != NULL) 
free (_CKFRR ); 
_CKFRR = NULL; 
}


double * CKFRR ()
{
if ( _CKFRR == NULL )
 {
    _CKFRR = malloc ( CKFRR_n_rows * CKFRR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKFRR_n_rows * CKFRR_n_cols ; i++ ) {_CKFRR[i]=0.0;}
  }
 }

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
atom3398 =  5.0000000000000000e-01*1.0/atom3368*atom3389*L_RAIL+5.0000000000000000e-01*atom3365*L_RAIL*atom3394+1.0;
atom3400 =  -5.0000000000000000e-01*L_RAIL*atom3394+atom3365;
atom3436 = (atom3398*atom3398);
atom3444 = pow( (atom3400*atom3400)+atom3436,-(1.0/2.0));
atom3445 = atom3444*atom3398;
atom66382 = -bFRR*epsiFRR*G_elastic*C11FRR*atom3445*aFRR;
atom3446 = atom3444*atom3400;
atom1017 = sin(aFBOG);
atom1497 = sin(cFSLD);
atom22450 = -zFWHSR*atom1017;
atom1018 = cos(bFBOG);
atom1019 = sin(bFBOG);
atom1016 = cos(aFBOG);
atom1021 = atom1019*atom1016;
atom2733 = atom1018*L_OBOG_OWHS;
atom22449 =  zFWHSR*atom1021-atom2733;
atom1496 = cos(cFSLD);
atom22456 =  atom22449*atom1496-atom1497*atom22450;
atom0 = -(1.0/2.0)*L_WAG;
atom1173 = sin(bWAG);
atom1174 = cos(aWAG);
atom22460 =  atom22456-atom0;
atom1194 = -atom1173*atom1174;
atom1175 = sin(aWAG);
atom22459 =  atom22450*atom1496+atom1497*atom22449;
atom1023 = atom1018*atom1016;
atom2741 = -L_OBOG_OWHS*atom1019;
atom22452 = -atom2741+zFWHSR*atom1023;
atom1172 = cos(bWAG);
atom22453 =  zFBOG+atom22452;
atom1195 = atom1172*atom1174;
atom22475 =  atom22460*atom1194+atom22453*atom1195+atom1175*atom22459;
atom1176 = cos(cWAG);
atom3229 =  uW_FRR-lW_FRR;
atom3235 =  atom3229*( cW_FRR+atom3229*( bW_FRR+atom3229*aW_FRR))+dW_FRR;
atom1512 =  atom1194*atom1496+atom1497*atom1175;
atom3236 = -sin(thetaW_FRR)*atom3235;
atom1530 = -atom1019*atom1195+atom1018*atom1512;
atom1533 =  atom1018*atom1195+atom1019*atom1512;
atom1514 = atom1175*atom1496;
atom1515 =  atom1514-atom1497*atom1194;
atom684 = sin(aFWHSR);
atom1551 = -atom1515*atom1017+atom1016*atom1533;
atom683 = cos(aFWHSR);
atom1548 =  atom1533*atom1017+atom1515*atom1016;
atom1607 =  atom683*atom1548+atom684*atom1551;
atom1610 = -atom684*atom1548+atom683*atom1551;
atom3238 = atom3235*cos(thetaW_FRR);
atom1702 = -5.0000000000000000e-01*L_WHS;
atom3241 =  atom684*atom1702+zFWHSR;
atom3239 = atom683*atom1702;
atom3248 =  atom3239*atom1016-atom3241*atom1017;
atom3245 =  atom3239*atom1019*atom1017-atom2733+atom3241*atom1021;
atom3260 = -atom1497*atom3248+atom3245*atom1496-atom0;
atom3259 =  atom1497*atom3245+atom3248*atom1496;
atom1022 = atom1018*atom1017;
atom3253 = -atom2741+zFBOG+atom3241*atom1023+atom3239*atom1022;
atom22481 =  atom1175*atom3259+atom1610*atom3238-atom22475+atom1194*atom3260+atom1607*uW_FRR+atom3253*atom1195+atom3236*atom1530;
atom58407 = -atom22475*atom1176;
atom66220 =  atom58407-atom1176*atom22481;
atom1177 = sin(cWAG);
atom58406 = atom22475*atom1177;
atom66222 =  ( atom58406+atom1177*atom22481)*atom3445+atom3446*atom66220;
atom1178 = -atom1177*atom1174;
atom1179 = atom1175*atom1177;
atom1185 = atom1176*atom1173;
atom1187 =  atom1172*atom1179+atom1185;
atom1184 =  atom1172*atom1176-atom1173*atom1179;
atom1500 =  atom1496*atom1184+atom1497*atom1178;
atom1521 =  atom1019*atom1500+atom1018*atom1187;
atom1503 =  atom1496*atom1178-atom1497*atom1184;
atom1539 = -atom1503*atom1017+atom1016*atom1521;
atom1536 =  atom1521*atom1017+atom1503*atom1016;
atom1598 =  atom683*atom1539-atom684*atom1536;
atom1595 =  atom684*atom1539+atom683*atom1536;
atom1518 =  atom1018*atom1500-atom1019*atom1187;
atom22465 =  atom22453*atom1187+atom1178*atom22459+atom22460*atom1184;
atom22479 = -atom22465+atom3260*atom1184+atom3253*atom1187+atom3236*atom1518+uW_FRR*atom1595+atom3259*atom1178+atom1598*atom3238;
atom58417 = -atom22475*atom1178+atom22465*atom1175;
atom66231 =  atom1175*atom22479+atom58417-atom1178*atom22481;
atom1181 = -atom1175*atom1176;
atom1191 = atom1177*atom1173;
atom1193 =  atom1191+atom1172*atom1181;
atom1180 = atom1176*atom1174;
atom1190 = -atom1181*atom1173+atom1172*atom1177;
atom22470 =  atom22460*atom1190+atom1180*atom22459+atom1193*atom22453;
atom1506 =  atom1190*atom1496+atom1497*atom1180;
atom1527 =  atom1019*atom1506+atom1193*atom1018;
atom1509 =  atom1180*atom1496-atom1497*atom1190;
atom1542 =  atom1016*atom1509+atom1527*atom1017;
atom1545 =  atom1527*atom1016-atom1017*atom1509;
atom1604 =  atom683*atom1545-atom684*atom1542;
atom1601 =  atom683*atom1542+atom684*atom1545;
atom1524 = -atom1193*atom1019+atom1018*atom1506;
atom22480 =  atom1193*atom3253+atom3236*atom1524+atom1604*atom3238+atom1180*atom3259+atom1190*atom3260-atom22470+uW_FRR*atom1601;
atom58414 = -atom1175*atom22470+atom1180*atom22475;
atom66233 =  atom3446*atom66231+( atom58414+atom1180*atom22481-atom1175*atom22480)*atom3445;
atom66236 =  atom22465+atom22479;
atom66238 =  atom3446*atom66236-( atom22470+atom22480)*atom3445;
atom3814 = -atom1175*atom1172;
atom60839 =  atom1191+atom1176*atom3814;
atom44188 = -atom1184*atom22459+atom22456*atom1178;
atom60833 = -atom3814*atom1177+atom1185;
atom44063 =  atom1180*atom22456-atom1190*atom22459;
atom66247 =  atom44063-atom60833*atom22481+atom1195*atom22479;
atom66249 =  atom3445*( atom44188+atom60839*atom22481-atom1195*atom22480)+atom66247*atom3446;
atom9499 =  atom3445*atom1187+atom1193*atom3446;
atom58423 = atom1018*atom22450;
atom58429 = -atom1019*atom22450;
atom58427 = -atom1018*atom22452-atom1019*atom22449;
atom58435 = -atom1496*atom58429-atom1497*atom58427;
atom58431 =  atom58427*atom1496-atom1497*atom58429;
atom41956 = atom1018*atom1496;
atom40896 = -atom1019*atom1173;
atom64448 =  atom40896+atom41956*atom1172;
atom40899 = atom1497*atom1018;
atom64442 = -atom1172*atom1019-atom41956*atom1173;
atom64445 =  atom40899*atom1174-atom1175*atom64442;
atom64461 =  atom1176*atom64445+atom64448*atom1177;
atom64453 =  atom64442*atom1174+atom1175*atom40899;
atom58438 =  atom58431*atom1178+atom58423*atom1187+atom58435*atom1184;
atom66252 = -atom64453*atom22480+atom64461*atom22481;
atom64450 =  atom1176*atom64448-atom64445*atom1177;
atom66257 =  atom64453*atom22479-atom64450*atom22481;
atom58443 =  atom1180*atom58431+atom58435*atom1190+atom1193*atom58423;
atom66258 =  atom66257+atom58443;
atom66260 =  atom3446*atom66258+atom3445*( atom58438+atom66252);
atom40804 = -atom1497*atom1172;
atom40806 = atom1497*atom1173;
atom64468 =  atom1496*atom1174-atom1175*atom40806;
atom64480 =  atom1176*atom64468+atom1177*atom40804;
atom40875 =  atom40806*atom1174+atom1514;
atom44126 = atom1497*atom22452;
atom44128 = atom1496*atom22452;
atom44216 =  atom44128*atom1184-atom22449*atom1187+atom1178*atom44126;
atom64471 = -atom1177*atom64468+atom1176*atom40804;
atom44131 = -atom1193*atom22449+atom1180*atom44126+atom44128*atom1190;
atom66269 =  atom40875*atom22479+atom44131-atom64471*atom22481;
atom66271 =  atom3446*atom66269-( atom40875*atom22480-atom44216-atom64480*atom22481)*atom3445;
atom6041 =  atom1497*atom1017+atom1021*atom1496;
atom6036 = -atom1496*atom1017;
atom6037 =  atom1497*atom1021+atom6036;
atom6044 =  atom1193*atom1023+atom1190*atom6041+atom1180*atom6037;
atom9508 =  atom3446*atom6044+atom3445*( atom1023*atom1187+atom6041*atom1184+atom6037*atom1178);
atom66274 =  atom3445*atom66252+atom3446*atom66257;
atom43497 = -atom683*atom1017-atom684*atom1016;
atom66275 = -atom1018*atom43497;
atom66278 = -atom1019*atom43497;
atom43485 = -atom684*atom1017+atom683*atom1016;
atom66280 =  atom66278*atom1496-atom1497*atom43485;
atom66282 =  atom66275*atom1172-atom66280*atom1173;
atom66286 =  atom43485*atom1496+atom1497*atom66278;
atom66288 =  atom1175*atom66286+atom1174*atom66282;
atom66292 = -atom1175*atom66282+atom66286*atom1174;
atom66296 =  atom66275*atom1173+atom1172*atom66280;
atom66298 =  atom1176*atom66292+atom1177*atom66296;
atom66305 = -atom66292*atom1177+atom1176*atom66296;
atom66307 =  atom66288*atom22479-atom66305*atom22481;
atom66309 =  atom3445*( atom66298*atom22481-atom66288*atom22480)+atom3446*atom66307;
atom66383 = -atom3446*bFRR*epsiFRR*G_elastic*C11FRR*aFRR;
atom3332 =  uR_FRR-lR_FRR;
atom3333 = atom3332*aR_FRR;
atom3334 =  atom3333+bR_FRR;
atom3403 =  atom3332*atom3334+cR_FRR+atom3332*( atom3333+atom3334);
atom3449 = pow( (atom3403*atom3403)+1.0,-(1.0/2.0));
atom66384 = -bFRR*epsiFRR*G_elastic*C22FRR*aFRR*atom3449;
atom3450 = atom3403*atom3449;
atom58410 =  atom1176*atom22470-atom22465*atom1177;
atom66316 =  atom66220*atom3449+( atom58410-atom22479*atom1177+atom1176*atom22480)*atom3450;
atom3404 = atom3400*atom3403;
atom3405 = -atom3398*atom3403;
atom3438 = pow( (atom3405*atom3405)+(atom3404*atom3404)+atom3436,-(1.0/2.0));
atom3439 = atom3404*atom3438;
atom3440 = atom3405*atom3438;
atom66386 = pow(bFRR*aFRR,(1.0/2.0));
atom66357 =  atom1176*atom3439+atom3440*atom1177;
atom66387 = -C23FRR*bFRR*epsiFRR*G_elastic*atom66386*aFRR*atom3449;
atom58420 =  atom22470*atom1178-atom22465*atom1180;
atom66323 =  atom3450*( atom22480*atom1178+atom58420-atom1180*atom22479)+atom66231*atom3449;
atom3441 = atom3398*atom3438;
atom66362 =  atom3439*atom1178+atom1175*atom3441+atom3440*atom1180;
atom66324 = atom66236*atom3449;
atom66366 =  atom3440*atom60839+atom3439*atom60833+atom1195*atom3441;
atom44067 =  atom1175*atom22456-atom1194*atom22459;
atom66331 = -atom3450*( atom60839*atom22479-atom22480*atom60833-atom44067)+atom66247*atom3449;
atom9548 =  atom1193*atom3449+atom1195*atom3450;
atom66371 =  atom3440*atom64461+atom64450*atom3439+atom64453*atom3441;
atom58448 =  atom58423*atom1195+atom58435*atom1194+atom1175*atom58431;
atom66334 =  atom64450*atom22480-atom22479*atom64461;
atom66338 =  atom3450*( atom58448+atom66334)+atom66258*atom3449;
atom66495 = atom66371*atom66387;
atom66376 =  atom3440*atom64480+atom40875*atom3441+atom3439*atom64471;
atom44137 =  atom1175*atom44126+atom44128*atom1194-atom22449*atom1195;
atom66345 =  atom66269*atom3449+( atom44137-atom64480*atom22479+atom64471*atom22480)*atom3450;
atom9557 =  atom6044*atom3449+atom3450*( atom1175*atom6037+atom1194*atom6041+atom1023*atom1195);
atom66348 =  atom66257*atom3449+atom3450*atom66334;
atom66354 =  atom66307*atom3449+( atom66305*atom22480-atom66298*atom22479)*atom3450;
atom66381 =  atom66288*atom3441+atom3439*atom66305+atom66298*atom3440;
atom66388 = -bFRR*epsiFRR*G_elastic*atom3450*C22FRR*aFRR;
atom66389 = -C23FRR*bFRR*epsiFRR*G_elastic*atom66386*atom3450*aFRR;
atom66530 = atom66371*atom66389;
atom40803 = atom1172*atom1496;
atom40902 =  atom1019*atom40803+atom1018*atom1173;
atom41903 = -atom1017*atom40804+atom40902*atom1016;
atom41900 =  atom40902*atom1017+atom1016*atom40804;
atom43488 =  atom683*atom41903-atom41900*atom684;
atom40898 =  atom1018*atom40803+atom40896;
atom43476 =  atom684*atom41903+atom683*atom41900;
atom60330 =  atom40898*atom1524+atom1604*atom43488+atom43476*atom1601;
atom60325 =  atom1610*atom43488+atom1530*atom40898+atom1607*atom43476;
atom60337 =  atom40898*atom1518+atom43476*atom1595+atom1598*atom43488;
atom60341 =  atom58407+atom60325*atom22479-atom60337*atom22481;
atom66390 = -bFRR*epsiFRR*G_elastic*C11FRR*aFRR*( atom3446*atom60341-( atom60325*atom22480-atom60330*atom22481-atom58406)*atom3445);
atom66140 =  atom60341*atom3449+atom3450*( atom58410+atom60337*atom22480-atom60330*atom22479);
atom22397 =  atom3439*atom1595+atom3440*atom1601+atom1607*atom3441;
atom66146 =  atom1530*atom3441+atom3440*atom1524+atom3439*atom1518;
atom66153 =  atom3440*atom1604+atom1610*atom3441+atom1598*atom3439;
atom66155 =  atom66146*atom40898+atom22397*atom43476+atom66153*atom43488;
atom66393 =  C23FRR*bFRR*epsiFRR*G_elastic*atom66386*aFRR*atom66155-bFRR*epsiFRR*G_elastic*C22FRR*atom66140*aFRR;
atom66395 = (bFRR*bFRR);
atom66396 = (aFRR*aFRR);
atom66398 = -C23FRR*bFRR*epsiFRR*G_elastic*atom66386*atom66140*aFRR-atom66395*C33FRR*epsiFRR*G_elastic*atom66396*atom66155;
atom66572 = atom66371*atom66398;
atom40903 = atom1497*atom1019;
atom41907 =  atom1016*atom40903+atom6036;
atom41905 =  atom40903*atom1017+atom1016*atom1496;
atom43491 = -atom684*atom41905+atom683*atom41907;
atom43479 =  atom684*atom41907+atom683*atom41905;
atom60359 =  atom1607*atom43479+atom1610*atom43491+atom1530*atom40899;
atom60364 =  atom1524*atom40899+atom1604*atom43491+atom1601*atom43479;
atom60371 =  atom40899*atom1518+atom1598*atom43491+atom1595*atom43479;
atom60375 = -atom60371*atom22481+atom22479*atom60359+atom58417;
atom66399 = -bFRR*epsiFRR*G_elastic*C11FRR*aFRR*( atom3445*( atom58414-atom60359*atom22480+atom60364*atom22481)+atom60375*atom3446);
atom66161 =  atom60375*atom3449+( atom22480*atom60371-atom60364*atom22479+atom58420)*atom3450;
atom66166 =  atom66153*atom43491+atom66146*atom40899+atom22397*atom43479;
atom66402 = -bFRR*epsiFRR*G_elastic*atom66161*C22FRR*aFRR+C23FRR*bFRR*epsiFRR*G_elastic*atom66386*aFRR*atom66166;
atom66405 = -C23FRR*bFRR*epsiFRR*G_elastic*atom66386*atom66161*aFRR-atom66395*C33FRR*epsiFRR*G_elastic*atom66396*atom66166;
atom66622 = atom66371*atom66405;
atom60392 =  (atom1607*atom1607)+(atom1530*atom1530)+(atom1610*atom1610);
atom60396 =  atom1530*atom1524+atom1610*atom1604+atom1607*atom1601;
atom60402 =  atom1607*atom1595+atom1598*atom1610+atom1530*atom1518;
atom60406 =  atom22465+atom22479*atom60392-atom60402*atom22481;
atom66406 = -bFRR*epsiFRR*G_elastic*C11FRR*aFRR*( ( atom60396*atom22481-atom22470-atom60392*atom22480)*atom3445+atom3446*atom60406);
atom66177 =  atom22397*atom1607+atom66153*atom1610+atom66146*atom1530;
atom66172 =  atom60406*atom3449-( atom60396*atom22479-atom60402*atom22480)*atom3450;
atom66409 = -bFRR*atom66172*epsiFRR*G_elastic*C22FRR*aFRR+C23FRR*bFRR*atom66177*epsiFRR*G_elastic*atom66386*aFRR;
atom66412 = -atom66395*atom66177*C33FRR*epsiFRR*G_elastic*atom66396-C23FRR*bFRR*atom66172*epsiFRR*G_elastic*atom66386*aFRR;
atom66672 = atom66371*atom66412;
atom43482 =  atom683*atom1022+atom684*atom1023;
atom43494 =  atom683*atom1023-atom684*atom1022;
atom60426 =  atom43494*atom1604-atom1019*atom1524+atom43482*atom1601;
atom60422 =  atom1607*atom43482-atom1530*atom1019+atom1610*atom43494;
atom60432 =  atom1598*atom43494+atom43482*atom1595-atom1019*atom1518;
atom60436 =  atom44063+atom60422*atom22479-atom60432*atom22481;
atom66413 = -bFRR*( atom3446*atom60436+( atom60426*atom22481+atom44188-atom60422*atom22480)*atom3445)*epsiFRR*G_elastic*C11FRR*aFRR;
atom66183 =  atom60436*atom3449-atom3450*( atom60426*atom22479-atom44067-atom60432*atom22480);
atom66188 = -atom66146*atom1019+atom66153*atom43494+atom22397*atom43482;
atom66416 = -bFRR*atom66183*epsiFRR*G_elastic*C22FRR*aFRR+C23FRR*bFRR*epsiFRR*G_elastic*atom66386*atom66188*aFRR;
atom66419 = -C23FRR*bFRR*atom66183*epsiFRR*G_elastic*atom66386*aFRR-atom66395*C33FRR*epsiFRR*G_elastic*atom66188*atom66396;
atom66722 = atom66371*atom66419;
atom66420 = -bFRR*epsiFRR*G_elastic*C11FRR*atom9499*aFRR;
atom66421 = -bFRR*epsiFRR*G_elastic*C22FRR*atom9548*aFRR;
atom66422 = -C23FRR*bFRR*epsiFRR*G_elastic*atom66386*atom9548*aFRR;
atom66772 = atom66371*atom66422;
atom60457 =  atom1530*atom22479-atom22481*atom1518;
atom60458 =  atom58443+atom60457;
atom60453 =  atom1524*atom22481-atom1530*atom22480;
atom66423 = -bFRR*( atom3445*( atom58438+atom60453)+atom3446*atom60458)*epsiFRR*G_elastic*C11FRR*aFRR;
atom60461 =  atom22480*atom1518-atom22479*atom1524;
atom66194 =  atom60458*atom3449+atom3450*( atom60461+atom58448);
atom66425 = C23FRR*atom66146*bFRR*epsiFRR*G_elastic*atom66386*aFRR;
atom66426 =  atom66425-bFRR*atom66194*epsiFRR*G_elastic*C22FRR*aFRR;
atom66428 = -atom66146*atom66395*C33FRR*epsiFRR*G_elastic*atom66396;
atom66429 = -C23FRR*bFRR*atom66194*epsiFRR*G_elastic*atom66386*aFRR+atom66428;
atom66822 = atom66371*atom66429;
atom60473 =  atom1607*atom43485+atom1610*atom43497;
atom60483 =  atom1598*atom43497+atom43485*atom1595;
atom60487 =  atom22479*atom60473-atom60483*atom22481+atom44131;
atom60477 =  atom1601*atom43485+atom1604*atom43497;
atom66430 = -bFRR*( atom3446*atom60487+( atom60477*atom22481-atom60473*atom22480+atom44216)*atom3445)*epsiFRR*G_elastic*C11FRR*aFRR;
atom66200 =  atom3450*( atom22480*atom60483+atom44137-atom22479*atom60477)+atom60487*atom3449;
atom66203 =  atom66153*atom43497+atom22397*atom43485;
atom66433 =  C23FRR*bFRR*epsiFRR*G_elastic*atom66386*atom66203*aFRR-bFRR*epsiFRR*G_elastic*C22FRR*atom66200*aFRR;
atom66436 = -C23FRR*bFRR*epsiFRR*G_elastic*atom66386*atom66200*aFRR-atom66395*C33FRR*epsiFRR*G_elastic*atom66203*atom66396;
atom66872 = atom66371*atom66436;
atom66437 = -bFRR*atom9508*epsiFRR*G_elastic*C11FRR*aFRR;
atom66438 = -bFRR*epsiFRR*G_elastic*C22FRR*aFRR*atom9557;
atom66439 = -C23FRR*bFRR*epsiFRR*G_elastic*atom66386*aFRR*atom9557;
atom66922 = atom66439*atom66371;
atom66440 = -bFRR*epsiFRR*G_elastic*C11FRR*( atom3445*atom60453+atom3446*atom60457)*aFRR;
atom66209 =  atom60461*atom3450+atom60457*atom3449;
atom66442 = -bFRR*epsiFRR*G_elastic*atom66209*C22FRR*aFRR+atom66425;
atom66444 =  atom66428-C23FRR*bFRR*epsiFRR*G_elastic*atom66386*atom66209*aFRR;
atom66972 = atom66371*atom66444;
atom60512 =  atom1607*atom22479-atom1595*atom22481;
atom66445 = bFRR*epsiFRR*G_elastic*C11FRR*( ( atom1607*atom22480-atom1601*atom22481)*atom3445-atom3446*atom60512)*aFRR;
atom66215 =  atom60512*atom3449+( atom22480*atom1595-atom22479*atom1601)*atom3450;
atom66448 = -bFRR*epsiFRR*G_elastic*C22FRR*aFRR*atom66215+atom22397*C23FRR*bFRR*epsiFRR*G_elastic*atom66386*aFRR;
atom66451 = -C23FRR*bFRR*epsiFRR*G_elastic*atom66386*aFRR*atom66215-atom22397*atom66395*C33FRR*epsiFRR*G_elastic*atom66396;
atom67022 = atom66371*atom66451;

_CKFRR[0] = atom3445*atom66382;
_CKFRR[1] = atom66383*atom3445;
_CKFRR[2] = 0.0;
_CKFRR[3] = atom66390*atom3445;
_CKFRR[4] = atom66399*atom3445;
_CKFRR[5] = atom3445*atom66406;
_CKFRR[6] = 0.0;
_CKFRR[7] = atom3445*atom66413;
_CKFRR[8] = 0.0;
_CKFRR[9] = 0.0;
_CKFRR[10] = 0.0;
_CKFRR[11] = atom3445*atom66420;
_CKFRR[12] = atom66423*atom3445;
_CKFRR[13] = atom3445*atom66430;
_CKFRR[14] = 0.0;
_CKFRR[15] = 0.0;
_CKFRR[16] = 0.0;
_CKFRR[17] = 0.0;
_CKFRR[18] = 0.0;
_CKFRR[19] = 0.0;
_CKFRR[20] = 0.0;
_CKFRR[21] = 0.0;
_CKFRR[22] = 0.0;
_CKFRR[23] = atom66437*atom3445;
_CKFRR[24] = atom66440*atom3445;
_CKFRR[25] = atom3445*atom66445;
_CKFRR[26] = 0.0;
_CKFRR[27] = 0.0;
_CKFRR[28] = 0.0;
_CKFRR[29] = 0.0;
_CKFRR[30] = 0.0;
_CKFRR[31] = 0.0;
_CKFRR[32] = 0.0;
_CKFRR[33] = 0.0;
_CKFRR[34] = 0.0;
_CKFRR[35] = 0.0;
_CKFRR[36] = 0.0;
_CKFRR[37] = 0.0;
_CKFRR[38] = 0.0;
_CKFRR[39] = 0.0;
_CKFRR[40] = 0.0;
_CKFRR[41] = 0.0;
_CKFRR[42] = 0.0;
_CKFRR[43] = 0.0;
_CKFRR[44] = atom3446*atom66382;
_CKFRR[45] =  atom66384*atom3449+atom3446*atom66383;
_CKFRR[46] = atom66388*atom3449;
_CKFRR[47] =  atom66393*atom3449+atom66390*atom3446;
_CKFRR[48] =  atom66402*atom3449+atom66399*atom3446;
_CKFRR[49] =  atom3446*atom66406+atom66409*atom3449;
_CKFRR[50] = 0.0;
_CKFRR[51] =  atom3449*atom66416+atom3446*atom66413;
_CKFRR[52] = 0.0;
_CKFRR[53] = 0.0;
_CKFRR[54] = 0.0;
_CKFRR[55] =  atom66421*atom3449+atom3446*atom66420;
_CKFRR[56] =  atom66426*atom3449+atom3446*atom66423;
_CKFRR[57] =  atom3446*atom66430+atom66433*atom3449;
_CKFRR[58] = 0.0;
_CKFRR[59] = 0.0;
_CKFRR[60] = 0.0;
_CKFRR[61] = 0.0;
_CKFRR[62] = 0.0;
_CKFRR[63] = 0.0;
_CKFRR[64] = 0.0;
_CKFRR[65] = 0.0;
_CKFRR[66] = 0.0;
_CKFRR[67] =  atom66437*atom3446+atom66438*atom3449;
_CKFRR[68] =  atom3446*atom66440+atom66442*atom3449;
_CKFRR[69] =  atom66448*atom3449+atom3446*atom66445;
_CKFRR[70] = 0.0;
_CKFRR[71] = 0.0;
_CKFRR[72] = 0.0;
_CKFRR[73] = 0.0;
_CKFRR[74] = 0.0;
_CKFRR[75] = 0.0;
_CKFRR[76] = 0.0;
_CKFRR[77] = 0.0;
_CKFRR[78] = 0.0;
_CKFRR[79] = 0.0;
_CKFRR[80] = 0.0;
_CKFRR[81] = 0.0;
_CKFRR[82] = 0.0;
_CKFRR[83] = 0.0;
_CKFRR[84] = 0.0;
_CKFRR[85] = 0.0;
_CKFRR[86] = 0.0;
_CKFRR[87] = 0.0;
_CKFRR[88] = 0.0;
_CKFRR[89] = atom66384*atom3450;
_CKFRR[90] = atom66388*atom3450;
_CKFRR[91] = atom66393*atom3450;
_CKFRR[92] = atom66402*atom3450;
_CKFRR[93] = atom3450*atom66409;
_CKFRR[94] = 0.0;
_CKFRR[95] = atom3450*atom66416;
_CKFRR[96] = 0.0;
_CKFRR[97] = 0.0;
_CKFRR[98] = 0.0;
_CKFRR[99] = atom3450*atom66421;
_CKFRR[100] = atom3450*atom66426;
_CKFRR[101] = atom66433*atom3450;
_CKFRR[102] = 0.0;
_CKFRR[103] = 0.0;
_CKFRR[104] = 0.0;
_CKFRR[105] = 0.0;
_CKFRR[106] = 0.0;
_CKFRR[107] = 0.0;
_CKFRR[108] = 0.0;
_CKFRR[109] = 0.0;
_CKFRR[110] = 0.0;
_CKFRR[111] = atom3450*atom66438;
_CKFRR[112] = atom3450*atom66442;
_CKFRR[113] = atom66448*atom3450;
_CKFRR[114] = 0.0;
_CKFRR[115] = 0.0;
_CKFRR[116] = 0.0;
_CKFRR[117] = 0.0;
_CKFRR[118] = 0.0;
_CKFRR[119] = 0.0;
_CKFRR[120] = 0.0;
_CKFRR[121] = 0.0;
_CKFRR[122] = 0.0;
_CKFRR[123] = 0.0;
_CKFRR[124] = 0.0;
_CKFRR[125] = 0.0;
_CKFRR[126] = 0.0;
_CKFRR[127] = 0.0;
_CKFRR[128] = 0.0;
_CKFRR[129] = 0.0;
_CKFRR[130] = 0.0;
_CKFRR[131] = 0.0;
_CKFRR[132] = atom66382*atom66222;
_CKFRR[133] =  atom66383*atom66222+atom66384*atom66316+atom66357*atom66387;
_CKFRR[134] =  atom66388*atom66316+atom66357*atom66389;
_CKFRR[135] =  atom66390*atom66222+atom66393*atom66316+atom66357*atom66398;
_CKFRR[136] =  atom66399*atom66222+atom66402*atom66316+atom66405*atom66357;
_CKFRR[137] =  atom66406*atom66222+atom66316*atom66409+atom66412*atom66357;
_CKFRR[138] = 0.0;
_CKFRR[139] =  atom66413*atom66222+atom66316*atom66416+atom66419*atom66357;
_CKFRR[140] = 0.0;
_CKFRR[141] = 0.0;
_CKFRR[142] = 0.0;
_CKFRR[143] =  atom66420*atom66222+atom66357*atom66422+atom66316*atom66421;
_CKFRR[144] =  atom66316*atom66426+atom66357*atom66429+atom66423*atom66222;
_CKFRR[145] =  atom66357*atom66436+atom66433*atom66316+atom66222*atom66430;
_CKFRR[146] = 0.0;
_CKFRR[147] = 0.0;
_CKFRR[148] = 0.0;
_CKFRR[149] = 0.0;
_CKFRR[150] = 0.0;
_CKFRR[151] = 0.0;
_CKFRR[152] = 0.0;
_CKFRR[153] = 0.0;
_CKFRR[154] = 0.0;
_CKFRR[155] =  atom66439*atom66357+atom66437*atom66222+atom66316*atom66438;
_CKFRR[156] =  atom66444*atom66357+atom66316*atom66442+atom66440*atom66222;
_CKFRR[157] =  atom66448*atom66316+atom66445*atom66222+atom66451*atom66357;
_CKFRR[158] = 0.0;
_CKFRR[159] = 0.0;
_CKFRR[160] = 0.0;
_CKFRR[161] = 0.0;
_CKFRR[162] = 0.0;
_CKFRR[163] = 0.0;
_CKFRR[164] = 0.0;
_CKFRR[165] = 0.0;
_CKFRR[166] = 0.0;
_CKFRR[167] = 0.0;
_CKFRR[168] = 0.0;
_CKFRR[169] = 0.0;
_CKFRR[170] = 0.0;
_CKFRR[171] = 0.0;
_CKFRR[172] = 0.0;
_CKFRR[173] = 0.0;
_CKFRR[174] = 0.0;
_CKFRR[175] = 0.0;
_CKFRR[176] = atom66233*atom66382;
_CKFRR[177] =  atom66383*atom66233+atom66323*atom66384+atom66362*atom66387;
_CKFRR[178] =  atom66323*atom66388+atom66362*atom66389;
_CKFRR[179] =  atom66390*atom66233+atom66393*atom66323+atom66362*atom66398;
_CKFRR[180] =  atom66399*atom66233+atom66402*atom66323+atom66362*atom66405;
_CKFRR[181] =  atom66233*atom66406+atom66323*atom66409+atom66362*atom66412;
_CKFRR[182] = 0.0;
_CKFRR[183] =  atom66323*atom66416+atom66362*atom66419+atom66413*atom66233;
_CKFRR[184] = 0.0;
_CKFRR[185] = 0.0;
_CKFRR[186] = 0.0;
_CKFRR[187] =  atom66420*atom66233+atom66323*atom66421+atom66362*atom66422;
_CKFRR[188] =  atom66362*atom66429+atom66423*atom66233+atom66323*atom66426;
_CKFRR[189] =  atom66362*atom66436+atom66233*atom66430+atom66323*atom66433;
_CKFRR[190] = 0.0;
_CKFRR[191] = 0.0;
_CKFRR[192] = 0.0;
_CKFRR[193] = 0.0;
_CKFRR[194] = 0.0;
_CKFRR[195] = 0.0;
_CKFRR[196] = 0.0;
_CKFRR[197] = 0.0;
_CKFRR[198] = 0.0;
_CKFRR[199] =  atom66323*atom66438+atom66437*atom66233+atom66439*atom66362;
_CKFRR[200] =  atom66323*atom66442+atom66362*atom66444+atom66440*atom66233;
_CKFRR[201] =  atom66233*atom66445+atom66323*atom66448+atom66362*atom66451;
_CKFRR[202] = 0.0;
_CKFRR[203] = 0.0;
_CKFRR[204] = 0.0;
_CKFRR[205] = 0.0;
_CKFRR[206] = 0.0;
_CKFRR[207] = 0.0;
_CKFRR[208] = 0.0;
_CKFRR[209] = 0.0;
_CKFRR[210] = 0.0;
_CKFRR[211] = 0.0;
_CKFRR[212] = 0.0;
_CKFRR[213] = 0.0;
_CKFRR[214] = 0.0;
_CKFRR[215] = 0.0;
_CKFRR[216] = 0.0;
_CKFRR[217] = 0.0;
_CKFRR[218] = 0.0;
_CKFRR[219] = 0.0;
_CKFRR[220] = atom66382*atom66238;
_CKFRR[221] =  atom3441*atom66387+atom66384*atom66324+atom66383*atom66238;
_CKFRR[222] =  atom66389*atom3441+atom66388*atom66324;
_CKFRR[223] =  atom66390*atom66238+atom66398*atom3441+atom66393*atom66324;
_CKFRR[224] =  atom66399*atom66238+atom66405*atom3441+atom66402*atom66324;
_CKFRR[225] =  atom66412*atom3441+atom66406*atom66238+atom66324*atom66409;
_CKFRR[226] = 0.0;
_CKFRR[227] =  atom66419*atom3441+atom66413*atom66238+atom66324*atom66416;
_CKFRR[228] = 0.0;
_CKFRR[229] = 0.0;
_CKFRR[230] = 0.0;
_CKFRR[231] =  atom3441*atom66422+atom66420*atom66238+atom66324*atom66421;
_CKFRR[232] =  atom66426*atom66324+atom3441*atom66429+atom66423*atom66238;
_CKFRR[233] =  atom66430*atom66238+atom66436*atom3441+atom66433*atom66324;
_CKFRR[234] = 0.0;
_CKFRR[235] = 0.0;
_CKFRR[236] = 0.0;
_CKFRR[237] = 0.0;
_CKFRR[238] = 0.0;
_CKFRR[239] = 0.0;
_CKFRR[240] = 0.0;
_CKFRR[241] = 0.0;
_CKFRR[242] = 0.0;
_CKFRR[243] =  atom66437*atom66238+atom66439*atom3441+atom66324*atom66438;
_CKFRR[244] =  atom66324*atom66442+atom66440*atom66238+atom66444*atom3441;
_CKFRR[245] =  atom66445*atom66238+atom66451*atom3441+atom66448*atom66324;
_CKFRR[246] = 0.0;
_CKFRR[247] = 0.0;
_CKFRR[248] = 0.0;
_CKFRR[249] = 0.0;
_CKFRR[250] = 0.0;
_CKFRR[251] = 0.0;
_CKFRR[252] = 0.0;
_CKFRR[253] = 0.0;
_CKFRR[254] = 0.0;
_CKFRR[255] = 0.0;
_CKFRR[256] = 0.0;
_CKFRR[257] = 0.0;
_CKFRR[258] = 0.0;
_CKFRR[259] = 0.0;
_CKFRR[260] = 0.0;
_CKFRR[261] = 0.0;
_CKFRR[262] = 0.0;
_CKFRR[263] = 0.0;
_CKFRR[264] = 0.0;
_CKFRR[265] = 0.0;
_CKFRR[266] = 0.0;
_CKFRR[267] = 0.0;
_CKFRR[268] = 0.0;
_CKFRR[269] = 0.0;
_CKFRR[270] = 0.0;
_CKFRR[271] = 0.0;
_CKFRR[272] = 0.0;
_CKFRR[273] = 0.0;
_CKFRR[274] = 0.0;
_CKFRR[275] = 0.0;
_CKFRR[276] = 0.0;
_CKFRR[277] = 0.0;
_CKFRR[278] = 0.0;
_CKFRR[279] = 0.0;
_CKFRR[280] = 0.0;
_CKFRR[281] = 0.0;
_CKFRR[282] = 0.0;
_CKFRR[283] = 0.0;
_CKFRR[284] = 0.0;
_CKFRR[285] = 0.0;
_CKFRR[286] = 0.0;
_CKFRR[287] = 0.0;
_CKFRR[288] = 0.0;
_CKFRR[289] = 0.0;
_CKFRR[290] = 0.0;
_CKFRR[291] = 0.0;
_CKFRR[292] = 0.0;
_CKFRR[293] = 0.0;
_CKFRR[294] = 0.0;
_CKFRR[295] = 0.0;
_CKFRR[296] = 0.0;
_CKFRR[297] = 0.0;
_CKFRR[298] = 0.0;
_CKFRR[299] = 0.0;
_CKFRR[300] = 0.0;
_CKFRR[301] = 0.0;
_CKFRR[302] = 0.0;
_CKFRR[303] = 0.0;
_CKFRR[304] = 0.0;
_CKFRR[305] = 0.0;
_CKFRR[306] = 0.0;
_CKFRR[307] = 0.0;
_CKFRR[308] = atom66249*atom66382;
_CKFRR[309] =  atom66366*atom66387+atom66383*atom66249+atom66384*atom66331;
_CKFRR[310] =  atom66366*atom66389+atom66388*atom66331;
_CKFRR[311] =  atom66366*atom66398+atom66393*atom66331+atom66390*atom66249;
_CKFRR[312] =  atom66402*atom66331+atom66366*atom66405+atom66399*atom66249;
_CKFRR[313] =  atom66331*atom66409+atom66249*atom66406+atom66366*atom66412;
_CKFRR[314] = 0.0;
_CKFRR[315] =  atom66331*atom66416+atom66249*atom66413+atom66366*atom66419;
_CKFRR[316] = 0.0;
_CKFRR[317] = 0.0;
_CKFRR[318] = 0.0;
_CKFRR[319] =  atom66366*atom66422+atom66421*atom66331+atom66249*atom66420;
_CKFRR[320] =  atom66426*atom66331+atom66366*atom66429+atom66249*atom66423;
_CKFRR[321] =  atom66249*atom66430+atom66433*atom66331+atom66366*atom66436;
_CKFRR[322] = 0.0;
_CKFRR[323] = 0.0;
_CKFRR[324] = 0.0;
_CKFRR[325] = 0.0;
_CKFRR[326] = 0.0;
_CKFRR[327] = 0.0;
_CKFRR[328] = 0.0;
_CKFRR[329] = 0.0;
_CKFRR[330] = 0.0;
_CKFRR[331] =  atom66331*atom66438+atom66437*atom66249+atom66439*atom66366;
_CKFRR[332] =  atom66442*atom66331+atom66249*atom66440+atom66366*atom66444;
_CKFRR[333] =  atom66366*atom66451+atom66249*atom66445+atom66448*atom66331;
_CKFRR[334] = 0.0;
_CKFRR[335] = 0.0;
_CKFRR[336] = 0.0;
_CKFRR[337] = 0.0;
_CKFRR[338] = 0.0;
_CKFRR[339] = 0.0;
_CKFRR[340] = 0.0;
_CKFRR[341] = 0.0;
_CKFRR[342] = 0.0;
_CKFRR[343] = 0.0;
_CKFRR[344] = 0.0;
_CKFRR[345] = 0.0;
_CKFRR[346] = 0.0;
_CKFRR[347] = 0.0;
_CKFRR[348] = 0.0;
_CKFRR[349] = 0.0;
_CKFRR[350] = 0.0;
_CKFRR[351] = 0.0;
_CKFRR[352] = 0.0;
_CKFRR[353] = 0.0;
_CKFRR[354] = 0.0;
_CKFRR[355] = 0.0;
_CKFRR[356] = 0.0;
_CKFRR[357] = 0.0;
_CKFRR[358] = 0.0;
_CKFRR[359] = 0.0;
_CKFRR[360] = 0.0;
_CKFRR[361] = 0.0;
_CKFRR[362] = 0.0;
_CKFRR[363] = 0.0;
_CKFRR[364] = 0.0;
_CKFRR[365] = 0.0;
_CKFRR[366] = 0.0;
_CKFRR[367] = 0.0;
_CKFRR[368] = 0.0;
_CKFRR[369] = 0.0;
_CKFRR[370] = 0.0;
_CKFRR[371] = 0.0;
_CKFRR[372] = 0.0;
_CKFRR[373] = 0.0;
_CKFRR[374] = 0.0;
_CKFRR[375] = 0.0;
_CKFRR[376] = 0.0;
_CKFRR[377] = 0.0;
_CKFRR[378] = 0.0;
_CKFRR[379] = 0.0;
_CKFRR[380] = 0.0;
_CKFRR[381] = 0.0;
_CKFRR[382] = 0.0;
_CKFRR[383] = 0.0;
_CKFRR[384] = 0.0;
_CKFRR[385] = 0.0;
_CKFRR[386] = 0.0;
_CKFRR[387] = 0.0;
_CKFRR[388] = 0.0;
_CKFRR[389] = 0.0;
_CKFRR[390] = 0.0;
_CKFRR[391] = 0.0;
_CKFRR[392] = 0.0;
_CKFRR[393] = 0.0;
_CKFRR[394] = 0.0;
_CKFRR[395] = 0.0;
_CKFRR[396] = 0.0;
_CKFRR[397] = 0.0;
_CKFRR[398] = 0.0;
_CKFRR[399] = 0.0;
_CKFRR[400] = 0.0;
_CKFRR[401] = 0.0;
_CKFRR[402] = 0.0;
_CKFRR[403] = 0.0;
_CKFRR[404] = 0.0;
_CKFRR[405] = 0.0;
_CKFRR[406] = 0.0;
_CKFRR[407] = 0.0;
_CKFRR[408] = 0.0;
_CKFRR[409] = 0.0;
_CKFRR[410] = 0.0;
_CKFRR[411] = 0.0;
_CKFRR[412] = 0.0;
_CKFRR[413] = 0.0;
_CKFRR[414] = 0.0;
_CKFRR[415] = 0.0;
_CKFRR[416] = 0.0;
_CKFRR[417] = 0.0;
_CKFRR[418] = 0.0;
_CKFRR[419] = 0.0;
_CKFRR[420] = 0.0;
_CKFRR[421] = 0.0;
_CKFRR[422] = 0.0;
_CKFRR[423] = 0.0;
_CKFRR[424] = 0.0;
_CKFRR[425] = 0.0;
_CKFRR[426] = 0.0;
_CKFRR[427] = 0.0;
_CKFRR[428] = 0.0;
_CKFRR[429] = 0.0;
_CKFRR[430] = 0.0;
_CKFRR[431] = 0.0;
_CKFRR[432] = 0.0;
_CKFRR[433] = 0.0;
_CKFRR[434] = 0.0;
_CKFRR[435] = 0.0;
_CKFRR[436] = 0.0;
_CKFRR[437] = 0.0;
_CKFRR[438] = 0.0;
_CKFRR[439] = 0.0;
_CKFRR[440] = 0.0;
_CKFRR[441] = 0.0;
_CKFRR[442] = 0.0;
_CKFRR[443] = 0.0;
_CKFRR[444] = 0.0;
_CKFRR[445] = 0.0;
_CKFRR[446] = 0.0;
_CKFRR[447] = 0.0;
_CKFRR[448] = 0.0;
_CKFRR[449] = 0.0;
_CKFRR[450] = 0.0;
_CKFRR[451] = 0.0;
_CKFRR[452] = 0.0;
_CKFRR[453] = 0.0;
_CKFRR[454] = 0.0;
_CKFRR[455] = 0.0;
_CKFRR[456] = 0.0;
_CKFRR[457] = 0.0;
_CKFRR[458] = 0.0;
_CKFRR[459] = 0.0;
_CKFRR[460] = 0.0;
_CKFRR[461] = 0.0;
_CKFRR[462] = 0.0;
_CKFRR[463] = 0.0;
_CKFRR[464] = 0.0;
_CKFRR[465] = 0.0;
_CKFRR[466] = 0.0;
_CKFRR[467] = 0.0;
_CKFRR[468] = 0.0;
_CKFRR[469] = 0.0;
_CKFRR[470] = 0.0;
_CKFRR[471] = 0.0;
_CKFRR[472] = 0.0;
_CKFRR[473] = 0.0;
_CKFRR[474] = 0.0;
_CKFRR[475] = 0.0;
_CKFRR[476] = 0.0;
_CKFRR[477] = 0.0;
_CKFRR[478] = 0.0;
_CKFRR[479] = 0.0;
_CKFRR[480] = 0.0;
_CKFRR[481] = 0.0;
_CKFRR[482] = 0.0;
_CKFRR[483] = 0.0;
_CKFRR[484] = atom9499*atom66382;
_CKFRR[485] =  atom66383*atom9499+atom66384*atom9548;
_CKFRR[486] = atom66388*atom9548;
_CKFRR[487] =  atom66390*atom9499+atom66393*atom9548;
_CKFRR[488] =  atom66402*atom9548+atom66399*atom9499;
_CKFRR[489] =  atom9548*atom66409+atom9499*atom66406;
_CKFRR[490] = 0.0;
_CKFRR[491] =  atom9499*atom66413+atom9548*atom66416;
_CKFRR[492] = 0.0;
_CKFRR[493] = 0.0;
_CKFRR[494] = 0.0;
_CKFRR[495] =  atom9548*atom66421+atom9499*atom66420;
_CKFRR[496] =  atom66426*atom9548+atom66423*atom9499;
_CKFRR[497] =  atom66433*atom9548+atom9499*atom66430;
_CKFRR[498] = 0.0;
_CKFRR[499] = 0.0;
_CKFRR[500] = 0.0;
_CKFRR[501] = 0.0;
_CKFRR[502] = 0.0;
_CKFRR[503] = 0.0;
_CKFRR[504] = 0.0;
_CKFRR[505] = 0.0;
_CKFRR[506] = 0.0;
_CKFRR[507] =  atom66437*atom9499+atom9548*atom66438;
_CKFRR[508] =  atom9548*atom66442+atom66440*atom9499;
_CKFRR[509] =  atom66448*atom9548+atom9499*atom66445;
_CKFRR[510] = 0.0;
_CKFRR[511] = 0.0;
_CKFRR[512] = 0.0;
_CKFRR[513] = 0.0;
_CKFRR[514] = 0.0;
_CKFRR[515] = 0.0;
_CKFRR[516] = 0.0;
_CKFRR[517] = 0.0;
_CKFRR[518] = 0.0;
_CKFRR[519] = 0.0;
_CKFRR[520] = 0.0;
_CKFRR[521] = 0.0;
_CKFRR[522] = 0.0;
_CKFRR[523] = 0.0;
_CKFRR[524] = 0.0;
_CKFRR[525] = 0.0;
_CKFRR[526] = 0.0;
_CKFRR[527] = 0.0;
_CKFRR[528] = atom66260*atom66382;
_CKFRR[529] =  atom66384*atom66338+atom66495+atom66260*atom66383;
_CKFRR[530] =  atom66530+atom66388*atom66338;
_CKFRR[531] =  atom66572+atom66260*atom66390+atom66393*atom66338;
_CKFRR[532] =  atom66622+atom66399*atom66260+atom66402*atom66338;
_CKFRR[533] =  atom66260*atom66406+atom66338*atom66409+atom66672;
_CKFRR[534] = 0.0;
_CKFRR[535] =  atom66722+atom66338*atom66416+atom66260*atom66413;
_CKFRR[536] = 0.0;
_CKFRR[537] = 0.0;
_CKFRR[538] = 0.0;
_CKFRR[539] =  atom66338*atom66421+atom66260*atom66420+atom66772;
_CKFRR[540] =  atom66822+atom66338*atom66426+atom66260*atom66423;
_CKFRR[541] =  atom66872+atom66260*atom66430+atom66433*atom66338;
_CKFRR[542] = 0.0;
_CKFRR[543] = 0.0;
_CKFRR[544] = 0.0;
_CKFRR[545] = 0.0;
_CKFRR[546] = 0.0;
_CKFRR[547] = 0.0;
_CKFRR[548] = 0.0;
_CKFRR[549] = 0.0;
_CKFRR[550] = 0.0;
_CKFRR[551] =  atom66338*atom66438+atom66922+atom66260*atom66437;
_CKFRR[552] =  atom66338*atom66442+atom66260*atom66440+atom66972;
_CKFRR[553] =  atom66260*atom66445+atom67022+atom66448*atom66338;
_CKFRR[554] = 0.0;
_CKFRR[555] = 0.0;
_CKFRR[556] = 0.0;
_CKFRR[557] = 0.0;
_CKFRR[558] = 0.0;
_CKFRR[559] = 0.0;
_CKFRR[560] = 0.0;
_CKFRR[561] = 0.0;
_CKFRR[562] = 0.0;
_CKFRR[563] = 0.0;
_CKFRR[564] = 0.0;
_CKFRR[565] = 0.0;
_CKFRR[566] = 0.0;
_CKFRR[567] = 0.0;
_CKFRR[568] = 0.0;
_CKFRR[569] = 0.0;
_CKFRR[570] = 0.0;
_CKFRR[571] = 0.0;
_CKFRR[572] = atom66271*atom66382;
_CKFRR[573] =  atom66384*atom66345+atom66376*atom66387+atom66383*atom66271;
_CKFRR[574] =  atom66389*atom66376+atom66345*atom66388;
_CKFRR[575] =  atom66398*atom66376+atom66393*atom66345+atom66390*atom66271;
_CKFRR[576] =  atom66405*atom66376+atom66402*atom66345+atom66399*atom66271;
_CKFRR[577] =  atom66412*atom66376+atom66345*atom66409+atom66271*atom66406;
_CKFRR[578] = 0.0;
_CKFRR[579] =  atom66413*atom66271+atom66419*atom66376+atom66345*atom66416;
_CKFRR[580] = 0.0;
_CKFRR[581] = 0.0;
_CKFRR[582] = 0.0;
_CKFRR[583] =  atom66376*atom66422+atom66345*atom66421+atom66271*atom66420;
_CKFRR[584] =  atom66345*atom66426+atom66423*atom66271+atom66376*atom66429;
_CKFRR[585] =  atom66271*atom66430+atom66436*atom66376+atom66345*atom66433;
_CKFRR[586] = 0.0;
_CKFRR[587] = 0.0;
_CKFRR[588] = 0.0;
_CKFRR[589] = 0.0;
_CKFRR[590] = 0.0;
_CKFRR[591] = 0.0;
_CKFRR[592] = 0.0;
_CKFRR[593] = 0.0;
_CKFRR[594] = 0.0;
_CKFRR[595] =  atom66439*atom66376+atom66345*atom66438+atom66437*atom66271;
_CKFRR[596] =  atom66440*atom66271+atom66444*atom66376+atom66345*atom66442;
_CKFRR[597] =  atom66451*atom66376+atom66271*atom66445+atom66345*atom66448;
_CKFRR[598] = 0.0;
_CKFRR[599] = 0.0;
_CKFRR[600] = 0.0;
_CKFRR[601] = 0.0;
_CKFRR[602] = 0.0;
_CKFRR[603] = 0.0;
_CKFRR[604] = 0.0;
_CKFRR[605] = 0.0;
_CKFRR[606] = 0.0;
_CKFRR[607] = 0.0;
_CKFRR[608] = 0.0;
_CKFRR[609] = 0.0;
_CKFRR[610] = 0.0;
_CKFRR[611] = 0.0;
_CKFRR[612] = 0.0;
_CKFRR[613] = 0.0;
_CKFRR[614] = 0.0;
_CKFRR[615] = 0.0;
_CKFRR[616] = 0.0;
_CKFRR[617] = 0.0;
_CKFRR[618] = 0.0;
_CKFRR[619] = 0.0;
_CKFRR[620] = 0.0;
_CKFRR[621] = 0.0;
_CKFRR[622] = 0.0;
_CKFRR[623] = 0.0;
_CKFRR[624] = 0.0;
_CKFRR[625] = 0.0;
_CKFRR[626] = 0.0;
_CKFRR[627] = 0.0;
_CKFRR[628] = 0.0;
_CKFRR[629] = 0.0;
_CKFRR[630] = 0.0;
_CKFRR[631] = 0.0;
_CKFRR[632] = 0.0;
_CKFRR[633] = 0.0;
_CKFRR[634] = 0.0;
_CKFRR[635] = 0.0;
_CKFRR[636] = 0.0;
_CKFRR[637] = 0.0;
_CKFRR[638] = 0.0;
_CKFRR[639] = 0.0;
_CKFRR[640] = 0.0;
_CKFRR[641] = 0.0;
_CKFRR[642] = 0.0;
_CKFRR[643] = 0.0;
_CKFRR[644] = 0.0;
_CKFRR[645] = 0.0;
_CKFRR[646] = 0.0;
_CKFRR[647] = 0.0;
_CKFRR[648] = 0.0;
_CKFRR[649] = 0.0;
_CKFRR[650] = 0.0;
_CKFRR[651] = 0.0;
_CKFRR[652] = 0.0;
_CKFRR[653] = 0.0;
_CKFRR[654] = 0.0;
_CKFRR[655] = 0.0;
_CKFRR[656] = 0.0;
_CKFRR[657] = 0.0;
_CKFRR[658] = 0.0;
_CKFRR[659] = 0.0;
_CKFRR[660] = 0.0;
_CKFRR[661] = 0.0;
_CKFRR[662] = 0.0;
_CKFRR[663] = 0.0;
_CKFRR[664] = 0.0;
_CKFRR[665] = 0.0;
_CKFRR[666] = 0.0;
_CKFRR[667] = 0.0;
_CKFRR[668] = 0.0;
_CKFRR[669] = 0.0;
_CKFRR[670] = 0.0;
_CKFRR[671] = 0.0;
_CKFRR[672] = 0.0;
_CKFRR[673] = 0.0;
_CKFRR[674] = 0.0;
_CKFRR[675] = 0.0;
_CKFRR[676] = 0.0;
_CKFRR[677] = 0.0;
_CKFRR[678] = 0.0;
_CKFRR[679] = 0.0;
_CKFRR[680] = 0.0;
_CKFRR[681] = 0.0;
_CKFRR[682] = 0.0;
_CKFRR[683] = 0.0;
_CKFRR[684] = 0.0;
_CKFRR[685] = 0.0;
_CKFRR[686] = 0.0;
_CKFRR[687] = 0.0;
_CKFRR[688] = 0.0;
_CKFRR[689] = 0.0;
_CKFRR[690] = 0.0;
_CKFRR[691] = 0.0;
_CKFRR[692] = 0.0;
_CKFRR[693] = 0.0;
_CKFRR[694] = 0.0;
_CKFRR[695] = 0.0;
_CKFRR[696] = 0.0;
_CKFRR[697] = 0.0;
_CKFRR[698] = 0.0;
_CKFRR[699] = 0.0;
_CKFRR[700] = 0.0;
_CKFRR[701] = 0.0;
_CKFRR[702] = 0.0;
_CKFRR[703] = 0.0;
_CKFRR[704] = 0.0;
_CKFRR[705] = 0.0;
_CKFRR[706] = 0.0;
_CKFRR[707] = 0.0;
_CKFRR[708] = 0.0;
_CKFRR[709] = 0.0;
_CKFRR[710] = 0.0;
_CKFRR[711] = 0.0;
_CKFRR[712] = 0.0;
_CKFRR[713] = 0.0;
_CKFRR[714] = 0.0;
_CKFRR[715] = 0.0;
_CKFRR[716] = 0.0;
_CKFRR[717] = 0.0;
_CKFRR[718] = 0.0;
_CKFRR[719] = 0.0;
_CKFRR[720] = 0.0;
_CKFRR[721] = 0.0;
_CKFRR[722] = 0.0;
_CKFRR[723] = 0.0;
_CKFRR[724] = 0.0;
_CKFRR[725] = 0.0;
_CKFRR[726] = 0.0;
_CKFRR[727] = 0.0;
_CKFRR[728] = 0.0;
_CKFRR[729] = 0.0;
_CKFRR[730] = 0.0;
_CKFRR[731] = 0.0;
_CKFRR[732] = 0.0;
_CKFRR[733] = 0.0;
_CKFRR[734] = 0.0;
_CKFRR[735] = 0.0;
_CKFRR[736] = 0.0;
_CKFRR[737] = 0.0;
_CKFRR[738] = 0.0;
_CKFRR[739] = 0.0;
_CKFRR[740] = 0.0;
_CKFRR[741] = 0.0;
_CKFRR[742] = 0.0;
_CKFRR[743] = 0.0;
_CKFRR[744] = 0.0;
_CKFRR[745] = 0.0;
_CKFRR[746] = 0.0;
_CKFRR[747] = 0.0;
_CKFRR[748] = 0.0;
_CKFRR[749] = 0.0;
_CKFRR[750] = 0.0;
_CKFRR[751] = 0.0;
_CKFRR[752] = 0.0;
_CKFRR[753] = 0.0;
_CKFRR[754] = 0.0;
_CKFRR[755] = 0.0;
_CKFRR[756] = 0.0;
_CKFRR[757] = 0.0;
_CKFRR[758] = 0.0;
_CKFRR[759] = 0.0;
_CKFRR[760] = 0.0;
_CKFRR[761] = 0.0;
_CKFRR[762] = 0.0;
_CKFRR[763] = 0.0;
_CKFRR[764] = 0.0;
_CKFRR[765] = 0.0;
_CKFRR[766] = 0.0;
_CKFRR[767] = 0.0;
_CKFRR[768] = 0.0;
_CKFRR[769] = 0.0;
_CKFRR[770] = 0.0;
_CKFRR[771] = 0.0;
_CKFRR[772] = 0.0;
_CKFRR[773] = 0.0;
_CKFRR[774] = 0.0;
_CKFRR[775] = 0.0;
_CKFRR[776] = 0.0;
_CKFRR[777] = 0.0;
_CKFRR[778] = 0.0;
_CKFRR[779] = 0.0;
_CKFRR[780] = 0.0;
_CKFRR[781] = 0.0;
_CKFRR[782] = 0.0;
_CKFRR[783] = 0.0;
_CKFRR[784] = 0.0;
_CKFRR[785] = 0.0;
_CKFRR[786] = 0.0;
_CKFRR[787] = 0.0;
_CKFRR[788] = 0.0;
_CKFRR[789] = 0.0;
_CKFRR[790] = 0.0;
_CKFRR[791] = 0.0;
_CKFRR[792] = 0.0;
_CKFRR[793] = 0.0;
_CKFRR[794] = 0.0;
_CKFRR[795] = 0.0;
_CKFRR[796] = 0.0;
_CKFRR[797] = 0.0;
_CKFRR[798] = 0.0;
_CKFRR[799] = 0.0;
_CKFRR[800] = 0.0;
_CKFRR[801] = 0.0;
_CKFRR[802] = 0.0;
_CKFRR[803] = 0.0;
_CKFRR[804] = 0.0;
_CKFRR[805] = 0.0;
_CKFRR[806] = 0.0;
_CKFRR[807] = 0.0;
_CKFRR[808] = 0.0;
_CKFRR[809] = 0.0;
_CKFRR[810] = 0.0;
_CKFRR[811] = 0.0;
_CKFRR[812] = 0.0;
_CKFRR[813] = 0.0;
_CKFRR[814] = 0.0;
_CKFRR[815] = 0.0;
_CKFRR[816] = 0.0;
_CKFRR[817] = 0.0;
_CKFRR[818] = 0.0;
_CKFRR[819] = 0.0;
_CKFRR[820] = 0.0;
_CKFRR[821] = 0.0;
_CKFRR[822] = 0.0;
_CKFRR[823] = 0.0;
_CKFRR[824] = 0.0;
_CKFRR[825] = 0.0;
_CKFRR[826] = 0.0;
_CKFRR[827] = 0.0;
_CKFRR[828] = 0.0;
_CKFRR[829] = 0.0;
_CKFRR[830] = 0.0;
_CKFRR[831] = 0.0;
_CKFRR[832] = 0.0;
_CKFRR[833] = 0.0;
_CKFRR[834] = 0.0;
_CKFRR[835] = 0.0;
_CKFRR[836] = 0.0;
_CKFRR[837] = 0.0;
_CKFRR[838] = 0.0;
_CKFRR[839] = 0.0;
_CKFRR[840] = 0.0;
_CKFRR[841] = 0.0;
_CKFRR[842] = 0.0;
_CKFRR[843] = 0.0;
_CKFRR[844] = 0.0;
_CKFRR[845] = 0.0;
_CKFRR[846] = 0.0;
_CKFRR[847] = 0.0;
_CKFRR[848] = 0.0;
_CKFRR[849] = 0.0;
_CKFRR[850] = 0.0;
_CKFRR[851] = 0.0;
_CKFRR[852] = 0.0;
_CKFRR[853] = 0.0;
_CKFRR[854] = 0.0;
_CKFRR[855] = 0.0;
_CKFRR[856] = 0.0;
_CKFRR[857] = 0.0;
_CKFRR[858] = 0.0;
_CKFRR[859] = 0.0;
_CKFRR[860] = 0.0;
_CKFRR[861] = 0.0;
_CKFRR[862] = 0.0;
_CKFRR[863] = 0.0;
_CKFRR[864] = 0.0;
_CKFRR[865] = 0.0;
_CKFRR[866] = 0.0;
_CKFRR[867] = 0.0;
_CKFRR[868] = 0.0;
_CKFRR[869] = 0.0;
_CKFRR[870] = 0.0;
_CKFRR[871] = 0.0;
_CKFRR[872] = 0.0;
_CKFRR[873] = 0.0;
_CKFRR[874] = 0.0;
_CKFRR[875] = 0.0;
_CKFRR[876] = 0.0;
_CKFRR[877] = 0.0;
_CKFRR[878] = 0.0;
_CKFRR[879] = 0.0;
_CKFRR[880] = 0.0;
_CKFRR[881] = 0.0;
_CKFRR[882] = 0.0;
_CKFRR[883] = 0.0;
_CKFRR[884] = 0.0;
_CKFRR[885] = 0.0;
_CKFRR[886] = 0.0;
_CKFRR[887] = 0.0;
_CKFRR[888] = 0.0;
_CKFRR[889] = 0.0;
_CKFRR[890] = 0.0;
_CKFRR[891] = 0.0;
_CKFRR[892] = 0.0;
_CKFRR[893] = 0.0;
_CKFRR[894] = 0.0;
_CKFRR[895] = 0.0;
_CKFRR[896] = 0.0;
_CKFRR[897] = 0.0;
_CKFRR[898] = 0.0;
_CKFRR[899] = 0.0;
_CKFRR[900] = 0.0;
_CKFRR[901] = 0.0;
_CKFRR[902] = 0.0;
_CKFRR[903] = 0.0;
_CKFRR[904] = 0.0;
_CKFRR[905] = 0.0;
_CKFRR[906] = 0.0;
_CKFRR[907] = 0.0;
_CKFRR[908] = 0.0;
_CKFRR[909] = 0.0;
_CKFRR[910] = 0.0;
_CKFRR[911] = 0.0;
_CKFRR[912] = 0.0;
_CKFRR[913] = 0.0;
_CKFRR[914] = 0.0;
_CKFRR[915] = 0.0;
_CKFRR[916] = 0.0;
_CKFRR[917] = 0.0;
_CKFRR[918] = 0.0;
_CKFRR[919] = 0.0;
_CKFRR[920] = 0.0;
_CKFRR[921] = 0.0;
_CKFRR[922] = 0.0;
_CKFRR[923] = 0.0;
_CKFRR[924] = 0.0;
_CKFRR[925] = 0.0;
_CKFRR[926] = 0.0;
_CKFRR[927] = 0.0;
_CKFRR[928] = 0.0;
_CKFRR[929] = 0.0;
_CKFRR[930] = 0.0;
_CKFRR[931] = 0.0;
_CKFRR[932] = 0.0;
_CKFRR[933] = 0.0;
_CKFRR[934] = 0.0;
_CKFRR[935] = 0.0;
_CKFRR[936] = 0.0;
_CKFRR[937] = 0.0;
_CKFRR[938] = 0.0;
_CKFRR[939] = 0.0;
_CKFRR[940] = 0.0;
_CKFRR[941] = 0.0;
_CKFRR[942] = 0.0;
_CKFRR[943] = 0.0;
_CKFRR[944] = 0.0;
_CKFRR[945] = 0.0;
_CKFRR[946] = 0.0;
_CKFRR[947] = 0.0;
_CKFRR[948] = 0.0;
_CKFRR[949] = 0.0;
_CKFRR[950] = 0.0;
_CKFRR[951] = 0.0;
_CKFRR[952] = 0.0;
_CKFRR[953] = 0.0;
_CKFRR[954] = 0.0;
_CKFRR[955] = 0.0;
_CKFRR[956] = 0.0;
_CKFRR[957] = 0.0;
_CKFRR[958] = 0.0;
_CKFRR[959] = 0.0;
_CKFRR[960] = 0.0;
_CKFRR[961] = 0.0;
_CKFRR[962] = 0.0;
_CKFRR[963] = 0.0;
_CKFRR[964] = 0.0;
_CKFRR[965] = 0.0;
_CKFRR[966] = 0.0;
_CKFRR[967] = 0.0;
_CKFRR[968] = 0.0;
_CKFRR[969] = 0.0;
_CKFRR[970] = 0.0;
_CKFRR[971] = 0.0;
_CKFRR[972] = 0.0;
_CKFRR[973] = 0.0;
_CKFRR[974] = 0.0;
_CKFRR[975] = 0.0;
_CKFRR[976] = 0.0;
_CKFRR[977] = 0.0;
_CKFRR[978] = 0.0;
_CKFRR[979] = 0.0;
_CKFRR[980] = 0.0;
_CKFRR[981] = 0.0;
_CKFRR[982] = 0.0;
_CKFRR[983] = 0.0;
_CKFRR[984] = 0.0;
_CKFRR[985] = 0.0;
_CKFRR[986] = 0.0;
_CKFRR[987] = 0.0;
_CKFRR[988] = 0.0;
_CKFRR[989] = 0.0;
_CKFRR[990] = 0.0;
_CKFRR[991] = 0.0;
_CKFRR[992] = 0.0;
_CKFRR[993] = 0.0;
_CKFRR[994] = 0.0;
_CKFRR[995] = 0.0;
_CKFRR[996] = 0.0;
_CKFRR[997] = 0.0;
_CKFRR[998] = 0.0;
_CKFRR[999] = 0.0;
_CKFRR[1000] = 0.0;
_CKFRR[1001] = 0.0;
_CKFRR[1002] = 0.0;
_CKFRR[1003] = 0.0;
_CKFRR[1004] = 0.0;
_CKFRR[1005] = 0.0;
_CKFRR[1006] = 0.0;
_CKFRR[1007] = 0.0;
_CKFRR[1008] = 0.0;
_CKFRR[1009] = 0.0;
_CKFRR[1010] = 0.0;
_CKFRR[1011] = 0.0;
_CKFRR[1012] = atom9508*atom66382;
_CKFRR[1013] =  atom66384*atom9557+atom66383*atom9508;
_CKFRR[1014] = atom66388*atom9557;
_CKFRR[1015] =  atom66393*atom9557+atom66390*atom9508;
_CKFRR[1016] =  atom66402*atom9557+atom66399*atom9508;
_CKFRR[1017] =  atom9508*atom66406+atom66409*atom9557;
_CKFRR[1018] = 0.0;
_CKFRR[1019] =  atom9508*atom66413+atom9557*atom66416;
_CKFRR[1020] = 0.0;
_CKFRR[1021] = 0.0;
_CKFRR[1022] = 0.0;
_CKFRR[1023] =  atom66421*atom9557+atom9508*atom66420;
_CKFRR[1024] =  atom66426*atom9557+atom66423*atom9508;
_CKFRR[1025] =  atom66433*atom9557+atom9508*atom66430;
_CKFRR[1026] = 0.0;
_CKFRR[1027] = 0.0;
_CKFRR[1028] = 0.0;
_CKFRR[1029] = 0.0;
_CKFRR[1030] = 0.0;
_CKFRR[1031] = 0.0;
_CKFRR[1032] = 0.0;
_CKFRR[1033] = 0.0;
_CKFRR[1034] = 0.0;
_CKFRR[1035] =  atom9557*atom66438+atom66437*atom9508;
_CKFRR[1036] =  atom66442*atom9557+atom9508*atom66440;
_CKFRR[1037] =  atom66448*atom9557+atom9508*atom66445;
_CKFRR[1038] = 0.0;
_CKFRR[1039] = 0.0;
_CKFRR[1040] = 0.0;
_CKFRR[1041] = 0.0;
_CKFRR[1042] = 0.0;
_CKFRR[1043] = 0.0;
_CKFRR[1044] = 0.0;
_CKFRR[1045] = 0.0;
_CKFRR[1046] = 0.0;
_CKFRR[1047] = 0.0;
_CKFRR[1048] = 0.0;
_CKFRR[1049] = 0.0;
_CKFRR[1050] = 0.0;
_CKFRR[1051] = 0.0;
_CKFRR[1052] = 0.0;
_CKFRR[1053] = 0.0;
_CKFRR[1054] = 0.0;
_CKFRR[1055] = 0.0;
_CKFRR[1056] = atom66274*atom66382;
_CKFRR[1057] =  atom66495+atom66384*atom66348+atom66383*atom66274;
_CKFRR[1058] =  atom66388*atom66348+atom66530;
_CKFRR[1059] =  atom66572+atom66393*atom66348+atom66390*atom66274;
_CKFRR[1060] =  atom66402*atom66348+atom66622+atom66399*atom66274;
_CKFRR[1061] =  atom66274*atom66406+atom66672+atom66348*atom66409;
_CKFRR[1062] = 0.0;
_CKFRR[1063] =  atom66722+atom66274*atom66413+atom66348*atom66416;
_CKFRR[1064] = 0.0;
_CKFRR[1065] = 0.0;
_CKFRR[1066] = 0.0;
_CKFRR[1067] =  atom66421*atom66348+atom66274*atom66420+atom66772;
_CKFRR[1068] =  atom66822+atom66423*atom66274+atom66426*atom66348;
_CKFRR[1069] =  atom66274*atom66430+atom66872+atom66433*atom66348;
_CKFRR[1070] = 0.0;
_CKFRR[1071] = 0.0;
_CKFRR[1072] = 0.0;
_CKFRR[1073] = 0.0;
_CKFRR[1074] = 0.0;
_CKFRR[1075] = 0.0;
_CKFRR[1076] = 0.0;
_CKFRR[1077] = 0.0;
_CKFRR[1078] = 0.0;
_CKFRR[1079] =  atom66437*atom66274+atom66922+atom66348*atom66438;
_CKFRR[1080] =  atom66440*atom66274+atom66442*atom66348+atom66972;
_CKFRR[1081] =  atom67022+atom66448*atom66348+atom66274*atom66445;
_CKFRR[1082] = 0.0;
_CKFRR[1083] = 0.0;
_CKFRR[1084] = 0.0;
_CKFRR[1085] = 0.0;
_CKFRR[1086] = 0.0;
_CKFRR[1087] = 0.0;
_CKFRR[1088] = 0.0;
_CKFRR[1089] = 0.0;
_CKFRR[1090] = 0.0;
_CKFRR[1091] = 0.0;
_CKFRR[1092] = 0.0;
_CKFRR[1093] = 0.0;
_CKFRR[1094] = 0.0;
_CKFRR[1095] = 0.0;
_CKFRR[1096] = 0.0;
_CKFRR[1097] = 0.0;
_CKFRR[1098] = 0.0;
_CKFRR[1099] = 0.0;
_CKFRR[1100] = atom66309*atom66382;
_CKFRR[1101] =  atom66384*atom66354+atom66381*atom66387+atom66383*atom66309;
_CKFRR[1102] =  atom66381*atom66389+atom66388*atom66354;
_CKFRR[1103] =  atom66381*atom66398+atom66390*atom66309+atom66393*atom66354;
_CKFRR[1104] =  atom66381*atom66405+atom66402*atom66354+atom66399*atom66309;
_CKFRR[1105] =  atom66354*atom66409+atom66412*atom66381+atom66309*atom66406;
_CKFRR[1106] = 0.0;
_CKFRR[1107] =  atom66309*atom66413+atom66354*atom66416+atom66419*atom66381;
_CKFRR[1108] = 0.0;
_CKFRR[1109] = 0.0;
_CKFRR[1110] = 0.0;
_CKFRR[1111] =  atom66354*atom66421+atom66381*atom66422+atom66309*atom66420;
_CKFRR[1112] =  atom66423*atom66309+atom66354*atom66426+atom66381*atom66429;
_CKFRR[1113] =  atom66381*atom66436+atom66309*atom66430+atom66433*atom66354;
_CKFRR[1114] = 0.0;
_CKFRR[1115] = 0.0;
_CKFRR[1116] = 0.0;
_CKFRR[1117] = 0.0;
_CKFRR[1118] = 0.0;
_CKFRR[1119] = 0.0;
_CKFRR[1120] = 0.0;
_CKFRR[1121] = 0.0;
_CKFRR[1122] = 0.0;
_CKFRR[1123] =  atom66439*atom66381+atom66354*atom66438+atom66437*atom66309;
_CKFRR[1124] =  atom66354*atom66442+atom66381*atom66444+atom66309*atom66440;
_CKFRR[1125] =  atom66381*atom66451+atom66309*atom66445+atom66448*atom66354;
_CKFRR[1126] = 0.0;
_CKFRR[1127] = 0.0;
_CKFRR[1128] = 0.0;
_CKFRR[1129] = 0.0;
_CKFRR[1130] = 0.0;
_CKFRR[1131] = 0.0;
_CKFRR[1132] = 0.0;
_CKFRR[1133] = 0.0;
_CKFRR[1134] = 0.0;
_CKFRR[1135] = 0.0;
_CKFRR[1136] = 0.0;
_CKFRR[1137] = 0.0;
_CKFRR[1138] = 0.0;
_CKFRR[1139] = 0.0;
_CKFRR[1140] = 0.0;
_CKFRR[1141] = 0.0;
_CKFRR[1142] = 0.0;
_CKFRR[1143] = 0.0;
_CKFRR[1144] = 0.0;
_CKFRR[1145] = 0.0;
_CKFRR[1146] = 0.0;
_CKFRR[1147] = 0.0;
_CKFRR[1148] = 0.0;
_CKFRR[1149] = 0.0;
_CKFRR[1150] = 0.0;
_CKFRR[1151] = 0.0;
_CKFRR[1152] = 0.0;
_CKFRR[1153] = 0.0;
_CKFRR[1154] = 0.0;
_CKFRR[1155] = 0.0;
_CKFRR[1156] = 0.0;
_CKFRR[1157] = 0.0;
_CKFRR[1158] = 0.0;
_CKFRR[1159] = 0.0;
_CKFRR[1160] = 0.0;
_CKFRR[1161] = 0.0;
_CKFRR[1162] = 0.0;
_CKFRR[1163] = 0.0;
_CKFRR[1164] = 0.0;
_CKFRR[1165] = 0.0;
_CKFRR[1166] = 0.0;
_CKFRR[1167] = 0.0;
_CKFRR[1168] = 0.0;
_CKFRR[1169] = 0.0;
_CKFRR[1170] = 0.0;
_CKFRR[1171] = 0.0;
_CKFRR[1172] = 0.0;
_CKFRR[1173] = 0.0;
_CKFRR[1174] = 0.0;
_CKFRR[1175] = 0.0;
_CKFRR[1176] = 0.0;
_CKFRR[1177] = 0.0;
_CKFRR[1178] = 0.0;
_CKFRR[1179] = 0.0;
_CKFRR[1180] = 0.0;
_CKFRR[1181] = 0.0;
_CKFRR[1182] = 0.0;
_CKFRR[1183] = 0.0;
_CKFRR[1184] = 0.0;
_CKFRR[1185] = 0.0;
_CKFRR[1186] = 0.0;
_CKFRR[1187] = 0.0;
_CKFRR[1188] = 0.0;
_CKFRR[1189] = 0.0;
_CKFRR[1190] = 0.0;
_CKFRR[1191] = 0.0;
_CKFRR[1192] = 0.0;
_CKFRR[1193] = 0.0;
_CKFRR[1194] = 0.0;
_CKFRR[1195] = 0.0;
_CKFRR[1196] = 0.0;
_CKFRR[1197] = 0.0;
_CKFRR[1198] = 0.0;
_CKFRR[1199] = 0.0;
_CKFRR[1200] = 0.0;
_CKFRR[1201] = 0.0;
_CKFRR[1202] = 0.0;
_CKFRR[1203] = 0.0;
_CKFRR[1204] = 0.0;
_CKFRR[1205] = 0.0;
_CKFRR[1206] = 0.0;
_CKFRR[1207] = 0.0;
_CKFRR[1208] = 0.0;
_CKFRR[1209] = 0.0;
_CKFRR[1210] = 0.0;
_CKFRR[1211] = 0.0;
_CKFRR[1212] = 0.0;
_CKFRR[1213] = 0.0;
_CKFRR[1214] = 0.0;
_CKFRR[1215] = 0.0;
_CKFRR[1216] = 0.0;
_CKFRR[1217] = 0.0;
_CKFRR[1218] = 0.0;
_CKFRR[1219] = 0.0;
_CKFRR[1220] = 0.0;
_CKFRR[1221] = 0.0;
_CKFRR[1222] = 0.0;
_CKFRR[1223] = 0.0;
_CKFRR[1224] = 0.0;
_CKFRR[1225] = 0.0;
_CKFRR[1226] = 0.0;
_CKFRR[1227] = 0.0;
_CKFRR[1228] = 0.0;
_CKFRR[1229] = 0.0;
_CKFRR[1230] = 0.0;
_CKFRR[1231] = 0.0;
_CKFRR[1232] = 0.0;
_CKFRR[1233] = 0.0;
_CKFRR[1234] = 0.0;
_CKFRR[1235] = 0.0;
_CKFRR[1236] = 0.0;
_CKFRR[1237] = 0.0;
_CKFRR[1238] = 0.0;
_CKFRR[1239] = 0.0;
_CKFRR[1240] = 0.0;
_CKFRR[1241] = 0.0;
_CKFRR[1242] = 0.0;
_CKFRR[1243] = 0.0;
_CKFRR[1244] = 0.0;
_CKFRR[1245] = 0.0;
_CKFRR[1246] = 0.0;
_CKFRR[1247] = 0.0;
_CKFRR[1248] = 0.0;
_CKFRR[1249] = 0.0;
_CKFRR[1250] = 0.0;
_CKFRR[1251] = 0.0;
_CKFRR[1252] = 0.0;
_CKFRR[1253] = 0.0;
_CKFRR[1254] = 0.0;
_CKFRR[1255] = 0.0;
_CKFRR[1256] = 0.0;
_CKFRR[1257] = 0.0;
_CKFRR[1258] = 0.0;
_CKFRR[1259] = 0.0;
_CKFRR[1260] = 0.0;
_CKFRR[1261] = 0.0;
_CKFRR[1262] = 0.0;
_CKFRR[1263] = 0.0;
_CKFRR[1264] = 0.0;
_CKFRR[1265] = 0.0;
_CKFRR[1266] = 0.0;
_CKFRR[1267] = 0.0;
_CKFRR[1268] = 0.0;
_CKFRR[1269] = 0.0;
_CKFRR[1270] = 0.0;
_CKFRR[1271] = 0.0;
_CKFRR[1272] = 0.0;
_CKFRR[1273] = 0.0;
_CKFRR[1274] = 0.0;
_CKFRR[1275] = 0.0;
_CKFRR[1276] = 0.0;
_CKFRR[1277] = 0.0;
_CKFRR[1278] = 0.0;
_CKFRR[1279] = 0.0;
_CKFRR[1280] = 0.0;
_CKFRR[1281] = 0.0;
_CKFRR[1282] = 0.0;
_CKFRR[1283] = 0.0;
_CKFRR[1284] = 0.0;
_CKFRR[1285] = 0.0;
_CKFRR[1286] = 0.0;
_CKFRR[1287] = 0.0;
_CKFRR[1288] = 0.0;
_CKFRR[1289] = 0.0;
_CKFRR[1290] = 0.0;
_CKFRR[1291] = 0.0;
_CKFRR[1292] = 0.0;
_CKFRR[1293] = 0.0;
_CKFRR[1294] = 0.0;
_CKFRR[1295] = 0.0;
_CKFRR[1296] = 0.0;
_CKFRR[1297] = 0.0;
_CKFRR[1298] = 0.0;
_CKFRR[1299] = 0.0;
_CKFRR[1300] = 0.0;
_CKFRR[1301] = 0.0;
_CKFRR[1302] = 0.0;
_CKFRR[1303] = 0.0;
_CKFRR[1304] = 0.0;
_CKFRR[1305] = 0.0;
_CKFRR[1306] = 0.0;
_CKFRR[1307] = 0.0;
_CKFRR[1308] = 0.0;
_CKFRR[1309] = 0.0;
_CKFRR[1310] = 0.0;
_CKFRR[1311] = 0.0;
_CKFRR[1312] = 0.0;
_CKFRR[1313] = 0.0;
_CKFRR[1314] = 0.0;
_CKFRR[1315] = 0.0;
_CKFRR[1316] = 0.0;
_CKFRR[1317] = 0.0;
_CKFRR[1318] = 0.0;
_CKFRR[1319] = 0.0;
_CKFRR[1320] = 0.0;
_CKFRR[1321] = 0.0;
_CKFRR[1322] = 0.0;
_CKFRR[1323] = 0.0;
_CKFRR[1324] = 0.0;
_CKFRR[1325] = 0.0;
_CKFRR[1326] = 0.0;
_CKFRR[1327] = 0.0;
_CKFRR[1328] = 0.0;
_CKFRR[1329] = 0.0;
_CKFRR[1330] = 0.0;
_CKFRR[1331] = 0.0;
_CKFRR[1332] = 0.0;
_CKFRR[1333] = 0.0;
_CKFRR[1334] = 0.0;
_CKFRR[1335] = 0.0;
_CKFRR[1336] = 0.0;
_CKFRR[1337] = 0.0;
_CKFRR[1338] = 0.0;
_CKFRR[1339] = 0.0;
_CKFRR[1340] = 0.0;
_CKFRR[1341] = 0.0;
_CKFRR[1342] = 0.0;
_CKFRR[1343] = 0.0;
_CKFRR[1344] = 0.0;
_CKFRR[1345] = 0.0;
_CKFRR[1346] = 0.0;
_CKFRR[1347] = 0.0;
_CKFRR[1348] = 0.0;
_CKFRR[1349] = 0.0;
_CKFRR[1350] = 0.0;
_CKFRR[1351] = 0.0;
_CKFRR[1352] = 0.0;
_CKFRR[1353] = 0.0;
_CKFRR[1354] = 0.0;
_CKFRR[1355] = 0.0;
_CKFRR[1356] = 0.0;
_CKFRR[1357] = 0.0;
_CKFRR[1358] = 0.0;
_CKFRR[1359] = 0.0;
_CKFRR[1360] = 0.0;
_CKFRR[1361] = 0.0;
_CKFRR[1362] = 0.0;
_CKFRR[1363] = 0.0;
_CKFRR[1364] = 0.0;
_CKFRR[1365] = 0.0;
_CKFRR[1366] = 0.0;
_CKFRR[1367] = 0.0;
_CKFRR[1368] = 0.0;
_CKFRR[1369] = 0.0;
_CKFRR[1370] = 0.0;
_CKFRR[1371] = 0.0;
_CKFRR[1372] = 0.0;
_CKFRR[1373] = 0.0;
_CKFRR[1374] = 0.0;
_CKFRR[1375] = 0.0;
_CKFRR[1376] = 0.0;
_CKFRR[1377] = 0.0;
_CKFRR[1378] = 0.0;
_CKFRR[1379] = 0.0;
_CKFRR[1380] = 0.0;
_CKFRR[1381] = 0.0;
_CKFRR[1382] = 0.0;
_CKFRR[1383] = 0.0;
_CKFRR[1384] = 0.0;
_CKFRR[1385] = 0.0;
_CKFRR[1386] = 0.0;
_CKFRR[1387] = 0.0;
_CKFRR[1388] = 0.0;
_CKFRR[1389] = 0.0;
_CKFRR[1390] = 0.0;
_CKFRR[1391] = 0.0;
_CKFRR[1392] = 0.0;
_CKFRR[1393] = 0.0;
_CKFRR[1394] = 0.0;
_CKFRR[1395] = 0.0;
_CKFRR[1396] = 0.0;
_CKFRR[1397] = 0.0;
_CKFRR[1398] = 0.0;
_CKFRR[1399] = 0.0;
_CKFRR[1400] = 0.0;
_CKFRR[1401] = 0.0;
_CKFRR[1402] = 0.0;
_CKFRR[1403] = 0.0;
_CKFRR[1404] = 0.0;
_CKFRR[1405] = 0.0;
_CKFRR[1406] = 0.0;
_CKFRR[1407] = 0.0;
_CKFRR[1408] = 0.0;
_CKFRR[1409] = 0.0;
_CKFRR[1410] = 0.0;
_CKFRR[1411] = 0.0;
_CKFRR[1412] = 0.0;
_CKFRR[1413] = 0.0;
_CKFRR[1414] = 0.0;
_CKFRR[1415] = 0.0;
_CKFRR[1416] = 0.0;
_CKFRR[1417] = 0.0;
_CKFRR[1418] = 0.0;
_CKFRR[1419] = 0.0;
_CKFRR[1420] = 0.0;
_CKFRR[1421] = 0.0;
_CKFRR[1422] = 0.0;
_CKFRR[1423] = 0.0;
_CKFRR[1424] = 0.0;
_CKFRR[1425] = 0.0;
_CKFRR[1426] = 0.0;
_CKFRR[1427] = 0.0;
_CKFRR[1428] = 0.0;
_CKFRR[1429] = 0.0;
_CKFRR[1430] = 0.0;
_CKFRR[1431] = 0.0;
_CKFRR[1432] = 0.0;
_CKFRR[1433] = 0.0;
_CKFRR[1434] = 0.0;
_CKFRR[1435] = 0.0;
_CKFRR[1436] = 0.0;
_CKFRR[1437] = 0.0;
_CKFRR[1438] = 0.0;
_CKFRR[1439] = 0.0;
_CKFRR[1440] = 0.0;
_CKFRR[1441] = 0.0;
_CKFRR[1442] = 0.0;
_CKFRR[1443] = 0.0;
_CKFRR[1444] = 0.0;
_CKFRR[1445] = 0.0;
_CKFRR[1446] = 0.0;
_CKFRR[1447] = 0.0;
_CKFRR[1448] = 0.0;
_CKFRR[1449] = 0.0;
_CKFRR[1450] = 0.0;
_CKFRR[1451] = 0.0;
_CKFRR[1452] = 0.0;
_CKFRR[1453] = 0.0;
_CKFRR[1454] = 0.0;
_CKFRR[1455] = 0.0;
_CKFRR[1456] = 0.0;
_CKFRR[1457] = 0.0;
_CKFRR[1458] = 0.0;
_CKFRR[1459] = 0.0;
_CKFRR[1460] = 0.0;
_CKFRR[1461] = 0.0;
_CKFRR[1462] = 0.0;
_CKFRR[1463] = 0.0;
_CKFRR[1464] = 0.0;
_CKFRR[1465] = 0.0;
_CKFRR[1466] = 0.0;
_CKFRR[1467] = 0.0;
_CKFRR[1468] = 0.0;
_CKFRR[1469] = 0.0;
_CKFRR[1470] = 0.0;
_CKFRR[1471] = 0.0;
_CKFRR[1472] = 0.0;
_CKFRR[1473] = 0.0;
_CKFRR[1474] = 0.0;
_CKFRR[1475] = 0.0;
_CKFRR[1476] = 0.0;
_CKFRR[1477] = 0.0;
_CKFRR[1478] = 0.0;
_CKFRR[1479] = 0.0;
_CKFRR[1480] = 0.0;
_CKFRR[1481] = 0.0;
_CKFRR[1482] = 0.0;
_CKFRR[1483] = 0.0;
_CKFRR[1484] = 0.0;
_CKFRR[1485] = 0.0;
_CKFRR[1486] = 0.0;
_CKFRR[1487] = 0.0;
_CKFRR[1488] = 0.0;
_CKFRR[1489] = 0.0;
_CKFRR[1490] = 0.0;
_CKFRR[1491] = 0.0;
_CKFRR[1492] = 0.0;
_CKFRR[1493] = 0.0;
_CKFRR[1494] = 0.0;
_CKFRR[1495] = 0.0;
_CKFRR[1496] = 0.0;
_CKFRR[1497] = 0.0;
_CKFRR[1498] = 0.0;
_CKFRR[1499] = 0.0;
_CKFRR[1500] = 0.0;
_CKFRR[1501] = 0.0;
_CKFRR[1502] = 0.0;
_CKFRR[1503] = 0.0;
_CKFRR[1504] = 0.0;
_CKFRR[1505] = 0.0;
_CKFRR[1506] = 0.0;
_CKFRR[1507] = 0.0;
_CKFRR[1508] = 0.0;
_CKFRR[1509] = 0.0;
_CKFRR[1510] = 0.0;
_CKFRR[1511] = 0.0;
_CKFRR[1512] = 0.0;
_CKFRR[1513] = 0.0;
_CKFRR[1514] = 0.0;
_CKFRR[1515] = 0.0;
_CKFRR[1516] = 0.0;
_CKFRR[1517] = 0.0;
_CKFRR[1518] = 0.0;
_CKFRR[1519] = 0.0;
_CKFRR[1520] = 0.0;
_CKFRR[1521] = 0.0;
_CKFRR[1522] = 0.0;
_CKFRR[1523] = 0.0;
_CKFRR[1524] = 0.0;
_CKFRR[1525] = 0.0;
_CKFRR[1526] = 0.0;
_CKFRR[1527] = 0.0;
_CKFRR[1528] = 0.0;
_CKFRR[1529] = 0.0;
_CKFRR[1530] = 0.0;
_CKFRR[1531] = 0.0;
_CKFRR[1532] = 0.0;
_CKFRR[1533] = 0.0;
_CKFRR[1534] = 0.0;
_CKFRR[1535] = 0.0;
_CKFRR[1536] = 0.0;
_CKFRR[1537] = 0.0;
_CKFRR[1538] = 0.0;
_CKFRR[1539] = 0.0;
_CKFRR[1540] = 0.0;
_CKFRR[1541] = 0.0;
_CKFRR[1542] = 0.0;
_CKFRR[1543] = 0.0;
_CKFRR[1544] = 0.0;
_CKFRR[1545] = 0.0;
_CKFRR[1546] = 0.0;
_CKFRR[1547] = 0.0;
_CKFRR[1548] = 0.0;
_CKFRR[1549] = 0.0;
_CKFRR[1550] = 0.0;
_CKFRR[1551] = 0.0;
_CKFRR[1552] = 0.0;
_CKFRR[1553] = 0.0;
_CKFRR[1554] = 0.0;
_CKFRR[1555] = 0.0;
_CKFRR[1556] = 0.0;
_CKFRR[1557] = 0.0;
_CKFRR[1558] = 0.0;
_CKFRR[1559] = 0.0;
_CKFRR[1560] = 0.0;
_CKFRR[1561] = 0.0;
_CKFRR[1562] = 0.0;
_CKFRR[1563] = 0.0;
_CKFRR[1564] = 0.0;
_CKFRR[1565] = 0.0;
_CKFRR[1566] = 0.0;
_CKFRR[1567] = 0.0;
_CKFRR[1568] = 0.0;
_CKFRR[1569] = 0.0;
_CKFRR[1570] = 0.0;
_CKFRR[1571] = 0.0;
_CKFRR[1572] = 0.0;
_CKFRR[1573] = 0.0;
_CKFRR[1574] = 0.0;
_CKFRR[1575] = 0.0;
_CKFRR[1576] = 0.0;
_CKFRR[1577] = 0.0;
_CKFRR[1578] = 0.0;
_CKFRR[1579] = 0.0;
_CKFRR[1580] = 0.0;
_CKFRR[1581] = 0.0;
_CKFRR[1582] = 0.0;
_CKFRR[1583] = 0.0;
_CKFRR[1584] = 0.0;
_CKFRR[1585] = 0.0;
_CKFRR[1586] = 0.0;
_CKFRR[1587] = 0.0;
_CKFRR[1588] = 0.0;
_CKFRR[1589] = 0.0;
_CKFRR[1590] = 0.0;
_CKFRR[1591] = 0.0;
_CKFRR[1592] = 0.0;
_CKFRR[1593] = 0.0;
_CKFRR[1594] = 0.0;
_CKFRR[1595] = 0.0;
_CKFRR[1596] = 0.0;
_CKFRR[1597] = 0.0;
_CKFRR[1598] = 0.0;
_CKFRR[1599] = 0.0;
_CKFRR[1600] = 0.0;
_CKFRR[1601] = 0.0;
_CKFRR[1602] = 0.0;
_CKFRR[1603] = 0.0;
_CKFRR[1604] = 0.0;
_CKFRR[1605] = 0.0;
_CKFRR[1606] = 0.0;
_CKFRR[1607] = 0.0;
_CKFRR[1608] = 0.0;
_CKFRR[1609] = 0.0;
_CKFRR[1610] = 0.0;
_CKFRR[1611] = 0.0;
_CKFRR[1612] = 0.0;
_CKFRR[1613] = 0.0;
_CKFRR[1614] = 0.0;
_CKFRR[1615] = 0.0;
_CKFRR[1616] = 0.0;
_CKFRR[1617] = 0.0;
_CKFRR[1618] = 0.0;
_CKFRR[1619] = 0.0;
_CKFRR[1620] = 0.0;
_CKFRR[1621] = 0.0;
_CKFRR[1622] = 0.0;
_CKFRR[1623] = 0.0;
_CKFRR[1624] = 0.0;
_CKFRR[1625] = 0.0;
_CKFRR[1626] = 0.0;
_CKFRR[1627] = 0.0;
_CKFRR[1628] = 0.0;
_CKFRR[1629] = 0.0;
_CKFRR[1630] = 0.0;
_CKFRR[1631] = 0.0;
_CKFRR[1632] = 0.0;
_CKFRR[1633] = 0.0;
_CKFRR[1634] = 0.0;
_CKFRR[1635] = 0.0;
_CKFRR[1636] = 0.0;
_CKFRR[1637] = 0.0;
_CKFRR[1638] = 0.0;
_CKFRR[1639] = 0.0;
_CKFRR[1640] = 0.0;
_CKFRR[1641] = 0.0;
_CKFRR[1642] = 0.0;
_CKFRR[1643] = 0.0;
_CKFRR[1644] = 0.0;
_CKFRR[1645] = 0.0;
_CKFRR[1646] = 0.0;
_CKFRR[1647] = 0.0;
_CKFRR[1648] = 0.0;
_CKFRR[1649] = 0.0;
_CKFRR[1650] = 0.0;
_CKFRR[1651] = 0.0;
_CKFRR[1652] = 0.0;
_CKFRR[1653] = 0.0;
_CKFRR[1654] = 0.0;
_CKFRR[1655] = 0.0;
_CKFRR[1656] = 0.0;
_CKFRR[1657] = 0.0;
_CKFRR[1658] = 0.0;
_CKFRR[1659] = 0.0;
_CKFRR[1660] = 0.0;
_CKFRR[1661] = 0.0;
_CKFRR[1662] = 0.0;
_CKFRR[1663] = 0.0;
_CKFRR[1664] = 0.0;
_CKFRR[1665] = 0.0;
_CKFRR[1666] = 0.0;
_CKFRR[1667] = 0.0;
_CKFRR[1668] = 0.0;
_CKFRR[1669] = 0.0;
_CKFRR[1670] = 0.0;
_CKFRR[1671] = 0.0;
_CKFRR[1672] = 0.0;
_CKFRR[1673] = 0.0;
_CKFRR[1674] = 0.0;
_CKFRR[1675] = 0.0;
_CKFRR[1676] = 0.0;
_CKFRR[1677] = 0.0;
_CKFRR[1678] = 0.0;
_CKFRR[1679] = 0.0;
_CKFRR[1680] = 0.0;
_CKFRR[1681] = 0.0;
_CKFRR[1682] = 0.0;
_CKFRR[1683] = 0.0;
_CKFRR[1684] = 0.0;
_CKFRR[1685] = 0.0;
_CKFRR[1686] = 0.0;
_CKFRR[1687] = 0.0;
_CKFRR[1688] = 0.0;
_CKFRR[1689] = 0.0;
_CKFRR[1690] = 0.0;
_CKFRR[1691] = 0.0;
_CKFRR[1692] = 0.0;
_CKFRR[1693] = 0.0;
_CKFRR[1694] = 0.0;
_CKFRR[1695] = 0.0;
_CKFRR[1696] = 0.0;
_CKFRR[1697] = 0.0;
_CKFRR[1698] = 0.0;
_CKFRR[1699] = 0.0;
_CKFRR[1700] = 0.0;
_CKFRR[1701] = 0.0;
_CKFRR[1702] = 0.0;
_CKFRR[1703] = 0.0;
_CKFRR[1704] = 0.0;
_CKFRR[1705] = 0.0;
_CKFRR[1706] = 0.0;
_CKFRR[1707] = 0.0;
_CKFRR[1708] = 0.0;
_CKFRR[1709] = 0.0;
_CKFRR[1710] = 0.0;
_CKFRR[1711] = 0.0;
_CKFRR[1712] = 0.0;
_CKFRR[1713] = 0.0;
_CKFRR[1714] = 0.0;
_CKFRR[1715] = 0.0;
_CKFRR[1716] = 0.0;
_CKFRR[1717] = 0.0;
_CKFRR[1718] = 0.0;
_CKFRR[1719] = 0.0;
_CKFRR[1720] = 0.0;
_CKFRR[1721] = 0.0;
_CKFRR[1722] = 0.0;
_CKFRR[1723] = 0.0;
_CKFRR[1724] = 0.0;
_CKFRR[1725] = 0.0;
_CKFRR[1726] = 0.0;
_CKFRR[1727] = 0.0;
_CKFRR[1728] = 0.0;
_CKFRR[1729] = 0.0;
_CKFRR[1730] = 0.0;
_CKFRR[1731] = 0.0;
_CKFRR[1732] = 0.0;
_CKFRR[1733] = 0.0;
_CKFRR[1734] = 0.0;
_CKFRR[1735] = 0.0;
_CKFRR[1736] = 0.0;
_CKFRR[1737] = 0.0;
_CKFRR[1738] = 0.0;
_CKFRR[1739] = 0.0;
_CKFRR[1740] = 0.0;
_CKFRR[1741] = 0.0;
_CKFRR[1742] = 0.0;
_CKFRR[1743] = 0.0;
_CKFRR[1744] = 0.0;
_CKFRR[1745] = 0.0;
_CKFRR[1746] = 0.0;
_CKFRR[1747] = 0.0;
_CKFRR[1748] = 0.0;
_CKFRR[1749] = 0.0;
_CKFRR[1750] = 0.0;
_CKFRR[1751] = 0.0;
_CKFRR[1752] = 0.0;
_CKFRR[1753] = 0.0;
_CKFRR[1754] = 0.0;
_CKFRR[1755] = 0.0;
_CKFRR[1756] = 0.0;
_CKFRR[1757] = 0.0;
_CKFRR[1758] = 0.0;
_CKFRR[1759] = 0.0;
_CKFRR[1760] = 0.0;
_CKFRR[1761] = 0.0;
_CKFRR[1762] = 0.0;
_CKFRR[1763] = 0.0;
_CKFRR[1764] = 0.0;
_CKFRR[1765] = 0.0;
_CKFRR[1766] = 0.0;
_CKFRR[1767] = 0.0;
_CKFRR[1768] = 0.0;
_CKFRR[1769] = 0.0;
_CKFRR[1770] = 0.0;
_CKFRR[1771] = 0.0;
_CKFRR[1772] = 0.0;
_CKFRR[1773] = 0.0;
_CKFRR[1774] = 0.0;
_CKFRR[1775] = 0.0;
_CKFRR[1776] = 0.0;
_CKFRR[1777] = 0.0;
_CKFRR[1778] = 0.0;
_CKFRR[1779] = 0.0;
_CKFRR[1780] = 0.0;
_CKFRR[1781] = 0.0;
_CKFRR[1782] = 0.0;
_CKFRR[1783] = 0.0;
_CKFRR[1784] = 0.0;
_CKFRR[1785] = 0.0;
_CKFRR[1786] = 0.0;
_CKFRR[1787] = 0.0;
_CKFRR[1788] = 0.0;
_CKFRR[1789] = 0.0;
_CKFRR[1790] = 0.0;
_CKFRR[1791] = 0.0;
_CKFRR[1792] = 0.0;
_CKFRR[1793] = 0.0;
_CKFRR[1794] = 0.0;
_CKFRR[1795] = 0.0;
_CKFRR[1796] = 0.0;
_CKFRR[1797] = 0.0;
_CKFRR[1798] = 0.0;
_CKFRR[1799] = 0.0;
_CKFRR[1800] = 0.0;
_CKFRR[1801] = 0.0;
_CKFRR[1802] = 0.0;
_CKFRR[1803] = 0.0;
_CKFRR[1804] = 0.0;
_CKFRR[1805] = 0.0;
_CKFRR[1806] = 0.0;
_CKFRR[1807] = 0.0;
_CKFRR[1808] = 0.0;
_CKFRR[1809] = 0.0;
_CKFRR[1810] = 0.0;
_CKFRR[1811] = 0.0;
_CKFRR[1812] = 0.0;
_CKFRR[1813] = 0.0;
_CKFRR[1814] = 0.0;
_CKFRR[1815] = 0.0;
_CKFRR[1816] = 0.0;
_CKFRR[1817] = 0.0;
_CKFRR[1818] = 0.0;
_CKFRR[1819] = 0.0;
_CKFRR[1820] = 0.0;
_CKFRR[1821] = 0.0;
_CKFRR[1822] = 0.0;
_CKFRR[1823] = 0.0;
_CKFRR[1824] = 0.0;
_CKFRR[1825] = 0.0;
_CKFRR[1826] = 0.0;
_CKFRR[1827] = 0.0;
_CKFRR[1828] = 0.0;
_CKFRR[1829] = 0.0;
_CKFRR[1830] = 0.0;
_CKFRR[1831] = 0.0;
_CKFRR[1832] = 0.0;
_CKFRR[1833] = 0.0;
_CKFRR[1834] = 0.0;
_CKFRR[1835] = 0.0;
_CKFRR[1836] = 0.0;
_CKFRR[1837] = 0.0;
_CKFRR[1838] = 0.0;
_CKFRR[1839] = 0.0;
_CKFRR[1840] = 0.0;
_CKFRR[1841] = 0.0;
_CKFRR[1842] = 0.0;
_CKFRR[1843] = 0.0;
_CKFRR[1844] = 0.0;
_CKFRR[1845] = 0.0;
_CKFRR[1846] = 0.0;
_CKFRR[1847] = 0.0;
_CKFRR[1848] = 0.0;
_CKFRR[1849] = 0.0;
_CKFRR[1850] = 0.0;
_CKFRR[1851] = 0.0;
_CKFRR[1852] = 0.0;
_CKFRR[1853] = 0.0;
_CKFRR[1854] = 0.0;
_CKFRR[1855] = 0.0;
_CKFRR[1856] = 0.0;
_CKFRR[1857] = 0.0;
_CKFRR[1858] = 0.0;
_CKFRR[1859] = 0.0;
_CKFRR[1860] = 0.0;
_CKFRR[1861] = 0.0;
_CKFRR[1862] = 0.0;
_CKFRR[1863] = 0.0;
_CKFRR[1864] = 0.0;
_CKFRR[1865] = 0.0;
_CKFRR[1866] = 0.0;
_CKFRR[1867] = 0.0;
_CKFRR[1868] = 0.0;
_CKFRR[1869] = 0.0;
_CKFRR[1870] = 0.0;
_CKFRR[1871] = 0.0;
_CKFRR[1872] = 0.0;
_CKFRR[1873] = 0.0;
_CKFRR[1874] = 0.0;
_CKFRR[1875] = 0.0;
_CKFRR[1876] = 0.0;
_CKFRR[1877] = 0.0;
_CKFRR[1878] = 0.0;
_CKFRR[1879] = 0.0;
_CKFRR[1880] = 0.0;
_CKFRR[1881] = 0.0;
_CKFRR[1882] = 0.0;
_CKFRR[1883] = 0.0;
_CKFRR[1884] = 0.0;
_CKFRR[1885] = 0.0;
_CKFRR[1886] = 0.0;
_CKFRR[1887] = 0.0;
_CKFRR[1888] = 0.0;
_CKFRR[1889] = 0.0;
_CKFRR[1890] = 0.0;
_CKFRR[1891] = 0.0;
_CKFRR[1892] = 0.0;
_CKFRR[1893] = 0.0;
_CKFRR[1894] = 0.0;
_CKFRR[1895] = 0.0;
_CKFRR[1896] = 0.0;
_CKFRR[1897] = 0.0;
_CKFRR[1898] = 0.0;
_CKFRR[1899] = 0.0;
_CKFRR[1900] = 0.0;
_CKFRR[1901] = 0.0;
_CKFRR[1902] = 0.0;
_CKFRR[1903] = 0.0;
_CKFRR[1904] = 0.0;
_CKFRR[1905] = 0.0;
_CKFRR[1906] = 0.0;
_CKFRR[1907] = 0.0;
_CKFRR[1908] = 0.0;
_CKFRR[1909] = 0.0;
_CKFRR[1910] = 0.0;
_CKFRR[1911] = 0.0;
_CKFRR[1912] = 0.0;
_CKFRR[1913] = 0.0;
_CKFRR[1914] = 0.0;
_CKFRR[1915] = 0.0;
_CKFRR[1916] = 0.0;
_CKFRR[1917] = 0.0;
_CKFRR[1918] = 0.0;
_CKFRR[1919] = 0.0;
_CKFRR[1920] = 0.0;
_CKFRR[1921] = 0.0;
_CKFRR[1922] = 0.0;
_CKFRR[1923] = 0.0;
_CKFRR[1924] = 0.0;
_CKFRR[1925] = 0.0;
_CKFRR[1926] = 0.0;
_CKFRR[1927] = 0.0;
_CKFRR[1928] = 0.0;
_CKFRR[1929] = 0.0;
_CKFRR[1930] = 0.0;
_CKFRR[1931] = 0.0;
_CKFRR[1932] = 0.0;
_CKFRR[1933] = 0.0;
_CKFRR[1934] = 0.0;
_CKFRR[1935] = 0.0;

return _CKFRR;
}
