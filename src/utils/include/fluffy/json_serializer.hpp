//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/04/18.
//

#pragma once

#include <fluffy/serializable.hpp>

namespace Fluffy {

class JsonSerializer
{
public:
    static bool serializeToString(Fluffy::Serializable& input, std::string& output);
    static bool deserializeFromString(std::string& input, Fluffy::Serializable& output);
    static bool serializeToFile(Fluffy::Serializable& input, std::string& filepath);
    static bool deserializeFromFile(std::string& filepath, Fluffy::Serializable& output);
};
}
