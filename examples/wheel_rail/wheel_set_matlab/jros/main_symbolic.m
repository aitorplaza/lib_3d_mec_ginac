clear all

syms x dx ddx theta dtheta ddtheta t R m I c Fe Me Xi real

q=[x,theta]'
dq=[dx,dtheta]'
ddq=[ddx,ddtheta]'

param=[ R m I c Fe Me]
T=1/2*m*dx^2+1/2*I*dtheta^2

eq_dyn=jacobian(jacobian(T,dq)',dq)*ddq-jacobian(T,q)'+c*(dx-R*dtheta)*[1,-R]'-[Fe,Me]'


M=jacobian(eq_dyn,ddq);
C=jacobian(eq_dyn,dq);
K=jacobian(eq_dyn,q);

M=simplify(M)
C=simplify(C)
K=simplify(K)

delta=eq_dyn-M*ddq-C*dq-K*q;

delta=-simplify(delta)

matlabFunction(M, 'file', 'M_','vars', {q, t,param});
matlabFunction(C, 'file', 'C_','vars', {q,dq, t,param});
matlabFunction(K, 'file', 'K_','vars', {q,dq, t,param});
matlabFunction(delta, 'file', 'delta_','vars', {q, dq, t,param});



 %~ ddq=(M_(q,t,param)^-1*-C_(q,dq,t,param)*dq+delta_(q,dq,t,param))
 %~ syms delta_t real
 %~ aux=simple(dq-ddq*delta_t)
 %~ 
%~ 
%~ 
%~ dq_new=simplify(inv(jacobian(aux,dq))*(dq+subs(ddq,dq,[0;0])*delta_t))
 
