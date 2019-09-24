'''
                       -------------------        
                      /                           |
                     /                            L
                    /                             |
-------------------/                              | 
|                  |   |                  |
t0                 t1  t2                 t3

h distance from the center of the two rails to one rail.

'''



import matplotlib.pyplot as plt
import numpy as np
import math
from sympy import *

t = Symbol('t')

t0 = 0
t1 = 10 
t2 = 60
t3 = 100

step = 0.1

L = 20 
h = 1

#############################################################################################
# Section 1
#############################################################################################
span01 = np.arange(t0, t1, step)

fx1 = t
fy1 = 0

x1 = [fx1.subs(t,k) for k in span01]
y1 = [fy1 for k in span01]


fx1L = t 
fy1L = 0 + h
x1L = [fx1L.subs(t,k) for k in span01]
y1L = [fy1L for k in span01]

fx1R = t 
fy1R = 0 - h
x1R = [fx1R.subs(t,k) for k in span01]
y1R = [fy1R for k in span01]


#############################################################################################
# Section 2
#############################################################################################
span12 = np.arange(t1, t2, step)

a2 = 6*L
b2 = -15*L
c2 = 10*L
d2 = 0
e2 = 0
f2 = 0

s = (t - t1) / (t2 - t1)


fx2 = t
fy2 = simplify( f2 + s * ( e2 + s * ( d2 + s * ( c2 + s * ( b2 + s * ( a2 ) ) ) ) ) )

x2 = [fx2.subs(t,k) for k in span12]
y2 = [fy2.subs(t,k) for k in span12]

dfx2 = simplify(fx2.diff(t))
dfy2 = simplify(fy2.diff(t))
f2mod = simplify(sqrt(dfx2**2 + dfy2**2))


fx2L = fx2 - h*dfy2/f2mod
fy2L = fy2 + h*dfx2/f2mod

x2L = [fx2L.subs(t,k) for k in span12]
y2L = [fy2L.subs(t,k) for k in span12]


fx2R = fx2 + h*dfy2/f2mod
fy2R = fy2 - h*dfx2/f2mod
x2R = [fx2R.subs(t,k) for k in span12]
y2R = [fy2R.subs(t,k) for k in span12]


#############################################################################################
# Section 3
#############################################################################################
span23 = np.arange(t2, t3, step)

fx3 = t 
fy3 = L

x3 = [fx3.subs(t,k) for k in span23]
y3 = [fy3 for k in span23]

fx3L = t 
fy3L = L + h
x3L = [fx3L.subs(t,k) for k in span23]
y3L = [fy3L for k in span23]

fx3R = t 
fy3R = L - h
x3R = [fx3R.subs(t,k) for k in span23]
y3R = [fy3R for k in span23]




#############################################################################################
# Plot
#############################################################################################

x = x1 + x2 + x3
y = y1 + y2 + y3

xL = x1L + x2L + x3L
yL = y1L + y2L + y3L

xR = x1R + x2R + x3R
yR = y1R + y2R + y3R

plt.plot(x, y, 'black',linewidth=2.0)
plt.plot(xL, yL, 'blue',linewidth=2.0)
plt.plot(xR, yR, 'red',linewidth=2.0)


plt.xlabel('x[m]')
plt.ylabel('y[m]')
plt.title('Railway', fontsize=10)
#plt.axis([0, 100, -10, 30])
plt.xlim(t0, t3)
plt.ylim(-(5+h), L+h+5)
plt.gca().set_aspect('equal', adjustable='box')
plt.grid()
plt.show()

