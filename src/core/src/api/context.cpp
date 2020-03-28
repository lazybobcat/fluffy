#include <fluffy/api/context.hpp>

using namespace Fluffy;

Context::Context(const ModuleRegistry& registry)
{
    auto modules = registry.getModules();

    {
        auto module = dynamic_cast<SystemModule*>(registry.getModule(ModuleType::System));
        assert(module && "System module must be defined");
        FLUFFY_LOG_INFO("Loaded " + toString(EnumNames::ModuleType[(int)ModuleType::System]) + " module: " + module->getName());
        systemModule.reset(module);
    }

    {
        auto module = dynamic_cast<VideoModule*>(registry.getModule(ModuleType::Video));
        assert(module && "Video module must be defined");
        FLUFFY_LOG_INFO("Loaded " + toString(EnumNames::ModuleType[(int)ModuleType::Video]) + " module: " + module->getName());
        videoModule.reset(module);
    }

    // @todo other modules here (they should not be mandatory as are system and video

    assign();
}

Context::~Context()
{
    terminate();
}

void Context::assign()
{
    system = systemModule.get();
    video  = videoModule.get();

    // @todo assign other modules
    //    if (...Module) {
    //        ... = ...Module.get();
    //    }
}

void Context::initialize()
{
    if (system) {
        system->initialize(*this);
    }

    if (video) {
        video->initialize(*this);
    }

    // @todo init other modules
}

void Context::terminate()
{
    if (system) {
        system->terminate();
    }

    if (video) {
        video->terminate();
    }

    // @todo terminate other modules
}
