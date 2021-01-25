#pragma once

#include "../windows/about_window.hpp"
#include "../windows/log_window.hpp"
#include "../windows/profiling_window.hpp"
#include "../windows/toolbar_window.hpp"
#include <fluffy/api/modules.hpp>
#include <fluffy/imgui/imgui_container.hpp>
#include <fluffy/input/input.hpp>
#include <fluffy/state/state.hpp>
#include <imgui.h>

class EditorState : public State<EditorState>
{
public:
    EditorState() {}

    void initialize() override
    {
        // ImGui
        container.pack(CreateRef<ToolbarWindow>(openedWindows));
        {
            ImGuiWindowDefinition logDefinition;
            logDefinition.title       = "Logs";
            logDefinition.openControl = &openedWindows.logsWindowOpened;
            container.pack(CreateRef<LogWindow>(logDefinition));
        }
#ifdef FLUFFY_PROFILING_ACTIVE
        container.pack(CreateRef<ProfilingWindow>(ProfilingWindowDefinition("Profiling", &openedWindows.profilingWindowOpened)));
#endif
        {
            ImGuiWindowDefinition aboutDefinition;
            aboutDefinition.title       = "About";
            aboutDefinition.openControl = &openedWindows.aboutWindowOpened;
            container.pack(CreateRef<AboutWindow>(aboutDefinition));
        }
    }

    void terminate() override
    {
    }

    void fixUpdate(Time dt) override
    {
        container.update(dt);
    }

    void render(RenderContext& context) override
    {
        {
            container.render();
        }
    }

    void onEvent(Event& event) override
    {
        if (event.type == Fluffy::Event::MouseButtonPressed) {
            auto position = Input::getMousePosition();
            std::cout << "MousePosition: " << position.x << "," << position.y << std::endl;
            event.stopPropagation();
        }
    }

private:
    OpenedWindowTracker openedWindows;
    ImGuiContainer      container;
};