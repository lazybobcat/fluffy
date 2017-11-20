//
// Created by loicb on 20/11/17.
//

#include <Fluffy/State/State.hpp>
#include <Fluffy/State/StateStack.hpp>

using namespace Fluffy::State;

template <typename T>
void BaseState::requestStackPush()
{
    assert(mStateStack);

    mStateStack->push<T>();
}