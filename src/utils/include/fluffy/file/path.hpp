#pragma once

#include <filesystem>

namespace Fluffy {

class Path
{
public:
    Path() = default;
    Path(const char* name);
    Path(const std::string& name);

    Path(const Path& other) = default;
    Path(Path&& other)      = default;
    Path& operator=(const Path& other) = default;
    Path& operator=(Path&& other) = default;
    Path& operator                =(const std::string& other);

    Path operator/(const char* other) const;
    Path operator/(const Path& other) const;
    Path operator/(const std::string& other) const;

    bool operator==(const char* other) const;
    bool operator==(const Path& other) const;
    bool operator!=(const Path& other) const;

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] bool exists() const;
    [[nodiscard]] bool isDirectory() const;
    [[nodiscard]] bool isFile() const;
    [[nodiscard]] bool isAbsolute() const;
    [[nodiscard]] bool isEmpty() const;

    void clear();

    [[nodiscard]] Path getParent() const;
    [[nodiscard]] Path getFilename() const;
    [[nodiscard]] Path getFileStem() const;
    [[nodiscard]] Path getFileExtension() const;

    static Path getWorkingDirectory();

private:
    explicit Path(const std::filesystem::path& path);
    void changePath(const std::string& name);
    void normalize();

private:
    std::filesystem::path mPath;
};

std::ostream& operator<<(std::ostream& os, const Path& p);
}
