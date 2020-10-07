#pragma once

#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class Renderer
{
public:
    static void beginScene(const Camera& camera);
    static void endScene();

    static void draw(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader);

private:
    struct SceneData
    {
        glm::mat4 viewProjectionMatrix;
    };

    static SceneData* mSceneData;
};
}
