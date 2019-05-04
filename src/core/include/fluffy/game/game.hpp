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
#include <fluffy/time/time.hpp>
#include <string>
#include <vector>

namespace Fluffy {
class Game
{
public:
    virtual ~Game() = default;

    virtual void initialize(const Context & /*context*/, const std::vector<std::string> /*args*/) {}

    // @todo handling states

    virtual bool isRunning() const
    {
        // @todo return if statestack is empty
        return true;
    }

    virtual int  getTargetFPS() const { return 60; }
    virtual bool infiniteReload() const { return false; }

    virtual void           update(Time dt)  = 0;
    virtual void           render()         = 0;
    virtual BaseState::Ptr start()          = 0;
    virtual std::string    getTitle() const = 0;
};
}