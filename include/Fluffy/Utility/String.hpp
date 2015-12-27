//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_STRING_HPP
#define FLUFFY_STRING_HPP

#include <string>
#include <sstream>

namespace Fluffy
{
namespace Utility
{

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}


}
}

#endif //FLUFFY_STRING_HPP
