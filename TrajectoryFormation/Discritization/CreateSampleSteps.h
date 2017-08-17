#pragma once

#include <iostream>

#include <algorithm>	/* find */
#include <fstream>
#include <vector>

#include <string>
#include <iomanip>      // std::get_time
#include <sstream>    

#include <random>
#include "Header.h"

class CreateSampleSteps
{


private:
    /*=================
    GLOBAL VARIABLES :
    =================*/
         std::vector<time_t>* points;
    std::vector<int> FilePrefixes;
   // points* out_files_array;
    std::ifstream in_IDfile;
    unsigned int file_length;

    std::ofstream out_file;
    std::ofstream out_file_forClustering;

    /*=================
    FUNC PROTOTYPES :
    =================*/
        int MakeNumerical(std::string& str);
    int comparetime(time_t time1, time_t time2);
        int GetAllIDs();
        time_t mktime_override(struct tm tm1);
        int PopulatePointsperHr();
        time_t makeTime(std::string strtemp);

public:
    //File pointer names
        std::string IDfilePath;
        int numSampleIDs;
        std::vector<unsigned int> SampleIDs;
        std::vector<unsigned int> IDs;
        std::vector <ref_time> step_array;
        int getTrajecs();
};
