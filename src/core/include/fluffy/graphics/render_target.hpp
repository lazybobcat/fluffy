#pragma once

#include <fluffy/math/rectangle.hpp>

namespace Fluffy {

class Painter;

class RenderTarget
{
public:
    virtual ~RenderTarget() = default;

    [[nodiscard]] virtual IntRect getViewport() const = 0;

    virtual void onBind(Painter& painter) {}
    virtual void onUnbind(Painter& painter) {}
    virtual void onStartDraw(Painter& painter) {}
    virtual void onEndDraw(Painter& painter) {}
};

class ScreenRenderTarget : public RenderTarget
{
public:
    explicit ScreenRenderTarget(const IntRect& viewport);
    virtual ~ScreenRenderTarget() = default;

    [[nodiscard]] IntRect getViewport() const override;

protected:
    IntRect  mViewport;
};
}