//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/event/event_manager.hpp>
#include <fluffy/state/state.hpp>
#include <map>
#include <vector>

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
    explicit StateStack(const Context& context);
    ~StateStack();

    void push(BaseState::Ptr state);
    void pop();
    void clear();

    bool isEmpty() const;

    void update(Time dt);
    void render();

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
        PendingChange(Action action, BaseState::Ptr state);

        Action         action;
        BaseState::Ptr state;
    };

private:
    const Context&              mContext;
    std::vector<BaseState::Ptr> mStack;
    std::vector<PendingChange>  mPendingList;

#if FLUFFY_ENV_TEST
public:
    std::size_t pendingListSize() const { return mPendingList.size(); };
#endif
};
}
