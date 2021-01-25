#pragma once

#include <fluffy/api/context.hpp>
#include <fluffy/resources/resource.hpp>
#include <fluffy/resources/resource_library.hpp>

namespace Fluffy {

class BaseResourceCollection;

class ResourceLoader
{
public:
    [[nodiscard]] const String&           getAssetId() const;
    [[nodiscard]] const ResourceLibrary&  getResourceLibrary() const;
    [[nodiscard]] const ResourceMetadata& getMetadata() const;

    Unique<StaticResourceData> getStaticData();

private:
    friend class BaseResourceCollection;

    ResourceLoader(const String& assetId, ResourceType type, const ResourceLibrary& resources);

private:
    const ResourceLibrary& mResources;
    String                 mAssetId;
    ResourceType           mType;
    ResourceMetadata       mMetadata;
};
}