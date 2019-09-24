from sympy import *
from sympy.parsing.sympy_parser import parse_expr
#init_printing(use_unicode=True)

def simple(eq):
    eq = eq.replace("^", "**")
    eq1 = parse_expr(eq)
    eq2 = str(simplify(eq1))
    return eq2.replace("**", "^")
b0=" sin(b1)*cos(a1)*sin(b)-cos(b)*sin(b1)*sin(a1)*sin(a)+cos(b)*cos(a)*cos(b1)"
b1=" cos(b)*cos(a)*cos(b2)-sin(b2)*cos(b)*sin(a2)*sin(a)+cos(a2)*sin(b2)*sin(b)"
b2=" (cos(a3)*sin(b3)*cos(2*alfa)-sin(b3)*sin(2*alfa)*sin(a3))*sin(b)-cos(b)*(sin(b3)*sin(a3)*cos(2*alfa)+cos(a3)*sin(b3)*sin(2*alfa))*sin(a)+cos(b)*cos(a)*cos(b3)"
b3=" cos(b)*cos(a)*cos(b4)-(sin(b4)*cos(a4)*sin(2*alfa)+sin(b4)*sin(a4)*cos(2*alfa))*cos(b)*sin(a)+(sin(b4)*cos(a4)*cos(2*alfa)-sin(b4)*sin(2*alfa)*sin(a4))*sin(b)"
b4=" -(sin(b5)*sin(a5)*sin((4.0)*alfa)-cos((4.0)*alfa)*sin(b5)*cos(a5))*sin(b)-cos(b)*(cos((4.0)*alfa)*sin(b5)*sin(a5)+sin(b5)*sin((4.0)*alfa)*cos(a5))*sin(a)+cos(b)*cos(a)*cos(b5)"
b5=" -cos(b)*(sin((4.0)*alfa)*cos(a6)*sin(b6)+cos((4.0)*alfa)*sin(a6)*sin(b6))*sin(a)+(cos((4.0)*alfa)*cos(a6)*sin(b6)-sin(a6)*sin((4.0)*alfa)*sin(b6))*sin(b)+cos(b)*cos(b6)*cos(a)"

b0=simple(b0)
b1=simple(b1)
b2=simple(b2)
b3=simple(b3)
b4=simple(b4)
b5=simple(b5)


f = open("NolinPhi2_python_exp.m","w")
f.write("NolinPhi2_matrix=[")
f.write(b0)
f.write(";")
f.write(b1)
f.write(";")
f.write(b2)
f.write(";")
f.write(b3)
f.write(";")
f.write(b4)
f.write(";")
f.write(b5)
f.write("];")

f.close() 
