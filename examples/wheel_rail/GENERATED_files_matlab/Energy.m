function Energy_ = Energy(q,qaux,dq,dqaux,ddq,ddqaux,time,param)

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


Energy_ = [1];

%endfunction
