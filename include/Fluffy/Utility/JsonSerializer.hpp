//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/04/18.
//

#ifndef FLUFFY_JSONSERIALIZER_HPP
#define FLUFFY_JSONSERIALIZER_HPP

#include <Fluffy/Utility/Serializable.hpp>

namespace Fluffy {
namespace Utility {

    class JsonSerializer
    {
    public:
        static bool serializeToString(Fluffy::Utility::Serializable &input, std::string &output);
        static bool serializeFromString(std::string &input, Fluffy::Utility::Serializable &output);
        static bool serializeToFile(Fluffy::Utility::Serializable &input, std::string &filepath);
        static bool serializeFromFile(std::string &filepath, Fluffy::Utility::Serializable &output);
    };
}
}

#endif //FLUFFY_JSONSERIALIZER_HPP
