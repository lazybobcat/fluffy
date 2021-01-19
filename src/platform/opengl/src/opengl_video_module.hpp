#pragma once

#include <fluffy/api/modules.hpp>
#include <fluffy/graphics/painter.hpp>

namespace Fluffy {

class OpenGLVideoModule : public VideoModule
{
public:
    OpenGLVideoModule(Window::Definition&& windowDefinition);

    Unique<ScreenRenderTarget> createScreenRenderTarget() override;
    Unique<Painter>            createPainter() override;

    void beginRender() override;
    void endRender() override;
};
}
