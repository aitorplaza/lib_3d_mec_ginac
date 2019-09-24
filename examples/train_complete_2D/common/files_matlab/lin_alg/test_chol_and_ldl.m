%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
clc;

Init_variables_parameters;
M_=M(q,dq);
chol(M_,'lower');
my_chol(M_);
test_chol_M=chol(M_,'lower')-my_chol(M_)

ldl(M_,'lower');
my_ldl(M_);
test_ldl_M=ldl(M_,'lower')-my_ldl(M_)

MX_=MXdPhi_dqZero(q,dq);
%chol(MX_,'lower');
%my_chol(MX_)
%test_chol_MX=chol(MX_,'lower')-my_chol(MX_)

[L,D]=ldl(MX_);
[LL,DD]=my_ldl(MX_);
test_ldl_MX=(L*D*L')-(LL*DD*LL')
