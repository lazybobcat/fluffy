#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/event/event_manager.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/state/state.hpp>

namespace Fluffy {

class StateStack
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(const Ref<Context>& context);
    ~StateStack();

    void push(Unique<BaseState> state);
    void pop();
    void clear();

    bool isEmpty() const;

    void fixUpdate(Time dt);
    void render(Time dt);
    void onEvent(Event& event);

    /**
     * You should NEVER user this method and rely on the triggering of BeforeGameTickEvent and AfterGameTickEvent for
     * the changes to be applied.
     *
     * But if you don't use these events nor Fluffy default loop, you can force the changes to be applied. Be sure to do
     * this only once the states have finished their updates/iterations to avoid any segfault.
     */
    void forcePendingChanges();

private:
    void applyPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action action);
        PendingChange(Action action, Unique<BaseState> state);

        Action            action;
        Unique<BaseState> state;
    };

private:
    Ref<Context>                   mContext;
    std::vector<Unique<BaseState>> mStack;
    std::vector<PendingChange>     mPendingList;

#if FLUFFY_DEBUG
public:
    std::size_t pendingListSize() const { return mPendingList.size(); };
#endif
};
}
