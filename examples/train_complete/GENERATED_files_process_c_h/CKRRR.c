/*----------CKRRR.c lib3D_MEC exported-----------*/

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

#include "CKRRR.h"

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
double atom2385;
double atom2383;
double atom2421;
double atom2429;
double atom2430;
double atom62787;
double atom2431;
double atom865;
double atom862;
double atom864;
double atom869;
double atom1725;
double atom21988;
double atom1172;
double atom1174;
double atom21989;
double atom1195;
double atom863;
double atom21986;
double atom1209;
double atom867;
double atom1717;
double atom21985;
double atom1210;
double atom1175;
double atom21995;
double atom1173;
double atom0;
double atom21992;
double atom1194;
double atom21996;
double atom22011;
double atom50;
double atom1702;
double atom2225;
double atom49;
double atom868;
double atom2223;
double atom2237;
double atom2229;
double atom2232;
double atom2243;
double atom2244;
double atom2212;
double atom2218;
double atom1225;
double atom1246;
double atom1227;
double atom1228;
double atom1264;
double atom1261;
double atom2222;
double atom1325;
double atom1243;
double atom2220;
double atom1322;
double atom22017;
double atom1176;
double atom52551;
double atom62625;
double atom1177;
double atom52415;
double atom62627;
double atom1181;
double atom1191;
double atom1193;
double atom1180;
double atom1190;
double atom22006;
double atom1222;
double atom1219;
double atom1240;
double atom1255;
double atom1258;
double atom1316;
double atom1237;
double atom1319;
double atom22016;
double atom52439;
double atom1179;
double atom1184;
double atom1178;
double atom1185;
double atom1187;
double atom1213;
double atom1234;
double atom1216;
double atom1252;
double atom1249;
double atom1310;
double atom1231;
double atom1313;
double atom22001;
double atom22015;
double atom52560;
double atom62636;
double atom62638;
double atom62641;
double atom62643;
double atom3814;
double atom60833;
double atom26169;
double atom62652;
double atom60839;
double atom26287;
double atom62654;
double atom8275;
double atom52503;
double atom52501;
double atom52509;
double atom52505;
double atom52512;
double atom22967;
double atom24052;
double atom60847;
double atom60849;
double atom22964;
double atom60856;
double atom60853;
double atom60858;
double atom52581;
double atom62662;
double atom62663;
double atom60865;
double atom52514;
double atom62657;
double atom62665;
double atom22861;
double atom22863;
double atom60874;
double atom60877;
double atom22942;
double atom26224;
double atom26233;
double atom26250;
double atom62674;
double atom60884;
double atom26315;
double atom62676;
double atom4138;
double atom4139;
double atom4143;
double atom4152;
double atom8284;
double atom62679;
double atom25584;
double atom25596;
double atom62682;
double atom62691;
double atom62685;
double atom62680;
double atom62687;
double atom62693;
double atom62697;
double atom62699;
double atom62703;
double atom62709;
double atom62712;
double atom62714;
double atom62788;
double atom2317;
double atom2318;
double atom2319;
double atom2388;
double atom2434;
double atom62789;
double atom2435;
double atom52596;
double atom62721;
double atom62791;
double atom2389;
double atom2390;
double atom2423;
double atom2424;
double atom2425;
double atom62792;
double atom62762;
double atom52605;
double atom62728;
double atom2426;
double atom62767;
double atom62729;
double atom62771;
double atom26165;
double atom62736;
double atom8324;
double atom62739;
double atom52627;
double atom62743;
double atom62776;
double atom62900;
double atom62781;
double atom26244;
double atom62750;
double atom8333;
double atom62753;
double atom62786;
double atom62759;
double atom62793;
double atom62794;
double atom62935;
double atom22860;
double atom22966;
double atom22970;
double atom23996;
double atom23999;
double atom25575;
double atom25587;
double atom59445;
double atom59458;
double atom59461;
double atom59450;
double atom62795;
double atom62545;
double atom62550;
double atom21939;
double atom62558;
double atom62560;
double atom62798;
double atom62800;
double atom62801;
double atom62803;
double atom62977;
double atom22971;
double atom24003;
double atom24001;
double atom25590;
double atom25578;
double atom59492;
double atom59479;
double atom59495;
double atom59484;
double atom62804;
double atom62566;
double atom62571;
double atom62807;
double atom62810;
double atom63027;
double atom59512;
double atom59516;
double atom59523;
double atom59526;
double atom62811;
double atom62577;
double atom62582;
double atom62814;
double atom62817;
double atom63077;
double atom25581;
double atom25593;
double atom59542;
double atom59546;
double atom59553;
double atom59556;
double atom62818;
double atom62588;
double atom62593;
double atom62821;
double atom62824;
double atom63127;
double atom62825;
double atom62826;
double atom62827;
double atom63177;
double atom59573;
double atom59577;
double atom59578;
double atom62828;
double atom59581;
double atom62599;
double atom62830;
double atom62831;
double atom62833;
double atom62834;
double atom63227;
double atom59597;
double atom59593;
double atom59604;
double atom59607;
double atom62835;
double atom62608;
double atom62605;
double atom62838;
double atom62841;
double atom63277;
double atom62842;
double atom62843;
double atom62844;
double atom63327;
double atom62845;
double atom62614;
double atom62847;
double atom62849;
double atom63377;
double atom59632;
double atom62850;
double atom62620;
double atom62853;
double atom62856;
double atom63427;

double * _CKRRR = NULL;
void Init_CKRRR ( ) 
{
    _CKRRR = malloc ( CKRRR_n_rows * CKRRR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKRRR_n_rows * CKRRR_n_cols ; i++ ) {_CKRRR[i]=0.0;}
  }
}

void Done_CKRRR ( ) 
{
if (_CKRRR != NULL) 
free (_CKRRR ); 
_CKRRR = NULL; 
}


