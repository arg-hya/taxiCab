// TaskAssingAndEvaluation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"

#include <algorithm>
#include <vector>
#include <stdlib.h>
#include "ReadClusters.h" 
#include "ReadSampleTasks.h"
#include "ReadTrajectory.h"

int DetermineCluspterPaymentRate(int tot_clusters, Cluster* &Clusters)
{
    for (size_t i = 0; i < tot_clusters; i++)
    {
        int cost = Clusters[i].CabIDs.size();
        Clusters[i].cost = cost;
    }
    return EXIT_SUCCESS;
}

int AssignTask(std::vector<Task>& SampleTasks, Cluster* &Clusters, int tot_clusters)
{
    int sampleTaskLen, minTakperCluster, k;

    sampleTaskLen = SampleTasks.size();
    minTakperCluster = MIN_TASKPERCLUSTER; //sampleTaskLen / tot_clusters;
    k = 0;

    for (size_t i = 0; i < tot_clusters; i++)
    {
        for (size_t j = 0; j < minTakperCluster; j++)
        {
            if (k == sampleTaskLen)   k = 0;
            Clusters[i].TaskIDs.push_back(k++);
        }
    }
    return EXIT_SUCCESS;
}

int PutTrajecsInClusters(Cluster* &Clusters, CabTrajectory** Cabs, std::vector<unsigned int> IDs,
    int tot_clusters, int tot_epoch)
{
    for (int i = 0; i < tot_clusters; i++)
    {
        Clusters[i].Cabs = new CabTrajectory*[Clusters[i].CabIDs.size()];

        for (int k = 0; k < Clusters[i].CabIDs.size(); k++)
        {
            unsigned int it = Clusters[i].CabIDs.at(k);

            //Find index
            std::vector<unsigned int>::iterator pt = std::find(IDs.begin(), IDs.end(), it);
            int pos = pt - IDs.begin();

            Clusters[i].Cabs[k] = new CabTrajectory[tot_epoch];
            for (int j = 0; j < tot_epoch; j++)
            {
                Clusters[i].Cabs[k][j] = Cabs[pos][j];
            }
        }
    }
    return EXIT_SUCCESS;
}

int CalculateSaptioTemporalCoverage(Cluster &Cluster, std::vector<Task> &SampleTasks, int tot_epoch, int tot_cabs)
{
    unsigned int sum_x = 0, sum_y = 0, spatcov = 0, min = 0;

    for (std::vector<int>::iterator it = Cluster.TaskIDs.begin(); it != Cluster.TaskIDs.end(); ++it)
    {
        int current_epoch = SampleTasks.at(*it).epoch;
        Task TempTask;
        TempTask.epoch = current_epoch;
        TempTask.lat = SampleTasks.at(*it).lat;
        TempTask.lon = SampleTasks.at(*it).lon;
        TempTask.idleTime = SampleTasks.at(*it).idleTime;

        for (int j = 0; j < tot_cabs; j++)
        {
            if ((Cluster.Cabs[j][current_epoch].lat == 0)|| (Cluster.Cabs[j][current_epoch].lon == 0))
                continue;
            sum_x = Cluster.Cabs[j][current_epoch].lat - TempTask.lat;
            sum_y = Cluster.Cabs[j][current_epoch].lon - TempTask.lon;

            unsigned int dist = std::sqrt(SQUARE((sum_x)) + SQUARE((sum_y)));
            if (0 == j)
                min = dist;
            else
            {
                if (min > dist)
                {
                    min = dist;
                }
            }
        }

        spatcov += min;
    }
   
    Cluster.spatcov = spatcov;

    return EXIT_SUCCESS;
}

//int CalculateSaptioTemporalCoverage(Cluster &Cluster, std::vector<Task> &SampleTasks, int tot_epoch, int tot_cabs)
//{
//    int k = 0, sum_x = 0, sum_y = 0, spatcov = 0;
//    std::vector<Task>* ClusterTasks = NULL;
//
//    /*Store the tasks assigned to this cluster per epoch-wise*/
//    ClusterTasks = new std::vector<Task>[tot_epoch];
//    for (std::vector<int>::iterator it = Cluster.TaskIDs.begin(); it != Cluster.TaskIDs.end(); ++it)
//    {
//        int current_epoch = SampleTasks.at(*it).epoch;
//        Task TempTask;
//        TempTask.epoch = current_epoch;
//        TempTask.lat = SampleTasks.at(*it).lat;
//        TempTask.lon = SampleTasks.at(*it).lon;
//        TempTask.idleTime = SampleTasks.at(*it).idleTime;
//
//        ClusterTasks[current_epoch].push_back(TempTask);
//    }
//
//    /*Get the trajectory of the cabs*/
//    for (int i = 0; i < tot_epoch; i++)
//    {
//        int x, y, x1, y1;
//        sum_x = sum_y = 0;
//        for (std::vector<Task>::iterator it = ClusterTasks[i].begin(); it != ClusterTasks[i].end(); ++it)
//        {
//            for (int j = 0; j < tot_cabs; j++)
//            {
//                sum_x += Cluster.Cabs[j][i].lat;
//                sum_y += Cluster.Cabs[j][i].lon;
//            }
//            x = (sum_x / tot_cabs);
//            y = (sum_y / tot_cabs);
//            x1 = ((sum_x + it->lat) / (tot_cabs + 1));
//            y1 = ((sum_y + it->lon) / (tot_cabs + 1));
//
//            spatcov += std::sqrt(SQUARE((x - x1)) + SQUARE((y - y1)));
//        }
//    }
//    Cluster.spatcov = spatcov;
//
//    //Clean up
//    for (int i = 0; i < tot_epoch; i++)
//    {
//        std::vector<Task>().swap(ClusterTasks[i]);
//    }
//    delete[] ClusterTasks;
//
//
//    return EXIT_SUCCESS;
//}

