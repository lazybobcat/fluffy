#include "layers/editor_state.hpp"
#include "layers/imgui_state.hpp"
#include <fluffy/game/game.hpp>
#include <fluffy/game/game_main.hpp>
#include <opengl_video_module.hpp>

namespace Fluffy {

class InitialState : public Layer<InitialState>
{
public:
    void initialize() override {}
    void fixUpdate(Time dt) override
    {
        if (!launched) {
            requestPopLayer();
            requestPushLayer(CreateUnique<ImGuiState>());
            requestPushLayer(CreateUnique<EditorState>());
            launched = true;
        }
    }
    void render(RenderContext& context) override {}
    void onEvent(Event& event) override {}

    bool launched = false;
};

class FluffyEditor : public Fluffy::Game
{
public:
    void initializeModules(ModuleRegistry& registry) override
    {
        registry.registerModule(new SystemModule());
        registry.registerModule(new OpenGLVideoModule({ getTitle(), WindowType::Windowed, 1280, 720 }));
        registry.registerModule(new InputModule());
    }

    Unique<BaseLayer> start() override
    {
        return CreateUnique<InitialState>();
    }

    [[nodiscard]] std::string getTitle() const override
    {
        return std::string("Fluffy Editor");
    }

    [[nodiscard]] int getTargetFPS() const override
    {
        return 120;
    }

    [[nodiscard]] bool fixedTimesteps() const override
    {
        return true;
    }
};
}

FluffyGame(Fluffy::FluffyEditor)