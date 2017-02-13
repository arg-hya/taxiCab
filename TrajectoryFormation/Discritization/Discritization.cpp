// Discritization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream> 
#include <vector>

#include "CreateSampleSteps.h"
#include "ReadWrtiteTrajecs.h"
#include "SampleTrajecs.h"
#include "Header.h"

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	mktime_override.
/*************************************************************************/
time_t mktime_override(struct tm tm1)
{
    time_t sec = tm1.tm_sec + (tm1.tm_min + tm1.tm_hour * 60) * 60;
    time_t hr = tm1.tm_mday * 24; // only for jan 2013

    sec += hr * 60 * 60;

    return  sec;
}

time_t makeTime(std::string strtemp)
{
    time_t tempTime;
    struct tm tm1 = {};

    //std::string strtemp = "01-01-2013 00:00:00";
    std::istringstream ss(strtemp);
    ss >> std::get_time(&tm1, "%d-%m-%Y %H:%M:%S");

    tempTime = mktime_override(tm1);

    return tempTime;
}

int main()
{
	/*IDs present from January are considered in unique ID generation*/
	points** Trajecs = NULL;
    std::vector <ref_time> step_array;

	unsigned int file_length;
	try
	{

        CreateSampleSteps * SampleSteps = new CreateSampleSteps();
        SampleSteps->numSampleIDs = 10;
        SampleSteps->IDfilePath = INPUT_DIR + "1" + "\\sampled.txt";
        SampleSteps->getTrajecs();
        step_array = SampleSteps->step_array;
        delete SampleSteps;
        SampleSteps = NULL;

        ReadWrtiteTrajecs * ReadID = new ReadWrtiteTrajecs();
        ReadID->path = OUTPUT_DIR;
        ReadID->IDfilePath = INPUT_DIR + "1" + "\\sampled.txt";
        ReadID->AllTrajecspath = OUTPUT_DIR + "Sampled_Trajecs\\" + "AllTrajecs.data";
        ReadID->getTrajecs(Trajecs, step_array);

        delete ReadID;
        ReadID = NULL;

      /*  std::vector <ref_time> step_array;

		for (int i = 0; i < 720; i++)
		{
            if (0 == i)  step_array.push_back({ makeTime("01-01-2013 00:01:00"), i });
			else
			{
                step_array.push_back({ (step_array[i - 1].t + 3600) , i});
			}
		}

        ReadWrtiteTrajecs * ReadID = new ReadWrtiteTrajecs();
		ReadID->path = OUTPUT_DIR;
		ReadID->IDfilePath = INPUT_DIR + "1" + "\\sampled.txt";
        ReadID->AllTrajecspath = OUTPUT_DIR + "Sampled_Trajecs\\" + "AllTrajecs.data";
		ReadID->getTrajecs(Trajecs, step_array);
       
        delete ReadID;
        ReadID = NULL;*/
    }
    catch (...)
    {
        std::cout << "EXCEPTION <***UNEXPECTED***> caught in Function " << std::string(__func__) << " "
            << "at " << __LINE__ << " of " << __FILE__ << std::endl;
    }

	return 0;
}

