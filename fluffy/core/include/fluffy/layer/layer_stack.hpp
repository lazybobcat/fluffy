#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/event/event_manager.hpp>
#include <fluffy/graphics/render_context.hpp>
#include <fluffy/layer/layer.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class LayerStack
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    explicit LayerStack(const Ref<Context>& context);
    ~LayerStack();

    void push(Ref<BaseLayer> state);
    void pushOverlay(Ref<BaseLayer> state);
    void pop();
    void popOverlay();
    void clear();

    bool isEmpty() const;

    void fixUpdate(Time dt);
    void render(RenderContext& context);
    void onEvent(Event& event);

    /**
     * You should NEVER use this method.
     *
     * But if you don't use Fluffy default loop, you can force the changes to be applied. Be sure to do
     * this only once the states have finished their updates/iterations to avoid any segfault.
     */
    void forcePendingChanges();

private:
    void applyPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action action);
        PendingChange(Action action, bool overlay);
        PendingChange(Action action, Ref<BaseLayer> state, bool overlay = false);

        Action         action;
        Ref<BaseLayer> state;
        bool           overlay = false;
    };

private:
    Ref<Context>                mContext;
    std::vector<Ref<BaseLayer>> mStack;
    std::vector<PendingChange>  mPendingList;
    std::uint32_t               mLayerInsertIndex = 0;

#if FLUFFY_UNIT_TESTING
public:
    std::size_t pendingListSize() const { return mPendingList.size(); };
#endif
};
}
