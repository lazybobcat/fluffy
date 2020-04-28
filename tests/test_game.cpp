#include <fluffy/api/modules.hpp>
#include <fluffy/fluffy_core.hpp>
#include <fluffy/fluffy_ecs.hpp>
#include <iostream>
#include <fluffy/graphics/transform.hpp>
#include <fluffy/graphics/vertex_array.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/input/input.hpp>

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
    }

    void fixUpdate(Time dt) override
    {
        transform.rotate(1, { 0, 0, 0 }, { 1, 0, 1 });
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