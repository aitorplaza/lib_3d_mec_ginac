%% Coord q
if strcmp(COORD,'COORD_DEP')
	for i=1:1
		delta_q = (pinv(Phi_q(q,dq)) * Phi(q,dq));
		q = q - delta_q;
    end
    delta_dq = (pinv(dPhi_dq(q,dq)) * (Beta(q,dq) - (dPhi_dq(q,dq) * dq))); % correction
	dq = dq + delta_dq;  
end
%% Coord z
if strcmp(COORD,'COORD_IND')
	z = q(1:n_coord_indep);
	d = q((n_coord_indep+1):n_gen_coord);
	dz = dq(1:n_vel_indep);
	dd = dq((n_vel_indep+1):n_gen_coord);    
    
	for i=1:1
		delta_d = (pinv(Phi_d(q,dq)) * Phi(q,dq));
		d = d - delta_d;
	end
	q = [z;d];
    dd = (pinv(Phi_d(q,dq)) * (Beta(q,dq) - (Phi_z(q,dq) * dz))); % correction
   	dq = [dz;dd];
end