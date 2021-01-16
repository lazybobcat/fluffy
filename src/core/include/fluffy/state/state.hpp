#pragma once

#include <fluffy/api/context.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

class StateStack;

/**
 * Internal class, you should use State to create your game states.
 */
class BaseState
{
public:
    typedef std::size_t Family;

    static const Family INVALID;

public:
    BaseState()          = default;
    virtual ~BaseState() = default;

    virtual void initialize();
    virtual void terminate();

    virtual void fixUpdate(Time dt) = 0;
    virtual void begin();
    virtual void render(Time dt) = 0;
    virtual void end();
    virtual void onEvent(Event& event) = 0;

    void pause();
    void resume();

    // If false, States that are further in the StateStack will be updated/drawn until a shielding state is found
    [[nodiscard]] virtual bool isShielding() const;
    [[nodiscard]] bool         isPaused() const;

private:
    friend StateStack;

protected:
    void requestStackPush(Unique<BaseState> state);
    void requestStackPop();
    void requestStackClear();

    Ref<Context> getContext();

protected:
    static Family mFamilyCounter;

private:
    StateStack*  mStateStack = nullptr;
    Ref<Context> mContext    = nullptr;
    bool         mPaused     = false;
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
