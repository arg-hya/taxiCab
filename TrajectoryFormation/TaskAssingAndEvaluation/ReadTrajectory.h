#pragma once

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	/* find */
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include "Header.h"

class ReadTrajectory
{
private:
    std::ifstream in_file;
    std::ifstream in_IDfile;
    
public:    
    std::string IDfilePath;
    std::string SampledTrajecFilesPath;
    int getIDs(std::vector<unsigned int>& IDs);
    int getTrajecs(CabTrajectory** Cabs, std::vector<unsigned int>& IDs, int tot_epoch);
};