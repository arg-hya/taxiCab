import numpy as np
from sklearn.cluster import KMeans

import pandas as pd

def kmeans_clustering():
    df = pd.read_csv('ClusteredCentroids.csv', sep=" ", header = None)
    #df.columns = ["Driver_ID","Distance_Feature","Speeding_Feature"]

    temp=[]

    for row in df.iterrows():
        index, data = row
        temp1 = data.tolist()
        temp2 = [int(i) for i in temp1]
        temp.append(temp2)




    X=np.matrix(temp)
    #print(X)
    kmeans = KMeans(n_clusters=200).fit(X)
    #Write to file
    target = open("Minimized_ClusteredCentroids_labels.clu",'w')
    for i in kmeans.labels_:
        target.write("%s\n" % (str(i)))
    target.close()
    return;
