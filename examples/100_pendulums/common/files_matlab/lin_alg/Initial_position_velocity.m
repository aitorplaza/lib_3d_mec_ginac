Phi_=Phi(q,dq);
n_coord_dep = length(Phi_);
n_coord_indep = n_gen_coord - n_coord_dep;
q_indep = q(1:n_coord_indep);

%% Coord q
if strcmp(COORD,'COORD_DEP')
    error_PhiInit = sqrt(PhiInit(q,dq)' * PhiInit(q,dq));

    while error_PhiInit > NEWTON_RAPHSON_TOLERANCE
        delta_q = ((PhiInit_q(q,dq)) \ PhiInit(q,dq));
        q = q - delta_q;
        error_PhiInit = sqrt(PhiInit(q,dq)' * PhiInit(q,dq));
    end
    dq = ((dPhiInit_dq(q,dq)) \ (BetaInit(q,dq)));
end
%% Coord z
if strcmp(COORD,'COORD_IND')
    Beta_=Beta(q,dq);
    n_vel_dep = length(Beta_);
    n_vel_indep = n_gen_vel - n_vel_dep;

    z = q(1:n_coord_indep);
    d = q((n_coord_indep+1):n_gen_coord);

    error_Phi = sqrt(Phi(q,dq)' * Phi(q,dq));

    while error_Phi > NEWTON_RAPHSON_TOLERANCE
        delta_d = ((Phi_d(q,dq)) \ Phi(q,dq));
        d = d - delta_d;
        q = [z;d];
        error_Phi = sqrt(Phi(q,dq)' * Phi(q,dq));
    end
    dz = dq(1:n_vel_indep);
    dd = ((Phi_d(q,dq)) \ (Beta(q,dq)-(Phi_z(q,dq)*dz)));
    dq = [dz;dd];
end
%% Accel at t=0
Solve_Dynamics; % Solucion sistema lineal eq.
%% Results
state=0;
time=t_ini;
if strcmp(TIME,'ON')
    tic;
else
    save_state;
end
