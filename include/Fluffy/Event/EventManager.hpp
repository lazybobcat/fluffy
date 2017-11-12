//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#ifndef FLUFFY_EVENTMANAGER_HPP
#define FLUFFY_EVENTMANAGER_HPP

#include <Fluffy/Event/Event.hpp>

namespace Fluffy {
namespace Event {

class EventManager
{
public:
    template <typename E>
    Slot connect(std::function<void(const E&)> callback);

    /**
     * You should prefer to use slot.disconnect() directly
     *
     * @param Slot slot
     */
    void disconnect(Slot& slot);

    template <typename E>
    void emit(const E& event);

private:
    template <typename E>
    BaseEvent::Family eventFamily();

protected:
    std::map<BaseEvent::Family, EventSignal> mConnections;
};
}
}

#include <Fluffy/Event/EventManager.inl>

#endif //FLUFFY_EVENTMANAGER_HPP
