/* Step forward delta_t */
   /* mexPrintf("q, dq,ddq  antes integrar dentro integrador \n");
    Vect_Print(n_gen_coord,q);
        Vect_Print(n_gen_coord,dq);
            Vect_Print(n_gen_coord,ddq);*/

    
for(i = 0; i < n_gen_coord; i++){ 
                /*mexPrintf("Antes---i=%d,q=%f,dq=%f,delta_t=%f,ddq=%f\n",i,q[i],dq[i],delta_t,ddq[i]);*/
                q[i] = q[i] + ( dq[i] + 0.5 * ddq[i] * delta_t ) * delta_t;	
               /* mexPrintf("Despues---i=%d,q=%f,dq=%f,delta_t=%f,ddq=%f\n",i,q[i],dq[i],delta_t,ddq[i]);*/}
    for(i = 0; i < n_gen_coord; i++){	dq[i] = dq[i] + ddq[i] * delta_t;	}
            
   /* mexPrintf("q desp integrar dentro integrador \n");
    Vect_Print(n_gen_coord,q);*/