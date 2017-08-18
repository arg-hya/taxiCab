from SOM import SOM

#For plotting the images
from matplotlib import pyplot as plt
import tensorflow as tf
import numpy as np
import multiprocessing

def SOM_clustering(split,selectedCab):    

    splits_count = 4
    selectedCab_index = 1
    
        #selectedCab_index = selectedCab_index + 1

    #print(selectedCab)
    
    
    
    #for split in range(1,splits_count+1):
    arr = np.array([])
    print("Split number : %d" % (split))        
    for cabID in selectedCab:
        arrcol =  np.array([])
        #print(cabID)
        filename = "..//Split//" + str(cabID) + "_" + str(split) + "_.traj"
        with open(filename) as f:
             for line in f:
                 line = line.rstrip()
                 arrcol = np.concatenate((arrcol,np.array([int(line)])),axis = 0)
        #print(arrcol)
        if len(arr) == 0:
           arr = np.concatenate((arr,arrcol),axis = 0)
        else:
           arr = np.vstack((arr,arrcol))
    testX = arr
    print(testX)
    print ("Cluster Start")
    length = len(arr[0])
    print("Dim : %d"  %(length))
    #Train a 20x30 SOM with 400 iterations
    som = SOM(20, 30, length, 1)
    som.train(testX)
    print ("get_centroids")
    #Get output grid
    image_grid = som.get_centroids()
    #Map colours to their closest neurons
    mapped = som.map_vects(testX)

    print ("Plot")
    array = np.zeros((20,30))
    filename_ClusterLabels = "Cabs_ClusterLabels" + str(split) +".csv"
    target = open(filename_ClusterLabels,'w')
    for i, m in enumerate(mapped):
        index = ((m[0]) * 2) + (m[1]+1)
        target.write("%s\n" % (index))
        #print(index)
        array[m[0], m[1]] += 1
    target.close()
    array = array.astype(int)
    array = np.reshape(array,600)
    print(array)
    #break;
    
    return;

def SOM_clustering_parallel():
    jobs = []
    splits_count = 4
    selectedCab = []
    
    for q in open('..//sampled.txt', 'r').read().split():
        selectedCab.append(int(q))
        
    for i in range(1,splits_count+1):
        p = multiprocessing.Process(target=SOM_clustering, args = (i,selectedCab))
        jobs.append(p)
        p.start()

    for proc in jobs:
        proc.join()


