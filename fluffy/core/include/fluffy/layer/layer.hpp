#pragma once

#include <fluffy/api/context.hpp>
#include <fluffy/graphics/render_context.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

class LayerStack;

/**
 * Internal class, you should use State to create your game states.
 */
class BaseLayer
{
public:
    typedef std::size_t Family;

    static const Family INVALID;

public:
    BaseLayer(const String& name = "Layer");
    virtual ~BaseLayer() = default;

    virtual void initialize();
    virtual void terminate();

    virtual void fixUpdate(Time dt) = 0;
    virtual void begin();
    virtual void render(RenderContext& context) = 0;
    virtual void end();
    virtual void onEvent(Event& event) = 0;

    void pause();
    void resume();

    // If false, States that are further in the StateStack will be updated/drawn until a shielding state is found
    [[nodiscard]] virtual bool isShielding() const;
    [[nodiscard]] bool         isPaused() const;
    [[nodiscard]] String       getName() const;

private:
    friend LayerStack;

    void setOverlay(bool flag);
    bool isOverlay() const;

protected:
    void requestPushLayer(Unique<BaseLayer> state);
    void requestPushOverlay(Unique<BaseLayer> state);
    void requestPopLayer();
    void requestPopOverlay();
    void requestStackClear();

    Ref<Context> getContext();

protected:
    static Family mFamilyCounter;

private:
    String       mName;
    LayerStack*  mLayerStack = nullptr;
    Ref<Context> mContext    = nullptr;
    bool         mPaused     = false;
    bool         mIsOverlay  = false;
};

/**
 * The class to inherit from to create game states.
 *
 * struct TitleLayer : public State<TitleLayer> {
 *
 * };
 */
template<typename Derived>
class Layer : public BaseLayer
{
public:
    virtual ~Layer() = default;

    static Family family()
    {
        static Family family = mFamilyCounter++;

        return family;
    }

protected:
    friend LayerStack;
};

struct InvalidLayer : public Layer<InvalidLayer>
{
};
}
