/*{*/
  double t1;
  double t100;
  double t101;
  double t102;
  double t103;
  double t104;
  double t107;
  double t108;
  double t109;
  double t110;
  double t112;
  double t114;
  double t115;
  double t116;
  double t117;
  double t12;
  double t120;
  double t122;
  double t123;
  double t124;
  double t128;
  double t130;
  double t132;
  double t133;
  double t134;
  double t136;
  double t137;
  double t138;
  double t139;
  double t14;
  double t140;
  double t141;
  double t142;
  double t147;
  double t15;
  double t151;
  double t152;
  double t154;
  double t156;
  double t158;
  double t16;
  double t161;
  double t162;
  double t164;
  double t165;
  double t171;
  double t179;
  double t18;
  double t184;
  double t186;
  double t19;
  double t190;
  double t193;
  double t197;
  double t2;
  double t200;
  double t201;
  double t204;
  double t205;
  double t207;
  double t208;
  double t209;
  double t21;
  double t211;
  double t218;
  double t22;
  double t222;
  double t227;
  double t229;
  double t232;
  double t237;
  double t241;
  double t243;
  double t249;
  double t25;
  double t250;
  double t251;
  double t253;
  double t255;
  double t256;
  double t257;
  double t26;
  double t267;
  double t269;
  double t271;
  double t272;
  double t274;
  double t275;
  double t276;
  double t277;
  double t28;
  double t280;
  double t283;
  double t284;
  double t285;
  double t287;
  double t289;
  double t291;
  double t293;
  double t299;
  double t3;
  double t307;
  double t315;
  double t319;
  double t32;
  double t320;
  double t331;
  double t335;
  double t336;
  double t338;
  double t34;
  double t340;
  double t344;
  double t346;
  double t347;
  double t348;
  double t35;
  double t350;
  double t351;
  double t353;
  double t356;
  double t357;
  double t358;
  double t36;
  double t360;
  double t364;
  double t37;
  double t378;
  double t38;
  double t388;
  double t39;
  double t397;
  double t399;
  double t40;
  double t402;
  double t407;
  double t409;
  double t414;
  double t42;
  double t43;
  double t434;
  double t443;
  double t453;
  double t455;
  double t46;
  double t462;
  double t465;
  double t468;
  double t47;
  double t482;
  double t489;
  double t49;
  double t493;
  double t497;
  double t5;
  double t505;
  double t512;
  double t52;
  double t522;
  double t525;
  double t528;
  double t529;
  double t533;
  double t537;
  double t54;
  double t542;
  double t545;
  double t547;
  double t552;
  double t56;
  double t57;
  double t573;
  double t574;
  double t577;
  double t578;
  double t582;
  double t59;
  double t590;
  double t594;
  double t6;
  double t603;
  double t605;
  double t610;
  double t613;
  double t62;
  double t625;
  double t631;
  double t634;
  double t656;
  double t659;
  double t66;
  double t661;
  double t663;
  double t667;
  double t671;
  double t675;
  double t689;
  double t69;
  double t696;
  double t70;
  double t711;
  double t72;
  double t721;
  double t722;
  double t723;
  double t727;
  double t742;
  double t746;
  double t761;
  double t764;
  double t77;
  double t772;
  double t775;
  double t777;
  double t787;
  double t789;
  double t793;
  double t8;
  double t80;
  double t802;
  double t806;
  double t82;
  double t83;
  double t84;
  double t85;
  double t86;
  double t87;
  double t88;
  double t89;
  double t90;
  double t93;
  double t94;
  double t96;
  /*{*/
    t1 = dphi3+dphi1;
    t2 = cos(phi3);
    t3 = sin(phi1);
    t5 = cos(phi1);
    t6 = sin(phi3);
    t8 = t2*t3+t5*t6;
    t12 = t5*t2-t6*t3;
    t14 = t8*IxzRuedaDcha-t12*IxyRuedaDcha;
    t15 = t1*t14;
    t16 = t12*IyzRuedaDcha;
    t18 = t16-t8*IzzRuedaDcha;
    t19 = t12*t18;
    t21 = t8*IyzRuedaDcha;
    t22 = t12*IzzRuedaDcha+t21;
    t25 = t12*IyyRuedaDcha-t21;
    t26 = t25*t8;
    t28 = t16+IyyRuedaDcha*t8;
    t32 = t15-(t19-t22*t8+t26+t12*t28)*drho1;
    t34 = sin(rho1);
    t35 = d+zcdg;
    t36 = t35*t3;
    t37 = t5*ycdg;
    t38 = t36-t37;
    t39 = t34*t38;
    t40 = t34*t5;
    t42 = cos(rho1);
    t43 = dphi1*t42;
    t46 = dycdg*(t40*drho1+t43*t3);
    t47 = pow(mRider,-0.1E1);
    t49 = ycdg+myRider*t47;
    t52 = d+mzRider*t47+zcdg;
    t54 = t5*t49-t52*t3;
    t56 = dycdg*t3;
    t57 = dphi1*t54+t56;
    t59 = t34*drho1;
    t62 = t49*t3+t5*t52;
    t66 = dphi1*t62;
    t69 = t5*dycdg;
    t70 = t66-mxRider*drho1*t47-t69;
    t72 = t42*drho1;
    t77 = (t46+(t57*t42-t59*t62)*dphi1-drho1*(t34*t70-t72*t54))*mRider;
    t80 = sin(theta1);
    t82 = cos(theta1);
    t83 = t5*t82;
    t84 = t83*IxzManillar;
    t85 = t3*IxyManillar;
    t86 = t5*IxxManillar*t80-t84-t85;
    t87 = t5*t86;
    t88 = t87*t80;
    t89 = t82*IxzManillar;
    t90 = t89*t3;
    t93 = t5*IxyManillar;
    t94 = t90-IxxManillar*t3*t80-t93;
    t96 = t94*t3*t80;
    t100 = t93*t80-IyyManillar*t3-t83*IyzManillar;
    t101 = t100*t3;
    t102 = t82*t3;
    t103 = t5*IyzManillar;
    t104 = IzzManillar*t82;
    t107 = IxzManillar*t3*t80;
    t108 = t103-t104*t3+t107;
    t109 = t102*t108;
    t110 = t5*IzzManillar;
    t112 = IyzManillar*t3;
    t114 = t5*IxzManillar*t80;
    t115 = t110*t82+t112-t114;
    t116 = t5*t115;
    t117 = t116*t82;
    t120 = t82*IyzManillar;
    t122 = t85*t80+IyyManillar*t5-t120*t3;
    t123 = t5*t122;
    t124 = t88+t96-t101+t109+t117-t123;
    t128 = t94*t82;
    t130 = dphi1*(t80*t108-t128);
    t132 = drho1+dtheta1*t3;
    t133 = t94*t5;
    t134 = t133*t80;
    t136 = t86*t3*t80;
    t137 = t83*t108;
    t138 = t100*t5;
    t139 = t3*t122;
    t140 = t115*t82;
    t141 = t140*t3;
    t142 = t134-t136+t137-t138+t139-t141;
    t147 = dtheta1*t5;
    t151 = (dtheta1*t124*t5-t130-t132*t142-dtheta1*(t136+t138+t141)*t3-t147*(
t88-t101+t117))*dphi1;
    t152 = IyzRider*t3;
    t154 = t152+t5*IzzRider;
    t156 = t5*IyzRider;
    t158 = t156+t3*IyyRider;
    t161 = t156-IzzRider*t3;
    t162 = t5*t161;
    t164 = t152-t5*IyyRider;
    t165 = t3*t164;
    t171 = (t5*IxyRider-IxzRider*t3)*dphi1;
    t179 = myRider*t34*t5-mxRider*t42-t34*mzRider*t3;
    t184 = ycdg*t3+t5*t35;
    t186 = t184*dphi1-t69;
    t190 = t184*t34;
    t193 = t56-t38*dphi1;
    t197 = t46-(t38*t42*drho1+t34*t186)*drho1-(t190*drho1-t193*t42)*dphi1;
    t200 = t5*IyzPlataforma;
    t201 = IyyPlataforma*t3+t200;
    t204 = t200-IzzPlataforma*t3;
    t205 = t5*t204;
    t207 = t3*IyzPlataforma;
    t208 = t5*IyyPlataforma-t207;
    t209 = t208*t3;
    t211 = t5*IzzPlataforma+t207;
    t218 = dphi1*(IxyPlataforma*t5-t3*IxzPlataforma);
    t222 = t184*t42;
    t227 = t5*t42;
    t229 = t34*dphi1;
    t232 = (t227*drho1-t229*t3)*dycdg;
    t237 = dphi1*(t222*drho1+t34*t193)-t232+(t42*t186-t39*drho1)*drho1;
    t241 = myRider*t5;
    t243 = mzRider*t42*t3-t34*mxRider-t241*t42;
    t249 = (t42*t80+t34*t82*t3)*man;
    t250 = cm*t3;
    t251 = d-rm;
    t253 = t250+t5*t251;
    t255 = t5*cm;
    t256 = t3*t251;
    t257 = t255-t256;
    t267 = dphi1*(t59*t253-t257*dphi1*t42)-(t257*t42*drho1-t229*t253)*drho1;
    t269 = t249*mManillar*t267;
    t271 = t257*t34;
    t272 = man*drho1;
    t274 = dtheta1*man;
    t275 = t3*t80;
    t276 = t274*t275;
    t277 = t82*man;
    t280 = t277+0.2E1*d-0.2E1*rm;
    t283 = t5*t280+0.2E1*t250;
    t284 = dphi1*t283;
    t285 = t272*t80+t276-t284;
    t287 = dtheta1*t82;
    t289 = 0.2E1*t255;
    t291 = t289-t280*t3;
    t293 = t287*man-drho1*t291;
    t299 = t274*t80+t272*t275;
    t307 = t287*man*t3+t277*drho1+t5*man*dphi1*t80;
    t315 = dphi1*t291-t147*man*t80;
    t319 = (t34*t285-t293*t42)*drho1+dtheta1*(t34*t299-t307*t42)-dphi1*(t59*
t283-t315*t42);
    t320 = t319*mManillar;
    t331 = t232-(t34*t57+t72*t62)*dphi1-(t70*t42+t59*t54)*drho1;
    t335 = dphi2+dphi1;
    t336 = sin(phi2);
    t338 = cos(phi2);
    t340 = t336*t3-t5*t338;
    t344 = t5*t336+t3*t338;
    t346 = t340*IxyRuedaIzq+IxzRuedaIzq*t344;
    t347 = t335*t346;
    t348 = IyzRuedaIzq*t344;
    t350 = t348+IyyRuedaIzq*t340;
    t351 = t350*t344;
    t353 = t348-t340*IzzRuedaIzq;
    t356 = IyzRuedaIzq*t340;
    t357 = IzzRuedaIzq*t344+t356;
    t358 = t340*t357;
    t360 = t356-IyyRuedaIzq*t344;
    t364 = t347+(t351+t353*t344-t358-t340*t360)*drho1;
    t378 = dtheta1*(t42*t299+t307*t34)-dphi1*(t72*t283+t34*t315)+drho1*(t285*
t42+t34*t293);
    t388 = (t34*t80-t82*t42*t3)*man;
    t397 = dphi1*(t72*t253+t271*dphi1)+drho1*(t271*drho1+t43*t253);
    t399 = t388*t397*mManillar;
    t402 = t110*t80+t84;
    t407 = t103*t80+t83*IxyManillar;
    t409 = t86*t82;
    t414 = t83*IxxManillar+t114;
    t434 = dtheta1*(t147*(t402*t82*t3-t5*t407-t409*t3+t115*t3*t80-t414*t3*t80)+
t132*(t87*t82-t402*t5*t82-t407*t3-t116*t80+t5*t414*t80)+dphi1*(t86*t80-t402*t80
-t82*t414+t140));
    _Q[0] = -dphi1*t32-t39*t77-t151-((t154*t3-t158*t5-t162+t165)*drho1-t171)*
