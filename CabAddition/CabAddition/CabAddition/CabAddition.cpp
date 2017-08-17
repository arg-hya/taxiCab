// CabAddition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include "ReadClusters.h" 
#include "ReadCabTrajectory.h"
#include "Header.h"

time_t mktime_override(struct tm tm1)
{
    time_t sec = tm1.tm_sec + (tm1.tm_min + tm1.tm_hour * 60) * 60;
    time_t hr = tm1.tm_mday * 24; // only for jan 2013

    sec += hr * 60 * 60;

    return  sec;
}

time_t makeTime(std::string strtemp)
{
    time_t tempTime;
    struct tm tm1 = {};

    //std::string strtemp = "01-01-2013 00:00:00";
    std::istringstream ss(strtemp);
    ss >> std::get_time(&tm1, "%d-%m-%Y %H:%M:%S");

    tempTime = mktime_override(tm1);

    return tempTime;
}

int main()
{
    int min_diff = 0, index = 0;
    Cluster* Clusters = NULL;
    CabTrajectory_latlon* CabTraj = NULL;
    CabTrajectory* CabTraj_converted = NULL;

    int tot_clusters = 0, tot_epoch = 0;

    //Read Clusters
    ReadClusters* ReadCluster = new ReadClusters();
    ReadCluster->ClusterFilePath = INPUT_DIR + "FinalClustersNopePoints.data";
    ReadCluster->getClusters(Clusters);
    tot_clusters = ReadCluster->count;
    tot_epoch = ReadCluster->tot_epoch;
    delete ReadCluster;

    //Read Cab Trajectory
    std::vector <ref_time> step_array;

    for (int i = 0; i < 720; i++)
    {
        if (0 == i)  step_array.push_back({ makeTime("01-01-2013 00:01:00"), i });
        else
        {
            step_array.push_back({ (step_array[i - 1].t + 3600) , i });
        }
    }

    ReadCabTrajectory* ReadTraj = new ReadCabTrajectory();
    ReadTraj->ClusterFilePath = INPUT_DIR + "2013000001_trajectory.traj";
    ReadTraj->ClusterOutputFilePath = INPUT_DIR + "2013000001_sampled.traj";
    ReadTraj->getTraj(CabTraj, step_array);

    //Convert Cab Trajectory to node points
    //Run node converter
    std::string filename = "..\\..\\CabTrajtoNodePointsConverter.py";
    std::string command = "python ";
    //command += filename;
    system(filename.c_str());

    //Get converted trajectory
    ReadTraj->ClusterConvertedFilePath = INPUT_DIR + "2013000001_nodepoints.traj";
    ReadTraj->getConvertedTraj(CabTraj_converted, tot_epoch);
    delete ReadTraj;   

    //Find suitable cluster
    for (int i = 0; i < tot_clusters; i++)
    {
        int diff = 0;

        for (int j = 0; j < tot_epoch; j++)
        {
            if (Clusters[i].TrajCentroid[j].node_point != CabTraj_converted[j].node_point)
            {
                diff++;
            }
        }
        if (i == 0)
        {
            min_diff = diff;
            index = i;
        }
        else
        {
            if (min_diff > diff)
            {
                min_diff = diff;
                index = i;
            }
        }
    }
    
    std::cout << "Cluster = " << index << std::endl;
    std::cout << "min_diff = " << min_diff << std::endl;
    return 0;
}

