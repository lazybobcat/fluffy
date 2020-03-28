#include <fluffy/api/context.hpp>
#include <fluffy/api/modules.hpp>

using namespace Fluffy;

void ModuleRegistry::registerModule(BaseModule* module)
{
    ModuleType type = module->getType();
    auto       it   = mRegistry.find(type);
    if (it != mRegistry.end()) {
        FLUFFY_LOG_WARN("Module '" + it->second->getName() + "' of type '" + EnumNames::ModuleType[(int)type] + "' has already been registered. Removing it.");
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
