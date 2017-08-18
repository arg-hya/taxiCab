// TrajSplit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include "ReadIDs.h"

#define INPUT_DIR  std::string("..\\Data\\")
#define OUTPUT_DIR  std::string("..\\Output\\")
#define ALLTRAJECS  std::string("..\\..\\TraNodeCreator\\")

struct CabTrajectory
{
	unsigned int lat = 0, lon = 0;
};

int main()
{
	int tot_epoch = 0, tot_cabs = 0, temp, count;
	std::vector<int> split_interval;
	std::string SampledTrajecFilesPath, strtemp;
	std::ifstream in_file;
	int** Cabs = NULL;

	/*IDs present from January are considered in unique ID generation*/
	std::vector<unsigned int> IDs;
	unsigned int file_length;
	try
	{
		tot_epoch = 720;

		ReadIDs * ReadID = new ReadIDs();
		ReadID->IDFile = INPUT_DIR + "1" + "\\sampled.txt";
		ReadID->getIDs(IDs, file_length);
		delete ReadID;
		ReadID = NULL;

		SampledTrajecFilesPath = ALLTRAJECS + "AllTrajecsNopePoints.data";
		in_file.open(SampledTrajecFilesPath, std::ios::in);
		Cabs = new int*[IDs.size()];
		
		count = 0;
		while (std::getline(in_file, strtemp))
		{
			int k = 0;
			char * pch = NULL;
			char * cstr = new char[strtemp.length() + 1];
			std::strcpy(cstr, strtemp.c_str());
			pch = std::strtok(cstr, " ");
			Cabs[count] = new int[tot_epoch];
			Cabs[count][k++] = stoi(std::string(pch));
			while (pch = std::strtok(NULL, " "))
			{
				Cabs[count][k++] = stoi(std::string(pch));
			}
			count++;
		}

		in_file.close();

		/*for (size_t i = 0; i < IDs.size(); i++)
		{
			for (size_t k = 0; k < tot_epoch; k++)
			{
				std::cout << Cabs[i][k++] << " ";
			}
			std::cout << std::endl << "NEW" << std::endl;
		}*/
		/*ReadTrajectory* ReadTrajec = new ReadTrajectory();
		ReadTrajec->IDfilePath = INPUT_DIR + "1\\" + "sampled.txt";
		ReadTrajec->SampledTrajecFilesPath = OUTPUT_DIR + "Sampled_Trajecs\\";
		ReadTrajec->getIDs(IDs);
		Cabs = new CabTrajectory*[IDs.size()];
		ReadTrajec->getTrajecs(Cabs, IDs, tot_epoch);
		tot_cabs = IDs.size();*/
		

		//Populate interval
		for (temp = 200; temp < tot_epoch; temp +=200)
		{
			split_interval.push_back(200);
		}
		temp -= 200;
		temp = tot_epoch - temp;
		split_interval.push_back(temp);

		int count = 0, start_time = 0;
		for (std::vector<int>::iterator it = split_interval.begin(); it != split_interval.end(); ++it)
		{			
			count++;
			//for (size_t i = 0; i < *it; i++)
			//{
				for (int k = 0; k < IDs.size(); k++)
				{
					std::ofstream output_file;
					std::string output_file_path = OUTPUT_DIR + "Sampled_Trajecs\\Split\\" + std::to_string(IDs[k]) + "_"+ 
						std::to_string(count) + "_.traj";

					output_file.open(output_file_path, std::ios::out);

					if (!output_file.is_open())
					{
						std::cout << "File not opening for reading" << std::endl;
						return EXIT_FAILURE;
					}
					//output_file << "Split number :: " << count << std::endl;
					for (size_t i = 0; i < *it; i++)
					{
						output_file << Cabs[k][start_time + i] << std::endl;
					}
					output_file.close();
				}
			//}
				start_time += *it;
				//end_time += start_time
		}
	}
	catch (...)
	{
		std::cout << "EXCEPTION <***UNEXPECTED***> caught in Function " << std::string(__func__) << " "
			<< "at " << __LINE__ << " of " << __FILE__ << std::endl;
	}

    return 0;
}

