for t=t_ini: delta_t :t_end;
    Integration; % Integrar en el TIEMPO
    Projection; % Corregir POSICION y VELOCIDAD en instante t+delta_t
    Solve_Dynamics; % Solucion sistema lineal eq.
    if strcmp(TIME,'OFF')
        save_state;   
    end
end