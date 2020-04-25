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

/**********************************************************************************************************************/

Event Event::createWindowResizedEvent(const Vector2u& size)
{
    Event event;
    event.type      = Event::WindowResized;
    event.size.size = size;

    return event;
}

Event Event::createWindowClosedEvent()
{
    Event event;
    event.type = Event::WindowClosed;

    return event;
}

Event Event::createWindowLostFocusEvent()
{
    Event event;
    event.type = Event::WindowLostFocus;

    return event;
}

Event Event::createWindowGainedFocusEvent()
{
    Event event;
    event.type = Event::WindowGainedFocus;

    return event;
}

Event Event::createKeyPressedEvent(Keyboard::Key key, bool repeated, bool ctrl, bool alt, bool shift)
{
    Event event;
    event.type         = Event::KeyPressed;
    event.key.code     = key;
    event.key.repeated = repeated;
    event.key.control  = ctrl;
    event.key.alt      = alt;
    event.key.shift    = shift;

    return event;
}

Event Event::createKeyReleasedEvent(Keyboard::Key key)
{
    Event event;
    event.type     = Event::KeyReleased;
    event.key.code = key;

    return event;
}

Event Event::createTextEnteredEvent(Char32 character)
{
    Event event;
    event.type         = Event::TextEntered;
    event.text.unicode = character;

    return event;
}

Event Event::createMouseMovedEvent(const Vector2f& position)
{
    Event event;
    event.type               = Event::MouseMoved;
    event.mouseMove.position = position;

    return event;
}

Event Event::createMouseEnteredEvent()
{
    Event event;
    event.type = Event::MouseEntered;

    return event;
}

Event Event::createMouseLeftEvent()
{
    Event event;
    event.type = Event::MouseLeft;

    return event;
}

Event Event::createMouseButtonPressedEvent(Mouse::Button button)
{
    Event event;
    event.type               = Event::MouseButtonPressed;
    event.mouseButton.button = button;

    return event;
}

Event Event::createMouseButtonReleasedEvent(Mouse::Button button)
{
    Event event;
    event.type               = Event::MouseButtonReleased;
    event.mouseButton.button = button;

    return event;
}

Event Event::createMouseWheelScrolledEvent(Vector2f delta)
{
    Event event;
    event.type             = Event::MouseWheelScrolled;
    event.mouseWheel.delta = delta;

    return event;
}
