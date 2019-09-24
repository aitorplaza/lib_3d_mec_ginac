#include "defines.h"
#include "Includes_variables_parameters.h"
#include "Includes_functions.h"
#include "Includes_Init_functions.h"
#include "lin_alg.h"


double module(int size ,double * Vector)
{
  int j;
  double modu = 0.0;
  for (j=0; j<size; j++){
    modu += fabs(Vector[j]);
  }
  return modu;
}
