#pragma once

#include <fluffy/time/time.hpp>
#include <fluffy/event/event.hpp>
#include <fluffy/graphics/render_context.hpp>

namespace Fluffy {

class ImGuiElement
{
public:
    ImGuiElement()          = default;
    virtual ~ImGuiElement() = default;

    virtual void render(RenderContext& context);
    virtual void update(Time dt);
    virtual void onEvent(Event& event);

    virtual void       show() { mShow = true; }
    virtual void       hide() { mShow = false; }
    [[nodiscard]] bool isVisible() const { return mShow; }

protected:
    virtual void begin();
    virtual void customRender(RenderContext& context) = 0;
    virtual void end();

private:
    bool mShow = true;
};
}