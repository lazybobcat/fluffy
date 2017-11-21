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
    StateStack(ServiceContainer& serviceContainer);
    ~StateStack();

    template <typename T, typename... Args>
    void registerState(Args&&... args);

    template <typename T>
    void push();

    void pop();
    void clear();

    bool isEmpty() const;

private:
    template <typename T>
    static BaseState::Family stateFamily();

    BaseState::Ptr createState(BaseState::Family family);

    // @todo subscribe to TickEvent to applyPendingChanges()
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
    std::vector<BaseState::Ptr> mStack;
    std::vector<PendingChange>  mPendingList;
    std::map<BaseState::Family, std::function<BaseState::Ptr(void)>> mFactories;
};
}
}

#include <Fluffy/State/StateStack.inl>

#endif //FLUFFY_STATESTACK_HPP
