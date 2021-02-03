#pragma once

#include "component_registry.hpp"
#include <fluffy/definitions.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class PluginRegistry;

class Plugin
{
public:
    virtual ~Plugin() = default;

    virtual String getPluginName() = 0;

    virtual void initialize(PluginRegistry* registry) = 0;
    virtual void terminate(PluginRegistry* registry)  = 0;
};

class PluginRegistry
{
public:
    PluginRegistry() = default;
    ~PluginRegistry();

    ComponentRegistry& components();

    template<typename T, typename... Args>
    void addPlugin(Args&&... args)
    {
        Ref<Plugin> plugin = CreateRef<T>(std::forward<Args>(args)...);
        plugin->initialize(this);
        mPlugins.insert({ plugin->getPluginName(), plugin });
    }

private:
    std::map<String, Ref<Plugin>> mPlugins;

    ComponentRegistry mComponents;
};
}
