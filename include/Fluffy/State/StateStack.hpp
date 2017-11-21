//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#ifndef FLUFFY_STATESTACK_HPP
#define FLUFFY_STATESTACK_HPP

#include <Fluffy/Event/EventManager.hpp>
#include <Fluffy/State/State.hpp>
#include <Fluffy/Utility/NonCopyable.hpp>
#include <Fluffy/Utility/ServiceContainer.hpp>
#include <map>
#include <vector>

namespace Fluffy {
namespace State {

class StateStack : Fluffy::Utility::NonCopyable
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(ServiceContainer& serviceContainer);
    ~StateStack();

    template <typename T, typename... Args>
    void registerState(Args&&... args);

    template <typename T>
    void push();

    void pop();
    void clear();

    bool isEmpty() const;

    /**
     * You should NEVER user this method and rely on the triggering of BeforeGameTickEvent and AfterGameTickEvent for
     * the changes to be applied.
     *
     * But if you don't use these events nor Fluffy default loop, you can force the changes to be applied. Be sure to do
     * this only once the states have finished their updates/iterations to avoid any segfault.
     */
    void forcePendingChanges();

private:
    template <typename T>
    static BaseState::Family stateFamily();

    BaseState::Ptr createState(BaseState::Family family);

    void onBeforeGameTickEvent(const BeforeGameTickEvent&);
    void onAfterGameTickEvent(const AfterGameTickEvent&);
    void applyPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action action, BaseState::Family family = BaseState::INVALID);

        Action            action;
        BaseState::Family family;
    };

private:
    ServiceContainer&           mServiceContainer;
    Slot                        mBeforeGameTickSlot;
    Slot                        mAfterGameTickSlot;
    std::vector<BaseState::Ptr> mStack;
    std::vector<PendingChange>  mPendingList;
    std::map<BaseState::Family, std::function<BaseState::Ptr(void)>> mFactories;
};
}
}

#include <Fluffy/State/StateStack.inl>

#endif //FLUFFY_STATESTACK_HPP
