from SOM_cluster import SOM_clustering_parallel
from kmeans import kmeans_clustering
from CombineClusters import combineClusters  

import time

if __name__ == "__main__":

    start = time.time()

    print("SOM Clustering")
    SOM_clustering_parallel();
    print("kmeans Clustering")
    kmeans_clustering();
    print("Combining Clusters")
    combineClusters();

    end = time.time()
    print(end - start)
    


