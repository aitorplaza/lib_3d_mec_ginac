with(codegen);
ssystem("rm -f ./_maple_include.c");
p:=proc()
local _Kinematics_Wheels;

_Kinematics_Wheels:= array(0 .. 35);
_Kinematics_Wheels[0]:=x+cos(b)*L*cos(c);
_Kinematics_Wheels[1]:=y+sin(c)*cos(b)*L;
_Kinematics_Wheels[2]:=-L*sin(b)+z;
_Kinematics_Wheels[3]:=cos(c)*(cos(r)*sin(a)*sin(b)-cos(b)*sin(r))-cos(r)*sin(c)*cos(a);
_Kinematics_Wheels[4]:=sin(c)*(cos(r)*sin(a)*sin(b)-cos(b)*sin(r))+cos(r)*cos(a)*cos(c);
_Kinematics_Wheels[5]:=sin(b)*sin(r)+cos(r)*sin(a)*cos(b);
_Kinematics_Wheels[6]:=dx-dc*sin(c)*cos(b)*L-L*db*sin(b)*cos(c);
_Kinematics_Wheels[7]:=dc*cos(b)*L*cos(c)-sin(c)*L*db*sin(b)+dy;
_Kinematics_Wheels[8]:=dz-cos(b)*L*db;
_Kinematics_Wheels[9]:=sin(c)*(sin(a)*dr-db-cos(r)*cos(a)*dt1)-((sin(r)*dt1-da)*cos(b)-(cos(r)*sin(a)*dt1+dr*cos(a))*sin(b))*cos(c);
_Kinematics_Wheels[10]:=-(sin(a)*dr-db-cos(r)*cos(a)*dt1)*cos(c)-sin(c)*((sin(r)*dt1-da)*cos(b)-(cos(r)*sin(a)*dt1+dr*cos(a))*sin(b));
_Kinematics_Wheels[11]:=dc+cos(b)*(cos(r)*sin(a)*dt1+dr*cos(a))+(sin(r)*dt1-da)*sin(b);
_Kinematics_Wheels[12]:=x+0.5*W*(sin(c)*cos(a)-sin(a)*sin(b)*cos(c));
_Kinematics_Wheels[13]:=-0.5*W*(sin(c)*sin(a)*sin(b)+cos(a)*cos(c))+y;
_Kinematics_Wheels[14]:=-0.5*sin(a)*W*cos(b)+z;
_Kinematics_Wheels[15]:=-sin(c)*cos(a)+sin(a)*sin(b)*cos(c);
_Kinematics_Wheels[16]:=sin(c)*sin(a)*sin(b)+cos(a)*cos(c);
_Kinematics_Wheels[17]:=sin(a)*cos(b);
_Kinematics_Wheels[18]:=dx-0.5*sin(a)*W*cos(b)*db*cos(c)-0.5*(sin(c)*sin(a)+sin(b)*cos(a)*cos(c))*W*da+0.5*dc*W*(sin(c)*sin(a)*sin(b)+cos(a)*cos(c));
_Kinematics_Wheels[19]:=0.5*dc*W*(sin(c)*cos(a)-sin(a)*sin(b)*cos(c))-0.5*W*(sin(c)*sin(b)*cos(a)-sin(a)*cos(c))*da+dy-0.5*sin(c)*sin(a)*W*cos(b)*db;
_Kinematics_Wheels[20]:=-0.5*W*cos(b)*da*cos(a)+dz+0.5*sin(a)*W*db*sin(b);
_Kinematics_Wheels[21]:=(cos(b)*da+sin(a)*sin(b)*dt2)*cos(c)-sin(c)*(dt2*cos(a)+db);
_Kinematics_Wheels[22]:=(dt2*cos(a)+db)*cos(c)+sin(c)*(cos(b)*da+sin(a)*sin(b)*dt2);
_Kinematics_Wheels[23]:=dc-sin(b)*da+sin(a)*cos(b)*dt2;
_Kinematics_Wheels[24]:=x-0.5*W*(sin(c)*cos(a)-sin(a)*sin(b)*cos(c));
_Kinematics_Wheels[25]:=0.5*W*(sin(c)*sin(a)*sin(b)+cos(a)*cos(c))+y;
_Kinematics_Wheels[26]:=0.5*sin(a)*W*cos(b)+z;
_Kinematics_Wheels[27]:=-sin(c)*cos(a)+sin(a)*sin(b)*cos(c);
_Kinematics_Wheels[28]:=sin(c)*sin(a)*sin(b)+cos(a)*cos(c);
_Kinematics_Wheels[29]:=sin(a)*cos(b);
_Kinematics_Wheels[30]:=dx+0.5*sin(a)*W*cos(b)*db*cos(c)+0.5*(sin(c)*sin(a)+sin(b)*cos(a)*cos(c))*W*da-0.5*dc*W*(sin(c)*sin(a)*sin(b)+cos(a)*cos(c));
_Kinematics_Wheels[31]:=-0.5*dc*W*(sin(c)*cos(a)-sin(a)*sin(b)*cos(c))+0.5*W*(sin(c)*sin(b)*cos(a)-sin(a)*cos(c))*da+dy+0.5*sin(c)*sin(a)*W*cos(b)*db;
_Kinematics_Wheels[32]:=0.5*W*cos(b)*da*cos(a)+dz-0.5*sin(a)*W*db*sin(b);
_Kinematics_Wheels[33]:=-sin(c)*(dt3*cos(a)+db)+(cos(b)*da+dt3*sin(a)*sin(b))*cos(c);
_Kinematics_Wheels[34]:=sin(c)*(cos(b)*da+dt3*sin(a)*sin(b))+(dt3*cos(a)+db)*cos(c);
_Kinematics_Wheels[35]:=dc-sin(b)*da+dt3*sin(a)*cos(b);

return _Kinematics_Wheels;
end proc;
C(p, optimized, precision=double, filename = "./_maple_include.c");
