//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <Fluffy/ECS/ComponentHandle.hpp>

using namespace Fluffy::ECS;

template <typename T>
ComponentHandle<T>::ComponentHandle()
  : mComponent(nullptr)
{
}

template <typename T>
ComponentHandle<T>::ComponentHandle(T* component)
  : mComponent(component)
{
}

template <typename T>
ComponentHandle<T>::operator bool() const
{
    return isValid();
}

template <typename T>
bool ComponentHandle<T>::isValid() const
{
    return mComponent != nullptr;
}

template <typename T>
T* ComponentHandle<T>::operator->() const
{
    return mComponent;
}

template <typename T>
T& ComponentHandle<T>::get()
{
    return *mComponent;
}
