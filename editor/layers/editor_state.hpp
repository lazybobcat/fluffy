#pragma once

#include "ui/panels/about_window.hpp"
#include "ui/panels/add_component_window.hpp"
#include "ui/panels/inspector_panel.hpp"
#include "ui/panels/log_window.hpp"
#include "ui/panels/profiling_window.hpp"
#include "ui/panels/scene_hierarchy_panel.hpp"
#include "ui/panels/toolbar.hpp"
#include "ui/panels/viewport_window.hpp"
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
    void openAddComponentWindow(Entity entity);

private:
    Time slowUpdateTimer = Time::Zero;

    OpenedWindowTracker openedWindows;
    ImGuiContainer      container;
    Ref<Scene>          scene = nullptr;

    // Viewport panel
    Ref<ViewportWindow> viewportWindow;
    Ref<Slot>           onRenderSlot;

    // Scene hierarchy panel
    Ref<SceneHierarchyPanel> sceneWindow;

    // Inspector window
    Ref<InspectorPanel> inspectorWindow;

    // Add component window
    Ref<AddComponentWindow> addComponentWindow;
};