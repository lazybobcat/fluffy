#pragma once

#include <fluffy/file/path.hpp>
#include <fluffy/pch.hpp>
#include <json/json.h>

namespace Fluffy {

using Byte  = std::byte;
using Bytes = std::span<Byte>;

class Filesystem
{
public:
    static bool exists(const Path& path);

    // @todo :
    //static bool isFile(const Path& path);
    //static bool isDirectory(const Path& path);

    static Json::Value readJson(const Path& path);
    static Bytes       read(const Path& path);

    /**
     * Reads data from a file and put its content in a buffer
     *
     * @param buffer A simple pointer, allocation will be done by this function. The caller takes ownership of the data!
     * @param size Buffer size
     * @param path The file path
     */
    static bool read(char** buffer, std::size_t* size, const Path& path);

    static void write(const Path& path, const char* data, std::size_t size);
    // @todo :
    /*
    static void write(const Path& path, const Bytes& data);
    static bool createDir(const Path& p);

    static int64_t getLastWriteTime(const Path& p);

    static void copyFile(const Path& src, const Path& dest);
    static bool remove(const Path& path);
    static std::vector<Path> list(const Path& path);

    static size_t fileSize(const Path& path);
     */
};
}