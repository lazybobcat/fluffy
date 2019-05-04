//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#include <fluffy/fluffy_core.hpp>

struct ShieldState : public State<ShieldState>
{
    void update(Time dt) override
    {
        std::cout << "\t<<<< SHIELD STATE  >>>>" << std::endl;
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
        std::cout << "\t(: NON SHIELD STATE  :)" << std::endl;
        requestStackPop();
    }

    void render() override
    {
    }

    bool isShielding() const override {
        return false;
    }
};

struct TestState : public State<TestState>
{
    int mNbUpdates = 0;

    void update(Time dt) override
    {
        mNbUpdates++;
        std::cout << "\tTestState has been updated (iteration " << mNbUpdates << ") after " << dt.seconds() << "sec" << std::endl;

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
    void update(Time dt) override
    {
        std::cout << "New Iteration:" << std::endl;
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