//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/04/18.
//

#pragma once

#include <json/json.h>

namespace Fluffy {

class Serializable
{
public:
    virtual ~Serializable()                     = default;
    virtual void serialize(Json::Value& to)     = 0;
    virtual void deserialize(Json::Value& from) = 0;
};
}
