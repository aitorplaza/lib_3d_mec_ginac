function dPhi_dq_ = dPhi_dq(q,qaux,time,param)

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
as = param( 12 ); 
bs = param( 13 ); 
cs = param( 14 ); 
ds = param( 15 ); 
es = param( 16 ); 
fs = param( 17 ); 
stas = param( 18 ); 
ends = param( 19 ); 
aW_R = param( 20 ); 
bW_R = param( 21 ); 
cW_R = param( 22 ); 
dW_R = param( 23 ); 
lW_R = param( 24 ); 
aR_R = param( 25 ); 
bR_R = param( 26 ); 
cR_R = param( 27 ); 
dR_R = param( 28 ); 
lR_R = param( 29 ); 
aW_L = param( 30 ); 
bW_L = param( 31 ); 
cW_L = param( 32 ); 
dW_L = param( 33 ); 
lW_L = param( 34 ); 
aR_L = param( 35 ); 
bR_L = param( 36 ); 
cR_L = param( 37 ); 
dR_L = param( 38 ); 
lR_L = param( 39 ); 
E_elastic = param( 40 ); 
nu_poisson = param( 41 ); 
G_elastic = param( 42 ); 
aR = param( 43 ); 
bR = param( 44 ); 
aL = param( 45 ); 
bL = param( 46 ); 
C11R = param( 47 ); 
C22R = param( 48 ); 
C23R = param( 49 ); 
C33R = param( 50 ); 
C11L = param( 51 ); 
C22L = param( 52 ); 
C23L = param( 53 ); 
C33L = param( 54 ); 
y0 = param( 55 ); 
b0 = param( 56 ); 

