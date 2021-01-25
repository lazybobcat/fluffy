#pragma once

#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/painter.hpp>

namespace Fluffy {

class RenderTarget;
class Game;

class RenderContext
{
public:
    RenderContext(RenderContext&& context);

    RenderContext with(Camera& camera) const;
    RenderContext with(RenderTarget& renderTarget) const;

    void bind(const std::function<void(Painter&)>& f);

    Camera&       getCamera() const;
    RenderTarget& getDefaultRenderTarget();

private:
    RenderContext(Painter& painter, Camera& camera, RenderTarget& renderTarget);
    void setActive();
    void setInactive();
    void pushContext();
    void popContext();

private:
    friend class Game;

    Painter&      mPainter;
    Camera&       mCamera;
    RenderTarget& mDefaultRenterTarget;

    RenderContext* mPreviousContext = nullptr;
};
}