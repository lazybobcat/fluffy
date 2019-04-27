//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#pragma once

#include <fluffy/event/event.hpp>

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
    BaseEvent::Family eventFamily();

protected:
    std::map<BaseEvent::Family, EventSignal> mConnections;
};
}

#include <fluffy/event/event_manager.inl>
