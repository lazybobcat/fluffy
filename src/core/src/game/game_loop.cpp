#include <fluffy/event/event.hpp>
#include <fluffy/game/game_loop.hpp>
#include <fluffy/profiling/profiler.hpp>

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
    Clock   clock;
    Time    timeSinceLastUpdate = Time::Zero;
    Time    timePerFrame        = seconds(1.f / mGameLoader.getGame().getTargetFPS());
    Game&   game                = mGameLoader.getGame();
    bool    restartClock        = false;
    Window* window              = game.getContext()->video->getWindow();
    Event   event;

    while (game.isRunning()) {
        timeSinceLastUpdate = clock.elapsedTime();

        while (timeSinceLastUpdate >= timePerFrame) {
            FLUFFY_PROFILE_FRAME();
            timeSinceLastUpdate -= timePerFrame;

            // Events
            {
                FLUFFY_PROFILE_SCOPE("Events");
                window->update();
                while (window->pollEvents(event)) {
                    game.onEvent(event);
                }
                processInput();
            }

            // Update
            {
                FLUFFY_PROFILE_SCOPE("Update");
                game.fixUpdate(timePerFrame);
            }

            // Draw
            {
                FLUFFY_PROFILE_SCOPE("Rendering");
                game.render(timePerFrame);
                window->swapBuffers();
            }

            restartClock = true;
            FLUFFY_PROFILE_END_FRAME();
        }

        if (restartClock) {
            auto elapsed = clock.restart();
            FLUFFY_PROFILE_FRAME_TIME(elapsed);
            restartClock = false;
        }
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