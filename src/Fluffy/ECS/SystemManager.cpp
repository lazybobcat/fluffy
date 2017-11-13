//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 13/11/17.
//

#include <Fluffy/ECS/SystemManager.hpp>

SystemManager::SystemManager(EntityManager &entityManager, EventManager &eventManager)
    : mEntityManager(entityManager)
    , mEventManager(eventManager)
{
}

void SystemManager::updateAll(float dt)
{
    assert(mConfigured && "You must configure the SystemManager first");
    for (auto& pair : mSystems) {
        pair.second->update(mEntityManager, dt);
    }
}

void SystemManager::configure()
{
    for (auto& pair : mSystems) {
        pair.second->configure(mEntityManager, mEventManager);
    }

    mConfigured = true;
}