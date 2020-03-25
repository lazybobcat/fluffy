#include <fluffy/ecs/entity.hpp>
#include <fluffy/ecs/entity_manager.hpp>
#include <fluffy/pch.hpp>

using namespace Fluffy;

template<typename C, typename... Args>
ComponentHandle<C> Entity::assign(Args&&... args)
{
    assert(isValid());

    return mManager->assign<C>(mId, std::forward<Args>(args)...);
}

template<typename C, typename... Args>
ComponentHandle<C> Entity::replace(Args&&... args)
{
    assert(isValid());

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
    assert(isValid());

    return mManager->hasComponent<C>(mId);
}

template<typename C>
ComponentHandle<C> Entity::component()
{
    assert(isValid());

    return mManager->component<C>(mId);
}

template<typename... Components>
std::tuple<ComponentHandle<Components>...> Entity::components()
{
    assert(isValid());

    return mManager->components<Components...>(mId);
}

template<typename C>
void Entity::remove()
{
    assert(isValid());

    if (!hasComponent<C>()) {
        FLUFFY_LOG_ERROR("Trying to remove unassigned component '" + toString(typeid(C).name()) + "' from entity #" + toString(mId.index()));
    }

    mManager->remove<C>(mId);
}