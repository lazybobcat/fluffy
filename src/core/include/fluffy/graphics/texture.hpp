#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/math/math.hpp>
#include <fluffy/resources/resource.hpp>

namespace Fluffy {

enum class RepeatType
{
    None,
    Repeat,
    MirrorRepeat,
};

class Texture
{
public:
    virtual ~Texture() = default;

    virtual void                   bind()          = 0;
    [[nodiscard]] virtual Vector2u getSize() const = 0;
};

class Texture2D : public Texture
{
public:
    virtual ~Texture2D() = default;

    static Ref<Texture2D> create(const Path& path);

    virtual void setRepeat(RepeatType type) = 0;
    virtual void setSmooth(bool smooth)     = 0;
    virtual void generateMipmaps()          = 0;
};
}
