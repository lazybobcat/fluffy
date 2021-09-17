#include "editor_scene.hpp"
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

EditorScene::EditorScene(Context& context)
  : Scene(context)
{
}

void EditorScene::updateEditor(Time dt)
{
}

void EditorScene::renderEditor(RenderContext& context, EditorCamera& camera)
{
    context.with(camera).bind([&](Painter& painter) {
        painter.clear(Color::fromInt8(43, 43, 43, 255));
        // draw scene
        auto view = getEntityRegistry()->view<TransformComponent, SpriteComponent>();
        for (auto [entity, transform, sprite] : view.each()) {
            RenderStates states;
            states.transform = transform.getTransformMatrix();
            painter.drawSprite(sprite.sprite, states);
        }
    });
}