double * CKRRR ()
{
if ( _CKRRR == NULL )
 {
    _CKRRR = malloc ( CKRRR_n_rows * CKRRR_n_cols * sizeof(double) );
  {int i;
  for ( i = 0 ; i < CKRRR_n_rows * CKRRR_n_cols ; i++ ) {_CKRRR[i]=0.0;}
  }
 }

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
atom2385 =  -5.0000000000000000e-01*L_RAIL*atom2379+atom2350;
atom2383 =  5.0000000000000000e-01*L_RAIL*atom2374/atom2353+5.0000000000000000e-01*atom2350*L_RAIL*atom2379+1.0;
atom2421 = (atom2383*atom2383);
atom2429 = pow( (atom2385*atom2385)+atom2421,-(1.0/2.0));
atom2430 = atom2429*atom2383;
atom62787 = -C11RRR*epsiRRR*G_elastic*aRRR*bRRR*atom2430;
atom2431 = atom2385*atom2429;
atom865 = sin(bRBOG);
atom862 = cos(aRBOG);
atom864 = cos(bRBOG);
atom869 = atom862*atom864;
atom1725 = -L_OBOG_OWHS*atom865;
atom21988 =  zRWHSR*atom869-atom1725;
atom1172 = cos(bWAG);
atom1174 = cos(aWAG);
atom21989 =  atom21988+zRBOG;
atom1195 = atom1172*atom1174;
atom863 = sin(aRBOG);
atom21986 = -atom863*zRWHSR;
atom1209 = cos(cRSLD);
atom867 = atom862*atom865;
atom1717 = L_OBOG_OWHS*atom864;
atom21985 = -atom1717+atom867*zRWHSR;
atom1210 = sin(cRSLD);
atom1175 = sin(aWAG);
atom21995 =  atom21986*atom1209+atom21985*atom1210;
atom1173 = sin(bWAG);
atom0 = -(1.0/2.0)*L_WAG;
atom21992 = -atom21986*atom1210+atom1209*atom21985;
atom1194 = -atom1173*atom1174;
atom21996 =  atom0+atom21992;
atom22011 =  atom1175*atom21995+atom1194*atom21996+atom21989*atom1195;
atom50 = sin(aRWHSR);
atom1702 = -5.0000000000000000e-01*L_WHS;
atom2225 =  atom50*atom1702+zRWHSR;
atom49 = cos(aRWHSR);
atom868 = atom863*atom864;
atom2223 = atom49*atom1702;
atom2237 =  zRBOG+atom868*atom2223-atom1725+atom2225*atom869;
atom2229 = -atom1717+atom867*atom2225+atom863*atom2223*atom865;
atom2232 =  atom862*atom2223-atom863*atom2225;
atom2243 =  atom2229*atom1210+atom1209*atom2232;
atom2244 =  atom0+atom1209*atom2229-atom2232*atom1210;
atom2212 =  uW_RRR-lW_RRR;
atom2218 =  atom2212*( cW_RRR+atom2212*( bW_RRR+atom2212*aW_RRR))+dW_RRR;
atom1225 =  atom1194*atom1209+atom1175*atom1210;
atom1246 =  atom1195*atom864+atom1225*atom865;
atom1227 = atom1175*atom1209;
atom1228 =  atom1227-atom1194*atom1210;
atom1264 =  atom862*atom1246-atom863*atom1228;
atom1261 =  atom862*atom1228+atom863*atom1246;
atom2222 = atom2218*cos(thetaW_RRR);
atom1325 =  atom49*atom1264-atom50*atom1261;
atom1243 =  atom1225*atom864-atom1195*atom865;
atom2220 = -sin(thetaW_RRR)*atom2218;
atom1322 =  atom49*atom1261+atom50*atom1264;
atom22017 =  atom2222*atom1325+uW_RRR*atom1322+atom1243*atom2220+atom1195*atom2237+atom1194*atom2244+atom1175*atom2243-atom22011;
atom1176 = cos(cWAG);
atom52551 = -atom1176*atom22011;
atom62625 = -atom22017*atom1176+atom52551;
atom1177 = sin(cWAG);
atom52415 = atom1177*atom22011;
atom62627 =  ( atom22017*atom1177+atom52415)*atom2430+atom62625*atom2431;
atom1181 = -atom1175*atom1176;
atom1191 = atom1177*atom1173;
atom1193 =  atom1191+atom1172*atom1181;
atom1180 = atom1176*atom1174;
atom1190 = -atom1181*atom1173+atom1172*atom1177;
atom22006 =  atom1193*atom21989+atom1180*atom21995+atom1190*atom21996;
atom1222 =  atom1180*atom1209-atom1190*atom1210;
atom1219 =  atom1180*atom1210+atom1190*atom1209;
atom1240 =  atom1219*atom865+atom1193*atom864;
atom1255 =  atom862*atom1222+atom863*atom1240;
atom1258 = -atom863*atom1222+atom862*atom1240;
atom1316 =  atom1255*atom49+atom1258*atom50;
atom1237 =  atom864*atom1219-atom1193*atom865;
atom1319 = -atom1255*atom50+atom1258*atom49;
atom22016 = -atom22006+atom1180*atom2243+atom1316*uW_RRR+atom1190*atom2244+atom1319*atom2222+atom1193*atom2237+atom2220*atom1237;
atom52439 =  atom1180*atom22011-atom22006*atom1175;
atom1179 = atom1175*atom1177;
atom1184 =  atom1172*atom1176-atom1173*atom1179;
atom1178 = -atom1177*atom1174;
atom1185 = atom1176*atom1173;
atom1187 =  atom1172*atom1179+atom1185;
atom1213 =  atom1209*atom1184+atom1178*atom1210;
atom1234 =  atom1213*atom865+atom864*atom1187;
atom1216 = -atom1184*atom1210+atom1209*atom1178;
atom1252 =  atom862*atom1234-atom863*atom1216;
atom1249 =  atom863*atom1234+atom862*atom1216;
atom1310 =  atom49*atom1249+atom50*atom1252;
atom1231 =  atom1213*atom864-atom1187*atom865;
atom1313 = -atom50*atom1249+atom49*atom1252;
atom22001 =  atom21996*atom1184+atom21989*atom1187+atom21995*atom1178;
atom22015 = -atom22001+uW_RRR*atom1310+atom2244*atom1184+atom2222*atom1313+atom2243*atom1178+atom1231*atom2220+atom2237*atom1187;
atom52560 =  atom1175*atom22001-atom1178*atom22011;
atom62636 =  atom1175*atom22015+atom52560-atom22017*atom1178;
atom62638 =  atom62636*atom2431+( atom52439-atom22016*atom1175+atom1180*atom22017)*atom2430;
atom62641 =  atom22001+atom22015;
atom62643 = -( atom22006+atom22016)*atom2430+atom62641*atom2431;
atom3814 = -atom1175*atom1172;
atom60833 = -atom3814*atom1177+atom1185;
atom26169 =  atom1180*atom21992-atom21995*atom1190;
atom62652 =  atom26169+atom1195*atom22015-atom22017*atom60833;
atom60839 =  atom1191+atom1176*atom3814;
atom26287 = -atom21995*atom1184+atom21992*atom1178;
atom62654 = -( atom22016*atom1195-atom22017*atom60839-atom26287)*atom2430+atom2431*atom62652;
atom8275 =  atom1193*atom2431+atom1187*atom2430;
atom52503 = -atom21986*atom865;
atom52501 = -atom865*atom21985-atom21988*atom864;
atom52509 =  atom1209*atom52501-atom52503*atom1210;
atom52505 = -atom52501*atom1210-atom1209*atom52503;
atom52512 = atom21986*atom864;
atom22967 = atom864*atom1210;
atom24052 = atom864*atom1209;
atom60847 = -atom1172*atom865-atom1173*atom24052;
atom60849 =  atom60847*atom1174+atom1175*atom22967;
atom22964 = -atom1173*atom865;
atom60856 =  atom1172*atom24052+atom22964;
atom60853 = -atom1175*atom60847+atom22967*atom1174;
atom60858 =  atom1176*atom60856-atom60853*atom1177;
atom52581 =  atom1193*atom52512+atom1180*atom52509+atom52505*atom1190;
atom62662 =  atom60849*atom22015-atom22017*atom60858;
atom62663 =  atom52581+atom62662;
atom60865 =  atom1176*atom60853+atom60856*atom1177;
atom52514 =  atom52509*atom1178+atom52505*atom1184+atom1187*atom52512;
atom62657 =  atom22017*atom60865-atom22016*atom60849;
atom62665 =  atom2431*atom62663+( atom52514+atom62657)*atom2430;
atom22861 = -atom1172*atom1210;
atom22863 = atom1173*atom1210;
atom60874 =  atom1209*atom1174-atom1175*atom22863;
atom60877 =  atom22861*atom1176-atom60874*atom1177;
atom22942 =  atom22863*atom1174+atom1227;
atom26224 = atom21988*atom1210;
atom26233 = atom21988*atom1209;
atom26250 = -atom1193*atom21985+atom1180*atom26224+atom1190*atom26233;
atom62674 =  atom22942*atom22015-atom22017*atom60877+atom26250;
atom60884 =  atom22861*atom1177+atom60874*atom1176;
atom26315 =  atom26233*atom1184-atom1187*atom21985+atom1178*atom26224;
atom62676 =  ( atom60884*atom22017+atom26315-atom22942*atom22016)*atom2430+atom2431*atom62674;
atom4138 = -atom863*atom1209;
atom4139 =  atom4138+atom867*atom1210;
atom4143 =  atom867*atom1209+atom863*atom1210;
atom4152 =  atom1193*atom869+atom1180*atom4139+atom4143*atom1190;
atom8284 =  ( atom4143*atom1184+atom4139*atom1178+atom1187*atom869)*atom2430+atom4152*atom2431;
atom62679 =  atom62662*atom2431+atom62657*atom2430;
atom25584 = -atom863*atom50+atom862*atom49;
atom25596 = -atom49*atom863-atom862*atom50;
atom62682 = -atom25596*atom865;
atom62691 =  atom62682*atom1210+atom1209*atom25584;
atom62685 =  atom62682*atom1209-atom25584*atom1210;
atom62680 = -atom25596*atom864;
atom62687 =  atom1172*atom62680-atom1173*atom62685;
atom62693 = -atom1175*atom62687+atom62691*atom1174;
atom62697 =  atom1172*atom62685+atom62680*atom1173;
atom62699 =  atom1176*atom62693+atom1177*atom62697;
atom62703 =  atom1175*atom62691+atom62687*atom1174;
atom62709 = -atom1177*atom62693+atom1176*atom62697;
atom62712 = -atom22017*atom62709+atom22015*atom62703;
atom62714 =  atom62712*atom2431-( atom22016*atom62703-atom22017*atom62699)*atom2430;
atom62788 = -C11RRR*epsiRRR*G_elastic*aRRR*atom2431*bRRR;
atom2317 =  uR_RRR-lR_RRR;
atom2318 = atom2317*aR_RRR;
atom2319 =  atom2318+bR_RRR;
atom2388 =  cR_RRR+atom2317*( atom2318+atom2319)+atom2317*atom2319;
atom2434 = pow( (atom2388*atom2388)+1.0,-(1.0/2.0));
atom62789 = -epsiRRR*C22RRR*atom2434*G_elastic*aRRR*bRRR;
atom2435 = atom2434*atom2388;
atom52596 =  atom22006*atom1176-atom22001*atom1177;
atom62721 =  ( atom22016*atom1176+atom52596-atom1177*atom22015)*atom2435+atom62625*atom2434;
atom62791 = pow(aRRR*bRRR,(1.0/2.0));
atom2389 = atom2385*atom2388;
atom2390 = -atom2383*atom2388;
atom2423 = pow( (atom2390*atom2390)+(atom2389*atom2389)+atom2421,-(1.0/2.0));
atom2424 = atom2423*atom2389;
atom2425 = atom2423*atom2390;
atom62792 = -epsiRRR*atom2434*G_elastic*aRRR*C23RRR*bRRR*atom62791;
atom62762 =  atom2425*atom1177+atom1176*atom2424;
atom52605 =  atom22006*atom1178-atom1180*atom22001;
atom62728 =  atom62636*atom2434+( atom22016*atom1178-atom1180*atom22015+atom52605)*atom2435;
atom2426 = atom2423*atom2383;
atom62767 =  atom1180*atom2425+atom1175*atom2426+atom2424*atom1178;
atom62729 = atom62641*atom2434;
atom62771 =  atom2425*atom60839+atom2424*atom60833+atom1195*atom2426;
atom26165 = -atom21995*atom1194+atom1175*atom21992;
atom62736 =  atom2434*atom62652+( atom22016*atom60833-atom60839*atom22015+atom26165)*atom2435;
atom8324 =  atom1193*atom2434+atom1195*atom2435;
atom62739 = -atom60865*atom22015+atom22016*atom60858;
atom52627 =  atom1195*atom52512+atom52505*atom1194+atom1175*atom52509;
atom62743 =  atom2434*atom62663+( atom62739+atom52627)*atom2435;
atom62776 =  atom2425*atom60865+atom2426*atom60849+atom60858*atom2424;
atom62900 = atom62776*atom62792;
atom62781 =  atom22942*atom2426+atom60877*atom2424+atom60884*atom2425;
atom26244 =  atom1194*atom26233+atom1175*atom26224-atom1195*atom21985;
atom62750 =  ( atom22016*atom60877+atom26244-atom60884*atom22015)*atom2435+atom2434*atom62674;
atom8333 =  ( atom4139*atom1175+atom1195*atom869+atom4143*atom1194)*atom2435+atom4152*atom2434;
atom62753 =  atom2434*atom62662+atom62739*atom2435;
atom62786 =  atom62709*atom2424+atom2426*atom62703+atom2425*atom62699;
atom62759 =  atom62712*atom2434+( atom22016*atom62709-atom62699*atom22015)*atom2435;
atom62793 = -epsiRRR*C22RRR*G_elastic*aRRR*bRRR*atom2435;
atom62794 = -epsiRRR*G_elastic*aRRR*C23RRR*bRRR*atom2435*atom62791;
atom62935 = atom62776*atom62794;
atom22860 = atom1172*atom1209;
atom22966 =  atom864*atom22860+atom22964;
atom22970 =  atom864*atom1173+atom22860*atom865;
atom23996 =  atom862*atom22861+atom22970*atom863;
atom23999 =  atom862*atom22970-atom22861*atom863;
atom25575 =  atom23999*atom50+atom23996*atom49;
atom25587 = -atom23996*atom50+atom23999*atom49;
atom59445 =  atom22966*atom1243+atom1325*atom25587+atom25575*atom1322;
atom59458 =  atom25587*atom1313+atom1231*atom22966+atom25575*atom1310;
atom59461 = -atom22017*atom59458+atom59445*atom22015+atom52551;
atom59450 =  atom1319*atom25587+atom22966*atom1237+atom1316*atom25575;
atom62795 = -C11RRR*epsiRRR*G_elastic*aRRR*bRRR*( ( atom22017*atom59450+atom52415-atom22016*atom59445)*atom2430+atom59461*atom2431);
atom62545 =  atom2434*atom59461+( atom22016*atom59458+atom52596-atom59450*atom22015)*atom2435;
atom62550 =  atom1243*atom2426+atom1231*atom2424+atom2425*atom1237;
atom21939 =  atom2426*atom1322+atom1316*atom2425+atom2424*atom1310;
atom62558 =  atom2426*atom1325+atom1319*atom2425+atom2424*atom1313;
atom62560 =  atom62558*atom25587+atom21939*atom25575+atom22966*atom62550;
atom62798 =  epsiRRR*atom62560*G_elastic*aRRR*C23RRR*bRRR*atom62791-epsiRRR*atom62545*C22RRR*G_elastic*aRRR*bRRR;
atom62800 = (aRRR*aRRR);
atom62801 = (bRRR*bRRR);
atom62803 = -epsiRRR*atom62560*G_elastic*atom62800*C33RRR*atom62801-epsiRRR*atom62545*G_elastic*aRRR*C23RRR*bRRR*atom62791;
atom62977 = atom62776*atom62803;
atom22971 = atom865*atom1210;
atom24003 =  atom4138+atom862*atom22971;
atom24001 =  atom862*atom1209+atom863*atom22971;
atom25590 = -atom24001*atom50+atom24003*atom49;
atom25578 =  atom49*atom24001+atom24003*atom50;
atom59492 =  atom25590*atom1313+atom25578*atom1310+atom1231*atom22967;
atom59479 =  atom1243*atom22967+atom25578*atom1322+atom25590*atom1325;
atom59495 =  atom59479*atom22015+atom52560-atom22017*atom59492;
atom59484 =  atom22967*atom1237+atom1319*atom25590+atom1316*atom25578;
atom62804 = -C11RRR*epsiRRR*( atom2431*atom59495+( atom52439+atom59484*atom22017-atom22016*atom59479)*atom2430)*G_elastic*aRRR*bRRR;
atom62566 =  atom2434*atom59495-( atom59484*atom22015-atom52605-atom22016*atom59492)*atom2435;
atom62571 =  atom62550*atom22967+atom62558*atom25590+atom25578*atom21939;
atom62807 =  epsiRRR*atom62571*G_elastic*aRRR*C23RRR*bRRR*atom62791-epsiRRR*C22RRR*G_elastic*aRRR*atom62566*bRRR;
atom62810 = -epsiRRR*atom62571*G_elastic*atom62800*C33RRR*atom62801-epsiRRR*G_elastic*aRRR*atom62566*C23RRR*bRRR*atom62791;
atom63027 = atom62776*atom62810;
atom59512 =  (atom1243*atom1243)+(atom1325*atom1325)+(atom1322*atom1322);
atom59516 =  atom1319*atom1325+atom1316*atom1322+atom1243*atom1237;
atom59523 =  atom1325*atom1313+atom1231*atom1243+atom1322*atom1310;
atom59526 =  atom22001-atom22017*atom59523+atom22015*atom59512;
atom62811 = C11RRR*epsiRRR*G_elastic*aRRR*( ( atom22006+atom22016*atom59512-atom59516*atom22017)*atom2430-atom2431*atom59526)*bRRR;
atom62577 =  atom2434*atom59526+( atom22016*atom59523-atom59516*atom22015)*atom2435;
atom62582 =  atom21939*atom1322+atom62558*atom1325+atom1243*atom62550;
atom62814 = -epsiRRR*C22RRR*G_elastic*aRRR*atom62577*bRRR+epsiRRR*atom62582*G_elastic*aRRR*C23RRR*bRRR*atom62791;
atom62817 = -epsiRRR*G_elastic*aRRR*atom62577*C23RRR*bRRR*atom62791-epsiRRR*atom62582*G_elastic*atom62800*C33RRR*atom62801;
atom63077 = atom62776*atom62817;
atom25581 =  atom49*atom868+atom50*atom869;
atom25593 =  atom49*atom869-atom868*atom50;
atom59542 = -atom1243*atom865+atom25593*atom1325+atom25581*atom1322;
atom59546 = -atom865*atom1237+atom1316*atom25581+atom1319*atom25593;
atom59553 =  atom25581*atom1310+atom25593*atom1313-atom1231*atom865;
atom59556 =  atom59542*atom22015+atom26169-atom22017*atom59553;
atom62818 = -C11RRR*epsiRRR*G_elastic*aRRR*bRRR*( atom2431*atom59556+( atom26287+atom22017*atom59546-atom22016*atom59542)*atom2430);
atom62588 =  ( atom22016*atom59553-atom59546*atom22015+atom26165)*atom2435+atom2434*atom59556;
atom62593 =  atom21939*atom25581-atom62550*atom865+atom62558*atom25593;
atom62821 =  epsiRRR*atom62593*G_elastic*aRRR*C23RRR*bRRR*atom62791-epsiRRR*atom62588*C22RRR*G_elastic*aRRR*bRRR;
atom62824 = -epsiRRR*atom62593*G_elastic*atom62800*C33RRR*atom62801-epsiRRR*atom62588*G_elastic*aRRR*C23RRR*bRRR*atom62791;
atom63127 = atom62776*atom62824;
atom62825 = -C11RRR*atom8275*epsiRRR*G_elastic*aRRR*bRRR;
atom62826 = -epsiRRR*C22RRR*G_elastic*aRRR*atom8324*bRRR;
atom62827 = -epsiRRR*G_elastic*aRRR*atom8324*C23RRR*bRRR*atom62791;
atom63177 = atom62776*atom62827;
atom59573 = -atom22016*atom1243+atom22017*atom1237;
atom59577 = -atom1231*atom22017+atom1243*atom22015;
atom59578 =  atom52581+atom59577;
atom62828 = -C11RRR*( ( atom59573+atom52514)*atom2430+atom59578*atom2431)*epsiRRR*G_elastic*aRRR*bRRR;
atom59581 =  atom22016*atom1231-atom22015*atom1237;
atom62599 =  atom2434*atom59578+( atom59581+atom52627)*atom2435;
atom62830 = epsiRRR*G_elastic*aRRR*C23RRR*atom62550*bRRR*atom62791;
atom62831 =  atom62830-epsiRRR*C22RRR*G_elastic*aRRR*bRRR*atom62599;
atom62833 = -epsiRRR*G_elastic*atom62800*atom62550*C33RRR*atom62801;
atom62834 = -epsiRRR*G_elastic*aRRR*C23RRR*bRRR*atom62599*atom62791+atom62833;
atom63227 = atom62834*atom62776;
atom59597 =  atom1316*atom25584+atom25596*atom1319;
atom59593 =  atom25596*atom1325+atom1322*atom25584;
atom59604 =  atom25596*atom1313+atom25584*atom1310;
atom59607 =  atom59593*atom22015-atom59604*atom22017+atom26250;
atom62835 = -C11RRR*epsiRRR*( atom59607*atom2431-( atom22016*atom59593-atom26315-atom22017*atom59597)*atom2430)*G_elastic*aRRR*bRRR;
atom62608 =  atom25596*atom62558+atom21939*atom25584;
atom62605 =  ( atom26244+atom59604*atom22016-atom59597*atom22015)*atom2435+atom59607*atom2434;
atom62838 =  epsiRRR*G_elastic*aRRR*atom62608*C23RRR*bRRR*atom62791-epsiRRR*C22RRR*G_elastic*aRRR*bRRR*atom62605;
atom62841 = -epsiRRR*G_elastic*atom62800*atom62608*C33RRR*atom62801-epsiRRR*G_elastic*aRRR*C23RRR*bRRR*atom62605*atom62791;
atom63277 = atom62776*atom62841;
atom62842 = -C11RRR*epsiRRR*G_elastic*aRRR*bRRR*atom8284;
atom62843 = -epsiRRR*atom8333*C22RRR*G_elastic*aRRR*bRRR;
atom62844 = -epsiRRR*atom8333*G_elastic*aRRR*C23RRR*bRRR*atom62791;
atom63327 = atom62776*atom62844;
atom62845 = -C11RRR*epsiRRR*G_elastic*aRRR*( atom2431*atom59577+atom59573*atom2430)*bRRR;
atom62614 =  atom2435*atom59581+atom2434*atom59577;
atom62847 = -epsiRRR*C22RRR*G_elastic*aRRR*atom62614*bRRR+atom62830;
atom62849 = -epsiRRR*G_elastic*aRRR*C23RRR*atom62614*bRRR*atom62791+atom62833;
atom63377 = atom62776*atom62849;
atom59632 = -atom22017*atom1310+atom1322*atom22015;
atom62850 = -C11RRR*epsiRRR*G_elastic*aRRR*( atom2431*atom59632-( atom22016*atom1322-atom1316*atom22017)*atom2430)*bRRR;
atom62620 =  ( atom22016*atom1310-atom1316*atom22015)*atom2435+atom2434*atom59632;
atom62853 =  epsiRRR*G_elastic*aRRR*atom21939*C23RRR*bRRR*atom62791-epsiRRR*atom62620*C22RRR*G_elastic*aRRR*bRRR;
atom62856 = -epsiRRR*atom62620*G_elastic*aRRR*C23RRR*bRRR*atom62791-epsiRRR*G_elastic*atom62800*atom21939*C33RRR*atom62801;
atom63427 = atom62776*atom62856;

_CKRRR[0] = atom2430*atom62787;
_CKRRR[1] = atom62788*atom2430;
_CKRRR[2] = 0.0;
_CKRRR[3] = atom62795*atom2430;
_CKRRR[4] = atom62804*atom2430;
_CKRRR[5] = atom62811*atom2430;
_CKRRR[6] = atom62818*atom2430;
_CKRRR[7] = 0.0;
_CKRRR[8] = atom62825*atom2430;
_CKRRR[9] = atom62828*atom2430;
_CKRRR[10] = atom62835*atom2430;
_CKRRR[11] = 0.0;
_CKRRR[12] = 0.0;
_CKRRR[13] = 0.0;
_CKRRR[14] = 0.0;
_CKRRR[15] = 0.0;
_CKRRR[16] = 0.0;
_CKRRR[17] = atom62842*atom2430;
_CKRRR[18] = atom62845*atom2430;
_CKRRR[19] = atom62850*atom2430;
_CKRRR[20] = 0.0;
_CKRRR[21] = 0.0;
_CKRRR[22] = 0.0;
_CKRRR[23] = 0.0;
_CKRRR[24] = 0.0;
_CKRRR[25] = 0.0;
_CKRRR[26] = 0.0;
_CKRRR[27] = 0.0;
_CKRRR[28] = 0.0;
_CKRRR[29] = 0.0;
_CKRRR[30] = 0.0;
_CKRRR[31] = 0.0;
_CKRRR[32] = 0.0;
_CKRRR[33] = 0.0;
_CKRRR[34] = 0.0;
_CKRRR[35] = 0.0;
_CKRRR[36] = 0.0;
_CKRRR[37] = 0.0;
_CKRRR[38] = 0.0;
_CKRRR[39] = 0.0;
_CKRRR[40] = 0.0;
_CKRRR[41] = 0.0;
_CKRRR[42] = 0.0;
_CKRRR[43] = 0.0;
_CKRRR[44] = atom2431*atom62787;
_CKRRR[45] =  atom62788*atom2431+atom2434*atom62789;
_CKRRR[46] = atom2434*atom62793;
_CKRRR[47] =  atom62795*atom2431+atom2434*atom62798;
_CKRRR[48] =  atom2434*atom62807+atom62804*atom2431;
_CKRRR[49] =  atom2434*atom62814+atom62811*atom2431;
_CKRRR[50] =  atom62818*atom2431+atom2434*atom62821;
_CKRRR[51] = 0.0;
_CKRRR[52] =  atom62826*atom2434+atom2431*atom62825;
_CKRRR[53] =  atom2431*atom62828+atom2434*atom62831;
_CKRRR[54] =  atom2431*atom62835+atom2434*atom62838;
_CKRRR[55] = 0.0;
_CKRRR[56] = 0.0;
_CKRRR[57] = 0.0;
_CKRRR[58] = 0.0;
_CKRRR[59] = 0.0;
_CKRRR[60] = 0.0;
_CKRRR[61] =  atom2434*atom62843+atom62842*atom2431;
_CKRRR[62] =  atom2431*atom62845+atom2434*atom62847;
_CKRRR[63] =  atom2434*atom62853+atom62850*atom2431;
_CKRRR[64] = 0.0;
_CKRRR[65] = 0.0;
_CKRRR[66] = 0.0;
_CKRRR[67] = 0.0;
_CKRRR[68] = 0.0;
_CKRRR[69] = 0.0;
_CKRRR[70] = 0.0;
_CKRRR[71] = 0.0;
_CKRRR[72] = 0.0;
_CKRRR[73] = 0.0;
_CKRRR[74] = 0.0;
_CKRRR[75] = 0.0;
_CKRRR[76] = 0.0;
_CKRRR[77] = 0.0;
_CKRRR[78] = 0.0;
_CKRRR[79] = 0.0;
_CKRRR[80] = 0.0;
_CKRRR[81] = 0.0;
_CKRRR[82] = 0.0;
_CKRRR[83] = 0.0;
_CKRRR[84] = 0.0;
_CKRRR[85] = 0.0;
_CKRRR[86] = 0.0;
_CKRRR[87] = 0.0;
_CKRRR[88] = 0.0;
_CKRRR[89] = atom62789*atom2435;
_CKRRR[90] = atom2435*atom62793;
_CKRRR[91] = atom62798*atom2435;
_CKRRR[92] = atom62807*atom2435;
_CKRRR[93] = atom62814*atom2435;
_CKRRR[94] = atom62821*atom2435;
_CKRRR[95] = 0.0;
_CKRRR[96] = atom62826*atom2435;
_CKRRR[97] = atom62831*atom2435;
_CKRRR[98] = atom62838*atom2435;
_CKRRR[99] = 0.0;
_CKRRR[100] = 0.0;
_CKRRR[101] = 0.0;
_CKRRR[102] = 0.0;
_CKRRR[103] = 0.0;
_CKRRR[104] = 0.0;
_CKRRR[105] = atom62843*atom2435;
_CKRRR[106] = atom62847*atom2435;
_CKRRR[107] = atom62853*atom2435;
_CKRRR[108] = 0.0;
_CKRRR[109] = 0.0;
_CKRRR[110] = 0.0;
_CKRRR[111] = 0.0;
_CKRRR[112] = 0.0;
_CKRRR[113] = 0.0;
_CKRRR[114] = 0.0;
_CKRRR[115] = 0.0;
_CKRRR[116] = 0.0;
_CKRRR[117] = 0.0;
_CKRRR[118] = 0.0;
_CKRRR[119] = 0.0;
_CKRRR[120] = 0.0;
_CKRRR[121] = 0.0;
_CKRRR[122] = 0.0;
_CKRRR[123] = 0.0;
_CKRRR[124] = 0.0;
_CKRRR[125] = 0.0;
_CKRRR[126] = 0.0;
_CKRRR[127] = 0.0;
_CKRRR[128] = 0.0;
_CKRRR[129] = 0.0;
_CKRRR[130] = 0.0;
_CKRRR[131] = 0.0;
_CKRRR[132] = atom62627*atom62787;
_CKRRR[133] =  atom62789*atom62721+atom62627*atom62788+atom62792*atom62762;
_CKRRR[134] =  atom62721*atom62793+atom62762*atom62794;
_CKRRR[135] =  atom62762*atom62803+atom62627*atom62795+atom62798*atom62721;
_CKRRR[136] =  atom62810*atom62762+atom62807*atom62721+atom62627*atom62804;
_CKRRR[137] =  atom62817*atom62762+atom62811*atom62627+atom62814*atom62721;
_CKRRR[138] =  atom62821*atom62721+atom62627*atom62818+atom62824*atom62762;
_CKRRR[139] = 0.0;
_CKRRR[140] =  atom62826*atom62721+atom62627*atom62825+atom62827*atom62762;
_CKRRR[141] =  atom62831*atom62721+atom62834*atom62762+atom62627*atom62828;
_CKRRR[142] =  atom62762*atom62841+atom62838*atom62721+atom62627*atom62835;
_CKRRR[143] = 0.0;
_CKRRR[144] = 0.0;
_CKRRR[145] = 0.0;
_CKRRR[146] = 0.0;
_CKRRR[147] = 0.0;
_CKRRR[148] = 0.0;
_CKRRR[149] =  atom62843*atom62721+atom62627*atom62842+atom62762*atom62844;
_CKRRR[150] =  atom62762*atom62849+atom62627*atom62845+atom62847*atom62721;
_CKRRR[151] =  atom62762*atom62856+atom62627*atom62850+atom62853*atom62721;
_CKRRR[152] = 0.0;
_CKRRR[153] = 0.0;
_CKRRR[154] = 0.0;
_CKRRR[155] = 0.0;
_CKRRR[156] = 0.0;
_CKRRR[157] = 0.0;
_CKRRR[158] = 0.0;
_CKRRR[159] = 0.0;
_CKRRR[160] = 0.0;
_CKRRR[161] = 0.0;
_CKRRR[162] = 0.0;
_CKRRR[163] = 0.0;
_CKRRR[164] = 0.0;
_CKRRR[165] = 0.0;
_CKRRR[166] = 0.0;
_CKRRR[167] = 0.0;
_CKRRR[168] = 0.0;
_CKRRR[169] = 0.0;
_CKRRR[170] = 0.0;
_CKRRR[171] = 0.0;
_CKRRR[172] = 0.0;
_CKRRR[173] = 0.0;
_CKRRR[174] = 0.0;
_CKRRR[175] = 0.0;
_CKRRR[176] = atom62638*atom62787;
_CKRRR[177] =  atom62728*atom62789+atom62767*atom62792+atom62788*atom62638;
_CKRRR[178] =  atom62728*atom62793+atom62767*atom62794;
_CKRRR[179] =  atom62767*atom62803+atom62638*atom62795+atom62728*atom62798;
_CKRRR[180] =  atom62804*atom62638+atom62810*atom62767+atom62728*atom62807;
_CKRRR[181] =  atom62728*atom62814+atom62767*atom62817+atom62811*atom62638;
_CKRRR[182] =  atom62824*atom62767+atom62818*atom62638+atom62728*atom62821;
_CKRRR[183] = 0.0;
_CKRRR[184] =  atom62827*atom62767+atom62826*atom62728+atom62638*atom62825;
_CKRRR[185] =  atom62728*atom62831+atom62638*atom62828+atom62834*atom62767;
_CKRRR[186] =  atom62638*atom62835+atom62728*atom62838+atom62767*atom62841;
_CKRRR[187] = 0.0;
_CKRRR[188] = 0.0;
_CKRRR[189] = 0.0;
_CKRRR[190] = 0.0;
_CKRRR[191] = 0.0;
_CKRRR[192] = 0.0;
_CKRRR[193] =  atom62767*atom62844+atom62728*atom62843+atom62638*atom62842;
_CKRRR[194] =  atom62638*atom62845+atom62767*atom62849+atom62728*atom62847;
_CKRRR[195] =  atom62728*atom62853+atom62638*atom62850+atom62767*atom62856;
_CKRRR[196] = 0.0;
_CKRRR[197] = 0.0;
_CKRRR[198] = 0.0;
_CKRRR[199] = 0.0;
_CKRRR[200] = 0.0;
_CKRRR[201] = 0.0;
_CKRRR[202] = 0.0;
_CKRRR[203] = 0.0;
_CKRRR[204] = 0.0;
_CKRRR[205] = 0.0;
_CKRRR[206] = 0.0;
_CKRRR[207] = 0.0;
_CKRRR[208] = 0.0;
_CKRRR[209] = 0.0;
_CKRRR[210] = 0.0;
_CKRRR[211] = 0.0;
_CKRRR[212] = 0.0;
_CKRRR[213] = 0.0;
_CKRRR[214] = 0.0;
_CKRRR[215] = 0.0;
_CKRRR[216] = 0.0;
_CKRRR[217] = 0.0;
_CKRRR[218] = 0.0;
_CKRRR[219] = 0.0;
_CKRRR[220] = atom62643*atom62787;
_CKRRR[221] =  atom62792*atom2426+atom62789*atom62729+atom62788*atom62643;
_CKRRR[222] =  atom2426*atom62794+atom62729*atom62793;
_CKRRR[223] =  atom62803*atom2426+atom62643*atom62795+atom62798*atom62729;
_CKRRR[224] =  atom62643*atom62804+atom62807*atom62729+atom62810*atom2426;
_CKRRR[225] =  atom62817*atom2426+atom62811*atom62643+atom62814*atom62729;
_CKRRR[226] =  atom62821*atom62729+atom62824*atom2426+atom62818*atom62643;
_CKRRR[227] = 0.0;
_CKRRR[228] =  atom62826*atom62729+atom62827*atom2426+atom62643*atom62825;
_CKRRR[229] =  atom62834*atom2426+atom62831*atom62729+atom62643*atom62828;
_CKRRR[230] =  atom62643*atom62835+atom2426*atom62841+atom62838*atom62729;
_CKRRR[231] = 0.0;
_CKRRR[232] = 0.0;
_CKRRR[233] = 0.0;
_CKRRR[234] = 0.0;
_CKRRR[235] = 0.0;
_CKRRR[236] = 0.0;
_CKRRR[237] =  atom62843*atom62729+atom62844*atom2426+atom62643*atom62842;
_CKRRR[238] =  atom62643*atom62845+atom2426*atom62849+atom62847*atom62729;
_CKRRR[239] =  atom62856*atom2426+atom62853*atom62729+atom62643*atom62850;
_CKRRR[240] = 0.0;
_CKRRR[241] = 0.0;
_CKRRR[242] = 0.0;
_CKRRR[243] = 0.0;
_CKRRR[244] = 0.0;
_CKRRR[245] = 0.0;
_CKRRR[246] = 0.0;
_CKRRR[247] = 0.0;
_CKRRR[248] = 0.0;
_CKRRR[249] = 0.0;
_CKRRR[250] = 0.0;
_CKRRR[251] = 0.0;
_CKRRR[252] = 0.0;
_CKRRR[253] = 0.0;
_CKRRR[254] = 0.0;
_CKRRR[255] = 0.0;
_CKRRR[256] = 0.0;
_CKRRR[257] = 0.0;
_CKRRR[258] = 0.0;
_CKRRR[259] = 0.0;
_CKRRR[260] = 0.0;
_CKRRR[261] = 0.0;
_CKRRR[262] = 0.0;
_CKRRR[263] = 0.0;
_CKRRR[264] = atom62654*atom62787;
_CKRRR[265] =  atom62788*atom62654+atom62792*atom62771+atom62789*atom62736;
_CKRRR[266] =  atom62736*atom62793+atom62771*atom62794;
_CKRRR[267] =  atom62654*atom62795+atom62803*atom62771+atom62736*atom62798;
_CKRRR[268] =  atom62810*atom62771+atom62654*atom62804+atom62736*atom62807;
_CKRRR[269] =  atom62814*atom62736+atom62811*atom62654+atom62817*atom62771;
_CKRRR[270] =  atom62736*atom62821+atom62824*atom62771+atom62818*atom62654;
_CKRRR[271] = 0.0;
_CKRRR[272] =  atom62654*atom62825+atom62826*atom62736+atom62827*atom62771;
_CKRRR[273] =  atom62736*atom62831+atom62654*atom62828+atom62834*atom62771;
_CKRRR[274] =  atom62771*atom62841+atom62736*atom62838+atom62654*atom62835;
_CKRRR[275] = 0.0;
_CKRRR[276] = 0.0;
_CKRRR[277] = 0.0;
_CKRRR[278] = 0.0;
_CKRRR[279] = 0.0;
_CKRRR[280] = 0.0;
_CKRRR[281] =  atom62654*atom62842+atom62843*atom62736+atom62844*atom62771;
_CKRRR[282] =  atom62654*atom62845+atom62771*atom62849+atom62736*atom62847;
_CKRRR[283] =  atom62654*atom62850+atom62853*atom62736+atom62771*atom62856;
_CKRRR[284] = 0.0;
_CKRRR[285] = 0.0;
_CKRRR[286] = 0.0;
_CKRRR[287] = 0.0;
_CKRRR[288] = 0.0;
_CKRRR[289] = 0.0;
_CKRRR[290] = 0.0;
_CKRRR[291] = 0.0;
_CKRRR[292] = 0.0;
_CKRRR[293] = 0.0;
_CKRRR[294] = 0.0;
_CKRRR[295] = 0.0;
_CKRRR[296] = 0.0;
_CKRRR[297] = 0.0;
_CKRRR[298] = 0.0;
_CKRRR[299] = 0.0;
_CKRRR[300] = 0.0;
_CKRRR[301] = 0.0;
_CKRRR[302] = 0.0;
_CKRRR[303] = 0.0;
_CKRRR[304] = 0.0;
_CKRRR[305] = 0.0;
_CKRRR[306] = 0.0;
_CKRRR[307] = 0.0;
_CKRRR[308] = 0.0;
_CKRRR[309] = 0.0;
_CKRRR[310] = 0.0;
_CKRRR[311] = 0.0;
_CKRRR[312] = 0.0;
_CKRRR[313] = 0.0;
_CKRRR[314] = 0.0;
_CKRRR[315] = 0.0;
_CKRRR[316] = 0.0;
_CKRRR[317] = 0.0;
_CKRRR[318] = 0.0;
_CKRRR[319] = 0.0;
_CKRRR[320] = 0.0;
_CKRRR[321] = 0.0;
_CKRRR[322] = 0.0;
_CKRRR[323] = 0.0;
_CKRRR[324] = 0.0;
_CKRRR[325] = 0.0;
_CKRRR[326] = 0.0;
_CKRRR[327] = 0.0;
_CKRRR[328] = 0.0;
_CKRRR[329] = 0.0;
_CKRRR[330] = 0.0;
_CKRRR[331] = 0.0;
_CKRRR[332] = 0.0;
_CKRRR[333] = 0.0;
_CKRRR[334] = 0.0;
_CKRRR[335] = 0.0;
_CKRRR[336] = 0.0;
_CKRRR[337] = 0.0;
_CKRRR[338] = 0.0;
_CKRRR[339] = 0.0;
_CKRRR[340] = 0.0;
_CKRRR[341] = 0.0;
_CKRRR[342] = 0.0;
_CKRRR[343] = 0.0;
_CKRRR[344] = 0.0;
_CKRRR[345] = 0.0;
_CKRRR[346] = 0.0;
_CKRRR[347] = 0.0;
_CKRRR[348] = 0.0;
_CKRRR[349] = 0.0;
_CKRRR[350] = 0.0;
_CKRRR[351] = 0.0;
_CKRRR[352] = atom8275*atom62787;
_CKRRR[353] =  atom62789*atom8324+atom62788*atom8275;
_CKRRR[354] = atom8324*atom62793;
_CKRRR[355] =  atom8324*atom62798+atom8275*atom62795;
_CKRRR[356] =  atom8324*atom62807+atom8275*atom62804;
_CKRRR[357] =  atom62814*atom8324+atom62811*atom8275;
_CKRRR[358] =  atom8324*atom62821+atom62818*atom8275;
_CKRRR[359] = 0.0;
_CKRRR[360] =  atom8275*atom62825+atom62826*atom8324;
_CKRRR[361] =  atom8275*atom62828+atom8324*atom62831;
_CKRRR[362] =  atom8324*atom62838+atom8275*atom62835;
_CKRRR[363] = 0.0;
_CKRRR[364] = 0.0;
_CKRRR[365] = 0.0;
_CKRRR[366] = 0.0;
_CKRRR[367] = 0.0;
_CKRRR[368] = 0.0;
_CKRRR[369] =  atom8275*atom62842+atom8324*atom62843;
_CKRRR[370] =  atom8324*atom62847+atom8275*atom62845;
_CKRRR[371] =  atom8275*atom62850+atom8324*atom62853;
_CKRRR[372] = 0.0;
_CKRRR[373] = 0.0;
_CKRRR[374] = 0.0;
_CKRRR[375] = 0.0;
_CKRRR[376] = 0.0;
_CKRRR[377] = 0.0;
_CKRRR[378] = 0.0;
_CKRRR[379] = 0.0;
_CKRRR[380] = 0.0;
_CKRRR[381] = 0.0;
_CKRRR[382] = 0.0;
_CKRRR[383] = 0.0;
_CKRRR[384] = 0.0;
_CKRRR[385] = 0.0;
_CKRRR[386] = 0.0;
_CKRRR[387] = 0.0;
_CKRRR[388] = 0.0;
_CKRRR[389] = 0.0;
_CKRRR[390] = 0.0;
_CKRRR[391] = 0.0;
_CKRRR[392] = 0.0;
_CKRRR[393] = 0.0;
_CKRRR[394] = 0.0;
_CKRRR[395] = 0.0;
_CKRRR[396] = atom62787*atom62665;
_CKRRR[397] =  atom62788*atom62665+atom62743*atom62789+atom62900;
_CKRRR[398] =  atom62935+atom62743*atom62793;
_CKRRR[399] =  atom62743*atom62798+atom62977+atom62795*atom62665;
_CKRRR[400] =  atom62743*atom62807+atom62804*atom62665+atom63027;
_CKRRR[401] =  atom63077+atom62811*atom62665+atom62743*atom62814;
_CKRRR[402] =  atom62743*atom62821+atom62818*atom62665+atom63127;
_CKRRR[403] = 0.0;
_CKRRR[404] =  atom62825*atom62665+atom62826*atom62743+atom63177;
_CKRRR[405] =  atom63227+atom62828*atom62665+atom62743*atom62831;
_CKRRR[406] =  atom62743*atom62838+atom62835*atom62665+atom63277;
_CKRRR[407] = 0.0;
_CKRRR[408] = 0.0;
_CKRRR[409] = 0.0;
_CKRRR[410] = 0.0;
_CKRRR[411] = 0.0;
_CKRRR[412] = 0.0;
_CKRRR[413] =  atom62743*atom62843+atom63327+atom62842*atom62665;
_CKRRR[414] =  atom62743*atom62847+atom62845*atom62665+atom63377;
_CKRRR[415] =  atom63427+atom62850*atom62665+atom62743*atom62853;
_CKRRR[416] = 0.0;
_CKRRR[417] = 0.0;
_CKRRR[418] = 0.0;
_CKRRR[419] = 0.0;
_CKRRR[420] = 0.0;
_CKRRR[421] = 0.0;
_CKRRR[422] = 0.0;
_CKRRR[423] = 0.0;
_CKRRR[424] = 0.0;
_CKRRR[425] = 0.0;
_CKRRR[426] = 0.0;
_CKRRR[427] = 0.0;
_CKRRR[428] = 0.0;
_CKRRR[429] = 0.0;
_CKRRR[430] = 0.0;
_CKRRR[431] = 0.0;
_CKRRR[432] = 0.0;
_CKRRR[433] = 0.0;
_CKRRR[434] = 0.0;
_CKRRR[435] = 0.0;
_CKRRR[436] = 0.0;
_CKRRR[437] = 0.0;
_CKRRR[438] = 0.0;
_CKRRR[439] = 0.0;
_CKRRR[440] = atom62676*atom62787;
_CKRRR[441] =  atom62781*atom62792+atom62789*atom62750+atom62788*atom62676;
_CKRRR[442] =  atom62781*atom62794+atom62750*atom62793;
_CKRRR[443] =  atom62781*atom62803+atom62750*atom62798+atom62795*atom62676;
_CKRRR[444] =  atom62750*atom62807+atom62804*atom62676+atom62781*atom62810;
_CKRRR[445] =  atom62781*atom62817+atom62811*atom62676+atom62750*atom62814;
_CKRRR[446] =  atom62750*atom62821+atom62818*atom62676+atom62781*atom62824;
_CKRRR[447] = 0.0;
_CKRRR[448] =  atom62826*atom62750+atom62781*atom62827+atom62825*atom62676;
_CKRRR[449] =  atom62750*atom62831+atom62828*atom62676+atom62834*atom62781;
_CKRRR[450] =  atom62835*atom62676+atom62750*atom62838+atom62781*atom62841;
_CKRRR[451] = 0.0;
_CKRRR[452] = 0.0;
_CKRRR[453] = 0.0;
_CKRRR[454] = 0.0;
_CKRRR[455] = 0.0;
_CKRRR[456] = 0.0;
_CKRRR[457] =  atom62750*atom62843+atom62781*atom62844+atom62842*atom62676;
_CKRRR[458] =  atom62750*atom62847+atom62845*atom62676+atom62781*atom62849;
_CKRRR[459] =  atom62781*atom62856+atom62850*atom62676+atom62750*atom62853;
_CKRRR[460] = 0.0;
_CKRRR[461] = 0.0;
_CKRRR[462] = 0.0;
_CKRRR[463] = 0.0;
_CKRRR[464] = 0.0;
_CKRRR[465] = 0.0;
_CKRRR[466] = 0.0;
_CKRRR[467] = 0.0;
_CKRRR[468] = 0.0;
_CKRRR[469] = 0.0;
_CKRRR[470] = 0.0;
_CKRRR[471] = 0.0;
_CKRRR[472] = 0.0;
_CKRRR[473] = 0.0;
_CKRRR[474] = 0.0;
_CKRRR[475] = 0.0;
_CKRRR[476] = 0.0;
_CKRRR[477] = 0.0;
_CKRRR[478] = 0.0;
_CKRRR[479] = 0.0;
_CKRRR[480] = 0.0;
_CKRRR[481] = 0.0;
_CKRRR[482] = 0.0;
_CKRRR[483] = 0.0;
_CKRRR[484] = 0.0;
_CKRRR[485] = 0.0;
_CKRRR[486] = 0.0;
_CKRRR[487] = 0.0;
_CKRRR[488] = 0.0;
_CKRRR[489] = 0.0;
_CKRRR[490] = 0.0;
_CKRRR[491] = 0.0;
_CKRRR[492] = 0.0;
_CKRRR[493] = 0.0;
_CKRRR[494] = 0.0;
_CKRRR[495] = 0.0;
_CKRRR[496] = 0.0;
_CKRRR[497] = 0.0;
_CKRRR[498] = 0.0;
_CKRRR[499] = 0.0;
_CKRRR[500] = 0.0;
_CKRRR[501] = 0.0;
_CKRRR[502] = 0.0;
_CKRRR[503] = 0.0;
_CKRRR[504] = 0.0;
_CKRRR[505] = 0.0;
_CKRRR[506] = 0.0;
_CKRRR[507] = 0.0;
_CKRRR[508] = 0.0;
_CKRRR[509] = 0.0;
_CKRRR[510] = 0.0;
_CKRRR[511] = 0.0;
_CKRRR[512] = 0.0;
_CKRRR[513] = 0.0;
_CKRRR[514] = 0.0;
_CKRRR[515] = 0.0;
_CKRRR[516] = 0.0;
_CKRRR[517] = 0.0;
_CKRRR[518] = 0.0;
_CKRRR[519] = 0.0;
_CKRRR[520] = 0.0;
_CKRRR[521] = 0.0;
_CKRRR[522] = 0.0;
_CKRRR[523] = 0.0;
_CKRRR[524] = 0.0;
_CKRRR[525] = 0.0;
_CKRRR[526] = 0.0;
_CKRRR[527] = 0.0;
_CKRRR[528] = 0.0;
_CKRRR[529] = 0.0;
_CKRRR[530] = 0.0;
_CKRRR[531] = 0.0;
_CKRRR[532] = 0.0;
_CKRRR[533] = 0.0;
_CKRRR[534] = 0.0;
_CKRRR[535] = 0.0;
_CKRRR[536] = 0.0;
_CKRRR[537] = 0.0;
_CKRRR[538] = 0.0;
_CKRRR[539] = 0.0;
_CKRRR[540] = 0.0;
_CKRRR[541] = 0.0;
_CKRRR[542] = 0.0;
_CKRRR[543] = 0.0;
_CKRRR[544] = 0.0;
_CKRRR[545] = 0.0;
_CKRRR[546] = 0.0;
_CKRRR[547] = 0.0;
_CKRRR[548] = 0.0;
_CKRRR[549] = 0.0;
_CKRRR[550] = 0.0;
_CKRRR[551] = 0.0;
_CKRRR[552] = 0.0;
_CKRRR[553] = 0.0;
_CKRRR[554] = 0.0;
_CKRRR[555] = 0.0;
_CKRRR[556] = 0.0;
_CKRRR[557] = 0.0;
_CKRRR[558] = 0.0;
_CKRRR[559] = 0.0;
_CKRRR[560] = 0.0;
_CKRRR[561] = 0.0;
_CKRRR[562] = 0.0;
_CKRRR[563] = 0.0;
_CKRRR[564] = 0.0;
_CKRRR[565] = 0.0;
_CKRRR[566] = 0.0;
_CKRRR[567] = 0.0;
_CKRRR[568] = 0.0;
_CKRRR[569] = 0.0;
_CKRRR[570] = 0.0;
_CKRRR[571] = 0.0;
_CKRRR[572] = 0.0;
_CKRRR[573] = 0.0;
_CKRRR[574] = 0.0;
_CKRRR[575] = 0.0;
_CKRRR[576] = 0.0;
_CKRRR[577] = 0.0;
_CKRRR[578] = 0.0;
_CKRRR[579] = 0.0;
_CKRRR[580] = 0.0;
_CKRRR[581] = 0.0;
_CKRRR[582] = 0.0;
_CKRRR[583] = 0.0;
_CKRRR[584] = 0.0;
_CKRRR[585] = 0.0;
_CKRRR[586] = 0.0;
_CKRRR[587] = 0.0;
_CKRRR[588] = 0.0;
_CKRRR[589] = 0.0;
_CKRRR[590] = 0.0;
_CKRRR[591] = 0.0;
_CKRRR[592] = 0.0;
_CKRRR[593] = 0.0;
_CKRRR[594] = 0.0;
_CKRRR[595] = 0.0;
_CKRRR[596] = 0.0;
_CKRRR[597] = 0.0;
_CKRRR[598] = 0.0;
_CKRRR[599] = 0.0;
_CKRRR[600] = 0.0;
_CKRRR[601] = 0.0;
_CKRRR[602] = 0.0;
_CKRRR[603] = 0.0;
_CKRRR[604] = 0.0;
_CKRRR[605] = 0.0;
_CKRRR[606] = 0.0;
_CKRRR[607] = 0.0;
_CKRRR[608] = 0.0;
_CKRRR[609] = 0.0;
_CKRRR[610] = 0.0;
_CKRRR[611] = 0.0;
_CKRRR[612] = 0.0;
_CKRRR[613] = 0.0;
_CKRRR[614] = 0.0;
_CKRRR[615] = 0.0;
_CKRRR[616] = 0.0;
_CKRRR[617] = 0.0;
_CKRRR[618] = 0.0;
_CKRRR[619] = 0.0;
_CKRRR[620] = 0.0;
_CKRRR[621] = 0.0;
_CKRRR[622] = 0.0;
_CKRRR[623] = 0.0;
_CKRRR[624] = 0.0;
_CKRRR[625] = 0.0;
_CKRRR[626] = 0.0;
_CKRRR[627] = 0.0;
_CKRRR[628] = 0.0;
_CKRRR[629] = 0.0;
_CKRRR[630] = 0.0;
_CKRRR[631] = 0.0;
_CKRRR[632] = 0.0;
_CKRRR[633] = 0.0;
_CKRRR[634] = 0.0;
_CKRRR[635] = 0.0;
_CKRRR[636] = 0.0;
_CKRRR[637] = 0.0;
_CKRRR[638] = 0.0;
_CKRRR[639] = 0.0;
_CKRRR[640] = 0.0;
_CKRRR[641] = 0.0;
_CKRRR[642] = 0.0;
_CKRRR[643] = 0.0;
_CKRRR[644] = 0.0;
_CKRRR[645] = 0.0;
_CKRRR[646] = 0.0;
_CKRRR[647] = 0.0;
_CKRRR[648] = 0.0;
_CKRRR[649] = 0.0;
_CKRRR[650] = 0.0;
_CKRRR[651] = 0.0;
_CKRRR[652] = 0.0;
_CKRRR[653] = 0.0;
_CKRRR[654] = 0.0;
_CKRRR[655] = 0.0;
_CKRRR[656] = 0.0;
_CKRRR[657] = 0.0;
_CKRRR[658] = 0.0;
_CKRRR[659] = 0.0;
_CKRRR[660] = 0.0;
_CKRRR[661] = 0.0;
_CKRRR[662] = 0.0;
_CKRRR[663] = 0.0;
_CKRRR[664] = 0.0;
_CKRRR[665] = 0.0;
_CKRRR[666] = 0.0;
_CKRRR[667] = 0.0;
_CKRRR[668] = 0.0;
_CKRRR[669] = 0.0;
_CKRRR[670] = 0.0;
_CKRRR[671] = 0.0;
_CKRRR[672] = 0.0;
_CKRRR[673] = 0.0;
_CKRRR[674] = 0.0;
_CKRRR[675] = 0.0;
_CKRRR[676] = 0.0;
_CKRRR[677] = 0.0;
_CKRRR[678] = 0.0;
_CKRRR[679] = 0.0;
_CKRRR[680] = 0.0;
_CKRRR[681] = 0.0;
_CKRRR[682] = 0.0;
_CKRRR[683] = 0.0;
_CKRRR[684] = 0.0;
_CKRRR[685] = 0.0;
_CKRRR[686] = 0.0;
_CKRRR[687] = 0.0;
_CKRRR[688] = 0.0;
_CKRRR[689] = 0.0;
_CKRRR[690] = 0.0;
_CKRRR[691] = 0.0;
_CKRRR[692] = 0.0;
_CKRRR[693] = 0.0;
_CKRRR[694] = 0.0;
_CKRRR[695] = 0.0;
_CKRRR[696] = 0.0;
_CKRRR[697] = 0.0;
_CKRRR[698] = 0.0;
_CKRRR[699] = 0.0;
_CKRRR[700] = 0.0;
_CKRRR[701] = 0.0;
_CKRRR[702] = 0.0;
_CKRRR[703] = 0.0;
_CKRRR[704] = 0.0;
_CKRRR[705] = 0.0;
_CKRRR[706] = 0.0;
_CKRRR[707] = 0.0;
_CKRRR[708] = 0.0;
_CKRRR[709] = 0.0;
_CKRRR[710] = 0.0;
_CKRRR[711] = 0.0;
_CKRRR[712] = 0.0;
_CKRRR[713] = 0.0;
_CKRRR[714] = 0.0;
_CKRRR[715] = 0.0;
_CKRRR[716] = 0.0;
_CKRRR[717] = 0.0;
_CKRRR[718] = 0.0;
_CKRRR[719] = 0.0;
_CKRRR[720] = 0.0;
_CKRRR[721] = 0.0;
_CKRRR[722] = 0.0;
_CKRRR[723] = 0.0;
_CKRRR[724] = 0.0;
_CKRRR[725] = 0.0;
_CKRRR[726] = 0.0;
_CKRRR[727] = 0.0;
_CKRRR[728] = 0.0;
_CKRRR[729] = 0.0;
_CKRRR[730] = 0.0;
_CKRRR[731] = 0.0;
_CKRRR[732] = 0.0;
_CKRRR[733] = 0.0;
_CKRRR[734] = 0.0;
_CKRRR[735] = 0.0;
_CKRRR[736] = 0.0;
_CKRRR[737] = 0.0;
_CKRRR[738] = 0.0;
_CKRRR[739] = 0.0;
_CKRRR[740] = 0.0;
_CKRRR[741] = 0.0;
_CKRRR[742] = 0.0;
_CKRRR[743] = 0.0;
_CKRRR[744] = 0.0;
_CKRRR[745] = 0.0;
_CKRRR[746] = 0.0;
_CKRRR[747] = 0.0;
_CKRRR[748] = atom8284*atom62787;
_CKRRR[749] =  atom62788*atom8284+atom8333*atom62789;
_CKRRR[750] = atom8333*atom62793;
_CKRRR[751] =  atom8333*atom62798+atom62795*atom8284;
_CKRRR[752] =  atom8333*atom62807+atom62804*atom8284;
_CKRRR[753] =  atom62811*atom8284+atom8333*atom62814;
_CKRRR[754] =  atom8333*atom62821+atom62818*atom8284;
_CKRRR[755] = 0.0;
_CKRRR[756] =  atom8284*atom62825+atom62826*atom8333;
_CKRRR[757] =  atom8333*atom62831+atom62828*atom8284;
_CKRRR[758] =  atom8333*atom62838+atom62835*atom8284;
_CKRRR[759] = 0.0;
_CKRRR[760] = 0.0;
_CKRRR[761] = 0.0;
_CKRRR[762] = 0.0;
_CKRRR[763] = 0.0;
_CKRRR[764] = 0.0;
_CKRRR[765] =  atom8333*atom62843+atom62842*atom8284;
_CKRRR[766] =  atom62845*atom8284+atom8333*atom62847;
_CKRRR[767] =  atom8333*atom62853+atom62850*atom8284;
_CKRRR[768] = 0.0;
_CKRRR[769] = 0.0;
_CKRRR[770] = 0.0;
_CKRRR[771] = 0.0;
_CKRRR[772] = 0.0;
_CKRRR[773] = 0.0;
_CKRRR[774] = 0.0;
_CKRRR[775] = 0.0;
_CKRRR[776] = 0.0;
_CKRRR[777] = 0.0;
_CKRRR[778] = 0.0;
_CKRRR[779] = 0.0;
_CKRRR[780] = 0.0;
_CKRRR[781] = 0.0;
_CKRRR[782] = 0.0;
_CKRRR[783] = 0.0;
_CKRRR[784] = 0.0;
_CKRRR[785] = 0.0;
_CKRRR[786] = 0.0;
_CKRRR[787] = 0.0;
_CKRRR[788] = 0.0;
_CKRRR[789] = 0.0;
_CKRRR[790] = 0.0;
_CKRRR[791] = 0.0;
_CKRRR[792] = atom62679*atom62787;
_CKRRR[793] =  atom62788*atom62679+atom62900+atom62753*atom62789;
_CKRRR[794] =  atom62935+atom62753*atom62793;
_CKRRR[795] =  atom62753*atom62798+atom62795*atom62679+atom62977;
_CKRRR[796] =  atom62804*atom62679+atom62753*atom62807+atom63027;
_CKRRR[797] =  atom63077+atom62753*atom62814+atom62811*atom62679;
_CKRRR[798] =  atom62753*atom62821+atom62818*atom62679+atom63127;
_CKRRR[799] = 0.0;
_CKRRR[800] =  atom62679*atom62825+atom63177+atom62826*atom62753;
_CKRRR[801] =  atom63227+atom62679*atom62828+atom62753*atom62831;
_CKRRR[802] =  atom62753*atom62838+atom63277+atom62679*atom62835;
_CKRRR[803] = 0.0;
_CKRRR[804] = 0.0;
_CKRRR[805] = 0.0;
_CKRRR[806] = 0.0;
_CKRRR[807] = 0.0;
_CKRRR[808] = 0.0;
_CKRRR[809] =  atom62842*atom62679+atom62753*atom62843+atom63327;
_CKRRR[810] =  atom62753*atom62847+atom62679*atom62845+atom63377;
_CKRRR[811] =  atom63427+atom62850*atom62679+atom62753*atom62853;
_CKRRR[812] = 0.0;
_CKRRR[813] = 0.0;
_CKRRR[814] = 0.0;
_CKRRR[815] = 0.0;
_CKRRR[816] = 0.0;
_CKRRR[817] = 0.0;
_CKRRR[818] = 0.0;
_CKRRR[819] = 0.0;
_CKRRR[820] = 0.0;
_CKRRR[821] = 0.0;
_CKRRR[822] = 0.0;
_CKRRR[823] = 0.0;
_CKRRR[824] = 0.0;
_CKRRR[825] = 0.0;
_CKRRR[826] = 0.0;
_CKRRR[827] = 0.0;
_CKRRR[828] = 0.0;
_CKRRR[829] = 0.0;
_CKRRR[830] = 0.0;
_CKRRR[831] = 0.0;
_CKRRR[832] = 0.0;
_CKRRR[833] = 0.0;
_CKRRR[834] = 0.0;
_CKRRR[835] = 0.0;
_CKRRR[836] = atom62714*atom62787;
_CKRRR[837] =  atom62789*atom62759+atom62786*atom62792+atom62788*atom62714;
_CKRRR[838] =  atom62786*atom62794+atom62759*atom62793;
_CKRRR[839] =  atom62786*atom62803+atom62714*atom62795+atom62798*atom62759;
_CKRRR[840] =  atom62804*atom62714+atom62807*atom62759+atom62786*atom62810;
_CKRRR[841] =  atom62786*atom62817+atom62814*atom62759+atom62811*atom62714;
_CKRRR[842] =  atom62824*atom62786+atom62821*atom62759+atom62818*atom62714;
_CKRRR[843] = 0.0;
_CKRRR[844] =  atom62827*atom62786+atom62826*atom62759+atom62714*atom62825;
_CKRRR[845] =  atom62714*atom62828+atom62831*atom62759+atom62834*atom62786;
_CKRRR[846] =  atom62838*atom62759+atom62714*atom62835+atom62786*atom62841;
_CKRRR[847] = 0.0;
_CKRRR[848] = 0.0;
_CKRRR[849] = 0.0;
_CKRRR[850] = 0.0;
_CKRRR[851] = 0.0;
_CKRRR[852] = 0.0;
_CKRRR[853] =  atom62786*atom62844+atom62843*atom62759+atom62714*atom62842;
_CKRRR[854] =  atom62714*atom62845+atom62847*atom62759+atom62786*atom62849;
_CKRRR[855] =  atom62714*atom62850+atom62853*atom62759+atom62786*atom62856;
_CKRRR[856] = 0.0;
_CKRRR[857] = 0.0;
_CKRRR[858] = 0.0;
_CKRRR[859] = 0.0;
_CKRRR[860] = 0.0;
_CKRRR[861] = 0.0;
_CKRRR[862] = 0.0;
_CKRRR[863] = 0.0;
_CKRRR[864] = 0.0;
_CKRRR[865] = 0.0;
_CKRRR[866] = 0.0;
_CKRRR[867] = 0.0;
_CKRRR[868] = 0.0;
_CKRRR[869] = 0.0;
_CKRRR[870] = 0.0;
_CKRRR[871] = 0.0;
_CKRRR[872] = 0.0;
_CKRRR[873] = 0.0;
_CKRRR[874] = 0.0;
_CKRRR[875] = 0.0;
_CKRRR[876] = 0.0;
_CKRRR[877] = 0.0;
_CKRRR[878] = 0.0;
_CKRRR[879] = 0.0;
_CKRRR[880] = 0.0;
_CKRRR[881] = 0.0;
_CKRRR[882] = 0.0;
_CKRRR[883] = 0.0;
_CKRRR[884] = 0.0;
_CKRRR[885] = 0.0;
_CKRRR[886] = 0.0;
_CKRRR[887] = 0.0;
_CKRRR[888] = 0.0;
_CKRRR[889] = 0.0;
_CKRRR[890] = 0.0;
_CKRRR[891] = 0.0;
_CKRRR[892] = 0.0;
_CKRRR[893] = 0.0;
_CKRRR[894] = 0.0;
_CKRRR[895] = 0.0;
_CKRRR[896] = 0.0;
_CKRRR[897] = 0.0;
_CKRRR[898] = 0.0;
_CKRRR[899] = 0.0;
_CKRRR[900] = 0.0;
_CKRRR[901] = 0.0;
_CKRRR[902] = 0.0;
_CKRRR[903] = 0.0;
_CKRRR[904] = 0.0;
_CKRRR[905] = 0.0;
_CKRRR[906] = 0.0;
_CKRRR[907] = 0.0;
_CKRRR[908] = 0.0;
_CKRRR[909] = 0.0;
_CKRRR[910] = 0.0;
_CKRRR[911] = 0.0;
_CKRRR[912] = 0.0;
_CKRRR[913] = 0.0;
_CKRRR[914] = 0.0;
_CKRRR[915] = 0.0;
_CKRRR[916] = 0.0;
_CKRRR[917] = 0.0;
_CKRRR[918] = 0.0;
_CKRRR[919] = 0.0;
_CKRRR[920] = 0.0;
_CKRRR[921] = 0.0;
_CKRRR[922] = 0.0;
_CKRRR[923] = 0.0;
_CKRRR[924] = 0.0;
_CKRRR[925] = 0.0;
_CKRRR[926] = 0.0;
_CKRRR[927] = 0.0;
_CKRRR[928] = 0.0;
_CKRRR[929] = 0.0;
_CKRRR[930] = 0.0;
_CKRRR[931] = 0.0;
_CKRRR[932] = 0.0;
_CKRRR[933] = 0.0;
_CKRRR[934] = 0.0;
_CKRRR[935] = 0.0;
_CKRRR[936] = 0.0;
_CKRRR[937] = 0.0;
_CKRRR[938] = 0.0;
_CKRRR[939] = 0.0;
_CKRRR[940] = 0.0;
_CKRRR[941] = 0.0;
_CKRRR[942] = 0.0;
_CKRRR[943] = 0.0;
_CKRRR[944] = 0.0;
_CKRRR[945] = 0.0;
_CKRRR[946] = 0.0;
_CKRRR[947] = 0.0;
_CKRRR[948] = 0.0;
_CKRRR[949] = 0.0;
_CKRRR[950] = 0.0;
_CKRRR[951] = 0.0;
_CKRRR[952] = 0.0;
_CKRRR[953] = 0.0;
_CKRRR[954] = 0.0;
_CKRRR[955] = 0.0;
_CKRRR[956] = 0.0;
_CKRRR[957] = 0.0;
_CKRRR[958] = 0.0;
_CKRRR[959] = 0.0;
_CKRRR[960] = 0.0;
_CKRRR[961] = 0.0;
_CKRRR[962] = 0.0;
_CKRRR[963] = 0.0;
_CKRRR[964] = 0.0;
_CKRRR[965] = 0.0;
_CKRRR[966] = 0.0;
_CKRRR[967] = 0.0;
_CKRRR[968] = 0.0;
_CKRRR[969] = 0.0;
_CKRRR[970] = 0.0;
_CKRRR[971] = 0.0;
_CKRRR[972] = 0.0;
_CKRRR[973] = 0.0;
_CKRRR[974] = 0.0;
_CKRRR[975] = 0.0;
_CKRRR[976] = 0.0;
_CKRRR[977] = 0.0;
_CKRRR[978] = 0.0;
_CKRRR[979] = 0.0;
_CKRRR[980] = 0.0;
_CKRRR[981] = 0.0;
_CKRRR[982] = 0.0;
_CKRRR[983] = 0.0;
_CKRRR[984] = 0.0;
_CKRRR[985] = 0.0;
_CKRRR[986] = 0.0;
_CKRRR[987] = 0.0;
_CKRRR[988] = 0.0;
_CKRRR[989] = 0.0;
_CKRRR[990] = 0.0;
_CKRRR[991] = 0.0;
_CKRRR[992] = 0.0;
_CKRRR[993] = 0.0;
_CKRRR[994] = 0.0;
_CKRRR[995] = 0.0;
_CKRRR[996] = 0.0;
_CKRRR[997] = 0.0;
_CKRRR[998] = 0.0;
_CKRRR[999] = 0.0;
_CKRRR[1000] = 0.0;
_CKRRR[1001] = 0.0;
_CKRRR[1002] = 0.0;
_CKRRR[1003] = 0.0;
_CKRRR[1004] = 0.0;
_CKRRR[1005] = 0.0;
_CKRRR[1006] = 0.0;
_CKRRR[1007] = 0.0;
_CKRRR[1008] = 0.0;
_CKRRR[1009] = 0.0;
_CKRRR[1010] = 0.0;
_CKRRR[1011] = 0.0;
_CKRRR[1012] = 0.0;
_CKRRR[1013] = 0.0;
_CKRRR[1014] = 0.0;
_CKRRR[1015] = 0.0;
_CKRRR[1016] = 0.0;
_CKRRR[1017] = 0.0;
_CKRRR[1018] = 0.0;
_CKRRR[1019] = 0.0;
_CKRRR[1020] = 0.0;
_CKRRR[1021] = 0.0;
_CKRRR[1022] = 0.0;
_CKRRR[1023] = 0.0;
_CKRRR[1024] = 0.0;
_CKRRR[1025] = 0.0;
_CKRRR[1026] = 0.0;
_CKRRR[1027] = 0.0;
_CKRRR[1028] = 0.0;
_CKRRR[1029] = 0.0;
_CKRRR[1030] = 0.0;
_CKRRR[1031] = 0.0;
_CKRRR[1032] = 0.0;
_CKRRR[1033] = 0.0;
_CKRRR[1034] = 0.0;
_CKRRR[1035] = 0.0;
_CKRRR[1036] = 0.0;
_CKRRR[1037] = 0.0;
_CKRRR[1038] = 0.0;
_CKRRR[1039] = 0.0;
_CKRRR[1040] = 0.0;
_CKRRR[1041] = 0.0;
_CKRRR[1042] = 0.0;
_CKRRR[1043] = 0.0;
_CKRRR[1044] = 0.0;
_CKRRR[1045] = 0.0;
_CKRRR[1046] = 0.0;
_CKRRR[1047] = 0.0;
_CKRRR[1048] = 0.0;
_CKRRR[1049] = 0.0;
_CKRRR[1050] = 0.0;
_CKRRR[1051] = 0.0;
_CKRRR[1052] = 0.0;
_CKRRR[1053] = 0.0;
_CKRRR[1054] = 0.0;
_CKRRR[1055] = 0.0;
_CKRRR[1056] = 0.0;
_CKRRR[1057] = 0.0;
_CKRRR[1058] = 0.0;
_CKRRR[1059] = 0.0;
_CKRRR[1060] = 0.0;
_CKRRR[1061] = 0.0;
_CKRRR[1062] = 0.0;
_CKRRR[1063] = 0.0;
_CKRRR[1064] = 0.0;
_CKRRR[1065] = 0.0;
_CKRRR[1066] = 0.0;
_CKRRR[1067] = 0.0;
_CKRRR[1068] = 0.0;
_CKRRR[1069] = 0.0;
_CKRRR[1070] = 0.0;
_CKRRR[1071] = 0.0;
_CKRRR[1072] = 0.0;
_CKRRR[1073] = 0.0;
_CKRRR[1074] = 0.0;
_CKRRR[1075] = 0.0;
_CKRRR[1076] = 0.0;
_CKRRR[1077] = 0.0;
_CKRRR[1078] = 0.0;
_CKRRR[1079] = 0.0;
_CKRRR[1080] = 0.0;
_CKRRR[1081] = 0.0;
_CKRRR[1082] = 0.0;
_CKRRR[1083] = 0.0;
_CKRRR[1084] = 0.0;
_CKRRR[1085] = 0.0;
_CKRRR[1086] = 0.0;
_CKRRR[1087] = 0.0;
_CKRRR[1088] = 0.0;
_CKRRR[1089] = 0.0;
_CKRRR[1090] = 0.0;
_CKRRR[1091] = 0.0;
_CKRRR[1092] = 0.0;
_CKRRR[1093] = 0.0;
_CKRRR[1094] = 0.0;
_CKRRR[1095] = 0.0;
_CKRRR[1096] = 0.0;
_CKRRR[1097] = 0.0;
_CKRRR[1098] = 0.0;
_CKRRR[1099] = 0.0;
_CKRRR[1100] = 0.0;
_CKRRR[1101] = 0.0;
_CKRRR[1102] = 0.0;
_CKRRR[1103] = 0.0;
_CKRRR[1104] = 0.0;
_CKRRR[1105] = 0.0;
_CKRRR[1106] = 0.0;
_CKRRR[1107] = 0.0;
_CKRRR[1108] = 0.0;
_CKRRR[1109] = 0.0;
_CKRRR[1110] = 0.0;
_CKRRR[1111] = 0.0;
_CKRRR[1112] = 0.0;
_CKRRR[1113] = 0.0;
_CKRRR[1114] = 0.0;
_CKRRR[1115] = 0.0;
_CKRRR[1116] = 0.0;
_CKRRR[1117] = 0.0;
_CKRRR[1118] = 0.0;
_CKRRR[1119] = 0.0;
_CKRRR[1120] = 0.0;
_CKRRR[1121] = 0.0;
_CKRRR[1122] = 0.0;
_CKRRR[1123] = 0.0;
_CKRRR[1124] = 0.0;
_CKRRR[1125] = 0.0;
_CKRRR[1126] = 0.0;
_CKRRR[1127] = 0.0;
_CKRRR[1128] = 0.0;
_CKRRR[1129] = 0.0;
_CKRRR[1130] = 0.0;
_CKRRR[1131] = 0.0;
_CKRRR[1132] = 0.0;
_CKRRR[1133] = 0.0;
_CKRRR[1134] = 0.0;
_CKRRR[1135] = 0.0;
_CKRRR[1136] = 0.0;
_CKRRR[1137] = 0.0;
_CKRRR[1138] = 0.0;
_CKRRR[1139] = 0.0;
_CKRRR[1140] = 0.0;
_CKRRR[1141] = 0.0;
_CKRRR[1142] = 0.0;
_CKRRR[1143] = 0.0;
_CKRRR[1144] = 0.0;
_CKRRR[1145] = 0.0;
_CKRRR[1146] = 0.0;
_CKRRR[1147] = 0.0;
_CKRRR[1148] = 0.0;
_CKRRR[1149] = 0.0;
_CKRRR[1150] = 0.0;
_CKRRR[1151] = 0.0;
_CKRRR[1152] = 0.0;
_CKRRR[1153] = 0.0;
_CKRRR[1154] = 0.0;
_CKRRR[1155] = 0.0;
_CKRRR[1156] = 0.0;
_CKRRR[1157] = 0.0;
_CKRRR[1158] = 0.0;
_CKRRR[1159] = 0.0;
_CKRRR[1160] = 0.0;
_CKRRR[1161] = 0.0;
_CKRRR[1162] = 0.0;
_CKRRR[1163] = 0.0;
_CKRRR[1164] = 0.0;
_CKRRR[1165] = 0.0;
_CKRRR[1166] = 0.0;
_CKRRR[1167] = 0.0;
_CKRRR[1168] = 0.0;
_CKRRR[1169] = 0.0;
_CKRRR[1170] = 0.0;
_CKRRR[1171] = 0.0;
_CKRRR[1172] = 0.0;
_CKRRR[1173] = 0.0;
_CKRRR[1174] = 0.0;
_CKRRR[1175] = 0.0;
_CKRRR[1176] = 0.0;
_CKRRR[1177] = 0.0;
_CKRRR[1178] = 0.0;
_CKRRR[1179] = 0.0;
_CKRRR[1180] = 0.0;
_CKRRR[1181] = 0.0;
_CKRRR[1182] = 0.0;
_CKRRR[1183] = 0.0;
_CKRRR[1184] = 0.0;
_CKRRR[1185] = 0.0;
_CKRRR[1186] = 0.0;
_CKRRR[1187] = 0.0;
_CKRRR[1188] = 0.0;
_CKRRR[1189] = 0.0;
_CKRRR[1190] = 0.0;
_CKRRR[1191] = 0.0;
_CKRRR[1192] = 0.0;
_CKRRR[1193] = 0.0;
_CKRRR[1194] = 0.0;
_CKRRR[1195] = 0.0;
_CKRRR[1196] = 0.0;
_CKRRR[1197] = 0.0;
_CKRRR[1198] = 0.0;
_CKRRR[1199] = 0.0;
_CKRRR[1200] = 0.0;
_CKRRR[1201] = 0.0;
_CKRRR[1202] = 0.0;
_CKRRR[1203] = 0.0;
_CKRRR[1204] = 0.0;
_CKRRR[1205] = 0.0;
_CKRRR[1206] = 0.0;
_CKRRR[1207] = 0.0;
_CKRRR[1208] = 0.0;
_CKRRR[1209] = 0.0;
_CKRRR[1210] = 0.0;
_CKRRR[1211] = 0.0;
_CKRRR[1212] = 0.0;
_CKRRR[1213] = 0.0;
_CKRRR[1214] = 0.0;
_CKRRR[1215] = 0.0;
_CKRRR[1216] = 0.0;
_CKRRR[1217] = 0.0;
_CKRRR[1218] = 0.0;
_CKRRR[1219] = 0.0;
_CKRRR[1220] = 0.0;
_CKRRR[1221] = 0.0;
_CKRRR[1222] = 0.0;
_CKRRR[1223] = 0.0;
_CKRRR[1224] = 0.0;
_CKRRR[1225] = 0.0;
_CKRRR[1226] = 0.0;
_CKRRR[1227] = 0.0;
_CKRRR[1228] = 0.0;
_CKRRR[1229] = 0.0;
_CKRRR[1230] = 0.0;
_CKRRR[1231] = 0.0;
_CKRRR[1232] = 0.0;
_CKRRR[1233] = 0.0;
_CKRRR[1234] = 0.0;
_CKRRR[1235] = 0.0;
_CKRRR[1236] = 0.0;
_CKRRR[1237] = 0.0;
_CKRRR[1238] = 0.0;
_CKRRR[1239] = 0.0;
_CKRRR[1240] = 0.0;
_CKRRR[1241] = 0.0;
_CKRRR[1242] = 0.0;
_CKRRR[1243] = 0.0;
_CKRRR[1244] = 0.0;
_CKRRR[1245] = 0.0;
_CKRRR[1246] = 0.0;
_CKRRR[1247] = 0.0;
_CKRRR[1248] = 0.0;
_CKRRR[1249] = 0.0;
_CKRRR[1250] = 0.0;
_CKRRR[1251] = 0.0;
_CKRRR[1252] = 0.0;
_CKRRR[1253] = 0.0;
_CKRRR[1254] = 0.0;
_CKRRR[1255] = 0.0;
_CKRRR[1256] = 0.0;
_CKRRR[1257] = 0.0;
_CKRRR[1258] = 0.0;
_CKRRR[1259] = 0.0;
_CKRRR[1260] = 0.0;
_CKRRR[1261] = 0.0;
_CKRRR[1262] = 0.0;
_CKRRR[1263] = 0.0;
_CKRRR[1264] = 0.0;
_CKRRR[1265] = 0.0;
_CKRRR[1266] = 0.0;
_CKRRR[1267] = 0.0;
_CKRRR[1268] = 0.0;
_CKRRR[1269] = 0.0;
_CKRRR[1270] = 0.0;
_CKRRR[1271] = 0.0;
_CKRRR[1272] = 0.0;
_CKRRR[1273] = 0.0;
_CKRRR[1274] = 0.0;
_CKRRR[1275] = 0.0;
_CKRRR[1276] = 0.0;
_CKRRR[1277] = 0.0;
_CKRRR[1278] = 0.0;
_CKRRR[1279] = 0.0;
_CKRRR[1280] = 0.0;
_CKRRR[1281] = 0.0;
_CKRRR[1282] = 0.0;
_CKRRR[1283] = 0.0;
_CKRRR[1284] = 0.0;
_CKRRR[1285] = 0.0;
_CKRRR[1286] = 0.0;
_CKRRR[1287] = 0.0;
_CKRRR[1288] = 0.0;
_CKRRR[1289] = 0.0;
_CKRRR[1290] = 0.0;
_CKRRR[1291] = 0.0;
_CKRRR[1292] = 0.0;
_CKRRR[1293] = 0.0;
_CKRRR[1294] = 0.0;
_CKRRR[1295] = 0.0;
_CKRRR[1296] = 0.0;
_CKRRR[1297] = 0.0;
_CKRRR[1298] = 0.0;
_CKRRR[1299] = 0.0;
_CKRRR[1300] = 0.0;
_CKRRR[1301] = 0.0;
_CKRRR[1302] = 0.0;
_CKRRR[1303] = 0.0;
_CKRRR[1304] = 0.0;
_CKRRR[1305] = 0.0;
_CKRRR[1306] = 0.0;
_CKRRR[1307] = 0.0;
_CKRRR[1308] = 0.0;
_CKRRR[1309] = 0.0;
_CKRRR[1310] = 0.0;
_CKRRR[1311] = 0.0;
_CKRRR[1312] = 0.0;
_CKRRR[1313] = 0.0;
_CKRRR[1314] = 0.0;
_CKRRR[1315] = 0.0;
_CKRRR[1316] = 0.0;
_CKRRR[1317] = 0.0;
_CKRRR[1318] = 0.0;
_CKRRR[1319] = 0.0;
_CKRRR[1320] = 0.0;
_CKRRR[1321] = 0.0;
_CKRRR[1322] = 0.0;
_CKRRR[1323] = 0.0;
_CKRRR[1324] = 0.0;
_CKRRR[1325] = 0.0;
_CKRRR[1326] = 0.0;
_CKRRR[1327] = 0.0;
_CKRRR[1328] = 0.0;
_CKRRR[1329] = 0.0;
_CKRRR[1330] = 0.0;
_CKRRR[1331] = 0.0;
_CKRRR[1332] = 0.0;
_CKRRR[1333] = 0.0;
_CKRRR[1334] = 0.0;
_CKRRR[1335] = 0.0;
_CKRRR[1336] = 0.0;
_CKRRR[1337] = 0.0;
_CKRRR[1338] = 0.0;
_CKRRR[1339] = 0.0;
_CKRRR[1340] = 0.0;
_CKRRR[1341] = 0.0;
_CKRRR[1342] = 0.0;
_CKRRR[1343] = 0.0;
_CKRRR[1344] = 0.0;
_CKRRR[1345] = 0.0;
_CKRRR[1346] = 0.0;
_CKRRR[1347] = 0.0;
_CKRRR[1348] = 0.0;
_CKRRR[1349] = 0.0;
_CKRRR[1350] = 0.0;
_CKRRR[1351] = 0.0;
_CKRRR[1352] = 0.0;
_CKRRR[1353] = 0.0;
_CKRRR[1354] = 0.0;
_CKRRR[1355] = 0.0;
_CKRRR[1356] = 0.0;
_CKRRR[1357] = 0.0;
_CKRRR[1358] = 0.0;
_CKRRR[1359] = 0.0;
_CKRRR[1360] = 0.0;
_CKRRR[1361] = 0.0;
_CKRRR[1362] = 0.0;
_CKRRR[1363] = 0.0;
_CKRRR[1364] = 0.0;
_CKRRR[1365] = 0.0;
_CKRRR[1366] = 0.0;
_CKRRR[1367] = 0.0;
_CKRRR[1368] = 0.0;
_CKRRR[1369] = 0.0;
_CKRRR[1370] = 0.0;
_CKRRR[1371] = 0.0;
_CKRRR[1372] = 0.0;
_CKRRR[1373] = 0.0;
_CKRRR[1374] = 0.0;
_CKRRR[1375] = 0.0;
_CKRRR[1376] = 0.0;
_CKRRR[1377] = 0.0;
_CKRRR[1378] = 0.0;
_CKRRR[1379] = 0.0;
_CKRRR[1380] = 0.0;
_CKRRR[1381] = 0.0;
_CKRRR[1382] = 0.0;
_CKRRR[1383] = 0.0;
_CKRRR[1384] = 0.0;
_CKRRR[1385] = 0.0;
_CKRRR[1386] = 0.0;
_CKRRR[1387] = 0.0;
_CKRRR[1388] = 0.0;
_CKRRR[1389] = 0.0;
_CKRRR[1390] = 0.0;
_CKRRR[1391] = 0.0;
_CKRRR[1392] = 0.0;
_CKRRR[1393] = 0.0;
_CKRRR[1394] = 0.0;
_CKRRR[1395] = 0.0;
_CKRRR[1396] = 0.0;
_CKRRR[1397] = 0.0;
_CKRRR[1398] = 0.0;
_CKRRR[1399] = 0.0;
_CKRRR[1400] = 0.0;
_CKRRR[1401] = 0.0;
_CKRRR[1402] = 0.0;
_CKRRR[1403] = 0.0;
_CKRRR[1404] = 0.0;
_CKRRR[1405] = 0.0;
_CKRRR[1406] = 0.0;
_CKRRR[1407] = 0.0;
_CKRRR[1408] = 0.0;
_CKRRR[1409] = 0.0;
_CKRRR[1410] = 0.0;
_CKRRR[1411] = 0.0;
_CKRRR[1412] = 0.0;
_CKRRR[1413] = 0.0;
_CKRRR[1414] = 0.0;
_CKRRR[1415] = 0.0;
_CKRRR[1416] = 0.0;
_CKRRR[1417] = 0.0;
_CKRRR[1418] = 0.0;
_CKRRR[1419] = 0.0;
_CKRRR[1420] = 0.0;
_CKRRR[1421] = 0.0;
_CKRRR[1422] = 0.0;
_CKRRR[1423] = 0.0;
_CKRRR[1424] = 0.0;
_CKRRR[1425] = 0.0;
_CKRRR[1426] = 0.0;
_CKRRR[1427] = 0.0;
_CKRRR[1428] = 0.0;
_CKRRR[1429] = 0.0;
_CKRRR[1430] = 0.0;
_CKRRR[1431] = 0.0;
_CKRRR[1432] = 0.0;
_CKRRR[1433] = 0.0;
_CKRRR[1434] = 0.0;
_CKRRR[1435] = 0.0;
_CKRRR[1436] = 0.0;
_CKRRR[1437] = 0.0;
_CKRRR[1438] = 0.0;
_CKRRR[1439] = 0.0;
_CKRRR[1440] = 0.0;
_CKRRR[1441] = 0.0;
_CKRRR[1442] = 0.0;
_CKRRR[1443] = 0.0;
_CKRRR[1444] = 0.0;
_CKRRR[1445] = 0.0;
_CKRRR[1446] = 0.0;
_CKRRR[1447] = 0.0;
_CKRRR[1448] = 0.0;
_CKRRR[1449] = 0.0;
_CKRRR[1450] = 0.0;
_CKRRR[1451] = 0.0;
_CKRRR[1452] = 0.0;
_CKRRR[1453] = 0.0;
_CKRRR[1454] = 0.0;
_CKRRR[1455] = 0.0;
_CKRRR[1456] = 0.0;
_CKRRR[1457] = 0.0;
_CKRRR[1458] = 0.0;
_CKRRR[1459] = 0.0;
_CKRRR[1460] = 0.0;
_CKRRR[1461] = 0.0;
_CKRRR[1462] = 0.0;
_CKRRR[1463] = 0.0;
_CKRRR[1464] = 0.0;
_CKRRR[1465] = 0.0;
_CKRRR[1466] = 0.0;
_CKRRR[1467] = 0.0;
_CKRRR[1468] = 0.0;
_CKRRR[1469] = 0.0;
_CKRRR[1470] = 0.0;
_CKRRR[1471] = 0.0;
_CKRRR[1472] = 0.0;
_CKRRR[1473] = 0.0;
_CKRRR[1474] = 0.0;
_CKRRR[1475] = 0.0;
_CKRRR[1476] = 0.0;
_CKRRR[1477] = 0.0;
_CKRRR[1478] = 0.0;
_CKRRR[1479] = 0.0;
_CKRRR[1480] = 0.0;
_CKRRR[1481] = 0.0;
_CKRRR[1482] = 0.0;
_CKRRR[1483] = 0.0;
_CKRRR[1484] = 0.0;
_CKRRR[1485] = 0.0;
_CKRRR[1486] = 0.0;
_CKRRR[1487] = 0.0;
_CKRRR[1488] = 0.0;
_CKRRR[1489] = 0.0;
_CKRRR[1490] = 0.0;
_CKRRR[1491] = 0.0;
_CKRRR[1492] = 0.0;
_CKRRR[1493] = 0.0;
_CKRRR[1494] = 0.0;
_CKRRR[1495] = 0.0;
_CKRRR[1496] = 0.0;
_CKRRR[1497] = 0.0;
_CKRRR[1498] = 0.0;
_CKRRR[1499] = 0.0;
_CKRRR[1500] = 0.0;
_CKRRR[1501] = 0.0;
_CKRRR[1502] = 0.0;
_CKRRR[1503] = 0.0;
_CKRRR[1504] = 0.0;
_CKRRR[1505] = 0.0;
_CKRRR[1506] = 0.0;
_CKRRR[1507] = 0.0;
_CKRRR[1508] = 0.0;
_CKRRR[1509] = 0.0;
_CKRRR[1510] = 0.0;
_CKRRR[1511] = 0.0;
_CKRRR[1512] = 0.0;
_CKRRR[1513] = 0.0;
_CKRRR[1514] = 0.0;
_CKRRR[1515] = 0.0;
_CKRRR[1516] = 0.0;
_CKRRR[1517] = 0.0;
_CKRRR[1518] = 0.0;
_CKRRR[1519] = 0.0;
_CKRRR[1520] = 0.0;
_CKRRR[1521] = 0.0;
_CKRRR[1522] = 0.0;
_CKRRR[1523] = 0.0;
_CKRRR[1524] = 0.0;
_CKRRR[1525] = 0.0;
_CKRRR[1526] = 0.0;
_CKRRR[1527] = 0.0;
_CKRRR[1528] = 0.0;
_CKRRR[1529] = 0.0;
_CKRRR[1530] = 0.0;
_CKRRR[1531] = 0.0;
_CKRRR[1532] = 0.0;
_CKRRR[1533] = 0.0;
_CKRRR[1534] = 0.0;
_CKRRR[1535] = 0.0;
_CKRRR[1536] = 0.0;
_CKRRR[1537] = 0.0;
_CKRRR[1538] = 0.0;
_CKRRR[1539] = 0.0;
_CKRRR[1540] = 0.0;
_CKRRR[1541] = 0.0;
_CKRRR[1542] = 0.0;
_CKRRR[1543] = 0.0;
_CKRRR[1544] = 0.0;
_CKRRR[1545] = 0.0;
_CKRRR[1546] = 0.0;
_CKRRR[1547] = 0.0;
_CKRRR[1548] = 0.0;
_CKRRR[1549] = 0.0;
_CKRRR[1550] = 0.0;
_CKRRR[1551] = 0.0;
_CKRRR[1552] = 0.0;
_CKRRR[1553] = 0.0;
_CKRRR[1554] = 0.0;
_CKRRR[1555] = 0.0;
_CKRRR[1556] = 0.0;
_CKRRR[1557] = 0.0;
_CKRRR[1558] = 0.0;
_CKRRR[1559] = 0.0;
_CKRRR[1560] = 0.0;
_CKRRR[1561] = 0.0;
_CKRRR[1562] = 0.0;
_CKRRR[1563] = 0.0;
_CKRRR[1564] = 0.0;
_CKRRR[1565] = 0.0;
_CKRRR[1566] = 0.0;
_CKRRR[1567] = 0.0;
_CKRRR[1568] = 0.0;
_CKRRR[1569] = 0.0;
_CKRRR[1570] = 0.0;
_CKRRR[1571] = 0.0;
_CKRRR[1572] = 0.0;
_CKRRR[1573] = 0.0;
_CKRRR[1574] = 0.0;
_CKRRR[1575] = 0.0;
_CKRRR[1576] = 0.0;
_CKRRR[1577] = 0.0;
_CKRRR[1578] = 0.0;
_CKRRR[1579] = 0.0;
_CKRRR[1580] = 0.0;
_CKRRR[1581] = 0.0;
_CKRRR[1582] = 0.0;
_CKRRR[1583] = 0.0;
_CKRRR[1584] = 0.0;
_CKRRR[1585] = 0.0;
_CKRRR[1586] = 0.0;
_CKRRR[1587] = 0.0;
_CKRRR[1588] = 0.0;
_CKRRR[1589] = 0.0;
_CKRRR[1590] = 0.0;
_CKRRR[1591] = 0.0;
_CKRRR[1592] = 0.0;
_CKRRR[1593] = 0.0;
_CKRRR[1594] = 0.0;
_CKRRR[1595] = 0.0;
_CKRRR[1596] = 0.0;
_CKRRR[1597] = 0.0;
_CKRRR[1598] = 0.0;
_CKRRR[1599] = 0.0;
_CKRRR[1600] = 0.0;
_CKRRR[1601] = 0.0;
_CKRRR[1602] = 0.0;
_CKRRR[1603] = 0.0;
_CKRRR[1604] = 0.0;
_CKRRR[1605] = 0.0;
_CKRRR[1606] = 0.0;
_CKRRR[1607] = 0.0;
_CKRRR[1608] = 0.0;
_CKRRR[1609] = 0.0;
_CKRRR[1610] = 0.0;
_CKRRR[1611] = 0.0;
_CKRRR[1612] = 0.0;
_CKRRR[1613] = 0.0;
_CKRRR[1614] = 0.0;
_CKRRR[1615] = 0.0;
_CKRRR[1616] = 0.0;
_CKRRR[1617] = 0.0;
_CKRRR[1618] = 0.0;
_CKRRR[1619] = 0.0;
_CKRRR[1620] = 0.0;
_CKRRR[1621] = 0.0;
_CKRRR[1622] = 0.0;
_CKRRR[1623] = 0.0;
_CKRRR[1624] = 0.0;
_CKRRR[1625] = 0.0;
_CKRRR[1626] = 0.0;
_CKRRR[1627] = 0.0;
_CKRRR[1628] = 0.0;
_CKRRR[1629] = 0.0;
_CKRRR[1630] = 0.0;
_CKRRR[1631] = 0.0;
_CKRRR[1632] = 0.0;
_CKRRR[1633] = 0.0;
_CKRRR[1634] = 0.0;
_CKRRR[1635] = 0.0;
_CKRRR[1636] = 0.0;
_CKRRR[1637] = 0.0;
_CKRRR[1638] = 0.0;
_CKRRR[1639] = 0.0;
_CKRRR[1640] = 0.0;
_CKRRR[1641] = 0.0;
_CKRRR[1642] = 0.0;
_CKRRR[1643] = 0.0;
_CKRRR[1644] = 0.0;
_CKRRR[1645] = 0.0;
_CKRRR[1646] = 0.0;
_CKRRR[1647] = 0.0;
_CKRRR[1648] = 0.0;
_CKRRR[1649] = 0.0;
_CKRRR[1650] = 0.0;
_CKRRR[1651] = 0.0;
_CKRRR[1652] = 0.0;
_CKRRR[1653] = 0.0;
_CKRRR[1654] = 0.0;
_CKRRR[1655] = 0.0;
_CKRRR[1656] = 0.0;
_CKRRR[1657] = 0.0;
_CKRRR[1658] = 0.0;
_CKRRR[1659] = 0.0;
_CKRRR[1660] = 0.0;
_CKRRR[1661] = 0.0;
_CKRRR[1662] = 0.0;
_CKRRR[1663] = 0.0;
_CKRRR[1664] = 0.0;
_CKRRR[1665] = 0.0;
_CKRRR[1666] = 0.0;
_CKRRR[1667] = 0.0;
_CKRRR[1668] = 0.0;
_CKRRR[1669] = 0.0;
_CKRRR[1670] = 0.0;
_CKRRR[1671] = 0.0;
_CKRRR[1672] = 0.0;
_CKRRR[1673] = 0.0;
_CKRRR[1674] = 0.0;
_CKRRR[1675] = 0.0;
_CKRRR[1676] = 0.0;
_CKRRR[1677] = 0.0;
_CKRRR[1678] = 0.0;
_CKRRR[1679] = 0.0;
_CKRRR[1680] = 0.0;
_CKRRR[1681] = 0.0;
_CKRRR[1682] = 0.0;
_CKRRR[1683] = 0.0;
_CKRRR[1684] = 0.0;
_CKRRR[1685] = 0.0;
_CKRRR[1686] = 0.0;
_CKRRR[1687] = 0.0;
_CKRRR[1688] = 0.0;
_CKRRR[1689] = 0.0;
_CKRRR[1690] = 0.0;
_CKRRR[1691] = 0.0;
_CKRRR[1692] = 0.0;
_CKRRR[1693] = 0.0;
_CKRRR[1694] = 0.0;
_CKRRR[1695] = 0.0;
_CKRRR[1696] = 0.0;
_CKRRR[1697] = 0.0;
_CKRRR[1698] = 0.0;
_CKRRR[1699] = 0.0;
_CKRRR[1700] = 0.0;
_CKRRR[1701] = 0.0;
_CKRRR[1702] = 0.0;
_CKRRR[1703] = 0.0;
_CKRRR[1704] = 0.0;
_CKRRR[1705] = 0.0;
_CKRRR[1706] = 0.0;
_CKRRR[1707] = 0.0;
_CKRRR[1708] = 0.0;
_CKRRR[1709] = 0.0;
_CKRRR[1710] = 0.0;
_CKRRR[1711] = 0.0;
_CKRRR[1712] = 0.0;
_CKRRR[1713] = 0.0;
_CKRRR[1714] = 0.0;
_CKRRR[1715] = 0.0;
_CKRRR[1716] = 0.0;
_CKRRR[1717] = 0.0;
_CKRRR[1718] = 0.0;
_CKRRR[1719] = 0.0;
_CKRRR[1720] = 0.0;
_CKRRR[1721] = 0.0;
_CKRRR[1722] = 0.0;
_CKRRR[1723] = 0.0;
_CKRRR[1724] = 0.0;
_CKRRR[1725] = 0.0;
_CKRRR[1726] = 0.0;
_CKRRR[1727] = 0.0;
_CKRRR[1728] = 0.0;
_CKRRR[1729] = 0.0;
_CKRRR[1730] = 0.0;
_CKRRR[1731] = 0.0;
_CKRRR[1732] = 0.0;
_CKRRR[1733] = 0.0;
_CKRRR[1734] = 0.0;
_CKRRR[1735] = 0.0;
_CKRRR[1736] = 0.0;
_CKRRR[1737] = 0.0;
_CKRRR[1738] = 0.0;
_CKRRR[1739] = 0.0;
_CKRRR[1740] = 0.0;
_CKRRR[1741] = 0.0;
_CKRRR[1742] = 0.0;
_CKRRR[1743] = 0.0;
_CKRRR[1744] = 0.0;
_CKRRR[1745] = 0.0;
_CKRRR[1746] = 0.0;
_CKRRR[1747] = 0.0;
_CKRRR[1748] = 0.0;
_CKRRR[1749] = 0.0;
_CKRRR[1750] = 0.0;
_CKRRR[1751] = 0.0;
_CKRRR[1752] = 0.0;
_CKRRR[1753] = 0.0;
_CKRRR[1754] = 0.0;
_CKRRR[1755] = 0.0;
_CKRRR[1756] = 0.0;
_CKRRR[1757] = 0.0;
_CKRRR[1758] = 0.0;
_CKRRR[1759] = 0.0;
_CKRRR[1760] = 0.0;
_CKRRR[1761] = 0.0;
_CKRRR[1762] = 0.0;
_CKRRR[1763] = 0.0;
_CKRRR[1764] = 0.0;
_CKRRR[1765] = 0.0;
_CKRRR[1766] = 0.0;
_CKRRR[1767] = 0.0;
_CKRRR[1768] = 0.0;
_CKRRR[1769] = 0.0;
_CKRRR[1770] = 0.0;
_CKRRR[1771] = 0.0;
_CKRRR[1772] = 0.0;
_CKRRR[1773] = 0.0;
_CKRRR[1774] = 0.0;
_CKRRR[1775] = 0.0;
_CKRRR[1776] = 0.0;
_CKRRR[1777] = 0.0;
_CKRRR[1778] = 0.0;
_CKRRR[1779] = 0.0;
_CKRRR[1780] = 0.0;
_CKRRR[1781] = 0.0;
_CKRRR[1782] = 0.0;
_CKRRR[1783] = 0.0;
_CKRRR[1784] = 0.0;
_CKRRR[1785] = 0.0;
_CKRRR[1786] = 0.0;
_CKRRR[1787] = 0.0;
_CKRRR[1788] = 0.0;
_CKRRR[1789] = 0.0;
_CKRRR[1790] = 0.0;
_CKRRR[1791] = 0.0;
_CKRRR[1792] = 0.0;
_CKRRR[1793] = 0.0;
_CKRRR[1794] = 0.0;
_CKRRR[1795] = 0.0;
_CKRRR[1796] = 0.0;
_CKRRR[1797] = 0.0;
_CKRRR[1798] = 0.0;
_CKRRR[1799] = 0.0;
_CKRRR[1800] = 0.0;
_CKRRR[1801] = 0.0;
_CKRRR[1802] = 0.0;
_CKRRR[1803] = 0.0;
_CKRRR[1804] = 0.0;
_CKRRR[1805] = 0.0;
_CKRRR[1806] = 0.0;
_CKRRR[1807] = 0.0;
_CKRRR[1808] = 0.0;
_CKRRR[1809] = 0.0;
_CKRRR[1810] = 0.0;
_CKRRR[1811] = 0.0;
_CKRRR[1812] = 0.0;
_CKRRR[1813] = 0.0;
_CKRRR[1814] = 0.0;
_CKRRR[1815] = 0.0;
_CKRRR[1816] = 0.0;
_CKRRR[1817] = 0.0;
_CKRRR[1818] = 0.0;
_CKRRR[1819] = 0.0;
_CKRRR[1820] = 0.0;
_CKRRR[1821] = 0.0;
_CKRRR[1822] = 0.0;
_CKRRR[1823] = 0.0;
_CKRRR[1824] = 0.0;
_CKRRR[1825] = 0.0;
_CKRRR[1826] = 0.0;
_CKRRR[1827] = 0.0;
_CKRRR[1828] = 0.0;
_CKRRR[1829] = 0.0;
_CKRRR[1830] = 0.0;
_CKRRR[1831] = 0.0;
_CKRRR[1832] = 0.0;
_CKRRR[1833] = 0.0;
_CKRRR[1834] = 0.0;
_CKRRR[1835] = 0.0;
_CKRRR[1836] = 0.0;
_CKRRR[1837] = 0.0;
_CKRRR[1838] = 0.0;
_CKRRR[1839] = 0.0;
_CKRRR[1840] = 0.0;
_CKRRR[1841] = 0.0;
_CKRRR[1842] = 0.0;
_CKRRR[1843] = 0.0;
_CKRRR[1844] = 0.0;
_CKRRR[1845] = 0.0;
_CKRRR[1846] = 0.0;
_CKRRR[1847] = 0.0;
_CKRRR[1848] = 0.0;
_CKRRR[1849] = 0.0;
_CKRRR[1850] = 0.0;
_CKRRR[1851] = 0.0;
_CKRRR[1852] = 0.0;
_CKRRR[1853] = 0.0;
_CKRRR[1854] = 0.0;
_CKRRR[1855] = 0.0;
_CKRRR[1856] = 0.0;
_CKRRR[1857] = 0.0;
_CKRRR[1858] = 0.0;
_CKRRR[1859] = 0.0;
_CKRRR[1860] = 0.0;
_CKRRR[1861] = 0.0;
_CKRRR[1862] = 0.0;
_CKRRR[1863] = 0.0;
_CKRRR[1864] = 0.0;
_CKRRR[1865] = 0.0;
_CKRRR[1866] = 0.0;
_CKRRR[1867] = 0.0;
_CKRRR[1868] = 0.0;
_CKRRR[1869] = 0.0;
_CKRRR[1870] = 0.0;
_CKRRR[1871] = 0.0;
_CKRRR[1872] = 0.0;
_CKRRR[1873] = 0.0;
_CKRRR[1874] = 0.0;
_CKRRR[1875] = 0.0;
_CKRRR[1876] = 0.0;
_CKRRR[1877] = 0.0;
_CKRRR[1878] = 0.0;
_CKRRR[1879] = 0.0;
_CKRRR[1880] = 0.0;
_CKRRR[1881] = 0.0;
_CKRRR[1882] = 0.0;
_CKRRR[1883] = 0.0;
_CKRRR[1884] = 0.0;
_CKRRR[1885] = 0.0;
_CKRRR[1886] = 0.0;
_CKRRR[1887] = 0.0;
_CKRRR[1888] = 0.0;
_CKRRR[1889] = 0.0;
_CKRRR[1890] = 0.0;
_CKRRR[1891] = 0.0;
_CKRRR[1892] = 0.0;
_CKRRR[1893] = 0.0;
_CKRRR[1894] = 0.0;
_CKRRR[1895] = 0.0;
_CKRRR[1896] = 0.0;
_CKRRR[1897] = 0.0;
_CKRRR[1898] = 0.0;
_CKRRR[1899] = 0.0;
_CKRRR[1900] = 0.0;
_CKRRR[1901] = 0.0;
_CKRRR[1902] = 0.0;
_CKRRR[1903] = 0.0;
_CKRRR[1904] = 0.0;
_CKRRR[1905] = 0.0;
_CKRRR[1906] = 0.0;
_CKRRR[1907] = 0.0;
_CKRRR[1908] = 0.0;
_CKRRR[1909] = 0.0;
_CKRRR[1910] = 0.0;
_CKRRR[1911] = 0.0;
_CKRRR[1912] = 0.0;
_CKRRR[1913] = 0.0;
_CKRRR[1914] = 0.0;
_CKRRR[1915] = 0.0;
_CKRRR[1916] = 0.0;
_CKRRR[1917] = 0.0;
_CKRRR[1918] = 0.0;
_CKRRR[1919] = 0.0;
_CKRRR[1920] = 0.0;
_CKRRR[1921] = 0.0;
_CKRRR[1922] = 0.0;
_CKRRR[1923] = 0.0;
_CKRRR[1924] = 0.0;
_CKRRR[1925] = 0.0;
_CKRRR[1926] = 0.0;
_CKRRR[1927] = 0.0;
_CKRRR[1928] = 0.0;
_CKRRR[1929] = 0.0;
_CKRRR[1930] = 0.0;
_CKRRR[1931] = 0.0;
_CKRRR[1932] = 0.0;
_CKRRR[1933] = 0.0;
_CKRRR[1934] = 0.0;
_CKRRR[1935] = 0.0;

return _CKRRR;
}
