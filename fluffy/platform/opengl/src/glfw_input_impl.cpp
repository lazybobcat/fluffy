#include "glfw_functions.hpp"
#include "glfw_window.hpp"
#include <fluffy/input/input.hpp>

using namespace Fluffy;

bool Input::isKeyPressed(Keyboard::Key key)
{
    auto* window = dynamic_cast<GlfwWindow*>(mWindow);
    auto  state  = glfwGetKey((GLFWwindow*)window->getNativeWindow(), (int)key);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

const char* Input::getKeyName(Keyboard::Key key)
{
    // This only return names for printable keys. @todo return names for all keys
    auto name = glfwGetKeyName((int)key, 0);

    return name ? name : "";
}

bool Input::isMouseButtonPressed(Mouse::Button button)
{
    auto* window = dynamic_cast<GlfwWindow*>(mWindow);
    auto  state  = glfwGetMouseButton((GLFWwindow*)window->getNativeWindow(), toGlfwButton(button));

    return state == GLFW_PRESS;
}

Vector2f Input::getMousePosition()
{
    auto*  window = dynamic_cast<GlfwWindow*>(mWindow);
    double xpos = 0, ypos = 0;
    glfwGetCursorPos((GLFWwindow*)window->getNativeWindow(), &xpos, &ypos);

    return { xpos, ypos };
}
