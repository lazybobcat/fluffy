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
