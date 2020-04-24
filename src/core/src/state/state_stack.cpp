#include <fluffy/state/state_stack.hpp>

using namespace Fluffy;

StateStack::PendingChange::PendingChange(Action action)
  : action(action)
  , state()
{
}

StateStack::PendingChange::PendingChange(Action action, BaseState::Ptr state)
  : action(action)
  , state(std::move(state))
{
}

StateStack::StateStack(const Ref<Context>& context)
  : mContext(context)
{
}

StateStack::~StateStack()
{
    // Terminate all states and clear the stack
    for (BaseState::Ptr& state : mStack) {
        state->terminate();
    }
    mStack.clear();
}

void StateStack::push(BaseState::Ptr state)
{
    mPendingList.emplace_back(Action::Push, std::move(state));
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

void StateStack::fixUpdate(Time dt)
{
    for (auto it = mStack.rbegin(); it != mStack.rend(); ++it) {
        (*it)->fixUpdate(dt);
        if ((*it)->isShielding()) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::variableUpdate(Time dt)
{
    for (auto it = mStack.rbegin(); it != mStack.rend(); ++it) {
        (*it)->variableUpdate(dt);
        if ((*it)->isShielding()) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::render(Time dt)
{
    for (BaseState::Ptr& state : mStack) {
        state->render(dt);
    }
}

void StateStack::forcePendingChanges()
{
    applyPendingChanges();
}

void StateStack::applyPendingChanges()
{
    for (auto& change : mPendingList) {
        switch (change.action) {
            case Action::Push:
                if (!mStack.empty()) {
                    mStack.back()->pause();
                }
                change.state->initialize();
                mStack.push_back(std::move(change.state));
                mStack.back()->mStateStack = this;
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