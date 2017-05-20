//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#ifndef FLUFFY_COMPONENTNOTFOUNDEXCEPTION_HPP
#define FLUFFY_COMPONENTNOTFOUNDEXCEPTION_HPP

#include <stdexcept>

namespace Fluffy {
namespace ECS {

class ComponentNotFoundException : public std::logic_error
{
public:
    ComponentNotFoundException(const std::string& what);
};
}
}

#endif //FLUFFY_COMPONENTNOTFOUNDEXCEPTION_HPP
