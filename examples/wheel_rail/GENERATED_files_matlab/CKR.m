function CKR_ = CKR(q,qaux,dq,time,param)

x = q( 1 ); 
y = q( 2 ); 
b = q( 3 ); 
c = q( 4 ); 
z = q( 5 ); 
a = q( 6 ); 

thetaW_R = qaux( 1 ); 
uW_R = qaux( 2 ); 
uR_R = qaux( 3 ); 
sR_R = qaux( 4 ); 
thetaW_L = qaux( 5 ); 
uW_L = qaux( 6 ); 
uR_L = qaux( 7 ); 
sR_L = qaux( 8 ); 

dx = dq( 1 ); 
dy = dq( 2 ); 
db = dq( 3 ); 
dc = dq( 4 ); 
dz = dq( 5 ); 
da = dq( 6 ); 

t= time ;

g = param( 1 ); 
a_pend = param( 2 ); 
b_pend = param( 3 ); 
L_R = param( 4 ); 
L_WHS = param( 5 ); 
a_rail = param( 6 ); 
mWHS = param( 7 ); 
I_WHSx = param( 8 ); 
I_WHSy = param( 9 ); 
I_WHSz = param( 10 ); 
tor = param( 11 ); 
asR = param( 12 ); 
bsR = param( 13 ); 
csR = param( 14 ); 
dsR = param( 15 ); 
esR = param( 16 ); 
fsR = param( 17 ); 
stasR = param( 18 ); 
endsR = param( 19 ); 
usRz = param( 20 ); 
aW_R = param( 21 ); 
bW_R = param( 22 ); 
cW_R = param( 23 ); 
dW_R = param( 24 ); 
lW_R = param( 25 ); 
aR_R = param( 26 ); 
bR_R = param( 27 ); 
cR_R = param( 28 ); 
dR_R = param( 29 ); 
lR_R = param( 30 ); 
asL = param( 31 ); 
bsL = param( 32 ); 
csL = param( 33 ); 
dsL = param( 34 ); 
esL = param( 35 ); 
fsL = param( 36 ); 
stasL = param( 37 ); 
endsL = param( 38 ); 
usLz = param( 39 ); 
aW_L = param( 40 ); 
bW_L = param( 41 ); 
cW_L = param( 42 ); 
dW_L = param( 43 ); 
lW_L = param( 44 ); 
aR_L = param( 45 ); 
bR_L = param( 46 ); 
cR_L = param( 47 ); 
dR_L = param( 48 ); 
lR_L = param( 49 ); 
E_elastic = param( 50 ); 
nu_poisson = param( 51 ); 
G_elastic = param( 52 ); 
aR = param( 53 ); 
bR = param( 54 ); 
aL = param( 55 ); 
bL = param( 56 ); 
C11R = param( 57 ); 
C22R = param( 58 ); 
C23R = param( 59 ); 
C33R = param( 60 ); 
C11L = param( 61 ); 
C22L = param( 62 ); 
C23L = param( 63 ); 
C33L = param( 64 ); 
y0 = param( 65 ); 
b0 = param( 66 ); 

