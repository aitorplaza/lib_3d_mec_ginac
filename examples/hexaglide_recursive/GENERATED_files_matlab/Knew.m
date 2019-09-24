function Knew_ = Knew(q,dq,ddq,unknowns,time,param)

x = q( 1 ); 
y = q( 2 ); 
z = q( 3 ); 
a = q( 4 ); 
b = q( 5 ); 
c = q( 6 ); 
a1 = q( 7 ); 
a2 = q( 8 ); 
a3 = q( 9 ); 
a4 = q( 10 ); 
a5 = q( 11 ); 
a6 = q( 12 ); 
b1 = q( 13 ); 
b2 = q( 14 ); 
b3 = q( 15 ); 
b4 = q( 16 ); 
b5 = q( 17 ); 
b6 = q( 18 ); 
s1 = q( 19 ); 
s2 = q( 20 ); 
s3 = q( 21 ); 
s4 = q( 22 ); 
s5 = q( 23 ); 
s6 = q( 24 ); 

dx = dq( 1 ); 
dy = dq( 2 ); 
dz = dq( 3 ); 
da = dq( 4 ); 
dB = dq( 5 ); 
dc = dq( 6 ); 
da1 = dq( 7 ); 
da2 = dq( 8 ); 
da3 = dq( 9 ); 
da4 = dq( 10 ); 
da5 = dq( 11 ); 
da6 = dq( 12 ); 
dB1 = dq( 13 ); 
dB2 = dq( 14 ); 
dB3 = dq( 15 ); 
dB4 = dq( 16 ); 
dB5 = dq( 17 ); 
dB6 = dq( 18 ); 
ds1 = dq( 19 ); 
ds2 = dq( 20 ); 
ds3 = dq( 21 ); 
ds4 = dq( 22 ); 
ds5 = dq( 23 ); 
ds6 = dq( 24 ); 

ddx = ddq( 1 ); 
ddy = ddq( 2 ); 
ddz = ddq( 3 ); 
dda = ddq( 4 ); 
ddB = ddq( 5 ); 
ddc = ddq( 6 ); 
dda1 = ddq( 7 ); 
dda2 = ddq( 8 ); 
dda3 = ddq( 9 ); 
dda4 = ddq( 10 ); 
dda5 = ddq( 11 ); 
dda6 = ddq( 12 ); 
ddB1 = ddq( 13 ); 
ddB2 = ddq( 14 ); 
ddB3 = ddq( 15 ); 
ddB4 = ddq( 16 ); 
ddB5 = ddq( 17 ); 
ddB6 = ddq( 18 ); 
dds1 = ddq( 19 ); 
dds2 = ddq( 20 ); 
dds3 = ddq( 21 ); 
dds4 = ddq( 22 ); 
dds5 = ddq( 23 ); 
dds6 = ddq( 24 ); 

lambda1 = unknowns( 1 ); 
lambda2 = unknowns( 2 ); 
lambda3 = unknowns( 3 ); 
lambda4 = unknowns( 4 ); 
lambda5 = unknowns( 5 ); 
lambda6 = unknowns( 6 ); 
lambda7 = unknowns( 7 ); 
lambda8 = unknowns( 8 ); 
lambda9 = unknowns( 9 ); 
lambda10 = unknowns( 10 ); 
lambda11 = unknowns( 11 ); 
lambda12 = unknowns( 12 ); 
lambda13 = unknowns( 13 ); 
lambda14 = unknowns( 14 ); 
lambda15 = unknowns( 15 ); 
lambda16 = unknowns( 16 ); 
lambda17 = unknowns( 17 ); 
lambda18 = unknowns( 18 ); 

t= time ;

