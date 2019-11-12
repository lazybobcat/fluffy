//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/11/17.
//

#pragma once

#include <cstddef>
#include <fluffy/context/context.hpp>
#include <fluffy/time/time.hpp>
#include <memory>

namespace Fluffy {

class StateStack;

/**
 * Internal class, you should use State to create your game states.
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

    virtual void initialize();
    virtual void terminate();

    // If false, States that are further in the StateStack will be updated/drawn until a shielding state is found
    virtual bool isShielding() const;
    virtual void update(Time dt) = 0;
    virtual void render()        = 0;

    void pause();
    void resume();
    bool isPaused() const;

private:
    friend StateStack;

protected:
    void requestStackPush(BaseState::Ptr state);
    void requestStackPop();
    void requestStackClear();

    const Context& getContext();

private:
    static Family mFamilyCounter;

    StateStack*    mStateStack = nullptr;
    const Context* mContext;
    bool           mPaused = false;
};

/**
 * The class to inherit from to create game states.
 *
 * struct TitleState : public State<TitleState> {
 *
 * };
 */
template<typename Derived>
class State : public BaseState
{
public:
    virtual ~State() = default;

    static Family family()
    {
        static Family family = mFamilyCounter++;

        return family;
    }

protected:
    friend StateStack;
};

struct InvalidState : public State<InvalidState>
{
};
}
