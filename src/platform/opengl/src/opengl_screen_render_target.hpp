#pragma once

#include <fluffy/graphics/render_target.hpp>

namespace Fluffy {

class OpenGLScreenRenderTarget : public ScreenRenderTarget
{
public:
    explicit OpenGLScreenRenderTarget(const IntRect& viewport);

    void onBind(Painter& painter) override;
};
}