int swapTasks(Cluster &Cluster1, Cluster &Cluster2)
{
    Cluster1.TaskIDs.swap(Cluster2.TaskIDs);

    return EXIT_SUCCESS;
}

bool customComp(tempst a, tempst b)
{
    return (a.data > b.data);
}


int selectClusters(Cluster* &Clusters, std::vector<unsigned int>& SelectedClusterIDs,
    int tot_clusters, int budget, int *Budget_rem)
{
    std::vector<tempst> sptcov_cost;

    for (int i = 0; i < tot_clusters; i++)
    {
        tempst temp;
        temp.indx = i;
        temp.data = Clusters[i].spatcov / Clusters[i].cost;

        sptcov_cost.push_back(temp);
    }

    std::sort(sptcov_cost.begin(), sptcov_cost.end(), customComp);

    int j = 0;
    while (j < sptcov_cost.size())
    {
        budget -= Clusters[sptcov_cost[j].indx].cost;
        if (budget > 0)
        {
            SelectedClusterIDs.push_back(sptcov_cost[j].indx);
            j++;
        }
        else
        {
            break;
        }
    }

    if (j >= sptcov_cost.size()) j--;

    *Budget_rem = budget + Clusters[sptcov_cost[j].indx].cost;

    return EXIT_SUCCESS;
}

int printSelectedClusters(Cluster* &Clusters, std::vector<unsigned int> SelectedClusterIDs)
{
    for (std::vector<unsigned int>::iterator it = SelectedClusterIDs.begin(); it != SelectedClusterIDs.end(); ++it)
    {
        std::cout << "Cluster No: " << *it << std::endl;
        for (std::vector<unsigned int>::iterator pt = Clusters[*it].CabIDs.begin();
            pt != Clusters[*it].CabIDs.end(); ++pt)
        {
            std::cout << *pt << " ";
        }
    }

    return EXIT_SUCCESS;
}

int writeSelectedClusters(Cluster* &Clusters, std::vector<unsigned int> SelectedClusterIDs, std::string OutIDFilepath, int tot_epoch)
{
    std::ofstream out_med_file;

    out_med_file.open(OutIDFilepath, std::ios::out);

    out_med_file << SelectedClusterIDs.size() << std::endl;
    out_med_file << tot_epoch << std::endl;

    for (std::vector<unsigned int>::iterator it = SelectedClusterIDs.begin(); it != SelectedClusterIDs.end(); ++it)
    {
        CabTrajectory* temp = new CabTrajectory[tot_epoch];
        for (int j = 0; j < tot_epoch; j++)
        {
            temp[j].lat = 0;
            temp[j].lon = 0;
        }

        out_med_file << std::endl;

        for (std::vector<unsigned int>::iterator pt = Clusters[*it].CabIDs.begin();
            pt != Clusters[*it].CabIDs.end(); ++pt)
        {
            out_med_file << *pt << " ";

        }
        
        out_med_file << std::endl;

        for (size_t i = 0; i < Clusters[*it].CabIDs.size(); i++)
        {
            for (int j = 0; j < tot_epoch; j++)
            {
                temp[j].lat += Clusters[*it].Cabs[i][j].lat;
                temp[j].lon += Clusters[*it].Cabs[i][j].lon;
            }
        }
        
        for (int j = 0; j < tot_epoch; j++)
        {
            out_med_file << (temp[j].lat / Clusters[*it].CabIDs.size()) << " ";
            out_med_file << (temp[j].lon / Clusters[*it].CabIDs.size()) << " ";
        }
    }
    out_med_file << std::endl;

    out_med_file.close();

    return EXIT_SUCCESS;
}

int getMin(int a, int b, int c, int d)
{
    int x, y;

    x = (a < b) ? a : b;
    y = (c < d) ? c : d;


    return (x < y) ? x : y;
}

