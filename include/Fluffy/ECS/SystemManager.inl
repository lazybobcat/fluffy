//
// Created by loicb on 13/11/17.
//

#include <Fluffy/ECS/SystemManager.hpp>
#include <cassert>

using namespace Fluffy::ECS;

template <typename S>
void SystemManager::add(std::shared_ptr<S> system)
{
    mSystems.insert(std::make_pair(S::family(), system));

    // Fool proofing
    if (mConfigured) {
        system->configure(mEntityManager, mEventManager);
    }
}

template <typename S, typename... Args>
std::shared_ptr<S> SystemManager::add(Args... args)
{
    std::shared_ptr<S> system(new S(std::forward(args)...));
    add(system);

    return system;
}

template<typename S>
void SystemManager::remove()
{
    auto it = mSystems.find(S::family());
    assert(it != mSystems.end());

    it->second->terminate();
    mSystems.erase(it);
}


template <typename S>
std::shared_ptr<S> SystemManager::system()
{
    auto it = mSystems.find(S::family());
    assert(it != mSystems.end());

    return std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
}

template <typename S>
void SystemManager::update(Fluffy::Utility::Time dt)
{
    assert(mConfigured && "You must configure the SystemManager first");
    std::shared_ptr<S> s = system<S>();
    s->update(mEntityManager, mEventManager, dt);
}