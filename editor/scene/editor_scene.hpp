#pragma once

#include "graphics/editor_camera.hpp"
#include <fluffy/scene/scene.hpp>

namespace Fluffy {

class EditorScene : public Scene
{
public:
    explicit EditorScene(Context& context);

    void updateEditor(Time dt);
    void renderEditor(RenderContext& context, EditorCamera& camera);
};
}