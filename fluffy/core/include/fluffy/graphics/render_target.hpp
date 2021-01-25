#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/math/rectangle.hpp>

namespace Fluffy {

class Painter;
class Texture2D;

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
    IntRect mViewport;
};

class TextureRenderTarget : public RenderTarget
{
public:
    virtual ~TextureRenderTarget() = default;

    void                  setTarget(const Ref<Texture2D>& texture);
    const Ref<Texture2D>& getTexture();

    void                  setDepth(Ref<Texture2D> texture);
    const Ref<Texture2D>& getDepth();

    void                  setViewPort(IntRect viewport);
    [[nodiscard]] IntRect getViewport() const override;

protected:
    Ref<Texture2D> mTexture      = nullptr;
    Ref<Texture2D> mDepthTexture = nullptr;
    IntRect        mViewport     = { 0, 0, 0, 0 };
};
}