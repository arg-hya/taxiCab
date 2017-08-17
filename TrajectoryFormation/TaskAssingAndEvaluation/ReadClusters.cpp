// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReadClusters.h"


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
int ReadClusters::getClusters(Cluster* &Clusters)
{
    std::string strtemp;

    in_file.open(ClusterFilePath, std::ios::in);

    if (!in_file.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    in_file.seekg(std::ios::beg); 

    std::getline(in_file, strtemp);
    count = stoi(strtemp);
    Clusters = new Cluster[count];

    std::getline(in_file, strtemp);
    tot_epoch = stoi(strtemp);

    for (int i = 0; i < count ; i++)
    {

        std::getline(in_file, strtemp);

        char * pch = NULL;
        char * cstr = new char[strtemp.length() + 1];
        std::strcpy(cstr, strtemp.c_str());
        pch = std::strtok(cstr, " ");

        while (pch != NULL)
        {
            Clusters[i].CabIDs.push_back(stoi(std::string(pch)));
            pch = std::strtok(NULL, " ");
        }
        delete[] cstr;

        std::getline(in_file, strtemp);
        Clusters[i].TrajCentroid = new CabTrajectory[tot_epoch];

        pch = NULL;
        cstr = new char[strtemp.length() + 1];
        std::strcpy(cstr, strtemp.c_str());
        pch = std::strtok(cstr, " ");

        int k = 0;
        do
        {
            Clusters[i].TrajCentroid[k].lat = stoi(std::string(pch));
            pch = std::strtok(NULL, " ");
            if (pch != NULL)
            {
                Clusters[i].TrajCentroid[k++].lon = stoi(std::string(pch));
            }
            pch = std::strtok(NULL, " ");
        }while (pch != NULL);
        delete[] cstr;
    }
    in_file.close();

    return EXIT_SUCCESS;
}
