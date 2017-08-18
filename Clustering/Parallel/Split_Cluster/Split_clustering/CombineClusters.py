import sys

def combineClusters():
    MinimizedClusteredCabs = {}
    ClusteredCentroids = {}
    selectedCab = {}
    ClusteredCabs_labels = {}
    SOMcluster_index = 1
    selectedCab_index = 1
    ClusteredCabs_labels_index = 1

    for w in open('Minimized_ClusteredCentroids_labels.clu', 'r').read().split():
        ClusteredCentroids[SOMcluster_index] = int(w)
        SOMcluster_index = SOMcluster_index + 1


    for q in open('sampled.txt', 'r').read().split():
        cabID = int(q)        
        ClusterID = ClusteredCentroids[selectedCab_index]
        selectedCab_index = selectedCab_index + 1
        if ClusterID not in MinimizedClusteredCabs.keys():
            MinimizedClusteredCabs[ClusterID] = list()

        MinimizedClusteredCabs[ClusterID].append(cabID)

    MinimizedClusteredCabs_count = len(MinimizedClusteredCabs.keys())
    target = open("FinalClusters_before_Optimization.csv",'w')
    target.write("%s\n" % (MinimizedClusteredCabs_count))

    for key in MinimizedClusteredCabs.keys():
        #print(MinimizedClusteredCabs[key])
        for index , item in enumerate(MinimizedClusteredCabs[key]):
                if(index != 0):
                    target.write(" ")
                target.write("%s" % (item))
        target.write("\n") 
    target.close()
    return;

