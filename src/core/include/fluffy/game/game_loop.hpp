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
    bool needToReload();

private:
    GameLoader& mGameLoader;
};
}