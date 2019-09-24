// ================================================================
// RAIL data splies:
// ================================================================
double * breaks_rail ()
{
if ( _breaks_rail == NULL )
 {
    _breaks_rail = malloc ( 1 * 15 * sizeof(double) );
  {int i;
  for ( i = 0 ; i < 1 * 15 ; i++ ) {_breaks_rail[i]=0.0;}
  }
 }
{
_breaks_rail[0] =-0.0350;
_breaks_rail[1] =-0.0300;
_breaks_rail[2] =-0.0250;
_breaks_rail[3] =-0.0200;
_breaks_rail[4] =-0.0150;
_breaks_rail[5] =-0.0100;
_breaks_rail[6] =-0.0050;
_breaks_rail[7] =      0;
_breaks_rail[8] = 0.0050;
_breaks_rail[9] = 0.0100;
_breaks_rail[10]= 0.0150;
_breaks_rail[11]= 0.0200;
_breaks_rail[12]= 0.0250;
_breaks_rail[13]= 0.0300;
_breaks_rail[14]= 0.0350;
}
return _breaks_rail;
}