dphi1+t179*t197+dphi1*((t5*t201+t205+t209-t3*t211)*drho1+t218)-dphi3*t32+t237*
t243+t269/2.0+t271*t320/2.0-t331*t38*t42*mRider-dphi1*t364+t257*t378*t42*
mManillar/2.0-dphi2*t364-t399/2.0+t434;
    t443 = dphi3*t14*drho1+t14*dphi1*drho1-(t15-(t19+t26)*drho1)*drho1;
    t453 = t12*IxzRuedaDcha+t8*IxyRuedaDcha;
    t455 = (t12*t22+t8*t28-t12*t25+t8*t18)*drho1+t1*t453;
    t462 = dphi1*t455-(t1*IxxRuedaDcha+drho1*t453)*drho1+dphi3*t455;
    t465 = (t42*t443-t34*t462)*t42;
    t468 = IxyPlataforma*t3+t5*IxzPlataforma;
    t482 = (t468*dphi1+drho1*(t201*t3+t3*t204-t5*t208+t5*t211))*dphi1-drho1*(
t468*drho1+dphi1*IxxPlataforma);
    t489 = t218*drho1-((t205+t209)*drho1+t218)*drho1;
    t493 = t331*mRider;
    t497 = IxyRuedaIzq*t344-t340*IxzRuedaIzq;
    t505 = t335*t497-(t340*t353+t340*t350+t357*t344+t360*t344)*drho1;
    t512 = dphi2*t505-(t497*drho1+IxxRuedaIzq*t335)*drho1+dphi1*t505;
    t522 = dphi2*t346*drho1+t346*dphi1*drho1-(t347+(t351-t358)*drho1)*drho1;
    t525 = t42*(t34*t512-t522*t42);
    t528 = t69*dphi1;
    t529 = dphi1*(t66-t69)-t528;
    t533 = mManillar*t253;
    t537 = t5*t80;
    t542 = t90+IzzManillar*t3*t80;
    t545 = t82*IxxManillar;
    t547 = t545*t3+t107;
    t552 = t112*t80+t102*IxyManillar;
    t573 = IxzManillar*t80;
    t574 = t545+t573;
    t577 = IzzManillar*t80+t89;
    t578 = t5*t577;
    t582 = IyzManillar*t80+t82*IxyManillar;
    t590 = t577*t82;
    t594 = t590*t3-t275*t574-t5*t582;
    t603 = dtheta1*(t96+t109-t123);
    t605 = t134+t137+t139;
    t610 = dtheta1*(t132*(t537*t108-t133*t82-t542*t5*t82+t5*t547*t80-t552*t3)-
t147*(t5*t552+t3*t547*t80-t128*t3-t542*t82*t3+t275*t108)-dphi1*(t542*t80+t82*
t108+t82*t547+t94*t80))+(t132*(t537*t574-t578*t82-t3*t582)-dphi1*(t82*t574+t577
*t80)+t147*t594)*drho1+(t124*t132-(t409-t115*t80)*dphi1-t603*t3-t147*t605+t147*
t142)*dphi1;
    t613 = man*mManillar;
    t625 = t104-t573;
    t631 = IxyManillar*t80-t120;
    t634 = t89-IxxManillar*t80;
    t656 = dphi1*(dtheta1*t594*t3-t132*t594)-(t605*t132-t603*t5+t130)*drho1+
