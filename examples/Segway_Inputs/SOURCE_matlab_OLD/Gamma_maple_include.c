/*{*/
  double t1;
  double t10;
  double t11;
  double t13;
  double t16;
  double t18;
  double t19;
  double t21;
  double t22;
  double t3;
  double t32;
  double t34;
  double t39;
  double t4;
  double t5;
  double t7;
  double t8;
  /*{*/
    _Gamma[0] = 0.0;
    _Gamma[1] = 0.0;
    t1 = sin(rho1);
    t3 = t1*drho1*le;
    t4 = R*t1;
    t5 = dphi2+dphi1;
    t7 = 0.2E1*t4*t5;
    t8 = t3+t7;
    t10 = 0.2E1*dxp;
    t11 = t3+t7-t10;
    t13 = cos(rho1);
    t16 = 0.2E1*R*t5*t13;
    t18 = t13*drho1*le;
    t19 = t16+t18;
    t21 = 0.2E1*dyp;
    t22 = t16+t18+t21;
    _Gamma[2] = (t1*t8-t1*t11+t13*t19-t22*t13)*drho1/2.0;
    _Gamma[3] = (t13*t8-t11*t13-t1*t19+t1*t22)*drho1/2.0;
    t32 = dphi3+dphi1;
    t34 = 0.2E1*t4*t32;
    t39 = 0.2E1*R*t32*t13;
    _Gamma[4] = -((t3-t34)*t13+t1*(t18-t39-t21)-t13*(t3-t34+t10)-t1*(t18-t39))*
drho1/2.0;
   /*}*/
 /*}*/

