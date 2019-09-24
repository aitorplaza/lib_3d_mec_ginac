/*{*/
  double t1;
  double t2;
  double t4;
  double t5;
  /*{*/
    _dPhiInit_dq[0] = 0.0;
    _dPhiInit_dq[1] = 0.0;
    _dPhiInit_dq[2] = 0.0;
    t1 = sin(rho1);
    t2 = pow(t1,0.2E1);
    t4 = cos(rho1);
    t5 = pow(t4,0.2E1);
    _dPhiInit_dq[3] = t2*le/2.0+t5*le/2.0;
    _dPhiInit_dq[4] = -_dPhiInit_dq[3];
    _dPhiInit_dq[5] = 0.0;
    _dPhiInit_dq[6] = 0.0;
    _dPhiInit_dq[7] = 0.0;
    _dPhiInit_dq[8] = R*t2+R*t5;
    _dPhiInit_dq[9] = _dPhiInit_dq[8];
    _dPhiInit_dq[10] = 0.0;
    _dPhiInit_dq[11] = 0.0;
    _dPhiInit_dq[12] = 0.0;
    _dPhiInit_dq[13] = _dPhiInit_dq[9];
    _dPhiInit_dq[14] = 0.0;
    _dPhiInit_dq[15] = 0.0;
    _dPhiInit_dq[16] = 0.0;
    _dPhiInit_dq[17] = 0.0;
    _dPhiInit_dq[18] = 0.0;
    _dPhiInit_dq[19] = _dPhiInit_dq[13];
    _dPhiInit_dq[20] = 0.0;
    _dPhiInit_dq[21] = 0.0;
    _dPhiInit_dq[22] = 0.0;
    _dPhiInit_dq[23] = 0.0;
    _dPhiInit_dq[24] = 0.0;
    _dPhiInit_dq[25] = 0.0;
    _dPhiInit_dq[26] = 0.0;
    _dPhiInit_dq[27] = t4;
    _dPhiInit_dq[28] = -t1;
    _dPhiInit_dq[29] = _dPhiInit_dq[28];
    _dPhiInit_dq[30] = 0.0;
    _dPhiInit_dq[31] = 0.0;
    _dPhiInit_dq[32] = t1;
    _dPhiInit_dq[33] = _dPhiInit_dq[27];
    _dPhiInit_dq[34] = _dPhiInit_dq[33];
    _dPhiInit_dq[35] = 0.1E1;
    _dPhiInit_dq[36] = 0.0;
    _dPhiInit_dq[37] = 0.0;
    _dPhiInit_dq[38] = 0.0;
    _dPhiInit_dq[39] = 0.0;
    _dPhiInit_dq[40] = 0.0;
    _dPhiInit_dq[41] = 0.1E1;
    _dPhiInit_dq[42] = 0.0;
    _dPhiInit_dq[43] = 0.0;
    _dPhiInit_dq[44] = 0.0;
   /*}*/
 /*}*/