dtheta1*((t5*t625*t82-t83*t574-t578*t80-t3*t631-t5*t634*t80)*t132-t147*(t625*
t82*t3-t577*t3*t80+t5*t631-t102*t574-t634*t3*t80)-dphi1*(t80*t574-t625*t80-t590
-t634*t82));
    t659 = pow(dphi1,0.2E1);
    t661 = t659*mManillar*t253;
    t663 = 0.2E1*t34*t610-t83*t613*t267+0.2E1*t656*t42-t388*t661;
    t667 = t528-dphi1*t186;
    t671 = t5*mzRider+myRider*t3;
    t675 = t3*IxyRider+IxzRider*t5;
    t689 = dphi1*(dphi1*t675+(t5*t154+t158*t3+t5*t164+t3*t161)*drho1)-(t675*
drho1+dphi1*IxxRider)*drho1;
    t696 = (t171+(t162-t165)*drho1)*drho1-t171*drho1;
    t711 = dphi1*(t276-t284)-dtheta1*(t147*t277-man*dphi1*t275);
    t721 = mPlataforma*g;
    t722 = pow(mPlataforma,-0.1E1);
    t723 = mzPlataforma*t722;
    t727 = t723*t3-t722*t5*myPlataforma;
    t742 = t34*(t34*t443+t462*t42);
    t746 = t34*(t42*t512+t34*t522);
    t761 = 0.2E1*t610*t42-t249*t661-t83*man*t397*mManillar-0.2E1*t34*t656;
    t764 = t257*t711*mManillar/2.0+g*(t289-t277*t3-0.2E1*t256)*mManillar/2.0-
