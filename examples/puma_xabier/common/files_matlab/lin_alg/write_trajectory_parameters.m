function write_trajectory_parameters;

%  The number of degrees of freedom of the mechanism
DOF=6;

%  The number of harmonics for the Fourier Series
H=4;

s=[];
for i=1:DOF
      s=[s,'FS00',int2str(i)];
      for h=1:H
	s=[s,'FSa',int2str(h),int2str(i),'FSb',int2str(h),int2str(i)];
      end
end
	    

sname='mytra_ml337';

eval(['load ../',sname,'.txt;']);
eval(['c=',sname,';']);

fprintf(['// Values of the parameters for the optimized trajectory: ',sname,'\n']);
for i=1:length(s)/5
	fprintf('\tsymbol_numeric ');
	fprintf(s(5*(i-1)+1:5*i));
	fprintf(' = *sys.new_Parameter("');
	fprintf(s(5*(i-1)+1:5*i));
	fprintf('",');
	fprintf('%3.10f',c(i+1));
	fprintf(');\n');
end

