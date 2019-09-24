%  This algorithm calculates the reduced model of a W*phi=tau model, with the minimum number
%  of parameters in phib, so that: norm(Wred*phib-tau)/norm(tau) < tol
%  The algorithm removes one-by-one a column of Wred
%  The column selected each time is the one that minimises: norm(Wi*pinv(Wi)*tau - tau)/norm(tau)
%  being Wi the matrix Wred without the i-th column and being pinv(Wi) the pseudoinverse of Wi
function [tol,valerror_elim,valerror_add,valerror_qr,n_elim,n_add,n_qr]=reduction(tol)


%  load matrix W and vector phi
load W_estimation.mat;
load pnum.mat;

W=W_estimation;
clear W_estimation;
phi=pnum;
clear pnum;

% calculate tau in terms of W and phi
tau=W*phi;

%  Relative tolerance for the error
%  tol=0.001;
%  tol=inf

%  Total number of parameters of the full model
nparam=length(phi);

%  The first reduced W is the full W
Wred=W;

%  The first reduced phi is the full phi
phired=phi;

%  The vector of the parameters of the reduced model
indexvector=1:nparam;


%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------the algorithm will eliminate one parameter at a time -------------------------
%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
for j=1:nparam-1
	error=Inf;
%  	the algorithm will check the error eliminating each parameter of the
%  	current reduced model
	for i=1:size(Wred,2)
	
%  		v is the vector of the column indices without the i
		v=complementary(i,size(Wred,2));
		
%  		W_i is matrix Wred without column i
		W_i=Wred(:,v);
		
%  		tau_i is the part of tau that can be written in terms of W_i
		phi_i=pinv(W_i)*tau;
		tau_i=W_i*phi_i;
		
%  		error_i is the normalized difference between tau and tau_i
		error_i=norm(tau-tau_i)/norm(tau);
		
%  		if the current error is smaller that all the previous ones
%  		the index of the column is marked as the smallest-error-column-index
		if error_i<error
		      error=error_i;
		      index=i;
		end
	end
	
%  	if the error between full-model and smallest-error-reduced-model is smaller than tol
%  	then reduce the model eliminating column with index "index"
	if error<tol
	
%  		v is the vector of the columns without the index
		v=complementary(index,size(Wred,2));
		
%  		Waux is the new reduced model matrix
%  		phiaux is the new reduced model parameter vector
%  		auxvector is the index vector of the new reduced model
		Waux=Wred(:,v);
		phiaux=phired(v);
		auxvector=indexvector(v);
		clear Wred;
		clear phired;
		clear indexvector;
		Wred=Waux;
		phired=phiaux;
		indexvector=auxvector;
	else
		break;
	end
	verror(j)=error;
end

indexvector_eliminate=indexvector;
clear indexvector;

%  figure,semilogy(verror,'r')
%  hold on

clear verror



%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------the algorithm will add one parameter at a time -------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
Wred=[];
indexvector=[];
for j=1:nparam-1
	error=Inf;
%  	the algorithm will check the error adding one parameter to the
%  	current reduced model
% 	v is the vector of the column indices that have not been selected yet
	v=complementary(indexvector,nparam);
	for i=1:length(v)
		
%  		W_i is matrix Wred with the additional column i
		W_i=[Wred,W(:,v(i))];
		
%  		tau_i is the part of tau that can be written in terms of W_i
		phi_i=pinv(W_i)*tau;
		tau_i=W_i*phi_i;
		
%  		error_i is the normalized difference between tau and tau_i
		error_i=norm(tau-tau_i)/norm(tau);
		
%  		if the current error is smaller that all the previous ones
%  		the index of the column is marked as the smallest-error-column-index
		if error_i<error
		      error=error_i;
		      index=i;
		end
	end
	
%  	if the error between full-model and smallest-error-reduced-model is still bigger than tol
%  	then extend the model adding the column with index "index"

%  	parameter index 
	indexvector=[indexvector,v(index)];
	
