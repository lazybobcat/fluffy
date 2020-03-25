#pragma once

#include <fluffy/pch.hpp>

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
    virtual ~BaseLoggerSink()                                    = default;
    virtual void log(LogLevel level, const std::string& message) = 0;

    void setLevel(LogLevel level) { mMinimumLevel = level; }
    bool canLog(LogLevel level) { return level >= mMinimumLevel; }

private:
    LogLevel mMinimumLevel = LogLevel::Debug;
};

class StdOutSink : public BaseLoggerSink
{
public:
    void log(LogLevel level, const std::string& message) override;

private:
    std::mutex mMutex;
};

class FileSink : public BaseLoggerSink
{
public:
    FileSink();
    void log(LogLevel level, const std::string& message) override;

private:
    std::mutex    mMutex;
    std::ofstream mFile;
};

class Logger
{
public:
    static void init(bool testMode = false);
    static void clear();

    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

private:
    Logger() = default;
    static void log(LogLevel level, const std::string& message);

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
