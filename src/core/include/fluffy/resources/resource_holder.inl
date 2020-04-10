#pragma once

using namespace Fluffy;

template<typename Resource>
typename Resource::Identifier ResourceHolder<Resource>::load(const Fluffy::Path& path)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(path)) {
        FLUFFY_LOG_ERROR("Failed to load resource from " + path.toString());

        return Resource::InvalidIdentifier;
    }

    return insertResource(std::move(resource));
}

template<typename Resource>
template<typename Parameter>
typename Resource::Identifier ResourceHolder<Resource>::load(const Fluffy::Path& path, const Parameter& secondParameter)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(path, secondParameter)) {
        FLUFFY_LOG_ERROR("Failed to load resource from " + path.toString());

        return Resource::InvalidIdentifier;
    }

    return insertResource(std::move(resource));
}

template<typename Resource>
typename Resource::Identifier ResourceHolder<Resource>::insertResource(std::unique_ptr<Resource> resource)
{
    std::unique_lock<std::mutex> lock(mMutex);

    typename Resource::Identifier id       = mNextId++;
    auto                          inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);

    return id;
}

template<typename Resource>
Resource& ResourceHolder<Resource>::get(typename Resource::Identifier id)
{
    std::unique_lock<std::mutex> lock(mMutex);

    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        FLUFFY_LOG_ERROR("Resource not found for ID " + id);

        return nullptr;
    }

    return *found->second;
}

template<typename Resource>
const Resource& ResourceHolder<Resource>::get(typename Resource::Identifier id) const
{
    std::unique_lock<std::mutex> lock(mMutex);

    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        FLUFFY_LOG_ERROR("Resource not found for ID " + id);

        return nullptr;
    }

    return *found->second;
}
