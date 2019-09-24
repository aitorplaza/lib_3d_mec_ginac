% main_reduction
clear all
close all

tol_min=log10(10^-8);
tol_max=log10(10^-0.25);
levels=48;


v = logspace(tol_min,tol_max,levels);

for i=1:length(v)
	[tol(i),valerror_elim(i),valerror_add(i),valerror_qr(i),n_elim(i),n_add(i),n_qr(i)]=reduction(v(i));
end

tol=tol(:);
valerror_elim=valerror_elim(:);
valerror_add =valerror_add(:);
valerror_qr  =valerror_qr(:);
n_elim=n_elim(:);
n_add =n_add(:);
n_qr  =n_qr(:);

save tol tol
save valerror_elim valerror_elim
save valerror_add valerror_add
save valerror_qr valerror_qr

reduction_results=[tol,valerror_elim,valerror_add,valerror_qr,n_elim,n_add,n_qr];

save reduction_results reduction_results

semilogy(n_elim,valerror_elim,'r',n_add,valerror_add,'g',n_qr,valerror_qr,'b') 
xlabel('Number of parameters of the reduced model','FontSize',16)
ylabel('Normalized estimation error: $\frac{\| \tau - \tau_{red} \|}{\|\tau\|}$','Interpreter','LaTex','FontSize',16)
legend('elim','add','qr','FontSize',16)
title('Validation Error. EstTraj=mytra\_ml335. ValTraj=mytra\_cond\_12.')

tol=		reduction_results(:,1);
valerror_elim=	reduction_results(:,2);
valerror_add =	reduction_results(:,3);
valerror_qr  =	reduction_results(:,4);
n_elim=		reduction_results(:,5);
n_add=		reduction_results(:,6);
n_qr=		reduction_results(:,7);