atom381 = (endsR-stasR)^(-1);
atom382 = (sR_R-stasR)*atom381;
atom384 = bsR+atom382*asR;
atom386 = atom382*atom384+csR;
atom393 = atom381*asR;
atom396 = atom381*atom384+atom393*atom382;
atom399 = atom382*atom396+atom386*atom381;
atom388 = atom386*atom382+dsR;
atom402 = atom399*atom382+atom381*atom388;
atom405 = (atom388*atom382+esR)*atom381+atom402*atom382;
atom407 = 1+atom405^2;
atom416 = atom381*atom396;
atom422 = atom381*atom399;
atom426 = atom381*atom402;
atom429 = 2*atom426+2*(atom422+(atom393*atom381*atom382+atom416)*atom382)*atom382;
atom408 = sqrt(atom407);
atom434 = -atom408^(-2)*atom429*atom405*atom407^(-1/2);
atom440 = atom405-(0.5)*atom434*L_R;
atom438 = 1+(0.5)*atom408^(-1)*atom429*L_R+(0.5)*atom405*atom434*L_R;
atom449 = atom438^2;
atom457 = (atom440^2+atom449)^(-1/2);
atom9 = cos(a_pend);
atom8 = sin(b_pend);
atom13 = -atom9*atom8;
atom458 = atom457*atom438;
atom459 = atom457*atom440;
atom10 = sin(a_pend);
atom1511 = atom459*atom10+atom13*atom458;
atom11 = atom10*atom8;
atom1504 = atom9*atom459+atom11*atom458;
atom7 = cos(b_pend);
atom1506 = atom7*atom458;
atom1513 = atom13*atom1511+atom1504*atom11+atom1506*atom7;
atom1733 = -C11R*bR*G_elastic*atom1513*aR;
atom372 = uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 = bR_R+atom373;
atom443 = atom374*atom372+cR_R+atom372*(atom374+atom373);
atom462 = (1+atom443^2)^(-1/2);
atom14 = atom9*atom7;
atom463 = atom462*atom443;
atom1523 = atom14*atom463+atom462*atom10;
atom12 = -atom10*atom7;
atom1516 = atom462*atom9+atom12*atom463;
atom1518 = atom463*atom8;
atom1525 = atom1516*atom11+atom1518*atom7+atom13*atom1523;
atom1734 = -bR*C22R*G_elastic*atom1525*aR;
atom6 = sin(c);
atom3 = cos(a);
atom144 = -atom6*atom3;
atom307 = -(0.5)*L_WHS;
atom309 = uW_R-lW_R;
atom315 = atom309*(cW_R+(aW_R*atom309+bW_R)*atom309)+dW_R;
atom5 = cos(c);
atom316 = -atom315*sin(thetaW_R);
atom4 = sin(a);
atom318 = atom315*cos(thetaW_R);
atom145 = atom6*atom4;
atom779 = atom5*atom316+atom318*atom145+uW_R*atom144+atom144*atom307;
atom781 = atom307*atom4+uW_R*atom4+atom318*atom3;
atom844 = atom779*atom4-atom781*atom144;
atom146 = atom5*atom3;
atom147 = -atom5*atom4;
atom780 = atom307*atom146+uW_R*atom146+atom6*atom316+atom318*atom147;
atom841 = -atom4*atom780+atom781*atom146;
atom1716 = atom844*atom459+atom841*atom458;
atom847 = atom144*atom780-atom779*atom146;
atom1725 = atom463*atom847+atom844*atom462;
atom445 = -atom438*atom443;
atom444 = atom443*atom440;
atom451 = (atom444^2+atom445^2+atom449)^(-1/2);
atom454 = atom438*atom451;
atom453 = atom451*atom445;
atom452 = atom444*atom451;
atom1736 = sqrt(bR*aR);
atom1063 = atom454*atom4+atom452*atom144+atom453*atom146;
atom1737 = -bR*atom1736*G_elastic*C23R*atom1525*aR;
atom1726 = atom462*atom779;
atom1719 = -atom458*atom780+atom459*atom779;
atom1732 = atom6*atom453+atom5*atom452;
atom894 = -atom5*atom781;
atom1722 = atom781*atom6*atom458+atom459*atom894;
atom1729 = atom462*atom894+(atom5*atom780-atom6*atom779)*atom463;
atom1528 = atom10*atom1511+atom9*atom1504;
atom1738 = -C11R*bR*atom1528*G_elastic*aR;
atom1531 = atom10*atom1523+atom9*atom1516;
atom1739 = -bR*atom1531*C22R*G_elastic*aR;
atom1740 = -bR*atom1736*atom1531*G_elastic*C23R*aR;
atom1539 = atom12*atom1504+atom14*atom1511+atom1506*atom8;
atom1741 = -C11R*bR*G_elastic*aR*(atom1539*atom847+atom841*atom1513+atom844*atom1528);
atom22 = -atom6*atom11+atom5*atom9;
atom1566 = atom12*atom454+atom452*atom11+atom9*atom453;
atom16 = -atom6*atom7;
atom1560 = atom452*atom7+atom454*atom8;
atom28 = -atom13*atom6+atom5*atom10;
atom1556 = atom10*atom453+atom14*atom454+atom452*atom13;
atom1569 = atom1566*(atom22*atom3+atom12*atom4)+(atom28*atom3+atom14*atom4)*atom1556+atom1560*(atom16*atom3+atom4*atom8);
atom1549 = atom14*atom1523+atom12*atom1516+atom1518*atom8;
atom1551 = atom844*atom1531+atom841*atom1525+atom847*atom1549;
atom1744 = -atom1551*bR*C22R*G_elastic*aR+bR*atom1736*G_elastic*atom1569*C23R*aR;
atom1747 = aR^2;
atom1746 = bR^2;
atom1749 = -C33R*atom1747*G_elastic*atom1569*atom1746-atom1551*bR*atom1736*G_elastic*C23R*aR;
atom2 = sin(b);
atom71 = -atom2*atom3;
atom1 = cos(b);
atom72 = atom1*atom3;
atom1376 = atom4^2+atom71^2+atom72^2;
atom150 = -atom2*atom145+atom5*atom1;
atom153 = atom5*atom2+atom1*atom145;
atom1389 = atom144*atom4+atom72*atom153+atom71*atom150;
atom1392 = -atom781*atom1389+atom1376*atom779;
atom156 = atom1*atom6-atom2*atom147;
atom159 = atom2*atom6+atom1*atom147;
atom1382 = atom4*atom146+atom159*atom72+atom71*atom156;
atom1384 = atom781*atom1382-atom1376*atom780;
atom1395 = atom1389*atom780-atom1382*atom779;
atom1750 = -C11R*bR*G_elastic*aR*(atom1392*atom1528+atom1384*atom1513+atom1539*atom1395);
atom46 = -atom28*atom4+atom14*atom3;
atom25 = atom5*atom13+atom10*atom6;
atom15 = atom5*atom7;
atom34 = atom3*atom8-atom16*atom4;
atom40 = atom12*atom3-atom22*atom4;
atom19 = atom5*atom11+atom9*atom6;
atom1591 = -atom1566*(atom2*atom40-atom1*atom19)+(atom1*atom25-atom2*atom46)*atom1556-atom1560*(atom34*atom2-atom1*atom15);
atom1584 = (atom1*atom40+atom2*atom19)*atom1566+(atom25*atom2+atom1*atom46)*atom1556+atom1560*(atom2*atom15+atom34*atom1);
atom1594 = atom1591*atom71+atom1584*atom72+atom1569*atom4;
atom1579 = atom1384*atom1525+atom1392*atom1531+atom1395*atom1549;
atom1753 = -bR*atom1579*C22R*G_elastic*aR+atom1594*bR*atom1736*G_elastic*C23R*aR;
atom1756 = -C33R*atom1594*atom1747*G_elastic*atom1746-bR*atom1736*atom1579*G_elastic*C23R*aR;
atom1757 = -atom1539*C11R*bR*G_elastic*aR;
atom1758 = -bR*C22R*G_elastic*aR*atom1549;
atom1759 = -bR*atom1736*G_elastic*C23R*aR*atom1549;
atom1410 = atom1*atom156+atom2*atom159;
atom1415 = atom1*atom150+atom2*atom153;
atom1421 = atom780*atom1415-atom1410*atom779;
atom1406 = atom2*atom72+atom1*atom71;
atom1418 = -atom781*atom1415+atom1406*atom779;
atom1412 = -atom1406*atom780+atom781*atom1410;
atom1760 = -C11R*bR*(atom1539*atom1421+atom1412*atom1513+atom1418*atom1528)*G_elastic*aR;
atom1604 = atom1421*atom1549+atom1412*atom1525+atom1418*atom1531;
atom1607 = atom1584*atom2+atom1*atom1591;
atom1763 = -bR*C22R*G_elastic*atom1604*aR+bR*atom1736*G_elastic*atom1607*C23R*aR;
atom1766 = -C33R*atom1747*G_elastic*atom1607*atom1746-bR*atom1736*G_elastic*C23R*atom1604*aR;

