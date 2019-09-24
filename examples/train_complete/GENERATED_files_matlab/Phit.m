function Phit_ = Phit(q,qaux,time,param)

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

atom1818 = (RFRstas-RFRends)^(-1);
atom1831 = -RFRas*atom1818;
atom1820 = atom1818*(RFRstas-xR_RFR);
atom1822 = atom1820*RFRas+RFRbs;
atom1834 = -atom1822*atom1818+atom1831*atom1820;
atom1824 = atom1820*atom1822+RFRcs;
atom1837 = -atom1818*atom1824+atom1820*atom1834;
atom1826 = RFRds+atom1820*atom1824;
atom1840 = atom1820*atom1837-atom1818*atom1826;
atom1828 = atom1820*atom1826+RFRes;
atom1857 = -atom1834*atom1818;
atom1860 = -atom1818*atom1837;
atom1864 = -atom1818*atom1840;
atom1843 = atom1820*atom1840-atom1818*atom1828;
atom1867 = 2*(atom1860+atom1820*(atom1857-atom1831*atom1820*atom1818))*atom1820+2*atom1864;
atom1845 = 1+atom1843^2;
atom1846 = sqrt(atom1845);
atom1872 = -atom1846^(-2)*atom1843*atom1867*atom1845^(-1/2);
atom1847 = atom1846^(-1);
atom1876 = 1+(0.5)*atom1867*L_RAIL*atom1847+(0.5)*atom1872*atom1843*L_RAIL;
atom1878 = -(0.5)*atom1872*L_RAIL+atom1843;
atom1914 = atom1876^2;
atom1922 = (atom1914+atom1878^2)^(-1/2);
atom1704 = uW_RFR-lW_RFR;
atom1710 = ((bW_RFR+aW_RFR*atom1704)*atom1704+cW_RFR)*atom1704+dW_RFR;
atom1703 = sin(thetaW_RFR);
atom1177 = sin(cWAG);
atom1173 = sin(bWAG);
atom1175 = sin(aWAG);
atom1176 = cos(cWAG);
atom1172 = cos(bWAG);
atom1181 = -atom1175*atom1176;
atom1193 = atom1177*atom1173+atom1172*atom1181;
atom865 = sin(bRBOG);
atom1174 = cos(aWAG);
atom1180 = atom1176*atom1174;
atom1210 = sin(cRSLD);
atom1190 = -atom1181*atom1173+atom1172*atom1177;
atom1209 = cos(cRSLD);
atom864 = cos(bRBOG);
atom1219 = atom1180*atom1210+atom1190*atom1209;
atom1711 = -atom1710*atom1703;
atom1237 = atom864*atom1219-atom1193*atom865;
atom862 = cos(aRBOG);
atom1222 = atom1180*atom1209-atom1190*atom1210;
atom863 = sin(aRBOG);
atom1240 = atom1219*atom865+atom1193*atom864;
atom1255 = atom862*atom1222+atom863*atom1240;
atom30 = cos(aRWHSF);
atom1258 = -atom863*atom1222+atom862*atom1240;
atom31 = sin(aRWHSF);
atom1279 = atom1258*atom31+atom1255*atom30;
atom1712 = cos(thetaW_RFR);
atom1282 = atom1258*atom30-atom1255*atom31;
atom1713 = atom1710*atom1712;
atom1702 = -(0.5)*L_WHS;
atom868 = atom863*atom864;
atom1714 = atom30*atom1702;
atom1726 = atom868*atom1714;
atom1725 = -L_OBOG_OWHS*atom865;
atom1715 = atom1702*atom31;
atom1716 = atom1715+zRWHSF;
atom869 = atom862*atom864;
atom1730 = atom1716*atom869+zRBOG+atom1726+atom1725;
atom867 = atom862*atom865;
atom866 = atom863*atom865;
atom1717 = L_OBOG_OWHS*atom864;
atom1718 = atom866*atom1714;
atom1721 = atom1717+atom867*atom1716+atom1718;
atom1722 = atom862*atom1714;
atom1724 = -atom863*atom1716+atom1722;
atom1736 = atom1721*atom1210+atom1724*atom1209;
atom0 = -1/2*L_WAG;
atom1737 = atom0-atom1724*atom1210+atom1721*atom1209;
atom1930 = -atom1820*atom1828+atom1180*atom1736+uW_RFR*atom1279+atom1711*atom1237+(0.5)*L_RAIL*atom1847-uR_RFR+atom1190*atom1737+atom1282*atom1713+yWAG+atom1730*atom1193-RFRfs;
atom1179 = atom1175*atom1177;
atom1187 = atom1172*atom1179+atom1176*atom1173;
atom1184 = atom1172*atom1176-atom1173*atom1179;
atom1178 = -atom1177*atom1174;
atom1213 = atom1209*atom1184+atom1178*atom1210;
atom1234 = atom1213*atom865+atom864*atom1187;
atom1216 = -atom1184*atom1210+atom1209*atom1178;
atom1252 = atom862*atom1234-atom863*atom1216;
atom1249 = atom863*atom1234+atom862*atom1216;
atom1276 = atom1252*atom30-atom1249*atom31;
atom1273 = atom1252*atom31+atom30*atom1249;
atom1231 = atom1213*atom864-atom1187*atom865;
atom1810 = uR_RFR-lR_RFR;
atom1811 = aR_RFR*atom1810;
atom1812 = atom1811+bR_RFR;
atom1814 = cR_RFR+atom1812*atom1810;
atom1881 = atom1814+atom1810*(atom1812+atom1811);
atom1927 = (1+atom1881^2)^(-1/2);
atom1194 = -atom1173*atom1174;
atom1195 = atom1172*atom1174;
atom1225 = atom1194*atom1209+atom1175*atom1210;
atom1243 = atom1225*atom864-atom1195*atom865;
atom1246 = atom1195*atom864+atom1225*atom865;
atom1228 = atom1175*atom1209-atom1194*atom1210;
atom1264 = atom862*atom1246-atom863*atom1228;
atom1261 = atom862*atom1228+atom863*atom1246;
atom1285 = atom30*atom1261+atom1264*atom31;
atom1288 = -atom1261*atom31+atom30*atom1264;
atom1882 = atom1881*atom1878;
atom1883 = -atom1876*atom1881;
atom1916 = (atom1914+atom1882^2+atom1883^2)^(-1/2);
atom1919 = atom1876*atom1916;
atom1918 = atom1916*atom1883;
atom1917 = atom1882*atom1916;
atom1786 = (bW_RFR+aW_RFR*atom1704)*atom1704+cW_RFR+(bW_RFR+2*aW_RFR*atom1704)*atom1704;
atom1789 = -atom1786*atom1703;
atom1787 = atom1786*atom1712;
atom2069 = (RFLstas-RFLends)^(-1);
atom2071 = atom2069*(RFLstas-xR_RFL);
atom2073 = atom2071*RFLas+RFLbs;
atom2075 = RFLcs+atom2071*atom2073;
atom2077 = atom2071*atom2075+RFLds;
atom2079 = atom2071*atom2077+RFLes;
atom2082 = -atom2069*RFLas;
atom2085 = atom2082*atom2071-atom2073*atom2069;
atom2088 = -atom2069*atom2075+atom2071*atom2085;
atom2091 = atom2071*atom2088-atom2069*atom2077;
atom2094 = atom2071*atom2091-atom2069*atom2079;
atom2096 = 1+atom2094^2;
atom2097 = sqrt(atom2096);
atom2098 = atom2097^(-1);
atom1962 = uW_RFL-lW_RFL;
atom1966 = cW_RFL+(aW_RFL*atom1962+bW_RFL)*atom1962;
atom1968 = dW_RFL+atom1966*atom1962;
atom1961 = sin(thetaW_RFL);
atom1969 = -atom1968*atom1961;
atom1970 = cos(thetaW_RFL);
atom1971 = atom1968*atom1970;
atom1972 = -atom1715+zRWHSF;
atom1975 = atom1972*atom867+atom1717-atom1718;
atom1977 = -atom1722-atom863*atom1972;
atom1987 = atom1977*atom1209+atom1975*atom1210;
atom1988 = atom0-atom1977*atom1210+atom1975*atom1209;
atom1981 = zRBOG+atom1972*atom869-atom1726+atom1725;
atom2108 = -atom2085*atom2069;
atom2112 = -atom2069*atom2088;
atom2105 = -atom2069*atom2091;
atom2118 = 2*atom2105+(2*atom2112+(-(2.0)*atom2082*atom2071*atom2069+2*atom2108)*atom2071)*atom2071;
atom2123 = -atom2094*atom2096^(-1/2)*atom2118*atom2097^(-2);
atom2127 = 1-(0.5)*atom2094*atom2123*L_RAIL-(0.5)*atom2098*atom2118*L_RAIL;
atom2129 = atom2094+(0.5)*atom2123*L_RAIL;
atom2165 = atom2127^2;
atom2173 = (atom2129^2+atom2165)^(-1/2);
atom2181 = atom1969*atom1237-RFLfs+uW_RFL*atom1279-atom2071*atom2079+atom1193*atom1981+atom1988*atom1190-(0.5)*atom2098*L_RAIL-uR_RFL+atom1282*atom1971+atom1180*atom1987+yWAG;
atom2061 = uR_RFL-lR_RFL;
atom2062 = atom2061*aR_RFL;
atom2063 = atom2062+bR_RFL;
atom2065 = atom2063*atom2061+cR_RFL;
atom2132 = (atom2063+atom2062)*atom2061+atom2065;
atom2178 = (1+atom2132^2)^(-1/2);
atom2134 = -atom2127*atom2132;
atom2133 = atom2129*atom2132;
atom2167 = (atom2165+atom2133^2+atom2134^2)^(-1/2);
atom2169 = atom2167*atom2134;
atom2168 = atom2167*atom2133;
atom2170 = atom2167*atom2127;
atom2037 = atom1966+(2*aW_RFL*atom1962+bW_RFL)*atom1962;
atom2041 = atom1970*atom2037;
atom2038 = -atom2037*atom1961;
atom2326 = (RRRstas-RRRends)^(-1);
atom2327 = atom2326*(RRRstas-xR_RRR);
atom2329 = atom2327*RRRas+RRRbs;
atom2331 = RRRcs+atom2327*atom2329;
atom2338 = -atom2326*RRRas;
atom2341 = -atom2329*atom2326+atom2327*atom2338;
atom2344 = atom2327*atom2341-atom2331*atom2326;
atom2333 = RRRds+atom2327*atom2331;
atom2347 = -atom2333*atom2326+atom2327*atom2344;
atom2335 = atom2327*atom2333+RRRes;
atom2350 = -atom2335*atom2326+atom2327*atom2347;
atom2352 = 1+atom2350^2;
atom2353 = sqrt(atom2352);
atom2361 = -atom2326*atom2341;
atom2367 = -atom2344*atom2326;
atom2372 = -atom2347*atom2326;
atom2374 = 2*atom2372+atom2327*(2*atom2367+atom2327*(-(2.0)*atom2327*atom2338*atom2326+2*atom2361));
atom2379 = -atom2350*atom2352^(-1/2)*atom2374*atom2353^(-2);
atom2385 = -(0.5)*L_RAIL*atom2379+atom2350;
atom2354 = atom2353^(-1);
atom2383 = 1+(0.5)*atom2354*L_RAIL*atom2374+(0.5)*atom2350*L_RAIL*atom2379;
atom2421 = atom2383^2;
atom2429 = (atom2385^2+atom2421)^(-1/2);
atom49 = cos(aRWHSR);
atom50 = sin(aRWHSR);
atom1316 = atom1255*atom49+atom1258*atom50;
atom2212 = uW_RRR-lW_RRR;
atom2219 = sin(thetaW_RRR);
atom2218 = atom2212*(cW_RRR+atom2212*(bW_RRR+atom2212*aW_RRR))+dW_RRR;
atom2220 = -atom2219*atom2218;
atom2221 = cos(thetaW_RRR);
atom1319 = -atom1255*atom50+atom1258*atom49;
atom2222 = atom2221*atom2218;
atom2224 = atom50*atom1702;
atom2225 = atom2224+zRWHSR;
atom2223 = atom49*atom1702;
atom2233 = atom868*atom2223;
atom2237 = zRBOG+atom2233-atom1725+atom2225*atom869;
atom2226 = atom866*atom2223;
atom2229 = -atom1717+atom2226+atom867*atom2225;
atom2230 = atom862*atom2223;
atom2232 = atom2230-atom863*atom2225;
atom2243 = atom2229*atom1210+atom1209*atom2232;
atom2244 = atom0+atom1209*atom2229-atom2232*atom1210;
atom2437 = -RRRfs-atom2327*atom2335+atom1180*atom2243+atom1316*uW_RRR+atom1190*atom2244+atom1319*atom2222-uR_RRR+atom1193*atom2237+yWAG+atom2220*atom1237+(0.5)*atom2354*L_RAIL;
atom1310 = atom49*atom1249+atom50*atom1252;
atom1313 = -atom50*atom1249+atom49*atom1252;
atom2317 = uR_RRR-lR_RRR;
atom2318 = atom2317*aR_RRR;
atom2319 = atom2318+bR_RRR;
atom2321 = cR_RRR+atom2317*atom2319;
atom2388 = atom2317*(atom2318+atom2319)+atom2321;
atom2434 = (1+atom2388^2)^(-1/2);
atom1325 = atom49*atom1264-atom50*atom1261;
atom1322 = atom49*atom1261+atom50*atom1264;
atom2389 = atom2385*atom2388;
atom2390 = -atom2383*atom2388;
atom2423 = (atom2390^2+atom2389^2+atom2421)^(-1/2);
atom2426 = atom2423*atom2383;
atom2425 = atom2423*atom2390;
atom2424 = atom2423*atom2389;
atom2293 = cW_RRR+atom2212*(bW_RRR+2*atom2212*aW_RRR)+atom2212*(bW_RRR+atom2212*aW_RRR);
atom2297 = atom2221*atom2293;
atom2294 = -atom2219*atom2293;
atom2577 = (RRLstas-RRLends)^(-1);
atom2578 = (RRLstas-xR_RRL)*atom2577;
atom2580 = atom2578*RRLas+RRLbs;
atom2582 = RRLcs+atom2578*atom2580;
atom2584 = atom2578*atom2582+RRLds;
atom2589 = -RRLas*atom2577;
atom2592 = atom2578*atom2589-atom2580*atom2577;
atom2595 = -atom2582*atom2577+atom2578*atom2592;
atom2598 = atom2578*atom2595-atom2584*atom2577;
atom2586 = atom2578*atom2584+RRLes;
atom2601 = atom2578*atom2598-atom2586*atom2577;
atom2603 = 1+atom2601^2;
atom2604 = sqrt(atom2603);
atom2616 = -atom2592*atom2577;
atom2612 = -atom2595*atom2577;
atom2623 = -atom2598*atom2577;
atom2605 = atom2604^(-1);
atom2625 = 2*atom2623-2*atom2578*(atom2578*(atom2578*atom2589*atom2577-atom2616)-atom2612);
atom2630 = -atom2603^(-1/2)*atom2601*atom2625*atom2604^(-2);
atom2634 = 1-(0.5)*atom2605*atom2625*L_RAIL-(0.5)*atom2601*atom2630*L_RAIL;
atom2636 = (0.5)*atom2630*L_RAIL+atom2601;
atom2672 = atom2634^2;
atom2680 = (atom2672+atom2636^2)^(-1/2);
atom2479 = -atom2224+zRWHSR;
atom2482 = -atom1717+atom867*atom2479-atom2226;
atom2484 = -atom863*atom2479-atom2230;
atom2495 = -atom2484*atom1210+atom2482*atom1209+atom0;
atom2494 = atom1209*atom2484+atom2482*atom1210;
atom2488 = zRBOG-atom2233+atom2479*atom869-atom1725;
atom2469 = uW_RRL-lW_RRL;
atom2475 = dW_RRL+atom2469*(cW_RRL+atom2469*(atom2469*aW_RRL+bW_RRL));
atom2468 = sin(thetaW_RRL);
atom2476 = -atom2475*atom2468;
atom2477 = cos(thetaW_RRL);
atom2478 = atom2475*atom2477;
atom2688 = -uR_RRL+atom1180*atom2494+atom2476*atom1237-RRLfs+atom1316*uW_RRL-(0.5)*atom2605*L_RAIL-atom2578*atom2586+atom1193*atom2488+atom1190*atom2495+yWAG+atom1319*atom2478;
atom2568 = uR_RRL-lR_RRL;
atom2569 = atom2568*aR_RRL;
atom2570 = bR_RRL+atom2569;
atom2572 = atom2570*atom2568+cR_RRL;
atom2639 = atom2572+(atom2570+atom2569)*atom2568;
atom2685 = (1+atom2639^2)^(-1/2);
atom2641 = -atom2639*atom2634;
atom2640 = atom2639*atom2636;
atom2674 = (atom2672+atom2641^2+atom2640^2)^(-1/2);
atom2675 = atom2674*atom2640;
atom2676 = atom2641*atom2674;
atom2677 = atom2634*atom2674;
atom2544 = cW_RRL+(2*atom2469*aW_RRL+bW_RRL)*atom2469+atom2469*(atom2469*aW_RRL+bW_RRL);
atom2545 = -atom2544*atom2468;
atom2548 = atom2544*atom2477;
atom2834 = (FFRends-FFRstas)^(-1);
atom2836 = atom2834*(xR_FFR-FFRstas);
atom2838 = FFRbs+atom2836*FFRas;
atom2840 = FFRcs+atom2836*atom2838;
atom2842 = FFRds+atom2836*atom2840;
atom2847 = atom2834*FFRas;
atom2850 = atom2834*atom2838+atom2836*atom2847;
atom2853 = atom2834*atom2840+atom2836*atom2850;
atom2856 = atom2836*atom2853+atom2842*atom2834;
atom2871 = atom2834*atom2850;
atom2870 = atom2834*atom2853;
atom2881 = atom2834*atom2856;
atom2844 = FFRes+atom2836*atom2842;
atom2859 = atom2836*atom2856+atom2834*atom2844;
atom2861 = 1+atom2859^2;
atom2862 = sqrt(atom2861);
atom2883 = 2*atom2881+2*atom2836*(atom2870+atom2836*(atom2871+atom2836*atom2834*atom2847));
atom2863 = atom2862^(-1);
atom2888 = -atom2862^(-2)*atom2859*atom2861^(-1/2)*atom2883;
atom2892 = 1+(0.5)*atom2883*atom2863*L_RAIL+(0.5)*atom2888*atom2859*L_RAIL;
atom2894 = atom2859-(0.5)*atom2888*L_RAIL;
atom2930 = atom2892^2;
atom2938 = (atom2894^2+atom2930)^(-1/2);
atom1019 = sin(bFBOG);
atom497 = cos(aFWHSF);
atom1018 = cos(bFBOG);
atom1017 = sin(aFBOG);
atom2730 = atom497*atom1702;
atom1022 = atom1018*atom1017;
atom2741 = -L_OBOG_OWHS*atom1019;
atom2742 = atom2730*atom1022;
atom1016 = cos(aFBOG);
atom498 = sin(aFWHSF);
atom2731 = atom498*atom1702;
atom1023 = atom1018*atom1016;
atom2732 = atom2731+zFWHSF;
atom2746 = atom2741+zFBOG+atom2742+atom1023*atom2732;
atom1020 = atom1019*atom1017;
atom2733 = atom1018*L_OBOG_OWHS;
atom2734 = atom1020*atom2730;
atom1021 = atom1019*atom1016;
atom2737 = atom1021*atom2732+atom2733+atom2734;
atom1496 = cos(cFSLD);
atom2738 = atom1016*atom2730;
atom1497 = sin(cFSLD);
atom2740 = -atom2732*atom1017+atom2738;
atom2753 = -atom1497*atom2740-atom0+atom2737*atom1496;
atom2752 = atom1497*atom2737+atom2740*atom1496;
atom2720 = uW_FFR-lW_FFR;
atom2726 = dW_FFR+(cW_FFR+(bW_FFR+aW_FFR*atom2720)*atom2720)*atom2720;
atom2728 = cos(thetaW_FFR);
atom1500 = atom1496*atom1184+atom1497*atom1178;
atom1521 = atom1019*atom1500+atom1018*atom1187;
atom1503 = atom1496*atom1178-atom1497*atom1184;
atom1539 = -atom1503*atom1017+atom1016*atom1521;
atom1536 = atom1521*atom1017+atom1503*atom1016;
atom2729 = atom2726*atom2728;
atom1562 = atom497*atom1539-atom498*atom1536;
atom1559 = atom497*atom1536+atom498*atom1539;
atom2719 = sin(thetaW_FFR);
atom2727 = -atom2726*atom2719;
atom1518 = atom1018*atom1500-atom1019*atom1187;
atom1506 = atom1190*atom1496+atom1497*atom1180;
atom1527 = atom1019*atom1506+atom1193*atom1018;
atom1509 = atom1180*atom1496-atom1497*atom1190;
atom1545 = atom1527*atom1016-atom1017*atom1509;
atom1542 = atom1016*atom1509+atom1527*atom1017;
atom1568 = atom497*atom1545-atom498*atom1542;
atom1565 = atom497*atom1542+atom498*atom1545;
atom1524 = -atom1193*atom1019+atom1018*atom1506;
atom2946 = atom2753*atom1190-uR_FFR+atom1180*atom2752+uW_FFR*atom1565+atom1524*atom2727-FFRfs+atom2729*atom1568+(0.5)*atom2863*L_RAIL+yWAG-atom2836*atom2844+atom2746*atom1193;
atom2826 = uR_FFR-lR_FFR;
atom2827 = atom2826*aR_FFR;
atom2828 = bR_FFR+atom2827;
atom2830 = atom2828*atom2826+cR_FFR;
atom2897 = atom2830+atom2826*(atom2828+atom2827);
atom2943 = (1+atom2897^2)^(-1/2);
atom1512 = atom1194*atom1496+atom1497*atom1175;
atom1530 = -atom1019*atom1195+atom1018*atom1512;
atom1533 = atom1018*atom1195+atom1019*atom1512;
atom1515 = atom1175*atom1496-atom1497*atom1194;
atom1551 = -atom1515*atom1017+atom1016*atom1533;
atom1548 = atom1533*atom1017+atom1515*atom1016;
atom1571 = atom497*atom1548+atom498*atom1551;
atom1574 = -atom498*atom1548+atom497*atom1551;
atom2899 = -atom2892*atom2897;
atom2898 = atom2894*atom2897;
atom2932 = (atom2899^2+atom2930+atom2898^2)^(-1/2);
atom2935 = atom2932*atom2892;
atom2934 = atom2899*atom2932;
atom2933 = atom2932*atom2898;
atom2802 = (bW_FFR+2*aW_FFR*atom2720)*atom2720+cW_FFR+(bW_FFR+aW_FFR*atom2720)*atom2720;
atom2803 = atom2802*atom2728;
atom2805 = -atom2802*atom2719;
atom3086 = (FFLstas-FFLends)^(-1);
atom3087 = (FFLstas-xR_FFL)*atom3086;
atom3098 = -FFLas*atom3086;
atom3089 = atom3087*FFLas+FFLbs;
atom3101 = atom3087*atom3098-atom3089*atom3086;
atom3091 = FFLcs+atom3087*atom3089;
atom3104 = atom3087*atom3101-atom3091*atom3086;
atom3124 = -atom3086*atom3101;
atom3121 = -atom3104*atom3086;
atom3093 = FFLds+atom3087*atom3091;
atom3107 = atom3087*atom3104-atom3093*atom3086;
atom3131 = -atom3107*atom3086;
atom3095 = atom3087*atom3093+FFLes;
atom3110 = -atom3095*atom3086+atom3087*atom3107;
atom3112 = 1+atom3110^2;
atom3113 = sqrt(atom3112);
atom3134 = 2*atom3087*((atom3124-atom3087*atom3098*atom3086)*atom3087+atom3121)+2*atom3131;
atom3114 = atom3113^(-1);
atom3139 = -atom3134*atom3113^(-2)*atom3110*atom3112^(-1/2);
atom3143 = 1-(0.5)*atom3139*atom3110*L_RAIL-(0.5)*atom3134*atom3114*L_RAIL;
atom3145 = atom3110+(0.5)*atom3139*L_RAIL;
atom3181 = atom3143^2;
atom3189 = (atom3181+atom3145^2)^(-1/2);
atom2978 = uW_FFL-lW_FFL;
atom2977 = sin(thetaW_FFL);
atom2984 = dW_FFL+atom2978*(atom2978*(atom2978*aW_FFL+bW_FFL)+cW_FFL);
atom2985 = -atom2977*atom2984;
atom2986 = cos(thetaW_FFL);
atom2987 = atom2986*atom2984;
atom2988 = -atom2731+zFWHSF;
atom2997 = atom2741+zFBOG+atom1023*atom2988-atom2742;
atom2993 = -atom1017*atom2988-atom2738;
atom2991 = atom1021*atom2988+atom2733-atom2734;
atom3003 = atom1497*atom2991+atom2993*atom1496;
atom3004 = atom2991*atom1496-atom0-atom1497*atom2993;
atom3197 = atom3004*atom1190+atom2987*atom1568+uW_FFL*atom1565-atom3087*atom3095-uR_FFL+atom1193*atom2997+atom1180*atom3003+yWAG-(0.5)*atom3114*L_RAIL-FFLfs+atom2985*atom1524;
atom3077 = uR_FFL-lR_FFL;
atom3078 = aR_FFL*atom3077;
atom3079 = atom3078+bR_FFL;
atom3081 = cR_FFL+atom3079*atom3077;
atom3148 = atom3081+atom3077*(atom3079+atom3078);
atom3194 = (1+atom3148^2)^(-1/2);
atom3149 = atom3145*atom3148;
atom3150 = -atom3143*atom3148;
atom3183 = (atom3181+atom3149^2+atom3150^2)^(-1/2);
atom3184 = atom3183*atom3149;
atom3185 = atom3150*atom3183;
atom3186 = atom3183*atom3143;
atom3053 = atom2978*(2*atom2978*aW_FFL+bW_FFL)+atom2978*(atom2978*aW_FFL+bW_FFL)+cW_FFL;
atom3057 = atom2986*atom3053;
atom3054 = -atom3053*atom2977;
atom683 = cos(aFWHSR);
atom3239 = atom683*atom1702;
atom3249 = atom3239*atom1022;
atom684 = sin(aFWHSR);
atom3240 = atom684*atom1702;
atom3241 = zFWHSR+atom3240;
atom3253 = -atom2741+zFBOG+atom3241*atom1023+atom3249;
atom3242 = atom3239*atom1020;
atom3245 = -atom2733+atom3241*atom1021+atom3242;
atom3246 = atom3239*atom1016;
atom3248 = -atom3241*atom1017+atom3246;
atom3259 = atom1497*atom3245+atom3248*atom1496;
atom3260 = -atom1497*atom3248+atom3245*atom1496-atom0;
atom3229 = uW_FRR-lW_FRR;
atom3230 = atom3229*aW_FRR;
atom3231 = atom3230+bW_FRR;
atom3233 = atom3231*atom3229+cW_FRR;
atom3237 = cos(thetaW_FRR);
atom3235 = dW_FRR+atom3229*atom3233;
atom1598 = atom683*atom1539-atom684*atom1536;
atom3238 = atom3237*atom3235;
atom1595 = atom684*atom1539+atom683*atom1536;
atom3228 = sin(thetaW_FRR);
atom3236 = -atom3228*atom3235;
atom3341 = (FRRstas-FRRends)^(-1);
atom3353 = -atom3341*FRRas;
atom3342 = atom3341*(FRRstas-xR_FRR);
atom3344 = FRRas*atom3342+FRRbs;
atom3356 = -atom3341*atom3344+atom3353*atom3342;
atom3346 = FRRcs+atom3344*atom3342;
atom3359 = atom3342*atom3356-atom3341*atom3346;
atom3348 = FRRds+atom3346*atom3342;
atom3362 = atom3359*atom3342-atom3341*atom3348;
atom3350 = atom3342*atom3348+FRRes;
atom3365 = atom3362*atom3342-atom3341*atom3350;
atom3367 = 1+atom3365^2;
atom3368 = sqrt(atom3367);
atom3369 = atom3368^(-1);
atom3378 = -atom3341*atom3356;
atom3383 = -atom3341*atom3359;
atom3387 = -atom3341*atom3362;
atom3389 = 2*atom3342*(atom3383-(atom3341*atom3353*atom3342-atom3378)*atom3342)+2*atom3387;
atom3394 = -atom3368^(-2)*atom3365*atom3389*atom3367^(-1/2);
atom3398 = 1+(0.5)*atom3369*atom3389*L_RAIL+(0.5)*atom3365*L_RAIL*atom3394;
atom3400 = -(0.5)*L_RAIL*atom3394+atom3365;
atom3436 = atom3398^2;
atom3444 = (atom3400^2+atom3436)^(-1/2);
atom1604 = atom683*atom1545-atom684*atom1542;
atom1601 = atom683*atom1542+atom684*atom1545;
atom3452 = atom1193*atom3253+atom3236*atom1524+atom1604*atom3238+(0.5)*atom3369*L_RAIL-atom3342*atom3350+atom1180*atom3259+atom1190*atom3260+uW_FRR*atom1601-uR_FRR+yWAG-FRRfs;
atom1607 = atom683*atom1548+atom684*atom1551;
atom1610 = -atom684*atom1548+atom683*atom1551;
atom3332 = uR_FRR-lR_FRR;
atom3333 = atom3332*aR_FRR;
atom3334 = atom3333+bR_FRR;
atom3336 = atom3332*atom3334+cR_FRR;
atom3403 = atom3336+atom3332*(atom3333+atom3334);
atom3449 = (1+atom3403^2)^(-1/2);
atom3404 = atom3400*atom3403;
atom3405 = -atom3398*atom3403;
atom3438 = (atom3405^2+atom3404^2+atom3436)^(-1/2);
atom3440 = atom3405*atom3438;
atom3439 = atom3404*atom3438;
atom3441 = atom3398*atom3438;
atom3308 = atom3233+atom3229*(atom3231+atom3230);
atom3311 = -atom3228*atom3308;
atom3309 = atom3237*atom3308;
atom3591 = (FRLstas-FRLends)^(-1);
atom3592 = atom3591*(FRLstas-xR_FRL);
atom3594 = FRLbs+atom3592*FRLas;
atom3596 = FRLcs+atom3592*atom3594;
atom3598 = FRLds+atom3596*atom3592;
atom3600 = atom3592*atom3598+FRLes;
atom3603 = -FRLas*atom3591;
atom3606 = -atom3594*atom3591+atom3603*atom3592;
atom3609 = -atom3596*atom3591+atom3592*atom3606;
atom3612 = -atom3598*atom3591+atom3609*atom3592;
atom3615 = -atom3600*atom3591+atom3612*atom3592;
atom3617 = 1+atom3615^2;
atom3618 = sqrt(atom3617);
atom3629 = -atom3606*atom3591;
atom3634 = -atom3609*atom3591;
atom3626 = -atom3612*atom3591;
atom3639 = 2*atom3626+2*atom3592*(atom3634+atom3592*(atom3629-atom3603*atom3592*atom3591));
atom3644 = -atom3615*atom3617^(-1/2)*atom3639*atom3618^(-2);
atom3650 = atom3615+(0.5)*atom3644*L_RAIL;
atom3619 = atom3618^(-1);
atom3648 = 1-(0.5)*atom3619*atom3639*L_RAIL-(0.5)*atom3615*atom3644*L_RAIL;
atom3686 = atom3648^2;
atom3694 = (atom3650^2+atom3686)^(-1/2);
atom3484 = uW_FRL-lW_FRL;
atom3485 = atom3484*aW_FRL;
atom3486 = atom3485+bW_FRL;
atom3488 = cW_FRL+atom3484*atom3486;
atom3492 = cos(thetaW_FRL);
atom3490 = dW_FRL+atom3488*atom3484;
atom3493 = atom3492*atom3490;
atom3483 = sin(thetaW_FRL);
atom3491 = -atom3483*atom3490;
atom3494 = zFWHSR-atom3240;
atom3499 = -atom3494*atom1017-atom3246;
atom3497 = atom3494*atom1021-atom2733-atom3242;
atom3509 = atom1497*atom3497+atom3499*atom1496;
atom3510 = atom3497*atom1496-atom0-atom1497*atom3499;
atom3503 = -atom2741+zFBOG+atom3494*atom1023-atom3249;
atom3702 = atom1604*atom3493+atom1193*atom3503+atom1180*atom3509-atom3592*atom3600+atom3510*atom1190-uR_FRL+uW_FRL*atom1601-(0.5)*atom3619*L_RAIL+atom3491*atom1524+yWAG-FRLfs;
atom3582 = uR_FRL-lR_FRL;
atom3583 = atom3582*aR_FRL;
atom3584 = atom3583+bR_FRL;
atom3586 = cR_FRL+atom3584*atom3582;
atom3653 = atom3582*(atom3584+atom3583)+atom3586;
atom3699 = (1+atom3653^2)^(-1/2);
atom3654 = atom3650*atom3653;
atom3655 = -atom3648*atom3653;
atom3688 = (atom3655^2+atom3654^2+atom3686)^(-1/2);
atom3691 = atom3688*atom3648;
atom3690 = atom3688*atom3655;
atom3689 = atom3654*atom3688;
atom3558 = atom3488+atom3484*(atom3485+atom3486);
atom3561 = -atom3483*atom3558;
atom3559 = atom3492*atom3558;

