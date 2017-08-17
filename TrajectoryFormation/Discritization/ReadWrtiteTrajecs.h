#pragma once

#include <iostream>

#include <algorithm>	/* find */
#include <fstream>
#include <vector>

#include <string>
#include <iomanip>      // std::get_time
#include <sstream>    

#include "Header.h"

class ReadWrtiteTrajecs
{


private:
	/*=================
	GLOBAL VARIABLES :
	=================*/	
	std::vector<int> FilePrefixes;
	points* out_files_array;
    std::ifstream in_IDfile;
    unsigned int file_length;

	std::ofstream out_file;
    std::ofstream out_file_forClustering;

	/*=================
	FUNC PROTOTYPES :
	=================*/
    int MakeNumerical(std::string& str);
	int comparetime(time_t time1, time_t time2);
	int WriteSampledTrajecs(int ID, bool* fillarray, int fillarray_size, std::vector<points> temp_points);
    time_t mktime_override(struct tm tm1);
    int ConvertGeoPosTo2D(std::string& lat, std::string& lon);

public:
	//File pointer names
	std::string path; 
	std::string IDfilePath;
    std::string AllTrajecspath;
    std::vector<unsigned int> IDs;
    bool ConvertPosTo2D = false;
	int getTrajecs(points** Trajecs, std::vector<ref_time>& step_array);
};
