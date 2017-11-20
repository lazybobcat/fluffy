//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#include <Fluffy/State/StateStack.hpp>

using namespace Fluffy::State;

StateStack::PendingChange::PendingChange(Action action, BaseState::Family family)
  : action(action)
  , family(family)
{
}

StateStack::StateStack(EventManager& eventManager)
  : mEventManager(eventManager)
{
    // @todo subscribe to AfterTickEvent once created
}

StateStack::~StateStack()
{
    // @todo unsubscribe from AfterTickEvent once created
    clear();
}

void StateStack::pop()
{
    mPendingList.emplace_back(Action::Pop);
}

void StateStack::clear()
{
    mPendingList.emplace_back(Action::Clear);
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

BaseState::Ptr StateStack::createState(BaseState::Family family)
{
    auto found = mFactories.find(family);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (PendingChange change : mPendingList) {
        switch (change.action) {
            case Action::Push:
                if (!mStack.empty()) {
                    mStack.back()->pause();
                }
                mStack.push_back(createState(change.family));
                break;

            case Action::Pop:
                mStack.back()->terminate();
                mStack.pop_back();
                if (!mStack.empty()) {
                    mStack.back()->resume();
                }
                break;

            case Action::Clear:
                for (BaseState::Ptr& state : mStack) {
                    state->terminate();
                }
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}