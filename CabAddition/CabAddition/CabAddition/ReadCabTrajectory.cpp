// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReadCabTrajectory.h"
#include "Header.h"

int ReadCabTrajectory::MakeNumerical(std::string& str)
{
    // enum months = { "jan" };

    std::string substr;
    substr = str.substr(3, 3);



    if ("Jan" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("FEB" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("MAR" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("APR" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("MAY" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("JUN" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("JUL" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("AUG" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("SEP" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("OCT" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("NOV" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("DEC" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	Constructor.
/*************************************************************************/
int ReadCabTrajectory::comparetime(time_t time1, time_t time2)
{
    bool hr = (time1 > time2);
    return   hr ? 1 : -1;
}

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	mktime_override.
/*************************************************************************/
time_t ReadCabTrajectory::mktime_override(struct tm tm1)
{
    time_t sec = tm1.tm_sec + (tm1.tm_min + tm1.tm_hour * 60) * 60;
    time_t hr = tm1.tm_mday * 24; // only for jan 2013

    sec += hr * 60 * 60;

    return  sec;
}

/*************************************************************************/
/// <b>Function: getClusters</b>
///
/// \param  
///
/// \return		Returns number of IDs
///
/// \remarks	This function  gets the total number of IDs in the dataset.
///              Medallion file is considered
/*************************************************************************/
int ReadCabTrajectory::getTraj(CabTrajectory_latlon* &Trajectory, std::vector<ref_time>& step_array)
{
    std::ofstream out_file;

    std::string strtemp_line;

    std::vector<points> temp_points;
    std::vector<points>().swap(temp_points);

    in_file.open(ClusterFilePath, std::ios::in);

    if (!in_file.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    Trajectory = new CabTrajectory_latlon[step_array.size()];

    std::vector<ref_time>::iterator tmt;
    std::vector<ref_time>::iterator old_tmt = step_array.begin();

    bool* fillarray = new bool[step_array.size()];
    for (int i = 0; i < step_array.size(); i++)
    {
        fillarray[i] = false;
    }

    in_file.seekg(std::ios::beg);

    while (getline(in_file, strtemp_line))
    {
        std::stringstream ss(strtemp_line);
        std::string strtemp_data;
        points temp_point;

        getline(ss, strtemp_data, ',');
        temp_point.idle_time = strtemp_data;
        getline(ss, strtemp_data, ' ');
        MakeNumerical(strtemp_data);
        temp_point.date_time_1 = strtemp_data;
        getline(ss, strtemp_data, ',');
        temp_point.date_time_2 = strtemp_data;
        getline(ss, strtemp_data, ',');
        temp_point.lat = strtemp_data;
        getline(ss, strtemp_data, '\n');
        temp_point.lon = strtemp_data;

        time_t tempTime;
        struct tm tm1 = {};
        std::string strtemp = temp_point.date_time_1 + " " + temp_point.date_time_2;
        std::istringstream iss(strtemp);
        iss >> std::get_time(&tm1, "%d-%m-%Y %H:%M:%S");
        tempTime = mktime_override(tm1);

        //int i_fill = 0;

        for (tmt = old_tmt; tmt != step_array.end(); ++tmt)
        {
            if (1 == comparetime(tempTime, tmt->t))
            {
                if ((tmt + 1 == step_array.end()) || (-1 == comparetime(tempTime, (tmt + 1)->t)))
                {
                    if (!fillarray[tmt->i])
                    {
                        //std::cout << tmt->i << std::endl;
                        fillarray[tmt->i] = true;
                        temp_points.push_back(temp_point);
                        if (tmt + 1 != step_array.end()) old_tmt = tmt + 1;
                        // i_fill++;							
                    }
                    break;
                }
            }
            // i_fill++;
        }
    }

    out_file.open(ClusterOutputFilePath, std::ios::out);

    int j = 0;
    for (int i = 0; i < step_array.size(); i++)
    {
        if (fillarray[i])
        {
            if (temp_points[j].lat == "nan" || temp_points[j].lon == "nan")
            {
                temp_points[j].lat = "0";
                temp_points[j].lon = "0";
            }
            Trajectory[i].lat = stoi(temp_points[j].lat);
            Trajectory[i].lon = stoi(temp_points[j].lon);
            j++;
        }
        else
        {
            Trajectory[i].lat = 0;
            Trajectory[i].lon = 0;
        }
        out_file << Trajectory[i].lat;
        out_file << " ";
        out_file << Trajectory[i].lon;
        out_file << std::endl;

    }
    out_file.close();
    in_file.close();

    return EXIT_SUCCESS;
}

int ReadCabTrajectory::getConvertedTraj(CabTrajectory* &CabTraj_converted, int size)
{
    int k = 0;
    std::string strtemp_line;

    in_file.open(ClusterConvertedFilePath, std::ios::in);

    if (!in_file.is_open())
    {
        std::cout << "File not opening for reading" << std::endl;
        return EXIT_FAILURE;
    }

    CabTraj_converted = new CabTrajectory[size];
    while (size --)
    {
        getline(in_file, strtemp_line);
        int temp = stoi(strtemp_line);
        CabTraj_converted[k].node_point = temp;
       // std::cout << CabTraj_converted[k].node_point << std::endl;
        k++;
    }
    std::cout << "finished";
    return EXIT_SUCCESS;
}