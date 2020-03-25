#include <fluffy/definitions.hpp>
#include <fluffy/serialization/json_serializer.hpp>

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
        FLUFFY_LOG_ERROR("An error occurred while deserializing json string: " + input);

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
        FLUFFY_LOG_ERROR("Unable to open file '" + filepath + "' for serialization");

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
        FLUFFY_LOG_ERROR("Unable to open file '" + filepath + "' for serialization");

        return false;
    }

    try {
        input >> value;
    } catch (Json::RuntimeError& e) {
        FLUFFY_LOG_ERROR("An error occurred while deserializing file '" + filepath + "': " + e.what());

        return false;
    }

    output.deserialize(value);

    return true;
}
