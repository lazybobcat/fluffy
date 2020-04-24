#pragma once

// Keep this first
#include <fluffy/graphics/platform/opengl.hpp>

// Then
#include <GLFW/glfw3.h>
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

    void handleEvents() override;
    void swapBuffers() override;
    bool shouldClose() const override;

    void  resize(int w, int h) override;
    void* getNativeWindow() override;

private:
    void initializeGLFWEvents();

private:
    GLFWwindow* mWindow;
    Definition  mDefinition;
};
}