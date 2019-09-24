clear all;

coord_init;
coord_vect_init;
vel_init;
vel_vect_init;
param_init;
param_vect_init;
inputs_init;
inputs_vect_init;


tic
Mnum=M(q,dq);
toc

tic
Qnum=Q(q,dq);
toc

tic
MQnum=MQ(q,dq);
toc
