function WPhinew_ = WPhinew(q,dq,ddq)

global t;
global g;
global d3;
global r3;
global d4;
global r4;
global m1;
global mx1;
global my1;
global mz1;
global Ixx1;
global Ixy1;
global Ixz1;
global Iyy1;
global Iyz1;
global Izz1;
global m2;
global mx2;
global my2;
global mz2;
global Ixx2;
global Ixy2;
global Ixz2;
global Iyy2;
global Iyz2;
global Izz2;
global m3;
global mx3;
global my3;
global mz3;
global Ixx3;
global Ixy3;
global Ixz3;
global Iyy3;
global Iyz3;
global Izz3;
global m4;
global mx4;
global my4;
global mz4;
global Ixx4;
global Ixy4;
global Ixz4;
global Iyy4;
global Iyz4;
global Izz4;
global m5;
global mx5;
global my5;
global mz5;
global Ixx5;
global Ixy5;
global Ixz5;
global Iyy5;
global Iyz5;
global Izz5;
global m6;
global mx6;
global my6;
global mz6;
global Ixx6;
global Ixy6;
global Ixz6;
global Iyy6;
global Iyz6;
global Izz6;
global Ma1;
global Ma2;
global Ma3;
global Ma4;
global Ma5;
global Ma6;
global FS001;
global FSa11;
global FSb11;
global FSa21;
global FSb21;
global FSa31;
global FSb31;
global FSa41;
global FSb41;
global FS002;
global FSa12;
global FSb12;
global FSa22;
global FSb22;
global FSa32;
global FSb32;
global FSa42;
global FSb42;
global FS003;
global FSa13;
global FSb13;
global FSa23;
global FSb23;
global FSa33;
global FSb33;
global FSa43;
global FSb43;
global FS004;
global FSa14;
global FSb14;
global FSa24;
global FSb24;
global FSa34;
global FSb34;
global FSa44;
global FSb44;
global FS005;
global FSa15;
global FSb15;
global FSa25;
global FSb25;
global FSa35;
global FSb35;
global FSa45;
global FSb45;
global FS006;
global FSa16;
global FSb16;
global FSa26;
global FSb26;
global FSa36;
global FSb36;
global FSa46;
global FSb46;
global g;
global a1;
global a2;
global a3;
global a4;
global a5;
global a6;
global da1;
global da2;
global da3;
global da4;
global da5;
global da6;
if nargin == 3
global dda1;
global dda2;
global dda3;
global dda4;
global dda5;
global dda6;
end
global lambda1;
global lambda2;
global lambda3;
global lambda4;
global lambda5;
global lambda6;

a1 = q( 1); 
a2 = q( 2); 
a3 = q( 3); 
a4 = q( 4); 
a5 = q( 5); 
a6 = q( 6); 
da1 = dq( 1); 
da2 = dq( 2); 
da3 = dq( 3); 
da4 = dq( 4); 
da5 = dq( 5); 
da6 = dq( 6); 
if nargin == 3
dda1 = ddq( 1); 
dda2 = ddq( 2); 
dda3 = ddq( 3); 
dda4 = ddq( 4); 
dda5 = ddq( 5); 
dda6 = ddq( 6); 
end

atom35 = cos(a2);
atom36 = sin(a2);

WPhinew_ = [0;
0;
0;
0;
0;
0];

%endfunction
