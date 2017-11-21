//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 21/11/17.
//

#include <Fluffy/Utility/ServiceContainer.hpp>
#include <cassert>

using namespace Fluffly::Utility;

template <typename T, typename... Deps, typename... Args>
void ServiceContainer::set(Args... args)
{
    auto                                  instance = std::make_unique<T>(get<typename std::remove_const<Deps>::type>()..., args...);
    std::unique_ptr<InstanceContainer<T>> service  = std::make_unique<InstanceContainer<T>>(std::move(instance));
    mContainer[typeId<T>()]                        = std::move(service);
}

template <typename T>
T* ServiceContainer::get()
{
    auto it = mContainer.find(typeId<T>());
    assert(it != mContainer.end());

    return static_cast<T*>(it->second->get());
}

template <typename T>
int ServiceContainer::typeId()
{
    static int id = ++mLastTypeId;

    return id;
}