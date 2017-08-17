// SampleTrajecs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SampleTrajecs.h"
#include "Header.h"

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	Constructor.
/*************************************************************************/
SampleTrajecs::SampleTrajecs(std::vector<time_t>& step_array)
{
    SampleTrajecs::step_array = step_array;
}

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	Constructor.
/*************************************************************************/
int SampleTrajecs::comparetime(time_t time1, time_t time2)
{
    return difftime(time1, time2) > 0.0 ? 1 : -1;
}

/*************************************************************************/
/// <b>Function: OpenIDFileforReading</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function opend files
/*************************************************************************/
int SampleTrajecs::WriteSampledTrajecs()
{
    std::string strtemp, strTempID;

    for (int i = 0; i < IDs.size(); i++)
    {
        std::string strtemp_path, strtemp_line;
        //unsigned int tempID;
        std::ifstream in_tempfile;
        std::vector<points> temp_points;

        strTempID = std::to_string(IDs[i]);
        //tempID = stoi(strTempID);
        strtemp_path = outputpath + strTempID + "_sampled.traj";

        out_file.open(strtemp_path, std::ios::out);
        for (unsigned int j = 0; j < cab_trajecs.size(); j++)
        {
            out_file << cab_trajecs[j]->idle_time << ",";
            out_file << cab_trajecs[j]->date_time_1 << " " << cab_trajecs[j]->date_time_2<< ",";
            out_file << cab_trajecs[j]->lat<< ",";
            out_file << cab_trajecs[j]->lon << "\n";
        }
       
        out_file.close();
    }
    return EXIT_SUCCESS;
}

/*************************************************************************/
/// <b>Function: OpenIDFileforReading</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function opend files
/*************************************************************************/
int SampleTrajecs::SampleIt(std::vector<std::vector<points>> Trajecs)
{
    unsigned int i = 0;

    std::vector<std::vector<points>>::iterator it;
    for (it = Trajecs.begin(); it != Trajecs.end(); ++it)
    {
        cab_trajecs.push_back(new points[step_array.size()]);

        std::vector<time_t>::iterator tmt;
        tmt = step_array.begin();

        std::vector<points>::iterator pt;
        for (pt = it->begin(); pt != it->end(); ++pt)
        {
            if (tmt == step_array.end())
            {
                break;
            }

            time_t tempTime;
            struct tm tm1 = {};
            std::string strtemp = pt->date_time_1 + " " +pt->date_time_2;
            std::istringstream ss(strtemp);
            ss >> std::get_time(&tm1, "%H:%M:%S %d-%m-%Y");
            tempTime = mktime(&tm1);

         
            if (1 == comparetime(tempTime, *tmt))
            {
                cab_trajecs[i]->date_time_1 = pt->date_time_1;
                cab_trajecs[i]->date_time_2 = pt->date_time_2;
                cab_trajecs[i]->idle_time = pt->idle_time;
                cab_trajecs[i]->lat = pt->lat;
                cab_trajecs[i]->lon = pt->lon;
                ++tmt;
            }            
        }
        if (tmt == step_array.end())
        {
            break;
        }
        i++;
    }

    WriteSampledTrajecs();

    return EXIT_SUCCESS;
}