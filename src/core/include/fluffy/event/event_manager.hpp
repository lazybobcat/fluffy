#pragma once

#include <fluffy/event/event.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class EventManager
{
public:
    template<typename E>
    Slot connect(std::function<void(const E&)> callback);

    /**
     * You should prefer to use slot.disconnect() directly
     *
     * @param Slot slot
     */
    void disconnect(Slot& slot);

    template<typename E>
    void emit(const E& event);

private:
    template<typename E>
    BaseGameEvent::Family eventFamily();

protected:
    std::map<BaseGameEvent::Family, GameEventSignal> mConnections;
};

class EventQueue
{
public:
    void  push(Event& event);
    Event pull();
    bool  isEmpty() const;

private:
    std::queue<Event> mEventQueue;
};
}

#include <fluffy/event/event_manager.inl>
