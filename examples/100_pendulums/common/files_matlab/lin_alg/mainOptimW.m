function mainOptimW(c);

USER_defines;
OPTIM_defines;

criterio=OPTIMIZATION_CRITERION;

tmax=t_end;
npts=NPTS;


% Getting constrain matrix and vector
[A,B]=linear_cons(npts);

%  [C,Ceq]=nolinear_cons(c);
C=-1;

% Testing for initial condition restriction violation
if (max(A*c-B)>0) & (max(C)>0)
	disp('No se cumplen las restricciones LINEALES y las NO LINEALES')
	%pause(1);
	return;
elseif max(A*c-B)>0
	disp('No se cumplen las restricciones LINEALES')
	%pause(1)
	return;
elseif max(C)>0
	disp('No se cumplen las restricciones NO LINEALES')
	%pause(1);
	return;
else
	disp('Se cumplen TODAS LAS RESTRICCIONES')
end

% Options for the optimization algorithm
options = optimset('MaxFunEvals',inf,'MaxIter',200,'Display','iter');

% Optimization
tic
%  [sol_nolin,fval,exitflag,output]=fmincon(@(c1)fobjetivo(c1,criterio),c,A,B,[],[],[],[],@nolinear_cons,options);
[sol_nolin,fval,exitflag,output]=fmincon(@(c1)fobjetivo(c1,criterio),c,A,B,[],[],[],[],[],options);
disp('Computational Time for a Single Trajectory')
toc


c2=[tmax;sol_nolin;];

ml= fobjetivo(sol_nolin,1);
con=fobjetivo(sol_nolin,2);
detmax=fobjetivo(sol_nolin,3);
tr=fobjetivo(sol_nolin,4);

vcri=[ml,con,detmax,tr];

c2q(criterio,c2,vcri);
