%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Calculates the creepage velocity                            % 
%                                                               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function Vcreep = Vcreepage(output,q,dq)

  if output(1) > 1e-4
    Vx  = output(3) / output(1);
    Vy  = output(4) / output(1);
    Phi = output(5) / output(1);  
  elseif output(1) < 1e-4  && (0.001 > output(3) || -0.001 < output(3) )
    Vx  = output(3) / (output(9)*dq(5));
    Vy  = output(4) / (output(9)*dq(5));
    Phi = output(5) / (output(9)*dq(5));  
  else 
    Vx  = 0;
    Vy  = 0;
    Phi = 0;
  end 
end

Vcreep = [Vx;Vy;Phi];
