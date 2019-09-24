%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%UNDER DEVELOPMENT
%UNDER DEVELOPMENT
%UNDER DEVELOPMENT

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for t=delta_t: delta_t :t_end;
    
    time=time + delta_t;

  	q_aux = q;
    dq_aux  = -( ( 2 * q / delta_t )  + dq ) ;
	ddq_aux = -( ( 4 * q / delta_t^2 )  + ( 4 * dq / delta_t )  + ddq ) ;
    
    q = q_aux + dq * delta_t + ddq * delta_t^2 / 2 ;
    dq = dq_aux + 2 * q / delta_t ;
    ddq = ddq_aux + 4 * q / delta_t^2 ;
    
    error= sqrt((q-q_aux)'*(q-q_aux));  
    %error = sqrt(Phi(q,dq)' * Phi(q,dq));
    iter=0;
    
    while error > TRAPEZOIDAL_TOLERANCE
        
        fq = (delta_t^2 / 4) * ( M(q,dq) * ddq + Phi_q(q,dq)' * LAMBDA - Q(q,dq));
        fq_q = M(q,dq)  - delta_t * Q_dq(q,dq) / 2 - delta_t^2 * Q_q(q,dq) / 4 ;
        
        BIG_fq=[fq;delta_t^2/4*Phi(q,dq)];
        BIG_fq_q=[fq_q,delta_t^2/4*Phi_q(q,dq)';delta_t^2/4*Phi_q(q,dq),zeros(n_coord_dep,n_coord_dep)];
        
        
        deltaqdeltalambda=-pinv(BIG_fq_q)*BIG_fq;
        delta_q=deltaqdeltalambda(1:n_gen_vel);
        delta_LAMBDA=deltaqdeltalambda(n_gen_vel+1:end);
        %inv_fq_q = inv(fq_q);
        %delta_q = - inv_fq_q * fq;
        %delta_q = - (pinv(Phi_q(q,dq)) * Phi(q,dq));
        %delta_LAMBDA = -(pinv(Phi_q(q,dq)') * ( fq + (fq_q * delta_q))) * (4 / delta_t^2);

        q = q + delta_q ;
        LAMBDA = LAMBDA +  delta_LAMBDA;
        
        dq = dq_aux + 2 * q / delta_t ;
        ddq = ddq_aux + 4 * q / delta_t^2 ;
        
        %LAMBDA = LAMBDA + (alfa.*Phi(q,dq)) ;    
        %dq = (pinv(dPhi_dq(q,dq)) * (Beta(q,dq)));
        %ddq = (pinv(dPhi_dq(q,dq)) * (Gamma(q,dq)));
        %LAMBDA = LAMBDA + (alfa.*Phi(q,dq)) ;
                 
        error= sqrt(delta_q'*delta_q);
        %error = sqrt(Phi(q,dq)' * Phi(q,dq));
        iter=iter+1;
	end

	%% Corregir VEL-ACEL en instante t
%{
    fq = (delta_t^2 / 4) * ( M(q,dq) * ddq + Phi_q(q,dq)' * LAMBDA - Q(q,dq));
    fq_q = M(q,dq)  - delta_t * Q_dq(q,dq) / 2 - delta_t^2 * Q_q(q,dq) / 4 ;
    inv_fq_q = inv(fq_q);
    
    dq  = inv_fq_q * ( fq_q * dq );
    ddq = inv_fq_q * ( fq_q * ddq );
%}
    
     dq = (pinv(dPhi_dq(q,dq)) * (Beta(q,dq)));
     ddq = (pinv(dPhi_dq(q,dq)) * (Gamma(q,dq)));
        
    if strcmp(TIME,'OFF')
        save_state;   
    end
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%