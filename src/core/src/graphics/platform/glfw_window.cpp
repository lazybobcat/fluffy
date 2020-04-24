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
    FLUFFY_LOG_ERROR("GLFW error ({}): {}", error, description);
}

GlfwWindow::GlfwWindow(Window::Definition definition)
  : mDefinition(std::move(definition))
{
    glfwSetErrorCallback(error_callback);
    FLUFFY_LOG_INFO("Creating window {} ({}x{})", mDefinition.title, mDefinition.width, mDefinition.height);

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
    FLUFFY_LOG_INFO("> {}", glGetString(GL_VENDOR));
    FLUFFY_LOG_INFO("> {}", glGetString(GL_RENDERER));
    FLUFFY_LOG_INFO("> {}", glGetString(GL_VERSION));
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

void GlfwWindow::updateDefinition(const Window::Definition& definition)
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

void GlfwWindow::handleEvents()
{
    glfwPollEvents();
}

void GlfwWindow::swapBuffers()
{
    glfwSwapBuffers(mWindow);
}

bool GlfwWindow::shouldClose() const
{
    return glfwWindowShouldClose(mWindow);
}
