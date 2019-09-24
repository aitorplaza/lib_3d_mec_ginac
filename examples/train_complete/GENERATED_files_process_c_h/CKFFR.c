/*----------CKFFR.c lib3D_MEC exported-----------*/

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

#include "CKFFR.h"

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
double atom2894;
double atom2930;
double atom2938;
double atom2939;
double atom64596;
double atom2940;
double atom1172;
double atom1174;
double atom1019;
double atom1195;
double atom1173;
double atom1194;
double atom1496;
double atom1497;
double atom1175;
double atom1018;
double atom1512;
double atom2720;
double atom2726;
double atom1530;
double atom2727;
double atom1016;
double atom1533;
double atom1514;
double atom1515;
double atom1017;
double atom498;
double atom1551;
double atom497;
double atom1548;
double atom1571;
double atom2729;
double atom1574;
double atom1702;
double atom2730;
double atom1022;
double atom2741;
double atom1023;
double atom2732;
double atom2746;
double atom2733;
double atom1021;
double atom2737;
double atom2740;
double atom2752;
double atom0;
double atom2753;
double atom22217;
double atom22218;
double atom22214;
double atom22215;
double atom22221;
double atom22225;
double atom22224;
double atom22240;
double atom1176;
double atom22246;
double atom58338;
double atom64408;
double atom1177;
double atom58337;
double atom64413;
double atom1178;
double atom1179;
double atom1184;
double atom1185;
double atom1187;
double atom22230;
double atom1500;
double atom1521;
double atom1503;
double atom1539;
double atom1536;
double atom1562;
double atom1559;
double atom1518;
double atom22244;
double atom58348;
double atom64417;
double atom1181;
double atom1191;
double atom1193;
double atom1180;
double atom1190;
double atom22235;
double atom1506;
double atom1527;
double atom1509;
double atom1545;
double atom1542;
double atom1568;
double atom1565;
double atom1524;
double atom22245;
double atom58345;
double atom64424;
double atom64425;
double atom64429;
double atom3814;
double atom60833;
double atom42760;
double atom64433;
double atom60839;
double atom42906;
double atom64440;
double atom8887;
double atom58356;
double atom58358;
double atom58360;
double atom58364;
double atom58367;
double atom41956;
double atom40896;
double atom64448;
double atom40899;
double atom64442;
double atom64445;
double atom64461;
double atom64453;
double atom58369;
double atom64463;
double atom64450;
double atom64455;
double atom58374;
double atom64456;
double atom64466;
double atom42824;
double atom42819;
double atom40806;
double atom40875;
double atom40804;
double atom64468;
double atom64471;
double atom42841;
double atom64475;
double atom64480;
double atom42934;
double atom64485;
double atom6041;
double atom6036;
double atom6037;
double atom6044;
double atom8896;
double atom64488;
double atom42093;
double atom64491;
double atom42081;
double atom64500;
double atom64494;
double atom64489;
double atom64496;
double atom64512;
double atom64502;
double atom64506;
double atom64508;
double atom64514;
double atom64519;
double atom64523;
double atom64597;
double atom2826;
double atom2827;
double atom2828;
double atom2897;
double atom2943;
double atom64598;
double atom2944;
double atom64600;
double atom2899;
double atom2898;
double atom2932;
double atom2934;
double atom2933;
double atom64601;
double atom64571;
double atom58341;
double atom64530;
double atom58351;
double atom64537;
double atom2935;
double atom64576;
double atom64538;
double atom64580;
double atom42756;
double atom64545;
double atom8936;
double atom64585;
double atom58379;
double atom64548;
double atom64552;
double atom64709;
double atom64590;
double atom42835;
double atom64559;
double atom8945;
double atom64562;
double atom64595;
double atom64568;
double atom64602;
double atom64603;
double atom64744;
double atom40803;
double atom40902;
double atom41903;
double atom41900;
double atom42072;
double atom40898;
double atom42084;
double atom59883;
double atom59897;
double atom59901;
double atom59889;
double atom64604;
double atom64331;
double atom64343;
double atom22168;
double atom64336;
double atom64346;
double atom64607;
double atom64609;
double atom64610;
double atom64612;
double atom64786;
double atom40903;
double atom41907;
double atom41905;
double atom42087;
double atom42075;
double atom59926;
double atom59920;
double atom59934;
double atom59938;
double atom64613;
double atom64352;
double atom64357;
double atom64616;
double atom64619;
double atom64836;
double atom59959;
double atom59955;
double atom59965;
double atom59969;
double atom64620;
double atom64363;
double atom64368;
double atom64623;
double atom64626;
double atom64886;
double atom42090;
double atom42078;
double atom59985;
double atom59989;
double atom59995;
double atom59999;
double atom64627;
double atom64379;
double atom64374;
double atom64630;
double atom64633;
double atom64936;
double atom64634;
double atom64635;
double atom64636;
double atom64986;
double atom60016;
double atom60020;
double atom60021;
double atom64637;
double atom60024;
double atom64385;
double atom64639;
double atom64640;
double atom64642;
double atom64643;
double atom65036;
double atom60036;
double atom60046;
double atom60050;
double atom60040;
double atom64644;
double atom64391;
double atom64394;
double atom64647;
double atom64650;
double atom65086;
double atom64651;
double atom64652;
double atom64653;
double atom65136;
double atom64654;
double atom64400;
double atom64656;
double atom64658;
double atom65186;
double atom60075;
double atom64659;
double atom64406;
double atom64662;
double atom64665;
double atom65236;

double * _CKFFR = NULL;
void Init_CKFFR ( ) 
{
    _CKFFR = malloc ( CKFFR_n_rows * CKFFR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKFFR_n_rows * CKFFR_n_cols ; i++ ) {_CKFFR[i]=0.0;}
  }
}

void Done_CKFFR ( ) 
{
if (_CKFFR != NULL) 
free (_CKFFR ); 
_CKFFR = NULL; 
}


