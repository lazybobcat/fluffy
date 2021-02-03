#pragma once

#include <fluffy/api/context.hpp>
#include <fluffy/api/modules.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/painter.hpp>
#include <fluffy/graphics/render_context.hpp>
#include <fluffy/graphics/render_target.hpp>
#include <fluffy/layer/layer.hpp>
#include <fluffy/layer/layer_stack.hpp>
#include <fluffy/pch.hpp>
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

    virtual bool fixedTimesteps() const { return true; }
    virtual int  getTargetFPS() const { return 60; }
    virtual bool infiniteReload() const { return false; }

    virtual Unique<BaseLayer> start()          = 0;
    virtual String            getTitle() const = 0;

protected:
    virtual void afterInitialize();
    virtual void beforeTerminate();

    void         setStartingState(Unique<BaseLayer> state, const Ref<Context>& context);
    Ref<Context> getContext() const;

    void doFixUpdate(Time dt);
    void doEvents(Time dt);
    void doRender(Time dt);
    void onEvent(Event& event);

private:
    friend GameLoader;
    friend GameLoop;

private:
    Unique<LayerStack> mStateStack;
    Ref<Context>       mContext = nullptr;

    Unique<Painter>      mPainter;
    Unique<Camera>       mCamera;
    Unique<RenderTarget> mScreenTarget;
    Vector2i             mPreviousWindowSize = { -1, -1 };
};
}