Phit_ = [atom1922*atom1876*(atom1184*atom1737+atom1276*atom1713-xR_RFR+uW_RFR*atom1273+atom1730*atom1187+atom1231*atom1711-(0.5)*atom1843*L_RAIL*atom1847+xWAG+atom1736*atom1178)+atom1922*atom1878*atom1930;
(atom1243*atom1711+atom1730*atom1195-dR_RFR+uW_RFR*atom1285+atom1288*atom1713-atom1810*atom1814+atom1175*atom1736-irrRFRz+zWAG+atom1194*atom1737)*atom1881*atom1927+atom1927*atom1930;
(atom1711*atom1282-atom1237*atom1713)*atom1918-(atom1243*atom1713-atom1288*atom1711)*atom1919+atom1917*(atom1276*atom1711-atom1231*atom1713);
atom1917*(atom1276*atom1787+atom1789*atom1231+atom1273)+atom1918*(atom1789*atom1237+atom1282*atom1787+atom1279)+atom1919*(atom1789*atom1243+atom1288*atom1787+atom1285);
atom2129*atom2181*atom2173+((0.5)*atom2094*atom2098*L_RAIL+atom1276*atom1971+atom1981*atom1187+atom1987*atom1178+atom1988*atom1184+atom1231*atom1969-xR_RFL+xWAG+uW_RFL*atom1273)*atom2127*atom2173;
atom2178*(atom1243*atom1969+uW_RFL*atom1285-atom2061*atom2065+atom1175*atom1987+atom1288*atom1971+atom1988*atom1194-dR_RFL-irrRFLz+atom1981*atom1195+zWAG)*atom2132+atom2178*atom2181;
atom2169*(atom1969*atom1282-atom1237*atom1971)+atom2168*(atom1276*atom1969-atom1231*atom1971)-(atom1243*atom1971-atom1288*atom1969)*atom2170;
atom2168*(atom1273+atom1231*atom2038+atom2041*atom1276)+(atom2038*atom1237+atom2041*atom1282+atom1279)*atom2169+(atom1243*atom2038+atom1285+atom2041*atom1288)*atom2170;
(-(0.5)*atom2350*atom2354*L_RAIL+uW_RRR*atom1310+atom2244*atom1184+atom2222*atom1313+atom2243*atom1178-xR_RRR+atom1231*atom2220+xWAG+atom2237*atom1187)*atom2429*atom2383+atom2385*atom2429*atom2437;
(atom2222*atom1325+uW_RRR*atom1322+atom1243*atom2220+atom1195*atom2237-dR_RRR-irrRRRz+atom1194*atom2244+zWAG+atom1175*atom2243-atom2317*atom2321)*atom2434*atom2388+atom2434*atom2437;
-(atom1231*atom2222-atom2220*atom1313)*atom2424+(atom2220*atom1325-atom1243*atom2222)*atom2426-(atom2222*atom1237-atom1319*atom2220)*atom2425;
atom2426*(atom1243*atom2294+atom2297*atom1325+atom1322)+atom2424*(atom2297*atom1313+atom1231*atom2294+atom1310)+atom2425*(atom1316+atom1319*atom2297+atom2294*atom1237);
((0.5)*atom2605*atom2601*L_RAIL+atom1184*atom2495+uW_RRL*atom1310+atom2488*atom1187+atom2476*atom1231+atom2478*atom1313+xWAG-xR_RRL+atom2494*atom1178)*atom2634*atom2680+atom2680*atom2636*atom2688;
atom2639*(atom1195*atom2488+uW_RRL*atom1322+atom2476*atom1243+atom2478*atom1325+atom1175*atom2494-atom2572*atom2568+zWAG-dR_RRL-irrRRLz+atom1194*atom2495)*atom2685+atom2685*atom2688;
(atom1319*atom2476-atom2478*atom1237)*atom2676+atom2675*(atom2476*atom1313-atom1231*atom2478)+atom2677*(atom2476*atom1325-atom2478*atom1243);
atom2677*(atom1243*atom2545+atom2548*atom1325+atom1322)+atom2675*(atom2548*atom1313+atom1310+atom1231*atom2545)+(atom1316+atom1319*atom2548+atom1237*atom2545)*atom2676;
-(xR_FFR+(0.5)*atom2859*atom2863*L_RAIL-atom2752*atom1178-atom2746*atom1187-atom1559*uW_FFR-atom2753*atom1184-xWAG-atom2727*atom1518-atom2729*atom1562)*atom2892*atom2938+atom2894*atom2946*atom2938;
atom2943*atom2946+atom2943*(atom2753*atom1194+atom2746*atom1195+atom1571*uW_FFR+atom2729*atom1574-irrFFRz-atom2830*atom2826+atom1175*atom2752+zWAG+atom1530*atom2727-dR_FFR)*atom2897;
(atom2727*atom1568-atom2729*atom1524)*atom2934+(atom1562*atom2727-atom2729*atom1518)*atom2933-atom2935*(atom1530*atom2729-atom1574*atom2727);
(atom2805*atom1524+atom1565+atom2803*atom1568)*atom2934+atom2935*(atom2803*atom1574+atom1571+atom1530*atom2805)+(atom1562*atom2803+atom1559+atom2805*atom1518)*atom2933;
((0.5)*atom3110*atom3114*L_RAIL+atom2987*atom1562+uW_FFL*atom1559+atom2997*atom1187-xR_FFL+atom2985*atom1518+atom3003*atom1178+atom3004*atom1184+xWAG)*atom3189*atom3143+atom3145*atom3189*atom3197;
(uW_FFL*atom1571+atom3004*atom1194+atom1175*atom3003-dR_FFL-irrFFLz-atom3081*atom3077+atom2987*atom1574+zWAG+atom1530*atom2985+atom2997*atom1195)*atom3194*atom3148+atom3194*atom3197;
atom3186*(atom2985*atom1574-atom1530*atom2987)-(atom2987*atom1524-atom2985*atom1568)*atom3185-(atom2987*atom1518-atom1562*atom2985)*atom3184;
(atom1559+atom3054*atom1518+atom1562*atom3057)*atom3184+atom3186*(atom1530*atom3054+atom3057*atom1574+atom1571)+(atom3057*atom1568+atom3054*atom1524+atom1565)*atom3185;
atom3444*(atom3260*atom1184+atom3253*atom1187+atom3236*atom1518+uW_FRR*atom1595+atom3259*atom1178-xR_FRR+atom1598*atom3238-(0.5)*atom3369*atom3365*L_RAIL+xWAG)*atom3398+atom3444*atom3400*atom3452;
atom3452*atom3449+(atom1175*atom3259+atom1610*atom3238-atom3332*atom3336+atom1194*atom3260-dR_FRR+atom1607*uW_FRR-irrFRRz+zWAG+atom3253*atom1195+atom3236*atom1530)*atom3403*atom3449;
atom3440*(atom3236*atom1604-atom3238*atom1524)+(atom3236*atom1598-atom3238*atom1518)*atom3439-atom3441*(atom1530*atom3238-atom3236*atom1610);
atom3441*(atom1607+atom1610*atom3309+atom1530*atom3311)+(atom3311*atom1518+atom1598*atom3309+atom1595)*atom3439+atom3440*(atom3311*atom1524+atom3309*atom1604+atom1601);
atom3650*atom3694*atom3702+(uW_FRL*atom1595+atom3509*atom1178+atom3510*atom1184-xR_FRL+atom1187*atom3503+atom1598*atom3493+atom3491*atom1518+(0.5)*atom3615*atom3619*L_RAIL+xWAG)*atom3694*atom3648;
atom3699*atom3702-atom3699*(atom3582*atom3586-atom1610*atom3493+dR_FRL+irrFRLz-atom1195*atom3503-atom3510*atom1194-atom1607*uW_FRL-atom1530*atom3491-atom1175*atom3509-zWAG)*atom3653;
(atom1598*atom3491-atom3493*atom1518)*atom3689-(atom3493*atom1524-atom1604*atom3491)*atom3690-(atom1530*atom3493-atom1610*atom3491)*atom3691;
(atom1607+atom1610*atom3559+atom1530*atom3561)*atom3691+(atom1598*atom3559+atom3561*atom1518+atom1595)*atom3689+atom3690*(atom3559*atom1604+atom1601+atom3561*atom1524)];

%endfunction