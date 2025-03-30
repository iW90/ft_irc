# include "Utils.hpp"


std::string Utils::get_time() {
    time_t rawtime;
    struct tm *timeinfo;
    char time_string[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(time_string, sizeof(time_string), "%d-%m-%Y %H:%M:%S", timeinfo);

    return std::string(time_string);
}
