void get_spline_coefs (double * param, int pos_a, double * coefs, double * breaks, double u, int length_breaks, int rows_coefs){

  int found = 0; // true 1 false 0
  int index = 0;
  int i;

  if (found == 0  && u < breaks[0])
    {
      index = 0;
      found = 1;
    }
  else if (found == 0  && u > breaks[length_breaks-1])
    {
      index = length_breaks;
      found = 1;
    }

  for (i=0; i<=length_breaks-1; i++){
    if (found == 0  && u > breaks[i] && u <= breaks[i+1] )
      {
        index = i;
        found = 1;
        break;
      }
  }
// printf ("index = %i\n",index);
// printf ("u = %f\n",u);
// printf (" breaks[i] = %f\n", breaks[index]);
// printf (" breaks[i+1] = %f\n", breaks[index+1]);
// printf ("\n");
  param[pos_a + 0] = coefs[index + 0 * rows_coefs];
  param[pos_a + 1] = coefs[index + 1 * rows_coefs];
  param[pos_a + 2] = coefs[index + 2 * rows_coefs];
  param[pos_a + 3] = coefs[index + 3 * rows_coefs];
  param[pos_a + 4] = breaks[index];
};
