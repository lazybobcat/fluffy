#include <filesystem>
#include <fluffy/file/filesystem.hpp>

using namespace Fluffy;

Bytes Filesystem::read(const Path& path)
{
    Bytes contents;

    std::ifstream fp(path.toString(), std::ios::binary | std::ios::in);
    if (!fp.is_open()) {
        return contents;
    }

    fp.seekg(0, std::ios::end);
    size_t size = fp.tellg();
    fp.seekg(0, std::ios::beg);

    fp.read(reinterpret_cast<char*>(contents.data()), size);
    fp.close();

    return contents;
}

bool Filesystem::read(char** buffer, size_t* size, const Path& path)
{
    std::ifstream fp(path.toString(), std::ios::binary | std::ios::in);
    if (!fp.is_open()) {
        *size = 0;

        return false;
    }

    fp.seekg(0, std::ios::end);
    *size = fp.tellg();
    fp.seekg(0, std::ios::beg);

    *buffer = new char[*size];

    fp.read(*buffer, *size);
    fp.close();

    return true;
}

void Filesystem::write(const Path& path, const char* data, std::size_t size)
{
    std::ofstream fp(path.toString(), std::ios::binary | std::ios::out);
    fp.write(data, size);
    fp.close();
}

bool Filesystem::exists(const Path& path)
{
    return path.exists();
}

Json::Value Filesystem::readJson(const Path& path)
{
    Json::Value  value;
    Json::Reader reader;

    std::ifstream input;
    input.open(path.toString());

    if (!input.is_open()) {
        FLUFFY_LOG_ERROR("Unable to open file '{}' for serialization", path);

        return value;
    }

    try {
        input >> value;
    } catch (Json::RuntimeError& e) {
        FLUFFY_LOG_ERROR("An error occurred while deserializing file '{}': ", path, e.what());

        return value;
    }

    return value;
}
