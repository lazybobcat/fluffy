#pragma once

#include <fluffy/pch.hpp>
#include <fluffy/text/string.hpp>
#include <fmt/format.h>
#include <mutex>

namespace Fluffy {

enum class LogLevel
{
    Debug,
    Info,
    Warning,
    Error,
};

class BaseLoggerSink
{
public:
    virtual ~BaseLoggerSink()                               = default;
    virtual void log(LogLevel level, const String& message) = 0;

    void setLevel(LogLevel level) { mMinimumLevel = level; }
    bool canLog(LogLevel level) { return level >= mMinimumLevel; }

private:
    LogLevel mMinimumLevel = LogLevel::Debug;
};

class StdOutSink : public BaseLoggerSink
{
public:
    void log(LogLevel level, const String& message) override;

private:
    std::mutex mMutex;
};

class FileSink : public BaseLoggerSink
{
public:
    FileSink();
    void log(LogLevel level, const String& message) override;

private:
    std::mutex    mMutex;
    std::ofstream mFile;
};

class Logger
{
public:
    static void init(bool testMode = false);
    static void clear();
    static void addSink(BaseLoggerSink* sink); // Logger takes ownership of the pointer

    template<typename... Args>
    static void debug(const String& message, Args... args)
    {
        log(LogLevel::Debug, fmt::format(message, args...));
    }

    template<typename... Args>
    static void info(const String& message, Args... args)
    {
        log(LogLevel::Info, fmt::format(message, args...));
    }

    template<typename... Args>
    static void warn(const String& message, Args... args)
    {
        log(LogLevel::Warning, fmt::format(message, args...));
    }

    template<typename... Args>
    static void error(const String& message, Args... args)
    {
        log(LogLevel::Error, fmt::format(message, args...));
    }

private:
    Logger() = default;
    static void log(LogLevel level, const String& message);

private:
    static Logger* sInstance;

    std::set<BaseLoggerSink*> mSinks;
};
}

// Fluffy core log macros
#define FLUFFY_LOG_DEBUG(...) Fluffy::Logger::debug(__VA_ARGS__)
#define FLUFFY_LOG_INFO(...) Fluffy::Logger::info(__VA_ARGS__)
#define FLUFFY_LOG_WARN(...) Fluffy::Logger::warn(__VA_ARGS__)
#define FLUFFY_LOG_ERROR(...) Fluffy::Logger::error(__VA_ARGS__)

std::ostream& operator<<(std::ostream& os, Fluffy::LogLevel level);
