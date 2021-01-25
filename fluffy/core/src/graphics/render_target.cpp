#include <fluffy/graphics/render_target.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/pch.hpp>
#include <utility>

using namespace Fluffy;

ScreenRenderTarget::ScreenRenderTarget(const IntRect& viewport)
  : mViewport(viewport)
{
    FLUFFY_LOG_INFO("A new screen render target has been created with viewport={}", viewport);
}

IntRect ScreenRenderTarget::getViewport() const
{
    return mViewport;
}

/**********************************************************************************************************************/

void TextureRenderTarget::setTarget(const Ref<Texture2D>& texture)
{
    mTexture  = std::move(texture);
    mViewport = { { 0, 0 }, mTexture->getSize() };
}

const Ref<Texture2D>& TextureRenderTarget::getTexture()
{
    return mTexture;
}

void TextureRenderTarget::setViewPort(IntRect viewport)
{
    mViewport = viewport;
}

IntRect TextureRenderTarget::getViewport() const
{
    return mViewport;
}

void TextureRenderTarget::setDepth(Ref<Texture2D> texture)
{
    mDepthTexture = std::move(texture);
}

const Ref<Texture2D>& TextureRenderTarget::getDepth()
{
    return mDepthTexture;
}
