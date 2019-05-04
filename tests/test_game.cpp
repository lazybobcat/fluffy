//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#include <fluffy/fluffy_core.hpp>

class TestGame : public Fluffy::Game
{
public:
    int mNbUpdates = 0;

    void update(Time dt) override
    {
        mNbUpdates++;
        std::cout << "TestGame has been updated (iteration " << mNbUpdates << ") after " << dt.seconds() << "sec" << std::endl;
    }

    void render() override
    {
    }

    BaseState::Ptr start() override
    {
        return nullptr;
    }

    std::string getTitle() const override
    {
        return std::string("TestGame");
    }

    bool isRunning() const override
    {
        return mNbUpdates < 10;
    }
};

FluffyGame(TestGame)