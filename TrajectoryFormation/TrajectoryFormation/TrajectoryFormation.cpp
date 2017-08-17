// TrajectoryFormation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include "ReadIDs.h"
#include "GenerateTraj.h"

#define INPUT_DIR  std::string("..\\Data\\")

int main()
{ 
    /*IDs present from January are considered in unique ID generation*/
    std::vector<unsigned int> IDs;
    unsigned int file_length;
    try
    {
        ReadIDs * ReadID = new ReadIDs();
        ReadID->IDFile = INPUT_DIR + "1" + "\\sampled.txt";
        ReadID->getIDs(IDs, file_length);
        delete ReadID;
        ReadID = NULL;
    }
    catch (...)
    {
        std::cout << "EXCEPTION <***UNEXPECTED***> caught in Function " << std::string(__func__) << " "
            << "at " << __LINE__ << " of " << __FILE__ << std::endl;
    }

    std::vector<int> FilePrefixes;
    FilePrefixes.push_back(1);
    //FilePrefixes.push_back(2);

   // try
   // {
        GenerateTraj* GenTr = new GenerateTraj(IDs, FilePrefixes, file_length);
       // GenTr->IDs = IDs;
       // GenTr->FilePrefixes = FilePrefixes;
        GenTr->generatetTrajectories();

        delete GenTr;
        GenTr = NULL;
    //}
    //catch (...)
    //{
    //    std::cout << "EXCEPTION <***UNEXPECTED***> caught in Function " << std::string(__func__) << " "
    //        << "at " << __LINE__ << " of " << __FILE__ << std::endl;
    //}


        return 0;
}

