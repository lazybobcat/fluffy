#pragma once

#include <fluffy/assert.hpp>
#include <fluffy/file/path.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/resources/resource.hpp>

namespace Fluffy {

template<typename Resource = Fluffy::Resource>
class ResourceHolder
{
public:
    typename Resource::Identifier load(const Path& path);
    template<typename Parameter>
    typename Resource::Identifier load(const Path& path, const Parameter& secondParameter);

    Resource&       get(typename Resource::Identifier id);
    const Resource& get(typename Resource::Identifier id) const;

private:
    typename Resource::Identifier insertResource(std::unique_ptr<Resource> resource);

private:
    static typename Resource::Identifier                               mNextId;
    mutable std::mutex                                                 mMutex;
    std::map<typename Resource::Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template<typename Resource>
typename Resource::Identifier ResourceHolder<Resource>::mNextId = 0;
}

#include <fluffy/resources/resource_holder.inl>
