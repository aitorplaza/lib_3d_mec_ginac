import sys
option=0
lineaini=0
lineafin=0
verbose=1
if len(sys.argv)>1:
	if sys.argv[1]!=(0):
		name=sys.argv[1]
#		if len(sys.argv)>2:
#			lineaini=sys.argv[2]
#			if len(sys.argv)>3:
#				lineafin=sys.argv[3]
#	else:
#		option=1
else:
	name=raw_input("introduzca el nombre del fichero a parsear: ")
#	if option<1:
#		lineaini=raw_input("introduzca la linea a partir de la cual quiere contar: ")
#		lineafin=raw_input("introduzca la ultima linea en la que quiera contar: ")

operaciones=["+","-","*","/","+-","^","sin(","cos(","tan(","sqrt(","fabs(","atan(","atan2(","asin(","acos(","pow(","round(","ceil(","floor("]
filer = open(name, "r")
text=filer.read()
#filew = open("python_cuenta.txt", "a")
cuenta=[]
for i in range(0,len(operaciones)):
	cuenta.append(text.count(operaciones[i]))
	#if verbose!=0:
		#print "La operacion {0} se repite {1} veces".format(operaciones[i],cuenta[i])
		#filew.write("\nLa operacion {0} se repite {1} veces".format(operaciones[i],cuenta[i]))
#print ('Hay {0} operaciones en el fichero {1}\n'.format(sum(cuenta),name));
#print ('Hay {0} operaciones en el fichero {1}\n'.format(sum(cuenta)-2*cuenta[4],name) + " (se han elimininado las operaciones +- )");
print ('{1} ops = {0}'.format(sum(cuenta)-2*cuenta[4],name));
#filew.write('\nHay {0} operaciones en el fichero {1}\n'.format((sum(cuenta)),name))
#filew.write('\nHay {0} operaciones en el fichero {1}\n'.format((sum(cuenta)-cuenta[4]),name))
filer.close()
