/*{*/
  double t2;
  double t5;
  /*{*/
    _dPhi_dq[0] = 0.0;
    _dPhi_dq[1] = 0.0;
    _dPhi_dq[2] = 0.0;
    _dPhi_dq[3] = 0.0;
    _dPhi_dq[4] = 0.0;
    _dPhi_dq[5] = -Rw;
    _dPhi_dq[6] = 0.0;
    _dPhi_dq[7] = 0.0;
    _dPhi_dq[8] = 0.0;
    _dPhi_dq[9] = -Rr;
    t2 = cos(a4);
    t5 = sin(a4);
    _dPhi_dq[10] = -(Rx+Ln)*t2-(Rr+Hi-Hb)*t5;
    _dPhi_dq[11] = 0.0;
   /*}*/
 /*}*/

