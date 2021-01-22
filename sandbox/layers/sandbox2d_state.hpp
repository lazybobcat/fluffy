#pragma once

#include <fluffy/api/modules.hpp>
#include <fluffy/fluffy_core.hpp>
#include <fluffy/fluffy_ecs.hpp>
#include <fluffy/fluffy_utils.hpp>
#include <fluffy/game/camera_controller.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/shape.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/graphics/transformable.hpp>
#include <fluffy/graphics/vertex_buffers.hpp>
#include <fluffy/imgui/imgui_container.hpp>
#include <fluffy/imgui/windows/about_window.hpp>
#include <fluffy/imgui/windows/log_window.hpp>
#include <fluffy/imgui/windows/profiling_window.hpp>
#include <fluffy/imgui/windows/toolbar_window.hpp>
#include <fluffy/input/input.hpp>
#include <imgui.h>
#include <iostream>
#include <opengl.hpp>

struct RectangleShape : public Shape
{
    explicit RectangleShape(const Vector2f& size)
      : size(size)
    {
        setOrigin({0.5f, 0.5f, 0.f});
        update();
    }

    size_t getVerticesCount() override
    {
        return 4;
    }

    Vector3f getVertexPosition(std::size_t index) override
    {
        auto origin = getOrigin();

        switch (index) {
            case 0:
                return { 0.f - origin.x * size.x, 0.f - origin.y * size.y, 0.f };
            case 1:
                return { size.x - origin.x * size.x, 0.f - origin.y * size.y, 0.f };
            case 2:
                return { size.x - origin.x * size.x, size.y - origin.y * size.y, 0.f };
            case 3:
                return { 0.f - origin.x * size.x, size.y - origin.y * size.y, 0.f };
        }

        return { 0.f, 0.f, 0.f };
    }

    Vector2f size;
};

class Sandbox2DState : public State<Sandbox2DState>
{
public:
    Sandbox2DState()
      : cameraController({ 1280, 720 })
      , rectangle1({ 100.f, 200.f })
      , rectangle2({ 80.f, 80.f })
    {}

    void initialize() override
    {
        FLUFFY_PROFILE_FUNCTION();

        rectangle1.setPosition({ 0.f, 0.f });
//        rectangle1.setOrigin({0.5f, 0.5f, 0.f});
        rectangle2.setPosition({ -200.f, 0.f });

        squareTransform.setScale({ .5f, 0.5f, 1.f });
        squareTransform.move({ 0.f, 0.f, 0.1f });

        // My texture
        texture = getContext()->system->getResources().get<Texture2D>("assets/textures/alpaca.png");
        texture->setRepeat(RepeatType::Repeat);

        tile = getContext()->system->getResources().get<Texture2D>("assets/textures/tile.png");
        tile->setRepeat(RepeatType::Repeat);

        // ImGui
        container.pack(CreateRef<ToolbarWindow>(openedWindows));
        {
            ImGuiWindowDefinition logDefinition;
            logDefinition.title       = "Logs";
            logDefinition.openControl = &openedWindows.logsWindowOpened;
            container.pack(CreateRef<LogWindow>(logDefinition));
        }
#ifdef FLUFFY_PROFILING_ACTIVE
        container.pack(CreateRef<ProfilingWindow>(ProfilingWindowDefinition("Profiling", &openedWindows.profilingWindowOpened)));
#endif
        {
            ImGuiWindowDefinition aboutDefinition;
            aboutDefinition.title       = "About";
            aboutDefinition.openControl = &openedWindows.aboutWindowOpened;
            container.pack(CreateRef<AboutWindow>(aboutDefinition));
        }
    }

    void terminate() override
    {
        FLUFFY_PROFILE_FUNCTION();
    }

    void fixUpdate(Time dt) override
    {
        FLUFFY_PROFILE_FUNCTION();

        // Update camera
        cameraController.update(dt);

        if (Input::isKeyPressed(Keyboard::Key::J)) {
            rectangle2.rotateZ(10.f * dt.seconds());
        }
        if (Input::isKeyPressed(Keyboard::Key::Right)) {
            rectangle2.move({ 100.f * dt.seconds(), 0.f });
        }
        if (Input::isKeyPressed(Keyboard::Key::Left)) {
            rectangle2.move({ -100.f * dt.seconds(), 0.f });
        }
        if (Input::isKeyPressed(Keyboard::Key::Up)) {
            rectangle2.move({ 0.f, -100.f * dt.seconds() });
        }
        if (Input::isKeyPressed(Keyboard::Key::Down)) {
            rectangle2.move({ 0.f, 100.f * dt.seconds() });
        }

        container.update(dt);
        rectangle1.setFillColor(squareColor);
        rectangle2.setFillColor(squareColor);
    }

    void render(RenderContext& context) override
    {
        FLUFFY_PROFILE_FUNCTION();

        {
            FLUFFY_PROFILE_SCOPE("Scene");

            RenderStates states1;
            //states1.texture = texture;

            RenderStates states2;
            //states2.texture = tile;

            context.with(cameraController.getCamera()).bind([&](Painter& painter) {
                painter.clear(Color::fromInt8(204, 51, 204, 255));

                // states1.transform = rectangle1.getTransformMatrix();
                // painter.drawQuads(rectangle1.vertices, states1);
                painter.drawShape(rectangle1, states1);

                // states2.transform = rectangle2.getTransformMatrix();
                // painter.drawQuads(rectangle2.vertices, states2);
                painter.drawShape(rectangle2, states2);

                painter.flush();
            });
        }

        // ImGUI Stuff
        FLUFFY_PROFILE_SCOPE("ImGui");
        {
            container.render();
            // ImGui::ShowDemoWindow();
        }
        {
            FLUFFY_PROFILE_SCOPE("ImGUI Settings");
            if (settingsOpened) {
                ImGui::SetNextWindowSize(ImVec2(315.f, 105.f));
                ImGui::Begin("Settings", &settingsOpened);
                ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor.value));
                ImGui::ColorEdit4("Alpaca color", glm::value_ptr(alpacaColor.value));
                ImGui::End();
            }

            // This actually appends to the existing main menu bar. AWESOME ImGui!!
            // Will be useful to add windows depending on the current state to pre-existing/default UI
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("View")) {
                    ImGui::Separator();
                    ImGui::MenuItem("(Sandbox2D)", nullptr, false, false);
                    ImGui::MenuItem("Settings", nullptr, &settingsOpened);
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }
        }
    }

    void onEvent(Event& event) override
    {
        FLUFFY_PROFILE_FUNCTION();

        // Update camera
        cameraController.onEvent(event);

        if (event.type == Fluffy::Event::MouseButtonPressed) {
            // auto position = Input::getMousePosition();
            event.stopPropagation();
        }
    }

private:
    OrthographicCameraController cameraController;
    Ref<Texture2D>               tile;
    Ref<Texture2D>               texture;
    Transformable                squareTransform;
    Color                        squareColor = { .2f, .8f, .43f, 1.f };
    Color                        alpacaColor = { 1.f, 1.f, 1.f, 1.f };

    RectangleShape rectangle1;
    RectangleShape rectangle2;

    bool settingsOpened = true;

    OpenedWindowTracker openedWindows;
    ImGuiContainer      container;
};