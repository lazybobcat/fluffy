#pragma once

#include "glfw.hpp"
#include <fluffy/input/mouse.hpp>

namespace Fluffy {

Mouse::Button toFluffyButton(int button);
int           toGlfwButton(Mouse::Button button);
}