%  	Wred is the new reduced model matrix
	Wred=W(:,indexvector);
	verror(nparam- j)=error;
	
	if error<tol
		break;
	end
end

indexvector_add=indexvector;
clear indexvector;

%  semilogy(verror,'g')
clear verror

%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  ------------------------------------ QR DECOMPOSITION METHOD ---------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  qr method
%  [Q,R,E] = QR(A) produces unitary Q, upper triangular R and a
%  permutation matrix E so that A*E = Q*R. The column permutation E is
%  chosen so that ABS(DIAG(R)) is decreasing.
[Q,R,E]=qr(W);
indexvector=E'*[1:size(E,1)]';
RAUX=R;
for j=1:nparam-1
	RAUX(:,nparam-j+1)=zeros(size(R,1),1);
	WAUX=Q*RAUX*E';
	tauredqr=WAUX*(pinv(WAUX)*tau);
	auxerror=norm(tau-tauredqr)/norm(tau);
	if auxerror>tol
		break
	else
		verror(j)=auxerror;
	end	
end

indexvector_qr=indexvector(1:nparam-j+1);
indexvector_qr=indexvector_qr(:)';
indexvector_qr;

clear indexvector;
clear auxerror;

%  semilogy(verror,'b')

%  semilogy(tol*ones(1,length(phi)),'k')

%  legend('eliminating','adding','qr','tol')


clear verror

n_elim=length(indexvector_eliminate)
n_add =length(indexvector_add)
n_qr  =length(indexvector_qr)

%  return

%  falta comparar la ordenación de parámetros que nos da cada método, utilizando la trayectoria de validación en vez de la de reducción del método.





