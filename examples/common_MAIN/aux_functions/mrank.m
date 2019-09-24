clear all;

coord_init;
coord_vect_init;
vel_init;
vel_vect_init;
param_init;
param_vect_init;


Mnum=Mnew(q,dq);

%if (size(Mnum)(1)>rank(Mnum))
%   printf ("Singular = 1\n");
%else
%   printf ("Singular = 0\n");
%endif

printf ("Rank = %d\n", rank(Mnum));