double * CKFFR ()
{
if ( _CKFFR == NULL )
 {
    _CKFFR = malloc ( CKFFR_n_rows * CKFFR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKFFR_n_rows * CKFFR_n_cols ; i++ ) {_CKFFR[i]=0.0;}
  }
 }

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
atom2894 =  atom2859+-5.0000000000000000e-01*atom2888*L_RAIL;
atom2930 = (atom2892*atom2892);
atom2938 = pow( (atom2894*atom2894)+atom2930,-(1.0/2.0));
atom2939 = atom2892*atom2938;
atom64596 = -aFFR*atom2939*G_elastic*bFFR*C11FFR*epsiFFR;
atom2940 = atom2894*atom2938;
atom1172 = cos(bWAG);
atom1174 = cos(aWAG);
atom1019 = sin(bFBOG);
atom1195 = atom1172*atom1174;
atom1173 = sin(bWAG);
atom1194 = -atom1173*atom1174;
atom1496 = cos(cFSLD);
atom1497 = sin(cFSLD);
atom1175 = sin(aWAG);
atom1018 = cos(bFBOG);
atom1512 =  atom1194*atom1496+atom1497*atom1175;
atom2720 =  uW_FFR-lW_FFR;
atom2726 =  dW_FFR+( cW_FFR+( bW_FFR+aW_FFR*atom2720)*atom2720)*atom2720;
atom1530 = -atom1019*atom1195+atom1018*atom1512;
atom2727 = -sin(thetaW_FFR)*atom2726;
atom1016 = cos(aFBOG);
atom1533 =  atom1018*atom1195+atom1019*atom1512;
atom1514 = atom1175*atom1496;
atom1515 =  atom1514-atom1497*atom1194;
atom1017 = sin(aFBOG);
atom498 = sin(aFWHSF);
atom1551 = -atom1515*atom1017+atom1016*atom1533;
atom497 = cos(aFWHSF);
atom1548 =  atom1533*atom1017+atom1515*atom1016;
atom1571 =  atom497*atom1548+atom498*atom1551;
atom2729 = atom2726*cos(thetaW_FFR);
atom1574 = -atom498*atom1548+atom497*atom1551;
atom1702 = -5.0000000000000000e-01*L_WHS;
atom2730 = atom497*atom1702;
atom1022 = atom1018*atom1017;
atom2741 = -L_OBOG_OWHS*atom1019;
atom1023 = atom1018*atom1016;
atom2732 =  atom498*atom1702+zFWHSF;
atom2746 =  atom2741+zFBOG+atom2730*atom1022+atom1023*atom2732;
atom2733 = atom1018*L_OBOG_OWHS;
atom1021 = atom1019*atom1016;
atom2737 =  atom1021*atom2732+atom2733+atom1019*atom2730*atom1017;
atom2740 = -atom2732*atom1017+atom1016*atom2730;
atom2752 =  atom1497*atom2737+atom2740*atom1496;
atom0 = -(1.0/2.0)*L_WAG;
atom2753 = -atom1497*atom2740-atom0+atom2737*atom1496;
atom22217 =  atom2741+atom1023*zFWHSF;
atom22218 =  zFBOG+atom22217;
atom22214 =  atom1021*zFWHSF+atom2733;
atom22215 = -zFWHSF*atom1017;
atom22221 = -atom1497*atom22215+atom22214*atom1496;
atom22225 = -atom0+atom22221;
atom22224 =  atom1496*atom22215+atom1497*atom22214;
atom22240 =  atom1194*atom22225+atom22218*atom1195+atom1175*atom22224;
atom1176 = cos(cWAG);
atom22246 =  atom2753*atom1194+atom2746*atom1195+atom1571*uW_FFR+atom2729*atom1574-atom22240+atom1175*atom2752+atom1530*atom2727;
atom58338 = -atom1176*atom22240;
atom64408 =  atom58338-atom1176*atom22246;
atom1177 = sin(cWAG);
atom58337 = atom22240*atom1177;
atom64413 =  atom64408*atom2940+( atom58337+atom1177*atom22246)*atom2939;
atom1178 = -atom1177*atom1174;
atom1179 = atom1175*atom1177;
atom1184 =  atom1172*atom1176-atom1173*atom1179;
atom1185 = atom1176*atom1173;
atom1187 =  atom1172*atom1179+atom1185;
atom22230 =  atom22225*atom1184+atom22218*atom1187+atom22224*atom1178;
atom1500 =  atom1496*atom1184+atom1497*atom1178;
atom1521 =  atom1019*atom1500+atom1018*atom1187;
atom1503 =  atom1496*atom1178-atom1497*atom1184;
atom1539 = -atom1503*atom1017+atom1016*atom1521;
atom1536 =  atom1521*atom1017+atom1503*atom1016;
atom1562 =  atom497*atom1539-atom498*atom1536;
atom1559 =  atom497*atom1536+atom498*atom1539;
atom1518 =  atom1018*atom1500-atom1019*atom1187;
atom22244 =  atom2752*atom1178+atom2746*atom1187+atom1559*uW_FFR+atom2753*atom1184-atom22230+atom2727*atom1518+atom2729*atom1562;
atom58348 = -atom22240*atom1178+atom1175*atom22230;
atom64417 =  atom1175*atom22244+atom58348-atom22246*atom1178;
atom1181 = -atom1175*atom1176;
atom1191 = atom1177*atom1173;
atom1193 =  atom1191+atom1172*atom1181;
atom1180 = atom1176*atom1174;
atom1190 = -atom1181*atom1173+atom1172*atom1177;
atom22235 =  atom1193*atom22218+atom1180*atom22224+atom1190*atom22225;
atom1506 =  atom1190*atom1496+atom1497*atom1180;
atom1527 =  atom1019*atom1506+atom1193*atom1018;
atom1509 =  atom1180*atom1496-atom1497*atom1190;
atom1545 =  atom1527*atom1016-atom1017*atom1509;
atom1542 =  atom1016*atom1509+atom1527*atom1017;
atom1568 =  atom497*atom1545-atom498*atom1542;
atom1565 =  atom497*atom1542+atom498*atom1545;
atom1524 = -atom1193*atom1019+atom1018*atom1506;
atom22245 =  atom2753*atom1190+atom1180*atom2752+uW_FFR*atom1565+atom1524*atom2727+atom2729*atom1568-atom22235+atom2746*atom1193;
atom58345 = -atom1175*atom22235+atom1180*atom22240;
atom64424 =  atom2939*( atom1180*atom22246-atom1175*atom22245+atom58345)+atom64417*atom2940;
atom64425 =  atom22244+atom22230;
atom64429 = -atom2939*( atom22235+atom22245)+atom64425*atom2940;
atom3814 = -atom1175*atom1172;
atom60833 = -atom3814*atom1177+atom1185;
atom42760 =  atom1180*atom22221-atom22224*atom1190;
atom64433 = -atom60833*atom22246+atom1195*atom22244+atom42760;
atom60839 =  atom1191+atom1176*atom3814;
atom42906 = -atom22224*atom1184+atom22221*atom1178;
atom64440 =  atom64433*atom2940-( atom1195*atom22245-atom60839*atom22246-atom42906)*atom2939;
atom8887 =  atom1193*atom2940+atom2939*atom1187;
atom58356 = -atom1019*atom22214-atom1018*atom22217;
atom58358 = -atom1019*atom22215;
atom58360 = -atom58358*atom1496-atom1497*atom58356;
atom58364 = -atom1497*atom58358+atom58356*atom1496;
atom58367 = atom1018*atom22215;
atom41956 = atom1018*atom1496;
atom40896 = -atom1019*atom1173;
atom64448 =  atom40896+atom41956*atom1172;
atom40899 = atom1497*atom1018;
atom64442 = -atom1172*atom1019-atom41956*atom1173;
atom64445 =  atom40899*atom1174-atom1175*atom64442;
atom64461 =  atom1176*atom64445+atom64448*atom1177;
atom64453 =  atom64442*atom1174+atom1175*atom40899;
atom58369 =  atom58360*atom1184+atom58364*atom1178+atom1187*atom58367;
atom64463 = -atom64453*atom22245+atom22246*atom64461;
atom64450 =  atom1176*atom64448-atom64445*atom1177;
atom64455 =  atom64453*atom22244-atom64450*atom22246;
atom58374 =  atom1193*atom58367+atom58364*atom1180+atom1190*atom58360;
atom64456 =  atom64455+atom58374;
atom64466 =  atom64456*atom2940+atom2939*( atom58369+atom64463);
atom42824 = atom22217*atom1496;
atom42819 = atom1497*atom22217;
atom40806 = atom1497*atom1173;
atom40875 =  atom40806*atom1174+atom1514;
atom40804 = -atom1497*atom1172;
atom64468 =  atom1496*atom1174-atom1175*atom40806;
atom64471 = -atom1177*atom64468+atom1176*atom40804;
atom42841 = -atom1193*atom22214+atom1180*atom42819+atom42824*atom1190;
atom64475 =  atom42841+atom40875*atom22244-atom64471*atom22246;
atom64480 =  atom1176*atom64468+atom1177*atom40804;
atom42934 =  atom42824*atom1184-atom22214*atom1187+atom1178*atom42819;
atom64485 =  atom2939*( atom42934+atom64480*atom22246-atom40875*atom22245)+atom2940*atom64475;
atom6041 =  atom1497*atom1017+atom1021*atom1496;
atom6036 = -atom1496*atom1017;
atom6037 =  atom1497*atom1021+atom6036;
atom6044 =  atom1193*atom1023+atom1190*atom6041+atom1180*atom6037;
atom8896 =  atom6044*atom2940+atom2939*( atom1023*atom1187+atom6041*atom1184+atom6037*atom1178);
atom64488 =  atom2939*atom64463+atom64455*atom2940;
atom42093 = -atom497*atom1017-atom498*atom1016;
atom64491 = -atom1019*atom42093;
atom42081 = -atom498*atom1017+atom497*atom1016;
atom64500 =  atom1497*atom64491+atom42081*atom1496;
atom64494 =  atom64491*atom1496-atom1497*atom42081;
atom64489 = -atom1018*atom42093;
atom64496 =  atom1172*atom64489-atom1173*atom64494;
atom64512 =  atom1175*atom64500+atom64496*atom1174;
atom64502 = -atom1175*atom64496+atom64500*atom1174;
atom64506 =  atom1172*atom64494+atom1173*atom64489;
atom64508 =  atom64506*atom1176-atom64502*atom1177;
atom64514 = -atom64508*atom22246+atom22244*atom64512;
atom64519 =  atom1176*atom64502+atom64506*atom1177;
atom64523 = -atom2939*( atom64512*atom22245-atom64519*atom22246)+atom64514*atom2940;
atom64597 = -aFFR*G_elastic*bFFR*C11FFR*epsiFFR*atom2940;
atom2826 =  uR_FFR-lR_FFR;
atom2827 = atom2826*aR_FFR;
atom2828 =  bR_FFR+atom2827;
atom2897 =  atom2828*atom2826+cR_FFR+atom2826*( atom2828+atom2827);
atom2943 = pow( (atom2897*atom2897)+1.0,-(1.0/2.0));
atom64598 = -C22FFR*aFFR*atom2943*G_elastic*bFFR*epsiFFR;
atom2944 = atom2943*atom2897;
atom64600 = pow(aFFR*bFFR,(1.0/2.0));
atom2899 = -atom2892*atom2897;
atom2898 = atom2894*atom2897;
atom2932 = pow( (atom2899*atom2899)+atom2930+(atom2898*atom2898),-(1.0/2.0));
atom2934 = atom2899*atom2932;
atom2933 = atom2932*atom2898;
atom64601 = -aFFR*atom2943*C23FFR*G_elastic*bFFR*atom64600*epsiFFR;
atom64571 =  atom2934*atom1177+atom1176*atom2933;
atom58341 =  atom1176*atom22235-atom1177*atom22230;
atom64530 =  ( atom1176*atom22245+atom58341-atom22244*atom1177)*atom2944+atom2943*atom64408;
atom58351 = -atom1180*atom22230+atom22235*atom1178;
atom64537 =  ( atom58351+atom22245*atom1178-atom1180*atom22244)*atom2944+atom2943*atom64417;
atom2935 = atom2932*atom2892;
atom64576 =  atom1180*atom2934+atom2933*atom1178+atom2935*atom1175;
atom64538 = atom2943*atom64425;
atom64580 =  atom2933*atom60833+atom2935*atom1195+atom2934*atom60839;
atom42756 =  atom1175*atom22221-atom22224*atom1194;
atom64545 = -( atom60839*atom22244-atom22245*atom60833-atom42756)*atom2944+atom2943*atom64433;
atom8936 =  atom1193*atom2943+atom1195*atom2944;
atom64585 =  atom2935*atom64453+atom64450*atom2933+atom2934*atom64461;
atom58379 =  atom1194*atom58360+atom1195*atom58367+atom58364*atom1175;
atom64548 = -atom22244*atom64461+atom64450*atom22245;
atom64552 =  ( atom58379+atom64548)*atom2944+atom64456*atom2943;
atom64709 = atom64601*atom64585;
atom64590 =  atom2934*atom64480+atom64471*atom2933+atom40875*atom2935;
atom42835 =  atom1175*atom42819+atom42824*atom1194-atom22214*atom1195;
atom64559 =  atom2943*atom64475+( atom42835+atom64471*atom22245-atom22244*atom64480)*atom2944;
atom8945 =  atom2943*atom6044+( atom1175*atom6037+atom1194*atom6041+atom1023*atom1195)*atom2944;
atom64562 =  atom2944*atom64548+atom2943*atom64455;
atom64595 =  atom64508*atom2933+atom2934*atom64519+atom2935*atom64512;
atom64568 =  atom2943*atom64514+( atom64508*atom22245-atom22244*atom64519)*atom2944;
atom64602 = -C22FFR*aFFR*G_elastic*bFFR*epsiFFR*atom2944;
atom64603 = -aFFR*C23FFR*G_elastic*bFFR*atom64600*epsiFFR*atom2944;
atom64744 = atom64585*atom64603;
atom40803 = atom1172*atom1496;
atom40902 =  atom1019*atom40803+atom1018*atom1173;
atom41903 = -atom1017*atom40804+atom40902*atom1016;
atom41900 =  atom40902*atom1017+atom1016*atom40804;
atom42072 =  atom41900*atom497+atom41903*atom498;
atom40898 =  atom1018*atom40803+atom40896;
atom42084 = -atom41900*atom498+atom497*atom41903;
atom59883 =  atom42072*atom1571+atom42084*atom1574+atom1530*atom40898;
atom59897 =  atom40898*atom1518+atom1562*atom42084+atom1559*atom42072;
atom59901 =  atom59883*atom22244-atom59897*atom22246+atom58338;
atom59889 =  atom40898*atom1524+atom42072*atom1565+atom42084*atom1568;
atom64604 = -aFFR*G_elastic*bFFR*C11FFR*( atom59901*atom2940-( atom59883*atom22245-atom58337-atom59889*atom22246)*atom2939)*epsiFFR;
atom64331 =  atom2944*( atom59897*atom22245+atom58341-atom22244*atom59889)+atom59901*atom2943;
atom64343 =  atom2933*atom1518+atom1530*atom2935+atom2934*atom1524;
atom22168 =  atom1559*atom2933+atom2935*atom1571+atom2934*atom1565;
atom64336 =  atom2935*atom1574+atom1562*atom2933+atom2934*atom1568;
atom64346 =  atom22168*atom42072+atom64336*atom42084+atom40898*atom64343;
atom64607 = -C22FFR*aFFR*G_elastic*bFFR*atom64331*epsiFFR+aFFR*atom64346*C23FFR*G_elastic*bFFR*atom64600*epsiFFR;
atom64609 = (aFFR*aFFR);
atom64610 = (bFFR*bFFR);
atom64612 = -atom64346*G_elastic*atom64609*C33FFR*epsiFFR*atom64610-aFFR*C23FFR*G_elastic*bFFR*atom64600*atom64331*epsiFFR;
atom64786 = atom64612*atom64585;
atom40903 = atom1497*atom1019;
atom41907 =  atom1016*atom40903+atom6036;
atom41905 =  atom40903*atom1017+atom1016*atom1496;
atom42087 =  atom497*atom41907-atom41905*atom498;
atom42075 =  atom497*atom41905+atom498*atom41907;
atom59926 =  atom1524*atom40899+atom42087*atom1568+atom42075*atom1565;
atom59920 =  atom42087*atom1574+atom42075*atom1571+atom1530*atom40899;
atom59934 =  atom40899*atom1518+atom1562*atom42087+atom42075*atom1559;
atom59938 =  atom58348+atom59920*atom22244-atom59934*atom22246;
atom64613 = ( ( atom59920*atom22245-atom59926*atom22246-atom58345)*atom2939-atom59938*atom2940)*aFFR*G_elastic*bFFR*C11FFR*epsiFFR;
atom64352 =  atom2944*( atom58351+atom59934*atom22245-atom22244*atom59926)+atom2943*atom59938;
atom64357 =  atom64336*atom42087+atom22168*atom42075+atom64343*atom40899;
atom64616 = -C22FFR*aFFR*atom64352*G_elastic*bFFR*epsiFFR+aFFR*atom64357*C23FFR*G_elastic*bFFR*atom64600*epsiFFR;
atom64619 = -aFFR*C23FFR*atom64352*G_elastic*bFFR*atom64600*epsiFFR-atom64357*G_elastic*atom64609*C33FFR*epsiFFR*atom64610;
atom64836 = atom64619*atom64585;
atom59959 =  atom1571*atom1565+atom1530*atom1524+atom1574*atom1568;
atom59955 =  (atom1530*atom1530)+(atom1574*atom1574)+(atom1571*atom1571);
atom59965 =  atom1562*atom1574+atom1559*atom1571+atom1530*atom1518;
atom59969 = -atom59965*atom22246+atom22244*atom59955+atom22230;
atom64620 = -aFFR*G_elastic*bFFR*C11FFR*( atom59969*atom2940+atom2939*( atom59959*atom22246-atom59955*atom22245-atom22235))*epsiFFR;
atom64363 = -atom2944*( atom59959*atom22244-atom59965*atom22245)+atom2943*atom59969;
atom64368 =  atom22168*atom1571+atom64336*atom1574+atom1530*atom64343;
atom64623 = -C22FFR*aFFR*atom64363*G_elastic*bFFR*epsiFFR+atom64368*aFFR*C23FFR*G_elastic*bFFR*atom64600*epsiFFR;
atom64626 = -atom64368*G_elastic*atom64609*C33FFR*epsiFFR*atom64610-aFFR*C23FFR*atom64363*G_elastic*bFFR*atom64600*epsiFFR;
atom64886 = atom64626*atom64585;
atom42090 =  atom497*atom1023-atom498*atom1022;
atom42078 =  atom497*atom1022+atom1023*atom498;
atom59985 =  atom42078*atom1571+atom42090*atom1574-atom1530*atom1019;
atom59989 =  atom42078*atom1565+atom42090*atom1568-atom1019*atom1524;
atom59995 =  atom1559*atom42078-atom1019*atom1518+atom1562*atom42090;
atom59999 =  atom22244*atom59985+atom42760-atom59995*atom22246;
atom64627 = -aFFR*( atom2939*( atom59989*atom22246-atom59985*atom22245+atom42906)+atom59999*atom2940)*G_elastic*bFFR*C11FFR*epsiFFR;
atom64379 = -atom1019*atom64343+atom42090*atom64336+atom22168*atom42078;
atom64374 =  atom2943*atom59999+( atom59995*atom22245-atom59989*atom22244+atom42756)*atom2944;
atom64630 = -C22FFR*aFFR*G_elastic*bFFR*atom64374*epsiFFR+aFFR*C23FFR*G_elastic*atom64379*bFFR*atom64600*epsiFFR;
atom64633 = -G_elastic*atom64379*atom64609*C33FFR*epsiFFR*atom64610-aFFR*C23FFR*G_elastic*bFFR*atom64600*atom64374*epsiFFR;
atom64936 = atom64633*atom64585;
atom64634 = -aFFR*G_elastic*bFFR*atom8887*C11FFR*epsiFFR;
atom64635 = -C22FFR*aFFR*atom8936*G_elastic*bFFR*epsiFFR;
atom64636 = -aFFR*atom8936*C23FFR*G_elastic*bFFR*atom64600*epsiFFR;
atom64986 = atom64585*atom64636;
atom60016 =  atom1524*atom22246-atom1530*atom22245;
atom60020 =  atom1530*atom22244-atom22246*atom1518;
atom60021 =  atom58374+atom60020;
atom64637 = -aFFR*G_elastic*( ( atom58369+atom60016)*atom2939+atom60021*atom2940)*bFFR*C11FFR*epsiFFR;
atom60024 = -atom22244*atom1524+atom22245*atom1518;
atom64385 =  atom2943*atom60021+( atom60024+atom58379)*atom2944;
atom64639 = aFFR*C23FFR*G_elastic*bFFR*atom64343*atom64600*epsiFFR;
atom64640 = -C22FFR*aFFR*G_elastic*bFFR*epsiFFR*atom64385+atom64639;
atom64642 = -G_elastic*atom64609*atom64343*C33FFR*epsiFFR*atom64610;
atom64643 = -aFFR*C23FFR*G_elastic*bFFR*atom64600*epsiFFR*atom64385+atom64642;
atom65036 = atom64643*atom64585;
atom60036 =  atom42081*atom1571+atom42093*atom1574;
atom60046 =  atom1559*atom42081+atom1562*atom42093;
atom60050 = -atom60046*atom22246+atom42841+atom60036*atom22244;
atom60040 =  atom42093*atom1568+atom42081*atom1565;
atom64644 = -aFFR*G_elastic*bFFR*C11FFR*epsiFFR*( atom60050*atom2940+atom2939*( atom42934+atom60040*atom22246-atom60036*atom22245));
atom64391 =  ( atom42835+atom60046*atom22245-atom60040*atom22244)*atom2944+atom2943*atom60050;
atom64394 =  atom64336*atom42093+atom22168*atom42081;
atom64647 =  aFFR*C23FFR*atom64394*G_elastic*bFFR*atom64600*epsiFFR-C22FFR*aFFR*G_elastic*bFFR*atom64391*epsiFFR;
atom64650 = -atom64394*G_elastic*atom64609*C33FFR*epsiFFR*atom64610-aFFR*C23FFR*G_elastic*bFFR*atom64600*atom64391*epsiFFR;
atom65086 = atom64650*atom64585;
atom64651 = -aFFR*G_elastic*bFFR*C11FFR*epsiFFR*atom8896;
atom64652 = -C22FFR*aFFR*atom8945*G_elastic*bFFR*epsiFFR;
atom64653 = -aFFR*atom8945*C23FFR*G_elastic*bFFR*atom64600*epsiFFR;
atom65136 = atom64653*atom64585;
atom64654 = -aFFR*G_elastic*bFFR*( atom60020*atom2940+atom2939*atom60016)*C11FFR*epsiFFR;
atom64400 =  atom60024*atom2944+atom2943*atom60020;
atom64656 = -C22FFR*aFFR*G_elastic*bFFR*epsiFFR*atom64400+atom64639;
atom64658 = -aFFR*C23FFR*G_elastic*bFFR*atom64600*epsiFFR*atom64400+atom64642;
atom65186 = atom64658*atom64585;
atom60075 =  atom22244*atom1571-atom1559*atom22246;
atom64659 = -aFFR*G_elastic*bFFR*C11FFR*epsiFFR*( atom60075*atom2940-atom2939*( atom22245*atom1571-atom22246*atom1565));
atom64406 =  atom60075*atom2943-( atom22244*atom1565-atom1559*atom22245)*atom2944;
atom64662 =  aFFR*atom22168*C23FFR*G_elastic*bFFR*atom64600*epsiFFR-C22FFR*aFFR*G_elastic*bFFR*epsiFFR*atom64406;
atom64665 = -atom22168*G_elastic*atom64609*C33FFR*epsiFFR*atom64610-aFFR*C23FFR*G_elastic*bFFR*atom64600*epsiFFR*atom64406;
atom65236 = atom64665*atom64585;

