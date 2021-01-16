#include <fluffy/game/game.hpp>

using namespace Fluffy;

bool Game::isRunning() const
{
    bool shouldClose = mContext->video->getWindow()->shouldClose();

    return mStateStack && !mStateStack->isEmpty() && !shouldClose;
}

void Game::setStartingState(Unique<BaseState> state, const Ref<Context>& context)
{
    mContext = context;

    if (!mStateStack) {
        mStateStack = Unique<StateStack>(new StateStack(context));
    }

    mStateStack->push(std::move(state));
    mStateStack->forcePendingChanges();
}

void Game::fixUpdate(Time dt)
{
    mStateStack->fixUpdate(dt);
}

void Game::render(Time dt)
{
    mStateStack->render(dt);
}

void Game::onEvent(Event& event)
{
    mStateStack->onEvent(event);
}

Ref<Context> Game::getContext() const
{
    return mContext;
}
