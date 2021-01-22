#include <fluffy/event/event.hpp>
#include <fluffy/game/game.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

void Game::internalInitialize()
{
    FLUFFY_PROFILE_FUNCTION();
}

void Game::internalTerminate()
{
    FLUFFY_PROFILE_FUNCTION();
    FLUFFY_LOG_INFO("Game is shutting down");

    mStateStack->clear();
    mPainter->terminate();
}

bool Game::isRunning() const
{
    bool shouldClose = mContext->video->getWindow()->shouldClose();

    return mStateStack && !mStateStack->isEmpty() && !shouldClose;
}

void Game::setStartingState(Unique<BaseState> state, const Ref<Context>& context)
{
    mContext = context;

    if (mContext->video) {
        mPainter = mContext->video->createPainter();
        mPainter->initialize(mContext->video);
    }

    if (!mStateStack) {
        mStateStack = Unique<StateStack>(new StateStack(context));
    }

    mStateStack->push(std::move(state));
    mStateStack->forcePendingChanges();
}

void Game::doFixUpdate(Time dt)
{
    FLUFFY_PROFILE_FUNCTION();
    mStateStack->fixUpdate(dt);
}

void Game::doEvents(Time dt)
{
    FLUFFY_PROFILE_FUNCTION();

    if (nullptr == mContext->video) {
        return;
    }

    auto  window = mContext->video->getWindow();
    Event event;

    window->update();
    while (window->pollEvents(event)) {
        onEvent(event);
    }
}

void Game::doRender(Time dt)
{
    FLUFFY_PROFILE_FUNCTION();
    auto* video = mContext->video;

    if (nullptr == video) {
        return;
    }

    auto windowSize = video->getWindow()->getSize();
    if (windowSize != mPreviousWindowSize) {
        mScreenTarget       = video->createScreenRenderTarget();
        mCamera             = CreateUnique<OrthographicCamera>(FloatRect(windowSize / 2, windowSize));
        mPreviousWindowSize = windowSize;
    }

    RenderContext context(*mPainter, *mCamera, *mScreenTarget);

    video->beginRender();
    mPainter->beginRender();

    mStateStack->render(context);

    mPainter->endRender();
    video->endRender(); // swaps buffers
}

void Game::onEvent(Event& event)
{
    FLUFFY_PROFILE_FUNCTION();
    mStateStack->onEvent(event);
}

Ref<Context> Game::getContext() const
{
    return mContext;
}
