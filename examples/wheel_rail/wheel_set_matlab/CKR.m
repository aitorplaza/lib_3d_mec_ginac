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

atom8 = sin(b_pend);
atom9 = cos(a_pend);
atom381 = (ends-stas)^(-1);
atom382 = (sR_R-stas)*atom381;
atom384 = bs+atom382*as;
atom386 = atom382*atom384+cs;
atom388 = ds+atom382*atom386;
atom393 = atom381*as;
atom396 = atom384*atom381+atom382*atom393;
atom399 = atom382*atom396+atom386*atom381;
atom402 = atom382*atom399+atom381*atom388;
atom405 = atom382*atom402+atom381*(atom382*atom388+es);
atom407 = 1+atom405^2;
atom408 = sqrt(atom407);
atom416 = atom396*atom381;
atom415 = atom381*atom399;
atom426 = atom381*atom402;
atom428 = 2*(atom415+atom382*(atom382*atom393*atom381+atom416))*atom382+2*atom426;
atom433 = -atom408^(-2)*atom405*atom407^(-1/2)*atom428;
atom437 = 1+(0.5)*L_R*atom408^(-1)*atom428+(0.5)*L_R*atom433*atom405;
atom439 = atom405-(0.5)*L_R*atom433;
atom448 = atom437^2;
atom456 = (atom439^2+atom448)^(-1/2);
atom13 = -atom8*atom9;
atom457 = atom456*atom437;
atom458 = atom456*atom439;
atom10 = sin(a_pend);
atom4132 = atom13*atom457+atom458*atom10;
atom11 = atom8*atom10;
atom4136 = atom458*atom9+atom457*atom11;
atom7 = cos(b_pend);
atom4138 = atom7*atom457;
atom4141 = atom4132*atom13+atom7*atom4138+atom4136*atom11;
atom4361 = -atom4141*C11R*bR*G_elastic*aR;
atom372 = uR_R-lR_R;
atom373 = aR_R*atom372;
atom374 = bR_R+atom373;
atom442 = atom374*atom372+(atom374+atom373)*atom372+cR_R;
atom461 = (1+atom442^2)^(-1/2);
atom14 = atom7*atom9;
atom462 = atom461*atom442;
atom4144 = atom461*atom10+atom14*atom462;
atom12 = -atom7*atom10;
atom4148 = atom12*atom462+atom461*atom9;
atom4150 = atom8*atom462;
atom4153 = atom7*atom4150+atom4144*atom13+atom4148*atom11;
atom4362 = -bR*atom4153*C22R*G_elastic*aR;
atom4364 = sqrt(bR*aR);
atom444 = -atom437*atom442;
atom443 = atom442*atom439;
atom450 = (atom444^2+atom443^2+atom448)^(-1/2);
atom4 = sin(a);
atom453 = atom437*atom450;
atom5 = cos(c);
atom3 = cos(a);
atom146 = atom5*atom3;
atom452 = atom450*atom444;
atom6 = sin(c);
atom451 = atom443*atom450;
atom144 = -atom6*atom3;
atom4365 = -bR*atom4153*atom4364*G_elastic*C23R*aR;
atom1057 = atom451*atom144+atom4*atom453+atom146*atom452;
atom307 = -(0.5)*L_WHS;
atom308 = lW_R-uW_R;
atom314 = dW_R+((bW_R-atom308*aW_R)*atom308-cW_R)*atom308;
atom318 = atom314*cos(thetaW_R);
atom775 = atom318*atom3+atom4*atom307+atom4*uW_R;
atom145 = atom4*atom6;
atom316 = -sin(thetaW_R)*atom314;
atom773 = atom318*atom145+atom5*atom316+atom144*atom307+atom144*uW_R;
atom838 = -atom144*atom775+atom4*atom773;
atom147 = -atom4*atom5;
atom774 = atom307*atom146+atom146*uW_R+atom147*atom318+atom316*atom6;
atom835 = atom146*atom775-atom4*atom774;
atom4344 = atom458*atom838+atom835*atom457;
atom841 = -atom773*atom146+atom144*atom774;
atom4353 = atom462*atom841+atom461*atom838;
atom4354 = atom461*atom773;
atom4347 = -atom774*atom457+atom458*atom773;
atom888 = -atom5*atom775;
atom4357 = -(atom773*atom6-atom5*atom774)*atom462+atom461*atom888;
atom4350 = atom458*atom888+atom457*atom775*atom6;
atom4360 = atom452*atom6+atom451*atom5;
atom4156 = atom4136*atom9+atom4132*atom10;
atom4366 = -atom4156*C11R*bR*G_elastic*aR;
atom4159 = atom4148*atom9+atom4144*atom10;
atom4367 = -bR*C22R*G_elastic*atom4159*aR;
atom4368 = -bR*atom4364*G_elastic*atom4159*C23R*aR;
atom4164 = atom8*atom4138+atom4136*atom12+atom4132*atom14;
atom4369 = -(atom841*atom4164+atom835*atom4141+atom4156*atom838)*C11R*bR*G_elastic*aR;
atom28 = atom5*atom10-atom13*atom6;
atom4195 = atom451*atom13+atom452*atom10+atom453*atom14;
atom16 = -atom7*atom6;
atom4182 = atom451*atom7+atom453*atom8;
atom22 = atom5*atom9-atom6*atom11;
atom4188 = atom453*atom12+atom451*atom11+atom9*atom452;
atom4197 = atom4195*(atom28*atom3+atom4*atom14)+atom4188*(atom4*atom12+atom22*atom3)+(atom16*atom3+atom4*atom8)*atom4182;
atom4174 = atom4148*atom12+atom8*atom4150+atom4144*atom14;
atom4179 = atom4174*atom841+atom835*atom4153+atom4159*atom838;
atom4372 = -atom4179*bR*C22R*G_elastic*aR+bR*atom4364*atom4197*G_elastic*C23R*aR;
atom4374 = bR^2;
atom4375 = aR^2;
atom4377 = -atom4179*bR*atom4364*G_elastic*C23R*aR-atom4374*C33R*atom4197*atom4375*G_elastic;
atom2 = sin(b);
atom71 = -atom2*atom3;
atom1 = cos(b);
atom72 = atom1*atom3;
atom4010 = atom71^2+atom4^2+atom72^2;
atom159 = atom147*atom1+atom2*atom6;
atom156 = atom1*atom6-atom147*atom2;
atom4004 = atom71*atom156+atom72*atom159+atom4*atom146;
atom4012 = -atom774*atom4010+atom4004*atom775;
atom150 = atom5*atom1-atom2*atom145;
atom153 = atom1*atom145+atom5*atom2;
atom4018 = atom71*atom150+atom72*atom153+atom144*atom4;
atom4020 = -atom4018*atom775+atom773*atom4010;
atom4023 = -atom4004*atom773+atom4018*atom774;
atom4378 = -C11R*bR*(atom4023*atom4164+atom4141*atom4012+atom4156*atom4020)*G_elastic*aR;
atom34 = -atom4*atom16+atom8*atom3;
atom15 = atom7*atom5;
atom19 = atom9*atom6+atom5*atom11;
atom40 = atom12*atom3-atom4*atom22;
atom25 = atom10*atom6+atom5*atom13;
atom46 = -atom4*atom28+atom14*atom3;
atom4213 = -atom4195*(atom46*atom2-atom1*atom25)+atom4188*(atom1*atom19-atom40*atom2)-(atom34*atom2-atom1*atom15)*atom4182;
atom4220 = (atom2*atom15+atom34*atom1)*atom4182+atom4188*(atom40*atom1+atom2*atom19)+atom4195*(atom25*atom2+atom46*atom1);
atom4222 = atom72*atom4220+atom4213*atom71+atom4*atom4197;
atom4207 = atom4174*atom4023+atom4020*atom4159+atom4153*atom4012;
atom4381 = -bR*atom4207*C22R*G_elastic*aR+atom4222*bR*atom4364*G_elastic*C23R*aR;
atom4384 = -bR*atom4364*atom4207*G_elastic*C23R*aR-atom4374*C33R*atom4222*atom4375*G_elastic;
atom4385 = -C11R*bR*G_elastic*atom4164*aR;
atom4386 = -atom4174*bR*C22R*G_elastic*aR;
atom4387 = -atom4174*bR*atom4364*G_elastic*C23R*aR;
atom4038 = atom71*atom1+atom72*atom2;
atom4044 = atom1*atom150+atom153*atom2;
atom4046 = atom773*atom4038-atom4044*atom775;
atom4034 = atom2*atom159+atom156*atom1;
atom4040 = atom775*atom4034-atom4038*atom774;
atom4049 = -atom773*atom4034+atom774*atom4044;
atom4388 = -C11R*(atom4141*atom4040+atom4156*atom4046+atom4049*atom4164)*bR*G_elastic*aR;
atom4235 = atom4220*atom2+atom4213*atom1;
atom4232 = atom4174*atom4049+atom4159*atom4046+atom4153*atom4040;
atom4391 = bR*atom4364*G_elastic*atom4235*C23R*aR-atom4232*bR*C22R*G_elastic*aR;
atom4394 = -atom4374*C33R*atom4375*G_elastic*atom4235-atom4232*bR*atom4364*G_elastic*C23R*aR;

