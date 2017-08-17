from SOM import SOM

#For plotting the images
from matplotlib import pyplot as plt
import tensorflow as tf
import numpy as np

def SOM_clustering():
    arr = np.array([])

    with open("AllTrajecsNopePoints.data") as f:
            for line in f:            
                strings = line.split(" ")
                arrcol =  np.array([])
                for str in strings:
                    arrcol = np.concatenate((arrcol,np.array([float(str)])),axis = 0)
                if len(arr) == 0:
                    arr = np.concatenate((arr,arrcol),axis = 0)
                else:
                    arr = np.vstack((arr,arrcol))
                #print (arr)

    testX = arr
 
    print ("Cluster Start")
    #Train a 20x30 SOM with 400 iterations
    som = SOM(20, 30, 720, 400)
    som.train(testX)

    print ("get_centroids")
    #Get output grid
    image_grid = som.get_centroids()
    #Write to file
    target = open("ClusteredCentroids.csv",'w')
    count = 0
    for i, m in enumerate(image_grid):
        for column in m:
            for k , dim in enumerate(column):
                if(k != 0):
                    target.write(" ")
                target.write("%s" % (dim))
            target.write("\n")

    #        target.write("%s " % (n))
    #    target.write("\n")
    target.close()
    #for i, m in enumerate(image_grid):
    #    print("i m[1] m[0] =", i ,m[1], m[0])
        
    #Map colours to their closest neurons
    mapped = som.map_vects(testX)

    print ("Plot")
    array = np.zeros((20,30))
    #Plot
    #plt.imshow(image_grid)
    #plt.title('Color SOM')
    #plt.plot(20, 30, 'b.')
    target = open("ClusteredCabs_labels.csv",'w')
    for i, m in enumerate(mapped):
        index = ((m[0]) * 30) + (m[1]+1)
        target.write("%s\n" % (index))
        print(index)
        array[m[0], m[1]] += 1
    target.close()
        #print("i m[1] m[0] =", i ,m[1], m[0])
        #plt.plot(m[1], m[0], 'ro')
        #plt.text(m[1], m[0], index, ha='center', va='center',
         #        bbox=dict(facecolor='white', alpha=0.5, lw=0))
    #plt.show()

    array = array.astype(int)
    array = np.reshape(array,600)
    print(array)
    #print (testX)

    ###Write to file
    ##target = open("ClusteredCabs.clu",'w')
    ##for i, m in enumerate(array):
    ##    #if m != 0 :
    ##        target.write("%s %s" % (i, m))
    ##        target.write("\n")
    ##target.close()
    return;

