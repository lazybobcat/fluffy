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

namespace Fluffy
{
namespace State
{

class StateStack;

class BaseState
{
public:
    typedef std::size_t Family;
    typedef std::unique_ptr<BaseState> Ptr;

public:
    BaseState(StateStack& stateStack);
    virtual ~BaseState() = default;

    virtual void initialize();
    virtual void terminate();
    virtual void pause();
    virtual void resume();
    virtual bool isPaused() const;

protected:
    /*template <typename T>
    void requestStackPush<T>();
    void requestStackPop();
    void requestStackClear();*/

protected:
    static Family mFamilyCounter;

    StateStack& mStateStack;
    bool        mPaused = false;
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
    static Family family() {
        static Family family = mFamilyCounter++;

        return family;
    }
};
}
}

#endif //FLUFFY_STATE_HPP
