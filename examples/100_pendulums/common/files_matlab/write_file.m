n=100;
T=[ones(n,1),zeros(n,3)];
T(1,1)=0;
T(1,2)=pi/2;

DH_generate_main_symbolic(T,1);

