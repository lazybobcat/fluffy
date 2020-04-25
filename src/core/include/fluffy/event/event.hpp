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
        bool          alt;
        bool          control;
        bool          shift;
        bool          system;
    };

    struct TextEvent
    {
        std::uint32_t unicode;
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

    enum class EventType
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
    void stopPropagation();
    bool isStopped() const;

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
