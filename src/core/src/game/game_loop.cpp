#include <fluffy/game/game_loop.hpp>
#include <fluffy/profiling/profiler.hpp>
#include <thread>

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
        timeSinceLastUpdate = clock.elapsedTime();

        if (timeSinceLastUpdate >= timePerFrame) {
            FLUFFY_PROFILE_FRAME_TIME(timeSinceLastUpdate);
            while (timeSinceLastUpdate >= timePerFrame) {
                FLUFFY_PROFILE_FRAME();
                timeSinceLastUpdate -= timePerFrame;

                // Events
                game.doEvents(timePerFrame);

                // Update
                game.doFixUpdate(timePerFrame);

                // Render
                game.doRender(timePerFrame);

                FLUFFY_PROFILE_END_FRAME();
            }

            clock.restart();
        } else {
            std::this_thread::yield();
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
