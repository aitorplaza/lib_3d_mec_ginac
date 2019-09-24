%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for t=delta_t: delta_t :t_end;
    
    time=time + delta_t;
  	q_aux = q;
    dq_aux  = -( ( 2 * q / delta_t )  + dq ) ;
    ddq_aux = -( ( 4 * q / delta_t^2 )  + ( 4 * dq / delta_t )  + ddq ) ;
    
    q = q_aux + dq * delta_t + ddq * delta_t^2 / 2;
    dq = dq_aux + 2 * q / delta_t ;
    ddq = ddq_aux + 4 * q / delta_t^2 ;
    
    error= sqrt((q-q_aux)'*(q-q_aux));
    %error = sqrt(Phi(q,dq)' * Phi(q,dq));
    iter=0;

    
    
    
    
    
    
    
    
    
    
    
    
    fq = (delta_t^2 / 4) * ( M(q,dq) * ddq + Phi_q(q,dq)' * (alfa.*Phi(q,dq) + LAMBDA) - Q(q,dq));
    AUX_fq_q = M(q,dq)  - delta_t * Q_dq(q,dq) / 2 - delta_t^2 * Q_q(q,dq) / 4 ;
    fq_q = AUX_fq_q + (delta_t^2 / 4) * ( Phi_q(q,dq)' * ALFA * Phi_q(q,dq));
    inv_fq_q = inv(fq_q);
    
    while error > TRAPEZOIDAL_TOLERANCE
             
        delta_q = - inv_fq_q * fq;
        q = q + delta_q ;
        dq = dq_aux + 2 * q / delta_t ;
        ddq = ddq_aux + 4 * q / delta_t^2 ;
        LAMBDA = LAMBDA + (alfa.*Phi(q,dq));

        error= sqrt(delta_q'*delta_q);
        %error = sqrt(Phi(q,dq)' * Phi(q,dq));
        iter=iter+1;

        
        
        
        
        fq = (delta_t^2 / 4) * ( M(q,dq) * ddq + Phi_q(q,dq)' * (alfa.*Phi(q,dq) + LAMBDA) - Q(q,dq));
        AUX_fq_q = M(q,dq)  - delta_t * Q_dq(q,dq) / 2 - delta_t^2 * Q_q(q,dq) / 4 ;
        fq_q = AUX_fq_q + (delta_t^2 / 4) * ( Phi_q(q,dq)' * ALFA * Phi_q(q,dq));
        inv_fq_q = inv(fq_q);
    end

    %% Corregir VEL-ACEL en instante t
    dq  = inv_fq_q * ( AUX_fq_q * dq  + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Beta (q,dq))));
    ddq = inv_fq_q * ( AUX_fq_q * ddq + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Gamma(q,dq))));
    
    if strcmp(TIME,'OFF')
        save_state;   
    end
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%