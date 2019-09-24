#Ellipse
transform --sz=3.0 < ./primes/sphere_prime.gts > aux1.gts
transform --sx=1.0 < aux1.gts > aux2.gts
transform --sy=2.0 < aux2.gts > aux3.gts
gts2stl < aux3.gts > ellipsoid.stl