atom380 = ends-stas;
atom379 = sR_R-stas;
atom381 = atom380^(-1);
atom382 = atom379*atom381;
atom384 = bs+atom382*as;
atom386 = atom382*atom384+cs;
atom388 = ds+atom382*atom386;
atom393 = atom381*as;
atom396 = atom384*atom381+atom382*atom393;
atom399 = atom382*atom396+atom386*atom381;
atom402 = atom382*atom399+atom381*atom388;
atom390 = atom382*atom388+es;
atom405 = atom382*atom402+atom381*atom390;
atom407 = 1+atom405^2;
atom408 = sqrt(atom407);
atom418 = 2*atom393*atom381;
atom416 = atom396*atom381;
atom421 = atom418*atom382+2*atom416;
atom415 = atom381*atom399;
atom424 = 2*atom415+atom382*atom421;
atom426 = atom381*atom402;
atom428 = atom382*atom424+2*atom426;
atom429 = 2*atom405*atom428;
atom430 = atom407^(-1/2);
atom432 = atom408^(-2);
atom431 = 1/2*atom429*atom430;
atom433 = -atom432*atom431;
atom409 = atom408^(-1);
atom435 = (0.5)*L_R*atom428*atom409;
atom437 = 1+(0.5)*L_R*atom433*atom405+atom435;
atom439 = atom405-(0.5)*L_R*atom433;
atom448 = atom437^2;
atom456 = (atom439^2+atom448)^(-1/2);
atom4 = sin(a);
atom5 = cos(c);
atom308 = lW_R-uW_R;
atom309 = -atom308*aW_R;
atom310 = bW_R+atom309;
atom312 = cW_R-atom308*atom310;
atom317 = cos(thetaW_R);
atom314 = dW_R-atom312*atom308;
atom147 = -atom4*atom5;
atom318 = atom317*atom314;
atom3 = cos(a);
atom146 = atom5*atom3;
atom315 = sin(thetaW_R);
atom316 = -atom315*atom314;
atom6 = sin(c);
atom330 = atom316*atom6;
atom333 = atom147*atom318;
atom307 = -(0.5)*L_WHS;
atom334 = atom146*uW_R+atom333+atom330;
atom320 = atom307*atom146;
atom1147 = -atom334-atom320;
atom457 = atom456*atom437;
atom145 = atom4*atom6;
atom144 = -atom6*atom3;
atom325 = atom5*atom316;
atom328 = atom318*atom145;
atom329 = atom328+atom325+atom144*uW_R;
atom319 = atom144*atom307;
atom458 = atom456*atom439;
atom1149 = atom329+atom319;
atom1161 = atom147*atom307;
atom1162 = atom1161-atom146*atom318+atom147*uW_R;
atom1152 = atom307*atom145;
atom1156 = -atom144*atom318+atom1152+uW_R*atom145;
atom346 = -atom318*atom6+atom147*atom316;
atom343 = -atom5*atom318+atom316*atom145;
atom348 = atom310+atom309;
atom350 = atom312-atom308*atom348;
atom353 = -atom350*atom315;
atom351 = atom350*atom317;
atom356 = atom144+atom351*atom145+atom353*atom5;
atom360 = atom146+atom147*atom351+atom353*atom6;
atom1194 = atom381*((sR_R-stas)*atom381*((sR_R-stas)*atom381^2*as+atom381*(bs+(sR_R-stas)*atom381*as))+atom381*(cs+(sR_R-stas)*atom381*(bs+(sR_R-stas)*atom381*as)))+atom379*atom381*((atom381*(bs+atom379*atom381*as)+atom379*atom381^2*as)*atom381+atom379*atom381^3*as);
atom1199 = atom381*(es+((sR_R-stas)*atom381*(cs+(sR_R-stas)*atom381*(bs+(sR_R-stas)*atom381*as))+ds)*(sR_R-stas)*atom381);
atom1200 = atom379*atom381*(atom381*((cs+atom379*atom381*(bs+atom379*atom381*as))*atom379*atom381+ds)+(atom379*(atom381*(bs+atom379*atom381*as)+atom379*atom381^2*as)*atom381+(cs+atom379*atom381*(bs+atom379*atom381*as))*atom381)*atom379*atom381);
atom1201 = atom1199+atom1200;
atom1202 = atom1201^2;
atom1203 = 1+atom1202;
atom1186 = atom381*((cs+atom379*atom381*(bs+atom379*atom381*as))*atom379*atom381+ds)+(atom379*(atom381*(bs+atom379*atom381*as)+atom379*atom381^2*as)*atom381+(cs+atom379*atom381*(bs+atom379*atom381*as))*atom381)*atom379*atom381;
atom1196 = atom381*atom1186+atom379*atom381*atom1194;
atom1209 = atom1196^2;
atom1220 = atom379*atom381*(atom379*atom380^(-4)*as+atom381*(atom379*atom380^(-3)*as+atom381*((sR_R-stas)*atom381^2*as+atom381*(bs+(sR_R-stas)*atom381*as))))+atom381*atom1194;
atom1236 = 2*atom381*atom1186+2*atom379*atom381*atom1194+3*L_R*atom1201*(1+atom1201^2)^(-3/2)*atom1220-6*L_R*atom1202*(1+atom1202)^(-5/2)*atom1209+2*L_R*atom1203^(-3/2)*atom1209;
atom1230 = L_R*(((ds+(sR_R-stas)*(ends-stas)^(-1)*(cs+(bs+(sR_R-stas)*(ends-stas)^(-1)*as)*(sR_R-stas)*(ends-stas)^(-1)))*(ends-stas)^(-1)+(sR_R-stas)*(ends-stas)^(-1)*((sR_R-stas)*(ends-stas)^(-1)*((sR_R-stas)*(ends-stas)^(-2)*as+(bs+(sR_R-stas)*(ends-stas)^(-1)*as)*(ends-stas)^(-1))+(ends-stas)^(-1)*(cs+(bs+(sR_R-stas)*(ends-stas)^(-1)*as)*(sR_R-stas)*(ends-stas)^(-1))))*(ends-stas)^(-1)+((sR_R-stas)*((sR_R-stas)*(ends-stas)^(-3)*as+(ends-stas)^(-1)*((sR_R-stas)*(ends-stas)^(-2)*as+(bs+(sR_R-stas)*(ends-stas)^(-1)*as)*(ends-stas)^(-1)))*(ends-stas)^(-1)+(ends-stas)^(-1)*((sR_R-stas)*(ends-stas)^(-1)*((sR_R-stas)*(ends-stas)^(-2)*as+(bs+(sR_R-stas)*(ends-stas)^(-1)*as)*(ends-stas)^(-1))+(ends-stas)^(-1)*(cs+(bs+(sR_R-stas)*(ends-stas)^(-1)*as)*(sR_R-stas)*(ends-stas)^(-1))))*(sR_R-stas)*(ends-stas)^(-1))*(atom1199+atom1200)*(1+(atom1199+atom1200)^2)^(-3/2)+atom1199+atom1200;
atom1222 = atom1203^(-1/2);
atom1227 = 1-L_R*atom1202*(1+atom1202)^(-3/2)*atom1196+L_R*atom1222*atom1196;
atom1224 = (6.0)*L_R*atom1201^3*atom1203^(-5/2)*atom1209+3*L_R*atom1222*atom1220-(3.0)*L_R*atom1202*(1+atom1202)^(-3/2)*atom1220-(6.0)*L_R*atom1201*(1+atom1201^2)^(-3/2)*atom1209;
atom1228 = atom1227*atom1224;
atom1240 = atom1230^2;
atom1239 = atom1227^2;
atom1243 = -(atom1236*atom1230+atom1228)*(atom1240+atom1239)^(-3/2);
atom1205 = -2*atom1201*(1+atom1201^2)^(-3/2)*atom1196;
atom1247 = atom418*atom381;
atom1249 = 3*atom1247;
atom1246 = atom381*atom421;
atom1255 = atom381*atom424;
atom1258 = atom382*(atom382*atom1249+3*atom1246)+3*atom1255;
atom1268 = 4*atom1201*(1+atom1201^2)^(-2)*atom431*atom1196-1/2*(atom429*atom1205+atom430*(2*atom428^2+2*atom405*atom1258))*atom432;
atom1283 = atom428-(0.5)*L_R*atom1268;
atom464 = atom334-atom382*atom390-uR_R+(0.5)*L_R*atom409-fs+y+atom320;
atom1288 = atom405-(0.5)*L_R*atom1205;
atom1275 = (0.5)*L_R*atom433*atom428+(0.5)*L_R*atom409*atom1258+(0.5)*L_R*atom405*atom1268+(0.5)*L_R*atom1205*atom428;
atom463 = atom329-sR_R+atom319-(0.5)*L_R*atom405*atom409+x;
atom1208 = 1.0+atom435+(0.5)*L_R*atom1205*atom405;
atom372 = uR_R-lR_R;
atom373 = aR_R*atom372;
atom374 = bR_R+atom373;
atom440 = atom374+atom373;
atom376 = atom374*atom372+cR_R;
atom442 = atom376+atom440*atom372;
atom461 = (1+atom442^2)^(-1/2);
atom1070 = atom307*atom3;
atom462 = atom461*atom442;
atom1295 = -atom4*atom318+atom1070+uW_R*atom3;
atom347 = atom316*atom3;
atom362 = atom4+atom351*atom3;
atom1069 = 2*atom440+2*aR_R*atom372;
atom1305 = bR_R+3*aR_R*atom372;
atom1310 = (bR_R+aR_R*atom372)*atom372+(bR_R+2*aR_R*atom372)*atom372+cR_R;
atom1314 = -2*atom1305*atom1310*(1+atom1310^2)^(-3/2);
atom321 = atom4*atom307;
atom336 = atom318*atom3;
atom465 = -dR_R+atom336-atom372*atom376+atom321+z+atom4*uW_R;
atom444 = -atom437*atom442;
atom443 = atom442*atom439;
atom450 = (atom444^2+atom443^2+atom448)^(-1/2);
atom451 = atom443*atom450;
atom452 = atom450*atom444;
atom453 = atom437*atom450;
atom1311 = atom1310^2;
atom1339 = (atom1239+atom1311*atom1239+atom1240*atom1311)^(-3/2);
atom1340 = -2*(atom1240*atom1305*atom1310+atom1305*atom1310*atom1239)*atom1339;
atom1341 = atom1340*atom437;
atom1354 = atom1340*atom443+atom450*atom1069*atom439;
atom1348 = atom1340*atom444-atom437*atom450*atom1069;
atom1361 = -(atom1311*atom1227*atom1224+atom1236*atom1311*atom1230+atom1228)*atom1339;
atom1369 = -atom450*atom442*atom1275+atom444*atom1361;
atom1376 = atom443*atom1361+atom1283*atom450*atom442;
atom1364 = atom437*atom1361+atom450*atom1275;
atom1437 = -(2.0)*atom308*aW_R+2*atom348;
atom1438 = atom1437*atom317;
atom1442 = -atom1437*atom315;
atom564 = sR_L-stas;
atom565 = atom381*atom564;
atom567 = bs+atom565*as;
atom569 = atom565*atom567+cs;
atom571 = atom569*atom565+ds;
atom573 = es+atom565*atom571;
atom578 = atom567*atom381+atom565*atom393;
atom581 = atom565*atom578+atom569*atom381;
atom584 = atom581*atom565+atom571*atom381;
atom587 = atom573*atom381+atom565*atom584;
atom589 = 1+atom587^2;
atom599 = atom578*atom381;
atom602 = atom418*atom565+2*atom599;
atom598 = atom581*atom381;
atom605 = atom565*atom602+2*atom598;
atom597 = atom381*atom584;
atom608 = 2*atom597+atom565*atom605;
atom610 = atom589^(-1/2);
atom609 = 2*atom587*atom608;
atom590 = sqrt(atom589);
atom611 = 1/2*atom610*atom609;
atom612 = atom590^(-2);
atom613 = -atom611*atom612;
atom591 = atom590^(-1);
atom615 = -(0.5)*L_R*atom608*atom591;
atom617 = 1+atom615-(0.5)*L_R*atom613*atom587;
atom619 = atom587+(0.5)*L_R*atom613;
atom628 = atom617^2;
atom636 = (atom619^2+atom628)^(-1/2);
atom495 = uW_L-lW_L;
atom504 = cos(thetaW_L);
atom501 = dW_L+(cW_L+(atom495*aW_L+bW_L)*atom495)*atom495;
atom505 = atom504*atom501;
atom502 = sin(thetaW_L);
atom503 = -atom501*atom502;
atom509 = atom503*atom5;
atom512 = atom505*atom145;
atom513 = atom144*uW_L+atom512+atom509;
atom638 = atom619*atom636;
atom1464 = -atom319+atom513;
atom514 = atom503*atom6;
atom517 = atom147*atom505;
atom518 = atom517+atom514+atom146*uW_L;
atom1462 = -atom518+atom320;
atom637 = atom636*atom617;
atom1475 = atom147*uW_L-atom1161-atom505*atom146;
atom1470 = -atom1152-atom144*atom505+uW_L*atom145;
atom530 = -atom505*atom6+atom147*atom503;
atom527 = atom503*atom145-atom5*atom505;
atom533 = 2*atom495*aW_L+bW_L;
atom535 = cW_L+(atom495*aW_L+bW_L)*atom495+atom495*atom533;
atom536 = atom504*atom535;
atom538 = -atom535*atom502;
atom541 = atom5*atom538+atom144+atom536*atom145;
atom545 = atom147*atom536+atom538*atom6+atom146;
atom1505 = ((atom381^2*as*atom564+(bs+atom381*as*atom564)*atom381)*atom381*atom564+atom381*(cs+(bs+atom381*as*atom564)*atom381*atom564))*atom381*atom564+(atom381*(cs+(bs+atom381*as*atom564)*atom381*atom564)*atom564+ds)*atom381;
atom1499 = atom381*((atom381*(atom381*(sR_L-stas)*as+bs)+atom381^2*(sR_L-stas)*as)*atom381*(sR_L-stas)+(atom381*(sR_L-stas)*(atom381*(sR_L-stas)*as+bs)+cs)*atom381)+(atom381^3*as*atom564+(atom381^2*as*atom564+(bs+atom381*as*atom564)*atom381)*atom381)*atom381*atom564;
atom1508 = atom381*atom1505*atom564;
atom1511 = atom381*(es+((atom381*(sR_L-stas)*(atom381*(sR_L-stas)*as+bs)+cs)*atom381*(sR_L-stas)+ds)*atom381*(sR_L-stas));
atom1512 = atom1508+atom1511;
atom1513 = atom1512^2;
atom1514 = 1+atom1513;
atom1507 = atom1499*atom381*atom564+atom381*atom1505;
atom1515 = atom1514^(-3/2);
atom1516 = -2*atom1507*atom1512*atom1515;
atom1595 = atom587+(0.5)*L_R*atom1516;
atom1520 = atom1514^(-1/2);
atom1537 = 1+L_R*atom1507*atom1513*atom1515-L_R*atom1507*atom1520;
atom1540 = atom1508+atom1511-L_R*(1+(atom1508+atom1511)^2)^(-3/2)*(((ends-stas)^(-1)*((ends-stas)^(-1)*(cs+(bs+(ends-stas)^(-1)*(sR_L-stas)*as)*(ends-stas)^(-1)*(sR_L-stas))+((bs+(ends-stas)^(-1)*(sR_L-stas)*as)*(ends-stas)^(-1)+(ends-stas)^(-2)*(sR_L-stas)*as)*(ends-stas)^(-1)*(sR_L-stas))+(ends-stas)^(-1)*(sR_L-stas)*(((bs+(ends-stas)^(-1)*(sR_L-stas)*as)*(ends-stas)^(-1)+(ends-stas)^(-2)*(sR_L-stas)*as)*(ends-stas)^(-1)+(ends-stas)^(-3)*(sR_L-stas)*as))*(ends-stas)^(-1)*(sR_L-stas)+((ends-stas)^(-1)*((ends-stas)^(-1)*(cs+(bs+(ends-stas)^(-1)*(sR_L-stas)*as)*(ends-stas)^(-1)*(sR_L-stas))+((bs+(ends-stas)^(-1)*(sR_L-stas)*as)*(ends-stas)^(-1)+(ends-stas)^(-2)*(sR_L-stas)*as)*(ends-stas)^(-1)*(sR_L-stas))*(sR_L-stas)+(ds+(ends-stas)^(-1)*(sR_L-stas)*(cs+(bs+(ends-stas)^(-1)*(sR_L-stas)*as)*(ends-stas)^(-1)*(sR_L-stas)))*(ends-stas)^(-1))*(ends-stas)^(-1))*(atom1508+atom1511);
atom1550 = atom1537^2;
atom1549 = atom1540^2;
atom1526 = atom1499*atom381+(atom381^4*as*atom564+(atom381^3*as*atom564+(atom381^2*as*atom564+(bs+atom381*as*atom564)*atom381)*atom381)*atom381)*atom381*atom564;
atom1528 = atom1507^2;
atom1529 = atom1514^(-5/2);
atom1546 = 2*atom1499*atom381*atom564+(6.0)*L_R*atom1528*atom1513*atom1529+2*atom381*atom1505-(2.0)*L_R*atom1528*atom1515-(3.0)*L_R*atom1512*atom1526*atom1515;
atom1538 = atom1537*(3*L_R*atom1526*atom1513*atom1515-(3.0)*L_R*atom1526*atom1520-6*L_R*atom1512^3*atom1528*atom1529+(6.0)*L_R*atom1512*atom1528*atom1515);
atom1553 = -(atom1550+atom1549)^(-3/2)*(atom1538+atom1540*atom1546);
atom1555 = atom602*atom381;
atom1554 = atom381*atom605;
atom1563 = atom565*(3*atom1555+atom565*atom1249)+3*atom1554;
atom1575 = 4*atom1507*atom1512*atom1514^(-2)*atom611-1/2*(atom610*(2*atom608^2+2*atom1563*atom587)+atom609*atom1516)*atom612;
atom1590 = atom608+(0.5)*L_R*atom1575;
atom644 = -atom565*atom573-uR_L-fs-(0.5)*L_R*atom591+y+atom518-atom320;
atom1519 = 1.0+atom615-(0.5)*L_R*atom587*atom1516;
atom1582 = -(0.5)*L_R*atom1516*atom608-(0.5)*L_R*atom613*atom608-(0.5)*atom1563*L_R*atom591-(0.5)*L_R*atom587*atom1575;
atom643 = -atom319+(0.5)*L_R*atom587*atom591-sR_L+atom513+x;
atom557 = uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 = atom558+bR_L;
atom560 = atom557*atom559;
atom620 = atom558+atom559;
atom561 = cR_L+atom560;
atom622 = atom561+atom620*atom557;
atom641 = (1+atom622^2)^(-1/2);
atom642 = atom622*atom641;
atom1602 = -atom1070-atom4*atom505+uW_L*atom3;
atom531 = atom503*atom3;
atom547 = atom4+atom536*atom3;
atom1120 = 2*atom620+2*aR_L*atom557;
atom1614 = atom557*(2*aR_L*atom557+bR_L)+cR_L+atom560;
atom1616 = 3*aR_L*atom557+bR_L;
atom1620 = -2*atom1614*(1+atom1614^2)^(-3/2)*atom1616;
atom520 = atom505*atom3;
atom645 = atom4*uW_L-atom321+z-dR_L+atom520-atom561*atom557;
atom624 = -atom622*atom617;
atom623 = atom622*atom619;
atom630 = (atom628+atom624^2+atom623^2)^(-1/2);
atom632 = atom630*atom624;
atom631 = atom630*atom623;
atom633 = atom630*atom617;
atom1617 = atom1614^2;
atom1645 = (atom1617*atom1549+atom1550*atom1617+atom1550)^(-3/2);
atom1646 = -2*(atom1614*atom1550*atom1616+atom1614*atom1549*atom1616)*atom1645;
atom1660 = atom630*atom1120*atom619+atom623*atom1646;
atom1654 = atom624*atom1646-atom630*atom1120*atom617;
atom1647 = atom1646*atom617;
atom1667 = -atom1645*(atom1538+atom1540*atom1617*atom1546+atom1538*((uR_L-lR_L)*(2*aR_L*(uR_L-lR_L)+bR_L)+cR_L+(aR_L*(uR_L-lR_L)+bR_L)*(uR_L-lR_L))^2);
atom1675 = -atom1582*atom622*atom630+atom624*atom1667;
atom1682 = atom622*atom630*atom1590+atom623*atom1667;
atom1670 = atom1667*atom617+atom1582*atom630;
atom1116 = 2*atom533+(2.0)*atom495*aW_L;
atom1744 = -atom1116*atom502;
atom1742 = atom1116*atom504;
atom1411 = atom353*atom453*atom3+atom452*(atom147*atom353-atom351*atom6)+atom451*(atom353*atom145-atom5*atom351);
atom1717 = (atom147*atom538-atom536*atom6)*atom632+atom631*(atom538*atom145-atom5*atom536)+atom633*atom538*atom3;

