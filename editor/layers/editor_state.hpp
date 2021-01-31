#pragma once

#include "ui/windows/about_window.hpp"
#include "ui/windows/inspector_window.hpp"
#include "ui/windows/log_window.hpp"
#include "ui/windows/profiling_window.hpp"
#include "ui/windows/scene_hierarchy_window.hpp"
#include "ui/windows/toolbar_window.hpp"
#include "ui/windows/viewport_window.hpp"
#include <fluffy/api/modules.hpp>
#include <fluffy/graphics/rectangle_shape.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/imgui/imgui_container.hpp>
#include <fluffy/input/input.hpp>
#include <fluffy/layer/layer.hpp>
#include <fluffy/scene/components.hpp>
#include <fluffy/scene/scene.hpp>
#include <fluffy/text/string.hpp>
#include <imgui.h>

class EditorState : public Layer<EditorState>
{
public:
    EditorState() = default;

    void initialize() override;
    void terminate() override;
    void fixUpdate(Time dt) override;
    void slowUpdate();
    void render(RenderContext& context) override;
    void renderViewport(Painter& painter);
    void onEvent(Event& event) override;

private:
    Time slowUpdateTimer = Time::Zero;

    OpenedWindowTracker openedWindows;
    ImGuiContainer      container;
    Ref<Scene>          scene = nullptr;

    // Viewport panel
    Ref<ViewportWindow> viewportWindow;
    Ref<Slot>           onRenderSlot;

    // Scene hierarchy panel
    Ref<SceneHierarchyWindow> sceneWindow;

    // Inspector window
    Ref<InspectorWindow> inspectorWindow;
};