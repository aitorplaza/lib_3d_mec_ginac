function L=my_chol(A)

n = length( A );
L = zeros( n, n );

for i=1:n
    L(i, i) = sqrt( A(i, i) - L(i, 1:i)*L(i, 1:i)' );
    for j=(i + 1):n
        L(j, i) = ( A(j, i) - L(i, 1:i)*L(j, 1:i)' )/L(i, i);
    end
end