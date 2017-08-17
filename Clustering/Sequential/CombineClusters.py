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
        selectedCab[selectedCab_index] = int(q)
        selectedCab_index = selectedCab_index + 1

    #print(selectedCab)
            
    for k in open('ClusteredCabs_labels.csv', 'r').read().split():
        
        cabID = selectedCab[ClusteredCabs_labels_index]
        ClusteredCabs_labels_index = ClusteredCabs_labels_index + 1

        if cabID == 0:
            print("Stop")
        
        if int(k) in list(ClusteredCentroids.keys()):
            MinimizedCluster_index = int(ClusteredCentroids[int(k)])

        else :
            print("Cluster %s not evalusted", (k))        
            sys.exit()

        if MinimizedCluster_index not in MinimizedClusteredCabs.keys():
            MinimizedClusteredCabs[MinimizedCluster_index] = list()

        MinimizedClusteredCabs[MinimizedCluster_index].append(cabID)

    MinimizedClusteredCabs_count = len(list(MinimizedClusteredCabs.keys()))

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
