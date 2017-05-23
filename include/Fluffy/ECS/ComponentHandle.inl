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
    assert(mManager);

    return mManager->template getComponentPointer<C>(mId);
}

//
//template <typename T>
//ComponentHandle<T>::operator bool() const
//{
//    return isValid();
//}
//
//template <typename T>
//bool ComponentHandle<T>::isValid() const
//{
//    return mComponent != nullptr;
//}

template <typename T>
T* ComponentHandle<T>::operator->()
{
    return get();
}

//template <typename T>
//T& ComponentHandle<T>::get()
//{
//    return *mComponent;
//}
