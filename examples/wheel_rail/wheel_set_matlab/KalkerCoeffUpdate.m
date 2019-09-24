% KalkerCoeffUpdate




[aR,bR] = Hertz_ellipse(Outputn(1) ,Outputn(7:10) ,param( 32 ),param( 33 ));
param( 35:36 ) = [aR,bR];
param( 39:42 ) = kalker_coeff(aR,bR,param( 33 ));

[aL,bL] = Hertz_ellipse(Outputn(11),Outputn(17:20),param( 32 ),param( 33 ));
param( 37:38 ) = [aL,bL];
param( 43:46 ) = kalker_coeff(aL,bL,param( 33 ));
