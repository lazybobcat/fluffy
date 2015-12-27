//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_LOGGER_HPP
#define FLUFFY_LOGGER_HPP

#include <Fluffy/Utility/NonCopyable.hpp>
#include <fstream>
#include <iostream>

namespace Fluffy
{
namespace Utility
{

class Logger : NonCopyable
{
public:
    enum class LogType
    {
        Info,
        Text,
        Warning,
        Error,
    };

    enum LogOutput
    {
        None    = 0,
        File    = 1 << 0,
        StdOut  = 1 << 1,
        Console = 1 << 2,
    };

public:
    ~Logger();

    static Logger*  getInstance(unsigned int output = File | StdOut);
    static void     deleteInstance();
    void            setOutput(unsigned int output);

    static void     log(LogType type, const std::string& message);

private:
    Logger(unsigned int output = File | StdOut);

    std::string formatAsHtml(LogType type, const std::string& message);
    std::string formatAsText(LogType type, const std::string& message);
    void        logToFile(const std::string& message, const std::string& datetime = "");
    void        logToStdOut(const std::string& message, const std::string& datetime = "");
    void        logToConsole(const std::string& message, const std::string& datetime = "");

private:
    static Logger*      mInstance;

    unsigned int        mOutput;
    std::ofstream       mFile;

    unsigned int        mWarnings;
    unsigned int        mErrors;
};

}
}

#endif //FLUFFY_LOGGER_HPP
