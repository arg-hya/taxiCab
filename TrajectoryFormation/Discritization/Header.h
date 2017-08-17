#pragma once

#include <time.h>

#define INPUT_DIR  std::string("..\\Data\\")
#define OUTPUT_DIR  std::string("..\\Output\\")

#define time_t unsigned int

struct ref_time
{ 
    time_t t;
    int i; 
};

struct points
{
	std::string idle_time;
	std::string date_time_1;
	std::string date_time_2;
    std::string lon;
	std::string lat;
};
