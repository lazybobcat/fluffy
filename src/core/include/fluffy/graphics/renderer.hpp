#pragma once

#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class Renderer
{
public:
    static void initialize();
    static void terminate();
    static void beginScene(const Camera& camera);
    static void endScene();

    static void draw(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.f));

private:
    struct SceneData
    {
        glm::mat4 viewProjectionMatrix;
    };

    static SceneData* mSceneData;
};

class Renderer2D
{
public:
    static void initialize();
    static void terminate();
    static void beginScene(const Camera& camera);
    static void endScene();

    static void drawQuad(const Color& color, const glm::mat4& transform = glm::mat4(1.f));
    static void drawQuad(const Ref<Texture2D>& texture, const Color& color = Color::White, const glm::mat4& transform = glm::mat4(1.f));
};
}
