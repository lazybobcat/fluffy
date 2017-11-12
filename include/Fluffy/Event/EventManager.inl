//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#include <Fluffy/Event/EventManager.hpp>

using namespace Fluffy::Event;

template <typename E>
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

template <typename E>
void EventManager::emit(const E& event)
{
    const BaseEvent::Family family = eventFamily<E>();

    if (mConnections.find(family) != mConnections.end()) {
        mConnections[family].emit(event);
    }
}

template <typename E>
BaseEvent::Family EventManager::eventFamily()
{
    return Event<typename std::remove_const<E>::type>::family();
}