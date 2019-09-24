function Phi_q_ = Phi_q(q,qaux,time,param)

xWAG = q( 1 ); 
yWAG = q( 2 ); 
zWAG = q( 3 ); 
aWAG = q( 4 ); 
bWAG = q( 5 ); 
cWAG = q( 6 ); 
cRSLD = q( 7 ); 
cFSLD = q( 8 ); 
zRBOG = q( 9 ); 
aRBOG = q( 10 ); 
bRBOG = q( 11 ); 
zFBOG = q( 12 ); 
aFBOG = q( 13 ); 
bFBOG = q( 14 ); 
zRWHSF = q( 15 ); 
aRWHSF = q( 16 ); 
bRWHSF = q( 17 ); 
zRWHSR = q( 18 ); 
aRWHSR = q( 19 ); 
bRWHSR = q( 20 ); 
zFWHSF = q( 21 ); 
aFWHSF = q( 22 ); 
bFWHSF = q( 23 ); 
zFWHSR = q( 24 ); 
aFWHSR = q( 25 ); 
bFWHSR = q( 26 ); 
bRAXBFL = q( 27 ); 
bRAXBFR = q( 28 ); 
bRAXBRL = q( 29 ); 
bRAXBRR = q( 30 ); 
bFAXBFL = q( 31 ); 
bFAXBFR = q( 32 ); 
bFAXBRL = q( 33 ); 
bFAXBRR = q( 34 ); 
xRMOTF = q( 35 ); 
yRMOTF = q( 36 ); 
zRMOTF = q( 37 ); 
bRMOTF = q( 38 ); 
xRMOTR = q( 39 ); 
yRMOTR = q( 40 ); 
zRMOTR = q( 41 ); 
bRMOTR = q( 42 ); 
bRROTF = q( 43 ); 
bRROTR = q( 44 ); 

thetaW_RFR = qaux( 1 ); 
uW_RFR = qaux( 2 ); 
uR_RFR = qaux( 3 ); 
xR_RFR = qaux( 4 ); 
thetaW_RFL = qaux( 5 ); 
uW_RFL = qaux( 6 ); 
uR_RFL = qaux( 7 ); 
xR_RFL = qaux( 8 ); 
thetaW_RRR = qaux( 9 ); 
uW_RRR = qaux( 10 ); 
uR_RRR = qaux( 11 ); 
xR_RRR = qaux( 12 ); 
thetaW_RRL = qaux( 13 ); 
uW_RRL = qaux( 14 ); 
uR_RRL = qaux( 15 ); 
xR_RRL = qaux( 16 ); 
thetaW_FFR = qaux( 17 ); 
uW_FFR = qaux( 18 ); 
uR_FFR = qaux( 19 ); 
xR_FFR = qaux( 20 ); 
thetaW_FFL = qaux( 21 ); 
uW_FFL = qaux( 22 ); 
uR_FFL = qaux( 23 ); 
xR_FFL = qaux( 24 ); 
thetaW_FRR = qaux( 25 ); 
uW_FRR = qaux( 26 ); 
uR_FRR = qaux( 27 ); 
xR_FRR = qaux( 28 ); 
thetaW_FRL = qaux( 29 ); 
uW_FRL = qaux( 30 ); 
uR_FRL = qaux( 31 ); 
xR_FRL = qaux( 32 ); 

t= time ;

