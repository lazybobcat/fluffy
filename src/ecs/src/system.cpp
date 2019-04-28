//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 09/11/17.
//

#include <fluffy/system.hpp>

using namespace Fluffy;

BaseSystem::Family BaseSystem::mFamilyCounter = 0;

void BaseSystem::initialize(EntityManager& entityManager, EventManager& eventManager)
{
}

void BaseSystem::terminate(EntityManager& entityManager, EventManager& eventManager)
{
}