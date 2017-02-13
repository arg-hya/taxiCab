// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReadIDs.h"


/*************************************************************************/
/// <b>Function: getIDs</b>
///
/// \param  
///
/// \return		Returns number of IDs
///
/// \remarks	This function  gets the total number of IDs in the dataset.
///              Medallion file is considered
/*************************************************************************/
int ReadIDs::getIDs(std::vector<unsigned int>& IDs, unsigned int &file_length)
{
    int count;
    std::string strtemp;

    in_file.open(IDFile,std::ios::in);

    if (!in_file.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    in_file.seekg(std::ios::beg);

    for (count = 0;; ++count)
    {
        if (0 == count)
        {
            std::getline(in_file, strtemp);
            //in_file >> strtemp;
            file_length = stoi(strtemp);
            continue;
        }

        std::getline(in_file, strtemp);
        if (in_file.eof())	break;
        //in_file >> strtemp;
        if (strtemp.empty())
        {
            std::cout << "Invalid Point";
            return EXIT_FAILURE;
        }
        IDs.push_back(stoi(strtemp));
    }

    in_file.close();

    return EXIT_SUCCESS;
}
