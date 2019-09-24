transform --sz=0.2 --sx=1 --sy=1 < primes/cylinder_prime.gts > aux.gts
transform --rx=-90 --ty=-0.1< aux.gts > cy_aux.gts
gts2stl < cy_aux.gts > disc.stl

transform --sz=2.0 --sx=0.1 --sy=0.1 < primes/cylinder_prime.gts > aux.gts
transform --rx=-90 --ty=-1.0< aux.gts > axe_aux.gts
gts2stl < axe_aux.gts > axe.stl

transform --sz=30.0 --sx=0.2 --sy=0.2 < primes/cylinder_prime.gts > aux.gts
transform --ry=90 --tx=-5.0< aux.gts > rail_aux.gts
gts2stl < rail_aux.gts > rail.stl


