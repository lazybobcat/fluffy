#pragma once

#include <fluffy/pch.hpp>

namespace Fluffy {

namespace EnumNames {
const std::array<const char*, 5> MouseButton({ { "left", "right", "middle", "xbutton1", "xbutton2" } });
}

class Mouse
{
public:
    enum Button
    {
        ButtonLeft = 0,
        ButtonRight,
        ButtonMiddle,
        XButton1,
        XButton2
    };

    // @todo get position and is button pressed methods
};
}
