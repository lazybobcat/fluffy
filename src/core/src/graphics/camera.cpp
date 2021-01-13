#include <fluffy/graphics/camera.hpp>

using namespace Fluffy;

OrthographicCamera::OrthographicCamera(FloatRect bounds)
  : mProjectionMatrix(glm::ortho(bounds.left, bounds.left + bounds.width, bounds.top - bounds.height, bounds.top, -1.f, 1.f))
{
}

void OrthographicCamera::setProjectionMatrix(FloatRect bounds)
{
    mProjectionMatrix = glm::ortho(bounds.left, bounds.left + bounds.width, bounds.top - bounds.height, bounds.top, -1.f, 1.f);
}

const glm::mat4& OrthographicCamera::getViewMatrix() const
{
    return getInverseTransform().getMatrix();
}

glm::mat4 OrthographicCamera::getViewProjection() const
{
    return mProjectionMatrix * getViewMatrix();
}

void OrthographicCamera::zoom(float factor)
{
    setScale(getScale() * factor);
}
