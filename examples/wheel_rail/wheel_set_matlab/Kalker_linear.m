%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Calculates the relationshio between creepages               % 
%   end creep forces                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function Forces = Kalker_linear(Vcreep,Kalker_coeff,a,b,G)

C11 = Kalker_coeff(1);
C22 = Kalker_coeff(2);
C23 = Kalker_coeff(3);
C33 = Kalker_coeff(4);

K_matrix=[
  C11 , 0             , 0;
  0   , C22           , sqrt(a*b)*C23
  0   , -sqrt(a*b)*C23, (a*b)*C33
];

Forces = - a*b*G* K_matrix * Vcreep;

end
