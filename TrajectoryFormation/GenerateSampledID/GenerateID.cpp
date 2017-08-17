// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GenerateID.h"
//#include "Header.h"


/*************************************************************************/
/// <b>Function: GenerateID constructor</b>
///
/// \remarks	Constructor.
/*************************************************************************/
GenerateID::GenerateID(std::string rnd)
{
    rnd_dist = rnd;
    srand((unsigned int)time(NULL));	// initialize random seed	
}

/*************************************************************************/
/// <b>Function: OpenIDFileforReading</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function opend files
/*************************************************************************/
int GenerateID::OpenIDFileforReading()
{
    //Open input File
    in_med_file.open(IDFile, std::ios::in);

    if (!in_med_file.is_open())			//Files not opened properly
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*************************************************************************/
/// <b>Function: GenerateUniqueIDs</b>
///
/// \param  
///
/// \return		Returns number of IDs
///
/// \remarks	This function  gets the total number of IDs in the dataset.
///              Medallion file is considered
/*************************************************************************/
int GenerateID::GenerateUniqueIDs()
{
    int hresult = EXIT_SUCCESS, count;
    unsigned int value = 0;
    std::string strtemp;

    in_med_file.seekg(std::ios::beg);
    in_med_file >> strtemp;

    for (count = 0;; ++count)
    {
        if (in_med_file.eof())	break;

        in_med_file >> strtemp;
        value = stoi(strtemp);

        //Assuming the input file is sorted in non-decreasing way
        if (0 == count)
        {
            Unique_IDs.push_back(value);
            Unique_IDs_hitcount.push_back(0);
        }
        else
        {
            if (value > Unique_IDs.back())
            {
                Unique_IDs.push_back(value);
                Unique_IDs_hitcount.push_back(0);
            }
            else if (value == Unique_IDs.back())
            {
                Unique_IDs_hitcount[Unique_IDs_hitcount.size() - 1] ++;
            }
        }        
        /*if (std::find(Unique_IDs.begin(), Unique_IDs.end(), value) == Unique_IDs.end())
        {
            Unique_IDs.push_back(value);
        }*/
    }

    //Cabs with a minimum number of records should be considered
    if (Unique_IDs_hitcount.size() != Unique_IDs.size())
    {
        std::cout << "Unique_IDs_hitcount.size() != Unique_IDs.size()" << std::endl;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < Unique_IDs_hitcount.size(); i++)
    {
        if (Unique_IDs_hitcount[i] <= MIN_RECORDS_REQUIRED)
        {
            Unique_IDs.erase(Unique_IDs.begin() + i);
            Unique_IDs_hitcount.erase(Unique_IDs_hitcount.begin() + i);
        }
    }

     file_length = count;
    return hresult;
}

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
int GenerateID::getIDs(std::vector<unsigned int>& IDs)
{
    int hresult = EXIT_FAILURE, 
        numSamples = numIDs;

    //Open input File
    hresult = OpenIDFileforReading();
    if (EXIT_FAILURE == hresult)	return	EXIT_FAILURE;

    //Open input File
    hresult = GenerateUniqueIDs();
    if (EXIT_FAILURE == hresult)	return	EXIT_FAILURE;

    //Sort vector
    std::sort(Unique_IDs.begin(), Unique_IDs.end());

    int count = Unique_IDs.size();

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, count);
    std::normal_distribution<double> distribution1(1, count);

    while (0 != numSamples)
    {
        int temp_pos = -1;
        unsigned int value = 0;

        if ("uni_rand" == rnd_dist) temp_pos = distribution(generator);
        else temp_pos = floor(distribution1(generator)); 

        value = Unique_IDs[temp_pos -1];
		if (std::find(IDs.begin(), IDs.end(), value) == IDs.end())
		{
			IDs.push_back(value);
			numSamples--;
		}       
    }
    
    //Sort vector
    std::sort(IDs.begin(), IDs.end());

    in_med_file.close();

    return EXIT_SUCCESS;
}

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
int GenerateID::storeIDs(std::vector<unsigned int>& IDs)
{
    std::ofstream out_med_file;

    out_med_file.open(OutIDFile, std::ios::out);
    out_med_file << file_length << std::endl;

    for (std::vector<unsigned int>::iterator it = IDs.begin(); it != IDs.end(); ++it)
    {
        out_med_file << *it << std::endl;
    }
    
    out_med_file.close();

    return EXIT_SUCCESS;
}