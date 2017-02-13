#pragma once

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	/* find */
#include <fstream>
#include <vector>
#include <string>
#include <sstream>      // std::istringstream


//#include <windows.h>	/*CreateDirectory*/


#define MIN_LONGITUDE	73.6 
#define MAX_LONGITUDE	74.3 
#define MIN_LATITUDE	40.5
#define MAX_LATITUDE	41.0

#define INPUT_DIR  std::string("Data\\")
#define OUTPUT_DIR  std::string("Output\\")
#define DATA_NUMBER  "8"

unsigned int noPoints = 0;

//File pointer names
std::string filename_in_med_file;
std::string filename_in_idle_file;
std::string filename_in_next_trip_start_datetime_file;
std::string filename_in_next_trip_start_location_file;
std::string filename_in_present_trip_end_datetime_file;
std::string filename_in_present_trip_end_location_file;

std::string filename_out_med_file;
std::string filename_out_idle_file;
std::string filename_out_next_trip_start_datetime_file;
std::string filename_out_next_trip_start_location_file;
std::string filename_out_present_trip_end_datetime_file;
std::string filename_out_present_trip_end_location_file;

std::ifstream in_med_file;
std::ifstream in_idle_file;
std::ifstream in_next_trip_start_datetime_file;
std::ifstream in_next_trip_start_location_file;
std::ifstream in_present_trip_end_datetime_file;
std::ifstream in_present_trip_end_location_file;

std::ofstream out_med_file;
std::ofstream out_idle_file;
std::ofstream out_next_trip_start_datetime_file;
std::ofstream out_next_trip_start_location_file;
std::ofstream out_present_trip_end_datetime_file;
std::ofstream out_present_trip_end_location_file;