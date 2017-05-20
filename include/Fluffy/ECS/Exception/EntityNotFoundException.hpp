//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#ifndef FLUFFY_ENTITYNOTFOUNDEXCEPTION_HPP
#define FLUFFY_ENTITYNOTFOUNDEXCEPTION_HPP

#include <stdexcept>

namespace Fluffy {
namespace ECS {

class EntityNotFoundException : public std::logic_error
{
public:
    EntityNotFoundException(const std::string& what);
};
}
}

#endif //FLUFFY_ENTITYNOTFOUNDEXCEPTION_HPP
