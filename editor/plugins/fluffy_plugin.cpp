#include "fluffy_plugin.hpp"
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

String FluffyPlugin::getPluginName()
{
    return "FluffyPlugin";
}

void FluffyPlugin::initialize(PluginRegistry* registry)
{
    auto&       components = registry->components();

    // TRANSFORM
    {
        ComponentData data;
        data.name = "Transform";
        data.icon = Texture2D::create("assets/textures/components/fluffy.png", {32, 0, 32, 32});
        data.addComponentFct = [](Entity entity) {
            entity.add<TransformComponent>();
        };
        components.addComponentData(data);
    }

    // SPRITE
    {
        ComponentData data;
        data.name            = "Sprite";
        data.icon = Texture2D::create("assets/textures/components/fluffy.png", {64, 0, 32, 32});
        data.addComponentFct = [](Entity entity) {
            entity.add<SpriteComponent>();
        };
        components.addComponentData(data);
    }

    // DUMMY
    {
        for (int i = 0; i < 10; ++i) {
            ComponentData data;
            data.name            = printString("Dummy {}", i);
            data.icon = Texture2D::create("assets/textures/components/fluffy.png", {0, 0, 32, 32});
            data.addComponentFct = [](Entity entity) {};
            components.addComponentData(data);
        }
    }
}

void FluffyPlugin::terminate(PluginRegistry* registry)
{
}
