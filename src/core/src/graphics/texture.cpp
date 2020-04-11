#include <fluffy/graphics/platform/opengl.hpp>
#include <fluffy/graphics/texture.hpp>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

using namespace Fluffy;

Texture2D::Texture2D()
{
    glGenTextures(1, &mTextureId);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &mTextureId);
}

bool Texture2D::loadFromFile(const Path& path)
{
    // Load image
    stbi_set_flip_vertically_on_load(1);

    int            width, height, channels;
    unsigned char* data = stbi_load(path.toString().c_str(), &width, &height, &channels, 0);

    if (!data) {
        FLUFFY_LOG_ERROR("stbi_load unable to load file '" + path.toString() + "'");

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
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    GlCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data));
    updateRepeatability();
    updateSmoothness();

    // Update internal data and free resources
    mSize = { static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
    stbi_image_free(data);

    return true;
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void Texture2D::setRepeat(RepeatType type)
{
    mRepeat = type;
    updateRepeatability();
}

void Texture2D::setSmooth(bool smooth)
{
    mSmoothed = smooth;
    updateSmoothness();
}

void Texture2D::generateMipmaps()
{
    mHasMipMaps = true;
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    GlCall(glGenerateMipmap(GL_TEXTURE_2D));
    updateSmoothness();
}

Vector2u Texture2D::getSize() const
{
    return mSize;
}

void Texture2D::updateSmoothness()
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mSmoothed ? GL_LINEAR : GL_NEAREST));

    if (mHasMipMaps) {
        GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mSmoothed ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
    } else {
        GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mSmoothed ? GL_LINEAR : GL_NEAREST));
    }
}

void Texture2D::updateRepeatability()
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);

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
