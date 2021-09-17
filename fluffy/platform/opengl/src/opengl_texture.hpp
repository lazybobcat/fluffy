#pragma once

#include <fluffy/graphics/texture.hpp>
#include <glad/glad.h>

namespace Fluffy {

class OpenglTexture2D : public Texture2D
{
public:
    OpenglTexture2D();
    OpenglTexture2D(std::uint32_t width, std::uint32_t height);
    OpenglTexture2D(const Path& path, const IntRect& area = IntRect());
    ~OpenglTexture2D();

    bool loadFromFile(const Path& path);
    void setData(void* data, std::size_t size) override;

    void bind(std::uint32_t slot = 0) override;
    void unbind() override;

    void setRepeat(RepeatType type) override;
    void setSmooth(bool smooth) override;
    void generateMipmaps() override;

    bool isRepeated() const override;

    [[nodiscard]] Vector2u      getSize() const override;
    [[nodiscard]] GLuint        getRendererIdOpenGL() const;
    [[nodiscard]] std::uint64_t getRendererId() const;

private:
    void create(unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int dataFormat);
    bool doLoad(int width, int height, int channels, unsigned char* data);
    void updateSmoothness();
    void updateRepeatability();

private:
    std::uint32_t mTextureId  = 0;
    Vector2u      mSize       = { 0, 0 };
    bool          mSmoothed   = false;
    bool          mHasMipMaps = false;
    RepeatType    mRepeat     = RepeatType::None;
    IntRect       mArea;
    GLenum        mInternalFormat, mDataFormat;
};
}
