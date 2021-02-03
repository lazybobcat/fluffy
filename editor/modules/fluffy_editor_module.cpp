#include "fluffy_editor_module.hpp"
#include "plugins/fluffy_plugin.hpp"

using namespace Fluffy;

void FluffyEditorModule::initialize(const Context& context)
{
}

void FluffyEditorModule::terminate()
{
}

String FluffyEditorModule::getName() const
{
    return "fluffy_editor_module";
}

ModuleType FluffyEditorModule::getType() const
{
    return ModuleType::Software;
}

void FluffyEditorModule::initializePlugins()
{
    mPlugins.addPlugin<FluffyPlugin>();
}

ComponentRegistry& FluffyEditorModule::components()
{
    return mPlugins.components();
}
