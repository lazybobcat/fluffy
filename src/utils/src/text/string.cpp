#include <fluffy/pch.hpp>
#include <fluffy/text/string.hpp>

using namespace Fluffy;

String Fluffy::fromUTF32(String32 string)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv;

    return cv.to_bytes(string);
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