t721*t727-MomRuedaIzq-g*(t36-t37+mzRider*t3*t47-t241*t47)*mRider-t34*(t42*t482-
t34*t489)-t742-t746-MomRuedaDcha+t34*(t237*t671-t42*t689+t179*t667-t34*t696)-
t34*t761/2.0;
    _Q[1] = -t465+(t34*t482+t42*t489)*t42-t190*t493+t525+t38*t529*mRider+t319*
t42*t533/2.0+t222*t77+t42*t663/2.0-(t243*t667-t197*t671-t34*t689+t696*t42)*t42-
t34*t378*t533/2.0+t764;
    _Q[2] = t525-MomRuedaIzq-t746+dphi2*Cvis1;
    _Q[3] = -t465+dphi3*Cvis2-t742-MomRuedaDcha;
    t772 = pow(t3,0.2E1);
    t775 = dtheta1*Cvis3+theta1*KMan;
    t777 = pow(t5,0.2E1);
    _Q[4] = -(0.2E1*t151-t269+t399-0.2E1*t434)*t3/2.0+t772*t775+t777*t775-t5*g*
t613*t80/2.0-t40*t663/2.0-t227*t761/2.0;
    t787 = pow(drho1,0.2E1);
    t789 = le*mRuedaDcha;
    t793 = t787*le;
    t802 = t723*t5+t722*myPlataforma*t3;
    t806 = t802*dphi1-t722*mxPlataforma*drho1;
    _Q[5] = t42*t787*t789/2.0-t493-mRuedaIzq*t42*t793/2.0-t378*mManillar/2.0-(
drho1*(t59*t727-t806*t42)+(t229*t727-t802*t42*drho1)*dphi1)*mPlataforma;
    _Q[6] = -t77+mPlataforma*((t806*t34+t72*t727)*drho1+(t43*t727+t802*t34*
drho1)*dphi1)-t320/2.0+t34*t787*t789/2.0-t34*mRuedaIzq*t793/2.0;
    _Q[7] = -t529*mRider+g*mRuedaDcha+g*mRider+t711*mManillar/2.0-t802*
mPlataforma*t659+t721+mRuedaIzq*g+g*mManillar;
    _Q[8] = -t227*t77+g*t3*mRider+t40*t493-t529*t3*mRider;
   /*}*/
 /*}*/

