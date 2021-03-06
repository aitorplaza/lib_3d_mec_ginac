#Note id a solid is rendered deep black use transform -i to put inside out.
transform --tz=0 < prime/cylinder_prime.gts > aux.gts
transform --sz=0.5 < aux.gts > aux1.gts
transform --sx=0.05 < aux1.gts > aux2.gts
transform --sy=0.05 < aux2.gts > aux3.gts
transform --rx=-90 < aux3.gts > aux4.gts
gts2stl < aux4.gts > arm1.stl

osgconv arm1.stl Solarm1.3ds


transform --tz=0 < prime/cylinder_prime.gts > aux.gts
transform --sz=1.5 < aux.gts > aux1.gts
transform --sx=0.05 < aux1.gts > aux2.gts
transform --sy=0.05 < aux2.gts > aux3.gts
transform --rx=-90 < aux3.gts > aux4.gts
gts2stl < aux4.gts > arm2.stl

osgconv arm2.stl Solarm2.3ds

transform --tz=-0.25 < prime/cylinder_prime.gts > aux.gts
transform --sz=0.05 < aux.gts > aux1.gts
transform --sx=1.0 < aux1.gts > aux2.gts
transform --sy=1.4 < aux2.gts > aux3.gts
transform --ry=-90 < aux3.gts > aux4.gts
gts2stl < aux4.gts > disc.stl

osgconv disc.stl Soldisc.3ds

transform --tz=0 < prime/axes_prime.gts > aux.gts
transform --sz=0.4 < aux.gts > aux1.gts
transform --sx=0.4 < aux1.gts > aux2.gts
transform --sy=0.4 < aux2.gts > aux3.gts
transform --ry=0 < aux3.gts > aux4.gts
gts2stl < aux4.gts > axes.stl

osgconv axes.stl axes.osg

transform --tz=-1 < prime/cube_prime.gts > aux.gts
transform --sz=0.1 < aux.gts > aux1.gts
transform --sx=0.1 < aux1.gts > aux2.gts
transform --sy=6 < aux2.gts > aux3.gts
transform --ry=0 < aux3.gts > aux4.gts
gts2stl < aux4.gts > plane.stl

osgconv plane.stl Solplane.3ds

