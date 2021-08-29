#include "fluffy_plugin.hpp"
#include "ui/layout.hpp"
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

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
        data.icon            = Texture2D::create("assets/textures/components/fluffy.png", { 32, 0, 32, 32 });
        data.addComponentFct = [](Entity entity) {
            if (!entity.has<TransformComponent>()) {
                entity.add<TransformComponent>();
            }
        };
        data.drawComponentFct = [](Entity entity) {
            Layout::drawComponent<TransformComponent>(entity, "Transform", [](Entity entity) {
                auto& Ctransform = entity.get<TransformComponent>();

                // Origin
                auto origin = Ctransform.getOrigin();
                Layout::drawXYZ("Origin", origin, 0.f, 0.1f);
                Ctransform.setOrigin(origin);

                // Position
                auto pos = Ctransform.getPosition();
                Layout::drawXYZ("Translation", pos);
                Ctransform.setPosition(pos);

                // Rotation
                auto rot = Ctransform.getEulerAngles();
                Layout::drawXYZ("Rotation", rot, 0.f, 0.5f);
                Ctransform.setRotation(rot);

                // Scale
                auto scale = Ctransform.getScale();
                Layout::drawXYZ("Scale", scale, 1.f, 0.1f);
                Ctransform.setScale(scale);
            });
        };
        components.addComponentData(data);
    }

    // SPRITE
    {
        ComponentData data;
        data.name            = "Sprite";
        data.icon            = Texture2D::create("assets/textures/components/fluffy.png", { 64, 0, 32, 32 });
        data.addComponentFct = [](Entity entity) {
            if (!entity.has<SpriteComponent>()) {
                entity.add<SpriteComponent>();
            }
        };
        data.drawComponentFct = [](Entity entity) {
            Layout::drawComponent<SpriteComponent>(entity, "Sprite", [](Entity entity) {
                auto& Csprite = entity.get<SpriteComponent>();
                auto  color   = Csprite.rectangle.getFillColor().value;
                if (Layout::drawColorPicker("Color", color)) {
                    Csprite.rectangle.setFillColor(color);
                }
            });
        };
        components.addComponentData(data);
    }
}

void FluffyPlugin::terminate(PluginRegistry* registry)
{
}
