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

	int med_number = -1, temp = -1, line_count = 0, goodIdlePoints = 0;
	std::string med_name;
	std::string idle_name;
	std::string strtemp;
	std::map<int, int> mMap;
	std::map<int, int>::iterator itr;

	std::ifstream med_file("Data\\trip_data_1_cab_ids.txt", std::ios::in);
	std::ifstream idle_file("Data\\trip_data_1_idle_time.txt", std::ios::in);

	std::ofstream myfile("Output\\ID_IdleTime_freq.txt", std::ios::out);
	std::ofstream myfile2("Output\\numIdleTimes_dist.csv", std::ios::out);

	std::getline(med_file, med_name); 
	//line_count++;
	std::getline(idle_file, idle_name);

	while ((med_file >> temp) && (!med_file.eof()))
	{
		int idletime = 0;

		//line_count++;
		//GotoLine(idle_file, line_count);
		idle_file >> strtemp;
		if (!strtemp.empty())
		{			
			struct std::tm tm1 = { 0 };
			std::stringstream ss1;

			if ('-' == strtemp.at(0))	strtemp.erase(strtemp.begin());

			ss1 << strtemp;
			ss1 >> std::get_time(&tm1, "%H:%M:%S"); 
			idletime = (((tm1.tm_hour * 60) + tm1.tm_min) * 60) + tm1.tm_sec;
		}

		if (idletime <= min_idleTime)	continue;
		goodIdlePoints++;

		itr = mMap.find(temp);
		if (itr != mMap.end())
		{
			mMap[itr->first] ++;
		}
		else
		{
			mMap.insert(std::pair<int, int>(temp, 1));
		}
	}

	if (myfile.is_open() && myfile2.is_open())
	{
		int count = 0;
		myfile << "IDS , Count";
		myfile2 << "Good Points = " << goodIdlePoints << std::endl;
		for (itr = mMap.begin(); itr != mMap.end(); ++itr)
		{
			myfile << std::endl;
			myfile << count++ << "," << itr->second;

			if (itr != mMap.begin())myfile2 << ",";
			myfile2 << itr->second;
		}
	}
	else std::cout << "Unable to open file";

	/*std::cout << "IDS , Count";
	for (itr = mMap.begin(); itr != mMap.end(); ++itr)
	{
	std::cout << std::endl;
	std::cout << itr->first << "," << itr->second;
	}*/

	med_file.close();
	myfile.close();
	myfile2.close();

	return 0;
}

