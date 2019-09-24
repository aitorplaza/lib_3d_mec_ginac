%% Coord q
if strcmp(COORD,'COORD_DEP')
    aux = inv(MXdPhi_dqZero(q,dq)) * Qgamma(q,dq);
	ddq = aux(1:n_gen_vel);
	unknowns = aux((n_gen_vel+1):(n_gen_vel + n_unknowns));
end
%% Coord z
if strcmp(COORD,'COORD_IND')
    inv_Phi_d = inv(Phi_d(q,dq));
    A  = -(inv_Phi_d * Phi_z(q,dq));
	b  = (inv_Phi_d * Gamma(q,dq));
	MZ = Mzz(q,dq)+ A' * Mzd(q,dq)' + Mzd(q,dq) * A + A' * Mdd(q,dq)' * A;
	QZ = (Qz(q,dq) + A' * Qd(q,dq)) - (Mzd(q,dq) + A' * Mdd(q,dq)') * b;
    
	ddz = inv(MZ) * QZ;
	ddd = A*ddz + b;
	ddq = [ddz;ddd];
end