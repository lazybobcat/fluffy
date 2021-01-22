#pragma once

#include <fluffy/assert.hpp>
#include <fluffy/file/path.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/resources/resource_collection.hpp>

namespace Fluffy {

enum class ResourceType;
class Resource;
class Context;

class ResourceLibrary
{
public:
    explicit ResourceLibrary(const Context& context);
    ~ResourceLibrary() = default;

    template<typename T = Fluffy::Resource>
    void init()
    {
        constexpr ResourceType type = T::getResourceType();
        constexpr auto         id   = (std::size_t)type;

        mCollections.resize(std::max(mCollections.size(), id + 1));
        mCollections[id] = CreateUnique<ResourceCollection<T>>(*this, type);
    }

    template<typename T = Fluffy::Resource>
    ResourceCollection<T>& of() const
    {
        return static_cast<ResourceCollection<T>&>(ofType(T::getResourceType()));
    }

    template<typename T = Fluffy::Resource>
    BaseResourceCollection& ofType(ResourceType type) const
    {
        return *mCollections[(int)type];
    }

    template<typename T = Fluffy::Resource>
    Ref<T> get(const String& assetId) const
    {
        return of<T>().get(assetId);
    }

private:
    const Context&                              mContext;
    std::vector<Unique<BaseResourceCollection>> mCollections;
};

}
