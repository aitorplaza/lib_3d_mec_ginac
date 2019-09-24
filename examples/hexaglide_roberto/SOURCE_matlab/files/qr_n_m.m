function [x,p,r]=qr_n_m(A,x,b)

% The function solves the system A*x=b when A is an (n*m) matrix that might have row dependencies.
% x is the  m row unknown vector and b is the n row independent vector.
% P is the permutation made internaly and is used to know which are the dependent and
% independent coordinates once the system is solved.
% n is rank(A)
% x(P(1:n)) are the dependent coordinates while x(P(n+1:m))
% tol is an internal parameter dealing with degree of independence.
% Would be nice to relate it to some internal Matlab parameter.

tol=1e-5;

[Q,R,p]=qr(A,0);
[n,m]=size(A);
 
if ((length(b) ~= n) || (length(x) ~= m))
   error('las dimensiones de A, x, b deben coincidir(n*m,m,n)');
end

r=rank(R);
Ad=R(1:r,1:r); % height limitation to n allows for linear combinations between A rows 
Ai=R(1:r,r+1:m); % idem
% else row index could be wholy expanded i.e. ':'.
% Use of Ai and Ad can be avoided.

xi=x(p(r+1:m)); % use of xi independent coordinates can be avoided.
aux=Q'*b; % would be nice to find a workarround to eliminate the need of the auxiliar array aux.
if m > r
   for i=r+1:n
      if abs(aux(i)) > tol
         error('El sistema es incompatible.');
      end
   end
end
aux=aux(1:r); % height limitation to n allows for linear combinations between A rows
xd=Ad\(aux-Ai*xi);%The inversion should be avoided by Matlab thought Ad is upper diagonal.
% use of xd can be avoided.
x(p(1:r))=xd;

%final remark a per iteration position problem solution must be implemented using this sover.
%
%Tested with
%A =
%    1     2     3
%     4     5     6
%
%b =
%     1
%     2
%
%x =
%   0
%    2.0000
%   0
% and with
%A =
%    1     2     3
%    4     5     6
%    1     2     3

%
%b =
%     1
%     2
%	1
%
%x =
%   0
%    2.0000
%   0
% In both cases x(2) remains unchanged while x satisfies the A *x = b system.
%
% (C) Javier Ros 6-abril-2000
