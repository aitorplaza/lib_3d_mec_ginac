function [F_k,Vcreep] = KLKR(a,b,dq)
global delta_t;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% KALKER
E = 210e9; % MPa
nu = 0.27; %Steel
G = E/(2*(1-nu)); % MPa
m = 1222;
I = 79.6;
r=0.5;

K=3.28*10^5; %%Mirar esto
gamma=0.5 ;
m_char=I/r^2 ;

g = 9.81;
alpha = 0.05; %angle
% F  max
% F_kmax = I*g*sin(alpha) / ((r^2) *(1+I/(m*r^2)));


Omega = dq(2);
Vx =  dq(1);
% if sqrt(Vx^2)  > 1e-8
%    Vcreep  = (Vx - r*Omega) / (abs(0.5 * (Vx + r*Omega) ));
%    %Vcreep  = (Vx - r*Omega) / (abs(Vx) ); %Funtziona
% else
%    Vcreep  = 0; 
% end

V=1/2*abs( Vx + r*Omega ); 
if (V < ( 1 + gamma ) * delta_t/2 * K/m_char)
  V = ( 1 + gamma ) * delta_t/2 * K/m_char;
end

if sqrt(Vx^2)  > 1e-8
   Vcreep  = (Vx - r*Omega) / abs(V);
   %Vcreep  = (Vx - r*Omega) / (abs(0.5 * (Vx + r*Omega) ));
   %Vcreep  = (Vx - r*Omega) / (abs(Vx) ); %Funtziona
else
   Vcreep  = 0; 
end

kalker_forces = -1*Kalker_linear([Vcreep,0,0]',a,b,G,nu);

% if abs(kalker_forces(1)) >= abs(2*F_kmax)
%     %F_k = F_kmax;
%     F_k = 0.3*m*g*cos(alpha);      
% else
%     F_k = (kalker_forces(1));
% end


F_k = (kalker_forces(1));
%F_k =F_kmax;




