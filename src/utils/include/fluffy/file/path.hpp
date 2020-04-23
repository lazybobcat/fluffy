#pragma once

#include <filesystem>
#include <fluffy/text/string.hpp>
#include <fmt/format.h>

namespace Fluffy {

class Path
{
public:
    Path() = default;
    Path(const char* name);
    Path(const String& name);

    Path(const Path& other) = default;
    Path(Path&& other)      = default;
    Path& operator=(const Path& other) = default;
    Path& operator=(Path&& other) = default;
    Path& operator                =(const String& other);

    Path operator/(const char* other) const;
    Path operator/(const Path& other) const;
    Path operator/(const String& other) const;

    bool operator==(const char* other) const;
    bool operator==(const Path& other) const;
    bool operator!=(const Path& other) const;

    [[nodiscard]] String toString() const;

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
    void changePath(const String& name);
    void normalize();

private:
    std::filesystem::path mPath;
};

std::ostream& operator<<(std::ostream& os, const Path& p);
}

template<>
struct fmt::formatter<Fluffy::Path>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Path& p, FormatContext& ctx)
    {
        return format_to(ctx.out(), "{}", p.toString());
    }
};
