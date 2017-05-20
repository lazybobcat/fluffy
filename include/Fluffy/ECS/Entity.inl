//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <Fluffy/ECS/Exception/ComponentNotFoundException.hpp>
#include <Fluffy/Utility/String.hpp>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

template<typename T, typename... Args>
ComponentHandle<T> Entity::assign(Args &&... args)
{
    auto found = mComponents.find(std::type_index(typeid(T)));
    if (found != mComponents.end())
    {
        delete found->second;
        mComponents.erase(found);
    }

    T* component = new T(args...);
    mComponents.insert({ std::type_index(typeid(T)) , component });

    // @todo emit event

    return ComponentHandle<T>(component);
}

template<typename T>
ComponentHandle<T> Entity::get()
{
    auto found = mComponents.find(std::type_index(typeid(T)));
    if (found != mComponents.end())
    {
        return ComponentHandle<T>(dynamic_cast<T*>(found->second));
    }

    throw ComponentNotFoundException(printString("Trying to get unassigned component '%1' in entity #%2", {
            toString(typeid(T).name()),
            toString(getRef())
    }));
}