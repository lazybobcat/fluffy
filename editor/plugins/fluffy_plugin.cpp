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
        data.icon            = Texture2D::create("assets/textures/components/fluffy_components.png", { 96, 0, 32, 32 });
        data.addComponentFct = [](Entity entity) {
            if (!entity.has<CameraComponent>()) {
                entity.add<CameraComponent>();
            }
        };
        data.drawComponentFct = [](Entity entity) {
            Layout::drawComponent<CameraComponent>(entity, "Camera", [](Entity entity) {
                auto&       Ccamera        = entity.get<CameraComponent>();
                const char* currentTypeStr = EnumNames::CameraType[(int)Ccamera.type];

                if (ImGui::BeginCombo("Type", currentTypeStr)) {
                    for (int i = 0; i < EnumNames::CameraType.size(); ++i) {
                        auto type       = EnumNames::CameraType.at(i);
                        bool isSelected = currentTypeStr == type;
                        if (ImGui::Selectable(type, isSelected)) {
                            currentTypeStr = type;
                            Ccamera.changeCamera((Camera::CameraType)i);
                        }

                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }

                if (Camera::CameraType::Orthographic == Ccamera.type) {
                    auto camera = dynamic_cast<OrthographicCamera*>(Ccamera.camera);

                    // Size
                    Vector2f size = camera->getSize();
                    Layout::drawXY("Size", size, 0.f, 2.f);
                    camera->setSize(size);

                    // Position
                    Vector2f pos = { camera->getPosition().x, camera->getPosition().y };
                    Layout::drawXY("Position", pos, 0.f, 1.f);
                    camera->setPosition(pos);

                    // Rotation
                    float rot = camera->getRotation();
                    Layout::drawFloat("Rotation", rot, 0.f, 1.f);
                    camera->setRotation(rot);

                    // Zoom
                    float zoom = camera->getZoom();
                    Layout::drawFloat("Zoom", zoom, 1.f, 0.1f);
                    camera->setZoom(zoom);
                } else if (Camera::CameraType::Perspective == Ccamera.type) {
                    auto camera = dynamic_cast<PerspectiveCamera*>(Ccamera.camera);

                    // Frustum
                    float fov = camera->getFov();
                    float ar  = camera->getAspectRatio();
                    Layout::draw2Floats("Frustum", "FOV", "A/R", fov, ar, 1.f, 0.2f);
                    camera->setFov(fov);
                    camera->setAspectRatio(ar);

                    // Clipping
                    float near = camera->getNear();
                    float far  = camera->getFar();
                    Layout::draw2Floats("Clipping", "Near", "Far", near, far, 1.f, 1.f);
                    camera->setNear(near);
                    camera->setFar(far);

                    // Look at
                    auto lookat = camera->getLookAt();
                    Layout::drawXYZ("Look at", lookat);
                    camera->setLookAt(lookat);

                    // Distance
                    float distance = camera->getDistance();
                    Layout::drawFloat("Distance", distance, 1000.f, 10.f);
                    camera->setDistance(distance);

                    // Orientation
                    float pitch = camera->getPitch();
                    float yaw   = camera->getYaw();
                    Layout::draw2Floats("Orientation", "Pitch", "Yaw", pitch, yaw, 1.f, 0.2f);
                    camera->setPitch(pitch);
                    camera->setYaw(yaw);
                }
            });
        };
        components.addComponentData(data);
    }
}

void FluffyPlugin::terminate(PluginRegistry* registry)
{
}