CKR_ = [atom4361*atom457 , atom461*atom4362+atom458*atom4361 , atom4362*atom4353+atom4365*atom1057+atom4344*atom4361 , atom4362*atom4354+atom4347*atom4361+atom453*atom4365 , atom4362*atom462 , atom4362*atom4357+atom4361*atom4350+atom4365*atom4360;
atom4366*atom457 , atom458*atom4366+atom461*atom4367 , atom1057*atom4368+atom4344*atom4366+atom4367*atom4353 , atom4367*atom4354+atom453*atom4368+atom4347*atom4366 , atom4367*atom462 , atom4367*atom4357+atom4366*atom4350+atom4360*atom4368;
atom457*atom4369 , atom458*atom4369+atom461*atom4372 , atom4377*atom1057+atom4372*atom4353+atom4344*atom4369 , atom453*atom4377+atom4347*atom4369+atom4354*atom4372 , atom4372*atom462 , atom4372*atom4357+atom4369*atom4350+atom4377*atom4360;
atom457*atom4378 , atom458*atom4378+atom461*atom4381 , atom4384*atom1057+atom4381*atom4353+atom4344*atom4378 , atom453*atom4384+atom4347*atom4378+atom4381*atom4354 , atom4381*atom462 , atom4384*atom4360+atom4381*atom4357+atom4378*atom4350;
atom4385*atom457 , atom458*atom4385+atom461*atom4386 , atom4344*atom4385+atom4387*atom1057+atom4386*atom4353 , atom453*atom4387+atom4347*atom4385+atom4354*atom4386 , atom4386*atom462 , atom4387*atom4360+atom4386*atom4357+atom4385*atom4350;
atom4388*atom457 , atom458*atom4388+atom461*atom4391 , atom4394*atom1057+atom4344*atom4388+atom4353*atom4391 , atom453*atom4394+atom4388*atom4347+atom4354*atom4391 , atom462*atom4391 , atom4394*atom4360+atom4391*atom4357+atom4388*atom4350];

%endfunction