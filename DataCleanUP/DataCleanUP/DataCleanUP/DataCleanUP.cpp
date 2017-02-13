// DataCleanUP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"


/*************************************************************************/
/// <b>Function: getNoPoints</b>
///
/// \param  
///
/// \return		Returns number of IDs
///
/// \remarks	This function  gets the total number of IDs in the dataset.
///              Medallion file is considered
/*************************************************************************/
int getNoPoints()
{
    int count;

    in_idle_file.seekg(std::ios::beg);
    for (count = 0;; ++count)
    {
        if (in_idle_file.eof())	break;
        in_idle_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    in_idle_file.seekg(std::ios::beg);

    return (count - 2);	//Ignoring first row and last blank line
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
int InitiateFileNames()
{
    //Opening files for reading
    filename_in_med_file = INPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_cab_ids.txt";
    filename_in_idle_file = INPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_idle_time.txt";
    filename_in_next_trip_start_datetime_file = INPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_next_trip_start_datetime.txt";
    filename_in_next_trip_start_location_file = INPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_next_trip_start_location.txt";
    filename_in_present_trip_end_datetime_file = INPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_present_trip_end_datetime.txt";
    filename_in_present_trip_end_location_file = INPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_present_trip_end_location.txt";

    filename_out_med_file = OUTPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_cab_ids.txt";
    filename_out_idle_file = OUTPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_idle_time.txt";
    filename_out_next_trip_start_datetime_file = OUTPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_next_trip_start_datetime.txt";
    filename_out_next_trip_start_location_file = OUTPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_next_trip_start_location.txt";
    filename_out_present_trip_end_datetime_file = OUTPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_present_trip_end_datetime.txt";
    filename_out_present_trip_end_location_file = OUTPUT_DIR + DATA_NUMBER + "\\trip_data_" + DATA_NUMBER + "_present_trip_end_location.txt";

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
int OpenFilesforReading()
{
    //Opening files for reading
    in_med_file.open(filename_in_med_file, std::ios::in);
    in_idle_file.open(filename_in_idle_file, std::ios::in);
    in_next_trip_start_datetime_file.open(filename_in_next_trip_start_datetime_file, std::ios::in);
    in_next_trip_start_location_file.open(filename_in_next_trip_start_location_file, std::ios::in);
    in_present_trip_end_datetime_file.open(filename_in_present_trip_end_datetime_file, std::ios::in);
    in_present_trip_end_location_file.open(filename_in_present_trip_end_location_file, std::ios::in);


    if (!in_med_file.is_open() || !in_idle_file.is_open() ||			//Files not opened properly
        !in_next_trip_start_datetime_file.is_open() || !in_next_trip_start_location_file.is_open() ||
        !in_present_trip_end_datetime_file.is_open() || !in_present_trip_end_location_file.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*************************************************************************/
/// <b>Function: OpenFilesforWriting</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function opend files
/*************************************************************************/
int OpenFilesforWriting()
{
    ////Creating directory
    //CreateDirectory(L"Output", NULL);

    //Opening files for reading
    out_med_file.open(filename_out_med_file, std::ios::out);
    out_idle_file.open(filename_out_idle_file, std::ios::out);
    out_next_trip_start_datetime_file.open(filename_out_next_trip_start_datetime_file, std::ios::out);
    out_next_trip_start_location_file.open(filename_out_next_trip_start_location_file, std::ios::out);
    out_present_trip_end_datetime_file.open(filename_out_present_trip_end_datetime_file, std::ios::out);
    out_present_trip_end_location_file.open(filename_out_present_trip_end_location_file, std::ios::out);


    if (!out_med_file.is_open() || !out_idle_file.is_open() ||			//Files not opened properly
        !out_next_trip_start_datetime_file.is_open() || !out_next_trip_start_location_file.is_open() ||
        !out_present_trip_end_datetime_file.is_open() || !out_present_trip_end_location_file.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
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
int CloseFilesforReading()
{
    //Closing Files
    in_med_file.close();
    in_idle_file.close();
    in_next_trip_start_datetime_file.close();
    in_next_trip_start_location_file.close();
    in_present_trip_end_datetime_file.close();
    in_present_trip_end_location_file.close();

    return EXIT_SUCCESS;
}

/*************************************************************************/
/// <b>Function: CloseFilesforWriting</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function closes files
/*************************************************************************/
int CloseFilesforWriting()
{
    //Closing Files
    out_med_file.close();
    out_idle_file.close();
    out_next_trip_start_datetime_file.close();
    out_next_trip_start_location_file.close();
    out_present_trip_end_datetime_file.close();
    out_present_trip_end_location_file.close();

    return EXIT_SUCCESS;
}

/*************************************************************************/
/// <b>Function: PerformFileIO</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function does creates the sampled files
/*************************************************************************/
int PerformFileIO()
{
    int hresult = EXIT_FAILURE;
    std::string strtemp;;
    std::string strtemp_s;
    std::string strtemp_n;

    /*For the first line*/
    //For med_file
    in_med_file >> strtemp;
    out_med_file << strtemp << std::endl;
    //For idle_file
    in_idle_file >> strtemp;
    out_idle_file << strtemp << std::endl;
    //For next_trip_start_datetime_file
    //in_next_trip_start_datetime_file >> strtemp;
    //out_next_trip_start_datetime_file << strtemp << " ";
    in_next_trip_start_datetime_file >> strtemp;
    out_next_trip_start_datetime_file << strtemp << std::endl;
    //For next_trip_start_location_file
    in_next_trip_start_location_file >> strtemp;
    out_next_trip_start_location_file << strtemp << std::endl;
    //For present_trip_end_datetime_file
    //in_present_trip_end_datetime_file >> strtemp;
    //out_present_trip_end_datetime_file << strtemp << " ";
    in_present_trip_end_datetime_file >> strtemp;
    out_present_trip_end_datetime_file << strtemp << std::endl;
    //For present_trip_end_location_file
    in_present_trip_end_location_file >> strtemp;
    out_present_trip_end_location_file << strtemp << std::endl;

    for (unsigned int i = 0; i < noPoints; i++)
    {
        bool bAllGood = true;
        int pos_start, pos_next;

        /*Unwanted data check START::*/
        pos_start = in_next_trip_start_location_file.tellg();
        strtemp_s.clear();
        std::getline(in_next_trip_start_location_file, strtemp_s, ',');
        if ('\n' == strtemp_s.at(0)) strtemp_s.erase(strtemp_s.begin());
        if ('-' == strtemp_s.at(0))	strtemp_s.erase(strtemp_s.begin());
        if ((stof(strtemp_s) < MIN_LONGITUDE) || (stof(strtemp_s) > MAX_LONGITUDE))
        {
            bAllGood = false;
        }
        double xdiff = 40.958122 - 40.715393;
        double ydiff = 73.926315 - 74.195487;
        double y = stof(strtemp_s);        
        
        strtemp_s.clear();
        std::getline(in_next_trip_start_location_file, strtemp_s, '\n');
        if (stof(strtemp_s) < MIN_LATITUDE || (stof(strtemp_s) > MAX_LATITUDE))
        {
            bAllGood = false;
        }
        double x = stof(strtemp_s);
        double side = (x - 40.715393)*ydiff - (y - 74.195487)*xdiff;
        if (side < 0)
        {
            bAllGood = false;
        }

        strtemp_n.clear();
        pos_next = in_present_trip_end_location_file.tellg();
        std::getline(in_present_trip_end_location_file, strtemp_n, ',');
        if ('\n' == strtemp_n.at(0)) strtemp_n.erase(strtemp_n.begin());
        if ('-' == strtemp_n.at(0))	strtemp_n.erase(strtemp_n.begin());
        if ((stof(strtemp_n) < MIN_LONGITUDE) || (stof(strtemp_n) > MAX_LONGITUDE))
        {
            bAllGood = false;
        }
        y = stof(strtemp_s);

        strtemp_n.clear();
        std::getline(in_present_trip_end_location_file, strtemp_n, '\n');
        if (stof(strtemp_n) < MIN_LATITUDE || (stof(strtemp_n) > MAX_LATITUDE))
        {
            bAllGood = false;
        }

        x = stof(strtemp_s);
        side = (x - 40.715393)*ydiff - (y - 74.195487)*xdiff;
        if (side < 0)
        {
            bAllGood = false;
        }

        if (bAllGood == false)
        {
            in_med_file >> strtemp;
            in_idle_file >> strtemp;
            in_next_trip_start_datetime_file >> strtemp;
            in_next_trip_start_datetime_file >> strtemp;
            in_present_trip_end_datetime_file >> strtemp;
            in_present_trip_end_datetime_file >> strtemp;
            continue;
        }
        /*Unwanted data check END::*/
        in_next_trip_start_location_file.seekg(std::ios::beg);
        in_present_trip_end_location_file.seekg(std::ios::beg);
        in_next_trip_start_location_file.seekg(pos_start);
        in_present_trip_end_location_file.seekg(pos_next);
        //For med_file
        in_med_file >> strtemp;
        out_med_file << strtemp << std::endl;
        //For idle_file
        in_idle_file >> strtemp;
        out_idle_file << strtemp << std::endl;
        //For next_trip_start_datetime_file
        in_next_trip_start_datetime_file >> strtemp;
        out_next_trip_start_datetime_file << strtemp << " ";
        in_next_trip_start_datetime_file >> strtemp;
        out_next_trip_start_datetime_file << strtemp << std::endl;
        //For next_trip_start_location_file
        in_next_trip_start_location_file >> strtemp;
        out_next_trip_start_location_file << strtemp << std::endl;
        //For present_trip_end_datetime_file
        in_present_trip_end_datetime_file >> strtemp;
        out_present_trip_end_datetime_file << strtemp << " ";
        in_present_trip_end_datetime_file >> strtemp;
        out_present_trip_end_datetime_file << strtemp << std::endl;
        //For present_trip_end_location_file
        in_present_trip_end_location_file >> strtemp;
        out_present_trip_end_location_file << strtemp << std::endl;
    }


    return EXIT_SUCCESS;
}

int main()
{    
    InitiateFileNames();
    OpenFilesforReading();
    OpenFilesforWriting();

    noPoints = getNoPoints();

    PerformFileIO();

    CloseFilesforReading();
    CloseFilesforWriting();

    return 0;
}

