#include <fluffy/service/service_container.hpp>

using namespace Fluffly;

template<typename T, typename... Deps, typename... Args>
void ServiceContainer::set(Args... args)
{
    auto                                  instance = std::make_unique<T>(get<typename std::remove_const<Deps>::type>()..., args...);
    std::unique_ptr<InstanceContainer<T>> service  = std::make_unique<InstanceContainer<T>>(std::move(instance));
    mContainer[typeId<T>()]                        = std::move(service);
}

template<typename T>
void ServiceContainer::give(T* service)
{
    auto                                  instance = std::unique_ptr<T>(service);
    std::unique_ptr<InstanceContainer<T>> cservice = std::make_unique<InstanceContainer<T>>(std::move(instance));
    mContainer[typeId<T>()]                        = std::move(cservice);
}

template<typename T>
T* ServiceContainer::get() const
{
    auto it = mContainer.find(typeId<T>());
    assert(it != mContainer.end());

    return static_cast<T*>(it->second->get());
}

template<typename T>
bool ServiceContainer::has() const
{
    auto it = mContainer.find(typeId<T>());

    return it != mContainer.end();
}

template<typename T>
int ServiceContainer::typeId() const
{
    static int id = ++mLastTypeId;

    return id;
}