#pragma once

#include <fluffy/file/filesystem.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/resources/resource_metadata.hpp>

namespace Fluffy {

class ResourceLibrary;
class BaseResourceCollection;

enum class ResourceType
{
    BinaryFile,
    TextFile,
    Texture,
    Shader,
    Material,
    Font,
    Sound,
    Music,
    Mesh,
    Prefab,
    Scene
};

namespace EnumNames {
const std::array<const char*, 11>
  ResourceType({ { "binary_file",
                   "text_file",
                   "texture",
                   "shader",
                   "material",
                   "font",
                   "sound",
                   "music",
                   "mesh",
                   "prefab",
                   "scene" } });
}

class Resource
{
public:
    Resource()          = default;
    virtual ~Resource() = default;

    [[nodiscard]] const String& getAssetId() const;
    [[nodiscard]] int           getAssertVersion() const;

    [[nodiscard]] const ResourceMetadata& getMetadata() const;
    [[nodiscard]] bool                    hasMetadata() const;

    /**
     * You want to implement these methods in your resources :
     */
    /// static constexpr ResourceType getResourceType();
    /// static Ref<T> loadResource(ResourceLoader& loader);
protected:
    virtual void onLoaded(const ResourceLibrary& resourceLibrary);
    virtual void onReload(Ref<Resource> resource);

private:
    friend class ResourceLibrary;
    friend class BaseResourceCollection;

    void setAssetId(String id);
    void setMetadata(ResourceMetadata metadata);
    void reloadResource(Ref<Resource> resource);

private:
    ResourceMetadata mMetadata;
    String           mAssetId;
    int              mAssetVersion = 0;
    bool             mHasMetadata  = false;
};

class BaseResourceData
{
public:
    explicit BaseResourceData(const Path& filepath);
    virtual ~BaseResourceData() = default;

    [[nodiscard]] const Path& getPath() const;

private:
    Path mPath;
};

class StaticResourceData : public BaseResourceData
{
public:
    StaticResourceData(const void* data, std::size_t size, const Path& filepath);

    static Unique<StaticResourceData> loadFromFile(const Path& filepath);

    [[nodiscard]] const void*           getData() const;
    [[nodiscard]] std::span<const Byte> getBytes() const;
    [[nodiscard]] String                getString() const;
    [[nodiscard]] std::size_t           getSize() const;

    void writeToFile(const Path& path) const;

private:
    void set(const void* data, std::size_t size);

private:
    Ref<const char> mData;
    std::size_t     mSize   = 0;
    bool            mLoaded = false;
};
}
