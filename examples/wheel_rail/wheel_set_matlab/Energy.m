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


Energy_ = [1];

%endfunction
