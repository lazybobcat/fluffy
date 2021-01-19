#pragma once

#include <fluffy/api/modules.hpp>
#include <fluffy/graphics/painter.hpp>

namespace Fluffy {

class OpenGLVideoModule : public VideoModule
{
public:
    explicit OpenGLVideoModule(Window::Definition&& windowDefinition);

public:
    int getMaxTextureSlots() override;

    Unique<ScreenRenderTarget> createScreenRenderTarget() override;
    Unique<Painter>            createPainter() override;

    void beginRender() override;
    void endRender() override;

protected:
    Unique<Window> createWindow(const Window::Definition& definition) override;
};
}
