//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 21/05/17.
//

#include <Fluffy/ECS/Component.hpp>
#include <Fluffy/ECS/Exception/BadComponentDestruction.hpp>

using namespace Fluffy::ECS;

BaseComponent::Family BaseComponent::mFamilyCounter = 0;

void BaseComponent::fail()
{
    throw BadComponentDestruction("You musn't delete any component by hand.");
}