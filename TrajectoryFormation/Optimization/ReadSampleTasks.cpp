// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReadSampleTasks.h"


/*************************************************************************/
/// <b>Function: getClusters</b>
///
/// \param  
///
/// \return		Returns number of IDs
///
/// \remarks	This function  gets the total number of IDs in the dataset.
///              Medallion file is considered
/*************************************************************************/
int ReadSampleTasks::getSampleTasks(std::vector<Task>& SampleTasks)
{
    std::string strtemp;

    in_file.open(SampleTasksFilePath, std::ios::in);

    if (!in_file.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    in_file.seekg(std::ios::beg);

    std::getline(in_file, strtemp);
    if (1 != sscanf(strtemp.c_str(), "Total count of epoch = %d", &tot_epoch))
    {
        return EXIT_FAILURE;
    }

    while (std::getline(in_file, strtemp))
    {
        Task TempTask;
        char * pch = NULL;
        char * cstr = new char[strtemp.length() + 1];
        std::strcpy(cstr, strtemp.c_str());
        pch = std::strtok(cstr, ",");
        TempTask.lat = stoi(std::string(pch));
        pch = std::strtok(NULL, ",");
        TempTask.lon = stoi(std::string(pch));
        pch = std::strtok(NULL, ",");
        TempTask.idleTime = stof(std::string(pch)); 
        pch = std::strtok(NULL, ",");
        TempTask.epoch = stof(std::string(pch));

        SampleTasks.push_back(TempTask);

        delete[] cstr;
    }
    
    in_file.close();

    return EXIT_SUCCESS;
}
