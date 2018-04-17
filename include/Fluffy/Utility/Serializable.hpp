//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/04/18.
//

#ifndef FLUFFY_SERIALIZABLE_HPP
#define FLUFFY_SERIALIZABLE_HPP

#include <json/json.h>

namespace Fluffy {
namespace Utility {

class Serializable
{
public:
    virtual ~Serializable() = default;
    virtual void serialize(Json::Value& to)     = 0;
    virtual void deserialize(Json::Value& from) = 0;
};
}
}

#endif //FLUFFY_SERIALIZABLE_HPP
