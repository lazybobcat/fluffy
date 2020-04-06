#include <fluffy/definitions.hpp>
#include <fluffy/graphics/platform/glfw_window.hpp>
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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mWindow))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Test triangle */

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
