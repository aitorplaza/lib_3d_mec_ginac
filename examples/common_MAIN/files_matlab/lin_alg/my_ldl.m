function [L,D]=my_ldl(A)

n = length( A );
L = zeros( n, n );
D = zeros( n, n );

for j=1:n
    AUX_D_k=0;
    for k=1:j-1
        AUX_D_k=AUX_D_k + L(j,k)*L(j,k)*D(k,k);
    end
    D(j,j)=A(j,j)-AUX_D_k;
    for i=j+1:n
        AUX_L_k=0;        
        for k=1:j-1
            AUX_L_k=AUX_L_k + L(i,k)*L(j,k)*D(k,k);
        end
        L(i,j)=(A(i,j)-AUX_L_k)/D(j,j);
    end
    L(j,j)=1;
end

