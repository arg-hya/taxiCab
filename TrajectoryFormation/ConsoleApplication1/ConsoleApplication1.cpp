// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#include <algorithm>	/* find */
#include <fstream>
#include <vector>
////#include <limits>
#include <string>
//#include <random>
#include <sstream>  

struct points
{
    std::string idle_time;
    std::string date_time_1;
    std::string date_time_2;
    std::string lon;
    std::string lat;
};

void func(std::vector<points>& point)
{
    points ot;
    ot.date_time_1 = ot.date_time_2 = ot.idle_time = ot.lat = ot.lon = "dfdf";

    point.push_back(ot);
}
int main()
{
    int count;
    std::string strtemp, strTempID;

    std::vector<points> pointss;

        func(pointss);

        std::string  strtemp_line;
        unsigned int tempID;
        std::ifstream in_tempfile;

        in_tempfile.open("test.txt", std::ios::in);
        //if (!in_tempfile.is_open())	continue;

        while (getline(in_tempfile, strtemp_line))
        {
            std::stringstream ss(strtemp_line);
            std::string strtemp_data;

            getline(ss, strtemp_data, ',');
            getline(ss, strtemp_data, ' ');
            getline(ss, strtemp_data, ',');
            getline(ss, strtemp_data, ',');
            getline(ss, strtemp_data, '\n');
        }

        in_tempfile.close();

    return EXIT_SUCCESS;
}

