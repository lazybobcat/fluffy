//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_DEBUGGABLE_HPP
#define FLUFFY_DEBUGGABLE_HPP

#include <string>
#include <json/json.h>

namespace Fluffy
{
namespace Utility
{

class Debuggable
{
public:
    Debuggable() = default;
    virtual ~Debuggable() = default;

    virtual void        serialize() = 0;
    virtual std::string debug();

    template <typename T>
    void serializeAttribute(const std::string& key, const T& value)
    {
        mSerialized[key] = value;
    }

private:
    Json::Value     mSerialized;
};

}
}

#endif //FLUFFY_DEBUGGABLE_HPP
