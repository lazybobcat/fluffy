//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
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