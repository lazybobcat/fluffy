//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#pragma once

#include <fluffy/game/game_loader.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy
{
class GameLoop
{
public:
    explicit GameLoop(GameLoader& loader);

    void run();

private:
    void runLoop();
    bool needToReload();

    void processInput();

private:
    GameLoader& mGameLoader;
};
}