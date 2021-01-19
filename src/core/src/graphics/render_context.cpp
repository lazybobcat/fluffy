#include <fluffy/graphics/render_context.hpp>

using namespace Fluffy;

Fluffy::RenderContext::RenderContext(Painter& painter, Camera& camera, RenderTarget& renderTarget)
  : mPainter(painter)
  , mCamera(camera)
  , mDefaultRenterTarget(renderTarget)
{
}

RenderContext::RenderContext(RenderContext&& context)
  : mPainter(context.mPainter)
  , mCamera(context.mCamera)
  , mDefaultRenterTarget(context.mDefaultRenterTarget)
{
}

RenderContext RenderContext::with(Camera& camera) const
{
    return RenderContext(mPainter, camera, mDefaultRenterTarget);
}

RenderContext RenderContext::with(RenderTarget& renderTarget) const
{
    return RenderContext(mPainter, mCamera, renderTarget);
}

void RenderContext::bind(const std::function<void(Painter&)>& f)
{
    pushContext();
    setActive();
    f(mPainter);
    setInactive();
    popContext();
}

void RenderContext::setActive()
{
    mPainter.bind(*this);
}

void RenderContext::setInactive()
{
    mPainter.unbind(*this);
}

void RenderContext::pushContext()
{
    mPreviousContext = mPainter.mActiveContext;
}

void RenderContext::popContext()
{
    if (mPreviousContext) {
        mPreviousContext->setActive();
        mPreviousContext = nullptr;
    }
}

Camera& RenderContext::getCamera() const
{
    return mCamera;
}

RenderTarget& RenderContext::getDefaultRenderTarget()
{
    return mDefaultRenterTarget;
}
