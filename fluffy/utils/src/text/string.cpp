#include <fluffy/pch.hpp>
#include <fluffy/text/string.hpp>

using namespace Fluffy;

String Fluffy::toString(int value)
{
    std::stringstream ss;
    ss << value;

    return ss.str();
}

String Fluffy::toString(float value)
{
    std::stringstream ss;
    ss << value;

    return ss.str();
}

bool Fluffy::isInteger(const String& value)
{
    return !value.empty() && value.find_first_not_of("-0123456789") == String::npos;
}

bool Fluffy::isNumber(const String& value)
{
    return !value.empty() && value.find_first_not_of(".-0123456789") == String::npos;
}

String Fluffy::currentDateTime()
{
    time_t    now = time(0);
    struct tm tstruct;
    char      buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return String(buf);
}