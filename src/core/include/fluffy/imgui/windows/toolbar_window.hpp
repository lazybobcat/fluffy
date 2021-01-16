#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/imgui/imgui_element.hpp>

namespace Fluffy {

struct OpenedWindowTracker
{
    bool profilingWindowOpened = true;
    bool aboutWindowOpened     = false;
};

class ToolbarWindow : public ImGuiElement
{
public:
    explicit ToolbarWindow(OpenedWindowTracker& tracker);

protected:
    void customRender() override;

private:
    OpenedWindowTracker& mWindowTracker;
};
}
