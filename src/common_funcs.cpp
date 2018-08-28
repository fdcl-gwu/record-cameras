#include "common_funcs.h"


std::string get_time(void)
{
    time_t now = time(0);
    struct tm tstruct;
    char start_time[80];
    tstruct = *localtime(&now);
    strftime(start_time, sizeof(start_time), "%H%M%S: ", &tstruct);

    return std::string(start_time);
}

