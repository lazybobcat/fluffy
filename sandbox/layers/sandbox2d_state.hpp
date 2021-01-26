#pragma once

#include <fluffy/api/modules.hpp>
#include <fluffy/fluffy_core.hpp>
#include <fluffy/fluffy_utils.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/rectangle_shape.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/graphics/transformable.hpp>
#include <fluffy/graphics/vertex_buffers.hpp>
#include <fluffy/input/input.hpp>
#include <imgui.h>
#include <iostream>
#include <opengl.hpp>

class Tilemap
{
    static constexpr int rows = 72;
    static constexpr int cols = 128;

public:
    Tilemap()
    {
        va      = VertexArray::create();
        auto vb = VertexBuffer::create(4 * rows * cols * sizeof(Vertex));
        vb->setLayout({
          { ShaderDataType::Vector3f, "aPos" },
          { ShaderDataType::Vector2f, "aTexCoord" },
          { ShaderDataType::Vector4f, "aColor" },
          { ShaderDataType::Float, "aTexSlot" },
        });
        va->addVertexBuffer(vb);

        std::uint32_t indices[6 * rows * cols];
        std::uint32_t offset = 0;
        for (std::uint32_t i = 0; i < 6 * rows * cols; i += 6) {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> ib = IndexBuffer::create(indices, 6 * rows * cols);
        va->setIndexBuffer(ib);

        ///

        for (int j = 0; j < rows; ++j) {
            for (int i = 0; i < cols; ++i) {
                RectangleShape rectangle({ 10.f, 10.f });
                rectangle.setPosition({ -645 + (i * 15), -360 + (j * 15) });
                rectangles.push_back(rectangle);
            }
        }

        ///

        auto quadVertexBufferBase = new Vertex[4 * rows * cols];
        auto quadVertexBufferPtr  = quadVertexBufferBase;

        for (auto& rectangle : rectangles) {
            auto vertices  = rectangle.getVertices();
            auto transform = rectangle.getTransformMatrix();
            for (std::size_t i = 0; i < vertices.getVerticesCount(); ++i) {
                quadVertexBufferPtr->position  = transform * Vector4f(vertices[i].position, 1.f);
                quadVertexBufferPtr->color     = { 0.353f, 0.902f, 0.996f, 0.5f };
                quadVertexBufferPtr->texCoords = vertices[i].texCoords;
                quadVertexBufferPtr++;
            }
        }

        std::uint32_t dataSize = (std::uint8_t*)quadVertexBufferPtr - (std::uint8_t*)quadVertexBufferBase;
        vb->setData(quadVertexBufferBase, dataSize);

        delete[] quadVertexBufferBase;
    }

    Ref<VertexArray>            va;
    std::vector<RectangleShape> rectangles;
};

class Sandbox2DState : public Layer<Sandbox2DState>
{
public:
    Sandbox2DState()
      : rectangle1({ 10.f, 10.f })
      , rectangle2({ 10.f, 10.f })
    {}

    void initialize() override
    {
        FLUFFY_PROFILE_FUNCTION();

        rectangle1.setPosition({ 0.f, 0.f });
        //        rectangle1.setOrigin({0.5f, 0.5f, 0.f});
        rectangle2.setPosition({ -100.f, -100.f });

        squareTransform.setScale({ .5f, 0.5f, 1.f });
        squareTransform.move({ 0.f, 0.f, 0.1f });

        // My texture
        texture = getContext()->system->getResources().get<Texture2D>("assets/textures/alpaca.png");
        texture->setRepeat(RepeatType::Repeat);

        tile = getContext()->system->getResources().get<Texture2D>("assets/textures/tile.png");
        tile->setRepeat(RepeatType::Repeat);
    }

    void terminate() override
    {
        FLUFFY_PROFILE_FUNCTION();
    }

    void fixUpdate(Time dt) override
    {
        FLUFFY_PROFILE_FUNCTION();

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

            context.with(testCamera).bind([&](Painter& painter) {
                painter.clear(Color::fromInt8(43, 43, 43, 255));

                painter.draw(tilemap.va, tilemap.va->getIndexBuffer()->count());

                // states1.transform = rectangle1.getTransformMatrix();
                // painter.drawQuads(rectangle1.vertices, states1);
                painter.drawShape(rectangle1, states1);

                // states2.transform = rectangle2.getTransformMatrix();
                // painter.drawQuads(rectangle2.vertices, states2);
                painter.drawShape(rectangle2, states2);
            });
        }

        // ImGUI Stuff
        {
            FLUFFY_PROFILE_SCOPE("ImGUI Settings");
            if (settingsOpened) {
                ImGui::SetNextWindowSize(ImVec2(315.f, 105.f));
                ImGui::Begin("Settings", &settingsOpened);
                ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor.value));
                ImGui::ColorEdit4("Alpaca color", glm::value_ptr(alpacaColor.value));
                ImGui::End();
            }
        }
    }

    void onEvent(Event& event) override
    {
        FLUFFY_PROFILE_FUNCTION();

        // Update camera
        if (event.type == Fluffy::Event::WindowResized) {
            testCamera.setViewportSize(event.size.size);
        }

        if (event.type == Fluffy::Event::KeyPressed) {
            switch (event.key.code) {
                case Keyboard::Key::W:
                    testCamera.move({ 0, -10 });
                    break;
                case Keyboard::Key::S:
                    testCamera.move({ 0, 10 });
                    break;
                case Keyboard::Key::A:
                    testCamera.move({ -10, 0 });
                    break;
                case Keyboard::Key::D:
                    testCamera.move({ 10, 0 });
                    break;
                case Keyboard::Key::NumPad0:
                    rectangle2.setPosition({ 0.f, 0.f });
                    break;
                case Keyboard::Key::NumPad1:
                    rectangle2.setPosition({ -640.f, -360.f });
                    break;
                case Keyboard::Key::NumPad2:
                    rectangle2.setPosition({ 640.f, -360.f });
                    break;
                case Keyboard::Key::NumPad3:
                    rectangle2.setPosition({ 640.f, 360.f });
                    break;
                case Keyboard::Key::NumPad4:
                    rectangle2.setPosition({ -640.f, 360.f });
                    break;
                case Keyboard::Key::NumPad5:
                    rectangle2.setPosition({ -10.f, -10.f });
                    break;
                case Keyboard::Key::NumPad6:
                    rectangle2.setPosition({ 0.f, -10.f });
                    break;
                case Keyboard::Key::NumPad7:
                    rectangle2.setPosition({ 10.f, -10.f });
                    break;
            }
        }

        if (event.type == Fluffy::Event::MouseButtonPressed) {
            auto position = Input::getMousePosition();
            std::cout << "MousePosition: " << position.x << "," << position.y << std::endl;
            event.stopPropagation();
        }
    }

private:
    Camera                       testCamera;
    Ref<Texture2D>               tile;
    Ref<Texture2D>               texture;
    Transformable                squareTransform;
    Color                        squareColor = { .2f, .8f, .43f, 1.f };
    Color                        alpacaColor = { 1.f, 1.f, 1.f, 1.f };

    RectangleShape rectangle1;
    RectangleShape rectangle2;
    Tilemap        tilemap;

    bool settingsOpened = true;
};