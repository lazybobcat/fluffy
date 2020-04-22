#include <fluffy/event/event_manager.hpp>
#include <fluffy/pch.hpp>

using namespace Fluffy;

template<typename E>
Slot EventManager::connect(std::function<void(const E&)> callback)
{
    const BaseEvent::Family family = eventFamily<E>();

    if (mConnections.find(family) == mConnections.end()) {
        mConnections[family] = EventSignal();
    }

    auto slot = mConnections[family].connect([=](const BaseEvent& event) {
        callback(static_cast<const E&>(event));
    });

    return slot;
}

template<typename E>
void EventManager::emit(const E& event)
{
    const BaseEvent::Family family = eventFamily<E>();

#if FLUFFY_DEBUG
    FLUFFY_LOG_DEBUG("Emitted event " + event.toString());
#endif

    if (mConnections.find(family) != mConnections.end()) {
        mConnections[family].emit(event);
    }
}

template<typename E>
BaseEvent::Family EventManager::eventFamily()
{
    return Event<typename std::remove_const<E>::type>::family();
}