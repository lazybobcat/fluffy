#include <fluffy/assert.hpp>
#include <fluffy/definitions.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/utils/logger.hpp>

using namespace Fluffy;

std::ostream& Fluffy::operator<<(std::ostream& os, Fluffy::LogLevel level)
{
    switch (level) {
        case LogLevel::Error:
            return os << "error";

        case LogLevel::Warning:
            return os << "warn";

        case LogLevel::Info:
            return os << "info";

        case LogLevel::Debug:
        default:
            return os << "debug";
    }

    return os;
}

/*****************************************************/

void StdOutSink::log(LogLevel level, const String& message)
{
    std::unique_lock<std::mutex> lock(mMutex);

    switch (level) {
        case LogLevel::Error:
            std::cout << "\033[31m";
            break;

        case LogLevel::Warning:
            std::cout << "\033[33m";
            break;

        case LogLevel::Info:
            std::cout << "\033[94m";
            break;

        case LogLevel::Debug:
            std::cout << "\033[37m";
            break;
    }

    std::cout << "[" << currentDateTime() << "] [" << level << "] " << message << "\033[0m" << std::endl;
}

FileSink::FileSink()
{
    mFile.open(FLUFFY_LOG_FILE, std::ios::trunc);
    mFile.close();
}

void FileSink::log(LogLevel level, const String& message)
{
    std::unique_lock<std::mutex> lock(mMutex);
    mFile.open(FLUFFY_LOG_FILE, std::ios::app);

    if (mFile.is_open()) {
        mFile << "[" << currentDateTime() << "] [" << level << "] " << message << std::endl;
        mFile.flush();
    }

    mFile.close();
}

/*****************************************************/

Logger* Logger::sInstance = nullptr;

void Logger::init(bool testMode)
{
    if (nullptr == sInstance) {
        sInstance = new Logger();

        if (!testMode) {
            auto console_sink = new StdOutSink();
            console_sink->setLevel(LogLevel::Debug);
            sInstance->mSinks.insert(console_sink);
        }

        auto file_sink = new FileSink();
        file_sink->setLevel(LogLevel::Info);
        sInstance->mSinks.insert(file_sink);
    }
}

void Logger::clear()
{
    for (BaseLoggerSink* sink : sInstance->mSinks) {
        delete sink;
    }

    delete sInstance;
    sInstance = nullptr;
}

void Logger::log(LogLevel level, const String& message)
{
    FLUFFY_ASSERT(sInstance, "No Logger instance has been created, use Logger::Init()");

    for (auto& sink : sInstance->mSinks) {
        if (sink->canLog(level)) {
            sink->log(level, message);
        }
    }
}

void Logger::addSink(BaseLoggerSink* sink)
{
    FLUFFY_ASSERT(sInstance, "No Logger instance has been created, use Logger::Init()");

    sInstance->mSinks.insert(sink);
}
