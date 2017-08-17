// TaskAssingAndEvaluation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"

#include <vector>
#include <stdlib.h>
#include "ReadClusters.h" 
#include "ReadSampleTasks.h"


int calDiff(Task tsk, CabTrajectory Centorid)
{
    int x,y, diff;

    x = tsk.lat - Centorid.lat;
    y = tsk.lon - Centorid.lon;

    diff = SQUARE(x) + SQUARE(y);
    diff = (int)std::sqrt(diff);

    return diff;
}

int printSelectedClusters(Cluster* &Clusters, int tot_clusters)
{

    for (int i = 0; i < tot_clusters; i++)
    {
        std::cout << "Cluster No: " << i << std::endl;
        std::cout << " Tasks: ";
        for (std::vector<int>::iterator it = Clusters[i].TaskIDs.begin(); it != Clusters[i].TaskIDs.end(); ++it)
        {
            std::cout << *it << " ";
        }
    }

    return EXIT_SUCCESS;
}

int main()
{
    std::ofstream out_med_file;
    out_med_file.open(OUTPUT_DIR + "ClusterID_TaskAssignation.data", std::ios::out);

    int tot_clusters = 0, tot_sampletask = 0, tot_epoch = 0;
    int Budget, Budget_rem;
    Cluster* Clusters = NULL;
    std::vector<Task> SampleTasks;

    ReadClusters* ReadCluster = new ReadClusters();
    ReadCluster->ClusterFilePath = OUTPUT_DIR + "FinalClusters.data";
    ReadCluster->getClusters(Clusters);
    tot_clusters = ReadCluster->count;
    tot_epoch = ReadCluster->tot_epoch;
    delete ReadCluster;

    ReadSampleTasks* ReadSampleTask = new ReadSampleTasks();
    ReadSampleTask->SampleTasksFilePath = OUTPUT_DIR + "SpecifiedTasks.data";
    ReadSampleTask->getSampleTasks(SampleTasks);
    tot_sampletask = SampleTasks.size();
    delete ReadSampleTask;

    //Assogn Tasks to each cluster by virtue of its centroid
    Budget = BUDGET;
    for (std::vector<Task>::iterator it = SampleTasks.begin(); it != SampleTasks.end(); ++it)
    {
        int epoch = it->epoch, diff = 0, old_diff = 0, indx = 0, taskID = 0;

        for (int i = 0; i < tot_clusters; i++)
        {
            old_diff = diff;
            if ((Clusters[i].TrajCentroid[epoch].lat == 0) || (Clusters[i].TrajCentroid[epoch].lon == 0))
                continue;
            diff = calDiff(*it, Clusters[i].TrajCentroid[epoch]);
            if (diff < old_diff)
            {
                indx = i;
            }
        }
        out_med_file << indx << std::endl;
        Clusters[indx].TaskIDs.push_back(taskID++);
    }

    out_med_file.close();

    return 0;
}

