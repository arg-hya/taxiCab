#pragma once
#include <vector>

#define INPUT_DIR  std::string("..\\Data\\")
#define OUTPUT_DIR  std::string("..\\Output\\")

#define BUDGET     20 

#define TIME_CONSTRAINT     10 
#define MIN_TASKPERCLUSTER     5
#define GREEDY_THRESHOLD     2

#define RANDOM(min, max)    min + rand() % (max - min + 1) //range : [min , max]
#define SQUARE(x)   x*x

struct CabTrajectory
{
    unsigned int lat = 0, lon = 0;
};

struct Cluster
{
    std::vector<unsigned int> CabIDs;
    std::vector<int> TaskIDs;
    CabTrajectory** Cabs;
    int cost;
    unsigned int spatcov;
};

struct Task
{
    unsigned int lat, lon;
    float idleTime;
    int epoch;
};

struct tempst
{
    int indx;
    float data;
};
