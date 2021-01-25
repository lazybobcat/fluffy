#include "glfw_functions.hpp"

using namespace Fluffy;

Mouse::Button Fluffy::toFluffyButton(int button)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            return Mouse::ButtonLeft;

        case GLFW_MOUSE_BUTTON_RIGHT:
            return Mouse::ButtonRight;

        case GLFW_MOUSE_BUTTON_MIDDLE:
            return Mouse::ButtonMiddle;

        case GLFW_MOUSE_BUTTON_4:
            return Mouse::XButton1;

        case GLFW_MOUSE_BUTTON_5:
            return Mouse::XButton2;

        default:
            return Mouse::ButtonLeft;
    }
}

int Fluffy::toGlfwButton(Mouse::Button button)
{
    switch (button) {
        case Mouse::ButtonLeft:
            return GLFW_MOUSE_BUTTON_LEFT;

        case Mouse::ButtonRight:
            return GLFW_MOUSE_BUTTON_RIGHT;

        case Mouse::ButtonMiddle:
            return GLFW_MOUSE_BUTTON_MIDDLE;

        case Mouse::XButton1:
            return GLFW_MOUSE_BUTTON_4;

        case Mouse::XButton2:
            return GLFW_MOUSE_BUTTON_5;

        default:
            return GLFW_MOUSE_BUTTON_LEFT;
    }
}
