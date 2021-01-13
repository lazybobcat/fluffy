#include "../src/platform/glfw/src/imgui_impl_glfw.h"
#include <fluffy/api/modules.hpp>
#include <fluffy/fluffy_core.hpp>
#include <fluffy/fluffy_ecs.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/render_command.hpp>
#include <fluffy/graphics/renderer.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/graphics/transform.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/input/input.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <opengl.hpp>

struct MyComponent : public Component<MyComponent>
{
    int a = 2;
};


class TestState : public State<TestState>
{
public:
    TestState() : camera({-1.6f, 0.9f, 2*1.6f, 2*0.9f}) {}

    void initialize() override
    {
        RenderCommand::setClearColor({204, 51, 204, 255});

        // Shader
        shader = Shader::create();
        shader->loadFromFile("assets/shaders/base.vertex.shader", "assets/shaders/base.fragment.shader");
//        shader->loadFromFile("assets/shaders/sprite.vertex.shader", "assets/shaders/sprite.fragment.shader");

        flatColorShader = Shader::create();
        flatColorShader->loadFromFile("assets/shaders/flat_color.vertex.shader", "assets/shaders/base.fragment.shader");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        vaTriangle = VertexArray::create();
        float vertices[3*7] = {
            0.f, 0.5f, -0.90f, 0.8f, 0.1f, 0.1f, 1.f,
            0.5f, -0.5f, -0.90f, 0.1f, 0.8f, 0.1f, 1.f,
            -0.5f, -0.5f, -0.90f, 0.1f, 0.1f, 0.8f, 1.f,
        };
        Ref<VertexBuffer> vbTriangle = VertexBuffer::create(vertices, sizeof(vertices));
        vbTriangle->setLayout({
            { ShaderDataType::Vector3f, "aPos" },
            { ShaderDataType::Vector4f, "aColor" },
        });
        std::uint32_t indices[3] = { 0, 1, 2 };
        Ref<IndexBuffer> ibTriangle = IndexBuffer::create(indices, 3);
        vaTriangle->addVertexBuffer(vbTriangle);
        vaTriangle->setIndexBuffer(ibTriangle);


        vaSquare = VertexArray::create();
        float verticesSquare[4*3] = {
          0.75f, -0.75f, 0.0f,
          0.75f, 0.75f, 0.0f,
          -0.75f, -0.75f, 0.0f,
          -0.75f, 0.75f, 0.0f,
        };
        Ref<VertexBuffer> vbSquare = VertexBuffer::create(verticesSquare, sizeof(verticesSquare));
        vbSquare->setLayout({
            { ShaderDataType::Vector3f, "aPos" },
        });
        std::uint32_t indicesSquare[6] = { 0, 1, 2, 2, 3, 1 };
        Ref<IndexBuffer> ibSquare = IndexBuffer::create(indicesSquare, 6);
        vaSquare->addVertexBuffer(vbSquare);
        vaSquare->setIndexBuffer(ibSquare);

        // My texture
        texture = Texture2D::create("assets/textures/alpaca.png");
        texture->setRepeat(RepeatType::Repeat);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.KeyMap[ImGuiKey_Tab] = (int)Keyboard::Key::Tab;
        io.KeyMap[ImGuiKey_LeftArrow] = (int)Keyboard::Key::Left;
        io.KeyMap[ImGuiKey_RightArrow] = (int)Keyboard::Key::Right;
        io.KeyMap[ImGuiKey_UpArrow] = (int)Keyboard::Key::Up;
        io.KeyMap[ImGuiKey_DownArrow] = (int)Keyboard::Key::Down;
        io.KeyMap[ImGuiKey_PageUp] = (int)Keyboard::Key::PageUp;
        io.KeyMap[ImGuiKey_PageDown] = (int)Keyboard::Key::PageDown;
        io.KeyMap[ImGuiKey_Home] = (int)Keyboard::Key::Home;
        io.KeyMap[ImGuiKey_End] = (int)Keyboard::Key::End;
        io.KeyMap[ImGuiKey_Insert] = (int)Keyboard::Key::Insert;
        io.KeyMap[ImGuiKey_Delete] = (int)Keyboard::Key::Delete;
        io.KeyMap[ImGuiKey_Backspace] = (int)Keyboard::Key::Backspace;
        io.KeyMap[ImGuiKey_Space] = (int)Keyboard::Key::Space;
        io.KeyMap[ImGuiKey_Enter] = (int)Keyboard::Key::Enter;
        io.KeyMap[ImGuiKey_Escape] = (int)Keyboard::Key::Escape;
        io.KeyMap[ImGuiKey_KeyPadEnter] = (int)Keyboard::Key::NumPadEnter;
        io.KeyMap[ImGuiKey_A] = (int)Keyboard::Key::Q;
        io.KeyMap[ImGuiKey_C] = (int)Keyboard::Key::C;
        io.KeyMap[ImGuiKey_V] = (int)Keyboard::Key::V;
        io.KeyMap[ImGuiKey_X] = (int)Keyboard::Key::X;
        io.KeyMap[ImGuiKey_Y] = (int)Keyboard::Key::Y;
        io.KeyMap[ImGuiKey_Z] = (int)Keyboard::Key::W;

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)getContext()->video->getWindow()->getNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 130");

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void terminate() override
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void fixUpdate(Time dt) override
    {
        if (Input::isKeyPressed(Keyboard::Key::W)) {
            transformSquare.translate({0.f, 1.f * dt.seconds(), 0.f});
        } else if (Input::isKeyPressed(Keyboard::Key::S)) {
            transformSquare.translate({0.f, -1.f * dt.seconds(), 0.f});
        }

        if (Input::isKeyPressed(Keyboard::Key::A)) {
            transformSquare.translate({-1.f * dt.seconds(), 0.f, 0.f});
        } else if (Input::isKeyPressed(Keyboard::Key::D)) {
            transformSquare.translate({ 1.f * dt.seconds(), 0.f, 0.f});
        }


        // ImGUI Stuff
        auto definition = getContext()->video->getWindow()->getDefinition();
        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = dt.seconds();
        io.DisplaySize = {definition.width * 1.f, definition.height * 1.f};

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Settings");
            ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor));
            ImGui::End();
        }
    }

    void render(Time dt) override
    {
        /* Render here */
        RenderCommand::clear();

        Renderer::beginScene(camera);

        flatColorShader->enable();
        flatColorShader->bindUniform("u_Color", squareColor);
        Renderer::draw(vaSquare, flatColorShader, transformSquare.getMatrix());
        Renderer::draw(vaTriangle, shader);

        Renderer::endScene();
//        Renderer::flush();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void onEvent(Event& event) override
    {
        if (event.type == Fluffy::Event::KeyPressed) {
            FLUFFY_LOG_DEBUG("key pressed: {} (ctrl: {}, alt: {}, shift: {})", event.key.code, event.key.control, event.key.alt, event.key.shift);
            if (Keyboard::Key::Up == event.key.code) {
                camera.move({0.f, 0.1f});
            } else if (Keyboard::Key::Down == event.key.code) {
                camera.move({0.f, -0.1f});
            } else if (Keyboard::Key::Left == event.key.code) {
                camera.move({-0.1f, 0.f});
            } else if (Keyboard::Key::Right == event.key.code) {
                camera.move({0.1f, 0.f});
            } else if (Keyboard::Key::R == event.key.code) {
                camera.rotateZ(1.f);
            } else if (Keyboard::Key::NumPadSubtract == event.key.code) {
                // If the camera "scales" up, we see a larger portion of the scene so everything is actually scaled down
                camera.setScale({2.f, 2.f});
            } else if (Keyboard::Key::NumPadAdd == event.key.code) {
                camera.setScale({1.f, 1.f});
            }
        }
        if (event.type == Fluffy::Event::MouseButtonPressed) {
            auto position = Input::getMousePosition();
            FLUFFY_LOG_DEBUG("Mouse button pressed: {} (at {})", EnumNames::MouseButton[(int)event.mouseButton.button], position);
        }
    }

private:
    OrthographicCamera camera;
    Ref<Shader> shader;
    Ref<Shader> flatColorShader;
    Ref<Texture2D> texture;
    Ref<VertexArray> vaTriangle;
    Ref<VertexArray> vaSquare;
    Transform transformSquare;
    Vector4f squareColor = {.2f, .8f, .43f, 1.f};
};


class EntityTestState : public State<EntityTestState>
{
public:
    void initialize() override
    {
        EntityManager em(getContext()->events);
        auto e = em.createEntity();
        e.assign<MyComponent>();
    }

    void fixUpdate(Time dt) override
    {
        requestStackPop();
        requestStackPush(CreateUnique<TestState>());
    }

    void render(Time dt) override
    {
    }

    void onEvent(Event& event) override
    {
    }
};

class TestGame : public Fluffy::Game
{
public:
    void initializeModules(ModuleRegistry& registry) override
    {
        registry.registerModule(new SystemModule());
        registry.registerModule(new VideoModule({getTitle(), WindowType::Windowed, 1280, 720}));
        registry.registerModule(new InputModule());
    }

    Unique<BaseState> start() override
    {
        return CreateUnique<EntityTestState>();
    }

    std::string getTitle() const override
    {
        return std::string("TestGame");
    }

    int getTargetFPS() const override
    {
        return 120;
    }
};

FluffyGame(TestGame)