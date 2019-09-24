% W matrix evaluation

%             	1    2     3    4    5    6     7     8     9     10
%      		mP, mxP, myP, mzP, IxxP, IxyP, IyyP, IxzP, IyzP, IzzP,
%  10x1		m1, mx1, my1, mz1, Ixx1, Ixy1, Iyy1, Ixz1, Iyz1, Izz1,
%  10x2		m2, mx2, my2, mz2, Ixx2, Ixy2, Iyy2, Ixz2, Iyz2, Izz2,
%  10x3		m3, mx3, my3, mz3, Ixx3, Ixy3, Iyy3, Ixz3, Iyz3, Izz3,
%  10x4		m4, mx4, my4, mz4, Ixx4, Ixy4, Iyy4, Ixz4, Iyz4, Izz4,
%  10x5		m5, mx5, my5, mz5, Ixx5, Ixy5, Iyy5, Ixz5, Iyz5, Izz5,
%  10x6		m6, mx6, my6, mz6, Ixx6, Ixy6, Iyy6, Ixz6, Iyz6, Izz6,
	
cols_P =[1,2,3,4,5,6,7,8,9,10];

%  From all the inertial parameters, user has to select the ones
%  that will be independent. i.e, phi_1 in:
%  phi_b = phi_1 + beta*phi_2

%  %  In this case these are the independent parameters (for simulation (me parece))
%  cols_1= 10+[1,2,3,4,5,6,7,8,9,10];
%  cols_2= 20+[1,2,3,4,5,6,7,8,9,10];
%  cols_3= 30+[1,2,3,4,5,6,7,8,9,10];
%  cols_4= 40+[1,2,3,4,5,6,7,8,9,10];
%  cols_5= 50+[1,2,3,4,5,6,7,8,9,10];
%  cols_6= 60+[1,2,3,4,5,6,7,8,9,10];

%  In this case these are the independent parameters (for trajectory optimization (falta el 4 y el 10) (me parece))
cols_1= 10+[1,2,3,5,6,7,8,9,10];
cols_2= 20+[1,2,3,5,6,7,8,9,10];
cols_3= 30+[1,2,3,5,6,7,8,9,10];
cols_4= 40+[1,2,3,5,6,7,8,9,10];
cols_5= 50+[1,2,3,5,6,7,8,9,10];
cols_6= 60+[1,2,3,5,6,7,8,9,10];

%  cols=[cols_P,cols_1,cols_2,cols_3,cols_4,cols_5,cols_6];


if (reduciendo==true && optimizando==false)
    cols=1:70;
elseif (reduciendo==false && optimizando == true)
    cols=[4,7,8,9,10,12,14,15,16,17,18,19,20,21,22,24,25,26,27,28,29,30,31,32,34,35,36,37,38,39,40,41,42,44,45,46,47,48,49,50,51,52,54,55,56,57,58,59,60,61,62,64,65,66,67,68,69,70];
else
    disp('no se ha especificado si se esta optimizando o reduciendo')
    pause
end

vind=19:24;
vdep= 1:18;

Wb=zeros(6*npts,length(cols));

for i=1:npts
	K_all=W(q_all(i,:),dq_all(i,:),ddq_all(i,:));
	Kind=K_all(vind,cols);
	Kdep=K_all(vdep,cols);
	A=Phi_q(q_all(i,:),dq_all(i,:));
	Phiq_all=A(1:18,:);
	Phiq_ind=Phiq_all(:,vind);
	Phiq_dep=Phiq_all(:,vdep);
	
	X=(-Phiq_ind'*inv(Phiq_dep'))';
	
	Wi=(Kind+X'*Kdep);
	
	d=size(Wi,1);
	Wb(d*(i-1)+1:d*i,:)=Wi;
end


% [U,S,V]=svd(Wb);
%  rs=rank(S) 
%  
%  semilogy(diag(S))
%  size(V)
%  pause
%  V2=V(:,rs+1:end);
%  
%  % This is an automatic way of selecting the parameters that form an invertible V22
%  [R,jb]=rref(V2'); indexV22=jb;jb,pause;
%  
%  v=[     1     2     3     5     6    11    13    23    33    43    53    63];
%  r=complementary(v,70);

