#pragma once

#include <iostream>
#include <algorithm>	/* find */
#include <fstream>
#include <vector>

#include <string>

//
#define INPUT_DIR  std::string("..\\Data\\")
#define OUTPUT_DIR  std::string("..\\Output\\")
#define INPUT_DIR1  INPUT_DIR



class GenerateTraj
{
	struct points
	{
		std::vector<std::string> idle_time;
		std::vector<std::string> date_time_1;
		std::vector<std::string> date_time_2;
		std::vector<std::string> loc;
		unsigned int count = 0;
	};

private:
    /*=================
    GLOBAL VARIABLES :
    =================*/
    std::vector<unsigned int> IDs;
    std::vector<int> FilePrefixes;
	points* out_files_array;
    unsigned int  old_strat, old_end, file_length;


    //File pointer names
    std::string filename_in_med_file;
    std::string filename_in_idle_file;
    std::string filename_in_present_trip_end_datetime_file;
    std::string filename_in_present_trip_end_location_file;


    std::ifstream in_med_file;
    std::ifstream in_idle_file;
    std::ifstream in_present_trip_end_datetime_file;
    std::ifstream in_present_trip_end_location_file;

    std::ofstream out_file;


    /*=================
    FUNC PROTOTYPES :
    =================*/

    int GotoLine(std::ifstream& file, unsigned int num);
    int InitiateFileNames(int tempPrefix);
    int OpenFilesforReading();
    int WriteTrajtoFiles();
    int CloseFilesforReading();


    int getStartandEndLine(unsigned int& tempID, unsigned int& strat, unsigned int& end, bool firsttime);
    int copyBlockfromAll(unsigned int j, unsigned int strat, unsigned int end);


public:
    GenerateTraj(std::vector<unsigned int>& one, std::vector<int>& two, unsigned int file_length);
    int generatetTrajectories();
};
