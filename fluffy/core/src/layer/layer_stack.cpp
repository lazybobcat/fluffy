#include <fluffy/layer/layer_stack.hpp>

using namespace Fluffy;

LayerStack::PendingChange::PendingChange(Action action)
  : action(action)
  , state()
{
}

LayerStack::PendingChange::PendingChange(LayerStack::Action action, bool overlay)
  : action(action)
  , state()
  , overlay(overlay)
{
}

LayerStack::PendingChange::PendingChange(Action action, Ref<BaseLayer> state, bool overlay)
  : action(action)
  , state(std::move(state))
  , overlay(overlay)
{
}

LayerStack::LayerStack(const Ref<Context>& context)
  : mContext(context)
{
}

LayerStack::~LayerStack()
{
    // Terminate all states and clear the stack
    for (Ref<BaseLayer>& state : mStack) {
        state->terminate();
    }
    mStack.clear();
}

void LayerStack::push(Ref<BaseLayer> state)
{
    mPendingList.emplace_back(Action::Push, std::move(state));
}

void LayerStack::pushOverlay(Ref<BaseLayer> state)
{
    mPendingList.emplace_back(Action::Push, std::move(state), true);
}

void LayerStack::pop()
{
    mPendingList.emplace_back(Action::Pop);
}

void LayerStack::popOverlay()
{
    mPendingList.emplace_back(Action::Pop, true);
}

void LayerStack::clear()
{
    mPendingList.emplace_back(Action::Clear);
}

bool LayerStack::isEmpty() const
{
    return mStack.empty();
}

void LayerStack::fixUpdate(Time dt)
{
    for (auto it = mStack.rbegin(); it != mStack.rend(); ++it) {
        if (!(*it)->isPaused()) {
            (*it)->fixUpdate(dt);

            if ((*it)->isShielding()) {
                break;
            }
        }
    }

    applyPendingChanges();
}

void LayerStack::render(RenderContext& context)
{
    for (Ref<BaseLayer>& state : mStack) {
        state->begin();
    }

    for (Ref<BaseLayer>& state : mStack) {
        state->render(context);
    }

    for (Ref<BaseLayer>& state : mStack) {
        state->end();
    }
}

void LayerStack::onEvent(Event& event)
{
    for (auto it = mStack.rbegin(); it != mStack.rend(); ++it) {
        (*it)->onEvent(event);
        if ((*it)->isShielding() || event.isStopped()) {
            break;
        }
    }
}

void LayerStack::forcePendingChanges()
{
    applyPendingChanges();
}

void LayerStack::applyPendingChanges()
{
    for (auto& change : mPendingList) {
        switch (change.action) {
            case Action::Push:
                if (!mStack.empty() && mLayerInsertIndex > 0) {
                    if (!mStack.at(mLayerInsertIndex - 1)->isOverlay()) {
                        mStack.at(mLayerInsertIndex - 1)->pause();
                    }
                }

                // Setup the state
                change.state->mLayerStack = this;
                change.state->mContext    = mContext;

                change.state->initialize();

                // Push it!
                if (change.overlay) {
                    change.state->setOverlay(true);
                    mStack.emplace_back(std::move(change.state));
                } else {
                    mStack.emplace(mStack.begin() + mLayerInsertIndex, std::move(change.state));
                    mLayerInsertIndex++;
                }
                break;

            case Action::Pop:
                if (change.overlay) {
                    if (mStack.back()->isOverlay()) {
                        mStack.back()->terminate();
                        mStack.pop_back();
                    }
                } else {
                    std::vector<Ref<BaseLayer>>::iterator position = mStack.end();
                    for (auto it = mStack.begin(); it != mStack.end(); ++it) {
                        if (!(*it)->isOverlay()) {
                            position = it;
                        }
                    }
                    if (position != mStack.end()) {
                        (*position)->terminate();
                        mStack.erase(position);
                        mLayerInsertIndex--;
                    }
                }
                break;

            case Action::Clear:
                for (Ref<BaseLayer>& state : mStack) {
                    state->terminate();
                }
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}
