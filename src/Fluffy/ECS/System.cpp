//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 09/11/17.
//

#include <Fluffy/ECS/System.hpp>

using namespace Fluffy::ECS;

BaseSystem::Family BaseSystem::mFamilyCounter = 0;

void BaseSystem::configure(EntityManager &entityManager, EventManager &eventManager)
{
}