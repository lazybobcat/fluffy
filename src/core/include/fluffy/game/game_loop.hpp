#pragma once

#include <fluffy/game/game_loader.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {
class GameLoop
{
public:
    explicit GameLoop(GameLoader& loader);

    void run();

private:
    void runLoop();
    void doFrame(Time& timePerFrame, Game& game) const;
    bool needToReload();

private:
    GameLoader& mGameLoader;
};
}