g = param( 1 ); 
R = param( 2 ); 
r = param( 3 ); 
L = param( 4 ); 
e = param( 5 ); 
mP = param( 6 ); 
mxP = param( 7 ); 
myP = param( 8 ); 
mzP = param( 9 ); 
IxxP = param( 10 ); 
IxyP = param( 11 ); 
IyyP = param( 12 ); 
IxzP = param( 13 ); 
IzzP = param( 14 ); 
IyzP = param( 15 ); 
m1 = param( 16 ); 
mx1 = param( 17 ); 
my1 = param( 18 ); 
mz1 = param( 19 ); 
Ixx1 = param( 20 ); 
Ixy1 = param( 21 ); 
Iyy1 = param( 22 ); 
Ixz1 = param( 23 ); 
Izz1 = param( 24 ); 
Iyz1 = param( 25 ); 
m2 = param( 26 ); 
mx2 = param( 27 ); 
my2 = param( 28 ); 
mz2 = param( 29 ); 
Ixx2 = param( 30 ); 
Ixy2 = param( 31 ); 
Iyy2 = param( 32 ); 
Ixz2 = param( 33 ); 
Izz2 = param( 34 ); 
Iyz2 = param( 35 ); 
m3 = param( 36 ); 
mx3 = param( 37 ); 
my3 = param( 38 ); 
mz3 = param( 39 ); 
Ixx3 = param( 40 ); 
Ixy3 = param( 41 ); 
Iyy3 = param( 42 ); 
Ixz3 = param( 43 ); 
Izz3 = param( 44 ); 
Iyz3 = param( 45 ); 
m4 = param( 46 ); 
mx4 = param( 47 ); 
my4 = param( 48 ); 
mz4 = param( 49 ); 
Ixx4 = param( 50 ); 
Ixy4 = param( 51 ); 
Iyy4 = param( 52 ); 
Ixz4 = param( 53 ); 
Izz4 = param( 54 ); 
Iyz4 = param( 55 ); 
m5 = param( 56 ); 
mx5 = param( 57 ); 
my5 = param( 58 ); 
mz5 = param( 59 ); 
Ixx5 = param( 60 ); 
Ixy5 = param( 61 ); 
Iyy5 = param( 62 ); 
Ixz5 = param( 63 ); 
Izz5 = param( 64 ); 
Iyz5 = param( 65 ); 
m6 = param( 66 ); 
mx6 = param( 67 ); 
my6 = param( 68 ); 
mz6 = param( 69 ); 
Ixx6 = param( 70 ); 
Ixy6 = param( 71 ); 
Iyy6 = param( 72 ); 
Ixz6 = param( 73 ); 
Izz6 = param( 74 ); 
Iyz6 = param( 75 ); 
Fs1 = param( 76 ); 
Fs2 = param( 77 ); 
Fs3 = param( 78 ); 
Fs4 = param( 79 ); 
Fs5 = param( 80 ); 
Fs6 = param( 81 ); 
FS001 = param( 82 ); 
FSa11 = param( 83 ); 
FSb11 = param( 84 ); 
FSa21 = param( 85 ); 
FSb21 = param( 86 ); 
FS002 = param( 87 ); 
FSa12 = param( 88 ); 
FSb12 = param( 89 ); 
FSa22 = param( 90 ); 
FSb22 = param( 91 ); 
FS003 = param( 92 ); 
FSa13 = param( 93 ); 
FSb13 = param( 94 ); 
FSa23 = param( 95 ); 
FSb23 = param( 96 ); 
FS004 = param( 97 ); 
FSa14 = param( 98 ); 
FSb14 = param( 99 ); 
FSa24 = param( 100 ); 
FSb24 = param( 101 ); 
FS005 = param( 102 ); 
FSa15 = param( 103 ); 
FSb15 = param( 104 ); 
FSa25 = param( 105 ); 
FSb25 = param( 106 ); 
FS006 = param( 107 ); 
FSa16 = param( 108 ); 
FSb16 = param( 109 ); 
FSa26 = param( 110 ); 
FSb26 = param( 111 ); 
gra = param( 112 ); 


