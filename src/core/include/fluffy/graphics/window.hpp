#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/pch.hpp>
#include <utility>

namespace Fluffy {

enum class WindowType
{
    Windowed,
    Fullscreen,
    Resizable
};

namespace EnumNames {
const std::array<const char*, 6> WindowType({ { "windowed", "fullscreen", "resizable" } });
}

class Window
{
public:
    struct Definition
    {
        Definition(String title = "Fluffy", WindowType type = WindowType::Windowed, unsigned int width = 1280, unsigned int height = 720)
          : title(std::move(title))
          , type(type)
          , width(width)
          , height(height)
        {
        }

        String       title;
        WindowType   type;
        unsigned int width;
        unsigned int height;
    };

public:
    virtual ~Window() = default;

    static Unique<Window> create(const Definition& definition);

    virtual void                            updateDefinition(const Definition& definition) = 0;
    virtual void                            setVsync(bool vsync)                           = 0;
    [[nodiscard]] virtual const Definition& getDefinition() const                          = 0;

    virtual void               handleEvents()      = 0;
    virtual void               swapBuffers()       = 0;
    [[nodiscard]] virtual bool shouldClose() const = 0;

    virtual void  resize(int w, int h) {}
    virtual void* getNativeWindow() { return nullptr; }
};
}