//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/04/18.
//

#include <Fluffy/Asset/AssetHolder.hpp>
#include <cassert>

using namespace Fluffy::Asset;

template <typename Resource, typename Identifier>
void AssetHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("AssetHolder failed to load asset from file" + filename);
    }

    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename... Args>
void AssetHolder<Resource, Identifier>::load(Identifier id, const std::string &filename, Args &&... args)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, args...)) {
        throw std::runtime_error("AssetHolder failed to load asset from file" + filename);
    }

    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& AssetHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& AssetHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
void AssetHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}