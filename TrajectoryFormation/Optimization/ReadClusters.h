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

class ReadClusters
{
private:
    std::ifstream in_file;
public:
    int count;
    std::string ClusterFilePath;
    int getClusters(Cluster* &Clusters);
};