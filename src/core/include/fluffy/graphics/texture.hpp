#pragma once

#include <fluffy/math/math.hpp>
#include <fluffy/resources/resource.hpp>

namespace Fluffy {

enum class RepeatType
{
    None,
    Repeat,
    MirrorRepeat,
};

class Texture2D : public Resource
{
public:
    Texture2D();
    ~Texture2D();

    bool loadFromFile(const Path& path) override;

    void bind();

    void setRepeat(RepeatType type);
    void setSmooth(bool smooth);
    void generateMipmaps();

    Vector2u getSize() const;

private:
    void updateSmoothness();
    void updateRepeatability();

private:
    unsigned int mTextureId;
    Vector2u     mSize       = { 0, 0 };
    bool         mSmoothed   = false;
    bool         mHasMipMaps = false;
    RepeatType   mRepeat     = RepeatType::None;
};
}
