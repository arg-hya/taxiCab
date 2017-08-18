from SOM_cluster_NOTPARALLEL  import SOM_clustering
from kmeans import kmeans_clustering
from CombineClusters import combineClusters  

if __name__ == "__main__":

    print("SOM Clustering")
    SOM_clustering();
    print("kmeans Clustering")
    kmeans_clustering();
    print("Combining Clusters")
    combineClusters();
    


