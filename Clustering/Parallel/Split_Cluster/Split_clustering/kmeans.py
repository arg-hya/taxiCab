import numpy as np
from sklearn.cluster import KMeans

import pandas as pd

def kmeans_clustering():

    temp={}
    arr = np.array([])
    for i in range(1,5):
        arrcol = np.array([])
        file_name = "Cabs_ClusterLabels" + str(i) + ".csv"
        print(file_name)
        index = 0

        with open(file_name) as f:
                 for line in f:
                     line = line.rstrip()
                     arrcol = np.concatenate((arrcol,np.array([int(line)])),axis = 0)
        if i == 1:
            for x in arrcol:
                temp[index] = list()
                index = index + 1           
            index = 0
            
        for x in arrcol:
            temp[index].append(float(x))
            index = index + 1
           
        
    for index in  temp.keys():
        if len(arr) == 0:
               arr = np.concatenate((arr,temp[index]),axis = 0)
        else:
               arr = np.vstack((arr,temp[index]))


    print(arr)
    kmeans = KMeans(n_clusters=200).fit(arr)
    #Write to file
    target = open("Minimized_ClusteredCentroids_labels.clu",'w')
    for i in kmeans.labels_:
        target.write("%s\n" % (str(i)))
    target.close()
    return;

