function kalker_forces = fcn(input_vector)
%#codegen
coder.extrinsic('kalker_coeff','Hertz_ellipse','Kalker_linear'); 


N = input_vector(1);
Vxslip = input_vector(2);
Vyslip = input_vector(3);
OMzslip = input_vector(4);
Vo = input_vector(5);
R = input_vector(6);
r = input_vector(7);


E = 210e9; % MPa
nu = 0.27; %Steel
G = E/(2*(1-nu)); % MPa

Ry_w = R; % m
Rx_r = r; % m 
Ry_r = inf; % m
Rx_w = inf; % m  
Radii = [Rx_w,Rx_r,Ry_w,Ry_r];

[a,b] = Hertz_ellipse(N,Radii,E,nu);
KalkerCoeff = zeros(1,4,'int32');
KalkerCoeff = kalker_coeff(a,b,nu);


 
if sqrt(Vxslip^2 + Vyslip^2 + OMzslip^2 ) > 1e-4
  Vx  = Vxslip / (0.5* Vxslip + Vo);
  Vy  = 0;%Output_(4) / (0.5*Output_(4) + Output_(1));
  Phi = 0;%Output_(5) / (0.5*Output_(5) + Output_(1));
%     VxL  = (Output_(3) - (Output_(10) * dq(5)) )/ (0.5 * (Output_(3) + Output_(10) * dq(5)) );
%     VyL  = 0;
%     PHIL = 0; 
%     VxL  = Output_(3) / Output_(1);
%     VyL  = Output_(4) / Output_(1);
%     PHIL = Output_(5) / Output_(1);
  else 
    Vx  = 0;
    Vy  = 0;
    Phi = 0;
  end 
  Vcreep = [Vx;Vy;Phi];
  
kalker_forces = zeros(3,1,'double');
kalker_forces = Kalker_linear(Vcreep,KalkerCoeff,a,b,G)

