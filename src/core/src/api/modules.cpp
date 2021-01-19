#include <fluffy/api/context.hpp>
#include <fluffy/api/modules.hpp>
#include <fluffy/input/input.hpp>

using namespace Fluffy;

void ModuleRegistry::registerModule(BaseModule* module)
{
    ModuleType type = module->getType();
    auto       it   = mRegistry.find(type);
    if (it != mRegistry.end()) {
        FLUFFY_LOG_WARN("Module '{}' of type '{}' has already been registered. Removing it.", it->second->getName(), EnumNames::ModuleType[(int)type]);
        delete it->second;
    }

    mRegistry[type] = module;
}

std::map<ModuleType, BaseModule*> ModuleRegistry::getModules() const
{
    return mRegistry;
}

BaseModule* ModuleRegistry::getModule(ModuleType type) const
{
    auto it = mRegistry.find(type);
    if (it != mRegistry.end()) {
        return it->second;
    }

    return nullptr;
}

/**********************************************************************************************************************/

void SystemModule::initialize(const Context& context)
{
}

void SystemModule::terminate()
{
}

/**********************************************************************************************************************/

VideoModule::VideoModule(Window::Definition&& windowDefinition)
  : mWindowDefinition(windowDefinition)
{
}

void VideoModule::initialize(const Context& context)
{
    mWindow = Window::create(mWindowDefinition);

}

void VideoModule::terminate()
{
}

/**********************************************************************************************************************/

void InputModule::initialize(const Context& context)
{
    Input::create(context.video->getWindow());
}

void InputModule::terminate()
{
}
