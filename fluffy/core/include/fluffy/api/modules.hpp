#pragma once

#include <fluffy/graphics/render_target.hpp>
#include <fluffy/graphics/window.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/resources/resource_library.hpp>

namespace Fluffy {

class Context;

enum class ModuleType
{
    System = 0,
    Video,
    Input,
    Audio,
    Network,
    Platform,
    Software,
};

namespace EnumNames {
const std::array<const char*, 7> ModuleType({ { "system", "video", "input", "audio", "network", "platform", "software" } });
}

class BaseModule
{
public:
    virtual ~BaseModule() = default;

    virtual void initialize(const Context& context) = 0;
    virtual void terminate()                        = 0;

    [[nodiscard]] virtual String     getName() const = 0;
    [[nodiscard]] virtual ModuleType getType() const = 0;
};

class ModuleRegistry
{
public:
    /**
     * ModuleRegistry takes the ownership of your modules!!!
     */
    void                                            registerModule(BaseModule* module);
    [[nodiscard]] std::map<ModuleType, BaseModule*> getModules() const;
    [[nodiscard]] BaseModule*                       getModule(ModuleType type) const;

private:
    std::map<ModuleType, BaseModule*> mRegistry;
};

class SystemModule : public BaseModule
{
public:
    void initialize(const Context& context) override;
    void terminate() override;

    ResourceLibrary& getResources() const;

    String getName() const override
    {
        return "system_module";
    }

    ModuleType getType() const override
    {
        return ModuleType::System;
    }

private:
    Unique<ResourceLibrary> mResources;
};

class VideoModule : public BaseModule
{
public:
    explicit VideoModule(Window::Definition&& windowDefinition);

    void initialize(const Context& context) override;
    void terminate() override;

    virtual int getMaxTextureSlots() = 0;
    /*
     * @todo
    virtual Unique<Texture> createTexture(Vector2i size) = 0;
    virtual Unique<Shader> createShader(const ShaderDefinition& definition) = 0;
     */
    virtual Unique<ScreenRenderTarget>  createScreenRenderTarget()  = 0;
    virtual Unique<TextureRenderTarget> createTextureRenderTarget() = 0;
    virtual Unique<Painter>             createPainter()             = 0;

    virtual void beginRender() = 0;
    virtual void endRender()   = 0;

    String getName() const override
    {
        return "video_module";
    }

    ModuleType getType() const override
    {
        return ModuleType::Video;
    }

    Window* getWindow() const
    {
        return mWindow.get();
    }

protected:
    virtual Unique<Window> createWindow(const Window::Definition& definition) = 0;

protected:
    Window::Definition mWindowDefinition;
    Unique<Window>     mWindow = nullptr;
};

class InputModule : public BaseModule
{
public:
    void initialize(const Context& context) override;
    void terminate() override;

    String getName() const override
    {
        return "input_module";
    }

    ModuleType getType() const override
    {
        return ModuleType::Input;
    }
};

class SoftwareModule : public BaseModule
{
public:
    virtual void initialize(const Context& context) override {}
    virtual void terminate() override {}

    String getName() const override
    {
        return "software_module";
    }

    ModuleType getType() const override
    {
        return ModuleType::Software;
    }
};
}