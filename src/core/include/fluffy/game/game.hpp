//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#pragma once

#include <fluffy/service/service_container.hpp>
#include <fluffy/state/state.hpp>
#include <string>
#include <vector>
#include <fluffy/time/time.hpp>

namespace Fluffy {
class Game
{
public:
    virtual ~Game() = default;

    virtual void init(ServiceContainer& /*serviceContainer*/, const std::vector<std::string> /*args*/) {}
    virtual void deInit() {}

    // @todo handling states

    bool isRunning() const
    {
        // @todo return if statestack is empty
        return true;
    }

    virtual int  getTargetFPS() const { return 60; }
    virtual bool infiniteReload() const { return false; }

    virtual void update(Time dt) = 0;
    virtual void render() = 0;
    virtual BaseState::Ptr start()          = 0;
    virtual std::string    getTitle() const = 0;
};
}