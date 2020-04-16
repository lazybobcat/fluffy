#pragma once

#include <fluffy/pch.hpp>

namespace Fluffy {

enum class RenderAPIList
{
    None   = 0,
    OpenGL = 1,
};

namespace EnumNames {
const std::array<const char*, 6> RenderAPI({ { "none", "OpenGL" } });
}

class Renderer
{
public:
    static RenderAPIList RenderAPI;
};
}
