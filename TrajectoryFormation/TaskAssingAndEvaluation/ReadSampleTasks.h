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

class ReadSampleTasks
{
private:
    std::ifstream in_file;
public:
    int tot_epoch;
    std::string SampleTasksFilePath;
    int getSampleTasks(std::vector<Task>& SampleTasks);
};