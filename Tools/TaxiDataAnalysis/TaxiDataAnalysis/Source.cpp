// IdleTimeAnalysis.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>      // std::istringstream
#include <map>
#include <iomanip>      // std::get_time
#include <ctime>        // struct std::tm

#define min_idleTime	(30*60)

int GotoLine(std::ifstream& file, unsigned int num) {
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return 0;
}



int main()
{

	int med_number = -1, temp = -1, count = 0;
	std::string med_name;


	//struct std::tm tm1;
	//std::istringstream ss("16:35:12");
	//ss >> std::get_time(&tm1, "%H:%M:%S"); // or just %T in this case
	//std::time_t time = mktime(&tm1);
	std::ifstream med_file("Data\\trip_data_1_idle_time.txt", std::ios::in);



	std::getline(med_file, med_name);
	

	while ((med_file >> med_name) && (!med_file.eof()))
	{
		int idletime = 0;
		struct std::tm tm1 = {0};
		std::stringstream ss1;

		if ('-' == med_name.at(0))	med_name.erase(med_name.begin());
		
		ss1 << med_name;
		ss1 >> std::get_time(&tm1, "%H:%M:%S"); // or just %T in this case
		idletime = (((tm1.tm_hour * 60) + tm1.tm_min) * 60) + tm1.tm_sec;
		if (idletime >= min_idleTime)	count++;
		//std::cout << ss1.str();
		//ss1.str(std::string());
	}

	std::string line8;
	GotoLine(med_file, 4);
	med_file >> line8;
	std::cout << line8;


	med_file.close();

	return 0;
}

