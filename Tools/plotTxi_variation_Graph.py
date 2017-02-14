import numpy as np
import matplotlib.pyplot as plt

#with open("ID_freq.txt") as f:
with open("ID_IdleTime_freq.txt") as f:
    next(f)
    data = f.read()

data = data.split('\n')

x = [row.split(',')[0] for row in data]
y = [row.split(',')[1] for row in data]

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("ID vs Freq plot")    
ax1.set_xlabel('ID')
ax1.set_ylabel('Freq')

ax1.plot(x,y, c='r', label='the data')

leg = ax1.legend()

plt.show()
