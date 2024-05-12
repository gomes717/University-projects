import matplotlib.pyplot as plt
import numpy as np

my_array2 = np.genfromtxt('output.txt',
                      filling_values=-999)

vec_bf = [my_array2[i][0] for i in range(my_array2.shape[0])]
vec_dc = [my_array2[i][6] for i in range(my_array2.shape[0])]
aux = np.arange(10,100)

if my_array2.shape[0] > 90 and my_array2.shape[0] < 180:
    s = np.arange(10,my_array2.shape[0] - 80)*10
    aux = np.concatenate((aux,s))
elif my_array2.shape[0] > 180 and my_array2.shape[0] < 270:
    s = np.arange(10,100)*10
    aux = np.concatenate((aux,s))
    s = np.arange(10,my_array2.shape[0] - 170)*100
    aux = np.concatenate((aux,s))
elif my_array2.shape[0] > 270 and my_array2.shape[0] < 360:
    s = np.arange(10,100)*10
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*100
    aux = np.concatenate((aux,s))
    s = np.arange(10,my_array2.shape[0] - 260)*1000
    aux = np.concatenate((aux,s))
elif my_array2.shape[0] > 360 and my_array2.shape[0] < 450:
    s = np.arange(10,100)*10
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*100
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*1000
    aux = np.concatenate((aux,s))
    s = np.arange(10,my_array2.shape[0] - 350)*10000
    aux = np.concatenate((aux,s))
elif my_array2.shape[0] > 450 and my_array2.shape[0] < 540:
    s = np.arange(10,100)*10
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*100
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*1000
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*10000
    aux = np.concatenate((aux,s))
    s = np.arange(10,my_array2.shape[0] - 440)*100000
    aux = np.concatenate((aux,s))
elif my_array2.shape[0] > 540 and my_array2.shape[0] < 630:
    s = np.arange(10,100)*10
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*100
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*1000
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*10000
    aux = np.concatenate((aux,s))
    s = np.arange(10,100)*100000
    aux = np.concatenate((aux,s))
    s = np.arange(10,my_array2.shape[0] - 530)*100000
    aux = np.concatenate((aux,s))


#plt.plot(aux,vec_bf)
plt.plot(aux,vec_dc)
plt.show()
print(aux)