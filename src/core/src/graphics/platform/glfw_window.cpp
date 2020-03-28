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
        FLUFFY_LOG_ERROR("something went wrong");
        exit(1);
    }

    mWindow = glfwCreateWindow((int)mDefinition.width, (int)mDefinition.height, mDefinition.title.c_str(), nullptr, nullptr);
    assert(mWindow);

    glfwMakeContextCurrent(mWindow);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Test triangle */
        glBegin(GL_TRIANGLES);
        glVertex2f(-.5f, -.5f);
        glVertex2f(0.f, .5f);
        glVertex2f(.5f, -.5f);
        glEnd();

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
