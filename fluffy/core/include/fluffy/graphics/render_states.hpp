#pragma once

#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/texture.hpp>

namespace Fluffy {

/**
 * @todo replace this by Material
 */
struct RenderStates
{
    static const RenderStates Default;

    glm::mat4      transform = glm::mat4(1.f);
    Ref<Texture2D> texture   = nullptr;
    Ref<Shader>    shader    = nullptr;
};
}