#include "stdio.h"
#include "wchar.h"

#include "param.h"
#include "inputs.h"
#include "gen_coord.h"
#include "gen_vel.h"

#ifdef MATLAB_MEX_FILE
    #define printf mexPrintf
#endif 
        
void read_config_file ( void ) {

    FILE *file ;
    file=fopen("config.ini","r");

    char cadena1[100];
    char cadena2[100];
    double valor;
    int i, aux;
    
    //~ int i=0, aux=0;
    //~ if (file == NULL) {
    	//~ printf("The config file does not exist\n");
    	//~ }
    //~ else{
    	//~ for ( i = 0 ; i < n_param ; i++ ){
    		//~ aux=fscanf (file, "%[^=]= %lf %[^;]",cadena1, &param[i],cadena2);
    	//~ }	
    //~ fclose(file);
        
    i=0; aux=0;
    file=fopen("param.ini","r");
    if (file == NULL) {
    	printf("param.ini file does not exist\n");
    	}
    else{
    	for ( i = 0 ; i < n_param ; i++ ){
    		aux=fscanf (file, "%[^=]= %lf %[^;]",cadena1, &param[i],cadena2);
            
    	}	
	    fclose(file);
    }
    
     i=0; aux=0;
    file=fopen("inputs.ini","r");
    if (file == NULL) {
    	printf("inputs.ini file does not exist\n");
    	}
    else{
    	for ( i = 0 ; i < n_inputs; i++ ){
    		aux=fscanf (file, "%[^=]= %lf %[^;]",cadena1, &inputs[i],cadena2);
            
    	}	
	    fclose(file);
    }
    
    i=0; aux=0;
    file=fopen("gen_coord.ini","r");
    if (file == NULL) {
    	printf("gen_coord.ini file does not exist\n");
    	}
    else{
    	for ( i = 0 ; i < n_gen_coord ; i++ ){
    		aux=fscanf (file, "%[^=]= %lf %[^;]",cadena1, &q[i],cadena2);
            
    	}	
	    fclose(file);
    }
    
    i=0; aux=0;
    file=fopen("gen_vel.ini","r");
    if (file == NULL) {
    	printf("The parameters.ini file does not exist\n");
    	}
    else{
    	for ( i = 0 ; i < n_inputs ; i++ ){
    		aux=fscanf (file, "%[^=]= %lf %[^;]",cadena1, &dq[i],cadena2);
            
    	}	
	    fclose(file);
    }
        
}



