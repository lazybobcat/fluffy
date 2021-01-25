#include <fluffy/assert.hpp>
#include <fluffy/resources/resource.hpp>
#include <fluffy/resources/resource_collection.hpp>
#include <fluffy/resources/resource_loader.hpp>

using namespace Fluffy;

BaseResourceCollection::BaseResourceCollection(ResourceLibrary& library, ResourceType type)
  : mResourceLibrary(library)
  , mType(type)
{
}

std::vector<String> BaseResourceCollection::list() const
{
    std::vector<String> list;
    for (const auto& it : mResources) {
        list.push_back(it.first);
    }

    return list;
}

bool BaseResourceCollection::has(const String& assetId) const
{
    return mResources.find(assetId) != mResources.end();
}

void BaseResourceCollection::add(const String& assetId, Ref<Resource> resource)
{
    mResources.emplace(assetId, resource);
}

void BaseResourceCollection::remove(const String& assetId)
{
    mResources.erase(assetId);
}

void BaseResourceCollection::clear()
{
    mResources.clear();
}

void BaseResourceCollection::reload(const String& assetId)
{
    auto it = mResources.find(assetId);
    if (it != mResources.end()) {
        auto newResource = doLoadResource(assetId);
        newResource->setAssetId(assetId);
        newResource->onLoaded(mResourceLibrary);
        it->second->reloadResource(newResource);
        FLUFFY_LOG_INFO("Reloaded asset '{}'.", assetId);
    }
}

Ref<Resource> BaseResourceCollection::getBase(const String& assetId)
{
    // First check in the collection if the resource has already been loaded
    auto it = mResources.find(assetId);
    if (it != mResources.end()) {
        return it->second;
    }

    // If not we load it and add it to the collection
    auto newResource = doLoadResource(assetId);
    newResource->setAssetId(assetId);
    add(assetId, newResource);
    newResource->onLoaded(mResourceLibrary);

    return newResource;
}

Ref<Resource> BaseResourceCollection::doLoadResource(const String& assetId)
{
    ResourceLoader loader(assetId, mType, mResourceLibrary);
    auto           newResource = loadResource(loader);

    FLUFFY_ASSERT((bool)newResource, printString("Unable to build resource from '{}'", assetId).c_str());

    const auto& meta = loader.getMetadata();
    if (meta.isLoaded()) {
        newResource->setMetadata(meta);
    }

    return newResource;
}
