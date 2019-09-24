time=time + delta_t;
if strcmp(INTEG,'EULER')
    q  = q + (dq + 0.5 * ddq * delta_t ) * delta_t;
    dq = dq + ddq * delta_t;
end

if strcmp(INTEG,'TRAPEZOIDAL')
    qn=q;
	dqn=dq;
    ddqn=ddq;
    
    % Euler
 	%q  = qn + dqn * delta_t;
	%dq  = dqn + ddqn * delta_t;
    
    % Euler mejorado
    q  = qn + (dqn + 0.5 * ddqn * delta_t ) * delta_t;
	dq = dqn + ddqn * delta_t;
    error= sqrt((q-qn)'*(q-qn))+sqrt((dq-dqn)'*(dq-dqn));
    %error = sqrt(Phi(q,dq)' * Phi(q,dq));
	iter=0;

	while error > TRAPEZOIDAL_TOLERANCE
        Solve_Dynamics; % Solucion sistema lineal eq.
        %{
		aux = inv(MXdPhi_dqZero(q,dq)) * Qgamma(q,dq);
		ddq = aux(1:n_gen_vel);
		unknowns=aux((n_gen_vel+1):(n_gen_vel + n_unknowns));
        %}
        qn1=q;
        dqn1=dq;
        ddqn1=ddq;

		q= qn +  0.5 * delta_t * ( dqn + dqn1 );
		dq=dqn + 0.5 * delta_t * ( ddqn + ddqn1 );
   		error= sqrt((q-qn1)'*(q-qn1))+sqrt((dq-dqn1)'*(dq-dqn1));
        %error = sqrt(Phi(q,dq)' * Phi(q,dq)); % same error than euler
		iter=iter+1;
	end
end

