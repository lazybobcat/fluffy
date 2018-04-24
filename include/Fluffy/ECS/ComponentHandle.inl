//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <Fluffy/ECS/ComponentHandle.hpp>
#include <Fluffy/ECS/EntityManager.hpp>
#include <cassert>

using namespace Fluffy::ECS;

template <typename C>
ComponentHandle<C>::ComponentHandle()
  : mManager(nullptr)
  , mId(Entity::INVALID)
{
}

template <typename C>
ComponentHandle<C>::ComponentHandle(EntityManager* manager, Entity::Id id)
  : mManager(manager)
  , mId(id)
{
}

template <typename C>
bool ComponentHandle<C>::operator==(const ComponentHandle<C>& other) const
{
    return mManager == other.mManager && mId == other.mId;
}

template <typename C>
bool ComponentHandle<C>::operator!=(const ComponentHandle<C>& other) const
{
    return !(*this == other);
}

template <typename C>
C* ComponentHandle<C>::get()
{
    assert(isValid());

    return mManager->template getComponentPointer<C>(mId);
}

template <typename C>
void ComponentHandle<C>::remove()
{
    assert(isValid());

    mManager->template remove<C>(mId);
}

template <typename C>
Entity ComponentHandle<C>::getEntity()
{
    assert(isValid());

    return mManager->getEntity(mId);
}

template <typename C>
ComponentHandle<C>::operator bool() const
{
    return isValid();
}

template <typename C>
bool ComponentHandle<C>::isValid() const
{
    return mManager && mManager->isValid(mId) && mManager->template hasComponent<C>(mId);
}

template <typename C>
C* ComponentHandle<C>::operator->()
{
    return get();
}

template <typename C>
const C* ComponentHandle<C>::get() const
{
    assert(isValid());

    return mManager->template getComponentPointer<C>(mId);
}

template <typename C>
const C* ComponentHandle<C>::operator->() const
{
    return get();
}
