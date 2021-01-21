#pragma once

#include <fluffy/file/path.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

enum class ResourceType;
class ResourceLibrary;
class Resource;
class ResourceLoader;

class BaseResourceCollection
{
public:
    BaseResourceCollection(ResourceLibrary& library, ResourceType type);
    virtual ~BaseResourceCollection() = default;

    [[nodiscard]] std::vector<String> list() const;
    [[nodiscard]] bool                has(const String& assetId) const;

    void add(const String& assetId, Ref<Resource> resource);
    void remove(const String& assetId);
    void clear();
    void reload(const String& assetId);

protected:
    Ref<Resource> getBase(const String& assetId);
    Ref<Resource> doLoadResource(const String& assetId);

    virtual Ref<Resource> loadResource(ResourceLoader& loader) = 0;

private:
    ResourceLibrary&                mResourceLibrary;
    std::map<String, Ref<Resource>> mResources;
    ResourceType                    mType;
    std::mutex                      mMutex;
};

template<typename T = Fluffy::Resource>
class ResourceCollection : public BaseResourceCollection
{
public:
    ResourceCollection(ResourceLibrary& library, ResourceType type)
      : BaseResourceCollection(library, type)
    {}

    Ref<T> get(const String& assetId)
    {
        return std::static_pointer_cast<T>(getBase(assetId));
    }

protected:
    Ref<T> loadResource(ResourceLoader& loader) override
    {
        return T::loadResource(loader);
    }
};

}