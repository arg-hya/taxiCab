// TaxiDataAnalysis.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <map>


int main()
{
	int med_number = -1, temp = -1;
	std::string med_name;
	std::map<int, int> mMap;
	std::map<int, int>::iterator itr;

	std::ifstream med_file("Data\\trip_data_4_cab_ids.txt", std::ios::in);

	std::ofstream myfile("Output\\ID_freq.txt", std::ios::out);
	std::ofstream myfile2("Output\\numRides_dist.csv", std::ios::out);

	std::getline(med_file, med_name);

	while ((med_file >> temp) && (!med_file.eof()))
	{
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
		myfile2 << "Count" << std::endl;
		for (itr = mMap.begin(); itr != mMap.end(); ++itr)
		{
			myfile << std::endl;
			myfile << count++ << "," << itr->second;

			if(itr != mMap.begin())myfile2 << ",";
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

