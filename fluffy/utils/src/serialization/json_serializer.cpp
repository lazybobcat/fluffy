#include <fluffy/definitions.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/serialization/json_serializer.hpp>

using namespace Fluffy;

bool JsonSerializer::serializeToString(Fluffy::Serializable& input, String& output)
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

bool JsonSerializer::deserializeFromString(String& input, Fluffy::Serializable& output)
{
    Json::Value  value;
    Json::Reader reader;

    if (!reader.parse(input, value)) {
        FLUFFY_LOG_ERROR("An error occurred while deserializing json string: {}", input);

        return false;
    }

    output.deserialize(value);

    return true;
}

bool JsonSerializer::serializeToFile(Fluffy::Serializable& input, const Path& filepath)
{
    Json::Value value;
    input.serialize(value);

#if FLUFFY_DEBUG_COMPACT_JSON
    Json::FastWriter writer;
#else
    Json::StyledWriter writer;
#endif

    std::ofstream output;
    output.open(filepath.toString());

    if (!output.is_open()) {
        FLUFFY_LOG_ERROR("Unable to open file '{}' for serialization", filepath);

        return false;
    }

    output << writer.write(value);
    output.close();

    return true;
}

bool JsonSerializer::deserializeFromFile(const Path& filepath, Fluffy::Serializable& output)
{
    Json::Value  value;
    Json::Reader reader;

    std::ifstream input;
    input.open(filepath.toString());

    if (!input.is_open()) {
        FLUFFY_LOG_ERROR("Unable to open file '{}' for serialization", filepath);

        return false;
    }

    try {
        input >> value;
    } catch (Json::RuntimeError& e) {
        FLUFFY_LOG_ERROR("An error occurred while deserializing file '{}': ", filepath, e.what());

        return false;
    }

    output.deserialize(value);

    return true;
}
