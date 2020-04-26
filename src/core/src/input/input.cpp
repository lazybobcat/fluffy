#include <fluffy/input/input.hpp>

using namespace Fluffy;

Input*  Input::mInstance = nullptr;
Window* Input::mWindow   = nullptr;

void Input::create(Window* window)
{
    if (!mInstance) {
        mInstance = new Input();
    }

    Input::mWindow = window;
}
