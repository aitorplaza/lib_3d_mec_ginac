%% Coord q
if strcmp(COORD,'COORD_DEP')
    if strcmp(SIZE,'DDL')
        aux = (MXdPhi_dqZero(q,dq)) \ Qgamma(q,dq);
        ddq = aux(1:n_gen_vel);
        unknowns = aux((n_gen_vel+1):(n_gen_vel + n_unknowns));
    elseif strcmp(SIZE,'DDQ')
        [LM,DM] = ldl(M(q,dq));
        Y1 = LM \ Q(q,dq); 
        for i=1:n_gen_vel
            Y1(i,1)=Y1(i,1)/DM(i,i);
        end        
        X1 = LM' \ Y1;
%{        
        Y2 = LM \ Phi_q(q,dq)';
        for i=1:n_gen_vel
        for j=1:n_unknowns
            Y2(i,j)=Y2(i,j)/DM(i,i);
        end
        end
        X2 = LM' \ Y2;
%}        
        
        X2 = M(q,dq) \ Phi_q(q,dq)';
        
        b=Phi_q(q,dq)*X1-Gamma(q,dq);
        A=Phi_q(q,dq)*X2;
        
        [LA,DA] = ldl(A);
        Y = LA \ b;
        for i=1:n_unknowns
            Y(i,1)=Y(i,1)/DA(i,i);
        end  
        unknowns = LA' \ Y;
        
        ddq=X1-X2*unknowns;
        
    else
        disp('Solving Dynamics with DEP COORD.');
        disp('Please select ddqunknowns FULL or SPLIT');
        finishdlg;
    end
end
%% Coord z
if strcmp(COORD,'COORD_IND')
    inv_Phi_d = inv(Phi_d(q,dq));
    AA  = -(inv_Phi_d * Phi_z(q,dq));
	bb  = (inv_Phi_d * Gamma(q,dq));
	MZ = Mzz(q,dq)+ AA' * Mzd(q,dq)' + Mzd(q,dq) * AA + AA' * Mdd(q,dq)' * AA;
	QZ = (Qz(q,dq) + AA' * Qd(q,dq)) - (Mzd(q,dq) + AA' * Mdd(q,dq)') * bb;
    
	ddz = (MZ) \ QZ;
	ddd = AA*ddz + bb;
	ddq = [ddz;ddd];
end