g = param( 1 ); 
L_OBOG_OAXBy = param( 2 ); 
L_OBOG_OAXBz = param( 3 ); 
L_OBOG_OSUSPy = param( 4 ); 
L_OBOG_OSUSPx = param( 5 ); 
L_OBOG_OSUSPz = param( 6 ); 
L_OBOG_OWHS = param( 7 ); 
L_OBOG_P1BOG = param( 8 ); 
L_MOT = param( 9 ); 
L_GEAR = param( 10 ); 
L_AXB1 = param( 11 ); 
L_AXB2 = param( 12 ); 
L_SUSP = param( 13 ); 
L_WHS = param( 14 ); 
L_RAIL = param( 15 ); 
L_WAG = param( 16 ); 
L_SUSPBEAM1 = param( 17 ); 
L_SUSPBEAM2 = param( 18 ); 
L_SLDx = param( 19 ); 
L_SLDy = param( 20 ); 
b_pend = param( 21 ); 
a_pend = param( 22 ); 
L0_1 = param( 23 ); 
L0_2 = param( 24 ); 
m_WAG = param( 25 ); 
I_WAGx = param( 26 ); 
I_WAGy = param( 27 ); 
I_WAGz = param( 28 ); 
xCGWAG = param( 29 ); 
yCGWAG = param( 30 ); 
zCGWAG = param( 31 ); 
G_BOGz = param( 32 ); 
m_BOG = param( 33 ); 
I_BOGx = param( 34 ); 
I_BOGy = param( 35 ); 
I_BOGz = param( 36 ); 
m_MOT = param( 37 ); 
I_MOTx = param( 38 ); 
I_MOTy = param( 39 ); 
I_MOTz = param( 40 ); 
m_ROT = param( 41 ); 
I_ROTx = param( 42 ); 
I_ROTy = param( 43 ); 
I_ROTz = param( 44 ); 
m_WHS = param( 45 ); 
I_WHSx = param( 46 ); 
I_WHSy = param( 47 ); 
I_WHSz = param( 48 ); 
I_CORy = param( 49 ); 
m_AXB = param( 50 ); 
I_AXBx = param( 51 ); 
I_AXBy = param( 52 ); 
I_AXBz = param( 53 ); 
m_SLD = param( 54 ); 
I_SLDx = param( 55 ); 
I_SLDy = param( 56 ); 
I_SLDz = param( 57 ); 
K_SSl = param( 58 ); 
C_SSl = param( 59 ); 
C_SSr = param( 60 ); 
K_SSr = param( 61 ); 
Kgear = param( 62 ); 
Cgear = param( 63 ); 
alpha_gear = param( 64 ); 
zROT = param( 65 ); 
zWHS = param( 66 ); 
K_S1 = param( 67 ); 
C_S1 = param( 68 ); 
K_S2 = param( 69 ); 
C_S2 = param( 70 ); 
aW_RFR = param( 71 ); 
bW_RFR = param( 72 ); 
cW_RFR = param( 73 ); 
dW_RFR = param( 74 ); 
lW_RFR = param( 75 ); 
aR_RFR = param( 76 ); 
bR_RFR = param( 77 ); 
cR_RFR = param( 78 ); 
dR_RFR = param( 79 ); 
lR_RFR = param( 80 ); 
RFRas = param( 81 ); 
RFRbs = param( 82 ); 
RFRcs = param( 83 ); 
RFRds = param( 84 ); 
RFRes = param( 85 ); 
RFRfs = param( 86 ); 
RFRstas = param( 87 ); 
RFRends = param( 88 ); 
irrRFRz = param( 89 ); 
aW_RFL = param( 90 ); 
bW_RFL = param( 91 ); 
cW_RFL = param( 92 ); 
dW_RFL = param( 93 ); 
lW_RFL = param( 94 ); 
aR_RFL = param( 95 ); 
bR_RFL = param( 96 ); 
cR_RFL = param( 97 ); 
dR_RFL = param( 98 ); 
lR_RFL = param( 99 ); 
RFLas = param( 100 ); 
RFLbs = param( 101 ); 
RFLcs = param( 102 ); 
RFLds = param( 103 ); 
RFLes = param( 104 ); 
RFLfs = param( 105 ); 
RFLstas = param( 106 ); 
RFLends = param( 107 ); 
irrRFLz = param( 108 ); 
aW_RRR = param( 109 ); 
bW_RRR = param( 110 ); 
cW_RRR = param( 111 ); 
dW_RRR = param( 112 ); 
lW_RRR = param( 113 ); 
aR_RRR = param( 114 ); 
bR_RRR = param( 115 ); 
cR_RRR = param( 116 ); 
dR_RRR = param( 117 ); 
lR_RRR = param( 118 ); 
RRRas = param( 119 ); 
RRRbs = param( 120 ); 
RRRcs = param( 121 ); 
RRRds = param( 122 ); 
RRRes = param( 123 ); 
RRRfs = param( 124 ); 
RRRstas = param( 125 ); 
RRRends = param( 126 ); 
irrRRRz = param( 127 ); 
aW_RRL = param( 128 ); 
bW_RRL = param( 129 ); 
cW_RRL = param( 130 ); 
dW_RRL = param( 131 ); 
lW_RRL = param( 132 ); 
aR_RRL = param( 133 ); 
bR_RRL = param( 134 ); 
cR_RRL = param( 135 ); 
dR_RRL = param( 136 ); 
lR_RRL = param( 137 ); 
RRLas = param( 138 ); 
RRLbs = param( 139 ); 
RRLcs = param( 140 ); 
RRLds = param( 141 ); 
RRLes = param( 142 ); 
RRLfs = param( 143 ); 
RRLstas = param( 144 ); 
RRLends = param( 145 ); 
irrRRLz = param( 146 ); 
aW_FFR = param( 147 ); 
bW_FFR = param( 148 ); 
cW_FFR = param( 149 ); 
dW_FFR = param( 150 ); 
lW_FFR = param( 151 ); 
aR_FFR = param( 152 ); 
bR_FFR = param( 153 ); 
cR_FFR = param( 154 ); 
dR_FFR = param( 155 ); 
lR_FFR = param( 156 ); 
FFRas = param( 157 ); 
FFRbs = param( 158 ); 
FFRcs = param( 159 ); 
FFRds = param( 160 ); 
FFRes = param( 161 ); 
FFRfs = param( 162 ); 
FFRstas = param( 163 ); 
FFRends = param( 164 ); 
irrFFRz = param( 165 ); 
aW_FFL = param( 166 ); 
bW_FFL = param( 167 ); 
cW_FFL = param( 168 ); 
dW_FFL = param( 169 ); 
lW_FFL = param( 170 ); 
aR_FFL = param( 171 ); 
bR_FFL = param( 172 ); 
cR_FFL = param( 173 ); 
dR_FFL = param( 174 ); 
lR_FFL = param( 175 ); 
FFLas = param( 176 ); 
FFLbs = param( 177 ); 
FFLcs = param( 178 ); 
FFLds = param( 179 ); 
FFLes = param( 180 ); 
FFLfs = param( 181 ); 
FFLstas = param( 182 ); 
FFLends = param( 183 ); 
irrFFLz = param( 184 ); 
aW_FRR = param( 185 ); 
bW_FRR = param( 186 ); 
cW_FRR = param( 187 ); 
dW_FRR = param( 188 ); 
lW_FRR = param( 189 ); 
aR_FRR = param( 190 ); 
bR_FRR = param( 191 ); 
cR_FRR = param( 192 ); 
dR_FRR = param( 193 ); 
lR_FRR = param( 194 ); 
FRRas = param( 195 ); 
FRRbs = param( 196 ); 
FRRcs = param( 197 ); 
FRRds = param( 198 ); 
FRRes = param( 199 ); 
FRRfs = param( 200 ); 
FRRstas = param( 201 ); 
FRRends = param( 202 ); 
irrFRRz = param( 203 ); 
aW_FRL = param( 204 ); 
bW_FRL = param( 205 ); 
cW_FRL = param( 206 ); 
dW_FRL = param( 207 ); 
lW_FRL = param( 208 ); 
aR_FRL = param( 209 ); 
bR_FRL = param( 210 ); 
cR_FRL = param( 211 ); 
dR_FRL = param( 212 ); 
lR_FRL = param( 213 ); 
FRLas = param( 214 ); 
FRLbs = param( 215 ); 
FRLcs = param( 216 ); 
FRLds = param( 217 ); 
FRLes = param( 218 ); 
FRLfs = param( 219 ); 
FRLstas = param( 220 ); 
FRLends = param( 221 ); 
irrFRLz = param( 222 ); 
E_elastic = param( 223 ); 
nu_poisson = param( 224 ); 
G_elastic = param( 225 ); 
aRFR = param( 226 ); 
bRFR = param( 227 ); 
C11RFR = param( 228 ); 
C22RFR = param( 229 ); 
C23RFR = param( 230 ); 
C33RFR = param( 231 ); 
aRFL = param( 232 ); 
bRFL = param( 233 ); 
C11RFL = param( 234 ); 
C22RFL = param( 235 ); 
C23RFL = param( 236 ); 
C33RFL = param( 237 ); 
aRRR = param( 238 ); 
bRRR = param( 239 ); 
C11RRR = param( 240 ); 
C22RRR = param( 241 ); 
C23RRR = param( 242 ); 
C33RRR = param( 243 ); 
aRRL = param( 244 ); 
bRRL = param( 245 ); 
C11RRL = param( 246 ); 
C22RRL = param( 247 ); 
C23RRL = param( 248 ); 
C33RRL = param( 249 ); 
aFFR = param( 250 ); 
bFFR = param( 251 ); 
C11FFR = param( 252 ); 
C22FFR = param( 253 ); 
C23FFR = param( 254 ); 
C33FFR = param( 255 ); 
aFFL = param( 256 ); 
bFFL = param( 257 ); 
C11FFL = param( 258 ); 
C22FFL = param( 259 ); 
C23FFL = param( 260 ); 
C33FFL = param( 261 ); 
aFRR = param( 262 ); 
bFRR = param( 263 ); 
C11FRR = param( 264 ); 
C22FRR = param( 265 ); 
C23FRR = param( 266 ); 
C33FRR = param( 267 ); 
aFRL = param( 268 ); 
bFRL = param( 269 ); 
C11FRL = param( 270 ); 
C22FRL = param( 271 ); 
C23FRL = param( 272 ); 
C33FRL = param( 273 ); 
epsiRFR = param( 274 ); 
epsiRFL = param( 275 ); 
epsiRRR = param( 276 ); 
epsiRRL = param( 277 ); 
epsiFFR = param( 278 ); 
epsiFFL = param( 279 ); 
epsiFRR = param( 280 ); 
epsiFRL = param( 281 ); 


Phi_q_ = [];

%endfunction