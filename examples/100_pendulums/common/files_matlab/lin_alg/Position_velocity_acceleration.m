
Phi_=Phi(q,dq);
n_coord_dep = length(Phi_);
n_coord_indep = n_gen_coord - n_coord_dep;
q_indep = q(1:n_coord_indep);


state=0;
for time=t_ini:delta_t:t_end
	t=time;
	error_Phi = sqrt(Phi(q,dq)' * Phi(q,dq));
	iter=0;
	while ((error_Phi > NEWTON_RAPHSON_TOLERANCE) && (iter<NEWTON_RAPHSON_MAX_ITER))
		delta_q = ((Phi_q(q,dq)) \ Phi(q,dq));
		q = q - NEWTON_RAPHSON_RELAXATION*delta_q;
		error_Phi = sqrt(Phi(q,dq)' * Phi(q,dq));
		iter=iter+1;
	end
	if iter ==NEWTON_RAPHSON_MAX_ITER
		mount=false;
		disp('----------------------------------------------')
		disp('Se ha salido de la iteracion de Newton-Raphson')
		disp('----------------------------------------------')
		break;
	end
	dq = ((dPhi_dq(q,dq)) \ (Beta(q,dq)));
	ddq = ((dPhiInit_dq(q,dq)) \ (Gamma(q,dq)));

	save_state;

end
