//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 28/12/15.
//

#ifndef FLUFFY_BINDABLE_HPP
#define FLUFFY_BINDABLE_HPP

#include <selene.h>

namespace Fluffy {
namespace Lua {

class Bindable
{
public:
    Bindable()          = default;
    virtual ~Bindable() = default;

    virtual void bind(sel::State&) = 0;
};
}
}

#endif //FLUFFY_BINDABLE_HPP
