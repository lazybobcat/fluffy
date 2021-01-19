#include <fluffy/graphics/render_target.hpp>
#include <fluffy/pch.hpp>

using namespace Fluffy;

ScreenRenderTarget::ScreenRenderTarget(const IntRect& viewport) : mViewport(viewport)
{
    FLUFFY_LOG_INFO("A new screen render target has been created with viewport={}", viewport);
}

IntRect ScreenRenderTarget::getViewport() const
{
    return mViewport;
}
