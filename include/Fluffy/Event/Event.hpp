//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#ifndef FLUFFY_EVENT_HPP
#define FLUFFY_EVENT_HPP

#include <Fluffy/Event/Signal.hpp>
#include <Fluffy/Utility/Time.hpp>

namespace Fluffy {
namespace Event {

/**
 * Used internally only
 */
class BaseEvent
{
public:
    typedef std::size_t Family;

public:
    BaseEvent()          = default;
    virtual ~BaseEvent() = default;

protected:
    static Family mFamilyCounter;
};

typedef Signal<const BaseEvent&> EventSignal;

template <typename Derived>
class Event : public BaseEvent
{
public:
    static Family family()
    {
        static Family family = mFamilyCounter++;

        return family;
    }
};

/**********************************************************************************************************************/

/**
 * Raised first at each loop iteration.
 */
struct BeforeGameTickEvent : public Event<BeforeGameTickEvent>
{
};

/**
 * Raised once at the beginning of each main loop iteration.
 */
struct GameTickEvent : public Event<GameTickEvent>
{
    explicit GameTickEvent(Fluffy::Utility::Time dt = Fluffy::Utility::Time::Zero)
      : dt(dt)
    {
    }

    Fluffy::Utility::Time dt;
};

/**
 * Raised at the end of the main loop iteration.
 */
struct AfterGameTickEvent : public Event<AfterGameTickEvent>
{
};
}
}

#endif //FLUFFY_EVENT_HPP
