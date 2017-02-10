'''
 -------------------------------------------------------------------------
 Function:
 [RD,CD,order]=optics(x,k)
 -------------------------------------------------------------------------
 Aim:
 Ordering objects of a data set to obtain the clustering structure
 -------------------------------------------------------------------------
 Input:
 x - data set (m,n); m-objects, n-variables
 k - number of objects in a neighborhood of the selected object
 (minimal number of objects considered as a cluster)
 -------------------------------------------------------------------------
 Output:
 RD - vector with reachability distances (m,1)
 CD - vector with core distances (m,1)
 order - vector specifying the order of objects (1,m)
 -------------------------------------------------------------------------
 Example of use:
 x=[randn(30,2)*.4;randn(40,2)*.5+ones(40,1)*[4 4]];
 [RD,CD,order]=optics(x,4)
 -------------------------------------------------------------------------
 References:
 [1] M. Ankrest, M. Breunig, H. Kriegel, J. Sander,
 OPTICS: Ordering Points To Identify the Clustering Structure,
 available from www.dbs.informatik.uni-muenchen.de/cgi-bin/papers?query=--CO
 [2] M. Daszykowski, B. Walczak, D.L. Massart, Looking for natural
 patterns in analytical data. Part 2. Tracing local density
 with OPTICS, J. Chem. Inf. Comput. Sci. 42 (2002) 500-507
 -------------------------------------------------------------------------
 Written by Michal Daszykowski
 Department of Chemometrics, Institute of Chemistry,
 The University of Silesia
 December 2004
 http://www.chemometria.us.edu.pl


ported to python Jan, 2009 by Brian H. Clowers, Pacific Northwest National Laboratory.
Dependencies include scipy, numpy, and hcluster.
bhclowers at gmail.com
'''


import numpy as N
import pylab as P
import matplotlib.pyplot as plt


def optics(x, k, distMethod = 'euclidean'):
    if len(x.shape)>1:
        m,n = x.shape
    else:
        m = x.shape[0]
        n == 1


    CD = N.zeros(m)
    RD = N.ones(m)*1E10

    for i in range(m):
        d = traj_euclid(x[i],x)
        d.sort()
        CD[i] = d[k]



    order = []
    seeds = N.arange(m, dtype = N.int)

    ind = 0
    while len(seeds) != 1:
#    for seed in seeds:
        ob = seeds[ind]
        seedInd = N.where(seeds != ob)
        seeds = seeds[seedInd]

        order.append(ob)
        tempX = N.ones(len(seeds))*CD[ob]
        tempD = traj_euclid(x[ob],x[seeds])

        temp = N.column_stack((tempX, tempD))
        mm = N.max(temp, axis = 1)
        ii = N.where(RD[seeds]>mm)[0]
        RD[seeds[ii]] = mm[ii]
        ind = N.argmin(RD[seeds])


    order.append(seeds[0])
    RD[0] = 0 #we set this point to 0 as it does not get overwritten
    return RD, CD, order

##def traj_euclid(i, x):
##    """euclidean(i, x) -> euclidean distance between x and y"""
##    y = N.zeros_like(x)    
##    y += 1
##    y[x == 0] = 0
##    tot_time = N.sum(y, axis = 1)
##    y *= i
##
##    if len(x) != len(y):
##        raise (ValueError, "vectors must be same length")
##    
##    d = (x-y)**2
##
##    dis = N.sqrt(N.sum(d, axis = 1))
##    dis1 = dis / tot_time
##    return dis1

def traj_euclid(i, x):
    """euclidean(i, x) -> euclidean distance between x and y"""
    y = N.zeros_like(x)    
    y += 1
    y *= i

    y[x == 0] = 0

    x[y == 0] = 0
    
    #tot_time = N.sum(y, axis = 1)
    

    if len(x) != len(y):
        raise (ValueError, "vectors must be same length")
    
    d = (x-y)**2
    ttime = N.zeros_like(d)
    ttime += 1
    ttime[d == 0] = 0
    tot_time = N.sum(ttime, axis = 1)

    dis = N.sqrt(N.sum(d, axis = 1))
    #print(dis)
    #print(tot_time)
    tot_time += 1
    dis1 = dis / tot_time
    return dis1

if __name__ == "__main__":
    arr = N.array([])
    
    with open("AllTrajecsConverted.data") as f:
        next(f)
        for line in f:            
            strings = line.split(",")
            arrcol =  N.array([])
            for str in strings:
                arrcol = N.concatenate((arrcol,N.array([float(str)])),axis = 0)
            if len(arr) == 0:
                arr = N.concatenate((arr,arrcol),axis = 0)
            else:
                arr = N.vstack((arr,arrcol))

    testX = arr
    #print (testX)

    RD, CD, order = optics(testX, 5)
    testXOrdered = testX[order]
    print(RD[order])

    RD_str = ""
    Order_str = ""
    for i in order:
        tempfloat = N.float32(RD[i]).item()
        tempstr = "%.3f" % tempfloat
        RD_str += tempstr
        RD_str += " "
        tempfloat = N.asscalar(N.int16(i))
        tempstr = "%d" % tempfloat
        Order_str += tempstr
        Order_str += " "

    target = open("RD.data",'w')
    target.write(RD_str)
    target.write("\n")    
    target.close()

    target = open("Order.data",'w')
    target.write(Order_str)
    target.write("\n")    
    target.close()
	
    #print (order)
    print (RD[order])

##    a = RD > 0.0023
##    b = RD
##    b[a] = 0.0
    #c = order[a]
    print (order)
##    N1 = len(order)
##    N = len(RD)
##    x = range(N)
##    width = 1/1.5
##    plt.bar(x, b, width, color="blue")
##    plt.xticks(x, order)
##    plt.ylabel('Order')
##    plt.title('Rechability Plot') 
##    plt.show()
    
    N = len(RD)
    x = range(N)
    width = 1/1.5
    plt.bar(x, RD[order], width, color="blue")
    plt.xticks(x, order)
    plt.ylabel('Order')
    plt.title('Rechability Plot') 
    plt.show()

    #P.show()
