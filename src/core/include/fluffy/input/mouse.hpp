#pragma once

#include <fluffy/pch.hpp>

namespace Fluffy {

namespace EnumNames {
const std::array<const char*, 5> MouseButton({ { "left", "right", "middle", "xbutton1", "xbutton2" } });
}

class Mouse
{
public:
    enum class Button
    {
        Left,
        Right,
        Middle,
        XButton1,
        XButton2
    };

    // @todo get position and is button pressed methods
};
}
