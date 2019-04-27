//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#include <fluffy/state/state.hpp>
#include <fluffy/state/state_stack.hpp>

using namespace Fluffy;

template<typename T>
void BaseState::requestStackPush()
{
    assert(mStateStack);

    mStateStack->push<T>();
}