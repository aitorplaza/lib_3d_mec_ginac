%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for t=delta_t: delta_t :t_end;
    
    time=time + delta_t;
  	q_aux = q;
    dq_aux  = -( ( 2 * q / delta_t )  + dq ) ;
	ddq_aux = -( ( 4 * q / delta_t^2 )  + ( 4 * dq / delta_t )  + ddq ) ;
    
    q = q_aux + dq * delta_t + ddq * delta_t^2 / 2;
    dq = dq_aux + 2 * q / delta_t;
    ddq = ddq_aux + 4 * q / delta_t^2; 
    
    error= sqrt((q-q_aux)'*(q-q_aux));
    %error = sqrt(Phi(q,dq)' * Phi(q,dq));
    iter=0;
    
    z_aux=q_aux(1:n_coord_indep);
    dz_aux=dq_aux(1:n_vel_indep);
    ddz_aux=ddq_aux(1:n_vel_indep);
    
    z=q(1:n_coord_indep);
    dz=dq(1:n_vel_indep);
    ddz=ddq(1:n_vel_indep);
    
    AA  = -((Phi_d(q,dq)) \ Phi_z(q,dq));
    bb  = ((Phi_d(q,dq)) \ Gamma(q,dq));
    ee  = ((Phi_d(q,dq)) \ Beta(q,dq));

    fz = (delta_t^2 / 4) * (( Mzz(q,dq) + Mzd(q,dq) * AA ) * ddz + Mzd(q,dq) * bb + Phi_z(q,dq)' * (alfa.*Phi(q,dq) + LAMBDA) - Qz(q,dq));
    AUX_fz_z = ( Mzz(q,dq) + Mzd(q,dq) * AA )  - delta_t * Qz_dz(q,dq) / 2 - delta_t^2 * Qz_z(q,dq) / 4 ;
    fz_z = AUX_fz_z + (delta_t^2 / 4) * ( Phi_z(q,dq)' * ALFA * Phi_z(q,dq));
    inv_fz_z = inv(fz_z);

    while error > TRAPEZOIDAL_TOLERANCE
        
        delta_z = - inv_fz_z * fz;
        z = z + delta_z ;                                               q(1:n_coord_indep)=z;
        dz = dz_aux + 2 * z / delta_t ;         dd = AA*dz + ee;        dq = [dz;dd];
        ddz = ddz_aux + 4 * z / delta_t^2 ;     ddd = AA*ddz + bb;      ddq = [ddz;ddd];
        LAMBDA = LAMBDA + (alfa.*Phi(q,dq));
                
        error= sqrt(delta_z'*delta_z);
        %error = sqrt(Phi(q,dq)' * Phi(q,dq));
        iter=iter+1;
        
        AA  = -((Phi_d(q,dq)) \ Phi_z(q,dq));
        bb  = ((Phi_d(q,dq)) \ Gamma(q,dq));
        ee  = ((Phi_d(q,dq)) \ Beta(q,dq));
        
        fz = (delta_t^2 / 4) * (( Mzz(q,dq) + Mzd(q,dq) * AA ) * ddz + Mzd(q,dq) * bb + Phi_z(q,dq)' * (alfa.*Phi(q,dq) + LAMBDA) - Qz(q,dq));
        AUX_fz_z = ( Mzz(q,dq) + Mzd(q,dq) * AA )  - delta_t * Qz_dz(q,dq) / 2 - delta_t^2 * Qz_z(q,dq) / 4;
        fz_z = AUX_fz_z + (delta_t^2 / 4) * ( Phi_z(q,dq)' * ALFA * Phi_z(q,dq));
        inv_fz_z = inv(fz_z);
    end
        
    %% Corregir VEL-ACEL independientes en instante t
    dd = AA*dz + ee;            dq = [dz;dd];
    ddd = AA*ddz + bb;          ddq = [ddz;ddd];    
    
    if strcmp(TIME,'OFF')
        save_state;   
    end
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%