dPhi_dq_ = [atom457 , atom458 , 0.0 , atom1147*atom457+atom458*atom1149 , 0.0 , atom1156*atom457+atom458*atom1162 , atom343*atom457+atom458*atom346 , atom356*atom457+atom458*atom360 , -atom458 , atom463*(atom456*atom1275+atom1243*atom437)-atom458*atom1288-atom1208*atom457+atom464*(atom1283*atom456+atom1243*atom439) , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , atom461 , 0.0 , atom461*atom1149 , atom462 , atom462*atom1295+atom461*atom1162 , atom347*atom462+atom461*atom346 , atom461*atom360+atom462*atom362 , -atom461-atom462*atom442+atom1314*atom464+(atom1314*atom442+atom461*atom1069)*atom465 , -atom461*atom1288 , 0.0 , 0.0 , 0.0 , 0.0;
atom451 , atom452 , 0.0 , atom452*atom1149+atom451*atom1147 , atom453 , atom451*atom1156+atom453*atom1295+atom452*atom1162 , atom451*atom343+atom452*atom346+atom453*atom347 , atom451*atom356+atom360*atom452+atom453*atom362 , atom464*atom1348-atom453*atom442+atom465*atom1341-atom452+atom463*atom1354 , -atom1288*atom452+atom1369*atom464+atom463*atom1376+atom465*atom1364-atom451*atom1208 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , atom452*atom343-atom451*atom346 , 0.0 , -atom451*atom144*atom316-atom4*atom453*atom316-atom146*atom316*atom452 , -atom453*atom336-atom451*(atom328+atom325)-atom452*(atom333+atom330) , atom1411 , atom1348*atom346+atom343*atom1354+atom347*atom1341 , atom343*atom1376+atom1369*atom346+atom347*atom1364 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , -atom451*atom360+atom356*atom452 , 0.0 , atom452*(atom147-atom146*atom351)-atom453*(atom4*atom351-atom3)-atom451*(atom144*atom351-atom145) , atom1411 , (atom147*atom1438+atom1442*atom6)*atom452+atom451*(atom1438*atom145+atom1442*atom5)+atom453*atom1438*atom3 , atom360*atom1348+atom356*atom1354+atom362*atom1341 , atom356*atom1376+atom1369*atom360+atom362*atom1364 , 0.0 , 0.0 , 0.0 , 0.0;
atom637 , atom638 , 0.0 , atom1462*atom637+atom638*atom1464 , 0.0 , atom1470*atom637+atom638*atom1475 , 0.0 , 0.0 , 0.0 , 0.0 , atom527*atom637+atom638*atom530 , atom545*atom638+atom637*atom541 , -atom638 , atom643*(atom1582*atom636+atom1553*atom617)-atom1519*atom637+atom644*(atom619*atom1553+atom1590*atom636)-atom638*atom1595;
0.0 , atom641 , 0.0 , atom641*atom1464 , atom642 , atom642*atom1602+atom1475*atom641 , 0.0 , 0.0 , 0.0 , 0.0 , atom531*atom642+atom530*atom641 , atom642*atom547+atom545*atom641 , atom1620*atom644-atom642*atom622-atom641+atom645*(atom1620*atom622+atom1120*atom641) , -atom641*atom1595;
atom631 , atom632 , 0.0 , atom631*atom1462+atom632*atom1464 , atom633 , atom631*atom1470+atom1475*atom632+atom633*atom1602 , 0.0 , 0.0 , 0.0 , 0.0 , atom531*atom633+atom631*atom527+atom530*atom632 , atom545*atom632+atom633*atom547+atom631*atom541 , atom645*atom1647+atom643*atom1660-atom632-atom633*atom622+atom644*atom1654 , atom1675*atom644+atom643*atom1682+atom645*atom1670-atom631*atom1519-atom632*atom1595;
0.0 , 0.0 , 0.0 , atom527*atom632-atom631*atom530 , 0.0 , -atom631*atom503*atom144-atom503*atom146*atom632-atom503*atom4*atom633 , 0.0 , 0.0 , 0.0 , 0.0 , -atom632*(atom517+atom514)-atom631*(atom512+atom509)-atom633*atom520 , atom1717 , atom1654*atom530+atom527*atom1660+atom531*atom1647 , atom1675*atom530+atom527*atom1682+atom531*atom1670;
0.0 , 0.0 , 0.0 , -atom631*atom545+atom632*atom541 , 0.0 , -atom633*(atom4*atom536-atom3)-atom631*(atom144*atom536-atom145)+atom632*(atom147-atom146*atom536) , 0.0 , 0.0 , 0.0 , 0.0 , atom1717 , (atom1744*atom6+atom147*atom1742)*atom632+atom633*atom3*atom1742+atom631*(atom1742*atom145+atom1744*atom5) , atom547*atom1647+atom1660*atom541+atom545*atom1654 , atom547*atom1670+atom545*atom1675+atom1682*atom541];

%endfunction
