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

//template <typename T, typename... Args>
//ComponentHandle<T> Entity::assign(Args&&... args)
//{
//    auto found = mComponents.find(std::type_index(typeid(T)));
//    if (found != mComponents.end()) {
//        delete found->second;
//        mComponents.erase(found);
//    }
//
//    T* component = new T(args...);
//    mComponents.insert({ std::type_index(typeid(T)), component });
//
//    // @todo emit event
//
//    return ComponentHandle<T>(component);
//}
//
//template <typename T>
//ComponentHandle<T> Entity::get()
//{
//    auto found = mComponents.find(std::type_index(typeid(T)));
//    if (found != mComponents.end()) {
//        return ComponentHandle<T>(dynamic_cast<T*>(found->second));
//    }
//
//    throw ComponentNotFoundException(printString("Trying to get unassigned component '%1' from entityByIndex #%2", { toString(typeid(T).name()), toString(getRef()) }));
//}
//
//template <typename T>
//bool Entity::has() const
//{
//    auto index = std::type_index(typeid(T));
//
//    return mComponents.find(index) != mComponents.end();
//}
//
//template <typename T, typename V, typename... Types>
//bool Entity::has() const
//{
//    return has<T>() && has<V, Types...>();
//};
//
//template <typename T>
//void Entity::remove()
//{
//    auto found = mComponents.find(std::type_index(typeid(T)));
//    if (found != mComponents.end()) {
//        delete found->second;
//        mComponents.erase(found);
//
//        return;
//    }
//
//    throw ComponentNotFoundException(printString("Trying to remove unassigned component '%1' from entityByIndex #%2", { toString(typeid(T).name()), toString(getRef()) }));
//}