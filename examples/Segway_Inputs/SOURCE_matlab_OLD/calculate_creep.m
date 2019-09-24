function creep = calculate_creep(output)


R=output(:,7);
OM=output(:,5);
vs = output(:,2);
creep = (vs - R.*OM)./(abs(0.5*(vs + R.*OM )));

