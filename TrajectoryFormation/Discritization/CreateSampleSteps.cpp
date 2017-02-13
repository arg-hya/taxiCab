// GenerateID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CreateSampleSteps.h"
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
int CreateSampleSteps::MakeNumerical(std::string& str)
{
    // enum months = { "jan" };

    std::string substr;
    substr = str.substr(3, 3);



    if ("Jan" == substr)
    {
        str.replace(3, 3, "001");
        return EXIT_SUCCESS;
    }
    else  if ("Feb" == substr)
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
    else
    {
        std::cout << "Fuck";
    }

    return EXIT_FAILURE;
}

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	Constructor.
/*************************************************************************/
int CreateSampleSteps::comparetime(time_t time1, time_t time2)
{
    bool hr = (time1 > time2);
    return   hr ? 1 : -1;
}

/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	mktime_override.
/*************************************************************************/
time_t CreateSampleSteps::mktime_override(struct tm tm1)
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
time_t CreateSampleSteps::makeTime(std::string strtemp)
{
    time_t tempTime;
    struct tm tm1 = {};

    //std::string strtemp = "01-01-2013 00:00:00";
    std::istringstream ss(strtemp);
    ss >> std::get_time(&tm1, "%d-%m-%Y %H:%M:%S");

    tempTime = mktime_override(tm1);

    return tempTime;
}

bool myComp(ref_time a, ref_time b)
{
    return (a.i < b.i);
}
/*************************************************************************/
/// <b>Function: SampleTrajecs constructor</b>
///
/// \remarks	mktime_override.
/*************************************************************************/
int CreateSampleSteps::PopulatePointsperHr()
{

    //std::vector <ref_time> step_array;
    int** pointDensity = NULL;
    int*  pointCommon = NULL;

    for (int i = 0; i < 744; i++)
    {
        if (0 == i)  step_array.push_back({ makeTime("01-01-2013 01:00:00"), i });
        else
        {
            step_array.push_back({ (step_array[i - 1].t + 3600) , i });
        }
    }

    pointDensity = new int*[SampleIDs.size()];
    pointCommon =  new int[step_array.size()];

    for (int j = 0; j < step_array.size(); j++)
    {
        pointCommon[j] = 0;
    }

    for (int i = 0; i < SampleIDs.size(); i++)
    {
        std::string strtemp_path, strtemp_line;

        pointDensity[i] = new int[step_array.size()];
        for (int j = 0; j < step_array.size(); j++)
        {
            pointDensity[i][j] = 0;
        }

        for (std::vector<time_t>::iterator points_it = points[i].begin(); points_it != points[i].end(); ++points_it)
        {


            for (std::vector<ref_time>::iterator tmt = step_array.begin(); tmt != step_array.end(); ++tmt)
            {
                if (1 == comparetime(*points_it, tmt->t))
                {
                    if ((tmt + 1 == step_array.end()) || (-1 == comparetime(*points_it, (tmt + 1)->t)))
                    {
                        pointDensity[i][tmt->i]++;

                        break;
                    }
                }
                // i_fill++;
            }
        }
    }

    for (int i = 0; i < SampleIDs.size(); i++)
    {
        for (int j = 0; j < step_array.size(); j++)
        {
           // std::cout << pointDensity[i][j] << " ";

            pointCommon[j] += pointDensity[i][j];
            /*if (0 == pointDensity[i][j])
            {
                if ((-1 == pointCommon[j]) || (0 == pointCommon[j])) pointCommon[j] = 0;
            }
            else
            {
                if ((-1 == pointCommon[j]) || (0 == pointCommon[j])) pointCommon[j] = 1;
            }*/
        }
       // std::cout << std::endl;
    }
    for (std::vector<ref_time>::iterator tmt = step_array.begin(); tmt != step_array.end(); ++tmt)
    {
        std::cout << tmt->i << " ";
    }

    int size = step_array.size();
    for (int j = 0; j < size; j++)
    {
        if (pointCommon[j] > 20)
        {
            step_array.push_back({ (step_array[j].t + 1200) , j });
            step_array.push_back({ (step_array[j].t + 1200) , j });
        }
        else if (pointCommon[j] > 10)
        {
            step_array.push_back({ (step_array[j].t + 1800) , j });
        }
         //std::cout << pointCommon[j] << " ";
    }
    std::sort(step_array.begin(), step_array.end(), myComp);


    std::cout << std::endl;

    for (std::vector<ref_time>::iterator tmt = step_array.begin(); tmt != step_array.end(); ++tmt)
    {
        std::cout << tmt->i << " ";
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
int CreateSampleSteps::GetAllIDs()
{
    int count;
    std::string strtemp, strTempID, strtemp_path;

    in_IDfile.open(IDfilePath, std::ios::in);

    if (!in_IDfile.is_open())
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

    in_IDfile.close();

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
int CreateSampleSteps::getTrajecs()
{    
    std::string strtemp, strTempID, strtemp_path;

    //Populate All IDs
    GetAllIDs();

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, IDs.size());

   //Generate Sample ID numbers
    for (int i = 0; i < numSampleIDs; i++)
    {
        int temp_pos = -1;
        temp_pos = distribution(generator);
        if (-1 != temp_pos)  SampleIDs.push_back(IDs[temp_pos]);
    }

    points = new std::vector<time_t>[numSampleIDs];

    //Get trajectories of the sampled IDs
    for (int i = 0; i < SampleIDs.size(); i++)
    {
        std::string strtemp_path, strtemp_line;
        //unsigned int tempID;
        std::ifstream in_tempfile;
        std::vector<time_t>().swap(points[i]);

        strTempID = std::to_string(SampleIDs[i]);
       // std::cout << i << std::endl;
        //tempID = stoi(strTempID);
        strtemp_path = OUTPUT_DIR + strTempID + "_trajectory.traj";

        in_tempfile.open(strtemp_path, std::ios::in);
        if (!in_tempfile.is_open())	continue;

        while (getline(in_tempfile, strtemp_line))
        {
            std::stringstream ss(strtemp_line);
            std::string strtemp1,strtemp_date_time_1, strtemp_date_time_2;

            getline(ss, strtemp1, ',');
            getline(ss, strtemp_date_time_1, ' ');
            MakeNumerical(strtemp_date_time_1);
            getline(ss, strtemp_date_time_2, ',');
            getline(ss, strtemp1, ',');
            getline(ss, strtemp1, '\n');

            std::string strtemp = strtemp_date_time_1 + " " + strtemp_date_time_2;
            points[i].push_back(makeTime(strtemp));
        }        

        in_tempfile.close();
    }

    PopulatePointsperHr();

    return EXIT_SUCCESS;
}