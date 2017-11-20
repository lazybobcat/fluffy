//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#ifndef FLUFFY_STATE_HPP
#define FLUFFY_STATE_HPP

#include <cstddef>
#include <memory>

namespace Fluffy {
namespace State {

class StateStack;

/**
 * Internal class, you should use State to create your game states
 */
class BaseState
{
public:
    typedef std::size_t                Family;
    typedef std::unique_ptr<BaseState> Ptr;

    static const Family INVALID;

public:
    BaseState()          = default;
    virtual ~BaseState() = default;

    virtual void initialize(StateStack* mStateStack);
    virtual void terminate();
    void         pause();
    void         resume();
    bool         isPaused() const;

protected:
    /*template <typename T>
    void requestStackPush<T>();
    void requestStackPop();
    void requestStackClear();*/

protected:
    static Family mFamilyCounter;

    StateStack* mStateStack = nullptr;
    bool        mPaused     = false;
};

/**
 * struct TitleState : public State<TitleState> {
 *
 * };
 */
template <typename Derived>
class State : public BaseState
{
public:
    virtual ~State() = default;

    static Family family()
    {
        static Family family = mFamilyCounter++;

        return family;
    }
};

struct InvalidState : public State<InvalidState>
{
};
}
}

#endif //FLUFFY_STATE_HPP