%  
%  %  ----------------------------------------------------------------------------------------------------------
%  %  ----------------------------------------------------------------------------------------------------------
%  %  --------------------------------------------- BASE PARAMETER CALCULATION --------------------------------
%  %  ----------------------------------------------------------------------------------------------------------
%  %  ----------------------------------------------------------------------------------------------------------
%  %  The symbolic parameters vector is defined
%  %  syms m1  mx1  mz1  Iyy1  m2  mx2  mz2  Iyy2  m3  mx3  my3  mz3  Ixy3  Ixx3  Ixz3  Iyy3  Iyz3  Izz3  m4  mx4  my4  mz4  Ixy4  Ixx4  Ixz4  Iyy4  Iyz4  Izz4  m5  mx5  my5  mz5  Ixy5  Ixx5  Ixz5  Iyy5  Iyz5  Izz5  mx6  my6  mz6  Ixy6  Ixx6  Ixz6  Iyy6  Iyz6  Izz6  m7  mx7  my7  mz7  Ixy7  Ixx7  Ixz7  Iyy7  Iyz7  Izz7 real;
%  
%  syms mP mxP myP mzP IxxP IxyP IyyP IxzP IyzP IzzP m1 mx1 my1 mz1 Ixx1 Ixy1 Iyy1 Ixz1 Iyz1 Izz1 m2 mx2 my2 mz2 Ixx2 Ixy2 Iyy2 Ixz2 Iyz2 Izz2 m3 mx3 my3 mz3 Ixx3 Ixy3 Iyy3 Ixz3 Iyz3 Izz3 m4 mx4 my4 mz4 Ixx4 Ixy4 Iyy4 Ixz4 Iyz4 Izz4 m5 mx5 my5 mz5 Ixx5 Ixy5 Iyy5 Ixz5 Iyz5 Izz5 m6 mx6 my6 mz6 Ixx6 Ixy6 Iyy6 Ixz6 Iyz6 Izz6 real
%  
%  load psym.mat;
%  psym';
%  
%  %  The vector of the parameters of the reduced model
%  disp('Parameters of the reduced model')
%  psym(indexvector)'
%  
%  %  Indices of the independent parameters
%  pind=indexvector;
%  %  Indices of the dependent parameters
%  pdep=complementary(pind,length(phi));
%  
%  %  Wind is the Wmatrix of the reduced model
%  Wind=W(:,pind);
%  %  Wdep is the rest of the full matrix
%  Wdep=W(:,pdep);
%  
%  %  Wdep0 is the part of Wdep that can be written as 
%  %  a linear combination of the columns of Wind.
%  %  It should be very close to Wdep
%  Wdep0=Wind*pinv(Wind)*Wdep;
%  
%  %  W0 is the full W matrix with the columns ordered
%  %  writing the independent in the begining
%  W0=[Wind,Wdep0];
%  
%  %  indexV21 are the indices of the independent parameters
%  indexV21=1:size(Wind,2);
%  %  indexV22 are the indices of the dependent parameters
%  indexV22=size(Wind,2)+1:size(W,2);
%  
%  disp('Performing SVD decomposition')
%  [U S V]=svd(W0);
%  
%  rs=rank(S);
%  lp2=length(psym);
%  
%  %  Check if the rank of S equals the rank of Wind
%  if rs==size(Wind,2)
%  	disp('The rank of W0 equals the number of columns of Wind')
%  else
%  	disp('The rank of W0 is not equal to the number of columns of Wind')
%  	return
%  end
%  	
%  fprintf('\n')
%  fprintf('There are %d parameters related to the dynamics.\n\n',lp2)
%  fprintf('There are %d base parameters.\n\n',rs)
%  fprintf('There are %d relations between the parameters.\n',lp2-rs)
%  
%  % Selecting the columns of V that correspond to the zero singular values
%  V2=V(:,rs+1:lp2);
%  
%  % Matrix reordering.
%  V22=V2(indexV22,:);
%  V21=V2(indexV21,:);
%  %  disp('rango de V22')
%  %  rank(V22)
%  
%  % The BETA matrix calculation
%  beta=-V21*inv(V22);
%  
%  %  Eliminate the elements of beta smaller than a tolerance
%  for i=1:length(beta(:,1))
%  	for j=1:length(beta(1,:))
%  		if abs(beta(i,j))<1e-12
%  			beta(i,j)=0;
%  		end
%  	end
%  end
%  
%  % The base parameters definition
%  P_BASE=psym(pind) + beta*psym(pdep);
%  
%  %  Obtain the numerical base parameters with 4 significant digits
%  P_BASE=vpa(P_BASE,4);
%  disp('base parameters expressions')
%  P_BASE
%  save P_BASE P_BASE
%  
%  %  Calculation of the error with the base parameters expressions
%  numbeta=double(beta);
%  relerror=norm(tau - Wind*(phi(pind)+numbeta*phi(pdep)))/norm(tau);
%  relerror


%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  -----------------------------------VALIDATION OF THE REDUCTION METHODS -----------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  ----------------------------------------------------------------------------------------------------------
%  load Wvalidation.mat;
load W_validation.mat
tauval=W_validation*phi;


%  independent and dependent parameters for each reduced model
%  Indices of the independent parameters
pind_elim=indexvector_eliminate;
pind_add =indexvector_add;
pind_qr  =indexvector_qr;

%  Indices of the dependent parameters
pdep_elim=complementary(pind_elim,length(phi));
pdep_add =complementary(pind_add ,length(phi));
pdep_qr  =complementary(pind_qr  ,length(phi));

%  tau estimation of the reduced models
taured_elim=W_validation(:,pind_elim)*pinv(W_validation(:,pind_elim))*tauval;
taured_add =W_validation(:,pind_add )*pinv(W_validation(:,pind_add ))*tauval;
taured_qr  =W_validation(:,pind_qr  )*pinv(W_validation(:,pind_qr  ))*tauval;

%  taured_elim=W_validation(:,pind_elim)*(phi(pind_elim)+numbeta*phi(pdep_elim));
%  taured_add =W_validation(:,pind_add )*(phi(pind_add )+numbeta*phi(pdep_add ));
%  taured_qr  =W_validation(:,pind_qr  )*(phi(pind_qr  )+numbeta*phi(pdep_qr  ));

