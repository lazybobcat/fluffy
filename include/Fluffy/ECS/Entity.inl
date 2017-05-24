//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <Fluffy/ECS/Entity.hpp>
#include <Fluffy/ECS/EntityManager.hpp>
#include <Fluffy/ECS/Exception/ComponentNotFoundException.hpp>
#include <Fluffy/Utility/String.hpp>
#include <cassert>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

template <typename C, typename... Args>
ComponentHandle<C> Entity::assign(Args&&... args)
{
    assert(isValid());

    return mManager->assign<C>(mId, std::forward<Args>(args)...);
}

template <typename C, typename... Args>
ComponentHandle<C> Entity::replace(Args&&... args)
{
    assert(isValid());

    auto handle = getComponent<C>();
    if (handle) {
        *(handle.get()) = C(std::forward<Args>(args)...);
    } else {
        handle = mManager->assign<C>(mId, std::forward<Args>(args)...);
    }

    return handle;
}

template <typename C>
bool Entity::hasComponent() const
{
    assert(isValid());

    return mManager->hasComponent<C>(mId);
}

template <typename C>
ComponentHandle<C> Entity::getComponent()
{
    assert(isValid());

    return mManager->component<C>(mId);
}

template <typename C>
void Entity::remove()
{
    assert(isValid());

    if (!hasComponent<C>()) {
        throw ComponentNotFoundException(printString("Trying to remove unassigned component '%1' from entity #%2", { toString(typeid(C).name()), toString(mId.getIndex()) }));
    }

    mManager->remove<C>(mId);
}