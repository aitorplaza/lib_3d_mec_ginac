from sys import argv
import matplotlib.pyplot as plt 
import scipy.io as sio
import numpy as np

script, filename = argv

txt = open(filename)

syms=[]
opsM=[]
opsQ=[]
opsMQ=[]
with open(filename) as f:
    for line in f:
        l=line.split(' ')
        if l[0]=='symb':
            syms.append(l[2])
        elif l[0]=='Mnew.c':
            opsM.append(int(l[3]))
        elif l[0]=='Qnew.c':
            opsQ.append(int(l[3]))            
        elif l[0]=='MQnew.c':
            opsMQ.append(int(l[3]))

symbs=range(len(opsM))

fig, ax = plt.subplots()
ax.plot(opsM, 'k--', label='M ops')
ax.plot(opsQ, 'k:', label='Q ops')
ax.plot(opsMQ, 'k', label='MQ ops')
plt.xlabel('symbs')
plt.ylabel('ops')
plt.title('Hexaglide')

plt.xlim([0,len(opsM)])
legend = ax.legend(loc='best', shadow=True)
plt.show()
plt.savefig('myfig.png')
vect = np.array([opsM,opsQ,opsMQ])
sio.savemat('data.mat', {'data':np.transpose(vect)})