valerror_elim=norm(tauval - taured_elim)/norm(tauval);
valerror_add =norm(tauval - taured_add )/norm(tauval);
valerror_qr  =norm(tauval - taured_qr  )/norm(tauval);

[tol,valerror_elim,valerror_add,valerror_qr]

%  % validation tau of the full model for each actuator
%  tauval_1=tauval(1:6:end);
%  tauval_2=tauval(2:6:end);
%  tauval_3=tauval(3:6:end);
%  tauval_4=tauval(4:6:end);
%  tauval_5=tauval(5:6:end);
%  tauval_6=tauval(6:6:end);
%  
%  % validation tau of the elimination reduced model for each actuator
%  taured_elim_1=taured_elim(1:6:end);
%  taured_elim_2=taured_elim(2:6:end);
%  taured_elim_3=taured_elim(3:6:end);
%  taured_elim_4=taured_elim(4:6:end);
%  taured_elim_5=taured_elim(5:6:end);
%  taured_elim_6=taured_elim(6:6:end);
%  
%  % validation tau of the additional reduced model for each actuator
%  taured_add_1=taured_add(1:6:end);
%  taured_add_2=taured_add(2:6:end);
%  taured_add_3=taured_add(3:6:end);
%  taured_add_4=taured_add(4:6:end);
%  taured_add_5=taured_add(5:6:end);
%  taured_add_6=taured_add(6:6:end);
%  
%  % validation tau of the qr-based reduced model for each actuator
%  taured_qr_1=taured_qr(1:6:end);
%  taured_qr_2=taured_qr(2:6:end);
%  taured_qr_3=taured_qr(3:6:end);
%  taured_qr_4=taured_qr(4:6:end);
%  taured_qr_5=taured_qr(5:6:end);
%  taured_qr_6=taured_qr(6:6:end);
%  
%  
%  t=1:length(taured_elim_1);
%  
%  figure,
%  subplot(2,3,1),plot(t,tauval_1,'k',t,taured_elim_1,'r',t,taured_add_1,'g',t,taured_qr_1,'b');
%  subplot(2,3,2),plot(t,tauval_2,'k',t,taured_elim_2,'r',t,taured_add_2,'g',t,taured_qr_2,'b')
%  subplot(2,3,3),plot(t,tauval_3,'k',t,taured_elim_3,'r',t,taured_add_3,'g',t,taured_qr_3,'b');
%  subplot(2,3,4),plot(t,tauval_4,'k',t,taured_elim_4,'r',t,taured_add_4,'g',t,taured_qr_4,'b');
%  subplot(2,3,5),plot(t,tauval_5,'k',t,taured_elim_5,'r',t,taured_add_5,'g',t,taured_qr_5,'b');
%  subplot(2,3,6),plot(t,tauval_6,'k',t,taured_elim_6,'r',t,taured_add_6,'g',t,taured_qr_6,'b');
%  
%  tauerror_elim=[tauval_1-taured_elim_1,tauval_2-taured_elim_2,tauval_3-taured_elim_3,tauval_4-taured_elim_4,tauval_5-taured_elim_5,tauval_6-taured_elim_6];
%  tauerror_add=[tauval_1-taured_add_1,tauval_2-taured_add_2,tauval_3-taured_add_3,tauval_4-taured_add_4,tauval_5-taured_add_5,tauval_6-taured_add_6];
%  tauerror_qr=[tauval_1-taured_qr_1,tauval_2-taured_qr_2,tauval_3-taured_qr_3,tauval_4-taured_qr_4,tauval_5-taured_qr_5,tauval_6-taured_qr_6];
%  
%  figure,
%  subplot(1,3,1),plot(t,tauerror_elim)
%  subplot(1,3,2),plot(t,tauerror_add )
%  subplot(1,3,3),plot(t,tauerror_qr  )

