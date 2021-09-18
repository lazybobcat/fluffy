#pragma once

#include "registry/plugin_registry.hpp"
#include <fluffy/graphics/transformable.hpp>

namespace Fluffy {

class FluffyPlugin : public Plugin
{
public:
    String getPluginName() override;
    void   initialize(PluginRegistry* registry) override;
    void   terminate(PluginRegistry* registry) override;
};
}
