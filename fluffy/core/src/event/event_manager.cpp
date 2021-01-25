#include <fluffy/event/event_manager.hpp>

using namespace Fluffy;

void EventManager::disconnect(Slot& slot)
{
    slot.disconnect();
}

/**********************************************************************************************************************/

void EventQueue::push(Event& event)
{
    mEventQueue.push(event);
}

Event EventQueue::pull()
{
    Event event = mEventQueue.front();
    mEventQueue.pop();

    return event;
}

bool EventQueue::isEmpty() const
{
    return mEventQueue.empty();
}