CKR_ = [atom458*atom1733 , atom459*atom1733+atom462*atom1734 , atom1725*atom1734+atom1063*atom1737+atom1716*atom1733 , atom454*atom1737+atom1726*atom1734+atom1719*atom1733 , atom463*atom1734 , atom1732*atom1737+atom1729*atom1734+atom1722*atom1733;
atom458*atom1738 , atom462*atom1739+atom459*atom1738 , atom1738*atom1716+atom1740*atom1063+atom1725*atom1739 , atom1719*atom1738+atom1740*atom454+atom1739*atom1726 , atom1739*atom463 , atom1739*atom1729+atom1732*atom1740+atom1722*atom1738;
atom1741*atom458 , atom459*atom1741+atom1744*atom462 , atom1744*atom1725+atom1741*atom1716+atom1063*atom1749 , atom1744*atom1726+atom454*atom1749+atom1741*atom1719 , atom1744*atom463 , atom1732*atom1749+atom1741*atom1722+atom1744*atom1729;
atom1750*atom458 , atom459*atom1750+atom462*atom1753 , atom1750*atom1716+atom1725*atom1753+atom1756*atom1063 , atom1750*atom1719+atom1726*atom1753+atom454*atom1756 , atom463*atom1753 , atom1729*atom1753+atom1732*atom1756+atom1750*atom1722;
atom1757*atom458 , atom462*atom1758+atom1757*atom459 , atom1063*atom1759+atom1758*atom1725+atom1757*atom1716 , atom454*atom1759+atom1757*atom1719+atom1758*atom1726 , atom1758*atom463 , atom1757*atom1722+atom1758*atom1729+atom1732*atom1759;
atom1760*atom458 , atom462*atom1763+atom1760*atom459 , atom1766*atom1063+atom1760*atom1716+atom1725*atom1763 , atom1760*atom1719+atom1763*atom1726+atom1766*atom454 , atom1763*atom463 , atom1763*atom1729+atom1766*atom1732+atom1760*atom1722];

%endfunction
