#pragma once

#include <fluffy/graphics/transformable.hpp>
#include <fluffy/math/rectangle.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class Camera : public Transformable
{
public:
    virtual glm::mat4 getViewProjection() const = 0;
};

// 2D camera
class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(FloatRect bounds);

    const glm::mat4& getProjectionMatrix() const { return mProjectionMatrix; }
    const glm::mat4& getViewMatrix() const;
    glm::mat4        getViewProjection() const override;

private:
    glm::mat4 mProjectionMatrix;
};
}
