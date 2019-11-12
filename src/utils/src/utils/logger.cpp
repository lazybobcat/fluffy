//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <ctime>
#include <fluffy/definitions.hpp>
#include <fluffy/text/string.hpp>
#include <fluffy/utils/logger.hpp>

using namespace Fluffy;

const std::string currentDateTime()
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

/*****************************************************/

Logger* Logger::mInstance = nullptr;

Logger* Logger::getInstance(unsigned int output)
{
    if (nullptr == Logger::mInstance) {
        Logger::mInstance = new Logger(output);
    } else {
        Logger::mInstance->setOutput(output);
    }

    return Logger::mInstance;
}

void Logger::deleteInstance()
{
    delete mInstance;
}

/*****************************************************/

Logger::Logger(unsigned int output)
  : mOutput(output)
  , mWarnings(0)
  , mErrors(0)
{
    mFile.open(FLUFFY_LOG_FILE, std::ios::trunc);
    if (!mFile.is_open()) {
        // throw exception
    }

    logToFile("<!doctype html>");
    logToFile("<html lang=\"fr-FR\">");
    logToFile("<head>");
    logToFile("\t<meta charset=\"utf-8\">");
    logToFile(printString("\t<title>Fluffy Logs - %1 (%2) - %3</title>", { FLUFFY_VERSION, STRING(FLUFFY_ENV), currentDateTime() }));
    logToFile("\t<style>body{font-size:15px;color:#000;background-color:#fff;} text,info,warning,error{display:block;} info{color:#3376FF;font-style:italic;} warning{color:#FF6A00;} error{color:#f00;font-weight:bold;}</style>");
    logToFile("</head>");
    logToFile("<body>");

    mFile.close();
}

Logger::~Logger()
{
    logToFile("</body>");
    logToFile("</html>");
}

void Logger::setOutput(unsigned int output)
{
    mOutput = output;
}

void Logger::log(LogType type, const std::string& message)
{
    if (nullptr == mInstance) {
        getInstance();
    }

    const std::string time = currentDateTime();

    if (mInstance->mOutput & File) {
        mInstance->logToFile(std::move(mInstance->formatAsHtml(type, message)), time);
    }

    if (mInstance->mOutput & StdOut) {
        mInstance->logToStdOut(std::move(mInstance->formatAsText(type, message)), time);
    }
}

std::string Logger::formatAsHtml(LogType type, const std::string& message)
{
    switch (type) {
        case LogType::Text:
            return "<text>" + message + "</text>";

        case LogType::Info:
            return "<info>" + message + "</info>";

        case LogType::Warning:
            return "<warning>" + message + "</warning>";

        case LogType::Error:
            return "<error>" + message + "</error>";
    }

    return message;
}

std::string Logger::formatAsText(LogType type, const std::string& message)
{
    switch (type) {
        case LogType::Text:
            return message;

        case LogType::Info:
            return "<info> " + message;

        case LogType::Warning:
            return "<warning> " + message;

        case LogType::Error:
            return "<error> " + message;
    }

    return message;
}

void Logger::logToFile(const std::string& message, const std::string& datetime)
{
    mFile.open(FLUFFY_LOG_FILE, std::ios::app);

    if (mFile.is_open()) {
        if (!datetime.empty()) {
            mFile << "<!-- " << datetime << " -->" << std::endl;
        }
        mFile << message << std::endl;
    }

    mFile.close();
}

void Logger::logToStdOut(const std::string& message, const std::string& datetime)
{
    if (!datetime.empty()) {
        std::cout << "[" << datetime << "] ";
    }
    std::cout << message << std::endl;
}

void Logger::logToConsole(const std::string& message, const std::string& datetime)
{
}
