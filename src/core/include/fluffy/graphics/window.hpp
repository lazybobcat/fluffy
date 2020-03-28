#pragma once

#include <fluffy/pch.hpp>
#include <utility>

namespace Fluffy {

enum class WindowType
{
    Windowed,
    Fullscreen,
    ResizableWindow
};

class Window
{
public:
    struct Definition
    {
        Definition(std::string title = "Fluffy", WindowType type = WindowType::Windowed, unsigned int width = 1280, unsigned int height = 720)
          : title(std::move(title))
          , type(type)
          , width(width)
          , height(height)
        {
        }

        std::string  title;
        WindowType   type;
        unsigned int width;
        unsigned int height;
    };

public:
    virtual ~Window() = default;

    virtual void update(const Definition& definition) = 0;
    virtual void setVsync(bool vsync) = 0;
    virtual const Definition& getDefinition() const = 0;

    virtual void* getNativeWindow() { return nullptr; }

private:
};
}