#pragma once

#pragma once

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	/* find */
#include <fstream>
#include <vector>

#include <string>
#include <random>

#define MIN_RECORDS_REQUIRED 10

class GenerateID
{
private:
    /*=================
    GLOBAL VARIABLES :
    =================*/   
    std::string rnd_dist;
    std::vector<unsigned int> Unique_IDs;
    std::vector<int> Unique_IDs_hitcount;
    
    std::ifstream in_med_file;
    
    /*=================
    FUNC PROTOTYPES :
    =================*/
  
    int OpenIDFileforReading();
    int GenerateUniqueIDs();
 
public:
    unsigned int numIDs;				//Number of IDs to get
    std::string IDFile;
    std::string OutIDFile;
    unsigned int file_length;;
 
    GenerateID(std::string rnd);
  
    int getIDs(std::vector<unsigned int>& IDs);
    int storeIDs(std::vector<unsigned int>& IDs);
};