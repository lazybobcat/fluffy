//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 21/05/17.
//

#include <Fluffy/ECS/Exception/BadComponentDestruction.hpp>

using namespace Fluffy::ECS;

BadComponentDestruction::BadComponentDestruction(const std::string& what)
        : std::logic_error(what)
{
}