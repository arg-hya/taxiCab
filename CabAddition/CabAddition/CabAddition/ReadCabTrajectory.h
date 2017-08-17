#pragma once

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	/* find */
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <sstream> 
#include <iomanip>
#include "Header.h"

class ReadCabTrajectory
{
private:
    std::ifstream in_file;
    int MakeNumerical(std::string& str);
    time_t mktime_override(struct tm tm1);
    int comparetime(time_t time1, time_t time2);
public:
    int count;
    int tot_epoch;
    std::string ClusterFilePath; 
    std::string ClusterOutputFilePath;
    std::string ClusterConvertedFilePath;
    int getTraj(CabTrajectory_latlon* &Clusters, std::vector<ref_time>& step_array);
    int getConvertedTraj(CabTrajectory* &CabTraj_converted, int size);
};