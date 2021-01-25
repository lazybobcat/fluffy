#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/input/keyboard.hpp>
#include <fluffy/input/mouse.hpp>
#include <fluffy/math/math.hpp>
#include <fluffy/signal/signal.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

/**
 * Used internally only
 */
class BaseGameEvent
{
public:
    typedef std::size_t Family;

public:
    BaseGameEvent()          = default;
    virtual ~BaseGameEvent() = default;

protected:
    static Family mFamilyCounter;
};

typedef Signal<const BaseGameEvent&> GameEventSignal;

template<typename Derived>
class GameEvent : public BaseGameEvent
{
public:
    static Family family()
    {
        static Family family = mFamilyCounter++;

        return family;
    }

#if FLUFFY_DEBUG
    virtual const String toString() const
    {
        return "'UnnamedEvent' {}";
    }
#endif
};

class Event
{
public:
    struct SizeEvent
    {
        Vector2u size;
    };

    struct KeyEvent
    {
        Keyboard::Key code;
        bool          repeated;
        bool          alt;
        bool          control;
        bool          shift;
    };

    struct TextEvent
    {
        Char32 unicode;
    };

    struct MouseMoveEvent
    {
        Vector2f position;
    };

    struct MouseButtonEvent
    {
        Mouse::Button button;
    };

    struct MouseWheelEvent
    {
        Vector2f delta;
    };

    enum EventType
    {
        WindowClosed,
        WindowResized,
        WindowLostFocus,
        WindowGainedFocus,
        TextEntered,
        KeyPressed,
        KeyReleased,
        MouseWheelScrolled,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseEntered,
        MouseLeft,
    };

public:
    static Event createWindowResizedEvent(const Vector2u& size);
    static Event createWindowClosedEvent();
    static Event createWindowLostFocusEvent();
    static Event createWindowGainedFocusEvent();
    static Event createKeyPressedEvent(Keyboard::Key key, bool repeated = false, bool ctrl = false, bool alt = false, bool shift = false);
    static Event createKeyReleasedEvent(Keyboard::Key key);
    static Event createTextEnteredEvent(Char32 character);
    static Event createMouseMovedEvent(const Vector2f& position);
    static Event createMouseEnteredEvent();
    static Event createMouseLeftEvent();
    static Event createMouseButtonPressedEvent(Mouse::Button button);
    static Event createMouseButtonReleasedEvent(Mouse::Button button);
    static Event createMouseWheelScrolledEvent(Vector2f delta);

    void               stopPropagation();
    [[nodiscard]] bool isStopped() const;

public:
    EventType type;

    union
    {
        SizeEvent        size;
        KeyEvent         key;
        TextEvent        text;
        MouseMoveEvent   mouseMove;
        MouseButtonEvent mouseButton;
        MouseWheelEvent  mouseWheel;
    };

private:
    bool mStopped = false;
};
}
