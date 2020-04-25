#include <fluffy/event/event.hpp>

using namespace Fluffy;

BaseGameEvent::Family BaseGameEvent::mFamilyCounter = 0;

void Event::stopPropagation()
{
    mStopped = true;
}

bool Event::isStopped() const
{
    return mStopped;
}
