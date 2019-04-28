//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <cassert>
#include <fluffy/entity.hpp>
#include <fluffy/entity_manager.hpp>
#include <fluffy/text/string.hpp>
#include <fluffy/utils/logger.hpp>

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
        Logger::log(Logger::LogType::Error, printString("Trying to remove unassigned component '%1' from entity #%2", { toString(typeid(C).name()), toString(mId.index()) }));
    }

    mManager->remove<C>(mId);
}