#include "layers/imgui_state.hpp"
#include "layers/sandbox2d_state.hpp"
#include <opengl_video_module.hpp>
#include <iostream>

class EditorState : public State<EditorState>
{
public:
    void initialize() override
    {
    }
    void fixUpdate(Time dt) override
    {
        if (!launched) {
            requestStackPush(CreateUnique<ImGuiState>());
            requestStackPush(CreateUnique<Sandbox2DState>());
        }
    }
    void render(RenderContext& context) override
    {
    }
    void onEvent(Event& event) override
    {
    }

    bool launched = false;
};

class TestGame : public Fluffy::Game
{
public:
    void initializeModules(ModuleRegistry& registry) override
    {
        registry.registerModule(new SystemModule());
        registry.registerModule(new OpenGLVideoModule({getTitle(), WindowType::Windowed, 1280, 720}));
        registry.registerModule(new InputModule());
    }

    Unique<BaseState> start() override
    {
        return CreateUnique<EditorState>();
    }

    [[nodiscard]] std::string getTitle() const override
    {
        return std::string("Fluffy Sandbox");
    }

    [[nodiscard]] int getTargetFPS() const override
    {
        return 120;
    }

    [[nodiscard]] bool fixedTimesteps() const override
    {
        return false;
    }
};

FluffyGame(TestGame)