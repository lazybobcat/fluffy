//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 13/11/17.
//

#ifndef FLUFFY_SYSTEMMANAGER_HPP
#define FLUFFY_SYSTEMMANAGER_HPP

#include <Fluffy/ECS/System.hpp>
#include <map>
#include <memory>

namespace Fluffy {
namespace ECS {

class SystemManager : public Fluffy::Utility::NonCopyable
{
public:
    SystemManager(EntityManager& entityManager, EventManager& eventManager);

    /**
     * Add a before-handed initialized System to the manager. You should prefer to let Fluffy manager the system for you
     * by using SystemManager::add(Args...) to create the Systems.
     */
    template <typename S>
    void add(std::shared_ptr<S> system);

    /**
     * Create and add a System in the manager
     */
    template <typename S, typename... Args>
    std::shared_ptr<S> add(Args... args);

    /**
     * Return the System passed as template parameter
     */
    template <typename S>
    std::shared_ptr<S> system();

    /**
     * Update the System passed as template parameter
     */
    template <typename S>
    void update(float dt);

    /**
     * Update all registered Systems
     */
    void updateAll(float dt);

    /**
     * Configure all registered Systems. You must call this after adding all the systems.
     */
    void configure();

private:
    bool           mConfigured = false;
    EntityManager& mEntityManager;
    EventManager&  mEventManager;
    std::map<BaseSystem::Family, std::shared_ptr<BaseSystem>> mSystems;
};
}
}

#include <Fluffy/ECS/SystemManager.inl>

#endif //FLUFFY_SYSTEMMANAGER_HPP
