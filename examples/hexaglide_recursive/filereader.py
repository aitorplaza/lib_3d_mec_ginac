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
opsKPhi=[]
sing = []
with open(filename) as f:
    for line in f:
        l=line.split(' ')
        if l[0]=='symb':
            #syms.append(l[2])
            syms.insert(0, l[2])
        elif l[0]=='Mnew.m':
            opsM.insert(0, int(l[3]))
            #opsM.append(int(l[3]))
        elif l[0]=='Qnew.m':
            #opsQ.append(int(l[3]))
            opsQ.insert(0, int(l[3]))
        elif l[0]=='MQnew.m':
            #opsMQ.append(int(l[3]))
            opsMQ.insert(0, int(l[3]))
        elif l[0]=='WPhinew.m':
            #opsKPhi.append(int(l[3]))
            opsKPhi.insert(0, int(l[3]))

          
symbs=range(len(opsM))

#fig, ax = plt.subplots()
#ax.plot(opsM, 'k--', label='$\mathbf{M}$ ops')
#ax.plot(opsQ, 'k:', label='$\mathbf{\delta}$ ops')
#ax.plot(opsMQ, 'k', label='$\mathbf{M}\mathbf{\delta}$ ops')
#plt.xlabel('Symbs')
#plt.ylabel('Ops')
#plt.title('Hexaglide')

#plt.xlim([0,len(opsM)])
#legend = ax.legend(loc='best', shadow=True)
#plt.show()

vect = np.array([opsM,opsQ,opsMQ,opsKPhi])
print('kuku')
#print(np.transpose(vect).shape)
#~ sio.savemat('hexa_ele.mat', mdict={'hexa_ele':np.transpose(vect)})
#~ sio.savemat('hexa_add.mat', mdict={'hexa_add':np.transpose(vect)})
sio.savemat('hexa_qr.mat', mdict={'hexa_qr':np.transpose(vect)})




