function MQrecsubs_ = MQrecsubs(q,dq,ddq)

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

atom57 = a3+a2;
atom58 = cos(atom57);
atom35 = cos(a2);
atom59 = sin(atom57);
atom36 = sin(a2);
atom2582 = -atom35*atom59+atom58*atom36;
atom2576 = r3*atom36;
atom2579 = atom59*atom36+atom58*atom35;
atom2575 = -atom35*r3;
atom81 = sin(a4);
atom2585 = atom2579*atom2575-atom2582*atom2576;
atom4606 = -atom36*atom2579+atom35*atom2582;
atom4602 = -atom36*atom2582-atom35*atom2579;
atom299 = atom35*d3;
atom80 = cos(a4);
atom5474 = -atom4606*r4+atom299-atom4602*d4;
atom152 = cos(a6);
atom5521 = atom80*atom5474-atom81*atom2585;
atom115 = sin(a5);
atom2588 = atom2579*atom2576+atom2582*atom2575;
atom114 = cos(a5);
atom5476 = atom81*atom5474+atom2585*atom80;
atom153 = sin(a6);
atom5510 = atom114*atom5476+atom115*atom2588;
atom5524 = -atom153*atom5510+atom152*atom5521;
atom5485 = atom4606*atom80;
atom5487 = atom114*atom5485+atom4602*atom115;
atom5478 = -atom81*atom4606;
atom5497 = atom5478*atom153+atom152*atom5487;
atom5514 = -atom115*atom5485+atom114*atom4602;
atom5529 = -mz6*atom5497+m6*atom5524-mx6*atom5514;
atom5533 = atom152*atom5510+atom5521*atom153;
atom5501 = atom5478*atom152-atom153*atom5487;
atom5538 = my6*atom5514+mz6*atom5501+m6*atom5533;
atom5541 = mz5*atom5514+atom5538*atom152-atom5478*my5+m5*atom5510-atom153*atom5529;
atom5492 = -atom115*atom5476+atom114*atom2588;
atom5506 = m5*atom5492-mz5*atom5487-my6*atom5497+m6*atom5492+atom5478*mx5+atom5501*mx6;
atom5544 = m4*atom5476-atom115*atom5506+atom114*atom5541+atom4602*my4+mz4*atom5478;
atom5560 = atom5487*my5-mz4*atom5485-atom4602*mx4-mx5*atom5514+atom5538*atom153+m4*atom5521+m5*atom5521+atom152*atom5529;
atom5562 = atom5560*atom80+atom81*atom5544;
atom5644 = atom5497*Ixy6+mz6*atom5533-Iyz6*atom5514+atom5501*Iyy6+mx6*atom5492;
atom5634 = -my6*atom5492-Ixz6*atom5514+atom5501*Ixy6-mz6*atom5524+Ixx6*atom5497;
atom5647 = Ixx5*atom5487-mz5*atom5492-atom5644*atom153+Ixz5*atom5478+Ixy5*atom5514+atom152*atom5634+atom5521*my5;
atom5614 = atom5501*Iyz6+Ixz6*atom5497-my6*atom5533+atom5524*mx6-Izz6*atom5514;
atom5615 = Iyy5*atom5514+atom5487*Ixy5+atom5478*Iyz5-atom5521*mx5-atom5614+mz5*atom5510;
atom5701 = -my4*atom5476+mx4*atom5521-Izz4*atom4602-atom5647*atom115-atom5615*atom114+Ixz4*atom5485+atom5478*Iyz4;
atom5705 = atom4606*Ixy3-mx3*atom299-atom5701-atom5562*d4+atom4602*Iyy3+mz3*atom2585;
atom5578 = -atom114*atom5506-m4*atom2588+atom5485*my4-atom5478*mx4-atom115*atom5541;
atom5582 = -atom5578-mz3*atom4606+m3*atom2588;
atom5589 = atom5544*atom80-atom81*atom5560;
atom5590 = m3*atom2585+atom5589+mz3*atom4602;
atom5659 = -mz4*atom5521+atom5478*Ixy4-atom2588*my4+Ixx4*atom5485-atom5615*atom115+atom114*atom5647-Ixz4*atom4602;
atom5673 = Izz5*atom5478+Iyz5*atom5514+atom5634*atom153+Ixz5*atom5487+mx5*atom5492+atom5644*atom152-atom5510*my5;
atom5683 = -atom4602*Iyz4+atom5673+atom5478*Iyy4+mx4*atom2588+mz4*atom5476+atom5485*Ixy4;
atom5687 = atom4602*Ixy3-mz3*atom2588-atom5562*r4+atom80*atom5659+Ixx3*atom4606+atom299*my3-atom5683*atom81;
atom5717 = -atom2582*atom5590+atom2579*atom5582;
atom2589 = -atom2582*d3;
atom2832 = -atom2589-r4;
atom2864 = -atom2832*atom80;
atom5724 = mz4*atom80;
atom2590 = atom2579*d3;
atom2831 = d4+atom2590;
atom5730 = atom114*atom2831-atom2864*atom115;
atom847 = atom81*atom114;
atom1444 = atom152*atom847+atom153*atom80;
atom1447 = -atom847*atom153+atom152*atom80;
atom5735 = my6*atom1444-atom1447*mx6;
atom5728 = -mz5*atom847+mx5*atom80;
atom5738 = m5*atom5730+atom5728+m6*atom5730-atom5735;
atom848 = -atom81*atom115;
atom5741 = atom115*atom2831+atom114*atom2864;
atom5745 = -atom80*my5+atom848*mz5;
atom2865 = atom81*atom2832;
atom5749 = -atom5741*atom153+atom2865*atom152;
atom5753 = -mz6*atom1444-atom848*mx6;
atom5754 = atom5753+atom5749*m6;
atom5758 = atom2865*atom153+atom152*atom5741;
atom5762 = atom1447*mz6+atom848*my6;
atom5763 = atom5762+m6*atom5758;
atom5766 = -atom5754*atom153+m5*atom5741+atom5745+atom152*atom5763;
atom5769 = atom114*atom5766+m4*atom2864-atom115*atom5738+atom5724;
atom5781 = -atom81*mz4;
atom5776 = -atom848*mx5+atom847*my5;
atom5783 = atom152*atom5754+atom5781+atom153*atom5763+atom2865*m5+atom5776+atom2865*m4;
atom5785 = atom80*atom5783+atom81*atom5769;
atom513 = atom81*Ixy4+Iyy4*atom80;
atom1467 = atom1447*Ixy6-atom848*Ixz6+atom1444*Ixx6;
atom5827 = -my6*atom5730-atom5749*mz6+atom1467;
atom1472 = -atom848*Iyz6+atom1444*Ixy6+atom1447*Iyy6;
atom5832 = mz6*atom5758+atom1472+mx6*atom5730;
atom878 = Izz5*atom80+atom848*Iyz5+Ixz5*atom847;
atom5848 = atom5832*atom152+atom878+mx5*atom5730+atom5827*atom153-atom5741*my5;
atom5850 = mx4*atom2831+atom513+atom5848+mz4*atom2864;
atom873 = atom80*Iyz5+atom847*Ixy5+atom848*Iyy5;
atom1477 = atom1447*Iyz6+Ixz6*atom1444-atom848*Izz6;
atom5818 = -my6*atom5758+atom1477+atom5749*mx6;
atom5819 = mz5*atom5741-atom2865*mx5+atom873-atom5818;
atom868 = atom848*Ixy5+atom847*Ixx5+Ixz5*atom80;
atom5835 = -mz5*atom5730+atom152*atom5827+atom2865*my5-atom5832*atom153+atom868;
atom510 = atom81*Ixx4+atom80*Ixy4;
atom5839 = -atom115*atom5819-atom2865*mz4-my4*atom2831+atom510+atom114*atom5835;
atom5854 = Ixz3+atom5839*atom80-atom81*atom5850-mz3*atom2590-r4*atom5785;
atom516 = Iyz4*atom80+atom81*Ixz4;
atom5859 = -atom114*atom5819-atom2864*my4+atom2865*mx4+atom516-atom5835*atom115;
atom5863 = -atom5859-d4*atom5785+mz3*atom2589+Iyz3;
atom5804 = atom5769*atom80-atom81*atom5783;
atom5805 = atom5804+m3*atom2589-my3;
atom5790 = atom81*my4-mx4*atom80;
atom5795 = -atom115*atom5766-m4*atom2831-atom114*atom5738+atom5790;
atom5798 = mx3+m3*atom2590-atom5795;
atom5875 = atom5798*atom2579-atom2582*atom5805;
atom2866 = r4*atom80;
atom2867 = -atom81*r4;
atom5891 = atom115*d4+atom114*atom2866;
atom5896 = atom2867*atom152-atom5891*atom153;
atom5898 = atom5753+m6*atom5896;
atom5902 = atom5891*atom152+atom2867*atom153;
atom5904 = atom5762+m6*atom5902;
atom5907 = -atom153*atom5898+atom5904*atom152+atom5891*m5+atom5745;
atom5883 = atom114*d4-atom115*atom2866;
atom5888 = atom5883*m6+atom5728+atom5883*m5-atom5735;
atom5910 = -atom5888*atom115+atom114*atom5907+m4*atom2866+atom5724;
atom5920 = atom2867*m4+atom152*atom5898+atom2867*m5+atom5781+atom5904*atom153+atom5776;
atom5922 = atom81*atom5910+atom5920*atom80;
atom5956 = atom1467-mz6*atom5896-atom5883*my6;
atom5961 = mz6*atom5902+atom1472+atom5883*mx6;
atom5977 = -atom5891*my5+atom878+atom5883*mx5+atom152*atom5961+atom153*atom5956;
atom5979 = atom513+mz4*atom2866+atom5977+d4*mx4;
atom5964 = -atom5883*mz5+atom2867*my5-atom153*atom5961+atom152*atom5956+atom868;
atom5947 = -my6*atom5902+atom1477+atom5896*mx6;
atom5948 = -atom5947+mz5*atom5891+atom873-atom2867*mx5;
atom5968 = -atom115*atom5948-d4*my4+atom114*atom5964+atom510-atom2867*mz4;
atom5983 = Ixz3-atom5922*r4-atom81*atom5979+atom5968*atom80;
atom5929 = -m4*d4-atom115*atom5907+atom5790-atom114*atom5888;
atom5930 = mx3-atom5929;
atom5934 = atom5910*atom80-atom81*atom5920;
atom5935 = -my3+atom5934;
atom6001 = atom2579*atom5930-atom2582*atom5935;
atom5988 = -atom114*atom5948-atom115*atom5964+atom516+atom2867*mx4-atom2866*my4;
atom5991 = Iyz3-atom5988-atom5922*d4;
atom3688 = atom115*atom153;
atom3687 = -atom115*atom152;
atom3817 = atom114*Iyz6+atom3688*Iyy6+atom3687*Ixy6;
atom3812 = atom114*Ixz6+atom3687*Ixx6+atom3688*Ixy6;
atom3889 = -atom3817*atom152+atom114*Iyz5+Ixz5*atom115-atom3812*atom153;
atom6060 = -atom3889+Iyz4;
atom6055 = -atom114*Ixy5+atom3812*atom152-atom3817*atom153-atom115*Ixx5;
atom3821 = atom114*Izz6;
atom3822 = Ixz6*atom3687+atom3821+atom3688*Iyz6;
atom6050 = -atom115*Ixy5-atom3822-atom114*Iyy5;
atom6058 = Ixz4-atom6050*atom115+atom114*atom6055;
atom6015 = -mz6*atom3687+atom114*mx6;
atom6019 = atom3688*mz6-atom114*my6;
atom6034 = -atom115*my5+atom152*atom6015+mx4+atom114*mx5+atom6019*atom153;
atom6010 = -my6*atom3687+mz5*atom115+atom3688*mx6;
atom6022 = -atom153*atom6015+atom6019*atom152-atom114*mz5;
atom6025 = atom114*atom6022-atom6010*atom115-my4;
atom6036 = atom6034*atom80+atom81*atom6025;
atom6063 = -atom81*atom6060+atom6058*atom80-atom6036*r4;
atom6044 = atom6025*atom80-atom81*atom6034;
atom6040 = -atom115*atom6022-atom114*atom6010;
atom6080 = -atom6044*atom2582-atom2579*atom6040;
atom6068 = Izz4-atom115*atom6055-atom114*atom6050;
atom6070 = -atom6036*d4-atom6068;
atom6090 = -mz6*atom153;
atom6092 = mz6*atom152;
atom6095 = -atom6090*atom153+atom6092*atom152-my5;
atom6087 = -atom152*mx6+my6*atom153;
atom6088 = -atom6087+mx5;
atom6097 = atom114*atom6095-atom115*atom6088;
atom6101 = atom6092*atom153+atom152*atom6090;
atom6103 = atom80*atom6101+atom81*atom6097;
atom3836 = atom152*Iyy6+atom153*Ixy6;
atom3833 = atom153*Ixx6+atom152*Ixy6;
atom3890 = -atom3836*atom152-Izz5-atom153*atom3833;
atom6122 = Ixz5-atom3836*atom153+atom152*atom3833;
atom3839 = Ixz6*atom153+atom152*Iyz6;
atom6117 = Iyz5-atom3839;
atom6124 = -atom115*atom6117+atom114*atom6122;
atom6128 = atom81*atom3890-r4*atom6103+atom6124*atom80;
atom6132 = -atom114*atom6117-atom115*atom6122;
atom6134 = -d4*atom6103-atom6132;
atom6111 = -atom81*atom6101+atom6097*atom80;
atom6107 = -atom115*atom6095-atom114*atom6088;
atom6144 = -atom6111*atom2582-atom2579*atom6107;
atom6170 = Ixz6*atom152-atom153*Iyz6;
atom6151 = -my6*atom152-atom153*mx6;
atom6152 = atom6151*atom114;
atom6155 = -atom6087*atom80+atom81*atom6152;
atom6179 = -atom115*atom6170+atom3821;
atom6181 = -atom6179-d4*atom6155;
atom6161 = atom6152*atom80+atom81*atom6087;
atom6157 = -atom6151*atom115;
atom6191 = -atom2582*atom6161-atom6157*atom2579;
atom6172 = atom114*atom6170+Izz6*atom115;
atom6176 = -atom81*atom3839-r4*atom6155+atom6172*atom80;
atom2449 = -atom36*da1;
atom2450 = -atom35*da1;
atom4467 = Iyz2*atom2450+Ixz2*atom2449+da2*Izz2;
atom4435 = -atom36*g;
atom4502 = atom2579*atom2450+atom2582*atom2449;
atom4652 = -atom4502+da4;
atom443 = da3;
atom4503 = atom443+da2;
atom4499 = atom2579*atom2449-atom2582*atom2450;
atom4651 = atom4503*atom80-atom81*atom4499;
atom4664 = atom4652^2;
atom4665 = atom4651^2;
atom2486 = da2*atom2450;
atom2485 = da2*atom2449;
atom4648 = atom81*atom4503+atom4499*atom80;
atom5125 = -atom2485*atom2579+atom2582*atom2486-atom443*atom4499;
atom4667 = atom4651*atom4648;
atom5119 = atom2485*atom2582+atom4502*atom443+atom2579*atom2486;
atom5137 = -da4*atom4648-atom81*atom5119;
atom4668 = atom4648*atom4652;
atom4517 = atom4502*atom4499;
atom4514 = atom4503^2;
atom4515 = atom4502^2;
atom4516 = -atom4514-atom4515;
atom2487 = atom2450^2;
atom5108 = atom4435-(da2^2+atom2487)*d3;
atom4436 = -atom35*g;
atom5111 = atom4436+d3*atom2450*atom2449;
atom5113 = -atom5111*atom2582+atom2579*atom5108;
atom5114 = d4*atom4516-atom4517*r4+atom5113;
atom4521 = atom4502*atom4503;
atom5120 = atom5119+atom4521;
atom4518 = atom4499*atom4503;
atom5126 = -atom5125+atom4518;
atom5131 = -r3*(atom2449^2+atom2487)+2*atom2485*d3;
atom5132 = atom5126*d4-r4*atom5120+atom5131;
atom5134 = atom81*atom5132+atom5114*atom80;
atom4778 = da5+atom4651;
atom4774 = -atom115*atom4652+atom114*atom4648;
atom4891 = -atom4774*atom153+atom152*atom4778;
atom4888 = atom4774*atom152+atom153*atom4778;
atom4905 = atom4891^2;
atom4909 = atom4888^2;
atom5150 = da4*atom4651+atom5119*atom80;
atom4777 = -atom115*atom4648-atom114*atom4652;
atom5153 = atom114*atom5150+atom115*atom5125+da5*atom4777;
atom4892 = da6-atom4777;
atom5177 = -da6*atom4888+atom5137*atom152-atom5153*atom153;
atom4908 = atom4892*atom4888;
atom5171 = da6*atom4891+atom5153*atom152+atom5137*atom153;
atom4911 = atom4892*atom4891;
atom4519 = atom4499^2;
atom4520 = -atom4514-atom4519;
atom5159 = atom5111*atom2579+atom2582*atom5108;
atom5162 = atom5159+atom4517*d4-r4*atom4520;
atom5165 = atom114*atom5162-atom115*atom5134;
atom4797 = atom4777*atom4778;
atom4793 = atom4774*atom4777;
atom4790 = atom4778^2;
atom4795 = atom4774^2;
atom5184 = (atom4905+atom4909)*mz6-mz5*(atom5153-atom4797)-my6*(atom5171+atom4911)+m6*atom5165-(atom4790+atom4795)*my5+m5*atom5165+(atom5177-atom4908)*mx6+(atom5137+atom4793)*mx5;
atom5188 = atom114*atom5134+atom115*atom5162;
atom4791 = atom4777^2;
atom4794 = atom4774*atom4778;
atom5193 = -atom115*atom5150+atom114*atom5125-atom4774*da5;
atom5203 = -atom81*atom5114+atom5132*atom80;
atom5218 = atom5203*atom153+atom5188*atom152;
atom4904 = atom4892^2;
atom4907 = atom4891*atom4888;
atom5226 = (atom5177+atom4908)*mz6-(atom4905+atom4904)*mx6+m6*atom5218+my6*(atom5193+atom4907);
atom5206 = -atom5188*atom153+atom152*atom5203;
atom5214 = -my6*(atom4909+atom4904)+atom5206*m6-mx6*(atom5193-atom4907)-mz6*(atom5171-atom4911);
atom5229 = atom152*atom5226-(atom5137-atom4793)*my5-(atom4791+atom4790)*mx5+mz5*(atom4794+atom5193)-atom153*atom5214+atom5188*m5;
atom5232 = -atom5184*atom115+atom114*atom5229-mx4*(atom4664+atom4665)+mz4*(atom5137+atom4668)+(atom5125+atom4667)*my4+m4*atom5134;
atom4669 = atom4648^2;
atom4671 = atom4651*atom4652;
atom5254 = m4*atom5203+atom153*atom5226+m5*atom5203-(atom4669+atom4664)*my4-(atom5125-atom4667)*mx4-mz5*(atom4791+atom4795)+(atom5153+atom4797)*my5+atom152*atom5214+(atom4794-atom5193)*mx5-mz4*(atom5150-atom4671);
atom5256 = atom80*atom5254+atom5232*atom81;
atom4581 = atom4499*Ixy3;
atom4612 = atom4502*Ixx3-atom4581;
atom4585 = atom4502*Iyy3+atom4581+atom4503*Iyz3;
atom4590 = Ixz3*atom4499+atom4503*Izz3+atom4502*Iyz3;
atom4741 = Ixz4*atom4648+Izz4*atom4652+atom4651*Iyz4;
atom4736 = atom4648*Ixy4+atom4651*Iyy4+Iyz4*atom4652;
atom4959 = atom4888*Ixx6+atom4891*Ixy6+atom4892*Ixz6;
atom4969 = atom4892*Izz6+atom4891*Iyz6+Ixz6*atom4888;
atom5362 = atom5171*Ixy6+mz6*atom5218+atom4959*atom4892-atom4969*atom4888-atom5193*Iyz6+atom5165*mx6+atom5177*Iyy6;
atom4964 = atom4888*Ixy6+atom4891*Iyy6+atom4892*Iyz6;
atom5351 = -Ixz6*atom5193+atom5177*Ixy6-mz6*atom5206+atom5171*Ixx6+atom4969*atom4891-my6*atom5165-atom4892*atom4964;
atom4855 = Izz5*atom4778+atom4777*Iyz5+atom4774*Ixz5;
atom4850 = atom4774*Ixy5+atom4778*Iyz5+atom4777*Iyy5;
atom5365 = atom4855*atom4777-atom153*atom5362+atom5351*atom152+atom5153*Ixx5+atom5193*Ixy5+Ixz5*atom5137+atom5203*my5-atom4850*atom4778-mz5*atom5165;
atom4845 = atom4777*Ixy5+Ixz5*atom4778+atom4774*Ixx5;
atom5329 = atom5206*mx6+atom5177*Iyz6-my6*atom5218+atom5171*Ixz6-Izz6*atom5193-atom4959*atom4891+atom4888*atom4964;
atom5330 = atom5137*Iyz5+atom5153*Ixy5+atom5193*Iyy5-atom5203*mx5-atom5329-atom4774*atom4855+atom4845*atom4778+atom5188*mz5;
atom5378 = -atom4736*atom4652-Ixz4*atom5125-atom5162*my4+atom4741*atom4651+atom5137*Ixy4-atom115*atom5330-mz4*atom5203+atom5150*Ixx4+atom114*atom5365;
atom4731 = Ixz4*atom4652+atom4648*Ixx4+atom4651*Ixy4;
atom5393 = Izz5*atom5137+atom152*atom5362-atom4777*atom4845+atom4774*atom4850-atom5188*my5+atom5165*mx5+atom5153*Ixz5+atom5193*Iyz5+atom5351*atom153;
atom5404 = atom5393+atom5137*Iyy4+mz4*atom5134+atom4652*atom4731-atom4741*atom4648-Iyz4*atom5125+atom5150*Ixy4+mx4*atom5162;
atom5408 = my3*atom5131-atom81*atom5404+atom80*atom5378-atom4503*atom4585-atom5256*r4+atom4612*da2+atom4502*atom4590+atom4612*da3-mz3*atom5159;
atom4462 = Ixy2*atom2450+Ixx2*atom2449+da2*Ixz2;
atom4577 = atom4502*Ixy3;
atom4580 = atom4577+Ixx3*atom4499+Ixz3*atom4503;
atom4617 = atom4577-Iyy3*atom4499;
atom5423 = atom4736*atom4648-atom4651*atom4731+atom5203*mx4-atom114*atom5330-Izz4*atom5125-atom5134*my4+Ixz4*atom5150+atom5137*Iyz4-atom115*atom5365;
atom5432 = -atom5256*d4-atom4499*atom4590+atom4580*atom4503+atom4617*da3+atom4617*da2+mz3*atom5113-mx3*atom5131-atom5423;
atom5276 = (atom5150+atom4671)*my4-atom115*atom5229-mz4*(atom4669+atom4665)-mx4*(atom5137-atom4668)-atom5184*atom114-m4*atom5162;
atom5284 = -mz3*(atom5119-atom4521)+atom4517*mx3+my3*atom4520+m3*atom5159-atom5276;
atom5295 = -atom81*atom5254+atom5232*atom80;
atom5296 = mx3*atom4516+m3*atom5113+atom4517*my3+mz3*(atom5125+atom4518)+atom5295;
atom4465 = da2*Iyz2+Ixy2*atom2449+Iyy2*atom2450;
atom5446 = atom2579*atom5284-atom5296*atom2582;
atom7796 = Ixz3*atom4606+atom4602*Iyz3+atom5589*r4+atom81*atom5659+atom5683*atom80-atom2585*my3+mx3*atom2588-atom5578*d4;
atom6204 = -d4*atom5795+atom81*atom5839+atom5804*r4+atom80*atom5850+mx3*atom2590-atom2589*my3+Izz3;
atom6215 = atom80*atom5979+atom81*atom5968-d4*atom5929+Izz3+r4*atom5934;
atom6224 = atom6060*atom80+atom81*atom6058+atom6044*r4-d4*atom6040;
atom6233 = -atom3890*atom80-d4*atom6107+atom6111*r4+atom81*atom6124;
atom6242 = r4*atom6161+atom80*atom3839-atom6157*d4+atom81*atom6172;
atom4623 = -atom4499*Iyz3+Ixz3*atom4502;
atom5467 = atom4623*da2+atom5404*atom80+atom5295*r4+atom4499*atom4585+atom81*atom5378+atom4623*da3-atom5113*my3+atom5159*mx3-d4*atom5276-atom4502*atom4580;

