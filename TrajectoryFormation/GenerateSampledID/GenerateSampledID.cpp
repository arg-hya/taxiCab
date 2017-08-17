// GenerateSampledID.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "GenerateID.h"

#define INPUT_DIR  std::string("..\\Data\\")

int main()
{
    /*IDs present from January are considered in unique ID generation*/
    std::vector<unsigned int> IDs;
    unsigned int file_length;
    try
    {
        GenerateID * GenID = new GenerateID("uni_rand");
        GenID->IDFile = INPUT_DIR + "1" + "\\trip_data_" + "1" + "_cab_ids.txt";
        GenID->OutIDFile = INPUT_DIR + "1" + "\\sampled.txt";
        GenID->numIDs = 5000;
        GenID->getIDs(IDs);
        GenID->storeIDs(IDs);
        file_length = GenID->file_length;

        delete GenID;
        GenID = NULL;
    }
    catch (...)
    {
        std::cout << "EXCEPTION <***UNEXPECTED***> caught in Function " << std::string(__func__) << " "
            << "at " << __LINE__ << " of " << __FILE__ << std::endl;
    }

   
    return 0;
}

