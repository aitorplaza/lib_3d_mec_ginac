A=[0 -1 3.25 0.2 50 100;
       0 2 1 7 1 50;
      2.4 10.4 -1.8 0 0 150;
       2.4 12.4 -0.8 7 1 200]
b=[-0.75;22;-3.6;0.2]

%tol=1e-14;
%pm_opt='matrix';
%A=[-6 -1 3.25 10.25;12 2 1 0;2.4 10.4 -1.8 2;0 1 14.8 1.2]
[L,U,p,q]=lucp_paraver(A)

