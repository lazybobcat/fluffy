#pragma once

#include "../windows/about_window.hpp"
#include "../windows/log_window.hpp"
#include "../windows/profiling_window.hpp"
#include "../windows/toolbar_window.hpp"
#include "../windows/viewport_window.hpp"
#include <fluffy/api/modules.hpp>
#include <fluffy/game/camera_controller.hpp>
#include <fluffy/graphics/rectangle_shape.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/imgui/imgui_container.hpp>
#include <fluffy/input/input.hpp>
#include <fluffy/layer/layer.hpp>
#include <imgui.h>

class EditorState : public Layer<EditorState>
{
public:
    EditorState() {}

    void initialize() override
    {
        // Top toolbar
        container.pack(CreateRef<ToolbarWindow>(openedWindows));
        {
            ImGuiWindowDefinition definition;
            definition.title       = "Logs";
            definition.openControl = &openedWindows.logsWindowOpened;
            container.pack(CreateRef<LogWindow>(definition));
        }

#ifdef FLUFFY_PROFILING_ACTIVE
        container.pack(CreateRef<ProfilingWindow>(ProfilingWindowDefinition("Profiling", &openedWindows.profilingWindowOpened)));
#endif

        // About window
        {
            ImGuiWindowDefinition definition;
            definition.title       = "About";
            definition.openControl = &openedWindows.aboutWindowOpened;
            container.pack(CreateRef<AboutWindow>(definition));
        }

        // Viewport window
        {
            ImGuiWindowDefinition definition;
            definition.title       = "Viewport";
            definition.openControl = &openedWindows.viewportWindowOpened;
            viewportWindow         = CreateRef<ViewportWindow>(definition, *getContext());
            onRenderSlot           = viewportWindow->OnRender.connect(std::bind(&EditorState::renderViewport, this, std::placeholders::_1));
            container.pack(viewportWindow);
        }
    }

    void terminate() override
    {
    }

    void fixUpdate(Time dt) override
    {
        container.update(dt);
    }

    void renderViewport(Painter& painter)
    {
        painter.clear(Color::fromInt8(43, 43, 43, 255));
    }

    void render(RenderContext& context) override
    {
        {
            container.render(context);
        }
    }

    void onEvent(Event& event) override
    {
        if (event.type == Fluffy::Event::MouseButtonPressed) {
            auto position = Input::getMousePosition();
            std::cout << "MousePosition: " << position.x << "," << position.y << std::endl;
            event.stopPropagation();
        }

        if (!event.isStopped()) {
            container.onEvent(event);
        }
    }

private:
    OpenedWindowTracker openedWindows;
    ImGuiContainer      container;

    Ref<ViewportWindow> viewportWindow;

    Ref<Slot> onRenderSlot;
};