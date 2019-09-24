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
%    inv_fq_q = inv(fq_q);

%{

% WRONG fq_q NON-symmetric
[L_l,D_l]=ldl(fq_q);
n_l = length( L_l );
y_l = -(L_l  \ fq);
for i=1:n_l
    y_l(i,1)=y_l(i,1)/D_l(i,i);
end
delta_q = L_l' \ y_l;

%    dq  = inv_fq_q * ( AUX_fq_q * dq  + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Beta (q,dq))));
y_l = (L_l  \  ( AUX_fq_q * dq  + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Beta (q,dq)))));
for i=1:n_l
    y_l(i,1)=y_l(i,1)/D_l(i,i);
end
dq = L_l' \ y_l;       

    
%    ddq = inv_fq_q * ( AUX_fq_q * ddq + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Gamma(q,dq))));
y_l = (L_l  \  ( AUX_fq_q * ddq + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Gamma(q,dq)))));
for i=1:n_l
    y_l(i,1)=y_l(i,1)/D_l(i,i);
end
ddq = L_l' \ y_l; 

%}

[L_l U_l P] = lu( fq_q ); % CUIDADO en matlab L * U = P * M
n_l = length( L_l );
aux = - P * fq;
y_l = L_l \ aux;
delta_q = U_l \ y_l;


%    dq  = inv_fq_q * ( AUX_fq_q * dq  + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Beta (q,dq))));
y_l = (L_l  \  ( P * ( AUX_fq_q * dq  + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Beta (q,dq))))));
dq = U_l \ y_l;       

    
%    ddq = inv_fq_q * ( AUX_fq_q * ddq + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Gamma(q,dq))));
y_l = (L_l  \  ( P * ( AUX_fq_q * ddq + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Gamma(q,dq))))));
ddq = U_l \ y_l; 

%%
while error > TRAPEZOIDAL_TOLERANCE
             
%        delta_q = - inv_fq_q * fq;
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
%        inv_fq_q = inv(fq_q);
        
[L_l U_l P] = lu( fq_q ); % CUIDADO en matlab L * U = P * M
n_l = length( L_l );
aux = - P * fq;
y_l = L_l \ aux;
delta_q = U_l \ y_l;


%    dq  = inv_fq_q * ( AUX_fq_q * dq  + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Beta (q,dq))));
y_l = (L_l  \  ( P * ( AUX_fq_q * dq  + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Beta (q,dq))))));
dq = U_l \ y_l;       

    
%    ddq = inv_fq_q * ( AUX_fq_q * ddq + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Gamma(q,dq))));
y_l = (L_l  \  ( P * ( AUX_fq_q * ddq + (delta_t^2 / 4) * ( Phi_q(q,dq)' * (alfa.*Gamma(q,dq))))));
ddq = U_l \ y_l; 

end

%%
 
    if strcmp(TIME,'OFF')
        save_state;   
    end
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%