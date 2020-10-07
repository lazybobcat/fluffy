#pragma once

#include <fmt/format.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace Fluffy {
typedef glm::vec<2, float>         Vector2f;
typedef glm::vec<2, std::int32_t>  Vector2i;
typedef glm::vec<2, std::uint32_t> Vector2u;

typedef glm::vec<3, float>         Vector3f;
typedef glm::vec<3, std::int32_t>  Vector3i;
typedef glm::vec<3, std::uint32_t> Vector3u;

typedef glm::vec<4, float>         Vector4f;
typedef glm::vec<4, std::int32_t>  Vector4i;
typedef glm::vec<4, std::uint32_t> Vector4u;
}

template<>
struct fmt::formatter<Fluffy::Vector2f>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector2f& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec2f{{{}, {}}}", v.x, v.y);
    }
};

template<>
struct fmt::formatter<Fluffy::Vector2i>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector2i& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec2i{{{}, {}}}", v.x, v.y);
    }
};

template<>
struct fmt::formatter<Fluffy::Vector2u>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector2u& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec2u{{{}, {}}}", v.x, v.y);
    }
};

template<>
struct fmt::formatter<Fluffy::Vector3f>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector3f& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec3f{{{}, {}, {}}}", v.x, v.y, v.z);
    }
};

template<>
struct fmt::formatter<Fluffy::Vector3i>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector3i& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec3i{{{}, {}, {}}}", v.x, v.y, v.z);
    }
};

template<>
struct fmt::formatter<Fluffy::Vector3u>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector3u& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec3u{{{}, {}, {}}}", v.x, v.y, v.z);
    }
};

template<>
struct fmt::formatter<Fluffy::Vector4f>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector4f& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec4f{{{}, {}, {}, {}}}", v.r, v.g, v.b, v.a);
    }
};

template<>
struct fmt::formatter<Fluffy::Vector4i>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector4i& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec4i{{{}, {}, {}, {}}}", v.r, v.g, v.b, v.a);
    }
};

template<>
struct fmt::formatter<Fluffy::Vector4u>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Vector4u& v, FormatContext& ctx)
    {
        return format_to(ctx.out(), "Vec4u{{{}, {}, {}, {}}}", v.r, v.g, v.b, v.a);
    }
};

template<>
struct fmt::formatter<glm::mat4>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const glm::mat4& m, FormatContext& ctx)
    {
        return format_to(ctx.out(), "mat4{{\n{}\n{}\n{}\n{}\n}}", m[0], m[1], m[2], m[3]);
    }
};