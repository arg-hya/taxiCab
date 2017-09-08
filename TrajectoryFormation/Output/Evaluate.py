from collections import namedtuple
import numpy as np

if __name__ == "__main__":

    Threshold  = 3633.578416263814

    Error = []
    Assigned_ClusterID = []
    Clusters = {}
    TaskDict = {}
    Task = namedtuple('Task','Lat Lon Idle_Time Epoch')
    a = Task(1,1,1,1)
#    print(a)
    #Getting Task info
    TaskCount = 0
    with open("SpecifiedTasks.data") as f:
        next(f)
        for line in f:
            strings = line.split(",")
            TaskDict[TaskCount] = Task(int(float(strings[0])),int(float(strings[1])),strings[2],strings[3].split("\n")[0])        
            TaskCount = TaskCount + 1

##    print("Task Count : " , TaskCount)
##    print(TaskDict)
##    
    #Getting the cluster IDs assigned to each task
    for w in open('ClusterID_TaskAssignation.data', 'r').read().split():
        Assigned_ClusterID.append(int(w))

    #Getting the clusters
    ID = 0
    isClusterIDs = True
    with open("FinalClusters.data") as f:
        next(f)
        next(f)
        for line in f:
            if isClusterIDs:
                line = line.rstrip()
                strings = line.split(" ")
                Clusters[ID] = list()
                for cabID in strings:
                     Clusters[ID].append(int(cabID))                     
                ID = ID + 1          
            isClusterIDs = not isClusterIDs
    ClustersCount = ID

    #print (Clusters)
    #Store cab trajectories
    nan_count = 0
    Trajectories = {}
    #print ("Clusters are :")
    for ClusterID in Clusters:
        #print (Clusters[ClusterID])
        for cabID in Clusters[ClusterID]:
            Trajectories[cabID] = list()
            filename = "Sampled_Trajecs\\" + str(cabID) + "_sampled.traj"
            epoch = 1          
            for w in open(filename, 'r').read().split("\n"):
                if w != '':
                    strings = w.split(",")
                    if strings[2] == 'nan' :
                        nan_count = nan_count + 1
                        Trajectories[cabID].append(Task(0,0,strings[0],epoch))
                    else:
                        Trajectories[cabID].append(Task(int(strings[2]),int(strings[3]),strings[0],epoch))
                    epoch = epoch + 1
                    #print(Trajectories[cabID])
    #print ("nan_count %s" %(nan_count))    
        
    #Evaluate error for each task
    for TaskID, ClusterID in enumerate(Assigned_ClusterID):
        #print("Evalusting Task ID : ", TaskID)
        #print("ClusterID : ", ClusterID)
        Epoch = int(TaskDict[TaskID].Epoch)
        #For each cab
        errorLat = 0 
        errorLon = 0
        min_error = float("inf")
        for CabID in Clusters[ClusterID]:
            if((Trajectories[CabID][Epoch].Lat != 0) or(Trajectories[CabID][Epoch].Lon != 0)):
                errorLat = errorLat + Trajectories[CabID][Epoch].Lat - TaskDict[TaskID].Lat
                errorLon = errorLon + Trajectories[CabID][Epoch].Lon - TaskDict[TaskID].Lon
                error = ( errorLat ** 2 + errorLon ** 2 ) ** 0.5
                if min_error > error:
                    min_error = error
        min_error = min_error / Threshold
        Error.append(int(min_error))
    print(Error)
