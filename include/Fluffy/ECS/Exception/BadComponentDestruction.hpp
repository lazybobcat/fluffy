//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 21/05/17.
//

#ifndef FLUFFY_BADCOMPONENTDESTRUCTION_HPP
#define FLUFFY_BADCOMPONENTDESTRUCTION_HPP

#include <stdexcept>

namespace Fluffy {
namespace ECS {

class BadComponentDestruction : public std::logic_error
{
public:
    BadComponentDestruction(const std::string& what);
};
}
}

#endif //FLUFFY_BADCOMPONENTDESTRUCTION_HPP
