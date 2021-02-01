#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/imgui/imgui_element.hpp>

namespace Fluffy {

struct OpenedWindowTracker
{
    bool profilingWindowOpened      = false;
    bool logsWindowOpened           = false;
    bool viewportWindowOpened       = true;
    bool sceneHierarchyWindowOpened = true;
    bool inspectorWindowOpened      = true;
    bool aboutWindowOpened          = false;
};

class Toolbar : public ImGuiElement
{
public:
    Signal<> OnExit;

public:
    explicit Toolbar(OpenedWindowTracker& tracker);

protected:
    void customRender(RenderContext&) override;

private:
    OpenedWindowTracker& mWindowTracker;
};
}
