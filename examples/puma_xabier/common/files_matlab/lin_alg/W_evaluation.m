% W matrix evaluation

%           	1    2     3    4    5    6     7     8     9     10
%      		m1, mx1, my1, mz1, Ixx1, Ixy1, Iyy1, Ixz1, Iyz1, Izz1,
%  10x1		m2, mx2, my2, mz2, Ixx2, Ixy2, Iyy2, Ixz2, Iyz2, Izz2,
%  10x2		m3, mx3, my3, mz3, Ixx3, Ixy3, Iyy3, Ixz3, Iyz3, Izz3,
%  10x3		m4, mx4, my4, mz4, Ixx4, Ixy4, Iyy4, Ixz4, Iyz4, Izz4,
%  10x4		m5, mx5, my5, mz5, Ixx5, Ixy5, Iyy5, Ixz5, Iyz5, Izz5,
%  10x5		m6, mx6, my6, mz6, Ixx6, Ixy6, Iyy6, Ixz6, Iyz6, Izz6,

%  From all the inertial parameters, user has to select the ones
%  that will be independent. i.e, phi_1 in:
%  phi_b = phi_1 + beta*phi_2

%  %  In this case these are the independent parameters
cols_1=  0+10;
cols_2= 10+[2,3,6,7,8,9,10];
cols_3= 20+[2,3,6,7,8,9,10];
cols_4= 30+[2,3,6,7,8,9,10];
cols_5= 40+[2,3,6,7,8,9,10];
cols_6= 50+[2,3,6,7,8,9,10];

cols=[cols_1,cols_2,cols_3,cols_4,cols_5,cols_6];

cols=1:60;

%  vind=19:24;
%  vdep= 1:18;

Wb=zeros(dof*npts,length(cols));

for i=1:npts
%  	K_all=W(q_all(i,:),dq_all(i,:),ddq_all(i,:));
%  	Kind=K_all(vind,cols);
%  	Kdep=K_all(vdep,cols);
%  	A=Phi_q(q_all(i,:),dq_all(i,:));
%  	Phiq_all=A(1:18,:);
%  	Phiq_ind=Phiq_all(:,vind);
%  	Phiq_dep=Phiq_all(:,vdep);
%  	
%  	X=(-Phiq_ind'*inv(Phiq_dep'))';
%  	
%  	Wi=(Kind+X'*Kdep);
%  	
%  	d=size(Wi,1);
%  	Wb(d*(i-1)+1:d*i,:)=Wi;
	Wi=W(q_all(i,:),dq_all(i,:),ddq_all(i,:));
	Wb(dof*(i-1)+1:dof*i,:)=Wi(:,cols);
end

%  W_all=Wb;
%  
%  disp('Deleting ZERO columns')
%  % Looking for Zero columns and collecting the indices in P1
%  k1=1;k2=1;
%  for i=1:size(W_all,2)
%  	b=true;
%  	for j=1:dof*npts
%  		if W_all(j,i)~=0
%  			b=false;
%  			break;
%  		end
%  	end
%  	if b
%  		% P1 is the vector of the eliminated parameters
%  		P1(k1)=i;
%  		k1=k1+1;
%  	else
%  		% P2 is the vector of the remaining parameters
%  		P2(k2)=i;
%  		k2=k2+1;
%  	end
%  end
%  
%  P1
%  P2
%  
%  % Deleting the Zero columns
%  W_0=W_all(:,P2);
%  
%  disp('Performing SVD decomposition')
%  % Performing the SVD decomposition
%  [U S V]=svd(W_0);
%  
%  
%  rs=rank(S);
%  lp2=length(P2);
%  
%  fprintf('\n')
%  fprintf('There are %d parameters related to the dynamics.\n\n',lp2)
%  fprintf('There are %d base parameters.\n\n',rs)
%  fprintf('There are %d relations between the parameters.\n',lp2-rs)
%  %  fprintf('The selected dependant parameters are the next ones:\n')
%  
%  % Selecting the columns of V that correspond to the zero singular values
%  V2=V(:,rs+1:lp2);
%  
%  %  Method for determining which of the new added parameters should be selected assuming that the basic ones remain selected as in the Valencian model.
%  % 
%  %  indexV22=[1,2,  4,5,    8];
%  %  indexV21=[    3,    6,7,  9,10,11];
%  %  V2=V2([indexV21,indexV22],:);
%  %  
%  %  % This is an automatic way of selecting the parameters that form an invertible V22
%  [R,jb]=rref(V2'); indexV22=jb;jb;
%  jb
%  
%  P2(jb)
%  
%  pause
%  
%  % Matrix reordering.
%  V22=V2(indexV22,:);
%  V21=V2(indexV21,:);
%  %  disp('rango de V22')
%  %  rank(V22)
%  
%  % The BETA matrix calculation
%  beta=V21*inv(V22);
%  
%  for i=1:length(beta(:,1))
%  	for j=1:length(beta(1,:))
%  		if abs(beta(i,j))<1e-12
%  			beta(i,j)=0;
%  		end
%  	end
%  end
%  
%  % Definition of a inertial parameters vector with the "observable" parameters
%  P_O=PARAM(P2);
%  P_O';
%  save P_O P_O;
%  
%  % The base parameters definition
%  P_BASE=P_O(indexV21) - beta*P_O(indexV22);
%  
%  % P_BASE=vpa(P_BASE,10);
%  P_BASE=vpa(P_BASE,4);
%  disp('base parameters expressions')
%  P_BASE
%  
%  save beta beta
%  
%  P_O(indexV22)';
%  P_O(indexV21)';
%  
%  
%  % The W reduced matrix
%  Wred=W_0(:,indexV21);
%  
%  save Wred Wred;
%  save P_BASE P_BASE;

