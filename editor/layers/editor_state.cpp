#include "editor_state.hpp"

using namespace Fluffy;

void EditorState::initialize()
{
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
            definition.title       = "Scene";
            definition.openControl = &openedWindows.sceneHierarchyWindowOpened;
            definition.scene       = scene;
            sceneWindow            = CreateRef<SceneHierarchyWindow>(definition);
            container.pack(sceneWindow);
        }

        // Inspector window
        {
            ImGuiWindowDefinition definition;
            definition.title                      = "Inspector";
            definition.openControl                = &openedWindows.inspectorWindowOpened;
            inspectorWindow                       = CreateRef<InspectorWindow>(definition);
            inspectorWindow->EntitySelectedSlot   = sceneWindow->OnEntitySelected.connect(std::bind(&InspectorWindow::onEntitySelected, inspectorWindow.get(), std::placeholders::_1));
            inspectorWindow->EntityUnselectedSlot = sceneWindow->OnEntityUnselected.connect(std::bind(&InspectorWindow::onEntityUnselected, inspectorWindow.get()));
            container.pack(inspectorWindow);
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
}

void EditorState::fixUpdate(Time dt)
{
    scene->update(dt);
    container.update(dt);

    slowUpdateTimer += dt;
    if (slowUpdateTimer.seconds() >= 1.f) {
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
