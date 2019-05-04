//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#pragma once

#include <fluffy/context/context.hpp>
#include <fluffy/state/state.hpp>
#include <fluffy/state/state_stack.hpp>
#include <fluffy/time/time.hpp>
#include <string>
#include <vector>

namespace Fluffy {

class GameLoader;
class GameLoop;

class Game
{
public:
    virtual ~Game() = default;

    virtual void initialize(const Context& /*context*/, const std::vector<std::string> /*args*/) {}

    bool isRunning() const;

    virtual int  getTargetFPS() const { return 60; }
    virtual bool infiniteReload() const { return false; }

    virtual void           update(Time dt)  = 0;
    virtual void           render()         = 0;
    virtual BaseState::Ptr start()          = 0;
    virtual std::string    getTitle() const = 0;

private:
    friend GameLoader;
    friend GameLoop;

    void setStartingState(BaseState::Ptr state, const Context& context);
    void internalUpdate(Time dt);

private:
    std::unique_ptr<StateStack> mStateStack;
};
}