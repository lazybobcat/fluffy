#pragma once

// Keep this first
#include <fluffy/graphics/platform/opengl.hpp>

// Then
#include <GLFW/glfw3.h>
#include <fluffy/event/event_manager.hpp>
#include <fluffy/graphics/window.hpp>

namespace Fluffy {

class GlfwWindow : public Window
{
public:
    GlfwWindow(Definition definition);
    ~GlfwWindow();

    void                            updateDefinition(const Definition& definition) override;
    void                            setVsync(bool vsync) override;
    [[nodiscard]] const Definition& getDefinition() const override;

    void update() override;
    void swapBuffers() override;
    bool shouldClose() const override;
    bool pollEvents(Event& event) override;

    void  resize(int w, int h) override;
    void* getNativeWindow() override;

    void pushEvent(Event&& event);

private:
    void initializeGLFWEvents();

private:
    GLFWwindow* mWindow;
    Definition  mDefinition;
    EventQueue  mEvents;
};
}