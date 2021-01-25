#pragma once

#include <fluffy/graphics/render_target.hpp>
#include <opengl.hpp>

namespace Fluffy {

class OpenGLScreenRenderTarget : public ScreenRenderTarget
{
public:
    explicit OpenGLScreenRenderTarget(const IntRect& viewport);
    virtual ~OpenGLScreenRenderTarget() = default;

    void onBind(Painter& painter) override;
};

class OpenGLTextureRenderTarget : public TextureRenderTarget
{
public:
    OpenGLTextureRenderTarget() = default;
    virtual ~OpenGLTextureRenderTarget();
    void onBind(Painter& painter) override;
    void onUnbind(Painter& painter) override;

private:
    void initialize();
    void terminate();

private:
    std::uint32_t mRendererId = 0;
};
}