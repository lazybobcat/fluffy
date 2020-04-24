#include <fluffy/event/event.hpp>
#include <fluffy/game/game_loop.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/time/clock.hpp>

using namespace Fluffy;

GameLoop::GameLoop(GameLoader& loader)
  : mGameLoader(loader)
{
    FLUFFY_LOG_INFO("Starting game {} with Fluffy...", mGameLoader.getGame().getTitle());
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

            // Events
            game.getContext()->video->getWindow()->handleEvents();
            processInput();

            // Update
            game.fixUpdate(timePerFrame);

            // Draw
            game.render(timePerFrame);
            game.getContext()->video->getWindow()->swapBuffers();

            restartClock = true;
        }

        if (restartClock) {
            clock.restart();
            restartClock = false;
        }

        game.variableUpdate(timeSinceLastUpdate);
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