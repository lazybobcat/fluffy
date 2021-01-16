#pragma once

#include <fluffy/time/time.hpp>

namespace Fluffy {

class ImGuiElement
{
public:
    ImGuiElement()          = default;
    virtual ~ImGuiElement() = default;

    virtual void render();
    virtual void update(Time dt);

    virtual void       show() { mShow = true; }
    virtual void       hide() { mShow = false; }
    [[nodiscard]] bool isVisible() const { return mShow; }

protected:
    virtual void begin();
    virtual void customRender() = 0;
    virtual void end();

private:
    bool mShow = true;
};
}