clear all

t=0

R=0.5
m=1222.0
I=79.60
c=2e6
Fe=-100
Me=-1*Fe*R

x=0
theta=0

Xi=0.01

dx=0
dtheta=dx/R-Xi/R
q=[x,theta]'
dq=[dx,dtheta]'
%ddq=[ddx,ddtheta]'

param=[ R m I c Fe Me]
delta_t=0.0001
Ri=dq(1,1)-R*dq(2,1);
aux_x=[q;dq;Ri]
t_end=4
alpha=0.001

fixed_point=1

for i=1:t_end/delta_t

%   ddq=M_(q,t,param)^-1*(-C_(q,dq,t,param)*dq+delta_(q,dq,t,param));
%   
%   dq=dq+ddq*delta_t;
dq_pre=dq;
if fixed_point==1
ddq=M_(q,t,param)^-1*(-C_(q,dq_pre,t,param)*dq+delta_(q,dq_pre,t,param));
dq=(1-alpha)*dq+alpha*(dq_pre+ddq*delta_t);
k=0;
while norm(dq-dq_pre)>0.000001*delta_t
    dq_pre=dq;
    ddq=M_(q,t,param)^-1*(-C_(q,dq_pre,t,param)*dq+delta_(q,dq_pre,t,param));
    dq=(1-alpha)*dq+alpha*(dq_pre+ddq*delta_t);
    k=k+1
end
else
 dq=(eye(2)-(M_(q,t,param)^-1*(-C_(q,dq,t,param))*delta_t))^-1*(dq+(M_(q,t,param)^-1*delta_(q,dq,t,param))*delta_t);
 %ddq=M_(q,t,param)^-1*(-C_(q,dq,t,param)*dq+delta_(q,dq,t,param));
end

%q=q+dq*delta_t+1/2*ddq*delta_t^2;
q=q+0.5*(dq_pre+dq)*delta_t;
% Sliding

Ri=dq(1,1)-R*dq(2,1);

t=t+delta_t;

aux_x=[aux_x,[q;dq;Ri]];
end

figure
subplot(5,1,1)
plot(0:delta_t:t_end,aux_x(1,:)')
subplot(5,1,2)
plot(0:delta_t:t_end,aux_x(2,:)')
subplot(5,1,3)
plot(0:delta_t:t_end,aux_x(3,:)')
subplot(5,1,4)
plot(0:delta_t:t_end,aux_x(4,:)')
subplot(5,1,5)
plot(0:delta_t:t_end,aux_x(5,:)')


