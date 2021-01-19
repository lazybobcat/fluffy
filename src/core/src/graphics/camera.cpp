#include <fluffy/graphics/camera.hpp>

using namespace Fluffy;

/**
 * Note: The Y-axis is pointing down so that (0,0) is on the top-left.
 * For that, we invert to top and bottom coordinates of the projection matrix.
 */

OrthographicCamera::OrthographicCamera(FloatRect bounds)
  : mProjectionMatrix(glm::ortho(bounds.left, bounds.left + bounds.width, bounds.top, bounds.top - bounds.height, -1.f, 1.f))
{
}

void OrthographicCamera::setProjectionMatrix(FloatRect bounds)
{
    mProjectionMatrix = glm::ortho(bounds.left, bounds.left + bounds.width, bounds.top, bounds.top - bounds.height, -1.f, 1.f);
}

const glm::mat4& OrthographicCamera::getViewMatrix() const
{
    return getInverseTransform();
}

glm::mat4 OrthographicCamera::getViewProjection() const
{
    return mProjectionMatrix * getViewMatrix();
}

void OrthographicCamera::zoom(float factor)
{
    setScale(getScale() * factor);
}
