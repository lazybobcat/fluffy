#include "glfw_window.hpp"
#include "../../opengl/src/opengl.hpp"
#include <fluffy/assert.hpp>
#include <fluffy/definitions.hpp>
#include <fluffy/pch.hpp>

using namespace Fluffy;

Unique<Window> Window::create(const Window::Definition& definition)
{
    return CreateUnique<GlfwWindow>(definition);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    glfwSetWindowUserPointer(mWindow, this);

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
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        glfwWindow->resize(width, height);
        glfwWindow->pushEvent(Event::createWindowResizedEvent({ width, height }));
    });

    glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        glfwWindow->pushEvent(Event::createWindowClosedEvent());
    });

    glfwSetWindowFocusCallback(mWindow, [](GLFWwindow* window, int focused) {
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        if (focused) {
            glfwWindow->pushEvent(Event::createWindowGainedFocusEvent());
        } else {
            glfwWindow->pushEvent(Event::createWindowLostFocusEvent());
        }
    });

    glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        //std::cout << "Key code is " << key << " (" << (char)key << ") / scancode is " << scancode << " (" << (char)scancode << ")" << std::endl;

        switch (action) {
            case GLFW_PRESS:
                glfwWindow->pushEvent(Event::createKeyPressedEvent(
                  static_cast<Keyboard::Key>(key),
                  false,
                  mods & GLFW_MOD_CONTROL,
                  mods & GLFW_MOD_ALT,
                  mods & GLFW_MOD_SHIFT));
                break;

            case GLFW_REPEAT:
                glfwWindow->pushEvent(Event::createKeyPressedEvent(static_cast<Keyboard::Key>(key), true));
                break;

            case GLFW_RELEASE:
                glfwWindow->pushEvent(Event::createKeyReleasedEvent(static_cast<Keyboard::Key>(key)));
                break;

            default:
                break;
        }
    });

    glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int unicode) {
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        glfwWindow->pushEvent(Event::createTextEnteredEvent(unicode));
    });

    glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double x, double y) {
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        glfwWindow->pushEvent(Event::createMouseMovedEvent({ x, y }));
    });

    glfwSetCursorEnterCallback(mWindow, [](GLFWwindow* window, int entered) {
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));

        if (entered) {
            glfwWindow->pushEvent(Event::createMouseEnteredEvent());
        } else {
            glfwWindow->pushEvent(Event::createMouseLeftEvent());
        }
    });

    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
        auto* glfwWindow     = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        auto  toFluffyButton = [](int button) -> Mouse::Button {
            switch (button) {
                case GLFW_MOUSE_BUTTON_LEFT:
                    return Mouse::ButtonLeft;

                case GLFW_MOUSE_BUTTON_RIGHT:
                    return Mouse::ButtonRight;

                case GLFW_MOUSE_BUTTON_MIDDLE:
                    return Mouse::ButtonMiddle;

                case GLFW_MOUSE_BUTTON_4:
                    return Mouse::XButton1;

                case GLFW_MOUSE_BUTTON_5:
                    return Mouse::XButton2;

                default:
                    return Mouse::ButtonLeft;
            }
        };

        switch (action) {
            case GLFW_PRESS:
                glfwWindow->pushEvent(Event::createMouseButtonPressedEvent(toFluffyButton(button)));
                break;

            case GLFW_RELEASE:
                glfwWindow->pushEvent(Event::createMouseButtonReleasedEvent(toFluffyButton(button)));
                break;

            default:
                break;
        }
    });

    glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double x, double y) {
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        glfwWindow->pushEvent(Event::createMouseWheelScrolledEvent({ x, y }));
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
    mDefinition.width  = w;
    mDefinition.height = h;
}

void GlfwWindow::update()
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

bool GlfwWindow::pollEvents(Event& event)
{
    if (mEvents.isEmpty()) {
        return false;
    }

    event = mEvents.pull();

    return true;
}

void GlfwWindow::pushEvent(Event&& event)
{
    mEvents.push(event);
}