MQrecsubs_ = [atom35*(atom5687*atom2582-r3*(atom2582*atom5582+atom2579*atom5590)+atom35*Iyy2-atom2579*atom5705+atom36*Ixy2+d3*(m3*atom299+atom5562-atom4602*mx3+atom4606*my3))-(atom5687*atom2579-atom36*Ixx2-r3*atom5717+atom2582*atom5705-atom35*Ixy2)*atom36+Izz1 , -atom36*(atom2582*atom5863-r3*atom5875+atom5854*atom2579+Ixz2)-atom35*(atom2579*atom5863+Iyz2+r3*(atom2579*atom5805+atom2582*atom5798)-atom5854*atom2582-d3*atom5785) , atom36*(r3*atom6001-atom5991*atom2582-atom5983*atom2579)+atom35*(atom5922*d3-r3*(atom2582*atom5930+atom5935*atom2579)-atom5991*atom2579+atom5983*atom2582) , -atom36*(atom6063*atom2579-r3*atom6080+atom2582*atom6070)+atom35*(atom6063*atom2582-r3*(atom6044*atom2579-atom2582*atom6040)-atom2579*atom6070+atom6036*d3) , atom36*(r3*atom6144-atom2579*atom6128-atom6134*atom2582)-atom35*(r3*(atom6111*atom2579-atom2582*atom6107)-atom2582*atom6128-d3*atom6103+atom6134*atom2579) , -atom36*(atom2582*atom6181+atom2579*atom6176-r3*atom6191)+(atom2582*atom6176-atom2579*atom6181+atom6155*d3-r3*(atom2579*atom6161-atom6157*atom2582))*atom35 , -(Ixx2*atom2486-atom4465*da2-atom4436*mz2+atom2579*atom5408+atom4467*atom2450+atom2582*atom5432-atom2485*Ixy2-r3*atom5446)*atom36-atom35*(atom4435*mz2+r3*(atom2582*atom5284+atom5296*atom2579)+Ixy2*atom2486+da2*atom4462-(atom5256+atom5126*mx3+atom5120*my3+m3*atom5131-mz3*(atom4519+atom4515))*d3-Iyy2*atom2485-atom2582*atom5408-atom4467*atom2449+atom2579*atom5432);
atom5717*d3-atom36*Ixz2+atom7796-atom35*Iyz2 , atom5875*d3+atom6204+Izz2 , atom6215+d3*atom6001 , atom6224+d3*atom6080 , atom6233+atom6144*d3 , atom6242+atom6191*d3 , atom5467-atom4462*atom2450+atom2486*Ixz2-atom2485*Iyz2+atom4465*atom2449-atom4435*my2+atom4436*mx2+atom5446*d3;
atom7796 , atom6204 , atom6215 , atom6224 , atom6233 , atom6242 , atom5467;
atom5701 , atom5859 , atom5988 , atom6068 , atom6132 , atom6179 , atom5423;
atom5673 , atom5848 , atom5977 , -atom3889 , -atom3890 , atom3839 , atom5393;
atom5614 , atom5818 , atom5947 , atom3822 , atom3839 , Izz6 , atom5329];

%endfunction
