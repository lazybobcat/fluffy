#pragma once

#include <fluffy/graphics/texture.hpp>

namespace Fluffy {

class OpenglTexture2D : public Resource
  , public Texture2D
{
public:
    OpenglTexture2D();
    explicit OpenglTexture2D(const Path& path);
    ~OpenglTexture2D();

    bool loadFromFile(const Path& path) override;

    void bind() override;

    void setRepeat(RepeatType type) override;
    void setSmooth(bool smooth) override;
    void generateMipmaps() override;

    [[nodiscard]] Vector2u getSize() const override;

private:
    void updateSmoothness();
    void updateRepeatability();

private:
    std::uint32_t mTextureId;
    Vector2u      mSize       = { 0, 0 };
    bool          mSmoothed   = false;
    bool          mHasMipMaps = false;
    RepeatType    mRepeat     = RepeatType::None;
};
}
