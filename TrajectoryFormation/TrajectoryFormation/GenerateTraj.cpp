// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GenerateTraj.h"
//#include "Header.h"

/*************************************************************************/
/// <b>Function: GenerateID constructor</b>
///
/// \remarks	Constructor.
/*************************************************************************/
GenerateTraj::GenerateTraj(std::vector<unsigned int>& one, std::vector<int>& two, unsigned int file_length)
{
    std::string g = INPUT_DIR + "1" + "\\sampled.txt";
	std::string gout = "sampled.txt";
    GenerateTraj::file_length = file_length;
    GenerateTraj::IDs = one;
    GenerateTraj::FilePrefixes = two;
    unsigned int size = IDs.size();
    GenerateTraj::out_files_array = new points[size];
}

/*************************************************************************/
/// <b>Function: GotoLine</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function makes the file pointer go to a specific location.
/*************************************************************************/
int GenerateTraj::GotoLine(std::ifstream& file, unsigned int num) {
   // file.seekg(std::ios::beg);
    for (int i = 0; i < num - 1; ++i) {
        if (file.eof())	return EXIT_FAILURE;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return EXIT_SUCCESS;
}

/*************************************************************************/
/// <b>Function: OpenFilesforReading</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function opend files
/*************************************************************************/
int GenerateTraj::InitiateFileNames(int tempPrefix)
{
    //Opening files for reading
    filename_in_med_file = INPUT_DIR1 + std::to_string(tempPrefix) + "\\trip_data_" + std::to_string(tempPrefix) + "_cab_ids.txt";
    filename_in_idle_file = INPUT_DIR1 + std::to_string(tempPrefix) + "\\trip_data_" + std::to_string(tempPrefix) + "_idle_time.txt";
    filename_in_present_trip_end_datetime_file = INPUT_DIR1 + std::to_string(tempPrefix) + "\\trip_data_" + std::to_string(tempPrefix) + "_present_trip_end_datetime.txt";
    filename_in_present_trip_end_location_file = INPUT_DIR1 + std::to_string(tempPrefix) + "\\trip_data_" + std::to_string(tempPrefix) + "_present_trip_end_location.txt";

    return EXIT_SUCCESS;
}

/*************************************************************************/
/// <b>Function: OpenFilesforReading</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function opend files
/*************************************************************************/
int GenerateTraj::OpenFilesforReading()
{

    in_med_file.open(filename_in_med_file, std::ios::in);
    in_idle_file.open(filename_in_idle_file, std::ios::in);
    in_present_trip_end_datetime_file.open(filename_in_present_trip_end_datetime_file, std::ios::in);
    in_present_trip_end_location_file.open(filename_in_present_trip_end_location_file, std::ios::in);


    if (!in_med_file.is_open() || !in_idle_file.is_open() ||			//Files not opened properly
        !in_present_trip_end_datetime_file.is_open() || !in_present_trip_end_location_file.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*************************************************************************/
/// <b>Function: WriteTrajtoFiles</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function opend files
/*************************************************************************/
int GenerateTraj::WriteTrajtoFiles()
{
	std::string filename;	
	unsigned int size = IDs.size();

	for (unsigned int i = 0; i < size; i++)
	{
		if (0 == out_files_array[i].count) continue;
		filename = OUTPUT_DIR + std::to_string(IDs[i]) + "_trajectory.traj";
		out_file.open(filename,std::ios::app);
		for (unsigned int j = 0; j < out_files_array[i].count; j++)
		{
			out_file << out_files_array[i].idle_time[j] << ",";
			out_file << out_files_array[i].date_time_1[j] << " " << out_files_array[i].date_time_2[j] << ",";
			out_file << out_files_array[i].loc[j] << "\n";
		}
		if(0 != out_files_array[i].count)
		{
			out_files_array[i].idle_time.clear();
			out_files_array[i].date_time_1.clear();
			out_files_array[i].date_time_2.clear();
			out_files_array[i].loc.clear();
			out_files_array[i].count = 0;
		}
		out_file.close();
	}


    return EXIT_SUCCESS;
}
/*************************************************************************/
/// <b>Function: CloseFilesforReading</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function closes files
/*************************************************************************/
int GenerateTraj::CloseFilesforReading()
{
    //Closing Files
    in_med_file.close();
    in_idle_file.close();
    in_present_trip_end_datetime_file.close();
    in_present_trip_end_location_file.close();

    return EXIT_SUCCESS;
}




/*************************************************************************/
/// <b>Function: GotoLine</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function makes the file pointer go to a specific location.
/*************************************************************************/
int GenerateTraj::getStartandEndLine(unsigned int& tempID, unsigned int& strat, unsigned int& end, bool firsttime)
{
    unsigned int value;
    std::string strtemp;
    int pos,pos1;
    old_strat = strat;
    old_end = end;

    pos1 = in_med_file.tellg();

    if (firsttime)
    {
        old_end = 1;
        std::getline(in_med_file, strtemp);
        std::getline(in_idle_file, strtemp);
        std::getline(in_present_trip_end_datetime_file, strtemp);
        std::getline(in_present_trip_end_location_file, strtemp);
    }

    for (int i = old_end + 1; i <= file_length; ++i)
    {     
        if (in_med_file.eof())	break;

        pos = in_med_file.tellg();
        std::getline(in_med_file, strtemp);// in_med_file >> strtemp;
        //if ("" == strtemp) break;

        value = stoi(strtemp);

        if (tempID == value)
        {
            if (old_strat == strat)
            {
                strat = i;
                end = i;
            }
            else
            {
                end = i;
                // break;
            }
        }
        else
        {
            if ((old_strat != strat) || (tempID < value))
            {
                break;
            }
        }
    }

    

    if (old_strat != strat)
    {
        in_med_file.seekg(pos, in_med_file.beg);
        for (unsigned int i = 1; i < (strat - old_end); i++)
        {
            in_idle_file >> strtemp;
            in_present_trip_end_datetime_file >> strtemp;
            in_present_trip_end_datetime_file >> strtemp;
            in_present_trip_end_location_file >> strtemp;
        }
        return EXIT_SUCCESS;
    }
    else
    {
        in_med_file.seekg(pos1, in_med_file.beg);
    }
    //old_end = end;

    return EXIT_FAILURE;
}

/*************************************************************************/
/// <b>Function: GotoLine</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function makes the file pointer go to a specific location.
/*************************************************************************/
int GenerateTraj::copyBlockfromAll(unsigned int j, unsigned int strat, unsigned int end)
{
    int hresult = EXIT_FAILURE;
    std::string strtemp;;


    for (unsigned int i = 0; i <= (end - strat); i++)
    {
        //For idle_file

        in_idle_file >> strtemp;
        if (strtemp.empty())
        {
            std::cout << "Invalid Point";
            return hresult;
        }
		out_files_array[j].idle_time.push_back(strtemp) ;

        //For present_trip_end_datetime_file

        in_present_trip_end_datetime_file >> strtemp;
        if (strtemp.empty())
        {
            std::cout << "Invalid Point";
            return hresult;
        }
		out_files_array[j].date_time_1.push_back(strtemp);
        in_present_trip_end_datetime_file >> strtemp;
        if (strtemp.empty())
        {
            std::cout << "Invalid Point";
            return hresult;
        }
		out_files_array[j].date_time_2.push_back(strtemp);

        //For present_trip_end_location_file

        in_present_trip_end_location_file >> strtemp;
        if (strtemp.empty())
        {
            std::cout << "Invalid Point";
            return hresult;
        }
		out_files_array[j].loc.push_back(strtemp);

		out_files_array[j].count++;
    }

   // out_files[j] << std::endl;
    
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
int GenerateTraj::generatetTrajectories()
{
    int tempPrefix = 0, hresult;
    unsigned int tempID = 0, strat = 0, end = 0;

    //OpenFilesforWriting();

    for (int i = 0; i < FilePrefixes.size(); i++)
    {
        tempID = 0, strat = 0, end = 0;

        tempPrefix = FilePrefixes[i];
        InitiateFileNames(tempPrefix);
        OpenFilesforReading();
        in_med_file.seekg(std::ios::beg);
        for (int j = 0; j < IDs.size(); j++)
        {
			if ((j % 1000) == 0)
			{
				WriteTrajtoFiles();
			}
			//std::cout << j  << std::endl;
            tempID = IDs[j];                  

            hresult = getStartandEndLine(tempID, strat, end, (!strat ? true : false ));

            if ((strat != end) && (EXIT_SUCCESS == hresult))
                copyBlockfromAll(j , strat, end);

            //Debug
            if (0 == out_files_array[j].count)
                std::cout << IDs[j] << std::endl;
        }
		WriteTrajtoFiles();
        CloseFilesforReading();
    }

    


    return EXIT_SUCCESS;
}