int main()
{
    srand((unsigned int)time(NULL));

    int tot_clusters = 0, tot_Selclusters = 0, time_constraint = 0, tot_sampletask = 0, tot_epoch = 0,
        tot_SelectedClusters = 0, tot_cabs = 0;
    int Budget, Budget_rem;
    Cluster* Clusters = NULL;
    CabTrajectory** Cabs = NULL;
    std::vector<Task> SampleTasks;
    std::vector<unsigned int> IDs;
    std::vector<unsigned int> SelectedClusterIDs;

    ReadClusters* ReadCluster = new ReadClusters();
    ReadCluster->ClusterFilePath = OUTPUT_DIR + "FinalClusters_before_Optimization.csv";
    ReadCluster->getClusters(Clusters);
    tot_clusters = ReadCluster->count;
    delete ReadCluster;

    ReadSampleTasks* ReadSampleTask = new ReadSampleTasks();
    ReadSampleTask->SampleTasksFilePath = OUTPUT_DIR + "TestTask.data";
    ReadSampleTask->getSampleTasks(SampleTasks);
    tot_sampletask = SampleTasks.size();
    tot_epoch = ReadSampleTask->tot_epoch;
    delete ReadSampleTask;
   // tot_epoch = 720;
    ReadTrajectory* ReadTrajec = new ReadTrajectory();
    ReadTrajec->IDfilePath = INPUT_DIR + "1\\" + "sampled.txt";
    ReadTrajec->SampledTrajecFilesPath = OUTPUT_DIR + "Sampled_Trajecs\\";
    ReadTrajec->getIDs(IDs);
    Cabs = new CabTrajectory*[IDs.size()];
    ReadTrajec->getTrajecs(Cabs, IDs, tot_epoch);
    tot_cabs = IDs.size();
      PutTrajecsInClusters(Clusters, Cabs, IDs, tot_clusters, tot_epoch);
    delete[] Cabs;
    delete ReadTrajec;

    Budget = BUDGET;

    DetermineCluspterPaymentRate(tot_clusters, Clusters);

    AssignTask(SampleTasks, Clusters, tot_clusters);

    for (size_t i = 0; i < tot_clusters; i++)
    {

        Clusters[i].spatcov = 0;
        CalculateSaptioTemporalCoverage(Clusters[i], SampleTasks, tot_epoch, Clusters[i].CabIDs.size());
    }

    selectClusters(Clusters, SelectedClusterIDs, tot_clusters, Budget, &Budget_rem);
    tot_SelectedClusters = SelectedClusterIDs.size();

    int count = 0;
    do
    {
        int indx_a = RANDOM(0, tot_clusters - 1);
        //int indx_a = a; //SelectedClusterIDs[a];
        int b = RANDOM(0, tot_SelectedClusters - 1);
        int indx_b = SelectedClusterIDs[b];
        int init_sptcov_a = Clusters[indx_a].spatcov;
        int init_sptcov_b = Clusters[indx_b].spatcov;

        swapTasks(Clusters[indx_a], Clusters[indx_b]);
        CalculateSaptioTemporalCoverage(Clusters[indx_a], SampleTasks, tot_epoch, Clusters[indx_a].CabIDs.size());
        CalculateSaptioTemporalCoverage(Clusters[indx_b], SampleTasks, tot_epoch, Clusters[indx_b].CabIDs.size());

        int max = getMin(init_sptcov_a, init_sptcov_b, Clusters[indx_a].spatcov, Clusters[indx_b].spatcov);

        if (max == init_sptcov_a)
        {
            swapTasks(Clusters[indx_a], Clusters[indx_b]);

            //Check if already present
            std::vector<unsigned int>::iterator pt = std::find(SelectedClusterIDs.begin(), SelectedClusterIDs.end(), indx_a);
            if (pt == SelectedClusterIDs.end())
            {
                if (Clusters[indx_a].cost <= (Clusters[indx_b].cost + Budget_rem))
                {
                    SelectedClusterIDs[b] = indx_a;
                    Budget_rem -= (Clusters[indx_a].cost - Clusters[indx_b].cost);
                    count = 0;
                }
            }
        }
        else if (max == init_sptcov_b)
        {
            swapTasks(Clusters[indx_a], Clusters[indx_b]);
            //select b;    
            count = 0;
        }
        else if (max == Clusters[indx_a].spatcov)
        {
            //Check if already present
            std::vector<unsigned int>::iterator pt = std::find(SelectedClusterIDs.begin(), SelectedClusterIDs.end(), indx_a);
            if (pt == SelectedClusterIDs.end())
            {
                if (Clusters[indx_a].cost <= (Clusters[indx_b].cost + Budget_rem))
                {
                    SelectedClusterIDs[b] = indx_a;
                    Budget_rem -= (Clusters[indx_a].cost - Clusters[indx_b].cost);
                }
                count = 0;
            }
            else //Index already present, thus reverting the changes done
            {
                swapTasks(Clusters[indx_a], Clusters[indx_b]);
                //count ++;
            }
        }
        else if (max == Clusters[indx_b].spatcov)
        {
            count++;
            //select b; 
        }

    } while ((count < GREEDY_THRESHOLD) || (Budget_rem > 0));

    std::sort(SelectedClusterIDs.begin(), SelectedClusterIDs.end());

    writeSelectedClusters(Clusters, SelectedClusterIDs, OUTPUT_DIR + "FinalClusters.data", tot_epoch);

    printSelectedClusters(Clusters, SelectedClusterIDs);

    return 0;
}

