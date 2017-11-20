//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#include <Fluffy/State/StateStack.hpp>

using namespace Fluffy::State;

BaseState::Family       BaseState::mFamilyCounter = 0;
const BaseState::Family BaseState::INVALID        = InvalidState::family();

void BaseState::initialize(StateStack* stateStack)
{
    mStateStack = stateStack;
}

void BaseState::terminate()
{
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

void BaseState::requestStackPop()
{
    assert(mStateStack);

    mStateStack->pop();
}

void BaseState::requestStackClear()
{
    assert(mStateStack);

    mStateStack->clear();
}