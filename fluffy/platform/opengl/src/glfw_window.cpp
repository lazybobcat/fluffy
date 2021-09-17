#include "glfw_window.hpp"
#include "glfw_functions.hpp"
#include <fluffy/pch.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

void error_callback(int error, const char* description)
{
    FLUFFY_LOG_ERROR("GLFW error ({}): {}", error, description);
}

const std::map<std::string, Keyboard::Key> keyMap = {
    { "a", Keyboard::Key::A },
    { "b", Keyboard::Key::B },
    { "c", Keyboard::Key::C },
    { "d", Keyboard::Key::D },
    { "e", Keyboard::Key::E },
    { "f", Keyboard::Key::F },
    { "g", Keyboard::Key::G },
    { "h", Keyboard::Key::H },
    { "i", Keyboard::Key::I },
    { "j", Keyboard::Key::J },
    { "k", Keyboard::Key::K },
    { "l", Keyboard::Key::L },
    { "m", Keyboard::Key::M },
    { "n", Keyboard::Key::N },
    { "o", Keyboard::Key::O },
    { "p", Keyboard::Key::P },
    { "q", Keyboard::Key::Q },
    { "r", Keyboard::Key::R },
    { "s", Keyboard::Key::S },
    { "t", Keyboard::Key::T },
    { "u", Keyboard::Key::U },
    { "v", Keyboard::Key::V },
    { "w", Keyboard::Key::W },
    { "x", Keyboard::Key::X },
    { "y", Keyboard::Key::Y },
    { "z", Keyboard::Key::Z },
    { "0", Keyboard::Key::Num0 },
    { "1", Keyboard::Key::Num1 },
    { "2", Keyboard::Key::Num2 },
    { "3", Keyboard::Key::Num3 },
    { "4", Keyboard::Key::Num4 },
    { "5", Keyboard::Key::Num5 },
    { "6", Keyboard::Key::Num6 },
    { "7", Keyboard::Key::Num7 },
    { "8", Keyboard::Key::Num8 },
    { "9", Keyboard::Key::Num9 },
};

Keyboard::Key toKeyboardKey(int key, int scancode)
{
    if (key >= 48 && key <= 90) {
        std::string alpha = glfwGetKeyName(key, 0);
        if (keyMap.find(alpha) != keyMap.end()) {
            return keyMap.find(alpha)->second;
        }
        FLUFFY_LOG_ERROR("Keyboard key {} ({}) not found.", key, alpha);
    }

    return static_cast<Keyboard::Key>(key);
}

GlfwWindow::GlfwWindow(Window::Definition definition)
  : mDefinition(std::move(definition))
{
    FLUFFY_PROFILE_FUNCTION();
    glfwSetErrorCallback(error_callback);
    FLUFFY_LOG_INFO("Creating window {} ({}x{})", mDefinition.title, mDefinition.width, mDefinition.height);

    int success = glfwInit();
    FLUFFY_ASSERT(success, "Failed to initialize GLFW");

    // Some declarations about our OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    bool doMaximize = false;

    switch (mDefinition.type) {
        case WindowType::Fullscreen: {
            auto size = getMonitorSize();
            FLUFFY_LOG_INFO("Fullscreen: Raw size is {}x{}", size.x, size.y);
            mDefinition.width  = size.x;
            mDefinition.height = size.y;
            mWindow            = glfwCreateWindow((int)mDefinition.width, (int)mDefinition.height, mDefinition.title.c_str(), glfwGetPrimaryMonitor(), nullptr);
        } break;
        case WindowType::Maximized: {
            doMaximize = true;
            auto size  = getMonitorSize();
            FLUFFY_LOG_INFO("Maximized: Raw size is {}x{}", size.x, size.y);
            mDefinition.width  = size.x;
            mDefinition.height = size.y;
        }
        case WindowType::Windowed:
        default:
            mWindow = glfwCreateWindow((int)mDefinition.width, (int)mDefinition.height, mDefinition.title.c_str(), nullptr, nullptr);
            break;
    }

    FLUFFY_ASSERT(mWindow, "Failed to create GLFW window");

    glfwMakeContextCurrent(mWindow);
    glfwSetWindowUserPointer(mWindow, this);

    auto initialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    FLUFFY_ASSERT(initialized, "Failed to initialize GLAD");

    resize(mDefinition.width, mDefinition.height);
    if (doMaximize) {
        maximize();
    }
    initializeGLFWEvents();
}

GlfwWindow::~GlfwWindow()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

Vector2u GlfwWindow::getMonitorSize() const
{
    int          posX, posY, width, height;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(monitor, &posX, &posY, &width, &height);

    return { width, height };
}

void GlfwWindow::initializeGLFWEvents()
{
    FLUFFY_PROFILE_FUNCTION();
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
//        std::cout << "Key code is " << key << " (" << (char)key << ") / scancode is " << scancode << " (" << (char)scancode << ")" << " / key name is " << glfwGetKeyName(key, 0) << std::endl;

        Keyboard::Key layoutKey = toKeyboardKey(key, scancode);

        switch (action) {
            case GLFW_PRESS:
                glfwWindow->pushEvent(Event::createKeyPressedEvent(
                  layoutKey,
                  false,
                  mods & GLFW_MOD_CONTROL,
                  mods & GLFW_MOD_ALT,
                  mods & GLFW_MOD_SHIFT));
                break;

            case GLFW_REPEAT:
                glfwWindow->pushEvent(Event::createKeyPressedEvent(layoutKey, true));
                break;

            case GLFW_RELEASE:
                glfwWindow->pushEvent(Event::createKeyReleasedEvent(layoutKey));
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
        auto* glfwWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));

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
    FLUFFY_PROFILE_FUNCTION();
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
    FLUFFY_PROFILE_FUNCTION();
    glfwSwapBuffers(mWindow);
}

bool GlfwWindow::shouldClose() const
{
    return glfwWindowShouldClose(mWindow);
}

bool GlfwWindow::pollEvents(Event& event)
{
    FLUFFY_PROFILE_FUNCTION();
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

void GlfwWindow::maximize()
{
    glfwMaximizeWindow(mWindow);
}

void GlfwWindow::close()
{
    glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}
