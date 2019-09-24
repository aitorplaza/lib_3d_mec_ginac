%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Calculates   creep forces divided by the creep velocity     % 
%                                                               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function F_V = Fcreep_Vcreep(Vcreep,KalkerCoeff,a,b,G)

  if -1e-4 < Vcreep(1) < 1e-4 && -1e-4 <  Vcreep(2) < 1e-4 && -1e-4 < Vcreep(3) < 1e-4
   F_V = [0;0;0];
  else 
   F_V = Kalker_linear(Vcreep,KalkerCoeff,a,b,G)./Vcreep';
  end
end