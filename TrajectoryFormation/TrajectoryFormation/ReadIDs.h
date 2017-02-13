#pragma once

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	/* find */
#include <fstream>
#include <vector>
#include <string>
#include <random>


class ReadIDs
{
private:
    std::ifstream in_file;
public:
    std::string IDFile;
    int getIDs(std::vector<unsigned int>& IDs, unsigned int &file_length);
};