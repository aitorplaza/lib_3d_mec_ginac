function dPhic_d_s = dPhic_ds(q,qaux,time,param)

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

atom309 = uW_R-lW_R;
atom310 = aW_R*atom309;
atom311 = bW_R+atom310;
atom313 = atom309*atom311+cW_R;
atom308 = sin(thetaW_R);
atom315 = dW_R+atom313*atom309;
atom3 = cos(a);
atom316 = -atom308*atom315;
atom381 = (endsR-stasR)^(-1);
atom379 = sR_R-stasR;
atom382 = atom381*atom379;
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
atom436 = (0.5)*atom408^(-1)*atom429*L_R;
atom438 = 1+(0.5)*atom405*atom434*L_R+atom436;
atom372 = uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 = bR_R+atom373;
atom443 = atom374*atom372+cR_R+atom372*(atom374+atom373);
atom445 = -atom438*atom443;
atom444 = (atom405-(0.5)*atom434*L_R)*atom443;
atom451 = (atom438^2+atom444^2+atom445^2)^(-1/2);
atom454 = atom438*atom451;
atom5 = cos(c);
atom4 = sin(a);
atom147 = -atom5*atom4;
atom317 = cos(thetaW_R);
atom318 = atom315*atom317;
atom6 = sin(c);
atom453 = atom451*atom445;
atom145 = atom6*atom4;
atom452 = atom444*atom451;
atom350 = atom313+(atom310+atom311)*atom309;
atom354 = atom350*atom317;
atom351 = -atom308*atom350;
atom146 = atom5*atom3;
atom144 = -atom6*atom3;
atom2086 = atom381*((atom381*(csR+(bsR+atom381*asR*atom379)*atom381*atom379)+atom381*(atom381^2*asR*atom379+(bsR+atom381*asR*atom379)*atom381)*atom379)*atom381*atom379+atom381*(atom381*(csR+(bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR))*atom379+atom381*(esR+atom381*(atom381*(csR+(bsR+atom381*asR*atom379)*atom381*atom379)*atom379+dsR)*atom379);
atom2100 = -2*(atom381*((sR_R-stasR)*((sR_R-stasR)*atom381*((bsR+(sR_R-stasR)*atom381*asR)*atom381+(sR_R-stasR)*atom381^2*asR)+atom381*((bsR+(sR_R-stasR)*atom381*asR)*(sR_R-stasR)*atom381+csR))*atom381+atom381*((sR_R-stasR)*atom381*((bsR+(sR_R-stasR)*atom381*asR)*(sR_R-stasR)*atom381+csR)+dsR))+atom381*((atom381*(atom381^2*asR*atom379+(bsR+atom381*asR*atom379)*atom381)+atom381^3*asR*atom379)*atom381*atom379+((sR_R-stasR)*atom381*((bsR+(sR_R-stasR)*atom381*asR)*atom381+(sR_R-stasR)*atom381^2*asR)+atom381*((bsR+(sR_R-stasR)*atom381*asR)*(sR_R-stasR)*atom381+csR))*atom381)*atom379)*(1+atom2086^2)^(-3/2)*atom2086;
atom564 = sR_L-stasL;
atom566 = (endsL-stasL)^(-1);
atom567 = atom564*atom566;
atom569 = bsL+atom567*asL;
atom571 = atom567*atom569+csL;
atom573 = atom567*atom571+dsL;
atom578 = atom566*asL;
atom581 = atom567*atom578+atom569*atom566;
atom584 = atom571*atom566+atom581*atom567;
atom587 = atom573*atom566+atom584*atom567;
atom590 = (esL+atom567*atom573)*atom566+atom567*atom587;
atom592 = 1+atom590^2;
atom593 = sqrt(atom592);
atom605 = atom581*atom566;
atom609 = atom584*atom566;
atom601 = atom587*atom566;
atom614 = 2*(atom567*(atom605+atom567*atom578*atom566)+atom609)*atom567+2*atom601;
atom619 = -atom593^(-2)*atom614*atom590*atom592^(-1/2);
atom557 = uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 = bR_L+atom558;
atom628 = atom559*atom557+cR_L+(atom559+atom558)*atom557;
atom620 = -(0.5)*atom593^(-1)*atom614*L_R;
atom623 = 1-(0.5)*atom590*L_R*atom619+atom620;
atom630 = -atom623*atom628;
atom629 = (atom590+(0.5)*L_R*atom619)*atom628;
atom636 = (atom623^2+atom629^2+atom630^2)^(-1/2);
atom497 = uW_L-lW_L;
atom498 = atom497*aW_L;
atom499 = atom498+bW_L;
atom501 = cW_L+atom497*atom499;
atom503 = dW_L+atom497*atom501;
atom505 = cos(thetaW_L);
atom506 = atom503*atom505;
atom496 = sin(thetaW_L);
atom504 = -atom503*atom496;
atom637 = atom629*atom636;
atom638 = atom630*atom636;
atom639 = atom623*atom636;
atom535 = atom501+atom497*(atom498+atom499);
atom538 = -atom535*atom496;
atom536 = atom535*atom505;
atom2160 = (esL+atom564*atom566*(atom564*atom566*(atom564*(bsL+atom564*atom566*asL)*atom566+csL)+dsL))*atom566+atom564*(atom566*(atom564*atom566*(atom564*(bsL+atom564*atom566*asL)*atom566+csL)+dsL)+atom564*(atom566*(atom564*(bsL+atom564*atom566*asL)*atom566+csL)+atom564*(atom564*atom566^2*asL+(bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566;
atom2174 = -2*atom2160*(((((sR_L-stasL)*atom566*(bsL+(sR_L-stasL)*atom566*asL)+csL)*(sR_L-stasL)*atom566+dsL)*atom566+atom564*(atom566*(atom564*(bsL+atom564*atom566*asL)*atom566+csL)+atom564*(atom564*atom566^2*asL+(bsL+atom564*atom566*asL)*atom566)*atom566)*atom566)*atom566+((atom566*(atom564*(bsL+atom564*atom566*asL)*atom566+csL)+atom564*(atom564*atom566^2*asL+(bsL+atom564*atom566*asL)*atom566)*atom566)*atom566+(atom564*atom566^3*asL+(atom564*atom566^2*asL+(bsL+atom564*atom566*asL)*atom566)*atom566)*atom564*atom566)*atom564*atom566)*(1+atom2160^2)^(-3/2);

dPhic_d_s = [atom3*atom454*atom316-(atom318*atom6-atom147*atom316)*atom453+atom452*(atom145*atom316-atom318*atom5) , (atom6*atom351+atom147*atom354+atom146)*atom453+atom452*(atom144+atom5*atom351+atom145*atom354)+atom454*(atom3*atom354+atom4) , -atom453-atom454*atom443 , -(atom405-(0.5)*atom2100*L_R)*atom453-atom452*(1.0+(0.5)*atom405*atom2100*L_R+atom436) , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , -(atom5*atom506-atom145*atom504)*atom637+atom3*atom639*atom504+atom638*(atom147*atom504-atom506*atom6) , atom637*(atom144+atom5*atom538+atom145*atom536)+atom638*(atom147*atom536+atom538*atom6+atom146)+atom639*(atom3*atom536+atom4) , -atom638-atom639*atom628 , -atom637*(1.0-(0.5)*atom590*atom2174*L_R+atom620)-atom638*((0.5)*atom2174*L_R+atom590)];

%endfunction
