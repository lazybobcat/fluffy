#include <fluffy/assert.hpp>
#include <fluffy/state/state_stack.hpp>

using namespace Fluffy;

BaseState::Family       BaseState::mFamilyCounter = 0;
const BaseState::Family BaseState::INVALID        = InvalidState::family();

void BaseState::initialize()
{
}

void BaseState::terminate()
{
}

bool BaseState::isShielding() const
{
    return true;
}

void BaseState::pause()
{
    mPaused = true;
}

void BaseState::resume()
{
    mPaused = false;
}

bool BaseState::isPaused() const
{
    return mPaused;
}

void BaseState::requestStackPush(BaseState::Ptr state)
{
    FLUFFY_ASSERT(mStateStack, "StateStack has not be defined, you shouldn't use States outside of a StateStack");

    mStateStack->push(std::move(state));
}

void BaseState::requestStackPop()
{
    FLUFFY_ASSERT(mStateStack, "StateStack has not be defined, you shouldn't use States outside of a StateStack");

    mStateStack->pop();
}

void BaseState::requestStackClear()
{
    FLUFFY_ASSERT(mStateStack, "StateStack has not be defined, you shouldn't use States outside of a StateStack");

    mStateStack->clear();
}

const Context& BaseState::getContext()
{
    return *mContext;
}