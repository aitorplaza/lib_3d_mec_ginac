for t=t_ini: delta_t :t_end;
    Solve_Dynamics; % Solucion sistema lineal eq.
    Integration; % Integrar en el TIEMPO
    Projection; % Corregir POSICION y VELOCIDAD en instante t+delta_t
    if strcmp(TIME,'OFF')
        save_state;   
    end
end