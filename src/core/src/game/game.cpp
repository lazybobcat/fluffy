#include <fluffy/game/game.hpp>

using namespace Fluffy;

bool Game::isRunning() const
{
    return mStateStack && !mStateStack->isEmpty();
}

void Game::setStartingState(BaseState::Ptr state, const Context& context)
{
    if (!mStateStack) {
        mStateStack = std::make_unique<StateStack>(context);
    }

    mStateStack->push(std::move(state));
    mStateStack->forcePendingChanges();
}

void Game::internalUpdate(Time dt)
{
    mStateStack->update(dt);
}