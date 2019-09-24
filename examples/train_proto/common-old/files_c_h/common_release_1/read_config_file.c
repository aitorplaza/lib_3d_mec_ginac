#include "stdio.h"
#include "wchar.h"

#include "param_vect_def.h"
void read_config_file ( void )
{
FILE *file ;
file=fopen("config.ini","r");

char cadena1[100];
char cadena2[100];
double valor;

int i=0, aux=0;
if (file == NULL) {
	printf("The config file does not exist\n");
	}
else{
	for ( i = 0 ; i < n_param ; i++ ){
		aux=fscanf (file, "%[^=]= %lf %[^;]",cadena1, &param[i],cadena2);
	}	
	fclose(file);
}


}


