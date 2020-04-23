#include <fluffy/graphics/platform/opengl.hpp>
#include <fluffy/graphics/platform/opengl_texture.hpp>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

using namespace Fluffy;

OpenglTexture2D::OpenglTexture2D()
{
}

OpenglTexture2D::OpenglTexture2D(const Path& path, const IntRect& area)
  : mArea(area)
{
    loadFromFile(path);
}

OpenglTexture2D::~OpenglTexture2D()
{
    if (mTextureId) {
        glDeleteTextures(1, &mTextureId);
    }
}

void OpenglTexture2D::create(unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int dataFormat)
{
    if (!mTextureId) {
        glGenTextures(1, &mTextureId);
    }

    bind();
    GlCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, nullptr));
}

bool OpenglTexture2D::loadFromFile(const Path& path)
{
    // Load image
    int            width, height, channels;
    unsigned char* data = stbi_load(path.toString().c_str(), &width, &height, &channels, 0);

    if (!data) {
        FLUFFY_LOG_ERROR("stbi_load unable to load file '{}'", path);

        return false;
    }

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4) {
        internalFormat = GL_RGBA8;
        dataFormat     = GL_RGBA;
    } else if (channels == 3) {
        internalFormat = GL_RGB8;
        dataFormat     = GL_RGB;
    }

    // Generate texture
    if (mArea == IntRect(0, 0, 0, 0)) {
        mArea.width  = width;
        mArea.height = height;

        create(mArea.width, mArea.height, internalFormat, dataFormat);
        GlCall(glTexSubImage2D(GL_TEXTURE_2D, 0, mArea.left, mArea.top, mArea.width, mArea.height, dataFormat, GL_UNSIGNED_BYTE, data));
    } else {
        IntRect rectangle = mArea;
        if (rectangle.left < 0)
            rectangle.left = 0;
        if (rectangle.top < 0)
            rectangle.top = 0;
        if (rectangle.left + rectangle.width > width)
            rectangle.width = width - rectangle.left;
        if (rectangle.top + rectangle.height > height)
            rectangle.height = height - rectangle.top;

        create(rectangle.width, rectangle.height, internalFormat, dataFormat);

        unsigned char* pixels = data + channels * (rectangle.left + (width * rectangle.top));
        for (int i = 0; i < rectangle.height; ++i) {
            GlCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, rectangle.width, 1, dataFormat, GL_UNSIGNED_BYTE, pixels));
            pixels += channels * width;
        }

        GlCall(glFlush());
    }

    updateRepeatability();
    updateSmoothness();

    // Update internal data and free resources
    mSize = { static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
    stbi_image_free(data);

    return true;
}

void OpenglTexture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void OpenglTexture2D::setRepeat(RepeatType type)
{
    mRepeat = type;
    bind();
    updateRepeatability();
}

void OpenglTexture2D::setSmooth(bool smooth)
{
    mSmoothed = smooth;
    bind();
    updateSmoothness();
}

void OpenglTexture2D::generateMipmaps()
{
    mHasMipMaps = true;
    bind();
    GlCall(glGenerateMipmap(GL_TEXTURE_2D));
    updateSmoothness();
}

Vector2u OpenglTexture2D::getSize() const
{
    return mSize;
}

void OpenglTexture2D::updateSmoothness()
{
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mSmoothed ? GL_LINEAR : GL_NEAREST));

    if (mHasMipMaps) {
        GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mSmoothed ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
    } else {
        GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mSmoothed ? GL_LINEAR : GL_NEAREST));
    }
}

void OpenglTexture2D::updateRepeatability()
{
    switch (mRepeat) {
        case RepeatType::None:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            break;

        case RepeatType::Repeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;

        case RepeatType::MirrorRepeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
    }
}
