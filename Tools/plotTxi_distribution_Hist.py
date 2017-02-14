from matplotlib import pyplot as PLT
import numpy as NP

#with open('numRides_dist.csv') as f:
with open('numIdleTimes_dist.csv') as f:
  #next(f)
  v = NP.loadtxt(f, delimiter=",", dtype='int', comments="#", skiprows=1, usecols=None)
  
v_hist = NP.ravel(v)   # 'flatten' v
fig = PLT.figure()
ax1 = fig.add_subplot(111)

n, bins, patches = ax1.hist(v_hist, bins=range(min(v_hist), max(v_hist) + 10, 10), normed=1, facecolor='red')
PLT.show()