// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReadTrajectory.h"


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
int ReadTrajectory::getIDs(std::vector<unsigned int>& IDs)
{
    int count, file_length;
    std::string strtemp, strTempID, strtemp_path;

    in_IDfile.open(IDfilePath, std::ios::in);

    if (!in_IDfile.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    in_IDfile.seekg(std::ios::beg);

    for (count = 0;; ++count)
    {
        if (0 == count)
        {
            std::getline(in_IDfile, strtemp);
            //in_file >> strtemp;
            file_length = stoi(strtemp);
            continue;
        }

        std::getline(in_IDfile, strtemp);
        if (in_IDfile.eof())	break;
        //in_file >> strtemp;
        if (strtemp.empty())
        {
            std::cout << "Invalid Point";
            return EXIT_FAILURE;
        }
        IDs.push_back(stoi(strtemp));
    }

    return EXIT_SUCCESS;

}

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
int ReadTrajectory::getTrajecs(CabTrajectory** Cabs, std::vector<unsigned int>& IDs, int tot_epoch)
{
    int count;
    std::string strtemp, strTempID, strtemp_path;


    for (int i = 0; i < IDs.size(); i++)
    {
        std::string strtemp_path, strtemp_line;
        //unsigned int tempID;
        std::ifstream in_tempfile;

        strTempID = std::to_string(IDs[i]);
        std::cout << i << std::endl;
        //tempID = stoi(strTempID);
        strtemp_path = SampledTrajecFilesPath + strTempID + "_sampled.traj";

        in_tempfile.open(strtemp_path, std::ios::in);
        if (!in_tempfile.is_open())	continue;

        Cabs[i] = new CabTrajectory[tot_epoch];

        int j = 0;
        while (std::getline(in_tempfile, strtemp))
        {
            char * pch = NULL;
            char * cstr = new char[strtemp.length() + 1];
            std::strcpy(cstr, strtemp.c_str());
            pch = std::strtok(cstr, ",");   //idle time
            pch = std::strtok(NULL, ",");   //date and time
            pch = std::strtok(NULL, ",");
            Cabs[i][j].lat = stof(std::string(pch));
            pch = std::strtok(NULL, ",");
            Cabs[i][j].lon = stof(std::string(pch));

            j++;
            delete[] cstr;
        }
        in_tempfile.close();
    }

    return EXIT_SUCCESS;

}