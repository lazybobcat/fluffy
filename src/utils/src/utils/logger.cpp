#include <fluffy/definitions.hpp>
#include <fluffy/utils/logger.hpp>

using namespace Fluffy;

std::string currentDateTime()
{
    time_t    now = time(0);
    struct tm tstruct;
    char      buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return std::string(buf);
}

std::ostream& operator<<(std::ostream& os, LogLevel level)
{
    switch (level) {
        case LogLevel::Error:
            return os << "error";

        case LogLevel::Warning:
            return os << "warn";

        case LogLevel::Info:
            return os << "info";

        case LogLevel::Debug:
            return os << "debug";
    }

    return os;
}

/*****************************************************/

void StdOutSink::log(LogLevel level, const std::string& message)
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

void FileSink::log(LogLevel level, const std::string& message)
{
    std::unique_lock<std::mutex> lock(mMutex);
    mFile.open(FLUFFY_LOG_FILE, std::ios::app);

    if (mFile.is_open()) {
        mFile << "[" << currentDateTime() << "] [" << level << "] " << message << std::endl;
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

void Logger::log(LogLevel level, const std::string& message)
{
    assert(sInstance);

    for (auto& sink : sInstance->mSinks) {
        if (sink->canLog(level)) {
            sink->log(level, message);
        }
    }
}

void Logger::debug(const std::string& message)
{
    log(LogLevel::Debug, message);
}

void Logger::info(const std::string& message)
{
    log(LogLevel::Info, message);
}

void Logger::warn(const std::string& message)
{
    log(LogLevel::Warning, message);
}

void Logger::error(const std::string& message)
{
    log(LogLevel::Error, message);
}
