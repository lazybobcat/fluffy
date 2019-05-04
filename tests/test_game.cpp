//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#include <fluffy/fluffy_core.hpp>

class TestState : public State<TestState>
{
    int mNbUpdates = 0;

    void update(Time dt) override
    {
        mNbUpdates++;
        std::cout << "TestState has been updated (iteration " << mNbUpdates << ") after " << dt.seconds() << "sec" << std::endl;

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
        std::cout << "TestGame has been updated" << std::endl;
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