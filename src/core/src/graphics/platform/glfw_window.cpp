#include <fluffy/definitions.hpp>
#include <fluffy/graphics/platform/glfw_window.hpp>
#include <utility>
#include <fluffy/graphics/platform/opengl_shader.hpp>
#include <fluffy/graphics/platform/opengl.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/graphics/vertex_array.hpp>

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
    if(!success) {
        FLUFFY_LOG_ERROR("Failed to initialize GLFW");
        exit(1); // @todo exit codes
    }

    // Some declarations about our OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow((int)mDefinition.width, (int)mDefinition.height, mDefinition.title.c_str(), nullptr, nullptr);
    if (!mWindow)
    {
        FLUFFY_LOG_ERROR("Failed to create GLFW window");
        exit(1); // @todo exit codes
    }

    glfwMakeContextCurrent(mWindow);

    auto initialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!initialized)
    {
        FLUFFY_LOG_ERROR("Failed to initialize GLAD (error " + toString(initialized));
        exit(1); // @todo exit codes
    }

    resize(mDefinition.width, mDefinition.height);
    initializeGLFWEvents();

    // Shader
    OpenglShader shader;
    shader.loadFromFile("assets/shaders/sprite.vertex.shader", "assets/shaders/sprite.fragment.shader");
    shader.enable();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    VertexArray va(4);
    va[0] = {{ 0.5f,  0.5f, 0.0f}, {255, 0, 0}, {1.0f, 1.0f}};
    va[1] = {{ 0.5f, -0.5f, 0.0f}, {0, 255, 0}, {1.0f, 0.0f}};
    va[2] = {{ -0.5f, -0.5f, 0.0f}, {0, 0, 255}, {0.0f, 0.0f}};
    va[3] = {{ -0.5f,  0.5f, 0.0f}, {255, 255, 0}, {0.0f, 1.0f}};
    const float* vertices = va.raw();
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    va.bind();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    GlCall(glBufferData(GL_ARRAY_BUFFER, va.getByteSize(), vertices, GL_STATIC_DRAW));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // Position
    GlCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
    glEnableVertexAttribArray(0);
    // Color
    GlCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float))));
    glEnableVertexAttribArray(1);
    // Texture
    GlCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // My texture
    Texture2D texture;
    texture.loadFromFile("assets/textures/tile.png");
    texture.setRepeat(RepeatType::Repeat);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mWindow))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Textures */
        texture.bind();

        /* Shader */
        shader.enable();

        /* Test triangle */
        va.bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        /* Swap front and back buffers */
        glfwSwapBuffers(mWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

GlfwWindow::~GlfwWindow()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void GlfwWindow::initializeGLFWEvents()
{
    glfwSetFramebufferSizeCallback(mWindow, [] (GLFWwindow* window, int width, int height) {
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
