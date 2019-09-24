function lin_sys(A,b)


%A=[25,-5,10;-5,17,10;10,10,62];
%b=[55;-19;114];

%A=[49,14,-7,7;14,29,-12,2;-7,-12,41,-19;7,2,-19,35];
%b=[14;-46;36;-32];

%A = [-6 -1 3.25 10.25; 12 2 1 0; 2.4 10.4 -1.8 2; 0 1 14.8 1.2]
%b = [-0.75;22;-3.6;0.2]


A
b

%% CHOLESKY
%{
L_c=my_chol(A);
n_c = length( L_c );

% Forward substitution
y_c = zeros( n_c, 1 );
aux_y_c = zeros( n_c, 1 );
for i=1:n_c
    for j=1:(i-1);
        aux_y_c(i)=aux_y_c(i)+L_c(i,j)*y_c(j);
    end
    y_c(i)=(b(i)-aux_y_c(i))/L_c(i,i);
end
y_c

% Backward substitution
x_c = zeros( n_c, 1 );
aux_x_c = zeros( n_c, 1 );
for i=n_c:-1:1
    for j=n_c:-1:(i+1);
        aux_x_c(i)=aux_x_c(i)+L_c(j,i)*x_c(j);
    end
    x_c(i)=(y_c(i)-aux_x_c(i))/L_c(i,i);
end
x_c
%}
%% CODIGO DIRECTO
% L_c = chol(A,'lower');
% y_c = L_c  \ b; % b = vector columna
% x_c = L_c' \ y_c;

%% LDL
%{
[L_l,D_l]=my_ldl(A);
n_l = length( L_l );

% Forward substitution
y_l = zeros( n_l, 1 );
aux_y_l = zeros( n_l, 1 );
for i=1:n_l
    for j=1:(i-1);
        aux_y_l(i)=aux_y_l(i)+L_l(i,j)*y_l(j);
    end
    y_l(i)=(b(i)-aux_y_l(i))/L_l(i,i);
end
y_l;

for i=1:n_l
    y_l(i,1)=y_l(i,1)/D_l(i,i);
end
y_l

% Backward substitution
x_l = zeros( n_l, 1 );
aux_x_l = zeros( n_l, 1 );
for i=n_l:-1:1
    for j=n_l:-1:(i+1);
        aux_x_l(i)=aux_x_l(i)+L_l(j,i)*x_l(j);
    end
    x_l(i)=(y_l(i)-aux_x_l(i))/L_l(i,i);
end
x_l
%}
%% CODIGO DIRECTO
% [L_l,D_l]=ldl(A)
% y_l = L_l  \ b; % b = vector columna
% for i=1:n_l
%    y_l(i,1)=y_l(i,1)/D_l(i,i);
%end
% x_l = L_l' \ y_l;

%% PLU
%{
M=A
n = length( M );
L = zeros( n, n );
U = M;
Pt = eye( n, n );
for i=1:(n - 1)
   % find the row with the maximum entry in the ith column on or below the diagonal
   [tmp, j] = max( abs( U(i:n, i) ) ) ;
   j = j + (i - 1);   % account for offset

   if ( tmp == 0 )
      error( 'the matrix is singular (non invertible)' );
   end

   % swap rows 'i' and 'j'
   U ([i, j], :) = U ([j, i], :);
   Pt([i, j], :) = Pt([j, i], :);
   L ([i, j], :) = L ([j, i], :);

   for j=(i + 1):n
      s = -U(j, i)/U(i, i);          % calculate multiplier
      U(j, :) = U(j, :) + s*U(i, :); % add the multiplier times the ith row onto the jth
      L(j, i) = -s;                  % store the negated multiplier
   end
end
Pt
LU=L+U
L = L + eye( n, n );  % add on the identity matrix


y = L \ (Pt * b) % Forward substitution asi o similar a LDL
x = U \ y % Backward substitution asi o similar a LDL
%}

%% LU
M=A;
n = length( M );

for i=1:n
    o(i)=i;
    s(i)=abs(M(i,1));
    for j=2:n
        if (abs(M(i,j)) > s(i))
           s(i)=abs(M(i,j));
        end
    end
end

for k=1:(n - 1)
    p = k; % p is the index to the pivot row
    big = abs(M(o(k),k) / s(o(k)));
    for i=k+1:n
        dummy = abs(M(o(i),k) / s(o(i)));
        if (dummy > big)
            big = dummy;
            p = i;
        end
    end

    dummy = o(p);
    o(p) = o(k);
    o(k) = dummy;

    for i = k+1:n
        factor = M(o(i),k) / M(o(k),k);
        M(o(i),k) = factor;
        for j = k+1:n
            M(o(i),j) = M(o(i),j) - factor * M(o(k),j);
        end
    end
end

LU_piv=M


%{
% Forward substitution
y(o(1)) = b(o(1));
for i = 2 : n
    sum = b(o(i));
    for j = 1 : i-1
        sum = sum - LU_piv(o(i),j) * y(o(j));
    end
    y(o(i)) = sum;
end
y

% Backward substitution
x(n) = y(o(n)) / LU_piv(o(n),n);
for i = n-1:-1: 1 
    sum = 0;
    for j = i+1 : n
        sum = sum + LU_piv(o(i),j) * x(j);
    end
    x(i) = (y(o(i)) - sum) / LU_piv(o(i),i);
end

x

%}

% Forward substitution
y(1) = b(o(1));
for i = 2 : n
    sum = b(o(i));
    for j = 1 : i-1
        sum = sum - LU_piv(o(i),j) * y(j);
    end
    y(i) = sum;
end
y

% Backward substitution
x(n) = y(n) / LU_piv(o(n),n);
for i = n-1:-1: 1 
    sum = 0;
    for j = i+1 : n
        sum = sum + LU_piv(o(i),j) * x(j);
    end
    x(i) = (y(i) - sum) / LU_piv(o(i),i);
end

x


%% CODIGO DIRECTO
% x=M\b
% or
%[L U P] = lu( M ) % CUIDADO en matlab L * U = P * M
%bb = P * b
% y = L \ bb;
% x = U \ y;


