//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#include <Fluffy/State/StateStack.hpp>
#include <cassert>

using namespace Fluffy::State;

template <typename T>
BaseState::Family StateStack::stateFamily()
{
    return State<typename std::remove_const<T>::type>::family();
}

template <typename T, typename... Args>
void StateStack::registerState(Args&&... args)
{
    const BaseState::Family family = stateFamily<T>();

    mFactories[family] = [=]() {
        auto state = BaseState::Ptr(new State<T>(std::forward(args...)));
        state->initialize(this);

        return state;
    };
};

template <typename T>
void StateStack::push()
{
    const BaseState::Family family = stateFamily<T>();

    mPendingList.emplace_back(Action::Push, family);
}