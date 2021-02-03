#pragma once

#include "registry/plugin_registry.hpp"
#include <fluffy/api/modules.hpp>

namespace Fluffy {

class FluffyEditorModule : public SoftwareModule
{
public:
    void       initialize(const Context& context) override;
    void       terminate() override;
    String     getName() const override;
    ModuleType getType() const override;

    void initializePlugins();

    ComponentRegistry& components();

private:
    PluginRegistry mPlugins;
};
}
