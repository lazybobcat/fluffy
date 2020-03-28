#pragma once

#include <GLFW/glfw3.h>
#include <fluffy/graphics/window.hpp>

namespace Fluffy {

class GlfwWindow : public Window
{
public:
    GlfwWindow(Definition definition);
    ~GlfwWindow();

    void              update(const Definition& definition) override;
    void              setVsync(bool vsync) override;
    const Definition& getDefinition() const override;
    void*             getNativeWindow() override;

private:
    GLFWwindow* mWindow;
    Definition  mDefinition;
};
}