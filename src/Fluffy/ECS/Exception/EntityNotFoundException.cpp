//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <Fluffy/ECS/Exception/EntityNotFoundException.hpp>

using namespace Fluffy::ECS;

EntityNotFoundException::EntityNotFoundException(const std::string& what)
  : std::logic_error(what)
{
}
