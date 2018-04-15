//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 15/04/18.
//

#ifndef FLUFFY_TRANSFORMABLE2D_HPP
#define FLUFFY_TRANSFORMABLE2D_HPP

#include <Fluffy/Graphics/Vector2.hpp>

namespace Fluffy {
namespace Graphics {

class Transformable2D
{
public:
    Transformable2D()          = default;
    virtual ~Transformable2D() = default;

    void move(Vector2f offset);
    void scale(Vector2f factor);
    void rotate(float angle);

    void setOrigin(Vector2f origin);
    void setPosition(Vector2f position);
    void setScale(Vector2f scale);
    void setRotation(float angle);

    Vector2f getOrigin() const;
    Vector2f getPosition() const;
    Vector2f getScale() const;
    float    getRotation() const;

private:
    Vector2f mOrigin   = { 0, 0 };
    Vector2f mPosition = { 0, 0 };
    Vector2f mScale    = { 1, 1 };
    float    mRotation = 0; // In degrees
};
}
}

#endif //FLUFFY_TRANSFORMABLE2D_HPP
