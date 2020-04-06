#pragma once

#include <fluffy/graphics/window.hpp>
#include <fluffy/pch.hpp>

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
};

namespace EnumNames {
const std::array<const char*, 6> ModuleType({ { "system", "video", "input", "audio", "network", "platform" } });
}

class BaseModule
{
public:
    virtual ~BaseModule() = default;

    virtual void initialize(const Context& context) = 0;
    virtual void terminate()                        = 0;

    [[nodiscard]] virtual std::string getName() const = 0;
    [[nodiscard]] virtual ModuleType  getType() const = 0;
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

    [[nodiscard]] std::string getName() const override {
        return "system_module";
    }

      [[nodiscard]] ModuleType getType() const override
    {
        return ModuleType::System;
    }
};

class VideoModule : public BaseModule
{
public:
    explicit VideoModule(Window::Definition&& windowDefinition);

    void initialize(const Context& context) override;
    void terminate() override;

    [[nodiscard]] std::string getName() const override {
        return "video_module";
    }

      [[nodiscard]] ModuleType getType() const override
    {
        return ModuleType::Video;
    }

    [[nodiscard]] Window* getWindow() const {
        return mWindow;
    }

    private : Window::Definition mWindowDefinition;
    Window* mWindow = nullptr;
};
}