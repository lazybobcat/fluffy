#include <fluffy/pch.hpp>

using namespace Fluffy;

template<typename E>
Slot EventManager::connect(std::function<void(const E&)> callback)
{
    const BaseGameEvent::Family family = eventFamily<E>();

    if (mConnections.find(family) == mConnections.end()) {
        mConnections[family] = GameEventSignal();
    }

    auto slot = mConnections[family].connect([=](const BaseGameEvent& event) {
        callback(static_cast<const E&>(event));
    });

    return slot;
}

template<typename E>
void EventManager::emit(const E& event)
{
    const BaseGameEvent::Family family = eventFamily<E>();

#if FLUFFY_DEBUG
    FLUFFY_LOG_DEBUG("Emitted event {}", event.toString());
#endif

    if (mConnections.find(family) != mConnections.end()) {
        mConnections[family].emit(event);
    }
}

template<typename E>
BaseGameEvent::Family EventManager::eventFamily()
{
    return GameEvent<typename std::remove_const<E>::type>::family();
}