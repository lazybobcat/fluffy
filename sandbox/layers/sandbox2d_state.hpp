#pragma once

#include <fluffy/api/modules.hpp>
#include <fluffy/fluffy_core.hpp>
#include <fluffy/fluffy_ecs.hpp>
#include <fluffy/fluffy_utils.hpp>
#include <fluffy/game/camera_controller.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/render_command.hpp>
#include <fluffy/graphics/renderer.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/graphics/transformable.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/imgui/imgui_container.hpp>
#include <fluffy/imgui/windows/about_window.hpp>
#include <fluffy/imgui/windows/profiling_window.hpp>
#include <fluffy/imgui/windows/toolbar_window.hpp>
#include <fluffy/input/input.hpp>
#include <imgui.h>
#include <iostream>
#include <opengl.hpp>

class Sandbox2DState : public State<Sandbox2DState>
{
public:
    Sandbox2DState()
      : cameraController(1280.f / 720.f)
    {}

    void initialize() override
    {
        RenderCommand::setClearColor(Color::fromInt8(204, 51, 204, 255));

        squareTransform.setScale({ .5f, 0.5f, 1.f });
        squareTransform.move({ 0.f, 0.f, 0.1f });

        // My texture
        texture = Texture2D::create("assets/textures/alpaca.png");
        texture->setRepeat(RepeatType::Repeat);

        // ImGui
        container.pack(CreateRef<ToolbarWindow>(openedWindows));
#ifdef FLUFFY_PROFILING_ACTIVE
        container.pack(CreateRef<ProfilingWindow>(ProfilingWindowDefinition("Profiling", &openedWindows.profilingWindowOpened)));
#endif
        ImGuiWindowDefinition aboutDefinition;
        aboutDefinition.title = "About";
        aboutDefinition.openControl = &openedWindows.aboutWindowOpened;
        container.pack(CreateRef<AboutWindow>(aboutDefinition));
    }

    void terminate() override
    {
    }

    void fixUpdate(Time dt) override
    {
        FLUFFY_PROFILE_SCOPE("Sandbox2DState::fixUpdate");

        // Update camera
        cameraController.update(dt);

        if (Input::isKeyPressed(Keyboard::Key::J)) {
            squareTransform.rotateZ(10.f * dt.seconds());
        }
        if (Input::isKeyPressed(Keyboard::Key::Right)) {
            squareTransform.move({ 5.f * dt.seconds(), 0.f });
        }
        if (Input::isKeyPressed(Keyboard::Key::Left)) {
            squareTransform.move({ -5.f * dt.seconds(), 0.f });
        }
        if (Input::isKeyPressed(Keyboard::Key::Up)) {
            squareTransform.move({ 0.f, 5.f * dt.seconds() });
        }
        if (Input::isKeyPressed(Keyboard::Key::Down)) {
            squareTransform.move({ 0.f, -5.f * dt.seconds() });
        }

        container.update(dt);
    }

    void render(Time dt) override
    {
        FLUFFY_PROFILE_SCOPE("Sandbox2DState::render");

        {
            FLUFFY_PROFILE_SCOPE("Scene");

            Renderer2D::beginScene(cameraController.getCamera());

            Renderer2D::drawQuad(squareColor, glm::mat4(1.f));
            Renderer2D::drawQuad(texture, alpacaColor, squareTransform.getTransformMatrix());

            Renderer2D::endScene();
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
        FLUFFY_PROFILE_SCOPE("Sandbox2DState::onEvent");

        // Update camera
        cameraController.onEvent(event);

        if (event.type == Fluffy::Event::MouseButtonPressed) {
            auto position = Input::getMousePosition();
            FLUFFY_LOG_DEBUG("Mouse button pressed: {} (at {})", EnumNames::MouseButton[(int)event.mouseButton.button], position);
        }
    }

private:
    OrthographicCameraController cameraController;
    Ref<Texture2D>               texture;
    Transformable                squareTransform;
    Color                        squareColor = { .2f, .8f, .43f, 1.f };
    Color                        alpacaColor = { 1.f, 1.f, 1.f, 1.f };

    bool settingsOpened = true;

    OpenedWindowTracker openedWindows;
    ImGuiContainer      container;
};