#include <fluffy/api/modules.hpp>
#include <fluffy/fluffy_core.hpp>
#include <fluffy/fluffy_utils.hpp>
#include <iostream>

struct ShieldState : public State<ShieldState>
{
    void update(Time dt) override
    {
        FLUFFY_LOG_DEBUG("\t<<<< SHIELD STATE  >>>>");
        requestStackPop();
    }

    void render() override
    {
    }
};

struct NonShieldState : public State<ShieldState>
{
    void update(Time dt) override
    {
        FLUFFY_LOG_DEBUG("\t(: NON SHIELD STATE  :)");
        requestStackPop();
    }

    void render() override
    {
    }

    bool isShielding() const override
    {
        return false;
    }
};

struct TestState : public State<TestState>
{
    int mNbUpdates = 0;

    void update(Time dt) override
    {
        mNbUpdates++;
        FLUFFY_LOG_DEBUG("\tTestState has been updated (iteration " + toString(mNbUpdates) + ") after " + toString(dt.seconds()) + "sec");

        if (mNbUpdates == 2) {
            requestStackPush(std::make_unique<ShieldState>());
        }
        if (mNbUpdates == 5) {
            requestStackPush(std::make_unique<NonShieldState>());
        }
        if (mNbUpdates >= 10) {
            requestStackPop(); // should end the game
        }
    }

    void render() override
    {
    }
};

class TestGame : public Fluffy::Game
{
public:
    void initializeModules(ModuleRegistry& registry) override
    {
        registry.registerModule(new SystemModule());
        registry.registerModule(new VideoModule({getTitle(), WindowType::Windowed, 1280, 720}));
    }

    void update(Time dt) override
    {
        FLUFFY_LOG_DEBUG("New Iteration:");
    }

    void render() override
    {
    }

    BaseState::Ptr start() override
    {
        return std::make_unique<TestState>();
    }

    std::string getTitle() const override
    {
        return std::string("TestGame");
    }
};

FluffyGame(TestGame)