#pragma once

#include <fluffy/graphics/window.hpp>
#include <fluffy/input/keyboard.hpp>

namespace Fluffy {

class InputModule;

class Input
{
public:
    static bool        isKeyPressed(Keyboard::Key key);
    static const char* getKeyName(Keyboard::Key key);

private:
    friend class InputModule;

    explicit Input() = default;
    static void create(Window* window);

private:
    static Input*  mInstance;
    static Window* mWindow;
};
}
