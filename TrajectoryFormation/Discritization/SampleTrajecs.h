#pragma once

#include <iostream>
//#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	/* find */
#include <fstream>
#include <vector>
////#include <limits>
#include <string>
//#include <random>
#include <sstream>      // std::istringstream
#include <iomanip>      // std::get_time
#include "Header.h"

class SampleTrajecs
{


private:
    /*=================
    GLOBAL VARIABLES :
    =================*/
   
    std::vector<int> FilePrefixes;
    points* out_files_array;
    // std::ofstream* out_files;
    unsigned int  old_strat, old_end, file_length;
    std::vector<points*> cab_trajecs;
   

    std::ofstream out_file;
 

    /*=================
    FUNC PROTOTYPES :
    =================*/
    int comparetime(time_t time1, time_t time2);
    int WriteSampledTrajecs();
    

public:
    std::vector<time_t> step_array;
    std::vector<unsigned int> IDs;
    //File pointer names
    std::string outputpath;
    std::string IDfilePath;
    SampleTrajecs(std::vector<time_t>& step_array);
    int SampleIt(std::vector<std::vector<points>> Trajecs);
};
