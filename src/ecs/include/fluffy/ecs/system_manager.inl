#include <cassert>
#include <fluffy/ecs/system_manager.hpp>

using namespace Fluffy;

template<typename S>
void SystemManager::add(std::shared_ptr<S> system)
{
    mSystems.insert(std::make_pair(S::family(), system));

    // Fool proofing
    if (mConfigured) {
        system->configure(mEntityManager, mEventManager);
    }
}

template<typename S, typename... Args>
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
    FLUFFY_ASSERT(it != mSystems.end(), "System not found");

    it->second->terminate();
    mSystems.erase(it);
}

template<typename S>
std::shared_ptr<S> SystemManager::system()
{
    auto it = mSystems.find(S::family());
    FLUFFY_ASSERT(it != mSystems.end(), "System not found");

    return std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
}

template<typename S>
void SystemManager::update(Fluffy::Time dt)
{
    FLUFFY_ASSERT(mConfigured, "You must configure the SystemManager first");
    std::shared_ptr<S> s = system<S>();
    s->update(mEntityManager, mEventManager, dt);
}