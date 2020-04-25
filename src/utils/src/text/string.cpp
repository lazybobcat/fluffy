#include <fluffy/pch.hpp>
#include <fluffy/text/string.hpp>

using namespace Fluffy;

String Fluffy::fromUTF32(String32 string)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv;

    return cv.to_bytes(string);
}
