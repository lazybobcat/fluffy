#include <fluffy/event/event.hpp>
#include <fluffy/game/game_loop.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/time/clock.hpp>

using namespace Fluffy;

GameLoop::GameLoop(GameLoader& loader)
  : mGameLoader(loader)
{
    FLUFFY_LOG_INFO("Starting game " + mGameLoader.getGame().getTitle() + " with Fluffy...");
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
    bool  restartClock        = false;

    while (game.isRunning()) {
        timeSinceLastUpdate = clock.elapsedTime();

        while (timeSinceLastUpdate >= timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;

            processInput();
            game.update(timePerFrame);
            game.internalUpdate(timePerFrame);
            restartClock = true;
        }

        if (restartClock) {
            clock.restart();
            restartClock = false;
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