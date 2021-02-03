#include <fluffy/api/context.hpp>
#include <fluffy/assert.hpp>
#include <fluffy/definitions.hpp>
#include <fluffy/file/path.hpp>

using namespace Fluffy;

Context::Context(const ModuleRegistry& registry)
{
    FLUFFY_LOG_INFO("Thanks for using Fluffy, {}", FLUFFY_VERSION);
#ifdef FLUFFY_DEBUG
    FLUFFY_LOG_WARN("Fluffy is in DEBUG mode");
#endif
    FLUFFY_LOG_INFO("Create game context");
    FLUFFY_LOG_INFO("> Working directory: '{}'", Path::getWorkingDirectory());

    // Event manager/bus
    eventManager = CreateUnique<EventManager>();

    auto modules = registry.getModules();

    {
        auto module = dynamic_cast<SystemModule*>(registry.getModule(ModuleType::System));
        FLUFFY_ASSERT(module, "System module must be defined");
        FLUFFY_LOG_INFO("> Loaded {} module: {}", EnumNames::ModuleType[(int)ModuleType::System], module->getName());
        systemModule.reset(module);
    }

    {
        auto module = dynamic_cast<VideoModule*>(registry.getModule(ModuleType::Video));
        FLUFFY_ASSERT(module, "Video module must be defined");
        FLUFFY_LOG_INFO("> Loaded {} module: {}", EnumNames::ModuleType[(int)ModuleType::Video], module->getName());
        videoModule.reset(module);
    }

    {
        auto module = dynamic_cast<InputModule*>(registry.getModule(ModuleType::Input));
        if (module) {
            FLUFFY_LOG_INFO("> Loaded {} module: {}", EnumNames::ModuleType[(int)ModuleType::Input], module->getName());
            inputModule.reset(module);
        }
    }

    {
        auto module = dynamic_cast<SoftwareModule*>(registry.getModule(ModuleType::Software));
        if (module) {
            FLUFFY_LOG_INFO("> Loaded {} module: {}", EnumNames::ModuleType[(int)ModuleType::Software], module->getName());
            softwareModule.reset(module);
        }
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
    events = eventManager.get();
    system = systemModule.get();
    video  = videoModule.get();

    if (inputModule) {
        input = inputModule.get();
    }

    if (softwareModule) {
        software = softwareModule.get();
    }

    // @todo assign other modules
}

void Context::initialize()
{
    if (system) {
        system->initialize(*this);
    }

    if (video) {
        video->initialize(*this);
    }

    if (input) {
        input->initialize(*this);
    }

    if (software) {
        software->initialize(*this);
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

    if (input) {
        input->terminate();
    }

    if (software) {
        software->terminate();
    }

    // @todo terminate other modules
}
