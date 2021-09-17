#include "editor_state.hpp"
#include "modules/fluffy_editor_module.hpp"

using namespace Fluffy;

void EditorState::initialize()
{
    auto module = dynamic_cast<FluffyEditorModule*>(getContext()->software);

    {
        // Scene
        scene = CreateRef<EditorScene>(*getContext());

        // Logo
        {
            auto  entity = scene->createEntity("Logo");
            auto& sc     = entity.add<SpriteComponent>();
            auto& tc     = entity.add<TransformComponent>();
            sc.sprite.setTexture(getContext()->system->getResources().get<Texture2D>("assets/textures/logo.png"));
            tc.setOrigin({ 640.f, 320.f });
        }

        // Background
        {
            auto  entity  = scene->createEntity("Tiles");
            auto& sc      = entity.add<SpriteComponent>();
            auto& tc      = entity.add<TransformComponent>();
            auto  texture = getContext()->system->getResources().get<Texture2D>("assets/textures/tile.png");
            texture->setRepeat(RepeatType::Repeat);
            sc.sprite.setTexture(texture);
            sc.sprite.setSize({ 1920, 1080 });
            //            tc.setOrigin({ 1920 / 2.f, 1080 / 2.f });
            tc.setPosition({ -1920 / 2.f, -1080 / 2.f });
        }

        scene->createEntity("Camera");
    }

    // Top toolbar
    {
        auto toolbar = CreateRef<Toolbar>(openedWindows);
        toolbar->OnNewScene.connect([this] { newScene(); });
        toolbar->OnOpen.connect([this] { openScene(); });
        toolbar->OnSave.connect([this] { saveScene(); });
        toolbar->OnSaveAs.connect([this] { saveSceneAs(); });
        toolbar->OnExit.connect([this] { exit(); });
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
        onComponentAddSlot = sceneWindow->OnOpenAddComponentDialog.connect([this] (Entity entity) { openAddComponentWindow(entity); });
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
        definition.title                     = "Viewport";
        definition.openControl               = &openedWindows.viewportWindowOpened;
        viewportWindow                       = CreateRef<ViewportWindow>(definition, *getContext());
        viewportWindow->EntitySelectedSlot   = sceneWindow->OnEntitySelected.connect(std::bind(&ViewportWindow::onEntitySelected, viewportWindow.get(), std::placeholders::_1));
        viewportWindow->EntityUnselectedSlot = sceneWindow->OnEntityUnselected.connect(std::bind(&ViewportWindow::onEntityUnselected, viewportWindow.get()));
        viewportWindow->EntityUnselectedSlot = sceneWindow->OnEntityUnselected.connect(std::bind(&ViewportWindow::onEntityUnselected, viewportWindow.get()));
        onViewportResizeSlot = viewportWindow->OnViewportResized.connect([&] (Vector2f size) {
            scene->onTargetResize({size.x, size.y});
        });
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
    if (viewportWindow->isPlaying()) {
        scene->update(dt);
    } else {
        scene->updateEditor(dt);
    }

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
    if (Event::KeyPressed == event.type) {
        switch (event.key.code) {
            case Keyboard::Key::N: {
                if (event.key.control)
                    newScene();
            } break;

            case Keyboard::Key::O: {
                if (event.key.control)
                    openScene();
            } break;

            case Keyboard::Key::S: {
                if (event.key.control && !event.key.shift)
                    saveScene();
                else if (event.key.control && event.key.shift)
                  saveSceneAs();
            } break;

            case Keyboard::Key::Q: {
                if (event.key.control)
                    exit();
            } break;

            default:break;
        }
    }

    if (!event.isStopped()) {
        container.onEvent(event);
    }

    scene->onEvent(event);
}

void EditorState::render(RenderContext& context)
{
    auto target = context.with(*viewportWindow->getRenderTarget());
    if (viewportWindow->isPlaying()) {
        scene->render(target);
    } else {
        scene->renderEditor(target, viewportWindow->getCamera());
    }

    container.render(context);
}

void EditorState::terminate()
{
}

void EditorState::openAddComponentWindow(Entity entity)
{
    addComponentWindow->openForEntity(entity);
}

void EditorState::newScene()
{
}

void EditorState::openScene()
{
}

void EditorState::saveScene()
{
}

void EditorState::saveSceneAs()
{
}

void EditorState::exit()
{
    getContext()->video->getWindow()->close();
}
