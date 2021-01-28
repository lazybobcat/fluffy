#pragma once

#include "../windows/about_window.hpp"
#include "../windows/log_window.hpp"
#include "../windows/profiling_window.hpp"
#include "../windows/scene_hierarchy_window.hpp"
#include "../windows/toolbar_window.hpp"
#include "../windows/viewport_window.hpp"
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

    void initialize() override
    {
        // Scene
        scene        = CreateRef<Scene>(*getContext());
        auto  entity = scene->createEntity("Square");
        auto& t      = entity.add<TransformComponent>();
        auto& sc     = entity.add<SpriteComponent>();
        sc.rectangle.setSize({ 100.f, 100.f });
        std::cout << "Entity tag=" << entity.get<TagComponent>().tag << std::endl;

        auto [tag, transform] = scene->getEntityRegistry()->get<TagComponent, TransformComponent>(entity);
        std::cout << "Entity tag=" << tag.tag << " and position=" << printString("{}", transform.getPosition()) << std::endl;

        scene->createEntity("Camera");
        scene->createEntity();

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

        // Scene hierarchy window
        {
            SceneHierarchyWindowDefinition definition;
            definition.title         = "Scene";
            definition.openControl   = &openedWindows.sceneHierarchyOpened;
            definition.scene         = scene;
            sceneWindow              = CreateRef<SceneHierarchyWindow>(definition);
            onEntitySelectionChanged = sceneWindow->OnEntitySelected.connect([](Entity entity) {
                auto Ctag = entity.get<TagComponent>();
                std::cout << Ctag.tag << " selected!" << std::endl;
            });
            container.pack(sceneWindow);
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

        // About window
        {
            ImGuiWindowDefinition definition;
            definition.title       = "About";
            definition.openControl = &openedWindows.aboutWindowOpened;
            container.pack(CreateRef<AboutWindow>(definition));
        }
    }

    void terminate() override
    {
    }

    void fixUpdate(Time dt) override
    {
        scene->update(dt);
        container.update(dt);
    }

    void renderViewport(Painter& painter)
    {
        painter.clear(Color::fromInt8(43, 43, 43, 255));
        // draw scene
        auto view = scene->getEntityRegistry()->view<TransformComponent, SpriteComponent>();
        for (auto [entity, transform, sprite] : view.each()) {
            RenderStates states;
            states.transform = transform.getTransformMatrix();
            painter.drawShape(sprite.rectangle, states);
        }
    }

    void render(RenderContext& context) override
    {
        {
            scene->render(context);
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

        scene->onEvent(event);
    }

private:
    OpenedWindowTracker openedWindows;
    ImGuiContainer      container;
    Ref<Scene>          scene = nullptr;

    // Viewport panel
    Ref<ViewportWindow> viewportWindow;
    Ref<Slot>           onRenderSlot;

    // Scene hierarchy panel
    Ref<SceneHierarchyWindow> sceneWindow;
    Ref<Slot>                 onEntitySelectionChanged;
};