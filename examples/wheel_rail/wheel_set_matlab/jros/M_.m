function M = M_(in1,t,in3)
%M_
%    M = M_(IN1,T,IN3)

%    This function was generated by the Symbolic Math Toolbox version 5.7.
%    18-Apr-2016 12:49:31

I = in3(:,3);
m = in3(:,2);
M = reshape([m,0.0,0.0,I],[2, 2]);
