#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/signal/signal.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

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

template<typename Derived>
class Event : public BaseEvent
{
public:
    static Family family()
    {
        static Family family = mFamilyCounter++;

        return family;
    }

#if FLUFFY_DEBUG
    virtual const std::string toString() const
    {
        return "'UnnamedEvent' {}";
    }
#endif
};
}
