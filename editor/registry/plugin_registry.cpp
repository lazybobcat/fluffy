#include "plugin_registry.hpp"

using namespace Fluffy;

PluginRegistry::~PluginRegistry()
{
    for (auto& it : mPlugins) {
        it.second->terminate(this);
    }
}

ComponentRegistry& PluginRegistry::components()
{
    return mComponents;
}
