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

    virtual void initialize(const std::vector<String> /*args*/) {}
    virtual void initializeModules(ModuleRegistry& registry) = 0;
    virtual void terminate(const Context& /*context*/) {}

    bool isRunning() const;

    virtual int  getTargetFPS() const { return 60; }
    virtual bool infiniteReload() const { return false; }

    virtual Unique<BaseState> start()          = 0;
    virtual String            getTitle() const = 0;

private:
    friend GameLoader;
    friend GameLoop;

    void         setStartingState(Unique<BaseState> state, const Ref<Context>& context);
    Ref<Context> getContext() const;

    void fixUpdate(Time dt);
    void variableUpdate(Time dt);
    void render(Time dt);
    void onEvent(Event& event);

private:
    Unique<StateStack> mStateStack;
    Ref<Context>       mContext = nullptr;
};
}