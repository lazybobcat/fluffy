#include "opengl_texture.hpp"
#include "opengl.hpp"
#include <fluffy/profiling/profiler.hpp>
#include <fluffy/resources/resource_loader.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <fluffy/graphics/texture.hpp>
#include <stb_image/stb_image.h>

using namespace Fluffy;

Ref<Texture2D> Texture2D::create(const Path& path, const IntRect& area)
{
    return CreateRef<OpenglTexture2D>(path, area);
}

Ref<Texture2D> Texture2D::create(std::uint32_t width, std::uint32_t height)
{
    return CreateRef<OpenglTexture2D>(width, height);
}

Ref<Texture2D> Texture2D::loadResource(ResourceLoader& loader)
{
    return CreateRef<OpenglTexture2D>(loader.getAssetId());
}

/**********************************************************************************************************************/

OpenglTexture2D::OpenglTexture2D()
{
}

OpenglTexture2D::OpenglTexture2D(const Path& path, const IntRect& area)
  : mArea(area)
{
    loadFromFile(path);
}

OpenglTexture2D::OpenglTexture2D(std::uint32_t width, std::uint32_t height)
  : mSize(width, height)
{
    create(width, height, GL_RGBA8, GL_RGBA);
}

OpenglTexture2D::~OpenglTexture2D()
{
    if (mTextureId) {
        glDeleteTextures(1, &mTextureId);
    }
}

void OpenglTexture2D::create(unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int dataFormat)
{
    FLUFFY_PROFILE_FUNCTION();
    FLUFFY_LOG_DEBUG("Create texture of {}x{}", width, height);

    mInternalFormat = internalFormat;
    mDataFormat     = dataFormat;
    mSize           = { width, height };

    if (!mTextureId) {
        glGenTextures(1, &mTextureId);
    }

    glBindTexture(GL_TEXTURE_2D, mTextureId);
    GlCall(glTexImage2D(GL_TEXTURE_2D, 0, mInternalFormat, width, height, 0, mDataFormat, GL_UNSIGNED_BYTE, nullptr));

    updateRepeatability();
    updateSmoothness();
}

bool OpenglTexture2D::loadFromFile(const Path& path)
{
    FLUFFY_PROFILE_FUNCTION();

    stbi_set_flip_vertically_on_load(false); // we use a reverted Y-axis so we don't need that (0,0) is top-left

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

bool OpenglTexture2D::doLoad(int width, int height, int channels, unsigned char* data)
{
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

void OpenglTexture2D::setData(void* data, std::size_t size)
{
    FLUFFY_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_2D, mTextureId);

    std::uint32_t bpp = (mDataFormat == GL_RGBA) ? 4 : 3;
    FLUFFY_ASSERT(size == (mSize.x * mSize.y * bpp), "The size of the data does not match the texture size!");
    GlCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mSize.x, mSize.y, mDataFormat, GL_UNSIGNED_BYTE, data));
}

void OpenglTexture2D::bind(std::uint32_t slot)
{
    FLUFFY_PROFILE_FUNCTION();

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void OpenglTexture2D::unbind()
{
    FLUFFY_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenglTexture2D::setRepeat(RepeatType type)
{
    mRepeat = type;
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    updateRepeatability();
}

void OpenglTexture2D::setSmooth(bool smooth)
{
    mSmoothed = smooth;
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    updateSmoothness();
}

void OpenglTexture2D::generateMipmaps()
{
    FLUFFY_PROFILE_FUNCTION();

    mHasMipMaps = true;
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    GlCall(glGenerateMipmap(GL_TEXTURE_2D));
    updateSmoothness();
}

Vector2u OpenglTexture2D::getSize() const
{
    return mSize;
}

void OpenglTexture2D::updateSmoothness()
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mSmoothed ? GL_LINEAR : GL_NEAREST));

    if (mHasMipMaps) {
        GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mSmoothed ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
    } else {
        GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mSmoothed ? GL_LINEAR : GL_NEAREST));
    }
}

void OpenglTexture2D::updateRepeatability()
{
    FLUFFY_PROFILE_FUNCTION();

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

std::uint64_t OpenglTexture2D::getRendererId() const
{
    return static_cast<std::uint64_t>(mTextureId);
}

GLuint OpenglTexture2D::getRendererIdOpenGL() const
{
    return mTextureId;
}

bool OpenglTexture2D::isRepeated() const
{
    return mRepeat != RepeatType::None;
}
