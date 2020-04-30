#include <fluffy/api/modules.hpp>
#include <fluffy/fluffy_core.hpp>
#include <fluffy/fluffy_ecs.hpp>
#include <fluffy/graphics/transform.hpp>
#include <fluffy/graphics/vertex_array.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/input/input.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include "../src/platform/glfw/src/imgui_impl_glfw.h"

struct MyComponent : public Component<MyComponent>
{
    int a = 2;
};


class TestState : public State<TestState>
{
public:
    void initialize() override
    {
        // Enable blending @todo move into the renderer init function
        GlCall(glEnable(GL_BLEND));
        GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Shader
        shader = Shader::create();
        shader->loadFromFile("assets/shaders/sprite.vertex.shader", "assets/shaders/sprite.fragment.shader");
        shader->enable();

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        va.setVertex(0, { { 0.5f, -0.5f, 0.0f }, { 0, 255, 0 }, { 1.0f, 1.0f } });
        va.setVertex(1, { { 0.5f, 0.5f, 0.0f }, { 255, 0, 0 }, { 1.0f, 0.0f } });
        va.setVertex(2, { { -0.5f, -0.5f, 0.0f }, { 0, 0, 255 }, { 0.0f, 1.0f } });
        va.setVertex(3, { { -0.5f, 0.5f, 0.0f }, { 255, 255, 0 }, { 0.0f, 0.0f } });

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        va.bind();

        // My texture
        texture = Texture2D::create("assets/textures/tile.png");
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
        transform.rotate(1, { 0, 0, 0 }, { 1, 0, 1 });

        auto definition = getContext()->video->getWindow()->getDefinition();
        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = dt.seconds();
        io.DisplaySize = {definition.width * 1.f, definition.height * 1.f};

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool showOther = false;
        if (demoWindow) {
            ImGui::ShowDemoWindow(&demoWindow);
        }

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &demoWindow);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &showOther);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
    }

    void render(Time dt) override
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Textures */
        texture->bind();

        /* Shader */
        shader->enable();
        shader->bindUniform("transform", transform);

        /* Test triangle */
        va.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void onEvent(Event& event) override
    {
        if (event.type == Fluffy::Event::KeyPressed) {
            FLUFFY_LOG_DEBUG("key pressed: {} (ctrl: {}, alt: {}, shift: {})", event.key.code, event.key.control, event.key.alt, event.key.shift);
        }
        if (event.type == Fluffy::Event::MouseButtonPressed) {
            auto position = Input::getMousePosition();
            FLUFFY_LOG_DEBUG("Mouse button pressed: {} (at {})", EnumNames::MouseButton[(int)event.mouseButton.button], position);
        }
    }

private:
    Transform transform;
    Ref<Shader> shader;
    Ref<Texture2D> texture;
    VertexArray va = VertexArray(PrimitiveType::TriangleStrip, 4);

    bool demoWindow = true;
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
        registry.registerModule(new VideoModule({getTitle(), WindowType::Windowed, 720, 720}));
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