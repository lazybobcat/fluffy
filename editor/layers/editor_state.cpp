#include "editor_state.hpp"
#include "modules/fluffy_editor_module.hpp"

using namespace Fluffy;

void EditorState::initialize()
{
    auto module = dynamic_cast<FluffyEditorModule*>(getContext()->software);

    {
        // Scene
        scene        = CreateRef<Scene>(*getContext());

        // Origin
        {
            auto  entity = scene->createEntity("Origin");
            auto& t      = entity.add<TransformComponent>();
            auto& sc     = entity.add<SpriteComponent>();
            sc.rectangle.setSize({ 1.f, 1.f });
            sc.rectangle.setFillColor(Color::Red);
        }

        // Square
        {
            auto  entity = scene->createEntity("Square");
            auto& t      = entity.add<TransformComponent>();
            auto& sc     = entity.add<SpriteComponent>();
            sc.rectangle.setSize({ 100.f, 100.f });
        }

        scene->createEntity("Camera");
    }

    // Top toolbar
    {
        auto toolbar = CreateRef<Toolbar>(openedWindows);
        toolbar->OnExit.connect([&]() {
            getContext()->video->getWindow()->close();
        });
        container.pack(toolbar);
    }

    // Log window
    {
        ImGuiPanelDefinition definition;
        definition.title       = "Logs";
        definition.openControl = &openedWindows.logsWindowOpened;
        container.pack(CreateRef<LogWindow>(definition));
    }

#ifdef FLUFFY_PROFILING_ACTIVE
    container.pack(CreateRef<ProfilingWindow>(ProfilingPanelDefinition("Profiling", &openedWindows.profilingWindowOpened)));
#endif

    // Scene hierarchy window
    {
        SceneHierarchyPanelDefinition definition;
        definition.title       = "Scene";
        definition.openControl = &openedWindows.sceneHierarchyWindowOpened;
        definition.scene       = scene;
        sceneWindow            = CreateRef<SceneHierarchyPanel>(definition);
        container.pack(sceneWindow);
    }

    // Inspector window
    {
        InspectorPanelWindowDefinition definition(module->components(), "Inspector", &openedWindows.inspectorWindowOpened);
        inspectorWindow                       = CreateRef<InspectorPanel>(definition);
        inspectorWindow->EntitySelectedSlot   = sceneWindow->OnEntitySelected.connect(std::bind(&InspectorPanel::onEntitySelected, inspectorWindow.get(), std::placeholders::_1));
        inspectorWindow->EntityUnselectedSlot = sceneWindow->OnEntityUnselected.connect(std::bind(&InspectorPanel::onEntityUnselected, inspectorWindow.get()));
        inspectorWindow->OnAddComponentButtonPressed.connect(std::bind(&EditorState::openAddComponentWindow, this, std::placeholders::_1));
        container.pack(inspectorWindow);
    }

    // Viewport window
    {
        ImGuiPanelDefinition definition;
        definition.title       = "Viewport";
        definition.openControl = &openedWindows.viewportWindowOpened;
        viewportWindow         = CreateRef<ViewportWindow>(definition, *getContext());
        onRenderSlot           = viewportWindow->OnRender.connect(std::bind(&EditorState::renderViewport, this, std::placeholders::_1));
        container.pack(viewportWindow);
    }

    // About window
    {
        ImGuiPanelDefinition definition;
        definition.title       = "About";
        definition.openControl = &openedWindows.aboutWindowOpened;
        container.pack(CreateRef<AboutWindow>(definition));
    }

    // Add component window
    {
        AddComponentWindowDefinition definition(module->components(), "Add component", &openedWindows.addComponentWindowOpened);
        addComponentWindow = CreateRef<AddComponentWindow>(definition);
        container.pack(addComponentWindow);
    }
}

void EditorState::fixUpdate(Time dt)
{
    scene->update(dt);
    container.update(dt);

    slowUpdateTimer += dt;
    if (slowUpdateTimer.seconds() >= 0.25f) {
        slowUpdate();
        slowUpdateTimer = Time::Zero;
    }
}

void EditorState::slowUpdate()
{
    scene->getEntityRegistry()->sort<TagComponent>([](const auto& lhs, const auto& rhs) {
        return lhs.tag < rhs.tag;
    });
}

void EditorState::onEvent(Event& event)
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

void EditorState::renderViewport(Painter& painter)
{
    painter.clear(Color::fromInt8(43, 43, 43, 255));
    // draw scene
    auto view = scene->getEntityRegistry()->view<TransformComponent, SpriteComponent>();
    for (auto [entity, transform, sprite] : view.each()) {
        RenderStates states;
        states.transform = transform.getTransformMatrix();
        sprite.rectangle.setScale(transform.getScale());
        painter.drawShape(sprite.rectangle, states);
    }
}

void EditorState::render(RenderContext& context)
{
    {
        scene->render(context);
        container.render(context);
    }
}

void EditorState::terminate()
{
}

void EditorState::openAddComponentWindow(Entity entity)
{
    addComponentWindow->openForEntity(entity);
}
