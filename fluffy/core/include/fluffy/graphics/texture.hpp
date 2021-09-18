#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/file/path.hpp>
#include <fluffy/math/math.hpp>
#include <fluffy/math/rectangle.hpp>
#include <fluffy/resources/resource.hpp>
#include <fluffy/resources/resource_loader.hpp>

namespace Fluffy {

enum class RepeatType
{
    None,
    Repeat,
    MirrorRepeat,
};

class Texture : public Resource
{
public:
    virtual ~Texture() = default;

    virtual void bind(std::uint32_t slot = 0) = 0;
    virtual void unbind()                     = 0;

    virtual void setData(void* data, std::size_t size) = 0;

    [[nodiscard]] virtual Vector2u getSize() const = 0;
};

class Texture2D : public Texture
{
public:
    virtual ~Texture2D() = default;

    static constexpr ResourceType getResourceType() { return ResourceType::Texture; }
    static Ref<Texture2D>         loadResource(ResourceLoader& loader);
    static Ref<Texture2D>         create(std::uint32_t width, std::uint32_t height);
    static Ref<Texture2D>         create(const Path& path, const IntRect& area = IntRect());

    virtual void setRepeat(RepeatType type) = 0;
    virtual void setSmooth(bool smooth)     = 0;
    virtual void generateMipmaps()          = 0;

    virtual bool isRepeated() const = 0;
};
}
