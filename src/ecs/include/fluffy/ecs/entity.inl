#include <fluffy/ecs/entity.hpp>
#include <fluffy/ecs/entity_manager.hpp>

using namespace Fluffy;

template<typename C, typename... Args>
ComponentHandle<C> Entity::assign(Args&&... args)
{
    FLUFFY_ASSERT(isValid(), "Entity is not valid");

    return mManager->assign<C>(mId, std::forward<Args>(args)...);
}

template<typename C, typename... Args>
ComponentHandle<C> Entity::replace(Args&&... args)
{
    FLUFFY_ASSERT(isValid(), "Entity is not valid");

    auto handle = component<C>();
    if (handle) {
        *(handle.get()) = C(std::forward<Args>(args)...);
    } else {
        handle = mManager->assign<C>(mId, std::forward<Args>(args)...);
    }

    return handle;
}

template<typename C>
bool Entity::hasComponent() const
{
    FLUFFY_ASSERT(isValid(), "Entity is not valid");

    return mManager->hasComponent<C>(mId);
}

template<typename C>
ComponentHandle<C> Entity::component()
{
    FLUFFY_ASSERT(isValid(), "Entity is not valid");

    return mManager->component<C>(mId);
}

template<typename... Components>
std::tuple<ComponentHandle<Components>...> Entity::components()
{
    FLUFFY_ASSERT(isValid(), "Entity is not valid");

    return mManager->components<Components...>(mId);
}

template<typename C>
void Entity::remove()
{
    FLUFFY_ASSERT(isValid(), "Entity is not valid");

    if (!hasComponent<C>()) {
        FLUFFY_LOG_ERROR("Trying to remove unassigned component '" + toString(typeid(C).name()) + "' from entity #" + toString(mId.index()));
    }

    mManager->remove<C>(mId);
}