//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#include <fluffy/event/event.hpp>
#include <fluffy/game/game_loop.hpp>
#include <fluffy/time/clock.hpp>

using namespace Fluffy;

GameLoop::GameLoop(GameLoader& loader)
  : mGameLoader(loader)
{
}

void GameLoop::run()
{
    do {
        runLoop();
    } while (needToReload());
}

void GameLoop::runLoop()
{
    Clock clock;
    Time  timeSinceLastUpdate = Time::Zero;
    Time  timePerFrame        = seconds(1.f / mGameLoader.getGame().getTargetFPS());
    Game& game                = mGameLoader.getGame();

    while (game.isRunning()) {
        Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate >= timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;

            processInput();
            game.update(timePerFrame);
            game.internalUpdate(timePerFrame);
        }

        game.render();
    }
}

bool GameLoop::needToReload()
{
    if (mGameLoader.getGame().infiniteReload()) {
        mGameLoader.reload();

        return true;
    }

    return false;
}

void GameLoop::processInput()
{
    // @todo input handling
}