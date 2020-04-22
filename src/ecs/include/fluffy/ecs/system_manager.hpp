#pragma once

#include <fluffy/ecs/system.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

class SystemManager
{
public:
    SystemManager(EntityManager& entityManager, EventManager& eventManager);
    SystemManager(EntityManager* entityManager, EventManager* eventManager);

    /**
     * Add a before-handed initialized System to the manager. You should prefer to let Fluffy manager the system for you
     * by using SystemManager::add(Args...) to create the Systems.
     */
    template<typename S>
    void add(std::shared_ptr<S> system);

    /**
     * Create and add a System in the manager
     */
    template<typename S, typename... Args>
    std::shared_ptr<S> add(Args... args);

    /**
     * Terminate and remove a System from the manager
     */
    template<typename S>
    void remove();

    /**
     * Return the System passed as template parameter
     */
    template<typename S>
    std::shared_ptr<S> system();

    /**
     * Update the System passed as template parameter
     */
    template<typename S>
    void update(Fluffy::Time dt);

    /**
     * Update all registered Systems
     */
    void updateAll(Fluffy::Time dt);

    /**
     * Configure all registered Systems. You must call this after adding all the systems.
     */
    void initialize();

    /**
     * Terminate all registered Systems.
     */
    void terminate();

private:
    bool                                                      mConfigured = false;
    EntityManager&                                            mEntityManager;
    EventManager&                                             mEventManager;
    std::map<BaseSystem::Family, std::shared_ptr<BaseSystem>> mSystems;
};
}

#include <fluffy/ecs/system_manager.inl>
