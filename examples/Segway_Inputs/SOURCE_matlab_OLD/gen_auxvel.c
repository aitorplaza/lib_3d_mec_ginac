#include <stdlib.h>
#include "gen_auxvel.h"


double * dqaux=NULL; 
void Init_dqaux_values ( void )
{
}

void Init_dqaux ( )
{
 dqaux = malloc ( n_gen_auxvel * sizeof(double) );
 {int i;
  for ( i = 0 ; i < n_gen_auxvel ; i++ ) {dqaux[i]=0.0;}
 }
}

void Done_dqaux( ) 
{
if ( dqaux != NULL) 
free ( dqaux ); 
dqaux = NULL; 
}

void Reallocate_dqaux( double * user_dqaux ) 
{
dqaux = user_dqaux; 
}

