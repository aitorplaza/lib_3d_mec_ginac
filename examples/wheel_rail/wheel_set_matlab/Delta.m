function Delta_ = Delta(q,dq,time,param)

x = q( 1 ); 
y = q( 2 ); 
b = q( 3 ); 
c = q( 4 ); 
z = q( 5 ); 
a = q( 6 ); 

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
atom65 = -mWHS*g;
atom13 = -atom8*atom9;
atom10 = sin(a_pend);
atom2 = sin(b);
atom3 = cos(a);
atom1 = cos(b);
atom3786 = atom3*dc;
atom3792 = atom1*atom3786+atom2*da;
atom3789 = atom1*da-atom2*atom3786;
atom7 = cos(b_pend);
atom4 = sin(a);
atom12 = -atom7*atom10;
atom5 = cos(c);
atom6 = sin(c);
atom11 = atom8*atom10;
atom22 = atom5*atom9-atom6*atom11;
atom37 = atom4*atom12+atom22*atom3;
atom753 = tor*atom37;
atom16 = -atom7*atom6;
atom31 = atom16*atom3+atom4*atom8;
atom752 = atom31*tor;
atom14 = atom7*atom9;
atom28 = atom5*atom10-atom13*atom6;
atom43 = atom28*atom3+atom4*atom14;
atom754 = tor*atom43;
atom3907 = atom3792*atom3789*I_WHSx-I_WHSz*atom3792*atom3789+I_WHSy*atom3786*da;
atom759 = atom43*atom754+atom31*atom752+atom753*atom37;
atom25 = atom10*atom6+atom5*atom13;
atom46 = -atom4*atom28+atom14*atom3;
atom34 = -atom4*atom16+atom8*atom3;
atom15 = atom7*atom5;
atom19 = atom9*atom6+atom5*atom11;
atom40 = atom12*atom3-atom4*atom22;
atom71 = -atom2*atom3;
atom3936 = -(atom34*atom2-atom1*atom15)*atom752-(atom46*atom2-atom1*atom25)*atom754+atom753*(atom1*atom19-atom40*atom2);
atom72 = atom1*atom3;
atom3941 = atom753*(atom40*atom1+atom2*atom19)+atom752*(atom2*atom15+atom34*atom1)+atom754*(atom25*atom2+atom46*atom1);
atom3785 = atom4*dc;
atom3793 = atom3785+db;
atom3908 = atom3793*I_WHSy*atom3789+I_WHSz*(atom3789*db-atom3785*atom1*da)-atom3793*atom3789*I_WHSx;
atom3906 = -(atom3792*db-atom3785*atom2*da)*I_WHSx+atom3793*I_WHSz*atom3792-atom3793*I_WHSy*atom3792;

Delta_ = [-atom65*atom13;
-atom65*atom10;
atom3907-atom759;
atom72*atom3908-atom72*atom3941-atom4*atom759+atom71*atom3906-atom71*atom3936+atom4*atom3907;
-atom65*atom14;
-atom3941*atom2-atom1*atom3936+atom3908*atom2+atom1*atom3906];

%endfunction
