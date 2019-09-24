%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Calculates the relationshio between creepages               % 
%   end creep forces                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function Forces = Kalker_linear(Vcreep,a,b,G,nu)

KalkerCoeff = kalker_coeff(a,b,nu);
Kalker_coeff_aux = zeros(1,4);

Kalker_coeff_aux = KalkerCoeff;

C11 = Kalker_coeff_aux(1);
C22 = Kalker_coeff_aux(2);
C23 = Kalker_coeff_aux(3);
C33 = Kalker_coeff_aux(4);

K_matrix=[
  C11 , 0              , 0;
  0   , C22            , sqrt(a*b)*C23;
  0   , -sqrt(a*b)*C23 , (a*b)*C33;
];

Forces = -a * b * G * K_matrix * Vcreep;
%  Forces = [-61.85;0;0];

end