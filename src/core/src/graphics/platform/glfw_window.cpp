#include <fluffy/assert.hpp>
#include <fluffy/definitions.hpp>
#include <fluffy/graphics/platform/glfw_window.hpp>
#include <fluffy/graphics/platform/opengl.hpp>
#include <fluffy/graphics/platform/opengl_shader.hpp>
#include <fluffy/graphics/platform/opengl_texture.hpp>
#include <fluffy/graphics/transform.hpp>
#include <fluffy/graphics/vertex_array.hpp>
#include <utility>

using namespace Fluffy;

void error_callback(int error, const char* description)
{
    FLUFFY_LOG_ERROR("GLFW error (" + toString(error) + "): " + toString(description));
}

GlfwWindow::GlfwWindow(Window::Definition definition)
  : mDefinition(std::move(definition))
{
    glfwSetErrorCallback(error_callback);
    FLUFFY_LOG_INFO("Creating window " + mDefinition.title + " (" + toString(mDefinition.width) + "x" + toString(mDefinition.height) + ")");

    int success = glfwInit();
    FLUFFY_ASSERT(success, "Failed to initialize GLFW");

    // Some declarations about our OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow((int)mDefinition.width, (int)mDefinition.height, mDefinition.title.c_str(), nullptr, nullptr);
    FLUFFY_ASSERT(mWindow, "Failed to create GLFW window");

    glfwMakeContextCurrent(mWindow);

    auto initialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    FLUFFY_ASSERT(initialized, "Failed to initialize GLAD");

    resize(mDefinition.width, mDefinition.height);
    initializeGLFWEvents();

    // @todo move into Context
    FLUFFY_LOG_INFO("> " + toString(glGetString(GL_VENDOR)));
    FLUFFY_LOG_INFO("> " + toString(glGetString(GL_RENDERER)));
    FLUFFY_LOG_INFO("> " + toString(glGetString(GL_VERSION)));

    // Enable blending @todo move into the renderer init function
    GlCall(glEnable(GL_BLEND));
    GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Shader
    auto shader = Shader::create();
    shader->loadFromFile("assets/shaders/sprite.vertex.shader", "assets/shaders/sprite.fragment.shader");
    shader->enable();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    VertexArray va(PrimitiveType::TriangleStrip, 4);
    va.setVertex(0, { { 0.5f, -0.5f, 0.0f }, { 0, 255, 0 }, { 1.0f, 1.0f } });
    va.setVertex(1, { { 0.5f, 0.5f, 0.0f }, { 255, 0, 0 }, { 1.0f, 0.0f } });
    va.setVertex(2, { { -0.5f, -0.5f, 0.0f }, { 0, 0, 255 }, { 0.0f, 1.0f } });
    va.setVertex(3, { { -0.5f, 0.5f, 0.0f }, { 255, 255, 0 }, { 0.0f, 0.0f } });

    //    va.append({{ -0.5f, -0.5f, -1.f}, {0, 255, 255}, {0.0f, 0.0f}}); // 4
    //    va.append({{ -0.5f,  0.5f, -1.f}, {255, 128, 128}, {0.0f, 1.0f}}); // 5
    //    va.append({{ 0.5f, -0.5f, -1.f}, {0, 255, 0}, {0.0f, 0.0f}}); // 6
    //    va.append({{ 0.5f,  0.5f, -1.f}, {0, 255, 0}, {0.0f, 1.0f}}); // 7
    //    va.append({{ 0.5f, -0.5f, 0.0f}, {0, 255, 0}, {1.0f, 0.0f}}); // 0
    //    va.append({{ 0.5f,  0.5f, 0.0f}, {255, 0, 0}, {1.0f, 1.0f}}); // 1

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    va.bind();

    // My texture
    auto texture = Texture2D::create("assets/textures/tile.png");
    texture->setRepeat(RepeatType::Repeat);

    // Transform
    Transform transform;
    //    transform.rotate(45, {0.2,0,0}, {0,0,1});
    //    transform.translate({0.2, 0, 0});

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mWindow)) {
        transform.rotate(1, { 0, 0, 0 }, { 1, 0, 1 });

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

        /* Swap front and back buffers */
        glfwSwapBuffers(mWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

GlfwWindow::~GlfwWindow()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void GlfwWindow::initializeGLFWEvents()
{
    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
}

void GlfwWindow::update(const Window::Definition& definition)
{
    mDefinition = definition;
}

void GlfwWindow::setVsync(bool vsync)
{
    if (vsync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
}

const Window::Definition& GlfwWindow::getDefinition() const
{
    return mDefinition;
}

void* GlfwWindow::getNativeWindow()
{
    return mWindow;
}

void GlfwWindow::resize(int w, int h)
{
    glViewport(0, 0, w, h);
}
