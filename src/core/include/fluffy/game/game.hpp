#pragma once

#include <fluffy/api/context.hpp>
#include <fluffy/api/modules.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/state/state.hpp>
#include <fluffy/state/state_stack.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

class GameLoader;
class GameLoop;

class Game
{
public:
    virtual ~Game() = default;

    virtual void initialize(const std::vector<std::string> /*args*/) {}
    virtual void initializeModules(ModuleRegistry& registry) = 0;
    virtual void terminate(const Context& /*context*/) {}

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