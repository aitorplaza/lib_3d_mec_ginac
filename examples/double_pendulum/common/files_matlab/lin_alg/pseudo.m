disp('****************************');
disp('SISTEMA determinado');

A=[1,1,1;2,1,0;2,0,1]
b=[1;1;3]

disp('inversa');
x=A^-1*b
COMP=A*x-b

disp('pseudo-inversa');
xp=pinv(A)*b
COMP=A*xp-b

disp('division-inversa');
xd=A\b
COMP=A*xd-b

disp('pseudo-inversa calculada');
pinvA=(A'*A)^-1 * A';
xc=pinvA*b
COMP=A*xc-b

disp('****************************');
disp('SISTEMA sobre-determinado');

AM=[1,1,1;2,1,0;2,0,1;0,1,1]
bM=[1;1;3;0]

disp('inversa');
disp('SOLO inversa de matrices cuadradas');
disp('');

disp('pseudo-inversa');
xMp=pinv(AM)*bM
COMP=AM*xMp-bM

disp('division-inversa');
xMd=AM\bM
COMP=AM*xMd-bM

disp('pseudo-inversa calculada');
pinvAM = (AM'*AM)^-1 * AM';
xMc=pinvAM*bM
COMP=AM*xMc-bM

disp('****************************');
disp('SISTEMA sub-determinado');

AN=[1,1,1;2,1,0]
bN=[1;1]

disp('inversa');
disp('SOLO inversa de matrices cuadradas');
disp('');

disp('pseudo-inversa');
xNp=pinv(AN)*bN
COMP=AN*xNp-bN

disp('division-inversa');
xNd=AN\bN
COMP=AN*xNd-bN

disp('pseudo-inversa calculada');
pinvAN = AN'* (AN*AN')^-1 ;
xNc=pinvAN*bN
COMP=AN*xNc-bN