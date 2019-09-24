function dPhic_dq_ = dPhic_dq(q,qaux,time,param)

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

atom372 = uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 = bR_R+atom373;
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
atom443 = atom374*atom372+cR_R+atom372*(atom374+atom373);
atom438 = 1+(0.5)*atom408^(-1)*atom429*L_R+(0.5)*atom405*atom434*L_R;
atom445 = -atom438*atom443;
atom444 = (atom405-(0.5)*atom434*L_R)*atom443;
atom451 = (atom438^2+atom444^2+atom445^2)^(-1/2);
atom5 = cos(c);
atom3 = cos(a);
atom307 = -(0.5)*L_WHS;
atom146 = atom5*atom3;
atom309 = uW_R-lW_R;
atom315 = atom309*(cW_R+(aW_R*atom309+bW_R)*atom309)+dW_R;
atom6 = sin(c);
atom316 = -atom315*sin(thetaW_R);
atom4 = sin(a);
atom318 = atom315*cos(thetaW_R);
atom147 = -atom5*atom4;
atom320 = atom307*atom146;
atom452 = atom444*atom451;
atom144 = -atom6*atom3;
atom145 = atom6*atom4;
atom319 = atom144*atom307;
atom453 = atom451*atom445;
atom1076 = atom3*atom307;
atom454 = atom438*atom451;
atom2108 = atom147*atom307;
atom2061 = atom145*atom307;
atom566 = (endsL-stasL)^(-1);
atom567 = (sR_L-stasL)*atom566;
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
atom623 = 1-(0.5)*atom590*L_R*atom619-(0.5)*atom593^(-1)*atom614*L_R;
atom630 = -atom623*atom628;
atom629 = (atom590+(0.5)*L_R*atom619)*atom628;
atom636 = (atom623^2+atom629^2+atom630^2)^(-1/2);
atom497 = uW_L-lW_L;
atom503 = dW_L+atom497*(atom497*(atom497*aW_L+bW_L)+cW_L);
atom506 = cos(thetaW_L)*atom503;
atom504 = -atom503*sin(thetaW_L);
atom638 = atom630*atom636;
atom637 = atom629*atom636;
atom639 = atom623*atom636;

dPhic_dq_ = [atom452 , atom453 , 0.0 , -atom452*(atom320+uW_R*atom146+atom6*atom316+atom318*atom147)+(atom5*atom316+atom318*atom145+uW_R*atom144+atom319)*atom453 , atom454 , (uW_R*atom3-atom318*atom4+atom1076)*atom454-(atom318*atom146-uW_R*atom147-atom2108)*atom453+atom452*(atom2061+uW_R*atom145-atom318*atom144);
atom637 , atom638 , 0.0 , atom637*(atom320-uW_L*atom146-atom506*atom147-atom6*atom504)+atom638*(atom5*atom504+atom506*atom145+atom144*uW_L-atom319) , atom639 , -(atom506*atom146-atom147*uW_L+atom2108)*atom638+(atom145*uW_L-atom2061-atom506*atom144)*atom637-(atom506*atom4-atom3*uW_L+atom1076)*atom639];

%endfunction