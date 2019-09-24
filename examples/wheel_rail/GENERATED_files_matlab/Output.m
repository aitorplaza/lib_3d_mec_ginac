function Output_ = Output(q,qaux,dq,dqaux,ddq,ddqaux,unknowns,time,param,inputs)

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

dthetaW_R = dqaux( 1 ); 
duW_R = dqaux( 2 ); 
duR_R = dqaux( 3 ); 
dsR_R = dqaux( 4 ); 
dthetaW_L = dqaux( 5 ); 
duW_L = dqaux( 6 ); 
duR_L = dqaux( 7 ); 
dsR_L = dqaux( 8 ); 

ddx = ddq( 1 ); 
ddy = ddq( 2 ); 
ddb = ddq( 3 ); 
ddc = ddq( 4 ); 
ddz = ddq( 5 ); 
dda = ddq( 6 ); 

ddthetaW_R = ddqaux( 1 ); 
dduW_R = ddqaux( 2 ); 
dduR_R = ddqaux( 3 ); 
ddsR_R = ddqaux( 4 ); 
ddthetaW_L = ddqaux( 5 ); 
dduW_L = ddqaux( 6 ); 
dduR_L = ddqaux( 7 ); 
ddsR_L = ddqaux( 8 ); 

lambda1 = unknowns( 1 ); 
lambda2 = unknowns( 2 ); 

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

Fx_R = inputs( 1 ); 
Fy_R = inputs( 2 ); 
Mz_R = inputs( 3 ); 
Fx_L = inputs( 4 ); 
Fy_L = inputs( 5 ); 
Mz_L = inputs( 6 ); 

atom4 = sin(a);
atom309 = uW_R-lW_R;
atom315 = atom309*(cW_R+(aW_R*atom309+bW_R)*atom309)+dW_R;
atom6 = sin(c);
atom316 = -atom315*sin(thetaW_R);
atom5 = cos(c);
atom3 = cos(a);
atom146 = atom5*atom3;
atom318 = atom315*cos(thetaW_R);
atom147 = -atom5*atom4;
atom307 = -(0.5)*L_WHS;
atom320 = atom307*atom146;
atom68 = dc+db*atom4;
atom780 = atom320+uW_R*atom146+atom6*atom316+atom318*atom147;
atom321 = atom307*atom4;
atom337 = uW_R*atom4+atom318*atom3;
atom66 = atom3*db;
atom781 = atom321+atom337;
atom787 = atom5*atom66+da*atom6;
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
atom784 = atom5*da-atom66*atom6;
atom144 = -atom6*atom3;
atom319 = atom144*atom307;
atom145 = atom6*atom4;
atom779 = atom5*atom316+atom318*atom145+uW_R*atom144+atom319;
atom798 = -atom781*atom784+atom68*atom779+dy;
atom372 = uR_R-lR_R;
atom373 = atom372*aR_R;
atom374 = bR_R+atom373;
atom441 = atom374+atom373;
atom443 = atom374*atom372+cR_R+atom372*atom441;
atom462 = (1+atom443^2)^(-1/2);
atom445 = -atom438*atom443;
atom444 = atom443*atom440;
atom451 = (atom444^2+atom445^2+atom449)^(-1/2);
atom454 = atom438*atom451;
atom453 = atom451*atom445;
atom452 = atom444*atom451;
atom1104 = uW_R*atom3-atom318*atom4;
atom1080 = -da*atom321;
atom1076 = atom3*atom307;
atom1079 = atom66*atom321-atom68*atom1076;
atom1087 = atom5*atom1080+atom6*atom1079;
atom1081 = da*atom1076;
atom1084 = atom5*atom1079-atom6*atom1080;
atom497 = uW_L-lW_L;
atom503 = dW_L+atom497*(atom497*(atom497*aW_L+bW_L)+cW_L);
atom506 = cos(thetaW_L)*atom503;
atom504 = -atom503*sin(thetaW_L);
atom923 = -atom320+uW_L*atom146+atom506*atom147+atom6*atom504;
atom522 = uW_L*atom4+atom506*atom3;
atom924 = atom522-atom321;
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
atom625 = atom590+(0.5)*L_R*atom619;
atom623 = 1-(0.5)*atom590*L_R*atom619-(0.5)*atom593^(-1)*atom614*L_R;
atom634 = atom623^2;
atom642 = (atom634+atom625^2)^(-1/2);
atom922 = atom5*atom504+atom506*atom145+atom144*uW_L-atom319;
atom935 = atom68*atom922-atom924*atom784+dy;
atom557 = uR_L-lR_L;
atom558 = aR_L*atom557;
atom559 = bR_L+atom558;
atom626 = atom559+atom558;
atom628 = atom557*atom626+atom559*atom557+cR_L;
atom647 = (1+atom628^2)^(-1/2);
atom630 = -atom623*atom628;
atom629 = atom625*atom628;
atom636 = (atom634+atom629^2+atom630^2)^(-1/2);
atom638 = atom630*atom636;
atom637 = atom629*atom636;
atom639 = atom623*atom636;
atom1147 = -atom506*atom4+atom3*uW_L;

Output_ = [sqrt(lambda1^2);
atom457*atom798*atom440+atom457*atom438*(atom781*atom787+dx-atom68*atom780);
atom462*(atom784*atom780-atom787*atom779+dz)*atom443+atom462*atom798;
atom68*atom454+atom787*atom453+atom452*atom784;
db;
1/2*sqrt((atom66*atom337-atom68*atom1104)^2+(da*atom337-atom68*atom316)^2+(atom66*atom316-da*atom1104)^2)+1/2*sqrt((dz+atom1081)^2+(atom1087+dy)^2+(atom1084+dx)^2);
(1-(atom454*atom4+atom452*atom144+atom453*atom146)^2)^(-1/2)*abs(sqrt(atom316^2+atom318^2));
10000.0;
6000000.0;
abs((1+atom443^(2.0))^(1.5))*abs(2*atom372*aR_R+2*atom441)^(-1);
sqrt(lambda2^2);
atom625*atom642*atom935+(dx+atom924*atom787-atom68*atom923)*atom642*atom623;
atom647*atom935+(atom784*atom923+dz-atom787*atom922)*atom647*atom628;
atom638*atom787+atom68*atom639+atom637*atom784;
db;
1/2*sqrt((atom1147*atom68-atom522*atom66)^2+(atom1147*da-atom66*atom504)^2+(atom522*da-atom68*atom504)^2)+1/2*sqrt((atom1087-dy)^2+(atom1084-dx)^2+(dz-atom1081)^2);
(1-(atom637*atom144+atom639*atom4+atom638*atom146)^2)^(-1/2)*abs(sqrt(atom504^2+atom506^2));
10000.0;
6000000.0;
abs((1+atom628^(2.0))^(1.5))*abs(2*aR_L*atom557+2*atom626)^(-1)];

%endfunction