atom37 = cos(c);
atom40 = sin(b);
atom2467 = da*atom40;
atom39 = cos(b);
atom38 = sin(c);
atom3803 = -dB*atom2467+dda*atom39;
atom3809 = atom37*ddB;
atom2466 = atom39*da;
atom2470 = atom38*dB+atom2466*atom37;
atom2626 = -dc*atom2470;
atom2474 = dc+atom2467;
atom3813 = -atom38*atom3803+atom3809+atom2626;
atom3818 = atom2474*atom2470;
atom3827 = -atom3813+atom3818;
atom2473 = dB*atom37-atom2466*atom38;
atom3802 = dda*atom40;
atom2628 = atom2466*dB;
atom3817 = atom2473*atom2470;
atom3811 = atom3802+atom2628+ddc;
atom48 = -atom38*atom39;
atom3825 = atom3817+atom3811;
atom3815 = atom2473^2;
atom3814 = atom2474^2;
atom47 = atom39*atom37;
atom3816 = -atom3815-atom3814;
atom3823 = atom3817-atom3811;
atom3819 = atom2470^2;
atom3820 = -atom3819-atom3814;
atom3806 = atom38*ddB;
atom2623 = dc*atom2473;
atom3812 = atom2623+atom3803*atom37+atom3806;
atom3821 = atom2474*atom2473;
atom3828 = atom3812+atom3821;
atom3826 = -atom3812+atom3821;
atom3824 = atom3813+atom3818;
atom3822 = -atom3815-atom3819;
atom42 = sin(a);
atom44 = -atom42*atom39;
atom43 = atom42*atom40;
atom41 = cos(a);
atom51 = atom43*atom37+atom41*atom38;
atom54 = atom41*atom37-atom38*atom43;
atom46 = atom41*atom39;
atom45 = -atom41*atom40;
atom60 = -atom38*atom45+atom42*atom37;
atom57 = atom45*atom37+atom42*atom38;
atom3829 = ddz+gra;
atom3873 = atom60*atom3829+ddx*atom48+ddy*atom54;
atom3878 = atom44*ddy+atom3829*atom46+ddx*atom40;
atom3868 = atom57*atom3829+ddy*atom51+atom47*ddx;
atom5019 = atom2623+atom47*dda-dB*atom2467*atom37+atom3806;
atom5021 = atom48*atom3818;
atom5023 = -atom3817*atom40;
atom5032 = -atom3815+atom3819;
atom5026 = dda*atom48+atom3809+atom2626+atom38*dB*atom2467;
atom5027 = -atom3818+atom5026;
atom5029 = atom5019+atom3821;
atom5035 = -atom47*atom3821;
atom5039 = atom3802+atom2628+ddc;
atom5040 = atom3817+atom5039;
atom5042 = -atom3819+atom3814;
atom5045 = atom5019-atom3821;
atom5053 = atom3818+atom5026;
atom5048 = atom3815-atom3814;
atom5050 = -atom3817+atom5039;
atom5064 = atom3818*atom37;
atom5071 = -atom38*atom3821;
atom4003 = gra+dds1;
atom82 = sin(a1);
atom80 = sin(b1);
atom4027 = atom4003*atom82;
atom81 = cos(a1);
atom85 = -atom80*atom81;
atom4026 = atom85*atom4003;
atom79 = cos(b1);
atom86 = atom81*atom79;
atom4028 = atom4003*atom86;
atom2697 = da1*atom79;
atom2785 = dB1*atom2697;
atom2698 = atom80*da1;
atom2784 = -atom2698*dB1;
atom3988 = atom2784+dda1*atom79;
atom5086 = -atom2785*atom80;
atom3994 = atom2697^2;
atom3991 = dB1^2;
atom3993 = atom2698*atom2697;
atom4001 = -ddB1+atom3993;
atom5092 = atom2784*atom79;
atom3989 = atom2785+atom80*dda1;
atom3999 = atom2785+atom3989;
atom4000 = -atom2784-atom3988;
atom3990 = atom2698^2;
atom3998 = ddB1+atom3993;
atom106 = sin(a2);
atom4099 = gra+dds2;
atom4123 = atom106*atom4099;
atom104 = sin(b2);
atom105 = cos(a2);
atom109 = -atom104*atom105;
atom4122 = atom109*atom4099;
atom103 = cos(b2);
atom110 = atom105*atom103;
atom4124 = atom4099*atom110;
atom2843 = da2*atom103;
atom2931 = dB2*atom2843;
atom2844 = atom104*da2;
atom2930 = -dB2*atom2844;
atom4084 = atom2930+dda2*atom103;
atom5108 = -atom104*atom2931;
atom4089 = atom2844*atom2843;
atom4097 = atom4089-ddB2;
atom4090 = atom2843^2;
atom4087 = dB2^2;
atom5115 = atom2930*atom103;
atom4096 = -atom4084-atom2930;
atom4085 = atom104*dda2+atom2931;
atom4095 = atom2931+atom4085;
atom4086 = atom2844^2;
atom4094 = atom4089+ddB2;
atom4195 = gra+dds3;
atom130 = sin(a3);
atom128 = sin(b3);
atom4219 = atom4195*atom130;
atom129 = cos(a3);
atom148 = -atom128*atom129;
atom4218 = atom4195*atom148;
atom127 = cos(b3);
atom149 = atom127*atom129;
atom4220 = atom4195*atom149;
atom2989 = atom127*da3;
atom3090 = atom2989*dB3;
atom2990 = atom128*da3;
atom3089 = -atom2990*dB3;
atom4180 = atom127*dda3+atom3089;
atom5131 = -atom3090*atom128;
atom4185 = atom2990*atom2989;
atom4193 = -ddB3+atom4185;
atom4186 = atom2989^2;
atom4183 = dB3^2;
atom5138 = atom127*atom3089;
atom4192 = -atom4180-atom3089;
atom4181 = atom3090+atom128*dda3;
atom4191 = atom3090+atom4181;
atom4182 = atom2990^2;
atom4190 = ddB3+atom4185;
atom4291 = gra+dds4;
atom171 = sin(a4);
atom169 = sin(b4);
atom4315 = atom4291*atom171;
atom170 = cos(a4);
atom168 = cos(b4);
atom189 = atom170*atom168;
atom4316 = atom4291*atom189;
atom188 = -atom169*atom170;
atom4314 = atom4291*atom188;
atom3149 = atom169*da4;
atom3248 = -dB4*atom3149;
atom4276 = atom3248+dda4*atom168;
atom3148 = da4*atom168;
atom3249 = atom3148*dB4;
atom5154 = -atom3249*atom169;
atom4281 = atom3148*atom3149;
atom4289 = atom4281-ddB4;
atom4282 = atom3148^2;
atom4279 = dB4^2;
atom5161 = atom3248*atom168;
atom4288 = -atom3248-atom4276;
atom4277 = atom3249+atom169*dda4;
atom4287 = atom3249+atom4277;
atom4278 = atom3149^2;
atom4286 = atom4281+ddB4;
atom4387 = gra+dds5;
atom211 = sin(a5);
atom209 = sin(b5);
atom4411 = atom4387*atom211;
atom210 = cos(a5);
atom208 = cos(b5);
atom229 = atom210*atom208;
atom4412 = atom4387*atom229;
atom228 = -atom209*atom210;
atom4410 = atom4387*atom228;
atom3308 = atom209*da5;
atom3407 = -atom3308*dB5;
atom4372 = atom3407+dda5*atom208;
atom3307 = da5*atom208;
atom3408 = atom3307*dB5;
atom5178 = -atom209*atom3408;
atom4377 = atom3308*atom3307;
atom4385 = -ddB5+atom4377;
atom4375 = dB5^2;
atom4378 = atom3307^2;
atom5184 = atom3407*atom208;
atom4384 = -atom3407-atom4372;
atom4373 = atom3408+atom209*dda5;
atom4383 = atom3408+atom4373;
atom4374 = atom3308^2;
atom4382 = ddB5+atom4377;
atom4483 = gra+dds6;
atom251 = sin(a6);
atom4507 = atom4483*atom251;
atom249 = sin(b6);
atom250 = cos(a6);
atom248 = cos(b6);
atom269 = atom250*atom248;
atom4508 = atom4483*atom269;
atom268 = -atom250*atom249;
atom4506 = atom268*atom4483;
atom3467 = da6*atom249;
atom3566 = -atom3467*dB6;
atom4468 = dda6*atom248+atom3566;
atom3466 = da6*atom248;
atom3567 = atom3466*dB6;
atom5200 = -atom3567*atom249;
atom4474 = atom3466^2;
atom4471 = dB6^2;
atom4473 = atom3467*atom3466;
atom4481 = -ddB6+atom4473;
atom5207 = atom248*atom3566;
atom4480 = -atom4468-atom3566;
atom4469 = dda6*atom249+atom3567;
atom4479 = atom4469+atom3567;
atom4478 = ddB6+atom4473;
atom4470 = atom3467^2;
atom3997 = atom2785-atom3989;
atom4002 = -atom2784+atom3988;
atom4098 = atom4084-atom2930;
atom4093 = atom2931-atom4085;
atom4194 = atom4180-atom3089;
atom4189 = atom3090-atom4181;
atom4290 = -atom3248+atom4276;
atom4285 = atom3249-atom4277;
atom4386 = -atom3407+atom4372;
atom4381 = atom3408-atom4373;
atom4482 = atom4468-atom3566;
atom4477 = -atom4469+atom3567;