_CKFFR[0] = atom2939*atom64596;
_CKFFR[1] = atom2939*atom64597;
_CKFFR[2] = 0.0;
_CKFFR[3] = atom2939*atom64604;
_CKFFR[4] = atom2939*atom64613;
_CKFFR[5] = atom64620*atom2939;
_CKFFR[6] = 0.0;
_CKFFR[7] = atom2939*atom64627;
_CKFFR[8] = 0.0;
_CKFFR[9] = 0.0;
_CKFFR[10] = 0.0;
_CKFFR[11] = atom2939*atom64634;
_CKFFR[12] = atom64637*atom2939;
_CKFFR[13] = atom64644*atom2939;
_CKFFR[14] = 0.0;
_CKFFR[15] = 0.0;
_CKFFR[16] = 0.0;
_CKFFR[17] = 0.0;
_CKFFR[18] = 0.0;
_CKFFR[19] = 0.0;
_CKFFR[20] = atom2939*atom64651;
_CKFFR[21] = atom2939*atom64654;
_CKFFR[22] = atom64659*atom2939;
_CKFFR[23] = 0.0;
_CKFFR[24] = 0.0;
_CKFFR[25] = 0.0;
_CKFFR[26] = 0.0;
_CKFFR[27] = 0.0;
_CKFFR[28] = 0.0;
_CKFFR[29] = 0.0;
_CKFFR[30] = 0.0;
_CKFFR[31] = 0.0;
_CKFFR[32] = 0.0;
_CKFFR[33] = 0.0;
_CKFFR[34] = 0.0;
_CKFFR[35] = 0.0;
_CKFFR[36] = 0.0;
_CKFFR[37] = 0.0;
_CKFFR[38] = 0.0;
_CKFFR[39] = 0.0;
_CKFFR[40] = 0.0;
_CKFFR[41] = 0.0;
_CKFFR[42] = 0.0;
_CKFFR[43] = 0.0;
_CKFFR[44] = atom2940*atom64596;
_CKFFR[45] =  atom64597*atom2940+atom2943*atom64598;
_CKFFR[46] = atom2943*atom64602;
_CKFFR[47] =  atom2943*atom64607+atom2940*atom64604;
_CKFFR[48] =  atom2943*atom64616+atom2940*atom64613;
_CKFFR[49] =  atom2943*atom64623+atom64620*atom2940;
_CKFFR[50] = 0.0;
_CKFFR[51] =  atom2943*atom64630+atom64627*atom2940;
_CKFFR[52] = 0.0;
_CKFFR[53] = 0.0;
_CKFFR[54] = 0.0;
_CKFFR[55] =  atom2943*atom64635+atom64634*atom2940;
_CKFFR[56] =  atom2943*atom64640+atom64637*atom2940;
_CKFFR[57] =  atom64644*atom2940+atom2943*atom64647;
_CKFFR[58] = 0.0;
_CKFFR[59] = 0.0;
_CKFFR[60] = 0.0;
_CKFFR[61] = 0.0;
_CKFFR[62] = 0.0;
_CKFFR[63] = 0.0;
_CKFFR[64] =  atom64651*atom2940+atom64652*atom2943;
_CKFFR[65] =  atom64654*atom2940+atom2943*atom64656;
_CKFFR[66] =  atom64659*atom2940+atom2943*atom64662;
_CKFFR[67] = 0.0;
_CKFFR[68] = 0.0;
_CKFFR[69] = 0.0;
_CKFFR[70] = 0.0;
_CKFFR[71] = 0.0;
_CKFFR[72] = 0.0;
_CKFFR[73] = 0.0;
_CKFFR[74] = 0.0;
_CKFFR[75] = 0.0;
_CKFFR[76] = 0.0;
_CKFFR[77] = 0.0;
_CKFFR[78] = 0.0;
_CKFFR[79] = 0.0;
_CKFFR[80] = 0.0;
_CKFFR[81] = 0.0;
_CKFFR[82] = 0.0;
_CKFFR[83] = 0.0;
_CKFFR[84] = 0.0;
_CKFFR[85] = 0.0;
_CKFFR[86] = 0.0;
_CKFFR[87] = 0.0;
_CKFFR[88] = 0.0;
_CKFFR[89] = atom2944*atom64598;
_CKFFR[90] = atom64602*atom2944;
_CKFFR[91] = atom64607*atom2944;
_CKFFR[92] = atom64616*atom2944;
_CKFFR[93] = atom64623*atom2944;
_CKFFR[94] = 0.0;
_CKFFR[95] = atom64630*atom2944;
_CKFFR[96] = 0.0;
_CKFFR[97] = 0.0;
_CKFFR[98] = 0.0;
_CKFFR[99] = atom64635*atom2944;
_CKFFR[100] = atom64640*atom2944;
_CKFFR[101] = atom64647*atom2944;
_CKFFR[102] = 0.0;
_CKFFR[103] = 0.0;
_CKFFR[104] = 0.0;
_CKFFR[105] = 0.0;
_CKFFR[106] = 0.0;
_CKFFR[107] = 0.0;
_CKFFR[108] = atom64652*atom2944;
_CKFFR[109] = atom64656*atom2944;
_CKFFR[110] = atom64662*atom2944;
_CKFFR[111] = 0.0;
_CKFFR[112] = 0.0;
_CKFFR[113] = 0.0;
_CKFFR[114] = 0.0;
_CKFFR[115] = 0.0;
_CKFFR[116] = 0.0;
_CKFFR[117] = 0.0;
_CKFFR[118] = 0.0;
_CKFFR[119] = 0.0;
_CKFFR[120] = 0.0;
_CKFFR[121] = 0.0;
_CKFFR[122] = 0.0;
_CKFFR[123] = 0.0;
_CKFFR[124] = 0.0;
_CKFFR[125] = 0.0;
_CKFFR[126] = 0.0;
_CKFFR[127] = 0.0;
_CKFFR[128] = 0.0;
_CKFFR[129] = 0.0;
_CKFFR[130] = 0.0;
_CKFFR[131] = 0.0;
_CKFFR[132] = atom64413*atom64596;
_CKFFR[133] =  atom64530*atom64598+atom64601*atom64571+atom64413*atom64597;
_CKFFR[134] =  atom64571*atom64603+atom64602*atom64530;
_CKFFR[135] =  atom64612*atom64571+atom64413*atom64604+atom64607*atom64530;
_CKFFR[136] =  atom64619*atom64571+atom64413*atom64613+atom64616*atom64530;
_CKFFR[137] =  atom64626*atom64571+atom64623*atom64530+atom64620*atom64413;
_CKFFR[138] = 0.0;
_CKFFR[139] =  atom64633*atom64571+atom64630*atom64530+atom64413*atom64627;
_CKFFR[140] = 0.0;
_CKFFR[141] = 0.0;
_CKFFR[142] = 0.0;
_CKFFR[143] =  atom64413*atom64634+atom64635*atom64530+atom64571*atom64636;
_CKFFR[144] =  atom64640*atom64530+atom64571*atom64643+atom64413*atom64637;
_CKFFR[145] =  atom64650*atom64571+atom64644*atom64413+atom64647*atom64530;
_CKFFR[146] = 0.0;
_CKFFR[147] = 0.0;
_CKFFR[148] = 0.0;
_CKFFR[149] = 0.0;
_CKFFR[150] = 0.0;
_CKFFR[151] = 0.0;
_CKFFR[152] =  atom64652*atom64530+atom64653*atom64571+atom64413*atom64651;
_CKFFR[153] =  atom64413*atom64654+atom64656*atom64530+atom64658*atom64571;
_CKFFR[154] =  atom64659*atom64413+atom64662*atom64530+atom64665*atom64571;
_CKFFR[155] = 0.0;
_CKFFR[156] = 0.0;
_CKFFR[157] = 0.0;
_CKFFR[158] = 0.0;
_CKFFR[159] = 0.0;
_CKFFR[160] = 0.0;
_CKFFR[161] = 0.0;
_CKFFR[162] = 0.0;
_CKFFR[163] = 0.0;
_CKFFR[164] = 0.0;
_CKFFR[165] = 0.0;
_CKFFR[166] = 0.0;
_CKFFR[167] = 0.0;
_CKFFR[168] = 0.0;
_CKFFR[169] = 0.0;
_CKFFR[170] = 0.0;
_CKFFR[171] = 0.0;
_CKFFR[172] = 0.0;
_CKFFR[173] = 0.0;
_CKFFR[174] = 0.0;
_CKFFR[175] = 0.0;
_CKFFR[176] = atom64424*atom64596;
_CKFFR[177] =  atom64537*atom64598+atom64576*atom64601+atom64424*atom64597;
_CKFFR[178] =  atom64576*atom64603+atom64537*atom64602;
_CKFFR[179] =  atom64537*atom64607+atom64576*atom64612+atom64424*atom64604;
_CKFFR[180] =  atom64537*atom64616+atom64576*atom64619+atom64424*atom64613;
_CKFFR[181] =  atom64537*atom64623+atom64576*atom64626+atom64620*atom64424;
_CKFFR[182] = 0.0;
_CKFFR[183] =  atom64537*atom64630+atom64576*atom64633+atom64424*atom64627;
_CKFFR[184] = 0.0;
_CKFFR[185] = 0.0;
_CKFFR[186] = 0.0;
_CKFFR[187] =  atom64537*atom64635+atom64424*atom64634+atom64576*atom64636;
_CKFFR[188] =  atom64537*atom64640+atom64576*atom64643+atom64424*atom64637;
_CKFFR[189] =  atom64644*atom64424+atom64537*atom64647+atom64576*atom64650;
_CKFFR[190] = 0.0;
_CKFFR[191] = 0.0;
_CKFFR[192] = 0.0;
_CKFFR[193] = 0.0;
_CKFFR[194] = 0.0;
_CKFFR[195] = 0.0;
_CKFFR[196] =  atom64652*atom64537+atom64424*atom64651+atom64576*atom64653;
_CKFFR[197] =  atom64424*atom64654+atom64576*atom64658+atom64537*atom64656;
_CKFFR[198] =  atom64576*atom64665+atom64424*atom64659+atom64537*atom64662;
_CKFFR[199] = 0.0;
_CKFFR[200] = 0.0;
_CKFFR[201] = 0.0;
_CKFFR[202] = 0.0;
_CKFFR[203] = 0.0;
_CKFFR[204] = 0.0;
_CKFFR[205] = 0.0;
_CKFFR[206] = 0.0;
_CKFFR[207] = 0.0;
_CKFFR[208] = 0.0;
_CKFFR[209] = 0.0;
_CKFFR[210] = 0.0;
_CKFFR[211] = 0.0;
_CKFFR[212] = 0.0;
_CKFFR[213] = 0.0;
_CKFFR[214] = 0.0;
_CKFFR[215] = 0.0;
_CKFFR[216] = 0.0;
_CKFFR[217] = 0.0;
_CKFFR[218] = 0.0;
_CKFFR[219] = 0.0;
_CKFFR[220] = atom64429*atom64596;
_CKFFR[221] =  atom64597*atom64429+atom2935*atom64601+atom64538*atom64598;
_CKFFR[222] =  atom2935*atom64603+atom64602*atom64538;
_CKFFR[223] =  atom64607*atom64538+atom64429*atom64604+atom2935*atom64612;
_CKFFR[224] =  atom64429*atom64613+atom2935*atom64619+atom64616*atom64538;
_CKFFR[225] =  atom2935*atom64626+atom64620*atom64429+atom64623*atom64538;
_CKFFR[226] = 0.0;
_CKFFR[227] =  atom64627*atom64429+atom64630*atom64538+atom2935*atom64633;
_CKFFR[228] = 0.0;
_CKFFR[229] = 0.0;
_CKFFR[230] = 0.0;
_CKFFR[231] =  atom64635*atom64538+atom64634*atom64429+atom2935*atom64636;
_CKFFR[232] =  atom2935*atom64643+atom64640*atom64538+atom64637*atom64429;
_CKFFR[233] =  atom2935*atom64650+atom64647*atom64538+atom64644*atom64429;
_CKFFR[234] = 0.0;
_CKFFR[235] = 0.0;
_CKFFR[236] = 0.0;
_CKFFR[237] = 0.0;
_CKFFR[238] = 0.0;
_CKFFR[239] = 0.0;
_CKFFR[240] =  atom64652*atom64538+atom64651*atom64429+atom64653*atom2935;
_CKFFR[241] =  atom64654*atom64429+atom64656*atom64538+atom2935*atom64658;
_CKFFR[242] =  atom64662*atom64538+atom2935*atom64665+atom64659*atom64429;
_CKFFR[243] = 0.0;
_CKFFR[244] = 0.0;
_CKFFR[245] = 0.0;
_CKFFR[246] = 0.0;
_CKFFR[247] = 0.0;
_CKFFR[248] = 0.0;
_CKFFR[249] = 0.0;
_CKFFR[250] = 0.0;
_CKFFR[251] = 0.0;
_CKFFR[252] = 0.0;
_CKFFR[253] = 0.0;
_CKFFR[254] = 0.0;
_CKFFR[255] = 0.0;
_CKFFR[256] = 0.0;
_CKFFR[257] = 0.0;
_CKFFR[258] = 0.0;
_CKFFR[259] = 0.0;
_CKFFR[260] = 0.0;
_CKFFR[261] = 0.0;
_CKFFR[262] = 0.0;
_CKFFR[263] = 0.0;
_CKFFR[264] = 0.0;
_CKFFR[265] = 0.0;
_CKFFR[266] = 0.0;
_CKFFR[267] = 0.0;
_CKFFR[268] = 0.0;
_CKFFR[269] = 0.0;
_CKFFR[270] = 0.0;
_CKFFR[271] = 0.0;
_CKFFR[272] = 0.0;
_CKFFR[273] = 0.0;
_CKFFR[274] = 0.0;
_CKFFR[275] = 0.0;
_CKFFR[276] = 0.0;
_CKFFR[277] = 0.0;
_CKFFR[278] = 0.0;
_CKFFR[279] = 0.0;
_CKFFR[280] = 0.0;
_CKFFR[281] = 0.0;
_CKFFR[282] = 0.0;
_CKFFR[283] = 0.0;
_CKFFR[284] = 0.0;
_CKFFR[285] = 0.0;
_CKFFR[286] = 0.0;
_CKFFR[287] = 0.0;
_CKFFR[288] = 0.0;
_CKFFR[289] = 0.0;
_CKFFR[290] = 0.0;
_CKFFR[291] = 0.0;
_CKFFR[292] = 0.0;
_CKFFR[293] = 0.0;
_CKFFR[294] = 0.0;
_CKFFR[295] = 0.0;
_CKFFR[296] = 0.0;
_CKFFR[297] = 0.0;
_CKFFR[298] = 0.0;
_CKFFR[299] = 0.0;
_CKFFR[300] = 0.0;
_CKFFR[301] = 0.0;
_CKFFR[302] = 0.0;
_CKFFR[303] = 0.0;
_CKFFR[304] = 0.0;
_CKFFR[305] = 0.0;
_CKFFR[306] = 0.0;
_CKFFR[307] = 0.0;
_CKFFR[308] = atom64440*atom64596;
_CKFFR[309] =  atom64440*atom64597+atom64601*atom64580+atom64545*atom64598;
_CKFFR[310] =  atom64545*atom64602+atom64580*atom64603;
_CKFFR[311] =  atom64440*atom64604+atom64607*atom64545+atom64612*atom64580;
_CKFFR[312] =  atom64616*atom64545+atom64440*atom64613+atom64619*atom64580;
_CKFFR[313] =  atom64580*atom64626+atom64623*atom64545+atom64620*atom64440;
_CKFFR[314] = 0.0;
_CKFFR[315] =  atom64440*atom64627+atom64633*atom64580+atom64630*atom64545;
_CKFFR[316] = 0.0;
_CKFFR[317] = 0.0;
_CKFFR[318] = 0.0;
_CKFFR[319] =  atom64545*atom64635+atom64580*atom64636+atom64440*atom64634;
_CKFFR[320] =  atom64545*atom64640+atom64440*atom64637+atom64580*atom64643;
_CKFFR[321] =  atom64650*atom64580+atom64545*atom64647+atom64440*atom64644;
_CKFFR[322] = 0.0;
_CKFFR[323] = 0.0;
_CKFFR[324] = 0.0;
_CKFFR[325] = 0.0;
_CKFFR[326] = 0.0;
_CKFFR[327] = 0.0;
_CKFFR[328] =  atom64440*atom64651+atom64653*atom64580+atom64652*atom64545;
_CKFFR[329] =  atom64656*atom64545+atom64440*atom64654+atom64580*atom64658;
_CKFFR[330] =  atom64665*atom64580+atom64662*atom64545+atom64440*atom64659;
_CKFFR[331] = 0.0;
_CKFFR[332] = 0.0;
_CKFFR[333] = 0.0;
_CKFFR[334] = 0.0;
_CKFFR[335] = 0.0;
_CKFFR[336] = 0.0;
_CKFFR[337] = 0.0;
_CKFFR[338] = 0.0;
_CKFFR[339] = 0.0;
_CKFFR[340] = 0.0;
_CKFFR[341] = 0.0;
_CKFFR[342] = 0.0;
_CKFFR[343] = 0.0;
_CKFFR[344] = 0.0;
_CKFFR[345] = 0.0;
_CKFFR[346] = 0.0;
_CKFFR[347] = 0.0;
_CKFFR[348] = 0.0;
_CKFFR[349] = 0.0;
_CKFFR[350] = 0.0;
_CKFFR[351] = 0.0;
_CKFFR[352] = 0.0;
_CKFFR[353] = 0.0;
_CKFFR[354] = 0.0;
_CKFFR[355] = 0.0;
_CKFFR[356] = 0.0;
_CKFFR[357] = 0.0;
_CKFFR[358] = 0.0;
_CKFFR[359] = 0.0;
_CKFFR[360] = 0.0;
_CKFFR[361] = 0.0;
_CKFFR[362] = 0.0;
_CKFFR[363] = 0.0;
_CKFFR[364] = 0.0;
_CKFFR[365] = 0.0;
_CKFFR[366] = 0.0;
_CKFFR[367] = 0.0;
_CKFFR[368] = 0.0;
_CKFFR[369] = 0.0;
_CKFFR[370] = 0.0;
_CKFFR[371] = 0.0;
_CKFFR[372] = 0.0;
_CKFFR[373] = 0.0;
_CKFFR[374] = 0.0;
_CKFFR[375] = 0.0;
_CKFFR[376] = 0.0;
_CKFFR[377] = 0.0;
_CKFFR[378] = 0.0;
_CKFFR[379] = 0.0;
_CKFFR[380] = 0.0;
_CKFFR[381] = 0.0;
_CKFFR[382] = 0.0;
_CKFFR[383] = 0.0;
_CKFFR[384] = 0.0;
_CKFFR[385] = 0.0;
_CKFFR[386] = 0.0;
_CKFFR[387] = 0.0;
_CKFFR[388] = 0.0;
_CKFFR[389] = 0.0;
_CKFFR[390] = 0.0;
_CKFFR[391] = 0.0;
_CKFFR[392] = 0.0;
_CKFFR[393] = 0.0;
_CKFFR[394] = 0.0;
_CKFFR[395] = 0.0;
_CKFFR[396] = 0.0;
_CKFFR[397] = 0.0;
_CKFFR[398] = 0.0;
_CKFFR[399] = 0.0;
_CKFFR[400] = 0.0;
_CKFFR[401] = 0.0;
_CKFFR[402] = 0.0;
_CKFFR[403] = 0.0;
_CKFFR[404] = 0.0;
_CKFFR[405] = 0.0;
_CKFFR[406] = 0.0;
_CKFFR[407] = 0.0;
_CKFFR[408] = 0.0;
_CKFFR[409] = 0.0;
_CKFFR[410] = 0.0;
_CKFFR[411] = 0.0;
_CKFFR[412] = 0.0;
_CKFFR[413] = 0.0;
_CKFFR[414] = 0.0;
_CKFFR[415] = 0.0;
_CKFFR[416] = 0.0;
_CKFFR[417] = 0.0;
_CKFFR[418] = 0.0;
_CKFFR[419] = 0.0;
_CKFFR[420] = 0.0;
_CKFFR[421] = 0.0;
_CKFFR[422] = 0.0;
_CKFFR[423] = 0.0;
_CKFFR[424] = 0.0;
_CKFFR[425] = 0.0;
_CKFFR[426] = 0.0;
_CKFFR[427] = 0.0;
_CKFFR[428] = 0.0;
_CKFFR[429] = 0.0;
_CKFFR[430] = 0.0;
_CKFFR[431] = 0.0;
_CKFFR[432] = 0.0;
_CKFFR[433] = 0.0;
_CKFFR[434] = 0.0;
_CKFFR[435] = 0.0;
_CKFFR[436] = 0.0;
_CKFFR[437] = 0.0;
_CKFFR[438] = 0.0;
_CKFFR[439] = 0.0;
_CKFFR[440] = 0.0;
_CKFFR[441] = 0.0;
_CKFFR[442] = 0.0;
_CKFFR[443] = 0.0;
_CKFFR[444] = 0.0;
_CKFFR[445] = 0.0;
_CKFFR[446] = 0.0;
_CKFFR[447] = 0.0;
_CKFFR[448] = 0.0;
_CKFFR[449] = 0.0;
_CKFFR[450] = 0.0;
_CKFFR[451] = 0.0;
_CKFFR[452] = 0.0;
_CKFFR[453] = 0.0;
_CKFFR[454] = 0.0;
_CKFFR[455] = 0.0;
_CKFFR[456] = 0.0;
_CKFFR[457] = 0.0;
_CKFFR[458] = 0.0;
_CKFFR[459] = 0.0;
_CKFFR[460] = 0.0;
_CKFFR[461] = 0.0;
_CKFFR[462] = 0.0;
_CKFFR[463] = 0.0;
_CKFFR[464] = 0.0;
_CKFFR[465] = 0.0;
_CKFFR[466] = 0.0;
_CKFFR[467] = 0.0;
_CKFFR[468] = 0.0;
_CKFFR[469] = 0.0;
_CKFFR[470] = 0.0;
_CKFFR[471] = 0.0;
_CKFFR[472] = 0.0;
_CKFFR[473] = 0.0;
_CKFFR[474] = 0.0;
_CKFFR[475] = 0.0;
_CKFFR[476] = 0.0;
_CKFFR[477] = 0.0;
_CKFFR[478] = 0.0;
_CKFFR[479] = 0.0;
_CKFFR[480] = 0.0;
_CKFFR[481] = 0.0;
_CKFFR[482] = 0.0;
_CKFFR[483] = 0.0;
_CKFFR[484] = atom8887*atom64596;
_CKFFR[485] =  atom8936*atom64598+atom8887*atom64597;
_CKFFR[486] = atom8936*atom64602;
_CKFFR[487] =  atom8936*atom64607+atom8887*atom64604;
_CKFFR[488] =  atom8936*atom64616+atom8887*atom64613;
_CKFFR[489] =  atom8936*atom64623+atom64620*atom8887;
_CKFFR[490] = 0.0;
_CKFFR[491] =  atom8936*atom64630+atom8887*atom64627;
_CKFFR[492] = 0.0;
_CKFFR[493] = 0.0;
_CKFFR[494] = 0.0;
_CKFFR[495] =  atom8887*atom64634+atom8936*atom64635;
_CKFFR[496] =  atom8936*atom64640+atom64637*atom8887;
_CKFFR[497] =  atom64644*atom8887+atom8936*atom64647;
_CKFFR[498] = 0.0;
_CKFFR[499] = 0.0;
_CKFFR[500] = 0.0;
_CKFFR[501] = 0.0;
_CKFFR[502] = 0.0;
_CKFFR[503] = 0.0;
_CKFFR[504] =  atom64652*atom8936+atom8887*atom64651;
_CKFFR[505] =  atom64654*atom8887+atom8936*atom64656;
_CKFFR[506] =  atom64659*atom8887+atom8936*atom64662;
_CKFFR[507] = 0.0;
_CKFFR[508] = 0.0;
_CKFFR[509] = 0.0;
_CKFFR[510] = 0.0;
_CKFFR[511] = 0.0;
_CKFFR[512] = 0.0;
_CKFFR[513] = 0.0;
_CKFFR[514] = 0.0;
_CKFFR[515] = 0.0;
_CKFFR[516] = 0.0;
_CKFFR[517] = 0.0;
_CKFFR[518] = 0.0;
_CKFFR[519] = 0.0;
_CKFFR[520] = 0.0;
_CKFFR[521] = 0.0;
_CKFFR[522] = 0.0;
_CKFFR[523] = 0.0;
_CKFFR[524] = 0.0;
_CKFFR[525] = 0.0;
_CKFFR[526] = 0.0;
_CKFFR[527] = 0.0;
_CKFFR[528] = atom64466*atom64596;
_CKFFR[529] =  atom64709+atom64466*atom64597+atom64552*atom64598;
_CKFFR[530] =  atom64602*atom64552+atom64744;
_CKFFR[531] =  atom64607*atom64552+atom64466*atom64604+atom64786;
_CKFFR[532] =  atom64466*atom64613+atom64836+atom64616*atom64552;
_CKFFR[533] =  atom64623*atom64552+atom64886+atom64620*atom64466;
_CKFFR[534] = 0.0;
_CKFFR[535] =  atom64466*atom64627+atom64630*atom64552+atom64936;
_CKFFR[536] = 0.0;
_CKFFR[537] = 0.0;
_CKFFR[538] = 0.0;
_CKFFR[539] =  atom64986+atom64466*atom64634+atom64552*atom64635;
_CKFFR[540] =  atom65036+atom64466*atom64637+atom64552*atom64640;
_CKFFR[541] =  atom65086+atom64647*atom64552+atom64466*atom64644;
_CKFFR[542] = 0.0;
_CKFFR[543] = 0.0;
_CKFFR[544] = 0.0;
_CKFFR[545] = 0.0;
_CKFFR[546] = 0.0;
_CKFFR[547] = 0.0;
_CKFFR[548] =  atom64466*atom64651+atom64652*atom64552+atom65136;
_CKFFR[549] =  atom65186+atom64466*atom64654+atom64656*atom64552;
_CKFFR[550] =  atom65236+atom64466*atom64659+atom64662*atom64552;
_CKFFR[551] = 0.0;
_CKFFR[552] = 0.0;
_CKFFR[553] = 0.0;
_CKFFR[554] = 0.0;
_CKFFR[555] = 0.0;
_CKFFR[556] = 0.0;
_CKFFR[557] = 0.0;
_CKFFR[558] = 0.0;
_CKFFR[559] = 0.0;
_CKFFR[560] = 0.0;
_CKFFR[561] = 0.0;
_CKFFR[562] = 0.0;
_CKFFR[563] = 0.0;
_CKFFR[564] = 0.0;
_CKFFR[565] = 0.0;
_CKFFR[566] = 0.0;
_CKFFR[567] = 0.0;
_CKFFR[568] = 0.0;
_CKFFR[569] = 0.0;
_CKFFR[570] = 0.0;
_CKFFR[571] = 0.0;
_CKFFR[572] = atom64485*atom64596;
_CKFFR[573] =  atom64601*atom64590+atom64559*atom64598+atom64485*atom64597;
_CKFFR[574] =  atom64559*atom64602+atom64590*atom64603;
_CKFFR[575] =  atom64485*atom64604+atom64559*atom64607+atom64612*atom64590;
_CKFFR[576] =  atom64485*atom64613+atom64619*atom64590+atom64559*atom64616;
_CKFFR[577] =  atom64590*atom64626+atom64559*atom64623+atom64620*atom64485;
_CKFFR[578] = 0.0;
_CKFFR[579] =  atom64630*atom64559+atom64633*atom64590+atom64485*atom64627;
_CKFFR[580] = 0.0;
_CKFFR[581] = 0.0;
_CKFFR[582] = 0.0;
_CKFFR[583] =  atom64485*atom64634+atom64559*atom64635+atom64590*atom64636;
_CKFFR[584] =  atom64590*atom64643+atom64559*atom64640+atom64485*atom64637;
_CKFFR[585] =  atom64559*atom64647+atom64644*atom64485+atom64650*atom64590;
_CKFFR[586] = 0.0;
_CKFFR[587] = 0.0;
_CKFFR[588] = 0.0;
_CKFFR[589] = 0.0;
_CKFFR[590] = 0.0;
_CKFFR[591] = 0.0;
_CKFFR[592] =  atom64652*atom64559+atom64485*atom64651+atom64653*atom64590;
_CKFFR[593] =  atom64559*atom64656+atom64485*atom64654+atom64658*atom64590;
_CKFFR[594] =  atom64559*atom64662+atom64665*atom64590+atom64485*atom64659;
_CKFFR[595] = 0.0;
_CKFFR[596] = 0.0;
_CKFFR[597] = 0.0;
_CKFFR[598] = 0.0;
_CKFFR[599] = 0.0;
_CKFFR[600] = 0.0;
_CKFFR[601] = 0.0;
_CKFFR[602] = 0.0;
_CKFFR[603] = 0.0;
_CKFFR[604] = 0.0;
_CKFFR[605] = 0.0;
_CKFFR[606] = 0.0;
_CKFFR[607] = 0.0;
_CKFFR[608] = 0.0;
_CKFFR[609] = 0.0;
_CKFFR[610] = 0.0;
_CKFFR[611] = 0.0;
_CKFFR[612] = 0.0;
_CKFFR[613] = 0.0;
_CKFFR[614] = 0.0;
_CKFFR[615] = 0.0;
_CKFFR[616] = 0.0;
_CKFFR[617] = 0.0;
_CKFFR[618] = 0.0;
_CKFFR[619] = 0.0;
_CKFFR[620] = 0.0;
_CKFFR[621] = 0.0;
_CKFFR[622] = 0.0;
_CKFFR[623] = 0.0;
_CKFFR[624] = 0.0;
_CKFFR[625] = 0.0;
_CKFFR[626] = 0.0;
_CKFFR[627] = 0.0;
_CKFFR[628] = 0.0;
_CKFFR[629] = 0.0;
_CKFFR[630] = 0.0;
_CKFFR[631] = 0.0;
_CKFFR[632] = 0.0;
_CKFFR[633] = 0.0;
_CKFFR[634] = 0.0;
_CKFFR[635] = 0.0;
_CKFFR[636] = 0.0;
_CKFFR[637] = 0.0;
_CKFFR[638] = 0.0;
_CKFFR[639] = 0.0;
_CKFFR[640] = 0.0;
_CKFFR[641] = 0.0;
_CKFFR[642] = 0.0;
_CKFFR[643] = 0.0;
_CKFFR[644] = 0.0;
_CKFFR[645] = 0.0;
_CKFFR[646] = 0.0;
_CKFFR[647] = 0.0;
_CKFFR[648] = 0.0;
_CKFFR[649] = 0.0;
_CKFFR[650] = 0.0;
_CKFFR[651] = 0.0;
_CKFFR[652] = 0.0;
_CKFFR[653] = 0.0;
_CKFFR[654] = 0.0;
_CKFFR[655] = 0.0;
_CKFFR[656] = 0.0;
_CKFFR[657] = 0.0;
_CKFFR[658] = 0.0;
_CKFFR[659] = 0.0;
_CKFFR[660] = 0.0;
_CKFFR[661] = 0.0;
_CKFFR[662] = 0.0;
_CKFFR[663] = 0.0;
_CKFFR[664] = 0.0;
_CKFFR[665] = 0.0;
_CKFFR[666] = 0.0;
_CKFFR[667] = 0.0;
_CKFFR[668] = 0.0;
_CKFFR[669] = 0.0;
_CKFFR[670] = 0.0;
_CKFFR[671] = 0.0;
_CKFFR[672] = 0.0;
_CKFFR[673] = 0.0;
_CKFFR[674] = 0.0;
_CKFFR[675] = 0.0;
_CKFFR[676] = 0.0;
_CKFFR[677] = 0.0;
_CKFFR[678] = 0.0;
_CKFFR[679] = 0.0;
_CKFFR[680] = 0.0;
_CKFFR[681] = 0.0;
_CKFFR[682] = 0.0;
_CKFFR[683] = 0.0;
_CKFFR[684] = 0.0;
_CKFFR[685] = 0.0;
_CKFFR[686] = 0.0;
_CKFFR[687] = 0.0;
_CKFFR[688] = 0.0;
_CKFFR[689] = 0.0;
_CKFFR[690] = 0.0;
_CKFFR[691] = 0.0;
_CKFFR[692] = 0.0;
_CKFFR[693] = 0.0;
_CKFFR[694] = 0.0;
_CKFFR[695] = 0.0;
_CKFFR[696] = 0.0;
_CKFFR[697] = 0.0;
_CKFFR[698] = 0.0;
_CKFFR[699] = 0.0;
_CKFFR[700] = 0.0;
_CKFFR[701] = 0.0;
_CKFFR[702] = 0.0;
_CKFFR[703] = 0.0;
_CKFFR[704] = 0.0;
_CKFFR[705] = 0.0;
_CKFFR[706] = 0.0;
_CKFFR[707] = 0.0;
_CKFFR[708] = 0.0;
_CKFFR[709] = 0.0;
_CKFFR[710] = 0.0;
_CKFFR[711] = 0.0;
_CKFFR[712] = 0.0;
_CKFFR[713] = 0.0;
_CKFFR[714] = 0.0;
_CKFFR[715] = 0.0;
_CKFFR[716] = 0.0;
_CKFFR[717] = 0.0;
_CKFFR[718] = 0.0;
_CKFFR[719] = 0.0;
_CKFFR[720] = 0.0;
_CKFFR[721] = 0.0;
_CKFFR[722] = 0.0;
_CKFFR[723] = 0.0;
_CKFFR[724] = 0.0;
_CKFFR[725] = 0.0;
_CKFFR[726] = 0.0;
_CKFFR[727] = 0.0;
_CKFFR[728] = 0.0;
_CKFFR[729] = 0.0;
_CKFFR[730] = 0.0;
_CKFFR[731] = 0.0;
_CKFFR[732] = 0.0;
_CKFFR[733] = 0.0;
_CKFFR[734] = 0.0;
_CKFFR[735] = 0.0;
_CKFFR[736] = 0.0;
_CKFFR[737] = 0.0;
_CKFFR[738] = 0.0;
_CKFFR[739] = 0.0;
_CKFFR[740] = 0.0;
_CKFFR[741] = 0.0;
_CKFFR[742] = 0.0;
_CKFFR[743] = 0.0;
_CKFFR[744] = 0.0;
_CKFFR[745] = 0.0;
_CKFFR[746] = 0.0;
_CKFFR[747] = 0.0;
_CKFFR[748] = 0.0;
_CKFFR[749] = 0.0;
_CKFFR[750] = 0.0;
_CKFFR[751] = 0.0;
_CKFFR[752] = 0.0;
_CKFFR[753] = 0.0;
_CKFFR[754] = 0.0;
_CKFFR[755] = 0.0;
_CKFFR[756] = 0.0;
_CKFFR[757] = 0.0;
_CKFFR[758] = 0.0;
_CKFFR[759] = 0.0;
_CKFFR[760] = 0.0;
_CKFFR[761] = 0.0;
_CKFFR[762] = 0.0;
_CKFFR[763] = 0.0;
_CKFFR[764] = 0.0;
_CKFFR[765] = 0.0;
_CKFFR[766] = 0.0;
_CKFFR[767] = 0.0;
_CKFFR[768] = 0.0;
_CKFFR[769] = 0.0;
_CKFFR[770] = 0.0;
_CKFFR[771] = 0.0;
_CKFFR[772] = 0.0;
_CKFFR[773] = 0.0;
_CKFFR[774] = 0.0;
_CKFFR[775] = 0.0;
_CKFFR[776] = 0.0;
_CKFFR[777] = 0.0;
_CKFFR[778] = 0.0;
_CKFFR[779] = 0.0;
_CKFFR[780] = 0.0;
_CKFFR[781] = 0.0;
_CKFFR[782] = 0.0;
_CKFFR[783] = 0.0;
_CKFFR[784] = 0.0;
_CKFFR[785] = 0.0;
_CKFFR[786] = 0.0;
_CKFFR[787] = 0.0;
_CKFFR[788] = 0.0;
_CKFFR[789] = 0.0;
_CKFFR[790] = 0.0;
_CKFFR[791] = 0.0;
_CKFFR[792] = 0.0;
_CKFFR[793] = 0.0;
_CKFFR[794] = 0.0;
_CKFFR[795] = 0.0;
_CKFFR[796] = 0.0;
_CKFFR[797] = 0.0;
_CKFFR[798] = 0.0;
_CKFFR[799] = 0.0;
_CKFFR[800] = 0.0;
_CKFFR[801] = 0.0;
_CKFFR[802] = 0.0;
_CKFFR[803] = 0.0;
_CKFFR[804] = 0.0;
_CKFFR[805] = 0.0;
_CKFFR[806] = 0.0;
_CKFFR[807] = 0.0;
_CKFFR[808] = 0.0;
_CKFFR[809] = 0.0;
_CKFFR[810] = 0.0;
_CKFFR[811] = 0.0;
_CKFFR[812] = 0.0;
_CKFFR[813] = 0.0;
_CKFFR[814] = 0.0;
_CKFFR[815] = 0.0;
_CKFFR[816] = 0.0;
_CKFFR[817] = 0.0;
_CKFFR[818] = 0.0;
_CKFFR[819] = 0.0;
_CKFFR[820] = 0.0;
_CKFFR[821] = 0.0;
_CKFFR[822] = 0.0;
_CKFFR[823] = 0.0;
_CKFFR[824] = 0.0;
_CKFFR[825] = 0.0;
_CKFFR[826] = 0.0;
_CKFFR[827] = 0.0;
_CKFFR[828] = 0.0;
_CKFFR[829] = 0.0;
_CKFFR[830] = 0.0;
_CKFFR[831] = 0.0;
_CKFFR[832] = 0.0;
_CKFFR[833] = 0.0;
_CKFFR[834] = 0.0;
_CKFFR[835] = 0.0;
_CKFFR[836] = 0.0;
_CKFFR[837] = 0.0;
_CKFFR[838] = 0.0;
_CKFFR[839] = 0.0;
_CKFFR[840] = 0.0;
_CKFFR[841] = 0.0;
_CKFFR[842] = 0.0;
_CKFFR[843] = 0.0;
_CKFFR[844] = 0.0;
_CKFFR[845] = 0.0;
_CKFFR[846] = 0.0;
_CKFFR[847] = 0.0;
_CKFFR[848] = 0.0;
_CKFFR[849] = 0.0;
_CKFFR[850] = 0.0;
_CKFFR[851] = 0.0;
_CKFFR[852] = 0.0;
_CKFFR[853] = 0.0;
_CKFFR[854] = 0.0;
_CKFFR[855] = 0.0;
_CKFFR[856] = 0.0;
_CKFFR[857] = 0.0;
_CKFFR[858] = 0.0;
_CKFFR[859] = 0.0;
_CKFFR[860] = 0.0;
_CKFFR[861] = 0.0;
_CKFFR[862] = 0.0;
_CKFFR[863] = 0.0;
_CKFFR[864] = 0.0;
_CKFFR[865] = 0.0;
_CKFFR[866] = 0.0;
_CKFFR[867] = 0.0;
_CKFFR[868] = 0.0;
_CKFFR[869] = 0.0;
_CKFFR[870] = 0.0;
_CKFFR[871] = 0.0;
_CKFFR[872] = 0.0;
_CKFFR[873] = 0.0;
_CKFFR[874] = 0.0;
_CKFFR[875] = 0.0;
_CKFFR[876] = 0.0;
_CKFFR[877] = 0.0;
_CKFFR[878] = 0.0;
_CKFFR[879] = 0.0;
_CKFFR[880] = atom8896*atom64596;
_CKFFR[881] =  atom8896*atom64597+atom8945*atom64598;
_CKFFR[882] = atom8945*atom64602;
_CKFFR[883] =  atom8896*atom64604+atom8945*atom64607;
_CKFFR[884] =  atom8896*atom64613+atom8945*atom64616;
_CKFFR[885] =  atom64620*atom8896+atom8945*atom64623;
_CKFFR[886] = 0.0;
_CKFFR[887] =  atom8896*atom64627+atom8945*atom64630;
_CKFFR[888] = 0.0;
_CKFFR[889] = 0.0;
_CKFFR[890] = 0.0;
_CKFFR[891] =  atom8945*atom64635+atom64634*atom8896;
_CKFFR[892] =  atom64637*atom8896+atom8945*atom64640;
_CKFFR[893] =  atom8945*atom64647+atom64644*atom8896;
_CKFFR[894] = 0.0;
_CKFFR[895] = 0.0;
_CKFFR[896] = 0.0;
_CKFFR[897] = 0.0;
_CKFFR[898] = 0.0;
_CKFFR[899] = 0.0;
_CKFFR[900] =  atom64651*atom8896+atom64652*atom8945;
_CKFFR[901] =  atom64654*atom8896+atom8945*atom64656;
_CKFFR[902] =  atom8945*atom64662+atom64659*atom8896;
_CKFFR[903] = 0.0;
_CKFFR[904] = 0.0;
_CKFFR[905] = 0.0;
_CKFFR[906] = 0.0;
_CKFFR[907] = 0.0;
_CKFFR[908] = 0.0;
_CKFFR[909] = 0.0;
_CKFFR[910] = 0.0;
_CKFFR[911] = 0.0;
_CKFFR[912] = 0.0;
_CKFFR[913] = 0.0;
_CKFFR[914] = 0.0;
_CKFFR[915] = 0.0;
_CKFFR[916] = 0.0;
_CKFFR[917] = 0.0;
_CKFFR[918] = 0.0;
_CKFFR[919] = 0.0;
_CKFFR[920] = 0.0;
_CKFFR[921] = 0.0;
_CKFFR[922] = 0.0;
_CKFFR[923] = 0.0;
_CKFFR[924] = atom64488*atom64596;
_CKFFR[925] =  atom64709+atom64562*atom64598+atom64488*atom64597;
_CKFFR[926] =  atom64744+atom64602*atom64562;
_CKFFR[927] =  atom64786+atom64607*atom64562+atom64488*atom64604;
_CKFFR[928] =  atom64836+atom64616*atom64562+atom64488*atom64613;
_CKFFR[929] =  atom64620*atom64488+atom64886+atom64623*atom64562;
_CKFFR[930] = 0.0;
_CKFFR[931] =  atom64630*atom64562+atom64936+atom64488*atom64627;
_CKFFR[932] = 0.0;
_CKFFR[933] = 0.0;
_CKFFR[934] = 0.0;
_CKFFR[935] =  atom64635*atom64562+atom64488*atom64634+atom64986;
_CKFFR[936] =  atom64640*atom64562+atom65036+atom64637*atom64488;
_CKFFR[937] =  atom65086+atom64647*atom64562+atom64644*atom64488;
_CKFFR[938] = 0.0;
_CKFFR[939] = 0.0;
_CKFFR[940] = 0.0;
_CKFFR[941] = 0.0;
_CKFFR[942] = 0.0;
_CKFFR[943] = 0.0;
_CKFFR[944] =  atom64652*atom64562+atom64488*atom64651+atom65136;
_CKFFR[945] =  atom64656*atom64562+atom64488*atom64654+atom65186;
_CKFFR[946] =  atom64662*atom64562+atom65236+atom64659*atom64488;
_CKFFR[947] = 0.0;
_CKFFR[948] = 0.0;
_CKFFR[949] = 0.0;
_CKFFR[950] = 0.0;
_CKFFR[951] = 0.0;
_CKFFR[952] = 0.0;
_CKFFR[953] = 0.0;
_CKFFR[954] = 0.0;
_CKFFR[955] = 0.0;
_CKFFR[956] = 0.0;
_CKFFR[957] = 0.0;
_CKFFR[958] = 0.0;
_CKFFR[959] = 0.0;
_CKFFR[960] = 0.0;
_CKFFR[961] = 0.0;
_CKFFR[962] = 0.0;
_CKFFR[963] = 0.0;
_CKFFR[964] = 0.0;
_CKFFR[965] = 0.0;
_CKFFR[966] = 0.0;
_CKFFR[967] = 0.0;
_CKFFR[968] = atom64523*atom64596;
_CKFFR[969] =  atom64601*atom64595+atom64523*atom64597+atom64568*atom64598;
_CKFFR[970] =  atom64595*atom64603+atom64602*atom64568;
_CKFFR[971] =  atom64523*atom64604+atom64607*atom64568+atom64612*atom64595;
_CKFFR[972] =  atom64523*atom64613+atom64595*atom64619+atom64616*atom64568;
_CKFFR[973] =  atom64595*atom64626+atom64623*atom64568+atom64620*atom64523;
_CKFFR[974] = 0.0;
_CKFFR[975] =  atom64630*atom64568+atom64523*atom64627+atom64633*atom64595;
_CKFFR[976] = 0.0;
_CKFFR[977] = 0.0;
_CKFFR[978] = 0.0;
_CKFFR[979] =  atom64523*atom64634+atom64635*atom64568+atom64595*atom64636;
_CKFFR[980] =  atom64595*atom64643+atom64640*atom64568+atom64523*atom64637;
_CKFFR[981] =  atom64644*atom64523+atom64650*atom64595+atom64647*atom64568;
_CKFFR[982] = 0.0;
_CKFFR[983] = 0.0;
_CKFFR[984] = 0.0;
_CKFFR[985] = 0.0;
_CKFFR[986] = 0.0;
_CKFFR[987] = 0.0;
_CKFFR[988] =  atom64652*atom64568+atom64653*atom64595+atom64523*atom64651;
_CKFFR[989] =  atom64656*atom64568+atom64523*atom64654+atom64595*atom64658;
_CKFFR[990] =  atom64659*atom64523+atom64665*atom64595+atom64662*atom64568;
_CKFFR[991] = 0.0;
_CKFFR[992] = 0.0;
_CKFFR[993] = 0.0;
_CKFFR[994] = 0.0;
_CKFFR[995] = 0.0;
_CKFFR[996] = 0.0;
_CKFFR[997] = 0.0;
_CKFFR[998] = 0.0;
_CKFFR[999] = 0.0;
_CKFFR[1000] = 0.0;
_CKFFR[1001] = 0.0;
_CKFFR[1002] = 0.0;
_CKFFR[1003] = 0.0;
_CKFFR[1004] = 0.0;
_CKFFR[1005] = 0.0;
_CKFFR[1006] = 0.0;
_CKFFR[1007] = 0.0;
_CKFFR[1008] = 0.0;
_CKFFR[1009] = 0.0;
_CKFFR[1010] = 0.0;
_CKFFR[1011] = 0.0;
_CKFFR[1012] = 0.0;
_CKFFR[1013] = 0.0;
_CKFFR[1014] = 0.0;
_CKFFR[1015] = 0.0;
_CKFFR[1016] = 0.0;
_CKFFR[1017] = 0.0;
_CKFFR[1018] = 0.0;
_CKFFR[1019] = 0.0;
_CKFFR[1020] = 0.0;
_CKFFR[1021] = 0.0;
_CKFFR[1022] = 0.0;
_CKFFR[1023] = 0.0;
_CKFFR[1024] = 0.0;
_CKFFR[1025] = 0.0;
_CKFFR[1026] = 0.0;
_CKFFR[1027] = 0.0;
_CKFFR[1028] = 0.0;
_CKFFR[1029] = 0.0;
_CKFFR[1030] = 0.0;
_CKFFR[1031] = 0.0;
_CKFFR[1032] = 0.0;
_CKFFR[1033] = 0.0;
_CKFFR[1034] = 0.0;
_CKFFR[1035] = 0.0;
_CKFFR[1036] = 0.0;
_CKFFR[1037] = 0.0;
_CKFFR[1038] = 0.0;
_CKFFR[1039] = 0.0;
_CKFFR[1040] = 0.0;
_CKFFR[1041] = 0.0;
_CKFFR[1042] = 0.0;
_CKFFR[1043] = 0.0;
_CKFFR[1044] = 0.0;
_CKFFR[1045] = 0.0;
_CKFFR[1046] = 0.0;
_CKFFR[1047] = 0.0;
_CKFFR[1048] = 0.0;
_CKFFR[1049] = 0.0;
_CKFFR[1050] = 0.0;
_CKFFR[1051] = 0.0;
_CKFFR[1052] = 0.0;
_CKFFR[1053] = 0.0;
_CKFFR[1054] = 0.0;
_CKFFR[1055] = 0.0;
_CKFFR[1056] = 0.0;
_CKFFR[1057] = 0.0;
_CKFFR[1058] = 0.0;
_CKFFR[1059] = 0.0;
_CKFFR[1060] = 0.0;
_CKFFR[1061] = 0.0;
_CKFFR[1062] = 0.0;
_CKFFR[1063] = 0.0;
_CKFFR[1064] = 0.0;
_CKFFR[1065] = 0.0;
_CKFFR[1066] = 0.0;
_CKFFR[1067] = 0.0;
_CKFFR[1068] = 0.0;
_CKFFR[1069] = 0.0;
_CKFFR[1070] = 0.0;
_CKFFR[1071] = 0.0;
_CKFFR[1072] = 0.0;
_CKFFR[1073] = 0.0;
_CKFFR[1074] = 0.0;
_CKFFR[1075] = 0.0;
_CKFFR[1076] = 0.0;
_CKFFR[1077] = 0.0;
_CKFFR[1078] = 0.0;
_CKFFR[1079] = 0.0;
_CKFFR[1080] = 0.0;
_CKFFR[1081] = 0.0;
_CKFFR[1082] = 0.0;
_CKFFR[1083] = 0.0;
_CKFFR[1084] = 0.0;
_CKFFR[1085] = 0.0;
_CKFFR[1086] = 0.0;
_CKFFR[1087] = 0.0;
_CKFFR[1088] = 0.0;
_CKFFR[1089] = 0.0;
_CKFFR[1090] = 0.0;
_CKFFR[1091] = 0.0;
_CKFFR[1092] = 0.0;
_CKFFR[1093] = 0.0;
_CKFFR[1094] = 0.0;
_CKFFR[1095] = 0.0;
_CKFFR[1096] = 0.0;
_CKFFR[1097] = 0.0;
_CKFFR[1098] = 0.0;
_CKFFR[1099] = 0.0;
_CKFFR[1100] = 0.0;
_CKFFR[1101] = 0.0;
_CKFFR[1102] = 0.0;
_CKFFR[1103] = 0.0;
_CKFFR[1104] = 0.0;
_CKFFR[1105] = 0.0;
_CKFFR[1106] = 0.0;
_CKFFR[1107] = 0.0;
_CKFFR[1108] = 0.0;
_CKFFR[1109] = 0.0;
_CKFFR[1110] = 0.0;
_CKFFR[1111] = 0.0;
_CKFFR[1112] = 0.0;
_CKFFR[1113] = 0.0;
_CKFFR[1114] = 0.0;
_CKFFR[1115] = 0.0;
_CKFFR[1116] = 0.0;
_CKFFR[1117] = 0.0;
_CKFFR[1118] = 0.0;
_CKFFR[1119] = 0.0;
_CKFFR[1120] = 0.0;
_CKFFR[1121] = 0.0;
_CKFFR[1122] = 0.0;
_CKFFR[1123] = 0.0;
_CKFFR[1124] = 0.0;
_CKFFR[1125] = 0.0;
_CKFFR[1126] = 0.0;
_CKFFR[1127] = 0.0;
_CKFFR[1128] = 0.0;
_CKFFR[1129] = 0.0;
_CKFFR[1130] = 0.0;
_CKFFR[1131] = 0.0;
_CKFFR[1132] = 0.0;
_CKFFR[1133] = 0.0;
_CKFFR[1134] = 0.0;
_CKFFR[1135] = 0.0;
_CKFFR[1136] = 0.0;
_CKFFR[1137] = 0.0;
_CKFFR[1138] = 0.0;
_CKFFR[1139] = 0.0;
_CKFFR[1140] = 0.0;
_CKFFR[1141] = 0.0;
_CKFFR[1142] = 0.0;
_CKFFR[1143] = 0.0;
_CKFFR[1144] = 0.0;
_CKFFR[1145] = 0.0;
_CKFFR[1146] = 0.0;
_CKFFR[1147] = 0.0;
_CKFFR[1148] = 0.0;
_CKFFR[1149] = 0.0;
_CKFFR[1150] = 0.0;
_CKFFR[1151] = 0.0;
_CKFFR[1152] = 0.0;
_CKFFR[1153] = 0.0;
_CKFFR[1154] = 0.0;
_CKFFR[1155] = 0.0;
_CKFFR[1156] = 0.0;
_CKFFR[1157] = 0.0;
_CKFFR[1158] = 0.0;
_CKFFR[1159] = 0.0;
_CKFFR[1160] = 0.0;
_CKFFR[1161] = 0.0;
_CKFFR[1162] = 0.0;
_CKFFR[1163] = 0.0;
_CKFFR[1164] = 0.0;
_CKFFR[1165] = 0.0;
_CKFFR[1166] = 0.0;
_CKFFR[1167] = 0.0;
_CKFFR[1168] = 0.0;
_CKFFR[1169] = 0.0;
_CKFFR[1170] = 0.0;
_CKFFR[1171] = 0.0;
_CKFFR[1172] = 0.0;
_CKFFR[1173] = 0.0;
_CKFFR[1174] = 0.0;
_CKFFR[1175] = 0.0;
_CKFFR[1176] = 0.0;
_CKFFR[1177] = 0.0;
_CKFFR[1178] = 0.0;
_CKFFR[1179] = 0.0;
_CKFFR[1180] = 0.0;
_CKFFR[1181] = 0.0;
_CKFFR[1182] = 0.0;
_CKFFR[1183] = 0.0;
_CKFFR[1184] = 0.0;
_CKFFR[1185] = 0.0;
_CKFFR[1186] = 0.0;
_CKFFR[1187] = 0.0;
_CKFFR[1188] = 0.0;
_CKFFR[1189] = 0.0;
_CKFFR[1190] = 0.0;
_CKFFR[1191] = 0.0;
_CKFFR[1192] = 0.0;
_CKFFR[1193] = 0.0;
_CKFFR[1194] = 0.0;
_CKFFR[1195] = 0.0;
_CKFFR[1196] = 0.0;
_CKFFR[1197] = 0.0;
_CKFFR[1198] = 0.0;
_CKFFR[1199] = 0.0;
_CKFFR[1200] = 0.0;
_CKFFR[1201] = 0.0;
_CKFFR[1202] = 0.0;
_CKFFR[1203] = 0.0;
_CKFFR[1204] = 0.0;
_CKFFR[1205] = 0.0;
_CKFFR[1206] = 0.0;
_CKFFR[1207] = 0.0;
_CKFFR[1208] = 0.0;
_CKFFR[1209] = 0.0;
_CKFFR[1210] = 0.0;
_CKFFR[1211] = 0.0;
_CKFFR[1212] = 0.0;
_CKFFR[1213] = 0.0;
_CKFFR[1214] = 0.0;
_CKFFR[1215] = 0.0;
_CKFFR[1216] = 0.0;
_CKFFR[1217] = 0.0;
_CKFFR[1218] = 0.0;
_CKFFR[1219] = 0.0;
_CKFFR[1220] = 0.0;
_CKFFR[1221] = 0.0;
_CKFFR[1222] = 0.0;
_CKFFR[1223] = 0.0;
_CKFFR[1224] = 0.0;
_CKFFR[1225] = 0.0;
_CKFFR[1226] = 0.0;
_CKFFR[1227] = 0.0;
_CKFFR[1228] = 0.0;
_CKFFR[1229] = 0.0;
_CKFFR[1230] = 0.0;
_CKFFR[1231] = 0.0;
_CKFFR[1232] = 0.0;
_CKFFR[1233] = 0.0;
_CKFFR[1234] = 0.0;
_CKFFR[1235] = 0.0;
_CKFFR[1236] = 0.0;
_CKFFR[1237] = 0.0;
_CKFFR[1238] = 0.0;
_CKFFR[1239] = 0.0;
_CKFFR[1240] = 0.0;
_CKFFR[1241] = 0.0;
_CKFFR[1242] = 0.0;
_CKFFR[1243] = 0.0;
_CKFFR[1244] = 0.0;
_CKFFR[1245] = 0.0;
_CKFFR[1246] = 0.0;
_CKFFR[1247] = 0.0;
_CKFFR[1248] = 0.0;
_CKFFR[1249] = 0.0;
_CKFFR[1250] = 0.0;
_CKFFR[1251] = 0.0;
_CKFFR[1252] = 0.0;
_CKFFR[1253] = 0.0;
_CKFFR[1254] = 0.0;
_CKFFR[1255] = 0.0;
_CKFFR[1256] = 0.0;
_CKFFR[1257] = 0.0;
_CKFFR[1258] = 0.0;
_CKFFR[1259] = 0.0;
_CKFFR[1260] = 0.0;
_CKFFR[1261] = 0.0;
_CKFFR[1262] = 0.0;
_CKFFR[1263] = 0.0;
_CKFFR[1264] = 0.0;
_CKFFR[1265] = 0.0;
_CKFFR[1266] = 0.0;
_CKFFR[1267] = 0.0;
_CKFFR[1268] = 0.0;
_CKFFR[1269] = 0.0;
_CKFFR[1270] = 0.0;
_CKFFR[1271] = 0.0;
_CKFFR[1272] = 0.0;
_CKFFR[1273] = 0.0;
_CKFFR[1274] = 0.0;
_CKFFR[1275] = 0.0;
_CKFFR[1276] = 0.0;
_CKFFR[1277] = 0.0;
_CKFFR[1278] = 0.0;
_CKFFR[1279] = 0.0;
_CKFFR[1280] = 0.0;
_CKFFR[1281] = 0.0;
_CKFFR[1282] = 0.0;
_CKFFR[1283] = 0.0;
_CKFFR[1284] = 0.0;
_CKFFR[1285] = 0.0;
_CKFFR[1286] = 0.0;
_CKFFR[1287] = 0.0;
_CKFFR[1288] = 0.0;
_CKFFR[1289] = 0.0;
_CKFFR[1290] = 0.0;
_CKFFR[1291] = 0.0;
_CKFFR[1292] = 0.0;
_CKFFR[1293] = 0.0;
_CKFFR[1294] = 0.0;
_CKFFR[1295] = 0.0;
_CKFFR[1296] = 0.0;
_CKFFR[1297] = 0.0;
_CKFFR[1298] = 0.0;
_CKFFR[1299] = 0.0;
_CKFFR[1300] = 0.0;
_CKFFR[1301] = 0.0;
_CKFFR[1302] = 0.0;
_CKFFR[1303] = 0.0;
_CKFFR[1304] = 0.0;
_CKFFR[1305] = 0.0;
_CKFFR[1306] = 0.0;
_CKFFR[1307] = 0.0;
_CKFFR[1308] = 0.0;
_CKFFR[1309] = 0.0;
_CKFFR[1310] = 0.0;
_CKFFR[1311] = 0.0;
_CKFFR[1312] = 0.0;
_CKFFR[1313] = 0.0;
_CKFFR[1314] = 0.0;
_CKFFR[1315] = 0.0;
_CKFFR[1316] = 0.0;
_CKFFR[1317] = 0.0;
_CKFFR[1318] = 0.0;
_CKFFR[1319] = 0.0;
_CKFFR[1320] = 0.0;
_CKFFR[1321] = 0.0;
_CKFFR[1322] = 0.0;
_CKFFR[1323] = 0.0;
_CKFFR[1324] = 0.0;
_CKFFR[1325] = 0.0;
_CKFFR[1326] = 0.0;
_CKFFR[1327] = 0.0;
_CKFFR[1328] = 0.0;
_CKFFR[1329] = 0.0;
_CKFFR[1330] = 0.0;
_CKFFR[1331] = 0.0;
_CKFFR[1332] = 0.0;
_CKFFR[1333] = 0.0;
_CKFFR[1334] = 0.0;
_CKFFR[1335] = 0.0;
_CKFFR[1336] = 0.0;
_CKFFR[1337] = 0.0;
_CKFFR[1338] = 0.0;
_CKFFR[1339] = 0.0;
_CKFFR[1340] = 0.0;
_CKFFR[1341] = 0.0;
_CKFFR[1342] = 0.0;
_CKFFR[1343] = 0.0;
_CKFFR[1344] = 0.0;
_CKFFR[1345] = 0.0;
_CKFFR[1346] = 0.0;
_CKFFR[1347] = 0.0;
_CKFFR[1348] = 0.0;
_CKFFR[1349] = 0.0;
_CKFFR[1350] = 0.0;
_CKFFR[1351] = 0.0;
_CKFFR[1352] = 0.0;
_CKFFR[1353] = 0.0;
_CKFFR[1354] = 0.0;
_CKFFR[1355] = 0.0;
_CKFFR[1356] = 0.0;
_CKFFR[1357] = 0.0;
_CKFFR[1358] = 0.0;
_CKFFR[1359] = 0.0;
_CKFFR[1360] = 0.0;
_CKFFR[1361] = 0.0;
_CKFFR[1362] = 0.0;
_CKFFR[1363] = 0.0;
_CKFFR[1364] = 0.0;
_CKFFR[1365] = 0.0;
_CKFFR[1366] = 0.0;
_CKFFR[1367] = 0.0;
_CKFFR[1368] = 0.0;
_CKFFR[1369] = 0.0;
_CKFFR[1370] = 0.0;
_CKFFR[1371] = 0.0;
_CKFFR[1372] = 0.0;
_CKFFR[1373] = 0.0;
_CKFFR[1374] = 0.0;
_CKFFR[1375] = 0.0;
_CKFFR[1376] = 0.0;
_CKFFR[1377] = 0.0;
_CKFFR[1378] = 0.0;
_CKFFR[1379] = 0.0;
_CKFFR[1380] = 0.0;
_CKFFR[1381] = 0.0;
_CKFFR[1382] = 0.0;
_CKFFR[1383] = 0.0;
_CKFFR[1384] = 0.0;
_CKFFR[1385] = 0.0;
_CKFFR[1386] = 0.0;
_CKFFR[1387] = 0.0;
_CKFFR[1388] = 0.0;
_CKFFR[1389] = 0.0;
_CKFFR[1390] = 0.0;
_CKFFR[1391] = 0.0;
_CKFFR[1392] = 0.0;
_CKFFR[1393] = 0.0;
_CKFFR[1394] = 0.0;
_CKFFR[1395] = 0.0;
_CKFFR[1396] = 0.0;
_CKFFR[1397] = 0.0;
_CKFFR[1398] = 0.0;
_CKFFR[1399] = 0.0;
_CKFFR[1400] = 0.0;
_CKFFR[1401] = 0.0;
_CKFFR[1402] = 0.0;
_CKFFR[1403] = 0.0;
_CKFFR[1404] = 0.0;
_CKFFR[1405] = 0.0;
_CKFFR[1406] = 0.0;
_CKFFR[1407] = 0.0;
_CKFFR[1408] = 0.0;
_CKFFR[1409] = 0.0;
_CKFFR[1410] = 0.0;
_CKFFR[1411] = 0.0;
_CKFFR[1412] = 0.0;
_CKFFR[1413] = 0.0;
_CKFFR[1414] = 0.0;
_CKFFR[1415] = 0.0;
_CKFFR[1416] = 0.0;
_CKFFR[1417] = 0.0;
_CKFFR[1418] = 0.0;
_CKFFR[1419] = 0.0;
_CKFFR[1420] = 0.0;
_CKFFR[1421] = 0.0;
_CKFFR[1422] = 0.0;
_CKFFR[1423] = 0.0;
_CKFFR[1424] = 0.0;
_CKFFR[1425] = 0.0;
_CKFFR[1426] = 0.0;
_CKFFR[1427] = 0.0;
_CKFFR[1428] = 0.0;
_CKFFR[1429] = 0.0;
_CKFFR[1430] = 0.0;
_CKFFR[1431] = 0.0;
_CKFFR[1432] = 0.0;
_CKFFR[1433] = 0.0;
_CKFFR[1434] = 0.0;
_CKFFR[1435] = 0.0;
_CKFFR[1436] = 0.0;
_CKFFR[1437] = 0.0;
_CKFFR[1438] = 0.0;
_CKFFR[1439] = 0.0;
_CKFFR[1440] = 0.0;
_CKFFR[1441] = 0.0;
_CKFFR[1442] = 0.0;
_CKFFR[1443] = 0.0;
_CKFFR[1444] = 0.0;
_CKFFR[1445] = 0.0;
_CKFFR[1446] = 0.0;
_CKFFR[1447] = 0.0;
_CKFFR[1448] = 0.0;
_CKFFR[1449] = 0.0;
_CKFFR[1450] = 0.0;
_CKFFR[1451] = 0.0;
_CKFFR[1452] = 0.0;
_CKFFR[1453] = 0.0;
_CKFFR[1454] = 0.0;
_CKFFR[1455] = 0.0;
_CKFFR[1456] = 0.0;
_CKFFR[1457] = 0.0;
_CKFFR[1458] = 0.0;
_CKFFR[1459] = 0.0;
_CKFFR[1460] = 0.0;
_CKFFR[1461] = 0.0;
_CKFFR[1462] = 0.0;
_CKFFR[1463] = 0.0;
_CKFFR[1464] = 0.0;
_CKFFR[1465] = 0.0;
_CKFFR[1466] = 0.0;
_CKFFR[1467] = 0.0;
_CKFFR[1468] = 0.0;
_CKFFR[1469] = 0.0;
_CKFFR[1470] = 0.0;
_CKFFR[1471] = 0.0;
_CKFFR[1472] = 0.0;
_CKFFR[1473] = 0.0;
_CKFFR[1474] = 0.0;
_CKFFR[1475] = 0.0;
_CKFFR[1476] = 0.0;
_CKFFR[1477] = 0.0;
_CKFFR[1478] = 0.0;
_CKFFR[1479] = 0.0;
_CKFFR[1480] = 0.0;
_CKFFR[1481] = 0.0;
_CKFFR[1482] = 0.0;
_CKFFR[1483] = 0.0;
_CKFFR[1484] = 0.0;
_CKFFR[1485] = 0.0;
_CKFFR[1486] = 0.0;
_CKFFR[1487] = 0.0;
_CKFFR[1488] = 0.0;
_CKFFR[1489] = 0.0;
_CKFFR[1490] = 0.0;
_CKFFR[1491] = 0.0;
_CKFFR[1492] = 0.0;
_CKFFR[1493] = 0.0;
_CKFFR[1494] = 0.0;
_CKFFR[1495] = 0.0;
_CKFFR[1496] = 0.0;
_CKFFR[1497] = 0.0;
_CKFFR[1498] = 0.0;
_CKFFR[1499] = 0.0;
_CKFFR[1500] = 0.0;
_CKFFR[1501] = 0.0;
_CKFFR[1502] = 0.0;
_CKFFR[1503] = 0.0;
_CKFFR[1504] = 0.0;
_CKFFR[1505] = 0.0;
_CKFFR[1506] = 0.0;
_CKFFR[1507] = 0.0;
_CKFFR[1508] = 0.0;
_CKFFR[1509] = 0.0;
_CKFFR[1510] = 0.0;
_CKFFR[1511] = 0.0;
_CKFFR[1512] = 0.0;
_CKFFR[1513] = 0.0;
_CKFFR[1514] = 0.0;
_CKFFR[1515] = 0.0;
_CKFFR[1516] = 0.0;
_CKFFR[1517] = 0.0;
_CKFFR[1518] = 0.0;
_CKFFR[1519] = 0.0;
_CKFFR[1520] = 0.0;
_CKFFR[1521] = 0.0;
_CKFFR[1522] = 0.0;
_CKFFR[1523] = 0.0;
_CKFFR[1524] = 0.0;
_CKFFR[1525] = 0.0;
_CKFFR[1526] = 0.0;
_CKFFR[1527] = 0.0;
_CKFFR[1528] = 0.0;
_CKFFR[1529] = 0.0;
_CKFFR[1530] = 0.0;
_CKFFR[1531] = 0.0;
_CKFFR[1532] = 0.0;
_CKFFR[1533] = 0.0;
_CKFFR[1534] = 0.0;
_CKFFR[1535] = 0.0;
_CKFFR[1536] = 0.0;
_CKFFR[1537] = 0.0;
_CKFFR[1538] = 0.0;
_CKFFR[1539] = 0.0;
_CKFFR[1540] = 0.0;
_CKFFR[1541] = 0.0;
_CKFFR[1542] = 0.0;
_CKFFR[1543] = 0.0;
_CKFFR[1544] = 0.0;
_CKFFR[1545] = 0.0;
_CKFFR[1546] = 0.0;
_CKFFR[1547] = 0.0;
_CKFFR[1548] = 0.0;
_CKFFR[1549] = 0.0;
_CKFFR[1550] = 0.0;
_CKFFR[1551] = 0.0;
_CKFFR[1552] = 0.0;
_CKFFR[1553] = 0.0;
_CKFFR[1554] = 0.0;
_CKFFR[1555] = 0.0;
_CKFFR[1556] = 0.0;
_CKFFR[1557] = 0.0;
_CKFFR[1558] = 0.0;
_CKFFR[1559] = 0.0;
_CKFFR[1560] = 0.0;
_CKFFR[1561] = 0.0;
_CKFFR[1562] = 0.0;
_CKFFR[1563] = 0.0;
_CKFFR[1564] = 0.0;
_CKFFR[1565] = 0.0;
_CKFFR[1566] = 0.0;
_CKFFR[1567] = 0.0;
_CKFFR[1568] = 0.0;
_CKFFR[1569] = 0.0;
_CKFFR[1570] = 0.0;
_CKFFR[1571] = 0.0;
_CKFFR[1572] = 0.0;
_CKFFR[1573] = 0.0;
_CKFFR[1574] = 0.0;
_CKFFR[1575] = 0.0;
_CKFFR[1576] = 0.0;
_CKFFR[1577] = 0.0;
_CKFFR[1578] = 0.0;
_CKFFR[1579] = 0.0;
_CKFFR[1580] = 0.0;
_CKFFR[1581] = 0.0;
_CKFFR[1582] = 0.0;
_CKFFR[1583] = 0.0;
_CKFFR[1584] = 0.0;
_CKFFR[1585] = 0.0;
_CKFFR[1586] = 0.0;
_CKFFR[1587] = 0.0;
_CKFFR[1588] = 0.0;
_CKFFR[1589] = 0.0;
_CKFFR[1590] = 0.0;
_CKFFR[1591] = 0.0;
_CKFFR[1592] = 0.0;
_CKFFR[1593] = 0.0;
_CKFFR[1594] = 0.0;
_CKFFR[1595] = 0.0;
_CKFFR[1596] = 0.0;
_CKFFR[1597] = 0.0;
_CKFFR[1598] = 0.0;
_CKFFR[1599] = 0.0;
_CKFFR[1600] = 0.0;
_CKFFR[1601] = 0.0;
_CKFFR[1602] = 0.0;
_CKFFR[1603] = 0.0;
_CKFFR[1604] = 0.0;
_CKFFR[1605] = 0.0;
_CKFFR[1606] = 0.0;
_CKFFR[1607] = 0.0;
_CKFFR[1608] = 0.0;
_CKFFR[1609] = 0.0;
_CKFFR[1610] = 0.0;
_CKFFR[1611] = 0.0;
_CKFFR[1612] = 0.0;
_CKFFR[1613] = 0.0;
_CKFFR[1614] = 0.0;
_CKFFR[1615] = 0.0;
_CKFFR[1616] = 0.0;
_CKFFR[1617] = 0.0;
_CKFFR[1618] = 0.0;
_CKFFR[1619] = 0.0;
_CKFFR[1620] = 0.0;
_CKFFR[1621] = 0.0;
_CKFFR[1622] = 0.0;
_CKFFR[1623] = 0.0;
_CKFFR[1624] = 0.0;
_CKFFR[1625] = 0.0;
_CKFFR[1626] = 0.0;
_CKFFR[1627] = 0.0;
_CKFFR[1628] = 0.0;
_CKFFR[1629] = 0.0;
_CKFFR[1630] = 0.0;
_CKFFR[1631] = 0.0;
_CKFFR[1632] = 0.0;
_CKFFR[1633] = 0.0;
_CKFFR[1634] = 0.0;
_CKFFR[1635] = 0.0;
_CKFFR[1636] = 0.0;
_CKFFR[1637] = 0.0;
_CKFFR[1638] = 0.0;
_CKFFR[1639] = 0.0;
_CKFFR[1640] = 0.0;
_CKFFR[1641] = 0.0;
_CKFFR[1642] = 0.0;
_CKFFR[1643] = 0.0;
_CKFFR[1644] = 0.0;
_CKFFR[1645] = 0.0;
_CKFFR[1646] = 0.0;
_CKFFR[1647] = 0.0;
_CKFFR[1648] = 0.0;
_CKFFR[1649] = 0.0;
_CKFFR[1650] = 0.0;
_CKFFR[1651] = 0.0;
_CKFFR[1652] = 0.0;
_CKFFR[1653] = 0.0;
_CKFFR[1654] = 0.0;
_CKFFR[1655] = 0.0;
_CKFFR[1656] = 0.0;
_CKFFR[1657] = 0.0;
_CKFFR[1658] = 0.0;
_CKFFR[1659] = 0.0;
_CKFFR[1660] = 0.0;
_CKFFR[1661] = 0.0;
_CKFFR[1662] = 0.0;
_CKFFR[1663] = 0.0;
_CKFFR[1664] = 0.0;
_CKFFR[1665] = 0.0;
_CKFFR[1666] = 0.0;
_CKFFR[1667] = 0.0;
_CKFFR[1668] = 0.0;
_CKFFR[1669] = 0.0;
_CKFFR[1670] = 0.0;
_CKFFR[1671] = 0.0;
_CKFFR[1672] = 0.0;
_CKFFR[1673] = 0.0;
_CKFFR[1674] = 0.0;
_CKFFR[1675] = 0.0;
_CKFFR[1676] = 0.0;
_CKFFR[1677] = 0.0;
_CKFFR[1678] = 0.0;
_CKFFR[1679] = 0.0;
_CKFFR[1680] = 0.0;
_CKFFR[1681] = 0.0;
_CKFFR[1682] = 0.0;
_CKFFR[1683] = 0.0;
_CKFFR[1684] = 0.0;
_CKFFR[1685] = 0.0;
_CKFFR[1686] = 0.0;
_CKFFR[1687] = 0.0;
_CKFFR[1688] = 0.0;
_CKFFR[1689] = 0.0;
_CKFFR[1690] = 0.0;
_CKFFR[1691] = 0.0;
_CKFFR[1692] = 0.0;
_CKFFR[1693] = 0.0;
_CKFFR[1694] = 0.0;
_CKFFR[1695] = 0.0;
_CKFFR[1696] = 0.0;
_CKFFR[1697] = 0.0;
_CKFFR[1698] = 0.0;
_CKFFR[1699] = 0.0;
_CKFFR[1700] = 0.0;
_CKFFR[1701] = 0.0;
_CKFFR[1702] = 0.0;
_CKFFR[1703] = 0.0;
_CKFFR[1704] = 0.0;
_CKFFR[1705] = 0.0;
_CKFFR[1706] = 0.0;
_CKFFR[1707] = 0.0;
_CKFFR[1708] = 0.0;
_CKFFR[1709] = 0.0;
_CKFFR[1710] = 0.0;
_CKFFR[1711] = 0.0;
_CKFFR[1712] = 0.0;
_CKFFR[1713] = 0.0;
_CKFFR[1714] = 0.0;
_CKFFR[1715] = 0.0;
_CKFFR[1716] = 0.0;
_CKFFR[1717] = 0.0;
_CKFFR[1718] = 0.0;
_CKFFR[1719] = 0.0;
_CKFFR[1720] = 0.0;
_CKFFR[1721] = 0.0;
_CKFFR[1722] = 0.0;
_CKFFR[1723] = 0.0;
_CKFFR[1724] = 0.0;
_CKFFR[1725] = 0.0;
_CKFFR[1726] = 0.0;
_CKFFR[1727] = 0.0;
_CKFFR[1728] = 0.0;
_CKFFR[1729] = 0.0;
_CKFFR[1730] = 0.0;
_CKFFR[1731] = 0.0;
_CKFFR[1732] = 0.0;
_CKFFR[1733] = 0.0;
_CKFFR[1734] = 0.0;
_CKFFR[1735] = 0.0;
_CKFFR[1736] = 0.0;
_CKFFR[1737] = 0.0;
_CKFFR[1738] = 0.0;
_CKFFR[1739] = 0.0;
_CKFFR[1740] = 0.0;
_CKFFR[1741] = 0.0;
_CKFFR[1742] = 0.0;
_CKFFR[1743] = 0.0;
_CKFFR[1744] = 0.0;
_CKFFR[1745] = 0.0;
_CKFFR[1746] = 0.0;
_CKFFR[1747] = 0.0;
_CKFFR[1748] = 0.0;
_CKFFR[1749] = 0.0;
_CKFFR[1750] = 0.0;
_CKFFR[1751] = 0.0;
_CKFFR[1752] = 0.0;
_CKFFR[1753] = 0.0;
_CKFFR[1754] = 0.0;
_CKFFR[1755] = 0.0;
_CKFFR[1756] = 0.0;
_CKFFR[1757] = 0.0;
_CKFFR[1758] = 0.0;
_CKFFR[1759] = 0.0;
_CKFFR[1760] = 0.0;
_CKFFR[1761] = 0.0;
_CKFFR[1762] = 0.0;
_CKFFR[1763] = 0.0;
_CKFFR[1764] = 0.0;
_CKFFR[1765] = 0.0;
_CKFFR[1766] = 0.0;
_CKFFR[1767] = 0.0;
_CKFFR[1768] = 0.0;
_CKFFR[1769] = 0.0;
_CKFFR[1770] = 0.0;
_CKFFR[1771] = 0.0;
_CKFFR[1772] = 0.0;
_CKFFR[1773] = 0.0;
_CKFFR[1774] = 0.0;
_CKFFR[1775] = 0.0;
_CKFFR[1776] = 0.0;
_CKFFR[1777] = 0.0;
_CKFFR[1778] = 0.0;
_CKFFR[1779] = 0.0;
_CKFFR[1780] = 0.0;
_CKFFR[1781] = 0.0;
_CKFFR[1782] = 0.0;
_CKFFR[1783] = 0.0;
_CKFFR[1784] = 0.0;
_CKFFR[1785] = 0.0;
_CKFFR[1786] = 0.0;
_CKFFR[1787] = 0.0;
_CKFFR[1788] = 0.0;
_CKFFR[1789] = 0.0;
_CKFFR[1790] = 0.0;
_CKFFR[1791] = 0.0;
_CKFFR[1792] = 0.0;
_CKFFR[1793] = 0.0;
_CKFFR[1794] = 0.0;
_CKFFR[1795] = 0.0;
_CKFFR[1796] = 0.0;
_CKFFR[1797] = 0.0;
_CKFFR[1798] = 0.0;
_CKFFR[1799] = 0.0;
_CKFFR[1800] = 0.0;
_CKFFR[1801] = 0.0;
_CKFFR[1802] = 0.0;
_CKFFR[1803] = 0.0;
_CKFFR[1804] = 0.0;
_CKFFR[1805] = 0.0;
_CKFFR[1806] = 0.0;
_CKFFR[1807] = 0.0;
_CKFFR[1808] = 0.0;
_CKFFR[1809] = 0.0;
_CKFFR[1810] = 0.0;
_CKFFR[1811] = 0.0;
_CKFFR[1812] = 0.0;
_CKFFR[1813] = 0.0;
_CKFFR[1814] = 0.0;
_CKFFR[1815] = 0.0;
_CKFFR[1816] = 0.0;
_CKFFR[1817] = 0.0;
_CKFFR[1818] = 0.0;
_CKFFR[1819] = 0.0;
_CKFFR[1820] = 0.0;
_CKFFR[1821] = 0.0;
_CKFFR[1822] = 0.0;
_CKFFR[1823] = 0.0;
_CKFFR[1824] = 0.0;
_CKFFR[1825] = 0.0;
_CKFFR[1826] = 0.0;
_CKFFR[1827] = 0.0;
_CKFFR[1828] = 0.0;
_CKFFR[1829] = 0.0;
_CKFFR[1830] = 0.0;
_CKFFR[1831] = 0.0;
_CKFFR[1832] = 0.0;
_CKFFR[1833] = 0.0;
_CKFFR[1834] = 0.0;
_CKFFR[1835] = 0.0;
_CKFFR[1836] = 0.0;
_CKFFR[1837] = 0.0;
_CKFFR[1838] = 0.0;
_CKFFR[1839] = 0.0;
_CKFFR[1840] = 0.0;
_CKFFR[1841] = 0.0;
_CKFFR[1842] = 0.0;
_CKFFR[1843] = 0.0;
_CKFFR[1844] = 0.0;
_CKFFR[1845] = 0.0;
_CKFFR[1846] = 0.0;
_CKFFR[1847] = 0.0;
_CKFFR[1848] = 0.0;
_CKFFR[1849] = 0.0;
_CKFFR[1850] = 0.0;
_CKFFR[1851] = 0.0;
_CKFFR[1852] = 0.0;
_CKFFR[1853] = 0.0;
_CKFFR[1854] = 0.0;
_CKFFR[1855] = 0.0;
_CKFFR[1856] = 0.0;
_CKFFR[1857] = 0.0;
_CKFFR[1858] = 0.0;
_CKFFR[1859] = 0.0;
_CKFFR[1860] = 0.0;
_CKFFR[1861] = 0.0;
_CKFFR[1862] = 0.0;
_CKFFR[1863] = 0.0;
_CKFFR[1864] = 0.0;
_CKFFR[1865] = 0.0;
_CKFFR[1866] = 0.0;
_CKFFR[1867] = 0.0;
_CKFFR[1868] = 0.0;
_CKFFR[1869] = 0.0;
_CKFFR[1870] = 0.0;
_CKFFR[1871] = 0.0;
_CKFFR[1872] = 0.0;
_CKFFR[1873] = 0.0;
_CKFFR[1874] = 0.0;
_CKFFR[1875] = 0.0;
_CKFFR[1876] = 0.0;
_CKFFR[1877] = 0.0;
_CKFFR[1878] = 0.0;
_CKFFR[1879] = 0.0;
_CKFFR[1880] = 0.0;
_CKFFR[1881] = 0.0;
_CKFFR[1882] = 0.0;
_CKFFR[1883] = 0.0;
_CKFFR[1884] = 0.0;
_CKFFR[1885] = 0.0;
_CKFFR[1886] = 0.0;
_CKFFR[1887] = 0.0;
_CKFFR[1888] = 0.0;
_CKFFR[1889] = 0.0;
_CKFFR[1890] = 0.0;
_CKFFR[1891] = 0.0;
_CKFFR[1892] = 0.0;
_CKFFR[1893] = 0.0;
_CKFFR[1894] = 0.0;
_CKFFR[1895] = 0.0;
_CKFFR[1896] = 0.0;
_CKFFR[1897] = 0.0;
_CKFFR[1898] = 0.0;
_CKFFR[1899] = 0.0;
_CKFFR[1900] = 0.0;
_CKFFR[1901] = 0.0;
_CKFFR[1902] = 0.0;
_CKFFR[1903] = 0.0;
_CKFFR[1904] = 0.0;
_CKFFR[1905] = 0.0;
_CKFFR[1906] = 0.0;
_CKFFR[1907] = 0.0;
_CKFFR[1908] = 0.0;
_CKFFR[1909] = 0.0;
_CKFFR[1910] = 0.0;
_CKFFR[1911] = 0.0;
_CKFFR[1912] = 0.0;
_CKFFR[1913] = 0.0;
_CKFFR[1914] = 0.0;
_CKFFR[1915] = 0.0;
_CKFFR[1916] = 0.0;
_CKFFR[1917] = 0.0;
_CKFFR[1918] = 0.0;
_CKFFR[1919] = 0.0;
_CKFFR[1920] = 0.0;
_CKFFR[1921] = 0.0;
_CKFFR[1922] = 0.0;
_CKFFR[1923] = 0.0;
_CKFFR[1924] = 0.0;
_CKFFR[1925] = 0.0;
_CKFFR[1926] = 0.0;
_CKFFR[1927] = 0.0;
_CKFFR[1928] = 0.0;
_CKFFR[1929] = 0.0;
_CKFFR[1930] = 0.0;
_CKFFR[1931] = 0.0;
_CKFFR[1932] = 0.0;
_CKFFR[1933] = 0.0;
_CKFFR[1934] = 0.0;
_CKFFR[1935] = 0.0;

return _CKFFR;
}
