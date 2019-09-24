%% Coord q
if strcmp(COORD,'COORD_DEP')
    if strcmp(LIN,'INV')
        for i=1:NUM_NR_ITER
            delta_q = - (pinv(Phi_q(q,dq)) * Phi(q,dq));
            q = q + delta_q;
        end
        delta_dq = (pinv(dPhi_dq(q,dq)) * (Beta(q,dq) - (dPhi_dq(q,dq) * dq))); % correction
        dq = dq + delta_dq;
    end
    
    if strcmp(LIN,'TRI')
        
        %{
         for i=1:NUM_NR_ITER
            A=pinv(Phi_q(q,dq));
            delta_q = - (A * Phi(q,dq));
            q = q + delta_q;
        end
        delta_dq = (pinv(dPhi_dq(q,dq)) * (Beta(q,dq) - (dPhi_dq(q,dq) * dq))); % correction
        dq = dq + delta_dq;       
        %}
        
        %
        for i=1:NUM_NR_ITER
            AUX=Phi_q(q,dq)*Phi_q(q,dq)';
            L = chol(AUX,'lower');
            y = L  \ Phi(q,dq) ; % b = vector columna
            aux = L' \ y;
            pinv_Phi_q_aux = Phi_q(q,dq)'*aux;
            q = q - pinv_Phi_q_aux;
        end
        AUX=dPhi_dq(q,dq)*dPhi_dq(q,dq)';
        L = chol(AUX,'lower');
        y = L \ (Beta(q,dq) - (dPhi_dq(q,dq) * dq));
        aux = L' \ y;
        pinv_dPhi_dq_aux = dPhi_dq(q,dq)'*aux;
        dq = dq + pinv_dPhi_dq_aux;
        %}
    end
    
end
%% Coord z
if strcmp(COORD,'COORD_IND')
	z = q(1:n_coord_indep);
	d = q((n_coord_indep+1):n_gen_coord);
	dz = dq(1:n_vel_indep);
	dd = dq((n_vel_indep+1):n_gen_coord);    
    
	for i=1:NUM_NR_ITER
		delta_d = ((Phi_d(q,dq)) \ Phi(q,dq));
		d = d - delta_d;
	end
	q = [z;d];
    dd = ((Phi_d(q,dq)) \ (Beta(q,dq) - (Phi_z(q,dq) * dz))); % correction
   	dq = [dz;dd];
end