#include <fluffy/resources/resource_loader.hpp>
#include <fluffy/serialization/json_serializer.hpp>

using namespace Fluffy;

ResourceLoader::ResourceLoader(const String& assetId, ResourceType type, const ResourceLibrary& resources)
  : mResources(resources)
  , mAssetId(assetId)
  , mType(type)
{
    auto path = Path(assetId + ".meta");

    if (path.exists()) {
        JsonSerializer::deserializeFromFile(path, mMetadata);
    }
}

Unique<StaticResourceData> ResourceLoader::getStaticData()
{
    return StaticResourceData::loadFromFile(mAssetId);
}
const String& ResourceLoader::getAssetId() const
{
    return mAssetId;
}

const ResourceLibrary& ResourceLoader::getResourceLibrary() const
{
    return mResources;
}

const ResourceMetadata& ResourceLoader::getMetadata() const
{
    return mMetadata;
}
