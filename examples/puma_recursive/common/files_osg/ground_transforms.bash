#Create solids files for DSM example
#Note id a solid is rendered deep black use transform -i to put inside out.
#Plane
transform --tz=-1 < ./Solids/primes/cube_prime.gts > aux.gts
transform --sz=0.05 < aux.gts > aux1.gts
transform --sx=1.0 < aux1.gts > aux2.gts
transform --sy=1.0 < aux2.gts > aux3.gts
transform --ry=0 < aux3.gts > aux4.gts
gts2stl < aux4.gts > ground.stl

rm *.gts


