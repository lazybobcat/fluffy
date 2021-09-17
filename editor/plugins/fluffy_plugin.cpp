#include "fluffy_plugin.hpp"
#include "ui/layout.hpp"
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

void createTransformWidgets(Transformable& transformable)
{
    // Origin
    auto origin = transformable.getOrigin();
    Layout::drawXYZ("Origin", origin, 0.f, 0.1f);
    transformable.setOrigin(origin);

    // Position
    auto pos = transformable.getPosition();
    Layout::drawXYZ("Translation", pos);
    transformable.setPosition(pos);

    // Rotation
    auto rot = transformable.getEulerAngles();
    Layout::drawXYZ("Rotation", rot, 0.f, 0.5f);
    transformable.setRotation(rot);

    // Scale
    auto scale = transformable.getScale();
    Layout::drawXYZ("Scale", scale, 1.f, 0.1f);
    transformable.setScale(scale);
}

/**********************************************************************************************************************/

String FluffyPlugin::getPluginName()
{
    return "FluffyPlugin";
}

void FluffyPlugin::initialize(PluginRegistry* registry)
{
    auto& components = registry->components();

    // TRANSFORM
    {
        ComponentData data;
        data.name            = "Transform";
        data.icon            = Texture2D::create("assets/textures/components/fluffy_components.png", { 32, 0, 32, 32 });
        data.addComponentFct = [](Entity entity) {
            if (!entity.has<TransformComponent>()) {
                entity.add<TransformComponent>();
            }
        };
        data.drawComponentFct = [](Entity entity) {
            Layout::drawComponent<TransformComponent>(entity, "Transform", [](Entity entity) {
                auto& Ctransform = entity.get<TransformComponent>();
                createTransformWidgets(Ctransform);
            });
        };
        components.addComponentData(data);
    }

    // SPRITE
    {
        ComponentData data;
        data.name            = "Sprite";
        data.icon            = Texture2D::create("assets/textures/components/fluffy_components.png", { 64, 0, 32, 32 });
        data.addComponentFct = [](Entity entity) {
            if (!entity.has<SpriteComponent>()) {
                entity.add<SpriteComponent>();
            }
        };
        data.drawComponentFct = [](Entity entity) {
            Layout::drawComponent<SpriteComponent>(entity, "Sprite", [](Entity entity) {
                auto& Csprite = entity.get<SpriteComponent>();

                // Visibility
                bool visible = Csprite.sprite.isVisible();
                if (Layout::drawCheckbox("Visible", visible)) {
                    Csprite.sprite.setVisible(visible);
                }

                // Color
                auto color = Csprite.sprite.getColor().value;
                if (Layout::drawColorPicker("Color", color)) {
                    Csprite.sprite.setColor(color);
                }

                // Size
                auto size = Csprite.sprite.getSize();
                Layout::drawXY("Size", size, size.x, 1.f);
                Csprite.sprite.setSize(size);

                // Texture rect
                auto rectangle = Csprite.sprite.getTextureRect();
                Layout::drawUintRectangle("Texture rect", rectangle);
                Csprite.sprite.setTextureRect(rectangle);
            });
        };
        components.addComponentData(data);
    }

    // CAMERA
    {
        ComponentData data;
        data.name            = "Camera";
        data.icon            = Texture2D::create("assets/textures/components/fluffy_components.png", { 32, 0, 32, 32 });
        data.addComponentFct = [](Entity entity) {
            if (!entity.has<CameraComponent>()) {
                entity.add<CameraComponent>();
            }
        };
        data.drawComponentFct = [](Entity entity) {
            Layout::drawComponent<CameraComponent>(entity, "Camera", [](Entity entity) {

            });
        };
        components.addComponentData(data);
    }
}

void FluffyPlugin::terminate(PluginRegistry* registry)
{
}
