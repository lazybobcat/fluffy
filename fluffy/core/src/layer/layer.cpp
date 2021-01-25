#include <fluffy/assert.hpp>
#include <fluffy/layer/layer.hpp>
#include <fluffy/layer/layer_stack.hpp>

using namespace Fluffy;

BaseLayer::Family       BaseLayer::mFamilyCounter = 0;
const BaseLayer::Family BaseLayer::INVALID        = InvalidLayer::family();

BaseLayer::BaseLayer(const String& name)
  : mName(name)
{
}

void BaseLayer::initialize()
{
}

void BaseLayer::terminate()
{
}

void BaseLayer::begin()
{
}

void BaseLayer::end()
{
}

bool BaseLayer::isShielding() const
{
    return true;
}

void BaseLayer::pause()
{
    mPaused = true;
}

void BaseLayer::resume()
{
    mPaused = false;
}

bool BaseLayer::isPaused() const
{
    return mPaused;
}

void BaseLayer::requestPushLayer(Unique<BaseLayer> state)
{
    FLUFFY_ASSERT(mLayerStack, "StateStack has not be defined, you shouldn't use States outside of a StateStack");

    mLayerStack->push(std::move(state));
}

void BaseLayer::requestPushOverlay(Unique<BaseLayer> state)
{
    FLUFFY_ASSERT(mLayerStack, "StateStack has not be defined, you shouldn't use States outside of a StateStack");

    mLayerStack->pushOverlay(std::move(state));
}

void BaseLayer::requestPopLayer()
{
    FLUFFY_ASSERT(mLayerStack, "StateStack has not be defined, you shouldn't use States outside of a StateStack");

    mLayerStack->pop();
}

void BaseLayer::requestPopOverlay()
{
    FLUFFY_ASSERT(mLayerStack, "StateStack has not be defined, you shouldn't use States outside of a StateStack");

    mLayerStack->popOverlay();
}

void BaseLayer::requestStackClear()
{
    FLUFFY_ASSERT(mLayerStack, "StateStack has not be defined, you shouldn't use States outside of a StateStack");

    mLayerStack->clear();
}

Ref<Context> BaseLayer::getContext()
{
    return mContext;
}

String BaseLayer::getName() const
{
    return mName;
}

void BaseLayer::setOverlay(bool flag)
{
    mIsOverlay = flag;
}
bool BaseLayer::isOverlay() const
{
    return mIsOverlay;
}
