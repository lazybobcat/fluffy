//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/04/18.
//

#include <fluffy/definitions.hpp>
#include <fluffy/serialization/json_serializer.hpp>
#include <fluffy/utils/logger.hpp>
#include <fluffy/text/string.hpp>
#include <fstream>

using namespace Fluffy;

bool JsonSerializer::serializeToString(Fluffy::Serializable& input, std::string& output)
{
    Json::Value value;
    input.serialize(value);

#if FLUFFY_DEBUG_COMPACT_JSON
    Json::FastWriter writer;
#else
    Json::StyledWriter writer;
#endif

    output = writer.write(value);

    return true;
}

bool JsonSerializer::deserializeFromString(std::string& input, Fluffy::Serializable& output)
{
    Json::Value  value;
    Json::Reader reader;

    if (!reader.parse(input, value)) {
        Logger::log(Logger::LogType::Error, printString("An error occurred while deserializing json string: %1", { input }));

        return false;
    }

    output.deserialize(value);

    return true;
}

bool JsonSerializer::serializeToFile(Fluffy::Serializable& input, std::string& filepath)
{
    Json::Value value;
    input.serialize(value);

#if FLUFFY_DEBUG_COMPACT_JSON
    Json::FastWriter writer;
#else
    Json::StyledWriter writer;
#endif

    std::ofstream output;
    output.open(filepath);

    if (!output.is_open()) {
        Logger::log(Logger::LogType::Error, printString("Unable to open file '%1' for serialization", { filepath }));

        return false;
    }

    output << writer.write(value);
    output.close();

    return true;
}

bool JsonSerializer::deserializeFromFile(std::string& filepath, Fluffy::Serializable& output)
{
    Json::Value  value;
    Json::Reader reader;

    std::ifstream input;
    input.open(filepath);

    if (!input.is_open()) {
        Logger::log(Logger::LogType::Error, printString("Unable to open file '%1' for deserialization", { filepath }));

        return false;
    }

    try {
        input >> value;
    } catch (Json::RuntimeError& e) {
        Logger::log(Logger::LogType::Error, printString("An error occurred while deserializing file '%1': %2", { filepath, e.what() }));

        return false;
    }

    output.deserialize(value);

    return true;
}
