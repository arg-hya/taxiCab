#pragma once
#include <vector>
#include <time.h>

#define time_t unsigned int

#define INPUT_DIR  std::string("..\\..\\Data\\")
#define OUTPUT_DIR  std::string("..\\Output\\")

#define BUDGET     20 

#define TIME_CONSTRAINT     10 
#define MIN_TASKPERCLUSTER     5
#define GREEDY_THRESHOLD     5

#define RANDOM(min, max)    min + rand() % (max - min + 1) //range : [min , max]
#define SQUARE(x)   x*x

struct CabTrajectory_latlon
{
   unsigned int lat;
   unsigned int lon;
};

struct CabTrajectory
{
    int node_point;
};

struct Cluster
{
    CabTrajectory* TrajCentroid;
};


struct ref_time
{
    time_t t;
    int i;
};

struct points
{
    std::string idle_time;
    std::string date_time_1;
    std::string date_time_2;
    std::string lon;
    std::string lat;
};
