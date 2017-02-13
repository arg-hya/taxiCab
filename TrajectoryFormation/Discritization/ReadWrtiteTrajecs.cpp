// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReadWrtiteTrajecs.h"
#include "Header.h"

/*************************************************************************/
/// <b>Function: OpenIDFileforReading</b>
///
/// \param  
///
/// \return		Returns error state
///
/// \remarks	This function opend files
/*************************************************************************/
int ReadWrtiteTrajecs::MakeNumerical(std::string& str)
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
int ReadWrtiteTrajecs::comparetime(time_t time1, time_t time2)
{
	bool hr = (time1 > time2);
	return   hr ? 1 : -1;
}

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	mktime_override.
/*************************************************************************/
time_t ReadWrtiteTrajecs::mktime_override(struct tm tm1)
{
    time_t sec = tm1.tm_sec + (tm1.tm_min + tm1.tm_hour * 60) * 60;
    time_t hr = tm1.tm_mday * 24; // only for jan 2013

    sec += hr * 60 * 60;

    return  sec;
}

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	mktime_override.
/*************************************************************************/
int ReadWrtiteTrajecs::ConvertGeoPosTo2D(std::string& lat, std::string& lon)
{
    

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
int ReadWrtiteTrajecs::WriteSampledTrajecs(int ID, bool* fillarray, int fillarray_size, std::vector<points> temp_points)
{
	std::string strtemp, strTempID;
	std::string strtemp_path;
	//unsigned int tempID;
	std::ifstream in_tempfile;

	strTempID = std::to_string(ID);
	//tempID = stoi(strTempID);
	strtemp_path = OUTPUT_DIR + "Sampled_Trajecs\\" + strTempID + "_sampled.traj";

	out_file.open(strtemp_path, std::ios::out);

	int j = 0;
	for (int i = 0; i < fillarray_size; i++)
	{
        if (i != 0) // Put comma after every lat,long pair. [for Pretty Printing]
        {
            out_file_forClustering << ",";
        }

		if (fillarray[i])
		{
			out_file << temp_points[j].idle_time << ",";
			out_file << temp_points[j].date_time_1 << " " << temp_points[j].date_time_2 << ",";
			out_file << temp_points[j].lat << ",";
			out_file << temp_points[j].lon << "\n";

            out_file_forClustering << temp_points[j].lat << "," << temp_points[j].lon;

			j++;
		}
        else
        {
            out_file_forClustering <<  "0,0";
            out_file << "0,0 0,0,0" << "\n";
        }
		
	}
    out_file_forClustering << std::endl;
	out_file.close();

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
int ReadWrtiteTrajecs::getTrajecs(points** Trajecs, std::vector<ref_time>& step_array)
{
	int count;
	std::string strtemp, strTempID, strtemp_path;

	in_IDfile.open(IDfilePath, std::ios::in);    
    out_file_forClustering.open(AllTrajecspath, std::ios::out);

	if (!in_IDfile.is_open() || !out_file_forClustering.is_open())
	{
		std::cout << "File not opening for reading" << std::endl;
		return EXIT_FAILURE;
	}

	in_IDfile.seekg(std::ios::beg);

	for (count = 0;; ++count)
	{
		if (0 == count)
		{
			std::getline(in_IDfile, strtemp);
			//in_file >> strtemp;
			file_length = stoi(strtemp);
			continue;
		}

		std::getline(in_IDfile, strtemp);
		if (in_IDfile.eof())	break;
		//in_file >> strtemp;
		if (strtemp.empty())
		{
			std::cout << "Invalid Point";
			return EXIT_FAILURE;
		}
		IDs.push_back(stoi(strtemp));
	}

    out_file_forClustering << "Cab ID:     <<Trajectory >>" << std::endl;

	for (int i = 0; i < IDs.size(); i++)
	{
		std::string strtemp_path, strtemp_line;
		//unsigned int tempID;
		std::ifstream in_tempfile;
        std::vector<points> temp_points;
		std::vector<points>().swap(temp_points);

		strTempID = std::to_string(IDs[i]);
        std::cout << i << std::endl;
		//tempID = stoi(strTempID);
		strtemp_path = OUTPUT_DIR + strTempID + "_trajectory.traj";

		in_tempfile.open(strtemp_path, std::ios::in);
		if (!in_tempfile.is_open())	continue;

		std::vector<ref_time>::iterator tmt;
		std::vector<ref_time>::iterator old_tmt = step_array.begin();

		bool* fillarray = new bool[step_array.size()];
		for (int i = 0; i < step_array.size(); i++)
		{
			fillarray[i] = false;
		}        

        while (getline(in_tempfile, strtemp_line))
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

            if (ConvertPosTo2D)
            {
                ConvertGeoPosTo2D(temp_point.lat, temp_point.lon);
            }

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
		WriteSampledTrajecs(IDs[i],fillarray, step_array.size(), temp_points);
		in_tempfile.close();
	}

	in_IDfile.close();
    out_file_forClustering.close();

	return EXIT_SUCCESS;
}