Knew_ = [ddx , atom47*atom3816+atom3827*atom40+atom48*atom3825 , atom47*atom3823+atom3828*atom40+atom48*atom3820 , atom3822*atom40+atom3826*atom48+atom47*atom3824 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
ddy , atom54*atom3825+atom44*atom3827+atom3816*atom51 , atom54*atom3820+atom44*atom3828+atom3823*atom51 , atom44*atom3822+atom3824*atom51+atom3826*atom54 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
atom3829 , atom57*atom3816+atom60*atom3825+atom46*atom3827 , atom57*atom3823+atom60*atom3820+atom46*atom3828 , atom3822*atom46+atom60*atom3826+atom57*atom3824 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , atom3873*atom40-atom3878*atom48 , atom47*atom3878-atom3868*atom40 , -atom47*atom3873+atom3868*atom48 , atom47*atom5019+atom5021+atom5023 , atom5027*atom47+atom5032*atom40+atom48*atom5029 , atom5035-atom5023+atom48*atom5026 , atom47*atom5040+atom48*atom5042+atom5045*atom40 , atom48*atom5050+atom47*atom5048+atom5053*atom40 , atom5039*atom40-atom5035-atom5021 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , -atom3878*atom37 , atom3878*atom38 , -atom3873*atom38+atom3868*atom37 , atom38*atom5019+atom5064 , atom5029*atom37+atom5027*atom38 , atom5071+atom5026*atom37 , atom5042*atom37+atom38*atom5040 , atom38*atom5048+atom5050*atom37 , -atom5071-atom5064 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , atom3873 , -atom3868 , 0.0 , -atom3817 , atom5032 , atom3817 , atom5045 , atom5053 , atom5039 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom80*atom4027 , atom4028*atom79-atom4026*atom80 , -atom4027*atom79 , atom5086+atom3988*atom79 , (atom3994-atom3991)*atom80-atom4001*atom79 , -atom5086+atom5092 , atom3999*atom79-atom80*atom4000 , atom3998*atom80+(atom3991-atom3990)*atom79 , atom80*atom3989-atom5092 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4123*atom104 , atom4124*atom103-atom104*atom4122 , -atom4123*atom103 , atom5108+atom4084*atom103 , -atom4097*atom103+atom104*(atom4090-atom4087) , -atom5108+atom5115 , -atom104*atom4096+atom4095*atom103 , -(atom4086-atom4087)*atom103+atom104*atom4094 , -atom5115+atom104*atom4085 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom128*atom4219 , -atom4218*atom128+atom127*atom4220 , -atom127*atom4219 , atom5131+atom127*atom4180 , -atom127*atom4193+atom128*(atom4186-atom4183) , -atom5131+atom5138 , -atom128*atom4192+atom4191*atom127 , atom128*atom4190+atom127*(atom4183-atom4182) , atom128*atom4181-atom5138 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom169*atom4315 , atom4316*atom168-atom169*atom4314 , -atom4315*atom168 , atom5154+atom4276*atom168 , atom169*(atom4282-atom4279)-atom4289*atom168 , atom5161-atom5154 , -atom4288*atom169+atom4287*atom168 , atom4286*atom169-(atom4278-atom4279)*atom168 , -atom5161+atom169*atom4277 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom209*atom4411 , -atom209*atom4410+atom208*atom4412 , -atom4411*atom208 , atom208*atom4372+atom5178 , -atom4385*atom208-atom209*(atom4375-atom4378) , -atom5178+atom5184 , -atom209*atom4384+atom4383*atom208 , -(atom4374-atom4375)*atom208+atom209*atom4382 , atom209*atom4373-atom5184 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4507*atom249 , atom248*atom4508-atom4506*atom249 , -atom4507*atom248 , atom5200+atom248*atom4468 , -atom248*atom4481+(atom4474-atom4471)*atom249 , atom5207-atom5200 , atom4479*atom248-atom4480*atom249 , -(atom4470-atom4471)*atom248+atom4478*atom249 , -atom5207+atom4469*atom249;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom4028 , 0.0 , atom4026 , atom3993 , atom4002 , ddB1 , -atom3994+atom3990 , -atom3997 , -atom3993 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom4124 , 0.0 , atom4122 , atom4089 , atom4098 , ddB2 , atom4086-atom4090 , -atom4093 , -atom4089 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom4220 , 0.0 , atom4218 , atom4185 , atom4194 , ddB3 , -atom4186+atom4182 , -atom4189 , -atom4185 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom4316 , 0.0 , atom4314 , atom4281 , atom4290 , ddB4 , atom4278-atom4282 , -atom4285 , -atom4281 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom4412 , 0.0 , atom4410 , atom4377 , atom4386 , ddB5 , atom4374-atom4378 , -atom4381 , -atom4377 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , -atom4508 , 0.0 , atom4506 , atom4473 , atom4482 , ddB6 , atom4470-atom4474 , -atom4477 , -atom4473;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4003 , atom4001*atom86+atom82*atom3999-atom85*(atom3991+atom3990) , -(atom3994+atom3990)*atom82+atom85*atom3997+atom4002*atom86 , atom85*atom3998+atom4000*atom82-(atom3994+atom3991)*atom86 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4099 , -atom109*(atom4086+atom4087)+atom4095*atom106+atom4097*atom110 , atom4098*atom110-(atom4086+atom4090)*atom106+atom109*atom4093 , atom109*atom4094-(atom4090+atom4087)*atom110+atom106*atom4096 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4195 , -atom148*(atom4183+atom4182)+atom4193*atom149+atom4191*atom130 , atom4194*atom149-(atom4186+atom4182)*atom130+atom4189*atom148 , atom4190*atom148-(atom4186+atom4183)*atom149+atom4192*atom130 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4291 , atom189*atom4289-(atom4278+atom4279)*atom188+atom4287*atom171 , -(atom4278+atom4282)*atom171+atom189*atom4290+atom4285*atom188 , atom4288*atom171+atom4286*atom188-atom189*(atom4282+atom4279) , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4387 , atom4385*atom229-(atom4374+atom4375)*atom228+atom211*atom4383 , -atom211*(atom4374+atom4378)+atom4386*atom229+atom4381*atom228 , -(atom4375+atom4378)*atom229+atom4382*atom228+atom211*atom4384 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0;
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , atom4483 , atom4479*atom251+atom4481*atom269-atom268*(atom4470+atom4471) , atom269*atom4482-atom251*(atom4470+atom4474)+atom268*atom4477 , atom268*atom4478+atom251*atom4480-(atom4474+atom4471)*atom269 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0];

%endfunction
