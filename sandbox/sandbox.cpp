#include "layers/test_state.hpp"
#include <iostream>


class TestGame : public Fluffy::Game
{
public:
    void initializeModules(ModuleRegistry& registry) override
    {
        registry.registerModule(new SystemModule());
        registry.registerModule(new VideoModule({getTitle(), WindowType::Windowed, 1280, 720}));
        registry.registerModule(new InputModule());
    }

    Unique<BaseState> start() override
    {
        return CreateUnique<TestState>();
    }

    [[nodiscard]] std::string getTitle() const override
    {
        return std::string("Fluffy Test");
    }

    [[nodiscard]] int getTargetFPS() const override
    {
        return 120;
    }
};

FluffyGame(TestGame)