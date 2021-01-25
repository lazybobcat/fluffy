#include <fluffy/ecs/system_manager.hpp>

SystemManager::SystemManager(EntityManager& entityManager, EventManager& eventManager)
  : mEntityManager(entityManager)
  , mEventManager(eventManager)
{
}

SystemManager::SystemManager(EntityManager* entityManager, EventManager* eventManager)
  : mEntityManager(*entityManager)
  , mEventManager(*eventManager)
{
}

void SystemManager::updateAll(Fluffy::Time dt)
{
    FLUFFY_ASSERT(mConfigured, "You must configure the SystemManager first");
    for (auto& pair : mSystems) {
        pair.second->update(mEntityManager, dt);
    }
}

void SystemManager::initialize()
{
    for (auto& pair : mSystems) {
        pair.second->initialize(mEntityManager, mEventManager);
    }

    mConfigured = true;
}

void SystemManager::terminate()
{
    for (auto& pair : mSystems) {
        pair.second->terminate(mEntityManager, mEventManager);
    }

    mConfigured = false;
}
