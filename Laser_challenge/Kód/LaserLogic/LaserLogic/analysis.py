from os import write
import matplotlib.pyplot as plt
import pandas as pd
from scipy.optimize import leastsq
import pylab as plt
import numpy as np
import scipy
import scipy.constants as pi


x, y, z = [], [], []

for line in open('LaserLogic/AweragedValues.txt', 'r'):
    values = [float(s) for s in line.split()]
    x.append(values[0])
plt.plot(x)
plt.show()

rt = []
for line in open('Gause.txt', 'r'):
    values = [float(s) for s in line.split()]
    rt.append(values[0])
plt.plot(rt)
plt.show()

#ploting first blade
#for line in open('data1firstblade.txt', 'r'):
#    values = [float(s) for s in line.split()]
#    x.append(values[0])
#plt.plot(x)
#plt.show()
#ploting secod blade whole pass
for line in open('data2secondblade.txt', 'r'):
    values = [float(s) for s in line.split()]
    y.append(values[0])    

FirstBlade = pd.read_csv('data3firstblade.csv', header = None)    
FirstBlade.mean(axis=1).plot(style='rx')
Length = len(FirstBlade)



plt.show()

data = pd.read_csv('data_static3.csv', header = None)
data[0].plot( style='o' )

#plt.plot([0, 75000],[22.3, 22.3], '-k')

plt.savefig('Static2PlotAndMesured.png', dpi = 1000, bbox_inches='tight')
plt.show()
plt.plot(z)
plt.plot(x)
plt.show()

length = len(x)

for i in range(170):

    for itr in range(length):
        if(itr == 0):

           x[itr] = x[itr] 
        if(itr == len(x) - 1):
          x[itr] = (x[itr] +  x[itr-1])/2   
        else:
            x[itr] = (x[itr] + x[itr+1] + x[itr-1])/3

Frequency, Wavelength, Speed = [], [], []
for power in range(length):
    Frequency.append((x[power]/1000000)/pi.h)
    Wavelength.append((pi.speed_of_light * pi.h)/(x[power]/1000000))
    #Speed.append(Wavelength * Frequency)

#plt.plot(Frequency, 'o')
#plt.show

#plt.plot(Wavelength)
#plt.show()


plt.plot(x, 'rx')
plt.show()