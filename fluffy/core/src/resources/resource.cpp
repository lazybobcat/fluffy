#include <fluffy/assert.hpp>
#include <fluffy/resources/resource.hpp>
#include <fluffy/resources/resource_collection.hpp>
#include <fluffy/resources/resource_library.hpp>
#include <utility>

using namespace Fluffy;

void Resource::setAssetId(String id)
{
    mAssetId = std::move(id);
}

void Resource::setMetadata(ResourceMetadata metadata)
{
    if (!mHasMetadata) {
        mMetadata    = std::move(metadata);
        mHasMetadata = true;
    }
}

void Resource::reloadResource(Ref<Resource> resource)
{
    resource->mAssetVersion = ++mAssetVersion;
    onReload(std::move(resource));
}

void Resource::onLoaded(const ResourceLibrary& resourceLibrary)
{
}

void Resource::onReload(Ref<Resource> resource)
{
}

const String& Resource::getAssetId() const
{
    return mAssetId;
}

int Resource::getAssertVersion() const
{
    return mAssetVersion;
}

const ResourceMetadata& Resource::getMetadata() const
{
    return mMetadata;
}

bool Fluffy::Resource::hasMetadata() const
{
    return mHasMetadata;
}

/**********************************************************************************************************************/

BaseResourceData::BaseResourceData(const Path& filepath)
  : mPath(filepath)
{
}

const Path& BaseResourceData::getPath() const
{
    return mPath;
}

/**********************************************************************************************************************/

Unique<StaticResourceData> StaticResourceData::loadFromFile(const Path& filepath)
{
    char*       buffer = nullptr;
    std::size_t size   = 0;

    bool r = Filesystem::read(&buffer, &size, filepath);
    FLUFFY_ASSERT(r, printString("The file {} could not be read by ResourceData", filepath.toString()).c_str());

    return CreateUnique<StaticResourceData>(buffer, size, filepath);
}

StaticResourceData::StaticResourceData(const void* data, std::size_t size, const Path& filepath)
  : BaseResourceData(filepath)
{
    set(data, size);
}

static void deleter(const char* data)
{
    delete[] data;
}

void StaticResourceData::set(const void* data, std::size_t size)
{
    mData   = Ref<const char>(static_cast<const char*>(data), deleter);
    mSize   = size;
    mLoaded = true;
}

const void* StaticResourceData::getData() const
{
    FLUFFY_ASSERT(mLoaded, "The data has not been loaded yet!");

    return mData.get();
}

std::span<const Byte> StaticResourceData::getBytes() const
{
    return std::span<const Byte>(reinterpret_cast<const Byte*>(getData()), getSize());
}

String StaticResourceData::getString() const
{
    return String(static_cast<const char*>(getData()), getSize());
}

std::size_t StaticResourceData::getSize() const
{
    FLUFFY_ASSERT(mLoaded, "The data has not been loaded yet!");

    return mSize;
}

void StaticResourceData::writeToFile(const Path& path) const
{
    FLUFFY_ASSERT(mLoaded, "The data has not been loaded yet!");

    Filesystem::write(path, mData.get(), mSize);
}
